VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   0  'None
   Caption         =   "��ͼ"
   ClientHeight    =   5400
   ClientLeft      =   45
   ClientTop       =   10860
   ClientWidth     =   6840
   LinkTopic       =   "Form1"
   ScaleHeight     =   360
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   456
   StartUpPosition =   2  '��Ļ����
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
            Object.Tag             =   "ѡȡĿ��  (��ѡ)"
            ImageKey        =   "pointselect"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "selectobjectfield"
            Object.ToolTipText     =   "Ŀ��ѡȡ  (����ѡ)"
            ImageKey        =   "selectfield"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "allselect"
            Object.ToolTipText     =   "ȫѡ"
            ImageKey        =   "all"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "exitselect"
            Object.ToolTipText     =   "�˳�ѡȡ"
            ImageKey        =   "cls"
         EndProperty
      EndProperty
   End
   Begin VB.TextBox tishitext2 
      Height          =   270
      Left            =   8040
      TabIndex        =   3
      ToolTipText     =   "�����¹�꽡��������򻥻�"
      Top             =   6240
      Width           =   975
   End
   Begin VB.TextBox tishitext1 
      Height          =   270
      Left            =   5160
      TabIndex        =   2
      ToolTipText     =   "�����¹�꽡��������򻥻�"
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
            Object.ToolTipText     =   "�߶λ�Բ���Ķ˵�"
            ImageKey        =   "end"
            Style           =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "snapelinemid"
            Object.ToolTipText     =   "��׽�߶λ�Բ�����е�"
            ImageKey        =   "mid"
            Style           =   1
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "snapecirclepoint"
            Object.ToolTipText     =   "��׽Բ��"
            ImageKey        =   "cirpoint"
            Style           =   1
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "snapemisspoint"
            Object.ToolTipText     =   "��׽����"
            ImageKey        =   "miss"
            Style           =   1
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "exitsnape"
            Object.ToolTipText     =   "�˳���׽"
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
            Object.ToolTipText     =   "����"
            ImageKey        =   "Rectangle"
            Style           =   5
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "zhen"
            Object.ToolTipText     =   "������"
            ImageKey        =   "same"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "tree"
            Object.ToolTipText     =   "������"
            ImageKey        =   "tree"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "stree"
            Object.ToolTipText     =   "�����Ǳ�"
            ImageKey        =   "stree"
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "six"
            Object.ToolTipText     =   " ��������"
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
            Object.ToolTipText     =   "Բ"
            ImageKey        =   "circle"
            Style           =   5
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "Arc"
            Object.ToolTipText     =   "Բ��"
            ImageKey        =   "Arc"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "Ellipse"
            Object.ToolTipText     =   "��Բ"
            ImageKey        =   "Ellipse"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "shan"
            Object.ToolTipText     =   "�� ��"
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
            Object.ToolTipText     =   "ֱ��"
            ImageKey        =   "Line"
            Style           =   5
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "������"
            Object.ToolTipText     =   "������"
            ImageKey        =   "mulline"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "Line Style"
            Object.ToolTipText     =   "����"
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
            Object.ToolTipText     =   "�������ļ�"
            ImageKey        =   "New"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "���ļ�"
            ImageKey        =   "Open"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "�����ļ�"
            ImageKey        =   "Save"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Print"
            Object.ToolTipText     =   "��ӡ"
            ImageKey        =   "Print"
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Delete"
            Object.ToolTipText     =   "ɾ��"
            ImageKey        =   "Delete"
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Undo"
            Object.ToolTipText     =   "ȡ��"
            ImageKey        =   "Undo"
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Redo"
            Object.ToolTipText     =   "�ػ�"
            ImageKey        =   "Redo"
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Copy"
            Object.ToolTipText     =   "����"
            ImageKey        =   "Copy"
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cut"
            Object.ToolTipText     =   "����"
            ImageKey        =   "Cut"
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Paste"
            Object.ToolTipText     =   "ճ��"
            ImageKey        =   "Paste"
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Help"
            Object.ToolTipText     =   "����"
            ImageKey        =   "Help"
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "text"
            Object.ToolTipText     =   "����"
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
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu meunnewfile 
         Caption         =   "���ļ�   (&N)"
      End
      Begin VB.Menu meunopenfile 
         Caption         =   "���ļ� (&O)"
      End
      Begin VB.Menu meunsavefile 
         Caption         =   "�����ļ� (&S)"
      End
      Begin VB.Menu meun1 
         Caption         =   "-"
      End
      Begin VB.Menu meunfiletool 
         Caption         =   "��ʾ�ļ�����(&S)"
         Checked         =   -1  'True
      End
      Begin VB.Menu meun2 
         Caption         =   "-"
         Index           =   1
      End
      Begin VB.Menu meunexit 
         Caption         =   "�˳�     (&E)"
      End
   End
   Begin VB.Menu meunedit 
      Caption         =   "�༭(&E)"
      Begin VB.Menu meunerase 
         Caption         =   "���(&E)"
      End
      Begin VB.Menu meunoops 
         Caption         =   "�ָ�(&R)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meuncut 
         Caption         =   "����(&T)"
      End
      Begin VB.Menu meuncopy 
         Caption         =   "����(&C)"
      End
      Begin VB.Menu meunpase 
         Caption         =   "ճ��(&P)"
      End
      Begin VB.Menu meun15 
         Caption         =   "-"
         Index           =   1
      End
      Begin VB.Menu meunmove 
         Caption         =   "�ƶ�(&M)"
      End
      Begin VB.Menu meunroun1 
         Caption         =   "��ת(&R)"
         Begin VB.Menu meunround 
            Caption         =   "ѡ�з�Χ������ת"
         End
         Begin VB.Menu meunrounda 
            Caption         =   "����һ����ת"
         End
      End
      Begin VB.Menu meunroin 
         Caption         =   "��ת(&F)"
         Begin VB.Menu meunroundh 
            Caption         =   "ˮƽ��ת"
         End
         Begin VB.Menu meunroundv 
            Caption         =   "��ֱ��ת"
         End
      End
      Begin VB.Menu menumirror0 
         Caption         =   "����(&M)"
         Begin VB.Menu meunmirror1 
            Caption         =   "����(����ͼ��)"
         End
         Begin VB.Menu meunmirror 
            Caption         =   "����(������ԭͼ��)"
         End
      End
      Begin VB.Menu meunhmirror 
         Caption         =   "��ѡһֱ������"
         Visible         =   0   'False
      End
      Begin VB.Menu meunvmirror 
         Caption         =   "��ֱ����"
         Visible         =   0   'False
      End
      Begin VB.Menu meunarray 
         Caption         =   "����"
         Enabled         =   0   'False
         Begin VB.Menu meunrectanglararray 
            Caption         =   "���γ���(&R)"
         End
         Begin VB.Menu meunpolararray 
            Caption         =   "Բ�γ���(&P)"
         End
      End
      Begin VB.Menu meun4 
         Caption         =   "-"
      End
      Begin VB.Menu meunbreak 
         Caption         =   "�ж�(&B)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meuntrim 
         Caption         =   "�޼�(&T)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunfillet 
         Caption         =   "Բ��(&F)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunchamfer 
         Caption         =   "�н�(&C)"
         Enabled         =   0   'False
      End
      Begin VB.Menu meun5 
         Caption         =   "-"
      End
      Begin VB.Menu meunedittool 
         Caption         =   "��ʾ�༭����(&S)"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meuntool 
      Caption         =   "��ͼ(&T)"
      Begin VB.Menu meuncolse 
         Caption         =   "����"
         Visible         =   0   'False
      End
      Begin VB.Menu meuncols 
         Caption         =   "���"
         Visible         =   0   'False
      End
      Begin VB.Menu meunredo 
         Caption         =   "ȡ��"
         Visible         =   0   'False
      End
      Begin VB.Menu meunu 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu meunpoint 
         Caption         =   "��"
         Enabled         =   0   'False
         Begin VB.Menu meunʵ�ĵ� 
            Caption         =   "ʵ�ĵ�"
         End
         Begin VB.Menu meuncrosspoint 
            Caption         =   "ʮ�ֵ�"
         End
         Begin VB.Menu meuncirlepoint 
            Caption         =   "Բ��"
         End
         Begin VB.Menu meun����� 
            Caption         =   "�����"
         End
      End
      Begin VB.Menu meunline0 
         Caption         =   "ֱ��......     "
         Begin VB.Menu meunline 
            Caption         =   "ֱ��"
         End
         Begin VB.Menu meun������ 
            Caption         =   "������"
         End
      End
      Begin VB.Menu meun���� 
         Caption         =   "������"
         Begin VB.Menu meun������ 
            Caption         =   "������"
         End
         Begin VB.Menu meun�������� 
            Caption         =   "��������"
         End
         Begin VB.Menu meun�������� 
            Caption         =   "��������"
            Visible         =   0   'False
         End
      End
      Begin VB.Menu meunbox 
         Caption         =   "����"
      End
      Begin VB.Menu meun����� 
         Caption         =   "�������"
         Begin VB.Menu meun������ 
            Caption         =   "������"
         End
         Begin VB.Menu meun������� 
            Caption         =   "�������"
            Visible         =   0   'False
         End
         Begin VB.Menu meun�������� 
            Caption         =   "��������"
         End
         Begin VB.Menu meun������� 
            Caption         =   "�������"
            Enabled         =   0   'False
         End
      End
      Begin VB.Menu meuncircle0 
         Caption         =   "Բ  ......"
         Index           =   0
         Begin VB.Menu meuncircle 
            Caption         =   "Բ"
         End
         Begin VB.Menu meun��Բ 
            Caption         =   "��Բ"
         End
         Begin VB.Menu meunarc 
            Caption         =   "Բ��"
         End
         Begin VB.Menu meun���� 
            Caption         =   "����"
         End
      End
      Begin VB.Menu meun���� 
         Caption         =   "����"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunpath 
         Caption         =   "����"
         Enabled         =   0   'False
      End
      Begin VB.Menu meuntext 
         Caption         =   "�ı�"
      End
      Begin VB.Menu meun3 
         Caption         =   "-"
         Index           =   1
      End
      Begin VB.Menu meundisptool 
         Caption         =   "��ʾ��ͼ����(&S)"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunoselect 
      Caption         =   "ѡȡ(&S)"
      Begin VB.Menu meunobject0 
         Caption         =   "ѡȡĿ��"
         Begin VB.Menu meunselectobject 
            Caption         =   "ѡȡĿ��(��ѡȡ)"
         End
         Begin VB.Menu menuselectobject 
            Caption         =   "ѡȡĿ��(����ѡȡ)"
         End
      End
      Begin VB.Menu meun14 
         Caption         =   "ѡ��"
      End
      Begin VB.Menu meunselectline 
         Caption         =   "ѡֱ��"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselectrectangle 
         Caption         =   "ѡ����"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselect������ 
         Caption         =   "ѡ������"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselcet������ 
         Caption         =   "������"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselectcircle 
         Caption         =   "ѡȡԲ"
         Visible         =   0   'False
      End
      Begin VB.Menu meunselectarc 
         Caption         =   "ѡԲ��������"
      End
      Begin VB.Menu meun32 
         Caption         =   "-"
      End
      Begin VB.Menu meunallselect 
         Caption         =   "ȫѡ"
      End
      Begin VB.Menu meun17 
         Caption         =   "-"
         Index           =   0
      End
      Begin VB.Menu meunexitselect 
         Caption         =   "�˳�ѡȡ"
      End
      Begin VB.Menu meun20 
         Caption         =   "-"
      End
      Begin VB.Menu meunselecttool 
         Caption         =   "��ʾѡȡ����(&S)"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunobjectsnpae 
      Caption         =   "Ŀ�겶׽(&N)"
      Begin VB.Menu meunselectsinglepoint 
         Caption         =   "ѡȡ������"
      End
      Begin VB.Menu meunselectendpoint 
         Caption         =   "ѡȡ�߶λ�Բ���Ķ˵�"
      End
      Begin VB.Menu meunselectmidpoint 
         Caption         =   "ѡȡ�߶λ�Բ�����е�"
      End
      Begin VB.Menu meunselectcirclepoint 
         Caption         =   "ѡȡԲ��"
      End
      Begin VB.Menu meunsnapemiss 
         Caption         =   "����"
      End
      Begin VB.Menu meunexitsnape 
         Caption         =   "�˳���׽"
         Checked         =   -1  'True
      End
      Begin VB.Menu mwunuu 
         Caption         =   "-"
      End
      Begin VB.Menu meunshowsnapetool 
         Caption         =   "��ʾ��׽����"
      End
   End
   Begin VB.Menu meunview 
      Caption         =   "��ͼ(&V)"
      Begin VB.Menu meunmouse��״ 
         Caption         =   "�����״"
         Begin VB.Menu meunmousecross 
            Caption         =   "ʮ�ֹ��"
         End
         Begin VB.Menu meunmousebigcross 
            Caption         =   "��ʮ�ֹ��"
         End
         Begin VB.Menu meunmouse���� 
            Caption         =   "���ι��"
         End
      End
      Begin VB.Menu meun_ 
         Caption         =   "-"
      End
      Begin VB.Menu meunattrib 
         Caption         =   "����"
         Enabled         =   0   'False
         Begin VB.Menu meunlayer 
            Caption         =   "ͼ��"
         End
         Begin VB.Menu meuncolor 
            Caption         =   "��ɫ"
         End
      End
      Begin VB.Menu meun21 
         Caption         =   "-"
         Index           =   0
      End
      Begin VB.Menu meunzoomout 
         Caption         =   "�Ŵ�       (&O)"
      End
      Begin VB.Menu meunzoomin 
         Caption         =   "��С       (&I)"
      End
      Begin VB.Menu meunselectzoom 
         Caption         =   "ѡ������   (&S)"
      End
      Begin VB.Menu meun�ָ�ԭ�ߴ� 
         Caption         =   "�ָ�ԭ�ߴ� (&R)"
      End
      Begin VB.Menu meun16 
         Caption         =   "-"
      End
      Begin VB.Menu meungirl 
         Caption         =   "��ʾդ��"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunoption1 
      Caption         =   "ѡ��(O)"
      Begin VB.Menu meunoption 
         Caption         =   "ѡ��(&O)"
      End
      Begin VB.Menu meun12 
         Caption         =   "-"
      End
      Begin VB.Menu meuntishi 
         Caption         =   "��ʾ��ʾ��"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunwindows 
      Caption         =   "����(&W)"
   End
   Begin VB.Menu meunhelp 
      Caption         =   "����(&H)"
      Begin VB.Menu meunabout 
         Caption         =   "����"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'������
Option Explicit

'Private Declare Function ShowCursor Lib "user32" (ByVal bShow As Long) As Long
Dim vartoolbar As Toolbar

Public Sub Savecommvar()  '���浱ǰ����
    user.Savemode = Form1.cad.DrawMode '���浱ǰģʽ
    user.Savecommvar.width = Form1.cad.DrawWidth
    user.Savecommvar.style = Form1.cad.DrawStyle
End Sub

Public Sub redocommvar()  '�ָ���ǰ����
    Form1.cad.DrawMode = user.Savemode   '�ָ���ǰģʽ
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

'��ͼ�˵�
Private Sub meuncolse_Click()   '����
        '��ͼ����,����������,��δ�����Բ,Բ��,����,��Բ
        user.drawflag = 1
        draw.redraw
End Sub

Private Sub meuncols_Click()   '���
Dim i
        '����ǰ����Ϊ������ʱ,�洢������,��ʹ�����߳�Ϊ��յ�����
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

Private Sub meunredo_Click()  'ȡ��
        'ȡ����ǰ����ͼ����
        Select Case user.CurrentOperist
               Case "Line"
                    ReDim Preserve user.LineType(UBound(user.LineType) - 1)
               Case "������"
               
               Case "Rectangle"
                     ReDim Preserve user.RectangleType(UBound(user.RectangleType) - 1)
               Case "������", "��������"
                    ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) - 1)
               Case "������"
                    ReDim Preserve user.SameRectangleType(UBound(user.SameRectangleType) - 1)
               Case "��������"
                     ReDim Preserve user.SixegdeType(UBound(user.SixegdeType) - 1)
               Case "circle"
                     ReDim Preserve user.CircleType(UBound(user.CircleType) - 1)
               Case "arc", "����"
                     ReDim Preserve user.ArcType(UBound(user.ArcType) - 1)
               Case "Ellipse"
                    ReDim Preserve user.EllipseType(UBound(user.EllipseType) - 1)
        End Select
        draw.redraw
