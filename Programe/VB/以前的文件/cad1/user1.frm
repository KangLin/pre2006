VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   0  'None
   Caption         =   "制图"
   ClientHeight    =   5400
   ClientLeft      =   45
   ClientTop       =   10860
   ClientWidth     =   6840
   LinkTopic       =   "Form1"
   ScaleHeight     =   360
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   456
   StartUpPosition =   2  '屏幕中心
   Begin MSComctlLib.Toolbar Toolbar2 
      Height          =   1380
      Left            =   0
      TabIndex        =   13
      Top             =   3360
      Width           =   375
      _ExtentX        =   661
      _ExtentY        =   2434
      ButtonWidth     =   609
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   4
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "selectobject"
            Object.Tag             =   "选取目标  (点选)"
            ImageKey        =   "pointselect"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "selectobjectfield"
            Object.ToolTipText     =   "目标选取  (区域选)"
            ImageKey        =   "selectfield"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "allselect"
            Object.ToolTipText     =   "全选"
            ImageKey        =   "all"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "exitselect"
            Object.ToolTipText     =   "退出选取"
            ImageKey        =   "cls"
         EndProperty
      EndProperty
   End
   Begin VB.TextBox tishitext2 
      Height          =   270
      Left            =   8040
      TabIndex        =   3
      ToolTipText     =   "用上下光标健进行输入框互换"
      Top             =   6240
      Width           =   975
   End
   Begin VB.TextBox tishitext1 
      Height          =   270
      Left            =   5160
      TabIndex        =   2
      ToolTipText     =   "用上下光标健进行输入框互换"
      Top             =   6240
      Width           =   975
   End
   Begin MSComctlLib.Toolbar snapetool 
      Height          =   1710
      Left            =   0
      TabIndex        =   12
      Top             =   840
      Visible         =   0   'False
      Width           =   420
      _ExtentX        =   741
      _ExtentY        =   3016
      ButtonWidth     =   609
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   5
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "lineendpoint"
            Object.ToolTipText     =   "线段或圆弧的端点"
            ImageKey        =   "end"
            Style           =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "snapelinemid"
            Object.ToolTipText     =   "捕捉线段或圆弧的中点"
            ImageKey        =   "mid"
            Style           =   1
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "snapecirclepoint"
            Object.ToolTipText     =   "捕捉圆心"
            ImageKey        =   "cirpoint"
            Style           =   1
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "snapemisspoint"
            Object.ToolTipText     =   "捕捉交点"
            ImageKey        =   "miss"
            Style           =   1
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "exitsnape"
            Object.ToolTipText     =   "退出捕捉"
            ImageKey        =   "cls"
            Style           =   1
         EndProperty
      EndProperty
   End
   Begin VB.Timer Timer 
      Left            =   480
      Top             =   1560
   End
   Begin MSComctlLib.StatusBar dispbar 
      Height          =   375
      Left            =   120
      TabIndex        =   11
      Top             =   4680
      Visible         =   0   'False
      Width           =   9405
      _ExtentX        =   16589
      _ExtentY        =   661
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   5
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
            Enabled         =   0   'False
            Object.Width           =   2011
            MinWidth        =   2011
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Bevel           =   2
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
            Enabled         =   0   'False
         EndProperty
         BeginProperty Panel4 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Bevel           =   2
         EndProperty
         BeginProperty Panel5 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar Toolrectangle 
      Height          =   390
      Left            =   4680
      TabIndex        =   9
      Top             =   0
      Width           =   555
      _ExtentX        =   979
      _ExtentY        =   688
      ButtonWidth     =   609
      ButtonHeight    =   582
      ImageList       =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   5
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "rectangle"
            Object.ToolTipText     =   "矩形"
            ImageKey        =   "Rectangle"
            Style           =   5
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "zhen"
            Object.ToolTipText     =   "正方形"
            ImageKey        =   "same"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "tree"
            Object.ToolTipText     =   "三角形"
            ImageKey        =   "tree"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "stree"
            Object.ToolTipText     =   "正三角表"
            ImageKey        =   "stree"
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "six"
            Object.ToolTipText     =   " 正六边形"
            ImageKey        =   "six"
         EndProperty
      EndProperty
   End
   Begin VB.VScrollBar deskvscroll 
      Height          =   1455
      Left            =   5760
      TabIndex        =   15
      TabStop         =   0   'False
      Top             =   2040
      Width           =   255
   End
   Begin VB.HScrollBar deskHScroll 
      Height          =   255
      Left            =   2400
      TabIndex        =   14
      TabStop         =   0   'False
      Top             =   3720
      Width           =   3255
   End
   Begin MSComctlLib.Toolbar Toolcircle 
      Height          =   390
      Left            =   5160
      TabIndex        =   10
      Top             =   0
      Width           =   615
      _ExtentX        =   1085
      _ExtentY        =   688
      ButtonWidth     =   609
      ButtonHeight    =   582
      ImageList       =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   4
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "circle"
            Object.ToolTipText     =   "圆"
            ImageKey        =   "circle"
            Style           =   5
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "Arc"
            Object.ToolTipText     =   "圆弧"
            ImageKey        =   "Arc"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "Ellipse"
            Object.ToolTipText     =   "椭圆"
            ImageKey        =   "Ellipse"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "shan"
            Object.ToolTipText     =   "扇 形"
            ImageKey        =   "ss"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar Toolline 
      Height          =   390
      Left            =   4200
      TabIndex        =   8
      Top             =   0
      Width           =   540
      _ExtentX        =   953
      _ExtentY        =   688
      ButtonWidth     =   609
      ButtonHeight    =   582
      ImageList       =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   3
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Line"
            Object.ToolTipText     =   "直线"
            ImageKey        =   "Line"
            Style           =   5
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "连画线"
            Object.ToolTipText     =   "连画线"
            ImageKey        =   "mulline"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "Line Style"
            Object.ToolTipText     =   "线形"
            ImageKey        =   "Line Style"
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   2400
      Top             =   1680
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      Flags           =   3
   End
   Begin VB.PictureBox desk 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00FFFF00&
      Height          =   2295
      Left            =   1080
      Negotiate       =   -1  'True
      ScaleHeight     =   149
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   277
      TabIndex        =   5
      Top             =   960
      Width           =   4215
      Begin VB.PictureBox cad 
         AutoRedraw      =   -1  'True
         AutoSize        =   -1  'True
         BackColor       =   &H00FFFFFF&
         ClipControls    =   0   'False
         Height          =   2175
         Left            =   0
         ScaleHeight     =   37.306
         ScaleMode       =   6  'Millimeter
         ScaleWidth      =   73.29
         TabIndex        =   6
         Top             =   0
         Width           =   4215
         Begin VB.Label text 
            AutoSize        =   -1  'True
            Caption         =   "Label1"
            Height          =   180
            Left            =   480
            TabIndex        =   16
            Top             =   960
            Visible         =   0   'False
            Width           =   540
         End
      End
   End
   Begin MSComctlLib.Toolbar Toolbar1 
      Height          =   390
      Left            =   0
      TabIndex        =   7
      Top             =   0
      Width           =   4200
      _ExtentX        =   7408
      _ExtentY        =   688
      ButtonWidth     =   609
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlToolbarIcons"
      HotImageList    =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   12
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "New"
            Object.ToolTipText     =   "建立新文件"
            ImageKey        =   "New"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "打开文件"
            ImageKey        =   "Open"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "保存文件"
            ImageKey        =   "Save"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Print"
            Object.ToolTipText     =   "打印"
            ImageKey        =   "Print"
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Delete"
            Object.ToolTipText     =   "删除"
            ImageKey        =   "Delete"
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Undo"
            Object.ToolTipText     =   "取消"
            ImageKey        =   "Undo"
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Redo"
            Object.ToolTipText     =   "重画"
            ImageKey        =   "Redo"
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Copy"
            Object.ToolTipText     =   "复制"
            ImageKey        =   "Copy"
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cut"
            Object.ToolTipText     =   "剪切"
            ImageKey        =   "Cut"
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Paste"
            Object.ToolTipText     =   "粘贴"
            ImageKey        =   "Paste"
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Help"
            Object.ToolTipText     =   "帮助"
            ImageKey        =   "Help"
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "text"
            Object.ToolTipText     =   "文字"
            ImageKey        =   "text"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   480
      Top             =   2160
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483648
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   43
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0000
            Key             =   "New"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0112
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0224
            Key             =   "Save"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0336
            Key             =   "Print"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0448
            Key             =   "Undo"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":055A
            Key             =   "Redo"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":066C
            Key             =   "Copy"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":077E
            Key             =   "Cut"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0890
            Key             =   "Paste"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":09A2
            Key             =   "Delete"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0AB4
            Key             =   "Line"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0BC6
            Key             =   "Rectangle"
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0CD8
            Key             =   "Line Style"
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0DEA
            Key             =   "Arc"
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":0EFC
            Key             =   "Ellipse"
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":100E
            Key             =   "Help"
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":1120
            Key             =   "abc"
         EndProperty
         BeginProperty ListImage18 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":179C
            Key             =   "IMG18"
         EndProperty
         BeginProperty ListImage19 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":1E18
            Key             =   "IMG19"
         EndProperty
         BeginProperty ListImage20 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":1F14
            Key             =   "IMG20"
         EndProperty
         BeginProperty ListImage21 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":2010
            Key             =   "IMG21"
         EndProperty
         BeginProperty ListImage22 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":2124
            Key             =   "mulline1"
         EndProperty
         BeginProperty ListImage23 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":4578
            Key             =   "IMG23"
         EndProperty
         BeginProperty ListImage24 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":63CC
            Key             =   "circle"
         EndProperty
         BeginProperty ListImage25 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":8220
            Key             =   "mulline"
         EndProperty
         BeginProperty ListImage26 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":A074
            Key             =   "IMG26"
         EndProperty
         BeginProperty ListImage27 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":BEC8
            Key             =   "ss"
         EndProperty
         BeginProperty ListImage28 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":DD1C
            Key             =   "IMG28"
         EndProperty
         BeginProperty ListImage29 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":FB70
            Key             =   "six"
         EndProperty
         BeginProperty ListImage30 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":119C4
            Key             =   "tree"
         EndProperty
         BeginProperty ListImage31 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":13818
            Key             =   "stree"
         EndProperty
         BeginProperty ListImage32 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":1566C
            Key             =   "same"
         EndProperty
         BeginProperty ListImage33 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":174C0
            Key             =   "end"
         EndProperty
         BeginProperty ListImage34 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":17754
            Key             =   "mid"
         EndProperty
         BeginProperty ListImage35 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":179E8
            Key             =   "miss"
         EndProperty
         BeginProperty ListImage36 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":17C7C
            Key             =   "cirpoint"
         EndProperty
         BeginProperty ListImage37 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":17F10
            Key             =   "pointselect"
         EndProperty
         BeginProperty ListImage38 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":1822C
            Key             =   "selectfield"
         EndProperty
         BeginProperty ListImage39 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":18548
            Key             =   ""
         EndProperty
         BeginProperty ListImage40 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":186AC
            Key             =   ""
         EndProperty
         BeginProperty ListImage41 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":18B00
            Key             =   "all"
         EndProperty
         BeginProperty ListImage42 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":19254
            Key             =   "cls"
         EndProperty
         BeginProperty ListImage43 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "user1.frx":196A8
            Key             =   "text"
         EndProperty
      EndProperty
   End
   Begin VB.Label tishi 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Index           =   2
      Left            =   6360
      TabIndex        =   0
      Top             =   6240
      Width           =   1455
   End
   Begin VB.Label tishi 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Index           =   1
      Left            =   3480
      TabIndex        =   1
      Top             =   6240
      Width           =   1455
   End
   Begin VB.Label tishi 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Index           =   0
      Left            =   0
      TabIndex        =   4
      Top             =   6240
      Width           =   3255
   End
   Begin VB.Menu meunfile 
      Caption         =   "文件(&F)"
      Begin VB.Menu meunnewfile 
         Caption         =   "新文件   (&N)"
      End
      Begin VB.Menu meunopenfile 
         Caption         =   "打开文件 (&O)"
      End
      Begin VB.Menu meunsavefile 
         Caption         =   "保存文件 (&S)"
      End
      Begin VB.Menu meun1 
         Caption         =   "-"
      End
      Begin VB.Menu meunfiletool 
         Caption         =   "显示文件工具(&S)"
         Checked         =   -1  'True
      End
      Begin VB.Menu meun2 
         Caption         =   "-"
         Index           =   1
      End
      Begin VB.Menu meunexit 
         Caption         =   "退出     (&E)"
      End
   End
   Begin VB.Menu meunedit 
      Caption         =   "编辑(&E)"
      Begin VB.Menu meunerase 
         Caption         =   "清除(&E)"
      End
      Begin VB.Menu meunoops 
         Caption         =   "恢复(&R)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meuncut 
         Caption         =   "剪切(&T)"
      End
      Begin VB.Menu meuncopy 
         Caption         =   "复制(&C)"
      End
      Begin VB.Menu meunpase 
         Caption         =   "粘贴(&P)"
      End
      Begin VB.Menu meun15 
         Caption         =   "-"
         Index           =   1
      End
      Begin VB.Menu meunmove 
         Caption         =   "移动(&M)"
      End
      Begin VB.Menu meunroun1 
         Caption         =   "旋转(&R)"
         Begin VB.Menu meunround 
            Caption         =   "选中范围中心旋转"
         End
         Begin VB.Menu meunrounda 
            Caption         =   "绕任一点旋转"
         End
      End
      Begin VB.Menu meunroin 
         Caption         =   "翻转(&F)"
         Begin VB.Menu meunroundh 
            Caption         =   "水平翻转"
         End
         Begin VB.Menu meunroundv 
            Caption         =   "垂直翻转"
         End
      End
      Begin VB.Menu menumirror0 
         Caption         =   "镜像(&M)"
         Begin VB.Menu meunmirror1 
            Caption         =   "镜像(保留图形)"
         End
         Begin VB.Menu meunmirror 
            Caption         =   "镜像(不保留原图形)"
         End
      End
      Begin VB.Menu meunhmirror 
         Caption         =   "任选一直线两点"
         Visible         =   0   'False
      End
      Begin VB.Menu meunvmirror 
         Caption         =   "垂直镜像"
         Visible         =   0   'False
      End
      Begin VB.Menu meunarray 
         Caption         =   "阵列"
         Enabled         =   0   'False
         Begin VB.Menu meunrectanglararray 
            Caption         =   "矩形陈列(&R)"
         End
         Begin VB.Menu meunpolararray 
            Caption         =   "圆形陈列(&P)"
         End
      End
      Begin VB.Menu meun4 
         Caption         =   "-"
      End
      Begin VB.Menu meunbreak 
         Caption         =   "切断(&B)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meuntrim 
         Caption         =   "修剪(&T)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunfillet 
         Caption         =   "圆角(&F)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunchamfer 
         Caption         =   "切角(&C)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meun5 
         Caption         =   "-"
      End
      Begin VB.Menu meunedittool 
         Caption         =   "显示编辑工具(&S)"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meuntool 
      Caption         =   "制图(&T)"
      Begin VB.Menu meuncolse 
         Caption         =   "结束"
         Visible         =   0   'False
      End
      Begin VB.Menu meuncols 
         Caption         =   "封闭"
         Visible         =   0   'False
      End
      Begin VB.Menu meunredo 
         Caption         =   "取消"
         Visible         =   0   'False
      End
      Begin VB.Menu meunu 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu meunpoint 
         Caption         =   "点"
         Enabled         =   0   'False
         Begin VB.Menu meun实心点 
            Caption         =   "实心点"
         End
         Begin VB.Menu meuncrosspoint 
            Caption         =   "十字点"
         End
         Begin VB.Menu meuncirlepoint 
            Caption         =   "圆点"
         End
         Begin VB.Menu meun交叉点 
            Caption         =   "交叉点"
         End
      End
      Begin VB.Menu meunline0 
         Caption         =   "直线......     "
         Begin VB.Menu meunline 
            Caption         =   "直线"
         End
         Begin VB.Menu meun连画线 
            Caption         =   "连画线"
         End
      End
      Begin VB.Menu meun三角 
         Caption         =   "三角形"
         Begin VB.Menu meun三角形 
            Caption         =   "三角形"
         End
         Begin VB.Menu meun正三角形 
            Caption         =   "正三角形"
         End
         Begin VB.Menu meun等三边形 
            Caption         =   "等三边形"
            Visible         =   0   'False
         End
      End
      Begin VB.Menu meunbox 
         Caption         =   "矩形"
      End
      Begin VB.Menu meun正多边 
         Caption         =   "正多边形"
         Begin VB.Menu meun正方形 
            Caption         =   "正方形"
         End
         Begin VB.Menu meun正五边形 
            Caption         =   "正五边形"
            Visible         =   0   'False
         End
         Begin VB.Menu meun正六边形 
            Caption         =   "正六边形"
         End
         Begin VB.Menu meun正多边形 
            Caption         =   "正多边形"
            Enabled         =   0   'False
         End
      End
      Begin VB.Menu meuncircle0 
         Caption         =   "圆  ......"
         Index           =   0
         Begin VB.Menu meuncircle 
            Caption         =   "圆"
         End
         Begin VB.Menu meun椭圆 
            Caption         =   "椭圆"
         End
         Begin VB.Menu meunarc 
            Caption         =   "圆弧"
         End
         Begin VB.Menu meun扇形 
            Caption         =   "扇形"
         End
      End
      Begin VB.Menu meun曲线 
         Caption         =   "曲线"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunpath 
         Caption         =   "迹线"
         Enabled         =   0   'False
      End
      Begin VB.Menu meuntext 
         Caption         =   "文本"
      End
      Begin VB.Menu meun3 
         Caption         =   "-"
         Index           =   1
      End
      Begin VB.Menu meundisptool 
         Caption         =   "显示制图工具(&S)"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunoselect 
      Caption         =   "选取(&S)"
      Begin VB.Menu meunobject0 
         Caption         =   "选取目标"
         Begin VB.Menu meunselectobject 
            Caption         =   "选取目标(点选取)"
         End
         Begin VB.Menu menuselectobject 
            Caption         =   "选取目标(区域选取)"
         End
      End
      Begin VB.Menu meun14 
         Caption         =   "选点"
      End
      Begin VB.Menu meunselectline 
         Caption         =   "选直线"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselectrectangle 
         Caption         =   "选矩形"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselect正方形 
         Caption         =   "选正方形"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselcet三角形 
         Caption         =   "三角形"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselectcircle 
         Caption         =   "选取圆"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselectarc 
         Caption         =   "选圆弧和扇形"
      End
      Begin VB.Menu meun32 
         Caption         =   "-"
      End
      Begin VB.Menu meunallselect 
         Caption         =   "全选"
      End
      Begin VB.Menu meun17 
         Caption         =   "-"
         Index           =   0
      End
      Begin VB.Menu meunexitselect 
         Caption         =   "退出选取"
      End
      Begin VB.Menu meun20 
         Caption         =   "-"
      End
      Begin VB.Menu meunselecttool 
         Caption         =   "显示选取工具(&S)"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunobjectsnpae 
      Caption         =   "目标捕捉(&N)"
      Begin VB.Menu meunselectsinglepoint 
         Caption         =   "选取单独点"
      End
      Begin VB.Menu meunselectendpoint 
         Caption         =   "选取线段或圆弧的端点"
      End
      Begin VB.Menu meunselectmidpoint 
         Caption         =   "选取线段或圆弧的中点"
      End
      Begin VB.Menu meunselectcirclepoint 
         Caption         =   "选取圆心"
      End
      Begin VB.Menu meunsnapemiss 
         Caption         =   "交点"
      End
      Begin VB.Menu meunexitsnape 
         Caption         =   "退出捕捉"
         Checked         =   -1  'True
      End
      Begin VB.Menu mwunuu 
         Caption         =   "-"
      End
      Begin VB.Menu meunshowsnapetool 
         Caption         =   "显示捕捉工具"
      End
   End
   Begin VB.Menu meunview 
      Caption         =   "视图(&V)"
      Begin VB.Menu meunmouse形状 
         Caption         =   "鼠标形状"
         Begin VB.Menu meunmousecross 
            Caption         =   "十字光标"
         End
         Begin VB.Menu meunmousebigcross 
            Caption         =   "大十字光标"
         End
         Begin VB.Menu meunmouse箭形 
            Caption         =   "箭形光标"
         End
      End
      Begin VB.Menu meun_ 
         Caption         =   "-"
      End
      Begin VB.Menu meunattrib 
         Caption         =   "属性"
         Enabled         =   0   'False
         Begin VB.Menu meunlayer 
            Caption         =   "图层"
         End
         Begin VB.Menu meuncolor 
            Caption         =   "颜色"
         End
      End
      Begin VB.Menu meun21 
         Caption         =   "-"
         Index           =   0
      End
      Begin VB.Menu meunzoomout 
         Caption         =   "放大       (&O)"
      End
      Begin VB.Menu meunzoomin 
         Caption         =   "缩小       (&I)"
      End
      Begin VB.Menu meunselectzoom 
         Caption         =   "选择缩放   (&S)"
      End
      Begin VB.Menu meun恢复原尺寸 
         Caption         =   "恢复原尺寸 (&R)"
      End
      Begin VB.Menu meun16 
         Caption         =   "-"
      End
      Begin VB.Menu meungirl 
         Caption         =   "显示栅格"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunoption1 
      Caption         =   "选项(O)"
      Begin VB.Menu meunoption 
         Caption         =   "选项(&O)"
      End
      Begin VB.Menu meun12 
         Caption         =   "-"
      End
      Begin VB.Menu meuntishi 
         Caption         =   "显示提示栏"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunwindows 
      Caption         =   "窗口(&W)"
   End
   Begin VB.Menu meunhelp 
      Caption         =   "帮助(&H)"
      Begin VB.Menu meunabout 
         Caption         =   "关于"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'主窗口
