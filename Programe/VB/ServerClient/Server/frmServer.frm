VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmServer 
   Caption         =   "服务端"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  '窗口缺省
   Begin MSWinsockLib.Winsock sckDataServer 
      Index           =   0
      Left            =   1320
      Top             =   840
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock sckCmdServer 
      Index           =   0
      Left            =   0
      Top             =   1080
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
End
Attribute VB_Name = "frmServer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim m_LocalPort As Long
Dim m_iCmdSck As Integer 'sckCmdServer进行联接的个数
Dim objServer() As CServer '

Private Sub Form_Load()
        m_iCmdSck = 0
        ReDim objServer(0)
        With sckCmdServer(0)
             .Protocol = sckTCPProtocol
             '修改：下面的端口设置在实际中确定
            ' GetSetting "ServerClient", "LocalPort", m_LocalPort, "1976"
             .LocalPort = 1976
             .Listen
        End With
        Set objServer(0) = New CServer
End Sub

Private Sub Form_Unload(Cancel As Integer)
'Dim obj As Integer
'For Each obj In objServer
'    Set objServer(obj) = Nothing
'Next obj
End Sub

Private Sub sckCmdServer_ConnectionRequest(Index As Integer, ByVal requestID As Long)
        If Index = 0 Then
           m_iCmdSck = m_iCmdSck + 1
           Load sckCmdServer(m_iCmdSck)
           Load sckDataServer(m_iCmdSck)
           ReDim Preserve objServer(UBound(objServer) + 1)
           Set objServer(UBound(objServer)) = New CServer
           With sckCmdServer(m_iCmdSck)
                .LocalPort = 0
                .Accept requestID
           End With
        End If
End Sub

Private Sub sckCmdServer_DataArrival(Index As Integer, ByVal bytesTotal As Long)
        Set objServer(Index).sckDataServer = sckDataServer(Index)
        objServer(Index).fCommmand sckCmdServer(Index), bytesTotal
End Sub

