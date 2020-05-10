VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form fOption 
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
      Index           =   4
      Left            =   4680
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   31
      TabStop         =   0   'False
      Top             =   3240
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame Frame6 
         Caption         =   "栅格类型"
         Height          =   2655
         Left            =   240
         TabIndex        =   84
         Top             =   360
         Width           =   2775
         Begin VB.ComboBox GirdDis 
            Height          =   345
            Left            =   960
            Style           =   2  'Dropdown List
            TabIndex        =   90
            Top             =   840
            Width           =   1575
         End
         Begin VB.ComboBox Gird 
            Height          =   345
            ItemData        =   "options.frx":0000
            Left            =   960
            List            =   "options.frx":0016
            Style           =   2  'Dropdown List
            TabIndex        =   87
            Top             =   360
            Width           =   1575
         End
         Begin VB.PictureBox PGird 
            BackColor       =   &H80000009&
            Height          =   1095
            Left            =   960
            ScaleHeight     =   1035
            ScaleWidth      =   1515
            TabIndex        =   86
            Top             =   1440
            Width           =   1575
            Begin VB.Line LGird 
               Index           =   0
               Visible         =   0   'False
               X1              =   360
               X2              =   360
               Y1              =   120
               Y2              =   720
            End
         End
         Begin VB.Label Label14 
            AutoSize        =   -1  'True
            Caption         =   "间距"
            Height          =   180
            Left            =   240
            TabIndex        =   89
            Top             =   840
            Width           =   360
         End
         Begin VB.Label Girdcolor 
            AutoSize        =   -1  'True
            Caption         =   "颜色"
            Height          =   180
            Left            =   240
            MouseIcon       =   "options.frx":0072
            MousePointer    =   99  'Custom
            TabIndex        =   88
            Top             =   1440
            Width           =   360
         End
         Begin VB.Label Label13 
            AutoSize        =   -1  'True
            Caption         =   "线型"
            Height          =   180
            Left            =   240
            TabIndex        =   85
            Top             =   360
            Width           =   360
         End
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   3
      Left            =   4440
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   840
      Visible         =   0   'False
      Width           =   5685
      Begin VB.CheckBox DimUnit 
         Caption         =   "自动标注单位"
         Height          =   255
         Left            =   3840
         TabIndex        =   80
         Top             =   2160
         Width           =   1455
      End
      Begin VB.ComboBox DimASize 
         Height          =   300
         ItemData        =   "options.frx":037C
         Left            =   4680
         List            =   "options.frx":03A3
         TabIndex        =   79
         Text            =   "Combo2"
         Top             =   360
         Width           =   855
      End
      Begin VB.Frame Frame5 
         Caption         =   "字体状态"
         Height          =   975
         Left            =   2160
         TabIndex        =   74
         Top             =   840
         Width           =   1455
         Begin VB.OptionButton DimState 
            Caption         =   "与标线平行"
            Height          =   180
            Index           =   2
            Left            =   120
            TabIndex        =   77
            Top             =   720
            Width           =   1215
         End
         Begin VB.OptionButton DimState 
            Caption         =   "保持垂直"
            Height          =   180
            Index           =   1
            Left            =   120
            TabIndex        =   76
            Top             =   480
            Width           =   1215
         End
         Begin VB.OptionButton DimState 
            Caption         =   "保持水平"
            Height          =   180
            Index           =   0
            Left            =   120
            TabIndex        =   75
            Top             =   240
            Width           =   1095
         End
      End
      Begin VB.Frame fraSample4 
         Caption         =   "标注方式"
         Height          =   3345
         Index           =   1
         Left            =   120
         TabIndex        =   48
         Top             =   240
         Width           =   1815
         Begin VB.OptionButton DimStyle 
            Caption         =   "水平标注"
            Height          =   180
            Index           =   0
            Left            =   240
            TabIndex        =   56
            Top             =   360
            Width           =   1335
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "垂直标注"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   55
            Top             =   720
            Width           =   1335
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "同基线标注"
            Height          =   255
            Index           =   2
            Left            =   240
            TabIndex        =   54
            Top             =   1080
            Width           =   1335
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "连续标注"
            Height          =   255
            Index           =   3
            Left            =   240
            TabIndex        =   53
            Top             =   1440
            Width           =   1215
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "半径尺寸"
            Height          =   255
            Index           =   4
            Left            =   240
            TabIndex        =   52
            Top             =   1800
            Width           =   1095
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "直径尺寸"
            Height          =   255
            Index           =   5
            Left            =   240
            TabIndex        =   51
            Top             =   2160
            Width           =   1215
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "旁注尺寸"
            Height          =   255
            Index           =   6
            Left            =   240
            TabIndex        =   50
            Top             =   2520
            Width           =   1095
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "角度尺寸"
            Height          =   255
            Index           =   7
            Left            =   240
            TabIndex        =   49
            Top             =   2880
            Width           =   1095
         End
      End
      Begin VB.PictureBox DimP 
         AutoRedraw      =   -1  'True
         BackColor       =   &H00FFFFFF&
         Height          =   1335
         Left            =   3240
         ScaleHeight     =   1275
         ScaleWidth      =   2235
         TabIndex        =   46
         Top             =   2400
         Width           =   2295
         Begin VB.Line DimFELine1 
            BorderColor     =   &H008080FF&
            X1              =   240
            X2              =   240
            Y1              =   240
            Y2              =   960
         End
         Begin VB.Line DimSELine1 
            X1              =   2040
            X2              =   2040
            Y1              =   240
            Y2              =   960
         End
         Begin VB.Label DimText 
            AutoSize        =   -1  'True
            BackColor       =   &H00FFFFFF&
            Caption         =   "100"
            Height          =   180
            Left            =   960
            TabIndex        =   47
            Top             =   120
            Width           =   270
         End
         Begin VB.Line Dline 
            X1              =   240
            X2              =   2040
            Y1              =   360
            Y2              =   360
         End
      End
      Begin VB.ComboBox DimLeftarrow 
         Height          =   345
         ItemData        =   "options.frx":03CA
         Left            =   2880
         List            =   "options.frx":03E6
         Style           =   2  'Dropdown List
         TabIndex        =   45
         Top             =   0
         Width           =   1695
      End
      Begin VB.ComboBox DimRightarrow 
         Height          =   345
         ItemData        =   "options.frx":0452
         Left            =   2880
         List            =   "options.frx":046E
         Style           =   2  'Dropdown List
         TabIndex        =   44
         Top             =   480
         Width           =   1695
      End
      Begin VB.Frame Frame1 
         Caption         =   "标注位置"
         Height          =   1215
         Left            =   3840
         TabIndex        =   40
         Top             =   840
         Width           =   1695
         Begin VB.OptionButton DimPos 
            Caption         =   "在标注线上方"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   43
            Top             =   240
            Width           =   1455
         End
         Begin VB.OptionButton DimPos 
            Caption         =   "在标注线外"
            Height          =   255
            Index           =   1
            Left            =   120
            TabIndex        =   42
            Top             =   600
            Width           =   1335
         End
         Begin VB.OptionButton DimPos 
            Caption         =   "在标注线上"
            Height          =   180
            Index           =   2
            Left            =   120
            TabIndex        =   41
            Top             =   960
            Width           =   1335
         End
      End
      Begin VB.CheckBox DimAutoDim 
         Caption         =   "自动标注"
         Height          =   255
         Left            =   2160
         TabIndex        =   39
         Top             =   2400
         Width           =   1095
      End
      Begin VB.CheckBox DimFELine 
         Caption         =   "第一条延长线"
         Height          =   255
         Left            =   2160
         TabIndex        =   38
         Top             =   1920
         Width           =   1455
      End
      Begin VB.CheckBox DimSELine 
         Caption         =   "第二条延长线"
         Height          =   255
         Left            =   2160
         TabIndex        =   37
         Top             =   2160
         Width           =   1575
      End
      Begin VB.Label Label12 
         Caption         =   "箭头尺寸"
         Height          =   255
         Left            =   4680
         TabIndex        =   78
         Top             =   0
         Width           =   855
      End
      Begin VB.Label DimELine 
         AutoSize        =   -1  'True
         Caption         =   "延长线颜色"
         Height          =   180
         Left            =   2160
         MouseIcon       =   "options.frx":04DA
         MousePointer    =   99  'Custom
         TabIndex        =   62
         Top             =   3480
         Width           =   900
      End
      Begin VB.Label Dimline 
         AutoSize        =   -1  'True
         Caption         =   "标注线颜色"
         Height          =   180
         Left            =   2160
         MouseIcon       =   "options.frx":07E4
         MousePointer    =   99  'Custom
         TabIndex        =   61
         Top             =   3240
         Width           =   900
      End
      Begin VB.Label DimFontColor 
         AutoSize        =   -1  'True
         Caption         =   "字体颜色"
         Height          =   180
         Left            =   2160
         MouseIcon       =   "options.frx":0AEE
         MousePointer    =   99  'Custom
         TabIndex        =   60
         Top             =   3000
         Width           =   720
      End
      Begin VB.Label DimFont 
         AutoSize        =   -1  'True
         Caption         =   "字体"
         Height          =   180
         Left            =   2160
         MouseIcon       =   "options.frx":0DF8
         MousePointer    =   99  'Custom
         TabIndex        =   59
         Top             =   2760
         Width           =   360
      End
      Begin VB.Label Label15 
         Caption         =   "左箭头"
         Height          =   255
         Left            =   2160
         TabIndex        =   58
         Top             =   120
         Width           =   615
      End
      Begin VB.Label Label16 
         Caption         =   "右箭头"
         Height          =   255
         Left            =   2160
         TabIndex        =   57
         Top             =   600
         Width           =   615
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   2
      Left            =   4320
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   840
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame Frame4 
         Caption         =   "鼠标"
         Height          =   1215
         Left            =   2400
         TabIndex        =   70
         Top             =   2280
         Width           =   3015
         Begin VB.ComboBox Mouse 
            Height          =   345
            ItemData        =   "options.frx":1102
            Left            =   1200
            List            =   "options.frx":1112
            Style           =   2  'Dropdown List
            TabIndex        =   71
            Top             =   360
            Width           =   1695
         End
         Begin VB.Label Label17 
            AutoSize        =   -1  'True
            Caption         =   "鼠标形状"
            Height          =   180
            Left            =   240
            TabIndex        =   73
            Top             =   480
            Width           =   720
         End
         Begin VB.Label MouseColor 
            AutoSize        =   -1  'True
            Caption         =   "自定义鼠标颜色"
            Height          =   180
            Left            =   240
            MouseIcon       =   "options.frx":1142
            MousePointer    =   99  'Custom
            TabIndex        =   72
            Top             =   840
            Width           =   1260
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "座标"
         Height          =   1215
         Left            =   240
         TabIndex        =   63
         Top             =   2280
         Width           =   1695
         Begin VB.OptionButton Coordinate 
            Caption         =   "极座标"
            Height          =   180
            Index           =   2
            Left            =   240
            TabIndex        =   66
            Top             =   960
            Width           =   1215
         End
         Begin VB.OptionButton Coordinate 
            Caption         =   "相对座标"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   65
            Top             =   600
            Width           =   1215
         End
         Begin VB.OptionButton Coordinate 
            Caption         =   "绝对座标"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   64
            Top             =   240
            Width           =   1215
         End
      End
      Begin VB.Frame fraSample3 
         Caption         =   "单位"
         Height          =   1785
         Left            =   240
         TabIndex        =   10
         Top             =   360
         Width           =   3255
         Begin VB.TextBox Ratio2 
            Height          =   270
            Left            =   2160
            TabIndex        =   36
            Top             =   1200
            Width           =   855
         End
         Begin VB.TextBox Ratio1 
            Height          =   270
            Left            =   960
            TabIndex        =   34
            Top             =   1200
            Width           =   855
         End
         Begin VB.ComboBox Unit 
            Height          =   345
            IMEMode         =   2  'OFF
            ItemData        =   "options.frx":144C
            Left            =   960
            List            =   "options.frx":1474
            Style           =   2  'Dropdown List
            TabIndex        =   30
            Top             =   480
            Width           =   1335
         End
         Begin VB.Label Label11 
            AutoSize        =   -1  'True
            Caption         =   "："
            BeginProperty Font 
               Name            =   "宋体"
               Size            =   18
               Charset         =   134
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   360
            Left            =   1920
            TabIndex        =   35
            Top             =   1080
            Width           =   360
         End
         Begin VB.Label Label10 
            AutoSize        =   -1  'True
            Caption         =   "比例尺"
            Height          =   180
            Left            =   240
            TabIndex        =   33
            Top             =   1320
            Width           =   540
         End
         Begin VB.Label Label9 
            AutoSize        =   -1  'True
            Caption         =   "单位:"
            Height          =   180
            Left            =   240
            TabIndex        =   29
            Top             =   600
            Width           =   450
         End
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   1
      Left            =   1320
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   1200
      Visible         =   0   'False
      Width           =   5685
      Begin VB.Frame fraSample4 
         Caption         =   "颜色"
         Height          =   1065
         Index           =   0
         Left            =   2520
         TabIndex        =   81
         Top             =   2640
         Width           =   3015
         Begin VB.Label GenerallyColor 
            AutoSize        =   -1  'True
            Caption         =   "修改画图时的参考颜色"
            Height          =   180
            Index           =   0
            Left            =   120
            MouseIcon       =   "options.frx":14C6
            MousePointer    =   99  'Custom
            TabIndex        =   83
            Top             =   360
            Width           =   1800
         End
         Begin VB.Label GenerallyColor 
            AutoSize        =   -1  'True
            Caption         =   "修改选取到目标后突出显示颜色"
            Height          =   180
            Index           =   1
            Left            =   120
            MouseIcon       =   "options.frx":17D0
            MousePointer    =   99  'Custom
            TabIndex        =   82
            Top             =   720
            Width           =   2520
         End
      End
      Begin VB.CheckBox Check1 
         BackColor       =   &H00C0C0C0&
         Caption         =   "恢复系统初始值 "
         Height          =   255
         Left            =   120
         TabIndex        =   32
         Top             =   3360
         Width           =   2175
      End
      Begin VB.CheckBox ShowPaper 
         Caption         =   "显示选取图纸窗口"
         Height          =   255
         Left            =   120
         TabIndex        =   22
         Top             =   3000
         Width           =   2175
      End
      Begin VB.CheckBox SaveToIniFile 
         Caption         =   "在配置文件中保存设置"
         Height          =   255
         Left            =   120
         TabIndex        =   21
         Top             =   2640
         Width           =   2295
      End
      Begin VB.Frame fraSample2 
         Caption         =   "桌面"
         Height          =   2265
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   4335
         Begin VB.TextBox PaperUnits 
            Enabled         =   0   'False
            Height          =   270
            Left            =   1200
            TabIndex        =   28
            Top             =   1080
            Width           =   855
         End
         Begin VB.TextBox PaperHeight 
            Enabled         =   0   'False
            Height          =   270
            Left            =   1080
            TabIndex        =   27
            Top             =   1800
            Width           =   975
         End
         Begin VB.TextBox PaperWidth 
            Enabled         =   0   'False
            Height          =   270
            Left            =   1080
            TabIndex        =   26
            Top             =   1440
            Width           =   975
         End
         Begin VB.PictureBox Picdesk 
            AutoRedraw      =   -1  'True
            BackColor       =   &H00FF0000&
            Height          =   1815
            Left            =   2400
            ScaleHeight     =   1755
            ScaleWidth      =   1755
            TabIndex        =   19
            Top             =   240
            Width           =   1815
            Begin VB.PictureBox Picpaper 
               BackColor       =   &H8000000E&
               Height          =   855
               Left            =   600
               ScaleHeight     =   795
               ScaleWidth      =   555
               TabIndex        =   20
               Top             =   480
               Width           =   615
            End
         End
         Begin VB.Label Label8 
            AutoSize        =   -1  'True
            Caption         =   "高度:"
            Height          =   180
            Left            =   360
            TabIndex        =   25
            Top             =   1920
            Width           =   450
         End
         Begin VB.Label Label7 
            AutoSize        =   -1  'True
            Caption         =   "宽度:"
            Height          =   180
            Left            =   360
            TabIndex        =   24
            Top             =   1560
            Width           =   450
         End
         Begin VB.Label Label6 
            AutoSize        =   -1  'True
            Caption         =   "图纸大小"
            Height          =   180
            Left            =   360
            TabIndex        =   23
            Top             =   1080
            Width           =   720
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "修改图板的颜色"
            Height          =   180
            Left            =   360
            MouseIcon       =   "options.frx":1ADA
            MousePointer    =   99  'Custom
            TabIndex        =   18
            Top             =   720
            Width           =   1260
         End
         Begin VB.Label Label4 
            AutoSize        =   -1  'True
            Caption         =   "修改图纸的颜色"
            Height          =   180
            Left            =   360
            MouseIcon       =   "options.frx":1DE4
            MousePointer    =   99  'Custom
            TabIndex        =   17
            Top             =   360
            Width           =   1260
         End
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'None
      Height          =   3780
      Index           =   0
      Left            =   240
      ScaleHeight     =   3780
      ScaleWidth      =   5685
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   600
      Width           =   5685
      Begin VB.Frame Frame3 
         Caption         =   "文字"
         Height          =   735
         Left            =   360
         TabIndex        =   67
         Top             =   2400
         Width           =   2295
         Begin VB.Label text 
            AutoSize        =   -1  'True
            Caption         =   "字体"
            Height          =   180
            Left            =   240
            MouseIcon       =   "options.frx":20EE
            MousePointer    =   99  'Custom
            TabIndex        =   69
            Top             =   360
            Width           =   360
         End
         Begin VB.Label textcolor 
            AutoSize        =   -1  'True
            Caption         =   "字体颜色"
            Height          =   180
            Left            =   1200
            MouseIcon       =   "options.frx":23F8
            MousePointer    =   99  'Custom
            TabIndex        =   68
            Top             =   360
            Width           =   720
         End
      End
      Begin VB.PictureBox pen 
         AutoRedraw      =   -1  'True
         BackColor       =   &H8000000E&
         Height          =   1095
         Left            =   3840
         ScaleHeight     =   1035
         ScaleWidth      =   1635
         TabIndex        =   16
         Top             =   2640
         Width           =   1695
      End
      Begin VB.Frame fraSample1 
         Caption         =   "笔"
         Height          =   2025
         Left            =   210
         TabIndex        =   5
         Top             =   255
         Width           =   3495
         Begin VB.ComboBox 线形 
            Height          =   345
            ItemData        =   "options.frx":2702
            Left            =   2040
            List            =   "options.frx":2715
            Style           =   2  'Dropdown List
            TabIndex        =   15
            Top             =   960
            Width           =   1215
         End
         Begin VB.ComboBox Combo1 
            Height          =   345
            ItemData        =   "options.frx":276D
            Left            =   2040
            List            =   "options.frx":278F
            Style           =   2  'Dropdown List
            TabIndex        =   12
            Top             =   480
            Width           =   1215
         End
         Begin VB.Label Label3 
            AutoSize        =   -1  'True
            Caption         =   "笔画类型"
            Height          =   180
            Left            =   360
            TabIndex        =   14
            Top             =   1080
            Width           =   720
         End
         Begin VB.Label Label2 
            AutoSize        =   -1  'True
            Caption         =   "笔画宽度"
            Height          =   180
            Left            =   360
            TabIndex        =   13
            Top             =   600
            Width           =   720
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "笔的颜色"
            Height          =   180
            Left            =   360
            MouseIcon       =   "options.frx":27B2
            MousePointer    =   99  'Custom
            TabIndex        =   11
            Top             =   1560
            Width           =   720
         End
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
      Top             =   4455
      Width           =   1095
   End
   Begin MSComctlLib.TabStrip Options 
      Height          =   4245
      Left            =   240
      TabIndex        =   0
      Top             =   360
      Width           =   5895
      _ExtentX        =   10398
      _ExtentY        =   7488
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   5
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "笔和文字"
            Key             =   "pen"
            Object.ToolTipText     =   "笔"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "常规选项"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "单位、比例、座标和鼠标"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "标注尺寸"
            Key             =   "dimension"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab5 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "栅格"
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
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   0
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
End
Attribute VB_Name = "fOption"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'设置窗口
'作者:康林

