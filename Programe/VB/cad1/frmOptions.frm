VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmOptions 
   Appearance      =   0  'Flat
   BackColor       =   &H80000004&
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "ѡ��"
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
   StartUpPosition =   2  '��Ļ����
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
         Caption         =   "��ʾÿ����ʾ"
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
         Caption         =   "ѡ������"
         Height          =   1785
         Left            =   600
         TabIndex        =   11
         Top             =   840
         Width           =   2295
         Begin VB.OptionButton Option4 
            Caption         =   "������"
            Height          =   255
            Left            =   360
            TabIndex        =   35
            Top             =   1200
            Width           =   1815
         End
         Begin VB.OptionButton Option3 
            Caption         =   "�������"
            Height          =   375
            Left            =   360
            TabIndex        =   34
            Top             =   720
            Width           =   1455
         End
         Begin VB.OptionButton Option2 
            Caption         =   "��������"
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
         Caption         =   " ��� "
         Height          =   2865
         Left            =   480
         TabIndex        =   10
         Top             =   360
         Width           =   2175
         Begin VB.OptionButton Option1 
            Caption         =   "бʮ����"
            Height          =   255
            Index           =   7
            Left            =   240
            TabIndex        =   31
            Top             =   2040
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "ʮ����"
            Height          =   255
            Index           =   6
            Left            =   240
            TabIndex        =   30
            Top             =   1800
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "б��"
            Height          =   255
            Index           =   5
            Left            =   240
            TabIndex        =   29
            Top             =   1560
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "��б��"
            Height          =   255
            Index           =   4
            Left            =   240
            TabIndex        =   28
            Top             =   1320
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "��ֱֱ��"
            Height          =   255
            Index           =   3
            Left            =   240
            TabIndex        =   27
            Top             =   1080
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "ˮƽֱ��"
            Height          =   255
            Index           =   2
            Left            =   240
            TabIndex        =   26
            Top             =   840
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "�ñ������"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   25
            Top             =   600
            Width           =   1455
         End
         Begin VB.OptionButton Option1 
            Caption         =   "����ɫ���"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   24
            Top             =   360
            Width           =   1455
         End
         Begin VB.Label Label7 
            AutoSize        =   -1  'True
            Caption         =   "��ɫѡ��"
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
         Caption         =   "    ������ļ�ʱʱ,��ʾͼֽѡȡ����"
         Height          =   180
         Left            =   480
         TabIndex        =   46
         Top             =   3240
         Width           =   3735
      End
      Begin VB.CheckBox Check1 
         Caption         =   "    ������ʱ��ʾͼֽѡȡ����"
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
         Caption         =   "ֽ�Ŵ�С"
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
            Text            =   "����(mm)"
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
            Caption         =   "ֽ����ɫѡ��"
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
            Caption         =   "ֽ�Ÿ�ʽ"
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
            Caption         =   "��λ"
            Height          =   180
            Left            =   240
            TabIndex        =   22
            Top             =   1200
            Width           =   360
         End
         Begin VB.Label Label4 
            AutoSize        =   -1  'True
            Caption         =   "���"
            Height          =   180
            Left            =   240
            TabIndex        =   19
            Top             =   840
            Width           =   360
         End
         Begin VB.Label Label3 
            AutoSize        =   -1  'True
            Caption         =   "�߶�"
            Height          =   180
            Left            =   240
            TabIndex        =   18
            Top             =   480
            Width           =   360
         End
      End
      Begin VB.Label ʵ�ʿ�� 
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
         Caption         =   "ʵ�ʿ��"
         Height          =   180
         Left            =   3720
         TabIndex        =   43
         Top             =   2520
         Width           =   720
      End
      Begin VB.Label Label11 
         AutoSize        =   -1  'True
         Caption         =   "ʵ�ʸ߶�"
         Height          =   180
         Left            =   2160
         TabIndex        =   42
         Top             =   2520
         Width           =   720
      End
      Begin VB.Label ʵ�ʸ߶� 
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
         Caption         =   "ֽ���ܱ��ĳߴ�"
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
            Name            =   "����"
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
         Caption         =   "������"
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
         Caption         =   "����ѡ��"
         Height          =   1305
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   2895
         Begin VB.ComboBox ���ο�� 
            Height          =   300
            ItemData        =   "frmOptions.frx":0C4A
            Left            =   1440
            List            =   "frmOptions.frx":0C6C
            TabIndex        =   16
            Text            =   "1"
            Top             =   720
            Width           =   1215
         End
         Begin VB.ComboBox ���� 
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
            Caption         =   "���ο��"
            Height          =   180
            Left            =   240
            TabIndex        =   14
            Top             =   720
            Width           =   720
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "����"
            Height          =   180
            Left            =   240
            TabIndex        =   12
            Top             =   360
            Width           =   360
         End
      End
      Begin VB.Label fone 
         AutoSize        =   -1  'True
         Caption         =   "����ѡ��"
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
         Caption         =   "��ɫѡ��"
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
            Caption         =   "�ʻ�"
            Key             =   "pen"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "ֽ�ŵĴ�С"
            Key             =   "paper"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "�������"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "����"
            Object.ToolTipText     =   "����"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab5 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "����"
            Object.ToolTipText     =   "����"
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
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'ѡ�����

