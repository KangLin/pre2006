VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmOption 
   Caption         =   "Form1"
   ClientHeight    =   4305
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4305
   ScaleWidth      =   4680
   WindowState     =   2  'Maximized
   Begin VB.Frame FrmBrower 
      Height          =   975
      Left            =   2280
      TabIndex        =   8
      Top             =   2160
      Visible         =   0   'False
      Width           =   2415
      Begin VB.TextBox txtInput 
         Height          =   270
         Left            =   120
         TabIndex        =   2
         Text            =   "Text1"
         Top             =   240
         Width           =   2175
      End
      Begin VB.CommandButton cmdBrower 
         Caption         =   "���(&B)..."
         Height          =   255
         Left            =   1245
         TabIndex        =   3
         Top             =   600
         Width           =   1050
      End
   End
   Begin VB.ListBox lst 
      Height          =   270
      Left            =   2520
      Style           =   1  'Checkbox
      TabIndex        =   1
      Top             =   1800
      Visible         =   0   'False
      Width           =   2175
   End
   Begin VB.TextBox Txt 
      Height          =   1575
      Left            =   2520
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   7
      Text            =   "Form1.frx":0000
      Top             =   0
      Width           =   2175
   End
   Begin VB.CommandButton cmdApply 
      Caption         =   "Ӧ��"
      Height          =   255
      Left            =   3840
      TabIndex        =   6
      Top             =   3960
      Width           =   735
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "ȡ��"
      CausesValidation=   0   'False
      Height          =   255
      Left            =   2880
      TabIndex        =   5
      Top             =   3960
      Width           =   735
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "ȷ��"
      Height          =   255
      Left            =   1920
      TabIndex        =   4
      Top             =   3960
      Width           =   735
   End
   Begin MSComctlLib.TreeView Tree 
      Height          =   3135
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   2175
      _ExtentX        =   3836
      _ExtentY        =   5530
      _Version        =   393217
      LabelEdit       =   1
      Style           =   7
      Appearance      =   1
   End
End
Attribute VB_Name = "frmOption"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Const EWX_SHUTDOWN = 1
Private Const EWX_REBOOT = 2
Private Declare Function ExitWindowsEx Lib "user32" (ByVal uFlags As Long, ByVal dwReserved As Long) As Long
Const CD = "Control panel\Desktop"
Const NL = "NetWork\Logon"
Const SCCU = "System\CurrentControlset\Control\Update"
Const SMWCE = "Software\Microsoft\Windows\CurrentVersion\Explorer"
Const SMWCPE = "Software\Microsoft\Windows\CurrentVersion\Policies\Explorer"
Const SMWCPS = "Software\Microsoft\Windows\CurrentVersion\Policies\System"
Const SMWCPSW = SMWCPS & "\WinOldApp"
Const SMWCPN = "Software\Microsoft\Windows\CurrentVersion\Policies\Network"

Dim boolnoItemClick As Boolean '���ǵ���ItemClick(��������������)ʱΪTrue,�ǵ���ʱΪTrue
Dim iWindowsStyle As Integer   '�����ڵ�����

Public Sub InputWindowsStyle(WindowsStyle As Enum_WindowsStyle)
Dim Nodx As Node
Dim n As Long
       iWindowsStyle = WindowsStyle
       With Me
            Select Case iWindowsStyle
                   Case Windows_Desktop_Enum
                        .Caption = "����"
                   Case Windows_ControlPanel_Enum
                        .Caption = "�������"
                   Case Windows_Security_Enum
                        .Caption = "��ȫ"
            End Select
            SetTreeNode
       End With
End Sub

Private Sub cmdBrower_Click()
        With frmBrow
             .InputWindowCaption "���ͼƬ"
             .Show 1
        End With
End Sub

Private Sub cmdCancel_Click()
        Unload Me
End Sub

