'*******************************************************************************************************
'文件名：OtherTools.vb
'功  能：其它工具
'        添加头文件
'        得到相对路径,并复制到剪切板
'        超链接、书签
'版  本：2005.3.*
'作  者：康  林
'        版权所有  保留所有权利
'E_Mail：kl222@126.com
'日  期：2005-5-14
'时  间：2005-5-14 21:27:55
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'
'FileName：OtherTools.vb
'Function：Other tools
'Author  ：KangLin
'          Copyright 2005 KangLin
'E_Mail  ：kl222@126.com
'Date    ：2005-5-14
'Time    ：2005-5-14 21:27:55
'Compiler：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************

Option Strict Off
Option Explicit On

Imports EnvDTE

#If VER_2005 Then
Imports EnvDTE80
#End If
Imports System.Windows.Forms
Imports System.Text.RegularExpressions

Public Class OtherTools
#If VER_2003 Then
    Public m_DTE As EnvDTE.DTE
#End If
#If VER_2005 Then
    Public m_DTE As EnvDTE80.DTE2
#End If

    Function ActiveDocument() As Document
        ActiveDocument = m_DTE.ActiveDocument()
    End Function

    '*******************************************************************************************************
    '过程名：IncludeFile
    '功  能：添加头文件
    '参  数：无
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-5-14
    '时  间：21:28:24
    '*******************************************************************************************************
    Public Sub IncludeFile()
        Dim Sel As TextSelection
        Dim frm As frmOpenPath
        Dim i As Integer
        Dim szRelativePath As String, szFile As String

        If (ActiveDocument() Is Nothing) Or ActiveDocument().Language <> EnvDTE.Constants.dsCPP Then
            MsgBox("此工具只能用于C/C++")
            Exit Sub
        End If

        Sel = ActiveDocument().Selection
        Sel.SelectLine()
        szFile = ActiveDocument.FullName
        szRelativePath = Space(MAX_PATH)

        frm = New frmOpenPath
        frm.ShowDialog()
        If frm.szFilePath <> "" Then
            i = PathRelativePath(szRelativePath, szFile, FILE_ATTRIBUTE_NORMAL, frm.szFilePath, FILE_ATTRIBUTE_NORMAL)
            If i Then
                szFile = szRelativePath
            Else
                szFile = frm.szFilePath
            End If

            If TrimString(Sel.Text) <> "" Then
                Sel.MoveToPoint(Sel.AnchorPoint)
                Sel.LineUp()
                Sel.EndOfLine()
                Sel.NewLine()
            Else
                Sel.MoveToPoint(Sel.AnchorPoint)
            End If
            Sel.Insert("#include """ & szFile & """", vsInsertFlags.vsInsertFlagsContainNewText)
            Sel.MoveToPoint(Sel.BottomPoint)
        Else
            Sel.MoveToPoint(Sel.ActivePoint)
        End If

    End Sub

    '*******************************************************************************************************
    '过程名：GetFileRelativePath
    '描  述：得到相对路径,并把它复制到剪切板
    '参  数：无
    '版  本：2005.3.*
    '作  者：康  林
    '时  间：2005-5-16 17:30:19
    '*******************************************************************************************************
    Public Sub GetFileRelativePath()
        Dim szDes As String, Sel As TextSelection
        If ActiveDocument() Is Nothing Then
            Exit Sub
        End If
        Sel = ActiveDocument().Selection
        Try
            If Not (ActiveDocument.FullName Is Nothing) Then
                GetRelativePath(szDes, ActiveDocument().FullName())
                Exit Sub
            End If
        Catch ex As Exception
            GetRelativePath()
        End Try
    End Sub

    '*******************************************************************************************************
    '过程名：GetDate
    '描  述：得到当前日期
    '参  数：无
    '版  本：2005.3.*
    '作  者：康  林
    '时  间：2005-6-11 10:18:04
    '*******************************************************************************************************
    Public Sub GetDate()
        Dim objTextSelection As TextSelection, Sel As TextSelection, S As String
        objTextSelection = CType(m_DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        objTextSelection.Text = System.DateTime.Now.ToLongDateString()
        Exit Sub
        If ActiveDocument() Is Nothing Then
            Exit Sub
        End If
        s = Now().Date.ToString("yyyy年MM月dd日")
        Sel = ActiveDocument.Selection
        If Sel Is Nothing Then
            Clipboard.SetDataObject(s, True)
        Else
            Sel.Text = s
        End If
    End Sub

    '*******************************************************************************************************
    '过程名：GetTime
    '功  能：得到当前时间
    '参  数：无
    '作  者：康  林
    '版  本：2005.3.*
    '日  期：2005-6-11
    '时  间：10:17:47
    '*******************************************************************************************************
    Public Sub GetTime()
        Dim objTextSelection As TextSelection
        objTextSelection = CType(m_DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        objTextSelection.Text = System.DateTime.Now.ToLongTimeString()
        Exit Sub
        Dim Sel As TextSelection, s As String
        s = Now().TimeOfDay.ToString
        s = Left(s, InStr(s, ".") - 1)
        If ActiveDocument() Is Nothing Then
            Exit Sub
        End If
        Sel = ActiveDocument.Selection
        If Sel Is Nothing Then
            Clipboard.SetDataObject(s, True)
        Else
            Sel.Text = s
        End If
    End Sub

    '*******************************************************************************************************
    '过程名：CreateBookMark
    '描  述：建立书签
    '参  数：无
    '版  本：2005.6.1.0
    '作  者：康  林
    '时  间：2005年7月18日 10:58:55
    '*******************************************************************************************************
    Public Sub CreateBookMark()
        Dim Sel As TextSelection
        Dim szBookMarkName As String
        Sel = CType(m_DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        szBookMarkName = Sel.Text
        Dim CurLine As Integer
        CurLine = Sel.ActivePoint.Line
        Dim szAll As String
        Sel.SelectAll()
        szAll = Sel.Text
        Sel.GotoLine(CurLine)
        Dim frmBook As frmBookMark
        frmBook = New frmBookMark
        With frmBook
            .m_szBookMark = szBookMarkName
            .m_szText = szAll
            .m_objSel = Sel
            .m_Line = CurLine
            .m_DTE = m_DTE
        End With
        frmBook.ShowDialog()
    End Sub

    '*******************************************************************************************************
    '过程名：CreateHyperlink
    '描  述：建立超链接
    '参  数：无
    '版  本：2005.7.0.0
    '作  者：康  林
    '时  间：2005年7月19日 12:29:11
    '*******************************************************************************************************
    Public Sub CreateHyperlink()
        Dim Sel As TextSelection
        Dim CurLine As Integer
        Sel = CType(m_DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        CurLine = Sel.ActivePoint.Line
        Dim frm As frmHyperlink
        frm = New frmHyperlink
        With frm
            .m_DTE = m_DTE
            .m_objSel = Sel
            .m_szCurFile = ActiveDocument.FullName
            .ShowDialog()
        End With
    End Sub

    '*******************************************************************************************************
    '过程名：GoHyperlink
    '描  述：跳转超链接
    '参  数：无
    '版  本：2005.7.0.0
    '作  者：康  林
    '时  间：2005年7月19日 12:28:55
    '*******************************************************************************************************
    Public Sub GoHyperlink()
        Dim szComment As String
        Dim szText As String, szTemp(0) As String
        Dim Sel As TextSelection
        Sel = CType(m_DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        szComment = SetComment(m_DTE)
        Sel.SelectLine()
        szText = Sel.Text
        Sel.StartOfLine()
        Dim szPattern As String
        szPattern = szComment & "\s*<a[ \t]+href\s*=\s*""(?<book>[^""]*)"">[\s\w]*</a>"
        Dim r As Regex
        r = New Regex(szPattern)
        Dim m As Match
        m = r.Match(szText)
        Dim i As Integer
        i = 0
        While m.Success
            If i <> 0 Then
                ReDim Preserve szTemp(i)
            End If
            szTemp(i) = m.Groups("book").Value
            m = m.NextMatch
            i = i + 1
        End While
        Dim szFile As String
        Dim szBookMark As String
        szFile = Split(szTemp(0), "#")(0)
        Dim szPath As String
        szPath = Space(MAX_PATH)
        i = FullPath(szPath, szFile, m_DTE.ActiveDocument.FullName)
        szFile = Left(szPath, i)
        m_DTE.ItemOperations.OpenFile(szFile, EnvDTE.Constants.vsViewKindCode).Activate()
        If InStr(szTemp(0), "#") > 0 Then
            szBookMark = Split(szTemp(0), "#")(1)
        End If
        szComment = SetComment(m_DTE)
        szPattern = szComment & ":Wh*\<a:Wh+name:Wh*=:Wh*""" & szBookMark & """\>:a*\</a\>"
        Sel = CType(m_DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        Sel.StartOfDocument()
        Sel.SelectAll()
        Sel.FindPattern(szPattern, EnvDTE.vsFindOptions.vsFindOptionsFromStart Or vsFindOptions.vsFindOptionsMatchInHiddenText Or vsFindOptions.vsFindOptionsRegularExpression)
        Sel.StartOfLine()
    End Sub

End Class
