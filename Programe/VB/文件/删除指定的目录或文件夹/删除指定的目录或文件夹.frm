VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form Form1 
   Caption         =   "删除指定的目录或文件"
   ClientHeight    =   9285
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   9600
   LinkTopic       =   "Form1"
   ScaleHeight     =   9285
   ScaleWidth      =   9600
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtSelect 
      Height          =   375
      Left            =   120
      TabIndex        =   22
      Text            =   "Text1"
      Top             =   840
      Width           =   6135
   End
   Begin VB.ListBox lstDelete 
      Height          =   2985
      Left            =   120
      TabIndex        =   21
      Top             =   6120
      Width           =   9255
   End
   Begin MSComDlg.CommonDialog comDlg 
      Left            =   7680
      Top             =   4800
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame Frame1 
      Caption         =   "要删除的内容："
      Height          =   2295
      Left            =   120
      TabIndex        =   13
      Top             =   2280
      Width           =   6135
      Begin VB.CommandButton cmdOpen 
         Caption         =   "打开"
         Height          =   375
         Left            =   5160
         TabIndex        =   17
         ToolTipText     =   "从文件中加载要删除的项"
         Top             =   240
         Width           =   855
      End
      Begin VB.ListBox lstName 
         Height          =   1620
         Left            =   120
         MultiSelect     =   2  'Extended
         TabIndex        =   16
         Top             =   240
         Width           =   4815
      End
      Begin VB.CommandButton cmdDeletList 
         Caption         =   "删除"
         Height          =   375
         Left            =   5160
         TabIndex        =   15
         ToolTipText     =   "删除指定的项"
         Top             =   840
         Width           =   855
      End
      Begin VB.CommandButton cmdDeleteAll 
         Caption         =   "全部删除"
         Height          =   375
         Left            =   5160
         TabIndex        =   14
         ToolTipText     =   "删除所有的项"
         Top             =   1440
         Width           =   855
      End
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "退出"
      Height          =   375
      Left            =   5040
      TabIndex        =   12
      ToolTipText     =   "退出程序"
      Top             =   4800
      Width           =   1215
   End
   Begin VB.Frame frameDisp 
      Height          =   615
      Left            =   120
      TabIndex        =   8
      Top             =   5400
      Width           =   9255
      Begin VB.Label LabDelFile 
         Height          =   255
         Left            =   3840
         TabIndex        =   20
         Top             =   240
         Width           =   975
      End
      Begin VB.Label Label4 
         Caption         =   "个文件；"
         Height          =   255
         Index           =   1
         Left            =   4800
         TabIndex        =   19
         Top             =   240
         Width           =   735
      End
      Begin VB.Label Label5 
         Caption         =   "删除了"
         Height          =   255
         Left            =   3240
         TabIndex        =   18
         Top             =   240
         Width           =   615
      End
      Begin VB.Label Label4 
         Caption         =   "个文件；"
         Height          =   255
         Index           =   0
         Left            =   1920
         TabIndex        =   11
         Top             =   240
         Width           =   735
      End
      Begin VB.Label labFileCount 
         Height          =   255
         Left            =   720
         TabIndex        =   10
         Top             =   240
         Width           =   975
      End
      Begin VB.Label Label3 
         Caption         =   "查找了"
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   615
      End
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "增加"
      Height          =   375
      Left            =   5280
      TabIndex        =   7
      ToolTipText     =   "把此项加入到要删除的内容列表中"
      Top             =   1800
      Width           =   855
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "取消"
      Height          =   375
      Left            =   2640
      TabIndex        =   5
      ToolTipText     =   "取消命令的执行"
      Top             =   4800
      Width           =   1455
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "删除"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      ToolTipText     =   "开始删除"
      Top             =   4800
      Width           =   1575
   End
   Begin VB.DirListBox Dir 
      Height          =   3690
      Left            =   6360
      TabIndex        =   3
      Top             =   960
      Width           =   3015
   End
   Begin VB.TextBox txtFileName 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   1800
      Width           =   4815
   End
   Begin VB.DriveListBox Driver 
      Height          =   300
      Left            =   6360
      TabIndex        =   0
      Top             =   480
      Width           =   3015
   End
   Begin VB.Label Label2 
      Caption         =   "当前选择的文件夹:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   360
      Width           =   3255
   End
   Begin VB.Label Label1 
      Caption         =   "要删除的目录(只含当前目录名)或文件:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   1440
      Width           =   4815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Dim WithEvents ObjFile As CFile