Option Explicit
'�����洢
Private col As ColorConstants         '�ߵ���ɫ
Private style As Integer             '����
Private Dwidth As Integer            '�߿�
Private Type font
        name As String           '������
        Bold As Boolean
        Italic As Boolean
        size As Integer
        Strikethrough As Boolean
        Underline As Boolean
        End Type
Private Ffont As font
Private PaperCol As ColorConstants   'ֽ����ɫ
Private Untl As ScaleModeConstants   '��λ
Private PaperHeight As Integer         'ֽ�ų���
Private PaperWidth As Integer          '....���
Private PaperScaleHeight As Single   '������λ,Ϊ�˱�֤���ŵı���
Private PaperScaleWidth As Single
Private PaperFlag As Boolean    'ͼֽ��С�Ƿ�ı�ı�־
Private Ratio As Double     '������
Private Ratio1 As Single   '�����ߵ�һ�������
Private Ratio2 As Single  '�����ߵڶ��������
Private Fillstyl As Integer  '�������
Private Fillstlyecol As ColorConstants '���ɫ
Private ���� As Integer   '��ѡ�������

Private Sub Check1_Click()
    ' �������´�����ʱ�Ƿ���ʾͼֽѡȡ����
    SaveSetting App.EXEName, "Options", "������ʱ��ʾ", Check1.Value

End Sub

Private Sub Check2_Click()
    ' �������´�����ʱ�Ƿ���ʾͼֽѡȡ����
    SaveSetting App.EXEName, "Options", "�ڵ�����ļ�ʱ��ʾ", Check2.Value
End Sub

Private Sub Check3_Click()
' �������´�����ʱ�Ƿ���ʾ�˴���
    SaveSetting App.EXEName, "Options", "������ʱ��ʾ��ʾ", Check3.Value
    End Sub

