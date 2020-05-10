VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmOptions 
   Appearance      =   0  'Flat
   BackColor       =   &H80000004&
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "选项"
   ClientHeight    =   4920
   ClientLeft      =   2565
   ClientTop       =   1440
   ClientWidth     =   6150
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   MouseIcon       =   "frmOptions.frx":0000
   ScaleHeight     =   4920
   ScaleWidth      =   6150
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  '屏幕中心
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   4
      Left            =   4680
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   49
      TabStop         =   0   'False
      Top             =   720
      Visible         =   0   'False
      Width           =   5685
      Begin VB.CheckBox Check3 
         Caption         =   "显示每日提示"
         Height          =   255
         Left            =   480
         TabIndex        =   50
         Top             =   360
         Width           =   1575
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   3
      Left            =   4080
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   360
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame fraSample4 
         Caption         =   "选择座标"
         Height          =   1785
         Left            =   600
         TabIndex        =   11
         Top             =   840
         Width           =   2295
         Begin VB.OptionButton Option4 
            Caption         =   "极座标"
            Height          =   255
            Left            =   360
            TabIndex        =   35
            Top             =   1200
            Width           =   1815
         End
         Begin VB.OptionButton Option3 
            Caption         =   "相对座标"
            Height          =   375
            Left            =   360
            TabIndex        =   34
            Top             =   720
            Width           =   1455
         End
         Begin VB.OptionButton Option2 
            Caption         =   "绝对座标"
            Height          =   180
            Left            =   360
            TabIndex        =   33
            Top             =   360
            Width           =   1575
         End
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   2
      Left            =   5160
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   360
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame fraSample3 
         Caption         =   " 填充 "
         Height          =   2865
         Left            =   480
         TabIndex        =   10
         Top             =   360
         Width           =   2175
         Begin VB.OptionButton Option1 
            Caption         =   "斜十字线"
            Height          =   255
            Index           =   7
            Left            =   240
            TabIndex        =   31
            Top             =   2040
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "十字线"
            Height          =   255
            Index           =   6
            Left            =   240
            TabIndex        =   30
            Top             =   1800
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "斜线"
            Height          =   255
            Index           =   5
            Left            =   240
            TabIndex        =   29
            Top             =   1560
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "反斜线"
            Height          =   255
            Index           =   4
            Left            =   240
            TabIndex        =   28
            Top             =   1320
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "垂直直线"
            Height          =   255
            Index           =   3
            Left            =   240
            TabIndex        =   27
            Top             =   1080
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "水平直线"
            Height          =   255
            Index           =   2
            Left            =   240
            TabIndex        =   26
            Top             =   840
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "用背景填充"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   25
            Top             =   600
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "用颜色填充"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   24
            Top             =   360
            Width           =   1455
         End
         Begin VB.Label Label7 
            AutoSize        =   -1  'True
            Caption         =   "颜色选项"
            Height          =   180
            Left            =   240
            MouseIcon       =   "frmOptions.frx":030A
            MousePointer    =   99  'Custom
            TabIndex        =   32
            Top             =   2400
            Width           =   720
         End
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   1
      Left            =   -360
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   360
      Visible         =   0   'False
      Width           =   5685
      Begin VB.CheckBox Check2 
         Caption         =   "    点击新文件时时,显示图纸选取窗体"
         Height          =   180
         Left            =   480
         TabIndex        =   46
         Top             =   3240
         Width           =   3735
      End
      Begin VB.CheckBox Check1 
         Caption         =   "    程序起动时显示图纸选取窗体"
         Height          =   180
         Left            =   480
         TabIndex        =   45
         Top             =   2880
         Width           =   3255
      End
      Begin VB.TextBox Text2 
         Height          =   270
         Left            =   2400
         TabIndex        =   39
         Text            =   "1"
         Top             =   2040
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Height          =   270
         Left            =   1440
         TabIndex        =   38
         Text            =   "1"
         Top             =   2040
         Width           =   615
      End
      Begin VB.Frame paper 
         Caption         =   "纸张大小"
         Height          =   1545
         Left            =   360
         TabIndex        =   9
         Top             =   360
         Width           =   4935
         Begin VB.ComboBox untle 
            Height          =   300
            ItemData        =   "frmOptions.frx":0614
            Left            =   1320
            List            =   "frmOptions.frx":061E
            TabIndex        =   23
            Text            =   "毫米(mm)"
            Top             =   1080
            Width           =   1695
         End
         Begin VB.ComboBox pwidth 
            Height          =   300
            Left            =   1320
            TabIndex        =   21
            Text            =   "11"
            Top             =   720
            Width           =   1695
         End
         Begin VB.ComboBox pheight 
            Height          =   300
            Left            =   1320
            TabIndex        =   20
            Text            =   "11"
            Top             =   360
            Width           =   1695
         End
         Begin VB.Label papercolor 
            AutoSize        =   -1  'True
            Caption         =   "纸张颜色选项"
            Height          =   180
            Left            =   3360
            MouseIcon       =   "frmOptions.frx":0636
            MousePointer    =   99  'Custom
            TabIndex        =   48
            Top             =   1080
            Width           =   1080
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "纸张格式"
            Height          =   180
            Left            =   3360
            MouseIcon       =   "frmOptions.frx":0940
            MousePointer    =   99  'Custom
            TabIndex        =   47
            Top             =   480
            Width           =   720
         End
         Begin VB.Label Label6 
            AutoSize        =   -1  'True
            Caption         =   "单位"
            Height          =   180
            Left            =   240
            TabIndex        =   22
            Top             =   1200
            Width           =   360
         End
         Begin VB.Label Label4 
            AutoSize        =   -1  'True
            Caption         =   "宽度"
            Height          =   180
            Left            =   240
            TabIndex        =   19
            Top             =   840
            Width           =   360
         End
         Begin VB.Label Label3 
            AutoSize        =   -1  'True
            Caption         =   "高度"
            Height          =   180
            Left            =   240
            TabIndex        =   18
            Top             =   480
            Width           =   360
         End
      End
      Begin VB.Label 实际宽度 
         AutoSize        =   -1  'True
         BackColor       =   &H0000FF00&
         Caption         =   "Label13"
         Height          =   180
         Left            =   4440
         TabIndex        =   44
         Top             =   2520
         Width           =   630
      End
      Begin VB.Label Label12 
         AutoSize        =   -1  'True
         Caption         =   "实际宽度"
         Height          =   180
         Left            =   3720
         TabIndex        =   43
         Top             =   2520
         Width           =   720
      End
      Begin VB.Label Label11 
         AutoSize        =   -1  'True
         Caption         =   "实际高度"
         Height          =   180
         Left            =   2160
         TabIndex        =   42
         Top             =   2520
         Width           =   720
      End
      Begin VB.Label 实际高度 
         AutoSize        =   -1  'True
         BackColor       =   &H0000FF00&
         Caption         =   "Label11"
         Height          =   180
         Left            =   2880
         TabIndex        =   41
         Top             =   2520
         Width           =   630
      End
      Begin VB.Label Label10 
         AutoSize        =   -1  'True
         Caption         =   "纸张能表达的尺寸"
         Height          =   180
         Left            =   480
         TabIndex        =   40
         Top             =   2520
         Width           =   1440
      End
      Begin VB.Label Label9 
         AutoSize        =   -1  'True
         Caption         =   ":"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   2160
         TabIndex        =   37
         Top             =   2040
         Width           =   60
      End
      Begin VB.Label Label8 
         AutoSize        =   -1  'True
         Caption         =   "比例尺"
         Height          =   180
         Left            =   480
         TabIndex        =   36
         Top             =   2160
         Width           =   540
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   0
      Left            =   -4920
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   600
      Width           =   5685
      Begin VB.Frame pensam 
         Caption         =   "线形选项"
         Height          =   1305
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   2895
         Begin VB.ComboBox 线形宽度 
            Height          =   300
            ItemData        =   "frmOptions.frx":0C4A
            Left            =   1440
            List            =   "frmOptions.frx":0C6C
            TabIndex        =   16
            Text            =   "1"
            Top             =   720
            Width           =   1215
         End
         Begin VB.ComboBox 线形 
            Height          =   300
            ItemData        =   "frmOptions.frx":0C8F
            Left            =   1440
            List            =   "frmOptions.frx":0CA2
            TabIndex        =   13
            Text            =   "__________________"
            Top             =   360
            Width           =   1215
         End
         Begin VB.Label Label2 
            AutoSize        =   -1  'True
            Caption         =   "线形宽度"
            Height          =   180
            Left            =   240
            TabIndex        =   14
            Top             =   720
            Width           =   720
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "线形"
            Height          =   180
            Left            =   240
            TabIndex        =   12
            Top             =   360
            Width           =   360
         End
      End
      Begin VB.Label fone 
         AutoSize        =   -1  'True
         Caption         =   "字体选项"
         Height          =   180
         Left            =   240
         MouseIcon       =   "frmOptions.frx":0CFA
         MousePointer    =   99  'Custom
         TabIndex        =   17
         Top             =   2400
         Width           =   720
      End
      Begin VB.Label color 
         AutoSize        =   -1  'True
         Caption         =   "颜色选项"
         Height          =   180
         Left            =   240
         MouseIcon       =   "frmOptions.frx":1004
         MousePointer    =   99  'Custom
         TabIndex        =   15
         Top             =   1920
         Width           =   720
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
      Default         =   -1  'True
      Height          =   375
      Left            =   2490
      TabIndex        =   1
      Top             =   4440
      Width           =   1095
   End
   Begin MSComctlLib.TabStrip tbsOptions 
      Height          =   4245
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5895
      _ExtentX        =   10398
      _ExtentY        =   7488
      MultiRow        =   -1  'True
      TabStyle        =   1
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   5
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "笔画"
            Key             =   "pen"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "纸张的大小"
            Key             =   "paper"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "填充类型"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "座标"
            Object.ToolTipText     =   "座标"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab5 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "其它"
            Object.ToolTipText     =   "其它"
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
'选择项窗口

