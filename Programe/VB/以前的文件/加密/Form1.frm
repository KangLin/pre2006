VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5235
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   7425
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5235
   ScaleWidth      =   7425
   StartUpPosition =   2  '��Ļ����
   Begin VB.Frame FraJm 
      BorderStyle     =   0  'None
      Height          =   495
      Left            =   3840
      TabIndex        =   22
      Top             =   480
      Width           =   3015
      Begin VB.OptionButton OptFind 
         Caption         =   "��ѯ�ļ�"
         Height          =   495
         Left            =   120
         TabIndex        =   24
         Top             =   0
         Width           =   1215
      End
      Begin VB.OptionButton OptJmFile 
         Caption         =   "�����ļ�"
         Height          =   495
         Left            =   1800
         TabIndex        =   23
         Top             =   0
         Width           =   1335
      End
   End
   Begin VB.ListBox LstDFile 
      Height          =   1680
      Left            =   3720
      MultiSelect     =   2  'Extended
      TabIndex        =   21
      Top             =   1920
      Width           =   3255
   End
   Begin VB.Frame FraAdd 
      Caption         =   "Ŀ���ļ��б�"
      Height          =   1695
      Left            =   3720
      TabIndex        =   13
      Top             =   240
      Width           =   3255
      Begin VB.TextBox TxtFileName 
         Height          =   270
         Left            =   840
         TabIndex        =   18
         Text            =   "Text1"
         Top             =   1320
         Width           =   2295
      End
      Begin VB.CommandButton CmdDBrow 
         Caption         =   "���(&L).."
         Height          =   255
         Left            =   2160
         TabIndex        =   17
         Top             =   1035
         Width           =   975
      End
      Begin VB.TextBox txtPath 
         Height          =   270
         Left            =   840
         TabIndex        =   16
         Text            =   "Text1"
         Top             =   720
         Width           =   2295
      End
      Begin VB.OptionButton OptOneToOne 
         Caption         =   "һһ��Ӧ�����ļ�"
         Height          =   495
         Left            =   1800
         TabIndex        =   15
         Top             =   240
         Width           =   1335
      End
      Begin VB.OptionButton OptOne 
         Caption         =   "���ܵ�һ���ļ�"
         Height          =   495
         Left            =   120
         TabIndex        =   14
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "�ļ���:"
         Height          =   180
         Left            =   120
         TabIndex        =   20
         Top             =   1440
         Width           =   630
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "·��:"
         Height          =   180
         Left            =   120
         TabIndex        =   19
         Top             =   720
         Width           =   450
      End
   End
   Begin MSComctlLib.ImageList ImgLst 
      Left            =   2640
      Top             =   3720
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      UseMaskColor    =   0   'False
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   12
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":0000
            Key             =   "close"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":0454
            Key             =   "file"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":08A8
            Key             =   "err"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":0CFC
            Key             =   "part"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":1150
            Key             =   "exp"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":15A4
            Key             =   "drop"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":19F8
            Key             =   "infor"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":1E4C
            Key             =   "no"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":2168
            Key             =   "fileend"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":25BC
            Key             =   "in"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":2A10
            Key             =   "open"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Form1.frx":2E64
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton CmdAllDel 
      Caption         =   "ȫ��ɾ��(&A)"
      Height          =   255
      Left            =   5040
      TabIndex        =   11
      Top             =   4680
      Width           =   1215
   End
   Begin VB.CommandButton CmdDel 
      Caption         =   "ɾ��(&D)"
      Height          =   255
      Left            =   3840
      TabIndex        =   10
      Top             =   4680
      Width           =   1095
   End
   Begin VB.Frame Frame2 
      Height          =   495
      Left            =   3960
      TabIndex        =   7
      Top             =   3960
      Width           =   2775
      Begin VB.OptionButton OptJM 
         Caption         =   "�����ļ�"
         Height          =   255
         Left            =   1440
         TabIndex        =   9
         Top             =   120
         Width           =   1215
      End
      Begin VB.OptionButton Optadd 
         Caption         =   "�����ļ�"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   120
         Width           =   1215
      End
   End
   Begin VB.CommandButton cmdBrow 
      Caption         =   "���(&B).."
      Height          =   255
      Left            =   2760
      TabIndex        =   6
      Top             =   4680
      Width           =   975
   End
   Begin VB.CommandButton CmdOk 
      Caption         =   "ȷ��(&Y)"
      Height          =   255
      Left            =   6360
      TabIndex        =   5
      Top             =   4680
      Width           =   855
   End
   Begin VB.Frame Frame1 
      Caption         =   "����:"
      Height          =   855
      Left            =   360
      TabIndex        =   2
      Top             =   4080
      Width           =   2175
      Begin VB.TextBox txtPassWord 
         Height          =   270
         Left            =   240
         TabIndex        =   4
         Text            =   "Text1"
         Top             =   480
         Width           =   1575
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "����Ϊ8λ�ַ�������"
         Height          =   180
         Left            =   240
         TabIndex        =   3
         Top             =   240
         Width           =   1710
      End
   End
   Begin MSComDlg.CommonDialog CMD 
      Left            =   4080
      Top             =   960
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame FraSFL 
      Caption         =   "Դ���ļ��б�"
      Height          =   3375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   3255
      Begin MSComctlLib.TreeView Tree 
         Height          =   3135
         Left            =   0
         TabIndex        =   12
         Top             =   240
         Width           =   3255
         _ExtentX        =   5741
         _ExtentY        =   5530
         _Version        =   393217
         Style           =   7
         Appearance      =   1
      End
      Begin VB.ListBox lstSFile 
         Height          =   3120
         Left            =   0
         MultiSelect     =   2  'Extended
         TabIndex        =   1
         Top             =   240
         Width           =   3255
      End
   End
   Begin VB.Menu mnuFile 
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "��(&O)"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "�˳�(&E)"
         Shortcut        =   ^E
      End
   End
   Begin VB.Menu mnuOption 
      Caption         =   "ѡ��(&O)"
      Begin VB.Menu mnuOptionAdd 
         Caption         =   "����(&A)"
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuOptionJianMi 
         Caption         =   "����(&J)"
         Shortcut        =   ^J
      End
      Begin VB.Menu mnuOptionBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionShowFileDiaglog 
         Caption         =   "��ʾ�ļ��Ի���(&S)"
         Shortcut        =   ^S
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim bDrop As Boolean '��������־
Dim DropNode As Node 'Ҫ�������Ľ��

Private Sub Form_Load()
Me.Caption = "�����ļ�"
With lstSFile
     .Clear
End With
With LstDFile
     .Clear
End With
txtPath.Text = ""
TxtFileName.Text = ""
CmdDel.Enabled = False
CmdAllDel.Enabled = False
txtPassWord.Text = ""
Optadd.Value = True
OptOne.Value = True
OptJmFile.Value = True
FraJm.Visible = False
With Tree
     .Visible = False
     '.LineStyle = tvwRootLines
     '.Checkboxes = True
     .Style = tvwTreelinesPlusMinusPictureText
     .ImageList = ImgLst
End With
End Sub

'---------------------------------------------------------
'�˵�
'---------------------------------------------------------
'�˳�
Private Sub mnuFileExit_Click()
Unload Me
End Sub

'��
Private Sub mnuFileOpen_Click()
cmdBrow_Click
End Sub

'����
Private Sub mnuOptionAdd_Click()
Optadd.Value = True
End Sub

'����
Private Sub mnuOptionJianMi_Click()
OptJM.Value = True
End Sub

'---------------------------------------------------------------
'��ѡ��ť
'---------------------------------------------------------------
'�����ļ���ť
Private Sub Optadd_Click()
mnuOptionAdd.Checked = Optadd.Value
mnuOptionJianMi.Checked = Not mnuOptionAdd.Checked
If Optadd.Value Then
   LstDFile.Visible = False
   FraAdd.Visible = True
   OptOne.Visible = True
   OptOneToOne.Visible = True
   FraJm.Visible = False
   Tree.Visible = False
   lstSFile.Visible = True
   txtPath.Enabled = True
   CmdDBrow.Enabled = True
   If OptOneToOne.Value Then
      TxtFileName.Enabled = False
   End If
   If lstSFile.SelCount Then
      CmdDel.Enabled = True
   Else
      CmdDel.Enabled = False
   End If
   If lstSFile.ListCount Then
      CmdAllDel.Enabled = True
   Else
      CmdAllDel.Enabled = False
   End If
End If
End Sub

'�����ļ���ť
Private Sub OptJM_Click()
mnuOptionJianMi.Checked = OptJM.Value
mnuOptionAdd.Checked = Not mnuOptionJianMi.Checked
If OptJM.Value Then
   Tree.Visible = True
   lstSFile.Visible = False
   LstDFile.Visible = True
   TxtFileName.Enabled = True
   If OptFind.Value Then
      txtPath.Enabled = False
      CmdDBrow.Enabled = False
   End If
   If Tree.SelectedItem Is Nothing Then
      CmdDel.Enabled = False
   Else
      CmdDel.Enabled = True
   End If
   If Tree.Nodes.Count Then
      CmdAllDel.Enabled = True
   Else
      CmdAllDel.Enabled = False
   End If
   OptOne.Visible = False
   OptOneToOne.Visible = False
   FraJm.Visible = True
