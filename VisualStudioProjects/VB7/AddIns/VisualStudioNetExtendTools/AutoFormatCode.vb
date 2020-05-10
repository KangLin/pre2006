'*******************************************************************************************************
'文件名：AutoFormatCode.vb
'功  能：自动格式化代码
'版  本：2005.3.*
'作  者：康  林
'        版权所有  保留所有权利
'E_Mail：kl222@126.com
'日  期：2005-5-5
'时  间：2005-5-5 7:59:38
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'
'FileName：AutoFormatCode.vb
'Function：
'Author  ：KangLin
'          Copyright 2005 KangLin
'E_Mail  ：kl222@126.com
'Date    ：2005-5-5
'Time    ：2005-5-5 7:59:38
'Compiler：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************

Option Strict Off
Option Explicit On 
Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If
Imports System.ComponentModel
Imports Microsoft.Win32
Imports System.Text.RegularExpressions
Imports Microsoft.VisualBasic

Public Class AutoFormatCode
#If VER_2003 Then
    Public m_DTE As EnvDTE.DTE
#End If
#If VER_2005 Then
    Public m_DTE As EnvDTE80.DTE2
#End If
    Dim Sel As TextSelection
    Public m_bAddEndIf As Boolean = True '自动格式化时，是否自动加结束块注释
    Public m_bEndIf As Boolean = False   '在任何条件下都自动修改结束块注释，当为 FALSE 时，只在有结束标志时才加
    Public m_szEndIf As String = "结束"

    '*******************************************************************************************************
    '过程名：FormatCode
    '功  能：格式化代码
    '参  数：
    '        ByVal StartPoint As EnvDTE.TextPoint：
    '        ByVal EndPoint As EnvDTE.TextPoint：
    '        ByVal Hint As Integer：
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-4-11
    '时  间：6:37:42
    '*******************************************************************************************************
    Public Sub FormatCode(ByRef StartPoint As EnvDTE.TextPoint, ByRef EndPoint As EnvDTE.TextPoint, ByVal Hint As Integer)
        Dim iStart As Integer, iEnd As Integer, iCur As Integer, iCommentStart As Integer, iCommentEnd As Integer
        Dim tp As TextPoint, iLen As Integer, iCol As Integer
        Dim szTemp As String, szOut As String

        Select Case m_DTE.ActiveDocument().Language
            Case EnvDTE.Constants.dsCPP
            Case EnvDTE.Constants.dsJava
            Case "Visual JSharp"
            Case "CSharp"
            Case Else
                Exit Sub
        End Select

        Sel = m_DTE.ActiveDocument.Selection

        iStart = StartPoint.Line
        iEnd = EndPoint.Line
        iCur = Sel.ActivePoint.Line
        iCol = Sel.ActivePoint.LineCharOffset
        Debug.WriteLine("startpoint:" & StartPoint.Line & " endpoint:" & EndPoint.Line & " Hint:" & Hint & "iCur:" & iCur & "iCol:" & iCol)
        tp = Sel.ActivePoint
        If iCur = iStart + 1 Then '光标下移一行
            Dim EditPt As EditPoint
            EditPt = EndPoint.CreateEditPoint ' Sel.AnchorPoint.CreateEditPoint
            iCommentEnd = EditPt.AbsoluteCharOffset
            If EditPt.FindPattern("/*", EnvDTE.vsFindOptions.vsFindOptionsBackwards) Then
                EditPt.StartOfLine()
                Dim iChar As Integer
                iChar = EditPt.AbsoluteCharOffset
                szTemp = EditPt.GetText(iCommentEnd - iChar)
                iCommentStart = EditPt.Line
                Dim szOutCode As String
                'Debug.WriteLine(Len(szTemp) & " " & szTemp)
                iChar = ValidCCode(szTemp, szOutCode, False, True) '情况“//*********”
                'Debug.WriteLine("输出长度：" & Len(szTemp) & " 输出：" & szTemp)
                szTemp = szOutCode
                iLen = ReverseMatchSplitSymbol(szTemp, "/*", "*/", szOut, szOut)
            Else
                Sel.MoveToPoint(EndPoint)
                Sel.MoveToPoint(StartPoint, True)
                szTemp = Sel.Text
                iLen = 0
            End If

            If iLen < 0 Then     '注释符不匹配,只有 "/*" 没有 "*/"
                '当前输入段是在注释中
                '注释不在当前输入行
                If iCommentStart <> StartPoint.Line Then
                    Sel.StartOfDocument()
                    Sel.MoveToPoint(EndPoint)

                    tp.TryToShow(vsPaneShowHow.vsPaneShowCentered)  '调整到屏幕中心
                    If iEnd = iStart Then                           '光标下移一行
                        Sel.LineDown()
                    End If
                    Exit Sub
                Else                                                '注释在当前输入行
                    '当前输入行为： a=/*....
                    Sel.GotoLine(iStart, True)
                    szTemp = Sel.Text
                End If

            Else
                If iLen > 0 Then                                    '注释符匹配
                    '形如:
                    '(1)/*...
                    '     .....
                    '     ...*/ a=b-5;
                    '和 
                    '(2)当前行包含有注释 a = /*..*/ b;
                    '(3)/*....
                    '     当前输入行：a=c;
                    '     ....*/
                    '的情况
                    Sel.MoveToPoint(EndPoint)
                    Sel.FindText("*/", EnvDTE.vsFindOptions.vsFindOptionsBackwards)
                    If Sel.ActivePoint.Line = iStart And iCommentStart <> iStart Then  '是否在输入行(1)
                        Sel.MoveToPoint(Sel.BottomPoint)
                        Sel.MoveToPoint(EndPoint, True)
                        szTemp = Left(Sel.Text, Len(Sel.Text) - 2)                     '去掉换行符 VbCrLf
                    Else                                                               '不在输入行或者注释都在输入行-情况(2)
                        Sel.GotoLine(iStart, True)
                        szTemp = Sel.Text
                    End If
                Else
                    Sel.GotoLine(iStart, True)
                    szTemp = Sel.Text
                End If
            End If

            If szTemp = "" Then
                Sel.LineDown()
                Exit Sub
            End If

            iLen = FormatVCCode(szTemp, szOut)  '得到VB的BSTR字符串的长度
            Sel.Delete()
            Sel.Insert(szOut, vsInsertFlags.vsInsertFlagsContainNewText)
            Sel.SmartFormat()                   '调用系统的格式化
            Sel.MoveToPoint(Sel.BottomPoint)


            'iLen = InStr(szOut, vbCrLf)
            'Dim szOutString As String
            'szOutString = szOut
            'While (iLen > 0)
            '    szTemp = Left(szOutString, iLen - 1)
            '    If Left(Trim(szTemp), 1) = "{" Or Left(Trim(szTemp), 1) = "}" Then
            '        Sel.Text = szTemp
            '        Sel.NewLine()
            '    Else
            '        Sel.Insert(szTemp, vsInsertFlags.vsInsertFlagsContainNewText)
            '        Sel.MoveToPoint(Sel.BottomPoint)
            '        Sel.NewLine()
            '    End If
            '    szOutString = Right(szOutString, Len(szOutString) - iLen - 1)
            '    iLen = InStr(szOutString, vbCrLf)
            'End While
            'If Left(Trim(szOutString), 1) = "{" Or Left(Trim(szOutString), 1) = "}" Then
            '    Sel.Text = szOutString
            'Else
            '    Sel.Insert(szOutString, vsInsertFlags.vsInsertFlagsContainNewText)
            '    Sel.MoveToPoint(Sel.BottomPoint)
            'End If
