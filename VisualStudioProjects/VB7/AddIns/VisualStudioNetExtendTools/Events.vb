'*******************************************************************************************************
'��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
'�ļ�����Events.vb
'��  �����¼���
'��  ����2005.6.*
'��  �ߣ���  ��
'E_Mail��kl222@126.com
'��  �ڣ�2005-6-15
'ʱ  �䣺2005-6-15 18:01:52
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
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

    Private WithEvents SolEvents As EnvDTE.SolutionEvents                     '��������¼�
    Private WithEvents ProjectItemEvents As EnvDTE.ProjectItemsEvents
    Private WithEvents ProjectEvents As EnvDTE.ProjectsEvents
    Private WithEvents DocEvents As EnvDTE.DocumentEvents                     '�ĵ��¼�
    Private WithEvents TextEditEvents As EnvDTE.TextEditorEvents              '�ı��༭�¼�

    Private WithEvents refEvents As ReferencesEvents                          '�����¼�
    
#If VER_2005 Then
    Private WithEvents KeyPressEvents As EnvDTE80.TextDocumentKeyPressEvents  '�ı��ĵ������¼�
#End If
#If VER_2003 Then
    private m_DTE As EnvDTE.DTE                                               'DTE
#End If
#If VER_2005 Then
    Private m_DTE As EnvDTE80.DTE2                                            'DTE
#End If
    Private m_addInInstance As EnvDTE.AddIn                                   'DTEʵ��

    Public m_bKeyPressEventsAfterKeyPress As Boolean                          '�Ƿ�������̺��¼�
    Public m_bKeyPressEventsBeforeKeyPress As Boolean                         '�Ƿ��������ǰ�¼�

    Public m_bAutoFormatVCCode As Boolean                                     '�Զ���ʽ��VC����
    Public m_AutoFormatCode As AutoFormatCode                                 '��ʽ������

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
            Debug.WriteLine("Events SetDTE �쳣")
        End Try
    End Sub

    '*******************************************************************************************************
    '��������DocEvents_DocumentOpened
    '��  �ܣ��ĵ����¼�
    '��  ����
    '        ByVal Document As EnvDTE.Document�������¼����ĵ�
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-4-11
    'ʱ  �䣺6:40:08
    '*******************************************************************************************************
    Private Sub DocEvents_DocumentOpened(ByVal Document As EnvDTE.Document) Handles DocEvents.DocumentOpened
        Debug.WriteLine("�ĵ����¼�")
    End Sub

    '*******************************************************************************************************
    '��������TextEditEvents_LineChanged
    '��  �ܣ������ı�/����༭���и������ƶ���������ʱ������
    '��  ����
    '        ByVal StartPoint As EnvDTE.TextPoint����ѡ�TextPoint ���󣬱�ʾ�Ѹ��ĵ��е����ס�
    '        ByVal EndPoint As EnvDTE.TextPoint����ѡ�TextPoint ���󣬱�ʾ�Ѹ��ĵ��е���β�� 
    '        ByVal Hint As Integer����ѡ�vsTextChanged ��������ʾ�¼�������һ������ԭ�����������˽⻺�����з��������顣 
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-4-11
    'ʱ  �䣺6:40:03
    '*******************************************************************************************************
    Private Sub TextEditEvents_LineChanged(ByVal StartPoint As EnvDTE.TextPoint, ByVal EndPoint As EnvDTE.TextPoint, ByVal Hint As Integer) Handles TextEditEvents.LineChanged
        Debug.WriteLine("�ı��иı��¼�")
        With m_AutoFormatCode
            .m_DTE = m_DTE
            If m_bAutoFormatVCCode Then
                .FormatCode(StartPoint, EndPoint, Hint)
            End If
        End With
    End Sub

    Private Sub SolEvents_AfterClosing() Handles SolEvents.AfterClosing
        Debug.WriteLine("�������,�رչ��̺�")
        Sol_AfterClosing()
    End Sub

    Private Sub SolEvents_Opened() Handles SolEvents.Opened
        '#If DEBUG Then
        '        Exit Sub
        '#End If
        Debug.WriteLine("����������¼���")

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

