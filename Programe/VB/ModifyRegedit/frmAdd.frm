VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmAdd 
   Caption         =   "������"
   ClientHeight    =   6150
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8025
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6150
   ScaleWidth      =   8025
   StartUpPosition =   2  '��Ļ����
   Begin VB.CommandButton cmdCAdd 
      Caption         =   "��������(&D)"
      Height          =   320
      Left            =   2520
      TabIndex        =   46
      Top             =   5760
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Frame fraControl 
      Caption         =   "���ӿؼ�"
      Height          =   5655
      Left            =   120
      TabIndex        =   22
      Top             =   0
      Width           =   7815
      Begin VB.Frame fraControlList 
         Caption         =   "�б�ؼ�"
         Height          =   4935
         Left            =   120
         TabIndex        =   39
         Top             =   240
         Visible         =   0   'False
         Width           =   3255
         Begin VB.ListBox lst 
            Height          =   3210
            Left            =   120
            Style           =   1  'Checkbox
            TabIndex        =   40
            Top             =   240
            Width           =   3015
         End
         Begin VB.Label lblControlList 
            Caption         =   "��һ���������б�ؼ���"
            Height          =   975
            Left            =   120
            TabIndex        =   41
            Top             =   3840
            Width           =   3015
            WordWrap        =   -1  'True
         End
      End
      Begin VB.Frame fraKeyVal 
         Caption         =   "��ֵ:"
         Height          =   5055
         Left            =   3480
         TabIndex        =   24
         Top             =   120
         Width           =   4335
         Begin VB.TextBox txtKeyControlText 
            Height          =   270
            Left            =   2040
            TabIndex        =   45
            Top             =   3480
            Width           =   2175
         End
         Begin VB.TextBox txtKeyReadme 
            Height          =   855
            Left            =   120
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   42
            Top             =   4200
            Width           =   4095
         End
         Begin VB.ComboBox cmbKeyRoot 
            Height          =   300
            ItemData        =   "frmAdd.frx":0000
            Left            =   240
            List            =   "frmAdd.frx":0013
            Style           =   2  'Dropdown List
            TabIndex        =   31
            Top             =   600
            Width           =   3975
         End
         Begin VB.ComboBox cmbMainKey 
            Height          =   300
            Left            =   240
            TabIndex        =   30
            Top             =   1200
            Width           =   3975
         End
         Begin VB.ComboBox cmbSubKey 
            Height          =   300
            Left            =   240
            Style           =   1  'Simple Combo
            TabIndex        =   29
            Top             =   1800
            Width           =   3975
         End
         Begin VB.ComboBox cmbKeyVal 
            Height          =   300
            Left            =   240
            Style           =   1  'Simple Combo
            TabIndex        =   28
            Top             =   2400
            Width           =   3975
         End
         Begin VB.ComboBox cmbKeyOperistSystem 
            Height          =   300
            ItemData        =   "frmAdd.frx":0072
            Left            =   1440
            List            =   "frmAdd.frx":008B
            Style           =   2  'Dropdown List
            TabIndex        =   27
            Top             =   3000
            Width           =   1455
         End
         Begin VB.ComboBox cmbKeyPassLevel 
            Height          =   300
            ItemData        =   "frmAdd.frx":011C
            Left            =   3240
            List            =   "frmAdd.frx":0129
            Style           =   2  'Dropdown List
            TabIndex        =   26
            Top             =   3000
            Width           =   975
         End
         Begin VB.ComboBox cmbKeyType 
            Height          =   300
            ItemData        =   "frmAdd.frx":0141
            Left            =   120
            List            =   "frmAdd.frx":014E
            Style           =   2  'Dropdown List
            TabIndex        =   25
            Top             =   3000
            Width           =   1215
         End
         Begin VB.Label Label9 
            AutoSize        =   -1  'True
            Caption         =   "�ؼ��е�˵�����֣�"
            Height          =   180
            Left            =   240
            TabIndex        =   44
            Top             =   3480
            Width           =   1620
         End
         Begin VB.Label Label8 
            AutoSize        =   -1  'True
            Caption         =   "��ֵ˵��(���������Լ�ֵ���ܵ�˵������"
            Height          =   180
            Left            =   120
            TabIndex        =   43
            Top             =   3960
            Width           =   3510
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "������"
            Height          =   180
            Index           =   0
            Left            =   240
            TabIndex        =   38
            Top             =   360
            Width           =   540
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "������"
            Height          =   180
            Index           =   1
            Left            =   240
            TabIndex        =   37
            Top             =   960
            Width           =   540
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "�Ӽ���"
            Height          =   180
            Index           =   2
            Left            =   240
            TabIndex        =   36
            Top             =   1560
            Width           =   540
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "��ֵ��"
            Height          =   180
            Index           =   3
            Left            =   240
            TabIndex        =   35
            Top             =   2160
            Width           =   540
         End
         Begin VB.Label Label5 
            AutoSize        =   -1  'True
            Caption         =   "���ò���ϵͳ��"
            Height          =   180
            Index           =   4
            Left            =   1440
            TabIndex        =   34
            Top             =   2760
            Width           =   1260
         End
         Begin VB.Label Label6 
            AutoSize        =   -1  'True
            Caption         =   "��ȫ����"
            Height          =   180
            Left            =   3240
            TabIndex        =   33
            Top             =   2760
            Width           =   900
         End
         Begin VB.Label Label7 
            AutoSize        =   -1  'True
            Caption         =   "��ֵ���ͣ�"
            Height          =   180
            Left            =   240
            TabIndex        =   32
            Top             =   2760
            Width           =   900
         End
      End
      Begin VB.CommandButton cmdAdd 
         Caption         =   "��������(&A)"
         Height          =   255
         Left            =   5520
         TabIndex        =   23
         Top             =   5280
         Width           =   1455
      End
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   " ȡ��(&C)"
      Height          =   320
      Left            =   6720
      TabIndex        =   5
      Top             =   5760
      Width           =   975
   End
   Begin VB.CommandButton cmdNext 
      Caption         =   "��һ��(&N)"
      Height          =   320
      Left            =   5400
      TabIndex        =   4
      Top             =   5760
      Width           =   975
   End
   Begin VB.CommandButton cmdprevious 
      Caption         =   "��һ��(&P)"
      Height          =   320
      Left            =   4080
      TabIndex        =   3
      Top             =   5760
      Width           =   975
   End
   Begin VB.Frame FraNode 
      Caption         =   "���ӽ��"
      Height          =   5655
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   7815
      Begin VB.Frame Frame2 
         Caption         =   "���İ�ȫ����"
         Height          =   615
         Left            =   3720
         TabIndex        =   18
         Top             =   4800
         Width           =   3855
         Begin VB.OptionButton optPassLevel 
            Caption         =   "����"
            Height          =   255
            Index           =   2
            Left            =   2160
            TabIndex        =   21
            Top             =   240
            Width           =   975
         End
         Begin VB.OptionButton optPassLevel 
            Caption         =   "�û���"
            Height          =   255
            Index           =   1
            Left            =   960
            TabIndex        =   20
            Top             =   240
            Width           =   975
         End
         Begin VB.OptionButton optPassLevel 
            Caption         =   "��`"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   19
            Top             =   240
            Value           =   -1  'True
            Width           =   735
         End
      End
      Begin VB.Frame Frame1 
         Caption         =   "ѡ��ؼ�����"
         Height          =   1575
         Left            =   3720
         TabIndex        =   12
         Top             =   3120
         Width           =   3855
         Begin VB.OptionButton optControl 
            Caption         =   "ֻѡ�ı��ؼ�"
            Height          =   180
            Index           =   0
            Left            =   240
            TabIndex        =   16
            Top             =   1320
            Value           =   -1  'True
            Width           =   2655
         End
         Begin VB.OptionButton optControl 
            Caption         =   "���������ؼ�(������·���ļ�ֵ)"
            Height          =   255
            Index           =   2
            Left            =   240
            TabIndex        =   15
            Top             =   840
            Width           =   3495
         End
         Begin VB.OptionButton optControl 
            Caption         =   "�б��ؼ�(����ֻ��Booleanֵ�ļ�ֵ)"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   14
            Top             =   600
            Width           =   3495
         End
         Begin VB.CheckBox chkText 
            Caption         =   "�ı�(���ڶԴ˲�������˵����Ϊ��ѡ)"
            Height          =   255
            Left            =   240
            TabIndex        =   13
            Top             =   240
            Value           =   1  'Checked
            Width           =   3375
         End
      End
      Begin VB.TextBox txtNodeText 
         Height          =   270
         Left            =   6480
         TabIndex        =   11
         Top             =   2160
         Width           =   975
      End
      Begin VB.TextBox txtNodeKey 
         Height          =   270
         Left            =   5040
         TabIndex        =   10
         Top             =   2160
         Width           =   975
      End
      Begin VB.TextBox txtNodeRalation 
         Height          =   270
         Left            =   3720
         TabIndex        =   9
         Top             =   2160
         Width           =   975
      End
      Begin MSComctlLib.TreeView Tree 
         Height          =   5055
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   3135
         _ExtentX        =   5530
         _ExtentY        =   8916
         _Version        =   393217
         Style           =   7
         Appearance      =   1
      End
      Begin VB.Line Line2 
         BorderColor     =   &H80000005&
         X1              =   3720
         X2              =   7560
         Y1              =   2520
         Y2              =   2520
      End
      Begin VB.Label Label4 
         Caption         =   "�ؼ��������ı�Ϊ��ѡ�ģ������Ŀؼ���ѡ��ֻ��ѡȡһ�֡�"
         Height          =   375
         Left            =   3720
         TabIndex        =   17
         Top             =   2640
         Width           =   3855
         WordWrap        =   -1  'True
      End
      Begin VB.Line Line1 
         BorderColor     =   &H80000005&
         X1              =   3720
         X2              =   7560
         Y1              =   1680
         Y2              =   1680
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "����:"
         Height          =   180
         Left            =   6480
         TabIndex        =   8
         Top             =   1800
         Width           =   450
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "�ؼ���:"
         Height          =   180
         Left            =   5040
         TabIndex        =   7
         Top             =   1800
         Width           =   630
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "��ϵ:"
         Height          =   180
         Left            =   3720
         TabIndex        =   6
         Top             =   1800
         Width           =   450
      End
      Begin VB.Label lblnode 
         Caption         =   "��һ��Ϊ����ؼ������ӽ�㡣"
         Height          =   1260
         Left            =   3720
         TabIndex        =   2
         Top             =   360
         Width           =   4020
         WordWrap        =   -1  'True
      End
   End
