VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmPeerA 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.TextBox txtOutput 
      Height          =   855
      Left            =   1680
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   1320
      Width           =   2175
   End
   Begin VB.TextBox txtSend 
      Height          =   495
      Left            =   1800
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   360
      Width           =   1455
   End
   Begin MSWinsockLib.Winsock udpPeerA 
      Left            =   600
      Top             =   480
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
      Protocol        =   1
   End
End
Attribute VB_Name = "frmPeerA"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
With udpPeerA
     .RemoteHost = "127.0.0.1"
     .RemotePort = 2001
     .LocalPort = 2001
     .Bind 2000
End With
frmPeerB.Show
End Sub

Private Sub txtSend_Change()
udpPeerA.SendData txtSend.Text
End Sub

Private Sub udpPeerA_DataArrival(ByVal bytesTotal As Long)
Dim strData As String
udpPeerA.GetData strData
txtOutput.Text = strData
End Sub