#If DEBUG Then
#Else
            '分析宏、常量
            GetMacro(szOut)
#End If

            tp.TryToShow(vsPaneShowHow.vsPaneShowCentered)  '调整到屏幕中心

        End If

        If iStart + 1 = iEnd Then                           '回车 

            If EndSectionBracket(EndPoint) <> "" Then       '自动增加 {}//...
                'Sel.NewLine()
                Sel.Insert(vbCrLf & "{", vsInsertFlags.vsInsertFlagsContainNewText)
                Sel.SmartFormat()
                Sel.MoveToPoint(Sel.BottomPoint)
            End If

            AddBracket(EndPoint, EndPoint.Line)             '自动添加大括号

            tp.TryToShow(vsPaneShowHow.vsPaneShowCentered)  '调整到屏幕中心

            Select Case Split(Trim(szOut))(0)
                Case "#if", "#ifdef"
                    Sel.NewLine()
                    Sel.Insert("#endif // 结束 " & szOut, vsInsertFlags.vsInsertFlagsContainNewText)
                    Sel.LineUp()
                Case Else
            End Select

        Else
            If iEnd + 1 = iCur Then                         '光标下移一行
                ModifyBracket(szOut, iStart, EndPoint)
                Sel.LineDown()
            End If
        End If

        '调整光标例的位置
        Sel.MoveToLineAndOffset(Sel.ActivePoint.Line, iCol)
    End Sub

    '*******************************************************************************************************
    '过程名：AddBracket
    '功  能：自动添加大括号
    '参  数：
    '        ByVal EndPoint As EnvDTE.TextPoint：
    '        ByVal Sel As TextSelection：
    '        ByVal iEnd As Integer：
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-4-10
    '时  间：21:22:03
    '*******************************************************************************************************
    Function AddBracket(ByRef EndPoint As EnvDTE.TextPoint, ByVal iEnd As Integer) As Boolean
        Dim Point As Integer, iPos As Integer
        Dim szTemp As String, szLeavings As String, szBefor As String, szBack As String
        Dim iRetrue As Integer, objEditPt As EditPoint, objTextDoc As TextDocument
        Dim Sel As TextSelection
        Sel = m_DTE.ActiveDocument.Selection

        objEditPt = Sel.AnchorPoint.CreateEditPoint
        objEditPt.EndOfDocument()
        iPos = objEditPt.Line
        szTemp = objEditPt.GetText(-objEditPt.AbsoluteCharOffset)
       
        '考虑去掉引号中的大括号{、小括号}
        iRetrue = ValidCCode(szTemp, szLeavings, False)
        szTemp = szLeavings
        Dim nCode As Integer, nBefor As Integer, nBack As Integer
        iRetrue = MatchSplitSymbolB(szTemp, "{", "}", szBefor, szBack, False) '用FALSE是加快速度' <a href = "..\..\..\VC7\DLL\Syntax\CSyntax.cpp#bQutation"></a>

        While iRetrue > 0 '大括号匹配
            szTemp = szBack
            iRetrue = MatchSplitSymbolB(szTemp, "{", "}", szBefor, szBack, False)
        End While

        If iRetrue < 0 Then '添加右大括号
            If m_bAddEndIf Then
                szTemp = EndSection(EndPoint, Sel) '添加 //if...
            Else
                szTemp = ""
            End If
            Sel.MoveToPoint(EndPoint)
            '添加右大括号
            'Sel.NewLine()
            Sel.Insert(vbCrLf & "}" & szTemp, vsInsertFlags.vsInsertFlagsContainNewText)
            Sel.SmartFormat()
            Sel.MoveToPoint(EndPoint)
        Else
            Sel.MoveToPoint(EndPoint)
        End If

    End Function

    '*******************************************************************************************************
    '函数名：EndSection
    '功  能：完成块的注释，详见：编程规范和范例（?2-4）
    '参  数：
    '        ByVal iEndt：
    '        Byval Sel As TextSelection：
    '返回值：
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-5-2
    '时  间：12:13:32
    '*******************************************************************************************************
    Function EndSection(ByVal Endpoint As EnvDTE.TextPoint, ByVal Sel As TextSelection) As String
        Dim szCode As String, szTemp As String
        Dim szBefor As String, szBack As String, objEditPt As EditPoint

        EndSection = ""
        szBefor = ""
        szBack = ""

        Sel.MoveToPoint(Endpoint)
        'Sel.StartOfDocument(True)
        Sel.LineUp(True, 2)
        szCode = Left(Sel.Text, Len(Sel.Text) - 3)

        Dim ir As Integer, szLeave As String

        ir = ValidCCode(szCode, szLeave)
        szCode = szLeave

        If Right(szCode, 1) = ")" Then
            ir = ReverseMatchSplitSymbol(szCode, "(", ")", szBefor, szBack)
            While ir <= 0 And (Not Sel.ActivePoint.AtStartOfDocument)
                Sel.LineUp(True)
                Sel.StartOfLine(, True)
                szCode = Left(Sel.Text, Len(Sel.Text) - 3)
                ir = ValidCCode(szCode, szLeave)
                szCode = szLeave
                ir = ReverseMatchSplitSymbol(szCode, "(", ")", szBefor, szBack)
            End While

            If ir > 0 And szBefor <> "" Then
                szTemp = StrReverse(ValidCode(szBefor))
                szTemp = Split(szTemp)(0)
                szTemp = StrReverse(szTemp)
                Select Case (szTemp)
                    Case "while"
                        szTemp = "while"
                    Case "if"
                        szTemp = "if"
                    Case "for"
                        szTemp = "for"
                    Case "switch"
                        szTemp = "switch"
                    Case Else
                        szTemp = ""
                End Select
                If szTemp <> "" Then
                    EndSection = " // " & m_szEndIf & " " & szTemp & "(" & ValidCode(szCode) & ")"
                End If
            End If
        End If

    End Function

    '*******************************************************************************************************
    '函数名：EndSectionBracket
    '功  能：完成块的注释，详见：编程规范和范例（?2-4）
    '        例如:输入 for(int i = 0; i < 10; i++)
    '             自动完成为 
    '                   for(int i = 0; i < 10; i++)
    '                   {
    '                   
    '                   } //结束 for(int i = 0; i < 10; i++)
    '参  数：
    '        ByVal Sel As TextSelection：
    '        Byval EndPoint As EnvDTE.TextPoint：
    '        ByVal iStart As Integer：插入点所在的行
    '返回值：
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-5-13
    '时  间：15:16:24
    '*******************************************************************************************************
    Function EndSectionBracket(ByRef EndPoint As EnvDTE.TextPoint) As String
        Dim szTemp As String, szBefor As String, szBack As String, szSource As String
        Dim Sel As TextSelection, objEditPt As EditPoint

        EndSectionBracket = ""
       
        Sel = m_DTE.ActiveDocument.Selection
        Sel.MoveToPoint(Sel.BottomPoint)
        'Sel.StartOfDocument(True)
        Sel.StartOfLine(, True)
        szTemp = Sel.Text
        'szTemp = ValidCode(Sel.Text)
        'objEditPt = Sel.BottomPoint.CreateEditPoint
        'szTemp = objEditPt.GetText(-objEditPt.AbsoluteCharOffset)
        Dim ir As Integer, szLeave As String
        '考虑去掉引号中的大括号{、小括号}
        ir = ValidCCode(szTemp, szLeave, False)
        szTemp = szLeave
        
        If Right(szTemp, 1) = ")" Then
            ir = ReverseMatchSplitSymbol(szTemp, "(", ")", szBefor, szBack)
            While ir <= 0
                Sel.LineUp(True)
                szTemp = Sel.Text
                ir = ValidCCode(szTemp, szLeave, False)
                szTemp = szLeave
                ir = ReverseMatchSplitSymbol(szTemp, "(", ")", szBefor, szBack)
            End While
            If ir > 0 And szBefor <> "" Then
                szTemp = StrReverse(ValidCode(szBefor))
                szTemp = Split(szTemp)(0)
                szTemp = StrReverse(szTemp)
                Select Case (szTemp)
                    Case "while"
                        szTemp = "while"
                    Case "if"
                        szTemp = "if"
                    Case "for"
                        szTemp = "for"
                    Case "switch"
                        szTemp = "switch"
                    Case Else
                        szTemp = ""
                End Select
                If szTemp <> "" Then
                    EndSectionBracket = "{"
                    Sel.MoveToPoint(Sel.BottomPoint)
                    Exit Function
                End If
            End If
        End If
        Sel.MoveToPoint(Sel.BottomPoint)
    End Function

    '*******************************************************************************************************
    '函数名：ModifyBracket
    '描  述：自动修改大括号后的注释。
    '        只有在关键字同行修改时，才能成功，如果不在关键字同行，则不能进行相应的修改。
    '参  数：
    '        ByVal szCode As String            ：修改的代码
    '        ByVal iStart As Integer           ：开始行
    '        ByVal EndPoint As EnvDTE.TextPoint：
    '返回值：
    '版  本：2005.6.*
    '作  者：康  林
    '时  间：2005-6-23 10:26:09
    '*******************************************************************************************************
    Public Function ModifyBracket(ByVal szCode As String, ByVal iStart As Integer, ByVal EndPoint As EnvDTE.TextPoint) As Boolean
