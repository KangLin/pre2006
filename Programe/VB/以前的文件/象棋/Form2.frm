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
   StartUpPosition =   2  '��Ļ����
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
      Caption         =   "���̹���"
      Height          =   1215
      Left            =   2640
      TabIndex        =   13
      Top             =   3840
      Width           =   1455
      Begin VB.CommandButton CmdNext 
         Caption         =   "��һ����&N)"
         Height          =   300
         Left            =   120
         TabIndex        =   16
         Top             =   600
         Width           =   1215
      End
      Begin VB.CommandButton CmdCanel 
         Caption         =   "ȡ  ��(&C)"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   960
         Width           =   1215
      End
      Begin VB.CommandButton CmdPre 
         Caption         =   "��һ����&P)"
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
      Caption         =   "��ʾ"
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
            Caption         =   "����ʱ�䣺"
            Height          =   180
            Index           =   1
            Left            =   120
            TabIndex        =   11
            Top             =   600
            Width           =   900
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "�ܹ�ʱ�䣺"
            Height          =   180
            Index           =   2
            Left            =   120
            TabIndex        =   10
            Top             =   960
            Width           =   900
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "����ʱ�䣺"
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
            Key             =   "ʿ"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":0848
            Key             =   "��"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":0B64
            Key             =   "��"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":0E80
            Key             =   "��"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":119C
            Key             =   "��"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":14B8
            Key             =   "��"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form2.frx":17D4
            Key             =   "��"
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
      Caption         =   "�ҷ�"
      Height          =   180
      Left            =   3120
      TabIndex        =   3
      Top             =   3600
      Width           =   360
   End
   Begin VB.Label LabJF 
      AutoSize        =   -1  'True
      Caption         =   "�׷�"
      Height          =   180
      Left            =   2880
      TabIndex        =   2
      Top             =   360
      Width           =   360
   End
   Begin VB.Menu mnuFile 
      Caption         =   "����(&T)"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "����(&O)"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "����(&S)"
      End
      Begin VB.Menu mnuFileContine 
         Caption         =   "������(&C)"
      End
      Begin VB.Menu mnuFileReStart 
         Caption         =   "���¿�ʼ(&R)"
      End
      Begin VB.Menu mnuBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileBuJu 
         Caption         =   "����(&B)"
      End
      Begin VB.Menu mnuFileBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "�˳�(&E)"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "�༭(&E)"
      Begin VB.Menu mnuEditCopy 
         Caption         =   "����(&C)"
      End
      Begin VB.Menu mnuEditPase 
         Caption         =   "ճ��(&P)"
      End
      Begin VB.Menu mnuEditCut 
         Caption         =   "����(&T)"
      End
   End
   Begin VB.Menu mnuOption 
      Caption         =   "ѡ��(&O)"
      Begin VB.Menu mnuFileManAndMan 
         Caption         =   "˫�˶�ս(&T)"
      End
      Begin VB.Menu mnuFileManAndMachine 
         Caption         =   "�˻���ս(&M)"
      End
      Begin VB.Menu mnuFileNet 
         Caption         =   "�����ս(&N)"
      End
      Begin VB.Menu mnuOPtionBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionSavePassWord 
         Caption         =   "���ñ�������(&C)"
      End
      Begin VB.Menu mnuOptionSetAutoFuPang 
         Caption         =   "�����Զ�����ʱ��(&T)"
      End
      Begin VB.Menu mnuOptionSetQiZhiChaiLiao 
         Caption         =   "�������Ӳ���(&M)"
      End
      Begin VB.Menu mnuOptionWindowBack 
         Caption         =   "���ô��ڱ���(&B)"
      End
      Begin VB.Menu mnuOptionQiPangStyle 
         Caption         =   "����������ʽ(&S)"
      End
      Begin VB.Menu mnuOPtionBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionShowTime 
         Caption         =   "��ʾʱ��(&X)"
      End
      Begin VB.Menu mnuOptionStateBar 
         Caption         =   "��ʾ״̬��(&Z)"
      End
      Begin VB.Menu mnuOptionShowTalk 
         Caption         =   "��ʾ�Ի���"
      End
   End
   Begin VB.Menu mnuOptionNet 
      Caption         =   "����ѡ��(&N)"
      Begin VB.Menu mnuOptionNetClearTalkRecord 
         Caption         =   "����Ի���¼"
      End
      Begin VB.Menu mnuOptionNetOpenTalkRecord 
         Caption         =   "�򿪶Ի���¼"
      End
      Begin VB.Menu mnuOptionNetSaveTalkRecord 
         Caption         =   "����Ի���¼"
      End
      Begin VB.Menu mnuOptionNetBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionNetTalkLocalColor 
         Caption         =   "���ñ��ؼ�¼��ɫ"
      End
      Begin VB.Menu mnuOptionNetTextTalkRemoteColor 
         Caption         =   "����Զ�˼�¼����ɫ"
      End
      Begin VB.Menu mnuOptionNetTextTalkRemoteOrtherColor 
         Caption         =   "����Զ��������¼����ɫ"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "����(&H)"
      Begin VB.Menu mnuHelpXinShiFenXiBiao 
         Caption         =   "���Ʒ�����(&X)"
      End
      Begin VB.Menu mnuHelpBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "����(&A)"
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
Dim bFileAdd_Mi As Boolean '��־װ����ļ��Ƿ��Ǽ����ļ�

Dim s��սģʽ As String
Dim bXiaoQi As Boolean '��־�Ƿ�����
Dim bFuPangEnd As Boolean '���̽�����־
Dim bFuPang As Boolean '���̱�־
Dim lFuPang As Long '��¼���̵Ĳ���
Dim nAutoFuPangTime As Date   '�Զ�����ʱ��
Private Type Type_Time
        StartTime As Date '��ʼ�����ʱ��
        OneStartTime As Date 'ÿ��һ����ʱ��
        TotalWalkTime As Date 'ÿһ���ܹ��ߵ�ʱ��
        jTotalWalkTime As Date '���ܹ��ߵ�ʱ��
        yTotalWalkTime As Date '���ܹ��ߵ�ʱ��
        End Type
Dim tTime As Type_Time
Dim sQiPangStyleFileName As String '������ʽ�ļ���
Dim IniFile As String '�����ļ�

'�������йصĲ���
Private Type Type_Net
        'Զ�˼�¼����ɫ
        NetTalkTextColorRemote As ColorConstants
        'Զ�˼�¼���û���
        NetTalkTextNameRemote As String
        'Զ��������¼����ɫ
        NetTalkTextColorRemoteOrther As ColorConstants
        '���ؼ�¼����ɫ
        NetTalkTextColorLocal As ColorConstants
        '���ؼ�¼���û���
        NetTalkUserNameLocal As String
        'Ҫ�༭�ĶԻ���
        NetEditText As RichTextBox
        'Զ������
        NetRemoteWork As Boolean
        End Type
Dim tNet As Type_Net
Enum Enum_SetNetPara_Called
     ���������е�Ĭ�ϵ���
     ���˵��е������ս����
     �������û�ʱ����
End Enum
Enum Enum_SendTalk
     ����Ĭ��ֵ
     ��������
     ���ͶԻ�
End Enum

Private Type Type_File_Hand
        AppTitle As String * 30 '����ı���
        Major As Integer '���汾��
        Minor As Integer '�ΰ汾��
        Disger As String * 4 '�����
        CompanyName  As String * 300 '��˾��
        NoPassWordFlag As Boolean '�Ƿ��������־,ֻ�е�
                'PassWord=0,�Ҵ�ֵΪ��ʱ,��FileTypeΪ�ı���ʽʱ
                '��MyPassWordm<>0,��û��������,
        FileType As Integer
        App_BiaoZhi As String * 10 'Ӧ�ó����ʶ
        App_BiaoZhi_ID As Long 'Ӧ�ó����ʶIDֵ
        PassWord As Double  '����
        MyPassWord As Long '�Լ�������
        bBuJu As Boolean '���ֱ�ʶ
        SheiZhou As Integer '����ʱ���߷�,ֻ��Ϊ����׷������ѷ�
        End Type
Dim tFileHand As Type_File_Hand

Enum Enum_IniFile '����ChangeIniFile�����������ļ�
     ȡ�����Ӳ���
     д��������Ӳ���
     д�����Ӳ�����ϵͳ���õ�
     ȡ��������ʽ
     д��������ʽ
     ȡ�����ڱ���
     д�봰�ڱ���
     ȡ���Զ����̵�ʱ��
     д���Զ����̵�ʱ��
     ȡ����ս��ʽ
     д���ս��ʽ֮���˶�ս
     д���ս��ʽ֮�˻���ս
     д���ս��ʽ֮�����ս
     д��˵�����ʾ״̬����״̬
     ȡ���˵�����ʾ״̬����״̬
     д��˵�����ʾʱ���״̬
     ȡ���˵�����ʾʱ���״̬
     д��Զ�˼�¼��ɫ
     ȡ��Զ�˼�¼��ɫ
     д��Զ��������¼��ɫ
     ȡ��Զ��������¼��ɫ
     д�뱾�ؼ�¼��ɫ
     ȡ�����ؼ�¼��ɫ
     д��˵�����ʾ�Ի����״̬
     ȡ���˵�����ʾ�Ի����״̬
End Enum

Enum Enum_File_Flag '�����ļ�����ı�־
     �ı���ʽ
     ���ܸ�ʽ
     �����ı���ʽ
     ���ּ��ܸ�ʽ
End Enum
 
Enum Enum_PassWord_Flag
     ���ļ��Ӽ��ܸ�ʽת��Ϊ�ı���ʽ
     �򿪼����ļ�
     ���ñ�������
End Enum

Private Enum Enum_SetUserName
        ���úڷ��û�����Initally�е���
        �����û���ǩλ��
End Enum

Public Enum Enum_Windows_style '����2������
       ���Ʒ�������
End Enum

