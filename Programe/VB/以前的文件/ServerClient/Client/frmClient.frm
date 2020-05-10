VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmClient 
   Caption         =   "客户端"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command3 
      Caption         =   "Command3"
      Height          =   375
      Left            =   3240
      TabIndex        =   2
      Top             =   1800
      Width           =   975
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Command2"
      Height          =   255
      Left            =   3600
      TabIndex        =   1
      Top             =   960
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   615
      Left            =   480
      TabIndex        =   0
      Top             =   960
      Width           =   2055
   End
   Begin MSWinsockLib.Winsock sckDataClient 
      Index           =   0
      Left            =   840
      Top             =   2160
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock sckCmdClient 
      Left            =   1080
      Top             =   240
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
   '调用 Connect 方法，初始化连接。
   sckCmdClient.Connect
End Sub

Private Sub Command2_Click()
Dim s As String
's = Trim(Str(cCmdGetLogicalDrives))
s = Trim(Str(cCmdFindFile)) & vbNullChar
s = s & "sys*" & vbNullChar
s = s & "c:\windows" & vbNullChar
s = s & sckDataClient(0).LocalIP & vbNullChar
s = s & Str(sckDataClient(0).LocalPort)
s = s & vbNullChar & vbNullChar

sckCmdClient.SendData s
End Sub

Private Sub Command3_Click()
Dim s As String
's = Trim(Str(cCmdGetLogicalDrives))
s = Trim(Str(cCmdCancel)) & vbNullChar & Chr(0)
sckCmdClient.SendData s
End Sub

Private Sub Form_Load()
   'Winsock 控件的名字为 tcpClient。
   '注意：要指定远程主机，可以使用
   ' IP 地址（例如："121.111.1.1"），也可以使用
   '计算机的“好听的名字”如下所示。
   With sckCmdClient
        .Protocol = sckTCPProtocol
        .RemoteHost = "127.0.0.1"
        .RemotePort = 1976
   End With
   With sckDataClient(0)
        .Protocol = sckTCPProtocol
        .LocalPort = 1999
        .Listen
   End With
End Sub


Private Sub sckCmdClient_DataArrival(ByVal bytesTotal As Long)
Dim s As String
Debug.Print "sckCmdClient_DataArrival"
sckCmdClient.GetData s
Debug.Print s
If 103 = fSplitString(s) Then
   Debug.Print fSplitString(s)
End If
End Sub

Private Sub sckDataClient_ConnectionRequest(Index As Integer, ByVal requestID As Long)
Load sckDataClient(sckDataClient.UBound + 1)
With sckDataClient(sckDataClient.UBound)
     .LocalPort = 0
     .Accept requestID
End With
End Sub

Private Sub sckDataClient_DataArrival(Index As Integer, ByVal bytesTotal As Long)
Dim s As String, a
Debug.Print "sckdataClient_DataArrival"
sckDataClient(Index).GetData s
Debug.Print s
End Sub