End
Attribute VB_Name = "frmAdd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Enum Enum_Step '������ö������
     Enum_Add_Node = 0
     Enum_Add_Control = 1
     End Enum
     
Dim boolAdd As Boolean '�����˵ı�ʶ
Dim StepNum As Integer   '����
Dim boolBulidNode As Boolean '�Ѿ�������һ�����
Dim DragNode As Node 'Ҫ�ж�����
Dim boolDrag As Boolean '�ж���ʶ
'-------------------------------------------------------
Dim NodeRalation As String '����ϵ
Dim NodeKey As String '���ؼ���
Dim NodeText As String '�������
Dim NodePassLevel As Enum_PassLevel '��ȫ����
Dim ControlText As String  '�ؼ��е��ı�
Dim ControlKeyType As ENUM_REG_KEY_TYPE '�ؼ��еļ�ֵ����
Dim ControlStartpos As Long '�ؼ��еļ���ֵ����ʼλ��
Dim ControlEndPos As Long '�ؼ��м�ֵ�Ľ���λ��

'---------------------------------------------
'��ť
Private Sub cmdCancel_Click()
        Unload Me
End Sub

Private Sub cmdprevious_Click()
Select Case StepNum
       Case Enum_Add_Node '���ӽ��
            
       Case Enum_Add_Control '���ӿؼ�
            cmdprevious.Enabled = False
            cmdCAdd.Visible = False
            cmdNext.Caption = "��һ��(&N)"
            FraNode.Visible = True
            fraControl.Visible = False
            
