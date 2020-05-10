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
         Caption         =   "浏览(&B)..."
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
      Caption         =   "应用"
      Height          =   255
      Left            =   3840
      TabIndex        =   6
      Top             =   3960
      Width           =   735
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "取消"
      CausesValidation=   0   'False
      Height          =   255
      Left            =   2880
      TabIndex        =   5
      Top             =   3960
      Width           =   735
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "确定"
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

Dim boolnoItemClick As Boolean '不是单击ItemClick(即从其它处调用)时为True,是单击时为True
Dim iWindowsStyle As Integer   '本窗口的类型

Public Sub InputWindowsStyle(WindowsStyle As Enum_WindowsStyle)
Dim Nodx As Node
Dim n As Long
       iWindowsStyle = WindowsStyle
       With Me
            Select Case iWindowsStyle
                   Case Windows_Desktop_Enum
                        .Caption = "桌面"
                   Case Windows_ControlPanel_Enum
                        .Caption = "控制面板"
                   Case Windows_Security_Enum
                        .Caption = "安全"
            End Select
            SetTreeNode
       End With
End Sub

Private Sub cmdBrower_Click()
        With frmBrow
             .InputWindowCaption "浏览图片"
             .Show 1
        End With
End Sub

Private Sub cmdCancel_Click()
        Unload Me
End Sub