Private Sub Form_Load()
    On Error Resume Next
    
    '��������λ��
    tbsOptions.left = 120
    tbsOptions.top = 120
    picOptions(0).top = 480
    picOptions(0).left = 210
    
    '���д���
    Me.Move (Screen.width - Me.width) / 2, (Screen.height - Me.height) / 2
    '����ԭʼ����
    col = user.Commvar.col       '���ε���ɫ
    style = user.Commvar.style   '����
    Dwidth = user.Commvar.width  '�߿�
    With Ffont
             .Bold = Form1.cad.FontBold
             .Italic = Form1.cad.FontItalic
             .name = Form1.cad.FontName
             .size = Form1.cad.FontSize
             .Strikethrough = Form1.cad.FontStrikethru
             .Underline = Form1.cad.FontUnderline
    End With
    
   ' ����ͼֽѡȡ���帴ѡ��
   Dim ShowAtStartup As Long
    ShowAtStartup = GetSetting(App.EXEName, "Options", "������ʱ��ʾ", 1)
    If ShowAtStartup <> 0 Then
       Me.Check1.Value = vbChecked
    End If
   ' ���õ�����ļ�ʱ��ʾ��ѡ��
    ShowAtStartup = GetSetting(App.EXEName, "Options", "�ڵ�����ļ�ʱ��ʾ", 1)
    If ShowAtStartup <> 0 Then
    ' �쿴�ڵ�����ļ�ʱ�Ƿ񽫱���ʾ
       Me.Check2.Value = vbChecked
    End If
    '����ÿ����ʾ��ѡ��
    ShowAtStartup = GetSetting(App.EXEName, "Options", "������ʱ��ʾ��ʾ", 1)
    If ShowAtStartup <> 0 Then
       Me.Check3.Value = vbChecked
    End If
 
    ���ο��.text = user.Commvar.width   '��ʾԭ�����߿�
    ����.text = ����.List(style)       '��ʾԭ��������
    PaperCol = Form1.cad.BackColor  '����ԭ������ɫ
    Untl = user.paper.until    '����ԭ���ĵ�λ
    Select Case Untl              '��ʾԭ���ĵ�λ
           Case vbCentimeters
                untle.text = "����(cm)"
           Case vbMillimeters
                untle.text = "����(mm)"
           Case 0
                untle.text = "�Զ��嵥λ"
    End Select
    PaperHeight = ScaleY(user.paper.height, 3, Untl) '��λת��
    pheight.text = PaperHeight     '��ʾֽԭ���ĸ߿�
    PaperWidth = ScaleX(user.paper.width, 3, Untl) ' ��λת��
    pwidth.text = PaperWidth       '��ʾֽԭ���Ŀ��
    With Form1.cad
         PaperScaleHeight = .ScaleHeight
         PaperScaleWidth = .scalewidth
    End With
    PaperFlag = False     'ͼֽ��С�ĸı��־
    Ratio = user.Ratio '���������
    Text1.text = user.Ratio1  ' �����ߵ�һ�������
    Text2.text = user.Ratio2  '.........��.......
    Ratio1 = user.Ratio1
    Ratio2 = user.Ratio2
    
    ʵ�ʸ߶�.Caption = PaperHeight * Ratio   '��ʾֽ�ŵı�ʾ��С
    ʵ�ʿ��.Caption = PaperWidth * Ratio

    Fillstyl = Form1.cad.FillStyle '����ԭ�����������
    Option1.Item(Fillstyl).Value = True  '��ʾ�������
    Fillstlyecol = Form1.cad.FillColor  '�������ɫ
    
    '��������
    ���� = user.����
    Select Case ����      '��ʾ��������
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
    '���ò���
    user.Commvar.col = col    '������ɫ
    user.Commvar.style = style   '����
    user.Commvar.width = Dwidth  '�߿�
    With Form1.cad.font
         .Bold = Ffont.Bold
         .Italic = Ffont.Italic
         .name = Ffont.name
         .size = Ffont.size
         .Strikethrough = Ffont.Strikethrough
         .Underline = Ffont.Underline
         End With
         
    With Form1.cad
        .BackColor = PaperCol 'ֽ����ɫ
        '.scalemode = Untl     '��λ
        .DrawWidth = Dwidth   ' �߿�
        .DrawStyle = style  '����
         End With
         
    user.Ratio = Ratio '������
    user.Ratio1 = Ratio1  '�����������
    user.Ratio2 = Ratio2
    
    If PaperFlag Then   'ͼֽ�仯����Ӧ�ı�Ŀؼ�
         With Form1.cad   'ͼֽ�Ŀ�Ⱥ͸߶�
         .width = ScaleX(PaperWidth, Untl, 3)  'ֽ�Ŀ��
         .height = ScaleY(PaperHeight, Untl, 3) 'ֽ�ĸ߶�
         .scalemode = Untl   '��λ
         End With
       
        '����Һ����
         user.Scrollbar (Form1.cad.width - Form1.desk.scalewidth) / 2, (Form1.cad.height - Form1.desk.ScaleHeight) / 2
    
         '������ͼ����ʼ����,����ͼ��������,���ڻָ�ԭ������ͼ��
         With user.paper
             .height = Form1.cad.height   '����Ϊ��λ
             .width = Form1.cad.width     '..........
             .top = Form1.cad.top         '.........
             .left = Form1.cad.left       '.........
             .scaleheigt = Form1.cad.ScaleHeight
             .scalewidth = Form1.cad.scalewidth
             .until = Untl       '���õĵ�λ
             .color = col
             .scalemode = Form1.cad.scalemode
         End With
         'With Form1.cad  '���ö�����λ
         '     .ScaleHeight = PaperScaleHeight
         '     .scalewidth = PaperScaleWidth
         'End With
    
    End If
    
    Form1.cad.FillStyle = Fillstyl    '�������
    Form1.cad.FillColor = Fillstlyecol  '�����ɫ
    
    user.���� = ����
    
    draw.redraw
End Sub