End Select
StepNum = StepNum - 1
End Sub

Private Sub cmdNext_Click()
Select Case StepNum
       Case Enum_Add_Node '���ӽ��
            If txtNodeKey.Text = "" Or txtNodeText.Text = "" Then
               MsgBox "�ؼ��ֺ����ֱ�����ֵ", , Me.Caption & "-���ӽ��"
               Exit Sub
            End If
            cmdprevious.Enabled = True
            cmdCAdd.Visible = True
            cmdNext.Caption = "���(&F)"
            FraNode.Visible = False
            fraControl.Visible = True
            ControlStartpos = UBound(tKeyVal)
            Select Case GetControl
                   Case Enum_Control.Enum_Control_List
                        fraControlList.Visible = True
                        lst.Clear
                   Case Enum_Control.Enum_Control_FrameInput
                        
                   Case Enum_Control.Enum_Control_DBGird
                        
            End Select
            
       Case Enum_Add_Control '���ӿؼ�;���
            If Not LetKeyVal Then Exit Sub
            ControlEndPos = UBound(tKeyVal)
            AddToTypeStructe '��ṹ����������
            SaveKeyFile  '���浽�ļ���
            
            Unload Me
End Select
StepNum = StepNum + 1
End Sub

Private Sub cmdAdd_Click()
If cmbKeyRoot.Text <> "" And cmbMainKey.Text <> "" _
   And cmbSubKey <> "" Then
   Call LetKeyVal
   lst.AddItem txtKeyControlText.Text
        AddIntoMainKey '���������������������е�����
Else
   MsgBox "�������������Ӽ����б��븳ֵ", , Me.Caption
End If
End Sub

Private Sub cmdCAdd_Click()
        If Not LetKeyVal Then Exit Sub
        ControlEndPos = UBound(tKeyVal)
        '��ṹ��ֵ , �洢
        AddToTypeStructe
        cmdCAdd.Visible = False
        cmdprevious.Enabled = False
        cmdNext.Caption = "��һ��(&N)"
        txtNodeKey = ""
        txtNodeText = ""
        StepNum = 0
        FraNode.Visible = True
        fraControl.Visible = False
        boolBulidNode = False
End Sub

Private Sub Form_Load()
Dim Nodx As Node, i As Long
cmdprevious.Enabled = False '�տ�ʼʱû����һ��
StepNum = 0 '��ʼ������
txtNodeRalation.Enabled = False '��ϵ�����޸�
boolBulidNode = False
With FraNode '���ӽ��ؼ���λ��
     .Top = 0
     .Left = 120
     .Visible = True
End With
With fraControl
     .Top = 0
     .Left = 120
     .Visible = False
End With
With Tree
    .LabelEdit = tvwManual
    .Style = tvwTreelinesPlusMinusPictureText
    .LineStyle = tvwRootLines
    .ImageList = frmMain.Img
     Set Nodx = .Nodes.add(, tvwChild, "mycomputer", "�ҵĵ���", "mycomputer")
     Set .SelectedItem = Nodx
     Set Nodx = .Nodes.add("mycomputer", tvwChild, "desktop", "����", "closedec")
     Set Nodx = .Nodes.add("desktop", tvwChild, "desktopstartmenu", "��ʼ�˵�", "closedec")
     Set Nodx = .Nodes.add("desktop", tvwChild, "desktopbackbamp", "���汳��", "closedec")
     Set Nodx = .Nodes.add("desktop", tvwChild, "desktopother", "����", "closedec")
     
     Set Nodx = .Nodes.add("desktopstartmenu", tvwChild, "desktopstartmenuset", "����", "closedec")
     '---------------------------------------------------------------------------------------------------------------------------
     Set Nodx = .Nodes.add("desktopstartmenuset", tvwChild, "desktopstartmenusetcontrolpanel", "�������", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelsystem", "ϵͳ", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpaneldisplay", "��ʾ��", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelnetwork", "����", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelnetworkhood", "�����ھ�", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelnetdial", "�κ�����", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelpassword", "����/����", "closedec")
     '----------------------------------------------------------------------------------------------------------------------------
     Set Nodx = .Nodes.add("desktopstartmenu", tvwChild, "desktopstartmenumsdos", "MSDOS��ʽ", "closedec")
     
     Set Nodx = .Nodes.add("mycomputer", tvwChild, "controlpanel", "�������", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelsystem", "ϵͳ", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpaneldisplay", "��ʾ��", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetwork", "����", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetworkhood", "�����ھ�", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetdial", "�κ�����", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelpassword", "����/����", "closedec")
     
     Set Nodx = .Nodes.add("mycomputer", tvwChild, "security", "��ȫ", "closedec")
     Set Nodx = .Nodes.add("security", tvwChild, "securitypassword", "����", "closedec")
          
End With
For i = 1 To UBound(tTree)
    With tTree(i)
         Set Nodx = Tree.Nodes.add(.Ralation, tvwChild, .Key, .Text, "closedec")
    End With