Attribute ObjFile.VB_VarHelpID = -1
Dim m_bCancel As Boolean
Dim m_bExit As Boolean
Dim m_iCount As Integer
Dim m_fs As FileSystemObject

Private Sub cmdAdd_Click()
    If txtFileName.Text <> "" Then
       lstName.AddItem txtFileName.Text
    End If
    txtFileName.Text = ""
End Sub

Private Sub cmdCancel_Click()
    m_bCancel = True
    m_bExit = True
End Sub

Private Sub cmdDelete_Click()
    lstDelete.Clear
    m_bCancel = False
    m_iCount = 0
    frameDisp.Visible = True
    m_bExit = False
    ObjFile.FindAllFiles txtSelect.Text
    MsgBox "删除完成" & vbCrLf & "共删除 " & m_iCount & "个文件(或目录)"
    frameDisp.Visible = False
    m_bExit = True
End Sub

Private Sub cmdDeleteAll_Click()
    lstName.Clear
End Sub

Private Sub cmdDeletList_Click()
    Dim iCount As Integer, i As Integer
    iCount = lstName.ListCount - 1
    For i = iCount To 0 Step -1
        If lstName.Selected(i) Then
           lstName.RemoveItem i
        End If
    Next i
End Sub

Private Sub cmdExit_Click()
    Unload Me
End Sub

Private Sub cmdOpen_Click()
    comDlg.FileName = ""
    comDlg.ShowOpen
    If comDlg.FileName <> "" Then
        LoadItemFormFile comDlg.FileName
    End If
End Sub

Private Sub LoadItemFormFile(ByVal strFile As String)
    On Error GoTo Err_Exit
    Dim nFileNum As Integer
    Dim strInput As String
    
    nFileNum = FreeFile() + 1
    Open strFile For Input As #nFileNum
    Do While Not EOF(nFileNum)   ' 循环至文件尾。
        strInput = ""
        Line Input #nFileNum, strInput   ' 读入一行数据并将其赋予某变量。
        If strInput <> "" Then
            If Not InList(strInput) Then
                lstName.AddItem strInput
            End If
        End If
    Loop
    Close nFileNum
    Exit Sub
    
Err_Exit:
    MsgBox Err.Description
    Close nFileNum
End Sub

Private Sub Dir_Change()
   txtSelect.Text = Dir
End Sub

Private Sub Driver_Change()
    Dir.Path = Driver
End Sub

Private Sub Form_Load()
    frameDisp.Visible = False
    m_bExit = True
    txtFileName.Text = ""
    txtSelect.Text = Dir
    m_bCancel = False
    Set ObjFile = New CFile
    Set m_fs = CreateObject("Scripting.FileSystemObject")
    lstName.AddItem "debug"
    lstName.AddItem "release"
    lstName.AddItem "bin"
    lstName.AddItem "obj"
    lstName.AddItem "temp"
    LoadItemFormFile App.Path & "\默认要删除的内容.txt"
End Sub

Private Sub Form_Unload(Cancel As Integer)
    If Not m_bExit Then
       MsgBox "先取消文件操作"
       Cancel = 1
    End If
End Sub

Private Sub lstDelete_Click()
    lstDelete.ToolTipText = lstDelete.Text
End Sub

Private Sub ObjFile_fFoundAllFilesEvent(ByVal strFoundFileName As String, ByVal iFileCount As Long, bCancel As Boolean)
    If InList(LCase(ObjFile.fGetFileTitle(strFoundFileName))) Then
       If GetAttr(strFoundFileName) And vbDirectory Then
            m_fs.DeleteFolder strFoundFileName, True
            lstDelete.AddItem "目录：" & strFoundFileName
       Else
            m_fs.DeleteFile strFoundFileName, True
            lstDelete.AddItem "文件：" & strFoundFileName
       End If
       m_iCount = m_iCount + 1
       LabDelFile.Caption = m_iCount
    End If
    bCancel = m_bCancel
    labFileCount.Caption = iFileCount
End Sub

Private Sub txtFileName_KeyUp(KeyCode As Integer, Shift As Integer)
    If KeyCode = 13 Then
       cmdAdd_Click
    End If
End Sub

Private Function InList(ByVal strName As String) As Boolean
    Dim i As Integer
    Dim iCount As Integer
        
    InList = False
    iCount = lstName.ListCount
    For i = 0 To iCount - 1
        If LCase(strName) Like LCase(lstName.List(i)) Then
            'If LCase(strName) = LCase(lstName.List(i)) Then
           InList = True
           Exit Function
        End If
    Next i
End Function
