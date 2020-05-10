VERSION 5.00
Begin VB.Form frmFind 
   Caption         =   "查找"
   ClientHeight    =   7620
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11040
   LinkTopic       =   "Form1"
   ScaleHeight     =   7620
   ScaleWidth      =   11040
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton cmdCondition 
      Caption         =   "查找条件"
      Height          =   375
      Left            =   4920
      TabIndex        =   12
      Top             =   6960
      Width           =   1335
   End
   Begin VB.TextBox txtDir 
      Height          =   375
      Left            =   1200
      TabIndex        =   11
      Text            =   "Text1"
      Top             =   360
      Width           =   6255
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "退出"
      Height          =   375
      Left            =   9360
      TabIndex        =   9
      Top             =   6960
      Width           =   1575
   End
   Begin VB.CommandButton cmdFindWord 
      Caption         =   "查找含有此词的文件"
      Height          =   375
      Left            =   2520
      TabIndex        =   8
      Top             =   6960
      Width           =   1815
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "取消"
      Height          =   375
      Left            =   7200
      TabIndex        =   7
      Top             =   6960
      Width           =   1455
   End
   Begin VB.CommandButton cmdFindFile 
      Caption         =   "查找文件"
      Height          =   375
      Left            =   480
      TabIndex        =   6
      Top             =   6960
      Width           =   1575
   End
   Begin VB.DirListBox Dir 
      Height          =   2400
      Left            =   7800
      TabIndex        =   5
      Top             =   960
      Width           =   3015
   End
   Begin VB.TextBox txtFileName 
      Height          =   375
      Left            =   1200
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   1080
      Width           =   6255
   End
   Begin VB.FileListBox File 
      Height          =   3330
      Left            =   7800
      TabIndex        =   2
      Top             =   3480
      Width           =   3015
   End
   Begin VB.DriveListBox Driver 
      Height          =   300
      Left            =   7800
      TabIndex        =   1
      Top             =   480
      Width           =   3015
   End
   Begin VB.ListBox lstFileName 
      Height          =   4920
      Left            =   360
      TabIndex        =   0
      Top             =   1680
      Width           =   7095
   End
   Begin VB.Label Label2 
      Caption         =   "目录:"
      Height          =   375
      Left            =   120
      TabIndex        =   10
      Top             =   360
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "查找内容:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1200
      Width           =   1095
   End
End
Attribute VB_Name = "frmFind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Const SW_SHOW = 5

Private Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" (ByVal hwnd As Long, ByVal lpOperation As String, ByVal lpFile As String, ByVal lpParameters As String, ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long

Dim WithEvents m_objFile As CFile
Attribute m_objFile.VB_VarHelpID = -1
Dim m_bCancel As Boolean
Dim m_bExit As Boolean
Private Enum ENUM_OPERATOR
        findfile
        findword
End Enum

Dim m_Operator As ENUM_OPERATOR   '操作

Private Sub cmdCancel_Click()
m_bCancel = True
m_bExit = True
End Sub

Private Sub cmdCondition_Click()
frmSearchCondition.Show vbModal, Me
End Sub

Private Sub cmdExit_Click()
Unload Me
End Sub

Private Sub Dir_Change()
File.Path = Dir
txtDir.Text = Dir
End Sub

Private Sub Dir_Click()
File.Path = Dir
End Sub

Private Sub Driver_Change()
Dir.Path = Driver
End Sub

Private Sub Form_Load()
lstFileName.Clear
txtFileName.Text = ""
m_bExit = True
txtDir.Text = Dir
Set m_objFile = New CFile
End Sub

Private Sub Form_Unload(Cancel As Integer)
If Not m_bExit Then
   MsgBox "查找正在进行,先取消操作"
   Cancel = 1
End If
End Sub

Private Sub cmdFindFile_Click()
Operator findfile
End Sub

Private Sub cmdFindWord_Click()
Operator findword
End Sub

Private Function Operator(ByVal op As ENUM_OPERATOR)
m_bCancel = False
m_bExit = False
m_Operator = op
Call m_objFile.FindAllFiles(txtDir)
m_bExit = True
End Function

Private Sub lstFileName_DblClick()
ShellExecute Me.hwnd, "", lstFileName.List(lstFileName.ListIndex), "", "", SW_SHOW
End Sub

Private Sub m_objFile_fFoundFilesEvent(ByVal strFoundFileName As String, bCancle As Boolean)
Dim FileNum As Integer
Dim szFile As String
Select Case m_Operator
Case findfile
     If LCase(m_objFile.fGetFileTitle(strFoundFileName)) Like LCase(txtFileName.Text) Then
        lstFileName.AddItem strFoundFileName
     End If
Case findword
     FileNum = FreeFile()
     Open strFoundFileName For Input As #FileNum
     While Not EOF(FileNum)
           Line Input #FileNum, szFile
           If szFile Like ("*" & txtFileName.Text & "*") Then
              Close #FileNum
              lstFileName.AddItem strFoundFileName
              Exit Sub
           End If
     Wend
     Close #FileNum
End Select
bCancle = m_bCancel
End Sub
