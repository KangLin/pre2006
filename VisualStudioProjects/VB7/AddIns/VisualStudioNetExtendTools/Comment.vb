'*******************************************************************************************************
'�ļ�����Comment.vb
'��  �ܣ����������ע��
'��  ����2005.3.*
'��  �ߣ���  ��
'        ��Ȩ����  ��������Ȩ��
'E_Mail��kl222@126.com
'��  �ڣ�2005-5-5
'ʱ  �䣺2005-5-5 7:54:47
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
'
'FileName��Comment.vb
'Function��
'Author  ��KangLin
'          Copyright 2005 KangLin
'E_Mail  ��kl222@126.com
'Date    ��2005-5-5
'Time    ��2005-5-5 7:54:47
'Compiler��Microsoft Development Environment 7.10 ���� Basic 7.10
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

#Region "�û����޸ĵĳ���"

    Public g_szAuthor As String = "��  ��"    '����
    Public g_szCorporation As String = "���ֹ�����" '��˾
    Public g_szEAuthor As String = "KangLin"
    Public g_szECorporation As String = "KangLin Studio"
    Public g_szEmail As String = "kl222@126.com"

    '1������
    '2��Ӣ��
    Public g_iLanguage As Integer = 1
    Public g_bFunctionAuthor As Boolean = True   '����ע��ʱ�Ƿ������
    Public g_bFunctionDate As Boolean = True   '����ע��ʱ�Ƿ������
    Public g_bFunctionVersion As Boolean = True   '����ע��ʱ�Ƿ�Ӱ汾

    Public m_szSubName As String = "��������"
    Public m_szFunctionName As String = "��������"
    Public m_szClassName As String = "��  ����"
    Public m_szDescription As String = "��  ����"
    Public m_szPara As String = "��  ����"
    Public m_szReturnVal As String = "����ֵ��"
    Public m_szVersion As String = "��  ����"
    Public m_szAuthor As String = "��  �ߣ�"
    Public m_szDate As String = "ʱ  �䣺"

    '����
    Dim g_lVersion As String   '�汾��
    Dim g_szCompiler As String  '�������汾

    '����ע�ͷ�ʽ�Ŀ���
    Public g_bDoxygen As Boolean = True

#If VER_2003 Then
    Public m_DTE As EnvDTE.DTE  '
#End If
#If VER_2005 Then
    Public m_DTE As EnvDTE80.DTE2
#End If
#End Region

#Region "�������û������޸�"
    Const gc_szCLineCommentSymbol As String = "//"  'C���Ե���ע�ͷ�
    Const gc_szMarcoLineCommentSymbol As String = "'"  '�����ע�ͷ�
    'ע�Ϳ�ʼ��
    Const gc_szStartCommentSymbol As String = "/*******************************************************************************************************"
    'ע�ͽ�����
    Const gc_szEndCommentSymbol As String = "*******************************************************************************************************/"
    '��ע�Ϳ�ʼ��
    Const gc_szMarcoStartCommentSymbol As String = "'*******************************************************************************************************"
    '��ע�ͽ�����
    Const gc_szMarcoEndCommentSymbol As String = "'*******************************************************************************************************"
    '���ͬһ���ܵĺ����鿪ʼ��
    Const gc_szFunctionSectionStart As String = "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
    '���ͬһ���ܵĺ����������
    Const gc_szFunctionSectionEnd As String = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
    '�ں��������ͬһ���ܵ����鿪ʼ��
    Const gc_szSentenceSectionStart As String = "------------------------------------------------------------------------"
    '�ں��������ͬһ���ܵ����������
    Const gc_szSentenceSectionEnd As String = "------------------------------------------------------------------------"
    'Const gc_szCompiler = "Visual C++ 6.0"

#End Region

