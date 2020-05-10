VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form2"
   ClientHeight    =   5190
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   5190
   ScaleWidth      =   4680
   StartUpPosition =   2  '屏幕中心
   WindowState     =   2  'Maximized
   Begin RichTextLib.RichTextBox txtNetInput 
      Height          =   375
      Left            =   960
      TabIndex        =   19
      Top             =   1320
      Width           =   855
      _ExtentX        =   1508
      _ExtentY        =   661
      _Version        =   393217
      ScrollBars      =   3
      TextRTF         =   $"Form2.frx":0000
   End
   Begin RichTextLib.RichTextBox txtNetTalk 
      Height          =   375
      Left            =   960
      TabIndex        =   18
      Top             =   960
      Width           =   855
      _ExtentX        =   1508
      _ExtentY        =   661
      _Version        =   393217
      ScrollBars      =   3
      TextRTF         =   $"Form2.frx":0296
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   120
      Top             =   840
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.PictureBox PicNoQi 
      Height          =   615
      Left            =   1200
      ScaleHeight     =   555
      ScaleWidth      =   795
      TabIndex        =   17
      Top             =   240
      Width           =   855
   End
   Begin VB.Frame Fraredo 
      Caption         =   "复盘工具"
      Height          =   1215
      Left            =   2640
      TabIndex        =   13
      Top             =   3840
      Width           =   1455
      Begin VB.CommandButton CmdNext 
         Caption         =   "下一步（&N)"
         Height          =   300
         Left            =   120
         TabIndex        =   16
         Top             =   600
         Width           =   1215
      End
      Begin VB.CommandButton CmdCanel 
         Caption         =   "取  消(&C)"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   960
         Width           =   1215
      End
      Begin VB.CommandButton CmdPre 
         Caption         =   "上一步（&P)"
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   240
         Width           =   1215
      End
   End
   Begin VB.Timer Tim 
      Left            =   1800
      Top             =   1560
   End
   Begin MSComctlLib.StatusBar StatBar 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   4
      Top             =   4935
      Width           =   4680
      _ExtentX        =   8255
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin VB.Frame FraTiShi 
      Caption         =   "提示"
      Height          =   1935
      Left            =   0
      TabIndex        =   1
      Top             =   2520
      Width           =   2175
      Begin VB.Frame FraTime 
         Height          =   1215
         Left            =   0
         TabIndex        =   5
         Top             =   720
         Width           =   2175
         Begin VB.TextBox TxtTotalTime 
            Enabled         =   0   'False
            Height          =   270
            Left            =   960
            TabIndex        =   8
            Top             =   480
            Width           =   1095
         End
         Begin VB.TextBox TxtTime 
            Enabled         =   0   'False
            Height          =   270
            Left            =   960
            TabIndex        =   7
            Top             =   840
            Width           =   1095
         End
         Begin VB.TextBox TxtHadTime 
            Enabled         =   0   'False
            Height          =   270
            Left            =   960
            TabIndex        =   6
            Top             =   120
            Width           =   1095
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "已走时间："
            Height          =   180
            Index           =   1
            Left            =   120
            TabIndex        =   11
            Top             =   600
            Width           =   900
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "总共时间："
            Height          =   180
            Index           =   2
            Left            =   120
            TabIndex        =   10
            Top             =   960
            Width           =   900
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "本步时间："
            Height          =   180
            Index           =   0
            Left            =   120
            TabIndex        =   9
            Top             =   240
            Width           =   900
         End
      End
      Begin VB.Label LabTiShi 
         AutoSize        =   -1  'True
         Caption         =   "Label4"
         Height          =   180
         Left            =   720
         TabIndex        =   12
         Top             =   600
         Width           =   540
      End
      Begin VB.Image TiShiQZ 
         Height          =   495
         Left            =   960
         Stretch         =   -1  'True
         Top             =   120
         Visible         =   0   'False
         Width           =   495
      End
   End
   Begin MSComDlg.CommonDialog CMD 
      Left            =   480
      Top             =   1680
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.PictureBox PicQiPang 
      Height          =   2295
      Left            =   2160
      ScaleHeight     =   2235
      ScaleWidth      =   2715
      TabIndex        =   0
      Top             =   720
      Width           =   2775
      Begin VB.Shape ShpCur 
         BorderColor     =   &H00FFFFFF&
         Height          =   255
         Left            =   480
         Top             =   1200
         Width           =   495
      End
      Begin VB.Shape ShpTSW 
         Height          =   615
         Left            =   1560
         Top             =   840
         Width           =   495
      End
      Begin VB.Shape ShpTSD 
         Height          =   495
         Left            =   480
         Top             =   1560
         Width           =   615
      End
      Begin VB.Image QZ 
         Height          =   495
         Index           =   0
         Left            =   480
         Stretch         =   -1  'True
         Top             =   480
         Visible         =   0   'False
         Width           =   495
      End
   End
   Begin MSComctlLib.ImageList ImgList 
      Left            =   0
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   9
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":052C
            Key             =   "士"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":0848
            Key             =   "车"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":0B64
            Key             =   "将"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":0E80
            Key             =   "马"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":119C
            Key             =   "炮"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":14B8
            Key             =   "象"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":17D4
            Key             =   "卒"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":1AF0
            Key             =   "r"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":1E0C
            Key             =   "b"
         EndProperty
      EndProperty
   End
   Begin VB.Label LabYF 
      AutoSize        =   -1  'True
      Caption         =   "乙方"
      Height          =   180
      Left            =   3120
      TabIndex        =   3
      Top             =   3600
      Width           =   360
   End
   Begin VB.Label LabJF 
      AutoSize        =   -1  'True
      Caption         =   "甲方"
      Height          =   180
      Left            =   2880
      TabIndex        =   2
      Top             =   360
      Width           =   360
   End
   Begin VB.Menu mnuFile 
      Caption         =   "工具(&T)"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "复盘(&O)"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "保存(&S)"
      End
      Begin VB.Menu mnuFileContine 
         Caption         =   "继续下(&C)"
      End
      Begin VB.Menu mnuFileReStart 
         Caption         =   "重新开始(&R)"
      End
      Begin VB.Menu mnuBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileBuJu 
         Caption         =   "布局(&B)"
      End
      Begin VB.Menu mnuFileBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "退出(&E)"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "编辑(&E)"
      Begin VB.Menu mnuEditCopy 
         Caption         =   "复制(&C)"
      End
      Begin VB.Menu mnuEditPase 
         Caption         =   "粘贴(&P)"
      End
      Begin VB.Menu mnuEditCut 
         Caption         =   "剪切(&T)"
      End
   End
   Begin VB.Menu mnuOption 
      Caption         =   "选项(&O)"
      Begin VB.Menu mnuFileManAndMan 
         Caption         =   "双人对战(&T)"
      End
      Begin VB.Menu mnuFileManAndMachine 
         Caption         =   "人机对战(&M)"
      End
      Begin VB.Menu mnuFileNet 
         Caption         =   "网络对战(&N)"
      End
      Begin VB.Menu mnuOPtionBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionSavePassWord 
         Caption         =   "设置保存密码(&C)"
      End
      Begin VB.Menu mnuOptionSetAutoFuPang 
         Caption         =   "设置自动复盘时间(&T)"
      End
      Begin VB.Menu mnuOptionSetQiZhiChaiLiao 
         Caption         =   "设置棋子材料(&M)"
      End
      Begin VB.Menu mnuOptionWindowBack 
         Caption         =   "设置窗口背景(&B)"
      End
      Begin VB.Menu mnuOptionQiPangStyle 
         Caption         =   "设置棋盘样式(&S)"
      End
      Begin VB.Menu mnuOPtionBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionShowTime 
         Caption         =   "显示时间(&X)"
      End
      Begin VB.Menu mnuOptionStateBar 
         Caption         =   "显示状态栏(&Z)"
      End
      Begin VB.Menu mnuOptionShowTalk 
         Caption         =   "显示对话框"
      End
   End
   Begin VB.Menu mnuOptionNet 
      Caption         =   "网络选项(&N)"
      Begin VB.Menu mnuOptionNetClearTalkRecord 
         Caption         =   "清除对话记录"
      End
      Begin VB.Menu mnuOptionNetOpenTalkRecord 
         Caption         =   "打开对话记录"
      End
      Begin VB.Menu mnuOptionNetSaveTalkRecord 
         Caption         =   "保存对话记录"
      End
      Begin VB.Menu mnuOptionNetBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionNetTalkLocalColor 
         Caption         =   "设置本地记录颜色"
      End
      Begin VB.Menu mnuOptionNetTextTalkRemoteColor 
         Caption         =   "设置远端记录的颜色"
      End
      Begin VB.Menu mnuOptionNetTextTalkRemoteOrtherColor 
         Caption         =   "设置远端其它记录的颜色"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "帮助(&H)"
      Begin VB.Menu mnuHelpXinShiFenXiBiao 
         Caption         =   "形势分析表(&X)"
      End
      Begin VB.Menu mnuHelpBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "关于(&A)"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Type LOGFONT
        lfHeight As Long
        lfWidth As Long
        lfEscapement As Long
        lfOrientation As Long
        lfWeight As Long
        lfItalic As Byte
        lfUnderline As Byte
        lfStrikeOut As Byte
        lfCharSet As Byte
        lfOutPrecision As Byte
        lfClipPrecision As Byte
        lfQuality As Byte
        lfPitchAndFamily As Byte
        lfFaceName As String
