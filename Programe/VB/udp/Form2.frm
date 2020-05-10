VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form Form2 
   Caption         =   "Form2"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.TextBox Text1 
      Height          =   735
      Left            =   1440
      TabIndex        =   2
      Text            =   "Text1"
      Top             =   0
      Width           =   1935
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   1440
      TabIndex        =   1
      Text            =   "Text2"
      Top             =   960
      Width           =   1935
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   1440
      TabIndex        =   0
      Top             =   1920
      Width           =   1335
   End
   Begin MSWinsockLib.Winsock SockServer 
      Left            =   0
      Top             =   0
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
SockServer.SendData Text2.Text
End Sub

Private Sub Form_Load()
With SockServer
     .RemoteHost = "127.0.0.1"
     .RemotePort = 2000
     .Connect
End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
SockServer.Close
End Sub

Private Sub SockServer_Close()
SockServer.Close
End Sub

Private Sub SockServer_DataArrival(ByVal bytesTotal As Long)
Dim s As String
SockServer.GetData s
Text1.Text = s
End Sub

