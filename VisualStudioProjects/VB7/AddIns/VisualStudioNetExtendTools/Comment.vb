'*******************************************************************************************************
'文件名：Comment.vb
'功  能：给代码添加注释
'版  本：2005.3.*
'作  者：康  林
'        版权所有  保留所有权利
'E_Mail：kl222@126.com
'日  期：2005-5-5
'时  间：2005-5-5 7:54:47
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'
'FileName：Comment.vb
'Function：
'Author  ：KangLin
'          Copyright 2005 KangLin
'E_Mail  ：kl222@126.com
'Date    ：2005-5-5
'Time    ：2005-5-5 7:54:47
'Compiler：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************

Option Strict Off
Option Explicit On 
Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If
Imports Microsoft.Win32
Imports System.Text.RegularExpressions

Public Class Comment

#Region "用户可修改的常量"

    Public g_szAuthor As String = "康  林"    '作者
    Public g_szCorporation As String = "康林工作室" '公司
    Public g_szEAuthor As String = "KangLin"
    Public g_szECorporation As String = "KangLin Studio"
    Public g_szEmail As String = "kl222@126.com"

    '1、中文
    '2、英文
    Public g_iLanguage As Integer = 1
    Public g_bFunctionAuthor As Boolean = True   '函数注释时是否加作者
    Public g_bFunctionDate As Boolean = True   '函数注释时是否加日期
    Public g_bFunctionVersion As Boolean = True   '函数注释时是否加版本

    Public m_szSubName As String = "过程名："
    Public m_szFunctionName As String = "函数名："
    Public m_szClassName As String = "类  名："
    Public m_szDescription As String = "描  述："
    Public m_szPara As String = "参  数："
    Public m_szReturnVal As String = "返回值："
    Public m_szVersion As String = "版  本："
    Public m_szAuthor As String = "作  者："
    Public m_szDate As String = "时  间："

    '变量
    Dim g_lVersion As String   '版本号
    Dim g_szCompiler As String  '编译器版本

    '用于注释方式的控制
    Public g_bDoxygen As Boolean = True

#If VER_2003 Then
    Public m_DTE As EnvDTE.DTE  '
#End If
#If VER_2005 Then
    Public m_DTE As EnvDTE80.DTE2
#End If
#End Region

#Region "常量，用户不用修改"
    Const gc_szCLineCommentSymbol As String = "//"  'C语言的行注释符
    Const gc_szMarcoLineCommentSymbol As String = "'"  '宏的行注释符
    '注释开始符
    Const gc_szStartCommentSymbol As String = "/*******************************************************************************************************"
    '注释结束符
    Const gc_szEndCommentSymbol As String = "*******************************************************************************************************/"
    '宏注释开始符
    Const gc_szMarcoStartCommentSymbol As String = "'*******************************************************************************************************"
    '宏注释结束符
    Const gc_szMarcoEndCommentSymbol As String = "'*******************************************************************************************************"
    '完成同一功能的函数块开始符
    Const gc_szFunctionSectionStart As String = "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
    '完成同一功能的函数块结束符
    Const gc_szFunctionSectionEnd As String = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
    '在函数内完成同一功能的语句块开始符
    Const gc_szSentenceSectionStart As String = "------------------------------------------------------------------------"
    '在函数内完成同一功能的语句块结束符
    Const gc_szSentenceSectionEnd As String = "------------------------------------------------------------------------"
    'Const gc_szCompiler = "Visual C++ 6.0"

#End Region

#Region "函数"

    Function ActiveDocument() As Document
        ActiveDocument = m_DTE.ActiveDocument()
    End Function

    '*******************************************************************************************************
    '函数名：ListProj
    '描  述：
    '参  数：
    '        ByVal projitems As ProjectItems        ：
    '        ByVal Level As Integer                 ：
    '        Optional ByRef bFlag As Boolean = False：
    '返回值：无
    '版  本：2005.8.0.0
    '作  者：康  林
    '时  间：2005年8月12日 18:07:26
    '*******************************************************************************************************
    Function ListProj(ByVal projitems As ProjectItems, ByVal Level As Integer, Optional ByRef bFlag As Boolean = False)
#If DEBUG Then
#Else
        on error Resume Next 