Option Explicit
'变量存储
Private col As ColorConstants         '线的颜色
Private style As Integer             '线形
Private Dwidth As Integer            '线宽
Private Type font
        name As String           '字体名
        Bold As Boolean
        Italic As Boolean
        size As Integer
        Strikethrough As Boolean
        Underline As Boolean
        End Type
Private Ffont As font
Private PaperCol As ColorConstants   '纸张颜色
Private Untl As ScaleModeConstants   '单位
Private PaperHeight As Integer         '纸张长度
Private PaperWidth As Integer          '....宽度
Private PaperScaleHeight As Single   '度量单位,为了保证缩放的比例
Private PaperScaleWidth As Single
Private PaperFlag As Boolean    '图纸大小是否改变的标志
Private Ratio As Double     '比例尺
Private Ratio1 As Single   '比例尺第一个输入框
Private Ratio2 As Single  '比例尺第二个输入框
Private Fillstyl As Integer  '填充类型
Private Fillstlyecol As ColorConstants '填充色
Private 座标 As Integer   '所选择的座标

Private Sub Check1_Click()
    ' 保存在下次启动时是否显示图纸选取窗体
    SaveSetting App.EXEName, "Options", "在启动时显示", Check1.Value

End Sub

Private Sub Check2_Click()
    ' 保存在下次启动时是否显示图纸选取窗体
    SaveSetting App.EXEName, "Options", "在点击新文件时显示", Check2.Value
