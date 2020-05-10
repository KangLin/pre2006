'*******************************************************************************************************
'��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
'�ļ�����Connect.vb
'��  ����AddIns���ӡ�ȡ�����ӹ���
'��  ����2005.12.*
'��  �ߣ���  ��
'E_Mail��kl222@126.com
'��  �ڣ�2005-6-7
'ʱ  �䣺2005-6-7 16:35:35
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
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
    Dim m_Events As Events = Nothing       '�¼�
    Dim m_DLLPath As String = Space(1024)  '��ǰ DLL ��·��

    Dim m_objDelete As Delete, m_objComment As Comment, m_objOtherTools As OtherTools
    Dim m_bAutoDisplayConst As Boolean = False

    Dim m_szMainKey As String

    Public Sub OnBeginShutdown(ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnBeginShutdown
        Debug.WriteLine("OnBeginShutdown")

        '�ͷż���������е� COM ָ��
        FreeKeyInputCom()
    End Sub

    Public Sub OnAddInsUpdate(ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnAddInsUpdate
        Debug.WriteLine("OnAddInsUpdate")
    End Sub

    Public Sub OnStartupComplete(ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnStartupComplete
        Debug.WriteLine("OnStartupComplete")
    End Sub

    Public Sub OnDisconnection(ByVal RemoveMode As Extensibility.ext_DisconnectMode, ByRef custom As System.Array) Implements Extensibility.IDTExtensibility2.OnDisconnection
        Debug.WriteLine("�ر�OnDisconnection" & RemoveMode)

#If DEBUG Then
#Else
        On Error Resume Next
#End If
        If RemoveMode = ext_DisconnectMode.ext_dm_UserClosed Then
            m_Events.m_bAutoFormatVCCode = False
            If m_objDelete.DeleteTool() Then
                'ɾ��ע����е�������ؼ�ֵ
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
        Debug.WriteLine("΢����������չ���߼�����OnConnection��connectMode =" & connectMode)
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
                Debug.Print("���ܴ�ע����" & m_szMainKey)
                Exit Sub
            End If
        End If
        If Not Register(Key.GetValue("Registry", True), "΢�����������߼�") Then
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
                Debug.Print("���ܽ���ע����" & m_szMainKey)
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

        '���ü���������е� COM ָ��
        InitKeyInputCom(CType(application, EnvDTE80.DTE2))

        '�¼�
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
                Debug.Print("���ܽ���ע����" & szKeyItem)
                Exit Sub
            End If
        End If
        m_Events.m_bAutoFormatVCCode = Key.GetValue("AutoFomatVCCode", True)
        m_bAutoDisplayConst = Key.GetValue("AutoDispConstOrMacro", True)
        Key.Close()

        'Dim objMenuItem As CommandBarControl '�˵���
        '�ڲ˵���������һ��
        'objMenuItem = objMenu.Controls.Add(Microsoft.Office.Core.MsoControlType.msoControlButton)
        'With objMenuItem
        '    .Visible = True
        '    .Caption = "��չ���߼�(&X)"
        '    .style = Microsoft.Office.Core.MsoButtonStyle.msoButtonCaption
        'End With
        If connectMode = Extensibility.ext_ConnectMode.ext_cm_UISetup Or connectMode = ext_ConnectMode.ext_cm_AfterStartup Or connectMode = ext_ConnectMode.ext_cm_Startup Then '��װ���һ������
            '����:���ע������Ƿ������������,�����汾���ǵ�ǰADDIN�İ汾,�������¼���
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
    '��������Exec
    '��  ����ִ�в˵�����
    'ע  �⣺Ҫ�¼�һ������ʱ��Ҫ�޸������ط�
    '        1���޸� LoadCommand ���ڲ˵��͹���������һ������
    '        2���޸� exec ���̣�������Ӧ�ĺ�������
    '        3���޸� DeleteTool ���̣�ɾ����Ӧ�Ĳ˵�
    '��  ����
    '        ByVal cmdName As String                   ��
    '        ByVal executeOption As vsCommandExecOption��
    '        ByRef varIn As Object                     ��
    '        ByRef varOut As Object                    ��
    '        ByRef handled As Boolean                  ��
    '��  ����2007.9.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��17�� 14:16:01
    '*******************************************************************************************************
    Public Sub Exec(ByVal cmdName As String, ByVal executeOption As vsCommandExecOption, ByRef varIn As Object, ByRef varOut As Object, ByRef handled As Boolean) Implements IDTCommandTarget.Exec
        Dim bAutoFormatCode As Boolean, szFile As String, bKeyPressEventsAfterKeyPress As Boolean

        If (executeOption = vsCommandExecOption.vsCommandExecOptionDoDefault) Then
            handled = False

            Select Case cmdName
                Case "VisualStudioNetExtendTools.Connect.FunctionComment"
                    bAutoFormatCode = m_Events.m_bAutoFormatVCCode '��ֹ�Զ���ʽ��
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
                Case "VisualStudioNetExtendTools.Connect.ɾ��������"
                    m_objDelete.ɾ��������()
                Case "VisualStudioNetExtendTools.Connect.ɾ������"
                    m_objDelete.ɾ������()
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
                        MsgBox("ֹͣʹ�ó��������Զ���ʾ��")
                    Else
                        SetHook()
                        m_bAutoDisplayConst = True
                        MsgBox("ʹ�ó��������Զ���ʾ��")
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
                    applicationObject.CommandBars("ɾ��").Visible = Not applicationObject.CommandBars("ɾ��").Visible
                Case "VisualStudioNetExtendTools.Connect.OtherTools"
                    applicationObject.CommandBars("��������").Visible = Not applicationObject.CommandBars("��������").Visible
                Case "VisualStudioNetExtendTools.Connect.VCTools"
                    applicationObject.CommandBars("VC����").Visible = Not applicationObject.CommandBars("VC����").Visible
                Case "VisualStudioNetExtendTools.Connect.Comments"
                    applicationObject.CommandBars("ע��").Visible = Not applicationObject.CommandBars("ע��").Visible
                Case "VisualStudioNetExtendTools.Connect.Registry"
                    Register(True, "΢�����������߼�", True)
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
                    If applicationObject.CommandBars("ɾ��").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
                Case "VisualStudioNetExtendTools.Connect.OtherTools"
                    If applicationObject.CommandBars("��������").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
                Case "VisualStudioNetExtendTools.Connect.VCTools"
                    If applicationObject.CommandBars("VC����").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
                Case "VisualStudioNetExtendTools.Connect.Comments"
                    If applicationObject.CommandBars("ע��").Visible Then
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusLatched + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    Else
                        statusOption = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
                    End If
            End Select
        End If

        m_Key.Close()

    End Sub

    '*******************************************************************************************************
    '��������LoadCommand
    '��  ������������˵��͹�������
    'ע  �⣺Ҫ�¼�һ������ʱ��Ҫ�޸������ط�
    '        1���޸� LoadCommand ���ڲ˵��͹���������һ������
    '        2���޸� exec ���̣�������Ӧ�ĺ�������
    '        3���޸� DeleteTool ���̣�ɾ����Ӧ�Ĳ˵�
    '��  ������
    '��  ����2007.9.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��17�� 14:12:48
    '*******************************************************************************************************
    Public Sub LoadCommand()
        Debug.WriteLine("��������")
#If DEBUG Then
#Else
        On Error Resume Next
#End If
        '���ӹ�����������
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
        Dim objMenu As CommandBar                              '�˵���
        Dim objMenuBar As CommandBar                           '��չ���߼��˵���
        Dim objMenuSet As CommandBar                           '���ò˵���
        Dim objMenuComment As CommandBar                       'ע�Ͳ˵���
        Dim objMenuTool As CommandBar                          '�������˵���
        Dim objMenuHyper As CommandBar                         '�����Ӳ˵���
        Dim objMenuC As CommandBar                             'C���Թ��߲˵���
        Dim objMenuOtherTools As CommandBar                    '�������߲˵���


        Dim objAddIn As AddIn = CType(addInInstance, AddIn)
        objMenu = applicationObject.CommandBars.ActiveMenuBar  '��ǰ�˵���

        objCommands = applicationObject.Commands

        objMenuBar = objCommands.AddCommandBar("��չ���߼�(&X)", vsCommandBarType.vsCommandBarTypeMenu, objMenu, 4)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "AboutExtendTools", "����΢����չ���߼�", "����΢����չ���߼�", True, 49, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuBar)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "Help", "����", "����", True, 49, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuBar)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "Registry", "ע��", "ע��", True, 277, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuBar).BeginGroup = True

        objMenuSet = objCommands.AddCommandBar("����", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)
        objMenuBar.Controls(1).BeginGroup = True

        CommandObj = objCommands.AddNamedCommand(objAddIn, "SetFunctionCommentPara", "���ú���ע�Ͳ���", "���ú���ע�Ͳ���", True, 548, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuSet)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "OtherSettings", "����", "����", True, 548, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuSet)

        objMenuTool = objCommands.AddCommandBar("������", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)
        objMenuBar.Controls(1).BeginGroup = True

        CommandObj = objCommands.AddNamedCommand(objAddIn, "Delete", "��ʾɾ��������", "��ʾɾ��������", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "OtherTools", "��ʾ����������", "��ʾ����������", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "VCTools", "��ʾ VC ������", "��ʾ VC ������", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "Comments", "��ʾע�͹�����", "��ʾע�͹�����", True, 0, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuTool)

        objComBar = objCommands.AddCommandBar("ɾ��", vsCommandBarType.vsCommandBarTypeToolbar)
        objComBar.Visible = False
        objMenuOtherTools = objCommands.AddCommandBar("��������", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "ɾ������", "ɾ��ָ��������", "ɾ��ָ��������", True, 214, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("ɾ��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "ɾ��������", "ɾ��ָ���Ĺ�����", "ɾ��ָ���Ĺ�����", True, 241, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("ɾ��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools).BeginGroup = True

        objComBar = objCommands.AddCommandBar("��������", vsCommandBarType.vsCommandBarTypeToolbar)


        CommandObj = objCommands.AddNamedCommand(objAddIn, "GetFileRelativePath", "�õ��ļ����·��", "�õ��ļ����·����·�����Ƶ����а���", True, 249, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("��������")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "GetDate", "�õ���ǰ����", "�õ���ǰ����", True, 83, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("��������")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "GetTime", "�õ���ǰʱ��", "�õ���ǰʱ��", True, 33, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("��������")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuOtherTools)


        objMenuHyper = objCommands.AddCommandBar("������", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "CreateHyperlink", "����������", "����������", True, 340, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("��������")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuHyper)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "GoHyperlink", "ת��������", "ת��������", True, 136, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("��������")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuHyper)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "CreateBookMark", "������ǩ", "������ǩ", True, 233, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("��������")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuHyper)

        objComBar = objCommands.AddCommandBar("VC����", vsCommandBarType.vsCommandBarTypeToolbar)
        objComBar.Visible = True
        objMenuC = objCommands.AddCommandBar("C ���Թ���", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = objCommands.AddNamedCommand(objAddIn, "AutoDispConstOrMacro", "�Զ���ʾ�������", "�Զ���ʾ�������", True, 180, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuC)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "AutoFomatVCCode", "�Զ���ʽ��VC����", "�Զ���ʽ��VC����", True, 253, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuC).BeginGroup = True

        CommandObj = objCommands.AddNamedCommand(objAddIn, "ModifyEndLineComment", "�Զ��޸ĳ��������е�ע��", "�Զ��޸ĳ��������е�ע��", True, 162, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuC)
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "UncommentTRACE", "ȡ��ע�͵� TRACE ���", "ȡ��ע�͵� TRACE ���", True, 663, Nothing, 1 + 2)
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC����")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "CommentTRACE", "ע�� TRACE ���", "ע�� TRACE ���", True, 662, Nothing, 1 + 2)
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC����")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)
        CommandObj = objCommands.AddNamedCommand(objAddIn, "IncludeFile", "���ͷ�ļ�", "���ͷ�ļ�", True, 246, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC����")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "SwitchCppToH", "ʵ���ļ�(CPP)��ͷ�ļ�(H)�����л�", "ʵ���ļ�(CPP)��ͷ�ļ�(H)�����л�", True, 173, Nothing, 1 + 2)      '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(applicationObject.CommandBars.Item("VC����")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj.AddControl(objMenuC)

        objComBar = objCommands.AddCommandBar("ע��", vsCommandBarType.vsCommandBarTypeToolbar)
        objComBar.Visible = True
        objMenuComment = objCommands.AddCommandBar("ע��", vsCommandBarType.vsCommandBarTypeMenu, objMenuBar)

        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "Modify", "�޸���Ϣ", "�޸���Ϣ", True, 47, Nothing, 1 + 2)      '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("ע��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AddEndIf", "���ӿ����ע��", "���ӿ����ע��", True, 288, Nothing, 1 + 2)      '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("ע��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignPointSign1", "�Զ�����ָ���ķ���", "�Զ�����ָ���ķ���(����Զ��Ϊ�����)", True, 15, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("ע��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignPointSign", "�Զ�����ָ���ķ���", "�Զ�����ָ���ķ���", True, 14, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("ע��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignComment1", "�Զ����������ע��", "�Զ����������ע��(����Զ��Ϊ�����)", True, 15, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("ע��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "AlignComment", "�Զ����������ע��", "�Զ����������ע��", True, 14, Nothing, 1 + 2) '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("ע��")).Style = MsoButtonStyle.msoButtonIcon
        CommandObj = applicationObject.Commands.AddNamedCommand(objAddIn, "FunctionComment", "�Զ����Ӻ������ļ�ע��", "�Զ����Ӻ������ļ�ע��", True, 593, Nothing, 1 + 2)     '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled

        'CommandObj.Bindings = "Text Editor::crl+F, ctrl+n"
        CommandObj.AddControl(objMenuComment)
        CommandObj.AddControl(applicationObject.CommandBars.Item("ע��")).Style = MsoButtonStyle.msoButtonIcon


        'For Each objComBarBut In applicationObject.CommandBars.Item("ע��").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'For Each objComBarBut In applicationObject.CommandBars.Item("VC����").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'For Each objComBarBut In applicationObject.CommandBars.Item("ɾ��").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'applicationObject.CommandBars.Item("ɾ��").Visible = False
        'For Each objComBarBut In applicationObject.CommandBars.Item("��������").Controls
        '    objComBarBut.Style = MsoButtonStyle.msoButtonIcon
        'Next
        'applicationObject.CommandBars.Item("��������").Visible = False
    End Sub

End Class
