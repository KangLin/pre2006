'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：Delete.vb
'描  述：删除工具实现文件。删除菜单栏、工具栏上的项目
'版  本：2005.6.1.0
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005年7月4日
'时  间：18:56:22
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
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

#Region "过程"

    '*******************************************************************************************************
    '函数名：DeleteTool
    '描  述：删除菜单和工具条
    '注  意：要新加一个命令时，要修改三个地方
    '        1、修改 LoadCommand ，在菜单和工具条增加一个命令
    '        2、修改 exec 过程，增加相应的函数调用
    '        3、修改 DeleteTool 过程，删除相应的菜单
    '参  数：无
    '返回值：类型为 Boolean 。
    '版  本：2007.9.1.0
    '作  者：康  林
    '时  间：2007年8月17日 14:16:18
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
                Case "注释", "删除", "自动", "其它工具", "VC工具", "设置", "工具栏", "超链接", "注释项", "C 语言工具", "扩展工具集(&X)"
                    m_DTE.Commands.RemoveCommandBar(cmdBar)
            End Select
        Next

#If VER_2005 Then
        '删除菜单中的工具条
        DeleteCommandBarInMenu("扩展工具集(&X)")
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
        objCommands.Item("VisualStudioNetExtendTools.Connect.删除工具栏").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.删除命令").Delete()
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

    Public Sub 删除工具栏()
        Dim i As Integer
        Dim szRe As String

        While 1
            szRe = InputBox("请输入要删除工具栏的名称：")
            If szRe = "" Then
                Exit While
            End If
            i = DeleteCommandBar(szRe)
            If i Then
                Debug.WriteLine("成功删除工具栏：" & szRe & ";共 " & i & " 个")
                MsgBox("成功删除工具栏：" & szRe & ";共 " & i & " 个")
                Exit Sub
            End If
        End While
    End Sub

    Public Sub 删除命令()
        Dim szRe As String
        Dim i As Integer
        While 1
            szRe = InputBox("请输入要删除命令的名称：")
            If szRe = "" Then
                Exit While
            End If
            i = DeleteCommand(szRe)
            If i Then
                Debug.WriteLine("成功删除命令：" & szRe & ";共 " & i & " 个")
                MsgBox("成功删除命令：" & szRe & ";共 " & i & " 个")
                Exit Sub
            End If
        End While
    End Sub

#End Region

#Region "函数"

    '*******************************************************************************************************
    '函数名：DeleteCommandBar
    '功  能：删除指定的工具栏
    '参  数：
    '        ByVal CommandBarName As String：要删除的工具栏名
    '返回值：删除的个数
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-3-26
    '时  间：9:54:41
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
    '函数名：DeleteCommand
    '功  能：
    '参  数：
    '        ByVal CommandName As String：
    '返回值：
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-3-26
    '时  间：11:08:13
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
        Dim objMenu As CommandBar  '菜单栏
        Dim obj As CommandBarControl
        objMenu = m_DTE.CommandBars.ActiveMenuBar '当前菜单栏
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