Next i
lblnode.Caption = "��һ��������ؼ����ӽ�㡣" + Chr(13) + _
                  "��ϵ:��ʾ���ӵĽ����ѡȡ�������ӽ��,��" + Chr(13) + _
                  "     �û�Ҫ�޸Ĺ�ϵʱ,�ڽ��ؼ���ֱ���ж���" + Chr(13) + _
                  "�ؼ���:���ڱ�ʶ�öԵ�,�Ա��Ժ����ӽ��ʱȷ" + Chr(13) + _
                  "     ����ϵ,������·��������" + Chr(13) + _
                  "����:��Ҫ���ӽ�����������,Ϊ��һ���Ĺؼ�" + Chr(13) + "     �֡�"
lblControlList.Caption = "��һ���������б�ؼ���" & Chr(13) & _
                "���ֿؼ����ڼ�ֵΪBooleanֵ����������Ӽ�ֵ���������������Ӽ�����ֵ�ȡ�"

'���ļ���װ�ؼ�ֵ

'����ֵ������ֵ
'AddIntoMainKey
If cmbMainKey.ListIndex <> -1 Then cmbMainKey.ListIndex = 0
cmbKeyRoot.ListIndex = 0
cmbKeyType.ListIndex = 0
cmbKeyOperistSystem.ListIndex = 0
cmbKeyPassLevel.ListIndex = 0
End Sub

'------------------------------------------------------------------------------------------
'��һ�����ӽ���ѡ��ؼ�����ȷ��tTree��tTreeNode
'------------------------------------------------------------------------------------------
Private Sub Tree_Collapse(ByVal Node As MSComctlLib.Node)
        If Node.Key <> "mycomputer" Then Node.Image = "closedec"
End Sub

Private Sub Tree_Expand(ByVal Node As MSComctlLib.Node)
        If Node.Key <> "mycomputer" Then Node.Image = "opendec"
End Sub

Private Sub Tree_NodeClick(ByVal Node As MSComctlLib.Node)
On Error Resume Next
   If boolBulidNode Then
      txtNodeRalation.Text = Node.Parent.Key
      If Err Then txtNodeRalation.Text = ""
      txtNodeKey.Text = Node.Key
      txtNodeText.Text = Node.Text
      If txtNodeKey.Text <> NodeKey Then
         txtNodeKey.Enabled = False
         txtNodeText.Enabled = False
      Else
         txtNodeKey.Enabled = True
         txtNodeText.Enabled = True
      End If
   Else
      txtNodeRalation.Text = Node.Key
   End If
End Sub

Private Sub Tree_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
If boolBulidNode And Tree.SelectedItem.Key = NodeKey Then
   boolDrag = True '�����ж���ʶ
   Set DragNode = Tree.SelectedItem
   Set Tree.DropHighlight = Nothing
Else
   Set DragNode = Nothing
End If
End Sub

Private Sub Tree_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Run Then On Error Resume Next
If Button = vbLeftButton And boolDrag Then
   Tree.DragIcon = Tree.SelectedItem.CreateDragImage
   Tree.Drag vbBeginDrag
End If
End Sub

Private Sub Tree_DragOver(Source As Control, X As Single, Y As Single, State As Integer)
If Run Then On Error Resume Next
If boolBulidNode And boolDrag Then
   Set Tree.DropHighlight = Tree.HitTest(X, Y)
End If
End Sub

Private Sub Tree_DragDrop(Source As Control, X As Single, Y As Single)
If boolBulidNode And boolDrag Then
   If Not Tree.DropHighlight Is Nothing Then
      Set DragNode.Parent = Tree.DropHighlight
      txtNodeRalation.Text = DragNode.Parent.Key
      NodeRalation = DragNode.Parent.Key
   End If
End If
boolDrag = False
End Sub

Private Sub txtNodeKey_LostFocus()
On Error GoTo txtnodekey_lostforcus_error
Dim Nodx As Node
If txtNodeKey.Text <> "" And txtNodeText.Text <> "" And boolBulidNode Then '�޸Ľ��
   Tree.SelectedItem.Key = txtNodeKey.Text
   NodeRalation = txtNodeRalation.Text
   NodeKey = txtNodeKey.Text
   NodeText = txtNodeText.Text
