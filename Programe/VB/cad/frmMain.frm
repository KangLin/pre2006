VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{38911DA0-E448-11D0-84A3-00DD01104159}#1.1#0"; "COMCT332.OCX"
Begin VB.MDIForm frmMain 
   BackColor       =   &H8000000C&
   Caption         =   "��ͼ"
   ClientHeight    =   5940
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   9360
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   3  '����ȱʡ
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
            Key             =   "����"
         EndProperty
         BeginProperty ListImage20 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1924
            Key             =   ""
         EndProperty
         BeginProperty ListImage21 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1C74
            Key             =   "������"
         EndProperty
         BeginProperty ListImage22 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1FC4
            Key             =   "��������"
         EndProperty
         BeginProperty ListImage23 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2314
            Key             =   "��������"
         EndProperty
         BeginProperty ListImage24 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2664
            Key             =   "������"
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
            Key             =   "����"
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
            Key             =   "m����"
         EndProperty
         BeginProperty ListImage44 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":66B0
            Key             =   "m������"
         EndProperty
         BeginProperty ListImage45 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6A00
            Key             =   "mcirclecross"
         EndProperty
         BeginProperty ListImage46 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6D50
            Key             =   "m������"
         EndProperty
         BeginProperty ListImage47 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":70A0
            Key             =   "m��������"
         EndProperty
         BeginProperty ListImage48 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":73F0
            Key             =   "m��������"
         EndProperty
         BeginProperty ListImage49 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7740
            Key             =   "mcircle"
         EndProperty
         BeginProperty ListImage50 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7A90
            Key             =   "ˮƽ��ע"
         EndProperty
         BeginProperty ListImage51 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7DE0
            Key             =   "����ˮƽ��ע"
         EndProperty
         BeginProperty ListImage52 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8130
            Key             =   "��ֱ��ע"
         EndProperty
         BeginProperty ListImage53 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8480
            Key             =   "������ֱ��ע"
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
            Key             =   "������"
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
            Key             =   "��ֱ�߶�"
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
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu mnuFileNew 
         Caption         =   "���ļ�  (&N)"
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFileOpen 
         Caption         =   "���ļ�(&O)..."
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "�ر��ļ�(&C)"
      End
      Begin VB.Menu mnuFileBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "�����ļ�(&S)"
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "����Ϊ  (&A)"
      End
      Begin VB.Menu mnuFileSaveAll 
         Caption         =   "ȫ������(&l)"
      End
      Begin VB.Menu mnuFileBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePageSetup 
         Caption         =   "ҳ����(&U)"
      End
      Begin VB.Menu mnuFilePrintPreview 
         Caption         =   "��ӡԤ��(&V)"
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "��ӡ(&P)"
      End
      Begin VB.Menu mnuFileBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnufileexit 
         Caption         =   "�˳�(&E)"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "�༭(&E)"
      Begin VB.Menu mnuEditDelete 
         Caption         =   "ɾ��(&L)"
      End
      Begin VB.Menu mnuEditRedraw 
         Caption         =   "�ػ�(&R)"
      End
      Begin VB.Menu mnuEditBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditCut 
         Caption         =   "����(&T)"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "����(&C)"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "ճ��(&P)"
         Shortcut        =   ^V
      End
      Begin VB.Menu mnuEditbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSelectPoint 
         Caption         =   "��ѡȡ(&S)"
      End
      Begin VB.Menu mnuEditSelectAll 
         Caption         =   "ȫѡ(&A)"
      End
      Begin VB.Menu mnuEditUndo 
         Caption         =   "ȡ��ѡȡ(&U)"
      End
      Begin VB.Menu mnuEditbar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditMake 
         Caption         =   "�任"
         Begin VB.Menu mnuEditMakeMove 
            Caption         =   "�ƶ�(&O)"
         End
         Begin VB.Menu mnuEditMakeCopy 
            Caption         =   "����"
         End
         Begin VB.Menu mnuEditMakeRound 
            Caption         =   "��ת(&R)"
         End
         Begin VB.Menu mnuEditMakeMirror 
            Caption         =   "����(&M)"
         End
         Begin VB.Menu mnuEditMakeMirrorSave 
            Caption         =   "����(����ԭͼ)"
            Enabled         =   0   'False
         End
         Begin VB.Menu mnuEditMakeArray 
            Caption         =   "����"
            Begin VB.Menu mnuEditModefiyArrayCircle 
               Caption         =   "Բ������"
            End
            Begin VB.Menu mnuEditModefiyArrayRectangle 
               Caption         =   "��������"
            End
         End
      End
      Begin VB.Menu mnuEditbar4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditModify 
         Caption         =   "�޸�"
         Begin VB.Menu mnuEditModifyRatioChange 
            Caption         =   "�����任"
            Visible         =   0   'False
         End
         Begin VB.Menu mnuEditModifyBreak 
            Caption         =   "�ж�(&B)"
         End
         Begin VB.Menu mnuEditModifyTrim 
            Caption         =   "�޼�"
         End
         Begin VB.Menu mnuEditModifyText 
            Caption         =   "�޸�����"
         End
         Begin VB.Menu mnuEditBar5 
            Caption         =   "-"
         End
         Begin VB.Menu mnuEditModifyFillet 
            Caption         =   "Բ��"
         End
         Begin VB.Menu mnuEditModifyChamfer 
            Caption         =   "�н�"
         End
         Begin VB.Menu mnuEditModifyParameter 
            Caption         =   "ȷ��Բ�Ǻ��нǵĲ���"
         End
         Begin VB.Menu mnuEditBar6 
            Caption         =   "-"
         End
         Begin VB.Menu mnuEditModifyTwoLineMiss 
            Caption         =   "ʹ��ֱ���ཻ"
         End
      End
   End
   Begin VB.Menu mnuMake 
      Caption         =   "��ͼ(&M)"
      Begin VB.Menu mnuMakeEnd 
         Caption         =   "����"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakeClose 
         Caption         =   "�ر�"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakeUndo 
         Caption         =   "ȡ��"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakebar1 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuMakeLine 
         Caption         =   "ֱ��"
         Begin VB.Menu mnuMakeLine�߶� 
            Caption         =   "�߶�"
         End
         Begin VB.Menu mnuMakeLine��ֱ�߶� 
            Caption         =   "��ֱ�߶�"
         End
         Begin VB.Menu mnuMake������ 
            Caption         =   "������"
         End
         Begin VB.Menu mnuMakeLine���㵽Բ������ 
            Caption         =   "���㵽Բ������"
         End
      End
      Begin VB.Menu mnuMake������ 
         Caption         =   "������"
      End
      Begin VB.Menu mnuMake�������� 
         Caption         =   "��������"
      End
      Begin VB.Menu mnuMake���� 
         Caption         =   "����"
      End
      Begin VB.Menu mnuMake������ 
         Caption         =   "������"
      End
      Begin VB.Menu mnuMake�������� 
         Caption         =   "��������"
      End
      Begin VB.Menu mnuMakeԲ 
         Caption         =   "Բ"
      End
      Begin VB.Menu mnuMakeԲ�� 
         Caption         =   "Բ��"
      End
      Begin VB.Menu mnuMake���� 
         Caption         =   "����"
      End
      Begin VB.Menu mnuMake��Բ 
         Caption         =   "��Բ"
      End
      Begin VB.Menu mnuMaketext 
         Caption         =   "����"
      End
      Begin VB.Menu mnuMake��ע 
         Caption         =   "��ע"
         Begin VB.Menu mnuMakeDimˮƽ��ע 
            Caption         =   "ˮƽ��ע"
         End
         Begin VB.Menu mnuMakeDim����ˮƽ��ע 
            Caption         =   "����ˮƽ��ע"
         End
         Begin VB.Menu mnuMakeDim��ֱ��ע 
            Caption         =   "��ֱ��ע"
         End
         Begin VB.Menu mnuMakeDim������ֱ��ע 
            Caption         =   "������ֱ��ע"
         End
         Begin VB.Menu mnuMakeDimͬ����ע 
            Caption         =   "ͬ���߱�ע"
         End
         Begin VB.Menu mnuMakeDim�뾶�ߴ� 
            Caption         =   "�뾶�ߴ�"
         End
         Begin VB.Menu mnuMakeDimֱ���ߴ� 
            Caption         =   "ֱ���ߴ�"
         End
         Begin VB.Menu mnuMakeDim�Ծ��ߴ� 
            Caption         =   "��ע�ߴ�"
         End
         Begin VB.Menu mnuMakeDim�Ƕȳߴ� 
            Caption         =   "�Ƕȳߴ�"
         End
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "��ͼ(&V)"
      Begin VB.Menu mnuViewZoomOut 
         Caption         =   "�Ŵ�(&O)"
      End
      Begin VB.Menu mnuViewZoomIn 
         Caption         =   "��С(&I)"
      End
      Begin VB.Menu mnuViewSelectZoom 
         Caption         =   "ѡ��Ŵ�(&S)"
      End
      Begin VB.Menu mnuViewExtents 
         Caption         =   "�ָ�ԭͼ(&R)"
      End
      Begin VB.Menu mnuViewFullWindow 
         Caption         =   "ȫͼ����(&F)"
      End
      Begin VB.Menu mnuViewbar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewMouse 
         Caption         =   "�����״(&M)"
         Begin VB.Menu mnuViewMouseLittleCross 
            Caption         =   "Сʮ�ֹ��"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuViewMouseBigCross 
            Caption         =   "��ʮ�ֹ��"
         End
         Begin VB.Menu mnuViewMouseArrow 
            Caption         =   "���ι��"
         End
         Begin VB.Menu mnuViewMouseCircle 
            Caption         =   "Բ�ι��"
         End
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "����(&W)"
      Begin VB.Menu mnuWindowNewWindow 
         Caption         =   "�´���(&N)"
      End
      Begin VB.Menu mnuWindowClose 
         Caption         =   "�رմ���(&C)"
      End
      Begin VB.Menu mnuWindowCloseAllWindow 
         Caption         =   "�ر����д���(&A)"
      End
      Begin VB.Menu mnuWindowBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuWindowCascade 
         Caption         =   "������д���(&L)"
      End
      Begin VB.Menu mnuWindowTileHorizontal 
         Caption         =   "ˮƽ���д���(&H)"
      End
      Begin VB.Menu mnuWindowTileVertical 
         Caption         =   "��ֱ���д���(&V)"
      End
      Begin VB.Menu mnuWindowArrangeIcons 
         Caption         =   "������С��ʱ��ͼ������"
      End
   End
   Begin VB.Menu mnuToolS 
      Caption         =   "����(&T)"
      Begin VB.Menu mnuToolSnape 
         Caption         =   "��׽"
         Begin VB.Menu mnuToolSnapeEndPoint 
            Caption         =   "��׽ֱ�߻�Բ���˵�"
         End
         Begin VB.Menu mnuToolSnapeMiddlePoint 
            Caption         =   "��׽ֱ�߻�Բ�����е�"
         End
         Begin VB.Menu mnuToolSnapeCentrPoint 
            Caption         =   "��׽Բ�ġ����ġ��������ġ���Բ����"
         End
         Begin VB.Menu mnuToolSnapeMissPoint 
            Caption         =   "��׽����"
         End
         Begin VB.Menu mnuToolSnapeExit 
            Caption         =   "�˳���׽"
         End
      End
      Begin VB.Menu mnuToolbar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolBar_File 
         Caption         =   "�ļ�������"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolBar_Edit 
         Caption         =   "�༭������"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolBar_Make 
         Caption         =   "��ͼ������"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolBar_Snape 
         Caption         =   "��׽������"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuToolbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolObjectList 
         Caption         =   "ʵ���б�"
      End
      Begin VB.Menu mnuToolbar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolsOptions 
         Caption         =   "ѡ��(&O)"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "����(&H)"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "Ŀ¼"
      End
      Begin VB.Menu mnuHelpSearchForHelpOn 
         Caption         =   "����....."
      End
      Begin VB.Menu mnuHelpBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "����(&A)"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'����:����

Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Any) As Long
Const EM_UNDO = &HC7
Private Declare Function OSWinHelp% Lib "user32" Alias "WinHelpA" (ByVal hwnd&, ByVal HelpFile$, ByVal wCommand%, dwData As Any)

