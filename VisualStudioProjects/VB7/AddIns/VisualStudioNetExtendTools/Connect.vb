'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：Connect.vb
'描  述：AddIns连接、取消连接管理
'版  本：2005.12.*
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005-6-7
'时  间：2005-6-7 16:35:35
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************

Option Strict Off
Option Explicit On
Imports EnvDTE
Imports Extensibility
Imports System.Runtime.InteropServices
#If VER_2003 Then
Imports Microsoft.Office.Core
#End If
#If VER_2005 Then
Imports EnvDTE80
Imports Microsoft.VisualStudio.CommandBars
#End If
Imports Microsoft.Win32
Imports System.Windows.Forms
Imports System.Version
Imports System.Diagnostics

#Region " Read me for Add-in installation and setup information. "
' When run, the Add-in wizard prepared the registry for the Add-in.
' At a later time, if the Add-in becomes unavailable for reasons such as:
'   1) You moved this project to a computer other than which is was originally created on.
'   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
'   3) Registry corruption.
' you will need to re-register the Add-in by building the VisualStudioNetExtendToolsSetup project 
' by right clicking the project in the Solution Explorer, then choosing install.
#End Region

<GuidAttribute("8BD6D236-B5CC-450C-A04B-DAE41B3CAAC0"), ProgIdAttribute("VisualStudioNetExtendTools.Connect")> _
Public Class Connect
    Implements Extensibility.IDTExtensibility2
    Implements IDTCommandTarget

#If VER_2003 Then
    Dim applicationObject As EnvDTE.DTE
#End If
#If VER_2005 Then
    Dim applicationObject As EnvDTE80.DTE2