ElseIf txtNodeKey.Text <> "" And txtNodeText.Text <> "" And Not boolBulidNode Then
   '���ӽ��
   Set Nodx = Tree.Nodes.add(txtNodeRalation.Text, tvwChild, txtNodeKey.Text, txtNodeText.Text, "closedec")
   Nodx.EnsureVisible
   boolBulidNode = True
   NodeRalation = txtNodeRalation.Text
   NodeKey = txtNodeKey.Text
   NodeText = txtNodeText.Text
ElseIf boolBulidNode Then
    Tree.SelectedItem.Key = txtNodeKey.Text
End If
Exit Sub
txtnodekey_lostforcus_error:
    If Err.Number = 35601 Then
       MsgBox "�˹�ϵ�����ڣ�������ȷ����ϵ", , "��ϵ������"
       txtNodeRalation.SetFocus
    End If
    If Err.Number = 35602 Then
       MsgBox "�ؼ����Ѿ�����,������ȷ���ؼ�ֵ", , "�ؼ�ֵ�ظ�"
       txtNodeKey.SetFocus
    End If
End Sub

Private Sub txtNodeText_LostFocus()
On Error GoTo txtnodetext_lostfocuserror
Dim Nodx As Node
If txtNodeKey.Text <> "" And txtNodeText.Text <> "" And boolBulidNode Then   '�޸Ľ��
   Tree.SelectedItem.Text = txtNodeText.Text
   NodeRalation = txtNodeRalation.Text
   NodeKey = txtNodeKey.Text
   NodeText = txtNodeText.Text
ElseIf txtNodeKey.Text <> "" And txtNodeText.Text <> "" And Not boolBulidNode Then
   '���ӽ��
   Set Nodx = Tree.Nodes.add(txtNodeRalation.Text, tvwChild, txtNodeKey.Text, txtNodeText.Text, "closedec")
   Nodx.EnsureVisible
   NodeRalation = txtNodeRalation.Text
   NodeKey = txtNodeKey.Text
   NodeText = txtNodeText.Text
   boolBulidNode = True
ElseIf boolBulidNode Then
    Tree.SelectedItem.Text = txtNodeText.Text
End If
Exit Sub
txtnodetext_lostfocuserror:
    If Err.Number = 35601 Then
       MsgBox "�˹�ϵ�����ڣ�������ȷ����ϵ", , "��ϵ������"
       txtNodeRalation.SetFocus
    End If
    If Err.Number = 35602 Then
       MsgBox "�ؼ����Ѿ�����,������ȷ���ؼ�ֵ", , "�ؼ�ֵ�ظ�"
       txtNodeKey.SetFocus
    End If
End Sub

Private Sub chkText_Click()
        chkText.Value = 1 '�ı��ؼ�Ϊ��ѡ,����˵��
End Sub

'-------------------------------------------------------------------------------------------------------
'��һ���е��Լ��ĺ���
'-------------------------------------------------------------------------------------------------------
'�õ��ؼ�
Public Function GetControl() As Enum_Control
Dim i As Long
For i = 0 To optControl.UBound
    If optControl(i).Value Then
       GetControl = i
       Exit Function
    End If
Next i
End Function

'�õ��ؼ������ַ���
Public Function sGetControl(i As Enum_Control) As String
       Select Case i
              Case Enum_Control.Enum_Control_List
                   sGetControl = "list"
              Case Enum_Control.Enum_Control_Only_Text
                   sGetControl = "only_text"
              Case Enum_Control.Enum_Control_FrameInput
                   sGetControl = "frameinput"
              Case Enum_Control.Enum_Control_DBGird
                   sGetControl = "dbgird"
       End Select
End Function

'�õ���ȫ����
Private Function GetPassLevel() As Enum_PassLevel
Dim i As Integer
    For i = 0 To optPassLevel.UBound
        If optPassLevel(i).Value Then
           GetPassLevel = i
           Exit Function
        End If
    Next i
End Function

'���������������������е�����
Private Sub AddIntoMainKey()
Dim i As Long
    cmbMainKey.Clear
    For i = 1 To UBound(tKeyVal)
        If Not boolStringInControl(cmbMainKey, tKeyVal(i).MainKey) Then
           cmbMainKey.AddItem tKeyVal(i).MainKey
        End If
    Next i
End Sub