Option Explicit

'Private Declare Function ShowCursor Lib "user32" (ByVal bShow As Long) As Long
Dim vartoolbar As Toolbar

Public Sub Savecommvar()  '保存当前参数
    user.Savemode = Form1.cad.DrawMode '保存当前模式
    user.Savecommvar.width = Form1.cad.DrawWidth
    user.Savecommvar.style = Form1.cad.DrawStyle
End Sub

Public Sub redocommvar()  '恢复当前参数
    Form1.cad.DrawMode = user.Savemode   '恢复当前模式
    Form1.cad.DrawWidth = user.Savecommvar.width
    Form1.cad.DrawStyle = user.Savecommvar.style
End Sub


Private Sub deskHScroll_Change()
        cad.left = -deskHScroll.Value
End Sub

Private Sub deskvscroll_Change()
        cad.top = -deskvscroll.Value
End Sub

Private Sub Form_Load()
On Error Resume Next
        Set vartoolbar = Toolline
        vartoolbar.Tag = "Line"
        
End Sub

Private Sub Form_Unload(Cancel As Integer)
            meunexit_Click
End Sub

Private Sub meunabout_Click()
        helpabout.Show 1, Form1
End Sub

Private Sub meuncopy_Click()
        user.CurrentOperist = "copy"
        edit.Mecopy
