VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   2160
      TabIndex        =   2
      Top             =   2520
      Width           =   1335
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   2160
      TabIndex        =   1
      Text            =   "Text2"
      Top             =   1560
      Width           =   1935
   End
   Begin VB.TextBox Text1 
      Height          =   735
      Left            =   2160
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   600
      Width           =   1935
   End
   Begin MSWinsockLib.Winsock SockServer 
      Left            =   720
      Top             =   600
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
SockServer.SendData Text2.Text
End Sub

Private Sub Form_Load()
SockServer.LocalPort = 2000
SockServer.Listen
Form2.Show
End Sub

Private Sub Form_Unload(Cancel As Integer)
SockServer.Close
End Sub

Private Sub SockServer_Close()
SockServer.Close
End Sub

Private Sub SockServer_ConnectionRequest(ByVal requestID As Long)
SockServer.Close
SockServer.Accept requestID
End Sub

Private Sub SockServer_DataArrival(ByVal bytesTotal As Long)
Dim s As String
SockServer.GetData s
Text1.Text = s
End Sub

