VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form fOption 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "ѡ��"
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
   StartUpPosition =   2  '��Ļ����
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
         Caption         =   "դ������"
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
            Caption         =   "���"
            Height          =   180
            Left            =   240
            TabIndex        =   89
            Top             =   840
            Width           =   360
         End
         Begin VB.Label Girdcolor 
            AutoSize        =   -1  'True
            Caption         =   "��ɫ"
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
            Caption         =   "����"
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
         Caption         =   "�Զ���ע��λ"
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
         Caption         =   "����״̬"
         Height          =   975
         Left            =   2160
         TabIndex        =   74
         Top             =   840
         Width           =   1455
         Begin VB.OptionButton DimState 
            Caption         =   "�����ƽ��"
            Height          =   180
            Index           =   2
            Left            =   120
            TabIndex        =   77
            Top             =   720
            Width           =   1215
         End
         Begin VB.OptionButton DimState 
            Caption         =   "���ִ�ֱ"
            Height          =   180
            Index           =   1
            Left            =   120
            TabIndex        =   76
            Top             =   480
            Width           =   1215
         End
         Begin VB.OptionButton DimState 
            Caption         =   "����ˮƽ"
            Height          =   180
            Index           =   0
            Left            =   120
            TabIndex        =   75
            Top             =   240
            Width           =   1095
         End
      End
      Begin VB.Frame fraSample4 
         Caption         =   "��ע��ʽ"
         Height          =   3345
         Index           =   1
         Left            =   120
         TabIndex        =   48
         Top             =   240
         Width           =   1815
         Begin VB.OptionButton DimStyle 
            Caption         =   "ˮƽ��ע"
            Height          =   180
            Index           =   0
            Left            =   240
            TabIndex        =   56
            Top             =   360
            Width           =   1335
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "��ֱ��ע"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   55
            Top             =   720
            Width           =   1335
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "ͬ���߱�ע"
            Height          =   255
            Index           =   2
            Left            =   240
            TabIndex        =   54
            Top             =   1080
            Width           =   1335
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "������ע"
            Height          =   255
            Index           =   3
            Left            =   240
            TabIndex        =   53
            Top             =   1440
            Width           =   1215
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "�뾶�ߴ�"
            Height          =   255
            Index           =   4
            Left            =   240
            TabIndex        =   52
            Top             =   1800
            Width           =   1095
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "ֱ���ߴ�"
            Height          =   255
            Index           =   5
            Left            =   240
            TabIndex        =   51
            Top             =   2160
            Width           =   1215
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "��ע�ߴ�"
            Height          =   255
            Index           =   6
            Left            =   240
            TabIndex        =   50
            Top             =   2520
            Width           =   1095
         End
         Begin VB.OptionButton DimStyle 
            Caption         =   "�Ƕȳߴ�"
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
         Caption         =   "��עλ��"
         Height          =   1215
         Left            =   3840
         TabIndex        =   40
         Top             =   840
         Width           =   1695
         Begin VB.OptionButton DimPos 
            Caption         =   "�ڱ�ע���Ϸ�"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   43
            Top             =   240
            Width           =   1455
         End
         Begin VB.OptionButton DimPos 
            Caption         =   "�ڱ�ע����"
            Height          =   255
            Index           =   1
            Left            =   120
            TabIndex        =   42
            Top             =   600
            Width           =   1335
         End
         Begin VB.OptionButton DimPos 
            Caption         =   "�ڱ�ע����"
            Height          =   180
            Index           =   2
            Left            =   120
            TabIndex        =   41
            Top             =   960
            Width           =   1335
         End
      End
      Begin VB.CheckBox DimAutoDim 
         Caption         =   "�Զ���ע"
         Height          =   255
         Left            =   2160
         TabIndex        =   39
         Top             =   2400
         Width           =   1095
      End
      Begin VB.CheckBox DimFELine 
         Caption         =   "��һ���ӳ���"
         Height          =   255
         Left            =   2160
         TabIndex        =   38
         Top             =   1920
         Width           =   1455
      End
      Begin VB.CheckBox DimSELine 
         Caption         =   "�ڶ����ӳ���"
         Height          =   255
         Left            =   2160
         TabIndex        =   37
         Top             =   2160
         Width           =   1575
      End
      Begin VB.Label Label12 
         Caption         =   "��ͷ�ߴ�"
         Height          =   255
         Left            =   4680
         TabIndex        =   78
         Top             =   0
         Width           =   855
      End
      Begin VB.Label DimELine 
         AutoSize        =   -1  'True
         Caption         =   "�ӳ�����ɫ"
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
         Caption         =   "��ע����ɫ"
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
         Caption         =   "������ɫ"
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
         Caption         =   "����"
         Height          =   180
         Left            =   2160
         MouseIcon       =   "options.frx":0DF8
         MousePointer    =   99  'Custom
         TabIndex        =   59
         Top             =   2760
         Width           =   360
      End
      Begin VB.Label Label15 
         Caption         =   "���ͷ"
         Height          =   255
         Left            =   2160
         TabIndex        =   58
         Top             =   120
         Width           =   615
      End
      Begin VB.Label Label16 
         Caption         =   "�Ҽ�ͷ"
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
         Caption         =   "���"
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
            Caption         =   "�����״"
            Height          =   180
            Left            =   240
            TabIndex        =   73
            Top             =   480
            Width           =   720
         End
         Begin VB.Label MouseColor 
            AutoSize        =   -1  'True
            Caption         =   "�Զ��������ɫ"
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
         Caption         =   "����"
         Height          =   1215
         Left            =   240
         TabIndex        =   63
         Top             =   2280
         Width           =   1695
         Begin VB.OptionButton Coordinate 
            Caption         =   "������"
            Height          =   180
            Index           =   2
            Left            =   240
            TabIndex        =   66
            Top             =   960
            Width           =   1215
         End
         Begin VB.OptionButton Coordinate 
            Caption         =   "�������"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   65
            Top             =   600
            Width           =   1215
         End
         Begin VB.OptionButton Coordinate 
            Caption         =   "��������"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   64
            Top             =   240
            Width           =   1215
         End
      End
      Begin VB.Frame fraSample3 
         Caption         =   "��λ"
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
            Caption         =   "��"
            BeginProperty Font 
               Name            =   "����"
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
            Caption         =   "������"
            Height          =   180
            Left            =   240
            TabIndex        =   33
            Top             =   1320
            Width           =   540
         End
         Begin VB.Label Label9 
            AutoSize        =   -1  'True
            Caption         =   "��λ:"
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
         Caption         =   "��ɫ"
         Height          =   1065
         Index           =   0
         Left            =   2520
         TabIndex        =   81
         Top             =   2640
         Width           =   3015
         Begin VB.Label GenerallyColor 
            AutoSize        =   -1  'True
            Caption         =   "�޸Ļ�ͼʱ�Ĳο���ɫ"
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
            Caption         =   "�޸�ѡȡ��Ŀ���ͻ����ʾ��ɫ"
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
         Caption         =   "�ָ�ϵͳ��ʼֵ "
         Height          =   255
         Left            =   120
         TabIndex        =   32
         Top             =   3360
         Width           =   2175
      End
      Begin VB.CheckBox ShowPaper 
         Caption         =   "��ʾѡȡͼֽ����"
         Height          =   255
         Left            =   120
         TabIndex        =   22
         Top             =   3000
         Width           =   2175
      End
      Begin VB.CheckBox SaveToIniFile 
         Caption         =   "�������ļ��б�������"
         Height          =   255
         Left            =   120
         TabIndex        =   21
         Top             =   2640
         Width           =   2295
      End
      Begin VB.Frame fraSample2 
         Caption         =   "����"
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
            Caption         =   "�߶�:"
            Height          =   180
            Left            =   360
            TabIndex        =   25
            Top             =   1920
            Width           =   450
         End
         Begin VB.Label Label7 
            AutoSize        =   -1  'True
            Caption         =   "���:"
            Height          =   180
            Left            =   360
            TabIndex        =   24
            Top             =   1560
            Width           =   450
         End
         Begin VB.Label Label6 
            AutoSize        =   -1  'True
            Caption         =   "ͼֽ��С"
            Height          =   180
            Left            =   360
            TabIndex        =   23
            Top             =   1080
            Width           =   720
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "�޸�ͼ�����ɫ"
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
            Caption         =   "�޸�ͼֽ����ɫ"
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
         Caption         =   "����"
         Height          =   735
         Left            =   360
         TabIndex        =   67
         Top             =   2400
         Width           =   2295
         Begin VB.Label text 
            AutoSize        =   -1  'True
            Caption         =   "����"
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
            Caption         =   "������ɫ"
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
         Caption         =   "��"
         Height          =   2025
         Left            =   210
         TabIndex        =   5
         Top             =   255
         Width           =   3495
         Begin VB.ComboBox ���� 
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
            Caption         =   "�ʻ�����"
            Height          =   180
            Left            =   360
            TabIndex        =   14
            Top             =   1080
            Width           =   720
         End
         Begin VB.Label Label2 
            AutoSize        =   -1  'True
            Caption         =   "�ʻ����"
            Height          =   180
            Left            =   360
            TabIndex        =   13
            Top             =   600
            Width           =   720
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "�ʵ���ɫ"
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
      Caption         =   "Ӧ��"
      Height          =   375
      Left            =   4920
      TabIndex        =   3
      Top             =   4455
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "ȡ��"
      Height          =   375
      Left            =   3720
      TabIndex        =   2
      Top             =   4455
      Width           =   1095
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "ȷ��"
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
            Caption         =   "�ʺ�����"
            Key             =   "pen"
            Object.ToolTipText     =   "��"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "����ѡ��"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "��λ����������������"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "��ע�ߴ�"
            Key             =   "dimension"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab5 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "դ��"
            ImageVarType    =   2
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "����"
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
'���ô���
'����:����

Option Explicit

Private NoExitFlag As Boolean   '�Ƿ��˳������ڵı�־
Private DrawParameter As Commonparameter '�ʵĲ���,��Ҫ���浽�����ļ���
Private Word As FontType    '���ֲ���
Private Type GenerallyType   '��������
        desk As DeskType   '���mmain.bas�еĶ���
        PaperColor As ColorConstants
        Paper As PaperType   '���mmain.bas�еĶ���
        Mouse As String    '�����״
        MouseColor As ColorConstants '������ɫ
        Viewcolor As ColorConstants  '��ͼʱ��Ԥ����ɫ,��mmain�ж���
        ShowObjectColor As ColorConstants   'ѡȡ��Ŀ���ͻ����ʾ��ɫ,��formcad�ж���
        End Type
Private Generally As GenerallyType '����Ĳ���,Ҫ���浽�����ļ���
Private Dimen As DimensionType     '��ע�Ĳ���,Ҫ���浽�����ļ���
Private Type GirdType
        Style As Integer '����
        Color As ColorConstants '��ɫ
        Distance As Single '���
        End Type
Private Type OtherType    '�����еı���,���浽�����ļ���
        Gird As GirdType  'դ������
        End Type
Private Other As OtherType
Private SaveParameterToInifileFlag As Boolean  '�Ƿ񱣴�����������ļ��еı�־
Private RedoSystemInitialStatusflag As Boolean '�ָ�ϵͳ��ʼֵ