End Sub

Private Sub meunline_Click()
        user.CurrentOperist = "Line"
End Sub

Private Sub meun������_Click()
        user.CurrentOperist = "������"
        user.drawflag = 1
End Sub

Private Sub meun������_Click()
        user.CurrentOperist = "������"
        user.drawflag = 1
End Sub

Private Sub meun��������_Click()
        user.CurrentOperist = "��������"
End Sub

Private Sub meun��������_Click()
        user.CurrentOperist = "�ȱ�������"
        user.drawflag = 1
End Sub

Private Sub meunbox_Click()     '����
     user.CurrentOperist = "Rectangle"
End Sub

Private Sub meun������_Click()
            user.CurrentOperist = "������"
            user.drawflag = 1
End Sub

Private Sub meun��������_Click()
       user.CurrentOperist = "��������"
       user.drawflag = 1
End Sub

Private Sub meuncircle_Click()  'Բ
        user.CurrentOperist = "circle"
End Sub

Private Sub meunarc_Click()  'Բ��
           user.CurrentOperist = "Arc"
           user.drawflag = 1
End Sub

Private Sub meun����_Click()
        user.CurrentOperist = "����"
        user.drawflag = 1
End Sub

Private Sub meun��Բ_Click()
            user.CurrentOperist = "Ellipse"
            user.drawflag = 1
End Sub

Private Sub meunʵ�ĵ�_Click()
        user.CurrentOperist = "ʵ�ĵ�"
End Sub

Private Sub meuntext_Click()
        user.CurrentOperist = "text"
End Sub

Private Sub meundisptool_Click()   '��ʾ��ͼ����
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

'Ŀ��ѡȡ
Private Sub meunselectline_Click()
        user.CurrentOperist = "selectline"
End Sub

Private Sub meunselectobject_Click()
        user.CurrentOperist = "selectobject"
End Sub

Private Sub menuselectobject_Click()
        user.CurrentOperist = "fieldselectobject"
End Sub

Private Sub meunallselect_Click()    'ȫѡ
        user.LinePoint = 1
        user.ArcPoint = 1
        user.CirclePoint = 1
        user.ThreeanglePoint = 1
        user.RectanglePoint = 1
        user.SixegdePoint = 1
        user.RectanglefourPoint = 1
        user.SameRectanglePoint = 1
        '�ӵ��ָ��
        
        '��ʾѡȡ��Ŀ��
        With user.SnapefieldType
             .x1 = -1
             .y1 = -1
             .x2 = -1
             .y2 = -1
        End With
        snape.showselectobject Form1.cad, True
End Sub

Private Sub meunexitselect_Click()   '�˳�ѡȡ
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

'��ʾѡȡ������
Private Sub meunselecttool_Click()
        If meunselecttool.Checked Then
           meunselecttool.Checked = False
           Toolbar2.Visible = False
           If meunshowsnapetool.Checked = False Then '��ʾĿ��ѡȡ��Ŀ�겶׽�й�
                  '�޸�����
                   desk.left = desk.left - snapetool.width
                   desk.width = desk.width + snapetool.width
                   '�޸�ˮƽ������
                   user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
           End If
        Else
           meunselecttool.Checked = True
           Toolbar2.Visible = True
           If meunshowsnapetool.Checked = False Then '��ʾĿ��ѡȡ��Ŀ�겶׽�й�
                  '�޸�����
                   desk.left = desk.left + snapetool.width
                   desk.width = desk.width - snapetool.width
                   '�޸�ˮƽ������
                   user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
           End If
        End If
        
End Sub

'Ŀ�겶׽�˵�
Private Sub meunselectendpoint_Click()    '��׽�߶λ�Բ���Ķ˵�
            '����˳�Ŀ�겶׽��ѡ��
            meunexitsnape.Checked = False
        If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "selectendpoint", vbBinaryCompare) = 0 Then
           user.SnapeOperist = user.SnapeOperist + "selectendpoint"
           meunselectendpoint.Checked = True   '��ʾ��ѡ��
           user.Mousesnape = "snapecirle"  '��׽ʱ������״,Ӱ�����snapemouse
          '���¹������ϵİ�Ť
          '���²�׽�˵㰴Ť
          snapetool.Buttons.Item("lineendpoint").Value = tbrPressed
        End If
End Sub

Private Sub meunselectmidpoint_Click()   '��׽�߶λ�Բ�����е�
            '����˳�Ŀ�겶׽��ѡ��
            meunexitsnape.Checked = False
If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "snapelinemid", vbBinaryCompare) = 0 Then
        user.SnapeOperist = user.SnapeOperist + "snapelinemid" '��׽����
        meunselectmidpoint.Checked = True    '��ʾ��ѡ��
        user.Mousesnape = "snapecirle"  '��׽ʱ������״,Ӱ�����snapemouse
        '���¹������ϵİ�Ť
        snapetool.Buttons.Item("snapelinemid").Value = tbrPressed
End If
End Sub

Private Sub meunselectcirclepoint_Click()   '��׽Բ��
            '����˳�Ŀ�겶׽��ѡ��
            meunexitsnape.Checked = False
If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "snapecirclepoint", vbBinaryCompare) = 0 Then
         meunselectcirclepoint.Checked = True '��ʾ��ѡ��
         user.SnapeOperist = user.SnapeOperist + "snapecirclepoint"
         user.Mousesnape = "snapecirle"  '��׽ʱ������״,Ӱ�����snapemouse
          '���¹������ϵİ�Ť
        snapetool.Buttons.Item("snapecirclepoint").Value = tbrPressed
