'*******************************************************************************************************
'�ļ�����AutoFormatCode.vb
'��  �ܣ��Զ���ʽ������
'��  ����2005.3.*
'��  �ߣ���  ��
'        ��Ȩ����  ��������Ȩ��
'E_Mail��kl222@126.com
'��  �ڣ�2005-5-5
'ʱ  �䣺2005-5-5 7:59:38
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
'
'FileName��AutoFormatCode.vb
'Function��
'Author  ��KangLin
'          Copyright 2005 KangLin
'E_Mail  ��kl222@126.com
'Date    ��2005-5-5
'Time    ��2005-5-5 7:59:38
'Compiler��Microsoft Development Environment 7.10 ���� Basic 7.10
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
    Public m_bAddEndIf As Boolean = True '�Զ���ʽ��ʱ���Ƿ��Զ��ӽ�����ע��
    Public m_bEndIf As Boolean = False   '���κ������¶��Զ��޸Ľ�����ע�ͣ���Ϊ FALSE ʱ��ֻ���н�����־ʱ�ż�
    Public m_szEndIf As String = "����"

    '*******************************************************************************************************
    '��������FormatCode
    '��  �ܣ���ʽ������
    '��  ����
    '        ByVal StartPoint As EnvDTE.TextPoint��
    '        ByVal EndPoint As EnvDTE.TextPoint��
    '        ByVal Hint As Integer��
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-4-11
    'ʱ  �䣺6:37:42
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
        If iCur = iStart + 1 Then '�������һ��
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
                iChar = ValidCCode(szTemp, szOutCode, False, True) '�����//*********��
                'Debug.WriteLine("������ȣ�" & Len(szTemp) & " �����" & szTemp)
                szTemp = szOutCode
                iLen = ReverseMatchSplitSymbol(szTemp, "/*", "*/", szOut, szOut)
            Else
                Sel.MoveToPoint(EndPoint)
                Sel.MoveToPoint(StartPoint, True)
                szTemp = Sel.Text
                iLen = 0
            End If

            If iLen < 0 Then     'ע�ͷ���ƥ��,ֻ�� "/*" û�� "*/"
                '��ǰ���������ע����
                'ע�Ͳ��ڵ�ǰ������
                If iCommentStart <> StartPoint.Line Then
                    Sel.StartOfDocument()
                    Sel.MoveToPoint(EndPoint)

                    tp.TryToShow(vsPaneShowHow.vsPaneShowCentered)  '��������Ļ����
                    If iEnd = iStart Then                           '�������һ��
                        Sel.LineDown()
                    End If
                    Exit Sub
                Else                                                'ע���ڵ�ǰ������
                    '��ǰ������Ϊ�� a=/*....
                    Sel.GotoLine(iStart, True)
                    szTemp = Sel.Text
                End If

            Else
                If iLen > 0 Then                                    'ע�ͷ�ƥ��
                    '����:
                    '(1)/*...
                    '     .....
                    '     ...*/ a=b-5;
                    '�� 
                    '(2)��ǰ�а�����ע�� a = /*..*/ b;
                    '(3)/*....
                    '     ��ǰ�����У�a=c;
                    '     ....*/
                    '�����
                    Sel.MoveToPoint(EndPoint)
                    Sel.FindText("*/", EnvDTE.vsFindOptions.vsFindOptionsBackwards)
                    If Sel.ActivePoint.Line = iStart And iCommentStart <> iStart Then  '�Ƿ���������(1)
                        Sel.MoveToPoint(Sel.BottomPoint)
                        Sel.MoveToPoint(EndPoint, True)
                        szTemp = Left(Sel.Text, Len(Sel.Text) - 2)                     'ȥ�����з� VbCrLf
                    Else                                                               '���������л���ע�Ͷ���������-���(2)
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

            iLen = FormatVCCode(szTemp, szOut)  '�õ�VB��BSTR�ַ����ĳ���
            Sel.Delete()
            Sel.Insert(szOut, vsInsertFlags.vsInsertFlagsContainNewText)
            Sel.SmartFormat()                   '����ϵͳ�ĸ�ʽ��
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
            '�����ꡢ����
            GetMacro(szOut)