Private Sub Form_Load()
'˵��:Object�����mmain.bas��,�˹����д��ݵ����Ӵ���
Dim i, ss As String * 10

    '���д���
    Me.Move (Screen.Width - Me.Width) / 2, (Screen.Height - Me.Height) / 2
    Options.top = 120   ' ����TapStrip��
    Options.left = 105
    With picOptions(0)
         .left = 210
         .top = 480
    End With
    
    '�ʺ�����(��Ҫ���浽�����ļ���)
    With DrawParameter '��
         Combo1.text = Combo1.List(fMainForm.ActiveForm.cad.DrawWidth - 1)    '�ʻ��Ĵ�ϸ
         .Width = Val(Combo1.text)
         ����.text = ����.List(fMainForm.ActiveForm.cad.DrawStyle)        '�ʻ�������
        .Style = fMainForm.ActiveForm.cad.DrawStyle
        .Color = fMainForm.ActiveForm.GetLineColor
        '��ʾͼ
        pen.DrawWidth = .Width
        pen.DrawStyle = .Style
        PenShow  '��ʾ
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
    
    '����
    With Generally   'ͼֽ��ͼ����ɫ(�Ժ�Ҫ���浽�����ļ���)
         .desk.Color = fMainForm.ActiveForm.desk.BackColor
         .PaperColor = fMainForm.ActiveForm.cad.BackColor
         Picdesk.BackColor = .desk.Color
         Picpaper.BackColor = .PaperColor
         .Viewcolor = Viewcolor Xor Generally.Paper.Color  '������������Ϊ��ɫ
         .ShowObjectColor = fMainForm.ActiveForm.GetShowObjectColor Xor Generally.Paper.Color
    End With
    'ͼֽ�Ĵ�С(��Ҫ���浽�����ļ���,����ͼֽѡȡ�����б��浽�����ļ���)
    PaperUnits.text = fMainForm.ActiveForm.GetPaperUnits  '��ʾͼֽ��λ
    i = GetPrivateProfileString("paper", "width", "8900", ss, 20, mmain.Inifile)
    If i = 0 Then
       ss = "8900"
    Else
       ss = left$(ss, i)
    End If
    PaperWidth.text = Val(ss)  '��ʾ
    i = GetPrivateProfileString("paper", "height", "4900", ss, 20, mmain.Inifile)
    If i = 0 Then
       ss = "4800"
    Else
       ss = left$(ss, i)
    End If
    PaperHeight.text = Val(ss) '��ʾ
    '��ѡ��,��ʾѡȡͼֽ����(��Ҫ���浽�����ļ���,�ڵ��ʱ���ѱ��浽�����ļ���)
    i = GetPrivateProfileString("ѡ��", "������ʱ��ʾѡȡͼֽ����", "1", ss, 10, Inifile)
    If i <> 0 Then
       ss = left$(ss, i)
    Else
       ss = "1"
    End If
    If Val(ss) <> 0 Then
       ShowPaper.Value = vbChecked
    End If
    '��ѡ��,�������ļ��б�������(��Ҫ���浽�����ļ���,�ڵ��ʱ���ѱ��浽�����ļ���)
    i = GetPrivateProfileString("ѡ��", "�����ñ����������ļ���", "1", ss, 10, Inifile)
    If i <> 0 Then
       ss = left$(ss, i)
    Else
       ss = "1"
    End If
    If Val(ss) <> 0 Then
       SaveToIniFile.Value = vbChecked
       SaveParameterToInifileFlag = True '��������������ļ��еı�־
    Else
       SaveParameterToInifileFlag = False
    End If
    '��ѡ��,�ָ�ϵͳ��ʼֵ
    RedoSystemInitialStatusflag = False
       
    '��λ�ͱ�����,����
    With Generally '(�Ժ�Ҫ���浽�����ļ���)
         .Paper.Units = fMainForm.ActiveForm.GetPaperUnits   '��λ
         Unit.text = fMainForm.ActiveForm.GetPaperUnits '��ʾ��λ
         '������
         .Paper.Ratio = fMainForm.ActiveForm.GetPaperRatio
         .Paper.Ratio1 = fMainForm.ActiveForm.GetPaperRatio1
         .Paper.Ratio2 = fMainForm.ActiveForm.GetPaperRatio2
         Ratio1.text = .Paper.Ratio1 '��ʾ
         Ratio2.text = .Paper.Ratio2
         ' ����
         .desk.Coordinates = Coordinates
         Coordinate.Item(Coordinates).Value = True
         '���
         .Mouse = fMainForm.ActiveForm.GetMouseStyle '�������״
         Mouse.text = .Mouse
         .MouseColor = fMainForm.ActiveForm.Line1.BorderColor    '�����ɫ
    End With
    
    '��ע
    With Dimension '(�Ժ�Ҫ���浽�����ļ���)
         Dimen.ArrowSize = .ArrowSize
         DimASize.text = CStr(.ArrowSize)
         Dimen.AutoDimension = .AutoDimension
         DimAutoDim.Value = .AutoDimension
         Dimen.DimensionUnits = .DimensionUnits
         DimUnit.Value = .DimensionUnits
         Dimen.DimensionColor = .DimensionColor
         Dline.BorderColor = .DimensionColor '�ο�ͼ��
         Dimen.ExtensioneLineColor = .ExtensioneLineColor
         DimFELine1.BorderColor = Color '�ο�ͼ��
         DimSELine1.BorderColor = Color
         Dimen.FirstDimension = .FirstDimension
         Dimen.FirstExtensinonLine = .FirstExtensinonLine
         DimFELine.Value = .FirstExtensinonLine
         DimSELine.Value = .SecondExtensioneLine
         DimFELine1.Visible = .FirstExtensinonLine
         Dimen.Font = .Font
         DimText.Font.Bold = .Font.Bold '�ο�ͼ��
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
    
    '����
    With Other '(�Ժ�Ҫ���浽�����ļ���)
         'դ������
         With .Gird
              '.Style = fMainForm.ActiveForm formcad.GIRDl.Item(1).BorderStyle
              'Gird.ListIndex = .Style
              '.Color = fMainForm.ActiveForm.GIRDl.BorderColor
             '.Distance = fMainForm.ActiveForm.GIRDl.Tag
             'GirdDis.text = CStr(.Distance)
         End With
         
    End With
         