#If DEBUG Then
#Else
        on error Resume Next 
#End If

        Dim iIf As Integer, iWhile As Integer, iFor As Integer, iSwitch As Integer, iLine As Integer
        Dim Sel As TextSelection, szTemp As String, szBefor As String, szBack As String, szKey As String
        Dim nCode As Integer

        Select Case m_DTE.ActiveDocument().Language
            Case EnvDTE.Constants.dsCPP
            Case EnvDTE.Constants.dsJava
            Case "Visual JSharp"
            Case "CSharp"
            Case Else
                Exit Function
        End Select
        Sel = m_DTE.ActiveDocument.Selection

        ValidCCode(szCode, szTemp)
        szCode = szTemp

        ModifyBracket = False
        Dim szPattern As String
        Dim r As Regex
        szPattern = "(?<Key>if|for|while|switch)\s*\("
        r = New Regex(szPattern)
        Dim m As Match
        m = r.Match(szCode)
        If m.Success Then
            szKey = m.Groups("Key").Value
        Else
            Return False
        End If
       
        iLine = 0
        Sel.GotoLine(iStart)
        Sel.SelectLine()
        szTemp = Sel.Text
ModifyBracket_Loop:
        While (MatchSplitSymbolB(szTemp, "{", "}") <= 0 And Not Sel.ActivePoint.AtEndOfDocument)   '没有符号或不匹配
            iLine = iLine + 1
            Sel.GotoLine(iStart + iLine)
            Sel.SelectLine()
            szTemp = szTemp & Sel.Text
        End While
        If m_bEndIf Then
            If Not Sel.ActivePoint.AtEndOfDocument Then
                Sel.GotoLine(iStart + iLine + 1)
            End If
            Sel.SelectLine()
            If InStr(Sel.Text, "else") = 0 Then
                Sel.GotoLine(iStart + iLine)
                szTemp = szCode
                Dim i As Integer
                i = 0
                While (MatchSplitSymbolB(szTemp, "(", ")") <= 0 And Not Sel.ActivePoint.AtEndOfDocument)
                    i = i + 1
                    Sel.GotoLine(iStart + i)
                    Sel.SelectLine()
                    szTemp = szTemp & Sel.Text
                End While
                szTemp = "} // " & m_szEndIf & " " & szKey & "(" & szTemp & ")"
                szTemp = DeleteSpace(TrimString(szTemp))
                Sel.StartOfLine()
                Sel.FindText("}")
                Sel.MoveToPoint(Sel.AnchorPoint)
                Sel.EndOfLine(True)
                Sel.Insert(szTemp, vsInsertFlags.vsInsertFlagsContainNewText)
                Sel.MoveToPoint(EndPoint)
            Else
                iLine = iLine + 1
                Sel.GotoLine(iStart + iLine)
                Sel.SelectLine()
                If InStr(ValidCode(Sel.Text), "else") > 0 Then
                    szTemp = Sel.Text
                    GoTo ModifyBracket_Loop
                End If
            End If
        Else

            If InStr(Sel.Text, m_szEndIf) Then
                szTemp = szCode
                Dim i As Integer
                i = 0
                While (MatchSplitSymbolB(szTemp, "(", ")") <= 0 And Not Sel.ActivePoint.AtEndOfDocument)
                    i = i + 1
                    Sel.GotoLine(iStart + i)
                    Sel.SelectLine()
                    szTemp = szTemp & Sel.Text
                End While
                szTemp = m_szEndIf & " " & szKey & "(" & szTemp & ")"
                szTemp = DeleteSpace(TrimString(szTemp))
                Sel.GotoLine(iStart + iLine)
                Sel.StartOfLine()
                Sel.FindText(m_szEndIf)
                Sel.MoveToPoint(Sel.AnchorPoint)
                Sel.EndOfLine(True)
                Sel.Insert(szTemp, vsInsertFlags.vsInsertFlagsContainNewText)
                Sel.MoveToPoint(EndPoint)
            Else
                iLine = iLine + 1
                Sel.GotoLine(iStart + iLine)
                Sel.SelectLine()
                If InStr(ValidCode(Sel.Text), "else") > 0 Then
                    szTemp = Sel.Text
                    GoTo ModifyBracket_Loop
                End If
            End If
        End If
    End Function

    Public Sub New()
        Dim Key As RegistryKey, iVal As Integer = 0
        Key = Registry.LocalMachine.OpenSubKey("SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\结束块注释", True)
        If Not Key Is Nothing Then
            With Key
                m_bEndIf = .GetValue("修改时任何情况下自动修改结束注释", False)
                m_bAddEndIf = .GetValue("格式化时自动增加结束块注释", True)
                m_szEndIf = .GetValue("结束注释块字符", "结束")
            End With
        End If
    End Sub


End Class