#End If

            tp.TryToShow(vsPaneShowHow.vsPaneShowCentered)  '��������Ļ����

        End If

        If iStart + 1 = iEnd Then                           '�س� 

            If EndSectionBracket(EndPoint) <> "" Then       '�Զ����� {}//...
                'Sel.NewLine()
                Sel.Insert(vbCrLf & "{", vsInsertFlags.vsInsertFlagsContainNewText)
                Sel.SmartFormat()
                Sel.MoveToPoint(Sel.BottomPoint)
            End If

            AddBracket(EndPoint, EndPoint.Line)             '�Զ���Ӵ�����

            tp.TryToShow(vsPaneShowHow.vsPaneShowCentered)  '��������Ļ����

            Select Case Split(Trim(szOut))(0)
                Case "#if", "#ifdef"
                    Sel.NewLine()
                    Sel.Insert("#endif // ���� " & szOut, vsInsertFlags.vsInsertFlagsContainNewText)
                    Sel.LineUp()
                Case Else
            End Select

        Else
            If iEnd + 1 = iCur Then                         '�������һ��
                ModifyBracket(szOut, iStart, EndPoint)
                Sel.LineDown()
            End If
        End If

        '�����������λ��
        Sel.MoveToLineAndOffset(Sel.ActivePoint.Line, iCol)
    End Sub

    '*******************************************************************************************************
    '��������AddBracket
    '��  �ܣ��Զ���Ӵ�����
    '��  ����
    '        ByVal EndPoint As EnvDTE.TextPoint��
    '        ByVal Sel As TextSelection��
    '        ByVal iEnd As Integer��
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-4-10
    'ʱ  �䣺21:22:03
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
       
        '����ȥ�������еĴ�����{��С����}
        iRetrue = ValidCCode(szTemp, szLeavings, False)
        szTemp = szLeavings
        Dim nCode As Integer, nBefor As Integer, nBack As Integer
        iRetrue = MatchSplitSymbolB(szTemp, "{", "}", szBefor, szBack, False) '��FALSE�Ǽӿ��ٶ�' <a href = "..\..\..\VC7\DLL\Syntax\CSyntax.cpp#bQutation"></a>

        While iRetrue > 0 '������ƥ��
            szTemp = szBack
            iRetrue = MatchSplitSymbolB(szTemp, "{", "}", szBefor, szBack, False)
        End While

        If iRetrue < 0 Then '����Ҵ�����
            If m_bAddEndIf Then
                szTemp = EndSection(EndPoint, Sel) '��� //if...
            Else
                szTemp = ""
            End If
            Sel.MoveToPoint(EndPoint)
            '����Ҵ�����
            'Sel.NewLine()
            Sel.Insert(vbCrLf & "}" & szTemp, vsInsertFlags.vsInsertFlagsContainNewText)
            Sel.SmartFormat()
            Sel.MoveToPoint(EndPoint)
        Else
            Sel.MoveToPoint(EndPoint)
        End If

    End Function

    '*******************************************************************************************************
    '��������EndSection
    '��  �ܣ���ɿ��ע�ͣ��������̹淶�ͷ�����?2-4��
    '��  ����
    '        ByVal iEndt��
    '        Byval Sel As TextSelection��
    '����ֵ��
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-5-2
    'ʱ  �䣺12:13:32
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
    '��������EndSectionBracket
    '��  �ܣ���ɿ��ע�ͣ��������̹淶�ͷ�����?2-4��
    '        ����:���� for(int i = 0; i < 10; i++)
    '             �Զ����Ϊ 
    '                   for(int i = 0; i < 10; i++)
    '                   {
    '                   
    '                   } //���� for(int i = 0; i < 10; i++)
    '��  ����
    '        ByVal Sel As TextSelection��
    '        Byval EndPoint As EnvDTE.TextPoint��
    '        ByVal iStart As Integer����������ڵ���
    '����ֵ��
    '��  �ߣ���  ��
    '��  ����2005.3.*
    '��  �ڣ�2005-5-13
    'ʱ  �䣺15:16:24
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
        '����ȥ�������еĴ�����{��С����}
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
    '��������ModifyBracket
    '��  �����Զ��޸Ĵ����ź��ע�͡�
    '        ֻ���ڹؼ���ͬ���޸�ʱ�����ܳɹ���������ڹؼ���ͬ�У����ܽ�����Ӧ���޸ġ�
    '��  ����
    '        ByVal szCode As String            ���޸ĵĴ���
    '        ByVal iStart As Integer           ����ʼ��
    '        ByVal EndPoint As EnvDTE.TextPoint��
    '����ֵ��
    '��  ����2005.6.*
    '��  �ߣ���  ��
    'ʱ  �䣺2005-6-23 10:26:09
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
        While (MatchSplitSymbolB(szTemp, "{", "}") <= 0 And Not Sel.ActivePoint.AtEndOfDocument)   'û�з��Ż�ƥ��
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
        Key = Registry.LocalMachine.OpenSubKey("SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\������ע��", True)
        If Not Key Is Nothing Then
            With Key
                m_bEndIf = .GetValue("�޸�ʱ�κ�������Զ��޸Ľ���ע��", False)
                m_bAddEndIf = .GetValue("��ʽ��ʱ�Զ����ӽ�����ע��", True)
                m_szEndIf = .GetValue("����ע�Ϳ��ַ�", "����")
            End With
        End If
    End Sub


End Class