'---------------------------------------------------------
Const s���ٸ��̶��Ǽ����� = "��ȷ�����ٸ���,���Ǽ�������"
Const s�����ļ����� = "�����ļ�����"
Const s���ļ����� = "���ļ�����"
Const s�����ļ� = "Ҫ������������?"
Const s�������ӵĲ���˵�� = "���ӵĲ���Ϊͼ��(.ICO)�ļ�,���������ӡ�"
Const s�������ӵĲ���˵��1 = "        ��Ҫ���Լ������Ӳ�����"
Const s�������ӵĲ���˵��2 = " ����&N)�����ָ�ϵͳĬ�����Ӳ��ϣ���"
Const s�����Ӳ����ļ����� = "�򿪵��ļ����Ͳ��ԡ�"
Const s�Զ�������ʾ = "�������������Զ�����ʱÿ���ļ��ʱ��"
Const s�Զ�������ʾ1 = "    (��ʽΪhh:mm:ss,��λΪ:��)��"
Const s�Զ�������ʾ2 = "�������Ҫ����Ϊ�ֶ�,������00:00:00��"
Const s���̽��� = "�����Ѿ�������"
Const s�ļ��򿪴��� = "�ļ��򿪴���"
Const s����ʱ��Ҫ���� = "����ʱ��Ҫ����,����ڴ˴���"
Const s�������߷� = "                 ѡ�����߷�?"
Const s�������߷�1 = "������߷�Ϊ�׷�,�뵥����(Y),���ѷ�,�뵥����(N)."
Const s˧�����Ƴ����� = "˧�����Ƴ�����"
Const s�޸Ķ�սģʽ = "��Ҫ�޸Ķ�սģʽ��?"
Const s�˻���սѡ�����߷� = "����Ϊ�׷�,�����������,�밴��(Y),���򰴷�(N)."
Const s���˶�ս˭���� = "����׷�����,�밴��(Y),���򰴷�(N)."
Const s�й����� = "�й����� "
Const s���� = " ���� "
Const s������ = " ������ "
Const s���� = " ���� "
Const s������Է���ַ = "������Է���ַ:"
Const s�Ǳ������еļ�¼ = "�������еļ�¼?"
Const s�����뱾���û��� = "�����뱾���û���:"
Const s������Զ���û��� = "������Զ���û���:"
Const s�Ƿ����� = "�����û�����?"

Dim sX As Single, sY As Single '���̵����
Dim sD As Long '���̼��
Dim qR As Single '���ӵİ뾶
Dim qCol As ColorConstants '���̵���ɫ
Private Type Type_QiJu
        iQiJu As Integer
        oObject As Object
        End Type
Dim QiJu(9, 10) As Type_QiJu '�������,���ڼ�¼��ǰ��ֵ���ʽ
Dim BuJuQiJu(9, 10) As Enum_QiZhi     '�ھ��������,���ڼ�¼���ֵ����
Dim QJ() As Integer '��������,���ڼ�¼����

Private Type Type_QiZhiAttrib '���ӵ�����,���ڱ�־���ӵ�����
        Color As ColorConstants
        Name As String '�û���
        sName As String '�׷����ҷ�
        End Type
Dim jF As Type_QiZhiAttrib
Dim yF As Type_QiZhiAttrib

Private Enum Enum_qStep '���岽����ö�ٱ�־
        ����׷�
        �׷���
        �����ҷ�
        �ҷ���
End Enum
Dim qStep As Enum_qStep  '���岽��:��˭��,����׷�,�׷���,�����ѷ�,�ѷ���
Dim ZouQiPangShu As Long '�����巽

Private Type Type_qDefine '���ڶ�������ʱ��ʱ��Ŷ�������Ӻ�λ�õĽṹ
        oQiZhi As Object '��Ŷ��������
        QiZhi As Enum_QiZhi
        X As Single     'λ��X
        Y As Single     'λ��Y
        End Type
Dim qDefine  As Type_qDefine '���ڶ�������ʱ��ʱ��Ŷ�������Ӻ�λ��

Private Enum Enum_Xin_Flag '��������λ��ö�ٱ�־
        ��
        ��
        �����
End Enum

Public Enum Enum_QiJu_eArrary_Flag '���ں���QiJu_eArrary,���������Ĳ���
        �����鸳ֵ
        ��������ȡֵ
End Enum

Private Enum Enum_RecordQj_Flag '���ں���RecordQJ,����������Ĳ���
        �����¼����
        �����¼�����е�Posλ��
        �Ӽ�¼������ȡ��
End Enum

Public Enum Enum_ZhouBiao_eTranslate_Flag '��������ת���ı�ٱ�־
        �������ϵ�����ת��Ϊ�������
        ���������ת��Ϊ�����ϵ�����
End Enum
Public Enum Enum_QZ '���ӵ�ö����
        No = 0 '����
        Che = 1 '��
        Ma = 2 '��
        Xiang = 3 '��
        Shi = 4  'ʿ
        Shuai = 5 '˧
        Bing = 6 ' ��
        Pao = 7 '��
        jFan = 1 '�׷�
        yFan = -1 '�ҷ�
End Enum

Public Enum Enum_QiZhi
        NoZhi = No '����
        '�׷�
        jChe = Che '��
        jMa = Ma '��
        jXiang = Xiang '��
        jShi = Shi 'ʿ
        jShuai = Shuai '˧
        jBing = Bing ' ��
        jPao = Pao '��
        '�ҷ�
        yChe = -Che
        yMa = -Ma
        yXiang = -Xiang
        yShi = -Shi
        yShuai = -Shuai
        yBing = -Bing
        yPao = -Pao
End Enum

'ѡ������,����:ȷ��LOGFONT����
'����:WidthΪ����Ŀ�,HeightΪ����ĸ�(��λΪ����),
'AngleΪ����ĽǶ�(��λΪ��)
Private Function OptionFont(Width As Long, Height As Long, Optional Angle As Long = 0) As LOGFONT 'ѡ������
With OptionFont
     .lfCharSet = OEM_CHARSET
     .lfWeight = 700
     .lfWidth = PicQiPang.ScaleX(Width, VBRUN.ScaleModeConstants.vbTwips, VBRUN.ScaleModeConstants.vbPixels)
     .lfHeight = PicQiPang.ScaleX(Height, VBRUN.ScaleModeConstants.vbTwips, VBRUN.ScaleModeConstants.vbPixels)
     .lfEscapement = Angle * 10
     .lfFaceName = "����"
End With
End Function

'������
Private Sub Draw_QiPang()
On Error Resume Next
Dim I As Long, W As Integer
Dim NewFont As Long, OldFont As Long, Col As ColorConstants
Dim LF As LOGFONT
W = PicQiPang.DrawWidth
Col = PicQiPang.ForeColor
PicQiPang.ForeColor = qCol '�����ߵ���ɫ

'ˮƽ��
For I = 0 To 9
    If I = 0 Or I = 9 Then
       PicQiPang.DrawWidth = 4
    Else
       PicQiPang.DrawWidth = 3
    End If
    PicQiPang.Line (sX, sY + I * sD)-(sX + 8 * sD, sY + I * sD), qCol
Next I
'��ֱ��
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
'�Ź�
PicQiPang.DrawWidth = 2
PicQiPang.Line (sX + 3 * sD, sY)-(sX + 5 * sD, sY + 2 * sD), qCol
PicQiPang.Line (sX + 5 * sD, sY)-(sX + 3 * sD, sY + 2 * sD), qCol
PicQiPang.Line (sX + 3 * sD, sY * 8)-(sX + 5 * sD, sY + 9 * sD), qCol
PicQiPang.Line (sX + 5 * sD, sY * 8)-(sX + 3 * sD, sY + 9 * sD), qCol
'��λ
For I = 1 To 3
    Xin sX + 2 * sD * I, sY + 3 * sD
    Xin sX + 2 * sD * I, sY + 6 * sD
Next
Xin sX + sD, sY + 2 * sD
Xin sX + 7 * sD, sY + 7 * sD
Xin sX + 7 * sD, sY + 2 * sD
Xin sX + sD, sY + 7 * sD
Xin sX, sY + 3 * sD, ��
Xin sX, sY + 6 * sD, ��
Xin sX + 8 * sD, sY + 3 * sD, ��
Xin sX + 8 * sD, sY + 6 * sD, ��
'д���Ӻ���
LF = OptionFont(sD * 4 / 10, sD * 8 / 10, 270)
NewFont = CreateFontIndirect(LF)
OldFont = SelectObject(PicQiPang.hDc, NewFont)
PicQiPang.CurrentY = sY + sD * 4 + sD * 1.5 / 10
PicQiPang.CurrentX = sX + sD * 2
PicQiPang.Print "��"
PicQiPang.CurrentY = sY + sD * 4 + sD * 1.5 / 10
PicQiPang.CurrentX = sX + sD * 3
PicQiPang.Print "��"
NewFont = SelectObject(PicQiPang.hDc, OldFont)
I = DeleteObject(NewFont)
LF = OptionFont(sD * 4 / 10, sD * 8 / 10, 90)
NewFont = CreateFontIndirect(LF)
OldFont = SelectObject(PicQiPang.hDc, NewFont)
PicQiPang.CurrentY = sY + sD * 5 - sD * 1.5 / 20
PicQiPang.CurrentX = sX + sD * 5
PicQiPang.Print "��"
PicQiPang.CurrentY = sY + sD * 5 - sD * 1.5 / 20
PicQiPang.CurrentX = sX + sD * 6
PicQiPang.Print "��"
NewFont = SelectObject(PicQiPang.hDc, OldFont)
I = DeleteObject(NewFont)
PicQiPang.DrawWidth = W
PicQiPang.ForeColor = Col
End Sub

'�������ϵ���λ
Private Sub Xin(X As Single, Y As Single, Optional Flag As Enum_Xin_Flag = �����)
Dim L As Single, L1 As Single, L2 As Single
L1 = sD / 10
L = sD / 2 - L1
'��
If Flag = �� Or Flag = ����� Then
   PicQiPang.Line (X - L1, Y - L)-(X - L1, Y - L1), qCol '  |
   PicQiPang.Line (X - L, Y - L1)-(X - L1, Y - L1), qCol ' --
   PicQiPang.Line (X - L, Y + L1)-(X - L1, Y + L1), qCol ' --
   PicQiPang.Line (X - L1, Y + L)-(X - L1, Y + L1), qCol '  |
End If
'��
If Flag = �� Or Flag = ����� Then
   PicQiPang.Line (X + L1, Y - L)-(X + L1, Y - L1), qCol '  |
   PicQiPang.Line (X + L, Y - L1)-(X + L1, Y - L1), qCol '   --
   PicQiPang.Line (X + L, Y + L1)-(X + L1, Y + L1), qCol '   --
   PicQiPang.Line (X + L1, Y + L)-(X + L1, Y + L1), qCol '  |
End If
End Sub

