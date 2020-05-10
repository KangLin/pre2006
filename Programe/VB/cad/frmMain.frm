VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{38911DA0-E448-11D0-84A3-00DD01104159}#1.1#0"; "COMCT332.OCX"
Begin VB.MDIForm frmMain 
   BackColor       =   &H8000000C&
   Caption         =   "制图"
   ClientHeight    =   5940
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   9360
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   3  '窗口缺省
   Begin ComCtl3.CoolBar CB 
      Align           =   1  'Align Top
      Height          =   60
      Index           =   0
      Left            =   0
      TabIndex        =   7
      Top             =   0
      Width           =   9360
      _ExtentX        =   16510
      _ExtentY        =   106
      BandCount       =   0
      _CBWidth        =   9360
      _CBHeight       =   60
      _Version        =   "6.0.8169"
      Begin MSComctlLib.Toolbar TB 
         Height          =   165
         Index           =   1
         Left            =   240
         TabIndex        =   8
         Top             =   0
         Width           =   3225
         _ExtentX        =   5689
         _ExtentY        =   291
         ButtonWidth     =   609
         ButtonHeight    =   582
         AllowCustomize  =   0   'False
         Wrappable       =   0   'False
         Appearance      =   1
         _Version        =   393216
         BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
            NumButtons      =   1
            BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            EndProperty
         EndProperty
      End
   End
   Begin ComCtl3.CoolBar cbar 
      Align           =   2  'Align Bottom
      Height          =   450
      Left            =   0
      TabIndex        =   0
      Top             =   5490
      Width           =   9360
      _ExtentX        =   16510
      _ExtentY        =   794
      BandCount       =   5
      _CBWidth        =   9360
      _CBHeight       =   450
      _Version        =   "6.0.8169"
      MinHeight1      =   360
      Width1          =   4230
      NewRow1         =   0   'False
      MinHeight2      =   360
      Width2          =   180
      NewRow2         =   0   'False
      Child3          =   "tishi3"
      MinHeight3      =   390
      Width3          =   1155
      NewRow3         =   0   'False
      MinHeight4      =   360
      Width4          =   180
      NewRow4         =   0   'False
      Child5          =   "tishi5"
      MinHeight5      =   390
      Width5          =   3435
      NewRow5         =   0   'False
      Begin VB.TextBox TCurrentOperist 
         Height          =   375
         Left            =   0
         TabIndex        =   6
         Top             =   0
         Visible         =   0   'False
         Width           =   855
      End
      Begin VB.TextBox tishi5 
         Height          =   390
         Left            =   6030
         TabIndex        =   3
         Top             =   30
         Width           =   3240
      End
      Begin VB.TextBox tishi3 
         Height          =   390
         Left            =   4635
         TabIndex        =   2
         Top             =   30
         Width           =   960
      End
      Begin VB.Label tishi4 
         AutoSize        =   -1  'True
         Height          =   180
         Left            =   6840
         TabIndex        =   5
         Top             =   120
         Width           =   450
      End
      Begin VB.Label Tishi2 
         AutoSize        =   -1  'True
         Height          =   180
         Left            =   4440
         TabIndex        =   4
         Top             =   120
         Width           =   90
      End
      Begin VB.Label TiShi1 
         AutoSize        =   -1  'True
         Height          =   180
         Left            =   240
         TabIndex        =   1
         Top             =   120
         Width           =   90
      End
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   480
      Top             =   1350
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   1800
      Top             =   1680
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483633
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   76
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0000
            Key             =   "new"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0112
            Key             =   "open"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0224
            Key             =   "save"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0336
            Key             =   "print"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0448
            Key             =   "cut"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":055A
            Key             =   "copy"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":066C
            Key             =   "paste"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":077E
            Key             =   "delete"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0890
            Key             =   "undo"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":09A2
            Key             =   "redo"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0AB4
            Key             =   "line"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0BC6
            Key             =   "rectangle"
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0CD8
            Key             =   "ellipse"
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0DEA
            Key             =   "arc"
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0EFC
            Key             =   "line style"
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":100E
            Key             =   "help"
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1120
            Key             =   "arrow"
         EndProperty
         BeginProperty ListImage18 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1284
            Key             =   "circle"
         EndProperty
         BeginProperty ListImage19 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":15D4
            Key             =   "扇形"
         EndProperty
         BeginProperty ListImage20 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1924
            Key             =   ""
         EndProperty
         BeginProperty ListImage21 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1C74
            Key             =   "正方形"
         EndProperty
         BeginProperty ListImage22 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1FC4
            Key             =   "正三角形"
         EndProperty
         BeginProperty ListImage23 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2314
            Key             =   "正六边形"
         EndProperty
         BeginProperty ListImage24 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2664
            Key             =   "三角形"
         EndProperty
         BeginProperty ListImage25 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":29B4
            Key             =   ""
         EndProperty
         BeginProperty ListImage26 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2B20
            Key             =   ""
         EndProperty
         BeginProperty ListImage27 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2C8C
            Key             =   "文字"
         EndProperty
         BeginProperty ListImage28 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":33EC
            Key             =   "text"
         EndProperty
         BeginProperty ListImage29 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":3500
            Key             =   ""
         EndProperty
         BeginProperty ListImage30 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":3850
            Key             =   ""
         EndProperty
         BeginProperty ListImage31 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":3BA0
            Key             =   "circlecross"
         EndProperty
         BeginProperty ListImage32 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":3EF0
            Key             =   ""
         EndProperty
         BeginProperty ListImage33 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4240
            Key             =   ""
         EndProperty
         BeginProperty ListImage34 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4590
            Key             =   ""
         EndProperty
         BeginProperty ListImage35 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":48E0
            Key             =   ""
         EndProperty
         BeginProperty ListImage36 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4C30
            Key             =   ""
         EndProperty
         BeginProperty ListImage37 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4F80
            Key             =   ""
         EndProperty
         BeginProperty ListImage38 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":52D0
            Key             =   ""
         EndProperty
         BeginProperty ListImage39 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":5620
            Key             =   ""
         EndProperty
         BeginProperty ListImage40 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":5970
            Key             =   ""
         EndProperty
         BeginProperty ListImage41 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":5CC0
            Key             =   ""
         EndProperty
         BeginProperty ListImage42 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6010
            Key             =   ""
         EndProperty
         BeginProperty ListImage43 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6360
            Key             =   "m扇形"
         EndProperty
         BeginProperty ListImage44 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":66B0
            Key             =   "m三角形"
         EndProperty
         BeginProperty ListImage45 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6A00
            Key             =   "mcirclecross"
         EndProperty
         BeginProperty ListImage46 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6D50
            Key             =   "m正方形"
         EndProperty
         BeginProperty ListImage47 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":70A0
            Key             =   "m正三角形"
         EndProperty
         BeginProperty ListImage48 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":73F0
            Key             =   "m正六边形"
         EndProperty
         BeginProperty ListImage49 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7740
            Key             =   "mcircle"
         EndProperty
         BeginProperty ListImage50 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7A90
            Key             =   "水平标注"
         EndProperty
         BeginProperty ListImage51 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7DE0
            Key             =   "连续水平标注"
         EndProperty
         BeginProperty ListImage52 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8130
            Key             =   "垂直标注"
         EndProperty
         BeginProperty ListImage53 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8480
            Key             =   "连续垂直标注"
         EndProperty
         BeginProperty ListImage54 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":87D0
            Key             =   ""
         EndProperty
         BeginProperty ListImage55 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8B20
            Key             =   ""
         EndProperty
         BeginProperty ListImage56 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8E70
            Key             =   ""
         EndProperty
         BeginProperty ListImage57 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":91C0
            Key             =   "select"
         EndProperty
         BeginProperty ListImage58 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":9328
            Key             =   "连画线"
         EndProperty
         BeginProperty ListImage59 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":9678
            Key             =   ""
         EndProperty
         BeginProperty ListImage60 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":99C8
            Key             =   ""
         EndProperty
         BeginProperty ListImage61 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":9D18
            Key             =   ""
         EndProperty
         BeginProperty ListImage62 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":A068
            Key             =   ""
         EndProperty
         BeginProperty ListImage63 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":A3B8
            Key             =   "snapemiss"
         EndProperty
         BeginProperty ListImage64 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":A708
            Key             =   "snapeend"
         EndProperty
         BeginProperty ListImage65 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":AA58
            Key             =   "snapemid"
         EndProperty
         BeginProperty ListImage66 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":ADA8
            Key             =   "snapecenter"
         EndProperty
         BeginProperty ListImage67 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":B0F8
            Key             =   "exit"
         EndProperty
         BeginProperty ListImage68 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":B448
            Key             =   "ccopy"
         EndProperty
         BeginProperty ListImage69 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":B798
            Key             =   "move"
         EndProperty
         BeginProperty ListImage70 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":BAE8
            Key             =   "mirror"
         EndProperty
         BeginProperty ListImage71 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":BE38
            Key             =   "round"
         EndProperty
         BeginProperty ListImage72 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":C188
            Key             =   "垂直线段"
         EndProperty
         BeginProperty ListImage73 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":C41C
            Key             =   "twolinemiss"
         EndProperty
         BeginProperty ListImage74 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":C6B0
            Key             =   "chamfer"
         EndProperty
         BeginProperty ListImage75 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":C944
            Key             =   "break"
         EndProperty
         BeginProperty ListImage76 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":CBD8
            Key             =   "tan"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "文件(&F)"
      Begin VB.Menu mnuFileNew 
         Caption         =   "新文件  (&N)"
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFileOpen 
         Caption         =   "打开文件(&O)..."
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "关闭文件(&C)"
      End
      Begin VB.Menu mnuFileBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "保存文件(&S)"
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "保存为  (&A)"
      End
      Begin VB.Menu mnuFileSaveAll 
         Caption         =   "全部保存(&l)"
      End
      Begin VB.Menu mnuFileBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePageSetup 
         Caption         =   "页设置(&U)"
      End
      Begin VB.Menu mnuFilePrintPreview 
         Caption         =   "打印预览(&V)"
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "打印(&P)"
      End
      Begin VB.Menu mnuFileBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnufileexit 
         Caption         =   "退出(&E)"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "编辑(&E)"
      Begin VB.Menu mnuEditDelete 
         Caption         =   "删除(&L)"
      End
      Begin VB.Menu mnuEditRedraw 
         Caption         =   "重画(&R)"
      End
      Begin VB.Menu mnuEditBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditCut 
         Caption         =   "剪切(&T)"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "复制(&C)"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "粘贴(&P)"
         Shortcut        =   ^V
      End
      Begin VB.Menu mnuEditbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSelectPoint 
         Caption         =   "点选取(&S)"
      End
      Begin VB.Menu mnuEditSelectAll 
         Caption         =   "全选(&A)"
      End
      Begin VB.Menu mnuEditUndo 
         Caption         =   "取消选取(&U)"
      End
      Begin VB.Menu mnuEditbar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditMake 
         Caption         =   "变换"
         Begin VB.Menu mnuEditMakeMove 
            Caption         =   "移动(&O)"
         End
         Begin VB.Menu mnuEditMakeCopy 
            Caption         =   "复制"
         End
         Begin VB.Menu mnuEditMakeRound 
            Caption         =   "旋转(&R)"
         End
         Begin VB.Menu mnuEditMakeMirror 
            Caption         =   "镜像(&M)"
         End
         Begin VB.Menu mnuEditMakeMirrorSave 
            Caption         =   "镜像(保留原图)"
            Enabled         =   0   'False
         End
         Begin VB.Menu mnuEditMakeArray 
            Caption         =   "阵列"
            Begin VB.Menu mnuEditModefiyArrayCircle 
               Caption         =   "圆形阵列"
            End
            Begin VB.Menu mnuEditModefiyArrayRectangle 
               Caption         =   "矩形阵列"
            End
         End
      End
      Begin VB.Menu mnuEditbar4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditModify 
         Caption         =   "修改"
         Begin VB.Menu mnuEditModifyRatioChange 
            Caption         =   "比例变换"
            Visible         =   0   'False
         End
         Begin VB.Menu mnuEditModifyBreak 
            Caption         =   "切断(&B)"
         End
         Begin VB.Menu mnuEditModifyTrim 
            Caption         =   "修剪"
         End
         Begin VB.Menu mnuEditModifyText 
            Caption         =   "修改文字"
         End
         Begin VB.Menu mnuEditBar5 
            Caption         =   "-"
         End
         Begin VB.Menu mnuEditModifyFillet 
            Caption         =   "圆角"
         End
         Begin VB.Menu mnuEditModifyChamfer 
            Caption         =   "切角"
         End
         Begin VB.Menu mnuEditModifyParameter 
            Caption         =   "确定圆角和切角的参数"
         End
         Begin VB.Menu mnuEditBar6 
            Caption         =   "-"
         End
         Begin VB.Menu mnuEditModifyTwoLineMiss 
            Caption         =   "使两直线相交"
         End
      End
   End
   Begin VB.Menu mnuMake 
      Caption         =   "制图(&M)"
      Begin VB.Menu mnuMakeEnd 
         Caption         =   "结束"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakeClose 
         Caption         =   "关闭"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakeUndo 
         Caption         =   "取消"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakebar1 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakeLine 
         Caption         =   "直线"
         Begin VB.Menu mnuMakeLine线段 
            Caption         =   "线段"
         End
         Begin VB.Menu mnuMakeLine垂直线段 
            Caption         =   "垂直线段"
         End
         Begin VB.Menu mnuMake连画线 
            Caption         =   "连画线"
         End
         Begin VB.Menu mnuMakeLine定点到圆的切线 
            Caption         =   "定点到圆的切线"
         End
      End
      Begin VB.Menu mnuMake三角形 
         Caption         =   "三角形"
      End
      Begin VB.Menu mnuMake正三角形 
         Caption         =   "正三角形"
      End
      Begin VB.Menu mnuMake矩形 
         Caption         =   "矩形"
      End
      Begin VB.Menu mnuMake正方形 
         Caption         =   "正方形"
      End
      Begin VB.Menu mnuMake正六边形 
         Caption         =   "正六边形"
      End
      Begin VB.Menu mnuMake圆 
         Caption         =   "圆"
      End
      Begin VB.Menu mnuMake圆弧 
         Caption         =   "圆弧"
      End
      Begin VB.Menu mnuMake扇形 
         Caption         =   "扇形"
      End
      Begin VB.Menu mnuMake椭圆 
         Caption         =   "椭圆"
      End
      Begin VB.Menu mnuMaketext 
         Caption         =   "文字"
      End
      Begin VB.Menu mnuMake标注 
         Caption         =   "标注"
         Begin VB.Menu mnuMakeDim水平标注 
            Caption         =   "水平标注"
         End
         Begin VB.Menu mnuMakeDim连续水平标注 
            Caption         =   "连续水平标注"
         End
         Begin VB.Menu mnuMakeDim垂直标注 
            Caption         =   "垂直标注"
         End
         Begin VB.Menu mnuMakeDim连续垂直标注 
            Caption         =   "连续垂直标注"
         End
         Begin VB.Menu mnuMakeDim同基标注 
            Caption         =   "同基线标注"
         End
         Begin VB.Menu mnuMakeDim半径尺寸 
            Caption         =   "半径尺寸"
         End
         Begin VB.Menu mnuMakeDim直径尺寸 
            Caption         =   "直径尺寸"
         End
         Begin VB.Menu mnuMakeDim旁径尺寸 
            Caption         =   "旁注尺寸"
         End
         Begin VB.Menu mnuMakeDim角度尺寸 
            Caption         =   "角度尺寸"
         End
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "视图(&V)"
      Begin VB.Menu mnuViewZoomOut 
         Caption         =   "放大(&O)"
      End
      Begin VB.Menu mnuViewZoomIn 
         Caption         =   "缩小(&I)"
      End
      Begin VB.Menu mnuViewSelectZoom 
         Caption         =   "选择放大(&S)"
      End
      Begin VB.Menu mnuViewExtents 
         Caption         =   "恢复原图(&R)"
      End
      Begin VB.Menu mnuViewFullWindow 
         Caption         =   "全图游览(&F)"
      End
      Begin VB.Menu mnuViewbar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewMouse 
         Caption         =   "鼠标形状(&M)"
         Begin VB.Menu mnuViewMouseLittleCross 
            Caption         =   "小十字光标"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuViewMouseBigCross 
            Caption         =   "大十字光标"
         End
         Begin VB.Menu mnuViewMouseArrow 
            Caption         =   "箭形光标"
         End
         Begin VB.Menu mnuViewMouseCircle 
            Caption         =   "圆形光标"
         End
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "窗口(&W)"
      Begin VB.Menu mnuWindowNewWindow 
         Caption         =   "新窗口(&N)"
      End
      Begin VB.Menu mnuWindowClose 
         Caption         =   "关闭窗口(&C)"
      End
      Begin VB.Menu mnuWindowCloseAllWindow 
         Caption         =   "关闭所有窗口(&A)"
      End
      Begin VB.Menu mnuWindowBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuWindowCascade 
         Caption         =   "层叠排列窗口(&L)"
      End
      Begin VB.Menu mnuWindowTileHorizontal 
         Caption         =   "水平排列窗口(&H)"
      End
      Begin VB.Menu mnuWindowTileVertical 
         Caption         =   "垂直排列窗口(&V)"
      End
      Begin VB.Menu mnuWindowArrangeIcons 
         Caption         =   "窗口最小化时按图标排列"
      End
   End
   Begin VB.Menu mnuToolS 
      Caption         =   "工具(&T)"
      Begin VB.Menu mnuToolSnape 
         Caption         =   "捕捉"
         Begin VB.Menu mnuToolSnapeEndPoint 
            Caption         =   "捕捉直线或圆弧端点"
         End
         Begin VB.Menu mnuToolSnapeMiddlePoint 
            Caption         =   "捕捉直线或圆弧的中点"
         End
         Begin VB.Menu mnuToolSnapeCentrPoint 
            Caption         =   "捕捉圆心、弧心、扇形中心、椭圆中心"
         End
         Begin VB.Menu mnuToolSnapeMissPoint 
            Caption         =   "捕捉交点"
         End
         Begin VB.Menu mnuToolSnapeExit 
            Caption         =   "退出捕捉"
         End
      End
      Begin VB.Menu mnuToolbar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolBar_File 
         Caption         =   "文件工具栏"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolBar_Edit 
         Caption         =   "编辑工具栏"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolBar_Make 
         Caption         =   "制图工具栏"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolBar_Snape 
         Caption         =   "捕捉工具栏"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolObjectList 
         Caption         =   "实体列表"
      End
      Begin VB.Menu mnuToolbar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolsOptions 
         Caption         =   "选项(&O)"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "帮助(&H)"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "目录"
      End
      Begin VB.Menu mnuHelpSearchForHelpOn 
         Caption         =   "搜索....."
      End
      Begin VB.Menu mnuHelpBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "关于(&A)"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'作者:康林

Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Any) As Long
Const EM_UNDO = &HC7
Private Declare Function OSWinHelp% Lib "user32" Alias "WinHelpA" (ByVal hwnd&, ByVal HelpFile$, ByVal wCommand%, dwData As Any)