Option Explicit

Private NoExitFlag As Boolean   '是否退出本窗口的标志
Private DrawParameter As Commonparameter '笔的参数,不要保存到配置文件中
Private Word As FontType    '文字参数
Private Type GenerallyType   '常规类型
        desk As DeskType   '详见mmain.bas中的定义
        PaperColor As ColorConstants
        Paper As PaperType   '详见mmain.bas中的定义
        Mouse As String    '鼠标形状
        MouseColor As ColorConstants '鼠标标颜色
        Viewcolor As ColorConstants  '画图时的预览颜色,在mmain中定义
        ShowObjectColor As ColorConstants   '选取到目标的突出显示颜色,在formcad中定义
        End Type
Private Generally As GenerallyType '常规的参数,要保存到配置文件中
Private Dimen As DimensionType     '标注的参数,要保存到配置文件中
Private Type GirdType
        Style As Integer '类型
        Color As ColorConstants '颜色
        Distance As Single '间距
        End Type
Private Type OtherType    '其它中的变量,保存到配置文件中
        Gird As GirdType  '栅格类型
        End Type
Private Other As OtherType
Private SaveParameterToInifileFlag As Boolean  '是否保存参数到配置文件中的标志
Private RedoSystemInitialStatusflag As Boolean '恢复系统初始值

