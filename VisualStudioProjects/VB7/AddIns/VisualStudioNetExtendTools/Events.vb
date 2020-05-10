'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：Events.vb
'描  述：事件类
'版  本：2005.6.*
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005-6-15
'时  间：2005-6-15 18:01:52
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************

Option Strict Off
Option Explicit On 
Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If
Imports System.ComponentModel
Imports VSLangProj

Public Class Events

    Private WithEvents SolEvents As EnvDTE.SolutionEvents                     '解决方案事件
    Private WithEvents ProjectItemEvents As EnvDTE.ProjectItemsEvents
    Private WithEvents ProjectEvents As EnvDTE.ProjectsEvents
    Private WithEvents DocEvents As EnvDTE.DocumentEvents                     '文档事件
    Private WithEvents TextEditEvents As EnvDTE.TextEditorEvents              '文本编辑事件

    Private WithEvents refEvents As ReferencesEvents                          '引用事件
    
#If VER_2005 Then
    Private WithEvents KeyPressEvents As EnvDTE80.TextDocumentKeyPressEvents  '文本文档键盘事件
#End If
#If VER_2003 Then
    private m_DTE As EnvDTE.DTE                                               'DTE
#End If
#If VER_2005 Then
    Private m_DTE As EnvDTE80.DTE2                                            'DTE
#End If
    Private m_addInInstance As EnvDTE.AddIn                                   'DTE实例

    Public m_bKeyPressEventsAfterKeyPress As Boolean                          '是否允许键盘后事件
    Public m_bKeyPressEventsBeforeKeyPress As Boolean                         '是否允许键盘前事件

    Public m_bAutoFormatVCCode As Boolean                                     '自动格式化VC代码
    Public m_AutoFormatCode As AutoFormatCode                                 '格式化代码

    Public Sub New()
        m_AutoFormatCode = New AutoFormatCode
        m_bKeyPressEventsAfterKeyPress = True

    End Sub

#If VER_2003 Then
    Public Sub SetDTE(ByRef DTE As EnvDTE.DTE)
#End If
#If VER_2005 Then
    Public Sub SetDTE(ByRef DTE As EnvDTE80.DTE2)
#End If
        Try
            m_DTE = DTE
            SolEvents = m_DTE.Events.SolutionEvents
            'ProjectEvents = m_DTE.Events.SolutionItemsEvents
            'ProjectEvents = m_DTE.Events.SolutionItemsEvents

            DocEvents = m_DTE.Events.DocumentEvents
            TextEditEvents = m_DTE.Events.TextEditorEvents
#If VER_2005 Then
            KeyPressEvents = CType(m_DTE.Events, EnvDTE80.Events2).TextDocumentKeyPressEvents
#End If
            refEvents = CType(DTE.Events.GetObject("VBReferencesEvents"), ReferencesEvents)
        Catch
            Debug.WriteLine("Events SetDTE 异常")
        End Try
    End Sub

    '*******************************************************************************************************
    '过程名：DocEvents_DocumentOpened
    '功  能：文档打开事件
    '参  数：
    '        ByVal Document As EnvDTE.Document：发生事件的文档
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-4-11
    '时  间：6:40:08
    '*******************************************************************************************************
    Private Sub DocEvents_DocumentOpened(ByVal Document As EnvDTE.Document) Handles DocEvents.DocumentOpened
        Debug.WriteLine("文档打开事件")
    End Sub

    '*******************************************************************************************************
    '过程名：TextEditEvents_LineChanged
    '功  能：当在文本/代码编辑器中更改了移动插入点的行时发生。
    '参  数：
    '        ByVal StartPoint As EnvDTE.TextPoint：必选项。TextPoint 对象，表示已更改的行的行首。
    '        ByVal EndPoint As EnvDTE.TextPoint：必选项。TextPoint 对象，表示已更改的行的行尾。 
    '        ByVal Hint As Integer：必选项。vsTextChanged 常数，表示事件发生的一个或多个原因，它有助于了解缓冲区中发生的事情。 
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-4-11
    '时  间：6:40:03
    '*******************************************************************************************************
    Private Sub TextEditEvents_LineChanged(ByVal StartPoint As EnvDTE.TextPoint, ByVal EndPoint As EnvDTE.TextPoint, ByVal Hint As Integer) Handles TextEditEvents.LineChanged
        Debug.WriteLine("文本行改变事件")
        With m_AutoFormatCode
            .m_DTE = m_DTE
            If m_bAutoFormatVCCode Then
                .FormatCode(StartPoint, EndPoint, Hint)
            End If
        End With
    End Sub

    Private Sub SolEvents_AfterClosing() Handles SolEvents.AfterClosing
        Debug.WriteLine("解决方案,关闭工程后")
        Sol_AfterClosing()
    End Sub

    Private Sub SolEvents_Opened() Handles SolEvents.Opened
        '#If DEBUG Then
        '        Exit Sub
        '#End If
        Debug.WriteLine("解决方案打开事件后")

        Sol_Open()

        Dim sol As Solution
        sol = m_DTE.Solution

        Dim pro As Project
        For Each pro In sol.Projects
            Debug.WriteLine(pro.Name)
            ListProj(pro.ProjectItems, 0)
            '    Select Case pro.CodeModel.Language
            '        Case CodeModelLanguageConstants.vsCMLanguageVB
            '            Debug.WriteLine("VB.NET")
            '        Case CodeModelLanguageConstants.vsCMLanguageVC
            '            Debug.WriteLine("VC.net")
            '        Case CodeModelLanguageConstants.vsCMLanguageCSharp
            '            Debug.WriteLine("C#.net")
            '    End Select
        Next

    End Sub