Public CloseAllWindowFlag As Boolean '是否关闭所有窗口标志,详见frmmain中mnuWindowCloseAllWindow()过程

Private Sub MDIForm_Load()
Dim i, ss As String * 20
    i = GetPrivateProfileString("window", "left", "1000", ss, 10, Inifile)
    If i = 0 Then
       Me.left = 1000
    Else
       Me.left = Val(left$(ss, i))
    End If
    i = GetPrivateProfileString("window", "top", "800", ss, 10, Inifile)
    If i = 0 Then
       Me.top = 800
    Else
       Me.top = Val(left$(ss, i))
    End If
    i = GetPrivateProfileString("window", "Width", "6500", ss, 10, Inifile)
    If i = 0 Then
       Me.Width = 8500
    Else
       Me.Width = Val(left$(ss, i))
    End If
    i = GetPrivateProfileString("window", "Height", "6500", ss, 10, Inifile)
    If i = 0 Then
       Me.Height = 8500
    Else
       Me.Height = Val(left$(ss, i))
    End If
    
    Inital_Tool  '初始化工具栏
    
    LoadNewCad  '加载窗体
    
    Inital_Menu Me
       
End Sub

Private Sub Inital_Tool() '初始化工具栏
    AddToolBar Me
    TB(TB_EDIT).Buttons.Item("paste").Enabled = False