#End If

        Dim projitem As ProjectItem
        Dim Sel As TextSelection
        Dim szTemp As String
        Dim FileNum As Integer

        If bFlag Then
            Exit Function
        End If

        For Each projitem In projitems
            If ActiveDocument.Language = EnvDTE.Constants.dsCPP Then
                If Trim(LCase(projitem.Name)) = "assemblyinfo.cpp" Then
                    projitem.Open()
                    projitem.Document.Activate()
                    Sel = ActiveDocument.Selection
                    Sel.StartOfDocument()
                    Sel.FindText("AssemblyVersionAttribute")
                    Sel.SelectLine()
                    g_lVersion = Trim(Split(ValidCode(Sel.Text), Chr(34))(1))
                    bFlag = True
                    Exit Function
                End If

                If LCase(GetFileExt(projitem.Name)) = LCase("rc") Then
                    FileNum = FreeFile()
                    FileOpen(FileNum, projitem.FileNames(0), OpenMode.Input)

                    While Not EOF(FileNum)
                        szTemp = LineInput(FileNum)
                        If InStr(szTemp, "FILEVERSION ") > 0 Then
                            g_lVersion = Split(szTemp, "FILEVERSION ")(1)
                            g_lVersion = Trim(Replace(g_lVersion, ",", "."))
                            Exit While
                        End If
                    End While
                    FileClose(FileNum)
                    bFlag = True
                    Exit Function
                End If
            End If

            If ActiveDocument.Language = "Basic" Then
                If Trim(LCase(projitem.Name)) = "assemblyinfo.vb" Then
                    projitem.Open()
                    projitem.Document.Activate()
                    Sel = ActiveDocument.Selection
                    Sel.StartOfDocument()
                    Sel.FindText("AssemblyVersion")
                    Sel.SelectLine()
                    g_lVersion = Trim(Split(ValidCode(Sel.Text), Chr(34))(1))
                    bFlag = True
                    Exit Function
                End If
            End If

            'MsgBox("Project item: " & projitem.Name, Level)
            ' Recurse if the project item has sub-items...
            Dim projitems2 As ProjectItems
            projitems2 = projitem.ProjectItems
            Dim notsubcoll As Boolean = projitems2 Is Nothing
            If Not notsubcoll Then
                ListProj(projitems2, Level + 1)
            End If
        Next
    End Function

    '*******************************************************************************************************
    '函数名：GetVerSion
    '功  能：得到版本号
    '参  数：无
    '返回值：版本号
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：18:58:32
    '*******************************************************************************************************
    Function GetVerSion() As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If

        Dim OldDocument As Document
        g_lVersion = "1.0"
        OldDocument = ActiveDocument()
        ListProj(ActiveDocument.ProjectItem.ContainingProject.ProjectItems, 0)
        OldDocument.Activate()

    End Function

    '*******************************************************************************************************
    '函数名：GetCompiler
    '功  能：得到编译器
    '参  数：无
    '返回值：编译器
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：18:58:32
    '*******************************************************************************************************
    Function GetCompiler() As String
        g_szCompiler = m_DTE.Name & " " & m_DTE.Version & " —— " & ActiveDocument().Language & " " & m_DTE.Version
    End Function

    '*******************************************************************************************************
    '函数名：GetFunctionReturn
    '描  述：得到函数返回值
    '参  数：
    '        ByVal szCode：代码
    '返回值：String
    '版  本：2005.6.1.0
    '作  者：康  林
    '时  间：2005年7月14日 10:17:34
    '*******************************************************************************************************
    Function GetFunctionReturn(ByVal szCode) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If
        GetFunctionReturn = ""
        Dim iPos As Integer, szTemp As String, szLeft As String, i As Integer, szLeave As String
        szCode = ValidCode(szCode)
        If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
            iPos = InStr(1, szCode, "(")
            If iPos Then
                szCode = Left(szCode, iPos - 1)
                iPos = Split(szCode, " ").GetUpperBound(0)
                szTemp = Left(Split(szCode)(iPos), 1)
                For i = 0 To iPos - 1
                    If i Then
                        szLeft = szLeft + " " + Split(szCode)(i)
                    Else
                        szLeft = Split(szCode)(i)
                    End If
                Next i
                szLeave = szLeft
                If iPos Then
                    szTemp = Left(Split(szCode)(iPos), 1)
                    If szTemp = "*" Or szTemp = "&" Then
                        szLeft = szLeft + szTemp
                    End If
                End If

                szTemp = ""
                Select Case iPos
                    Case 0
                        If g_iLanguage And 1 Then
                            GetFunctionReturn = "无"
                        Else
                            GetFunctionReturn = "void"
                        End If
                    Case 1
                        szTemp = szLeft & " 。"
                    Case 2
                        If Split(szCode)(0) = "extern" Or Split(szCode)(0) = "static" Then
                            szTemp = Left(Split(szCode)(iPos), 1)
                            If szTemp = "*" Or szTemp = "&" Then
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & szTemp & " 。"
                            Else
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & " 。"
                            End If
                        Else
                            szTemp = szLeft & " 。"
                        End If
                    Case Else
                        If Split(szCode)(0) = "static" Then
                            szTemp = Left(Split(szCode)(iPos), 1)
                            If szTemp = "*" Or szTemp = "&" Then
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & szTemp & " 。"
                            Else
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & " 。"
                            End If
                        ElseIf Split(szCode)(0) = "extern" And UCase(Split(szCode)(1)) = """C""" Then
                            szTemp = Left(Split(szCode)(iPos), 1)
                            If szTemp = "*" Or szTemp = "&" Then
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0)) - Len(Split(szCode)(2)) - 1) & szTemp & " 。"
                            Else
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0)) - Len(Split(szCode)(2)) - 1) & " 。"
                            End If
                        Else
                            szTemp = szLeft & " 。"
                        End If
                End Select
                If Trim(szTemp) = "template 。" Then
                    szTemp = ""
                End If
                If szTemp <> "" Then
                    GetFunctionReturn = "类型为 " & szTemp
                End If
                If GetFunctionReturn = "void" And (g_iLanguage And 1) Then
                    GetFunctionReturn = "无"
                End If
            End If
        Else
            Dim szBefor As String, szBack As String
            iPos = MatchSplitSymbol(szCode, "(", ")", szBefor, szBack)
            If iPos > 0 Then
                iPos = InStrRev(LCase(szBack), " as ")
                If iPos Then
                    GetFunctionReturn = "类型为 " & Right(szBack, Len(szBack) - iPos - 3) & " 。"
                    Exit Function
                End If
            End If
            If g_iLanguage And 1 Then
                GetFunctionReturn = "无"
            Else
                GetFunctionReturn = "void"
            End If
        End If
    End Function

    '*******************************************************************************************************
    '函数名：FileDoxgenCommentString
    '描  述：用于得到 Doxgen 生成帮助的文件注释
    '参  数：void
    '返回值：类型为 String 。
    '版  本：2006.12.1.0
    '作  者：KangLin
    '时  间：2007年5月13日 18:58:40
    '*******************************************************************************************************
    Function FileDoxgenCommentString() As String
        Dim Sel As TextSelection
        Sel = ActiveDocument.Selection
        Sel.Insert("/*!" & vbCrLf)
        If g_iLanguage And 1 Then
            Sel.Insert("\warning 版权所有 (C) " & Year(Date.Today()) & " " & g_szCorporation & "；保留所有权利。" & vbCrLf)
            Sel.Insert("\file    " & ActiveDocument.Name & vbCrLf)
            Sel.Insert("\brief   详细描述" & vbCrLf)
            Sel.Insert("\version " & g_lVersion & vbCrLf _
                     & "\author  " & g_szAuthor _
                     & " (" & g_szEmail & ")" & vbCrLf _
                     & "\date    " & Now().ToLongDateString & "  " & Now().ToLongTimeString & vbCrLf)
            Sel.Insert("\par     编译器:" & vbCrLf _
                     & "         " & g_szCompiler & vbCrLf)
        End If
        If g_iLanguage And 2 Then
            Sel.Insert("\warning Copyright (C) " & Year(Date.Today()) & " " & g_szECorporation & ";All rights reserved." & vbCrLf)
            Sel.Insert("\file    " & ActiveDocument.Name & vbCrLf)
            Sel.Insert("\brief   Description" & vbCrLf)
            Sel.Insert("\version " & g_lVersion & vbCrLf _
                     & "\author  " & g_szEAuthor _
                     & " (" & g_szEmail & ")" & vbCrLf _
                     & "\date    " & Now() & vbCrLf)
            Sel.Insert("\par     Compiler:" & vbCrLf & "         " & g_szCompiler & vbCrLf)
        End If
        Sel.Insert("*/")
    End Function

    '*******************************************************************************************************
    '函数名：FileCommentString
    '功  能：得到文件的注释
    '参  数：无
    '返回值：文件注释字符串
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-8-17
    '时  间：19:45:54
    '*******************************************************************************************************
    Function FileCommentString() As String
        Dim Sel As TextSelection
        Sel = ActiveDocument.Selection
        'VC工程
        If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
            '允许生成doxgen注释
            If g_bDoxygen Then
                FileCommentString = FileDoxgenCommentString()
            Else

                'Sel.Text = gc_szStartCommentSymbol & vbCrLf
                Sel.Insert(gc_szStartCommentSymbol & vbCrLf)
                If g_iLanguage And 1 Then
                    'Sel.Text =
                    Sel.Insert("版权所有 (C) " & Year(Date.Today()) & " " & g_szCorporation & "；保留所有权利。" & vbCrLf _
                       & "文件名：" & ActiveDocument.Name & vbCrLf _
                       & "描  述：" & vbCrLf _
                       & "版  本：" & g_lVersion & vbCrLf _
                       & "作  者：" & g_szAuthor & vbCrLf)
                    Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                    'Sel.Text = 
                    Sel.Insert("E_Mail：" & g_szEmail & vbCrLf _
                                       & "日  期：" & Now().ToLongDateString & vbCrLf _
                                       & "时  间：" & Now().ToLongTimeString & vbCrLf _
                                       & "编译器：" & g_szCompiler & vbCrLf)
                End If
                If g_iLanguage = 3 Then
                    'Sel.Text = vbCrLf
                    Sel.Insert(vbCrLf)
                End If
                If g_iLanguage And 2 Then
                    'Sel.Text =
                    Sel.Insert("Copyright (C) " & Year(Date.Today()) & " " & g_szECorporation & ";All rights reserved." & vbCrLf _
                                             & "FileName   ：" & ActiveDocument.Name & vbCrLf _
                                             & "Description：" & vbCrLf _
                                             & "Version    ：" & g_lVersion & vbCrLf _
                                             & "Author     ：" & g_szEAuthor & vbCrLf)
                    Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                    'Sel.Text = 
                    Sel.Insert("E_Mail     ：" & g_szEmail & vbCrLf _
                                             & "Date       ：" & Now().Date() & vbCrLf _
                                             & "Time       ：" & Now().ToLongTimeString & vbCrLf _
                                             & "Compiler   ：" & g_szCompiler & vbCrLf)
                End If
                'Sel.Text = 
                Sel.Insert(gc_szEndCommentSymbol)
            End If
        End If

        'VB工程
        If ActiveDocument.Language = "Basic" Then
            Sel.Text = gc_szMarcoStartCommentSymbol & vbCrLf
            If g_iLanguage And 1 Then
                'Sel.Text =
                Sel.Insert("'版权所有 (C) " & Year(Date.Today) & " " & g_szCorporation & "；保留所有权利。" & vbCrLf _
                      & "'文件名：" & ActiveDocument.Name & vbCrLf _
                      & "'描  述：" & vbCrLf _
                      & "'版  本：" & g_lVersion & vbCrLf _
                      & "'作  者：" & g_szAuthor & vbCrLf)

                Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                'Sel.Text =
                Sel.Insert("'E_Mail：" & g_szEmail & vbCrLf _
                      & "'日  期：" & Now().ToLongDateString & vbCrLf _
                      & "'时  间：" & Now().ToLongTimeString & vbCrLf _
                      & "'编译器：" & g_szCompiler & vbCrLf)
            End If
            If g_iLanguage = 3 Then
                Sel.Text = "'" & vbCrLf
            End If
            If g_iLanguage And 2 Then
                'Sel.Text =
                Sel.Insert("'Copyright (C) " & Year(Date.Today()) & " " & g_szECorporation & ";All rights reserved." & vbCrLf _
                         & "'FileName   ：" & ActiveDocument.Name & vbCrLf _
                         & "'Description：" & vbCrLf _
                         & "'Version    ：" & g_lVersion & vbCrLf _
                         & "'Author     ：" & g_szEAuthor & vbCrLf)
                Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                'Sel.Text =
                Sel.Insert("'E_Mail     ：" & g_szEmail & vbCrLf _
                         & "'Date       ：" & Now().ToLongDateString & vbCrLf _
                         & "'Time       ：" & Now().ToLongTimeString & vbCrLf _
                         & "'Compiler   ：" & g_szCompiler & vbCrLf)
            End If
            Sel.Text = gc_szMarcoEndCommentSymbol
        End If

    End Function

    '*******************************************************************************************************
    '函数名：GetFunctionParamters
    '功  能：得到参数列表
    '修改:当有模块做参数时a(CList<T,T> p) ,参数出错．
    '参  数：
    '        ByVal szCode：代码
    '返回值：参数列表
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：15:02:44
    '*******************************************************************************************************
    Function GetFunctionParamters(ByVal szCode As String) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If

        Dim szTemp As String, i As Integer, j As Integer
        Dim szPara As String, iLen As Integer
        Dim szBefor As String, szBack As String
        iLen = 0
        szTemp = ValidCode(szCode)
        MatchSplitSymbolB(szCode, "(", ")") '得到括号中的参数
        szTemp = ValidCode(szCode)

        If szTemp = "" Then '无参数
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                If g_iLanguage And 1 Then
                    GetFunctionParamters = "无" & vbCrLf
                Else
                    GetFunctionParamters = "void" & vbCrLf
                End If
            End If
            If ActiveDocument.Language = "Basic" Then
                If g_iLanguage And 1 Then
                    GetFunctionParamters = "无"
                Else
                    GetFunctionParamters = "void"
                End If
            End If
        Else '有参数
            '考虑到括号中有逗号的情况
            GetFunctionParamters = CommaInBracket(szTemp)

            '对齐分号
            szPara = ""
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                j = UBound(Split(GetFunctionParamters, "：" & vbCrLf))
                For i = 0 To j - 1 '得到参数长度
                    szTemp = Split(GetFunctionParamters, "：" & vbCrLf)(i)
                    If Len(szTemp) > iLen Then
                        iLen = Len(szTemp)
                    End If
                Next i

                For i = 0 To j - 1 '得到参数长度
                    szTemp = Split(GetFunctionParamters, "：" & vbCrLf)(i)
                    If iLen - Len(szTemp) > 0 Then
                        szPara = szPara & szTemp & Space(iLen - Len(szTemp)) & "：" & vbCrLf
                    Else
                        szPara = szPara & szTemp & "：" & vbCrLf
                    End If
                Next i

                If szPara <> "" Then
                    GetFunctionParamters = vbCrLf & "        " & szPara
                End If
            End If

            If ActiveDocument.Language = "Basic" Then
                j = UBound(Split(GetFunctionParamters, vbCrLf))
                For i = 0 To j  '得到参数长度
                    szTemp = Split(GetFunctionParamters, vbCrLf)(i)
                    If Len(szTemp) > iLen Then
                        iLen = Len(szTemp)
                    End If
                Next i

                For i = 1 To j  '得到参数长度
                    szTemp = Split(GetFunctionParamters, vbCrLf)(i)
                    If iLen - Len(szTemp) > 0 Then
                        szPara = szPara & vbCrLf & Left(szTemp, Len(szTemp) - 1) & Space(iLen - Len(szTemp)) & "："
                    Else
                        szPara = szPara & vbCrLf & szTemp
                    End If
                Next i

                If szPara <> "" Then
                    GetFunctionParamters = szPara
                End If
            End If
        End If
    End Function

    '*******************************************************************************************************
    '函数名：CommaInBracket
    '功  能：考虑参数中有括号，且括号中有逗号的情况
    '参  数：
    '        ByVal szCode：代码
    '返回值：参数列表
    '作  者：康  林
    '版  本：1.0
    '日  期：2006-11-4
    '时  间：17:29:44
    '*******************************************************************************************************
    Function CommaInBracket(ByVal szCode As String) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If
        Dim szTemp As String, szBack As String, szBefor As String, iLen As Integer, szPara As String
        Dim i As Integer, j As Integer, k As Integer
        Dim szBeforChar As String, szBackChar As String


        szTemp = szCode
        '括号中有逗号的情况：int a(int (*p)(int c, int d), int f);
        i = MatchSplitSymbolB(szTemp, "(", ")")
        If i > 0 Then
            i = InStr(szCode, "(")
            szBeforChar = "("
            szBackChar = ")"
        End If
        szTemp = szCode
        j = MatchSplitSymbolB(szTemp, "<", ">")
        If j > 0 Then
            j = InStr(szCode, "<")
            If j < i Or i = 0 Then
                szBeforChar = "<"
                szBackChar = ">"
            End If
        End If
        szTemp = szCode
        k = MatchSplitSymbolB(szTemp, "[", "]")
        If k > 0 Then
            k = InStr(szCode, "[")
            If (j = 0 And i = 0) Or (i = 0 And k < j) Or (j = 0 And k < i) Or (k < i And k < j) Then
                szBeforChar = "["
                szBackChar = "]"
            End If
        End If

        szTemp = szCode

        If i < 0 Or j < 0 Then '修改:括号不匹配，出错
            MsgBox("参数有错，请检查", MsgBoxStyle.Critical Or MsgBoxStyle.OkOnly)
            CommaInBracket = GetParamters(szTemp, iLen)
            Exit Function
        End If

        If i > 0 Or j > 0 Or k > 0 Then
            MatchSplitSymbolB(szTemp, szBeforChar, szBackChar, szBefor, szBack)
            szPara = GetParamters(szBefor, iLen)
            szPara = Left(szPara, Len(szPara) - Len("：" & vbCrLf))
            szPara = szPara & szBeforChar & szTemp & szBackChar
            If Not (szBack Is Nothing) Then
                CommaInBracket = szPara & CommaInBracket(szBack)
            End If
        Else '无括号的情况
            CommaInBracket = GetParamters(szTemp, iLen)
        End If
    End Function

    '*******************************************************************************************************
    '函数名：GetParamters
    '描  述：得到不包含括号参数列表的参数列表。仅通过逗号区别参数。
    '参  数：
    '        ByVal szTemp As String：参数
    '        ByRef iLen As Integer ：参数的长度
    '返回值：类型为 String 。参数列表。
    '版  本：2005.8.0.0
    '作  者：康  林
    '时  间：2005年8月12日 16:33:41
    '*******************************************************************************************************
    Function GetParamters(ByVal szTemp As String, ByRef iLen As Integer) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If
        Dim i As Integer, j As Integer, szPara As String
        j = UBound(Split(szTemp, ","))
        'If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
        '    GetParamters = vbCrLf & "        "
        'End If
        'For i = 0 To j '得到参数长度
        '    If Len(ValidCode(Split(szTemp, ",")(i))) > iLen Then
        '        iLen = Len(ValidCode(Split(szTemp, ",")(i)))
        '    End If
        'Next i
        For i = 0 To j
            'C工程
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                szPara = ValidCode(Split(szTemp, ",")(i))
                If szPara = "void" Then
                    If g_iLanguage And 1 Then
                        szPara = "void：无"
                    Else
                        szPara = "void：void"
                    End If
                Else
                    'szPara = szPara & Space(iLen - Len(szPara)) & "："
                    szPara = szPara & "："
                End If

                GetParamters = GetParamters & szPara & vbCrLf
            End If
            'VB工程
            If ActiveDocument.Language = "Basic" Then
                'GetParamters = GetParamters _
                '                       & vbCrLf & "'        " _
                '                       & ValidCode(Split(szTemp, ",")(i)) _
                '                       & Space(iLen - Len(ValidCode(Split(szTemp, ",")(i)))) _
                '                       & "："
                GetParamters = GetParamters _
                                      & vbCrLf & "'        " _
                                      & ValidCode(Split(szTemp, ",")(i)) _
                                      & "："
            End If
        Next
    End Function

    Function GetFunctionDoxgenParamters(ByVal szCode As String) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If

        Dim szTemp As String, i As Integer, j As Integer
        Dim szPara As String, iLen As Integer

        iLen = 0
        szTemp = ValidCode(szCode)
        MatchSplitSymbolB(szCode, "(", ")") '得到括号中的参数
        szTemp = ValidCode(szCode)

        If szTemp = "" Then '无参数
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                If g_iLanguage And 1 Then
                    GetFunctionDoxgenParamters = "无" & vbCrLf
                Else
                    GetFunctionDoxgenParamters = "void" & vbCrLf
                End If
            End If
            If ActiveDocument.Language = "Basic" Then
                If g_iLanguage And 1 Then
                    GetFunctionDoxgenParamters = "无"
                Else
                    GetFunctionDoxgenParamters = "void"
                End If
            End If
            GetFunctionDoxgenParamters = "\param   " & GetFunctionDoxgenParamters
        Else '有参数
            '考虑到括号中有逗号的情况
            GetFunctionDoxgenParamters = CommaInBracket(szTemp)

            '对齐分号
            szPara = ""
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                j = UBound(Split(GetFunctionDoxgenParamters, "：" & vbCrLf))
                For i = 0 To j - 1 '得到参数长度
                    szTemp = Split(GetFunctionDoxgenParamters, "：" & vbCrLf)(i)
                    If Len(szTemp) > iLen Then
                        iLen = Len(szTemp)
                    End If
                Next i

                For i = 0 To j - 1 '得到参数长度
                    szTemp = Split(GetFunctionDoxgenParamters, "：" & vbCrLf)(i)
                    If iLen - Len(szTemp) > 0 Then
                        szPara = szPara & "\param   " & szTemp & Space(iLen - Len(szTemp)) & "：" & vbCrLf
                    Else
                        szPara = szPara & "\param   " & szTemp & "：" & vbCrLf
                    End If
                Next i

                GetFunctionDoxgenParamters = szPara
            End If
        End If
    End Function

    '*******************************************************************************************************
    '函数名：FunctionDoxgenCommentString
    '描  述：用于得到 Doxgen 注释生成帮助的函数参数
    '参  数：
    '        ByVal szCode As String：
    '返回值：类型为 String 。
    '版  本：2006.12.1.0
    '作  者：KangLin
    '时  间：2007年5月13日 18:59:32
    '*******************************************************************************************************
    Function FunctionDoxgenCommentString(ByVal szCode As String) As String
        Dim Sel As TextSelection

        Sel = ActiveDocument.Selection

        Sel.Insert("/*!" & vbCrLf _
                 & "\brief   " & GetFunctionName(szCode) & vbCrLf)
        Sel.Insert(GetFunctionDoxgenParamters(szCode))
        Sel.Insert("\return  " & GetFunctionReturn(szCode) & vbCrLf)
        If g_bFunctionVersion Then
            Sel.Insert("\version " & g_lVersion & vbCrLf)
        End If
        If g_bFunctionAuthor Then
            If g_iLanguage And 1 Then
                Sel.Insert("\author  " & g_szAuthor & vbCrLf)
            End If
            If g_iLanguage And 2 Then
                Sel.Insert("\author  " & g_szEAuthor & vbCrLf)
            End If
        End If
        If g_bFunctionDate Then
            Sel.Insert("\date    " & Now() & vbCrLf)
        End If
        Sel.Text = "*/"
    End Function

    '*******************************************************************************************************
    '函数名：FunctionCommentString
    '功  能：自动生成函数注释
    '参  数：
    '        ByVal szCode：代码
    '返回值：注释
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-8-17
    '时  间：13:38:42
    '*******************************************************************************************************
    Function FunctionCommentString(ByVal szCode As String) As String
        Dim Sel As TextSelection
        Dim szTemp As String

        Sel = ActiveDocument.Selection

        'VC工程
        If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
            '允许生成doxgen注释
            If g_bDoxygen Then
                FunctionCommentString = FunctionDoxgenCommentString(szCode)
            Else
                Sel.Text = gc_szStartCommentSymbol & vbCrLf _
                & m_szFunctionName & GetFunctionName(szCode) & vbCrLf _
                       & m_szDescription & vbCrLf
                Sel.LineUp()
                Sel.SelectLine()
                szTemp = Sel.Text
                szTemp = Left(szTemp, InStr(szTemp, m_szDescription) - 1)
                Sel.EndOfLine()
                Sel.CharLeft()

                Sel.Text = vbCrLf & m_szPara & GetFunctionParamters(szCode)
                Sel.EndOfLine()
                Sel.LineDown(True)
                Sel.Text = szTemp
                Sel.Text = m_szReturnVal & GetFunctionReturn(szCode) & vbCrLf
                If g_bFunctionVersion Then
                    Sel.Text = m_szVersion & g_lVersion & vbCrLf
                End If
                If g_bFunctionAuthor Then
                    If g_iLanguage And 1 Then
                        Sel.Text = m_szAuthor & g_szAuthor & vbCrLf
                    End If
                    If g_iLanguage And 2 Then
                        Sel.Text = m_szAuthor & g_szEAuthor & vbCrLf
                    End If
                    'Sel.LineUp(, 5)
                    'Sel.EndOfLine()
                    'Sel.NewLine()
                    'Sel.Text = m_szPara & GetFunctionParamters(szCode)
                    'Sel.LineUp()
                    'Sel.EndOfLine()
                    'Sel.Delete()
                End If
                If g_bFunctionDate Then
                    Sel.Text = m_szDate & Now().ToLongDateString & " " & Now.ToLongTimeString & vbCrLf
                End If
                Sel.Text = gc_szEndCommentSymbol
            End If
        End If

        'VB工程
        If ActiveDocument.Language = "Basic" Then
            FunctionCommentString = gc_szMarcoStartCommentSymbol & vbCrLf
            If InStr(1, LCase(szCode), "sub ") Or InStr(1, LCase(szCode), " sub ") Then
                FunctionCommentString = FunctionCommentString & "'" & m_szSubName
            Else
                FunctionCommentString = FunctionCommentString & "'" & m_szFunctionName
            End If
            FunctionCommentString = FunctionCommentString & GetFunctionName(szCode) & vbCrLf _
               & "'" & m_szDescription & vbCrLf _
               & "'" & m_szPara & GetFunctionParamters(szCode) & vbCrLf
            If InStr(1, LCase(szCode), "sub ") Then
            Else
                FunctionCommentString = FunctionCommentString & "'" & m_szReturnVal & GetFunctionReturn(szCode) & vbCrLf
            End If
            FunctionCommentString = FunctionCommentString
            If g_bFunctionVersion Then
                FunctionCommentString = FunctionCommentString & "'" & m_szVersion & g_lVersion & vbCrLf
            End If
            If g_bFunctionAuthor Then
                If g_iLanguage And 1 Then
                    FunctionCommentString = FunctionCommentString & "'" & m_szAuthor & g_szAuthor & vbCrLf
                End If
                If g_iLanguage And 2 Then
                    FunctionCommentString = FunctionCommentString & "'" & m_szAuthor & g_szEAuthor & vbCrLf
                End If
            End If
            If g_bFunctionDate Then
                FunctionCommentString = FunctionCommentString & "'" & m_szDate & Now().ToLongDateString() & " " & Now.ToLongTimeString & vbCrLf
            End If
            FunctionCommentString = FunctionCommentString & gc_szMarcoEndCommentSymbol
            Sel.Text = FunctionCommentString
        End If

    End Function

    '*******************************************************************************************************
    '函数名：Section
    '功  能：对块加注释
    '参  数：
    '        ByVal szPrompt：提示字符
    '        ByVal szInput：块完成的功能
    '        ByVal szFunctionSectionStart：注释格式的开始符号
    '        ByVal szFunctionSectionEnd：注释格式的结束符号
    '返回值：无
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-10-18
    '时  间：12:15:03
    '*******************************************************************************************************
    Function Section(ByVal szPrompt As String, ByVal szInput As String, ByVal szFunctionSectionStart As String, ByVal szFunctionSectionEnd As String) As String
        Dim sel As TextSelection, iStart As Integer, iEnd As Integer, szText As Integer
        Dim szCommentSymbol As String
        sel = ActiveDocument.Selection
        If ActiveDocument.Language = "Basic" Then
            szCommentSymbol = gc_szMarcoLineCommentSymbol
        End If
        If EnvDTE.Constants.dsCPP = ActiveDocument.Language Then
            szCommentSymbol = gc_szCLineCommentSymbol
        End If
        iStart = sel.AnchorPoint.Line
        iEnd = sel.BottomPoint.Line
        sel.GotoLine(iEnd)
        sel.EndOfLine()
        sel.NewLine()
        sel.NewLine()
        sel.Text = szCommentSymbol
        'sel.EndOfLine()
        sel.NewLine()
        sel.Text = szCommentSymbol & "以上是" & szInput & szPrompt
        'sel.EndOfLine()
        sel.NewLine()
        sel.Text = szFunctionSectionEnd

        sel.GotoLine(iStart)
        sel.LineUp()
        sel.EndOfLine()
        sel.NewLine()
        sel.Text = szFunctionSectionStart
        'sel.EndOfLine()
        sel.NewLine()
        sel.Text = szCommentSymbol & "以下是" & szInput & szPrompt
        'sel.EndOfLine()
        sel.NewLine()
        sel.Text = szCommentSymbol
        'sel.EndOfLine()
        sel.NewLine()
    End Function