#End If
    Dim addInInstance As EnvDTE.AddIn
    Dim m_Events As Events = Nothing       '事件
    Dim m_DLLPath As String = Space(1024)  '当前 DLL 的路径

    Dim m_objDelete As Delete, m_objComment As Comment, m_objOtherTools As OtherTools
    Dim m_bAutoDisplayConst As Boolean = False

    Dim m_szMainKey As String

    Public Sub OnBeginShutdown(ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnBeginShutdown
        Debug.WriteLine("OnBeginShutdown")

        '释放键盘输入库中的 COM 指针
        FreeKeyInputCom()
    End Sub

    Public Sub OnAddInsUpdate(ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnAddInsUpdate
        Debug.WriteLine("OnAddInsUpdate")
    End Sub

    Public Sub OnStartupComplete(ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnStartupComplete
        Debug.WriteLine("OnStartupComplete")
    End Sub

    Public Sub OnDisconnection(ByVal RemoveMode As Extensibility.ext_DisconnectMode, ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnDisconnection
        Debug.WriteLine("关闭OnDisconnection" & RemoveMode)

#If DEBUG Then
#Else
        On Error Resume Next
#End If
        If RemoveMode = ext_DisconnectMode.ext_dm_UserClosed Then
            m_Events.m_bAutoFormatVCCode = False
            If m_objDelete.DeleteTool() Then
                '删除注册表中的命令加载键值
                Dim Key As RegistryKey
                Key = Registry.LocalMachine.OpenSubKey(m_szMainKey, True)
                Key.DeleteValue("Version")
            End If
            'm_Events = Nothing
            'm_objDelete = Nothing
            'm_objComment = Nothing
            'm_objOtherTools = Nothing
        End If
        If m_bAutoDisplayConst Then
            UnHook()
            m_bAutoDisplayConst = False
        End If
    End Sub

    Public Sub OnConnection(ByVal application As Object, ByVal connectMode As Extensibility.ext_ConnectMode, ByVal addInInst As Object, ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnConnection

#If DEBUG Then
        Debug.WriteLine("微软开发环境扩展工具集——OnConnection。connectMode =" & connectMode)
#Else
        On Error Resume Next
#End If
        Dim i As Integer
        Dim Key As RegistryKey

        m_szMainKey = "SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect"

#If __LIMIT__ Then
        Key = Registry.LocalMachine.OpenSubKey(m_szMainKey, True)
        If Key Is Nothing Then
            Key = Registry.LocalMachine.CreateSubKey(m_szMainKey)
            If Key Is Nothing Then
                Debug.Print("不能打开注册表项：" & m_szMainKey)
                Exit Sub
            End If
        End If
        If Not Register(Key.GetValue("Registry", True), "微软开发环境工具集") Then
            Key.Close()
            Exit Sub
        End If
        Key.Close()

#End If

        Dim bVal As Boolean
        Key = Registry.LocalMachine.OpenSubKey(m_szMainKey, True)
        If Key Is Nothing Then
            Key = Registry.LocalMachine.CreateSubKey(m_szMainKey)
            If Key Is Nothing Then
                Debug.Print("不能建立注册表项：" & m_szMainKey)
                Exit Sub
            End If
        End If
        If Not Key Is Nothing Then
            With Key
                bVal = .GetValue("ShowLicense", True)
                If bVal Then
                    Dim iShowLicense As Integer
                    iShowLicense = ShowLicense()
                    If iShowLicense And 1 Then
                        Key.SetValue("ShowLicense", True)
                    Else
                        If iShowLicense = 0 Then
                            Key.Close()
                            Exit Sub
                        End If
                        Key.SetValue("ShowLicense", False)
                    End If
                End If
            End With
            Key.Close()
        End If

        GetDLLPath(m_DLLPath)
#If VER_2003 Then
        applicationObject = CType(application, EnvDTE.DTE)
#End If
#If VER_2005 Then
        applicationObject = CType(application, EnvDTE80.DTE2)
#End If
        addInInstance = CType(addInInst, EnvDTE.AddIn)

        '设置键盘输入库中的 COM 指针
        InitKeyInputCom(CType(application, EnvDTE80.DTE2))

        '事件
        If connectMode = Extensibility.ext_ConnectMode.ext_cm_Startup Or connectMode = ext_ConnectMode.ext_cm_AfterStartup Then
            'm_Events = Nothing
            'm_objDelete = Nothing
            'm_objComment = Nothing
            'm_objOtherTools = Nothing

            If m_Events Is Nothing Then
                m_Events = New Events
                With m_Events
                    .SetDTE(applicationObject)
                    .m_bAutoFormatVCCode = True
                End With

                m_objComment = New Comment
                m_objDelete = New Delete
                m_objOtherTools = New OtherTools
                m_objDelete.m_DTE = applicationObject
                m_objComment.m_DTE = applicationObject
                m_objOtherTools.m_DTE = applicationObject

                Dim frmSet As frmSettings
                Key = Registry.LocalMachine.OpenSubKey(m_szMainKey, True)
                If Not Key Is Nothing Then
                    If Key.GetValue("Show", True) Then
                        frmSet = New frmSettings
                        frmSet.m_objComment = m_objComment
                        frmSet.ShowDialog()
                    End If
                    Key.Close()
                End If
            End If
        End If

        Dim szKeyItem As String
        szKeyItem = "SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\VC"
        Key = Registry.LocalMachine.OpenSubKey(szKeyItem, True)
        If Key Is Nothing Then
            Key = Registry.LocalMachine.CreateSubKey(szKeyItem)
            If Key Is Nothing Then
                Debug.Print("不能建立注册表项：" & szKeyItem)
                Exit Sub
            End If
        End If
        m_Events.m_bAutoFormatVCCode = Key.GetValue("AutoFomatVCCode", True)
        m_bAutoDisplayConst = Key.GetValue("AutoDispConstOrMacro", True)
        Key.Close()

        'Dim objMenuItem As CommandBarControl '菜单项
        '在菜单栏中增加一项
        'objMenuItem = objMenu.Controls.Add(Microsoft.Office.Core.MsoControlType.msoControlButton)
        'With objMenuItem
        '    .Visible = True
        '    .Caption = "扩展工具集(&X)"
        '    .style = Microsoft.Office.Core.MsoButtonStyle.msoButtonCaption
        'End With
        If connectMode = Extensibility.ext_ConnectMode.ext_cm_UISetup Or connectMode = ext_ConnectMode.ext_cm_AfterStartup Or connectMode = ext_ConnectMode.ext_cm_Startup Then '安装后第一次运行
            '增加:检查注册表中是否有命令加载项,并检查版本是是当前ADDIN的版本,否则重新加载
            Dim szKey As String, szVersion As String

            Dim f As FileVersionInfo = FileVersionInfo.GetVersionInfo(m_DLLPath & "\VisualStudioNetExtendTools.dll")
            szVersion = f.FileVersion
            Key = Registry.LocalMachine.OpenSubKey(m_szMainKey, True)
            If Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(m_szMainKey)
            End If
            szKey = Key.GetValue("Version", "")
            If szKey = "" Then
                Key.SetValue("Version", szVersion)
            End If
            If szKey <> szVersion Then
                m_objDelete.DeleteTool()
                LoadCommand()
                Key.SetValue("Version", szVersion)
            End If
            Key.Close()
        End If

        If m_bAutoDisplayConst Then
            SetHook()
        End If

    End Sub

    '*******************************************************************************************************
    '过程名：Exec
    '描  述：执行菜单命令
    '注  意：要新加一个命令时，要修改三个地方
    '        1、修改 LoadCommand ，在菜单和工具条增加一个命令
    '        2、修改 exec 过程，增加相应的函数调用
    '        3、修改 DeleteTool 过程，删除相应的菜单
    '参  数：
    '        ByVal cmdName As String                   ：
    '        ByVal executeOption As vsCommandExecOption：
    '        ByRef varIn As Object                     ：
    '        ByRef varOut As Object                    ：
    '        ByRef handled As Boolean                  ：
    '版  本：2007.9.1.0
    '作  者：康  林
    '时  间：2007年8月17日 14:16:01
    '*******************************************************************************************************
    Public Sub Exec(ByVal cmdName As String, ByVal executeOption As vsCommandExecOption, ByRef varIn As Object, ByRef varOut As Object, ByRef handled As Boolean) Implements IDTCommandTarget.Exec
        Dim bAutoFormatCode As Boolean, szFile As String, bKeyPressEventsAfterKeyPress As Boolean

        If (executeOption = vsCommandExecOption.vsCommandExecOptionDoDefault) Then
            handled = False

            Select Case cmdName
                Case "VisualStudioNetExtendTools.Connect.FunctionComment"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode '防止自动格式化
                    bKeyPressEventsAfterKeyPress = m_Events.m_bKeyPressEventsAfterKeyPress
                    m_Events.m_bAutoFormatVCCode = False
                    m_Events.m_bKeyPressEventsAfterKeyPress = False
                    m_objComment.FunctionComment()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                    m_Events.m_bKeyPressEventsAfterKeyPress = bKeyPressEventsAfterKeyPress
                Case "VisualStudioNetExtendTools.Connect.AlignComment"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.AlignComment()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.AlignComment1"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.AlignComment1()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.AlignPointSign"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.AlignPointSign()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.AlignPointSign1"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.AlignPointSign1()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.AddEndIf"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.AddEndIf()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.SwitchCppToH"
                    m_objComment.SwitchCppToH()
                Case "VisualStudioNetExtendTools.Connect.CommentTRACE"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.CommentTRACE()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.UncommentTRACE"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.UnCommentTRACE()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.Modify"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode
                    m_Events.m_bAutoFormatVCCode = False
                    m_objComment.Modify()
                    m_Events.m_bAutoFormatVCCode = bAutoFormatCode
                Case "VisualStudioNetExtendTools.Connect.删除工具栏"
                    m_objDelete.删除工具栏()
                Case "VisualStudioNetExtendTools.Connect.删除命令"
                    m_objDelete.删除命令()
                Case "VisualStudioNetExtendTools.Connect.IncludeFile"
                    m_objOtherTools.IncludeFile()
                Case "VisualStudioNetExtendTools.Connect.GetFileRelativePath"
                    m_objOtherTools.GetFileRelativePath()
                Case "VisualStudioNetExtendTools.Connect.GetDate"
                    m_objOtherTools.GetDate()
                Case "VisualStudioNetExtendTools.Connect.GetTime"
                    m_objOtherTools.GetTime()
                Case "VisualStudioNetExtendTools.Connect.CreateBookMark"
                    m_objOtherTools.CreateBookMark()
                Case "VisualStudioNetExtendTools.Connect.CreateHyperlink"
                    m_objOtherTools.CreateHyperlink()
                Case "VisualStudioNetExtendTools.Connect.GoHyperlink"
                    m_objOtherTools.GoHyperlink()
                Case "VisualStudioNetExtendTools.Connect.ModifyEndLineComment"
                    Dim Sel As TextSelection = applicationObject.DTE.ActiveDocument.Selection
                    Sel.SelectLine()
                    m_Events.m_AutoFormatCode.ModifyBracket(Sel.Text, Sel.AnchorPoint.Line, Sel.BottomPoint)
                Case "VisualStudioNetExtendTools.Connect.AutoFomatVCCode"
                    m_Events.m_bAutoFormatVCCode = Not m_Events.m_bAutoFormatVCCode
                Case "VisualStudioNetExtendTools.Connect.AutoDispConstOrMacro"
                    If m_bAutoDisplayConst Then
                        UnHook()
                        m_bAutoDisplayConst = False
                        MsgBox("停止使用常量、宏自动提示器")
                    Else
                        SetHook()
                        m_bAutoDisplayConst = True
                        MsgBox("使用常量、宏自动提示器")
                    End If
                Case "VisualStudioNetExtendTools.Connect.SetFunctionCommentPara"
                    Dim frmSet As frmSettings
                    frmSet = New frmSettings
                    frmSet.m_objComment = m_objComment
                    frmSet.ShowDialog()
                Case "VisualStudioNetExtendTools.Connect.OtherSettings"
                    Dim frm As frmOtherSettings
                    frm = New frmOtherSettings
                    frm.m_objEvent = m_Events
                    frm.m_objComment = m_objComment
                    frm.ShowDialog()
                Case "VisualStudioNetExtendTools.Connect.Delete"
                    applicationObject.CommandBars("删除").Visible = Not applicationObject.CommandBars("删除").Visible
                Case "VisualStudioNetExtendTools.Connect.OtherTools"
                    applicationObject.CommandBars("其它工具").Visible = Not applicationObject.CommandBars("其它工具").Visible
                Case "VisualStudioNetExtendTools.Connect.VCTools"
                    applicationObject.CommandBars("VC工具").Visible = Not applicationObject.CommandBars("VC工具").Visible
                Case "VisualStudioNetExtendTools.Connect.Comments"
                    applicationObject.CommandBars("注释").Visible = Not applicationObject.CommandBars("注释").Visible
                Case "VisualStudioNetExtendTools.Connect.Registry"
                    Register(True, "微软开发环境工具集", True)
                Case "VisualStudioNetExtendTools.Connect.Help"
                    ShowHelp()
                Case "VisualStudioNetExtendTools.Connect.AboutExtendTools"
                    ShowVersion()
            End Select

            handled = True
        End If

    End Sub

    Public Sub QueryStatus(ByVal cmdName As String, ByVal neededText As vsCommandStatusTextWanted, ByRef statusOption As vsCommandStatus, ByRef commandText As Object) Implements IDTCommandTarget.QueryStatus
        On Error Resume Next
        Dim m_Key As RegistryKey
        Dim m_KeyItem As String
        m_KeyItem = "SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\VC\"
        m_Key = Registry.LocalMachine.OpenSubKey("SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\VC", True)
        If m_Key Is Nothing Then
            m_Key = Registry.LocalMachine.CreateSubKey("SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\VC")
        End If

        If neededText = EnvDTE.vsCommandStatusTextWanted.vsCommandStatusTextWantedNone Then
            statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
            Select Case cmdName
                Case "VisualStudioNetExtendTools.Connect.AutoFomatVCCode"
                    If m_Events.m_bAutoFormatVCCode Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                        m_Key.SetValue("AutoFomatVCCode", True)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                        m_Key.SetValue("AutoFomatVCCode", False)
                    End If
                Case "VisualStudioNetExtendTools.Connect.AutoDispConstOrMacro"
                    If m_bAutoDisplayConst Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                        m_Key.SetValue("AutoDispConstOrMacro", True)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                        m_Key.SetValue("AutoDispConstOrMacro", False)
                    End If
                Case "VisualStudioNetExtendTools.Connect.Delete"
                    If applicationObject.CommandBars("删除").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
                Case "VisualStudioNetExtendTools.Connect.OtherTools"
                    If applicationObject.CommandBars("其它工具").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
                Case "VisualStudioNetExtendTools.Connect.VCTools"
                    If applicationObject.CommandBars("VC工具").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
                Case "VisualStudioNetExtendTools.Connect.Comments"
                    If applicationObject.CommandBars("注释").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
            End Select
        End If

        m_Key.Close()

    End Sub

    '*******************************************************************************************************
    '过程名：LoadCommand
    '描  述：加载命令到菜单和工具条。
    '注  意：要新加一个命令时，要修改三个地方
    '        1、修改 LoadCommand ，在菜单和工具条增加一个命令
    '        2、修改 exec 过程，增加相应的函数调用
    '        3、修改 DeleteTool 过程，删除相应的菜单
    '参  数：无
    '版  本：2007.9.1.0
    '作  者：康  林
    '时  间：2007年8月17日 14:12:48
    '*******************************************************************************************************
    Public Sub LoadCommand()
        Debug.WriteLine("加载命令")
#If DEBUG Then
#Else
        On Error Resume Next
#End If
        '增加工具栏和命令
        ' When run, the Add-in wizard prepared the registry for the Add-in.
        ' At a later time, the Add-in or its commands may become unavailable for reasons such as:
        '   1) You moved this project to a computer other than which is was originally created on.
        '   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
        '   3) You add new commands or modify commands already defined.
        ' You will need to re-register the Add-in by building the VisualStudioNetExtendToolsSetup project,
        ' right-clicking the project in the Solution Explorer, and then choosing install.
        ' Alternatively, you could execute the ReCreateCommands.reg file the Add-in Wizard generated in
        ' the project directory, or run 'devenv /setup' from a command prompt.

        Dim objCommands As Commands
        Dim CommandObj As Command
        Dim objComBar As CommandBar
        Dim objMenu As CommandBar                              '菜单栏
        Dim objMenuBar As CommandBar                           '扩展工具集菜单项
        Dim objMenuSet As CommandBar                           '设置菜单项
        Dim objMenuComment As CommandBar                       '注释菜单项
        Dim objMenuTool As CommandBar                          '工具栏菜单项
        Dim objMenuHyper As CommandBar                         '超链接菜单项
        Dim objMenuC As CommandBar                             'C语言工具菜单项
        Dim objMenuOtherTools As CommandBar                    '其它工具菜单项


        Dim objAddIn As AddIn = CType(addInInstance, AddIn)
        objMenu = applicationObject.CommandBars.ActiveMenuBar  '当前菜单栏

        objCommands = applicationObject.Commands

        objMenuBar = objCommands.AddCommandBar("扩展工具集(&X)", vsCommandBarType.vsCommandBarTypeMenu, objMenu, 4)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "AboutExtendTools", "关于微软扩展工具集", "关于微软扩展工具集", True, 49, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuBar)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "Help", "帮助", "帮助", True, 49, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuBar)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "Registry", "注册", "注册", True, 277, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuBar).BeginGroup = True

        objMenuSet = objCommands.AddCommandBar("设置", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)
        objMenuBar.Controls(1).BeginGroup = True

        CommandObj = objCommands.AddNamedCommand(objAddIn, "SetFunctionCommentPara", "设置函数注释参数", "设置函数注释参数", True, 548, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuSet)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "OtherSettings", "设置", "设置", True, 548, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuSet)

        objMenuTool = objCommands.AddCommandBar("工具栏", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)
        objMenuBar.Controls(1).BeginGroup = True

        CommandObj = objCommands.AddNamedCommand(objAddIn, "Delete", "显示删除工具栏", "显示删除工具栏", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "OtherTools", "显示其它工具栏", "显示其它工具栏", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "VCTools", "显示 VC 工具栏", "显示 VC 工具栏", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "Comments", "显示注释工具栏", "显示注释工具栏", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)

        objComBar = objCommands.AddCommandBar("删除", vsCommandBarType.vsCommandBarTypeToolbar)
        objComBar.Visible = False
        objMenuOtherTools = objCommands.AddCommandBar("其它工具", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "删除命令", "删除指定的命令", "删除指定的命令", True, 214, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("删除")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "删除工具栏", "删除指定的工具栏", "删除指定的工具栏", True, 241, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("删除")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools).BeginGroup = True

        objComBar = objCommands.AddCommandBar("其它工具", vsCommandBarType.vsCommandBarTypeToolbar)


        CommandObj = objCommands.AddNamedCommand(objAddIn, "GetFileRelativePath", "得到文件相对路径", "得到文件相对路径，路径复制到剪切板中", True, 249, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("其它工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "GetDate", "得到当前日期", "得到当前日期", True, 83, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("其它工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "GetTime", "得到当前时间", "得到当前时间", True, 33, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("其它工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)


        objMenuHyper = objCommands.AddCommandBar("超链接", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "CreateHyperlink", "建立超链接", "建立超链接", True, 340, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("其它工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuHyper)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "GoHyperlink", "转到超链接", "转到超链接", True, 136, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("其它工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuHyper)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "CreateBookMark", "插入书签", "插入书签", True, 233, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("其它工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuHyper)

        objComBar = objCommands.AddCommandBar("VC工具", vsCommandBarType.vsCommandBarTypeToolbar)
        objComBar.Visible = True
        objMenuC = objCommands.AddCommandBar("C 语言工具", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "AutoDispConstOrMacro", "自动提示常量或宏", "自动提示常量或宏", True, 180, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuC)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "AutoFomatVCCode", "自动格式化VC代码", "自动格式化VC代码", True, 253, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuC).BeginGroup = True

        CommandObj = objCommands.AddNamedCommand(objAddIn, "ModifyEndLineComment", "自动修改程序块结束行的注释", "自动修改程序块结束行的注释", True, 162, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuC)
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "UncommentTRACE", "取消注释的 TRACE 语句", "取消注释的 TRACE 语句", True, 663, Nothing, 1 + 2)
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "CommentTRACE", "注释 TRACE 语句", "注释 TRACE 语句", True, 662, Nothing, 1 + 2)
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "IncludeFile", "添加头文件", "添加头文件", True, 246, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "SwitchCppToH", "实现文件(CPP)与头文件(H)互相切换", "实现文件(CPP)与头文件(H)互相切换", True, 173, Nothing, 1 + 2)      '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC工具")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)

        objComBar = objCommands.AddCommandBar("注释", vsCommandBarType.vsCommandBarTypeToolbar)
        objComBar.Visible = True
        objMenuComment = objCommands.AddCommandBar("注释", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "Modify", "修改信息", "修改信息", True, 47, Nothing, 1 + 2)      '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("注释")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AddEndIf", "增加块结束注释", "增加块结束注释", True, 288, Nothing, 1 + 2)      '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("注释")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignPointSign1", "自动对齐指定的符号", "自动对齐指定的符号(以最远处为对齐点)", True, 15, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("注释")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignPointSign", "自动对齐指定的符号", "自动对齐指定的符号", True, 14, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("注释")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignComment1", "自动对齐语句后的注释", "自动对齐语句后的注释(以最远处为对齐点)", True, 15, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("注释")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignComment", "自动对齐语句后的注释", "自动对齐语句后的注释", True, 14, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("注释")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "FunctionComment", "自动增加函数或文件注释", "自动增加函数或文件注释", True, 593, Nothing, 1 + 2)     '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled

        'CommandObj.Bindings = "Text Editor::crl+F, ctrl+n"
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("注释")).Style = MsoButtonStyle.msoButtonIcon


        'For Each objComBarBut In applicationObject.CommandBars.Item("注释").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'For Each objComBarBut In applicationObject.CommandBars.Item("VC工具").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'For Each objComBarBut In applicationObject.CommandBars.Item("删除").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'applicationObject.CommandBars.Item("删除").Visible = False
        'For Each objComBarBut In applicationObject.CommandBars.Item("其它工具").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'applicationObject.CommandBars.Item("其它工具").Visible = False
    End Sub

End Class
