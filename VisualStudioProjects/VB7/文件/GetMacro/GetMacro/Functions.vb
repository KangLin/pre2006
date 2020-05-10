Option Strict Off
Option Explicit On 

Module Functions

    Function Min(ByVal Num1 As Integer, ByVal Num2 As Integer) As Integer
        If Num1 > Num2 Then
            Min = Num2
        Else
            Min = Num1
        End If
    End Function

    Function Max(ByVal Num1 As Integer, ByVal Num2 As Integer) As Integer
        If Num1 > Num2 Then
            Max = Num1
        Else
            Max = Num2
        End If
    End Function

    '*******************************************************************************************************
    '��������GetFilePath
    '��  �ܣ��õ��ļ�·��
    '��  ����
    '        ByVal szFileName���ļ���
    '����ֵ���ļ�·��
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺19:00:10
    '*******************************************************************************************************
    Function GetFilePath(ByVal szFileName As String) As String
        Dim iPos As Integer
        iPos = InStrRev(szFileName, "\")
        If iPos <> 0 Then
            GetFilePath = Left(szFileName, iPos - 1)
        End If
    End Function

    '*******************************************************************************************************
    '��������GetFileExt
    '��  �ܣ��õ��ļ���չ��
    '��  ����
    '        ByVal szDocName���ļ���
    '����ֵ���ļ���չ��
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺15:18:15
    '*******************************************************************************************************
    Function GetFileExt(ByVal szDocName As String) As String
        GetFileExt = szDocName
        If InStr(GetFileExt, ".") > 0 Then
            GetFileExt = Split(GetFileExt, ".")(1)
        Else
            GetFileExt = ""
        End If
        'GetFileExt = LCase(GetFileExt)
    End Function

    '*******************************************************************************************************
    '��������GetFileTitle
    '��  �ܣ��õ��ļ�����
    '��  ����
    '        ByVal szDocName���ļ���
    '����ֵ���ļ�����
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺13:44:36
    '*******************************************************************************************************
    Function GetFileTitle(ByVal szDocName As String) As String
        GetFileTitle = szDocName
        If InStr(GetFileTitle, ".") > 0 Then
            GetFileTitle = Split(GetFileTitle, ".")(0)
        End If
    End Function

    '*******************************************************************************************************
    '��������DeleteSpace
    '��  �ܣ�ɾ������Ŀո�
    '��  ����
    '        ByVal szSource��Դ����
    '����ֵ��ɾ������Ŀո�Ĵ���
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺15:25:37
    '*******************************************************************************************************
    '����:
    Function DeleteSpace(ByVal szSource As String) As String
        While InStr(1, szSource, "  ") > 0
            szSource = Replace(szSource, "  ", " ")
        End While
        DeleteSpace = szSource
    End Function

    '*******************************************************************************************************
    '��������TrimString
    '��  �ܣ�ɾ��ǰ��/�󵼿ո�ͻس���CHR(13)�����з�CHR(10)���Ʊ��CHR(9)
    '��  ����
    '        ByVal szSource��Դ����
    '����ֵ��ɾ��ǰ��/�󵼿ո�ͻس���CHR(13)�����з�CHR(10)���Ʊ��CHR(9)�Ĵ���
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺15:23:37
    '*******************************************************************************************************
    Function TrimString(ByVal szSource As String) As String
        szSource = Replace(szSource, Chr(9), " ")
        szSource = Replace(szSource, " \", " ")
        szSource = Replace(szSource, Chr(13) + Chr(10), " ")
        TrimString = Trim(szSource)
    End Function

    '*******************************************************************************************************
    '��������ValidCode
    '��  �ܣ���񻯴��루ȥ��ע�͡�����Ŀո�ǰ��/�󵼿ո�ͻس���CHR(13)�����з�CHR(10)���Ʊ��CHR(9)��
    '��  ����
    '        ByVal szSource��Դ����
    '����ֵ����񻯺�Ĵ���
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺15:06:23
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
    '��������MatchSplitSymbol
    '��  �ܣ�ƥ������
    '��  ����
    '        ByRef szSource�����룬���ƥ��ɹ����˲��������ָ����м���ַ����������ָ�����
    '        ByVal String1���ָ���1
    '        ByVal String2���ָ���2
    '����ֵ������ɹ������س�ȥ�ָ��������е��ַ���ʣ�µ��ַ���,
    '        ���򣬷ָ�����ƥ��,����chr(0)
    '        û�зָ���,����Chr(1)
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺15:02:13
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
        ElseIf InStr(1, szSource, String2) <> 0 Then 'ֻ�зָ���2
            MatchSplitSymbol = Chr(0) '��ƥ��
            Exit Function
        Else '�����ָ�����û��
            MatchSplitSymbol = Chr(1) '��ƥ��
            Exit Function
        End If
        If iStack = 0 Then '�ָ���ƥ��
            If iCurrent <= Len(szSource) Then
                MatchSplitSymbol = Left(szSource, iSP - 1) & Right(szSource, Len(szSource) - iCurrent + 1)
                szSource = Mid(szSource, iSP + iLen1, iCurrent - iLen2 - (iSP + iLen1))
            Else
                MatchSplitSymbol = Left(szSource, iSP - 1)
                szSource = Mid(szSource, iSP + iLen1, iCurrent - iLen2 - (iSP + iLen1))
            End If
        Else '��ƥ��
            MatchSplitSymbol = Chr(0)
        End If
    End Function

    '*******************************************************************************************************
    '��������MatchSplitSymbol
    '��  �ܣ�ƥ������ָ�����
    '        ����:Դ�ַ���:szSource = "for(int i = 1; i < 10; i++) { b++; }"
    '             �ָ���:String1 = "("
    '                    String2 = ")"
    '        ����ô˺����󷵻أ�
    '            szSource = "int i = 1; i < 10; i++"
    '            szBefor = "for"
    '            szBack = " { b++; }"
    '��  ����
    '        ByRef szSource As String�����롣���ƥ��ɹ����˲���Ϊ�ָ����еĴ��루�������ָ�����
    '        ByVal String1 As String���ָ���1
    '        ByVal String2 As String���ָ���2
    '        ByRef szBefor As String�����ƥ��ɹ����ָ���ǰ�Ĵ��루�������ָ�����
    '        ByRef szBack As String�����ƥ��ɹ����ָ�����Ĵ��루�������ָ�����
    '����ֵ��ƥ��ʧ�ܣ�0
    '        ������û��ָ���ķָ�����-1
    '        �ɹ������طָ����д���ĳ���(�����ָ���)
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-5-2
    'ʱ  �䣺9:51:07
    '*******************************************************************************************************
    Function MatchSplitSymbol(ByRef szSource As String, ByVal String1 As String, ByVal String2 As String, ByRef szBefor As String, ByRef szBack As String) As Long
        Dim iStack As Integer, iCurrent As Integer, iStart As Integer, iEnd As Integer, iSP As Integer
        Dim iLen1 As Integer, iLen2 As Integer

        szBefor = ""
        szBack = ""
        MatchSplitSymbol = 0

        iLen1 = Len(String1)
        iLen2 = Len(String2)
        iSP = InStr(1, szSource, String1)
        If iSP <> 0 Then '�зָ���1
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
        ElseIf InStr(1, szSource, String2) <> 0 Then 'ֻ�зָ���2
            MatchSplitSymbol = 0 '��ƥ��
            Exit Function
        Else '�����ָ�����û��
            MatchSplitSymbol = -1 '��ƥ��
            Exit Function
        End If
        If iStack = 0 Then '�ָ���ƥ��
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
        Else '��ƥ��
            MatchSplitSymbol = 0
        End If
    End Function

    '*******************************************************************************************************
    '��������ReverseMatchSplitSymbol
    '��  �ܣ�����ƥ������ķָ���
    '        ����:Դ�ַ���:szSource = "for(int i = 1; i < 10; i++) { b++; }"
    '             �ָ���:String1 = "("
    '                    String2 = ")"
    '        ����ô˺����󷵻أ�
    '            szSource = "int i = 1; i < 10; i++"
    '            szBefor = "for"
    '            szBack = " { b++; }"
    '��  ����
    '        ByRef szSource As String�����롣���ƥ��ɹ����˲���Ϊ�ָ����еĴ��루�������ָ�����
    '        ByVal String1 As String���ָ���1
    '        ByVal String2 As String���ָ���2
    '        ByRef szBefor As String�����ƥ��ɹ����ָ���ǰ�Ĵ��루�������ָ�����,ʧ��,,���ַ���
    '        ByRef szBack As String�����ƥ��ɹ����ָ�����Ĵ��루�������ָ�����,ʧ��,���ַ���
    '����ֵ��ƥ��ʧ�ܣ�0
    '        ������û��ָ���ķָ�����-1
    '        �ɹ������طָ����д���ĳ���
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-5-2
    'ʱ  �䣺11:33:00
    '*******************************************************************************************************
    Function ReverseMatchSplitSymbol(ByRef szSource As String, _
                                     ByVal String1 As String, _
                                     ByVal String2 As String, _
                                     ByRef szBefor As String, _
                                     ByRef szBack As String) As Long
        Dim szReSou As String, szReStr1 As String, szReStr2 As String, szReBef As String, szReBack As String

        szBefor = ""
        szBack = ""
        szReSou = ""
        szReBack = ""

        szReSou = StrReverse(szSource)
        szReStr1 = StrReverse(String1)
        szReStr2 = StrReverse(String2)
        ReverseMatchSplitSymbol = MatchSplitSymbol(szReSou, szReStr2, szReStr1, szReBef, szReBack)
        If ReverseMatchSplitSymbol > 0 Then
            szBefor = StrReverse(szReBack)
            szBack = StrReverse(szReBef)
            szSource = StrReverse(szReSou)
        End If

    End Function

    '*******************************************************************************************************
    '��������MatchAllSymbol
    '��  �ܣ���Դ�ַ�����,�����ķָ����Ƿ�ƥ��
    '��  ����
    '        ByVal szSource As String��Դ�ַ���
    '        ByVal String1 As String���ָ���һ
    '        ByVal string2 As String���ָ�����
    '����ֵ��ȫ��ƥ�䷵�� TRUE�����򷵻� FALSE��
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-5-4
    'ʱ  �䣺14:47:01
    '*******************************************************************************************************
    Function MatchAllSymbol(ByVal szSource As String, ByVal String1 As String, ByVal string2 As String) As Boolean
        Dim szTemp As String, iRetrue As Integer, szBefor As String, szBack As String

        szTemp = szSource
        iRetrue = MatchSplitSymbol(szTemp, String1, string2, szBefor, szBack)
        While iRetrue > 0 '������ƥ���û������
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
    '��������GetFunctionName
    '��  �ܣ��õ�������
    '��  ����
    '        szCode:����
    '����ֵ��������
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺14:03:31
    '*******************************************************************************************************
    Function GetFunctionName(ByVal szCode As String) As String
        Dim iPos As Integer, Pos As Integer
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
            If InStr(GetFunctionName, "::") > 0 Then
                GetFunctionName = Split(GetFunctionName, "::")(1)
            End If
        End If
    End Function

End Module