End Type
Private Const SYMBOL_CHARSET = 2
Private Const ANSI_CHARSET = 0
Private Const OEM_CHARSET = 255
Private Const UNIQUE_NAME = &H0
Private Const PS_SOLID = 0
Private Declare Function CreateFontIndirect Lib "gdi32" Alias "CreateFontIndirectA" (lpLogFont As LOGFONT) As Long
Private Declare Function TextOut Lib "gdi32" Alias "TextOutA" (ByVal hDc As Long, ByVal X As Long, ByVal Y As Long, ByVal lpString As String, ByVal nCount As Long) As Long
Private Declare Function GetDC Lib "user32" (ByVal hwnd As Long) As Long
Private Declare Function CreatePen Lib "gdi32" (ByVal nPenStyle As Long, ByVal nWidth As Long, ByVal crColor As Long) As Long
Private Declare Function CreateSolidBrush Lib "gdi32" (ByVal crColor As Long) As Long
Private Declare Function Ellipse Lib "gdi32" (ByVal hDc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
Private Declare Function SelectObject Lib "gdi32" (ByVal hDc As Long, ByVal hObject As Long) As Long
Private Declare Function DeleteObject Lib "gdi32" (ByVal hObject As Long) As Long
Private Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Private Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long

Const Run = 0
Dim bFileAdd_Mi As Boolean '标志装入的文件是否是加密文件

Dim s对战模式 As String
Dim bXiaoQi As Boolean '标志是否走棋
Dim bFuPangEnd As Boolean '复盘结束标志
Dim bFuPang As Boolean '复盘标志
Dim lFuPang As Long '记录复盘的步数
Dim nAutoFuPangTime As Date   '自动复盘时间
Private Type Type_Time
        StartTime As Date '开始走棋的时间
        OneStartTime As Date '每走一步的时间
        TotalWalkTime As Date '每一方总共走的时间
        jTotalWalkTime As Date '甲总共走的时间
        yTotalWalkTime As Date '乙总共走的时间
        End Type
Dim tTime As Type_Time
Dim sQiPangStyleFileName As String '棋盘样式文件名
Dim IniFile As String '配置文件

'与网络有关的参数
Private Type Type_Net
        '远端记录的颜色
        NetTalkTextColorRemote As ColorConstants
        '远端记录的用户名
        NetTalkTextNameRemote As String
        '远端其它记录的颜色
        NetTalkTextColorRemoteOrther As ColorConstants
        '本地记录的颜色
        NetTalkTextColorLocal As ColorConstants
        '本地记录的用户名
        NetTalkUserNameLocal As String
        '要编辑的对话框
        NetEditText As RichTextBox
        '远端走棋
        NetRemoteWork As Boolean
        End Type
Dim tNet As Type_Net
Enum Enum_SetNetPara_Called
     网络设置中的默认调用
     被菜单中的网络对战调用
     在设置用户时调用
End Enum
Enum Enum_SendTalk
     发送默认值
     发送走棋
     发送对话
End Enum

Private Type Type_File_Hand
        AppTitle As String * 30 '程序的标题
        Major As Integer '主版本号
        Minor As Integer '次版本号
        Disger As String * 4 '设计者
        CompanyName  As String * 300 '公司名
        NoPassWordFlag As Boolean '是否有密码标志,只有当
                'PassWord=0,且此值为真时,且FileType为文本格式时
                '且MyPassWordm<>0,才没有设密码,
        FileType As Integer
        App_BiaoZhi As String * 10 '应用程序标识
        App_BiaoZhi_ID As Long '应用程序标识ID值
        PassWord As Double  '密码
        MyPassWord As Long '自己的密码
        bBuJu As Boolean '布局标识
        SheiZhou As Integer '布局时的走方,只能为定义甲方或定义已方
        End Type
Dim tFileHand As Type_File_Hand

Enum Enum_IniFile '用于ChangeIniFile函数，配置文件
     取出棋子材料
     写入更新棋子材料
     写入棋子材料用系统设置的
     取出棋盘样式
     写入棋盘样式
     取出窗口背景
     写入窗口背景
     取出自动复盘的时间
     写入自动复盘的时间
     取出对战方式
     写入对战方式之人人对战
     写入对战方式之人机对战
     写入对战方式之网络对战
     写入菜单中显示状态栏的状态
     取出菜单中显示状态栏的状态
     写入菜单中显示时间的状态
     取出菜单中显示时间的状态
     写入远端记录颜色
     取出远端记录颜色
     写入远端其它记录颜色
     取出远端其它记录颜色
     写入本地记录颜色
     取出本地记录颜色
     写入菜单中显示对话框的状态
     取出菜单中显示对话框的状态
End Enum

Enum Enum_File_Flag '用于文件处理的标志
     文本格式
     加密格式
     布局文本格式
     布局加密格式
End Enum
 
Enum Enum_PassWord_Flag
     把文件从加密格式转化为文本格式
     打开加密文件
     设置保存密码
End Enum

Private Enum Enum_SetUserName
        设置黑方用户名从Initally中调用
        设置用户标签位置
End Enum

Public Enum Enum_Windows_style '窗口2的作用
       形势分析表窗口
End Enum

'---------------------------------------------------------
Const s不再复盘而是继续下 = "你确定不再复盘,而是继续下吗？"
Const s保存文件出错 = "保存文件出错"
Const s打开文件出错 = "打开文件出错"
Const s保存文件 = "要保存这盘棋吗?"
Const s设置棋子的材料说明 = "棋子的材料为图标(.ICO)文件,用于做棋子。"
Const s设置棋子的材料说明1 = "        你要用自己的棋子材料吗？"
Const s设置棋子的材料说明2 = " 按否（&N)键，恢复系统默认棋子材料）。"
Const s打开棋子材料文件出错 = "打开的文件类型不对。"
Const s自动复盘提示 = "请在下面输入自动复盘时每步的间隔时间"
Const s自动复盘提示1 = "    (格式为hh:mm:ss,单位为:秒)。"
Const s自动复盘提示2 = "如果用是要设置为手动,请输入00:00:00。"
Const s复盘结束 = "复盘已经结束。"
Const s文件打开错误 = "文件打开错误"
Const s布局时不要的棋 = "布局时不要的棋,请放在此处。"
Const s布局先走方 = "                 选择先走方?"
Const s布局先走方1 = "如果先走方为甲方,请单击是(Y),是已方,请单击否(N)."
Const s帅不能移出棋盘 = "帅不能移出棋盘"
Const s修改对战模式 = "你要修改对战模式吗?"
Const s人机对战选择先走方 = "机器为甲方,如果机器先走,请按是(Y),否则按否(N)."
Const s人人对战谁先走 = "如果甲方先走,请按是(Y),否则按否(N)."
Const s中国象棋 = "中国象棋 "
Const s复盘 = " 复盘 "
Const s继续下 = " 继续下 "
Const s布局 = " 布局 "
Const s请输入对方地址 = "请输入对方地址:"
Const s是保留已有的记录 = "保留已有的记录?"
Const s请输入本地用户名 = "请输入本地用户名:"
Const s请输入远地用户名 = "请输入远地用户名:"
Const s是否先走 = "本地用户先走?"

Dim sX As Single, sY As Single '棋盘的起点
Dim sD As Long '棋盘间距
Dim qR As Single '棋子的半径
Dim qCol As ColorConstants '棋盘的颜色
Private Type Type_QiJu
        iQiJu As Integer
        oObject As Object
        End Type
Dim QiJu(9, 10) As Type_QiJu '棋局数组,用于记录当前棋局的形式
Dim BuJuQiJu(9, 10) As Enum_QiZhi     '在局棋局数组,用于记录布局的棋局
Dim QJ() As Integer '走棋数组,用于记录走棋

Private Type Type_QiZhiAttrib '棋子的属性,用于标志棋子的性质
        Color As ColorConstants
        Name As String '用户名
        sName As String '甲方或乙方
        End Type
Dim jF As Type_QiZhiAttrib
Dim yF As Type_QiZhiAttrib

Private Enum Enum_qStep '走棋步数的枚举标志
        定义甲方
        甲方走
        定义乙方
        乙方走
End Enum
Dim qStep As Enum_qStep  '走棋步数:该谁走,定义甲方,甲方走,定义已方,已方走
Dim ZouQiPangShu As Long '先走棋方

Private Type Type_qDefine '用于定义棋子时暂时存放定义的棋子和位置的结构
        oQiZhi As Object '存放定义的棋子
        QiZhi As Enum_QiZhi
        X As Single     '位置X
        Y As Single     '位置Y
        End Type
Dim qDefine  As Type_qDefine '用于定义棋子时暂时存放定义的棋子和位置

Private Enum Enum_Xin_Flag '棋盘上星位的枚举标志
        左
        右
        左和右
End Enum

Public Enum Enum_QiJu_eArrary_Flag '用于函数QiJu_eArrary,对棋局数组的操作
        给数组赋值
        从数组中取值
End Enum

Private Enum Enum_RecordQj_Flag '用于函数RecordQJ,对走棋数组的操作
        存入记录数组
        存入记录数组中的Pos位置
        从记录数组中取出
End Enum

Public Enum Enum_ZhouBiao_eTranslate_Flag '用于座标转换的标举标志
        把棋盘上的座标转换为棋局座标
        把棋局座标转换为棋盘上的座标
End Enum
Public Enum Enum_QZ '棋子的枚举量
        No = 0 '无子
        Che = 1 '车
        Ma = 2 '马
        Xiang = 3 '相
        Shi = 4  '士
        Shuai = 5 '帅
        Bing = 6 ' 兵
        Pao = 7 '炮
        jFan = 1 '甲方
        yFan = -1 '乙方
End Enum

Public Enum Enum_QiZhi
        NoZhi = No '无子
        '甲方
        jChe = Che '车
        jMa = Ma '马
        jXiang = Xiang '相
        jShi = Shi '士
        jShuai = Shuai '帅
        jBing = Bing ' 兵
        jPao = Pao '炮
        '乙方
        yChe = -Che
        yMa = -Ma
        yXiang = -Xiang
        yShi = -Shi
        yShuai = -Shuai
        yBing = -Bing
        yPao = -Pao
End Enum

'选择字体,作用:确定LOGFONT数组
'参数:Width为字体的宽,Height为字体的高(单位为像素),
'Angle为字体的角度(单位为度)
Private Function OptionFont(Width As Long, Height As Long, Optional Angle As Long = 0) As LOGFONT '选择字体
With OptionFont
     .lfCharSet = OEM_CHARSET
     .lfWeight = 700
     .lfWidth = PicQiPang.ScaleX(Width, VBRUN.ScaleModeConstants.vbTwips, VBRUN.ScaleModeConstants.vbPixels)
     .lfHeight = PicQiPang.ScaleX(Height, VBRUN.ScaleModeConstants.vbTwips, VBRUN.ScaleModeConstants.vbPixels)
     .lfEscapement = Angle * 10
     .lfFaceName = "宋体"
End With
End Function

'画棋盘
Private Sub Draw_QiPang()
On Error Resume Next
Dim I As Long, W As Integer
Dim NewFont As Long, OldFont As Long, Col As ColorConstants
Dim LF As LOGFONT
W = PicQiPang.DrawWidth
Col = PicQiPang.ForeColor
PicQiPang.ForeColor = qCol '棋盘线的颜色

'水平线
For I = 0 To 9
    If I = 0 Or I = 9 Then
       PicQiPang.DrawWidth = 4
    Else
       PicQiPang.DrawWidth = 3
    End If
    PicQiPang.Line (sX, sY + I * sD)-(sX + 8 * sD, sY + I * sD), qCol
Next I
'垂直线
For I = 0 To 8
    If I = 0 Or I = 8 Then
       PicQiPang.DrawWidth = 4
       PicQiPang.Line (sX + I * sD, sY)-(sX + I * sD, sY + 9 * sD), qCol
    Else
       PicQiPang.DrawWidth = 2
       PicQiPang.Line (sX + I * sD, sY)-(sX + I * sD, sY + 4 * sD), qCol
       PicQiPang.Line (sX + I * sD, sY + 5 * sD)-(sX + I * sD, sY + 9 * sD), qCol
    End If
Next I
'九宫
PicQiPang.DrawWidth = 2
PicQiPang.Line (sX + 3 * sD, sY)-(sX + 5 * sD, sY + 2 * sD), qCol
PicQiPang.Line (sX + 5 * sD, sY)-(sX + 3 * sD, sY + 2 * sD), qCol
PicQiPang.Line (sX + 3 * sD, sY * 8)-(sX + 5 * sD, sY + 9 * sD), qCol
PicQiPang.Line (sX + 5 * sD, sY * 8)-(sX + 3 * sD, sY + 9 * sD), qCol
'星位
For I = 1 To 3
    Xin sX + 2 * sD * I, sY + 3 * sD
    Xin sX + 2 * sD * I, sY + 6 * sD
Next
Xin sX + sD, sY + 2 * sD
Xin sX + 7 * sD, sY + 7 * sD
Xin sX + 7 * sD, sY + 2 * sD
Xin sX + sD, sY + 7 * sD
Xin sX, sY + 3 * sD, 右
Xin sX, sY + 6 * sD, 右
Xin sX + 8 * sD, sY + 3 * sD, 左
Xin sX + 8 * sD, sY + 6 * sD, 左
'写楚河汉界
LF = OptionFont(sD * 4 / 10, sD * 8 / 10, 270)
NewFont = CreateFontIndirect(LF)
OldFont = SelectObject(PicQiPang.hDc, NewFont)
PicQiPang.CurrentY = sY + sD * 4 + sD * 1.5 / 10
PicQiPang.CurrentX = sX + sD * 2
PicQiPang.Print "河"
PicQiPang.CurrentY = sY + sD * 4 + sD * 1.5 / 10
PicQiPang.CurrentX = sX + sD * 3
PicQiPang.Print "楚"
NewFont = SelectObject(PicQiPang.hDc, OldFont)
I = DeleteObject(NewFont)
LF = OptionFont(sD * 4 / 10, sD * 8 / 10, 90)
NewFont = CreateFontIndirect(LF)
OldFont = SelectObject(PicQiPang.hDc, NewFont)
PicQiPang.CurrentY = sY + sD * 5 - sD * 1.5 / 20
PicQiPang.CurrentX = sX + sD * 5
PicQiPang.Print "汉"
PicQiPang.CurrentY = sY + sD * 5 - sD * 1.5 / 20
PicQiPang.CurrentX = sX + sD * 6
PicQiPang.Print "界"
NewFont = SelectObject(PicQiPang.hDc, OldFont)
I = DeleteObject(NewFont)
PicQiPang.DrawWidth = W
PicQiPang.ForeColor = Col
End Sub

'画棋盘上的星位
Private Sub Xin(X As Single, Y As Single, Optional Flag As Enum_Xin_Flag = 左和右)
Dim L As Single, L1 As Single, L2 As Single
L1 = sD / 10
L = sD / 2 - L1
'左
If Flag = 左 Or Flag = 左和右 Then
   PicQiPang.Line (X - L1, Y - L)-(X - L1, Y - L1), qCol '  |
   PicQiPang.Line (X - L, Y - L1)-(X - L1, Y - L1), qCol ' --
   PicQiPang.Line (X - L, Y + L1)-(X - L1, Y + L1), qCol ' --
   PicQiPang.Line (X - L1, Y + L)-(X - L1, Y + L1), qCol '  |
End If
'右
If Flag = 右 Or Flag = 左和右 Then
   PicQiPang.Line (X + L1, Y - L)-(X + L1, Y - L1), qCol '  |
   PicQiPang.Line (X + L, Y - L1)-(X + L1, Y - L1), qCol '   --
   PicQiPang.Line (X + L, Y + L1)-(X + L1, Y + L1), qCol '   --
   PicQiPang.Line (X + L1, Y + L)-(X + L1, Y + L1), qCol '  |
End If
End Sub

'设置棋子的位置
Private Sub SetPos(ByVal X As Single, ByVal Y As Single, QiZhi As Object)
Dim I As Integer, j As Integer
ZhouBiao_eTranslate X, Y, I, j '座标转换
With QiZhi
     .Visible = False
     ZhouBiao_eTranslate X, Y, I, j, 把棋局座标转换为棋盘上的座标
     .Top = Y - .Height / 2
     .Left = X - .Width / 2
     '.Top = sY + sD * J - .Height / 2
     '.Left = sX + sD * I - .Width / 2
     .Visible = True
End With
End Sub

'对棋局数组的操作:向数组赋值;从数组中取值
'返回值:向数组赋值无返回值;从数组中取值,返回棋子的标志值
Public Function QiJu_eArrary(X As Single, Y As Single, Optional QiZhi As Enum_QiZhi, Optional Flag As Enum_QiJu_eArrary_Flag = 从数组中取值, Optional Object As Object = Nothing) As Integer
Dim I As Integer, j As Integer
ZhouBiao_eTranslate X, Y, I, j '座标转换
'转换为数组
If Flag = 给数组赋值 Then
   With QiJu(I, j)
        .iQiJu = QiZhi
        Set .oObject = Object
   End With
End If
If Flag = 从数组中取值 Then
   QiJu_eArrary = QiJu(I, j).iQiJu
   Set Object = QiJu(I, j).oObject
End If
End Function

'座标转换:把棋盘上的座标转换为棋局座标
Public Sub ZhouBiao_eTranslate(X As Single, Y As Single, I As Integer, j As Integer, Optional Flag As Enum_ZhouBiao_eTranslate_Flag = 把棋盘上的座标转换为棋局座标)
Select Case Flag
       Case 把棋盘上的座标转换为棋局座标
            I = (X - sX) \ sD
            If I < 0 Then I = 0
            If (X - sX) - I * sD > qR Then I = I + 1
            If I > 8 Then I = 8
            j = (Y - sY) \ sD
            If j < 0 Then j = 0
            If (Y - sY) - j * sD > qR Then j = j + 1
            If j > 9 Then j = 9
            I = I + 1
            j = j + 1
       Case 把棋局座标转换为棋盘上的座标
            Y = sY + sD * (j - 1)
            X = sX + sD * (I - 1)
End Select
End Sub

'生成棋子:完成以下4步:生成新控件,装入棋子图片
'         放在设置的位置(X,Y),并修改棋局数组
Private Sub Make_QiZhi(X As Single, Y As Single, QiZhi As Enum_QiZhi)
Dim hPen As Long, hBrush As Long, hDc As Long
Dim hFont As Long, hOld As Long
Dim hPic As New StdPicture, tFont As LOGFONT
Dim W As Long, H As Single
Dim S As String

If QiZhi <> NoZhi Then
   '1.新装载棋子控件
   Load QZ(QZ.UBound + 1)
   With QZ(QZ.UBound)
     .Tag = QiZhi '标识控件为什么棋,
          '用在布局上,即函数 _
          'PicNoQi_DragDrop和PicQiPang_DragDrop
     .Width = 2 * qR
     .Height = .Width
     .Stretch = True
     .DragMode = vbManual
      '2.画棋子,即装入棋子图片
      Set .Picture = Draw_QiZhi(QiZhi)
     .Visible = True
   End With
   '3.设置棋子的位置
   SetPos X, Y, QZ(QZ.UBound)
   '4.给棋局数组赋值(带控件)
   QiJu_eArrary X, Y, QiZhi, 给数组赋值, QZ(QZ.UBound)
Else '4.从棋局数组中赋值(不带控件)
   QiJu_eArrary X, Y, QiZhi, 给数组赋值
End If
End Sub

'画棋子,即装入棋子图片
'棋子图片是由两张图片(棋子的材料图片和棋子的字图片)叠加而成的
Private Function Draw_QiZhi(QiZhi As Enum_QiZhi) As IPictureDisp
On Error Resume Next
Dim S As String, oPic As New StdPicture, K As String
   '确定棋子的字图片
   Select Case QiZhi
          Case jChe
               'If Run Then
               '   s = "红车"
               'Else
                  S = "车"
               'End If
               K = "r"
          Case yChe
               S = "车"
               K = "b"
          Case jMa
               'If Run Then
               '   s = "红马"
               'Else
                  S = "马"
               'End If
               K = "r"
          Case yMa
               S = "马": K = "b"
          Case jXiang
               S = "象": K = "r"
          Case yXiang
               S = "象": K = "b"
          Case jShi
               S = "士": K = "r"
          Case yShi
               S = "士": K = "b"
          Case jShuai
               S = "将": K = "r"
          Case yShuai
               S = "将": K = "b"
          Case jBing
               S = "卒": K = "r"
          Case yBing
               S = "卒": K = "b"
          Case jPao
               'If Run Then
               '   s = "红炮"
               'Else
                  S = "炮"
               'End If
               K = "r"
          Case yPao
               S = "炮": K = "b"
   End Select
   With ImgList
        Set Draw_QiZhi = .Overlay("add", S) '用用户设置的棋子材料图片
        If Err.Number Then '用自带的棋子材料图片
           Set Draw_QiZhi = .Overlay(K, S)
        End If
   End With
End Function

'布子
Private Sub PutDown()
Dim I As Integer
'If QZ.Count > 1 Then
'   For I = 1 To QZ.UBound
'       Unload QZ(I)
'   Next I
'End If
Make_QiZhi sX, sY, jChe
Make_QiZhi sX + sD, sY, jMa
Make_QiZhi sX + 2 * sD, sY, jXiang
Make_QiZhi sX + sD * 3, sY, jShi
Make_QiZhi sX + sD * 4, sY, jShuai
Make_QiZhi sX + sD * 5, sY, jShi
Make_QiZhi sX + sD * 6, sY, jXiang
Make_QiZhi sX + sD * 7, sY, jMa
Make_QiZhi sX + sD * 8, sY, jChe
Make_QiZhi sX + sD, sY + sD * 2, jPao
Make_QiZhi sX + sD * 7, sY + sD * 2, jPao
For I = 0 To 8 Step 2
    Make_QiZhi sX + sD * I, sY + sD * 3, jBing
Next I

Make_QiZhi sX, sY + sD * 9, yChe
Make_QiZhi sX + sD, sY + sD * 9, yMa
Make_QiZhi sX + 2 * sD, sY + sD * 9, yXiang
Make_QiZhi sX + sD * 3, sY + sD * 9, yShi
Make_QiZhi sX + sD * 4, sY + sD * 9, yShuai
Make_QiZhi sX + sD * 5, sY + sD * 9, yShi
Make_QiZhi sX + sD * 6, sY + sD * 9, yXiang
Make_QiZhi sX + sD * 7, sY + sD * 9, yMa
Make_QiZhi sX + sD * 8, sY + sD * 9, yChe
Make_QiZhi sX + sD, sY + sD * 7, yPao
Make_QiZhi sX + sD * 7, sY + sD * 7, yPao
For I = 0 To 8 Step 2
    Make_QiZhi sX + sD * I, sY + sD * 6, yBing
Next I
End Sub

'初始化,分5步,这5步的位置不能改变.
Private Sub Initally()
'On Error Resume Next
Dim I As Long, Ctr As Object

'1.设置初始常量
Erase QiJu '(9, 10) '置空数组
ReDim QJ(0)

Me.Caption = s中国象棋 & "-" & s对战模式
bXiaoQi = False '下棋标志
mnuFileBuJu.Checked = False '重置布局选项
tFileHand.bBuJu = False
bFileAdd_Mi = False
bFuPangEnd = False '复盘结束标志
Set qDefine.oQiZhi = Nothing
tFileHand.SheiZhou = qStep
SetUserName '设置各方的用户名称
For Each Ctr In QZ
    If Not Ctr Is QZ(0) Then
       Unload Ctr
    End If
Next
QZ(0).Visible = False
PicQiPang.Cls

'2.确定棋盘参数
With PicQiPang
     sX = (Me.ScaleHeight - LabJF.Height - LabYF.Height) / 15
     .Top = 2 * sX
     .Height = Me.ScaleHeight - 4 * sX
     .Width = sX * 11
     .Left = (Me.ScaleWidth - .Width) / 2
     SetUserName 设置用户标签位置
     sX = PicQiPang.ScaleHeight / 11
     sD = sX
     sY = sX
     qR = sD * 9 / 20  '棋子的半径
End With
qCol = vbRed '设置棋盘的颜色
'3.设置棋盘样式,画棋盘
If sQiPangStyleFileName <> "" Then
   LoadQiPangStyle sQiPangStyleFileName
Else
   Draw_QiPang '画棋盘
End If
'4.布子
PutDown

'5.初始化界面
InitallyInterface

'6.人机对战时,机器先走标识
If mnuFileManAndMachine.Checked Then
   MachineWalk
End If
'7.提示
Call Tishi
End Sub

'初始化界面
Private Sub InitallyInterface()
'1.初始化状态条
With StatBar
     .Panels.Clear
     .Panels.Add , "j", "红方:"
     .Panels("j").Bevel = sbrRaised
     .Panels("j").Alignment = sbrCenter
     .Panels.Add , "jtext", jF.Name
     .Panels.Item(.Panels.Count).AutoSize = sbrContents
     .Panels.Add , "y", "黑方:"
     .Panels("y").Bevel = sbrRaised
     .Panels("y").Alignment = sbrCenter
     .Panels.Add , "ytext", yF.Name
     .Panels.Add , , "第 " & ZouQiPangShu & " 盘"
     .Panels.Item(.Panels.Count).AutoSize = sbrContents
     .Panels.Add , "t", "时间:"
     .Panels.Item(.Panels.Count).AutoSize = sbrContents
     .Panels("t").Bevel = sbrRaised
     .Panels("t").Alignment = sbrCenter
     .Panels.Add , "to"
     .Panels("to").Style = sbrTime
     .Visible = mnuOptionStateBar.Checked
End With
Tim.Interval = 360
'2.提示
With tTime '提示中的时间
     .StartTime = Time
     .jTotalWalkTime = 0
     .OneStartTime = Time
     .TotalWalkTime = 0
     .yTotalWalkTime = 0
End With
TxtHadTime = ""
TxtHadTime.Enabled = False
TxtTotalTime = ""
TxtTotalTime.Enabled = False
TxtTime.Enabled = False
TxtTime.Text = ""
With FraTime
     .Left = (FraTiShi.Width - .Width) / 2
End With
With FraTiShi '提示控件
     '.Top = PicQiPang.Top
     .Left = 0
     .Caption = ""
End With
With TiShiQZ '提示中的样棋
     .Width = 2 * qR
     .Height = .Width
     .Left = (FraTiShi.Width - .Width) / 2
     LabTiShi.Top = .Top + .Height + 100
     LabTiShi.Left = (FraTiShi.Width - LabTiShi.Width) / 2
End With
'3.设置复盘工具
bFuPang = False '复盘标志
lFuPang = 0 '复盘步数
With Fraredo '复盘工具
     .Caption = ""
End With
Set_Fupang_eTool '设置复盘工具
'设置网络通讯工具
If s对战模式 = " 网络对战 " Then
   SetNetPara , 被菜单中的网络对战调用
Else
   SetNetPara False, 被菜单中的网络对战调用
End If

'4.设置棋盘上的两个提示框
With ShpTSD '提示框
     .Visible = False
     .Width = sD
     .Height = sD
End With
With ShpTSW
     .Visible = False
     .Width = sD
     .Height = sD
End With
With ShpCur '光标
     .Top = sX + sD * 4 - sD / 2
     .Left = sY + 4 * sD - sD / 2
     .Width = sD
     .Height = sD
     If mnuFileManAndMan.Checked Then
        .Visible = True
     Else
        .Visible = False
     End If
End With
fNoQi '初始化布局移出子收集容器
End Sub

'布局移出子收集容器
Private Sub fNoQi()
With PicNoQi
     .Cls
     .Top = PicQiPang.Top
     .Height = PicQiPang.Height
     .AutoRedraw = True
     If Not Run Then
        .Visible = True
        .Left = PicQiPang.Left + PicQiPang.Width
        .Width = Me.ScaleWidth - PicQiPang.Left - PicQiPang.Width
     Else
        PicNoQi.ForeColor = vbRed
        PicNoQi.Print s布局时不要的棋
        .Left = 0
        .Width = PicQiPang.Left
     End If
End With
If Not Run Then
     Dim I As Integer, j As Integer
     For j = 0 To 10
         For I = 0 To 9
             PicNoQi.ForeColor = vbBlack
             PicNoQi.Print QiJu(I, j).iQiJu;
         Next
         PicNoQi.Print
     Next
End If
If mnuFileBuJu.Checked Then
   PicNoQi.Visible = True
ElseIf Run Then
   PicNoQi.Visible = False
End If
End Sub

'设置复盘工具,当是复盘时显示复盘工具,
'否则,当为网战时显示网络工具
Private Sub Set_Fupang_eTool()
'复盘工具的位置
Fraredo.Top = PicQiPang.Top + PicQiPang.Height / 2 - Fraredo.Height / 2
Fraredo.Left = 0
If bFuPang Then '复盘工具
   CmdPre.Caption = "上一步(&P)"
   CmdNext.Caption = "下一步(&N)"
   CmdCanel.Caption = "取消"
   Fraredo.Visible = True
ElseIf mnuFileNet.Checked Then '网络工具
   CmdPre.Caption = "认输(&S)"
   CmdNext.Caption = "求和(&P)"
   CmdCanel.Caption = "取消"
   Fraredo.Visible = True
Else
   Fraredo.Visible = False
End If
End Sub

Private Sub cmdCanel_Click() '复盘中的取消
Dim exi As Integer
If bFuPang Then
      exi = MsgBox(s不再复盘而是继续下, vbYesNo + vbQuestion)
      If exi = vbYes Then
         bFuPang = False
         Set_Fupang_eTool
         ReDim Preserve QJ(lFuPang)
      Else
         Exit Sub
      End If
Else ''是网络工具时

End If
End Sub

Private Sub cmdNext_Click() '复盘中的下一步
If Run Then On Error Resume Next
Dim X As Single, Y As Single, QiZhi As Enum_QiZhi
Dim Obj As Object

If bFuPang Then
   If lFuPang < UBound(QJ) Then
      RecordQJ X, Y, QiZhi, 从记录数组中取出
      If Walk(X, Y) Then '减去多增加的
         ReDim Preserve QJ(UBound(QJ) - 1)
      End If
   Else
      If Not bFuPangEnd Then
         MsgBox s复盘结束
         bFuPangEnd = True
      End If
   End If
ElseIf mnuFileNet.Checked Then '是网络工具时

End If
End Sub

Private Sub cmdPre_Click() '复盘中的上一步
Dim X As Single, Y As Single, QiZhi As Enum_QiZhi
Dim XX As Single, YY As Single, Obj As Object
If bFuPang Then
   If lFuPang < 1 Then
      Beep
   Else
      bFuPangEnd = False
      lFuPang = lFuPang - 1
      Select Case qStep
             Case Enum_qStep.定义甲方, Enum_qStep.定义乙方
                  '取出被吃子和位置
                  RecordQJ X, Y, QiZhi, 从记录数组中取出
                  'XX = X: YY = Y
                  '取出定义位置上的子和位置,
                  With qDefine '恢复暂存结构
                       RecordQJ .X, .Y, .QiZhi, 从记录数组中取出, lFuPang - 1
                       '恢复定义位置上的子
                       QiJu_eArrary .X, .Y, QiJu_eArrary(X, Y, , , Obj), 给数组赋值, Obj
                       SetPos .X, .Y, Obj
                       XX = .X: YY = .Y
                       Set .oQiZhi = Obj
                  End With
                  '恢复被子吃子
                  Make_QiZhi X, Y, QiZhi
                  With ShpTSD '棋盘上的提示框
                       .Left = XX - .Width / 2
                       .Top = YY - .Height / 2
                       .Visible = True
                  End With
                  With ShpTSW
                       .Left = X - .Width / 2
                       .Top = Y - .Height / 2
                       .Visible = True
                  End With
                  If qStep = 定义甲方 Then
                     qStep = 乙方走
                  Else
                     qStep = 甲方走
                  End If
             Case Enum_qStep.甲方走, Enum_qStep.乙方走
                  RecordQJ X, Y, , 从记录数组中取出
                  With qDefine
                       RecordQJ .X, .Y, .QiZhi, 从记录数组中取出, lFuPang
                  End With
                  With ShpTSD '棋盘上的提示框
                       .Left = X - .Width / 2
                       .Top = Y - .Height / 2
                       .Visible = True
                  End With
                  ShpTSW.Visible = False
                  If qStep = 甲方走 Then
                     qStep = 定义甲方
                  Else
                     qStep = 定义乙方
                  End If
      End Select
      lFuPang = lFuPang - 1
      Tishi
   End If
ElseIf mnuFileNet.Checked Then '是网络工具时

End If
End Sub

Private Sub Form_Load()
PicQiPang.AutoRedraw = True
Me.ScaleMode = vbTwips
PicQiPang.ScaleMode = Me.ScaleMode
Me.Width = Screen.Width
Me.Height = Screen.Height

'初始化与网络有关的参数
With txtNetTalk
     .Locked = True
     .Visible = False
     .Text = ""
End With
With txtNetInput
     .Text = ""
     .Visible = False
End With

'保存一些关于的文件参数
With tFileHand
     .App_BiaoZhi = "中国象棋"  '应用程序标识
     .App_BiaoZhi_ID = 19760121  '应用程序标识ID值
     .MyPassWord = 19780201
     .Major = App.Major
     .Minor = App.Minor
End With

'设置提示控件的高
FraTiShi.Height = FraTiShi.Height - FraTime.Height

IniFile = App.Path + "\象棋设置.ini"

ChangeIniFile 取出对战方式
ChangeIniFile 取出棋子材料
ChangeIniFile 取出棋盘样式
ChangeIniFile 取出自动复盘的时间
ChangeIniFile 取出窗口背景
ChangeIniFile 取出本地记录颜色
ChangeIniFile 取出远端记录颜色
ChangeIniFile 取出远端其它记录颜色

Initally  '进行初始化

ChangeIniFile 取出菜单中显示时间的状态
ChangeIniFile 取出菜单中显示状态栏的状态
ChangeIniFile 写入菜单中显示对话框的状态

End Sub

'以上的为初始化过程
'===============================================================

Private Sub Form_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = vbRightButton Then
   PopupMenu mnuFile '快捷菜单
End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
Dim exi  As Integer
If bXiaoQi Then
   exi = MsgBox(s保存文件, vbQuestion + vbYesNoCancel)
   If exi = vbYes Then
      With CMD
          .FileName = ""
          .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + cdlOFNExtensionDifferent
          .Filter = "*.xq|*.xq|*.*|*.*"
          .DialogTitle = "保存为"
          .ShowSave
          If .FileName <> "" Then
             SaveFile .FileName
          End If
      End With
    ElseIf exi = vbCancel Then
      Cancel = exi
    End If
End If
End Sub

Private Sub FraTime_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = vbRightButton Then
   PopupMenu mnuOption
End If
End Sub

Private Sub FraTishi_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = vbRightButton Then
   PopupMenu mnuOption
End If
End Sub

Private Sub Label1_MouseUp(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = vbRightButton Then
   PopupMenu mnuOption
End If
End Sub

Private Sub labTIshi_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = vbRightButton Then
   PopupMenu mnuOption
End If
End Sub

'下面的为菜单
'----------------------------------------------------
Private Sub mnuFileBuJu_Click()
Dim Ctr As Image, I As Integer, j As Integer
Dim exi As Integer
With mnuFileBuJu
     If bXiaoQi Then
        .Checked = False
     Else
        .Checked = (Not .Checked)
     End If
     If .Checked Then
        Me.Caption = s中国象棋 & "-" & s对战模式 & "-" & s布局
        For Each Ctr In QZ
            Ctr.DragMode = vbAutomatic
        Next Ctr
     Else
        If tFileHand.bBuJu Then 'tFileHand.bBuJu在PicQiPang_DragDrop中定义
           exi = MsgBox(s布局先走方 + Chr(13) + s布局先走方1, vbQuestion + vbYesNo)
           If exi = vbYes Then
              qStep = 定义甲方
              tFileHand.SheiZhou = qStep
           Else
              qStep = 定义乙方
              tFileHand.SheiZhou = qStep
           End If
           Tishi
           For I = 1 To 9
               For j = 1 To 10
                   BuJuQiJu(I, j) = QiJu(I, j).iQiJu
               Next j
           Next I
        End If
        For Each Ctr In QZ
            Ctr.DragMode = vbManual
        Next Ctr
        Me.Caption = s中国象棋 & "-" & s对战模式
     End If
End With
Call fNoQi
End Sub

Private Sub mnuFileExit_Click() '退出
Unload Me
End Sub

Private Sub mnuEdit_Click()
If tNet.NetEditText Is Nothing Then
   mnuEditCopy.Enabled = False
   mnuEditCut.Enabled = False
   mnuEditPase.Enabled = False
Else
   If tNet.NetEditText.SelText = "" Then
      mnuEditCopy.Enabled = False
      mnuEditCut.Enabled = False
   Else
      mnuEditCopy.Enabled = True
      If tNet.NetEditText <> txtNetTalk Then
         mnuEditCut.Enabled = True
      Else
         mnuEditCut.Enabled = False
      End If
   End If
   If Clipboard.GetText = "" Then
      mnuEditPase.Enabled = False
   ElseIf tNet.NetEditText <> txtNetTalk Then
      mnuEditPase.Enabled = True
   Else
      mnuEditPase.Enabled = False
   End If
End If
End Sub

Private Sub mnuEditCopy_Click()
Clipboard.SetText tNet.NetEditText.SelText
End Sub

Private Sub mnuEditCut_Click()
Clipboard.SetText tNet.NetEditText.SelText
tNet.NetEditText.SelText = ""
End Sub

Private Sub mnuEditPase_Click()
If Not tNet.NetEditText Is Nothing Then
   tNet.NetEditText.SelText = Clipboard.GetText
End If
End Sub

'修改对战模式
Private Function Modify_DuaiZhang_eMode(Mode As String) As Boolean
If MsgBox(s修改对战模式, vbQuestion + vbYesNo) = vbYes Then
   ZouQiPangShu = 0
   If mnuFileManAndMachine.Checked Then mnuFileManAndMachine.Checked = False
   If mnuFileManAndMan.Checked Then mnuFileManAndMan.Checked = False: ShpCur.Visible = False
   If mnuFileNet.Checked Then mnuFileNet.Checked = False
   '下面两句的顺序不能调换
   s对战模式 = Mode
   mnuFileReStart_Click
   Modify_DuaiZhang_eMode = True
Else
   Modify_DuaiZhang_eMode = False
End If
End Function

'人机对战
Private Sub mnuFileManAndMachine_Click()
With mnuFileManAndMachine
    If Not .Checked Then
       If Modify_DuaiZhang_eMode(" 人机对战 ") Then
         .Checked = Not .Checked
         ChangeIniFile 写入对战方式之人机对战
         If MsgBox(s人机对战选择先走方, vbQuestion + vbYesNo) = vbYes Then
            '机器先走
            qStep = 定义甲方
            jF.Name = "机器"
            MachineWalk
         Else
            '人先走
            qStep = 定义乙方
         End If
         Call Tishi
       End If
    End If
End With
End Sub

'人人对战
Private Sub mnuFileManAndMan_Click()
With mnuFileManAndMan
    If Not .Checked Then
      If Modify_DuaiZhang_eMode(" 人人对战 ") Then
         .Checked = Not .Checked
         ChangeIniFile 写入对战方式之人人对战
         If MsgBox(s人人对战谁先走, vbQuestion + vbYesNo) = vbYes Then
            qStep = 定义甲方
         Else
            qStep = 定义乙方
         End If
         ShpCur.Visible = True
         Call Tishi
      End If
    End If
End With
End Sub

'网络对战
'其中网络工具的设置在 Modify_DuaiZhang_eMode(" 网络对战 ") 中完成
Private Sub mnuFileNet_Click()
With mnuFileNet
  If Not .Checked Then
     If Modify_DuaiZhang_eMode(" 网络对战 ") Then
       .Checked = Not .Checked
        ChangeIniFile 写入对战方式之网络对战
        Set_Fupang_eTool
     End If
  End If
End With
End Sub

'复盘
Private Sub mnuFileOpen_Click()
If bXiaoQi Then
   mnuFileReStart_Click
End If
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames
     .DialogTitle = "打开"
     .Filter = "中国象棋文件(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
     .ShowOpen
     If .FileName <> "" Then
        Initally '初始化棋盘
        If OpenFile(.FileName) Then
           With tTime '重设时间
                .TotalWalkTime = 0
                .jTotalWalkTime = 0
                .yTotalWalkTime = 0
           End With
           If tFileHand.bBuJu Then '布局复盘
              BuJuFuPang
           End If
           bFuPang = True '设置复盘标志
           Set_Fupang_eTool ' 设置复盘工具
           Me.Caption = s中国象棋 & "-" & s复盘 & "-" & " [" & .FileName & "]"
        End If
     End If
End With
End Sub

'继续下
Private Sub mnuFileContine_Click()
If bXiaoQi Then
   mnuFileReStart_Click
End If
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames
     .DialogTitle = "打开上一盘棋"
     .Filter = "中国象棋文件(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
     .ShowOpen
     If .FileName <> "" Then
        Initally
        If OpenFile(.FileName) Then
           Me.Caption = s中国象棋 & "-" & s对战模式 & "-" & s继续下 & "- {" & .FileName & "}"
           bFuPang = True
           If tFileHand.bBuJu Then '布局复盘
              BuJuFuPang
           End If
           While lFuPang < UBound(QJ)
              cmdNext_Click
           Wend
           bFuPang = False
        End If
     End If
End With
End Sub

'重新开始
Public Sub mnuFileReStart_Click()
Dim exi  As Integer
If bXiaoQi Then
   exi = MsgBox(s保存文件, vbQuestion + vbYesNoCancel)
   If exi = vbYes Then
      With CMD
          .FileName = ""
          .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + cdlOFNExtensionDifferent
          .Filter = "中国象棋(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
          .DialogTitle = "保存为"
          .ShowSave
           If .FileName <> "" Then
              SaveFile .FileName
           End If
      End With
   ElseIf exi = vbCancel Then
      Exit Sub
   End If
End If
Call Initally '初始化
End Sub

'保存文件
Private Sub mnuFileSave_Click()
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNExtensionDifferent
     .Filter = "中国象棋文件(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
     .DialogTitle = "保存"
     .ShowSave
     If .FileName <> "" Then
        SaveFile .FileName
        bXiaoQi = False
     End If
End With
End Sub

Private Sub mnuHelpXinShiFenXiBiao_Click()
Dim I As Integer, j As Integer, iQiJu(9, 10) As Integer
For I = 1 To 9
    For j = 1 To 10
        iQiJu(I, j) = QiJu(I, j).iQiJu
    Next j
Next I
Form2.WindowsCommand 形势分析表窗口, iQiJu
End Sub

'清除对话记录
Private Sub mnuOptionNetClearTalkRecord_Click()
txtNetTalk.Text = ""
End Sub

Private Sub mnuOptionNetOpenTalkRecord_Click()
'打开对话记录
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNExtensionDifferent
     .Filter = "对话记录文件(*.tal)|*.tal|*.*|*.*"
     .DialogTitle = "打开对话记录"
     .ShowOpen
     If .FileName <> "" Then
        If Len(txtNetTalk.Text) Then
           If MsgBox(s是保留已有的记录, vbQuestion + vbYesNo) = vbYes Then
              Dim S As String
              With txtNetInput
                   S = .Text
                   .Visible = False
                   .LoadFile CMD.FileName
                   txtNetTalk.SelText = .Text
                   .Text = S
                   .Visible = True
              End With
           Else
              txtNetTalk.LoadFile .FileName
              txtNetTalk.SelStart = Len(txtNetTalk.Text)
           End If
        Else
           txtNetTalk.LoadFile .FileName
           txtNetTalk.SelStart = Len(txtNetTalk.Text)
        End If
     End If
     Call ChangeRichTextColor
End With
End Sub

Private Sub mnuOptionNetSaveTalkRecord_Click()
'保存对话记录
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNExtensionDifferent
     .Filter = "对话记录文件(*.tal)|*.tal|*.*|*.*"
     .DialogTitle = "保存对话记录"
     .ShowSave
     If .FileName <> "" Then
        txtNetTalk.SaveFile .FileName
     End If
End With
End Sub

'设置本地记录颜色
Private Sub mnuOptionNetTalkLocalColor_Click()
With CMD
     .DialogTitle = "选择本地记录颜色"
     .Flags = mscomdlg.ColorConstants.cdlCCRGBInit
     .Color = tNet.NetTalkTextColorLocal
     .ShowColor
     tNet.NetTalkTextColorLocal = .Color
    ChangeIniFile 写入本地记录颜色, , .Color
    Call ChangeRichTextColor
End With
End Sub

'设置远地记录颜色
Private Sub mnuOptionNetTextTalkRemoteColor_Click()
With CMD
     .DialogTitle = "选择远地记录颜色"
     .Flags = mscomdlg.ColorConstants.cdlCCRGBInit
     .Color = tNet.NetTalkTextColorRemote
     .ShowColor
     tNet.NetTalkTextColorRemote = .Color
    ChangeIniFile 写入远端记录颜色, , .Color
    Call ChangeRichTextColor
End With
End Sub

Private Sub mnuOptionNetTextTalkRemoteOrtherColor_Click()
With CMD
     .DialogTitle = "选择远地其它记录颜色"
     .Flags = mscomdlg.ColorConstants.cdlCCRGBInit
     .Color = tNet.NetTalkTextColorRemoteOrther
     .ShowColor
     tNet.NetTalkTextColorRemoteOrther = .Color
     ChangeIniFile 写入远端其它记录颜色, , .Color
     Call ChangeRichTextColor
End With
End Sub

Private Sub mnuOptionSavePassWord_Click()
PassWord 设置保存密码
End Sub

'设置自动复盘
Private Sub mnuOptionSetAutoFuPang_Click()
Dim S As String
S = InputBox(s自动复盘提示 + Chr(13) + s自动复盘提示1 + Chr(13) + s自动复盘提示2, , CStr(nAutoFuPangTime))
If S <> "" Then
   nAutoFuPangTime = CDate(S)
   ChangeIniFile 写入自动复盘的时间, S
End If
End Sub

'设置棋子材料
Private Sub mnuOptionSetQiZhiChaiLiao_Click()
On Error Resume Next
Dim exi As Long, Ctr As Image
exi = MsgBox(s设置棋子的材料说明 + Chr(13) + s设置棋子的材料说明1 + Chr(13) + s设置棋子的材料说明2, vbQuestion + vbYesNoCancel)
If exi = vbYes Then
      With CMD
          .FileName = ""
          .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNExtensionDifferent
          .Filter = "棋子材料文件(*.ico)|*.ico"
          .DialogTitle = "打开棋子材料文件"
          .ShowSave
           If .FileName <> "" Then
              ImgList.ListImages.Add , "add", LoadPicture(.FileName)
              If Err.Number = 35602 Then
                 ImgList.ListImages.Remove ("add")
                 ImgList.ListImages.Add , "add", LoadPicture(.FileName)
              ElseIf Err.Number Then
                 GoTo mnuOptionSetQiZiChaiLiaoError
              End If
              ChangeIniFile 写入更新棋子材料, .FileName
           End If
      End With
ElseIf exi = vbNo Then
      ImgList.ListImages.Remove ("add")
      ChangeIniFile 写入棋子材料用系统设置的
ElseIf exi = vbCancel Then
    Exit Sub
End If
'更新棋子
For Each Ctr In QZ
    Set Ctr.Picture = Draw_QiZhi(Ctr.Tag)
Next Ctr
Exit Sub
mnuOptionSetQiZiChaiLiaoError:
If Not Err.Number = 35601 Then
   MsgBox s打开棋子材料文件出错
End If
End Sub

Private Sub mnuOptionShowTalk_Click()
With mnuOptionShowTalk
     .Checked = Not .Checked
     SetNetPara .Checked
     ChangeIniFile 写入菜单中显示对话框的状态, .Checked
End With
End Sub

'设置窗口背景
Private Sub mnuOptionWindowBack_Click()
On Error GoTo mnuOptionWindowBackError
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNExtensionDifferent
     .Filter = "棋子材料文件(*.bmp;*.jpg)|*.ico;*.jpg"
     .DialogTitle = "打开窗口背景..."
     .ShowOpen
     If .FileName <> "" Then Me.Picture = LoadPicture(.FileName)
     ChangeIniFile 写入窗口背景, .FileName
End With
Exit Sub
mnuOptionWindowBackError:
MsgBox s打开文件出错
End Sub

'设置棋盘样式
Private Sub mnuOptionQiPangStyle_Click()
With CMD
     .DialogTitle = "设置棋盘样式..."
     .FileName = ""
     .Filter = "棋盘样式文件(*.bmp;*.ico;*.cur)|*.bmp;*.ico;*.cur|*.*|*.*"
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNExtensionDifferent
     .ShowOpen
     If .FileName <> "" Then
        LoadQiPangStyle .FileName
        ChangeIniFile 写入棋盘样式, .FileName
     End If
End With
End Sub


'显示时间
Private Sub mnuOPtionShowTime_Click()
If Run Then On Error Resume Next
With mnuOptionShowTime
     .Checked = Not .Checked
     FraTime.Visible = .Checked
     Call ChangeIniFile(写入菜单中显示时间的状态, .Checked)
     If .Checked Then
        With FraTiShi
             .Height = .Height + FraTime.Height
             If .Top <> PicQiPang.Top Then
                .Top = .Top - FraTime.Height
             End If
        End With
     Else
        With FraTiShi
             .Height = .Height - FraTime.Height
             If .Top <> PicQiPang.Top Then
                .Top = .Top + FraTime.Height
             End If
        End With
     End If
End With
End Sub

'设置状态条
Private Sub mnuOptionStateBar_Click()
With mnuOptionStateBar
     .Checked = Not .Checked
     StatBar.Visible = .Checked
     Call ChangeIniFile(写入菜单中显示状态栏的状态, .Checked)
     Call ReSetPostion(.Checked, StatBar.Height)
End With
End Sub

'从文件中装入棋盘样式图片
Private Sub LoadQiPangStyle(FileName As String)
If Run Then On Error Resume Next
Dim Pic As StdPicture
        Set Pic = LoadPicture(FileName)
        PicQiPang.Cls
        PicQiPang.PaintPicture Pic, 0, 0 _
                    , PicQiPang.Width, PicQiPang.Height
        Draw_QiPang
        '把文件夹名放入变量中
        sQiPangStyleFileName = FileName
End Sub

'===========================================================================================
'以下的为走子
'-------------------------------------------------------------------------------------------
'人机对战时机器走棋
Private Function MachineWalk() As Integer
Dim I As Integer, j As Integer
Dim iQiJu(9, 10) As Integer
Screen.MousePointer = vbHourglass
Call Tishi
For I = 1 To 9
    For j = 1 To 10
        iQiJu(I, j) = QiJu(I, j).iQiJu
    Next j
Next I
'1.当机器为甲方时
If qStep = 定义甲方 Then
   '加走棋代码
   'XinShiFenXi iQiJu, Enum_QZ.jFan
   qStep = 定义乙方
   Screen.MousePointer = vbDefault
   Exit Function
End If
'2.当机器为乙方时
If qStep = 定义乙方 Then
   '加走棋代码
   'XinShiFenXi iQiJu, Enum_QZ.yFan
   qStep = 定义甲方
End If
Screen.MousePointer = vbDefault
End Function

'走子
Public Function Walk(X As Single, Y As Single, Optional Object As Object = Nothing) As Boolean
'走子分为四步:
'qStep=1为定义甲方,2为甲方走棋,3为定义乙方，4为乙方走棋
'只有当成功时qStep才能增加
'判断是否能走子或定义子
Dim Obj As Object
ReSetXY X, Y '重设置座标
If bPangDuangShiFoLengZhougZhi(X, Y, Object) Then '能走子或定义子
   RecordQJ X, Y '把当前位置的棋局存储到记录数组中
   Walk = True
   Select Case qStep
          Case Enum_qStep.定义甲方, Enum_qStep.定义乙方
               With qDefine
                    .QiZhi = QiJu_eArrary(X, Y, , , Obj)
                    Set .oQiZhi = Obj
                    .X = X
                    .Y = Y
               End With
               With ShpTSD
                    .Top = Y - .Height / 2
                    .Left = X - .Width / 2
                    .Visible = True
               End With
               ShpTSW.Visible = False
               If qStep = 定义甲方 Then
                  qStep = 甲方走
               Else
                  qStep = 乙方走
               End If
          Case Enum_qStep.甲方走, Enum_qStep.乙方走
               If Not (Object Is Nothing) Then '如果原位置有子则吃掉
                  Unload Object
               Else
                  QiJu_eArrary X, Y, , , Obj
                  If Not (Obj Is Nothing) Then
                     Unload Obj
                  End If
               End If
               '否则走子
               SetPos X, Y, qDefine.oQiZhi
               QiJu_eArrary X, Y, QiJu_eArrary(qDefine.X, qDefine.Y, , , Obj), 给数组赋值, Obj
               QiJu_eArrary qDefine.X, qDefine.Y, NoZhi, 给数组赋值
               With ShpTSW
                    .Top = Y - .Height / 2
                    .Left = X - .Width / 2
                    .Visible = True
               End With
               If qStep = 甲方走 Then
                  qStep = 定义乙方
               Else
                  qStep = 定义甲方
               End If
               '人机对战时机器走子
               If mnuFileManAndMachine.Checked Then
                  MachineWalk
               End If
   End Select
   If bJiaoJian Then '提示叫将
      bJiaoJian = False
      MsgBox s叫将, vbInformation
   End If
   If Not bFuPang Then bXiaoQi = True '置下棋标识
   Tishi X, Y, Object
   If Not Run Then fNoQi
Else '不能走子或定义子
   Walk = False
   Beep
   '人机对战时机器走子
   If mnuFileManAndMachine.Checked Then
      MachineWalk
   End If
End If
End Function

Private Sub ReSetXY(X As Single, Y As Single)
Dim I As Integer, j As Integer
ZhouBiao_eTranslate X, Y, I, j
X = sX + sD * (I - 1)
Y = sY + sD * (j - 1)
End Sub

'判断是否能走子或定义子
Private Function bPangDuangShiFoLengZhougZhi(X As Single, Y As Single, Object As Object) As Boolean
Dim Obj As Object
'把鼠标限制在棋盘内
If X < sX - qR Or Y < sY - qR Or X > sX + qR + 8 * sD _
   Or Y > sY + qR + 9 * sD Then
   bPangDuangShiFoLengZhougZhi = False
   Exit Function
End If
Select Case qStep
       Case Enum_qStep.定义甲方
            If QiJu_eArrary(X, Y, , , Obj) > 0 And (Not Obj Is Nothing) Then '
               bPangDuangShiFoLengZhougZhi = True
            Else
               bPangDuangShiFoLengZhougZhi = False
            End If
       Case Enum_qStep.甲方走
            '判断当前点是否有子
            '如果有,且是本方的子时,重定义棋子,返回False
            '否则，检察是否满足定义棋子的走法。
            If QiJu_eArrary(X, Y, , , Obj) > 0 Then
               If Not Obj Is Nothing Then '重定义棋子
                  RecordQJ X, Y, , 存入记录数组中的Pos位置
                  With qDefine
                       .QiZhi = QiJu_eArrary(X, Y, , , Obj)
                       Set .oQiZhi = Obj
                       .X = X
                       .Y = Y
                  End With
                  With ShpTSD
                    .Top = Y - .Height / 2
                    .Left = X - .Width / 2
                    .Visible = True
                  End With
                  Tishi X, Y, Obj
               End If
               bPangDuangShiFoLengZhougZhi = False
            Else
               bPangDuangShiFoLengZhougZhi = bQiZhiWalk(X, Y)
            End If
       Case Enum_qStep.定义乙方
            If QiJu_eArrary(X, Y, , , Obj) < 0 And (Not Obj Is Nothing) Then '
               bPangDuangShiFoLengZhougZhi = True
            Else
               bPangDuangShiFoLengZhougZhi = False
            End If
       Case Enum_qStep.乙方走
            '判断当前点是否有子
            '如果有,且是本方的子时,重新定义棋子,返回False
            '否则，检察是否满足定义棋子的走法。
            If QiJu_eArrary(X, Y, , , Obj) < 0 Then
               If Not Obj Is Nothing Then '重新定义棋子
                  RecordQJ X, Y, , 存入记录数组中的Pos位置
                  With qDefine
                       .QiZhi = QiJu_eArrary(X, Y, , , Obj)
                       Set .oQiZhi = Obj
                       .X = X
                       .Y = Y
                  End With
                  With ShpTSD
                    .Top = Y - .Height / 2
                    .Left = X - .Width / 2
                    .Visible = True
                  End With
                  Tishi X, Y, Obj
               End If
               bPangDuangShiFoLengZhougZhi = False
            Else
               bPangDuangShiFoLengZhougZhi = bQiZhiWalk(X, Y)
            End If
End Select
End Function

'--------------------------------------------------------------
'以下是棋子的走法
Private Function bQiZhiWalk(X As Single, Y As Single) As Boolean
'1.如果是一边的棋,前一步必须已经考虑了
If Sgn(qDefine.QiZhi) = Sgn(QiJu_eArrary(X, Y)) Then
   bQiZhiWalk = False
   Exit Function
End If

Dim Di As Integer, Dj As Integer, I As Integer, j As Integer
Dim iQiJu(9, 10) As Integer
For I = 0 To 9 '
    For j = 0 To 10
        iQiJu(I, j) = QiJu(I, j).iQiJu
    Next j
Next I
ZhouBiao_eTranslate qDefine.X, qDefine.Y, Di, Dj
ZhouBiao_eTranslate X, Y, I, j

'2.判断能否走
Select Case Abs(qDefine.QiZhi)
       Case Enum_QZ.Bing
            bQiZhiWalk = bBingWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Che
            bQiZhiWalk = bCheWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Ma
            bQiZhiWalk = bMaWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Pao
            bQiZhiWalk = bPaoWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Shi
            bQiZhiWalk = bShiWalk(Di, Dj, I, j, iQiJu)
       Case Enum_QZ.Shuai
            bQiZhiWalk = bShuaiWalk(Di, Dj, I, j, iQiJu)
            bQiZhiWalk = Not bShuaiDuaiMei(Di, Dj, I, j, iQiJu, True)
            GoTo bQizhiWalkLoop
       Case Enum_QZ.Xiang
            bQiZhiWalk = bXiangWalk(Di, Dj, I, j, iQiJu)
End Select

If bQiZhiWalk Then
   '判断将对面
   bQiZhiWalk = Not bShuaiDuaiMei(Di, Dj, I, j, iQiJu)
End If
'注意位置不能动位置
bQizhiWalkLoop:
If bQiZhiWalk Then
   '判断是否将军,包括叫将与被将.
   '叫将返回Enum_Walk_Val.叫将(真值)
   '被将返回Enum_Walk_Val.被将(假值)
   bQiZhiWalk = JianJun(Di, Dj, I, j, iQiJu)
End If

End Function

'提示
Private Sub Tishi(Optional X As Single = 0, Optional Y As Single = 0, Optional Object As Object = Nothing)
On Error Resume Next
Select Case qStep
       Case Enum_qStep.定义甲方
            TiShiQZ.Visible = False
            TiShiQZ.Stretch = True
            FraTiShi.Top = PicQiPang.Top
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height / 2
            If jF.Name <> "" Then
               LabTiShi.Caption = jF.Name + "确定棋子"
            Else
               LabTiShi.Caption = jF.sName + "确定棋子"
            End If
            With tTime
                 .yTotalWalkTime = .yTotalWalkTime + CDate(TxtHadTime.Text)
                 .TotalWalkTime = .jTotalWalkTime
                 .OneStartTime = Time
            End With
       Case Enum_qStep.甲方走
            TiShiQZ.Stretch = True
            Set TiShiQZ = qDefine.oQiZhi
            TiShiQZ.Visible = True
            FraTiShi.Top = PicQiPang.Top
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height
            If jF.Name <> "" Then
               LabTiShi.Caption = jF.Name + "走"
            Else
               LabTiShi.Caption = jF.sName + "走"
            End If
            If Not Object Is Nothing Then
               
            End If
       Case Enum_qStep.定义乙方
            TiShiQZ.Visible = False
            FraTiShi.Top = PicQiPang.Top + PicQiPang.Height - FraTiShi.Height
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height / 2
            If yF.Name <> "" Then
               LabTiShi.Caption = yF.Name + "确定棋子"
            Else
               LabTiShi.Caption = yF.sName + "确定棋子"
            End If
            With tTime
                 .jTotalWalkTime = .jTotalWalkTime + CDate(TxtHadTime.Text)
                 .TotalWalkTime = .yTotalWalkTime
                 .OneStartTime = Time
            End With
       Case Enum_qStep.乙方走
            TiShiQZ.Stretch = True
            Set TiShiQZ = qDefine.oQiZhi
            TiShiQZ.Visible = True
            FraTiShi.Top = PicQiPang.Top + PicQiPang.Height - FraTiShi.Height
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height
            If yF.Name <> "" Then
               LabTiShi.Caption = yF.Name + "走"
            Else
               LabTiShi.Caption = yF.sName + "走"
            End If
            If Not Object Is Nothing Then
               
            End If
End Select
LabTiShi.Left = (FraTiShi.Width - LabTiShi.Width) / 2
End Sub

'记录走棋
Private Sub RecordQJ(Optional X As Single = 0, Optional Y As Single = 0, Optional QiZhi As Enum_QiZhi = Enum_QiZhi.NoZhi, Optional Flag As Enum_RecordQj_Flag = 存入记录数组, Optional Pos As Long = 0)
Dim I As Integer, j As Integer, K As Single, L As Integer
K = Pos
ZhouBiao_eTranslate X, Y, I, j
Select Case Flag
       Case 存入记录数组
            ReDim Preserve QJ(UBound(QJ) + 1)
            L = QiJu_eArrary(X, Y) '要存入的棋子
            'If L <> 0 Then
               QJ(UBound(QJ)) = QiJuBianMa(I, j, L) 'Sgn(k) * (J + I * 100 + Abs(k * 1000))
            'Else
            '   QJ(UBound(QJ)) = J + I * 100
            'End If
       Case 存入记录数组中的Pos位置
            If Pos = 0 Then Pos = UBound(QJ)
            L = QiJu_eArrary(X, Y)
            'If L <> 0 Then
               QJ(Pos) = QiJuBianMa(I, j, L) ' Sgn(k) * (J + I * 100 + Abs(k * 1000))
            'Else
            '   QJ(UBound(QJ)) = J + I * 100
            'End If
       Case 从记录数组中取出
            If K = 0 Then
               If lFuPang < UBound(QJ) And lFuPang >= 0 Then
                  lFuPang = lFuPang + 1
                  QiZhi = QiJuBianMa(I, j, QJ(lFuPang), 进行解码)
               Else
                  lFuPang = UBound(QJ) '把指针指向数组的最后部
                  Beep
               End If
            Else
               QiZhi = QiJuBianMa(I, j, QJ(K), 进行解码)
            End If
            ZhouBiao_eTranslate X, Y, I, j, 把棋局座标转换为棋盘上的座标
End Select
End Sub

'以上为棋子的走法
'--------------------------------------
'以上为走子
'=============================================================================================
'以下为文件操作
Private Sub SaveFile(FileName As String, Optional Flag As Enum_File_Flag = Enum_File_Flag.加密格式)
If Run Then On Error Resume Next
If Dir(FileName) <> "" Then
   Kill FileName
End If
If UCase$(Right$(FileName, 4)) = UCase$(".xqt") Then
   Flag = 文本格式
Else
   Flag = 加密格式
End If
Select Case Flag
       Case Enum_File_Flag.加密格式
            If tFileHand.bBuJu Then
               Call SaveFileAdd_MiDiBuJu(FileName)
            Else
               Call SaveFileAdd_Mi(FileName)
            End If
       Case Enum_File_Flag.文本格式
            If bFileAdd_Mi Then
               If Not PassWord(把文件从加密格式转化为文本格式) Then
                  Exit Sub
               End If
            End If
            If tFileHand.bBuJu Then
               Call SaveFileText_BuJu(FileName)
            Else
               Call SaveFileText(FileName)
            End If
End Select
End Sub

'保存布局文件
Private Sub SaveFileAdd_MiDiBuJu(FileName As String)
Dim Num As Integer, I As Long, j As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "中国象棋"
     .CompanyName = "康林工作室"
     .Disger = "康林"
     .FileType = Enum_File_Flag.布局加密格式
     .App_BiaoZhi = tFileHand.App_BiaoZhi
     .App_BiaoZhi_ID = tFileHand.App_BiaoZhi_ID
     .Major = tFileHand.Major
     .Minor = tFileHand.Minor
     .MyPassWord = tFileHand.MyPassWord
     .PassWord = tFileHand.PassWord
     If .PassWord = 0 Then
        .NoPassWordFlag = True
     Else
        .NoPassWordFlag = False
     End If
     .bBuJu = True
     .SheiZhou = tFileHand.SheiZhou
End With
Open FileName For Random As #Num Len = Len(tFh)
Put #Num, , tFh
Close #Num
'存入时间
'时间(Date)的长度为8字节
'整数(Integer)的长度为2字节
'长整数(Long)的长度为4字节
'单精度(Single)的长度为4字节
'双精度(Double)的长度为8字节
Num = FreeFile
Open FileName For Binary As #Num Len = 8
With tTime
     S = Format(TxtTime.Text, "hh:mm:ss")
     Put #Num, Len(tFh) + 1, S
     S = Format(.jTotalWalkTime, "hh:mm:ss")
     Put #Num, , S
     S = Format(.yTotalWalkTime, "hh:mm:ss")
     Put #Num, , S
End With
Close #Num
Open FileName For Binary As #Num Len = Len(QJ(0))
Put #Num, Len(tFh) + 24 + 1, QJ(0) '设置文件指针
For I = 1 To 9
    For j = 1 To 10
        Put #Num, , BuJuQiJu(I, j)
    Next j
Next I
For I = 1 To UBound(QJ)
    Put #Num, , QJ(I)
Next I
Close #Num
Exit Sub
SaveFileError:
If Not Run Then MsgBox Err.Description  's保存文件出错
End Sub

'加密格式文件
Private Sub SaveFileAdd_Mi(FileName As String)
Dim Num As Integer, I As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "中国象棋"
     .CompanyName = "康林工作室"
     .Disger = "康林"
     .FileType = 加密格式
     .App_BiaoZhi = tFileHand.App_BiaoZhi
     .App_BiaoZhi_ID = tFileHand.App_BiaoZhi_ID
     .Major = tFileHand.Major
     .Minor = tFileHand.Minor
     .MyPassWord = tFileHand.MyPassWord
     .PassWord = tFileHand.PassWord
     If .PassWord = 0 Then
        .NoPassWordFlag = True
     Else
        .NoPassWordFlag = False
     End If
     .SheiZhou = tFileHand.SheiZhou
End With
Open FileName For Random As #Num Len = Len(tFh)
Put #Num, , tFh
Close #Num
'存入时间
'时间(Date)的长度为8字节
'整数(Integer)的长度为2字节
'长整数(Long)的长度为4字节
'单精度(Single)的长度为4字节
'双精度(Double)的长度为8字节
Num = FreeFile
Open FileName For Binary As #Num Len = 8
With tTime
     S = Format(TxtTime.Text, "hh:mm:ss")
     Put #Num, Len(tFh) + 1, S
     S = Format(.jTotalWalkTime, "hh:mm:ss")
     Put #Num, , S
     S = Format(.yTotalWalkTime, "hh:mm:ss")
     Put #Num, , S
End With
Close #Num
Open FileName For Binary As #Num Len = Len(QJ(0))
Put #Num, Len(tFh) + 24 + 1, QJ(0) '设置文件指针
For I = 1 To UBound(QJ)
    Put #Num, , QJ(I)
Next I
Close #Num
Exit Sub
SaveFileError:
If Not Run Then MsgBox Err.Description  's保存文件出错

End Sub

'布局的文本格式文件
Private Sub SaveFileText_BuJu(FileName As String)
On Error GoTo SaveFileError
Dim Num As Integer, I As Long, j As Integer
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "中国象棋"
     .CompanyName = "康林工作室"
     .Disger = "康林"
     .FileType = Enum_File_Flag.布局文本格式
     .App_BiaoZhi = tFileHand.App_BiaoZhi
     .App_BiaoZhi_ID = tFileHand.App_BiaoZhi_ID
     .Major = tFileHand.Major
     .Minor = tFileHand.Minor
     .MyPassWord = 0
     .PassWord = tFileHand.PassWord
     .NoPassWordFlag = True
     .bBuJu = True
     .SheiZhou = tFileHand.SheiZhou
End With
Open FileName For Random As #Num Len = Len(tFh)
Put #Num, , tFh
Close #Num
Num = FreeFile
Open FileName For Append As #Num
Print #Num, '此句在第一行
With tTime
     Print #Num, TxtTime
     Print #Num, .jTotalWalkTime
     Print #Num, .yTotalWalkTime
End With
'加入布局
For I = 1 To 9
    For j = 1 To 10
        Print #Num, BuJuQiJu(I, j)
    Next j
Next I
For I = 1 To UBound(QJ)
    Print #Num, QJ(I)
Next I
Close #Num
Exit Sub
SaveFileError:
If Not Run Then MsgBox Err.Description  's保存文件出错

End Sub

'文本格式文件
Private Sub SaveFileText(FileName As String)
On Error GoTo SaveFileError
Dim Num As Integer, I As Long
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "中国象棋"
     .CompanyName = "康林工作室"
     .Disger = "康林"
     .FileType = Enum_File_Flag.文本格式
     .App_BiaoZhi = tFileHand.App_BiaoZhi
     .App_BiaoZhi_ID = tFileHand.App_BiaoZhi_ID
     .Major = tFileHand.Major
     .Minor = tFileHand.Minor
     .MyPassWord = 0
     .PassWord = tFileHand.PassWord
     .NoPassWordFlag = True
     .SheiZhou = tFileHand.SheiZhou
End With
Open FileName For Random As #Num Len = Len(tFh)
Put #Num, , tFh
Close #Num
Num = FreeFile
Open FileName For Append As #Num
Print #Num, '此句在第一行
With tTime
     Print #Num, TxtTime
     Print #Num, .jTotalWalkTime
     Print #Num, .yTotalWalkTime
End With
For I = 1 To UBound(QJ)
    Print #Num, QJ(I)
Next I
Close #Num
Exit Sub
SaveFileError:
If Not Run Then MsgBox Err.Description  's保存文件出错
End Sub
 
'打开文件
Private Function OpenFile(FileName As String) As Boolean
If Run Then On Error GoTo OpenFileError
Dim Num As Integer
Dim tFh As Type_File_Hand
Dim Flag As Enum_File_Flag

Num = FreeFile
Open FileName For Random As #Num Len = Len(tFh)
Get #Num, , tFh
With tFh
     If .App_BiaoZhi_ID = tFileHand.App_BiaoZhi_ID Then
        If Left(.App_BiaoZhi, 4) = Left(tFileHand.App_BiaoZhi, 4) Then
           Flag = .FileType
        Else
           MsgBox s文件打开错误
           OpenFile = False
           Close #Num
           Exit Function
        End If
     Else
        MsgBox s文件打开错误
        OpenFile = False
        Close #Num
        Exit Function
     End If
End With
Close #Num
If (Not tFh.NoPassWordFlag) Or tFh.PassWord Then
   If Not PassWord(打开加密文件, tFh.PassWord) Then
      OpenFile = False
      Exit Function
   End If
End If
Select Case Flag
       Case Enum_File_Flag.加密格式
            OpenFile = OpenFileAdd_Mi(FileName)
       Case Enum_File_Flag.文本格式
            OpenFile = OpenFileText(FileName)
       Case Enum_File_Flag.布局加密格式
            OpenFile = OpenFileAdd_MiDiBuJu(FileName)
       Case Enum_File_Flag.布局文本格式
            OpenFile = OpenFileText_BuJu(FileName)
End Select
If OpenFile Then '复制从文件中提取的参数
   qStep = tFh.SheiZhou
   With tFileHand
        .bBuJu = tFh.bBuJu
        .FileType = tFh.FileType
        .PassWord = tFh.PassWord
        .SheiZhou = tFh.SheiZhou
   End With
End If
Exit Function
OpenFileError:
    OpenFile = False
End Function

'打开布局文件
Private Function OpenFileAdd_MiDiBuJu(FileName As String) As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, I As Long, j As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
Open FileName For Binary As #Num Len = Len(tFh)
Get #Num, , tFh
Close #Num
'取出时间
'时间(Date)的长度为8字节
'整数(Integer)的长度为2字节
'长整数(Long)的长度为4字节
'单精度(Single)的长度为4字节
'双精度(Double)的长度为8字节
Num = FreeFile
Open FileName For Binary As #Num Len = 8
With tTime
     Get #Num, Len(tFh) + 1, S
     TxtTime.Text = S
     Get #Num, , S
     .jTotalWalkTime = CDate(S)
     Get #Num, , S
     .yTotalWalkTime = CDate(S)
End With
Close #Num
Num = FreeFile
Open FileName For Binary As #Num Len = Len(QJ(0))
Get #Num, Len(tFh) + 25, QJ(0) '设置文件指针
For I = 1 To 9
    For j = 1 To 10
        Get #Num, , BuJuQiJu(I, j)
    Next j
Next I
I = 0
While (Not EOF(Num))
      I = I + 1
      ReDim Preserve QJ(I)
      Get #Num, , QJ(I)
Wend
Close #Num
If I Then
   OpenFileAdd_MiDiBuJu = True
   bFileAdd_Mi = True
Else
   OpenFileAdd_MiDiBuJu = False
End If
End Function

'打开加密格式文件
Private Function OpenFileAdd_Mi(FileName As String) As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, I As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
Open FileName For Binary As #Num Len = Len(tFh)
Get #Num, , tFh
Close #Num
'取出时间
'时间(Date)的长度为8字节
'整数(Integer)的长度为2字节
'长整数(Long)的长度为4字节
'单精度(Single)的长度为4字节
'双精度(Double)的长度为8字节
Num = FreeFile
Open FileName For Binary As #Num Len = 8
With tTime
     Get #Num, Len(tFh) + 1, S
     TxtTime.Text = S
     Get #Num, , S
     .jTotalWalkTime = CDate(S)
     Get #Num, , S
     .yTotalWalkTime = CDate(S)
End With
Close #Num
Num = FreeFile
Open FileName For Binary As #Num Len = Len(QJ(0))
I = 0
Get #Num, Len(tFh) + 25, QJ(0) '设置文件指针
While (Not EOF(Num))
      I = I + 1
      ReDim Preserve QJ(I)
      Get #Num, , QJ(I)
Wend
Close #Num
If I Then
   OpenFileAdd_Mi = True
   bFileAdd_Mi = True
Else
   OpenFileAdd_Mi = False
End If
End Function

'打开布局文件
Private Function OpenFileText_BuJu(FileName As String) As Boolean
If Run Then On Error GoTo OpenFileError
Dim Num As Integer, I As Long, j As Integer
Dim tFh As Type_File_Hand
Dim S As String
Num = FreeFile
Open FileName For Input As #Num
Line Input #Num, S '注意只有一句
           '因为SaveFileText中的后一个Print语句也在第一行
With tTime
     Line Input #Num, S
     TxtTime.Text = S
     Line Input #Num, S
    .jTotalWalkTime = CDate(S)
     Line Input #Num, S
    .yTotalWalkTime = CDate(S)
End With
'取出布局
For I = 1 To 9
    For j = 1 To 10
        Input #Num, BuJuQiJu(I, j)
    Next j
Next I
ReDim QJ(0)
I = 0
While (Not EOF(Num))
      I = I + 1
      ReDim Preserve QJ(I)
      Input #Num, QJ(I)
Wend
If I Then
   OpenFileText_BuJu = True
   bFileAdd_Mi = False '标志此文件不是加密文件
End If
Close #Num
Exit Function
OpenFileError:
   OpenFileText_BuJu = False
   Close #Num
   If Not Run Then MsgBox Err.Description
End Function


'打开文本格式文件
Private Function OpenFileText(FileName As String) As Boolean
If Run Then On Error GoTo OpenFileError
Dim Num As Integer, I As Long
Dim tFh As Type_File_Hand
Dim S As String
Num = FreeFile
ReDim QJ(0)
I = 0
Open FileName For Input As #Num
Line Input #Num, S '注意只有一句
           '因为SaveFileText中的后一个Print语句也在第一行
With tTime
     Line Input #Num, S
     TxtTime.Text = S
     Line Input #Num, S
    .jTotalWalkTime = CDate(S)
     Line Input #Num, S
    .yTotalWalkTime = CDate(S)
End With
While (Not EOF(Num))
      I = I + 1
      ReDim Preserve QJ(I)
      Input #Num, QJ(I)
Wend
If I Then
   OpenFileText = True
   bFileAdd_Mi = False '标志此文件不是加密文件
End If
Close #Num
Exit Function
OpenFileError:
   OpenFileText = False
   Close #Num
   If Not Run Then MsgBox Err.Description
End Function

'读写配置文件
Private Function ChangeIniFile(ChangeFlag As Enum_IniFile, Optional szString As String, Optional AnyPara As Variant)
Dim ss As String * 1024, I As Long
If Run Then On Error Resume Next

Select Case ChangeFlag
       Case Enum_IniFile.取出棋子材料
            I = GetPrivateProfileString("外观", "棋子的材料", "", ss, 1024, IniFile)
            If I Then
               ImgList.ListImages.Add , "add", LoadPicture(LeftB(ss, I))
            End If
       Case Enum_IniFile.写入更新棋子材料
            I = WritePrivateProfileString("外观", "棋子的材料", szString, IniFile)
       Case Enum_IniFile.写入棋子材料用系统设置的
            I = WritePrivateProfileString("外观", "棋子的材料", "", IniFile)
       Case Enum_IniFile.写入棋盘样式
            I = WritePrivateProfileString("外观", "棋盘的样式", szString, IniFile)
       Case Enum_IniFile.取出棋盘样式
            I = GetPrivateProfileString("外观", "棋盘的样式", "", ss, 1024, IniFile)
            If I Then
               sQiPangStyleFileName = Left$(ss, I)
            End If
       Case Enum_IniFile.写入窗口背景
            I = WritePrivateProfileString("外观", "窗口背景", szString, IniFile)
       Case Enum_IniFile.取出窗口背景
            I = GetPrivateProfileString("外观", "窗口背景", "", ss, 1024, IniFile)
            If I Then
               Form1.Picture = LoadPicture(Left(ss, I))
            End If
       Case Enum_IniFile.写入自动复盘的时间
            I = WritePrivateProfileString("设置", "自动复盘的时间", szString, IniFile)
       Case Enum_IniFile.取出自动复盘的时间
            I = GetPrivateProfileString("设置", "自动复盘的时间", "", ss, 1024, IniFile)
            If I Then
               nAutoFuPangTime = CDate(LeftB(ss, I))
            End If
       Case 写入对战方式之人机对战
            I = WritePrivateProfileString("设置", "对战方式", "人机对战", IniFile)
       Case 写入对战方式之人人对战
            I = WritePrivateProfileString("设置", "对战方式", "人人对战", IniFile)
       Case 写入对战方式之网络对战
            I = WritePrivateProfileString("设置", "对战方式", "网络对战", IniFile)
       Case Enum_IniFile.取出对战方式
            I = GetPrivateProfileString("设置", "对战方式", "人人对战", ss, 1024, IniFile)
            If I Then
               Select Case LeftB((ss), I)
                      Case "人人对战"
                           s对战模式 = " 人人对战 "
                           mnuFileManAndMan.Checked = True
                      Case "人机对战"
                           s对战模式 = " 人机对战 "
                           mnuFileManAndMachine.Checked = True
                      Case "网络对战"
                           mnuFileNet.Checked = True
                           s对战模式 = " 网络对战 "
               End Select
            End If
       Case Enum_IniFile.取出菜单中显示时间的状态
            I = GetPrivateProfileString("菜单", "显示时间", "True", ss, 1024, IniFile)
            If I Then
               mnuOptionShowTime.Checked = Not CBool(Left(ss, I))
               mnuOPtionShowTime_Click
            End If
       Case Enum_IniFile.写入菜单中显示时间的状态
            I = WritePrivateProfileString("菜单", "显示时间", szString, IniFile)
       Case Enum_IniFile.取出菜单中显示状态栏的状态
            I = GetPrivateProfileString("菜单", "显示状态栏", "True", ss, 1024, IniFile)
            If I Then
               mnuOptionStateBar.Checked = Not CBool(Left(ss, I))
               mnuOptionStateBar_Click
            End If
       Case Enum_IniFile.写入菜单中显示状态栏的状态
            I = WritePrivateProfileString("菜单", "显示状态栏", szString, IniFile)
       Case Enum_IniFile.写入菜单中显示对话框的状态
            I = WritePrivateProfileString("菜单", "显示对话框", szString, IniFile)
       Case Enum_IniFile.取出菜单中显示对话框的状态
            I = GetPrivateProfileString("菜单", "显示对话框", "True", ss, 1024, IniFile)
            If I Then
               mnuOptionStateBar.Checked = Not CBool(Left(ss, I))
               mnuOptionShowTalk_Click
            End If
       Case Enum_IniFile.取出本地记录颜色
            I = GetPrivateProfileString("网络", "本地记录颜色", vbBlack, ss, 10, IniFile)
            If I Then
               tNet.NetTalkTextColorLocal = Val(Left(ss, I))
            Else
               tNet.NetTalkTextColorLocal = vbBlack
            End If
       Case Enum_IniFile.取出远端记录颜色
            I = GetPrivateProfileString("网络", "远端记录颜色", vbRed, ss, 10, IniFile)
            If I Then
               tNet.NetTalkTextColorRemote = Val(Left(ss, I))
            Else
               tNet.NetTalkTextColorRemote = vbRed
            End If
       Case Enum_IniFile.写入本地记录颜色
            I = WritePrivateProfileString("网络", "本地记录颜色", CStr(AnyPara), IniFile)
       Case Enum_IniFile.写入远端记录颜色
            I = WritePrivateProfileString("网络", "远端记录颜色", CStr(AnyPara), IniFile)
       Case Enum_IniFile.写入远端其它记录颜色
            I = WritePrivateProfileString("网络", "远端其它记录颜色", CStr(AnyPara), IniFile)
       Case Enum_IniFile.取出远端其它记录颜色
            I = GetPrivateProfileString("网络", "远端其它记录颜色", vbYellow, ss, 10, IniFile)
            If I Then
               tNet.NetTalkTextColorRemoteOrther = Val(Left(ss, I))
            Else
               tNet.NetTalkTextColorRemoteOrther = vbRed
            End If
       
End Select
End Function

'以上为文件操作
'====================================================================
''响应光标键
Private Function Key_ChuLi(KeyCode As Integer, Shift As Integer)
Dim Obj As Object
With ShpCur
     Select Case KeyCode
            Case vbKeyUp
                 If .Top > sY Then
                    .Top = .Top - sD
                 Else
                    Beep
                 End If
            Case vbKeyDown
                 If .Top < sY + 8 * sD Then
                    .Top = .Top + sD
                 Else
                    Beep
                 End If
            Case vbKeyRight
                 If .Left < sX + 7 * sD Then
                    .Left = .Left + sD
                 Else
                    Beep
                 End If
            Case vbKeyLeft
                 If .Left > sX Then
                    .Left = .Left - sD
                 Else
                    Beep
                 End If
            Case 13
                 Call QiJu_eArrary(.Left + sD / 2, .Top + sD / 2, , , Obj)
                 Walk .Left + sD / 2, .Top + sD / 2, Obj
     End Select
End With
End Function

Private Sub PicNoQi_GotFocus()
PicQiPang.SetFocus
End Sub

'以下为控件操作
'响应光标键
Private Sub PicQiPang_KeyUp(KeyCode As Integer, Shift As Integer)
Key_ChuLi KeyCode, Shift
End Sub

Private Sub PicNoQi_DragDrop(Source As Control, X As Single, Y As Single)
Dim XX As Single, YY As Single, Ctr As Image
If mnuFileBuJu.Checked And Not (Source Is Nothing) Then
   With Source
        If Abs(Source.Tag) Mod 10 = Enum_QZ.Shuai Then
           MsgBox s帅不能移出棋盘, vbCritical
           Exit Sub
        End If
        '清除原位置的棋
        QiJu_eArrary .Left, .Top, Enum_QiZhi.NoZhi, 给数组赋值
        .Top = Y
        .Left = X
        '把QZ.Tag的十位置1，标识此子已移出棋盘
        Source.Tag = Sgn(Source.Tag) * (Abs(Source.Tag) + 10)
        Set Source.Container = PicNoQi '改变容器
   End With
   fNoQi
   tFileHand.bBuJu = True '置布局标识
   If Run Then '排列位置
      XX = -Source.Width: YY = Source.Height
      For Each Ctr In QZ
          If Ctr.Container Is PicNoQi Then
             If XX > PicNoQi.ScaleWidth Then
                XX = 0
                YY = YY + Ctr.Height
             Else
                XX = XX + Ctr.Width
             End If
             Ctr.Top = YY
             Ctr.Left = XX
          End If
      Next Ctr
   End If
End If
End Sub

Private Sub PicQiPang_DragDrop(Source As Control, X As Single, Y As Single)
Dim I As Integer, j As Integer, Di As Integer, Dj As Integer
Dim XX As Single, YY As Single, Ctr As Image
If mnuFileBuJu.Checked Then
   '把鼠标限制在棋盘内
   If X < sX - qR Or Y < sY - qR Or X > sX + qR + 8 * sD _
      Or Y > sY + qR + 9 * sD Then
      Exit Sub
   End If
   Call ZhouBiao_eTranslate(X, Y, I, j)
   Di = I: Dj = j
   Call ZhouBiao_eTranslate(X, Y, I, j, 把棋局座标转换为棋盘上的座标)
   '当前位置无棋且此位置符合棋子走法
   If QiJu_eArrary(X, Y) = Enum_QiZhi.NoZhi And _
      bBuJu_eWalk_fa(Di, Dj, Source) Then
      With Source
        If Abs(Source.Tag) \ 10 Mod 10 = 0 Then 'Source.Tag详见Make_QiZhi和PicNoQi_DragDrop
           '在棋盘中移动,清除原位置的棋
           QiJu_eArrary .Left, .Top, Enum_QiZhi.NoZhi, 给数组赋值
        Else '修改Source.Tag,把十位置0
           Source.Tag = Sgn(Source.Tag) * (Abs(Source.Tag) Mod 10)
           Set Source.Container = PicQiPang '改变容器
        End If
        SetPos X, Y, Source '设置移动后的位置
        '移动后给棋局数组赋值
        QiJu_eArrary X, Y, Source.Tag, 给数组赋值, Source 'Source.Tag详见Make_QiZhi和PicNoQi_DragDrop
        fNoQi
        tFileHand.bBuJu = True '置布局标识
        If Run Then '排列PicNoqi中移出棋子的位置
           XX = -Source.Width: YY = Source.Height
           For Each Ctr In QZ
               If Ctr.Container Is PicNoQi Then
                  If XX > PicNoQi.ScaleWidth Then
                     XX = 0
                     YY = YY + Ctr.Height
                  Else
                     XX = XX + Ctr.Width
                  End If
                  Ctr.Top = YY
                  Ctr.Left = XX
                End If
            Next Ctr
        End If
      End With
   End If
End If
End Sub

Private Sub PicQiPang_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim exi As Long
If Button = vbLeftButton And Not mnuFileBuJu.Checked Then
   If bFuPang And s对战模式 <> " 网络对战 " Then
      exi = MsgBox(s不再复盘而是继续下, vbYesNo + vbQuestion)
      If exi = vbYes Then
         bFuPang = False
         Set_Fupang_eTool
         ReDim Preserve QJ(lFuPang)
      Else
         Exit Sub
      End If
   End If
   If s对战模式 <> " 网络对战 " Then
       Call Walk(X, Y)
   Else
       If Not tNet.NetRemoteWork Then
          If Walk(X, Y) Then
             Call SendTalkText(发送走棋)
          End If
       End If
   End If
End If
If Button = vbRightButton Then
   PopupMenu mnuFile
End If
End Sub

Private Sub QZ_MouseUp(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim exi As Long
If Button = vbRightButton Then
   PopupMenu mnuFile
End If
If Button = vbLeftButton And Not mnuFileBuJu.Checked Then
   If bFuPang And s对战模式 <> " 网络对战 " Then
      exi = MsgBox(s不再复盘而是继续下, vbYesNo + vbQuestion)
      If exi = vbYes Then
         bFuPang = False
         Set_Fupang_eTool
         ReDim Preserve QJ(lFuPang)
      Else
         Exit Sub
      End If
   End If
   If s对战模式 <> " 网络对战 " Then
       Walk QZ(Index).Left + qR, qR + QZ(Index).Top, QZ(Index)
   Else
       If Not tNet.NetRemoteWork Then
          If Walk(QZ(Index).Left + qR, qR + QZ(Index).Top, QZ(Index)) Then
             Call SendTalkText(发送走棋)
          End If
       End If
   End If
End If
PicQiPang.SetFocus
End Sub

Private Sub Tim_Timer()
Dim I
'总共时间
TxtTime.Text = Format(Time - tTime.StartTime, "hh:mm:ss")
'本步走的时间
TxtHadTime.Text = Format(Time - tTime.OneStartTime, "hh:mm:ss")
'已走的时间
TxtTotalTime.Text = Format(tTime.TotalWalkTime + TxtHadTime.Text, "hh:mm:ss")
'自动复盘
If bFuPang And nAutoFuPangTime > CDate(0) Then
   If TxtHadTime.Text > nAutoFuPangTime Then
      cmdNext_Click
   End If
End If
End Sub

'重新设置各控件的位置
Private Sub ReSetPostion(Flag As Boolean, Optional Height As Single = 0, Optional Width As Single = 0)
With PicQiPang
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
With LabJF
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
With LabYF
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
With FraTiShi
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
With Fraredo
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
With txtNetTalk
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
With txtNetInput
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
With PicNoQi
     If Flag Then
        .Top = .Top - Height
        .Left = .Left - Width
     Else
        .Top = .Top + Height
        .Left = .Left + Width
     End If
End With
End Sub

'设置密码
Private Function PassWord(Flag As Enum_PassWord_Flag, Optional Param As Variant) As Boolean
If Run Then
   Select Case Flag
          Case 把文件从加密格式转化为文本格式
          
          Case Enum_PassWord_Flag.打开加密文件
          
          Case Enum_PassWord_Flag.设置保存密码
          '先确定tFileHand中是否为0
          '如为0，则以前没设密码
          '否则,设有密码
          
   End Select
Else
   MsgBox "PassWord"
   PassWord = True
End If
End Function

'布局复盘
Private Sub BuJuFuPang()
Dim Ctr As Image, I As Integer, j As Integer
Dim X As Single, Y As Single
For Each Ctr In QZ
    If Ctr <> QZ(0) Then Unload Ctr
Next Ctr
For I = 1 To 9
    For j = 1 To 10
        With QiJu(I, j) '清空棋局
             .iQiJu = Enum_QiZhi.NoZhi
             Set .oObject = Nothing
        End With
        If BuJuQiJu(I, j) <> Enum_QiZhi.NoZhi Then
           ZhouBiao_eTranslate X, Y, I, j, 把棋局座标转换为棋盘上的座标
           Call Make_QiZhi(X, Y, BuJuQiJu(I, j))
        End If
    Next j
Next I
Tishi
If Not Run Then fNoQi
End Sub

Private Sub txtNetInput_GotFocus()
txtNetInput.SelColor = tNet.NetTalkTextColorLocal
Set tNet.NetEditText = txtNetInput
End Sub

Private Sub txtNetInput_KeyUp(KeyCode As Integer, Shift As Integer)
If Shift = 2 And KeyCode = 13 Then
   Call SendTalkText
End If
End Sub

Private Sub txtNetInput_LostFocus()
If tNet.NetEditText Is txtNetInput Then
   Set tNet.NetEditText = Nothing
End If
End Sub

Private Sub txtNetInput_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Run Then On Error Resume Next
If Button = vbRightButton And s对战模式 = " 网络对战 " Then
   Set tNet.NetEditText = txtNetInput
   Me.PopupMenu mnuEdit
End If
End Sub

Private Sub txtNetTalk_GotFocus()
Set tNet.NetEditText = txtNetTalk
End Sub

Private Sub txtNetTalk_LostFocus()
If tNet.NetEditText Is txtNetTalk Then
   Set tNet.NetEditText = Nothing
End If
End Sub

Private Sub txtNetTalk_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Run Then On Error Resume Next
If Button = vbRightButton And s对战模式 = " 网络对战 " Then
   Set tNet.NetEditText = txtNetTalk
   Me.PopupMenu mnuEdit
End If
End Sub

Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
On Error Resume Next
Dim S As String
Winsock1.GetData S, vbString
With txtNetTalk
     .SelStart = Len(.Text)
     .SelColor = tNet.NetTalkTextColorRemote
     .SelText = txtNetInput.Text + Chr(10)
End With
End Sub

'-----------------------------------------------------------
'以下为网络函数
'-----------------------------------------------------------
'设置网络工具
Private Sub SetNetPara(Optional bVisible As Boolean = True, Optional Called As Enum_SetNetPara_Called = Enum_SetNetPara_Called.网络设置中的默认调用)
'设置远端走棋,位置不能变，只能放在最前面
If Called = 在设置用户时调用 Then
   tNet.NetRemoteWork = bVisible
   '设置UDP
   With Winsock1
        .Close
        .Protocol = sckUDPProtocol
        If Run Then
          .RemoteHost = InputBox(s请输入对方地址)
          .RemotePort = 0
          .LocalPort = 0
          .Bind 0
        Else
          .RemoteHost = "127.0.0.1"
          .RemotePort = 1000
          .LocalPort = 1001
          .Bind 1001
        End If
   End With
   Exit Sub
End If

'其实 InitallyInterface() 中调用
If Called = 被菜单中的网络对战调用 Then
   mnuOptionShowTalk.Visible = bVisible
End If
mnuOptionShowTalk.Checked = bVisible
mnuEdit.Visible = bVisible
mnuOptionNet.Visible = bVisible
With txtNetTalk
     If bVisible Then
        .Top = PicQiPang.Top
        .Left = PicQiPang.Left + PicQiPang.Width + 100
        .Height = PicQiPang.Height * 2 / 3
        .Width = Me.ScaleWidth - .Left
     End If
     .Visible = bVisible
End With
With txtNetInput
     If bVisible Then
        .Top = txtNetTalk.Top + txtNetTalk.Height
        .Left = txtNetTalk.Left
        .Width = txtNetTalk.Width
        .Height = PicQiPang.Height / 3
     End If
     .Visible = bVisible
End With
End Sub

Private Function SetFirstWork() As Boolean
'返回真值为红方先走,假值为圉方先走

End Function

'发送对话
'CHR（1）左边的为说话人的名字，右边为说的话，
'以两个 CHR(13).CHR(10) 结束.
Public Function SendTalkText(Optional Sender As _
       Enum_SendTalk = Enum_SendTalk.发送默认值, _
       Optional sString As String, _
       Optional lPara As Long)
Select Case Sender
Case Enum_SendTalk.发送默认值
   With txtNetTalk
        .SelStart = Len(.Text)
        .SelColor = tNet.NetTalkTextColorLocal
        .SelText = tNet.NetTalkUserNameLocal + _
            Chr(1) + txtNetInput.Text + Chr(13) + Chr(10)
   End With
   Winsock1.SendData tNet.NetTalkUserNameLocal + txtNetInput.Text + Chr(13) + Chr(10)
   txtNetInput.Text = ""
  
End Select
End Function

'改变用户对话的颜色
'CHR（1）左边的为说话人的名字，右边为说的话，
'以两个 CHR(13).CHR(10) 结束.
Private Function ChangeRichTextColor()
Dim S As String, ss As String
Dim I As Long
With txtNetInput
     S = .Text
     .Text = txtNetTalk.Text
     txtNetTalk.Text = ""
     .Visible = False
     '以两个 CHR(13).CHR(10) 做为一段对话的分隔符
     I = GetEndPostion(.Text, Chr(10))
     Do While I
        Select Case Left(.Text, InStr(1, .Text, Chr(1)) - 1)
               Case tNet.NetTalkUserNameLocal
                    txtNetTalk.SelColor = tNet.NetTalkTextColorLocal
                    txtNetTalk.SelText = Left(.Text, I)
               Case tNet.NetTalkTextNameRemote
                    txtNetTalk.SelColor = tNet.NetTalkTextColorRemote
                    txtNetTalk.SelText = Left(.Text, I)
               Case Else
                    txtNetTalk.SelColor = tNet.NetTalkTextColorRemoteOrther
                    txtNetTalk.SelText = Left(.Text, I)
        End Select
        .Text = Right(.Text, Len(.Text) - I)
        I = GetEndPostion(.Text, Chr(10))
     Loop
     txtNetTalk.SelStart = Len(txtNetTalk.Text)
     .Text = S
     .Visible = True
End With
End Function

'得到两个连续相同的字符 (CHR(13).CHR(10)) 的位置
Private Function GetEndPostion(sString As String, Char As String, Optional StartPostion = 1) As Long
StartPostion = InStr(StartPostion, sString, Char)
If StartPostion = 0 Then GetEndPostion = 0: Exit Function
If Chr(13) = Mid(sString, StartPostion + 1, 1) And _
Chr(10) = Mid(sString, StartPostion + 2, 1) Then
      GetEndPostion = StartPostion + 2
Else
   GetEndPostion = GetEndPostion(sString, Char, StartPostion + 1)
End If
End Function

Private Sub SetUserName(Optional Flag As Enum_SetUserName = Enum_SetUserName.设置黑方用户名从Initally中调用)
Dim S As String
Select Case Flag
       Case Enum_SetUserName.设置黑方用户名从Initally中调用
            If s对战模式 = " 网络对战 " Then
               If ZouQiPangShu = 0 Then
                  If yF.Name = "" Then
                     yF.Name = InputBox(s请输入本地用户名, , "黑方")
                     tNet.NetTalkUserNameLocal = yF.Name & ":"
                  End If
                  jF.Name = InputBox(s请输入远地用户名, , "红方")
                  tNet.NetTalkTextNameRemote = jF.Name & ":"
                  LabJF.Caption = jF.sName & ": " & jF.Name
                  LabYF.Caption = yF.sName & ": " & yF.Name
                  If SetFirstWork Then
                     SetNetPara False, 在设置用户时调用
                  Else
                     SetNetPara , 在设置用户时调用
                  End If
               End If
            Else
               SetNetPara False, 在设置用户时调用
               jF.Color = vbRed '甲方的颜色
               jF.sName = "红方"
               jF.Name = ""
               yF.Color = vbBlue '乙方的颜色
               yF.sName = "黑方"
               yF.Name = ""
               LabJF.Caption = jF.sName
               LabYF.Caption = yF.sName
            End If
            If ZouQiPangShu Mod 2 Then
                  qStep = 定义乙方
                  ZouQiPangShu = ZouQiPangShu + 1
            Else
                  qStep = 定义甲方
                  ZouQiPangShu = ZouQiPangShu + 1
            End If
       Case Enum_SetUserName.设置用户标签位置
            With PicQiPang
                 LabJF.Top = .Top - LabJF.Height
                 LabYF.Top = .Top + .Height
                 LabYF.Left = .Left + (.Width - LabYF.Width) / 2
                 LabJF.Left = LabYF.Left
            End With
            LabJF.Visible = True
            LabYF.Visible = True
End Select
End Sub