'�������ӵ�λ��
Private Sub SetPos(ByVal X As Single, ByVal Y As Single, QiZhi As Object)
Dim I As Integer, j As Integer
ZhouBiao_eTranslate X, Y, I, j '����ת��
With QiZhi
     .Visible = False
     ZhouBiao_eTranslate X, Y, I, j, ���������ת��Ϊ�����ϵ�����
     .Top = Y - .Height / 2
     .Left = X - .Width / 2
     '.Top = sY + sD * J - .Height / 2
     '.Left = sX + sD * I - .Width / 2
     .Visible = True
End With
End Sub

'���������Ĳ���:�����鸳ֵ;��������ȡֵ
'����ֵ:�����鸳ֵ�޷���ֵ;��������ȡֵ,�������ӵı�־ֵ
Public Function QiJu_eArrary(X As Single, Y As Single, Optional QiZhi As Enum_QiZhi, Optional Flag As Enum_QiJu_eArrary_Flag = ��������ȡֵ, Optional Object As Object = Nothing) As Integer
Dim I As Integer, j As Integer
ZhouBiao_eTranslate X, Y, I, j '����ת��
'ת��Ϊ����
If Flag = �����鸳ֵ Then
   With QiJu(I, j)
        .iQiJu = QiZhi
        Set .oObject = Object
   End With
End If
If Flag = ��������ȡֵ Then
   QiJu_eArrary = QiJu(I, j).iQiJu
   Set Object = QiJu(I, j).oObject
End If
End Function

'����ת��:�������ϵ�����ת��Ϊ�������
Public Sub ZhouBiao_eTranslate(X As Single, Y As Single, I As Integer, j As Integer, Optional Flag As Enum_ZhouBiao_eTranslate_Flag = �������ϵ�����ת��Ϊ�������)
Select Case Flag
       Case �������ϵ�����ת��Ϊ�������
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
       Case ���������ת��Ϊ�����ϵ�����
            Y = sY + sD * (j - 1)
            X = sX + sD * (I - 1)
End Select
End Sub

'��������:�������4��:�����¿ؼ�,װ������ͼƬ
'         �������õ�λ��(X,Y),���޸��������
Private Sub Make_QiZhi(X As Single, Y As Single, QiZhi As Enum_QiZhi)
Dim hPen As Long, hBrush As Long, hDc As Long
Dim hFont As Long, hOld As Long
Dim hPic As New StdPicture, tFont As LOGFONT
Dim W As Long, H As Single
Dim S As String

If QiZhi <> NoZhi Then
   '1.��װ�����ӿؼ�
   Load QZ(QZ.UBound + 1)
   With QZ(QZ.UBound)
     .Tag = QiZhi '��ʶ�ؼ�Ϊʲô��,
          '���ڲ�����,������ _
          'PicNoQi_DragDrop��PicQiPang_DragDrop
     .Width = 2 * qR
     .Height = .Width
     .Stretch = True
     .DragMode = vbManual
      '2.������,��װ������ͼƬ
      Set .Picture = Draw_QiZhi(QiZhi)
     .Visible = True
   End With
   '3.�������ӵ�λ��
   SetPos X, Y, QZ(QZ.UBound)
   '4.��������鸳ֵ(���ؼ�)
   QiJu_eArrary X, Y, QiZhi, �����鸳ֵ, QZ(QZ.UBound)
Else '4.����������и�ֵ(�����ؼ�)
   QiJu_eArrary X, Y, QiZhi, �����鸳ֵ
End If
End Sub

'������,��װ������ͼƬ
'����ͼƬ��������ͼƬ(���ӵĲ���ͼƬ�����ӵ���ͼƬ)���Ӷ��ɵ�
Private Function Draw_QiZhi(QiZhi As Enum_QiZhi) As IPictureDisp
On Error Resume Next
Dim S As String, oPic As New StdPicture, K As String
   'ȷ�����ӵ���ͼƬ
   Select Case QiZhi
          Case jChe
               'If Run Then
               '   s = "�쳵"
               'Else
                  S = "��"
               'End If
               K = "r"
          Case yChe
               S = "��"
               K = "b"
          Case jMa
               'If Run Then
               '   s = "����"
               'Else
                  S = "��"
               'End If
               K = "r"
          Case yMa
               S = "��": K = "b"
          Case jXiang
               S = "��": K = "r"
          Case yXiang
               S = "��": K = "b"
          Case jShi
               S = "ʿ": K = "r"
          Case yShi
               S = "ʿ": K = "b"
          Case jShuai
               S = "��": K = "r"
          Case yShuai
               S = "��": K = "b"
          Case jBing
               S = "��": K = "r"
          Case yBing
               S = "��": K = "b"
          Case jPao
               'If Run Then
               '   s = "����"
               'Else
                  S = "��"
               'End If
               K = "r"
          Case yPao
               S = "��": K = "b"
   End Select
   With ImgList
        Set Draw_QiZhi = .Overlay("add", S) '���û����õ����Ӳ���ͼƬ
        If Err.Number Then '���Դ������Ӳ���ͼƬ
           Set Draw_QiZhi = .Overlay(K, S)
        End If
   End With
End Function

'����
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

'��ʼ��,��5��,��5����λ�ò��ܸı�.
Private Sub Initally()
'On Error Resume Next
Dim I As Long, Ctr As Object

'1.���ó�ʼ����
Erase QiJu '(9, 10) '�ÿ�����
ReDim QJ(0)

Me.Caption = s�й����� & "-" & s��սģʽ
bXiaoQi = False '�����־
mnuFileBuJu.Checked = False '���ò���ѡ��
tFileHand.bBuJu = False
bFileAdd_Mi = False
bFuPangEnd = False '���̽�����־
Set qDefine.oQiZhi = Nothing
tFileHand.SheiZhou = qStep
SetUserName '���ø������û�����
For Each Ctr In QZ
    If Not Ctr Is QZ(0) Then
       Unload Ctr
    End If
Next
QZ(0).Visible = False
PicQiPang.Cls

'2.ȷ�����̲���
With PicQiPang
     sX = (Me.ScaleHeight - LabJF.Height - LabYF.Height) / 15
     .Top = 2 * sX
     .Height = Me.ScaleHeight - 4 * sX
     .Width = sX * 11
     .Left = (Me.ScaleWidth - .Width) / 2
     SetUserName �����û���ǩλ��
     sX = PicQiPang.ScaleHeight / 11
     sD = sX
     sY = sX
     qR = sD * 9 / 20  '���ӵİ뾶
End With
qCol = vbRed '�������̵���ɫ
'3.����������ʽ,������
If sQiPangStyleFileName <> "" Then
   LoadQiPangStyle sQiPangStyleFileName
Else
   Draw_QiPang '������
End If
'4.����
PutDown

'5.��ʼ������
InitallyInterface

'6.�˻���սʱ,�������߱�ʶ
If mnuFileManAndMachine.Checked Then
   MachineWalk
End If
'7.��ʾ
Call Tishi
End Sub

'��ʼ������
Private Sub InitallyInterface()
'1.��ʼ��״̬��
With StatBar
     .Panels.Clear
     .Panels.Add , "j", "�췽:"
     .Panels("j").Bevel = sbrRaised
     .Panels("j").Alignment = sbrCenter
     .Panels.Add , "jtext", jF.Name
     .Panels.Item(.Panels.Count).AutoSize = sbrContents
     .Panels.Add , "y", "�ڷ�:"
     .Panels("y").Bevel = sbrRaised
     .Panels("y").Alignment = sbrCenter
     .Panels.Add , "ytext", yF.Name
     .Panels.Add , , "�� " & ZouQiPangShu & " ��"
     .Panels.Item(.Panels.Count).AutoSize = sbrContents
     .Panels.Add , "t", "ʱ��:"
     .Panels.Item(.Panels.Count).AutoSize = sbrContents
     .Panels("t").Bevel = sbrRaised
     .Panels("t").Alignment = sbrCenter
     .Panels.Add , "to"
     .Panels("to").Style = sbrTime
     .Visible = mnuOptionStateBar.Checked
End With
Tim.Interval = 360
'2.��ʾ
With tTime '��ʾ�е�ʱ��
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
With FraTiShi '��ʾ�ؼ�
     '.Top = PicQiPang.Top
     .Left = 0
     .Caption = ""
End With
With TiShiQZ '��ʾ�е�����
     .Width = 2 * qR
     .Height = .Width
     .Left = (FraTiShi.Width - .Width) / 2
     LabTiShi.Top = .Top + .Height + 100
     LabTiShi.Left = (FraTiShi.Width - LabTiShi.Width) / 2
End With
'3.���ø��̹���
bFuPang = False '���̱�־
lFuPang = 0 '���̲���
With Fraredo '���̹���
     .Caption = ""
End With
Set_Fupang_eTool '���ø��̹���
'��������ͨѶ����
If s��սģʽ = " �����ս " Then
   SetNetPara , ���˵��е������ս����
Else
   SetNetPara False, ���˵��е������ս����
End If

'4.���������ϵ�������ʾ��
With ShpTSD '��ʾ��
     .Visible = False
     .Width = sD
     .Height = sD
End With
With ShpTSW
     .Visible = False
     .Width = sD
     .Height = sD
End With
With ShpCur '���
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
fNoQi '��ʼ�������Ƴ����ռ�����
End Sub

'�����Ƴ����ռ�����
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
        PicNoQi.Print s����ʱ��Ҫ����
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

'���ø��̹���,���Ǹ���ʱ��ʾ���̹���,
'����,��Ϊ��սʱ��ʾ���繤��
Private Sub Set_Fupang_eTool()
'���̹��ߵ�λ��
Fraredo.Top = PicQiPang.Top + PicQiPang.Height / 2 - Fraredo.Height / 2
Fraredo.Left = 0
If bFuPang Then '���̹���
   CmdPre.Caption = "��һ��(&P)"
   CmdNext.Caption = "��һ��(&N)"
   CmdCanel.Caption = "ȡ��"
   Fraredo.Visible = True
ElseIf mnuFileNet.Checked Then '���繤��
   CmdPre.Caption = "����(&S)"
   CmdNext.Caption = "���(&P)"
   CmdCanel.Caption = "ȡ��"
   Fraredo.Visible = True
Else
   Fraredo.Visible = False
End If
End Sub

Private Sub cmdCanel_Click() '�����е�ȡ��
Dim exi As Integer
If bFuPang Then
      exi = MsgBox(s���ٸ��̶��Ǽ�����, vbYesNo + vbQuestion)
      If exi = vbYes Then
         bFuPang = False
         Set_Fupang_eTool
         ReDim Preserve QJ(lFuPang)
      Else
         Exit Sub
      End If