Public CloseAllWindowFlag As Boolean '�Ƿ�ر����д��ڱ�־,���frmmain��mnuWindowCloseAllWindow()����

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
    
    Inital_Tool  '��ʼ��������
    
    LoadNewCad  '���ش���
    
    Inital_Menu Me
       
End Sub

Private Sub Inital_Tool() '��ʼ��������
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
         .Caption = "��ͼ " & lCadCount
         .Show
    End With
        
    NoEnabled_Edit 'ʹ�༭��ť����Ӧ�¼�

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
        TCurrentOperist.text = "����"
End Sub

Private Sub mnuEditMakeMirror_Click()
        TCurrentOperist.text = "����"
End Sub

Private Sub mnuEditMakeMirrorSave_Click()
        TCurrentOperist.text = "������ԭͼ"
End Sub

Private Sub mnuEditMakeMove_Click()
         TCurrentOperist.text = "�ƶ�"
End Sub

Private Sub mnuEditMakeRound_Click()
        TCurrentOperist.text = "��ת"
End Sub

Private Sub mnuEditModefiyArrayCircle_Click()
        TCurrentOperist.text = "Բ������"
        DrawFlag = 1
End Sub

Private Sub mnuEditModefiyArrayRectangle_Click()
        TCurrentOperist.text = "��������"