Private Sub cmdOk_Click()
Dim exi As Integer
        '�����޸�ע���Ĺ���
        ModifyKey
        exi = MsgBox("��Ҫ������,ʹ�޸ĵ�ֵ��Ч��" & Chr$(13) & _
                     "       Ҫ��������?", vbQuestion + _
                     vbYesNo, frmMain.Caption)
        If exi = vbYes Then
           ExitWindowsEx EWX_REBOOT Or EWX_SHUTDOWN, 0
        End If
End Sub

Private Sub Txt_KeyDown(KeyCode As Integer, Shift As Integer)
           KeyCode = 0
End Sub

Private Sub Txt_KeyPress(KeyAscii As Integer)
           KeyAscii = 0
End Sub

Private Sub Form_Resize() '������С
If Run Then On Error Resume Next
boolnoItemClick = True
        With Tree
             .Top = 0
             .Left = 0
             .Width = Me.ScaleWidth / 2 - 50
             .Height = Me.ScaleHeight - cmdOk.Height - 600
        End With
        With Txt
             .Top = 0
             .Left = Me.ScaleWidth / 2 + 50
             .Width = Me.ScaleWidth / 2
             If lst.Visible Then
                .Height = (Me.ScaleHeight - cmdOk.Height - 600) / 3
                lst.Left = .Left
                lst.Height = .Height * 2
                lst.Top = Tree.Height - lst.Height
                lst.Width = .Width
             ElseIf FrmBrower.Visible Then
                 .Height = Tree.Height - FrmBrower.Height
                 FrmBrower.Top = .Top + .Height
                 FrmBrower.Left = .Left
                 FrmBrower.Width = .Width - 100
                 txtInput.Width = FrmBrower.Width - 200
                 cmdBrower.Left = FrmBrower.Width - 300 - cmdBrower.Width
             Else
                .Height = Me.ScaleHeight - cmdOk.Height - 600
             End If
        End With
        cmdOk.Top = Tree.Height + 300
        cmdCancel.Top = cmdOk.Top
        cmdApply.Top = cmdOk.Top
        cmdOk.Left = Me.ScaleWidth - 1500 - cmdOk.Width - cmdCancel.Width - cmdApply.Height
        cmdCancel.Left = cmdOk.Left + cmdOk.Width + 300
        cmdApply.Left = cmdCancel.Left + cmdCancel.Width + 300
boolnoItemClick = False
End Sub

Private Sub Form_Load()
'��ʼ��
boolnoItemClick = True
Txt.Text = ""
txtInput.Text = ""
boolnoItemClick = False
End Sub

Private Sub SetTreeNode()
Dim Nodx As Node, i As Long
boolnoItemClick = True
With Tree
    .Nodes.Clear
    .Style = tvwTreelinesPlusMinusPictureText
    .LineStyle = tvwRootLines
    .ImageList = frmMain.Img
     Set Nodx = .Nodes.add(, , "mycomputer", "�ҵĵ���", "mycomputer")
     
     Set Nodx = .Nodes.add("mycomputer", tvwChild, "desktop", "����", "closedec")
     If iWindowsStyle = Windows_Desktop_Enum Then
        Tree.SelectedItem = Nodx
     End If
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
     If iWindowsStyle = Windows_Desktop_Enum Then
        Nodx.EnsureVisible
     End If
     '----------------------------------------------------------------------------------------------------------------------------
     Set Nodx = .Nodes.add("desktopstartmenu", tvwChild, "desktopstartmenumsdos", "MSDOS��ʽ", "closedec")

     Set Nodx = .Nodes.add("mycomputer", tvwChild, "controlpanel", "�������", "closedec")
     If iWindowsStyle = Windows_ControlPanel_Enum Then
        Tree.SelectedItem = Nodx
     End If
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelsystem", "ϵͳ", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpaneldisplay", "��ʾ��", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetwork", "����", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetworkhood", "�����ھ�", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetdial", "�κ�����", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelpassword", "����/����", "closedec")
     If iWindowsStyle = Windows_ControlPanel_Enum Then Nodx.EnsureVisible
     
     Set Nodx = .Nodes.add("mycomputer", tvwChild, "security", "��ȫ", "closedec")
     If iWindowsStyle = Windows_Security_Enum Then
        .SelectedItem = Nodx
     End If
     Set Nodx = .Nodes.add("security", tvwChild, "securitypassword", "����", "closedec")
     
     If iWindowsStyle = Windows_Security_Enum Then Nodx.EnsureVisible
     
     For i = 1 To UBound(tTree) '��������װ��
         With tTree(i)
              Set Nodx = Tree.Nodes.add(.Ralation, tvwChild, .Key, .Text, "closedec")
         End With
         Nodx.Tag = i
     Next i
     Tree_NodeClick .SelectedItem