End Sub

Private Sub Check3_Click()
' 保存在下次启动时是否显示此窗体
    SaveSetting App.EXEName, "Options", "在启动时显示提示", Check3.Value
    End Sub

Private Sub Form_Load()
    On Error Resume Next
    
    '设置容器位置
    tbsOptions.left = 120
    tbsOptions.top = 120
    picOptions(0).top = 480
    picOptions(0).left = 210
    
    '置中窗体
    Me.Move (Screen.width - Me.width) / 2, (Screen.height - Me.height) / 2
    '保存原始参数
    col = user.Commvar.col       '线形的颜色
    style = user.Commvar.style   '线形
    Dwidth = user.Commvar.width  '线宽
    With Ffont
             .Bold = Form1.cad.FontBold
             .Italic = Form1.cad.FontItalic
             .name = Form1.cad.FontName
             .size = Form1.cad.FontSize
             .Strikethrough = Form1.cad.FontStrikethru
             .Underline = Form1.cad.FontUnderline
    End With
    
   ' 设置图纸选取窗体复选框
   Dim ShowAtStartup As Long
    ShowAtStartup = GetSetting(App.EXEName, "Options", "在启动时显示", 1)
    If ShowAtStartup <> 0 Then
       Me.Check1.Value = vbChecked
    End If
   ' 设置点击新文件时显示复选框
    ShowAtStartup = GetSetting(App.EXEName, "Options", "在点击新文件时显示", 1)
    If ShowAtStartup <> 0 Then
    ' 察看在点击新文件时是否将被显示
       Me.Check2.Value = vbChecked
    End If
    '设置每日提示复选框
    ShowAtStartup = GetSetting(App.EXEName, "Options", "在启动时显示提示", 1)
    If ShowAtStartup <> 0 Then
       Me.Check3.Value = vbChecked
    End If
 
    线形宽度.text = user.Commvar.width   '显示原来的线宽
    线形.text = 线形.List(style)       '显示原来的线形
    PaperCol = Form1.cad.BackColor  '保存原来的颜色
    Untl = user.paper.until    '保存原来的单位
    Select Case Untl              '显示原来的单位
           Case vbCentimeters
                untle.text = "厘米(cm)"
           Case vbMillimeters
                untle.text = "毫米(mm)"
           Case 0
                untle.text = "自定义单位"
    End Select
    PaperHeight = ScaleY(user.paper.height, 3, Untl) '单位转换
    pheight.text = PaperHeight     '显示纸原来的高宽
    PaperWidth = ScaleX(user.paper.width, 3, Untl) ' 单位转换
    pwidth.text = PaperWidth       '显示纸原来的宽度
    With Form1.cad
         PaperScaleHeight = .ScaleHeight
         PaperScaleWidth = .scalewidth
    End With
    PaperFlag = False     '图纸大小的改变标志
    Ratio = user.Ratio '保存比例尺
    Text1.text = user.Ratio1  ' 比例尺第一个输入框
    Text2.text = user.Ratio2  '.........二.......
    Ratio1 = user.Ratio1
    Ratio2 = user.Ratio2
    
    实际高度.Caption = PaperHeight * Ratio   '显示纸张的表示大小
    实际宽度.Caption = PaperWidth * Ratio

    Fillstyl = Form1.cad.FillStyle '保存原来的填充类型
    Option1.Item(Fillstyl).Value = True  '显示填充类型
    Fillstlyecol = Form1.cad.FillColor  '保存填充色
    
    '保存座标
    座标 = user.座标
    Select Case 座标      '显示座标类型
           Case 1
                Option2.Value = True
           Case 2
                Option3.Value = True
           Case 3
                Option4.Value = True
    End Select
    