End If
End Sub

Private Sub meunsnapemiss_Click()  '��׽����
            '����˳�Ŀ�겶׽��ѡ��
            meunexitsnape.Checked = False
If user.SnapeOperist = "null" Or InStrB(1, user.SnapeOperist, "snapemisspoint", vbBinaryCompare) = 0 Then
         meunsnapemiss.Checked = True
         '�˹���ûд��
         user.Mousesnape = "snapecirle"  '��׽ʱ������״,Ӱ�����snapemouse
         '��׽����
         user.SnapeOperist = user.SnapeOperist + "snapemisspoint"
        '���¹������ϵİ�Ť
        snapetool.Buttons.Item("snapemisspoint").Value = tbrPressed
End If
End Sub

Private Sub meunexitsnape_Click()  '�˳���׽״̬
Dim i
            '������и�ѡ��
            meunselectendpoint.Checked = False  '�˵�
            meunselectmidpoint.Checked = False '�е�
            meunselectcirclepoint.Checked = False 'Բ��
            meunsnapemiss.Checked = False '����
            '��ʾ��ѡ��
            meunexitsnape.Checked = True
            user.SnapeOperist = "null"
            user.Mousesnape = "null"  '��׽ʱ������״,Ӱ�����snapemouse
            SnapeMouseFlag = 0 '���user�д�ֵ����
            '���𹤾����ϵİ�Ť
            For i = 1 To snapetool.Buttons.Count   '�������а�Ť
                snapetool.Buttons(i).Value = tbrUnpressed
            Next i
        
End Sub

Public Sub meunshowsnapetool_Click()   '��ʾ��׽������
       If meunshowsnapetool.Checked Then
               meunshowsnapetool.Checked = False
               snapetool.Visible = False
               If meunselecttool.Checked = False Then '��ʾĿ��ѡȡ��Ŀ�겶׽�й�
                  '�޸�����
                   desk.left = desk.left - snapetool.width
                   desk.width = desk.width + snapetool.width
                   '�޸�ˮƽ������
                   user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
               End If
       Else
               meunshowsnapetool.Checked = True
               '��ʾ����
               snapetool.Visible = True
               If meunselecttool.Checked = False Then '��ʾĿ��ѡȡ��Ŀ�겶׽�й�
                  '�޸�����
                  desk.left = desk.left + snapetool.width
                  desk.width = desk.width - snapetool.width
                  '�޸�ˮƽ������
                  user.Scrollbar Abs(Form1.cad.left), Abs(Form1.cad.top)
               End If
               
       End If
End Sub

'��ͼ�˵�
'�����״�˵�
Private Sub meunmousecross_Click()   'ʮ�ֹ��
user.Usermouse��״.Checked = False
cad.MousePointer = MousePointerConstants.vbCrosshair
Set user.Usermouse��״ = meunmousecross
meunmousecross.Checked = True
End Sub

Private Sub meunmousebigcross_Click()    '��ʮ�ֹ��
'Dim x
'x = ShowCursor(False)
user.Usermouse��״.Checked = False
'cad.MousePointer = MousePointerConstants.vbCrosshair
cad.MousePointer = VBRUN.vbUseDefaultCursor
Set user.Usermouse��״ = meunmousebigcross
meunmousebigcross.Checked = True
End Sub

Private Sub meunmouse����_Click()
user.Usermouse��״.Checked = False
cad.MousePointer = MousePointerConstants.vbArrow
Set user.Usermouse��״ = meunmouse����
meunmouse����.Checked = True
End Sub

Private Sub meunzoomout_Click()  '�Ŵ�
On Error Resume Next
        user.SnapeField = user.SnapeField / 2 '�Ŵ�׽����
        cad.top = cad.top - cad.height / 2
        cad.left = cad.left - cad.width / 2
        cad.width = cad.width * 2
        cad.height = cad.height * 2
        cad.ScaleHeight = cad.ScaleHeight / 2
        cad.scalewidth = cad.scalewidth / 2
        user.Scrollbar Abs(cad.left), Abs(cad.top)  '������
        draw.redraw
End Sub

Private Sub meunzoomin_Click()   '��С
On Error Resume Next
        user.SnapeField = user.SnapeField * 2 '��С��׽����
        cad.top = cad.top + cad.height / 4
        cad.left = cad.left + cad.width / 4
        cad.width = cad.width / 2
        cad.height = cad.height / 2
        cad.ScaleHeight = cad.ScaleHeight * 2
        cad.scalewidth = cad.scalewidth * 2
        user.Scrollbar Abs(cad.left), Abs(cad.top)  '������
        draw.redraw
End Sub

Private Sub meunselectzoom_Click()
        user.CurrentOperist = "selectzoom"
End Sub

Private Sub meun�ָ�ԭ�ߴ�_Click()
        cad.Move user.paper.left, user.paper.top, user.paper.width, user.paper.height
        cad.ScaleHeight = user.paper.scaleheigt
        cad.scalewidth = user.paper.scalewidth
        draw.redraw
        'user.scrollbar (Form1.cad.width - Form1.desk.scalewidth) / 2, (Form1.cad.Height - Form1.desk.ScaleHeight) / 2
End Sub

Private Sub meungirl_Click()  '��ʾդ��
            If meungirl.Checked = True Then
               meungirl.Checked = False
            Else
               meungirl.Checked = True
            End If
End Sub

'ѡ��˵�
Private Sub meunoption_Click()
   frmOptions.Show 1, Form1
End Sub

Private Sub meuntishi_Click()   '��ʾ״̬��
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

'�ļ��˵�
Private Sub meunnewfile_Click()
On Error Resume Next
        If user.CurrentOperistFlag Then   '�����ǰ��������,����б���
           meunsavefile_Click
        End If
        user.Showselectpaperform = True    '��־�Ƿ�����ļ�������,���Ǵӳ�����ʱ����
        user.Initiale     '�����ǰ������
        selectpaper.Show 1, Form1
        user.Showselectpaperform = False
        user.CurrentOperistFlag = False     '���ļ�δ�����κβ���
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
     user.CurrentOperistFlag = False  '��־�Ƿ�����˲���
End Sub

Private Sub meunexit_Click()
Dim exi
If user.CurrentOperistFlag Then
    exi = MsgBox("��Ҫ�����ļ���?", vbQuestion + vbYesNoCancel)
    If exi = vbYes Then
       user.SaveFile
    Else
       If exi = 2 Then   '����ȡ����ʱ
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

Private Sub meunselcet������_Click()
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

'��׽����
Private Sub snapetool_ButtonClick(ByVal Button As MSComctlLib.Button)
          Select Case Button.Key
                 Case "lineendpoint"   '��׽�˵�
                       meunselectendpoint_Click
                 Case "snapelinemid"  '��׽�е�
                       meunselectmidpoint_Click
                 Case "snapecirclepoint"  '��׽Բ��
                       meunselectcirclepoint_Click
                 Case "snapemisspoint"   '��׽����
                       meunsnapemiss_Click
                 Case "exitsnape"    '�˳���׽
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
            '���ù��߰�ť
            vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
            Set vartoolbar = Toolline      '��ֵ
            vartoolbar.Tag = Button.Key
            '��ʾ���а�ť������������ť
            For i = 1 To Toolline.Buttons.Count
                Toolline.Buttons.Item(i).Visible = True
                Button.Value = tbrUnpressed
            Next i
            '����������ť�����°�ť
            Button.style = tbrDefault
            Button.Value = tbrPressed
