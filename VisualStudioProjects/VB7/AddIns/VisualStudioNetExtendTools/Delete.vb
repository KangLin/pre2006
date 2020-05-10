'*******************************************************************************************************
'��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
'�ļ�����Delete.vb
'��  ����ɾ������ʵ���ļ���ɾ���˵������������ϵ���Ŀ
'��  ����2005.6.1.0
'��  �ߣ���  ��
'E_Mail��kl222@126.com
'��  �ڣ�2005��7��4��
'ʱ  �䣺18:56:22
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
'*******************************************************************************************************
Option Strict Off
Option Explicit On 
Imports EnvDTE
Imports System.Diagnostics

#If VER_2003 Then
Imports Microsoft.Office.Core
#End If
#If VER_2005 Then
Imports EnvDTE80
Imports Microsoft.VisualStudio.CommandBars
#End If

Public Class Delete
#If VER_2003 Then
    Public m_DTE As EnvDTE.DTE
#End If
#If VER_2005 Then
    Public m_DTE As EnvDTE80.DTE2
#End If

#Region "����"

    '*******************************************************************************************************
    '��������DeleteTool
    '��  ����ɾ���˵��͹�����
    'ע  �⣺Ҫ�¼�һ������ʱ��Ҫ�޸������ط�
    '        1���޸� LoadCommand ���ڲ˵��͹���������һ������
    '        2���޸� exec ���̣�������Ӧ�ĺ�������
    '        3���޸� DeleteTool ���̣�ɾ����Ӧ�Ĳ˵�
    '��  ������
    '����ֵ������Ϊ Boolean ��
    '��  ����2007.9.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��17�� 14:16:18
    '*******************************************************************************************************
    Public Function DeleteTool() As Boolean
        On Error Resume Next
        DeleteTool = False
        Dim objCommands As Commands
        objCommands = m_DTE.Commands

        Dim cmdBar As CommandBar
        Dim CommandBarName As String
        For Each cmdBar In m_DTE.CommandBars
            CommandBarName = cmdBar.Name
            Select Case CommandBarName
                Case "ע��", "ɾ��", "�Զ�", "��������", "VC����", "����", "������", "������", "ע����", "C ���Թ���", "��չ���߼�(&X)"
                    m_DTE.Commands.RemoveCommandBar(cmdBar)
            End Select
        Next

#If VER_2005 Then
        'ɾ���˵��еĹ�����
        DeleteCommandBarInMenu("��չ���߼�(&X)")
#End If

        objCommands.Item("VisualStudioNetExtendTools.Connect.FunctionComment").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.CommentTRACE").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.UncommentTRACE").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AlignComment").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AlignComment1").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AlignPointSign").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AlignPointSign1").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AddEndIf").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.SwitchCppToH").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.Modify").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.ɾ��������").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.ɾ������").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AutoFomatVCCode").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.IncludeFile").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.GetFileRelativePath").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.GetDate").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.GetTime").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.ModifyEndLineComment").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AutoDispConstOrMacro").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AboutExtendTools").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.SetFunctionCommentPara").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.Delete").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.OtherTools").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.VCTools").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.Comments").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.Help").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.CreateBookMark").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.CreateHyperlink").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.GoHyperlink").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.SetFunctionCommentPara").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.OtherSettings").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.Registry").Delete()
        Return True
    End Function

    Public Sub ɾ��������()
        Dim i As Integer
        Dim szRe As String

        While 1
            szRe = InputBox("������Ҫɾ�������������ƣ�")
            If szRe = "" Then
                Exit While
            End If
            i = DeleteCommandBar(szRe)
            If i Then
                Debug.WriteLine("�ɹ�ɾ����������" & szRe & ";�� " & i & " ��")
                MsgBox("�ɹ�ɾ����������" & szRe & ";�� " & i & " ��")
                Exit Sub
            End If
        End While
    End Sub

    Public Sub ɾ������()
        Dim szRe As String
        Dim i As Integer
        While 1
            szRe = InputBox("������Ҫɾ����������ƣ�")
            If szRe = "" Then
                Exit While
            End If
            i = DeleteCommand(szRe)
            If i Then
                Debug.WriteLine("�ɹ�ɾ�����" & szRe & ";�� " & i & " ��")
                MsgBox("�ɹ�ɾ�����" & szRe & ";�� " & i & " ��")
                Exit Sub
            End If
        End While
    End Sub

#End Region

#Region "����"

    '*******************************************************************************************************
    '��������DeleteCommandBar
    '��  �ܣ�ɾ��ָ���Ĺ�����
    '��  ����
    '        ByVal CommandBarName As String��Ҫɾ���Ĺ�������
    '����ֵ��ɾ���ĸ���
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-3-26
    'ʱ  �䣺9:54:41
    '*******************************************************************************************************
    Function DeleteCommandBar(ByVal CommandBarName As String) As Integer
        Dim cmdBar As CommandBar
        DeleteCommandBar = 0
        For Each cmdBar In m_DTE.CommandBars
            Debug.Print(cmdBar.Name)
            If LCase(Trim(cmdBar.Name)) = LCase(Trim(CommandBarName)) Then
                m_DTE.Commands.RemoveCommandBar(cmdBar)
                DeleteCommandBar = DeleteCommandBar + 1
            End If
        Next
    End Function

    '*******************************************************************************************************
    '��������DeleteCommand
    '��  �ܣ�
    '��  ����
    '        ByVal CommandName As String��
    '����ֵ��
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-3-26
    'ʱ  �䣺11:08:13
    '*******************************************************************************************************
    Function DeleteCommand(ByVal CommandName As String) As Integer
        Dim cmd As Command
        DeleteCommand = 0
        For Each cmd In m_DTE.Commands
            Debug.WriteLine(cmd.Name)
            If LCase(Trim(cmd.Name)) = LCase(Trim(CommandName)) Then
                cmd.Delete()
                DeleteCommand = DeleteCommand + 1
            End If
        Next
    End Function

#If VER_2005 Then
    Function DeleteCommandBarInMenu(ByVal CommandBarName As String) As Integer
        Dim objMenu As CommandBar  '�˵���
        Dim obj As CommandBarControl
        objMenu = m_DTE.CommandBars.ActiveMenuBar '��ǰ�˵���
        For Each obj In objMenu.Controls
            'Debug.Print(objMenu.Name)
            'Debug.Print(objMenu.Controls(4).Caption)
            'objMenu.Controls(4).Delete()
            If obj.Caption = CommandBarName Then
                obj.Delete()
            End If
        Next
    End Function
#End If

#End Region
End Class