End Sub

Private Sub meunpase_Click()
        edit.Mepase
End Sub


Private Sub meuncrosspoint_Click()
        user.CurrentOperist = "crosspoint"
End Sub

Private Sub meunedittool_Click()
        If meunedittool.Checked Then
           meunedittool.Checked = False
           Toolbar1.Visible = False
           If meundisptool.Checked = False Then
              desk.top = desk.top - Toolbar1.height
              desk.height = desk.height + Toolbar1.height
              user.Scrollbar Abs(cad.left), Abs(cad.top)
           End If
        Else
           meunedittool.Checked = True
           Toolbar1.Visible = True
           If meundisptool.Checked = False Then
              desk.top = desk.top + Toolbar1.height
              desk.height = desk.height - Toolbar1.height
              user.Scrollbar Abs(cad.left), Abs(cad.top)
           End If
        End If
End Sub

Private Sub meunerase_Click()
        user.ClearObject
End Sub

'制图菜单
Private Sub meuncolse_Click()   '结束
        '作图结束,用于连画线,或未画完的圆,圆弧,扇形,椭圆
        user.drawflag = 1
        draw.redraw
End Sub

Private Sub meuncols_Click()   '封闭
Dim i
        '当当前操作为连画线时,存储连画线,并使连画线成为封闭的连线
        For i = UBound(user.LineType) To 1 Step -1
             If i - 1 < 1 Or user.LineType(i).x0 <> user.LineType(i - 1).X Or user.LineType(i).y0 <> user.LineType(i - 1).Y Then
                ReDim Preserve user.LineType(UBound(user.LineType) + 1)
                user.Savepraam
                user.LineType(UBound(user.LineType)).X = user.LineType(i).x0
                user.LineType(UBound(user.LineType)).Y = user.LineType(i).y0
                Exit For
             End If
        Next i
        user.drawflag = 1
        draw.redraw
End Sub

Private Sub meunredo_Click()  '取消
        '取消当前的制图操作
        Select Case user.CurrentOperist
               Case "Line"
                    ReDim Preserve user.LineType(UBound(user.LineType) - 1)
               Case "连画线"
               
               Case "Rectangle"
                     ReDim Preserve user.RectangleType(UBound(user.RectangleType) - 1)
               Case "三角形", "正三角形"
                    ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) - 1)
               Case "正方形"
                    ReDim Preserve user.SameRectangleType(UBound(user.SameRectangleType) - 1)
               Case "正六边形"
                     ReDim Preserve user.SixegdeType(UBound(user.SixegdeType) - 1)
               Case "circle"
                     ReDim Preserve user.CircleType(UBound(user.CircleType) - 1)
               Case "arc", "扇形"
                     ReDim Preserve user.ArcType(UBound(user.ArcType) - 1)
               Case "Ellipse"
                    ReDim Preserve user.EllipseType(UBound(user.EllipseType) - 1)
        End Select
        draw.redraw
End Sub

Private Sub meunline_Click()
        user.CurrentOperist = "Line"
End Sub

Private Sub meun连画线_Click()
        user.CurrentOperist = "连画线"
        user.drawflag = 1
End Sub

Private Sub meun三角形_Click()
        user.CurrentOperist = "三角形"
        user.drawflag = 1
End Sub

Private Sub meun正三角形_Click()
        user.CurrentOperist = "正三角形"
End Sub

Private Sub meun等三边形_Click()
        user.CurrentOperist = "等边三角形"
        user.drawflag = 1
End Sub

Private Sub meunbox_Click()     '矩形
     user.CurrentOperist = "Rectangle"
End Sub

Private Sub meun正方形_Click()
            user.CurrentOperist = "正方形"
            user.drawflag = 1
End Sub

Private Sub meun正六边形_Click()
       user.CurrentOperist = "正六边形"
       user.drawflag = 1
End Sub

Private Sub meuncircle_Click()  '圆
        user.CurrentOperist = "circle"
End Sub

Private Sub meunarc_Click()  '圆弧
           user.CurrentOperist = "Arc"
           user.drawflag = 1
End Sub

Private Sub meun扇形_Click()
        user.CurrentOperist = "扇形"
        user.drawflag = 1
End Sub

Private Sub meun椭圆_Click()
            user.CurrentOperist = "Ellipse"
            user.drawflag = 1
End Sub

Private Sub meun实心点_Click()
        user.CurrentOperist = "实心点"
End Sub

Private Sub meuntext_Click()
        user.CurrentOperist = "text"
End Sub

