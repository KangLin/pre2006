VERSION 5.00
Begin VB.Form FCP 
   Caption         =   "ȷ��Բ�Ǻ��нǵĲ���"
   ClientHeight    =   4005
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4935
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   4005
   ScaleWidth      =   4935
   StartUpPosition =   1  '����������
   Begin VB.CheckBox Ch 
      Caption         =   "�������浽�����ļ���"
      Height          =   255
      Left            =   720
      TabIndex        =   10
      Top             =   2880
      Width           =   2535
   End
   Begin VB.Frame Frame2 
      Caption         =   "Բ��"
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
         Caption         =   "Բ�ǵİ뾶"
         Height          =   180
         Index           =   2
         Left            =   360
         TabIndex        =   8
         Top             =   480
         Width           =   900
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "�н�"
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
         Caption         =   "�ڶ����н��ߵľ���"
         Height          =   180
         Index           =   1
         Left            =   240
         TabIndex        =   4
         Top             =   960
         Width           =   1620
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "��һ���н��ߵľ���"
         Height          =   180
         Index           =   0
         Left            =   240
         TabIndex        =   3
         Top             =   480
         Width           =   1620
      End
   End
   Begin VB.CommandButton C_candle 
      Caption         =   "ȡ��"
      Height          =   375
      Left            =   2760
      TabIndex        =   1
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CommandButton c_ok 
      Caption         =   "ȷ��"
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
'����:����

Private Sub C_candle_Click()
        Unload Me
End Sub

Private Sub c_ok_Click()
Dim i
        ChamferFirstDistance = Text1(0).text
        ChamferSecondDistance = Text1(1).text
        FilletRadius = Text1(2).text
        If Ch.Value = tbrCheck Then
           i = WritePrivateProfileString("Բ�Ǻ��нǵĲ���", "�нǵĵ�һ������", CStr(Text1(0).text), Inifile)
           i = WritePrivateProfileString("Բ�Ǻ��нǵĲ���", "�нǵĵڶ�������", CStr(Text1(1).text), Inifile)
           i = WritePrivateProfileString("Բ�Ǻ��нǵĲ���", "Բ�ǵİ뾶", CStr(Text1(2).text), Inifile)
        End If
        Unload Me
End Sub

Private Sub Ch_Click()
Dim i
        i = WritePrivateProfileString("Բ�Ǻ��нǵĲ���", "���浽�����ļ���", CStr(Ch.Value), Inifile)
End Sub

Private Sub Form_Load()
Dim i, ss As String * 20
        Text1(0).text = ChamferFirstDistance
        Text1(1).text = ChamferSecondDistance
        Text1(2).text = FilletRadius
        i = GetPrivateProfileString("Բ�Ǻ��нǵĲ���", "���浽�����ļ���", 0, ss, 20, Inifile)
        If i = 0 Then ss = "0"
        Ch.Value = Val(ss)
End Sub