End Sub

Private Sub LoadNewCad()
    Static lCadCount As Long
    Dim Form1 As formcad
    If ActiveForm Is Nothing Then lCadCount = 0
    lCadCount = lCadCount + 1
    Set Form1 = New formcad
    With Form1
         .Caption = "制图 " & lCadCount
         .Show
    End With
        
    NoEnabled_Edit '使编辑按钮不响应事件

End Sub

Private Sub MDIForm_Unload(Cancel As Integer)
Dim i
    If Me.WindowState <> vbMinimized Then
        i = WritePrivateProfileString("window", "left", CStr(Me.left), Inifile)
        i = WritePrivateProfileString("window", "top", CStr(Me.top), Inifile)
        i = WritePrivateProfileString("window", "Width", CStr(Me.Width), Inifile)
        i = WritePrivateProfileString("window", "Height", CStr(Me.Height), Inifile)
    End If
End Sub

Private Sub mnuEditDelete_Click()
        ActiveForm.EditClear True
End Sub

Private Sub mnuEditMakeCopy_Click()
        TCurrentOperist.text = "复制"
End Sub

Private Sub mnuEditMakeMirror_Click()
        TCurrentOperist.text = "镜像"
End Sub

Private Sub mnuEditMakeMirrorSave_Click()
        TCurrentOperist.text = "镜像保留原图"