End Sub

Private Sub Toolline_ButtonClick(ByVal Button As MSComctlLib.Button)
 Dim i
        '���ù��߰�ť
        vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
        Set vartoolbar = Toolline         '��ֵ
        vartoolbar.Tag = Button.Key
        '�������а�ť
        For i = 1 To Toolline.Buttons.Count
                Toolline.Buttons.Item(i).Visible = False
        Next i
        '��ʾ������ť�����°�ť
        Button.Value = tbrPressed
        Button.style = tbrDropdown
        Button.Visible = True
        '����ǰ������ֵ
        Select Case Button.Key
               Case "Line"
                    meunline_Click
               Case "������"
                    meun������_Click
               Case "Line Style"
                    meunoption_Click
        End Select
End Sub

Private Sub Toolrectangle_ButtonDropDown(ByVal Button As MSComctlLib.Button)
 Dim i
            '���ù��߰�ť
            vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
            Set vartoolbar = Toolrectangle      '��ֵ ��
            vartoolbar.Tag = Button.Key
            '��ʾ���а�ť������������ť
            For i = 1 To Toolrectangle.Buttons.Count    '��
                Toolrectangle.Buttons.Item(i).Visible = True  '��
                Button.Value = tbrUnpressed
            Next i
            '����������ť�����°�ť
            Button.style = tbrCheck
            Button.Value = tbrPressed
End Sub

Private Sub Toolrectangle_ButtonClick(ByVal Button As MSComctlLib.Button)
Dim i
       '�������а�ť
        For i = 1 To Toolrectangle.Buttons.Count
                Toolrectangle.Buttons.Item(i).Visible = False
        Next i
        '���ù��߰�ť
        vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
        Set vartoolbar = Toolrectangle     '��ֵ
        vartoolbar.Tag = Button.Key
        '��ʾ������ť�����°�ť
        Button.Visible = True
        Button.style = tbrDropdown
        Button.Value = tbrPressed
        '����ǰ������ֵ
        Select Case Button.Key
               Case "rectangle"
                     meunbox_Click
               Case "stree"
                    meun��������_Click
               Case "tree"
                    meun������_Click
               Case "six"
                    meun��������_Click
               Case "zhen"
                    meun������_Click
        End Select
End Sub

Private Sub Toolcircle_ButtonClick(ByVal Button As MSComctlLib.Button)
Dim i
       '���ù��߰�ť
        vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
        Set vartoolbar = Toolcircle     '��ֵ
        vartoolbar.Tag = Button.Key
        '�������а�ť
        For i = 1 To Toolcircle.Buttons.Count
                Toolcircle.Buttons.Item(i).Visible = False
        Next i
        '��ʾ������ť�����°�ť
        Button.Visible = True
        Button.style = tbrDropdown
        Button.Value = tbrPressed
        '����ǰ������ֵ
        Select Case Button.Key
               Case "circle"
                    meuncircle_Click
               Case "Ellipse"
                    meun��Բ_Click
               Case "Arc"
                    meunarc_Click
               Case "shan"
                    meun����_Click
        End Select
                    
End Sub

Private Sub Toolcircle_ButtonDropDown(ByVal Button As MSComctlLib.Button)
 Dim i
            '���ù��߰�Ť
            vartoolbar.Buttons.Item(vartoolbar.Tag).Value = tbrUnpressed
            Set vartoolbar = Toolcircle     '��ֵ
            vartoolbar.Tag = Button.Key
            '��ʾ���а�ť������������ť
            For i = 1 To Toolcircle.Buttons.Count
                Toolcircle.Buttons.Item(i).Visible = True
                Button.Value = tbrUnpressed
            Next i
            '���߰�ť����
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
                    '����ʾ����ֱ��������������
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
                    '����ʾ����ֱ��������������
                    user.KeyInputData X, Y
                    
               Case vbKeyUp, vbKeyDown
                    tishitext1.SetFocus
        End Select
End Sub

Public Sub cad_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim mode
'���һ����ʱ,��ʾ�˵�
If Button = VBRUN.vbRightButton Then
   user.RightChickMenu X, Y
End If
 
'��shift������ʱ
     If Shift = VBRUN.ShiftConstants.vbShiftMask Then
        If Abs(X - user.Mouseleftdownx) < Abs(Y - user.mouseleftdowny) Then
           X = user.Mouseleftdownx
        Else
           Y = user.mouseleftdowny
        End If
     End If

'�жϵ�����Ƿ��Ƶ���ͼ�߽�
'If Button = vbLeftButton Then
'   If X < user.deskx1 Or X > user.deskx2 Or Y < user.desky1 Or Y > user.desky2 Then
'      user.movepaper X, Y, Form1.cad         '�Զ��ƶ�ͼֽ
'   End If
'End If

'user.tishiinitale (button)
'��ֹ��Բ���ĵ�������������������,����ֱ��
If (user.CurrentOperist = "Arc" Or user.CurrentOperist = "����") And user.drawflag = 2 Then
   user.drawflag = 4
End If

 Dim snapepoint As snapepoint '���user�е���������
 With snapepoint
      .r = -1
      .X = X
      .Y = Y
      '�����˳���ܱ仯
      '�߶λ�Բ�����е�
      If InStrB(1, user.SnapeOperist, "selectendpoint", vbBinaryCompare) <> 0 Then
         snape.snapeendpoint X, Y, Form1.cad, snapepoint
      End If

      '����
      If InStrB(1, user.SnapeOperist, "snapemisspoint", vbBinaryCompare) <> 0 Then
             snape.snapemisspoint X, Y, Form1.cad, snapepoint
      End If
       '�߶λ�Բ�����е�
      If InStrB(1, user.SnapeOperist, "snapelinemid", vbBinaryCompare) <> 0 Then
             snape.snapelinemidpoint X, Y, Form1.cad, snapepoint
      End If
      'Բ��
      If InStrB(1, user.SnapeOperist, "snapecirclepoint", vbBinaryCompare) <> 0 Then
            snape.snapecirclepoint X, Y, Form1.cad, snapepoint
      End If
      
     X = .X
     Y = .Y
 
 End With
     
     Select Case user.CurrentOperist
            Case "������"
                 Select Case user.drawflag
                        Case 1    '����һ��ʱ��ȡ������,�����㲻ȡֵ
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
           ' Case "selectobject"         '���������ǰѡ����Ŀ��
            '      snape.selectobjectclare x, y, Form1.cad
            Case "round"      '��Ŀ��������ת
                   'Ϊ�ο�ֱ�߸�ֵ
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
    
'ͻ����ʾĿ�겶׽���ĵ�
    With snapepoint
    If .r >= 0 Then
       draw.showpoint .X, .Y, Form1.cad, user.Snapecolor
    End If
    End With
'��ʾ��ʮ�ֹ��
user.DispBigCross Form1.cad, X, Y
user.DispBigCross Form1.cad, X, Y
'��ʾ��׽���
 user.SnapeMouse Form1.cad, X, Y
 user.SnapeMouse Form1.cad, X, Y
End Sub