Private Sub cmdOk_Click()
Dim exi As Integer
        '加入修改注册表的过程
        ModifyKey
        exi = MsgBox("需要重新起动,使修改的值生效。" & Chr$(13) & _
                     "       要重新起动吗?", vbQuestion + _
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

Private Sub Form_Resize() '调整大小
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
'初始化
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
     Set Nodx = .Nodes.add(, , "mycomputer", "我的电脑", "mycomputer")
     
     Set Nodx = .Nodes.add("mycomputer", tvwChild, "desktop", "桌面", "closedec")
     If iWindowsStyle = Windows_Desktop_Enum Then
        Tree.SelectedItem = Nodx
     End If
     Set Nodx = .Nodes.add("desktop", tvwChild, "desktopstartmenu", "开始菜单", "closedec")
     Set Nodx = .Nodes.add("desktop", tvwChild, "desktopbackbamp", "桌面背景", "closedec")
     Set Nodx = .Nodes.add("desktop", tvwChild, "desktopother", "其它", "closedec")
     
     Set Nodx = .Nodes.add("desktopstartmenu", tvwChild, "desktopstartmenuset", "设置", "closedec")
     '---------------------------------------------------------------------------------------------------------------------------
     Set Nodx = .Nodes.add("desktopstartmenuset", tvwChild, "desktopstartmenusetcontrolpanel", "控制面板", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelsystem", "系统", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpaneldisplay", "显示器", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelnetwork", "网络", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelnetworkhood", "网络邻居", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelnetdial", "拔号网络", "closedec")
     Set Nodx = .Nodes.add("desktopstartmenusetcontrolpanel", tvwChild, "desktopstartmnuesetcontrolpanelpassword", "密码/口令", "closedec")
     If iWindowsStyle = Windows_Desktop_Enum Then
        Nodx.EnsureVisible
     End If
     '----------------------------------------------------------------------------------------------------------------------------
     Set Nodx = .Nodes.add("desktopstartmenu", tvwChild, "desktopstartmenumsdos", "MSDOS方式", "closedec")

     Set Nodx = .Nodes.add("mycomputer", tvwChild, "controlpanel", "控制面板", "closedec")
     If iWindowsStyle = Windows_ControlPanel_Enum Then
        Tree.SelectedItem = Nodx
     End If
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelsystem", "系统", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpaneldisplay", "显示器", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetwork", "网络", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetworkhood", "网络邻居", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelnetdial", "拔号网络", "closedec")
     Set Nodx = .Nodes.add("controlpanel", tvwChild, "controlpanelpassword", "密码/口令", "closedec")
     If iWindowsStyle = Windows_ControlPanel_Enum Then Nodx.EnsureVisible
     
     Set Nodx = .Nodes.add("mycomputer", tvwChild, "security", "安全", "closedec")
     If iWindowsStyle = Windows_Security_Enum Then
        .SelectedItem = Nodx
     End If
     Set Nodx = .Nodes.add("security", tvwChild, "securitypassword", "口令", "closedec")
     
     If iWindowsStyle = Windows_Security_Enum Then Nodx.EnsureVisible
     
     For i = 1 To UBound(tTree) '从数组中装载
         With tTree(i)
              Set Nodx = Tree.Nodes.add(.Ralation, tvwChild, .Key, .Text, "closedec")
         End With
         Nodx.Tag = i
     Next i
     Tree_NodeClick .SelectedItem
End With
boolnoItemClick = False
End Sub

'此函数的作用:
'根据键值设置控件的状态
Private Function SetKeyVal( _
     KeyRoot As Long, MainKey As String, _
     SubKey As String, Optional KeyType _
     As ENUM_REG_KEY_TYPE = REG_DWORD, _
     Optional bFlag As Boolean = False) As String
'参数:
'KeyRoot根键值
'MainKey主键
'SubKey子键
'KeyType键类型
'bFlag当子键与键值相反时为False,相同时为True

If Run Then On Error Resume Next
Dim vall As String, i As Long
With lst
     For i = 1 To UBound(Key)
         '健值已在Key内
         If SubKey = Key(i).SubKey _
            And MainKey = Key(i).MainKey _
            And KeyRoot = Key(i).KeyRoot Then
            '根据类型变化
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
      '不在Key内,直接从注册表中读取
      vall = GetKeyValue(KeyRoot, MainKey, SubKey)
      '根据类型变化
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
'初始化
Dim i As Long
Txt.Text = ""
lst.Clear
lst.Tag = 0
lst.Visible = False
FrmBrower.Visible = False
boolnoItemClick = True

Select Case Node.Key
       Case "mycomputer" '此处只加驱动器
             With lst
                 .AddItem "显示所有驱动器"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoDrives")
                 '一 一 显示系统驱动器
                 GetDrive lst
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       '---------------------------------------------------------------------
       Case "desktop"
            With lst
                 .AddItem "桌面"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoDeskTop")
                 .AddItem "退出系统时保存所作的设置"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoSaveSettings")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmenu"
            With lst
                 .AddItem "查找项"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoFind")
                 .AddItem "运行项"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoRun")
                 .AddItem "关闭系统项"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoClose")
                 .AddItem "'开始菜单'中的子文件夹"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoStartMenuSubFolders")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmenuset"
            With lst
                 .AddItem "文件夹选项"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoSetFolders")
                 .AddItem "任务栏和开始菜单"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoSetTaskbar")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmenusetcontrolpanel", "controlpanel" '控制面板
            Txt.Text = "包括:1.'系统'属性 " + Chr(13) + Chr(10) + _
                       "     2.'显示器'属性" + Chr(13) + Chr(10) + _
                       "     3.'网络'属性" + Chr(13) + Chr(10) + _
                       "     4.'网络邻居'属性" + Chr(13) + Chr(10) + _
                       "     5.'拔号网络'属性" + Chr(13) + Chr(10) + _
                       "     6.'密码'属性"
       Case "desktopstartmnuesetcontrolpanelsystem", "controlpanelsystem" '控制面板中的"系统"
            With lst
                 .AddItem "'系统'属性中的'用户配置文件'页"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoProfilePage")
                 .AddItem "'系统'属性中的'设备管理'页"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDevMgrPage")
                 .AddItem "'系统'属性中的'硬件配置文件'页"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoConfigPage")
                 .AddItem "'系统'属性中的'性能'页中的'文件系统'按钮"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoFileSysPage")
                 .AddItem "'系统'属性中的'性能'页中的'虚拟内存'按钮"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoVirtMemPage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmnuesetcontrolpaneldisplay", "controlpaneldisplay" '控制面板中的"显示器"
            With lst
                 .AddItem "'显示器'属性"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispCPL")
                 .AddItem "'显示器'属性中的'背景'项"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispBackgroundPage")
                 .AddItem "'显示器'属性中的'屏幕保护'项"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispScrSavPage")
                 .AddItem "'显示器'属性中的'外观'项"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoDispAppearacePage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
      Case "desktopstartmnuesetcontrolpanelnetwork", "controlpanelnetwork"
            With lst
                 .AddItem "'网络'属性"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPN, "NoNetSetup")
                 .AddItem "'网络'属性中的'标识'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPN, "NoNetSetupIDPage")
                 .AddItem "'网络'属性中的'访问控制'页"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPN, "NoNetSetupSecurityPage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
       Case "desktopstartmnuesetcontrolpanelnetdial", "controlpanelnetdial" '拔号网络
            With lst
                 .AddItem "禁止拔入"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "NoDialIn")
                 .AddItem "禁用文件共享"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "NoFileSharing")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
      Case "desktopstartmnuesetcontrolpanelnetworkhood", "controlpanelnetworkhood"
            With lst
                 .AddItem "'网络邻居'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoNetHood")
                 .AddItem "'整个网络'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoEntioeNetwork")
                 .AddItem "'工作组目录'"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoWorkgroupContents")
            
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
      Case "desktopstartmnuesetcontrolpanelpassword", "controlpanelpassword"
            With lst
                 .AddItem "'密码'属性"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoSecCPL")
                 .AddItem "'密码'属性中的'更改密码'页"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoPwdPage")
                 .AddItem "'远程管理'页"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "NoAdminPage")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
       Case "desktopstartmenumsdos" 'MSDOS方式
            With lst
                 .AddItem "MSDOS方式"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPSW, "Disabled")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
       Case "desktopbackbamp"
            lst.Visible = False
            FrmBrower.Visible = True
            Txt.Text = "桌面背景,在下面填入背景图片的路径或点击浏览"
            Call SetKeyVal(HKEY_CURRENT_USER, CD, "Wallpaper", REG_SZ)
                    
       Case "desktopother" '其它
            With lst
                 .AddItem "光盘自起动"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "NoDriveTypeAutoRun")
                 .AddItem "自动刷新"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SCCU, "UpdataMode", , True)
                 .AddItem "创建有'快捷方式'字样的快捷方式"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPE, "Link")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
            
        '-----------------------------------------------------------------------------------
        Case "security" '安全
            With lst
                 .AddItem "使用注册表编辑器"
                 Call SetKeyVal(HKEY_CURRENT_USER, SMWCPS, "DisableRegistryTools")
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
        Case "securitypassword" '口令
            With lst
                 .AddItem "登录时必须输入密码"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, NL, "MustBevalidated", , True)
                 .AddItem "显示上次登录的用户名"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "DontDisplayLastUserName")
                 .AddItem "使用口令缓存"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "DisablePwdCaching")
                 .AddItem "WINDOWS口令必须使用数字"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "AlphanumPwds")
                 .AddItem "使用星号(*)隐藏共享口令"
                 Call SetKeyVal(HKEY_LOCAL_MACHINE, SMWCPN, "HideSharePwds", , True)
                 
                 .ListIndex = 0
                 lst_Click
                 .Visible = True
            End With
        