Private Sub meundisptool_Click()   '显示制图工具
        If meundisptool.Checked = True Then
           meundisptool.Checked = False
           Toolline.Visible = False
           Toolcircle.Visible = False
           Toolrectangle.Visible = False
           If meunedittool.Checked = False Then
              desk.height = desk.height + Toolbar1.height
              desk.top = desk.top - Toolbar1.height
              user.Scrollbar Abs(cad.left), Abs(cad.top)
           End If
        Else
           meundisptool.Checked = True
           Toolline.Visible = True
           Toolcircle.Visible = True
           Toolrectangle.Visible = True
           If meunedittool.Checked = False Then
              desk.top = desk.top + Toolbar1.height
              desk.height = desk.height - Toolbar1.height
              user.Scrollbar Abs(cad.left), Abs(cad.top)
           End If
        End If
End Sub

'目标选取
Private Sub meunselectline_Click()
        user.CurrentOperist = "selectline"
End Sub

Private Sub meunselectobject_Click()
        user.CurrentOperist = "selectobject"
End Sub

Private Sub menuselectobject_Click()
        user.CurrentOperist = "fieldselectobject"
End Sub

Private Sub meunallselect_Click()    '全选
        user.LinePoint = 1
        user.ArcPoint = 1
        user.CirclePoint = 1
        user.ThreeanglePoint = 1
        user.RectanglePoint = 1
        user.SixegdePoint = 1
        user.RectanglefourPoint = 1
        user.SameRectanglePoint = 1
        '加点的指针
        
        '显示选取的目标
        With user.SnapefieldType
             .x1 = -1
             .y1 = -1
             .x2 = -1
             .y2 = -1
        End With
        snape.showselectobject Form1.cad, True
End Sub

Private Sub meunexitselect_Click()   '退出选取
        If user.CurrentOperist = "selectobject" Or user.CurrentOperist = "fieldselectobject" Then
           user.CurrentOperist = "null"
        End If
        With user.SnapefieldType
             .x1 = -1
             .x2 = -1
             .y1 = -1
             .y2 = -1
        End With
        draw.redraw
End Sub

'显示选取工具栏
Private Sub meunselecttool_Click()
        If meunselecttool.Checked Then
           meunselecttool.Checked = False
           Toolbar2.Visible = False
           If meunshowsnapetool.Checked = False Then '显示目标选取与目标捕捉有关
                  '修改桌面
                   desk.left = desk.left - snapetool.width
                   desk.width = desk.width + snapetool.width
                   '修改水平滚动条
                   user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
           End If
        Else
           meunselecttool.Checked = True
           Toolbar2.Visible = True
           If meunshowsnapetool.Checked = False Then '显示目标选取与目标捕捉有关
                  '修改桌面
                   desk.left = desk.left + snapetool.width
                   desk.width = desk.width - snapetool.width
                   '修改水平滚动条
                   user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
           End If
        End If
        
End Sub

'目标捕捉菜单
Private Sub meunselectendpoint_Click()    '捕捉线段或圆弧的端点
            '清除退出目标捕捉复选框
            meunexitsnape.Checked = False
        If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "selectendpoint", vbBinaryCompare) = 0 Then
           user.SnapeOperist = user.SnapeOperist + "selectendpoint"
           meunselectendpoint.Checked = True   '显示复选框
           user.Mousesnape = "snapecirle"  '捕捉时鼠标的形状,影响过程snapemouse
          '按下工具栏上的按扭
          '按下捕捉端点按扭
          snapetool.Buttons.Item("lineendpoint").Value = tbrPressed
        End If
End Sub

Private Sub meunselectmidpoint_Click()   '捕捉线段或圆弧的中点
            '清除退出目标捕捉复选框
            meunexitsnape.Checked = False
If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "snapelinemid", vbBinaryCompare) = 0 Then
        user.SnapeOperist = user.SnapeOperist + "snapelinemid" '捕捉操作
        meunselectmidpoint.Checked = True    '显示复选框
        user.Mousesnape = "snapecirle"  '捕捉时鼠标的形状,影响过程snapemouse
        '按下工具栏上的按扭
        snapetool.Buttons.Item("snapelinemid").Value = tbrPressed
End If
End Sub

Private Sub meunselectcirclepoint_Click()   '捕捉圆心
            '清除退出目标捕捉复选框
            meunexitsnape.Checked = False
If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "snapecirclepoint", vbBinaryCompare) = 0 Then
         meunselectcirclepoint.Checked = True '显示复选框
         user.SnapeOperist = user.SnapeOperist + "snapecirclepoint"
         user.Mousesnape = "snapecirle"  '捕捉时鼠标的形状,影响过程snapemouse
          '按下工具栏上的按扭
        snapetool.Buttons.Item("snapecirclepoint").Value = tbrPressed
End If
End Sub

Private Sub meunsnapemiss_Click()  '捕捉交点
            '清除退出目标捕捉复选框
            meunexitsnape.Checked = False
If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "snapemisspoint", vbBinaryCompare) = 0 Then
         meunsnapemiss.Checked = True
         '此过程没写完
         user.Mousesnape = "snapecirle"  '捕捉时鼠标的形状,影响过程snapemouse
         '捕捉操作
         user.SnapeOperist = user.SnapeOperist + "snapemisspoint"
        '按下工具栏上的按扭
        snapetool.Buttons.Item("snapemisspoint").Value = tbrPressed
End If
End Sub

Private Sub meunexitsnape_Click()  '退出捕捉状态
Dim i
            '清除所有复选框
            meunselectendpoint.Checked = False  '端点
            meunselectmidpoint.Checked = False '中点
            meunselectcirclepoint.Checked = False '圆心
            meunsnapemiss.Checked = False '交点
            '显示复选框
            meunexitsnape.Checked = True
            user.SnapeOperist = "null"
            user.Mousesnape = "null"  '捕捉时鼠标的形状,影响过程snapemouse
            SnapeMouseFlag = 0 '详见user中此值声明
            '弹起工具栏上的按扭
            For i = 1 To snapetool.Buttons.Count   '弹起所有按扭
                snapetool.Buttons(i).Value = tbrUnpressed
            Next i
        
End Sub

Public Sub meunshowsnapetool_Click()   '显示捕捉工具栏
       If meunshowsnapetool.Checked Then
               meunshowsnapetool.Checked = False
               snapetool.Visible = False
               If meunselecttool.Checked = False Then '显示目标选取与目标捕捉有关
                  '修改桌面
                   desk.left = desk.left - snapetool.width
                   desk.width = desk.width + snapetool.width
                   '修改水平滚动条
                   user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
               End If
       Else
               meunshowsnapetool.Checked = True
               '显示工具
               snapetool.Visible = True
               If meunselecttool.Checked = False Then '显示目标选取与目标捕捉有关
                  '修改桌面
                  desk.left = desk.left + snapetool.width
                  desk.width = desk.width - snapetool.width
                  '修改水平滚动条
                  user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
               End If
               
       End If
End Sub

'视图菜单
'鼠标形状菜单
Private Sub meunmousecross_Click()   '十字光标
user.Usermouse形状.Checked = False
cad.MousePointer = MousePointerConstants.vbCrosshair
Set user.Usermouse形状 = meunmousecross
meunmousecross.Checked = True
End Sub

Private Sub meunmousebigcross_Click()    '大十字光标
'Dim x
'x = ShowCursor(False)
user.Usermouse形状.Checked = False
'cad.MousePointer = MousePointerConstants.vbCrosshair
cad.MousePointer = VBRUN.vbUseDefaultCursor
Set user.Usermouse形状 = meunmousebigcross
meunmousebigcross.Checked = True
End Sub

Private Sub meunmouse箭形_Click()
user.Usermouse形状.Checked = False
cad.MousePointer = MousePointerConstants.vbArrow
Set user.Usermouse形状 = meunmouse箭形
meunmouse箭形.Checked = True
End Sub

Private Sub meunzoomout_Click()  '放大
On Error Resume Next
        user.SnapeField = user.SnapeField / 2 '放大捕捉区域
        cad.top = cad.top - cad.height / 2
        cad.left = cad.left - cad.width / 2
        cad.width = cad.width * 2
        cad.height = cad.height * 2
        cad.ScaleHeight = cad.ScaleHeight / 2
        cad.scalewidth = cad.scalewidth / 2
        user.Scrollbar Abs(cad.left), Abs(cad.top)  '滚动条
        draw.redraw
End Sub

Private Sub meunzoomin_Click()   '缩小
On Error Resume Next
        user.SnapeField = user.SnapeField * 2 '缩小捕捉区域
        cad.top = cad.top + cad.height / 4
        cad.left = cad.left + cad.width / 4
        cad.width = cad.width / 2
        cad.height = cad.height / 2
        cad.ScaleHeight = cad.ScaleHeight * 2
        cad.scalewidth = cad.scalewidth * 2
        user.Scrollbar Abs(cad.left), Abs(cad.top)  '滚动条
        draw.redraw
End Sub

Private Sub meunselectzoom_Click()
        user.CurrentOperist = "selectzoom"
End Sub

Private Sub meun恢复原尺寸_Click()
        cad.Move user.paper.left, user.paper.top, user.paper.width, user.paper.height
        cad.ScaleHeight = user.paper.scaleheigt
        cad.scalewidth = user.paper.scalewidth
        draw.redraw
        'user.scrollbar (Form1.cad.width - Form1.desk.scalewidth) / 2, (Form1.cad.Height - Form1.desk.ScaleHeight) / 2