Private Sub Form_Load()
'说明:Object定义见mmain.bas中,此过程中传递的是子窗体
Dim i, ss As String * 10

    '置中窗体
    Me.Move (Screen.Width - Me.Width) / 2, (Screen.Height - Me.Height) / 2
    Options.top = 120   ' 置中TapStrip框
    Options.left = 105
    With picOptions(0)
         .left = 210
         .top = 480
    End With
    
    '笔和文字(不要保存到配置文件中)
    With DrawParameter '笔
         Combo1.text = Combo1.List(fMainForm.ActiveForm.cad.DrawWidth - 1)    '笔画的粗细
         .Width = Val(Combo1.text)
         线形.text = 线形.List(fMainForm.ActiveForm.cad.DrawStyle)        '笔画的类型
        .Style = fMainForm.ActiveForm.cad.DrawStyle
        .Color = fMainForm.ActiveForm.GetLineColor
        '提示图
        pen.DrawWidth = .Width
        pen.DrawStyle = .Style
        PenShow  '显示
    End With
    With fMainForm.ActiveForm.cad
         Word.Bold = .FontBold
         Word.Color = .ForeColor
         Word.Italic = .FontItalic
         Word.name = .FontName
         Word.Size = .FontSize
         Word.Strikethru = .FontStrikethru
         Word.Transparent = .FontTransparent
         Word.Underline = .FontUnderline
    End With
    
    '常规
    With Generally   '图纸和图板颜色(以后要保存到配置文件中)
         .desk.Color = fMainForm.ActiveForm.desk.BackColor
         .PaperColor = fMainForm.ActiveForm.cad.BackColor
         Picdesk.BackColor = .desk.Color
         Picpaper.BackColor = .PaperColor
         .Viewcolor = Viewcolor Xor Generally.Paper.Color  '进行异或操作变为本色
         .ShowObjectColor = fMainForm.ActiveForm.GetShowObjectColor Xor Generally.Paper.Color
    End With
    '图纸的大小(不要保存到配置文件中,已在图纸选取窗口中保存到配置文件中)
    PaperUnits.text = fMainForm.ActiveForm.GetPaperUnits  '显示图纸单位
    i = GetPrivateProfileString("paper", "width", "8900", ss, 20, mmain.Inifile)
    If i = 0 Then
       ss = "8900"
    Else
       ss = left$(ss, i)
    End If
    PaperWidth.text = Val(ss)  '显示
    i = GetPrivateProfileString("paper", "height", "4900", ss, 20, mmain.Inifile)
    If i = 0 Then
       ss = "4800"
    Else
       ss = left$(ss, i)
    End If
    PaperHeight.text = Val(ss) '显示
    '复选框,显示选取图纸窗口(不要保存到配置文件中,在点击时就已保存到配置文件中)
    i = GetPrivateProfileString("选项", "在启动时显示选取图纸窗口", "1", ss, 10, Inifile)
    If i <> 0 Then
       ss = left$(ss, i)
    Else
       ss = "1"
    End If
    If Val(ss) <> 0 Then
       ShowPaper.Value = vbChecked
    End If
    '复选框,在配置文件中保存设置(不要保存到配置文件中,在点击时就已保存到配置文件中)
    i = GetPrivateProfileString("选项", "把设置保存在配置文件中", "1", ss, 10, Inifile)
    If i <> 0 Then
       ss = left$(ss, i)
    Else
       ss = "1"
    End If
    If Val(ss) <> 0 Then
       SaveToIniFile.Value = vbChecked
       SaveParameterToInifileFlag = True '保存参数到配置文件中的标志
    Else
       SaveParameterToInifileFlag = False
    End If
    '复选框,恢复系统初始值
    RedoSystemInitialStatusflag = False
       
    '单位和比例尺,座标
    With Generally '(以后要保存到配置文件中)
         .Paper.Units = fMainForm.ActiveForm.GetPaperUnits   '单位
         Unit.text = fMainForm.ActiveForm.GetPaperUnits '显示单位
         '比例尺
         .Paper.Ratio = fMainForm.ActiveForm.GetPaperRatio
         .Paper.Ratio1 = fMainForm.ActiveForm.GetPaperRatio1
         .Paper.Ratio2 = fMainForm.ActiveForm.GetPaperRatio2
         Ratio1.text = .Paper.Ratio1 '显示
         Ratio2.text = .Paper.Ratio2
         ' 座标
         .desk.Coordinates = Coordinates
         Coordinate.Item(Coordinates).Value = True
         '鼠标
         .Mouse = fMainForm.ActiveForm.GetMouseStyle '鼠标形形状
         Mouse.text = .Mouse
         .MouseColor = fMainForm.ActiveForm.Line1.BorderColor    '鼠标颜色
    End With
    
    '标注
    With Dimension '(以后不要保存到配置文件中)
         Dimen.ArrowSize = .ArrowSize
         DimASize.text = CStr(.ArrowSize)
         Dimen.AutoDimension = .AutoDimension
         DimAutoDim.Value = .AutoDimension
         Dimen.DimensionUnits = .DimensionUnits
         DimUnit.Value = .DimensionUnits
         Dimen.DimensionColor = .DimensionColor
         Dline.BorderColor = .DimensionColor '参考图形
         Dimen.ExtensioneLineColor = .ExtensioneLineColor
         DimFELine1.BorderColor = Color '参考图形
         DimSELine1.BorderColor = Color
         Dimen.FirstDimension = .FirstDimension
         Dimen.FirstExtensinonLine = .FirstExtensinonLine
         DimFELine.Value = .FirstExtensinonLine
         DimSELine.Value = .SecondExtensioneLine
         DimFELine1.Visible = .FirstExtensinonLine
         Dimen.Font = .Font
         DimText.Font.Bold = .Font.Bold '参考图形
         DimText.Font.Italic = .Font.Italic
         DimText.Font.name = .Font.name
         DimText.Font.Size = .Font.Size
         DimText.Font.Strikethrough = .Font.Strikethru
         DimText.Font.Underline = .Font.Underline
         Dimen.FontState = .FontState
         DimState(.FontState).Value = True
         Dimen.LeftArrowHead = .LeftArrowHead
         DimLeftarrow.text = DimLeftarrow.List(.LeftArrowHead)
         Dimen.OutsideDimension = .OutsideDimension
         Dimen.Position = .Position
         DimPos(.Position).Value = True
         Dimen.RightArrowHead = .RightArrowHead
         DimRightarrow.text = DimRightarrow.List(.RightArrowHead)
         DimP.Cls
         DrawArrow DimP, .DimensionColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, .LeftArrowHead, .RightArrowHead, .ArrowSize, True, 0
         Dimen.SecondDimension = .SecondDimension
         Dimen.SecondExtensioneLine = .SecondExtensioneLine
         DimSELine1.Visible = .SecondExtensioneLine
         DimSELine.Value = .SecondExtensioneLine
         Dimen.Style = .Style
         For i = 0 To 7
             If DimStyle(i).Caption = .Style Then
                DimStyle(i).Value = True
             End If
         Next i
    End With
    
    Me.Refresh
    
    '其它
    With Other '(以后要保存到配置文件中)
         '栅格类型
         With .Gird
              '.Style = fMainForm.ActiveForm formcad.GIRDl.Item(1).BorderStyle
              'Gird.ListIndex = .Style
              '.Color = fMainForm.ActiveForm.GIRDl.BorderColor
             '.Distance = fMainForm.ActiveForm.GIRDl.Tag
             'GirdDis.text = CStr(.Distance)
         End With
         
    End With
         