Else ''�����繤��ʱ

End If
End Sub

Private Sub cmdNext_Click() '�����е���һ��
If Run Then On Error Resume Next
Dim X As Single, Y As Single, QiZhi As Enum_QiZhi
Dim Obj As Object

If bFuPang Then
   If lFuPang < UBound(QJ) Then
      RecordQJ X, Y, QiZhi, �Ӽ�¼������ȡ��
      If Walk(X, Y) Then '��ȥ�����ӵ�
         ReDim Preserve QJ(UBound(QJ) - 1)
      End If
   Else
      If Not bFuPangEnd Then
         MsgBox s���̽���
         bFuPangEnd = True
      End If
   End If
ElseIf mnuFileNet.Checked Then '�����繤��ʱ

End If
End Sub

Private Sub cmdPre_Click() '�����е���һ��
Dim X As Single, Y As Single, QiZhi As Enum_QiZhi
Dim XX As Single, YY As Single, Obj As Object
If bFuPang Then
   If lFuPang < 1 Then
      Beep
   Else
      bFuPangEnd = False
      lFuPang = lFuPang - 1
      Select Case qStep
             Case Enum_qStep.����׷�, Enum_qStep.�����ҷ�
                  'ȡ�������Ӻ�λ��
                  RecordQJ X, Y, QiZhi, �Ӽ�¼������ȡ��
                  'XX = X: YY = Y
                  'ȡ������λ���ϵ��Ӻ�λ��,
                  With qDefine '�ָ��ݴ�ṹ
                       RecordQJ .X, .Y, .QiZhi, �Ӽ�¼������ȡ��, lFuPang - 1
                       '�ָ�����λ���ϵ���
                       QiJu_eArrary .X, .Y, QiJu_eArrary(X, Y, , , Obj), �����鸳ֵ, Obj
                       SetPos .X, .Y, Obj
                       XX = .X: YY = .Y
                       Set .oQiZhi = Obj
                  End With
                  '�ָ����ӳ���
                  Make_QiZhi X, Y, QiZhi
                  With ShpTSD '�����ϵ���ʾ��
                       .Left = XX - .Width / 2
                       .Top = YY - .Height / 2
                       .Visible = True
                  End With
                  With ShpTSW
                       .Left = X - .Width / 2
                       .Top = Y - .Height / 2
                       .Visible = True
                  End With
                  If qStep = ����׷� Then
                     qStep = �ҷ���
                  Else
                     qStep = �׷���
                  End If
             Case Enum_qStep.�׷���, Enum_qStep.�ҷ���
                  RecordQJ X, Y, , �Ӽ�¼������ȡ��
                  With qDefine
                       RecordQJ .X, .Y, .QiZhi, �Ӽ�¼������ȡ��, lFuPang
                  End With
                  With ShpTSD '�����ϵ���ʾ��
                       .Left = X - .Width / 2
                       .Top = Y - .Height / 2
                       .Visible = True
                  End With
                  ShpTSW.Visible = False
                  If qStep = �׷��� Then
                     qStep = ����׷�
                  Else
                     qStep = �����ҷ�
                  End If
      End Select
      lFuPang = lFuPang - 1
      Tishi
   End If
ElseIf mnuFileNet.Checked Then '�����繤��ʱ

End If
End Sub

Private Sub Form_Load()
PicQiPang.AutoRedraw = True
Me.ScaleMode = vbTwips
PicQiPang.ScaleMode = Me.ScaleMode
Me.Width = Screen.Width
Me.Height = Screen.Height

'��ʼ���������йصĲ���
With txtNetTalk
     .Locked = True
     .Visible = False
     .Text = ""
End With
With txtNetInput
     .Text = ""
     .Visible = False
End With

'����һЩ���ڵ��ļ�����
With tFileHand
     .App_BiaoZhi = "�й�����"  'Ӧ�ó����ʶ
     .App_BiaoZhi_ID = 19760121  'Ӧ�ó����ʶIDֵ
     .MyPassWord = 19780201
     .Major = App.Major
     .Minor = App.Minor
End With

'������ʾ�ؼ��ĸ�
FraTiShi.Height = FraTiShi.Height - FraTime.Height

IniFile = App.Path + "\��������.ini"

ChangeIniFile ȡ����ս��ʽ
ChangeIniFile ȡ�����Ӳ���
ChangeIniFile ȡ��������ʽ
ChangeIniFile ȡ���Զ����̵�ʱ��
ChangeIniFile ȡ�����ڱ���
ChangeIniFile ȡ�����ؼ�¼��ɫ
ChangeIniFile ȡ��Զ�˼�¼��ɫ
ChangeIniFile ȡ��Զ��������¼��ɫ

Initally  '���г�ʼ��

ChangeIniFile ȡ���˵�����ʾʱ���״̬
ChangeIniFile ȡ���˵�����ʾ״̬����״̬
ChangeIniFile д��˵�����ʾ�Ի����״̬

End Sub

'���ϵ�Ϊ��ʼ������
'===============================================================

Private Sub Form_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = vbRightButton Then
   PopupMenu mnuFile '��ݲ˵�
End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
Dim exi  As Integer
If bXiaoQi Then
   exi = MsgBox(s�����ļ�, vbQuestion + vbYesNoCancel)
   If exi = vbYes Then
      With CMD
          .FileName = ""
          .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + cdlOFNExtensionDifferent
          .Filter = "*.xq|*.xq|*.*|*.*"
          .DialogTitle = "����Ϊ"
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

'�����Ϊ�˵�
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
        Me.Caption = s�й����� & "-" & s��սģʽ & "-" & s����
        For Each Ctr In QZ
            Ctr.DragMode = vbAutomatic
        Next Ctr
     Else
        If tFileHand.bBuJu Then 'tFileHand.bBuJu��PicQiPang_DragDrop�ж���
           exi = MsgBox(s�������߷� + Chr(13) + s�������߷�1, vbQuestion + vbYesNo)
           If exi = vbYes Then
              qStep = ����׷�
              tFileHand.SheiZhou = qStep
           Else
              qStep = �����ҷ�
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
        Me.Caption = s�й����� & "-" & s��սģʽ
     End If
End With
Call fNoQi
End Sub

Private Sub mnuFileExit_Click() '�˳�
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

'�޸Ķ�սģʽ
Private Function Modify_DuaiZhang_eMode(Mode As String) As Boolean
If MsgBox(s�޸Ķ�սģʽ, vbQuestion + vbYesNo) = vbYes Then
   ZouQiPangShu = 0
   If mnuFileManAndMachine.Checked Then mnuFileManAndMachine.Checked = False
   If mnuFileManAndMan.Checked Then mnuFileManAndMan.Checked = False: ShpCur.Visible = False
   If mnuFileNet.Checked Then mnuFileNet.Checked = False
   '���������˳���ܵ���
   s��սģʽ = Mode
   mnuFileReStart_Click
   Modify_DuaiZhang_eMode = True
Else
   Modify_DuaiZhang_eMode = False
End If
End Function

'�˻���ս
Private Sub mnuFileManAndMachine_Click()
With mnuFileManAndMachine
    If Not .Checked Then
       If Modify_DuaiZhang_eMode(" �˻���ս ") Then
         .Checked = Not .Checked
         ChangeIniFile д���ս��ʽ֮�˻���ս
         If MsgBox(s�˻���սѡ�����߷�, vbQuestion + vbYesNo) = vbYes Then
            '��������
            qStep = ����׷�
            jF.Name = "����"
            MachineWalk
         Else
            '������
            qStep = �����ҷ�
         End If
         Call Tishi
       End If
    End If
End With
End Sub

'���˶�ս
Private Sub mnuFileManAndMan_Click()
With mnuFileManAndMan
    If Not .Checked Then
      If Modify_DuaiZhang_eMode(" ���˶�ս ") Then
         .Checked = Not .Checked
         ChangeIniFile д���ս��ʽ֮���˶�ս
         If MsgBox(s���˶�ս˭����, vbQuestion + vbYesNo) = vbYes Then
            qStep = ����׷�
         Else
            qStep = �����ҷ�
         End If
         ShpCur.Visible = True
         Call Tishi
      End If
    End If
End With
End Sub

'�����ս
'�������繤�ߵ������� Modify_DuaiZhang_eMode(" �����ս ") �����
Private Sub mnuFileNet_Click()
With mnuFileNet
  If Not .Checked Then
     If Modify_DuaiZhang_eMode(" �����ս ") Then
       .Checked = Not .Checked
        ChangeIniFile д���ս��ʽ֮�����ս
        Set_Fupang_eTool
     End If
  End If
End With
End Sub

'����
Private Sub mnuFileOpen_Click()
If bXiaoQi Then
   mnuFileReStart_Click
End If
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames
     .DialogTitle = "��"
     .Filter = "�й������ļ�(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
     .ShowOpen
     If .FileName <> "" Then
        Initally '��ʼ������
        If OpenFile(.FileName) Then
           With tTime '����ʱ��
                .TotalWalkTime = 0
                .jTotalWalkTime = 0
                .yTotalWalkTime = 0
           End With
           If tFileHand.bBuJu Then '���ָ���
              BuJuFuPang
           End If
           bFuPang = True '���ø��̱�־
           Set_Fupang_eTool ' ���ø��̹���
           Me.Caption = s�й����� & "-" & s���� & "-" & " [" & .FileName & "]"
        End If
     End If
End With
End Sub

'������
Private Sub mnuFileContine_Click()
If bXiaoQi Then
   mnuFileReStart_Click
End If
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames
     .DialogTitle = "����һ����"
     .Filter = "�й������ļ�(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
     .ShowOpen
     If .FileName <> "" Then
        Initally
        If OpenFile(.FileName) Then
           Me.Caption = s�й����� & "-" & s��սģʽ & "-" & s������ & "- {" & .FileName & "}"
           bFuPang = True
           If tFileHand.bBuJu Then '���ָ���
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

'���¿�ʼ
Public Sub mnuFileReStart_Click()
Dim exi  As Integer
If bXiaoQi Then
   exi = MsgBox(s�����ļ�, vbQuestion + vbYesNoCancel)
   If exi = vbYes Then
      With CMD
          .FileName = ""
          .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + cdlOFNExtensionDifferent
          .Filter = "�й�����(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
          .DialogTitle = "����Ϊ"
          .ShowSave
           If .FileName <> "" Then
              SaveFile .FileName
           End If
      End With
   ElseIf exi = vbCancel Then
      Exit Sub
   End If