End With
boolnoItemClick = False
End Sub

'�˺���������:
'���ݼ�ֵ���ÿؼ���״̬
Private Function SetKeyVal( _
     KeyRoot As Long, MainKey As String, _
     SubKey As String, Optional KeyType _
     As ENUM_REG_KEY_TYPE = REG_DWORD, _
     Optional bFlag As Boolean = False) As String
'����:
'KeyRoot����ֵ
'MainKey����
'SubKey�Ӽ�
'KeyType������
'bFlag���Ӽ����ֵ�෴ʱΪFalse,��ͬʱΪTrue

If Run Then On Error Resume Next
Dim vall As String, i As Long
With lst
     For i = 1 To UBound(Key)
         '��ֵ����Key��
         If SubKey = Key(i).SubKey _
            And MainKey = Key(i).MainKey _
            And KeyRoot = Key(i).KeyRoot Then
            '�������ͱ仯
            Select Case KeyType
                   Case REG_DWORD
                        If bFlag Then
                           .Selected(.ListCount - 1) = CBool(Key(i).KeyVal)
                        Else
                           .Selected(.ListCount - 1) = Not CBool(Key(i).KeyVal)
                        End If
                   Case REG_SZ
                        txtInput.Text = Key(i).KeyVal
            End Select
            Exit Function
          End If
      Next i
      '����Key��,ֱ�Ӵ�ע����ж�ȡ
      vall = GetKeyValue(KeyRoot, MainKey, SubKey)
      '�������ͱ仯
      Select Case KeyType
             Case REG_DWORD
                  If bFlag Then
                     .Selected(.ListCount - 1) = CBool(Val(vall))
                  Else
                     .Selected(.ListCount - 1) = Not CBool(Val(vall))
                  End If
             Case REG_SZ
                  txtInput.Text = vall
             End Select
       End With
End Function

Private Sub Tree_Collapse(ByVal Node As MSComctlLib.Node)
        If Node.Key <> "mycomputer" Then Node.Image = "closedec"
End Sub

Private Sub Tree_Expand(ByVal Node As MSComctlLib.Node)
        If Node.Key <> "mycomputer" Then Node.Image = "opendec"
End Sub

Private Sub Tree_NodeClick(ByVal Node As MSComctlLib.Node)
'��ʼ��
Dim i As Long
Txt.Text = ""
lst.Clear
lst.Tag = 0
lst.Visible = False
FrmBrower.Visible = False
boolnoItemClick = True