Private Sub cad_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim col As ColorConstants
col = user.Pramcol
'��shift������ʱ
     If Shift = VBRUN.ShiftConstants.vbShiftMask Then
        If Abs(X - user.Mouseleftdownx) < Abs(Y - user.mouseleftdowny) Then
           X = user.Mouseleftdownx
        Else
           Y = user.mouseleftdowny
        End If
     End If
     
'�жϵ�����Ƿ��Ƶ���ͼ�߽�
'If Button = vbLeftButton Then
'   If X < user.deskx1 Or X > user.deskx2 Or Y < user.desky1 Or Y > user.desky2 Then
'      user.movepaper X, Y, Form1.cad         '�Զ��ƶ�ͼֽ
'   End If
'End If
     
If meuntishi.Checked = True Then
   'user.tishi x, y, Button    '��ʾ��
   user.TiShiInitale X, Y, Button
End If
Select Case user.CurrentOperist
        Case "Line"
             draw.singleline Button, X, Y, col, cad
        Case "������"
             draw.singleline Button, X, Y, col, cad
        Case "Rectangle"
            draw.rectangle cad, X, Y, col, Button
        Case "������"
            draw.three Form1.cad, Button, X, Y, col
        Case "��������"
             draw.�������� Form1.cad, X, Y, Button, col
        Case "�ȱ�������"
            draw.three Form1.cad, Button, X, Y, col
        Case "������"
            draw.������ Form1.cad, Button, X, Y, col
        Case "��������"
             draw.�������� Form1.cad, Button, X, Y, col
        Case "Line Style"
            MsgBox "Add 'Line Style' button code."
        Case "Arc"
            draw.arc Form1.cad, Button, X, Y, col
        Case "����"
            draw.arc Form1.cad, Button, X, Y, col
        Case "Ellipse"
            draw.ellipse Form1.cad, X, Y, Button, col
        Case "circle"
            draw.mousecircle Button, X, Y, col, Form1.cad
            
        '�༭
        Case "move"
              edit.Move X, Y, Form1.cad, Button
        Case "round"  '��Ŀ��������ת
             edit.Round X, Y, Form1.cad, Button, user.Snapecolor, 0
        Case "rounda"   '����һ����ת
             edit.Round X, Y, Form1.cad, Button, user.Snapecolor, 0
        'Case "mirror", "mirrorsave"
        '     If user.drawflag = 1 Then     'ֱ�������ȷ�������ߵ�����
        '        If Button = VBRUN.vbLeftButton Then
        '           draw.singleline Button, X, Y, user.Snapecolor, Form1.cad
        '          edit.Mirror Form1.cad, X, Y, user.Snapecolor, 0
        '        End If
        '     End If
        '     If user.drawflag = 2 Then   '�ò�׽Ŀ�귽ʽȷ������������
        '        draw.singleline VBRUN.vbLeftButton, X, Y, user.Snapecolor, Form1.cad
        '     End If
        Case "copy"
             edit.Move X, Y, Form1.cad, Button
        Case "selectzoom"
             draw.selectzoomrectangle Form1.cad, Button, col, X, Y
        Case "fieldselectobject"  '����ѡȡĿ��
             draw.rectangle Form1.cad, X, Y, user.Snapecolor, Button
End Select
'��ʾ��ʮ�ֹ��
user.DispBigCross Form1.cad, X, Y
user.DispBigCross Form1.cad, X, Y
'��ʾ��׽���
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
'��shift������ʱ
     If Shift = VBRUN.ShiftConstants.vbShiftMask Then
        If Abs(X - user.Mouseleftdownx) < Abs(Y - user.mouseleftdowny) Then
           X = user.Mouseleftdownx
        Else
           Y = user.mouseleftdowny
        End If
     End If

 '��׽Ŀ���ͬʱ��ͼ
Dim snapepoint As snapepoint   '���user�е���������
With snapepoint
     .r = -1
     .X = X
     .Y = Y
      '�����˳���ܱ仯
      '�߶λ�Բ���Ķ˵�
      If InStrB(1, user.SnapeOperist, "selectendpoint", vbBinaryCompare) <> 0 Then
              snape.snapeendpoint X, Y, Form1.cad, snapepoint
      End If
      '����
      If InStrB(1, user.SnapeOperist, "snapemisspoint", vbBinaryCompare) <> 0 Then
              snape.snapemisspoint X, Y, Form1.cad, snapepoint
              snape.snapemisspoint X, Y, Form1.cad, snapepoint
              snape.snapemisspoint X, Y, Form1.cad, snapepoint
      End If
      '�߶λ�Բ�����е�
      If InStrB(1, user.SnapeOperist, "snapelinemid", vbBinaryCompare) <> 0 Then
                 snape.snapelinemidpoint X, Y, Form1.cad, snapepoint
      End If
      'Բ��
      If InStrB(1, user.SnapeOperist, "snapecirclepoint", vbBinaryCompare) <> 0 Then
              snape.snapecirclepoint X, Y, Form1.cad, snapepoint
      End If
      
  X = .X
  Y = .Y
    'ͻ����ʾĿ�겶׽���ĵ�
    If .r >= 0 Then
       draw.showpoint .X, .Y, Form1.cad, user.Snapecolor
    End If
End With