End If
Call Initally '��ʼ��
End Sub

'�����ļ�
Private Sub mnuFileSave_Click()
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNExtensionDifferent
     .Filter = "�й������ļ�(*.xq;*.xqt)|*.xq;*.xqt|*.*|*.*"
     .DialogTitle = "����"
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
Form2.WindowsCommand ���Ʒ�������, iQiJu
End Sub

'����Ի���¼
Private Sub mnuOptionNetClearTalkRecord_Click()
txtNetTalk.Text = ""
End Sub

Private Sub mnuOptionNetOpenTalkRecord_Click()
'�򿪶Ի���¼
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNExtensionDifferent
     .Filter = "�Ի���¼�ļ�(*.tal)|*.tal|*.*|*.*"
     .DialogTitle = "�򿪶Ի���¼"
     .ShowOpen
     If .FileName <> "" Then
        If Len(txtNetTalk.Text) Then
           If MsgBox(s�Ǳ������еļ�¼, vbQuestion + vbYesNo) = vbYes Then
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
'����Ի���¼
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNExtensionDifferent
     .Filter = "�Ի���¼�ļ�(*.tal)|*.tal|*.*|*.*"
     .DialogTitle = "����Ի���¼"
     .ShowSave
     If .FileName <> "" Then
        txtNetTalk.SaveFile .FileName
     End If
End With
End Sub

'���ñ��ؼ�¼��ɫ
Private Sub mnuOptionNetTalkLocalColor_Click()
With CMD
     .DialogTitle = "ѡ�񱾵ؼ�¼��ɫ"
     .Flags = mscomdlg.ColorConstants.cdlCCRGBInit
     .Color = tNet.NetTalkTextColorLocal
     .ShowColor
     tNet.NetTalkTextColorLocal = .Color
    ChangeIniFile д�뱾�ؼ�¼��ɫ, , .Color
    Call ChangeRichTextColor
End With
End Sub

'����Զ�ؼ�¼��ɫ
Private Sub mnuOptionNetTextTalkRemoteColor_Click()
With CMD
     .DialogTitle = "ѡ��Զ�ؼ�¼��ɫ"
     .Flags = mscomdlg.ColorConstants.cdlCCRGBInit
     .Color = tNet.NetTalkTextColorRemote
     .ShowColor
     tNet.NetTalkTextColorRemote = .Color
    ChangeIniFile д��Զ�˼�¼��ɫ, , .Color
    Call ChangeRichTextColor
End With
End Sub

Private Sub mnuOptionNetTextTalkRemoteOrtherColor_Click()
With CMD
     .DialogTitle = "ѡ��Զ��������¼��ɫ"
     .Flags = mscomdlg.ColorConstants.cdlCCRGBInit
     .Color = tNet.NetTalkTextColorRemoteOrther
     .ShowColor
     tNet.NetTalkTextColorRemoteOrther = .Color
     ChangeIniFile д��Զ��������¼��ɫ, , .Color
     Call ChangeRichTextColor
End With
End Sub

Private Sub mnuOptionSavePassWord_Click()
PassWord ���ñ�������
End Sub

'�����Զ�����
Private Sub mnuOptionSetAutoFuPang_Click()
Dim S As String
S = InputBox(s�Զ�������ʾ + Chr(13) + s�Զ�������ʾ1 + Chr(13) + s�Զ�������ʾ2, , CStr(nAutoFuPangTime))
If S <> "" Then
   nAutoFuPangTime = CDate(S)
   ChangeIniFile д���Զ����̵�ʱ��, S
End If
End Sub

'�������Ӳ���
Private Sub mnuOptionSetQiZhiChaiLiao_Click()
On Error Resume Next
Dim exi As Long, Ctr As Image
exi = MsgBox(s�������ӵĲ���˵�� + Chr(13) + s�������ӵĲ���˵��1 + Chr(13) + s�������ӵĲ���˵��2, vbQuestion + vbYesNoCancel)
If exi = vbYes Then
      With CMD
          .FileName = ""
          .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNExtensionDifferent
          .Filter = "���Ӳ����ļ�(*.ico)|*.ico"
          .DialogTitle = "�����Ӳ����ļ�"
          .ShowSave
           If .FileName <> "" Then
              ImgList.ListImages.Add , "add", LoadPicture(.FileName)
              If Err.Number = 35602 Then
                 ImgList.ListImages.Remove ("add")
                 ImgList.ListImages.Add , "add", LoadPicture(.FileName)
              ElseIf Err.Number Then
                 GoTo mnuOptionSetQiZiChaiLiaoError
              End If
              ChangeIniFile д��������Ӳ���, .FileName
           End If
      End With
ElseIf exi = vbNo Then
      ImgList.ListImages.Remove ("add")
      ChangeIniFile д�����Ӳ�����ϵͳ���õ�
ElseIf exi = vbCancel Then
    Exit Sub
End If
'��������
For Each Ctr In QZ
    Set Ctr.Picture = Draw_QiZhi(Ctr.Tag)
Next Ctr
Exit Sub
mnuOptionSetQiZiChaiLiaoError:
If Not Err.Number = 35601 Then
   MsgBox s�����Ӳ����ļ�����
End If
End Sub

Private Sub mnuOptionShowTalk_Click()
With mnuOptionShowTalk
     .Checked = Not .Checked
     SetNetPara .Checked
     ChangeIniFile д��˵�����ʾ�Ի����״̬, .Checked
End With
End Sub

'���ô��ڱ���
Private Sub mnuOptionWindowBack_Click()
On Error GoTo mnuOptionWindowBackError
With CMD
     .FileName = ""
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNExtensionDifferent
     .Filter = "���Ӳ����ļ�(*.bmp;*.jpg)|*.ico;*.jpg"
     .DialogTitle = "�򿪴��ڱ���..."
     .ShowOpen
     If .FileName <> "" Then Me.Picture = LoadPicture(.FileName)
     ChangeIniFile д�봰�ڱ���, .FileName
End With
Exit Sub
mnuOptionWindowBackError:
MsgBox s���ļ�����
End Sub

'����������ʽ
Private Sub mnuOptionQiPangStyle_Click()
With CMD
     .DialogTitle = "����������ʽ..."
     .FileName = ""
     .Filter = "������ʽ�ļ�(*.bmp;*.ico;*.cur)|*.bmp;*.ico;*.cur|*.*|*.*"
     .Flags = cdlOFNHideReadOnly + cdlOFNLongNames + cdlOFNCreatePrompt + cdlOFNExtensionDifferent
     .ShowOpen
     If .FileName <> "" Then
        LoadQiPangStyle .FileName
        ChangeIniFile д��������ʽ, .FileName
     End If
End With
End Sub


'��ʾʱ��
Private Sub mnuOPtionShowTime_Click()
If Run Then On Error Resume Next
With mnuOptionShowTime
     .Checked = Not .Checked
     FraTime.Visible = .Checked
     Call ChangeIniFile(д��˵�����ʾʱ���״̬, .Checked)
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

'����״̬��
Private Sub mnuOptionStateBar_Click()
With mnuOptionStateBar
     .Checked = Not .Checked
     StatBar.Visible = .Checked
     Call ChangeIniFile(д��˵�����ʾ״̬����״̬, .Checked)
     Call ReSetPostion(.Checked, StatBar.Height)
End With
End Sub

'���ļ���װ��������ʽͼƬ
Private Sub LoadQiPangStyle(FileName As String)
If Run Then On Error Resume Next
Dim Pic As StdPicture
        Set Pic = LoadPicture(FileName)
        PicQiPang.Cls
        PicQiPang.PaintPicture Pic, 0, 0 _
                    , PicQiPang.Width, PicQiPang.Height
        Draw_QiPang
        '���ļ��������������
        sQiPangStyleFileName = FileName
End Sub

'===========================================================================================
'���µ�Ϊ����
'-------------------------------------------------------------------------------------------
'�˻���սʱ��������
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
'1.������Ϊ�׷�ʱ
If qStep = ����׷� Then
   '���������
   'XinShiFenXi iQiJu, Enum_QZ.jFan
   qStep = �����ҷ�
   Screen.MousePointer = vbDefault
   Exit Function
End If
'2.������Ϊ�ҷ�ʱ
If qStep = �����ҷ� Then
   '���������
   'XinShiFenXi iQiJu, Enum_QZ.yFan
   qStep = ����׷�
End If
Screen.MousePointer = vbDefault
End Function

'����
Public Function Walk(X As Single, Y As Single, Optional Object As Object = Nothing) As Boolean
'���ӷ�Ϊ�Ĳ�:
'qStep=1Ϊ����׷�,2Ϊ�׷�����,3Ϊ�����ҷ���4Ϊ�ҷ�����
'ֻ�е��ɹ�ʱqStep��������
'�ж��Ƿ������ӻ�����
Dim Obj As Object
ReSetXY X, Y '����������
If bPangDuangShiFoLengZhougZhi(X, Y, Object) Then '�����ӻ�����
   RecordQJ X, Y '�ѵ�ǰλ�õ���ִ洢����¼������
   Walk = True
   Select Case qStep
          Case Enum_qStep.����׷�, Enum_qStep.�����ҷ�
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
               If qStep = ����׷� Then
                  qStep = �׷���
               Else
                  qStep = �ҷ���
               End If
          Case Enum_qStep.�׷���, Enum_qStep.�ҷ���
               If Not (Object Is Nothing) Then '���ԭλ��������Ե�
                  Unload Object
               Else
                  QiJu_eArrary X, Y, , , Obj
                  If Not (Obj Is Nothing) Then
                     Unload Obj
                  End If
               End If
               '��������
               SetPos X, Y, qDefine.oQiZhi
               QiJu_eArrary X, Y, QiJu_eArrary(qDefine.X, qDefine.Y, , , Obj), �����鸳ֵ, Obj
               QiJu_eArrary qDefine.X, qDefine.Y, NoZhi, �����鸳ֵ
               With ShpTSW
                    .Top = Y - .Height / 2
                    .Left = X - .Width / 2
                    .Visible = True
               End With
               If qStep = �׷��� Then
                  qStep = �����ҷ�
               Else
                  qStep = ����׷�
               End If
               '�˻���սʱ��������
               If mnuFileManAndMachine.Checked Then
                  MachineWalk
               End If
   End Select
   If bJiaoJian Then '��ʾ�н�
      bJiaoJian = False
      MsgBox s�н�, vbInformation
   End If
   If Not bFuPang Then bXiaoQi = True '�������ʶ
   Tishi X, Y, Object
   If Not Run Then fNoQi
