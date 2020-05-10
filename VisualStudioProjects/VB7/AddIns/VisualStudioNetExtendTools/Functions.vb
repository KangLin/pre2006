'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：Functions.vb
'描  述：公共函数模块
'版  本：2005.6.*
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005-6-18
'时  间：2005-6-18 13:52:40
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************
Option Strict Off
Option Explicit On 

Module Functions

    '*******************************************************************************************************
    '函数名：Min
    '描  述：求两个数中的小的一个
    '参  数：
    '        ByVal Num1 As Integer：数一
    '        ByVal Num2 As Integer：数二
    '返回值：小的数
    '版  本：2005.6.*
    '作  者：康  林
    '时  间：2005-6-18 13:52:56
    '*******************************************************************************************************
    Function Min(ByVal Num1 As Integer, ByVal Num2 As Integer) As Integer
        If Num1 > Num2 Then
            Min = Num2
        Else
            Min = Num1
        End If
    End Function

    '*******************************************************************************************************
    '函数名：Max
    '描  述：求两个数中的大的数
    '参  数：
    '        ByVal Num1 As Integer：数一
    '        ByVal Num2 As Integer：数二
    '返回值：大的数
    '版  本：2005.6.*
    '作  者：康  林
    '时  间：2005-6-18 13:53:41
    '*******************************************************************************************************
    Function Max(ByVal Num1 As Integer, ByVal Num2 As Integer) As Integer
        If Num1 > Num2 Then
            Max = Num1
        Else
            Max = Num2
        End If
    End Function

    '*******************************************************************************************************
    '函数名：GetFilePath
    '功  能：得到文件路径
    '参  数：
    '        ByVal szFileName：文件名
    '返回值：文件路径
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：19:00:10
    '*******************************************************************************************************
    Function GetFilePath(ByVal szFileName As String) As String
        Dim iPos As Integer
        iPos = InStrRev(szFileName, "\")
        If iPos <> 0 Then
            GetFilePath = Left(szFileName, iPos - 1)
        End If
    End Function

    '*******************************************************************************************************
    '函数名：GetFileExt
    '功  能：得到文件扩展名
    '参  数：
    '        ByVal szDocName：文件名
    '返回值：文件扩展名
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：15:18:15
    '*******************************************************************************************************
    Function GetFileExt(ByVal szDocName As String) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If
        Dim i As Integer
        GetFileExt = szDocName
        If InStr(GetFileExt, ".") > 0 Then
            i = InStrRev(GetFileExt, ".")
            GetFileExt = Right(GetFileExt, Len(GetFileExt) - i)
            'GetFileExt = Split(GetFileExt, ".")(1)
        Else
            GetFileExt = ""
        End If
        'GetFileExt = LCase(GetFileExt)
    End Function

    '*******************************************************************************************************
    '函数名：GetFileTitle
    '功  能：得到文件标题
    '参  数：
    '        ByVal szDocName：文件名
    '返回值：文件标题
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：13:44:36
    '*******************************************************************************************************
    Function GetFileTitle(ByVal szDocName As String) As String
        Dim i As Integer
        GetFileTitle = szDocName
        If InStr(GetFileTitle, ".") > 0 Then
            i = InStrRev(GetFileTitle, ".")
            GetFileTitle = Left(GetFileTitle, i - 1)
            'GetFileTitle = Split(GetFileTitle, ".")(0)
        End If
    End Function

    '*******************************************************************************************************
    '函数名：DeleteSpace
    '功  能：删除多余的空格
    '参  数：
    '        ByVal szSource：源代码
    '返回值：删除多余的空格的代码
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：15:25:37
    '*******************************************************************************************************
    '功能:
    Function DeleteSpace(ByVal szSource As String) As String
        While InStr(1, szSource, "  ") > 0
            szSource = Replace(szSource, "  ", " ")
        End While
        DeleteSpace = szSource
    End Function

    '*******************************************************************************************************
    '函数名：TrimString
    '功  能：删除前导/后导空格和回车符CHR(13)、换行符CHR(10)、制表符CHR(9)
    '参  数：
    '        ByVal szSource：源代码
    '返回值：删除前导/后导空格和回车符CHR(13)、换行符CHR(10)、制表符CHR(9)的代码
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：15:23:37
    '*******************************************************************************************************
    Function TrimString(ByVal szSource As String) As String
        szSource = Replace(szSource, Chr(9), " ")
        szSource = Replace(szSource, " \", " ")
        szSource = Replace(szSource, Chr(13) + Chr(10), " ")
        TrimString = Trim(szSource)
    End Function

    '*******************************************************************************************************
    '函数名：ValidCode
    '功  能：规格化代码（去掉注释、多余的空格、前导/后导空格和回车符CHR(13)、换行符CHR(10)、制表符CHR(9)）
    '参  数：
    '        ByVal szSource：源代码
    '返回值：规格化后的代码
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：15:06:23
    '*******************************************************************************************************
    Function ValidCode(ByVal szSource As String) As String
        Dim szTemp As String, szBefor As String, szBack As String
        Dim iR As Integer

        szTemp = szSource
        szBefor = ""
        szBack = ""

        iR = InStr(szTemp, "/*")
        While iR > 0
            szSource = Left(szTemp, iR - 1)
            szTemp = Right(szTemp, Len(szTemp) - iR - 1)
            iR = InStr(szTemp, "*/")
            szSource = szSource & " " & Right(szTemp, Len(szTemp) - iR - 1)
            szTemp = szSource
            iR = InStr(szTemp, "/*")
        End While

        iR = InStr(szTemp, "//")
        While iR > 0
            szSource = Left(szTemp, iR - 1)
            szTemp = Right(szTemp, Len(szTemp) - iR - 1)
            iR = InStr(szTemp, vbCrLf)
            If iR > 0 Then
                szSource = szSource & " " & Right(szTemp, Len(szTemp) - iR - 1)
            End If
            'Debug.WriteLine(szSource)
            szTemp = szSource
            iR = InStr(szTemp, "//")
        End While

        szTemp = DeleteSpace(TrimString(szSource))
        ValidCode = szTemp
    End Function

    '*******************************************************************************************************
    '函数名：MatchSplitSymbol
    '功  能：匹配括号
    '参  数：
    '        ByRef szSource：代码，如果匹配成功，此参数包含分隔符中间的字符（不包含分隔符）
    '        ByVal String1：分隔符1
    '        ByVal String2：分隔符2
    '返回值：如果成功，返回除去分隔符和其中的字符所剩下的字符串,
    '        否则，分隔符不匹配,返回chr(0)
    '        没有分隔符,返回Chr(1)
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：15:02:13
    '*******************************************************************************************************
    Function MatchSplitSymbol(ByRef szSource As String, ByVal String1 As String, ByVal String2 As String) As String
        Dim iStack As Integer, iCurrent As Integer, iStart As Integer, iEnd As Integer, iSP As Integer
        Dim iLen1 As Integer, iLen2 As Integer
        iLen1 = Len(String1)
        iLen2 = Len(String2)
        iSP = InStr(1, szSource, String1)
        If iSP <> 0 Then
            iStack = iStack + 1
            iCurrent = iSP + iLen1
            Do While (iCurrent <= Len(szSource)) And CBool(iStack)
                iStart = InStr(iCurrent, szSource, String1)
                iEnd = InStr(iCurrent, szSource, String2)
                If (iStart < iEnd And iStart <> 0) Or (iStart <> 0 And iEnd = 0) Then
                    iStack = iStack + 1
                    iCurrent = iStart + iLen1
                End If
                If (iStart > iEnd And iEnd <> 0) Or (iStart = 0 And iEnd <> 0) Then
                    iStack = iStack - 1
                    iCurrent = iEnd + iLen2
                End If
                If iStart = 0 And iEnd = 0 Then
                    Exit Do
                End If
            Loop
        ElseIf InStr(1, szSource, String2) <> 0 Then '只有分隔符2
            MatchSplitSymbol = Chr(0) '不匹配
            Exit Function
        Else '两个分隔符都没有
            MatchSplitSymbol = Chr(1) '不匹配
            Exit Function
        End If
        If iStack = 0 Then '分隔符匹配
            If iCurrent <= Len(szSource) Then
                MatchSplitSymbol = Left(szSource, iSP - 1) & Right(szSource, Len(szSource) - iCurrent + 1)
                szSource = Mid(szSource, iSP + iLen1, iCurrent - iLen2 - (iSP + iLen1))
            Else
                MatchSplitSymbol = Left(szSource, iSP - 1)
                szSource = Mid(szSource, iSP + iLen1, iCurrent - iLen2 - (iSP + iLen1))
            End If
        Else '不匹配
            MatchSplitSymbol = Chr(0)
        End If
    End Function

    '*******************************************************************************************************
    '函数名：MatchSplitSymbol
    '功  能：匹配给定分隔符号
    '        例如:源字符串:szSource = "for(int i = 1; i < 10; i++) { b++; }"
    '             分隔符:String1 = "("
    '                    String2 = ")"
    '        则调用此函数后返回：
    '            szSource = "int i = 1; i < 10; i++"
    '            szBefor = "for"
    '            szBack = " { b++; }"
    '注意:没有考虑引号中有分隔符的情况
    '参  数：
    '        ByRef szSource As String：代码。如果匹配成功，此参数为分隔符中的代码（不包含分隔符）
    '        ByVal String1 As String：分隔符1
    '        ByVal String2 As String：分隔符2
    '        ByRef szBefor As String：如果匹配成功。分隔符前的代码（不包含分隔符）
    '        ByRef szBack As String：如果匹配成功。分隔符后的代码（不包含分隔符）
    '返回值：匹配失败：0
    '        代码中没有指定的分隔符：-1
    '        成功：返回分隔符中代码的长度(包括分隔符)
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-5-2
    '时  间：9:51:07
    '*******************************************************************************************************
    Function MatchSplitSymbol(ByRef szSource As String, ByVal String1 As String, ByVal String2 As String, ByRef szBefor As String, ByRef szBack As String) As Long
        Dim iStack As Integer, iCurrent As Integer, iStart As Integer, iEnd As Integer, iSP As Integer
        Dim iLen1 As Integer, iLen2 As Integer

        szBefor = ""
        szBack = ""
        MatchSplitSymbol = 0
        iSP = 0

        iLen1 = Len(String1)
        iLen2 = Len(String2)
        iSP = InStr(1, szSource, String1)
        If iSP <> 0 Then '有分隔符1
            iStack = iStack + 1
            iCurrent = iSP + iLen1
            Do While (iCurrent <= Len(szSource)) And CBool(iStack)
                iStart = InStr(iCurrent, szSource, String1)
                iEnd = InStr(iCurrent, szSource, String2)
                If (iStart < iEnd And iStart <> 0) Or (iStart <> 0 And iEnd = 0) Then
                    iStack = iStack + 1
                    iCurrent = iStart + iLen1
                End If
                If (iStart > iEnd And iEnd <> 0) Or (iStart = 0 And iEnd <> 0) Then
                    iStack = iStack - 1
                    iCurrent = iEnd + iLen2
                End If
                If iStart = 0 And iEnd = 0 Then
                    Exit Do
                End If
            Loop
        ElseIf InStr(1, szSource, String2) <> 0 Then '只有分隔符2
            MatchSplitSymbol = 0 '不匹配
            Exit Function
        Else '两个分隔符都没有
            MatchSplitSymbol = -1 '不匹配
            Exit Function
        End If
        If iStack = 0 Then '分隔符匹配
            If iCurrent <= Len(szSource) Then
                szBefor = Left(szSource, iSP - 1)
                szBack = Right(szSource, Len(szSource) - iCurrent + 1)
                szSource = Mid(szSource, iSP + iLen1, iCurrent - iLen2 - (iSP + iLen1))
            Else
                szBefor = Left(szSource, iSP - 1)
                szBack = ""
                szSource = Mid(szSource, iSP + iLen1, iCurrent - iLen2 - (iSP + iLen1))
            End If
            MatchSplitSymbol = iLen1 + Len(szSource) + iLen2
        Else '不匹配
            MatchSplitSymbol = 0
        End If
    End Function

    '*******************************************************************************************************
    '函数名：ReverseMatchSplitSymbol
    '功  能：反向匹配给定的分隔符
    '        例如:源字符串:szSource = "for(int i = 1; i < 10; i++) { b++; }"
    '             分隔符:String1 = "("
    '                    String2 = ")"
    '        则调用此函数后返回：
    '            szSource = "int i = 1; i < 10; i++"
    '            szBefor = "for"
    '            szBack = " { b++; }"
    '参  数：
    '        ByRef szSource As String：代码。如果匹配成功，此参数为分隔符中的代码（不包含分隔符）
    '        ByVal String1 As String：分隔符1
    '        ByVal String2 As String：分隔符2
    '        ByRef szBefor As String：如果匹配成功。分隔符前的代码（不包含分隔符）,失败,,空字符串
    '        ByRef szBack As String：如果匹配成功。分隔符后的代码（不包含分隔符）,失败,空字符串
    '返回值：失败,返回-1,缺少分隔符1；返回-2,缺少分隔符2。
    '        成功,>0,分离出的字符串的长度(包含分隔符的长度)
    '        没有分隔符,为0
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-5-2
    '时  间：11:33:00
    '*******************************************************************************************************
    Function ReverseMatchSplitSymbol(ByRef szSource As String, _
                                     ByVal String1 As String, _
                                     ByVal String2 As String, _
                                     ByRef szBefor As String, _
                                     ByRef szBack As String) As Long
        Dim szReSou As String, szReStr1 As String, szReStr2 As String, szReBef As String, szReBack As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If
        szBefor = ""
        szBack = ""

        szReSou = StrReverse(szSource)
        szReStr1 = StrReverse(String1)
        szReStr2 = StrReverse(String2)
        szReBack = Space(Len(szReSou))
        szReBef = Space(Len(szReSou))
        'ReverseMatchSplitSymbol = MatchSplitSymbol(szReSou, szReStr2, szReStr1, szReBef, szReBack)
        Dim nCode As Integer, nBefor As Integer, nBack As Integer
        ReverseMatchSplitSymbol = MatchSplitSymbolB(szReSou, szReStr2, szReStr1, szReBef, szReBack)
        If ReverseMatchSplitSymbol > 0 Then
            Dim szTemp As String
            szTemp = ValidString(szReBack)
            szBefor = StrReverse(szTemp)
            szTemp = ValidString(szReBef)
            szBack = StrReverse(szTemp)
            szTemp = ValidString(szReSou)
            szSource = StrReverse(szTemp)
        End If

    End Function

    '*******************************************************************************************************
    '函数名：MatchAllSymbol
    '功  能：在源字符串中,给定的分隔符是否都匹配
    '参  数：
    '        ByVal szSource As String：源字符串
    '        ByVal String1 As String ：分隔符一
    '        ByVal string2 As String ：分隔符二
    '返回值：全都匹配返回 TRUE，否则返回 FALSE。
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-5-4
    '时  间：14:47:01
    '*******************************************************************************************************
    Function MatchAllSymbol(ByVal szSource As String, ByVal String1 As String, ByVal string2 As String) As Boolean
        Dim szTemp As String, iRetrue As Integer, szBefor As String, szBack As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If

        szTemp = szSource
        iRetrue = MatchSplitSymbol(szTemp, String1, string2, szBefor, szBack)
        While iRetrue > 0 '大括号匹配或没大括号
            szTemp = szBack
            iRetrue = MatchSplitSymbol(szTemp, String1, string2, szBefor, szBack)
        End While

        If iRetrue = 0 Then
            MatchAllSymbol = False
        Else
            MatchAllSymbol = True
        End If
    End Function

    '*******************************************************************************************************
    '函数名：GetFunctionName
    '功  能：得到函数名
    '参  数：
    '        szCode:代码
    '返回值：函数名
    '作  者：康  林
    '版  本：1.0
    '日  期：2004-8-17
    '时  间：14:03:31
    '*******************************************************************************************************
    Function GetFunctionName(ByVal szCode As String) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If

        Dim iPos As Integer, Pos As Integer
        GetFunctionName = ""
        szCode = ValidCode(szCode)
        iPos = InStr(1, szCode, "(")
        If CBool(iPos) Then
            GetFunctionName = ValidCode(Split(szCode, "(")(0))
            If InStr(GetFunctionName, " operator") > 0 Then
                GetFunctionName = ValidCode(Split(GetFunctionName, " operator")(1))
                GetFunctionName = "operator " + GetFunctionName
                Exit Function
            End If

            Pos = InStrRev(GetFunctionName, " ")
            If Pos > 0 Then
                GetFunctionName = Right(GetFunctionName, Len(GetFunctionName) - Pos)
            End If
            '类成员函数：int class1::subclass2::function(int para1, int para2)
            If InStr(GetFunctionName, "::") > 0 Then
                'GetFunctionName = Split(GetFunctionName, "::")(1)
                Pos = InStrRev(GetFunctionName, "::")
                GetFunctionName = Right(GetFunctionName, Len(GetFunctionName) - Pos - 1)
            End If

            Dim szLeft As String
            szLeft = Left(GetFunctionName, 1)
            If szLeft = "*" Or szLeft = "&" Then
                GetFunctionName = Right(GetFunctionName, Len(GetFunctionName) - 1)
            End If
        End If
    End Function

    '*******************************************************************************************************
    '函数名：GetSection
    '描  述：得到块
    '参  数：
    '        ByRef szCode As String：代码
    '返回值：String：块的类型
    '版  本：2005.7.3.0
    '作  者：康  林
    '时  间：2005年7月26日 17:04:11
    '*******************************************************************************************************
    Function GetSection(ByRef szCode As String) As String
#If DEBUG Then
#Else
        on error Resume Next 
#End If
        Dim ir As Integer, nCode As Integer, nBefor As Integer
        Dim szTemp As String, szBefor As String, szBack As String
        GetSection = ""
        szTemp = szCode
        szBefor = szCode
        szBack = szCode
        ir = MatchSplitSymbolB(szCode, "{", "}", szBefor)
        If ir <= 0 Then
            Return ""
        End If
        szCode = szBefor

        ir = ReverseMatchSplitSymbol(szCode, "(", ")", szBefor, szBack)

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
                    szTemp = "other"
            End Select
            GetSection = szTemp
        End If
    End Function

    '*******************************************************************************************************
    '函数名：ValidString
    '描  述：有效从API函数中得到的字符串
    '参  数：
    '        ByRef szString As String：从API函数中得到的字符串
    '返回值：String：有效的字符串
    '版  本：2005.7.3.0
    '作  者：康  林
    '时  间：2005年7月26日 17:03:17
    '*******************************************************************************************************
    Public Function ValidString(ByRef szString As String) As String
        Try
            Dim i As Integer
            i = InStr(szString, Chr(0))
            If i >= 1 Then
                ValidString = Left(szString, i - 1)
            Else
                ValidString = szString
            End If
        Catch ex As Exception
            ValidString = szString
            Debug.WriteLine(ex.ToString)
        End Try
    End Function
End Module