End Select
 '从数组中装载
If Val(Node.Tag) > 0 Then
   With tTree(Val(Node.Tag))
        '增加密码级别判断
        Select Case .Control
               Case Enum_Control.Enum_Control_List
                    With lst
                         '加控件的内容
                         For i = tTree(Val(Node.Tag)).StartPos + 1 To tTree(Val(Node.Tag)).EndPos
                             .AddItem tKeyVal(i).ControlText
                         Next i
                         '从数组tTree(lst.Tag)中的StartPos和EndPos确定控件的键值
                         .Tag = Val(Node.Tag)
                         .ListIndex = 0
                         lst_Click
                         .Visible = True
                    End With
               Case Enum_Control.Enum_Control_FrameInput
               
               Case Enum_Control.Enum_Control_DBGird
               
               Case Enum_Control.Enum_Control_Only_Text
                    '此处不要赋值
        End Select
   End With
End If
Form_Resize
boolnoItemClick = False
End Sub

Private Sub lst_Click()
If Tree.SelectedItem.Text = "我的电脑" Then
   Txt.Text = "我的电脑中的" & Right$(lst.List(lst.ListIndex), Len(lst.List(lst.ListIndex)) - 2)
End If
Select Case lst.List(lst.ListIndex)
       Case "显示所有驱动器"
            Txt.Text = "显示我的电脑中的所有驱动器"
       Case "桌面"
            Txt.Text = "桌面"
       Case "退出系统时保存所作的设置"
            Txt.Text = "退出系统时保存所作的设置"
       Case "MSDOS方式"
            Txt.Text = "MSDOS方式"
       Case "文件夹选项"
            Txt.Text = "'开始菜单'中的'设置\文件夹选项'项"
       Case "任务栏和开始菜单"
            Txt.Text = "'开始菜单'中的'任务栏和开始菜单'项"
       Case "查找项"
            Txt.Text = "'开始菜单'中的'查找'项"
       Case "运行项"
            Txt.Text = "'开始菜单'中的'运行'项"
       Case "关闭系统项"
            Txt.Text = "开始菜单'中的'关闭'项"
       Case "'开始菜单'中的子文件夹"
            Txt.Text = "'开始菜单'中的子文件夹"
       '---------------------------------------------------------------------------------
       Case "'系统'属性中的'用户配置文件'页"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'系统'属性中的'用户配置文件'页"
       Case "'系统'属性中的'设备管理'页"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'系统'属性中的'设备管理'页"
       Case "'系统'属性中的'硬件配置文件'页"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'系统'属性中的'硬件配置文件'页"
       Case "'系统'属性中的'性能'页中的'文件系统'按钮"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'系统'属性中的'性能'页中的'文件系统'按钮"
       Case "'系统'属性中的'性能'页中的'虚拟内存'按钮"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'系统'属性中的'性能'页中的'虚拟内存'按钮"
       '---------------------------------------------------------------------------------
       Case "'显示器'属性"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'显示器'属性"
       Case "'显示器'属性中的'背景'项"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'显示器'属性中的'背景'页"
       Case "'显示器'属性中的'屏幕保护'项"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'显示器'属性中的'屏幕保护'页"
       Case "'显示器'属性中的'外观'项"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'显示器'属性中的'外观'页"
       '--------------------------------------------------------------------------------------
       Case "'网络'属性"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'网络'属性"
       Case "'网络'属性中的'标识'"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'网络'属性中的'标识'页"
       Case "'网络'属性中的'访问控制'页"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'网络'属性中的'访问控制'页"
       '----------------------------------------------------------------------------------
       Case "'网络邻居'"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'网络邻居'"
       Case "'整个网络'"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'网络邻居'中的'整个网络'"
       Case "'工作组目录'"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'网络邻居'中的'工作组目录'"
       '---------------------------------------------------------------------------------
       Case "禁止拔入"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'拔号网络'中的'禁止拔入'"
       Case "禁用文件共享"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'拔号网络'中的'禁用文件共享'"
       '---------------------------------------------------------------------------------
       Case "'密码'属性"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'密码/口令'属性"
       Case "'密码'属性中的'更改密码'页"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'密码/口令'属性中的'更改密码'页"
       Case "'远程管理'页"
            Txt.Text = "开始菜单'中的'设置'项中的控制面板中的'远程管理'页"
       '---------------------------------------------------------------------------------
       Case "光盘自起动"
            Txt.Text = "光盘自起动是指把光盘放入光驱,光盘上的自运行程序自动运行"
       Case "自动刷新"
            Txt.Text = "系统自动刷新"
       Case "创建有'快捷方式'字样的快捷方式"
            Txt.Text = "创建有'快捷方式'字样的快捷方式"
       '---------------------------------------------------------------------------------
       Case "使用注册表编辑器"
            Txt.Text = "使用注册表编辑器"
       Case "登录时必须输入密码"
            Txt.Text = "在登录时必须输入密码"
       Case "显示上次登录的用户名"
            Txt.Text = "在登录时显示上次登录的用户名"
       Case "使用口令缓存"
            Txt.Text = "使用口令缓存.注意:这样的话,用户可不用密码即可登录"
       Case "WINDOWS口令必须使用数字"
            Txt.Text = "WINDOWS口令必须使用数字"
       Case "使用星号(*)隐藏共享口令"
            Txt.Text = "使用星号(*)隐藏共享口令"
              