Else '�������ӻ�����
   Walk = False
   Beep
   '�˻���սʱ��������
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

'�ж��Ƿ������ӻ�����
Private Function bPangDuangShiFoLengZhougZhi(X As Single, Y As Single, Object As Object) As Boolean
Dim Obj As Object
'�����������������
If X < sX - qR Or Y < sY - qR Or X > sX + qR + 8 * sD _
   Or Y > sY + qR + 9 * sD Then
   bPangDuangShiFoLengZhougZhi = False
   Exit Function
End If
Select Case qStep
       Case Enum_qStep.����׷�
            If QiJu_eArrary(X, Y, , , Obj) > 0 And (Not Obj Is Nothing) Then '
               bPangDuangShiFoLengZhougZhi = True
            Else
               bPangDuangShiFoLengZhougZhi = False
            End If
       Case Enum_qStep.�׷���
            '�жϵ�ǰ���Ƿ�����
            '�����,���Ǳ�������ʱ,�ض�������,����False
            '���򣬼���Ƿ����㶨�����ӵ��߷���
            If QiJu_eArrary(X, Y, , , Obj) > 0 Then
               If Not Obj Is Nothing Then '�ض�������
                  RecordQJ X, Y, , �����¼�����е�Posλ��
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
       Case Enum_qStep.�����ҷ�
            If QiJu_eArrary(X, Y, , , Obj) < 0 And (Not Obj Is Nothing) Then '
               bPangDuangShiFoLengZhougZhi = True
            Else
               bPangDuangShiFoLengZhougZhi = False
            End If
       Case Enum_qStep.�ҷ���
            '�жϵ�ǰ���Ƿ�����
            '�����,���Ǳ�������ʱ,���¶�������,����False
            '���򣬼���Ƿ����㶨�����ӵ��߷���
            If QiJu_eArrary(X, Y, , , Obj) < 0 Then
               If Not Obj Is Nothing Then '���¶�������
                  RecordQJ X, Y, , �����¼�����е�Posλ��
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
'���������ӵ��߷�
Private Function bQiZhiWalk(X As Single, Y As Single) As Boolean
'1.�����һ�ߵ���,ǰһ�������Ѿ�������
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

'2.�ж��ܷ���
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
   '�жϽ�����
   bQiZhiWalk = Not bShuaiDuaiMei(Di, Dj, I, j, iQiJu)
End If
'ע��λ�ò��ܶ�λ��
bQizhiWalkLoop:
If bQiZhiWalk Then
   '�ж��Ƿ񽫾�,�����н��뱻��.
   '�н�����Enum_Walk_Val.�н�(��ֵ)
   '��������Enum_Walk_Val.����(��ֵ)
   bQiZhiWalk = JianJun(Di, Dj, I, j, iQiJu)
End If

End Function

'��ʾ
Private Sub Tishi(Optional X As Single = 0, Optional Y As Single = 0, Optional Object As Object = Nothing)
On Error Resume Next
Select Case qStep
       Case Enum_qStep.����׷�
            TiShiQZ.Visible = False
            TiShiQZ.Stretch = True
            FraTiShi.Top = PicQiPang.Top
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height / 2
            If jF.Name <> "" Then
               LabTiShi.Caption = jF.Name + "ȷ������"
            Else
               LabTiShi.Caption = jF.sName + "ȷ������"
            End If
            With tTime
                 .yTotalWalkTime = .yTotalWalkTime + CDate(TxtHadTime.Text)
                 .TotalWalkTime = .jTotalWalkTime
                 .OneStartTime = Time
            End With
       Case Enum_qStep.�׷���
            TiShiQZ.Stretch = True
            Set TiShiQZ = qDefine.oQiZhi
            TiShiQZ.Visible = True
            FraTiShi.Top = PicQiPang.Top
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height
            If jF.Name <> "" Then
               LabTiShi.Caption = jF.Name + "��"
            Else
               LabTiShi.Caption = jF.sName + "��"
            End If
            If Not Object Is Nothing Then
               
            End If
       Case Enum_qStep.�����ҷ�
            TiShiQZ.Visible = False
            FraTiShi.Top = PicQiPang.Top + PicQiPang.Height - FraTiShi.Height
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height / 2
            If yF.Name <> "" Then
               LabTiShi.Caption = yF.Name + "ȷ������"
            Else
               LabTiShi.Caption = yF.sName + "ȷ������"
            End If
            With tTime
                 .jTotalWalkTime = .jTotalWalkTime + CDate(TxtHadTime.Text)
                 .TotalWalkTime = .yTotalWalkTime
                 .OneStartTime = Time
            End With
       Case Enum_qStep.�ҷ���
            TiShiQZ.Stretch = True
            Set TiShiQZ = qDefine.oQiZhi
            TiShiQZ.Visible = True
            FraTiShi.Top = PicQiPang.Top + PicQiPang.Height - FraTiShi.Height
            LabTiShi.Top = TiShiQZ.Top + TiShiQZ.Height
            If yF.Name <> "" Then
               LabTiShi.Caption = yF.Name + "��"
            Else
               LabTiShi.Caption = yF.sName + "��"
            End If
            If Not Object Is Nothing Then
               
            End If
End Select
LabTiShi.Left = (FraTiShi.Width - LabTiShi.Width) / 2
End Sub

'��¼����
Private Sub RecordQJ(Optional X As Single = 0, Optional Y As Single = 0, Optional QiZhi As Enum_QiZhi = Enum_QiZhi.NoZhi, Optional Flag As Enum_RecordQj_Flag = �����¼����, Optional Pos As Long = 0)
Dim I As Integer, j As Integer, K As Single, L As Integer
K = Pos
ZhouBiao_eTranslate X, Y, I, j
Select Case Flag
       Case �����¼����
            ReDim Preserve QJ(UBound(QJ) + 1)
            L = QiJu_eArrary(X, Y) 'Ҫ���������
            'If L <> 0 Then
               QJ(UBound(QJ)) = QiJuBianMa(I, j, L) 'Sgn(k) * (J + I * 100 + Abs(k * 1000))
            'Else
            '   QJ(UBound(QJ)) = J + I * 100
            'End If
       Case �����¼�����е�Posλ��
            If Pos = 0 Then Pos = UBound(QJ)
            L = QiJu_eArrary(X, Y)
            'If L <> 0 Then
               QJ(Pos) = QiJuBianMa(I, j, L) ' Sgn(k) * (J + I * 100 + Abs(k * 1000))
            'Else
            '   QJ(UBound(QJ)) = J + I * 100
            'End If
       Case �Ӽ�¼������ȡ��
            If K = 0 Then
               If lFuPang < UBound(QJ) And lFuPang >= 0 Then
                  lFuPang = lFuPang + 1
                  QiZhi = QiJuBianMa(I, j, QJ(lFuPang), ���н���)
               Else
                  lFuPang = UBound(QJ) '��ָ��ָ����������
                  Beep
               End If
            Else
               QiZhi = QiJuBianMa(I, j, QJ(K), ���н���)
            End If
            ZhouBiao_eTranslate X, Y, I, j, ���������ת��Ϊ�����ϵ�����
End Select
End Sub

'����Ϊ���ӵ��߷�
'--------------------------------------
'����Ϊ����
'=============================================================================================
'����Ϊ�ļ�����
Private Sub SaveFile(FileName As String, Optional Flag As Enum_File_Flag = Enum_File_Flag.���ܸ�ʽ)
If Run Then On Error Resume Next
If Dir(FileName) <> "" Then
   Kill FileName
End If
If UCase$(Right$(FileName, 4)) = UCase$(".xqt") Then
   Flag = �ı���ʽ
Else
   Flag = ���ܸ�ʽ
End If
Select Case Flag
       Case Enum_File_Flag.���ܸ�ʽ
            If tFileHand.bBuJu Then
               Call SaveFileAdd_MiDiBuJu(FileName)
            Else
               Call SaveFileAdd_Mi(FileName)
            End If
       Case Enum_File_Flag.�ı���ʽ
            If bFileAdd_Mi Then
               If Not PassWord(���ļ��Ӽ��ܸ�ʽת��Ϊ�ı���ʽ) Then
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

'���沼���ļ�
Private Sub SaveFileAdd_MiDiBuJu(FileName As String)
Dim Num As Integer, I As Long, j As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "�й�����"
     .CompanyName = "���ֹ�����"
     .Disger = "����"
     .FileType = Enum_File_Flag.���ּ��ܸ�ʽ
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
'����ʱ��
'ʱ��(Date)�ĳ���Ϊ8�ֽ�
'����(Integer)�ĳ���Ϊ2�ֽ�
'������(Long)�ĳ���Ϊ4�ֽ�
'������(Single)�ĳ���Ϊ4�ֽ�
'˫����(Double)�ĳ���Ϊ8�ֽ�
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
Put #Num, Len(tFh) + 24 + 1, QJ(0) '�����ļ�ָ��
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
If Not Run Then MsgBox Err.Description  's�����ļ�����
End Sub

'���ܸ�ʽ�ļ�
Private Sub SaveFileAdd_Mi(FileName As String)
Dim Num As Integer, I As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "�й�����"
     .CompanyName = "���ֹ�����"
     .Disger = "����"
     .FileType = ���ܸ�ʽ
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
'����ʱ��
'ʱ��(Date)�ĳ���Ϊ8�ֽ�
'����(Integer)�ĳ���Ϊ2�ֽ�
'������(Long)�ĳ���Ϊ4�ֽ�
'������(Single)�ĳ���Ϊ4�ֽ�
'˫����(Double)�ĳ���Ϊ8�ֽ�
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
Put #Num, Len(tFh) + 24 + 1, QJ(0) '�����ļ�ָ��
For I = 1 To UBound(QJ)
    Put #Num, , QJ(I)
Next I
Close #Num
Exit Sub
SaveFileError:
If Not Run Then MsgBox Err.Description  's�����ļ�����

End Sub

'���ֵ��ı���ʽ�ļ�
Private Sub SaveFileText_BuJu(FileName As String)
On Error GoTo SaveFileError
Dim Num As Integer, I As Long, j As Integer
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "�й�����"
     .CompanyName = "���ֹ�����"
     .Disger = "����"
     .FileType = Enum_File_Flag.�����ı���ʽ
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
Print #Num, '�˾��ڵ�һ��
With tTime
     Print #Num, TxtTime
     Print #Num, .jTotalWalkTime
     Print #Num, .yTotalWalkTime