End Sub

Private Sub mnuEditMakeMove_Click()
         TCurrentOperist.text = "移动"
End Sub

Private Sub mnuEditMakeRound_Click()
        TCurrentOperist.text = "旋转"
End Sub

Private Sub mnuEditModefiyArrayCircle_Click()
        TCurrentOperist.text = "圆形阵列"
        DrawFlag = 1
End Sub

Private Sub mnuEditModefiyArrayRectangle_Click()
        TCurrentOperist.text = "矩形阵列"
End Sub

Private Sub mnuEditModifyBreak_Click()
        TCurrentOperist.text = "切断"
        DrawFlag = 1
End Sub

Private Sub mnuEditModifyChamfer_Click() '切角
        TCurrentOperist.text = "切角"
        DrawFlag = 1
End Sub

Private Sub mnuEditModifyFillet_Click() '圆角
        TCurrentOperist = "圆角"
        DrawFlag = 1
End Sub

Private Sub mnuEditModifyParameter_Click() '确定切角圆 角的参数
        FCP.Show 1, Me
End Sub

Private Sub mnuEditModifyText_Click() '修改文字
        TCurrentOperist.text = "修改文字"
End Sub

Private Sub mnuEditModifyTrim_Click() '修剪

End Sub

Private Sub mnuEditModifyTwoLineMiss_Click() '使两条直线相交
        TCurrentOperist.text = "使两直线相交"
        DrawFlag = 1
End Sub

Private Sub mnuEditRedraw_Click()
        ActiveForm.Redraw
End Sub

