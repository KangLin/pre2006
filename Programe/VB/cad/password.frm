VERSION 5.00
Begin VB.Form PassWord 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "密码"
   ClientHeight    =   1545
   ClientLeft      =   2835
   ClientTop       =   3480
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   912.837
   ScaleMode       =   0  'User
   ScaleWidth      =   3521.047
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox txtUserName 
      Height          =   345
      Left            =   1290
      TabIndex        =   1
      Top             =   135
      Width           =   2325
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   4
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "取消"
      Height          =   390
      Left            =   2100
      TabIndex        =   5
      Top             =   1020
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1290
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   525
      Width           =   2325
   End
   Begin VB.Label TiShi 
      AutoSize        =   -1  'True
      Caption         =   "Label1"
      Height          =   180
      Left            =   120
      TabIndex        =   6
      Top             =   120
      Visible         =   0   'False
      Width           =   540
   End
   Begin VB.Label LB 
      Caption         =   "用户名称(&U):"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label LB 
      Caption         =   "密码(&P):"
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   2
      Top             =   540
      Width           =   1080
   End
End
Attribute VB_Name = "PassWord"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'登录框
'作者:康林

Option Explicit

Public LoginSucceeded As Boolean
Public PassWordText As String
Public PassWordStyle As String
Dim i

Private Sub cmdCancel_Click()
    '设置全局变量为 false
    '不提示失败的登录
    LoginSucceeded = False
    Unload Me
End Sub

Private Sub cmdOK_Click()
    '检查正确的密码
    If txtPassword = PassWordText Then
        '将代码放在这里传递
        '成功到 calling 函数
        LoginSucceeded = True
        Unload Me
    Else
        If i < 3 Then
           MsgBox "无效的密码，请重试!", , Me.Caption
           txtPassword.SetFocus
           SendKeys "{Home}+{End}"
           i = i + 1
        Else
           LoginSucceeded = False
           Unload Me
        End If
    End If
End Sub

Private Sub Form_Load()
LoginSucceeded = False '初始化
i = 0
txtPassword = ""
Me.Caption = "密码"
        Select Case PassWordStyle
               Case "实体列表"
                    LB(0).Visible = False
                    txtUserName.Visible = False
                    TiShi.Caption = "此功能仅供程序员使用,请输入密码:"
                    Me.Caption = "实体列表密码"
                    TiShi.Visible = True
                    PassWordText = "~!@#$%^&*()KangLin)(*&^%$#@!~"
        End Select
End Sub