End If
End Sub

Private Sub OptFind_Click()
txtPath.Enabled = Not OptFind.Value
CmdDBrow.Enabled = Not OptFind.Value
End Sub

Private Sub OptJmFile_Click()
txtPath.Enabled = OptJmFile.Value
CmdDBrow.Enabled = OptJmFile.Value
End Sub

Private Sub OptOne_Click()
TxtFileName.Enabled = OptOne.Value
End Sub

Private Sub OptOneToOne_Click()
TxtFileName.Enabled = Not OptOneToOne.Value
End Sub

'---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
'��ͨ��ť
'---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
'���
Private Sub cmdBrow_Click()
Dim sFileName() As String
Dim I As Long, J As Long
Dim Nodex As Node, N As Node
With CMD
     .Flags = mscomdlg.FileOpenConstants.cdlOFNAllowMultiselect + FileOpenConstants.cdlOFNHideReadOnly + FileOpenConstants.cdlOFNExplorer + FileOpenConstants.cdlOFNLongNames
     .FileName = ""
     .DialogTitle = "��"
     If Optadd.Value Then
        .Filter = "�����ļ�(*.*)|*.*"
     Else
        .Filter = "�����ļ�(*.jmw)|*.jmw|�����ļ�(*.*)|*.*"
     End If
     .MaxFileSize = 1500
     .ShowOpen
     If .FileName <> "" Then
        ReDim sFileName(0)
        sGetAllFile .FileName, sFileName
        For I = 1 To UBound(sFileName)
            If Tree.Visible Then
               If Tree.Nodes.Count Then '��ֹ��ͬ���ļ�
                  Set N = Tree.Nodes.Item(1).FirstSibling
                  Do While (Not (N Is Nothing))
                     If UCase(N.Text) = UCase(sFileName(I)) Then
                        Exit Do
                     End If
                     Set N = N.Next
                  Loop
               End If
               If N Is Nothing Then
                  Set Nodex = Tree.Nodes.Add(, , , sFileName(I), "close")
                  Nodex.Tag = "JMW"  '���ñ�־Ϊ�����ļ�
               End If
            Else
               For J = 0 To lstSFile.ListCount - 1 '��ֹ��ͬ���ļ�
                   If UCase(lstSFile.List(J)) = UCase(sFileName(I)) Then
                      Exit For
                   End If
               Next J
               If J >= lstSFile.ListCount Then
                  lstSFile.AddItem sFileName(I)
               End If
            End If
        Next I
        CmdAllDel.Enabled = True
     End If
End With
End Sub

Private Sub CmdDel_Click()
Dim I As Integer
If lstSFile.Visible Then
   For I = lstSFile.ListCount - 1 To 0 Step -1
       If lstSFile.Selected(I) Then
          lstSFile.RemoveItem I
       End If
   Next I
   If lstSFile.SelCount = 0 Then
      CmdDel.Enabled = False
   End If
End If
If Tree.Visible Then
   Tree.Nodes.Remove Tree.SelectedItem.Index
   CmdDel.Enabled = False
End If
End Sub

Private Sub CmdAllDel_Click()
Dim I As Integer
If lstSFile.Visible Then
   lstSFile.Clear
End If
If Tree.Visible Then
   Tree.Nodes.Clear
End If
CmdAllDel.Enabled = False
CmdDel.Enabled = False
End Sub

Private Sub CmdOk_Click()
Dim I As Long, N As Node
Screen.MousePointer = VBRUN.MousePointerConstants.vbHourglass
If Optadd.Value Then
   If OptOne.Value Then
      If TxtFileName = "" Then
         MsgBox "������Ŀ���ļ�����"
         Screen.MousePointer = vbDefault
         Exit Sub
      End If
      For I = 0 To lstSFile.ListCount - 1
          AddFileEx lstSFile.List(I), TxtFileName, txtPassWord, txtPath
      Next I
   Else
      For I = 0 To lstSFile.ListCount - 1
          AddFileEx lstSFile.List(I), , txtPassWord, txtPath, ����Դ�ļ� Or �����µ����ļ�
      Next I
   End If
End If
If OptJM.Value Then
   If Tree.Nodes.Count Then
      Set N = Tree.Nodes.Item(1).FirstSibling
   End If
Do While (Not (N Is Nothing))
   fJM_eFile N
   Set N = N.Next
Loop
End If
Screen.MousePointer = vbDefault
End Sub