'�ж����б�ؼ����Ƿ��Ѵ����ַ�
Private Function boolStringInControl(Object As ComboBox, sString As String) As Boolean
Dim i As Long
    For i = 0 To Object.ListCount - 1
        If sString = Object.List(i) Then
           boolStringInControl = True
           Exit Function
        End If
    Next i
    boolStringInControl = False
End Function

'----------------------------------------------------------------------------------------------------
'�ڶ��������ӿؼ�ȷ��tControl��tKyeValAdd
'----------------------------------------------------------------------------------------------------
'----------------------------------------------------------------------------------------------------
'�ڶ����е��Լ��ĺ���
'----------------------------------------------------------------------------------------------------
'�õ���ȫ����
Public Function GetPassLevel2() As Enum_PassLevel
        GetPassLevel2 = cmbKeyPassLevel.ListIndex
End Function

Public Function sGetPassLevel(i As Enum_PassLevel) As String
       Select Case i
              Case Enum_PassLevel.Enum_PassLevel_Null
                   sGetPassLevel = "��"
              Case Enum_PassLevel.Enum_passLevel_User
                   sGetPassLevel = "�û�����"
              Case Enum_PassLevel.Enum_PassLevel_Manager
                   sGetPassLevel = "������"
       End Select
End Function

'�õ�����ϵͳ
Public Function lGetOperistSystem() As Long
        Select Case cmbKeyOperistSystem.ListIndex
               Case 0 'WINDOWS95
                    lGetOperistSystem = 1
               Case 1 'WINDOWS98
                    lGetOperistSystem = 2
               Case 2 'WINDOWS2000
                    lGetOperistSystem = 4
               Case 3 'WINDOWS95 AND WINDOWS98
                    lGetOperistSystem = 3
               Case 4 'WINDOWS95 AND WINDOWS2000
                    lGetOperistSystem = 5
               Case 5 'WINDOWS98 AND WINDOWS2000
                    lGetOperistSystem = 6
               Case 6 'WINDOWS95 AND WINDOWS98 AND WINDOWS2000
                    lGetOperistSystem = 7
        End Select
End Function

Public Function sGetOperistSystem(i As Long) As String
Dim s As String, k As Long
k = 7
      If i And 1 Then s = "WINDOWS95"
      If i And 2 Then s = s & "��WINDOWS98"
      If i And 4 Then s = s & "��WINDOWS2000"
      If i And (Not k) Then s = s & "����������ϵͳ"
      If Left$(s, 1) = "��" Then
         sGetOperistSystem = Right$(s, Len(s) - 1)
      Else
         sGetOperistSystem = s
      End If
End Function

Private Function LetKeyVal() As Boolean
If cmbKeyRoot.Text <> "" And cmbMainKey.Text <> "" _
   And cmbSubKey <> "" Then
   ReDim Preserve tKeyVal(UBound(tKeyVal) + 1)
   With tKeyVal(UBound(tKeyVal)) '��tKeyVal�ṹ��ֵ
        .ControlText = txtKeyControlText.Text
        .KeyRoot = f_lChangeRootKey(cmbKeyRoot.Text)
        .KeyType = f_lChangeKeyType(cmbKeyType.Text)
        .KeyVal = cmbKeyVal.Text
        .MainKey = cmbMainKey.Text
        .OperistSystem = lGetOperistSystem
        .PassLevel = GetPassLevel2
        .Readme = txtKeyReadme.Text
        .SubKey = cmbSubKey.Text
   End With
   LetKeyVal = True
Else
   MsgBox "�������������Ӽ����б��븳ֵ", , Me.Caption
   LetKeyVal = False
End If
End Function

'�����ṹ����������
Private Sub AddToTypeStructe()
ReDim Preserve tTree(UBound(tTree) + 1)
      With tTree(UBound(tTree))
          .Ralation = NodeRalation
          .Key = NodeKey
          .Text = NodeText
          .Control = GetControl
          .PassLevel = GetPassLevel
          Select Case GetControl
          Case Enum_Control.Enum_Control_List
                 .StartPos = ControlStartpos
                 .EndPos = ControlEndPos
          Case Enum_Control.Enum_Control_Only_Text
          Case Enum_Control.Enum_Control_FrameInput
          Case Enum_Control.Enum_Control_DBGird
          End Select
       End With
End Sub