End With
'���벼��
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
If Not Run Then MsgBox Err.Description  's�����ļ�����

End Sub

'�ı���ʽ�ļ�
Private Sub SaveFileText(FileName As String)
On Error GoTo SaveFileError
Dim Num As Integer, I As Long
Dim tFh As Type_File_Hand
Num = FreeFile
With tFh
     .AppTitle = "�й�����"
     .CompanyName = "���ֹ�����"
     .Disger = "����"
     .FileType = Enum_File_Flag.�ı���ʽ
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
Print #Num, '�˾��ڵ�һ��
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
If Not Run Then MsgBox Err.Description  's�����ļ�����
End Sub
 
'���ļ�
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
           MsgBox s�ļ��򿪴���
           OpenFile = False
           Close #Num
           Exit Function
        End If
     Else
        MsgBox s�ļ��򿪴���
        OpenFile = False
        Close #Num
        Exit Function
     End If
End With
Close #Num
If (Not tFh.NoPassWordFlag) Or tFh.PassWord Then
   If Not PassWord(�򿪼����ļ�, tFh.PassWord) Then
      OpenFile = False
      Exit Function
   End If
End If
Select Case Flag
       Case Enum_File_Flag.���ܸ�ʽ
            OpenFile = OpenFileAdd_Mi(FileName)
       Case Enum_File_Flag.�ı���ʽ
            OpenFile = OpenFileText(FileName)
       Case Enum_File_Flag.���ּ��ܸ�ʽ
            OpenFile = OpenFileAdd_MiDiBuJu(FileName)
       Case Enum_File_Flag.�����ı���ʽ
            OpenFile = OpenFileText_BuJu(FileName)
End Select
If OpenFile Then '���ƴ��ļ�����ȡ�Ĳ���
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

'�򿪲����ļ�
Private Function OpenFileAdd_MiDiBuJu(FileName As String) As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, I As Long, j As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
Open FileName For Binary As #Num Len = Len(tFh)
Get #Num, , tFh
Close #Num
'ȡ��ʱ��
'ʱ��(Date)�ĳ���Ϊ8�ֽ�
'����(Integer)�ĳ���Ϊ2�ֽ�
'������(Long)�ĳ���Ϊ4�ֽ�
'������(Single)�ĳ���Ϊ4�ֽ�
'˫����(Double)�ĳ���Ϊ8�ֽ�
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
Get #Num, Len(tFh) + 25, QJ(0) '�����ļ�ָ��
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

'�򿪼��ܸ�ʽ�ļ�
Private Function OpenFileAdd_Mi(FileName As String) As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, I As Long
Dim S As String * 8
Dim tFh As Type_File_Hand
Num = FreeFile
Open FileName For Binary As #Num Len = Len(tFh)
Get #Num, , tFh
Close #Num
'ȡ��ʱ��
'ʱ��(Date)�ĳ���Ϊ8�ֽ�
'����(Integer)�ĳ���Ϊ2�ֽ�
'������(Long)�ĳ���Ϊ4�ֽ�
'������(Single)�ĳ���Ϊ4�ֽ�
'˫����(Double)�ĳ���Ϊ8�ֽ�
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
Get #Num, Len(tFh) + 25, QJ(0) '�����ļ�ָ��
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

'�򿪲����ļ�
Private Function OpenFileText_BuJu(FileName As String) As Boolean
If Run Then On Error GoTo OpenFileError
Dim Num As Integer, I As Long, j As Integer
Dim tFh As Type_File_Hand
Dim S As String
Num = FreeFile
Open FileName For Input As #Num
Line Input #Num, S 'ע��ֻ��һ��
           '��ΪSaveFileText�еĺ�һ��Print���Ҳ�ڵ�һ��
With tTime
     Line Input #Num, S
     TxtTime.Text = S
     Line Input #Num, S
    .jTotalWalkTime = CDate(S)
     Line Input #Num, S
    .yTotalWalkTime = CDate(S)
End With
'ȡ������
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
   bFileAdd_Mi = False '��־���ļ����Ǽ����ļ�
End If
Close #Num
Exit Function
OpenFileError:
   OpenFileText_BuJu = False
   Close #Num
   If Not Run Then MsgBox Err.Description
End Function


'���ı���ʽ�ļ�
Private Function OpenFileText(FileName As String) As Boolean
If Run Then On Error GoTo OpenFileError
Dim Num As Integer, I As Long
Dim tFh As Type_File_Hand
Dim S As String
Num = FreeFile
ReDim QJ(0)
I = 0
Open FileName For Input As #Num
Line Input #Num, S 'ע��ֻ��һ��
           '��ΪSaveFileText�еĺ�һ��Print���Ҳ�ڵ�һ��
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
   bFileAdd_Mi = False '��־���ļ����Ǽ����ļ�
End If
Close #Num
Exit Function
OpenFileError:
   OpenFileText = False
   Close #Num
   If Not Run Then MsgBox Err.Description
End Function

'��д�����ļ�
Private Function ChangeIniFile(ChangeFlag As Enum_IniFile, Optional szString As String, Optional AnyPara As Variant)
Dim ss As String * 1024, I As Long
If Run Then On Error Resume Next

Select Case ChangeFlag
       Case Enum_IniFile.ȡ�����Ӳ���
            I = GetPrivateProfileString("���", "���ӵĲ���", "", ss, 1024, IniFile)
            If I Then
               ImgList.ListImages.Add , "add", LoadPicture(LeftB(ss, I))
            End If
       Case Enum_IniFile.д��������Ӳ���
            I = WritePrivateProfileString("���", "���ӵĲ���", szString, IniFile)
       Case Enum_IniFile.д�����Ӳ�����ϵͳ���õ�
            I = WritePrivateProfileString("���", "���ӵĲ���", "", IniFile)
       Case Enum_IniFile.д��������ʽ
            I = WritePrivateProfileString("���", "���̵���ʽ", szString, IniFile)
       Case Enum_IniFile.ȡ��������ʽ
            I = GetPrivateProfileString("���", "���̵���ʽ", "", ss, 1024, IniFile)
            If I Then
               sQiPangStyleFileName = Left$(ss, I)
            End If
       Case Enum_IniFile.д�봰�ڱ���
            I = WritePrivateProfileString("���", "���ڱ���", szString, IniFile)
       Case Enum_IniFile.ȡ�����ڱ���
            I = GetPrivateProfileString("���", "���ڱ���", "", ss, 1024, IniFile)
            If I Then
               Form1.Picture = LoadPicture(Left(ss, I))
            End If
       Case Enum_IniFile.д���Զ����̵�ʱ��
            I = WritePrivateProfileString("����", "�Զ����̵�ʱ��", szString, IniFile)
       Case Enum_IniFile.ȡ���Զ����̵�ʱ��
            I = GetPrivateProfileString("����", "�Զ����̵�ʱ��", "", ss, 1024, IniFile)
            If I Then
               nAutoFuPangTime = CDate(LeftB(ss, I))
            End If
       Case д���ս��ʽ֮�˻���ս
            I = WritePrivateProfileString("����", "��ս��ʽ", "�˻���ս", IniFile)
       Case д���ս��ʽ֮���˶�ս
            I = WritePrivateProfileString("����", "��ս��ʽ", "���˶�ս", IniFile)
       Case д���ս��ʽ֮�����ս
            I = WritePrivateProfileString("����", "��ս��ʽ", "�����ս", IniFile)
       Case Enum_IniFile.ȡ����ս��ʽ
            I = GetPrivateProfileString("����", "��ս��ʽ", "���˶�ս", ss, 1024, IniFile)
            If I Then
               Select Case LeftB((ss), I)
                      Case "���˶�ս"
                           s��սģʽ = " ���˶�ս "
                           mnuFileManAndMan.Checked = True
                      Case "�˻���ս"
                           s��սģʽ = " �˻���ս "
                           mnuFileManAndMachine.Checked = True
                      Case "�����ս"
                           mnuFileNet.Checked = True
                           s��սģʽ = " �����ս "
               End Select
            End If
       Case Enum_IniFile.ȡ���˵�����ʾʱ���״̬
            I = GetPrivateProfileString("�˵�", "��ʾʱ��", "True", ss, 1024, IniFile)
            If I Then
               mnuOptionShowTime.Checked = Not CBool(Left(ss, I))
               mnuOPtionShowTime_Click
            End If
       Case Enum_IniFile.д��˵�����ʾʱ���״̬
            I = WritePrivateProfileString("�˵�", "��ʾʱ��", szString, IniFile)
       Case Enum_IniFile.ȡ���˵�����ʾ״̬����״̬
            I = GetPrivateProfileString("�˵�", "��ʾ״̬��", "True", ss, 1024, IniFile)
            If I Then
               mnuOptionStateBar.Checked = Not CBool(Left(ss, I))
               mnuOptionStateBar_Click
            End If
       Case Enum_IniFile.д��˵�����ʾ״̬����״̬
            I = WritePrivateProfileString("�˵�", "��ʾ״̬��", szString, IniFile)
       Case Enum_IniFile.д��˵�����ʾ�Ի����״̬
            I = WritePrivateProfileString("�˵�", "��ʾ�Ի���", szString, IniFile)
       Case Enum_IniFile.ȡ���˵�����ʾ�Ի����״̬
            I = GetPrivateProfileString("�˵�", "��ʾ�Ի���", "True", ss, 1024, IniFile)
            If I Then
               mnuOptionStateBar.Checked = Not CBool(Left(ss, I))
               mnuOptionShowTalk_Click
            End If
       Case Enum_IniFile.ȡ�����ؼ�¼��ɫ
            I = GetPrivateProfileString("����", "���ؼ�¼��ɫ", vbBlack, ss, 10, IniFile)
            If I Then
               tNet.NetTalkTextColorLocal = Val(Left(ss, I))
            Else
               tNet.NetTalkTextColorLocal = vbBlack
            End If
       Case Enum_IniFile.ȡ��Զ�˼�¼��ɫ
            I = GetPrivateProfileString("����", "Զ�˼�¼��ɫ", vbRed, ss, 10, IniFile)
            If I Then
               tNet.NetTalkTextColorRemote = Val(Left(ss, I))
            Else
               tNet.NetTalkTextColorRemote = vbRed
            End If
       Case Enum_IniFile.д�뱾�ؼ�¼��ɫ
            I = WritePrivateProfileString("����", "���ؼ�¼��ɫ", CStr(AnyPara), IniFile)
       Case Enum_IniFile.д��Զ�˼�¼��ɫ
            I = WritePrivateProfileString("����", "Զ�˼�¼��ɫ", CStr(AnyPara), IniFile)
       Case Enum_IniFile.д��Զ��������¼��ɫ
            I = WritePrivateProfileString("����", "Զ��������¼��ɫ", CStr(AnyPara), IniFile)
       Case Enum_IniFile.ȡ��Զ��������¼��ɫ
            I = GetPrivateProfileString("����", "Զ��������¼��ɫ", vbYellow, ss, 10, IniFile)
            If I Then
               tNet.NetTalkTextColorRemoteOrther = Val(Left(ss, I))
            Else
               tNet.NetTalkTextColorRemoteOrther = vbRed
            End If
       