Public Sub cmdOK_Click()
    On Error Resume Next
    'MsgBox "��������ô���������ѡ��ҹرնԻ���!"
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
        ���� = 1
End Sub

Private Sub Option3_Click()
        ���� = 2
End Sub

Private Sub Option4_Click()
        ���� = 3
End Sub

Private Sub tbsOptions_Click()
    
    Dim i As Integer
    '��ʾ��ʹѡ��Ŀؼ�����
    '��������ʹ����������
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
    '���� ctrl+tab �����ƶ�����һ��ѡ��
    If Shift = vbCtrlMask And KeyCode = vbKeyTab Then
        i = tbsOptions.SelectedItem.Index
        If i = tbsOptions.Tabs.Count Then
            '�ѵ�������ѡ��,ת�ص�ѡ�� 1
            Set tbsOptions.SelectedItem = tbsOptions.Tabs(1)
        Else
            '����ѡ��
            Set tbsOptions.SelectedItem = tbsOptions.Tabs(i + 1)
        End If
    End If
End Sub

Private Sub fone_Click()
On Error Resume Next
'    Form1.CommonDialog1.Flags = 3
    With Form1.CommonDialog1    '��ʾ��ǰ������
         .FontBold = Ffont.Bold
        ' .FontItalic ffont.Italic
         .FontName = Ffont.name
         .FontSize = Ffont.size
         .FontStrikethru = Ffont.Strikethrough
         .FontUnderline = Ffont.Underline
         End With
    Form1.CommonDialog1.ShowFont
    With Form1.CommonDialog1        '�����帳ֵ
         Ffont.Bold = .FontBold
         Ffont.Italic = .FontItalic
         Ffont.name = .FontName
         Ffont.size = .FontSize
         Ffont.Strikethrough = .FontStrikethru
         Ffont.Underline = .FontUnderline
    End With
End Sub

'���β���
Private Sub color_Click()
 On Error Resume Next
 Form1.CommonDialog1.ShowColor
 col = Form1.CommonDialog1.color
End Sub

Private Sub ����_Click()
  On Error Resume Next
  style = ����.ListIndex
  Form1.cad.DrawStyle = style
End Sub

Private Sub ���ο��_Change()
On Error Resume Next
        If ���ο��.text > 0 Then
           Dwidth = ���ο��.text
           Form1.cad.DrawWidth = Dwidth
        End If
End Sub

Private Sub ���ο��_Click()
On Error Resume Next
   Dwidth = ���ο��.text
   Form1.cad.DrawWidth = Dwidth
End Sub

'ֽ�ŵĲ���
Private Sub papercolor_Click()
        On Error Resume Next
        'ֽ�ŵ���ɫ
        Form1.CommonDialog1.ShowColor
        PaperCol = Form1.CommonDialog1.color
End Sub

Private Sub pheight_Change()  '
        On Error Resume Next
        PaperHeight = pheight.text
        ʵ�ʿ��.Caption = PaperWidth * Ratio
        ʵ�ʸ߶�.Caption = PaperHeight * Ratio
        PaperFlag = True
End Sub

Private Sub pheight_Click()
        On Error Resume Next
        PaperHeight = pheight.text
        ʵ�ʿ��.Caption = PaperWidth * Ratio
        ʵ�ʸ߶�.Caption = PaperHeight * Ratio
        PaperFlag = True
End Sub

Private Sub pwidth_Change()
        On Error Resume Next
        PaperWidth = pwidth.text
        ʵ�ʸ߶�.Caption = PaperHeight * Ratio
        ʵ�ʿ��.Caption = PaperWidth * Ratio
        PaperFlag = True
End Sub

Private Sub pwidth_Click()
        On Error Resume Next
        PaperWidth = pwidth.text
        ʵ�ʿ��.Caption = PaperWidth * Ratio
        ʵ�ʸ߶�.Caption = PaperHeight * Ratio
        PaperFlag = True
End Sub

Private Sub untle_Click()     'ֽ�ŵ�λ
        On Error Resume Next
        Select Case untle.text
               Case "����(mm)"
                    Untl = vbMillimeters
               Case "����(cm)"
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
       ʵ�ʿ��.Caption = PaperWidth * Ratio
       ʵ�ʸ߶�.Caption = PaperHeight * Ratio
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
    ʵ�ʿ��.Caption = PaperWidth * Ratio
    ʵ�ʸ߶�.Caption = PaperHeight * Ratio
    End If
End Sub