#Region "枚举项目函数"
    Function ListProj(ByVal projitems As ProjectItems, ByVal Level As Integer, Optional ByRef bFlag As Boolean = False)
        Dim projitem As ProjectItem
        Dim Sel As TextSelection
        Dim szTemp As String
        Dim FileNum As Integer

        If bFlag Then
            Exit Function
        End If

        For Each projitem In projitems
            Dim szExt As String
            szExt = UCase(GetFileExt(projitem.FileNames(0)))

            '添加宏和常量
            If (szExt = "CPP" Or szExt = "C" Or szExt = "h") And projitem.Document.Language = EnvDTE.Constants.dsCPP Then
                FileNum = FreeFile()
                FileOpen(FileNum, projitem.FileNames(0), OpenMode.Input)
                szTemp = ""
                While Not EOF(FileNum)
                    szTemp = szTemp & LineInput(FileNum) & vbCrLf
                End While
                GetMacro(szTemp)
                FileClose(FileNum)
            End If

            '添加头文件
            If szExt = "h" Then

            End If

            Debug.WriteLine("Project item: " & projitem.Name & Level)
            ' Recurse if the project item has sub-items...
            Dim projitems2 As ProjectItems
            projitems2 = projitem.ProjectItems
            Dim notsubcoll As Boolean = projitems2 Is Nothing
            If Not notsubcoll Then
                ListProj(projitems2, Level + 1)
            End If
        Next
    End Function
#End Region

    Private Sub SolEvents_BeforeClosing() Handles SolEvents.BeforeClosing
        '#If DEBUG Then
        '        Exit Sub
        '#End If

        Debug.WriteLine("解决方案关闭前事件")
        'Dim fileNum As Integer
        'fileNum = FreeFile()
        'FileOpen(fileNum, g_szListTempFile, OpenMode.Input)
        'While Not EOF(fileNum)
        '    DeleteListItem(LineInput(fileNum))
        'End While
        'FileClose(fileNum)

        'Kill(g_szListTempFile)
        DeleteTempList()
    End Sub

    Private Sub SolEvents_ProjectAdded(ByVal Project As EnvDTE.Project) Handles SolEvents.ProjectAdded
        Debug.WriteLine("解决方案,加入工程后")
        Sol_ProjectAdded(Project)
    End Sub

    Private Sub SolEvents_ProjectRemoved(ByVal Project As EnvDTE.Project) Handles SolEvents.ProjectRemoved
        Debug.WriteLine("解决方案,删除工程后")
    End Sub

    Private Sub SolEvents_ProjectRenamed(ByVal Project As EnvDTE.Project, ByVal OldName As String) Handles SolEvents.ProjectRenamed
        Debug.WriteLine("解决方案,重命名工程后")
    End Sub

    Private Sub SolEvents_Renamed(ByVal OldName As String) Handles SolEvents.Renamed
        Debug.WriteLine("解决方案重命名")
    End Sub

    Private Sub ProjectItemEvents_ItemAdded(ByVal ProjectItem As EnvDTE.ProjectItem) Handles ProjectItemEvents.ItemAdded
        Debug.WriteLine("增加条目")
        Pro_ItemAdded(ProjectItem)
    End Sub

    Private Sub ProjectItemEvents_ItemRemoved(ByVal ProjectItem As EnvDTE.ProjectItem) Handles ProjectItemEvents.ItemRemoved
        Debug.WriteLine("删除条目")
        Pro_ItemAdded(ProjectItem)
    End Sub

    Private Sub ProjectItemEvents_ItemRenamed(ByVal ProjectItem As EnvDTE.ProjectItem, ByVal OldName As String) Handles ProjectItemEvents.ItemRenamed
        Debug.WriteLine("重命名条目")
        Pro_ItemAdded(ProjectItem)
    End Sub

    Private Sub ProjectEvents_ItemAdded(ByVal Project As EnvDTE.Project) Handles ProjectEvents.ItemAdded
        Debug.WriteLine("增加项目")

    End Sub

    Private Sub ProjectEvents_ItemRemoved(ByVal Project As EnvDTE.Project) Handles ProjectEvents.ItemRemoved
        Debug.WriteLine("删除项目")
    End Sub

    Private Sub ProjectEvents_ItemRenamed(ByVal Project As EnvDTE.Project, ByVal OldName As String) Handles ProjectEvents.ItemRenamed
        Debug.WriteLine("重命名项目")
    End Sub

#If VER_2005 Then
    Private Sub KeyPressEvents_AfterKeyPress(ByVal Keypress As String, ByVal Selection As EnvDTE.TextSelection, ByVal InStatementCompletion As Boolean) Handles KeyPressEvents.AfterKeyPress
        Debug.WriteLine("文本文档键盘后事件")
        Debug.WriteLine(Asc(Keypress))
        If m_bKeyPressEventsAfterKeyPress Then
            AfterKeyPress(Keypress)
        End If
    End Sub

    Private Sub KeyPressEvents_BeforeKeyPress(ByVal Keypress As String, ByVal Selection As EnvDTE.TextSelection, ByVal InStatementCompletion As Boolean, ByRef CancelKeypress As Boolean) Handles KeyPressEvents.BeforeKeyPress
        Debug.WriteLine("文本文档键盘前事件")
        If m_bKeyPressEventsBeforeKeyPress Then
            CancelKeypress = BeforeKeyPress(Keypress)
        End If
    End Sub
#End If

    '引用事件
    Public Sub refEvents_ReferenceAdded(ByVal pReference As VSLangProj.Reference) Handles refEvents.ReferenceAdded
        Debug.WriteLine(pReference.Name)
    End Sub

End Class