End Select
End Function

'����Ϊ�ļ�����
'====================================================================
''��Ӧ����
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

'����Ϊ�ؼ�����
'��Ӧ����
Private Sub PicQiPang_KeyUp(KeyCode As Integer, Shift As Integer)
Key_ChuLi KeyCode, Shift
End Sub

Private Sub PicNoQi_DragDrop(Source As Control, X As Single, Y As Single)
Dim XX As Single, YY As Single, Ctr As Image
If mnuFileBuJu.Checked And Not (Source Is Nothing) Then
   With Source
        If Abs(Source.Tag) Mod 10 = Enum_QZ.Shuai Then
           MsgBox s˧�����Ƴ�����, vbCritical
           Exit Sub
        End If
        '���ԭλ�õ���
        QiJu_eArrary .Left, .Top, Enum_QiZhi.NoZhi, �����鸳ֵ
        .Top = Y
        .Left = X
        '��QZ.Tag��ʮλ��1����ʶ�������Ƴ�����
        Source.Tag = Sgn(Source.Tag) * (Abs(Source.Tag) + 10)
        Set Source.Container = PicNoQi '�ı�����
   End With
   fNoQi
   tFileHand.bBuJu = True '�ò��ֱ�ʶ
   If Run Then '����λ��
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
   '�����������������
   If X < sX - qR Or Y < sY - qR Or X > sX + qR + 8 * sD _
      Or Y > sY + qR + 9 * sD Then
      Exit Sub
   End If
   Call ZhouBiao_eTranslate(X, Y, I, j)
   Di = I: Dj = j
   Call ZhouBiao_eTranslate(X, Y, I, j, ���������ת��Ϊ�����ϵ�����)
   '��ǰλ�������Ҵ�λ�÷��������߷�
   If QiJu_eArrary(X, Y) = Enum_QiZhi.NoZhi And _
      bBuJu_eWalk_fa(Di, Dj, Source) Then
      With Source
        If Abs(Source.Tag) \ 10 Mod 10 = 0 Then 'Source.Tag���Make_QiZhi��PicNoQi_DragDrop
           '���������ƶ�,���ԭλ�õ���
           QiJu_eArrary .Left, .Top, Enum_QiZhi.NoZhi, �����鸳ֵ
        Else '�޸�Source.Tag,��ʮλ��0
           Source.Tag = Sgn(Source.Tag) * (Abs(Source.Tag) Mod 10)
           Set Source.Container = PicQiPang '�ı�����
        End If
        SetPos X, Y, Source '�����ƶ����λ��
        '�ƶ����������鸳ֵ
        QiJu_eArrary X, Y, Source.Tag, �����鸳ֵ, Source 'Source.Tag���Make_QiZhi��PicNoQi_DragDrop
        fNoQi
        tFileHand.bBuJu = True '�ò��ֱ�ʶ
        If Run Then '����PicNoqi���Ƴ����ӵ�λ��
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
   If bFuPang And s��սģʽ <> " �����ս " Then
      exi = MsgBox(s���ٸ��̶��Ǽ�����, vbYesNo + vbQuestion)
      If exi = vbYes Then
         bFuPang = False
         Set_Fupang_eTool
         ReDim Preserve QJ(lFuPang)
      Else
         Exit Sub
      End If
   End If
   If s��սģʽ <> " �����ս " Then
       Call Walk(X, Y)
   Else
       If Not tNet.NetRemoteWork Then
          If Walk(X, Y) Then
             Call SendTalkText(��������)
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
   If bFuPang And s��սģʽ <> " �����ս " Then
      exi = MsgBox(s���ٸ��̶��Ǽ�����, vbYesNo + vbQuestion)
      If exi = vbYes Then
         bFuPang = False
         Set_Fupang_eTool
         ReDim Preserve QJ(lFuPang)
      Else
         Exit Sub
      End If
   End If
   If s��սģʽ <> " �����ս " Then
       Walk QZ(Index).Left + qR, qR + QZ(Index).Top, QZ(Index)
   Else
       If Not tNet.NetRemoteWork Then
          If Walk(QZ(Index).Left + qR, qR + QZ(Index).Top, QZ(Index)) Then
             Call SendTalkText(��������)
          End If
       End If
   End If
End If
PicQiPang.SetFocus
End Sub

Private Sub Tim_Timer()
Dim I
'�ܹ�ʱ��
TxtTime.Text = Format(Time - tTime.StartTime, "hh:mm:ss")
'�����ߵ�ʱ��
TxtHadTime.Text = Format(Time - tTime.OneStartTime, "hh:mm:ss")
'���ߵ�ʱ��
TxtTotalTime.Text = Format(tTime.TotalWalkTime + TxtHadTime.Text, "hh:mm:ss")
'�Զ�����
If bFuPang And nAutoFuPangTime > CDate(0) Then
   If TxtHadTime.Text > nAutoFuPangTime Then
      cmdNext_Click
   End If
End If
End Sub

'�������ø��ؼ���λ��
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

'��������
Private Function PassWord(Flag As Enum_PassWord_Flag, Optional Param As Variant) As Boolean
If Run Then
   Select Case Flag
          Case ���ļ��Ӽ��ܸ�ʽת��Ϊ�ı���ʽ
          
          Case Enum_PassWord_Flag.�򿪼����ļ�
          
          Case Enum_PassWord_Flag.���ñ�������
          '��ȷ��tFileHand���Ƿ�Ϊ0
          '��Ϊ0������ǰû������
          '����,��������
          
   End Select
Else
   MsgBox "PassWord"
   PassWord = True
End If
End Function

'���ָ���
Private Sub BuJuFuPang()
Dim Ctr As Image, I As Integer, j As Integer
Dim X As Single, Y As Single
For Each Ctr In QZ
    If Ctr <> QZ(0) Then Unload Ctr
Next Ctr
For I = 1 To 9
    For j = 1 To 10
        With QiJu(I, j) '������
             .iQiJu = Enum_QiZhi.NoZhi
             Set .oObject = Nothing
        End With
        If BuJuQiJu(I, j) <> Enum_QiZhi.NoZhi Then
           ZhouBiao_eTranslate X, Y, I, j, ���������ת��Ϊ�����ϵ�����
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
If Button = vbRightButton And s��սģʽ = " �����ս " Then
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
If Button = vbRightButton And s��սģʽ = " �����ս " Then
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
'����Ϊ���纯��
'-----------------------------------------------------------
'�������繤��
Private Sub SetNetPara(Optional bVisible As Boolean = True, Optional Called As Enum_SetNetPara_Called = Enum_SetNetPara_Called.���������е�Ĭ�ϵ���)
'����Զ������,λ�ò��ܱ䣬ֻ�ܷ�����ǰ��
If Called = �������û�ʱ���� Then
   tNet.NetRemoteWork = bVisible
   '����UDP
   With Winsock1
        .Close
        .Protocol = sckUDPProtocol
        If Run Then
          .RemoteHost = InputBox(s������Է���ַ)
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

'��ʵ InitallyInterface() �е���
If Called = ���˵��е������ս���� Then
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
'������ֵΪ�췽����,��ֵΪ��������

End Function

'���ͶԻ�
'CHR��1����ߵ�Ϊ˵���˵����֣��ұ�Ϊ˵�Ļ���
'������ CHR(13).CHR(10) ����.
Public Function SendTalkText(Optional Sender As _
       Enum_SendTalk = Enum_SendTalk.����Ĭ��ֵ, _
       Optional sString As String, _
       Optional lPara As Long)
Select Case Sender
Case Enum_SendTalk.����Ĭ��ֵ
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

'�ı��û��Ի�����ɫ
'CHR��1����ߵ�Ϊ˵���˵����֣��ұ�Ϊ˵�Ļ���
'������ CHR(13).CHR(10) ����.
Private Function ChangeRichTextColor()
Dim S As String, ss As String
Dim I As Long
With txtNetInput
     S = .Text
     .Text = txtNetTalk.Text
     txtNetTalk.Text = ""
     .Visible = False
     '������ CHR(13).CHR(10) ��Ϊһ�ζԻ��ķָ���
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

'�õ�����������ͬ���ַ� (CHR(13).CHR(10)) ��λ��
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

Private Sub SetUserName(Optional Flag As Enum_SetUserName = Enum_SetUserName.���úڷ��û�����Initally�е���)
Dim S As String
Select Case Flag
       Case Enum_SetUserName.���úڷ��û�����Initally�е���
            If s��սģʽ = " �����ս " Then
               If ZouQiPangShu = 0 Then
                  If yF.Name = "" Then
                     yF.Name = InputBox(s�����뱾���û���, , "�ڷ�")
                     tNet.NetTalkUserNameLocal = yF.Name & ":"
                  End If
                  jF.Name = InputBox(s������Զ���û���, , "�췽")
                  tNet.NetTalkTextNameRemote = jF.Name & ":"
                  LabJF.Caption = jF.sName & ": " & jF.Name
                  LabYF.Caption = yF.sName & ": " & yF.Name
                  If SetFirstWork Then
                     SetNetPara False, �������û�ʱ����
                  Else
                     SetNetPara , �������û�ʱ����
                  End If
               End If
            Else
               SetNetPara False, �������û�ʱ����
               jF.Color = vbRed '�׷�����ɫ
               jF.sName = "�췽"
               jF.Name = ""
               yF.Color = vbBlue '�ҷ�����ɫ
               yF.sName = "�ڷ�"
               yF.Name = ""
               LabJF.Caption = jF.sName
               LabYF.Caption = yF.sName
            End If
            If ZouQiPangShu Mod 2 Then
                  qStep = �����ҷ�
                  ZouQiPangShu = ZouQiPangShu + 1
            Else
                  qStep = ����׷�
                  ZouQiPangShu = ZouQiPangShu + 1
            End If
       Case Enum_SetUserName.�����û���ǩλ��
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