End Select
If Val(lst.Tag) <> 0 Then
   Txt.Text = tKeyVal(tTree(Val(lst.Tag)).StartPos + lst.ListIndex + 1).Readme
End If
End Sub

 '把要修改的值加入到数组KEY中
Private Sub lst_ItemCheck(Item As Integer)
If Not boolnoItemClick Then
If Tree.SelectedItem.Text = "我的电脑" And lst.List(Item) <> "显示所有驱动器" Then
   AddToSameKey HKEY_CURRENT_USER, "NoDrives", SMWCPE, Not (lst.Selected(lst.ListIndex)), , lst.List(lst.ListIndex)
End If
Select Case lst.List(Item)
       Case "显示所有驱动器"
             AddToKey HKEY_CURRENT_USER, "NoDrives", SMWCPE, (Not lst.Selected(lst.ListIndex)), REG_DWORD, "显示所有驱动器"
       Case "桌面"
             AddToKey HKEY_CURRENT_USER, "NoDeskTop", SMWCPE, (Not lst.Selected(lst.ListIndex)), , "桌面"
       Case "退出系统时保存所作的设置"
             AddToKey HKEY_CURRENT_USER, "NoSaveSettings", SMWCPE, (Not lst.Selected(lst.ListIndex)), , "退出系统时保存所作的设置"
       Case "MSDOS方式"
             AddToKey HKEY_CURRENT_USER, "disabled", SMWCPSW, (Not lst.Selected(lst.ListIndex)), , "MSDOS方式"
       Case "文件夹选项"
            AddToKey HKEY_CURRENT_USER, "NoSetFolders", SMWCPE, Not lst.Selected(lst.ListIndex), , "文件夹选项"
       Case "任务栏和开始菜单"
            AddToKey HKEY_CURRENT_USER, "NoSetTaskbar", SMWCPE, Not lst.Selected(lst.ListIndex), , "任务栏和开始菜单"
       Case "查找项"
            AddToKey HKEY_CURRENT_USER, "NoFind", SMWCPE, Not lst.Selected(lst.ListIndex), , "查找项"
       Case "运行项"
            AddToKey HKEY_CURRENT_USER, "NoRun", SMWCPE, Not lst.Selected(lst.ListIndex), , "运行项"
       Case "关闭系统项"
            AddToKey HKEY_CURRENT_USER, "NoClose", SMWCPE, Not lst.Selected(lst.ListIndex), , "关闭系统项"
       Case "'开始菜单'中的子文件夹"
            AddToKey HKEY_CURRENT_USER, "NoStartMenuSubFolders", SMWCPE, Not lst.Selected(lst.ListIndex), , "'开始菜单'中的子文件夹"
       '-------------------------------------------------------------------------------------------------
       Case "'系统'属性中的'用户配置文件'页"
            AddToKey HKEY_CURRENT_USER, "NoProfilePage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'系统'属性中的'用户配置文件'页"
       Case "'系统'属性中的'设备管理'页"
            AddToKey HKEY_CURRENT_USER, "NoDevMgrPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'系统'属性中的'设备管理'页"
       Case "'系统'属性中的'硬件配置文件'页"
            AddToKey HKEY_CURRENT_USER, "NoConfigPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'系统'属性中的'硬件配置文件'页"
       Case "'系统'属性中的'性能'页中的'文件系统'按钮"
            AddToKey HKEY_CURRENT_USER, "NoFileSysPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'系统'属性中的'性能'页中的'文件系统'按钮"
       Case "'系统'属性中的'性能'页中的'虚拟内存'按钮"
            AddToKey HKEY_CURRENT_USER, "NoVirtMemPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'系统'属性中的'性能'页中的'虚拟内存'按钮"
       '-------------------------------------------------------------------------------------------------
       Case "'显示器'属性"
            AddToKey HKEY_CURRENT_USER, "NoDispCPL", SMWCPS, Not lst.Selected(lst.ListIndex), , "'显示器'属性"
       Case "'显示器'属性中的'背景'项"
            AddToKey HKEY_CURRENT_USER, "NoDispBackgroundPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'显示器'属性中的'背景'项"
       Case "'显示器'属性中的'屏幕保护'项"
            AddToKey HKEY_CURRENT_USER, "NoDispScrSavPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'显示器'属性中的'屏幕保护'项"
       Case "'显示器'属性中的'外观'项"
            AddToKey HKEY_CURRENT_USER, "NoDispAppearancePage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'显示器'属性中的'外观'项"
       '--------------------------------------------------------------------------------------
       Case "'网络'属性"
            AddToKey HKEY_CURRENT_USER, "NoNetSetup", SMWCPN, Not lst.Selected(lst.ListIndex), , "'网络'属性"
       Case "'网络'属性中的'标识'"
            AddToKey HKEY_CURRENT_USER, "NoNetSetupIDPage", SMWCPN, Not lst.Selected(lst.ListIndex), , "'网络'属性中的'标识'"
       Case "'网络'属性中的'访问控制'页"
            AddToKey HKEY_CURRENT_USER, "NoNetSetupSecurityPage", SMWCPN, Not lst.Selected(lst.ListIndex), , "'网络'属性中的'访问控制'页"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "禁止拔入"
            AddToKey HKEY_LOCAL_MACHINE, "NoDialIn", SMWCPN, Not lst.Selected(lst.ListIndex), , "禁止拔入"
       Case "禁用文件共享"
            AddToKey HKEY_LOCAL_MACHINE, "NoFileSharing", SMWCPN, Not lst.Selected(lst.ListIndex), , "禁用文件共享"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "'网络邻居'"
            AddToKey HKEY_CURRENT_USER, "NoNetHood", SMWCPE, Not lst.Selected(lst.ListIndex), , "'网络邻居'"
       Case "'整个网络'"
            AddToKey HKEY_CURRENT_USER, "NoEntioeNetwork", SMWCPE, Not lst.Selected(lst.ListIndex), , "'整个网络'"
       Case "'工作组目录'"
            AddToKey HKEY_CURRENT_USER, "NoWorkgroupContents", SMWCPE, Not lst.Selected(lst.ListIndex), , "'工作组目录'"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "'密码'属性"
            AddToKey HKEY_CURRENT_USER, "NoSecCPL", SMWCPS, Not lst.Selected(lst.ListIndex), , "'密码'属性"
       Case "'密码'属性中的'更改密码'页"
            AddToKey HKEY_CURRENT_USER, "NoPwdPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'密码'属性中的'更改密码'页"
       Case "'远程管理'页"
            AddToKey HKEY_CURRENT_USER, "NoAdminPage", SMWCPS, Not lst.Selected(lst.ListIndex), , "'远程管理'页"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "光盘自起动"
            AddToKey HKEY_CURRENT_USER, "NoDriveTypeAutoRun", SMWCPE, Not lst.Selected(lst.ListIndex), , "光盘自起动"
       Case "自动刷新"
            AddToKey HKEY_LOCAL_MACHINE, "UpdataMode", SCCU, lst.Selected(lst.ListIndex), , "自动刷新"
       Case "创建有'快捷方式'字样的快捷方式"
            AddToKey HKEY_CURRENT_USER, "Link", SMWCPE, Not lst.Selected(lst.ListIndex), , "创建有'快捷方式'字样的快捷方式"
       '-------------------------------------------------------------------------------------------------------------------------------
       Case "使用注册表编辑器"
             If PassWord(Enum_PassStyle_Regedit) Then
                AddToKey HKEY_CURRENT_USER, "DisableRegistryTools", SMWCPS, Not lst.Selected(lst.ListIndex), , "使用注册表编辑器"
             End If
       Case "登录时必须输入密码"
            AddToKey HKEY_LOCAL_MACHINE, "MustBevalidated", NL, lst.Selected(lst.ListIndex), , "登录时必须输入密码"
       Case "显示上次登录的用户名"
            AddToKey HKEY_LOCAL_MACHINE, "DontDisplayLastUserName", SMWCPN, Not lst.Selected(lst.ListIndex), , "显示上次登录的用户名"
       Case "使用口令缓存"
            AddToKey HKEY_LOCAL_MACHINE, "DisablePwdCaching", SMWCPN, Not lst.Selected(lst.ListIndex), , "使用口令缓存"
       Case "WINDOWS口令必须使用数字"
            AddToKey HKEY_LOCAL_MACHINE, "AlphanumPwds", SMWCPN, Not lst.Selected(lst.ListIndex), , "WINDOWS口令必须使用数字"
       Case "使用星号(*)隐藏共享口令"
            AddToKey HKEY_LOCAL_MACHINE, "HideSharePwds", SMWCPN, lst.Selected(lst.ListIndex), , "使用星号(*)隐藏共享口令"
              
End Select
End If
End Sub


Private Sub txtInput_Change()
If Not boolnoItemClick Then
   If frmBrow.Caption = "浏览图片" Then
      AddToKey HKEY_CURRENT_USER, "Wallpaper", CD, txtInput.Text, REG_SZ, "图形"
   End If
End If
End Sub