End Sub

Private Sub cmdApply_Click()   'Ӧ��
Dim i

    If RedoSystemInitialStatusflag Then '�ָ�ϵͳ��ʼֵ
       i = MsgBox("���Ƿ�����ָ���ϵͳ��ʼֵ���ǽ���ʧ�����û�ֵ��", vbQuestion + vbDefaultButton2 + vbYesNoCancel, "�ָ�ϵͳ����")
       Select Case i
              Case vbYes
                   Kill (Inifile)   'ɾ�������ļ�
                   i = MsgBox("�ѻָ���ϵͳ�ĳ�ʼֵ��Ҫʹ����Ч��" + Chr$(13) + _
                              "     ������������Ӧ�ó���" + Chr$(13) + _
                              "           ������", vbQuestion + vbYesNo + vbDefaultButton2, "ѡ��")
                   If i = vbYes Then
                      Shell App.EXEName, vbMaximizedFocus
                      Unload fMainForm   '�������
                   End If
                   Exit Sub
              Case vbCancel
                   NoExitFlag = True
        End Select
    End If
    
    '�ʺ��ı�
    fMainForm.ActiveForm.InputDrawColor DrawParameter.Color '�ʻ���ɫ
    With fMainForm.ActiveForm.cad ' ��
        .DrawWidth = DrawParameter.Width '�ʻ���ϸ
        .DrawStyle = DrawParameter.Style '�ʻ�����
    End With
    With fMainForm.ActiveForm.cad '�ı�
         .FontBold = Word.Bold
         .ForeColor = Word.Color
         .FontItalic = Word.Italic
         .Font.name = Word.name
         .FontSize = Word.Size
         .FontStrikethru = Word.Strikethru
         .FontTransparent = Word.Transparent
         .FontUnderline = Word.Underline
    End With
    
    '����
    With Generally  'ͼֽ��ͼ����ɫ(Ҫ���浽�����ļ���)
         fMainForm.ActiveForm.desk.BackColor = .desk.Color
         fMainForm.ActiveForm.cad.BackColor = .PaperColor
         Viewcolor = .Viewcolor Xor Generally.Paper.Color   '��ͼʱ��Ԥ����ɫ
         fMainForm.ActiveForm.InputShowObjectColor (.ShowObjectColor Xor Generally.Paper.Color)  'ͻ����ʾ��ɫ
         For i = 0 To 8
             fMainForm.ActiveForm.Shape1(i).BorderColor = .ShowObjectColor + .ShowObjectColor Mod 255
             fMainForm.ActiveForm.Shape1(i).FillColor = .ShowObjectColor + .ShowObjectColor Mod 255
         Next i
         fMainForm.ActiveForm.SPshow.BorderColor = .ShowObjectColor + .ShowObjectColor Mod 255
    End With
    
    '��λ�ͱ�����,��������
    With Generally
         fMainForm.ActiveForm.InputPaperUnits (.Paper.Units)
         fMainForm.ActiveForm.InputPaperRatio (.Paper.Ratio)
         fMainForm.ActiveForm.InputPaperRatio1 (.Paper.Ratio1)
         fMainForm.ActiveForm.InputPaperRatio2 (.Paper.Ratio2)
         Coordinates = .desk.Coordinates '����
         '���
         fMainForm.ActiveForm.InputMouseStyle (.Mouse) '�����״
         fMainForm.ActiveForm.Form_Activate
         .MouseColor = .MouseColor
         fMainForm.ActiveForm.Line1.BorderColor = .MouseColor '�Զ��������ɫ
         fMainForm.ActiveForm.Line2.BorderColor = .MouseColor
         'fMainForm.ActiveForm.Smouse.BorderColor = .MouseColor
    End With
    
    '��ע
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
    
    '����
    With Other
         'դ������
         With .Gird
              'fMainForm.ActiveForm.GIRDl.DrawStyle = .Style
              'fMainForm.ActiveForm.GIRDl.BorderColor = .Color
              
         End With
    End With
    
    '��������������ļ���,
    If SaveParameterToInifileFlag Then
        With Generally '����face.bas ����Ӧ�ĳ�ʼ������
             'ͼֽ��ɫ
             i = WritePrivateProfileString("ѡ��", "ͼֽ��ɫ", CStr(.PaperColor), Inifile)
             'ͼ����ɫ
             i = WritePrivateProfileString("ѡ��", "ͼ����ɫ", CStr(.desk.Color), Inifile)
              '��ͼʱ��Ԥ����ɫ
             i = WritePrivateProfileString("ѡ��", "��ͼʱ��Ԥ����ɫ", CStr(.Viewcolor), Inifile)
             'ѡȡ��Ŀ��ʱ��ͻ����ʾ��ɫ
             i = WritePrivateProfileString("ѡ��", "ͻ����ʾ��ɫ", CStr(.ShowObjectColor), Inifile)
            '��λ
             i = WritePrivateProfileString("ѡ��", "��λ", .Paper.Units, Inifile)
             '������
             i = WritePrivateProfileString("ѡ��", "������", CStr(.Paper.Ratio), Inifile)
             i = WritePrivateProfileString("ѡ��", "������1", CStr(.Paper.Ratio1), Inifile)
             i = WritePrivateProfileString("ѡ��", "������2", CStr(.Paper.Ratio2), Inifile)
             '����
             i = WritePrivateProfileString("ѡ��", "����", CStr(.desk.Coordinates), Inifile)
             '�����״
             i = WritePrivateProfileString("ѡ��", "�����״", .Mouse, Inifile)
             i = WritePrivateProfileString("ѡ��", "�Զ��������ɫ", CStr(.MouseColor), Inifile)
        End With
        With Other
             
        End With
    End If
    
    fMainForm.ActiveForm.Redraw