End Sub

Private Sub mnuEditModifyBreak_Click()
        TCurrentOperist.text = "�ж�"
        DrawFlag = 1
End Sub

Private Sub mnuEditModifyChamfer_Click() '�н�
        TCurrentOperist.text = "�н�"
        DrawFlag = 1
End Sub

Private Sub mnuEditModifyFillet_Click() 'Բ��
        TCurrentOperist = "Բ��"
        DrawFlag = 1
End Sub

Private Sub mnuEditModifyParameter_Click() 'ȷ���н�Բ �ǵĲ���
        FCP.Show 1, Me
End Sub

Private Sub mnuEditModifyText_Click() '�޸�����
        TCurrentOperist.text = "�޸�����"
End Sub

Private Sub mnuEditModifyTrim_Click() '�޼�

End Sub

Private Sub mnuEditModifyTwoLineMiss_Click() 'ʹ����ֱ���ཻ
        TCurrentOperist.text = "ʹ��ֱ���ཻ"
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

Private Sub mnuMakeClose_Click()  '�ر�
        Select Case fMainForm.TCurrentOperist '�ı��ؼ�ʡ��Ϊ.text
               Case "������"
                    DrawFlag = 1
                    ActiveForm.ȷ�����������ֱ�� "close"
               
        End Select
