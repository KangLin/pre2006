VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmReadSet 
   Caption         =   "����"
   ClientHeight    =   2040
   ClientLeft      =   60
   ClientTop       =   750
   ClientWidth     =   6795
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   2040
   ScaleWidth      =   6795
   StartUpPosition =   2  '��Ļ����
   Begin VB.CommandButton cmdCancel 
      Caption         =   "ȡ��(&C)"
      Height          =   255
      Left            =   4200
      TabIndex        =   7
      Top             =   1440
      Width           =   1095
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "ȷ��(&O)"
      Height          =   255
      Left            =   1320
      TabIndex        =   6
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton cmdBroweFile 
      Caption         =   "���(&B)"
      Height          =   255
      Left            =   5640
      TabIndex        =   5
      Top             =   840
      Width           =   855
   End
   Begin VB.TextBox txtReadFile 
      Height          =   270
      Left            =   1320
      TabIndex        =   4
      Top             =   840
      Width           =   4215
   End
   Begin VB.CommandButton cmdBroweReader 
      Caption         =   "���(&B)"
      Height          =   255
      Left            =   5640
      TabIndex        =   2
      Top             =   360
      Width           =   855
   End
   Begin MSComDlg.CommonDialog Cmd 
      Left            =   480
      Top             =   1200
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.TextBox txtReader 
      Height          =   270
      Left            =   1320
      TabIndex        =   0
      Top             =   240
      Width           =   4215
   End
   Begin VB.Label Label2 
      Caption         =   "�����ļ�:"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "�Ķ���:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   735
   End
   Begin VB.Menu munFile 
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu mnuExit 
         Caption         =   "�˳�(&E)"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "����(&H)"
   End
End
Attribute VB_Name = "frmReadSet"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdBroweFile_Click()
With Cmd
     .FileName = ""
     .InitDir = App.Path
     .ShowOpen
     If .FileName <> "" Then
        txtReadFile.Text = .FileTitle
     End If
End With
End Sub

Private Sub cmdBroweReader_Click()
With Cmd
     .FileName = ""
     .ShowOpen
     If .FileName <> "" Then
        txtReader.Text = .FileName
     End If
End With
End Sub

Private Sub cmdCancel_Click()
Unload Me
End Sub

Private Sub cmdOK_Click()
WriteIniFile szIniFile, "����", "�Ķ���", txtReader.Text
WriteIniFile szIniFile, "����", "�ļ�", txtReadFile.Text
Unload Me
End Sub

Private Sub Form_Load()
txtReader.Text = ReadIniFile(szIniFile, "����", "�Ķ���")
txtReadFile.Text = ReadIniFile(szIniFile, "����", "�ļ�")
End Sub

Private Sub mnuExit_Click()
Unload Me
End Sub

Private Sub mnuHelp_Click()
frmAbout.Show vbModal
End Sub