End Sub

Private Sub cmdCancel_Click()  'ȡ��
    Unload Me
End Sub

Private Sub cmdOK_Click() 'ȷ��
    'MsgBox "��������ô���������ѡ��ҹرնԻ���!"
    cmdApply_Click
    If Not NoExitFlag Then
       Unload Me
    End If
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim i As Integer
    '���� ctrl+tab �����ƶ�����һ��ѡ��
    If Shift = vbCtrlMask And KeyCode = vbKeyTab Then
        i = Options.SelectedItem.Index
        If i = Options.Tabs.Count Then
            '�ѵ�������ѡ��,ת�ص�ѡ�� 1
            Set Options.SelectedItem = Options.Tabs(1)
        Else
            '����ѡ��
            Set Options.SelectedItem = Options.Tabs(i + 1)
        End If
    End If
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
        Exit Sub
End Sub

Private Sub Options_Click()
    
    Dim i As Integer
    '��ʾ��ʹѡ��Ŀؼ�����
    '��������ʹ����������
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

'��
Private Sub Label1_Click()  '��ɫ
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = DrawParameter.Color
             .ShowColor
        End With
        DrawParameter.Color = CommonDialog1.Color
        PenShow   'Ԥ��
End Sub

Private Sub Combo1_Click() '�߿�
        DrawParameter.Width = Val(Combo1.text)
        pen.DrawWidth = DrawParameter.Width 'Ԥ��
        PenShow 'Ԥ��
End Sub

Private Sub ����_Click() '������
Dim Style
#If ON_ERROR_RESUME_NEXT Then
  On Error Resume Next
#End If
  Style = ����.ListIndex
  DrawParameter.Style = Style
  pen.DrawStyle = Style 'Ԥ��
  PenShow 'Ԥ��
End Sub

Private Sub PenShow()  'Ԥ����ʾ
        pen.Cls
        pen.Line (300, 200)-(1300, 900), DrawParameter.Color, B
End Sub

Private Sub text_Click() '��������
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

Private Sub textcolor_Click() '������ɫ
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Word.Color
             .ShowColor
             Word.Color = .Color
        End With
End Sub

'����
Private Sub Label4_Click()  '�޸�ͼֽ��ɫ
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Generally.PaperColor
             .ShowColor
        End With
        Generally.PaperColor = CommonDialog1.Color
        'Ԥ��
        Picpaper.BackColor = CommonDialog1.Color 'Ԥ��
End Sub

Private Sub Label5_Click()  '�޸�ͼ�����ɫ
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Generally.desk.Color
             .ShowColor
        End With
        Generally.desk.Color = CommonDialog1.Color
        'Ԥ��
        Picdesk.BackColor = CommonDialog1.Color
End Sub

Private Sub SaveToIniFile_Click() '�������ļ��б�������
        Dim i
        i = WritePrivateProfileString("ѡ��", "�����ñ����������ļ���", CStr(SaveToIniFile.Value), Inifile)
        If SaveToIniFile.Value <> 0 Then  '�Ƿ񱣴�����������ļ���
           SaveParameterToInifileFlag = True
        Else
           SaveParameterToInifileFlag = False
        End If