#End Region

#Region "过程"
#Region "VB和VC共用"
    '*******************************************************************************************************
    '过程名：FunctionComment
    '功  能：给函数或文件或类自动加注释
    '用  法：先把光标放在函数定义行的头行上，然后再执行本过程即可自动给函数加注释
    '参  数：无
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：15:29:30
    '*******************************************************************************************************
    Sub FunctionComment()
        'DESCRIPTION: 自动增加函数注释
        Dim Sel As TextSelection, SelText As String, szTemp As String, szText As String
        Dim EditPt As VirtualPoint, iLine As Integer
        Dim iFunctionStartLine As Integer

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        Sel = ActiveDocument.Selection
        Call GetVerSion()
        Call GetCompiler()

        Sel.SelectLine()
        If ValidCode(Sel.Text) <> "" Then
            Sel.LineUp()
            Sel.SelectLine()
            If ValidCode(Sel.Text) <> "" Then
                Select Case MsgBox("是否在当前位置插入注释?", MsgBoxStyle.YesNoCancel Or MsgBoxStyle.Information Or MsgBoxStyle.DefaultButton2)
                    Case MsgBoxResult.No
                        While (ValidCode(Sel.Text) <> "" And Sel.AnchorPoint.Line > 1)
                            Sel.LineUp()
                            Sel.SelectLine()
                        End While
                    Case MsgBoxResult.Cancel
                        Exit Sub
                End Select
            End If
        End If

        If Sel.AnchorPoint.Line = 1 Then '文件注释
            Sel.GotoLine(Sel.AnchorPoint.Line())
            Sel.NewLine()
            Sel.LineUp()
            FileCommentString()
            Sel.StartOfLine()
            Sel.LineDown()
            Exit Sub
        End If

        Sel.SelectLine()
        SelText = Sel.Text
        ValidCCode(SelText, szTemp)
        SelText = szTemp
        While MatchSplitSymbolB(szTemp, "(", ")") <= 0
            If ClassComment(szTemp) Then
                Exit Sub
            End If
            '括号不匹配
            Sel.LineDown(True)
            szText = Sel.Text
            ValidCCode(szText, szTemp)
            SelText = szTemp
            If Sel.BottomPoint.AtEndOfDocument Then
                MsgBox("错误！请把光标放在函数定义的第一行。", MsgBoxStyle.OkOnly Xor MsgBoxStyle.Critical)
                Sel.MoveToPoint(Sel.AnchorPoint)
                Exit Sub
            End If
        End While

        '考虑:_declspec __declspec
        If EnvDTE.Constants.dsCPP = ActiveDocument.Language Then
            Dim szBefor As String, szBack As String
            Select Case GetFunctionName(SelText)
                Case "_declspec", "__declspec"
                    iLine = Sel.AnchorPoint.Line()
                    MatchSplitSymbolB(SelText, "(", ")", szBefor, szBack)
                    SelText = Left(szBefor, InStrRev(szBefor, " ")) & szBack
                    szTemp = SelText

                    While MatchSplitSymbolB(szTemp, "(", ")") <= 0
                        '括号不匹配
                        Sel.SelectLine()
                        SelText = SelText & Sel.Text
                        ValidCCode(SelText, szTemp)
                        SelText = szTemp
                    End While
                    Sel.GotoLine(iLine)
            End Select
        End If

        Sel.GotoLine(Sel.AnchorPoint.Line())
        Sel.LineUp()
        Sel.EndOfLine()
        Sel.NewLine()
        FunctionCommentString(SelText)
        Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
        Sel.LineDown()
    End Sub

    Sub 函数注释()
        FunctionComment()
    End Sub

    '*******************************************************************************************************
    '过程名：AlignComment
    '功  能：对齐语句后的注释
    '参  数：无
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-12-21
    '时  间：16:57:27
    '*******************************************************************************************************
    Sub AlignComment()
        'DESCRIPTION: 对齐语句后的注释
        Dim szComment As String
        Dim sel As TextSelection

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        sel = ActiveDocument.Selection

        If ActiveDocument.Language = "Basic" Then
            szComment = gc_szMarcoLineCommentSymbol
        End If
        If ActiveDocument.Language = EnvDTE.Constants.dsCPP Then
            szComment = gc_szCLineCommentSymbol
        End If

        AlignSign(szComment)
      
    End Sub

    '*******************************************************************************************************
    '过程名：AlignPointSign
    '描  述：对齐指定的输入符号
    '参  数：无
    '版  本：2007.9.1.0
    '作  者：康  林
    '时  间：2007年8月17日 13:35:48
    '*******************************************************************************************************
    Sub AlignPointSign()
        Dim szSign As String
        szSign = InputBox("输入要对齐的符号：", "对齐指定的符号", "=")
        If szSign <> "" Then
            AlignSign(szSign)
        End If
    End Sub

    '*******************************************************************************************************
    '过程名：AlignPointSign1
    '描  述：对齐指定的输入符号
    '参  数：无
    '版  本：2007.9.1.0
    '作  者：康  林
    '时  间：2007年8月17日 13:35:48
    '*******************************************************************************************************
    Sub AlignPointSign1()
        Dim szSign As String
        szSign = InputBox("输入要对齐的符号：", "对齐指定的符号", "=")
        If szSign <> "" Then
            AlignSign1(szSign)
        End If
    End Sub

    '*******************************************************************************************************
    '过程名：AlignSign
    '描  述：按照给定的符号进行对齐
    '参  数：
    '        ByVal szComment As String：给定的对齐符号
    '版  本：2007.9.1.0
    '作  者：康  林
    '时  间：2007年8月17日 13:26:25
    '*******************************************************************************************************
    Sub AlignSign(ByVal szComment As String)
        Dim sel As TextSelection, iStart As Integer, iEnd As Integer, iCol As Integer, iCur As Integer
        Dim i As Integer, j As Integer
        Dim iLine As Integer

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        sel = ActiveDocument.Selection

        iCol = 0 '注释的最大位置处
        iStart = sel.AnchorPoint.Line
        iEnd = sel.BottomPoint.Line
        iCur = sel.ActivePoint.Line
        i = Min(Min(iStart, iEnd), iCur)
        j = Max(Max(iStart, iEnd), iCur)
        iStart = i
        iEnd = j
        sel.GotoLine(iStart)
        For i = iStart To iEnd
            iLine = sel.ActivePoint.Line
            sel.SelectLine()
            Debug.WriteLine(iLine)
            '判断此行是否只是注释行
            If LCase(Left(TrimString(sel.Text), Len(szComment))) <> LCase(szComment) Then
                '此行注释在语句的后面
                If InStr(1, sel.Text, szComment) > 0 Then
                    sel.GotoLine(sel.AnchorPoint.Line)
                    sel.FindText(szComment)
                    sel.MoveToPoint(sel.ActivePoint)
                    sel.CharLeft(True, Len(szComment))
                    While TrimString(sel.Text) = szComment
                        sel.CharLeft(True, 1)
                    End While
                    sel.CharRight(True, 1)
                    sel.Text = " " & szComment
                    j = sel.ActivePoint.DisplayColumn - Len(szComment)
                Else '此行无注释
                    j = 0
                End If
                If j > iCol Then
                    iCol = j
                End If
            End If
            sel.GotoLine(iLine + 1)
        Next i

        sel.GotoLine(iStart)
        For i = iStart To iEnd
            iLine = sel.ActivePoint.Line
            'Debug.WriteLine(iLine)
            sel.SelectLine()
            If LCase(Left(TrimString(sel.Text), Len(szComment))) <> LCase(szComment) Then
                If InStr(1, sel.Text, szComment) > 0 Then
                    sel.GotoLine(sel.AnchorPoint.Line)
                    sel.FindText(szComment)
                    j = sel.AnchorPoint.DisplayColumn - 1
                    If j <= iCol Then
                        sel.Text = Space(iCol - j) & szComment
                    End If
                End If
            End If
            sel.GotoLine(iLine + 1)
        Next i
    End Sub

    Sub 对齐注释()
        AlignComment()
    End Sub

    Sub AlignSign1(ByVal szComment As String)
        Dim sel As TextSelection, iStart As Integer, iEnd As Integer, iCol As Integer
        Dim i As Integer, j As Integer
        Dim iLine As Integer, iCur As Integer

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        sel = ActiveDocument.Selection
        iCol = 0 '注释的最大位置处
        iStart = sel.AnchorPoint.Line
        iEnd = sel.BottomPoint.Line
        iCur = sel.ActivePoint.Line
        i = Min(Min(iStart, iEnd), iCur)
        j = Max(Max(iStart, iEnd), iCur)
        iStart = i
        iEnd = j
        sel.GotoLine(iStart)
        For i = iStart To iEnd
            iLine = sel.ActivePoint.Line
            sel.SelectLine()
            '判断此行是否只是注释行
            If LCase(Left(TrimString(sel.Text), Len(szComment))) <> LCase(szComment) Then
                '此行注释在语句的后面
                If InStr(1, sel.Text, szComment) > 0 Then
                    sel.GotoLine(sel.AnchorPoint.Line)
                    sel.FindText(szComment)
                    j = sel.ActivePoint.DisplayColumn - Len(szComment)
                Else '此行无注释
                    j = 0
                End If
                If j > iCol Then
                    iCol = j
                End If
            End If
            sel.GotoLine(iLine + 1)
        Next

        sel.GotoLine(iStart)
        For i = iStart To iEnd
            iLine = sel.ActivePoint.Line
            sel.SelectLine()
            If LCase(Left(TrimString(sel.Text), Len(szComment))) <> LCase(szComment) Then
                If InStr(1, sel.Text, szComment) > 0 Then
                    sel.GotoLine(sel.AnchorPoint.Line)
                    sel.FindText(szComment)
                    j = sel.ActivePoint.DisplayColumn - Len(szComment)
                    If j < iCol Then
                        sel.Text = Space(iCol - j) & szComment
                    End If
                End If
            End If
            sel.GotoLine(iLine + 1)
        Next
    End Sub

    '*******************************************************************************************************
    '过程名：AlignComment1
    '功  能：对齐语句后的注释,与AlignComment的区别在于:它是与最远处注释对齐
    '参  数：无
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-12-21
    '时  间：16:57:27
    '*******************************************************************************************************
    Sub AlignComment1()
        'DESCRIPTION: 对齐语句后的注释,以最远的注释为准
        Dim sel As TextSelection
        Dim szComment As String

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        sel = ActiveDocument.Selection
        If ActiveDocument.Language = "Basic" Then
            szComment = gc_szMarcoLineCommentSymbol
        End If
        If ActiveDocument.Language = EnvDTE.Constants.dsCPP Then
            szComment = gc_szCLineCommentSymbol
        End If

        AlignSign1(szComment)
     
    End Sub

    Sub 对齐注释1()
        AlignComment1()
    End Sub

    '*******************************************************************************************************
    '过程名：FunctionSection
    '功  能：给执行某个功能的函数块加标志。
    '参  数：无
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-10-18
    '时  间：12:17:09
    '*******************************************************************************************************
    Sub FunctionSection()
        'DESCRIPTION: 标志出执行某个功能的函数块。
        Dim szInput As String, szCommentSymbol As String
        Dim Sel As TextSelection

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        Sel = ActiveDocument.Selection
        If ActiveDocument.Language = "Basic" Then
            szCommentSymbol = gc_szMarcoLineCommentSymbol
        End If
        If ActiveDocument.Language = EnvDTE.Constants.dsCPP Then
            szCommentSymbol = gc_szCLineCommentSymbol
        End If
        szInput = InputBox("请输入函数块的功能：", "函数块功能")
        If szInput <> "" Then
            Section("功能的函数块", "完成 ===" & szInput & "=== ", szCommentSymbol & gc_szFunctionSectionStart, szCommentSymbol & gc_szFunctionSectionEnd)
        End If
    End Sub

    Sub 函数块注释()
        FunctionSection()
    End Sub

    '*******************************************************************************************************
    '过程名：SentenceSection
    '功  能：标志出在某个函数内执行某个功能的语句块。
    '参  数：无
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-10-18
    '时  间：12:23:48
    '*******************************************************************************************************
    Sub SentenceSection()
        'DESCRIPTION:  标志出在某个函数内执行某个功能的语句块。
        Dim szInput As String, szCommentSymbol As String
        Dim Sel As TextSelection

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        Sel = ActiveDocument.Selection
        If ActiveDocument.Language = "Basic" Then
            szCommentSymbol = gc_szMarcoLineCommentSymbol
        End If
        If ActiveDocument.Language = EnvDTE.Constants.dsCPP Then
            szCommentSymbol = gc_szCLineCommentSymbol
        End If
        szInput = InputBox("请输入语句块的功能：", "语句块功能")
        If szInput <> "" Then
            Section("功能的语句块", "完成 ===" & szInput & "=== ", szCommentSymbol & gc_szSentenceSectionStart, szCommentSymbol & gc_szSentenceSectionEnd)
        End If
    End Sub

    '*******************************************************************************************************
    '过程名：AddEndIf
    '描  述：增加结束块注释
    '参  数：无
    '版  本：2005.7.0.0
    '作  者：康  林
    '时  间：2005年7月24日 17:08:41
    '*******************************************************************************************************
    '    Sub AddEndIf()
    '        Dim sel As TextSelection, szCommentSymbol As String
    '        If (ActiveDocument() Is Nothing) Then
    '            Exit Sub
    '        End If

    '        sel = ActiveDocument.Selection
    '        Select Case ActiveDocument.Language
    '            Case EnvDTE.Constants.dsCPP
    '                szCommentSymbol = gc_szCLineCommentSymbol
    '            Case "Basic"
    '                '    szCommentSymbol = gc_szMarcoLineCommentSymbol
    '        End Select
    '        Dim szCode As String, szTemp As String, szEndIf As String
    '        Dim iStart As Integer, iEnd As Integer, iLine As Integer, nCode As Integer
    '        Dim iBrack As Integer, szIn As String
    '        iStart = sel.AnchorPoint.Line
    '        iEnd = sel.BottomPoint.Line

    '        iLine = 0
    '        iBrack = iStart
    '        nCode = 0
    '        sel.GotoLine(iStart, True)
    '        szTemp = sel.Text

    '        Exit Sub

    'AddEndIf_Loop:
    '        While (MatchSplitSymbolB(szTemp,  "{", "}") <= 0) '没有符号或不匹配
    '            iLine = iLine + 1
    '            sel.GotoLine(iStart + iLine)
    '            sel.SelectLine()
    '            szTemp = szTemp & sel.Text
    '            szCode = szTemp
    '        End While
    '        If nCode > 0 Then
    '            sel.GotoLine(iStart + iLine + 1, True)
    '            szIn = Left(szTemp, InStr(szTemp, Chr(0)) - 1)
    '            szTemp = GetSection(szCode)
    '            If szTemp <> "" And szTemp <> "other" Then
    '                szTemp = szCommentSymbol & " " & szEndIf & " " & szTemp & " (" & szCode & ")"
    '                szTemp = " " & DeleteSpace(TrimString(szTemp))
    '                If InStr(sel.Text, "else") = 0 Then
    '                    sel.GotoLine(iStart + iLine)
    '                    sel.StartOfLine()
    '                    sel.FindText("}")
    '                    sel.MoveToPoint(sel.BottomPoint)
    '                    sel.EndOfLine(True)
    '                    sel.Insert(szTemp, vsInsertFlags.vsInsertFlagsContainNewText)
    '                    If InStr(szIn, "{") Then '块内有嵌套
    '                        iLine = iBrack - iStart + 1
    '                        sel.GotoLine(iStart + iLine, True)
    '                        iBrack = 0
    '                        szTemp = sel.Text
    '                        GoTo AddEndIf_Loop
    '                    Else
    '                        iBrack = 0
    '                        If iBrack = 0 And iStart + iLine < iEnd Then
    '                            iLine = iLine + 1
    '                            sel.GotoLine(iStart + iLine, True)
    '                            szTemp = sel.Text
    '                            GoTo AddEndIf_Loop
    '                        End If
    '                    End If
    '                Else
    '                    iLine = iLine + 1
    '                    sel.GotoLine(iStart + iLine)
    '                    sel.SelectLine()
    '                    If InStr(ValidCode(sel.Text), "else") > 0 Then
    '                        szTemp = Right(szTemp, Len(szTemp) - (InStr(szTemp, szCommentSymbol) + Len(szCommentSymbol)))
    '                        GoTo AddEndIf_Loop
    '                    End If
    '                End If
    '            Else
    '                If iBrack < iEnd And iBrack <> 0 Then
    '                    iLine = iBrack - iStart + 1
    '                    sel.GotoLine(iStart + iLine, True)
    '                    iBrack = 0
    '                    szTemp = sel.Text
    '                    GoTo AddEndIf_Loop
    '                Else
    '                    iBrack = 0
    '                    If iBrack = 0 And iStart + iLine < iEnd Then
    '                        iLine = iLine + 1
    '                        sel.GotoLine(iStart + iLine, True)
    '                        szTemp = sel.Text
    '                        GoTo AddEndIf_Loop
    '                    End If
    '                End If
    '            End If
    '        End If
    '    End Sub

    '*******************************************************************************************************
    '过程名：AddEndIf
    '描  述：增加结束块注释
    '参  数：无
    '版  本：2005.7.3.0
    '作  者：康  林
    '时  间：2005年7月26日 17:02:41
    '*******************************************************************************************************
    Public Sub AddEndIf()
        Dim Sel As TextSelection, szTemp As String
        Dim iStart As Integer, iEnd As Integer, iLine As Integer
        Dim Events As AutoFormatCode, bEndIf As Boolean
        Sel = m_DTE.ActiveDocument.Selection
        Events = New AutoFormatCode
        With Events
            .m_DTE = m_DTE
            bEndIf = .m_bEndIf
            .m_bEndIf = True
        End With
        iStart = Sel.AnchorPoint.Line
        iEnd = Sel.BottomPoint.Line
        Dim iMax As Integer
        iMax = Max(iStart, iEnd)
        iStart = Min(iStart, iEnd)
        iEnd = iMax
        Sel.SmartFormat()
        For iLine = iStart To iEnd
            Sel.GotoLine(iLine, True)
            szTemp = Sel.Text
            Events.ModifyBracket(szTemp, iLine, Sel.ActivePoint)
        Next
        Events.m_bEndIf = bEndIf

    End Sub