End Sub

Private Sub meungirl_Click()  '显示栅格
            If meungirl.Checked = True Then
               meungirl.Checked = False
            Else
               meungirl.Checked = True
            End If
End Sub

'选项菜单
Private Sub meunoption_Click()
   frmOptions.Show 1, Form1
End Sub

Private Sub meuntishi_Click()   '显示状态栏
Dim i
        If meuntishi.Checked = True Then
           'dispbar.Visible = False
           meuntishi.Checked = False
           For i = 0 To tishi.Count - 1
               tishi.Item(i).Visible = False
           Next i
           tishitext1.Visible = False
           tishitext2.Visible = False
           
        Else
           'dispbar.Visible = True
           meuntishi.Checked = True
           For i = 0 To tishi.Count - 1
               tishi.Item(i).Visible = False
           Next i
           tishitext1.Visible = True
           tishitext2.Visible = True
        End If
        
End Sub

Private Sub meunlayer_Click()
frmOptions.Show 1, Form1
End Sub

Private Sub meunmirror_Click()
        user.CurrentOperist = "mirror"
        user.drawflag = 1
End Sub

Private Sub meunmirror1_Click()
        user.CurrentOperist = "mirrorsave"
        user.drawflag = 1
End Sub

Private Sub meunmove_Click()
        user.CurrentOperist = "move"
End Sub

'文件菜单
Private Sub meunnewfile_Click()
On Error Resume Next
        If user.CurrentOperistFlag Then   '如果以前做过操作,则进行保存
           meunsavefile_Click
        End If
        user.Showselectpaperform = True    '标志是否从新文件处调用,还是从程序起动时调用
        user.Initiale     '清除以前的数据
        selectpaper.Show 1, Form1
        user.Showselectpaperform = False
        user.CurrentOperistFlag = False     '新文件未进行任何操作
End Sub

Private Sub meunopenfile_Click()
      If user.CurrentOperistFlag Then
         meunsavefile_Click
      End If
          user.OpenFile
          
          Load frmOptions
          With user.paper
               frmOptions.pheight.text = desk.ScaleX(.height, 3, .until)
               frmOptions.pwidth.text = desk.ScaleY(.width, 3, .until)
          End With
          cad.scalemode = user.paper.until
          frmOptions.cmdOK_Click
'        draw.redraw
End Sub

Private Sub meunsavefile_Click()
     user.SaveFile
     user.CurrentOperistFlag = False  '标志是否进行了操作
End Sub

Private Sub meunexit_Click()
Dim exi
If user.CurrentOperistFlag Then
    exi = MsgBox("你要保存文件吗?", vbQuestion + vbYesNoCancel)
    If exi = vbYes Then
       user.SaveFile
    Else
       If exi = 2 Then   '按下取消健时
          Exit Sub
       End If
    End If
End If
End
End Sub

Private Sub meunround_Click()
        user.CurrentOperist = "round"
End Sub

Private Sub meunrounda_Click()
        user.CurrentOperist = "rounda"
End Sub

Private Sub meunroundh_Click()
        edit.Roundh Form1.cad, user.Snapecolor
End Sub

Private Sub meunroundv_Click()
        edit.Roundv Form1.cad, user.Snapecolor
End Sub

Private Sub meunselcet三角形_Click()
        user.CurrentOperist = "selectthreeangle"
End Sub

Private Sub meunselectarc_Click()
        user.CurrentOperist = "selectarc"
End Sub

Private Sub meunselectcircle_Click()
        user.CurrentOperist = "selectcircle"
End Sub

Private Sub meunselectrectangle_Click()
        user.CurrentOperist = "selectrectangle"
End Sub

'捕捉工栏
Private Sub snapetool_ButtonClick(ByVal Button As MSComctlLib.Button)
          Select Case Button.Key
                 Case "lineendpoint"   '捕捉端点
                       meunselectendpoint_Click
                 Case "snapelinemid"  '捕捉中点
                       meunselectmidpoint_Click
                 Case "snapecirclepoint"  '捕捉圆心
                       meunselectcirclepoint_Click
                 Case "snapemisspoint"   '捕捉交点
                       meunsnapemiss_Click
                 Case "exitsnape"    '退出捕捉
                       meunexitsnape_Click
                 
          End Select
            
End Sub

Private Sub Toolbar2_ButtonClick(ByVal Button As MSComctlLib.Button)
        Select Case Button.Key
               Case "selectobject"
                    meunselectobject_Click
               Case "selectobjectfield"
                    menuselectobject_Click
               Case "allselect"
                    meunallselect_Click
               Case "exitselect"
                    meunexitselect_Click
        End Select
End Sub

Private Sub Toolline_ButtonDropDown(ByVal Button As MSComctlLib.Button)
 Dim i
            '设置工具按钮
            vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
            Set vartoolbar = Toolline      '赋值
            vartoolbar.Tag = Button.Key
            '显示所有按钮并隐藏下拉按钮
            For i = 1 To Toolline.Buttons.Count
                Toolline.Buttons.Item(i).Visible = True
                Button.Value = tbrUnpressed
            Next i
            '隐藏下拉按钮并按下按钮
            Button.style = tbrDefault
            Button.Value = tbrPressed
End Sub

Private Sub Toolline_ButtonClick(ByVal Button As MSComctlLib.Button)
 Dim i
        '设置工具按钮
        vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
        Set vartoolbar = Toolline         '赋值
        vartoolbar.Tag = Button.Key
        '隐藏所有按钮
        For i = 1 To Toolline.Buttons.Count
                Toolline.Buttons.Item(i).Visible = False
        Next i
        '显示下拉按钮并按下按钮
        Button.Value = tbrPressed
        Button.style = tbrDropdown
        Button.Visible = True
        '给当前操作赋值
        Select Case Button.Key
               Case "Line"
                    meunline_Click
               Case "连画线"
                    meun连画线_Click
               Case "Line Style"
                    meunoption_Click
        End Select
End Sub

Private Sub Toolrectangle_ButtonDropDown(ByVal Button As MSComctlLib.Button)
 Dim i
            '设置工具按钮
            vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
            Set vartoolbar = Toolrectangle      '赋值 改
            vartoolbar.Tag = Button.Key
            '显示所有按钮并隐藏下拉按钮
            For i = 1 To Toolrectangle.Buttons.Count    '改
                Toolrectangle.Buttons.Item(i).Visible = True  '改
                Button.Value = tbrUnpressed
            Next i
            '隐藏下拉按钮并按下按钮
            Button.style = tbrCheck
            Button.Value = tbrPressed
End Sub

Private Sub Toolrectangle_ButtonClick(ByVal Button As MSComctlLib.Button)
Dim i
       '隐藏所有按钮
        For i = 1 To Toolrectangle.Buttons.Count
                Toolrectangle.Buttons.Item(i).Visible = False
        Next i
        '设置工具按钮
        vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
        Set vartoolbar = Toolrectangle     '赋值
        vartoolbar.Tag = Button.Key
        '显示下拉按钮并按下按钮
        Button.Visible = True
        Button.style = tbrDropdown
        Button.Value = tbrPressed
        '给当前操作赋值
        Select Case Button.Key
               Case "rectangle"
                     meunbox_Click
               Case "stree"
                    meun正三角形_Click
               Case "tree"
                    meun三角形_Click
               Case "six"
                    meun正六边形_Click
               Case "zhen"
                    meun正方形_Click
        End Select
End Sub

Private Sub Toolcircle_ButtonClick(ByVal Button As MSComctlLib.Button)
Dim i
       '设置工具按钮
        vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
        Set vartoolbar = Toolcircle     '赋值
        vartoolbar.Tag = Button.Key
        '隐藏所有按钮
        For i = 1 To Toolcircle.Buttons.Count
                Toolcircle.Buttons.Item(i).Visible = False
        Next i
        '显示下拉按钮并按下按钮
        Button.Visible = True
        Button.style = tbrDropdown
        Button.Value = tbrPressed
        '给当前操作赋值
        Select Case Button.Key
               Case "circle"
                    meuncircle_Click
               Case "Ellipse"
                    meun椭圆_Click
               Case "Arc"
                    meunarc_Click
               Case "shan"
                    meun扇形_Click
        End Select
                    
End Sub

Private Sub Toolcircle_ButtonDropDown(ByVal Button As MSComctlLib.Button)
 Dim i
            '设置工具按扭
            vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
            Set vartoolbar = Toolcircle     '赋值
            vartoolbar.Tag = Button.Key
            '显示所有按钮并隐藏下拉按钮
            For i = 1 To Toolcircle.Buttons.Count
                Toolcircle.Buttons.Item(i).Visible = True
                Button.Value = tbrUnpressed
            Next i
            '工具按钮按下
            Button.style = tbrCheck
            Button.Value = tbrPressed
End Sub


Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)
    On Error Resume Next
    Select Case Button.Key
        Case "New"
            'ToDo: Add 'New' button code.
            'MsgBox "Add 'New' button code."
            meunnewfile_Click
        Case "Open"
             meunopenfile_Click
        Case "Save"
             meunsavefile_Click
        Case "Print"
            'ToDo: Add 'Print' button code.
            MsgBox "Add 'Print' button code."
        Case "Undo"
            'meunerase_Click
            cad.Cls
        Case "Redo"
            'meunoops_Click
            cad.Cls
            draw.redraw
        Case "Copy"
             meuncopy_Click
        Case "Cut"
            'ToDo: Add 'Cut' button code.
            MsgBox "Add 'Cut' button code."
        Case "Paste"
            meunpase_Click
        Case "Delete"
             meunerase_Click
        Case "Help"
            'ToDo: Add 'Help' button code.
            MsgBox "Add 'Help' button code."
        Case "text"
             meuntext_Click
    End Select