End Sub

Private Sub ShowPaper_Click() '��ʾͼֽѡȡ����
Dim i
i = WritePrivateProfileString("ѡ��", "������ʱ��ʾѡȡͼֽ����", CStr(ShowPaper.Value), Inifile)
End Sub

Private Sub Check1_Click()  '�ָ�ϵͳ��ʼֵ
Dim i
        If Check1.Value <> 0 Then
           i = MsgBox("���Ƿ�����ָ���ϵͳ��ʼֵ��" + Chr$(13) + "�ǽ���ʧ�����û�ֵ��", vbQuestion + vbYesNo + vbDefaultButton2, "�ָ�ϵͳ����")
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
                    Case 0  '��ͼʱ��Ԥ����ɫ
                         CommonDialog1.Color = .Viewcolor
                         CommonDialog1.Flags = cdlCCFullOpen + cdlCCRGBInit
                         CommonDialog1.ShowColor
                         .Viewcolor = CommonDialog1.Color
                    Case 1 'ͻ����ʾ��ɫ
                         CommonDialog1.Color = .ShowObjectColor
                         CommonDialog1.Flags = cdlCCFullOpen + cdlCCRGBInit
                         CommonDialog1.ShowColor
                         .ShowObjectColor = CommonDialog1.Color
             End Select
        End With
DimP.DrawMode = m
End Sub

'��λ�ͱ�����,��������
Private Sub Unit_Click()   '��λ
        Generally.Paper.Units = Unit.List(Unit.ListIndex)
        PaperUnits.text = Generally.Paper.Units  'ͼֽ��λ
        DimUnit_Click '��ע�еĲο�ͼ���еĵ�λ
End Sub

Private Sub Ratio1_Change()  '������1
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        With Generally
             .Paper.Ratio1 = Ratio1.text
             .Paper.Ratio = Val(Ratio2.text) / Val(Ratio1.text)
        End With
End Sub

Private Sub Ratio2_Change() ' ������2
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        With Generally.Paper
             .Ratio2 = Ratio2.text
             .Ratio = Val(Ratio2.text) / Val(Ratio1.text)
        End With
End Sub

Private Sub Coordinate_Click(Index As Integer)  '����
        Generally.desk.Coordinates = Index
End Sub