Select Case Node.Key
       Case "mycomputer" '�˴�ֻ��������
             With lst
                 .AddItem "��ʾ����������"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoDrives")
                 'һ һ ��ʾϵͳ������
                 GetDrive lst
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       '---------------------------------------------------------------------
       Case "desktop"
            With lst
                 .AddItem "����"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoDeskTop")
                 .AddItem "�˳�ϵͳʱ��������������"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoSaveSettings")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmenu"
            With lst
                 .AddItem "������"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoFind")
                 .AddItem "������"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoRun")
                 .AddItem "�ر�ϵͳ��"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoClose")
                 .AddItem "'��ʼ�˵�'�е����ļ���"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoStartMenuSubFolders")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmenuset"
            With lst
                 .AddItem "�ļ���ѡ��"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoSetFolders")
                 .AddItem "�������Ϳ�ʼ�˵�"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoSetTaskbar")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmenusetcontrolpanel", "controlpanel" '�������
            Txt.Text = "����:1.'ϵͳ'���� " + Chr(13) + Chr(10) + _
                       "     2.'��ʾ��'����" + Chr(13) + Chr(10) + _
                       "     3.'����'����" + Chr(13) + Chr(10) + _
                       "     4.'�����ھ�'����" + Chr(13) + Chr(10) + _
                       "     5.'�κ�����'����" + Chr(13) + Chr(10) + _
                       "     6.'����'����"
       Case "desktopstartmnuesetcontrolpanelsystem", "controlpanelsystem" '��������е�"ϵͳ"
            With lst
                 .AddItem "'ϵͳ'�����е�'�û������ļ�'ҳ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoProfilePage")
                 .AddItem "'ϵͳ'�����е�'�豸����'ҳ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDevMgrPage")
                 .AddItem "'ϵͳ'�����е�'Ӳ�������ļ�'ҳ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoConfigPage")
                 .AddItem "'ϵͳ'�����е�'����'ҳ�е�'�ļ�ϵͳ'��ť"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoFileSysPage")
                 .AddItem "'ϵͳ'�����е�'����'ҳ�е�'�����ڴ�'��ť"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoVirtMemPage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmnuesetcontrolpaneldisplay", "controlpaneldisplay" '��������е�"��ʾ��"
            With lst
                 .AddItem "'��ʾ��'����"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispCPL")
                 .AddItem "'��ʾ��'�����е�'����'��"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispBackgroundPage")
                 .AddItem "'��ʾ��'�����е�'��Ļ����'��"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispScrSavPage")
                 .AddItem "'��ʾ��'�����е�'���'��"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispAppearacePage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
      Case "desktopstartmnuesetcontrolpanelnetwork", "controlpanelnetwork"
            With lst
                 .AddItem "'����'����"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPN, "NoNetSetup")
                 .AddItem "'����'�����е�'��ʶ'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPN, "NoNetSetupIDPage")
                 .AddItem "'����'�����е�'���ʿ���'ҳ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPN, "NoNetSetupSecurityPage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmnuesetcontrolpanelnetdial", "controlpanelnetdial" '�κ�����
            With lst
                 .AddItem "��ֹ����"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "NoDialIn")
                 .AddItem "�����ļ�����"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "NoFileSharing")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
      Case "desktopstartmnuesetcontrolpanelnetworkhood", "controlpanelnetworkhood"
            With lst
                 .AddItem "'�����ھ�'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoNetHood")
                 .AddItem "'��������'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoEntioeNetwork")
                 .AddItem "'������Ŀ¼'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoWorkgroupContents")
            
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
      Case "desktopstartmnuesetcontrolpanelpassword", "controlpanelpassword"
            With lst
                 .AddItem "'����'����"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoSecCPL")
                 .AddItem "'����'�����е�'��������'ҳ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoPwdPage")
                 .AddItem "'Զ�̹���'ҳ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoAdminPage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
       Case "desktopstartmenumsdos" 'MSDOS��ʽ
            With lst
                 .AddItem "MSDOS��ʽ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPSW, "Disabled")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
       Case "desktopbackbamp"
            lst.Visible = False
            FrmBrower.Visible = True
            Txt.Text = "���汳��,���������뱳��ͼƬ��·���������"
            Call SetKeyVal(HKEY_CURRENT_USER, CD, "Wallpaper", REG_SZ)
                    
       Case "desktopother" '����
            With lst
                 .AddItem "��������"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoDriveTypeAutoRun")
                 .AddItem "�Զ�ˢ��"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SCCU, "UpdataMode", , True)
                 .AddItem "������'��ݷ�ʽ'�����Ŀ�ݷ�ʽ"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "Link")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
        '-----------------------------------------------------------------------------------
        Case "security" '��ȫ
            With lst
                 .AddItem "ʹ��ע���༭��"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "DisableRegistryTools")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
        Case "securitypassword" '����
            With lst
                 .AddItem "��¼ʱ������������"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, NL, "MustBevalidated", , True)
                 .AddItem "��ʾ�ϴε�¼���û���"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "DontDisplayLastUserName")
                 .AddItem "ʹ�ÿ����"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "DisablePwdCaching")
                 .AddItem "WINDOWS�������ʹ������"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "AlphanumPwds")
                 .AddItem "ʹ���Ǻ�(*)���ع������"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "HideSharePwds", , True)
                 
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
        