End Sub

Private Sub mnuMakeEnd_Click() '����
        Select Case fMainForm.TCurrentOperist
               Case "������"
                    DrawFlag = 1
                    ActiveForm.ȷ�����������ֱ�� "end"
               Case "����ˮƽ��ע", "������ֱ��ע"
                    DrawFlag = 1
                    ActiveForm.HorizontalEnd "end"
        End Select
End Sub

Private Sub mnuMakeUndo_Click() 'ȡ��
        Select Case fMainForm.TCurrentOperist
               Case "������"
                    DrawFlag = 1
                    ActiveForm.ȷ�����������ֱ�� "undo"
               Case "����ˮƽ��ע", "������ֱ��ע"
                    ActiveForm.HorizontalEnd "undo"
                    DrawFlag = 1
               Case Else
                    ActiveForm.MakeUndo TCurrentOperist
        End Select
End Sub

Private Sub mnuMakeLine�߶�_Click()
        fMainForm.TCurrentOperist = "line"
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMakeLine��ֱ�߶�_Click() '
        TCurrentOperist.text = "��ֱ�߶�"
        DrawFlag = 1
End Sub

Private Sub mnuMakeLine���㵽Բ������_Click()
        TCurrentOperist.text = "���㵽Բ������"
        DrawFlag = 1
End Sub

Private Sub mnuMake������_Click()
        fMainForm.TCurrentOperist = "������"
        DrawFlag = 1
        mnuMakeClose.Visible = True '�������ĸ��˵�
        mnuMakeEnd.Visible = True
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake������_Click()
            fMainForm.TCurrentOperist = "������"
            DrawFlag = 1
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake��������_Click()
            fMainForm.TCurrentOperist = "��������"
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake����_Click()
        fMainForm.TCurrentOperist = "����"
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake������_Click()
        fMainForm.TCurrentOperist = "������"
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake��������_Click()
        fMainForm.TCurrentOperist = "��������"
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMakeԲ_Click()
        fMainForm.TCurrentOperist = "Բ"
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMakeԲ��_Click()
        fMainForm.TCurrentOperist = "Բ��"
        DrawFlag = 1
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake����_Click()
        fMainForm.TCurrentOperist = "����"
        DrawFlag = 1
        mnuMakeClose.Visible = False '�������ĸ��˵�
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMake��Բ_Click()
        fMainForm.TCurrentOperist = "��Բ"
        mnuMakeClose.Visible = False '�������ĸ��˵�
        DrawFlag = 1
        mnuMakeEnd.Visible = False
        mnuMakeUndo.Visible = True
        mnuMakebar1.Visible = True
