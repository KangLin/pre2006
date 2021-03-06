Option Strict Off
Option Explicit On 
Imports EnvDTE
Imports System.Diagnostics
Imports Microsoft.Office.Core

Public Module 删除

    Sub DeleteTool()
        On Error Resume Next
        Dim objCommands As Commands
        objCommands = DTE.Commands

        Dim cmdBar As CommandBar
        Dim CommandBarName As String
        For Each cmdBar In DTE.CommandBars
            CommandBarName = cmdBar.Name
            Select Case CommandBarName
                Case "注释", "删除", "自动", "其它工具", "VC工具", "扩展工具集(&X)", "设置", "工具栏"
                    DTE.Commands.RemoveCommandBar(cmdBar)
            End Select
        Next
        
        objCommands.Item("VisualStudioNetExtendTools.Connect.FunctionComment").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.CommentTRACE").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.UncommentTRACE").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AlignComment").Delete()
        objCommands.Item("VisualStudioNetExtendTools.Connect.AlignComment1").Delete()
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
    End Sub

End Module