Private Sub mnuEditSelectAll_Click()
        ActiveForm.Select_All
End Sub

Private Sub mnuEditSelectPoint_Click()
        fMainForm.TCurrentOperist = "pointselect"
        DrawFlag = 0
End Sub

Private Sub mnuFileSaveAll_Click()
Dim hwn As Long, obj As Object, i, ss As String * 20
'hwn = GetWindow(Me.hwnd, GW_HWNDNEXT)
'i = SetActiveWindow(hwn)
'ActiveForm.cad.Cls
'ActiveForm.cad.Print "pkpk'"
End Sub

Private Sub mnuMakeClose_Click()  '关闭
        Select Case fMainForm.TCurrentOperist '文本控件省略为.text
               Case "连画线"
                    DrawFlag = 1
                    ActiveForm.确定连画线最后直线 "close"
               
        End Select
End Sub

Private Sub mnuMakeEnd_Click() '结束
        Select Case fMainForm.TCurrentOperist
               Case "连画线"
                    DrawFlag = 1
                    ActiveForm.确定连画线最后直线 "end"
               Case "连续水平标注", "连续垂直标注"
                    DrawFlag = 1
                    ActiveForm.HorizontalEnd "end"
        End Select
End Sub

Private Sub mnuMakeUndo_Click() '取消
        Select Case fMainForm.TCurrentOperist
               Case "连画线"
                    DrawFlag = 1
                    ActiveForm.确定连画线最后直线 "undo"
               Case "连续水平标注", "连续垂直标注"
                    ActiveForm.HorizontalEnd "undo"
                    DrawFlag = 1
               Case Else
                    ActiveForm.MakeUndo TCurrentOperist
        End Select
End Sub

Private Sub mnuMakeLine线段_Click()
        fMainForm.TCurrentOperist = "line"
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMakeLine垂直线段_Click() '
        TCurrentOperist.text = "垂直线段"
        DrawFlag = 1
End Sub

Private Sub mnuMakeLine定点到圆的切线_Click()
        TCurrentOperist.text = "定点到圆的切线"
        DrawFlag = 1
End Sub

Private Sub mnuMake连画线_Click()
        fMainForm.TCurrentOperist = "连画线"
        DrawFlag = 1
        mnuMakeClose.Visible = True '隐藏这四个菜单
        mnuMakeEnd.Visible = True
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake三角形_Click()
            fMainForm.TCurrentOperist = "三角形"
            DrawFlag = 1
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake正三角形_Click()
            fMainForm.TCurrentOperist = "正三角形"
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake矩形_Click()
        fMainForm.TCurrentOperist = "矩形"
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake正方形_Click()
        fMainForm.TCurrentOperist = "正方形"
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake正六边形_Click()
        fMainForm.TCurrentOperist = "正六边形"
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake圆_Click()
        fMainForm.TCurrentOperist = "圆"
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake圆弧_Click()
        fMainForm.TCurrentOperist = "圆弧"
        DrawFlag = 1
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake扇形_Click()
        fMainForm.TCurrentOperist = "扇形"
        DrawFlag = 1
        mnuMakeClose.Visible = False '隐藏这四个菜单
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake椭圆_Click()
        fMainForm.TCurrentOperist = "椭圆"
        mnuMakeClose.Visible = False '隐藏这四个菜单
        DrawFlag = 1
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMaketext_Click()
        TCurrentOperist.text = "文字"
End Sub

Private Sub mnuMakeDim水平标注_Click()
        TCurrentOperist.text = "水平标注"
        DrawFlag = 1
End Sub

Private Sub mnuMakeDim连续水平标注_Click() '
        TCurrentOperist.text = "连续水平标注"
        DrawFlag = 1
End Sub

Private Sub mnuMakeDIm垂直标注_Click()
        TCurrentOperist.text = "垂直标注"
        DrawFlag = 1
End Sub

Private Sub mnuMakeDim连续垂直标注_Click() '
        TCurrentOperist.text = "连续垂直标注"
        DrawFlag = 1
End Sub

Private Sub mnuMakedim同基标注_Click() '

End Sub

Private Sub mnuMakedim半径尺寸_Click() '

End Sub

Private Sub mnuMakedim直径尺寸_Click() '

End Sub

Private Sub mnuMakedim旁径尺寸_Click() '

End Sub

Private Sub mnuMakedim角度尺寸_Click() '

End Sub

Private Sub mnuToolObjectList_Click()
        If ON_ERROR_RESUME_NEXT Then
           PassWord.PassWordStyle = "实体列表"
           PassWord.Show 1, Me
           If Not PassWord.LoginSucceeded Then
              Exit Sub
           End If
        End If
        fMainForm.ActiveForm.ObjectList
End Sub

Private Sub mnuToolSnapeCentrPoint_Click()
        mnuToolSnapeCentrPoint.Checked = Not mnuToolSnapeCentrPoint.Checked
        If mnuToolSnapeCentrPoint.Checked Then
           TB(TB_SNAPE).Buttons.Item("snapecenter").Value = tbrPressed
        Else
           TB(TB_SNAPE).Buttons.Item("snapecenter").Value = tbrUnpressed
        End If
End Sub

Private Sub mnuToolSnapeEndPoint_Click()
        mnuToolSnapeEndPoint.Checked = Not mnuToolSnapeEndPoint.Checked
        If mnuToolSnapeEndPoint.Checked Then
           TB(TB_SNAPE).Buttons.Item("snapeend").Value = tbrPressed
        Else
           TB(TB_SNAPE).Buttons.Item("snapeend").Value = tbrUnpressed
        End If
End Sub

Private Sub mnuToolSnapeMiddlePoint_Click()
        mnuToolSnapeMiddlePoint.Checked = Not mnuToolSnapeMiddlePoint.Checked
        If mnuToolSnapeMiddlePoint.Checked Then
           TB(TB_SNAPE).Buttons.Item("snapemid").Value = tbrPressed
        Else
           TB(TB_SNAPE).Buttons.Item("snapemid").Value = tbrUnpressed
        End If