End Sub

Private Sub mnuMaketext_Click()
        TCurrentOperist.text = "����"
End Sub

Private Sub mnuMakeDimˮƽ��ע_Click()
        TCurrentOperist.text = "ˮƽ��ע"
        DrawFlag = 1
End Sub

Private Sub mnuMakeDim����ˮƽ��ע_Click() '
        TCurrentOperist.text = "����ˮƽ��ע"
        DrawFlag = 1
End Sub

Private Sub mnuMakeDIm��ֱ��ע_Click()
        TCurrentOperist.text = "��ֱ��ע"
        DrawFlag = 1
End Sub

Private Sub mnuMakeDim������ֱ��ע_Click() '
        TCurrentOperist.text = "������ֱ��ע"
        DrawFlag = 1
End Sub

Private Sub mnuMakedimͬ����ע_Click() '

End Sub

Private Sub mnuMakedim�뾶�ߴ�_Click() '

End Sub

Private Sub mnuMakedimֱ���ߴ�_Click() '

End Sub

Private Sub mnuMakedim�Ծ��ߴ�_Click() '

End Sub

Private Sub mnuMakedim�Ƕȳߴ�_Click() '

End Sub

Private Sub mnuToolObjectList_Click()
        If ON_ERROR_RESUME_NEXT Then
           PassWord.PassWordStyle = "ʵ���б�"
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

Public Sub mnuViewMouseArrow_Click() '���ι��
        With ActiveForm
             .cad.MousePointer = vbArrow
             .Line1.Visible = False
             .Line2.Visible = False
             .Smouse.Visible = False
             .Mousestyle = "���ι��"
        End With
        mnuViewMouseArrow.Checked = True
        mnuViewMouseCircle.Checked = False
        mnuViewMouseBigCross.Checked = False
        mnuViewMouseLittleCross.Checked = False
End Sub

Public Sub mnuViewMouseBigCross_Click()  '��ʮ�ֹ��
        With ActiveForm
             .cad.MousePointer = vbCrosshair       '�Զ�����
             .Line1.Visible = True
             .Line2.Visible = True
             .Smouse.Visible = False
             .Mousestyle = "��ʮ�ֹ��"
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

Public Sub mnuViewMouseCircle_Click()  'Բ�ι��
        With ActiveForm
             .cad.MousePointer = vbCrosshair     '�Զ�����
             .Smouse.Visible = True
             .Mousestyle = "Բ�ι��"
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

Public Sub mnuViewMouseLittleCross_Click()    'Сʮ�ֹ��
        With ActiveForm
            .cad.MousePointer = vbCrosshair
             .Line1.Visible = False
             .Line2.Visible = False
             .Smouse.Visible = False
             .Mousestyle = "Сʮ�ֹ��"
        End With
        mnuViewMouseArrow.Checked = False
        mnuViewMouseBigCross.Checked = False
        mnuViewMouseLittleCross.Checked = True
        mnuViewMouseCircle.Checked = False
End Sub

Private Sub mnuViewZoomIn_Click()  '��С
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    With ActiveForm.cad
        'SnapeField =SnapeField * 2 '��С��׽����
        .top = .top / 2
        .left = .left / 2
        .Width = .Width / 2
        .Height = .Height / 2
        .ScaleHeight = .ScaleHeight * 2
        .Scalewidth = .Scalewidth * 2
        Scroll ActiveForm, .left, .top '������
        ActiveForm.Redraw
    End With
End Sub

Private Sub mnuViewZoomOut_Click() '�Ŵ�
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    With ActiveForm.cad
        'SnapeField = SnapeField / 2 '�Ŵ�׽����
        .top = .top * 2
        .left = .left * 2
        .Width = .Width * 2
        .Height = .Height * 2
        .ScaleHeight = .ScaleHeight / 2
        .Scalewidth = .Scalewidth / 2
        Scroll ActiveForm, .left, .top  '������
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