End Sub

Private Sub cmdApply_Click()   '应用
Dim i

    If RedoSystemInitialStatusflag Then '恢复系统初始值
       i = MsgBox("你是否真想恢复到系统初始值？那将丢失所有用户值。", vbQuestion + vbDefaultButton2 + vbYesNoCancel, "恢复系统设置")
       Select Case i
              Case vbYes
                   Kill (Inifile)   '删除配置文件
                   i = MsgBox("已恢复到系统的初始值，要使其生效，" + Chr$(13) + _
                              "     须重新启动本应用程序。" + Chr$(13) + _
                              "           重启吗？", vbQuestion + vbYesNo + vbDefaultButton2, "选项")
                   If i = vbYes Then
                      Shell App.EXEName, vbMaximizedFocus
                      Unload fMainForm   '程序结束
                   End If
                   Exit Sub
              Case vbCancel
                   NoExitFlag = True
        End Select
    End If
    
    '笔和文本
    fMainForm.ActiveForm.InputDrawColor DrawParameter.Color '笔画颜色
    With fMainForm.ActiveForm.cad ' 笔
        .DrawWidth = DrawParameter.Width '笔画粗细
        .DrawStyle = DrawParameter.Style '笔画类型
    End With
    With fMainForm.ActiveForm.cad '文本
         .FontBold = Word.Bold
         .ForeColor = Word.Color
         .FontItalic = Word.Italic
         .Font.name = Word.name
         .FontSize = Word.Size
         .FontStrikethru = Word.Strikethru
         .FontTransparent = Word.Transparent
         .FontUnderline = Word.Underline
    End With
    
    '常规
    With Generally  '图纸和图板颜色(要保存到配置文件中)
         fMainForm.ActiveForm.desk.BackColor = .desk.Color
         fMainForm.ActiveForm.cad.BackColor = .PaperColor
         Viewcolor = .Viewcolor Xor Generally.Paper.Color   '画图时的预览颜色
         fMainForm.ActiveForm.InputShowObjectColor (.ShowObjectColor Xor Generally.Paper.Color)  '突出显示颜色
         For i = 0 To 8
             fMainForm.ActiveForm.Shape1(i).BorderColor = .ShowObjectColor + .ShowObjectColor Mod 255
             fMainForm.ActiveForm.Shape1(i).FillColor = .ShowObjectColor + .ShowObjectColor Mod 255
         Next i
         fMainForm.ActiveForm.SPshow.BorderColor = .ShowObjectColor + .ShowObjectColor Mod 255
    End With
    
    '单位和比例尺,座标和鼠标
    With Generally
         fMainForm.ActiveForm.InputPaperUnits (.Paper.Units)
         fMainForm.ActiveForm.InputPaperRatio (.Paper.Ratio)
         fMainForm.ActiveForm.InputPaperRatio1 (.Paper.Ratio1)
         fMainForm.ActiveForm.InputPaperRatio2 (.Paper.Ratio2)
         Coordinates = .desk.Coordinates '座标
         '鼠标
         fMainForm.ActiveForm.InputMouseStyle (.Mouse) '鼠标形状
         fMainForm.ActiveForm.Form_Activate
         .MouseColor = .MouseColor
         fMainForm.ActiveForm.Line1.BorderColor = .MouseColor '自定义鼠标颜色
         fMainForm.ActiveForm.Line2.BorderColor = .MouseColor
         'fMainForm.ActiveForm.Smouse.BorderColor = .MouseColor
    End With
    
    '标注
    With Dimension
         .ArrowSize = Dimen.ArrowSize
         .AutoDimension = Dimen.AutoDimension
         .DimensionUnits = Dimen.DimensionUnits
         .DimensionColor = Dimen.DimensionColor
         .ExtensioneLineColor = Dimen.ExtensioneLineColor
         .FirstDimension = Dimen.FirstDimension
         .FirstExtensinonLine = Dimen.FirstExtensinonLine
         .Font = Dimen.Font
         .FontState = Dimen.FontState
         .LeftArrowHead = Dimen.LeftArrowHead
         .OutsideDimension = Dimen.OutsideDimension
         .Position = Dimen.Position
         .RightArrowHead = Dimen.RightArrowHead
         .SecondDimension = Dimen.SecondDimension
         .SecondExtensioneLine = Dimen.SecondExtensioneLine
         .Style = Dimen.Style
    End With
    
    '其它
    With Other
         '栅格类型
         With .Gird
              'fMainForm.ActiveForm.GIRDl.DrawStyle = .Style
              'fMainForm.ActiveForm.GIRDl.BorderColor = .Color
              
         End With
    End With
    
    '保存参数到配置文件中,
    If SaveParameterToInifileFlag Then
        With Generally '对照face.bas 中相应的初始化过程
             '图纸颜色
             i = WritePrivateProfileString("选项", "图纸颜色", CStr(.PaperColor), Inifile)
             '图板颜色
             i = WritePrivateProfileString("选项", "图板颜色", CStr(.desk.Color), Inifile)
              '画图时的预览颜色
             i = WritePrivateProfileString("选项", "画图时的预览颜色", CStr(.Viewcolor), Inifile)
             '选取到目标时的突出显示颜色
             i = WritePrivateProfileString("选项", "突出显示颜色", CStr(.ShowObjectColor), Inifile)
            '单位
             i = WritePrivateProfileString("选项", "单位", .Paper.Units, Inifile)
             '比例尺
             i = WritePrivateProfileString("选项", "比例尺", CStr(.Paper.Ratio), Inifile)
             i = WritePrivateProfileString("选项", "比例尺1", CStr(.Paper.Ratio1), Inifile)
             i = WritePrivateProfileString("选项", "比例尺2", CStr(.Paper.Ratio2), Inifile)
             '座标
             i = WritePrivateProfileString("选项", "座标", CStr(.desk.Coordinates), Inifile)
             '鼠标形状
             i = WritePrivateProfileString("选项", "鼠标形状", .Mouse, Inifile)
             i = WritePrivateProfileString("选项", "自定义鼠标颜色", CStr(.MouseColor), Inifile)
        End With
        With Other
             
        End With
    End If
    
    fMainForm.ActiveForm.Redraw