End Sub

Private Sub mnuToolSnapeMissPoint_Click()
        mnuToolSnapeMissPoint.Checked = Not mnuToolSnapeMissPoint.Checked
        If mnuToolSnapeMissPoint.Checked Then
           TB(TB_SNAPE).Buttons.Item("snapemiss").Value = tbrPressed
        Else
           TB(TB_SNAPE).Buttons.Item("snapemiss").Value = tbrUnpressed
        End If
End Sub

Private Sub mnuToolSnapeExit_Click()
        TB(TB_SNAPE).Buttons.Item("snapecenter").Value = tbrUnpressed
        TB(TB_SNAPE).Buttons.Item("snapeend").Value = tbrUnpressed
        TB(TB_SNAPE).Buttons.Item("snapemid").Value = tbrUnpressed
        TB(TB_SNAPE).Buttons.Item("snapemiss").Value = tbrUnpressed
        mnuToolSnapeEndPoint.Checked = False
        mnuToolSnapeMiddlePoint.Checked = False
        mnuToolSnapeCentrPoint.Checked = False
        mnuToolSnapeMissPoint.Checked = False
End Sub

Private Sub mnuToolBar_File_Click()
        mnuToolBar_File.Checked = Not mnuToolBar_File.Checked
        TB(TB_FILE).Visible = mnuToolBar_File.Checked
        CB(0).Bands.Item(TB_FILE).Visible = mnuToolBar_File.Checked
End Sub

Private Sub mnuToolBar_Edit_Click()
        mnuToolBar_Edit.Checked = Not mnuToolBar_Edit.Checked
        TB(TB_EDIT).Visible = mnuToolBar_Edit.Checked
        CB(0).Bands.Item(TB_EDIT).Visible = mnuToolBar_Edit.Checked
End Sub

Private Sub mnuToolBar_Make_Click()
        mnuToolBar_Make.Checked = Not mnuToolBar_Make.Checked
        TB(TB_MAKE).Visible = mnuToolBar_Make.Checked
        CB(0).Bands.Item(TB_MAKE).Visible = mnuToolBar_Make.Checked
End Sub

Private Sub mnuToolBar_Snape_Click()
        mnuToolBar_Snape.Checked = Not mnuToolBar_Snape.Checked
        TB(TB_SNAPE).Visible = mnuToolBar_Snape.Checked
        CB(1).Visible = mnuToolBar_Snape.Checked
End Sub

Public Sub mnuViewMouseArrow_Click() '箭形光标
        With ActiveForm
             .cad.MousePointer = vbArrow
             .Line1.Visible = False
             .Line2.Visible = False
             .Smouse.Visible = False
             .Mousestyle = "箭形光标"
        End With
        mnuViewMouseArrow.Checked = True
        mnuViewMouseCircle.Checked = False
        mnuViewMouseBigCross.Checked = False
        mnuViewMouseLittleCross.Checked = False
End Sub

Public Sub mnuViewMouseBigCross_Click()  '大十字光标
        With ActiveForm
             .cad.MousePointer = vbCrosshair       '自定义光标
             .Line1.Visible = True
             .Line2.Visible = True
             .Smouse.Visible = False
             .Mousestyle = "大十字光标"
        End With
        With ActiveForm.Line1
             .X1 = 0
             .Y1 = 0
             .X2 = 0
             .Y2 = 0
        End With
        With ActiveForm.Line2
             .X1 = 0
             .Y1 = 0
             .X2 = 0
             .Y2 = 0
        End With
        mnuViewMouseArrow.Checked = False
        mnuViewMouseBigCross.Checked = True
        mnuViewMouseLittleCross.Checked = False
        mnuViewMouseCircle.Checked = False
End Sub

Public Sub mnuViewMouseCircle_Click()  '圆形光标
        With ActiveForm
             .cad.MousePointer = vbCrosshair     '自定义光标
             .Smouse.Visible = True
             .Mousestyle = "圆形光标"
             .Smouse.Height = 0
             .Smouse.Width = 0
             .Line1.Visible = False
             .Line2.Visible = False
        End With
        mnuViewMouseArrow.Checked = False
        mnuViewMouseBigCross.Checked = False
        mnuViewMouseLittleCross.Checked = False
        mnuViewMouseCircle.Checked = True
End Sub

Public Sub mnuViewMouseLittleCross_Click()    '小十字光标
        With ActiveForm
            .cad.MousePointer = vbCrosshair
             .Line1.Visible = False
             .Line2.Visible = False
             .Smouse.Visible = False
             .Mousestyle = "小十字光标"
        End With
        mnuViewMouseArrow.Checked = False
        mnuViewMouseBigCross.Checked = False
        mnuViewMouseLittleCross.Checked = True
        mnuViewMouseCircle.Checked = False
End Sub

Private Sub mnuViewZoomIn_Click()  '缩小
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    With ActiveForm.cad
        'SnapeField =SnapeField * 2 '缩小捕捉区域
        .top = .top / 2
        .left = .left / 2
        .Width = .Width / 2
        .Height = .Height / 2
        .ScaleHeight = .ScaleHeight * 2
        .Scalewidth = .Scalewidth * 2
        Scroll ActiveForm, .left, .top '滚动条
        ActiveForm.Redraw
    End With
End Sub

Private Sub mnuViewZoomOut_Click() '放大
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    With ActiveForm.cad
        'SnapeField = SnapeField / 2 '放大捕捉区域
        .top = .top * 2
        .left = .left * 2
        .Width = .Width * 2
        .Height = .Height * 2
        .ScaleHeight = .ScaleHeight / 2
        .Scalewidth = .Scalewidth / 2
        Scroll ActiveForm, .left, .top  '滚动条
        ActiveForm.Redraw
   End With
End Sub

Private Sub mnuHelpAbout_Click()
        frmAbout.Show vbModal, Me
End Sub