End Sub

Private Sub tishitext1_KeyUp(KeyCode As Integer, Shift As Integer)
On Error Resume Next
Dim X As Single, Y As Single
        Select Case KeyCode
               Case 13
                    X = tishitext1.text
                    Y = tishitext2.text
                    '从提示栏中直接输入座标数据
                    user.KeyInputData X, Y
                    
               Case vbKeyUp, vbKeyDown
                    tishitext2.SetFocus
        End Select
End Sub

Private Sub tishitext2_keyup(KeyCode As Integer, Shift As Integer)
On Error Resume Next
Dim X As Single, Y As Single
        Select Case KeyCode
               Case 13
                    X = tishitext1.text
                    Y = tishitext2.text
                    '从提示栏中直接输入座标数据
                    user.KeyInputData X, Y
                    
               Case vbKeyUp, vbKeyDown
                    tishitext1.SetFocus
        End Select
End Sub

Public Sub cad_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim mode
'当右击鼠标时,显示菜单
If Button = VBRUN.vbRightButton Then
   user.RightChickMenu X, Y
End If
 
'当shift键按下时
     If Shift = VBRUN.ShiftConstants.vbShiftMask Then
        If Abs(X - user.Mouseleftdownx) < Abs(Y - user.mouseleftdowny) Then
           X = user.Mouseleftdownx
        Else
           Y = user.mouseleftdowny
        End If
     End If

'判断当鼠标是否移到视图边界
'If Button = vbLeftButton Then
'   If X < user.deskx1 Or X > user.deskx2 Or Y < user.desky1 Or Y > user.desky2 Then
'      user.movepaper X, Y, Form1.cad         '自动移动图纸
'   End If
'End If

'user.tishiinitale (button)
'防止画圆弧的第三步按下鼠标左键不放,拉出直线
If (user.CurrentOperist = "Arc" Or user.CurrentOperist = "扇形") And user.drawflag = 2 Then
   user.drawflag = 4
End If

 Dim snapepoint As snapepoint '详见user中的声明部分
 With snapepoint
      .r = -1
      .X = X
      .Y = Y
      '下面的顺序不能变化
      '线段或圆弧的中点
      If InStrB(1, user.SnapeOperist, "selectendpoint", vbBinaryCompare) <> 0 Then
         snape.snapeendpoint X, Y, Form1.cad, snapepoint
      End If

      '交点
      If InStrB(1, user.SnapeOperist, "snapemisspoint", vbBinaryCompare) <> 0 Then
             snape.snapemisspoint X, Y, Form1.cad, snapepoint
      End If
       '线段或圆弧的中点
      If InStrB(1, user.SnapeOperist, "snapelinemid", vbBinaryCompare) <> 0 Then
             snape.snapelinemidpoint X, Y, Form1.cad, snapepoint
      End If
      '圆心
      If InStrB(1, user.SnapeOperist, "snapecirclepoint", vbBinaryCompare) <> 0 Then
            snape.snapecirclepoint X, Y, Form1.cad, snapepoint
      End If
      
     X = .X
     Y = .Y
 
 End With
     
     Select Case user.CurrentOperist
            Case "连画线"
                 Select Case user.drawflag
                        Case 1    '当第一点时所取的座标,其他点不取值
                             If Button = VBRUN.vbLeftButton Then
                                user.Mousepausex = X
                                user.Mouseleftdownx = X
                                user.mousepausey = Y
                                user.mouseleftdowny = Y
                             End If
                  End Select
            Case "ellispe"
                  Select Case user.drawflag
                         Case 1
                              If Button = VBRUN.vbLeftButton Then
                                 user.Mousepausex = X
                                 user.Mouseleftdownx = X
                                 user.mousepausey = Y
                                 user.mouseleftdowny = Y
                              End If
                  End Select
           ' Case "selectobject"         '清除所有以前选定的目标
            '      snape.selectobjectclare x, y, Form1.cad
            Case "round"      '绕目标中心旋转
                   '为参考直线赋值
                   user.Mouseleftdownx = (user.SnapefieldType.x1 + user.SnapefieldType.x2) / 2
                   user.mouseleftdowny = (user.SnapefieldType.y1 + user.SnapefieldType.y2) / 2
                   user.Mousepausex = user.Mouseleftdownx
                   user.mousepausey = user.mouseleftdowny
            Case Else
                 If Button = VBRUN.vbLeftButton Then
                    user.Mousepausex = X
                    user.Mouseleftdownx = X
                    user.mousepausey = Y
                    user.mouseleftdowny = Y
                 End If
    End Select
    
'突出显示目标捕捉到的点
    With snapepoint
    If .r >= 0 Then
       draw.showpoint .X, .Y, Form1.cad, user.Snapecolor
    End If
    End With
'显示大十字光标
user.DispBigCross Form1.cad, X, Y
user.DispBigCross Form1.cad, X, Y
'显示捕捉光标
 user.SnapeMouse Form1.cad, X, Y
 user.SnapeMouse Form1.cad, X, Y
End Sub

Private Sub cad_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim col As ColorConstants
col = user.Pramcol
'当shift键按下时
     If Shift = VBRUN.ShiftConstants.vbShiftMask Then
        If Abs(X - user.Mouseleftdownx) < Abs(Y - user.mouseleftdowny) Then
           X = user.Mouseleftdownx
        Else
           Y = user.mouseleftdowny
        End If
     End If
     
'判断当鼠标是否移到视图边界
'If Button = vbLeftButton Then
'   If X < user.deskx1 Or X > user.deskx2 Or Y < user.desky1 Or Y > user.desky2 Then
'      user.movepaper X, Y, Form1.cad         '自动移动图纸
'   End If
'End If
     
If meuntishi.Checked = True Then
   'user.tishi x, y, Button    '提示栏
   user.TiShiInitale X, Y, Button
End If
Select Case user.CurrentOperist
        Case "Line"
             draw.singleline Button, X, Y, col, cad
        Case "连画线"
             draw.singleline Button, X, Y, col, cad
        Case "Rectangle"
            draw.rectangle cad, X, Y, col, Button
        Case "三角形"
            draw.three Form1.cad, Button, X, Y, col
        Case "正三角形"
             draw.正三角形 Form1.cad, X, Y, Button, col
        Case "等边三角形"
            draw.three Form1.cad, Button, X, Y, col
        Case "正方形"
            draw.正方形 Form1.cad, Button, X, Y, col
        Case "正六边形"
             draw.正六边形 Form1.cad, Button, X, Y, col
        Case "Line Style"
            MsgBox "Add 'Line Style' button code."
        Case "Arc"
            draw.arc Form1.cad, Button, X, Y, col
        Case "扇形"
            draw.arc Form1.cad, Button, X, Y, col
        Case "Ellipse"
            draw.ellipse Form1.cad, X, Y, Button, col
        Case "circle"
            draw.mousecircle Button, X, Y, col, Form1.cad
            
        '编辑
        Case "move"
              edit.Move X, Y, Form1.cad, Button
        Case "round"  '绕目标中心旋转
             edit.Round X, Y, Form1.cad, Button, user.Snapecolor, 0
        Case "rounda"   '绕任一点旋转
             edit.Round X, Y, Form1.cad, Button, user.Snapecolor, 0
        'Case "mirror", "mirrorsave"
        '     If user.drawflag = 1 Then     '直接用鼠标确定镜像线的两点
        '        If Button = VBRUN.vbLeftButton Then
        '           draw.singleline Button, X, Y, user.Snapecolor, Form1.cad
        '          edit.Mirror Form1.cad, X, Y, user.Snapecolor, 0
        '        End If
        '     End If
        '     If user.drawflag = 2 Then   '用捕捉目标方式确定镜像线两点
        '        draw.singleline VBRUN.vbLeftButton, X, Y, user.Snapecolor, Form1.cad
        '     End If
        Case "copy"
             edit.Move X, Y, Form1.cad, Button
        Case "selectzoom"
             draw.selectzoomrectangle Form1.cad, Button, col, X, Y
        Case "fieldselectobject"  '区域选取目标
             draw.rectangle Form1.cad, X, Y, user.Snapecolor, Button
End Select
'显示大十字光标
user.DispBigCross Form1.cad, X, Y
user.DispBigCross Form1.cad, X, Y
'显示捕捉光标
 user.SnapeMouse Form1.cad, X, Y
 user.SnapeMouse Form1.cad, X, Y
                              
End Sub

Public Sub cad_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
On Error Resume Next
Dim col As ColorConstants
Dim rad As Double, mode
Dim xx, yy, mose, x1, y1
col = user.Pramcol
mode = cad.DrawMode
'当shift键按下时
     If Shift = VBRUN.ShiftConstants.vbShiftMask Then
        If Abs(X - user.Mouseleftdownx) < Abs(Y - user.mouseleftdowny) Then
           X = user.Mouseleftdownx
        Else
           Y = user.mouseleftdowny
        End If
     End If

 '捕捉目标的同时制图