End Sub

Private Sub cmdCancel_Click()  '取消
    Unload Me
End Sub

Private Sub cmdOK_Click() '确定
    'MsgBox "在这里放置代码来设置选项并且关闭对话框!"
    cmdApply_Click
    If Not NoExitFlag Then
       Unload Me
    End If
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim i As Integer
    '处理 ctrl+tab 键来移动到下一个选项
    If Shift = vbCtrlMask And KeyCode = vbKeyTab Then
        i = Options.SelectedItem.Index
        If i = Options.Tabs.Count Then
            '已到达最后的选项,转回到选项 1
            Set Options.SelectedItem = Options.Tabs(1)
        Else
            '递增选项
            Set Options.SelectedItem = Options.Tabs(i + 1)
        End If
    End If
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
        Exit Sub
End Sub

Private Sub Options_Click()
    
    Dim i As Integer
    '显示并使选项的控件可用
    '并且隐藏使其他被禁用
    For i = 0 To Options.Tabs.Count - 1
        If i = Options.SelectedItem.Index - 1 Then
           With picOptions(i)
                .left = 210
                .top = 480
                .Visible = True
                .Enabled = True
           End With
        Else
           With picOptions(i)
                .left = -20000
                .Visible = False
                .Enabled = False
            End With
        End If
    Next
    