Private Sub Mouse_Click() '�����״
        Generally.Mouse = Mouse.List(Mouse.ListIndex)
End Sub

Private Sub MouseColor_Click() ' �Զ��������ɫ
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Generally.MouseColor
             .ShowColor
             Generally.MouseColor = .Color
        End With
End Sub

'��ע
Private Sub DimStyle_Click(Index As Integer) '��ע����
        Dimen.Style = DimStyle(Index).Caption
End Sub

Private Sub DimLeftarrow_Click() '���ͷ
        Dimen.LeftArrowHead = DimLeftarrow.ListIndex
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimRightarrow_Click() '�Ҽ�ͷ
        Dimen.RightArrowHead = DimRightarrow.ListIndex
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimASize_Click() '��ͷ�ߴ�
        Dimen.ArrowSize = Val(DimASize.text)
        DimP.Cls '�ο�ͼ��
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimState_Click(Index As Integer) '����״̬
        Dimen.FontState = Index
End Sub

Private Sub DimPos_Click(Index As Integer) '��עλ��
        Dimen.Position = Index
        With DimText '�ο�ͼ��
             Select Case Index
                    Case 0
                         .top = Dline.Y1 - .Height
                    Case 1
               
                    Case 2
                         .top = Dline.Y1 - .Height / 2
             End Select
        End With
End Sub

Private Sub DimFELine_Click() '��һ���ӳ���
        Dimen.FirstExtensinonLine = DimFELine.Value
        DimFELine1.Visible = DimFELine.Value '�ο�ͼ��
End Sub

Private Sub DimSELine_Click() '�ڶ����ӳ���
        Dimen.SecondExtensioneLine = DimSELine.Value
        DimSELine1.Visible = DimSELine.Value '�ο�ͼ��
End Sub

Private Sub DimAutoDim_Click() '�Զ���ע
        Dimen.AutoDimension = DimAutoDim.Value
        If DimAutoDim.Value Then '�ο�ͼ��
           DimText.Visible = True
        Else
           DimText.Visible = False
        End If
End Sub

Private Sub DimUnit_Click() '�Զ���ע��λ
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

Private Sub DimFont_Click() '��ע����
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
             DimText.Font.Bold = .FontBold     '�ο�ͼ��
             DimText.Font.Italic = .FontItalic
             DimText.Font.name = .FontName
             DimText.Font.Size = .FontSize
             DimText.Font.Strikethrough = .FontStrikethru
             DimText.Font.Underline = .FontUnderline
        End With
        With Dline  '�ο�ͼ��
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

Private Sub DimFontColor_Click() '��ע������ɫ
        With CommonDialog1
            .Flags = cdlCCFullOpen + cdlCCRGBInit
            .Color = Dimen.Font.Color
             .ShowColor
             Dimen.Font.Color = .Color
             DimText.ForeColor = .Color  '�ο�ͼ��
        End With
End Sub

Private Sub Dimline_Click() '��ע����ɫ
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Dimen.DimensionColor
             .ShowColor
             Dimen.DimensionColor = .Color
             Dline.BorderColor = .Color  '�ο�ͼ��
        End With
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub DimELine_Click() '�ӳ�����ɫ
        With CommonDialog1
             .Flags = cdlCCFullOpen + cdlCCRGBInit
             .Color = Dimen.ExtensioneLineColor
             .ShowColor
             Dimen.ExtensioneLineColor = .Color
             DimFELine1.BorderColor = .Color   '�ο�ͼ��
             DimSELine1.BorderColor = .Color
        End With
        DimP.Cls
        DrawArrow DimP, Dline.BorderColor, Dline.X1, Dline.Y1, Dline.X2, Dline.Y2, Dimen.LeftArrowHead, Dimen.RightArrowHead, Dimen.ArrowSize, True, 0
End Sub

Private Sub Gird_Click() 'դ������
Dim Style
#If ON_ERROR_RESUME_NEXT Then
  On Error Resume Next
#End If
  Style = Gird.ListIndex
  Other.GirdStyle = Style
  pen.DrawStyle = Style 'Ԥ��
  PenShow 'Ԥ��
End Sub


'����
         

