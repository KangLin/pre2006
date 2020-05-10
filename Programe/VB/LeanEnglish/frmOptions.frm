VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmOptions 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "选项"
   ClientHeight    =   4920
   ClientLeft      =   2565
   ClientTop       =   1500
   ClientWidth     =   6150
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4920
   ScaleWidth      =   6150
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  '屏幕中心
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   3
      Left            =   -20000
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame fraSample4 
         Caption         =   "示例 4"
         Height          =   1785
         Left            =   2100
         TabIndex        =   11
         Top             =   840
         Width           =   2055
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   2
      Left            =   -20000
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame fraSample3 
         Caption         =   "示例 3"
         Height          =   1785
         Left            =   1545
         TabIndex        =   10
         Top             =   675
         Width           =   2055
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   1
      Left            =   -20000
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame fraSample2 
         Caption         =   "示例 2"
         Height          =   1785
         Left            =   645
         TabIndex        =   9
         Top             =   300
         Width           =   2055
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   0
      Left            =   210
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   5685
      Begin VB.FileListBox file1 
         Height          =   1350
         Left            =   3720
         TabIndex        =   14
         Top             =   2400
         Width           =   1935
      End
      Begin VB.CommandButton Command1 
         Caption         =   "浏览..."
         Height          =   375
         Left            =   600
         TabIndex        =   12
         Top             =   3120
         Width           =   1095
      End
      Begin VB.Frame fraSample1 
         Height          =   1785
         Left            =   210
         TabIndex        =   5
         Top             =   255
         Width           =   2055
         Begin VB.CheckBox clkPic 
            Caption         =   "主窗口背景图片"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   13
            Top             =   240
            Width           =   1815
         End
      End
      Begin VB.Image Img 
         Height          =   2055
         Left            =   3720
         Stretch         =   -1  'True
         Top             =   120
         Width           =   1935
      End
   End
   Begin VB.CommandButton cmdApply 
      Caption         =   "应用"
      Height          =   375
      Left            =   4920
      TabIndex        =   3
      Top             =   4455
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "取消"
      Height          =   375
      Left            =   3720
      TabIndex        =   2
      Top             =   4455
      Width           =   1095
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定"
      Height          =   375
      Left            =   2490
      TabIndex        =   1
      Top             =   4455
      Width           =   1095
   End
   Begin MSComctlLib.TabStrip tbsOptions 
      Height          =   4245
      Left            =   105
      TabIndex        =   0
      Top             =   120
      Width           =   5895
      _ExtentX        =   10398
      _ExtentY        =   7488
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   4
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "图片"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "群组 2"
            Key             =   "Group2"
            Object.ToolTipText     =   "为群组 2 设置选项"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "群组 3"
            Key             =   "Group3"
            Object.ToolTipText     =   "为群组 3 设置选项"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "群组 4"
            Key             =   "Group4"
            Object.ToolTipText     =   "为群组 4 设置选项"
            ImageVarType    =   2
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
On Error GoTo Command_Click_Error
Dim i
Dim ss As String

        With frmMain.ComD
             .Filter = "*.bmp|*.bmp|*.*|*.*"
             .DialogTitle = "打开"
             .ShowOpen
             If .FileName <> "" Then
                LetPicture .FileName
                Img.Picture = LoadPicture(.FileName)
                i = InStr(1, .FileName, .FileTitle)
                ss = Left$(.FileName, i - 2)
                file1.Path = ss
                file1.FileName = .FileTitle
             End If
        End With
        Exit Sub
        
Command_Click_Error:
        MsgBox Err.Description
End Sub

Private Sub file1_Click()
        LetPicture file1.List(file1.ListIndex)
End Sub

Sub LetPicture(FileName As String)
Dim i
        For i = 1 To clkPic.UBound
            If Not clkPic(i).Value Then Exit For
        Next i
        Select Case i
               Case 0
                    OptionsVal.Backmap = FileName
        End Select
        Img.Picture = LoadPicture(FileName)

End Sub

Private Sub Form_Load()
Dim ss As String, i

    '置中窗体
    Me.Move (Screen.Width - Me.Width) / 2, (Screen.Height - Me.Height) / 2
    Me.picOptions(0).Visible = True
    
    With file1
         .Path = App.Path
         .FileName = "*.bmp"
    End With

End Sub

Private Sub cmdApply_Click()
Dim i
    If OptionsVal.Backmap <> "" Then
        WritePrivateProfileString "图片", "背景图片", OptionsVal.Backmap, INIFile
        frmMain.Picture = LoadPicture(OptionsVal.Backmap)
    End If
        
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
    cmdApply_Click
    Unload Me
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim i As Integer
    '处理 ctrl+tab 键来移动到下一个选项
    If Shift = vbCtrlMask And KeyCode = vbKeyTab Then
        i = tbsOptions.SelectedItem.Index
        If i = tbsOptions.Tabs.Count Then
            '已到达最后的选项,转回到选项 1
            Set tbsOptions.SelectedItem = tbsOptions.Tabs(1)
        Else
            '递增选项
            Set tbsOptions.SelectedItem = tbsOptions.Tabs(i + 1)
        End If
    End If
End Sub

Private Sub tbsOptions_Click()
    
    Dim i As Integer
    '显示并使选项的控件可用
    '并且隐藏使其他被禁用
    For i = 0 To tbsOptions.Tabs.Count - 1
        If i = tbsOptions.SelectedItem.Index - 1 Then
            picOptions(i).Left = 210
            picOptions(i).Left = 480
            picOptions(i).Visible = True
        Else
            picOptions(i).Left = -20000
            picOptions(i).Visible = False
        End If
    Next
    
End Sub