#End Region

#Region "仅VC用"
    '*******************************************************************************************************
    '过程名：SwitchCppToH
    '功  能：执行文件与头文件互换
    '参  数：无
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-10-18
    '时  间：10:10:18
    '*******************************************************************************************************
    Sub SwitchCppToH()
#If DEBUG Then
#Else
        On Error Resume Next
#End If
        'DESCRIPTION: 执行文件与头文件互换
        Dim FileName As String, FileExt As String

        If (ActiveDocument() Is Nothing) Or ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("此命令只能用于 C/C++")
            Exit Sub
        End If

        FileName = ActiveDocument.FullName
        FileExt = GetFileExt(FileName)

        If UCase(FileExt) = "H" Then
            FileName = GetFileTitle(FileName)
            m_DTE.ItemOperations.OpenFile(FileName & ".cpp")
            m_DTE.ItemOperations.OpenFile(FileName & ".cxx")
            m_DTE.ItemOperations.OpenFile(FileName & ".cc")
            m_DTE.ItemOperations.OpenFile(FileName & ".c")
        Else
            FileName = GetFileTitle(FileName)
            m_DTE.ItemOperations.OpenFile(FileName & ".h")
        End If
    End Sub

    Sub 头文件与执行文件互相切换()
        SwitchCppToH()
    End Sub

    '*******************************************************************************************************
    '过程名：Modify
    '功  能：修改、增加、删除的信息
    '参  数：无
    '作  者：康  林
    '版  本：2.0.0.1
    '日  期：2004-11-17
    '时  间：13:57:41
    '*******************************************************************************************************
    Sub Modify()
        'DESCRIPTION: 修改信息
        Dim sel As TextSelection
        Dim szCommentSymbol As String, szEndCommentSymbol As String
        Dim szInput As String

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        If ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("此命令仅用于C")
            Exit Sub
        End If

        Call GetVerSion()
        sel = ActiveDocument.Selection
        sel = ActiveDocument.Selection
        If LCase(GetFileExt(ActiveDocument.Name)) = "dsm" Then
            szCommentSymbol = gc_szMarcoLineCommentSymbol
        Else
            szCommentSymbol = gc_szCLineCommentSymbol
        End If
        'sel.LineUp
        'sel.EndOfLine
        'sel.NewLine
        'sel.StartOfLine
        'sel.NewLine
        'sel.text = "作  者：" &  g_szAuthor & vbCrLf _
        '         & "版  本：" & g_lVersion & vbCrLf _
        '		 & "日  期：" & Date & vbCrLf _
        '		 & "时  间：" & Time & vbCrLf _
        szInput = InputBox("请输入：" & vbCrLf _
                         & "         1、增加" & vbCrLf _
             & "         2、增加注释" & vbCrLf _
             & "         3、修改" & vbCrLf _
             & "         4、删除(函数内)" & vbCrLf _
             & "         5、删除(函数外)" & vbCrLf, "修改", "1")

        If szInput = "" Then
            Exit Sub
        End If

        If szInput = "1" Then
            szInput = "增加"
            szEndCommentSymbol = szCommentSymbol
        End If

        If szInput = "2" Then
            szInput = "增加注释"
            Section("", "由 ---" & g_szAuthor & "--- " & szInput & "于 " & Now(), _
              gc_szStartCommentSymbol, gc_szCLineCommentSymbol & gc_szEndCommentSymbol)
            Exit Sub
        End If

        If szInput = "3" Then
            szInput = "修改"
            szEndCommentSymbol = szCommentSymbol
        End If

        If szInput = "4" Then
            szInput = "删除"
            szCommentSymbol = "/*"
            szEndCommentSymbol = "*/"
            Section("", "由 ---" & g_szAuthor & "--- " & szInput & "于 " & Now(), _
                     szCommentSymbol & gc_szSentenceSectionStart, _
                     gc_szCLineCommentSymbol & gc_szSentenceSectionEnd & szEndCommentSymbol)
            Exit Sub
        End If

        If szInput = "5" Then
            szInput = "删除"
            Section("", "由 ---" & g_szAuthor & "--- " & szInput & "于 " & Now(), _
                     gc_szStartCommentSymbol, gc_szCLineCommentSymbol & gc_szEndCommentSymbol)
            Exit Sub
        End If
        Section("", "由 ---" & g_szAuthor & "--- " & szInput & "于 " & Now().ToString, _
            szCommentSymbol & gc_szSentenceSectionStart, szEndCommentSymbol & gc_szSentenceSectionEnd)
    End Sub

    '*******************************************************************************************************
    '过程名：TRACE
    '功  能：增加 TRACE 语句
    '参  数：无
    '作  者：康  林
    '版  本：1.0.0.1
    '日  期：2004-12-21
    '时  间：16:57:06
    '*******************************************************************************************************
    Sub TRACE()
        'DESCRIPTION: 增加 TRACE 语句
        Dim sel As TextSelection, szFormat As String, szInput As String, szOutput As String

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        If ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("此命令仅用于C")
            Exit Sub
        End If

        sel = ActiveDocument.Selection
        szInput = InputBox("请输入格式:" & vbCrLf _
                           & "格式字符串与输入字符串之间用" & Chr(34) & ";" & Chr(34) & "隔开" & vbCrLf _
                           & "1、TRACE(_T(" & Chr(34) & "文件:%s(行:%d) : " & "提示字符串。\n" _
               & Chr(34) & "), __FILE__, __LINE__);" & vbCrLf _
               & "可输入为:" & vbCrLf _
               & ";提示字符串" & vbCrLf _
               & "2、TRACE(_T(" & Chr(34) & "文件:%s(行:%d) : %s, %d\n" & Chr(34) & "), szStr, iLen);" & vbCrLf _
               & "可输入为:" & vbCrLf _
               & ";%s, %d; szStr, iLen" & vbCrLf _
               & "3、TRACE(_T(" & Chr(34) & "%s, %d\n" & Chr(34) & "), szStr, iLen);" & vbCrLf _
               & "可输入为:" & vbCrLf _
               & "%s, %d; szStr, iLen" & vbCrLf _
               & "4、TRACE(_T(" & Chr(34) & "HELLO\n" & Chr(34) & "));" & vbCrLf _
               & "可输入为:" & vbCrLf _
               & "HELLO" & vbCrLf, _
               "自动增加TRACE语句")
        If szInput = "" Then
            Exit Sub
        End If
        If InStr(1, szInput, ";") = 1 Then
            szFormat = "%s(%d) : "
            szOutput = "__FILE__, __LINE__"
            If InStr(2, szInput, ";") <> 0 Then
                szFormat = szFormat & Split(szInput, ";")(1)
                szOutput = szOutput & ", " & Split(szInput, ";")(2)
            Else
                szFormat = szFormat & Split(szInput, ";")(1)
            End If
        Else
            If InStr(1, szInput, ";") <> 0 Then
                szFormat = Split(szInput, ";")(0)
                szOutput = Split(szInput, ";")(1)
            Else
                sel.Text = "TRACE(_T(""" & szInput & "\n""));"
                Exit Sub
            End If
        End If

        sel.Text = "TRACE(_T(""" & szFormat & "\n""), " & szOutput & ");"

    End Sub

    Sub T()
        'DESCRIPTION: 自动增加 _T("")
        Dim Sel As TextSelection, szInput As String

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        If ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("此命令仅用于C")
            Exit Sub
        End If

        Sel = ActiveDocument.Selection
        szInput = InputBox("请输入", "_T()")
        If szInput <> "" Then
            Sel.Text = "_T(" & Chr(34) & szInput & Chr(34) & ")"
        End If
    End Sub

    '*******************************************************************************************************
    '过程名：CommentTRACE
    '描  述：注释掉 TRACE 语句
    '参  数：无
    '版  本：1.0
    '作  者：康  林
    '时  间：2005-6-10 9:20:56
    '*******************************************************************************************************
    Sub CommentTRACE()
        Dim Sel As TextSelection, szTemp As String, szBefor As String, szBack As String, ir As Long
        Dim szInput As String
        If ActiveDocument() Is Nothing Or ActiveDocument.Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("此命令只能用于 C/C++")
            Exit Sub
        End If
        Sel = ActiveDocument.Selection
        Sel.StartOfDocument()

        Do
            '去掉注释
            Sel.SelectLine()
            szTemp = Sel.Text
            If InStr(szTemp, "//") > 0 Then
                Sel.MoveToPoint(Sel.AnchorPoint)
                Sel.FindText("//", EnvDTE.vsFindOptions.vsFindOptionsMatchInHiddenText)
                Sel.CharLeft(, 1)
                Sel.StartOfLine(, True)
                szTemp = Sel.Text
                Sel.MoveToPoint(Sel.BottomPoint)
            Else
                If InStr(szTemp, "/*") > 0 Then
                    Sel.MoveToPoint(Sel.AnchorPoint)
                    Sel.FindText("/*", EnvDTE.vsFindOptions.vsFindOptionsMatchInHiddenText)
                    Sel.FindText("*/", EnvDTE.vsFindOptions.vsFindOptionsMatchInHiddenText)
                    Sel.CharRight()
                    Sel.EndOfLine(True)
                    szTemp = Sel.Text
                End If
            End If


            '开始注释 TRACE
            While InStr(szTemp, "TRACE") > 0
                ir = MatchSplitSymbol(szTemp, "(", ")", szBefor, szBack)
                If ir > 0 Then
                    szBefor = Replace(szBefor, "TRACE", "/*TRACE", , 1)
                    szBack = Replace(szBack, ";", ";*/", , 1)
                    Sel.Text = szBefor & "(" & szTemp & ")" & szBack
                    Sel.LineUp()
                    Exit While
                Else
                    Sel.LineDown(True)
                    szTemp = Sel.Text
                End If
            End While
            Sel.MoveToPoint(Sel.AnchorPoint)
            Sel.LineDown()
        Loop Until Sel.BottomPoint.AtEndOfDocument
    End Sub

    Sub UnCommentTRACE()
        Dim Sel As TextSelection
        If ActiveDocument() Is Nothing Or ActiveDocument.Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("此命令只能用于 C/C++")
            Exit Sub
        End If
        Sel = ActiveDocument.Selection
        Sel.StartOfDocument()
        Do
            If Sel.FindText("/*TRACE", EnvDTE.vsFindOptions.vsFindOptionsMatchInHiddenText) Then
                Sel.Text = "TRACE"
            Else
                Exit Sub
            End If
            If Sel.FindText(";*/", EnvDTE.vsFindOptions.vsFindOptionsMatchInHiddenText) Then
                Sel.Text = ";"
            Else
                Exit Sub
            End If
        Loop Until Sel.BottomPoint.AtEndOfDocument
    End Sub

    '*******************************************************************************************************
    '函数名：ClassComment
    '描  述：类注释
    '参  数：无
    '返回值：类型为 Integer 。
    '版  本：2006.12.1.0
    '作  者：康  林
    '时  间：2007年8月14日 12:46:53
    '*******************************************************************************************************
    Function ClassComment(ByVal szText As String) As Boolean
        Dim szPattern As String, szClassName As String
        Dim Sel As TextSelection

        ClassComment = False

        szPattern = "\s*class\s+([_a-zA-Z][_0-9a-zA-Z]*)\s*:?\s*(public|private|protected)?\s*([_a-zA-Z][_0-9a-zA-Z]*,?)?\s*{"
        Dim r As Regex
        r = New Regex(szPattern)
        Dim m As Match
        m = r.Match(szText)
        If m.Success = False Then
            ClassComment = False
            Exit Function
        End If

        If (ActiveDocument() Is Nothing) Then
            Exit Function
        End If

        Sel = ActiveDocument.Selection

        While m.Success
            szClassName = m.Groups(1).Value
            m = m.NextMatch
        End While

        Sel.GotoLine(Sel.AnchorPoint.Line())
        Sel.LineUp()
        Sel.EndOfLine()
        Sel.NewLine()
        If g_bDoxygen Then
            ClassDoxgenCommentString(szClassName)
        Else
            ClassCommentString(szClassName)
        End If

        Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
        Sel.LineDown()

        ClassComment = True
    End Function

    '*******************************************************************************************************
    '过程名：ClassCommentString
    '描  述：类注释串
    '参  数：
    '        ByVal ClassName As String：
    '版  本：2006.12.1.0
    '作  者：康  林
    '时  间：2007年8月14日 15:31:11
    '*******************************************************************************************************
    Sub ClassCommentString(ByVal ClassName As String)
        Dim Sel As TextSelection

        Sel = ActiveDocument.Selection

        Sel.Text = gc_szStartCommentSymbol & vbCrLf _
                    & m_szClassName & ClassName & vbCrLf _
                    & m_szDescription & vbCrLf

        If g_bFunctionVersion Then
            Sel.Text = m_szVersion & g_lVersion & vbCrLf
        End If
        If g_bFunctionAuthor Then
            If g_iLanguage And 1 Then
                Sel.Text = m_szAuthor & g_szAuthor & vbCrLf
            End If
            If g_iLanguage And 2 Then
                Sel.Text = m_szAuthor & g_szEAuthor & vbCrLf
            End If
            'Sel.LineUp(, 5)
            'Sel.EndOfLine()
            'Sel.NewLine()
            'Sel.Text = m_szPara & GetFunctionParamters(szCode)
            'Sel.LineUp()
            'Sel.EndOfLine()
            'Sel.Delete()
        End If
        If g_bFunctionDate Then
            Sel.Text = m_szDate & Now().ToLongDateString & " " & Now.ToLongTimeString & vbCrLf
        End If
        Sel.Text = gc_szEndCommentSymbol

    End Sub

    '*******************************************************************************************************
    '过程名：ClassDoxgenCommentString
    '描  述：类Doxgen注释串
    '参  数：
    '        ByVal ClassName As String：
    '版  本：2006.12.1.0
    '作  者：康  林
    '时  间：2007年8月14日 15:31:20
    '*******************************************************************************************************
    Sub ClassDoxgenCommentString(ByVal ClassName As String)
        Dim Sel As TextSelection

        Sel = ActiveDocument.Selection

        Sel.Text = "/*!" & vbCrLf _
                    & "\class   " & ClassName & vbCrLf _
                    & "\brief   " & vbCrLf

        If g_bFunctionVersion Then
            Sel.Text = "\version " & g_lVersion & vbCrLf
        End If
        If g_bFunctionAuthor Then
            If g_iLanguage And 1 Then
                Sel.Insert("\author  " & g_szAuthor & vbCrLf)
            End If
            If g_iLanguage And 2 Then
                Sel.Insert("\author  " & g_szEAuthor & vbCrLf)
            End If
        End If
        If g_bFunctionDate Then
            Sel.Insert("\date    " & Now() & vbCrLf)
        End If
        Sel.Text = "*/"

    End Sub