Dim snapepoint As snapepoint   '详见user中的声明部分
With snapepoint
     .r = -1
     .X = X
     .Y = Y
      '下面的顺序不能变化
      '线段或圆弧的端点
      If InStrB(1, user.SnapeOperist, "selectendpoint", vbBinaryCompare) <> 0 Then
              snape.snapeendpoint X, Y, Form1.cad, snapepoint
      End If
      '交点
      If InStrB(1, user.SnapeOperist, "snapemisspoint", vbBinaryCompare) <> 0 Then
              snape.snapemisspoint X, Y, Form1.cad, snapepoint
              snape.snapemisspoint X, Y, Form1.cad, snapepoint
              snape.snapemisspoint X, Y, Form1.cad, snapepoint
      End If
      '线段或圆弧的中点
      If InStrB(1, user.SnapeOperist, "snapelinemid", vbBinaryCompare) <> 0 Then
                 snape.snapelinemidpoint X, Y, Form1.cad, snapepoint
      End If
      '圆心
      If InStrB(1, user.SnapeOperist, "snapecirclepoint", vbBinaryCompare) <> 0 Then
              snape.snapecirclepoint X, Y, Form1.cad, snapepoint
      End If
      
  X = .X
  Y = .Y
    '突出显示目标捕捉到的点
    If .r >= 0 Then
       draw.showpoint .X, .Y, Form1.cad, user.Snapecolor
    End If
End With