End Sub

Private Sub cmdApply_Click()
On Error Resume Next
    '重置参数
    user.Commvar.col = col    '线形颜色
    user.Commvar.style = style   '线形
    user.Commvar.width = Dwidth  '线宽
    With Form1.cad.font
         .Bold = Ffont.Bold
         .Italic = Ffont.Italic
         .name = Ffont.name
         .size = Ffont.size
         .Strikethrough = Ffont.Strikethrough
         .Underline = Ffont.Underline
         End With
         
    With Form1.cad
        .BackColor = PaperCol '纸的颜色
        '.scalemode = Untl     '单位
        .DrawWidth = Dwidth   ' 线宽
        .DrawStyle = style  '线型
         End With
         
    user.Ratio = Ratio '比例尺
    user.Ratio1 = Ratio1  '比例尺输入框
    user.Ratio2 = Ratio2
    
    If PaperFlag Then   '图纸变化后相应改变的控件
         With Form1.cad   '图纸的宽度和高度
         .width = ScaleX(PaperWidth, Untl, 3)  '纸的宽度
         .height = ScaleY(PaperHeight, Untl, 3) '纸的高度
         .scalemode = Untl   '单位
         End With
       
        '重置液动条
         user.Scrollbar (Form1.cad.width - Form1.desk.scalewidth) / 2, (Form1.cad.height - Form1.desk.ScaleHeight) / 2
    
         '保存制图区初始区域,当制图区放缩后,便于恢复原来的制图区
         With user.paper
             .height = Form1.cad.height   '以提为单位
             .width = Form1.cad.width     '..........
             .top = Form1.cad.top         '.........
             .left = Form1.cad.left       '.........
             .scaleheigt = Form1.cad.ScaleHeight
             .scalewidth = Form1.cad.scalewidth
             .until = Untl       '设置的单位
             .color = col
             .scalemode = Form1.cad.scalemode
         End With
         'With Form1.cad  '设置度量单位
         '     .ScaleHeight = PaperScaleHeight
         '     .scalewidth = PaperScaleWidth
         'End With
    
    End If
    
    Form1.cad.FillStyle = Fillstyl    '真充类型
    Form1.cad.FillColor = Fillstlyecol  '填充颜色
    
    user.座标 = 座标
    
    draw.redraw
End Sub

Public Sub cmdOK_Click()
    On Error Resume Next
    'MsgBox "在这里放置代码来设置选项并且关闭对话框!"
    cmdApply_Click
Unload Me
End Sub

Private Sub Label5_Click()
        selectpaper.showthiswindowsflag = True
        selectpaper.Show 1, frmOptions
        selectpaper.showthiswindowsflag = False
End Sub

Private Sub Label7_Click()
        Form1.CommonDialog1.ShowColor
        Fillstlyecol = Form1.CommonDialog1.color