Private Sub mnuHelpSearchForHelpOn_Click()
    Dim nRet As Integer


    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        #If ON_ERROR_RESUME_NEXT Then
            On Error Resume Next
        #End If
        nRet = OSWinHelp(Me.hwnd, App.HelpFile, 261, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If

End Sub

Private Sub mnuHelpContents_Click()
    Dim nRet As Integer


    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        #If ON_ERROR_RESUME_NEXT Then
            On Error Resume Next
        #End If
        nRet = OSWinHelp(Me.hwnd, App.HelpFile, 3, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If

End Sub


Private Sub mnuToolsOptions_Click()
        fOption.Show 1
End Sub

Private Sub mnuWindowArrangeIcons_Click()
    Me.Arrange vbArrangeIcons
End Sub

Private Sub mnuWindowTileVertical_Click()
    Me.Arrange vbTileVertical
End Sub

Private Sub mnuWindowTileHorizontal_Click()
    Me.Arrange vbTileHorizontal
End Sub

Private Sub mnuWindowCascade_Click()
    Me.Arrange vbCascade
End Sub

Private Sub mnuWindowNewWindow_Click()
    LoadNewCad
End Sub

Private Sub mnuWindowClose_Click() '关闭窗口
        Unload ActiveForm
End Sub

Private Sub mnuWindowCloseAllWindow_Click() '关闭所有窗口
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        'CloseAllWindowFlag的作用是当关闭窗口时,
        '如果后悔,可按取消,停止关闭.即防止此处死循环,
        '该值在formcad中的Form_QueryUnload过程中设置
        CloseAllWindowFlag = True
        While ((Not ActiveForm Is Nothing) And CloseAllWindowFlag)
              Unload ActiveForm
        Wend
End Sub

Private Sub mnuEditPaste_Click()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    ActiveForm.EditPaste

End Sub

Private Sub mnuEditCopy_Click()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
      ActiveForm.EditCopy
End Sub

Private Sub mnuEditCut_Click()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        ActiveForm.EditCut
End Sub

Public Sub mnuEditUndo_Click()
        ActiveForm.EditClear False
End Sub

Private Sub mnuFileExit_Click()
    Unload Me
End Sub

Private Sub mnuFileSend_Click()
    'ToDo: Add 'mnuFileSend_Click' code.
    MsgBox "Add 'mnuFileSend_Click' code."
End Sub

Private Sub mnuFilePrint_Click()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    If ActiveForm Is Nothing Then Exit Sub
    

    With dlgCommonDialog
        .DialogTitle = "Print"
        .CancelError = True
        .Flags = cdlPDReturnDC + cdlPDNoPageNums
        If ActiveForm.rtfText.SelLength = 0 Then
            .Flags = .Flags + cdlPDAllPages
        Else
            .Flags = .Flags + cdlPDSelection
        End If
        .ShowPrinter
        If Err <> MSComDlg.cdlCancel Then
            ActiveForm.rtfText.SelPrint .hdc
        End If
    End With

End Sub

Private Sub mnuFilePrintPreview_Click()
    'ToDo: Add 'mnuFilePrintPreview_Click' code.
    MsgBox "Add 'mnuFilePrintPreview_Click' code."
End Sub

Private Sub mnuFilePageSetup_Click()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    With dlgCommonDialog
        .DialogTitle = "Page Setup"
        .CancelError = True
        .ShowPrinter
    End With

End Sub

Private Sub mnuFileProperties_Click()
    'ToDo: Add 'mnuFileProperties_Click' code.
    MsgBox "Add 'mnuFileProperties_Click' code."
End Sub

Private Sub mnuFileSaveAs_Click()
    Dim sFile As String

    If ActiveForm Is Nothing Then Exit Sub

    With dlgCommonDialog
        .DialogTitle = "保存为"
        .CancelError = False
        'ToDo: set the flags and attributes of the Commondialog control
        .Filter = "All Files (*.*)|*.*"
        .ShowSave
        If Len(.FileName) = 0 Then
            Exit Sub
        End If
        sFile = .FileName
    End With
    ActiveForm.Caption = sFile
    ActiveForm.SaveFile sFile

End Sub

Public Sub mnuFileSave_Click()
    Dim sFile As String
    If left$(ActiveForm.Caption, 2) = "制图" Then
        With dlgCommonDialog
            .DialogTitle = "保存"
            .CancelError = False
            'ToDo: set the flags and attributes of the Commondialog control
            .Filter = "计算机制图 (*.kld)|*.kld|All Files (*.*)|*.*"
            .ShowSave
            If Len(.FileName) = 0 Then
                Exit Sub
            End If
            sFile = .FileName
        End With
        ActiveForm.SaveFile sFile
    Else
        sFile = ActiveForm.Caption
        ActiveForm.SaveFile sFile
    End If

End Sub

Private Sub mnuFileClose_Click()
        mnuWindowClose_Click
End Sub

Private Sub mnuFileOpen_Click()
    Dim sFile As String

    'If ActiveForm Is Nothing Then LoadNewCad
    LoadNewCad
    With dlgCommonDialog
        .DialogTitle = "打开文件"
        .CancelError = False
        'ToDo: set the flags and attributes of the Commondialog control
        .Filter = "计算机制图 (*.kld)|*.kld|All Files (*.*)|*.*"
        .ShowOpen
        If Len(.FileName) = 0 Then
            mnuWindowClose_Click
            Exit Sub
        End If
        sFile = .FileName
    End With
    
    ActiveForm.OpenFile sFile  '打开文件
    ActiveForm.Caption = sFile  '把文件名放在窗口标题内

End Sub

Private Sub mnuFileNew_Click()
    LoadNewCad
End Sub

Private Sub Tb_ButtonClick(Index As Integer, ByVal Button As MSComctlLib.Button)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    Select Case Button.Key
        Case "new"
            LoadNewCad
        Case "open"
            mnuFileOpen_Click
        Case "save"
            mnuFileSave_Click
        Case "print"
            mnuFilePrint_Click
        Case "cut"
            mnuEditCut_Click
        Case "copy"
            mnuEditCopy_Click
        Case "paste"
            mnuEditPaste_Click
        Case "delete"
            mnuEditDelete_Click
        Case "undo"
            mnuEditUndo_Click
        Case "redo"
             mnuEditRedraw_Click
        Case "select"
             mnuEditSelectPoint_Click
             UnPressButton TB(TB_EDIT)
             Button.Value = tbrPressed
        Case "ccopy"
             mnuEditMakeCopy_Click
             UnPressButton TB(TB_EDIT)
             Button.Value = tbrPressed
        Case "round"
             mnuEditMakeRound_Click
             UnPressButton TB(TB_EDIT)
             Button.Value = tbrPressed
        Case "break"
             mnuEditModifyBreak_Click
             UnPressButton TB(TB_EDIT)
             Button.Value = tbrPressed
        Case "chamfer"
             UnPressButton TB(TB_EDIT)
             Button.Value = tbrPressed
             mnuEditModifyChamfer_Click
        Case "text"
             mnuEditModifyText_Click
        Case "mirror"
             mnuEditMakeMirror_Click
             UnPressButton TB(TB_EDIT)
             Button.Value = tbrPressed
        Case "line"
             mnuMakeLine线段_Click
        Case "twolinemiss"
             mnuEditModifyTwoLineMiss_Click
        Case "垂直线段"
             mnuMakeLine垂直线段_Click
        Case "连画线"
             mnuMake连画线_Click
        Case "tan"
             mnuMakeLine定点到圆的切线_Click
        Case "line style"
             mnuToolsOptions_Click
        Case "三角形"
             mnuMake三角形_Click
        Case "正三角形"
             mnuMake正三角形_Click
        Case "正方形"
             mnuMake正方形_Click
        Case "rectangle"
             mnuMake矩形_Click
        Case "正六边形"
             mnuMake正六边形_Click
        Case "circle"
             mnuMake圆_Click
        Case "rectangle"
            mnuMake矩形_Click
        Case "arc"
             mnuMake圆弧_Click
        Case "扇形"
            mnuMake扇形_Click
        Case "ellipse"
            mnuMake椭圆_Click
        Case "文字"
            mnuMaketext_Click
        Case "水平标注"
            mnuMakeDim水平标注_Click
        Case "连续水平标注"
            mnuMakeDim连续水平标注_Click
        Case "垂直标注"
            mnuMakeDIm垂直标注_Click
        Case "连续垂直标注"
            mnuMakeDim连续垂直标注_Click
        Case "snapeend"
            mnuToolSnapeEndPoint_Click
        Case "snapemid"
            mnuToolSnapeMiddlePoint_Click
        Case "snapecenter"
            mnuToolSnapeCentrPoint_Click
        Case "snapemiss"
            mnuToolSnapeMissPoint_Click
        Case "snapeexit"
            mnuToolSnapeExit_Click
            UnPressButton TB(TB_SNAPE)
        Case "help"
            'ToDo: Add 'Help' button code.
            MsgBox "Add 'Help' button code."
    End Select
    
    Select Case Index
           Case TB_MAKE
                UnPressButton TB(Index)
                Button.Value = tbrPressed
    End Select
End Sub

Private Sub TB_ButtonDropDown(Index As Integer, ByVal Button As MSComctlLib.Button)
        'Select Case Index  '使所有按钮恢复原样
        '       Case TB_MAKE
                    UnPressButton TB(Index)
        'End Select
        Button.Value = tbrPressed
End Sub

Private Sub TB_ButtonMenuClick(Index As Integer, ByVal ButtonMenu As MSComctlLib.ButtonMenu)
        '设置按钮的样式
        With ButtonMenu.Parent
             .Key = ButtonMenu.Key
             .Image = ButtonMenu.Key
             .ToolTipText = ButtonMenu.text
             Tb_ButtonClick Index, TB(Index).Buttons.Item(ButtonMenu.Key)
             .Value = tbrPressed
        End With
End Sub

Private Sub TB_DragDrop(Index As Integer, Source As control, x As Single, y As Single)
        Source.top = y
        Source.left = x
End Sub

Private Sub CBTop_DragOver(Source As control, x As Single, y As Single, State As Integer)
        Source.top = y
        Source.left = x
End Sub

Private Sub TCurrentOperist_Change()
Const Make = "line水平线段垂直线段连画线正三角形正方形矩形正六边形圆弧扇形椭圆连续水平标注文字连续垂直标注定点到圆的切线"
Const Edit = "pointselect移动复制旋转镜像保留原图矩形阵列圆形阵列比例变换"
Const Break = "切断"
Dim text As String, Tag As String
    With TCurrentOperist
      If InStrB(1, Make, .text) <> 0 Then text = "make"
      If InStrB(1, Edit, .text) <> 0 Then text = "edit"
      If InStrB(1, Make, .Tag) <> 0 Then Tag = "make"
      If InStrB(1, Edit, .Tag) <> 0 Then Tag = "edit"
    End With
    If Tag <> text Then
        Select Case Tag
               Case "edit"
                    mnuEditUndo_Click
                    UnPressButton TB(TB_EDIT)
                    NoEnabled_Edit '使编辑工具不响应事件
               Case "make"
                    UnPressButton TB(TB_MAKE)
                    If TCurrentOperist.Tag = "定点到圆的切线" And DrawFlag = 2 Then
                       ActiveForm.MakeUndo TCurrentOperist.Tag
                    End If
        End Select
    End If
    
    ActiveForm.SSnape.Visible = False '清除捕捉目标
           
    With TCurrentOperist
       .Tag = .text
       If Val(ActiveForm.cad.Tag) And .text <> "移动" And .text <> "比例变换" Then MouseChange_Undo ActiveForm '恢复鼠标
       If .text = "pointselect" Then mnuToolSnapeExit_Click  '选取时不能用捕捉
       
    End With
End Sub