Select Case user.CurrentOperist
        Case "ʵ�ĵ�"
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
                '����ο�ֱ��
                cad.DrawMode = 7
                cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                '��ʾȷ����ֱ��
                cad.DrawMode = VBRUN.vbCopyPen
                cad.Line (Mouseleftdownx, mouseleftdowny)-(X, Y), user.Commvar.col
                '�洢ֱ�߲���
                user.name = "line"
                ReDim Preserve user.LineType(UBound(user.LineType) + 1)
                user.LineType(UBound(user.LineType)).X = X    '�洢�߶ε��յ�
                user.LineType(UBound(user.LineType)).Y = Y
                user.Savepraam  '���������Ĵ洢,�����߶ε����
                'Put #200, , user.name
                'Put #200, , linetype
                End If
                user.CurrentOperistFlag = True
        Case "������"
             Select Case user.drawflag
                    Case 1
                         If Button = VBRUN.vbLeftButton Then
                            '����ο�ֱ��
                            cad.DrawMode = 7
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                            '��ʾȷ����ֱ��
                            cad.DrawMode = VBRUN.DrawModeConstants.vbNotXorPen
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(X, Y), user.Commvar.col
                            '�洢ֱ�߲���
                            user.name = "line"     '��Ϊ����������line��ͬ
                            ReDim Preserve user.LineType(UBound(user.LineType) + 1)
                            user.LineType(UBound(user.LineType)).X = X  '�洢�����ߵĵڶ���
                            user.LineType(UBound(user.LineType)).Y = Y
                            user.Savepraam  '���������Ĵ洢,���������ߵĵ�һ��
                         End If
                         user.drawflag = 2     '����һ����־
                    Case 2
                         If Button = VBRUN.vbLeftButton Then
                            '����ο�ֱ��
                            cad.DrawMode = 7
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                            '��ʾȷ����ֱ��
                            cad.DrawMode = VBRUN.vbCopyPen
                            cad.Line (Mouseleftdownx, mouseleftdowny)-(X, Y), user.Commvar.col
                            '�洢ֱ�߲���
                            user.name = "line"     '��Ϊ����������line��ͬ
                            ReDim Preserve user.LineType(UBound(user.LineType) + 1)
                            user.LineType(UBound(user.LineType)).X = X   '�洢��һ��
                            user.LineType(UBound(user.LineType)).Y = Y
                            user.Savepraam  '���������Ĵ洢,����ǰһ��
                          End If
            End Select
            '����һֱ����㸳ֵ
            user.Mouseleftdownx = X
            user.mouseleftdowny = Y
            user.CurrentOperistFlag = True
            
        Case "Rectangle"
            'ToDo: Add 'Rectangle' button code.
            'MsgBox "Add 'Rectangle' button code."
            If Button = VBRUN.vbLeftButton Then
                '����ο�����
                cad.DrawMode = 7
                cad.Line (user.Mouseleftdownx, mouseleftdowny)-(Mousepausex, user.mouseleftdowny), col
                cad.Line -(user.Mousepausex, user.mousepausey), col
                cad.Line -(user.Mouseleftdownx, user.mousepausey), col
                cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
                '��ʾȷ����ֱ��
                cad.DrawMode = VBRUN.vbCopyPen
                cad.Line (Mouseleftdownx, mouseleftdowny)-(X, user.mouseleftdowny), user.Commvar.col
                cad.Line -(X, Y), user.Commvar.col
                cad.Line -(user.Mouseleftdownx, Y), user.Commvar.col
                cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), user.Commvar.col
                '�洢���β���
                user.name = "rectangle"
                ReDim Preserve user.RectangleType(UBound(user.RectangleType) + 1)
                user.RectangleType(UBound(user.RectangleType)).X = X
                user.RectangleType(UBound(user.RectangleType)).Y = Y
                user.Savepraam  '���������Ĵ洢
            End If
            user.CurrentOperistFlag = True
        Case "Line Style"
            'ToDo: Add 'Line Style' button code.
            MsgBox "Add 'Line Style' button code."
        Case "������"
            Select Case user.drawflag
                   Case 1
                        user.drawflag = 2
                       '����ο�ֱ��
                       cad.DrawMode = 7
                       cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                       '��ʾȷ����ֱ��
                       'cad.DrawMode = VBRUN.vbCopyPen
                       cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), user.Commvar.col
                       '���ݴ�㸳ֵΪ����,��������ѻ��õ���
                       'user.mousepausex = user.mouseleftdownx
                       'user.mousepausey = user.mouseleftdowny
                       '�洢�����β���
                        user.name = "������"
                        ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) + 1)
                        '�������
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 = X   '
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 = Y
                        user.Savepraam
                   Case 2
                        user.drawflag = 1
                        cad.DrawMode = 7
                        '�����ο���
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(user.Mousepausex, user.mousepausey), col
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(user.Mousepausex, user.mousepausey), col
                        'ȷ��������
                        cad.DrawMode = VBRUN.vbCopyPen
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(X, Y), user.Commvar.col
                        Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(X, Y), user.Commvar.col
                        '�������
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).x3 = X
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).y3 = Y
                        draw.redraw
            End Select
            user.CurrentOperistFlag = True
        Case "��������"
            ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) + 1)
            '�������
            user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 = X
            user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 = Y
            '�������Ƶ���һ��
            xx = X - user.Mouseleftdownx
            yy = Y - user.mouseleftdowny
            '�ѵڶ���Χ�Ƶ�һ����ʱ��ת60��
            x1 = xx / 2 - yy * Sin(user.pi / 3)
            y1 = xx * Sin(user.pi / 3) + yy / 2
            '�ٰ������ƻ�ԭ��
            xx = x1 + user.Mouseleftdownx
            yy = y1 + user.mouseleftdowny
            user.ThreeAngleType(UBound(user.ThreeAngleType)).x3 = xx
            user.ThreeAngleType(UBound(user.ThreeAngleType)).y3 = yy
            user.name = "������"
            user.Savepraam   '���湫������
            user.CurrentOperistFlag = True
        Case "�ȱ�������"
             Select Case user.drawflag
                    Case 1
                        user.drawflag = 2
                       '����ο�ֱ��
                       cad.DrawMode = 7
                       cad.Line (Mouseleftdownx, mouseleftdowny)-(Mousepausex, mousepausey), col
                       '��ʾȷ����ֱ��
                       cad.DrawMode = VBRUN.vbCopyPen
                       cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), user.Commvar.col
                       '���ݴ�㸳ֵΪ����,��������ѻ��õ���
                       user.Mousepausex = user.Mouseleftdownx
                       user.mousepausey = user.mouseleftdowny
                       '�洢�����β���
                        user.name = "������"
                        ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) + 1)
                        '�������
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 = X
                        user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 = Y
                        user.Savepraam
                    Case 2
                        user.drawflag = 1
                        
             End Select
             user.CurrentOperistFlag = True
        Case "������"
            user.drawflag = 2
            draw.������ Form1.cad, Button, X, Y, col
            user.name = "������"
            ReDim Preserve user.SameRectangleType(UBound(user.SameRectangleType) + 1)
            user.SameRectangleType(UBound(user.SameRectangleType)).X = X
            user.SameRectangleType(UBound(user.SameRectangleType)).Y = Y
            user.Savepraam
            user.CurrentOperistFlag = True
        Case "��������"
            user.drawflag = 2
            draw.�������� Form1.cad, Button, X, Y, col
            user.drawflag = 1
            user.name = "��������"
            ReDim Preserve user.SixegdeType(UBound(user.SixegdeType) + 1)
            '�������
            user.SixegdeType(UBound(user.SixegdeType)).X = X
            user.SixegdeType(UBound(user.SixegdeType)).Y = Y
            user.Savepraam
            user.CurrentOperistFlag = True
        Case "Arc"
            Select Case user.drawflag
                   Case 1
                        user.drawflag = 2
                        ReDim Preserve user.ArcType(UBound(user.ArcType) + 1)
                        'ȷ��Բ�뾶
                        rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                                           (mouseleftdowny - Y) ^ 2)
                        '�洢Բ���Ĳ���
                        user.name = "arc"
                        user.ArcType(UBound(user.ArcType)).r = rad
                        user.Savepraam  '���������Ĵ洢
                        cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
                        user.Mousepausex = X
                        user.mousepausey = Y
                    Case 4
                        user.drawflag = 3
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)  '����ʼ��
                        user.ArcType(UBound(user.ArcType)).start = rad
                   Case 3
                        user.drawflag = 1
                        '�����ο���
                        cad.DrawMode = 7
                        cad.Line (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y)-(user.Mousepausex, user.mousepausey), col
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)  '�������
                        user.ArcType(UBound(user.ArcType)).end = rad
                        'ȷ��Բ��
                        cad.DrawMode = VBRUN.vbCopyPen
                        cad.Circle (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y), user.ArcType(UBound(user.ArcType)).r, user.ArcType(UBound(user.ArcType)).comvar.col, user.ArcType(UBound(user.ArcType)).start, user.ArcType(UBound(user.ArcType)).end
            End Select
            user.CurrentOperistFlag = True
        Case "����"
            Select Case user.drawflag
                   Case 1
                        user.drawflag = 2
                        ReDim Preserve user.ArcType(UBound(user.ArcType) + 1)
                        'ȷ��Բ�뾶
                        rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                                           (mouseleftdowny - Y) ^ 2)
                        '�洢Բ���Ĳ���
                        user.name = "arc"
                        user.ArcType(UBound(user.ArcType)).r = rad
                        user.Savepraam  '���������Ĵ洢
                        cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
                        user.Mousepausex = X
                        user.mousepausey = Y
                    Case 4
                        user.drawflag = 3
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)   '������
                        user.ArcType(UBound(user.ArcType)).start = -rad
                   Case 3
                        user.drawflag = 1
                        '�����ο���
                        cad.DrawMode = 7
                        cad.Line (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y)-(user.Mousepausex, user.mousepausey), col
                        xx = X - user.ArcType(UBound(user.ArcType)).X
                        yy = Y - user.ArcType(UBound(user.ArcType)).Y
                        rad = math.angle(xx, yy)  '�������
                        user.ArcType(UBound(user.ArcType)).end = -rad
                        'ȷ��Բ��
                        cad.DrawMode = VBRUN.vbCopyPen
                        cad.Circle (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y), user.ArcType(UBound(user.ArcType)).r, user.ArcType(UBound(user.ArcType)).comvar.col, user.ArcType(UBound(user.ArcType)).start, user.ArcType(UBound(user.ArcType)).end
            End Select
            user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
        Case "Ellipse"
            If user.drawflag = 1 Then
               user.drawflag = 2
               ReDim Preserve user.EllipseType(UBound(user.EllipseType) + 1)
               'ȷ��Բ�뾶
               rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                     (mouseleftdowny - Y) ^ 2)
               '�洢��Բ�Ĳ���
               user.name = "ellipse"
               user.EllipseType(UBound(user.EllipseType)).r = rad
               user.Savepraam  '���������Ĵ洢
               user.Mousepausex = 1       '��ʱ���������
            Else
               user.drawflag = 1
               user.EllipseType(UBound(user.EllipseType)).asp = Abs((Y - user.EllipseType(UBound(user.EllipseType)).Y) / user.EllipseType(UBound(user.EllipseType)).r)
            End If
            user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
        Case "circle"
              rad = Sqr((Mouseleftdownx - Mousepausex) ^ 2 _
                   + (mouseleftdowny - mousepausey) ^ 2)
              '����ο�Բ
              cad.DrawMode = 7
              cad.Circle (Mouseleftdownx, mouseleftdowny), rad, col
              'ȷ��Բ
              cad.DrawMode = VBRUN.DrawModeConstants.vbCopyPen
              rad = Sqr((Mouseleftdownx - X) ^ 2 + _
                        (mouseleftdowny - Y) ^ 2)
              cad.Circle (Mouseleftdownx, mouseleftdowny), rad, user.Commvar.col
              '�洢Բ�Ĳ���
              user.name = "circle"
              ReDim Preserve user.CircleType(UBound(user.CircleType) + 1)
              user.CircleType(UBound(user.CircleType)).r = rad
              user.Savepraam  '���������Ĵ洢
              'Put #200, , user.name
              'Put #200, , circletype
              user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
        Case "text"
               Form1.cad.CurrentX = X
               Form1.cad.CurrentY = Y
               inputtextbox.Show 1, Form1
               draw.redraw
               user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
               
          'ͼ�α༭
        Case "selectobject", "fieldselectobject"    'Ŀ��ѡȡ
                'With user.snapefieldtype  '����׽���θ�ֵ
                '     .x1 = x
                '     .x2 = x
                '     .y1 = y
                '     .y2 = y
                'End With
                snape.selectobjectclare X, Y, Form1.cad   '�����ǰѡȡ��Ŀ��
           
                snape.selectobject X, Y, Form1.cad   'ѡȡĿ��
                
                '����ѡȡʱʱ,����ο���׽���β�����׽���ķ�Χ��ֵ
                If user.CurrentOperist = "fieldselectobject" Then
                   Form1.cad.DrawMode = 7
                   draw.drawrectangle Form1.cad, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey, user.Snapecolor
                   
                   user.Mousepausex = X
                   user.mousepausey = Y
                End If
                user.CurrentOperist = "move"
                
        'ѡȡĿ��
        'Case "selectendpoint" 'ѡȡ�߶εĶ˵�
        '       user.mousesnape = "snapecirle"  '��׽ʱ������״,Ӱ�����snapemouse
        '       If Button = VBRUN.vbLeftButton Then snape.snapeendpoint x, y, Form1.cad
        Case "selectline"
                Mousesnape = "snapecirle" '��׽ʱ������״,Ӱ�����snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snapeline X, Y, Form1.cad
        Case "selectcircle"
               Mousesnape = "snapecirle" '��׽ʱ������״,Ӱ�����snapemouse
               If Button = VBRUN.vbLeftButton Then snape.snapecircle X, Y, Form1.cad
        Case "selectrectangle"
                Mousesnape = "snapecirle" '��׽ʱ������״,Ӱ�����snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snaperectangle X, Y, Form1.cad
        Case "selectthreeangle"
                Mousesnape = "snapecirle" '��׽ʱ������״,Ӱ�����snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snapethreeangle X, Y, Form1.cad
        Case "selectarc"
                Mousesnape = "snapecirle" '��׽ʱ������״,Ӱ�����snapemouse
                If Button = VBRUN.vbLeftButton Then snape.snapearc X, Y, Form1.cad
                
        '�༭ѡȡ��Ŀ��
        Case "move"    '�ƶ�
              edit.Moveadd X, Y, Form1.cad, False
              With user.SnapefieldType   '�����ǰ�Ĳ�׽����
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '��ʾ��׽����
             snape.showselectobject Form1.cad, True
             user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
        Case "copy"    '����
              edit.Moveadd X, Y, Form1.cad, True
              With user.SnapefieldType   '�����ǰ�Ĳ�׽����
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '��ʾ��׽����
              snape.showselectobject Form1.cad, True
              user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
              
        Case "rounda", "round" '��Ŀ��������ת
             edit.Round X, Y, Form1.cad, Button, vbBlack, 1
             With user.SnapefieldType   '�����ǰ�Ĳ�׽����
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '��ʾ��ת���Ŀ��
             snape.showselectobject Form1.cad, True
             user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
        Case "mirror"     '������ԭͼ�εľ���
               Select Case user.drawflag
                      Case 1
                           edit.Mirror Form1.cad, X, Y, user.Snapecolor, 1
                      Case 2
                           user.drawflag = 3
                           
                      Case 3
               End Select
             With user.SnapefieldType   '�����ǰ�Ĳ�׽����
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '��ʾ��׽����
              snape.showselectobject Form1.cad, True
              user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
        Case "mirrorsave"   '����ԭͼ�εľ���
               Select Case user.drawflag
                      Case 1
                           edit.Mirror Form1.cad, X, Y, user.Snapecolor, 2
                      Case 2
                           user.drawflag = 3
                           
                      Case 3
               End Select
             With user.SnapefieldType   '�����ǰ�Ĳ�׽����
                  .x1 = -1
                  .x2 = -1
                  .y1 = -1
                  .y2 = -1
                  End With
              '��ʾ��׽����
              snape.showselectobject Form1.cad, True
              user.CurrentOperistFlag = True  '��־�Ƿ�����˲���
              
        '����
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
                  user.SnapeField = user.SnapeField / user.HeightZoomnum  '��׽���մ�С
                  draw.redraw
              End If
              
End Select
cad.DrawMode = mode
'��ʾ��ʮ�ֹ��
user.DispBigCross Form1.cad, X, Y
user.DispBigCross Form1.cad, X, Y
'��ʾ��׽���
 user.SnapeMouse Form1.cad, X, Y
 user.SnapeMouse Form1.cad, X, Y
End Sub