#Region "ö����Ŀ����"
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

            '��Ӻ�ͳ���
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

            '���ͷ�ļ�
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

        Debug.WriteLine("��������ر�ǰ�¼�")
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
        Debug.WriteLine("�������,���빤�̺�")
        Sol_ProjectAdded(Project)
    End Sub

    Private Sub SolEvents_ProjectRemoved(ByVal Project As EnvDTE.Project) Handles SolEvents.ProjectRemoved
        Debug.WriteLine("�������,ɾ�����̺�")
    End Sub

    Private Sub SolEvents_ProjectRenamed(ByVal Project As EnvDTE.Project, ByVal OldName As String) Handles SolEvents.ProjectRenamed
        Debug.WriteLine("�������,���������̺�")
    End Sub

    Private Sub SolEvents_Renamed(ByVal OldName As String) Handles SolEvents.Renamed
        Debug.WriteLine("�������������")
    End Sub

    Private Sub ProjectItemEvents_ItemAdded(ByVal ProjectItem As EnvDTE.ProjectItem) Handles ProjectItemEvents.ItemAdded
        Debug.WriteLine("������Ŀ")
        Pro_ItemAdded(ProjectItem)
    End Sub

    Private Sub ProjectItemEvents_ItemRemoved(ByVal ProjectItem As EnvDTE.ProjectItem) Handles ProjectItemEvents.ItemRemoved
        Debug.WriteLine("ɾ����Ŀ")
        Pro_ItemAdded(ProjectItem)
    End Sub

    Private Sub ProjectItemEvents_ItemRenamed(ByVal ProjectItem As EnvDTE.ProjectItem, ByVal OldName As String) Handles ProjectItemEvents.ItemRenamed
        Debug.WriteLine("��������Ŀ")
        Pro_ItemAdded(ProjectItem)
    End Sub

    Private Sub ProjectEvents_ItemAdded(ByVal Project As EnvDTE.Project) Handles ProjectEvents.ItemAdded
        Debug.WriteLine("������Ŀ")

    End Sub

    Private Sub ProjectEvents_ItemRemoved(ByVal Project As EnvDTE.Project) Handles ProjectEvents.ItemRemoved
        Debug.WriteLine("ɾ����Ŀ")
    End Sub

    Private Sub ProjectEvents_ItemRenamed(ByVal Project As EnvDTE.Project, ByVal OldName As String) Handles ProjectEvents.ItemRenamed
        Debug.WriteLine("��������Ŀ")
    End Sub

#If VER_2005 Then
    Private Sub KeyPressEvents_AfterKeyPress(ByVal Keypress As String, ByVal Selection As EnvDTE.TextSelection, ByVal InStatementCompletion As Boolean) Handles KeyPressEvents.AfterKeyPress
        Debug.WriteLine("�ı��ĵ����̺��¼�")
        Debug.WriteLine(Asc(Keypress))
        If m_bKeyPressEventsAfterKeyPress Then
            AfterKeyPress(Keypress)
        End If
    End Sub

    Private Sub KeyPressEvents_BeforeKeyPress(ByVal Keypress As String, ByVal Selection As EnvDTE.TextSelection, ByVal InStatementCompletion As Boolean, ByRef CancelKeypress As Boolean) Handles KeyPressEvents.BeforeKeyPress
        Debug.WriteLine("�ı��ĵ�����ǰ�¼�")
        If m_bKeyPressEventsBeforeKeyPress Then
            CancelKeypress = BeforeKeyPress(Keypress)
        End If
    End Sub
#End If

    '�����¼�
    Public Sub refEvents_ReferenceAdded(ByVal pReference As VSLangProj.Reference) Handles refEvents.ReferenceAdded
        Debug.WriteLine(pReference.Name)
    End Sub

End Class