Select Case user.CurrentOperist
        Case "实心点"
             ReDim Preserve user.PointType(UBound(user.PointType) + 1)
             user.PointType(UBound(user.PointType)).X = X
             user.PointType(UBound(user.PointType)).Y = Y
             user.PointType(UBound(user.PointType)).col = user.Commvar.col
             user.PointType(UBound(user.PointType)).PointType = 1
             cad.PSet (X, Y), user.Commvar.col
             user.CurrentOperistFlag = True
        Case "crosspoint"
        
        Case "Line"
             If Button = VBRUN.vbLeftButton Then
                '清除参考直线
                cad.DrawMode = 7
                cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                '显示确定的直线
                cad.DrawMode = VBRUN.vbCopyPen
                cad.Line (Mouseleftdownx, mouseleftdowny)-(X, Y), user.Commvar.col
                '存储直线参数
                user.name = "line"
                ReDim Preserve user.LineType(UBound(user.LineType) + 1)
                user.LineType(UBound(user.LineType)).X = X    '存储线段的终点
                user.LineType(UBound(user.LineType)).Y = Y
                user.Savepraam  '公共参数的存储,包括线段的起点
                'Put #200, , user.name
                'Put #200, , linetype
                End If
                user.CurrentOperistFlag = True
        Case "连画线"
             Select Case user.drawflag
                    Case 1
                         If Button = VBRUN.vbLeftButton Then
                            '清除参考直线
                            cad.DrawMode = 7
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                            '显示确定的直线
                            cad.DrawMode = VBRUN.DrawModeConstants.vbNotXorPen
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(X, Y), user.Commvar.col
                            '存储直线参数
                            user.name = "line"     '因为公共参数与line相同
                            ReDim Preserve user.LineType(UBound(user.LineType) + 1)
                            user.LineType(UBound(user.LineType)).X = X  '存储连画线的第二点
                            user.LineType(UBound(user.LineType)).Y = Y
                            user.Savepraam  '公共参数的存储,包括连画线的第一点
                         End If
                         user.drawflag = 2     '做下一步标志
                    Case 2
                         If Button = VBRUN.vbLeftButton Then
                            '清除参考直线
                            cad.DrawMode = 7
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                            '显示确定的直线
                            cad.DrawMode = VBRUN.vbCopyPen
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(X, Y), user.Commvar.col
                            '存储直线参数
                            user.name = "line"     '因为公共参数与line相同
                            ReDim Preserve user.LineType(UBound(user.LineType) + 1)
                            user.LineType(UBound(user.LineType)).X = X   '存储下一点
                            user.LineType(UBound(user.LineType)).Y = Y
                            user.Savepraam  '公共参数的存储,包括前一点
                          End If
            End Select
            '给下一直线起点赋值
            user.Mouseleftdownx = X
            user.mouseleftdowny = Y
            user.CurrentOperistFlag = True
            
        Case "Rectangle"
            'ToDo: Add 'Rectangle' button code.
            'MsgBox "Add 'Rectangle' button code."
            If Button = VBRUN.vbLeftButton Then
                '清除参考钜形
                cad.DrawMode = 7
                cad.Line (user.Mouseleftdownx, mouseleftdowny)-(Mousepausex, user.mouseleftdowny), col
                cad.Line -(user.Mousepausex, user.mousepausey), col
                cad.Line -(user.Mouseleftdownx, user.mousepausey), col
                cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
                '显示确定的直线
                cad.DrawMode = VBRUN.vbCopyPen
                cad.Line (Mouseleftdownx, mouseleftdowny)-(X, user.mouseleftdowny), user.Commvar.col
                cad.Line -(X, Y), user.Commvar.col
                cad.Line -(user.Mouseleftdownx, Y), user.Commvar.col
                cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), user.Commvar.col
                '存储矩形参数
                user.name = "rectangle"
                ReDim Preserve user.RectangleType(UBound(user.RectangleType) + 1)
                user.RectangleType(UBound(user.RectangleType)).X = X
                user.RectangleType(UBound(user.RectangleType)).Y = Y
                user.Savepraam  '公共参数的存储
            End If
            user.CurrentOperistFlag = True
        Case "Line Style"
            'ToDo: Add 'Line Style' button code.
            MsgBox "Add 'Line Style' button code."
        Case "三角形"
            Select Case user.drawflag
                   Case 1
                        user.drawflag = 2
                       '清除参考直线
                       cad.DrawMode = 7
                       cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                       '显示确定的直线
                       'cad.DrawMode = VBRUN.vbCopyPen
                       cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), user.Commvar.col
                       '把暂存点赋值为顶点,免得消除已画好的线
                       'user.mousepausex = user.mouseleftdownx
                       'user.mousepausey = user.mouseleftdowny
                       '存储三角形参数
                        user.name = "三角形"
                        ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) + 1)
                        '保存参数
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 = X   '
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 = Y
                        user.Savepraam
                   Case 2
                        user.drawflag = 1
                        cad.DrawMode = 7
                        '消除参考线
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(user.Mousepausex, user.mousepausey), col
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(user.Mousepausex, user.mousepausey), col
                        '确定三角形
                        cad.DrawMode = VBRUN.vbCopyPen
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(X, Y), user.Commvar.col
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(X, Y), user.Commvar.col
                        '保存参数
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).x3 = X
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).y3 = Y
                        draw.redraw
            End Select
            user.CurrentOperistFlag = True
        Case "正三角形"
            ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) + 1)
            '保存参数
            user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 = X
            user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 = Y
            '把座标移到第一点
            xx = X - user.Mouseleftdownx
            yy = Y - user.mouseleftdowny
            '把第二点围绕第一点逆时针转60度
            x1 = xx / 2 - yy * Sin(user.pi / 3)
            y1 = xx * Sin(user.pi / 3) + yy / 2
            '再把座标移回原点
            xx = x1 + user.Mouseleftdownx
            yy = y1 + user.mouseleftdowny
            user.ThreeAngleType(UBound(user.ThreeAngleType)).x3 = xx
            user.ThreeAngleType(UBound(user.ThreeAngleType)).y3 = yy
            user.name = "三角形"
            user.Savepraam   '保存公共参数
            user.CurrentOperistFlag = True
        Case "等边三角形"
             Select Case user.drawflag
                    Case 1
                        user.drawflag = 2
                       '清除参考直线
                       cad.DrawMode = 7
                       cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                       '显示确定的直线
                       cad.DrawMode = VBRUN.vbCopyPen
                       cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), user.Commvar.col
                       '把暂存点赋值为顶点,免得消除已画好的线
                       user.Mousepausex = user.Mouseleftdownx
                       user.mousepausey = user.mouseleftdowny
                       '存储三角形参数
                        user.name = "三角形"
                        ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) + 1)
                        '保存参数
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 = X
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 = Y
                        user.Savepraam
                    Case 2
                        user.drawflag = 1
                        
             End Select
             user.CurrentOperistFlag = True
        Case "正方形"
            user.drawflag = 2
            draw.正方形 Form1.cad, Button, X, Y, col
            user.name = "正方形"
            ReDim Preserve user.SameRectangleType(UBound(user.SameRectangleType) + 1)
            user.SameRectangleType(UBound(user.SameRectangleType)).X = X
            user.SameRectangleType(UBound(user.SameRectangleType)).Y = Y
            user.Savepraam
            user.CurrentOperistFlag = True
        Case "正六边形"
            user.drawflag = 2
            draw.正六边形 Form1.cad, Button, X, Y, col
            user.drawflag = 1
            user.name = "正六边形"
            ReDim Preserve user.SixegdeType(UBound(user.SixegdeType) + 1)
            '保存参数
            user.SixegdeType(UBound(user.SixegdeType)).X = X
            user.SixegdeType(UBound(user.SixegdeType)).Y = Y
            user.Savepraam
            user.CurrentOperistFlag = True
        Case "Arc"
            Select Case user.drawflag
                   Case 1
                        user.drawflag = 2
                        ReDim Preserve user.ArcType(UBound(user.ArcType) + 1)
                        '确定圆半径
                        rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                                           (mouseleftdowny - Y) ^ 2)
                        '存储圆弧的参数
                        user.name = "arc"
                        user.ArcType(UBound(user.ArcType)).r = rad
                        user.Savepraam  '公共参数的存储
                        cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
                        user.Mousepausex = X
                        user.mousepausey = Y
                    Case 4
                        user.drawflag = 3
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)  '求起始角
                        user.ArcType(UBound(user.ArcType)).start = rad
                   Case 3
                        user.drawflag = 1
                        '消除参考线
                        cad.DrawMode = 7
                        cad.Line (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y)-(user.Mousepausex, user.mousepausey), col
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)  '求结束角
                        user.ArcType(UBound(user.ArcType)).end = rad
                        '确定圆弧
                        cad.DrawMode = VBRUN.vbCopyPen
                        cad.Circle (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y), user.ArcType(UBound(user.ArcType)).r, user.ArcType(UBound(user.ArcType)).comvar.col, user.ArcType(UBound(user.ArcType)).start, user.ArcType(UBound(user.ArcType)).end
            End Select
            user.CurrentOperistFlag = True
        Case "扇形"
            Select Case user.drawflag
                   Case 1
                        user.drawflag = 2
                        ReDim Preserve user.ArcType(UBound(user.ArcType) + 1)
                        '确定圆半径
                        rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                                           (mouseleftdowny - Y) ^ 2)
                        '存储圆弧的参数
                        user.name = "arc"
                        user.ArcType(UBound(user.ArcType)).r = rad
                        user.Savepraam  '公共参数的存储
                        cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
                        user.Mousepausex = X
                        user.mousepausey = Y
                    Case 4
                        user.drawflag = 3
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)   '结束角
                        user.ArcType(UBound(user.ArcType)).start = -rad
                   Case 3
                        user.drawflag = 1
                        '消除参考线
                        cad.DrawMode = 7
                        cad.Line (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y)-(user.Mousepausex, user.mousepausey), col
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)  '求结束角
                        user.ArcType(UBound(user.ArcType)).end = -rad
                        '确定圆弧
                        cad.DrawMode = VBRUN.vbCopyPen
                        cad.Circle (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y), user.ArcType(UBound(user.ArcType)).r, user.ArcType(UBound(user.ArcType)).comvar.col, user.ArcType(UBound(user.ArcType)).start, user.ArcType(UBound(user.ArcType)).end
            End Select
            user.CurrentOperistFlag = True  '标志是否进行了操作
        Case "Ellipse"
            If user.drawflag = 1 Then
               user.drawflag = 2
               ReDim Preserve user.EllipseType(UBound(user.EllipseType) + 1)
               '确定圆半径
               rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                     (mouseleftdowny - Y) ^ 2)
               '存储椭圆的参数
               user.name = "ellipse"
               user.EllipseType(UBound(user.EllipseType)).r = rad
               user.Savepraam  '公共参数的存储
               user.Mousepausex = 1       '暂时存放离心率
            Else
               user.drawflag = 1
               user.EllipseType(UBound(user.EllipseType)).asp = Abs((Y - user.EllipseType(UBound(user.EllipseType)).Y) / user.EllipseType(UBound(user.EllipseType)).r)
            End If
            user.CurrentOperistFlag = True  '标志是否进行了操作
        Case "circle"
              rad = Sqr((Mouseleftdownx - Mousepausex) ^ 2 _
                   + (mouseleftdowny - mousepausey) ^ 2)
              '清除参考圆
              cad.DrawMode = 7
              cad.Circle (Mouseleftdownx, mouseleftdowny), rad, col
              '确定圆
              cad.DrawMode = VBRUN.DrawModeConstants.vbCopyPen
              rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                        (mouseleftdowny - Y) ^ 2)
              cad.Circle (Mouseleftdownx, mouseleftdowny), rad, user.Commvar.col
              '存储圆的参数
              user.name = "circle"
              ReDim Preserve user.CircleType(UBound(user.CircleType) + 1)
              user.CircleType(UBound(user.CircleType)).r = rad
              user.Savepraam  '公共参数的存储
              'Put #200, , user.name
              'Put #200, , circletype
              user.CurrentOperistFlag = True  '标志是否进行了操作
        Case "text"
               Form1.cad.CurrentX = X
               Form1.cad.CurrentY = Y
               inputtextbox.Show 1, Form1
               draw.redraw
               user.CurrentOperistFlag = True  '标志是否进行了操作
               
          '图形编辑
        Case "selectobject", "fieldselectobject"    '目标选取
                'With user.snapefieldtype  '给捕捉矩形赋值
                '     .x1 = x
                '     .x2 = x
                '     .y1 = y
                '     .y2 = y
                'End With
                snape.selectobjectclare X, Y, Form1.cad   '清除以前选取的目标
           
                snape.selectobject X, Y, Form1.cad   '选取目标
                
                '区域选取时时,清除参考捕捉矩形并给捕捉到的范围赋值
                If user.CurrentOperist = "fieldselectobject" Then
                   Form1.cad.DrawMode = 7
                   draw.drawrectangle Form1.cad, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey, user.Snapecolor
                   
                   user.Mousepausex = X
                   user.mousepausey = Y
                End If
                user.CurrentOperist = "move"
                
        '选取目标
        'Case "selectendpoint" '选取线段的端点
        '       user.mousesnape = "snapecirle"  '捕捉时鼠标的形状,影响过程snapemouse
        '       If Button = VBRUN.vbLeftButton Then snape.snapeendpoint x, y, Form1.cad
        Case "selectline"
                Mousesnape = "snapecirle" '捕捉时鼠标的形状,影响过程snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snapeline X, Y, Form1.cad
        Case "selectcircle"
               Mousesnape = "snapecirle" '捕捉时鼠标的形状,影响过程snapemouse
               If Button = VBRUN.vbLeftButton Then snape.snapecircle X, Y, Form1.cad
        Case "selectrectangle"
                Mousesnape = "snapecirle" '捕捉时鼠标的形状,影响过程snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snaperectangle X, Y, Form1.cad
        Case "selectthreeangle"
                Mousesnape = "snapecirle" '捕捉时鼠标的形状,影响过程snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snapethreeangle X, Y, Form1.cad
        Case "selectarc"
                Mousesnape = "snapecirle" '捕捉时鼠标的形状,影响过程snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snapearc X, Y, Form1.cad
                
        '编辑选取的目标
        Case "move"    '移动
              edit.Moveadd X, Y, Form1.cad, False
              With user.SnapefieldType   '清除以前的捕捉矩形
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '显示捕捉矩形
             snape.showselectobject Form1.cad, True
             user.CurrentOperistFlag = True  '标志是否进行了操作
        Case "copy"    '复制
              edit.Moveadd X, Y, Form1.cad, True
              With user.SnapefieldType   '清除以前的捕捉矩形
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '显示捕捉矩形
              snape.showselectobject Form1.cad, True
              user.CurrentOperistFlag = True  '标志是否进行了操作
              
        Case "rounda", "round" '绕目标中心旋转
             edit.Round X, Y, Form1.cad, Button, vbBlack, 1
             With user.SnapefieldType   '清除以前的捕捉矩形
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '显示旋转后的目标
             snape.showselectobject Form1.cad, True
             user.CurrentOperistFlag = True  '标志是否进行了操作
        Case "mirror"     '不保存原图形的镜像
               Select Case user.drawflag
                      Case 1
                           edit.Mirror Form1.cad, X, Y, user.Snapecolor, 1
                      Case 2
                           user.drawflag = 3
                           
                      Case 3
               End Select
             With user.SnapefieldType   '清除以前的捕捉矩形
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '显示捕捉矩形
              snape.showselectobject Form1.cad, True
              user.CurrentOperistFlag = True  '标志是否进行了操作
        Case "mirrorsave"   '保存原图形的镜像
               Select Case user.drawflag
                      Case 1
                           edit.Mirror Form1.cad, X, Y, user.Snapecolor, 2
                      Case 2
                           user.drawflag = 3
                           
                      Case 3
               End Select
             With user.SnapefieldType   '清除以前的捕捉矩形
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '显示捕捉矩形
              snape.showselectobject Form1.cad, True
              user.CurrentOperistFlag = True  '标志是否进行了操作
              
        '缩放
        Case "selectzoom"
              If user.mousepausey - user.mouseleftdowny <> 0 _
                  And user.Mousepausex - user.Mouseleftdownx <> 0 _
              Then
                  user.HeightZoomnum = Form1.desk.ScaleHeight / _
                  ScaleX(Abs(user.mouseleftdowny - _
                  user.mousepausey), user.paper.until, 3)
                  user.WidthZoomnum = Form1.desk.scalewidth / _
                  ScaleY(Abs(user.Mouseleftdownx - _
                  user.Mousepausex), user.paper.until, 3)
                  math.zoom Form1.cad, X, Y
                  user.SnapeField = user.SnapeField / user.HeightZoomnum  '捕捉区哉大小
                  draw.redraw
              End If
              
End Select
cad.DrawMode = mode
'显示大十字光标
user.DispBigCross Form1.cad, X, Y
user.DispBigCross Form1.cad, X, Y
'显示捕捉光标
 user.SnapeMouse Form1.cad, X, Y
 user.SnapeMouse Form1.cad, X, Y
End Sub


