VERSION 5.00
Begin VB.UserControl 服务端控件 
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   3600
   ScaleWidth      =   4800
End
Attribute VB_Name = "服务端控件"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
'缺省属性值:
Const m_def_LocalPort = 1976
'属性变量:
Dim m_LocalPort As Long

'Dim WithEvents objServer As CServer

Dim m_iCmdSck As Integer

'注意！不要删除或修改下列被注释的行！
'MemberInfo=8,0,0,1976
Public Property Get LocalPort() As Long
    LocalPort = m_LocalPort
End Property

Public Property Let LocalPort(ByVal New_LocalPort As Long)
    m_LocalPort = New_LocalPort
    PropertyChanged "LocalPort"
End Property

'为用户控件初始化属性
Private Sub UserControl_InitProperties()
    m_LocalPort = m_def_LocalPort
End Sub

'从存贮器中加载属性值
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    m_LocalPort = PropBag.ReadProperty("LocalPort", m_def_LocalPort)
    
    fInitProcude
End Sub

'将属性值写到存储器
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)

    Call PropBag.WriteProperty("LocalPort", m_LocalPort, m_def_LocalPort)
End Sub

Private Function fInitProcude()
        With sckCmdServer(0)
             .Protocol = sckTCPProtocol
             .LocalPort = m_LocalPort
             .Listen
        End With
End Function

Private Sub sckCmdServer_ConnectionRequest(Index As Integer, ByVal requestID As Long)
        If Index = 0 Then
           m_iCmdSck = m_iCmdSck + 1
           Load sckCmdServer(m_iCmdSck)
           With sckCmdServer(m_iCmdSck)
                .LocalPort = 0
                .Accept (requestID)
           End With
        End If
End Sub

Private Sub sckCmdServer_DataArrival(Index As Integer, ByVal bytesTotal As Long)

End Sub