End Select
 '��������װ��
If Val(Node.Tag) > 0 Then
   With tTree(Val(Node.Tag))
        '�������뼶���ж�
        Select Case .Control
               Case Enum_Control.Enum_Control_List
                    With lst
                         '�ӿؼ�������
                         For i = tTree(Val(Node.Tag)).StartPos + 1 To tTree(Val(Node.Tag)).EndPos
                             .AddItem tKeyVal(i).ControlText
                         Next i
                         '������tTree(lst.Tag)�е�StartPos��EndPosȷ���ؼ��ļ�ֵ
                         .Tag = Val(Node.Tag)
                         .ListIndex = 0
                         lst_Click
                         .Visible = True
                    End With
               Case Enum_Control.Enum_Control_FrameInput
               
               Case Enum_Control.Enum_Control_DBGird
               
               Case Enum_Control.Enum_Control_Only_Text
                    '�˴���Ҫ��ֵ
        End Select
   End With
End If
Form_Resize
boolnoItemClick = False
End Sub

Private Sub lst_Click()
If Tree.SelectedItem.Text = "�ҵĵ���" Then
   Txt.Text = "�ҵĵ����е�" & Right$(lst.List(lst.ListIndex), Len(lst.List(lst.ListIndex)) - 2)
End If
Select Case lst.List(lst.ListIndex)
       Case "��ʾ����������"
            Txt.Text = "��ʾ�ҵĵ����е�����������"
       Case "����"
            Txt.Text = "����"
       Case "�˳�ϵͳʱ��������������"
            Txt.Text = "�˳�ϵͳʱ��������������"
       Case "MSDOS��ʽ"
            Txt.Text = "MSDOS��ʽ"
       Case "�ļ���ѡ��"
            Txt.Text = "'��ʼ�˵�'�е�'����\�ļ���ѡ��'��"
       Case "�������Ϳ�ʼ�˵�"
            Txt.Text = "'��ʼ�˵�'�е�'�������Ϳ�ʼ�˵�'��"
       Case "������"
            Txt.Text = "'��ʼ�˵�'�е�'����'��"
       Case "������"
            Txt.Text = "'��ʼ�˵�'�е�'����'��"
       Case "�ر�ϵͳ��"
            Txt.Text = "��ʼ�˵�'�е�'�ر�'��"
       Case "'��ʼ�˵�'�е����ļ���"
            Txt.Text = "'��ʼ�˵�'�е����ļ���"
       '---------------------------------------------------------------------------------
       Case "'ϵͳ'�����е�'�û������ļ�'ҳ"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'ϵͳ'�����е�'�û������ļ�'ҳ"
       Case "'ϵͳ'�����е�'�豸����'ҳ"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'ϵͳ'�����е�'�豸����'ҳ"
       Case "'ϵͳ'�����е�'Ӳ�������ļ�'ҳ"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'ϵͳ'�����е�'Ӳ�������ļ�'ҳ"
       Case "'ϵͳ'�����е�'����'ҳ�е�'�ļ�ϵͳ'��ť"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'ϵͳ'�����е�'����'ҳ�е�'�ļ�ϵͳ'��ť"
       Case "'ϵͳ'�����е�'����'ҳ�е�'�����ڴ�'��ť"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'ϵͳ'�����е�'����'ҳ�е�'�����ڴ�'��ť"
       '---------------------------------------------------------------------------------
       Case "'��ʾ��'����"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'��ʾ��'����"
       Case "'��ʾ��'�����е�'����'��"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'��ʾ��'�����е�'����'ҳ"
       Case "'��ʾ��'�����е�'��Ļ����'��"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'��ʾ��'�����е�'��Ļ����'ҳ"
       Case "'��ʾ��'�����е�'���'��"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'��ʾ��'�����е�'���'ҳ"
       '--------------------------------------------------------------------------------------
       Case "'����'����"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'����'����"
       Case "'����'�����е�'��ʶ'"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'����'�����е�'��ʶ'ҳ"
       Case "'����'�����е�'���ʿ���'ҳ"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'����'�����е�'���ʿ���'ҳ"
       '----------------------------------------------------------------------------------
       Case "'�����ھ�'"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'�����ھ�'"
       Case "'��������'"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'�����ھ�'�е�'��������'"
       Case "'������Ŀ¼'"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'�����ھ�'�е�'������Ŀ¼'"
       '---------------------------------------------------------------------------------
       Case "��ֹ����"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'�κ�����'�е�'��ֹ����'"
       Case "�����ļ�����"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'�κ�����'�е�'�����ļ�����'"
       '---------------------------------------------------------------------------------
       Case "'����'����"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'����/����'����"
       Case "'����'�����е�'��������'ҳ"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'����/����'�����е�'��������'ҳ"
       Case "'Զ�̹���'ҳ"
            Txt.Text = "��ʼ�˵�'�е�'����'���еĿ�������е�'Զ�̹���'ҳ"
       '---------------------------------------------------------------------------------
       Case "��������"
            Txt.Text = "����������ָ�ѹ��̷������,�����ϵ������г����Զ�����"
       Case "�Զ�ˢ��"
            Txt.Text = "ϵͳ�Զ�ˢ��"
       Case "������'��ݷ�ʽ'�����Ŀ�ݷ�ʽ"
            Txt.Text = "������'��ݷ�ʽ'�����Ŀ�ݷ�ʽ"
       '---------------------------------------------------------------------------------
       Case "ʹ��ע���༭��"
            Txt.Text = "ʹ��ע���༭��"
       Case "��¼ʱ������������"
            Txt.Text = "�ڵ�¼ʱ������������"
       Case "��ʾ�ϴε�¼���û���"
            Txt.Text = "�ڵ�¼ʱ��ʾ�ϴε�¼���û���"
       Case "ʹ�ÿ����"
            Txt.Text = "ʹ�ÿ����.ע��:�����Ļ�,�û��ɲ������뼴�ɵ�¼"
       Case "WINDOWS�������ʹ������"
            Txt.Text = "WINDOWS�������ʹ������"
       Case "ʹ���Ǻ�(*)���ع������"
            Txt.Text = "ʹ���Ǻ�(*)���ع������"
              
