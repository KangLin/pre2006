VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "删除文件中的空行"
   ClientHeight    =   6225
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11040
   LinkTopic       =   "Form1"
   ScaleHeight     =   6225
   ScaleWidth      =   11040
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton cmdClearFileList 
      Caption         =   "清除文件列表"
      Height          =   375
      Left            =   7440
      TabIndex        =   9
      Top             =   5280
      Width           =   1575
   End
   Begin VB.CommandButton cmdSelectFile 
      Caption         =   "选择所有文件"
      Height          =   375
      Left            =   5160
      TabIndex        =   8
      Top             =   5280
      Width           =   1575
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "取消"
      Height          =   375
      Left            =   2880
      TabIndex        =   7
      Top             =   5280
      Width           =   1455
   End
   Begin VB.CommandButton cmdDeletSpace 
      Caption         =   "删除空行"
      Height          =   375
      Left            =   480
      TabIndex        =   6
      Top             =   5280
      Width           =   1575
   End
   Begin VB.DirListBox Dir 
      Height          =   1560
      Left            =   7800
      TabIndex        =   5
      Top             =   960
      Width           =   3015
   End
   Begin VB.TextBox txtFileName 
      Height          =   375
      Left            =   720
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   360
      Width           =   6855
   End
   Begin VB.FileListBox File 
      Height          =   1890
      Left            =   7800
      TabIndex        =   2
      Top             =   2760
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
      Height          =   3660
      Left            =   360
      TabIndex        =   0
      Top             =   960
      Width           =   7095
   End
   Begin VB.Label Label1 
      Caption         =   "文件:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   480
      Width           =   615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdCancel_Click()
Unload Me
End Sub

Private Sub cmdClearFileList_Click()
lstFileName.Clear
End Sub

Private Sub cmdDeletSpace_Click()
Dim InNum As Integer, OutNum As Integer
Dim i As Integer, str As String, tmpStr As String
For i = 0 To lstFileName.ListCount - 1
    InNum = FreeFile()
    OutNum = FreeFile() + 1
    Open lstFileName.List(i) For Input As #InNum
    Open lstFileName.List(i) & ".txt" For Output As #OutNum
    While Not EOF(InNum)
          Line Input #InNum, str
          If Trim(Replace(str, vbTab, Space(1))) <> "" Then
             Print #OutNum, str
          End If
    Wend
    Close #OutNum
    Close #InNum
Next i
End Sub

Private Sub cmdSelectFile_Click()
Dim i As Integer
For i = 0 To File.ListCount - 1
    If Right(File.Path, 1) = "\" Then
       lstFileName.AddItem File.Path & File.List(i)
    Else
       lstFileName.AddItem File.Path & "\" & File.List(i)
    End If
Next i
End Sub

Private Sub Dir_Change()
File.Path = Dir
End Sub

Private Sub Dir_Click()
File.Path = Dir
End Sub

Private Sub Driver_Change()
Dir.Path = Driver
End Sub

Private Sub File_Click()
If Right(File.Path, 1) = "\" Then
   txtFileName.Text = File.Path & File.FileName
Else
   txtFileName.Text = File.Path & "\" & File.FileName
End If
End Sub

Private Sub File_DblClick()
lstFileName.AddItem txtFileName.Text
End Sub

Private Sub Form_Load()
lstFileName.Clear
txtFileName.Text = ""
End Sub