End Sub

'笔
Private Sub Label1_Click()  '颜色
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = DrawParameter.Color
             .ShowColor
        End With
        DrawParameter.Color = CommonDialog1.Color
        PenShow   '预览
End Sub

Private Sub Combo1_Click() '线宽
        DrawParameter.Width = Val(Combo1.text)
        pen.DrawWidth = DrawParameter.Width '预览
        PenShow '预览
End Sub

Private Sub 线形_Click() '线类型
Dim Style
#If ON_ERROR_RESUME_NEXT Then
  On Error Resume Next
#End If
  Style = 线形.ListIndex
  DrawParameter.Style = Style
  pen.DrawStyle = Style '预览
  PenShow '预览
End Sub

Private Sub PenShow()  '预览显示
        pen.Cls
        pen.Line (300, 200)-(1300, 900), DrawParameter.Color, B
End Sub

Private Sub text_Click() '文字字体
        With CommonDialog1
             .Flags = cdlCFEffects + cdlCFScreenFonts
             .FontBold = Word.Bold
             .FontItalic = Word.Italic
             .FontName = Word.name
             .FontSize = Word.Size
             .FontStrikethru = Word.Strikethru
             .FontUnderline = Word.Underline
             .ShowFont
             Word.Bold = .FontBold
             Word.Italic = .FontItalic
             Word.name = .FontName
             Word.Size = .FontSize
             Word.Strikethru = .FontStrikethru
             Word.Transparent = False
             Word.Underline = .FontUnderline
        End With