#End Region

#Region "辅助过程"
    Sub LoadSettings()
        Dim szKeyItem As String, Key As RegistryKey

        szKeyItem = "SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\"
        Try
            Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "文件注释", True)
            If Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(szKeyItem & "文件注释")
                Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "文件注释", True)
            End If
            g_szAuthor = Key.GetValue("作者", g_szAuthor)
            g_szCorporation = Key.GetValue("公司", g_szCorporation)
            g_szEAuthor = Key.GetValue("Author", g_szEAuthor)
            g_szECorporation = Key.GetValue("Corporation", g_szECorporation)
            g_szEmail = Key.GetValue("EMail", g_szEmail)
            g_iLanguage = Key.GetValue("中文", g_iLanguage)
            If Key.GetValue("英文", g_iLanguage) And 2 Then
                g_iLanguage = Key.GetValue("英文", g_iLanguage) + g_iLanguage
            End If
            Key.Close()

            Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "函数注释", True)
            If Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(szKeyItem & "函数注释")
                Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "函数注释", True)
            End If
            m_szSubName = Key.GetValue("过程名", m_szSubName)
            m_szFunctionName = Key.GetValue("函数名", m_szFunctionName)
            m_szClassName = Key.GetValue("类名", m_szClassName)
            m_szDescription = Key.GetValue("描述", m_szDescription)
            m_szPara = Key.GetValue("参数", m_szPara)
            m_szReturnVal = Key.GetValue("返回值", m_szReturnVal)
            m_szVersion = Key.GetValue("版本", m_szVersion)
            m_szAuthor = Key.GetValue("作者", m_szAuthor)
            m_szDate = Key.GetValue("日期", m_szDate)
            g_bFunctionVersion = Key.GetValue("加入版本", g_bFunctionVersion)
            g_bFunctionAuthor = Key.GetValue("加入作者", g_bFunctionAuthor)
            g_bFunctionDate = Key.GetValue("加入日期", g_bFunctionDate)
            Key.Close()

            Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "VC", True)
            If Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(szKeyItem & "VC")
                Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "VC", True)
            End If
            g_bDoxygen = Key.GetValue("DoxgenComment", True)
            Key.Close()
        Catch ex As Exception
            Debug.WriteLine(ex.Message)
        End Try
    End Sub
#End Region
#End Region

    Public Sub New()
        LoadSettings()
    End Sub
End Class