End Select
If Val(lst.Tag) <> 0 Then
   Txt.Text = tKeyVal(tTree(Val(lst.Tag)).StartPos + lst.ListIndex + 1).Readme
End If
End Sub

 '��Ҫ�޸ĵ�ֵ���뵽����KEY��
Private Sub lst_ItemCheck(Item As Integer)
If Not boolnoItemClick Then
If Tree.SelectedItem.Text = "�ҵĵ���" And lst.List(Item) <> "��ʾ����������" Then
   AddToSameKey HKEY_CURRENT_USER, "NoDrives", SMWCPE, Not (lst.Selected(lst.ListIndex)), , lst.List(lst.ListIndex)
End If
Select Case lst.List(Item)
       Case "��ʾ����������"
             AddToKey HKEY_CURRENT_USER, "NoDrives", SMWCPE, (Not lst.Selected(lst.ListIndex)), REG_DWORD, "��ʾ����������"
       Case "����"
             AddToKey HKEY_CURRENT_USER, "NoDeskTop", SMWCPE, (Not lst.Selected(lst.ListIndex)), , "����"
       Case "�˳�ϵͳʱ��������������"
             AddToKey HKEY_CURRENT_USER, "NoSaveSettings", SMWCPE, (Not lst.Selected(lst.ListIndex)), , "�˳�ϵͳʱ��������������"
       Case "MSDOS��ʽ"
             AddToKey HKEY_CURRENT_USER, "disabled", SMWCPSW, (Not lst.Selected(lst.ListIndex)), , "MSDOS��ʽ"
       Case "�ļ���ѡ��"
            AddToKey HKEY_CURRENT_USER, "NoSetFolders", SMWCPE, Not lst.Selected(lst.ListIndex), , "�ļ���ѡ��"
       Case "�������Ϳ�ʼ�˵�"
            AddToKey HKEY_CURRENT_USER, "NoSetTaskbar", SMWCPE, Not lst.Selected(lst.ListIndex), , "�������Ϳ�ʼ�˵�"
       Case "������"
            AddToKey HKEY_CURRENT_USER, "NoFind", SMWCPE, Not lst.Selected(lst.ListIndex), , "������"
       Case "������"
            AddToKey HKEY_CURRENT_USER, "NoRun", SMWCPE, Not lst.Selected(lst.ListIndex), , "������"
       Case "�ر�ϵͳ��"
            AddToKey HKEY_CURRENT_USER, "NoClose", SMWCPE, Not lst.Selected(lst.ListIndex), , "�ر�ϵͳ��"
       Case "'��ʼ�˵�'�е����ļ���"
            AddToKey HKEY_CURRENT_USER, "NoStartMenuSubFolders", SMWCPE, Not lst.Selected(lst.ListIndex), , "'��ʼ�˵�'�е����ļ���"
       '-------------------------------------------------------------------------------------------------
       Case "'ϵͳ'�����е�'�û������ļ�'ҳ"
            AddToKey HKEY_CURRENT_USER, "NoProfilePage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'ϵͳ'�����е�'�û������ļ�'ҳ"
       Case "'ϵͳ'�����е�'�豸����'ҳ"
            AddToKey HKEY_CURRENT_USER, "NoDevMgrPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'ϵͳ'�����е�'�豸����'ҳ"
       Case "'ϵͳ'�����е�'Ӳ�������ļ�'ҳ"
            AddToKey HKEY_CURRENT_USER, "NoConfigPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'ϵͳ'�����е�'Ӳ�������ļ�'ҳ"
       Case "'ϵͳ'�����е�'����'ҳ�е�'�ļ�ϵͳ'��ť"
            AddToKey HKEY_CURRENT_USER, "NoFileSysPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'ϵͳ'�����е�'����'ҳ�е�'�ļ�ϵͳ'��ť"
       Case "'ϵͳ'�����е�'����'ҳ�е�'�����ڴ�'��ť"
            AddToKey HKEY_CURRENT_USER, "NoVirtMemPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'ϵͳ'�����е�'����'ҳ�е�'�����ڴ�'��ť"
       '-------------------------------------------------------------------------------------------------
       Case "'��ʾ��'����"
            AddToKey HKEY_CURRENT_USER, "NoDispCPL", SMWCPS, Not lst.Selected(lst.ListIndex), , "'��ʾ��'����"
       Case "'��ʾ��'�����е�'����'��"
            AddToKey HKEY_CURRENT_USER, "NoDispBackgroundPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'��ʾ��'�����е�'����'��"
       Case "'��ʾ��'�����е�'��Ļ����'��"
            AddToKey HKEY_CURRENT_USER, "NoDispScrSavPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'��ʾ��'�����е�'��Ļ����'��"
       Case "'��ʾ��'�����е�'���'��"
            AddToKey HKEY_CURRENT_USER, "NoDispAppearancePage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'��ʾ��'�����е�'���'��"
       '--------------------------------------------------------------------------------------
       Case "'����'����"
            AddToKey HKEY_CURRENT_USER, "NoNetSetup", SMWCPN, Not lst.Selected(lst.ListIndex), , "'����'����"
       Case "'����'�����е�'��ʶ'"
            AddToKey HKEY_CURRENT_USER, "NoNetSetupIDPage", SMWCPN, Not lst.Selected(lst.ListIndex), , "'����'�����е�'��ʶ'"
       Case "'����'�����е�'���ʿ���'ҳ"
            AddToKey HKEY_CURRENT_USER, "NoNetSetupSecurityPage", SMWCPN, Not lst.Selected(lst.ListIndex), , "'����'�����е�'���ʿ���'ҳ"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "��ֹ����"
            AddToKey HKEY_LOCAL_MACHINE, "NoDialIn", SMWCPN, Not lst.Selected(lst.ListIndex), , "��ֹ����"
       Case "�����ļ�����"
            AddToKey HKEY_LOCAL_MACHINE, "NoFileSharing", SMWCPN, Not lst.Selected(lst.ListIndex), , "�����ļ�����"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "'�����ھ�'"
            AddToKey HKEY_CURRENT_USER, "NoNetHood", SMWCPE, Not lst.Selected(lst.ListIndex), , "'�����ھ�'"
       Case "'��������'"
            AddToKey HKEY_CURRENT_USER, "NoEntioeNetwork", SMWCPE, Not lst.Selected(lst.ListIndex), , "'��������'"
       Case "'������Ŀ¼'"
            AddToKey HKEY_CURRENT_USER, "NoWorkgroupContents", SMWCPE, Not lst.Selected(lst.ListIndex), , "'������Ŀ¼'"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "'����'����"
            AddToKey HKEY_CURRENT_USER, "NoSecCPL", SMWCPS, Not lst.Selected(lst.ListIndex), , "'����'����"
       Case "'����'�����е�'��������'ҳ"
            AddToKey HKEY_CURRENT_USER, "NoPwdPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'����'�����е�'��������'ҳ"
       Case "'Զ�̹���'ҳ"
            AddToKey HKEY_CURRENT_USER, "NoAdminPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'Զ�̹���'ҳ"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "��������"
            AddToKey HKEY_CURRENT_USER, "NoDriveTypeAutoRun", SMWCPE, Not lst.Selected(lst.ListIndex), , "��������"
       Case "�Զ�ˢ��"
            AddToKey HKEY_LOCAL_MACHINE, "UpdataMode", SCCU, lst.Selected(lst.ListIndex), , "�Զ�ˢ��"
       Case "������'��ݷ�ʽ'�����Ŀ�ݷ�ʽ"
            AddToKey HKEY_CURRENT_USER, "Link", SMWCPE, Not lst.Selected(lst.ListIndex), , "������'��ݷ�ʽ'�����Ŀ�ݷ�ʽ"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "ʹ��ע���༭��"
             If PassWord(Enum_PassStyle_Regedit) Then
                AddToKey HKEY_CURRENT_USER, "DisableRegistryTools", SMWCPS, Not lst.Selected(lst.ListIndex), , "ʹ��ע���༭��"
             End If
       Case "��¼ʱ������������"
            AddToKey HKEY_LOCAL_MACHINE, "MustBevalidated", NL, lst.Selected(lst.ListIndex), , "��¼ʱ������������"
       Case "��ʾ�ϴε�¼���û���"
            AddToKey HKEY_LOCAL_MACHINE, "DontDisplayLastUserName", SMWCPN, Not lst.Selected(lst.ListIndex), , "��ʾ�ϴε�¼���û���"
       Case "ʹ�ÿ����"
            AddToKey HKEY_LOCAL_MACHINE, "DisablePwdCaching", SMWCPN, Not lst.Selected(lst.ListIndex), , "ʹ�ÿ����"
       Case "WINDOWS�������ʹ������"
            AddToKey HKEY_LOCAL_MACHINE, "AlphanumPwds", SMWCPN, Not lst.Selected(lst.ListIndex), , "WINDOWS�������ʹ������"
       Case "ʹ���Ǻ�(*)���ع������"
            AddToKey HKEY_LOCAL_MACHINE, "HideSharePwds", SMWCPN, lst.Selected(lst.ListIndex), , "ʹ���Ǻ�(*)���ع������"
              
End Select
End If
End Sub


Private Sub txtInput_Change()
If Not boolnoItemClick Then
   If frmBrow.Caption = "���ͼƬ" Then
      AddToKey HKEY_CURRENT_USER, "Wallpaper", CD, txtInput.Text, REG_SZ, "ͼ��"
   End If
End If
End Sub