End Sub

Private Sub textcolor_Click() '文字颜色
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Word.Color
             .ShowColor
             Word.Color = .Color
        End With
End Sub

'常规
Private Sub Label4_Click()  '修改图纸颜色
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Generally.PaperColor
             .ShowColor
        End With
        Generally.PaperColor = CommonDialog1.Color
        '预览
        Picpaper.BackColor = CommonDialog1.Color '预览
End Sub

Private Sub Label5_Click()  '修改图板的颜色
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Generally.desk.Color
             .ShowColor
        End With
        Generally.desk.Color = CommonDialog1.Color
        '预览
        Picdesk.BackColor = CommonDialog1.Color
End Sub

Private Sub SaveToIniFile_Click() '在配置文件中保存设置
        Dim i
        i = WritePrivateProfileString("选项", "把设置保存在配置文件中", CStr(SaveToIniFile.Value), Inifile)
        If SaveToIniFile.Value <> 0 Then  '是否保存参数到配置文件中
           SaveParameterToInifileFlag = True
        Else
           SaveParameterToInifileFlag = False
        End If
End Sub

Private Sub ShowPaper_Click() '显示图纸选取窗体
Dim i
i = WritePrivateProfileString("选项", "在启动时显示选取图纸窗口", CStr(ShowPaper.Value), Inifile)
End Sub

Private Sub Check1_Click()  '恢复系统初始值
Dim i
        If Check1.Value <> 0 Then
           i = MsgBox("你是否真想恢复到系统初始值？" + Chr$(13) + "那将丢失所有用户值。", vbQuestion + vbYesNo + vbDefaultButton2, "恢复系统设置")
           If i = vbYes Then
              RedoSystemInitialStatusflag = True
           Else
              RedoSystemInitialStatusflag = False
              Check1.Value = Unchecked
           End If
        End If
End Sub

Private Sub GenerallyColor_Click(Index As Integer)
Dim m As Integer
m = DimP.DrawMode
        With Generally
             Select Case Index
                    Case 0  '画图时的预鉴颜色
                         CommonDialog1.Color = .Viewcolor
                         CommonDialog1.Flags = cdlCCFullOpen + cdlCCRGBInit
                         CommonDialog1.ShowColor
                         .Viewcolor = CommonDialog1.Color
                    Case 1 '突出显示颜色
                         CommonDialog1.Color = .ShowObjectColor
                         CommonDialog1.Flags = cdlCCFullOpen + cdlCCRGBInit
                         CommonDialog1.ShowColor
                         .ShowObjectColor = CommonDialog1.Color
             End Select
        End With