'----------------------------------------------------------------------
'���Ϳؼ�
'----------------------------------------------------------------------
Private Sub Tree_NodeClick(ByVal Node As MSComctlLib.Node)
Dim I As Long, FI() As Type_File_Information
Dim Nodex As Node
If Node.Tag = "JMW" And Node.Image = "close" And OptFind.Value Then
   Node.Image = "exp"
   I = JM_eFile(Node.Text, FI(), , ��Դ�ļ��в��������ļ���Ϣ, txtPassWord)
   If I And Enum_Command_para_JM.���ļ����Ǽ����ļ� Then
      Node.Image = "err"
      If MsgBox("���ļ����Ǽ����ļ�,�Ƿ���б����Ƴ�?", vbCritical + vbYesNo) = vbYes Then
         Tree.Nodes.Remove Node.Index
      End If
   Else
      fInforMationToNode Node, FI
   Node.Image = "open"
   End If
End If
CmdDel.Enabled = True
End Sub

Private Sub Tree_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
If Button = vbLeftButton Then
   If Tree.SelectedItem.Tag = "JMW" Or Tree.SelectedItem.Tag = "FILE" Then
      bDrop = True
      Set DropNode = Tree.SelectedItem
      Tree.DragIcon = ImgLst.ListImages("drop").Picture
      Tree.Drag vbBeginDrag
   Else
      bDrop = False
      Set DropNode = Nothing
      Tree.DragIcon = ImgLst.ListImages("no").Picture
   End If
End If
End Sub

Private Sub Tree_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
If Button = vbLeftButton Then
   bDrop = False
End If
End Sub

'------------------------------------------------------------------------------
'�б�ؼ�
'------------------------------------------------------------------------------
Private Sub LstDFile_DragDrop(Source As Control, x As Single, y As Single)
Dim I
If bDrop Then
   I = fJM_eFile(DropNode)
   Set DropNode = Nothing
   Tree.Drag vbEndDrag
End If
End Sub

Private Sub lstSFile_Click()
If lstSFile.ListCount Then
   CmdDel.Enabled = True
End If
End Sub

'---------------------------------------------------------------------------
'����
'---------------------------------------------------------------------------
'�����ļ�����
Private Function fJM_eFile(Node As Node)
Dim FI() As Type_File_Information, I As Long
   If Node.Tag = "JMW" Then
      If TxtFileName.Text = "" Or TxtFileName.Text = "*.*" Then
         JM_eFile Node.Text, FI(), , _
            ��Դ�ļ��м�����Ϣ�ֽ���ļ� Or _
               ��Դ�ļ��в��������ļ���Ϣ, _
               txtPassWord.Text, txtPath.Text
         For I = 1 To UBound(FI)
             LstDFile.AddItem FI(I).FileName
         Next I
      Else
         JM_eFile Node.Text, FI(), TxtFileName.Text, _
               ��Դ�ļ��м�����Ϣ�ֽ���ļ� Or _
               ��Դ�ļ��в���ĳ�ļ���Ϣ, _
               txtPassWord, txtPath
         LstDFile.AddItem FI(UBound(FI)).FileName
      End If
      If Node.Image = "close" Then
         fInforMationToNode Node, FI
      End If
      Node.Image = "open"
   End If
   If Node.Tag = "FILE" Then
      JM_eFile Node.Parent.Text, FI(), TxtFileName.Text, ��Դ�ļ��в���ĳ�ļ���Ϣ Or ��Դ�ļ��м�����Ϣ�ֽ���ļ�, txtPassWord, txtPath
      Node.Image = "fileend"
      LstDFile.AddItem FI(1).FileName
   End If
End Function

'�ѽ������Ϣ�������Ϳؼ�
Private Function fInforMationToNode(Node As Node, FI() As Type_File_Information)
Dim I As Long, Nodex As Node
For I = 1 To UBound(FI)
    With Tree.Nodes
         Set Nodex = .Add(Node, tvwChild, , FI(I).FileName, "file")
         Nodex.Tag = "FILE"
         If UCase(Nodex.Text) = UCase(LTrim(RTrim(TxtFileName.Text))) Then
            Nodex.EnsureVisible
         End If
         If IsNumeric(TxtFileName) And I = Val(TxtFileName) Then
            Nodex.EnsureVisible
         End If
        .Add Nodex, tvwChild, , "λ���ļ��е� " & I & " ��", "infor"
        .Add Nodex, tvwChild, , "�ļ�����:" & Str(FI(I).lFileLength) & " �ֽ�", "infor"
        .Add Nodex, tvwChild, , "��������:" & Format(FI(I).dDate, "yyyy��mm��dd��"), "infor"
    End With
Next I
End Function
