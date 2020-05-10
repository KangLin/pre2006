'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：OtherFunction.vb
'描  述：其它功能函数
'版  本：2005.6.*
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005-6-18
'时  间：2005-6-18 13:52:11
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************
Option Strict On
Option Explicit On 

Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If

Module OtherFunction
    '*******************************************************************************************************
    '函数名：GetMacro
    '描  述：添加c语言编译宏
    '参  数：
    '        ByVal szCode As String：代码
    '返回值：
    '版  本：2005.6.*
    '作  者：康  林
    '时  间：2005-6-15 23:49:07
    '*******************************************************************************************************
    Function GetMacro(ByVal szCode As String) As Boolean
        Dim sztemp As String, i As Integer, iMax As Integer
        Dim szBefor As String, szBack As String
        Dim Num As String
        'Num = FreeFile()
        'FileOpen(Num, g_szListTempFile, OpenMode.Append)

        sztemp = ValidCode(szCode)

        'While MatchSplitSymbol(sztemp, "const ", "=", szBefor, szBack) > 0
        '    sztemp = Trim(sztemp)
        '    If sztemp <> "" Then
        '        sztemp = StrReverse(Trim(Split(StrReverse(sztemp))(0)))
        '        If Left(sztemp, 1) = "*" Or Left(sztemp, 1) = "&" Then
        '            sztemp = Right(sztemp, Len(sztemp) - 1)
        '        End If
        '        Debug.WriteLine("加入 " & sztemp)
        '        If AddListItem(sztemp) Then
        '            Debug.WriteLine("常量增加 成功")
        '            PrintLine(Num, sztemp)
        '        Else
        '            Debug.WriteLine("常量增加 失败")
        '        End If
        '    End If
        '    sztemp = szBack
        'End While

        szCode = ValidCode(szCode)
        i = InStr(szCode, "#define ")
        While i > 0
            sztemp = Trim(Left(szCode, i - 1))
            szCode = Right(szCode, Len(szCode) - (i + Len("#define ")) + 1)
            If szCode <> "" Then
                sztemp = Split(Trim(szCode))(0)
                Debug.WriteLine("加入 " & sztemp)
                If sztemp <> "" Then
                    If InStr(sztemp, "(") > 0 Then
                        sztemp = Left(sztemp, InStr(sztemp, "(") - 1)
                    End If
                    If AddTempList(sztemp) Then
                        Debug.WriteLine("AddListItem 成功")
                        'PrintLine(Num, sztemp)
                    Else
                        Debug.WriteLine("AddListItem 失败")
                    End If
                End If
            End If

            i = InStr(szCode, "#define ")
        End While
        'FileClose(Num)
    End Function
#If VER_2003 Then
    Public Function SetComment(ByVal DTE As DTE) As String
#End If
#If VER_2005 Then
    Public Function SetComment(ByVal DTE As EnvDTE80.DTE2) As String
#End If
        Dim Sel As TextSelection, szcomment As String
        Sel = CType(DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        Select Case DTE.ActiveDocument().Language
            Case EnvDTE.Constants.dsCPP, "Visual JSharp", EnvDTE.Constants.dsJava, "CSharp"
                szcomment = "//"
            Case EnvDTE.Constants.dsVBSMacro, "Basic"
                szcomment = "'"
            Case Else
                szcomment = ""
        End Select
        Return szcomment
    End Function
End Module