End Sub

Private Sub Option1_Click(Index As Integer)
        Fillstyl = Index
End Sub

Private Sub Option2_Click()
        座标 = 1
End Sub

Private Sub Option3_Click()
        座标 = 2
End Sub

Private Sub Option4_Click()
        座标 = 3
End Sub

Private Sub tbsOptions_Click()
    
    Dim i As Integer
    '显示并使选项的控件可用
    '并且隐藏使其他被禁用
    For i = 0 To tbsOptions.Tabs.Count - 1
        If i = tbsOptions.SelectedItem.Index - 1 Then
            picOptions(i).top = 480
            picOptions(i).left = 210
            picOptions(i).Visible = True
        Else
            picOptions(i).left = -20000
            picOptions(i).Visible = False
        End If
    Next
    
End Sub

Private Sub cmdCancel_Click()
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

Private Sub fone_Click()
On Error Resume Next
'    Form1.CommonDialog1.Flags = 3
    With Form1.CommonDialog1    '显示以前的字体
         .FontBold = Ffont.Bold
        ' .FontItalic ffont.Italic
         .FontName = Ffont.name
         .FontSize = Ffont.size
         .FontStrikethru = Ffont.Strikethrough
         .FontUnderline = Ffont.Underline
         End With
    Form1.CommonDialog1.ShowFont
    With Form1.CommonDialog1        '给字体赋值
         Ffont.Bold = .FontBold
         Ffont.Italic = .FontItalic
         Ffont.name = .FontName
         Ffont.size = .FontSize
         Ffont.Strikethrough = .FontStrikethru
         Ffont.Underline = .FontUnderline
    End With
End Sub

'线形参数
Private Sub color_Click()
 On Error Resume Next
 Form1.CommonDialog1.ShowColor
 col = Form1.CommonDialog1.color
End Sub

Private Sub 线形_Click()
  On Error Resume Next
  style = 线形.ListIndex
  Form1.cad.DrawStyle = style
End Sub

Private Sub 线形宽度_Change()
On Error Resume Next
        If 线形宽度.text > 0 Then
           Dwidth = 线形宽度.text
           Form1.cad.DrawWidth = Dwidth
        End If
End Sub

Private Sub 线形宽度_Click()
On Error Resume Next
   Dwidth = 线形宽度.text
   Form1.cad.DrawWidth = Dwidth
End Sub

'纸张的参数
Private Sub papercolor_Click()
        On Error Resume Next
        '纸张的颜色
        Form1.CommonDialog1.ShowColor
        PaperCol = Form1.CommonDialog1.color
End Sub

Private Sub pheight_Change()  '
        On Error Resume Next
        PaperHeight = pheight.text
        实际宽度.Caption = PaperWidth * Ratio
        实际高度.Caption = PaperHeight * Ratio
        PaperFlag = True
End Sub

Private Sub pheight_Click()
        On Error Resume Next
        PaperHeight = pheight.text
        实际宽度.Caption = PaperWidth * Ratio
        实际高度.Caption = PaperHeight * Ratio
        PaperFlag = True
End Sub

Private Sub pwidth_Change()
        On Error Resume Next
        PaperWidth = pwidth.text
        实际高度.Caption = PaperHeight * Ratio
        实际宽度.Caption = PaperWidth * Ratio
        PaperFlag = True
End Sub

Private Sub pwidth_Click()
        On Error Resume Next
        PaperWidth = pwidth.text
        实际宽度.Caption = PaperWidth * Ratio
        实际高度.Caption = PaperHeight * Ratio
        PaperFlag = True
End Sub

Private Sub untle_Click()     '纸张单位
        On Error Resume Next
        Select Case untle.text
               Case "毫米(mm)"
                    Untl = vbMillimeters
               Case "厘米(cm)"
                    Untl = vbCentimeters
        End Select
End Sub

Private Sub Text1_Change()
On Error Resume Next
Dim i, j
    Ratio1 = Text1.text
    i = Text1.text
    j = Text2.text
    If i <> 0 Then
       Ratio = j / i
       实际宽度.Caption = PaperWidth * Ratio
       实际高度.Caption = PaperHeight * Ratio
    End If
End Sub

Private Sub Text2_Change()
On Error Resume Next
Dim i, j
    Ratio2 = Text2.text
    i = Text1.text
    j = Text2.text
    If i <> 0 Then
    Ratio = j / i
    实际宽度.Caption = PaperWidth * Ratio
    实际高度.Caption = PaperHeight * Ratio
    End If
End Sub


