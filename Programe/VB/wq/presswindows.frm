VERSION 5.00
Begin VB.Form presswindows 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   0  'None
   ClientHeight    =   1680
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   690
   LinkTopic       =   "Form3"
   LockControls    =   -1  'True
   ScaleHeight     =   1680
   ScaleWidth      =   690
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  '窗口缺省
   Begin VB.Label Label7 
      BackColor       =   &H0080FF80&
      Caption         =   "退出"
      Height          =   255
      Left            =   0
      TabIndex        =   6
      Top             =   1440
      Width           =   735
   End
   Begin VB.Label Label6 
      BackColor       =   &H0080FF80&
      Caption         =   "复盘"
      Height          =   255
      Left            =   0
      TabIndex        =   5
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label Label5 
      BackColor       =   &H0080FF80&
      Caption         =   "还原"
      Height          =   255
      Left            =   0
      TabIndex        =   4
      Top             =   960
      Width           =   735
   End
   Begin VB.Label Label4 
      BackColor       =   &H0080FF80&
      Caption         =   "悔棋"
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   720
      Width           =   735
   End
   Begin VB.Label Label3 
      BackColor       =   &H0080FF80&
      Caption         =   "提子"
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   480
      Width           =   735
   End
   Begin VB.Label Label2 
      BackColor       =   &H0080FF80&
      Caption         =   "走子"
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   240
      Width           =   735
   End
   Begin VB.Label Label1 
      BackColor       =   &H0080FF80&
      Caption         =   "重新开始"
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   735
   End
End
Attribute VB_Name = "presswindows"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public Sub presswin(X, Y)
Show
Label1.Enabled = True
Label2.Enabled = True
Label4.Enabled = True
Label5.Enabled = True
presswindows.Height = 1680
Label7.Top = presswindows.Height - Label7.Height
presswindows.Left = X + Form1.wqpang.Left
End Sub

Private Sub Label1_Click()
Form1.重新开始_Click
Unload Me
End Sub

Private Sub Label2_Click()
Form1.work_Click
Unload Me
End Sub

Private Sub Label3_Click()
Form1.eat_Click
Unload Me
End Sub

Private Sub Label4_Click()
Form1.悔棋_Click
Unload Me
End Sub

Private Sub Label5_Click()
Form1.RedoWeiqi
Unload Me
End Sub

Private Sub Label6_Click()
Label1.Enabled = False
Label2.Enabled = False
Label4.Enabled = False
Label5.Enabled = False
Form1.meunopen_Click
Unload Me
End Sub

Private Sub Label7_Click()
Form1.meunexit_Click
End Sub
