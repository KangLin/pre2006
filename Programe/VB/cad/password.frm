VERSION 5.00
Begin VB.Form PassWord 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "����"
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
      Caption         =   "ȷ��"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   4
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "ȡ��"
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
      Caption         =   "�û�����(&U):"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label LB 
      Caption         =   "����(&P):"
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
'��¼��
'����:����

Option Explicit

Public LoginSucceeded As Boolean
Public PassWordText As String
Public PassWordStyle As String
Dim i

Private Sub cmdCancel_Click()
    '����ȫ�ֱ���Ϊ false
    '����ʾʧ�ܵĵ�¼
    LoginSucceeded = False
    Unload Me
End Sub

Private Sub cmdOK_Click()
    '�����ȷ������
    If txtPassword = PassWordText Then
        '������������ﴫ��
        '�ɹ��� calling ����
        LoginSucceeded = True
        Unload Me
    Else
        If i < 3 Then
           MsgBox "��Ч�����룬������!", , Me.Caption
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
LoginSucceeded = False '��ʼ��
i = 0
txtPassword = ""
Me.Caption = "����"
        Select Case PassWordStyle
               Case "ʵ���б�"
                    LB(0).Visible = False
                    txtUserName.Visible = False
                    TiShi.Caption = "�˹��ܽ�������Աʹ��,����������:"
                    Me.Caption = "ʵ���б�����"
                    TiShi.Visible = True
                    PassWordText = "~!@#$%^&*()KangLin)(*&^%$#@!~"
        End Select
End Sub