DimP.DrawMode = m
End Sub

'单位和比例尺,座标和鼠标
Private Sub Unit_Click()   '单位
        Generally.Paper.Units = Unit.List(Unit.ListIndex)
        PaperUnits.text = Generally.Paper.Units  '图纸单位
        DimUnit_Click '标注中的参考图形中的单位
End Sub

Private Sub Ratio1_Change()  '比例尺1
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        With Generally
             .Paper.Ratio1 = Ratio1.text
             .Paper.Ratio = Val(Ratio2.text) / Val(Ratio1.text)
        End With
End Sub

Private Sub Ratio2_Change() ' 比例尺2
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        With Generally.Paper
             .Ratio2 = Ratio2.text
             .Ratio = Val(Ratio2.text) / Val(Ratio1.text)
        End With
End Sub

Private Sub Coordinate_Click(Index As Integer)  '座标
        Generally.desk.Coordinates = Index
End Sub

Private Sub Mouse_Click() '鼠标形状
        Generally.Mouse = Mouse.List(Mouse.ListIndex)
End Sub

Private Sub MouseColor_Click() ' 自定义鼠标颜色
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Generally.MouseColor
             .ShowColor
             Generally.MouseColor = .Color
        End With
End Sub

'标注
Private Sub DimStyle_Click(Index As Integer) '标注类型
        Dimen.Style = DimStyle(Index).Caption
End Sub

Private Sub DimLeftarrow_Click() '左箭头
        Dimen.LeftArrowHead = DimLeftarrow.ListIndex
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimRightarrow_Click() '右箭头
        Dimen.RightArrowHead = DimRightarrow.ListIndex
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimASize_Click() '箭头尺寸
        Dimen.ArrowSize = Val(DimASize.text)
        DimP.Cls '参考图形
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimState_Click(Index As Integer) '字体状态
        Dimen.FontState = Index
End Sub

Private Sub DimPos_Click(Index As Integer) '标注位置
        Dimen.Position = Index
        With DimText '参考图形
             Select Case Index
                    Case 0
                         .top = Dline.Y1 - .Height
                    Case 1
               
                    Case 2
                         .top = Dline.Y1 - .Height / 2
             End Select
        End With
End Sub

Private Sub DimFELine_Click() '第一条延长线
        Dimen.FirstExtensinonLine = DimFELine.Value
        DimFELine1.Visible = DimFELine.Value '参考图形
End Sub

Private Sub DimSELine_Click() '第二条延长线
        Dimen.SecondExtensioneLine = DimSELine.Value
        DimSELine1.Visible = DimSELine.Value '参考图形
End Sub

Private Sub DimAutoDim_Click() '自动标注
        Dimen.AutoDimension = DimAutoDim.Value
        If DimAutoDim.Value Then '参考图形
           DimText.Visible = True
        Else
           DimText.Visible = False
        End If
End Sub

Private Sub DimUnit_Click() '自动标注单位
        Dimen.DimensionUnits = DimUnit.Value
        With Dline
             If DimUnit.Value Then
                DimText.Caption = "100" & Generally.Paper.Units
                DimText.left = (.X1 + .X2) / 2 - DimText.Width / 2
             Else
                DimText.Caption = "100"
                DimText.left = (.X1 + .X2) / 2 - DimText.Width / 2
             End If
        End With
End Sub

Private Sub DimFont_Click() '标注字体
        With CommonDialog1
             .Flags = cdlCFEffects + cdlCFBoth + cdlCFScalableOnly
             .FontBold = Word.Bold
             .FontItalic = Word.Italic
             .FontName = Word.name
             .FontSize = Word.Size
             .FontStrikethru = Word.Strikethru
             .FontUnderline = Word.Underline
             .ShowFont
             Dimen.Font.Bold = .FontBold
             Dimen.Font.Italic = .FontItalic
             Dimen.Font.name = .FontName
             Dimen.Font.Size = .FontSize
             Dimen.Font.Strikethru = .FontStrikethru
             Dimen.Font.Transparent = False
             Dimen.Font.Underline = .FontUnderline
             DimText.Font.Bold = .FontBold     '参考图形
             DimText.Font.Italic = .FontItalic
             DimText.Font.name = .FontName
             DimText.Font.Size = .FontSize
             DimText.Font.Strikethrough = .FontStrikethru
             DimText.Font.Underline = .FontUnderline
        End With
        With Dline  '参考图形
             DimText.left = (.X1 + .X2) / 2 - DimText.Width / 2
             Select Case Dimen.Position
                    Case 0
                         DimText.top = .Y1 - DimText.Height
                    Case 1
                    
                    Case 2
                         DimText.top = .Y1 - DimText.Height / 2
             End Select
        End With
End Sub

Private Sub DimFontColor_Click() '标注字体颜色
        With CommonDialog1
            .Flags = cdlCCFullOpen + cdlCCRGBInit
            .Color = Dimen.Font.Color
             .ShowColor
             Dimen.Font.Color = .Color
             DimText.ForeColor = .Color  '参考图形
        End With
End Sub

Private Sub Dimline_Click() '标注线颜色
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Dimen.DimensionColor
             .ShowColor
             Dimen.DimensionColor = .Color
             Dline.BorderColor = .Color  '参考图形
        End With
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimELine_Click() '延长线颜色
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Dimen.ExtensioneLineColor
             .ShowColor
             Dimen.ExtensioneLineColor = .Color
             DimFELine1.BorderColor = .Color   '参考图形
             DimSELine1.BorderColor = .Color
        End With
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub Gird_Click() '栅格类型
Dim Style
#If ON_ERROR_RESUME_NEXT Then
  On Error Resume Next
#End If
  Style = Gird.ListIndex
  Other.GirdStyle = Style
  pen.DrawStyle = Style '预览
  PenShow '预览
End Sub


'其它
         