Private Sub mnuWindowClose_Click() '�رմ���
        Unload ActiveForm
End Sub

Private Sub mnuWindowCloseAllWindow_Click() '�ر����д���
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        'CloseAllWindowFlag�������ǵ��رմ���ʱ,
        '������,�ɰ�ȡ��,ֹͣ�ر�.����ֹ�˴���ѭ��,
        '��ֵ��formcad�е�Form_QueryUnload����������
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
        .DialogTitle = "����Ϊ"
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
    If left$(ActiveForm.Caption, 2) = "��ͼ" Then
        With dlgCommonDialog
            .DialogTitle = "����"
            .CancelError = False
            'ToDo: set the flags and attributes of the Commondialog control
            .Filter = "�������ͼ (*.kld)|*.kld|All Files (*.*)|*.*"
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
        .DialogTitle = "���ļ�"
        .CancelError = False
        'ToDo: set the flags and attributes of the Commondialog control
        .Filter = "�������ͼ (*.kld)|*.kld|All Files (*.*)|*.*"
        .ShowOpen
        If Len(.FileName) = 0 Then
            mnuWindowClose_Click
            Exit Sub
        End If
        sFile = .FileName
    End With
    
    ActiveForm.OpenFile sFile  '���ļ�
    ActiveForm.Caption = sFile  '���ļ������ڴ��ڱ�����

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
             mnuMakeLine�߶�_Click
        Case "twolinemiss"
             mnuEditModifyTwoLineMiss_Click
        Case "��ֱ�߶�"
             mnuMakeLine��ֱ�߶�_Click
        Case "������"
             mnuMake������_Click
        Case "tan"
             mnuMakeLine���㵽Բ������_Click
        Case "line style"
             mnuToolsOptions_Click
        Case "������"
             mnuMake������_Click
        Case "��������"
             mnuMake��������_Click
        Case "������"
             mnuMake������_Click
        Case "rectangle"
             mnuMake����_Click
        Case "��������"
             mnuMake��������_Click
        Case "circle"
             mnuMakeԲ_Click
        Case "rectangle"
            mnuMake����_Click
        Case "arc"
             mnuMakeԲ��_Click
        Case "����"
            mnuMake����_Click
        Case "ellipse"
            mnuMake��Բ_Click
        Case "����"
            mnuMaketext_Click
        Case "ˮƽ��ע"
            mnuMakeDimˮƽ��ע_Click
        Case "����ˮƽ��ע"
            mnuMakeDim����ˮƽ��ע_Click
        Case "��ֱ��ע"
            mnuMakeDIm��ֱ��ע_Click
        Case "������ֱ��ע"
            mnuMakeDim������ֱ��ע_Click
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
        'Select Case Index  'ʹ���а�ť�ָ�ԭ��
        '       Case TB_MAKE
                    UnPressButton TB(Index)
        'End Select
        Button.Value = tbrPressed
End Sub

Private Sub TB_ButtonMenuClick(Index As Integer, ByVal ButtonMenu As MSComctlLib.ButtonMenu)
        '���ð�ť����ʽ
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
Const Make = "lineˮƽ�߶δ�ֱ�߶��������������������ξ�����������Բ��������Բ����ˮƽ��ע����������ֱ��ע���㵽Բ������"
Const Edit = "pointselect�ƶ�������ת������ԭͼ��������Բ�����б����任"
Const Break = "�ж�"
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
                    NoEnabled_Edit 'ʹ�༭���߲���Ӧ�¼�
               Case "make"
                    UnPressButton TB(TB_MAKE)
                    If TCurrentOperist.Tag = "���㵽Բ������" And DrawFlag = 2 Then
                       ActiveForm.MakeUndo TCurrentOperist.Tag
                    End If
        End Select
    End If
    
    ActiveForm.SSnape.Visible = False '�����׽Ŀ��
           
    With TCurrentOperist
       .Tag = .text
       If Val(ActiveForm.cad.Tag) And .text <> "�ƶ�" And .text <> "�����任" Then MouseChange_Undo ActiveForm '�ָ����
       If .text = "pointselect" Then mnuToolSnapeExit_Click  'ѡȡʱ�����ò�׽
       
    End With
End Sub
