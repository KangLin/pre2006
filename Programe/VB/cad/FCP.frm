VERSION 5.00
Begin VB.Form FCP 
   Caption         =   "确定圆角和切角的参数"
   ClientHeight    =   4005
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4935
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   4005
   ScaleWidth      =   4935
   StartUpPosition =   1  '所有者中心
   Begin VB.CheckBox Ch 
      Caption         =   "参数保存到配置文件中"
      Height          =   255
      Left            =   720
      TabIndex        =   10
      Top             =   2880
      Width           =   2535
   End
   Begin VB.Frame Frame2 
      Caption         =   "圆角"
      Height          =   855
      Left            =   360
      TabIndex        =   7
      Top             =   1800
      Width           =   3975
      Begin VB.TextBox Text1 
         Height          =   270
         Index           =   2
         Left            =   2040
         TabIndex        =   9
         Text            =   "100"
         Top             =   360
         Width           =   1455
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "圆角的半径"
         Height          =   180
         Index           =   2
         Left            =   360
         TabIndex        =   8
         Top             =   480
         Width           =   900
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "切角"
      Height          =   1335
      Left            =   360
      TabIndex        =   2
      Top             =   240
      Width           =   3975
      Begin VB.TextBox Text1 
         Height          =   270
         Index           =   1
         Left            =   2280
         TabIndex        =   6
         Text            =   "100"
         Top             =   840
         Width           =   1455
      End
      Begin VB.TextBox Text1 
         Height          =   270
         Index           =   0
         Left            =   2280
         TabIndex        =   5
         Text            =   "100"
         Top             =   360
         Width           =   1455
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "第二条切角线的距离"
         Height          =   180
         Index           =   1
         Left            =   240
         TabIndex        =   4
         Top             =   960
         Width           =   1620
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "第一条切角线的距离"
         Height          =   180
         Index           =   0
         Left            =   240
         TabIndex        =   3
         Top             =   480
         Width           =   1620
      End
   End
   Begin VB.CommandButton C_candle 
      Caption         =   "取消"
      Height          =   375
      Left            =   2760
      TabIndex        =   1
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CommandButton c_ok 
      Caption         =   "确定"
      Height          =   375
      Left            =   600
      TabIndex        =   0
      Top             =   3360
      Width           =   1215
   End
End
Attribute VB_Name = "FCP"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'作者:康林

Private Sub C_candle_Click()
        Unload Me
End Sub

Private Sub c_ok_Click()
Dim i
        ChamferFirstDistance = Text1(0).text
        ChamferSecondDistance = Text1(1).text
        FilletRadius = Text1(2).text
        If Ch.Value = tbrCheck Then
           i = WritePrivateProfileString("圆角和切角的参数", "切角的第一条距离", CStr(Text1(0).text), Inifile)
           i = WritePrivateProfileString("圆角和切角的参数", "切角的第二条距离", CStr(Text1(1).text), Inifile)
           i = WritePrivateProfileString("圆角和切角的参数", "圆角的半径", CStr(Text1(2).text), Inifile)
        End If
        Unload Me
End Sub

Private Sub Ch_Click()
Dim i
        i = WritePrivateProfileString("圆角和切角的参数", "保存到配置文件中", CStr(Ch.Value), Inifile)
End Sub

Private Sub Form_Load()
Dim i, ss As String * 20
        Text1(0).text = ChamferFirstDistance
        Text1(1).text = ChamferSecondDistance
        Text1(2).text = FilletRadius
        i = GetPrivateProfileString("圆角和切角的参数", "保存到配置文件中", 0, ss, 20, Inifile)
        If i = 0 Then ss = "0"
        Ch.Value = Val(ss)
End Sub