#Region "����"

    Function ActiveDocument() As Document
        ActiveDocument = m_DTE.ActiveDocument()
    End Function

    '*******************************************************************************************************
    '��������ListProj
    '��  ����
    '��  ����
    '        ByVal projitems As ProjectItems        ��
    '        ByVal Level As Integer                 ��
    '        Optional ByRef bFlag As Boolean = False��
    '����ֵ����
    '��  ����2005.8.0.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005��8��12�� 18:07:26
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
    '��������GetVerSion
    '��  �ܣ��õ��汾��
    '��  ������
    '����ֵ���汾��
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺18:58:32
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
    '��������GetCompiler
    '��  �ܣ��õ�������
    '��  ������
    '����ֵ��������
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺18:58:32
    '*******************************************************************************************************
    Function GetCompiler() As String
        g_szCompiler = m_DTE.Name & " " & m_DTE.Version & " ���� " & ActiveDocument().Language & " " & m_DTE.Version
    End Function

    '*******************************************************************************************************
    '��������GetFunctionReturn
    '��  �����õ���������ֵ
    '��  ����
    '        ByVal szCode������
    '����ֵ��String
    '��  ����2005.6.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005��7��14�� 10:17:34
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
                            GetFunctionReturn = "��"
                        Else
                            GetFunctionReturn = "void"
                        End If
                    Case 1
                        szTemp = szLeft & " ��"
                    Case 2
                        If Split(szCode)(0) = "extern" Or Split(szCode)(0) = "static" Then
                            szTemp = Left(Split(szCode)(iPos), 1)
                            If szTemp = "*" Or szTemp = "&" Then
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & szTemp & " ��"
                            Else
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & " ��"
                            End If
                        Else
                            szTemp = szLeft & " ��"
                        End If
                    Case Else
                        If Split(szCode)(0) = "static" Then
                            szTemp = Left(Split(szCode)(iPos), 1)
                            If szTemp = "*" Or szTemp = "&" Then
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & szTemp & " ��"
                            Else
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0))) & " ��"
                            End If
                        ElseIf Split(szCode)(0) = "extern" And UCase(Split(szCode)(1)) = """C""" Then
                            szTemp = Left(Split(szCode)(iPos), 1)
                            If szTemp = "*" Or szTemp = "&" Then
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0)) - Len(Split(szCode)(2)) - 1) & szTemp & " ��"
                            Else
                                szTemp = Right(szLeave, Len(szLeave) - Len(Split(szCode)(0)) - Len(Split(szCode)(2)) - 1) & " ��"
                            End If
                        Else
                            szTemp = szLeft & " ��"
                        End If
                End Select
                If Trim(szTemp) = "template ��" Then
                    szTemp = ""
                End If
                If szTemp <> "" Then
                    GetFunctionReturn = "����Ϊ " & szTemp
                End If
                If GetFunctionReturn = "void" And (g_iLanguage And 1) Then
                    GetFunctionReturn = "��"
                End If
            End If
        Else
            Dim szBefor As String, szBack As String
            iPos = MatchSplitSymbol(szCode, "(", ")", szBefor, szBack)
            If iPos > 0 Then
                iPos = InStrRev(LCase(szBack), " as ")
                If iPos Then
                    GetFunctionReturn = "����Ϊ " & Right(szBack, Len(szBack) - iPos - 3) & " ��"
                    Exit Function
                End If
            End If
            If g_iLanguage And 1 Then
                GetFunctionReturn = "��"
            Else
                GetFunctionReturn = "void"
            End If
        End If
    End Function

    '*******************************************************************************************************
    '��������FileDoxgenCommentString
    '��  �������ڵõ� Doxgen ���ɰ������ļ�ע��
    '��  ����void
    '����ֵ������Ϊ String ��
    '��  ����2006.12.1.0
    '��  �ߣ�KangLin
    'ʱ  �䣺2007��5��13�� 18:58:40
    '*******************************************************************************************************
    Function FileDoxgenCommentString() As String
        Dim Sel As TextSelection
        Sel = ActiveDocument.Selection
        Sel.Insert("/*!" & vbCrLf)
        If g_iLanguage And 1 Then
            Sel.Insert("\warning ��Ȩ���� (C) " & Year(Date.Today()) & " " & g_szCorporation & "����������Ȩ����" & vbCrLf)
            Sel.Insert("\file    " & ActiveDocument.Name & vbCrLf)
            Sel.Insert("\brief   ��ϸ����" & vbCrLf)
            Sel.Insert("\version " & g_lVersion & vbCrLf _
                     & "\author  " & g_szAuthor _
                     & " (" & g_szEmail & ")" & vbCrLf _
                     & "\date    " & Now().ToLongDateString & "  " & Now().ToLongTimeString & vbCrLf)
            Sel.Insert("\par     ������:" & vbCrLf _
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
    '��������FileCommentString
    '��  �ܣ��õ��ļ���ע��
    '��  ������
    '����ֵ���ļ�ע���ַ���
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-8-17
    'ʱ  �䣺19:45:54
    '*******************************************************************************************************
    Function FileCommentString() As String
        Dim Sel As TextSelection
        Sel = ActiveDocument.Selection
        'VC����
        If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
            '��������doxgenע��
            If g_bDoxygen Then
                FileCommentString = FileDoxgenCommentString()
            Else

                'Sel.Text = gc_szStartCommentSymbol & vbCrLf
                Sel.Insert(gc_szStartCommentSymbol & vbCrLf)
                If g_iLanguage And 1 Then
                    'Sel.Text =
                    Sel.Insert("��Ȩ���� (C) " & Year(Date.Today()) & " " & g_szCorporation & "����������Ȩ����" & vbCrLf _
                       & "�ļ�����" & ActiveDocument.Name & vbCrLf _
                       & "��  ����" & vbCrLf _
                       & "��  ����" & g_lVersion & vbCrLf _
                       & "��  �ߣ�" & g_szAuthor & vbCrLf)
                    Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                    'Sel.Text = 
                    Sel.Insert("E_Mail��" & g_szEmail & vbCrLf _
                                       & "��  �ڣ�" & Now().ToLongDateString & vbCrLf _
                                       & "ʱ  �䣺" & Now().ToLongTimeString & vbCrLf _
                                       & "��������" & g_szCompiler & vbCrLf)
                End If
                If g_iLanguage = 3 Then
                    'Sel.Text = vbCrLf
                    Sel.Insert(vbCrLf)
                End If
                If g_iLanguage And 2 Then
                    'Sel.Text =
                    Sel.Insert("Copyright (C) " & Year(Date.Today()) & " " & g_szECorporation & ";All rights reserved." & vbCrLf _
                                             & "FileName   ��" & ActiveDocument.Name & vbCrLf _
                                             & "Description��" & vbCrLf _
                                             & "Version    ��" & g_lVersion & vbCrLf _
                                             & "Author     ��" & g_szEAuthor & vbCrLf)
                    Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                    'Sel.Text = 
                    Sel.Insert("E_Mail     ��" & g_szEmail & vbCrLf _
                                             & "Date       ��" & Now().Date() & vbCrLf _
                                             & "Time       ��" & Now().ToLongTimeString & vbCrLf _
                                             & "Compiler   ��" & g_szCompiler & vbCrLf)
                End If
                'Sel.Text = 
                Sel.Insert(gc_szEndCommentSymbol)
            End If
        End If

        'VB����
        If ActiveDocument.Language = "Basic" Then
            Sel.Text = gc_szMarcoStartCommentSymbol & vbCrLf
            If g_iLanguage And 1 Then
                'Sel.Text =
                Sel.Insert("'��Ȩ���� (C) " & Year(Date.Today) & " " & g_szCorporation & "����������Ȩ����" & vbCrLf _
                      & "'�ļ�����" & ActiveDocument.Name & vbCrLf _
                      & "'��  ����" & vbCrLf _
                      & "'��  ����" & g_lVersion & vbCrLf _
                      & "'��  �ߣ�" & g_szAuthor & vbCrLf)

                Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                'Sel.Text =
                Sel.Insert("'E_Mail��" & g_szEmail & vbCrLf _
                      & "'��  �ڣ�" & Now().ToLongDateString & vbCrLf _
                      & "'ʱ  �䣺" & Now().ToLongTimeString & vbCrLf _
                      & "'��������" & g_szCompiler & vbCrLf)
            End If
            If g_iLanguage = 3 Then
                Sel.Text = "'" & vbCrLf
            End If
            If g_iLanguage And 2 Then
                'Sel.Text =
                Sel.Insert("'Copyright (C) " & Year(Date.Today()) & " " & g_szECorporation & ";All rights reserved." & vbCrLf _
                         & "'FileName   ��" & ActiveDocument.Name & vbCrLf _
                         & "'Description��" & vbCrLf _
                         & "'Version    ��" & g_lVersion & vbCrLf _
                         & "'Author     ��" & g_szEAuthor & vbCrLf)
                Sel.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
                'Sel.Text =
                Sel.Insert("'E_Mail     ��" & g_szEmail & vbCrLf _
                         & "'Date       ��" & Now().ToLongDateString & vbCrLf _
                         & "'Time       ��" & Now().ToLongTimeString & vbCrLf _
                         & "'Compiler   ��" & g_szCompiler & vbCrLf)
            End If
            Sel.Text = gc_szMarcoEndCommentSymbol
        End If

    End Function

    '*******************************************************************************************************
    '��������GetFunctionParamters
    '��  �ܣ��õ������б�
    '�޸�:����ģ��������ʱa(CList<T,T> p) ,��������
    '��  ����
    '        ByVal szCode������
    '����ֵ�������б�
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺15:02:44
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
        MatchSplitSymbolB(szCode, "(", ")") '�õ������еĲ���
        szTemp = ValidCode(szCode)

        If szTemp = "" Then '�޲���
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                If g_iLanguage And 1 Then
                    GetFunctionParamters = "��" & vbCrLf
                Else
                    GetFunctionParamters = "void" & vbCrLf
                End If
            End If
            If ActiveDocument.Language = "Basic" Then
                If g_iLanguage And 1 Then
                    GetFunctionParamters = "��"
                Else
                    GetFunctionParamters = "void"
                End If
            End If
        Else '�в���
            '���ǵ��������ж��ŵ����
            GetFunctionParamters = CommaInBracket(szTemp)

            '����ֺ�
            szPara = ""
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                j = UBound(Split(GetFunctionParamters, "��" & vbCrLf))
                For i = 0 To j - 1 '�õ���������
                    szTemp = Split(GetFunctionParamters, "��" & vbCrLf)(i)
                    If Len(szTemp) > iLen Then
                        iLen = Len(szTemp)
                    End If
                Next i

                For i = 0 To j - 1 '�õ���������
                    szTemp = Split(GetFunctionParamters, "��" & vbCrLf)(i)
                    If iLen - Len(szTemp) > 0 Then
                        szPara = szPara & szTemp & Space(iLen - Len(szTemp)) & "��" & vbCrLf
                    Else
                        szPara = szPara & szTemp & "��" & vbCrLf
                    End If
                Next i

                If szPara <> "" Then
                    GetFunctionParamters = vbCrLf & "        " & szPara
                End If
            End If

            If ActiveDocument.Language = "Basic" Then
                j = UBound(Split(GetFunctionParamters, vbCrLf))
                For i = 0 To j  '�õ���������
                    szTemp = Split(GetFunctionParamters, vbCrLf)(i)
                    If Len(szTemp) > iLen Then
                        iLen = Len(szTemp)
                    End If
                Next i

                For i = 1 To j  '�õ���������
                    szTemp = Split(GetFunctionParamters, vbCrLf)(i)
                    If iLen - Len(szTemp) > 0 Then
                        szPara = szPara & vbCrLf & Left(szTemp, Len(szTemp) - 1) & Space(iLen - Len(szTemp)) & "��"
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
    '��������CommaInBracket
    '��  �ܣ����ǲ����������ţ����������ж��ŵ����
    '��  ����
    '        ByVal szCode������
    '����ֵ�������б�
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2006-11-4
    'ʱ  �䣺17:29:44
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
        '�������ж��ŵ������int a(int (*p)(int c, int d), int f);
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

        If i < 0 Or j < 0 Then '�޸�:���Ų�ƥ�䣬����
            MsgBox("�����д�����", MsgBoxStyle.Critical Or MsgBoxStyle.OkOnly)
            CommaInBracket = GetParamters(szTemp, iLen)
            Exit Function
        End If

        If i > 0 Or j > 0 Or k > 0 Then
            MatchSplitSymbolB(szTemp, szBeforChar, szBackChar, szBefor, szBack)
            szPara = GetParamters(szBefor, iLen)
            szPara = Left(szPara, Len(szPara) - Len("��" & vbCrLf))
            szPara = szPara & szBeforChar & szTemp & szBackChar
            If Not (szBack Is Nothing) Then
                CommaInBracket = szPara & CommaInBracket(szBack)
            End If
        Else '�����ŵ����
            CommaInBracket = GetParamters(szTemp, iLen)
        End If
    End Function

    '*******************************************************************************************************
    '��������GetParamters
    '��  �����õ����������Ų����б�Ĳ����б���ͨ���������������
    '��  ����
    '        ByVal szTemp As String������
    '        ByRef iLen As Integer �������ĳ���
    '����ֵ������Ϊ String �������б�
    '��  ����2005.8.0.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005��8��12�� 16:33:41
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
        'For i = 0 To j '�õ���������
        '    If Len(ValidCode(Split(szTemp, ",")(i))) > iLen Then
        '        iLen = Len(ValidCode(Split(szTemp, ",")(i)))
        '    End If
        'Next i
        For i = 0 To j
            'C����
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                szPara = ValidCode(Split(szTemp, ",")(i))
                If szPara = "void" Then
                    If g_iLanguage And 1 Then
                        szPara = "void����"
                    Else
                        szPara = "void��void"
                    End If
                Else
                    'szPara = szPara & Space(iLen - Len(szPara)) & "��"
                    szPara = szPara & "��"
                End If

                GetParamters = GetParamters & szPara & vbCrLf
            End If
            'VB����
            If ActiveDocument.Language = "Basic" Then
                'GetParamters = GetParamters _
                '                       & vbCrLf & "'        " _
                '                       & ValidCode(Split(szTemp, ",")(i)) _
                '                       & Space(iLen - Len(ValidCode(Split(szTemp, ",")(i)))) _
                '                       & "��"
                GetParamters = GetParamters _
                                      & vbCrLf & "'        " _
                                      & ValidCode(Split(szTemp, ",")(i)) _
                                      & "��"
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
        MatchSplitSymbolB(szCode, "(", ")") '�õ������еĲ���
        szTemp = ValidCode(szCode)

        If szTemp = "" Then '�޲���
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                If g_iLanguage And 1 Then
                    GetFunctionDoxgenParamters = "��" & vbCrLf
                Else
                    GetFunctionDoxgenParamters = "void" & vbCrLf
                End If
            End If
            If ActiveDocument.Language = "Basic" Then
                If g_iLanguage And 1 Then
                    GetFunctionDoxgenParamters = "��"
                Else
                    GetFunctionDoxgenParamters = "void"
                End If
            End If
            GetFunctionDoxgenParamters = "\param   " & GetFunctionDoxgenParamters
        Else '�в���
            '���ǵ��������ж��ŵ����
            GetFunctionDoxgenParamters = CommaInBracket(szTemp)

            '����ֺ�
            szPara = ""
            If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
                j = UBound(Split(GetFunctionDoxgenParamters, "��" & vbCrLf))
                For i = 0 To j - 1 '�õ���������
                    szTemp = Split(GetFunctionDoxgenParamters, "��" & vbCrLf)(i)
                    If Len(szTemp) > iLen Then
                        iLen = Len(szTemp)
                    End If
                Next i

                For i = 0 To j - 1 '�õ���������
                    szTemp = Split(GetFunctionDoxgenParamters, "��" & vbCrLf)(i)
                    If iLen - Len(szTemp) > 0 Then
                        szPara = szPara & "\param   " & szTemp & Space(iLen - Len(szTemp)) & "��" & vbCrLf
                    Else
                        szPara = szPara & "\param   " & szTemp & "��" & vbCrLf
                    End If
                Next i

                GetFunctionDoxgenParamters = szPara
            End If
        End If
    End Function

    '*******************************************************************************************************
    '��������FunctionDoxgenCommentString
    '��  �������ڵõ� Doxgen ע�����ɰ����ĺ�������
    '��  ����
    '        ByVal szCode As String��
    '����ֵ������Ϊ String ��
    '��  ����2006.12.1.0
    '��  �ߣ�KangLin
    'ʱ  �䣺2007��5��13�� 18:59:32
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
    '��������FunctionCommentString
    '��  �ܣ��Զ����ɺ���ע��
    '��  ����
    '        ByVal szCode������
    '����ֵ��ע��
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-8-17
    'ʱ  �䣺13:38:42
    '*******************************************************************************************************
    Function FunctionCommentString(ByVal szCode As String) As String
        Dim Sel As TextSelection
        Dim szTemp As String

        Sel = ActiveDocument.Selection

        'VC����
        If ActiveDocument().Language = EnvDTE.Constants.dsCPP Then
            '��������doxgenע��
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

        'VB����
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
    '��������Section
    '��  �ܣ��Կ��ע��
    '��  ����
    '        ByVal szPrompt����ʾ�ַ�
    '        ByVal szInput������ɵĹ���
    '        ByVal szFunctionSectionStart��ע�͸�ʽ�Ŀ�ʼ����
    '        ByVal szFunctionSectionEnd��ע�͸�ʽ�Ľ�������
    '����ֵ����
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-10-18
    'ʱ  �䣺12:15:03
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
        sel.Text = szCommentSymbol & "������" & szInput & szPrompt
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
        sel.Text = szCommentSymbol & "������" & szInput & szPrompt
        'sel.EndOfLine()
        sel.NewLine()
        sel.Text = szCommentSymbol
        'sel.EndOfLine()
        sel.NewLine()
    End Function

#End Region

#Region "����"
#Region "VB��VC����"
    '*******************************************************************************************************
    '��������FunctionComment
    '��  �ܣ����������ļ������Զ���ע��
    '��  �����Ȱѹ����ں��������е�ͷ���ϣ�Ȼ����ִ�б����̼����Զ���������ע��
    '��  ������
    '��  �ߣ���  ��
    '��  ����1.0
    '��  �ڣ�2004-8-17
    'ʱ  �䣺15:29:30
    '*******************************************************************************************************
    Sub FunctionComment()
        'DESCRIPTION: �Զ����Ӻ���ע��
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
                Select Case MsgBox("�Ƿ��ڵ�ǰλ�ò���ע��?", MsgBoxStyle.YesNoCancel Or MsgBoxStyle.Information Or MsgBoxStyle.DefaultButton2)
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

        If Sel.AnchorPoint.Line = 1 Then '�ļ�ע��
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
            '���Ų�ƥ��
            Sel.LineDown(True)
            szText = Sel.Text
            ValidCCode(szText, szTemp)
            SelText = szTemp
            If Sel.BottomPoint.AtEndOfDocument Then
                MsgBox("������ѹ����ں�������ĵ�һ�С�", MsgBoxStyle.OkOnly Xor MsgBoxStyle.Critical)
                Sel.MoveToPoint(Sel.AnchorPoint)
                Exit Sub
            End If
        End While

        '����:_declspec __declspec
        If EnvDTE.Constants.dsCPP = ActiveDocument.Language Then
            Dim szBefor As String, szBack As String
            Select Case GetFunctionName(SelText)
                Case "_declspec", "__declspec"
                    iLine = Sel.AnchorPoint.Line()
                    MatchSplitSymbolB(SelText, "(", ")", szBefor, szBack)
                    SelText = Left(szBefor, InStrRev(szBefor, " ")) & szBack
                    szTemp = SelText

                    While MatchSplitSymbolB(szTemp, "(", ")") <= 0
                        '���Ų�ƥ��
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

    Sub ����ע��()
        FunctionComment()
    End Sub

    '*******************************************************************************************************
    '��������AlignComment
    '��  �ܣ����������ע��
    '��  ������
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-12-21
    'ʱ  �䣺16:57:27
    '*******************************************************************************************************
    Sub AlignComment()
        'DESCRIPTION: ���������ע��
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
    '��������AlignPointSign
    '��  ��������ָ�����������
    '��  ������
    '��  ����2007.9.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��17�� 13:35:48
    '*******************************************************************************************************
    Sub AlignPointSign()
        Dim szSign As String
        szSign = InputBox("����Ҫ����ķ��ţ�", "����ָ���ķ���", "=")
        If szSign <> "" Then
            AlignSign(szSign)
        End If
    End Sub

    '*******************************************************************************************************
    '��������AlignPointSign1
    '��  ��������ָ�����������
    '��  ������
    '��  ����2007.9.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��17�� 13:35:48
    '*******************************************************************************************************
    Sub AlignPointSign1()
        Dim szSign As String
        szSign = InputBox("����Ҫ����ķ��ţ�", "����ָ���ķ���", "=")
        If szSign <> "" Then
            AlignSign1(szSign)
        End If
    End Sub

    '*******************************************************************************************************
    '��������AlignSign
    '��  �������ո����ķ��Ž��ж���
    '��  ����
    '        ByVal szComment As String�������Ķ������
    '��  ����2007.9.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��17�� 13:26:25
    '*******************************************************************************************************
    Sub AlignSign(ByVal szComment As String)
        Dim sel As TextSelection, iStart As Integer, iEnd As Integer, iCol As Integer, iCur As Integer
        Dim i As Integer, j As Integer
        Dim iLine As Integer

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        sel = ActiveDocument.Selection

        iCol = 0 'ע�͵����λ�ô�
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
            '�жϴ����Ƿ�ֻ��ע����
            If LCase(Left(TrimString(sel.Text), Len(szComment))) <> LCase(szComment) Then
                '����ע�������ĺ���
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
                Else '������ע��
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

    Sub ����ע��()
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
        iCol = 0 'ע�͵����λ�ô�
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
            '�жϴ����Ƿ�ֻ��ע����
            If LCase(Left(TrimString(sel.Text), Len(szComment))) <> LCase(szComment) Then
                '����ע�������ĺ���
                If InStr(1, sel.Text, szComment) > 0 Then
                    sel.GotoLine(sel.AnchorPoint.Line)
                    sel.FindText(szComment)
                    j = sel.ActivePoint.DisplayColumn - Len(szComment)
                Else '������ע��
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
    '��������AlignComment1
    '��  �ܣ����������ע��,��AlignComment����������:��������Զ��ע�Ͷ���
    '��  ������
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-12-21
    'ʱ  �䣺16:57:27
    '*******************************************************************************************************
    Sub AlignComment1()
        'DESCRIPTION: ���������ע��,����Զ��ע��Ϊ׼
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

    Sub ����ע��1()
        AlignComment1()
    End Sub

    '*******************************************************************************************************
    '��������FunctionSection
    '��  �ܣ���ִ��ĳ�����ܵĺ�����ӱ�־��
    '��  ������
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-10-18
    'ʱ  �䣺12:17:09
    '*******************************************************************************************************
    Sub FunctionSection()
        'DESCRIPTION: ��־��ִ��ĳ�����ܵĺ����顣
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
        szInput = InputBox("�����뺯����Ĺ��ܣ�", "�����鹦��")
        If szInput <> "" Then
            Section("���ܵĺ�����", "��� ===" & szInput & "=== ", szCommentSymbol & gc_szFunctionSectionStart, szCommentSymbol & gc_szFunctionSectionEnd)
        End If
    End Sub

    Sub ������ע��()
        FunctionSection()
    End Sub

    '*******************************************************************************************************
    '��������SentenceSection
    '��  �ܣ���־����ĳ��������ִ��ĳ�����ܵ����顣
    '��  ������
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-10-18
    'ʱ  �䣺12:23:48
    '*******************************************************************************************************
    Sub SentenceSection()
        'DESCRIPTION:  ��־����ĳ��������ִ��ĳ�����ܵ����顣
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
        szInput = InputBox("����������Ĺ��ܣ�", "���鹦��")
        If szInput <> "" Then
            Section("���ܵ�����", "��� ===" & szInput & "=== ", szCommentSymbol & gc_szSentenceSectionStart, szCommentSymbol & gc_szSentenceSectionEnd)
        End If
    End Sub

    '*******************************************************************************************************
    '��������AddEndIf
    '��  �������ӽ�����ע��
    '��  ������
    '��  ����2005.7.0.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005��7��24�� 17:08:41
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
    '        While (MatchSplitSymbolB(szTemp,  "{", "}") <= 0) 'û�з��Ż�ƥ��
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
    '                    If InStr(szIn, "{") Then '������Ƕ��
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
    '��������AddEndIf
    '��  �������ӽ�����ע��
    '��  ������
    '��  ����2005.7.3.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005��7��26�� 17:02:41
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

#Region "��VC��"
    '*******************************************************************************************************
    '��������SwitchCppToH
    '��  �ܣ�ִ���ļ���ͷ�ļ�����
    '��  ������
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-10-18
    'ʱ  �䣺10:10:18
    '*******************************************************************************************************
    Sub SwitchCppToH()
#If DEBUG Then
#Else
        On Error Resume Next
#End If
        'DESCRIPTION: ִ���ļ���ͷ�ļ�����
        Dim FileName As String, FileExt As String

        If (ActiveDocument() Is Nothing) Or ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("������ֻ������ C/C++")
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

    Sub ͷ�ļ���ִ���ļ������л�()
        SwitchCppToH()
    End Sub

    '*******************************************************************************************************
    '��������Modify
    '��  �ܣ��޸ġ����ӡ�ɾ������Ϣ
    '��  ������
    '��  �ߣ���  ��
    '��  ����2.0.0.1
    '��  �ڣ�2004-11-17
    'ʱ  �䣺13:57:41
    '*******************************************************************************************************
    Sub Modify()
        'DESCRIPTION: �޸���Ϣ
        Dim sel As TextSelection
        Dim szCommentSymbol As String, szEndCommentSymbol As String
        Dim szInput As String

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        If ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("�����������C")
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
        'sel.text = "��  �ߣ�" &  g_szAuthor & vbCrLf _
        '         & "��  ����" & g_lVersion & vbCrLf _
        '		 & "��  �ڣ�" & Date & vbCrLf _
        '		 & "ʱ  �䣺" & Time & vbCrLf _
        szInput = InputBox("�����룺" & vbCrLf _
                         & "         1������" & vbCrLf _
             & "         2������ע��" & vbCrLf _
             & "         3���޸�" & vbCrLf _
             & "         4��ɾ��(������)" & vbCrLf _
             & "         5��ɾ��(������)" & vbCrLf, "�޸�", "1")

        If szInput = "" Then
            Exit Sub
        End If

        If szInput = "1" Then
            szInput = "����"
            szEndCommentSymbol = szCommentSymbol
        End If

        If szInput = "2" Then
            szInput = "����ע��"
            Section("", "�� ---" & g_szAuthor & "--- " & szInput & "�� " & Now(), _
              gc_szStartCommentSymbol, gc_szCLineCommentSymbol & gc_szEndCommentSymbol)
            Exit Sub
        End If

        If szInput = "3" Then
            szInput = "�޸�"
            szEndCommentSymbol = szCommentSymbol
        End If

        If szInput = "4" Then
            szInput = "ɾ��"
            szCommentSymbol = "/*"
            szEndCommentSymbol = "*/"
            Section("", "�� ---" & g_szAuthor & "--- " & szInput & "�� " & Now(), _
                     szCommentSymbol & gc_szSentenceSectionStart, _
                     gc_szCLineCommentSymbol & gc_szSentenceSectionEnd & szEndCommentSymbol)
            Exit Sub
        End If

        If szInput = "5" Then
            szInput = "ɾ��"
            Section("", "�� ---" & g_szAuthor & "--- " & szInput & "�� " & Now(), _
                     gc_szStartCommentSymbol, gc_szCLineCommentSymbol & gc_szEndCommentSymbol)
            Exit Sub
        End If
        Section("", "�� ---" & g_szAuthor & "--- " & szInput & "�� " & Now().ToString, _
            szCommentSymbol & gc_szSentenceSectionStart, szEndCommentSymbol & gc_szSentenceSectionEnd)
    End Sub

    '*******************************************************************************************************
    '��������TRACE
    '��  �ܣ����� TRACE ���
    '��  ������
    '��  �ߣ���  ��
    '��  ����1.0.0.1
    '��  �ڣ�2004-12-21
    'ʱ  �䣺16:57:06
    '*******************************************************************************************************
    Sub TRACE()
        'DESCRIPTION: ���� TRACE ���
        Dim sel As TextSelection, szFormat As String, szInput As String, szOutput As String

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        If ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("�����������C")
            Exit Sub
        End If

        sel = ActiveDocument.Selection
        szInput = InputBox("�������ʽ:" & vbCrLf _
                           & "��ʽ�ַ����������ַ���֮����" & Chr(34) & ";" & Chr(34) & "����" & vbCrLf _
                           & "1��TRACE(_T(" & Chr(34) & "�ļ�:%s(��:%d) : " & "��ʾ�ַ�����\n" _
               & Chr(34) & "), __FILE__, __LINE__);" & vbCrLf _
               & "������Ϊ:" & vbCrLf _
               & ";��ʾ�ַ���" & vbCrLf _
               & "2��TRACE(_T(" & Chr(34) & "�ļ�:%s(��:%d) : %s, %d\n" & Chr(34) & "), szStr, iLen);" & vbCrLf _
               & "������Ϊ:" & vbCrLf _
               & ";%s, %d; szStr, iLen" & vbCrLf _
               & "3��TRACE(_T(" & Chr(34) & "%s, %d\n" & Chr(34) & "), szStr, iLen);" & vbCrLf _
               & "������Ϊ:" & vbCrLf _
               & "%s, %d; szStr, iLen" & vbCrLf _
               & "4��TRACE(_T(" & Chr(34) & "HELLO\n" & Chr(34) & "));" & vbCrLf _
               & "������Ϊ:" & vbCrLf _
               & "HELLO" & vbCrLf, _
               "�Զ�����TRACE���")
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
        'DESCRIPTION: �Զ����� _T("")
        Dim Sel As TextSelection, szInput As String

        If (ActiveDocument() Is Nothing) Then
            Exit Sub
        End If

        If ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("�����������C")
            Exit Sub
        End If

        Sel = ActiveDocument.Selection
        szInput = InputBox("������", "_T()")
        If szInput <> "" Then
            Sel.Text = "_T(" & Chr(34) & szInput & Chr(34) & ")"
        End If
    End Sub

    '*******************************************************************************************************
    '��������CommentTRACE
    '��  ����ע�͵� TRACE ���
    '��  ������
    '��  ����1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005-6-10 9:20:56
    '*******************************************************************************************************
    Sub CommentTRACE()
        Dim Sel As TextSelection, szTemp As String, szBefor As String, szBack As String, ir As Long
        Dim szInput As String
        If ActiveDocument() Is Nothing Or ActiveDocument.Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("������ֻ������ C/C++")
            Exit Sub
        End If
        Sel = ActiveDocument.Selection
        Sel.StartOfDocument()

        Do
            'ȥ��ע��
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


            '��ʼע�� TRACE
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
            MsgBox("������ֻ������ C/C++")
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
    '��������ClassComment
    '��  ������ע��
    '��  ������
    '����ֵ������Ϊ Integer ��
    '��  ����2006.12.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��14�� 12:46:53
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
    '��������ClassCommentString
    '��  ������ע�ʹ�
    '��  ����
    '        ByVal ClassName As String��
    '��  ����2006.12.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��14�� 15:31:11
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
    '��������ClassDoxgenCommentString
    '��  ������Doxgenע�ʹ�
    '��  ����
    '        ByVal ClassName As String��
    '��  ����2006.12.1.0
    '��  �ߣ���  ��
    'ʱ  �䣺2007��8��14�� 15:31:20
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

#Region "��������"
    Sub LoadSettings()
        Dim szKeyItem As String, Key As RegistryKey

        szKeyItem = "SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\"
        Try
            Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "�ļ�ע��", True)
            If Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(szKeyItem & "�ļ�ע��")
                Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "�ļ�ע��", True)
            End If
            g_szAuthor = Key.GetValue("����", g_szAuthor)
            g_szCorporation = Key.GetValue("��˾", g_szCorporation)
            g_szEAuthor = Key.GetValue("Author", g_szEAuthor)
            g_szECorporation = Key.GetValue("Corporation", g_szECorporation)
            g_szEmail = Key.GetValue("EMail", g_szEmail)
            g_iLanguage = Key.GetValue("����", g_iLanguage)
            If Key.GetValue("Ӣ��", g_iLanguage) And 2 Then
                g_iLanguage = Key.GetValue("Ӣ��", g_iLanguage) + g_iLanguage
            End If
            Key.Close()

            Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "����ע��", True)
            If Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(szKeyItem & "����ע��")
                Key = Registry.LocalMachine.OpenSubKey(szKeyItem & "����ע��", True)
            End If
            m_szSubName = Key.GetValue("������", m_szSubName)
            m_szFunctionName = Key.GetValue("������", m_szFunctionName)
            m_szClassName = Key.GetValue("����", m_szClassName)
            m_szDescription = Key.GetValue("����", m_szDescription)
            m_szPara = Key.GetValue("����", m_szPara)
            m_szReturnVal = Key.GetValue("����ֵ", m_szReturnVal)
            m_szVersion = Key.GetValue("�汾", m_szVersion)
            m_szAuthor = Key.GetValue("����", m_szAuthor)
            m_szDate = Key.GetValue("����", m_szDate)
            g_bFunctionVersion = Key.GetValue("����汾", g_bFunctionVersion)
            g_bFunctionAuthor = Key.GetValue("��������", g_bFunctionAuthor)
            g_bFunctionDate = Key.GetValue("��������", g_bFunctionDate)
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
