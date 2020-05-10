'*******************************************************************************************************
'��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
'�ļ�����frmHyperlink.vb
'��  �����༭������
'��  ����2005.7.0.0
'��  �ߣ���  ��
'E_Mail��kl222@126.com
'��  �ڣ�2005��7��19��
'ʱ  �䣺12:28:10
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
'*******************************************************************************************************
Option Strict On
Option Explicit On 

Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If

Imports System.Text.RegularExpressions
Imports System.Windows.Forms

Public Class frmHyperlink
    Inherits System.Windows.Forms.Form

    Public m_szCurFile As String '��ǰ�ĵ���
    Public m_objSel As TextSelection
#If VER_2003 Then
    Public m_DTE As DTE
#End If
#If VER_2005 Then
    Public m_DTE As EnvDTE80.DTE2
#End If


#Region " Windows ������������ɵĴ��� "

    Public Sub New()
        MyBase.New()

        '�õ����� Windows ���������������ġ�
        InitializeComponent()

        '�� InitializeComponent() ����֮������κγ�ʼ��

    End Sub

    '������д dispose ����������б�
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Windows ����������������
    Private components As System.ComponentModel.IContainer

    'ע��: ���¹����� Windows ����������������
    '����ʹ�� Windows ����������޸Ĵ˹��̡�
    '��Ҫʹ�ô���༭���޸�����
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents txtFile As System.Windows.Forms.TextBox
    Friend WithEvents butFile As System.Windows.Forms.Button
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents txtBookMark As System.Windows.Forms.TextBox
    Friend WithEvents butBookMark As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents txtHyperLink As System.Windows.Forms.TextBox
    Friend WithEvents butOK As System.Windows.Forms.Button
    Friend WithEvents butCancel As System.Windows.Forms.Button
    Friend WithEvents dlgOpen As System.Windows.Forms.OpenFileDialog
    Friend WithEvents butDelete As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmHyperlink))
        Me.Label1 = New System.Windows.Forms.Label
        Me.txtFile = New System.Windows.Forms.TextBox
        Me.butFile = New System.Windows.Forms.Button
        Me.Label2 = New System.Windows.Forms.Label
        Me.txtBookMark = New System.Windows.Forms.TextBox
        Me.butBookMark = New System.Windows.Forms.Button
        Me.Label3 = New System.Windows.Forms.Label
        Me.txtHyperLink = New System.Windows.Forms.TextBox
        Me.butOK = New System.Windows.Forms.Button
        Me.butCancel = New System.Windows.Forms.Button
        Me.dlgOpen = New System.Windows.Forms.OpenFileDialog
        Me.butDelete = New System.Windows.Forms.Button
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 40)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "�ļ���"
        '
        'txtFile
        '
        Me.txtFile.Location = New System.Drawing.Point(72, 32)
        Me.txtFile.Name = "txtFile"
        Me.txtFile.Size = New System.Drawing.Size(360, 21)
        Me.txtFile.TabIndex = 1
        Me.txtFile.Text = "txtFile"
        '
        'butFile
        '
        Me.butFile.Location = New System.Drawing.Point(440, 32)
        Me.butFile.Name = "butFile"
        Me.butFile.Size = New System.Drawing.Size(80, 24)
        Me.butFile.TabIndex = 2
        Me.butFile.Text = "���"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(16, 80)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(48, 16)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "��ǩ��"
        '
        'txtBookMark
        '
        Me.txtBookMark.Location = New System.Drawing.Point(72, 72)
        Me.txtBookMark.Name = "txtBookMark"
        Me.txtBookMark.Size = New System.Drawing.Size(360, 21)
        Me.txtBookMark.TabIndex = 4
        Me.txtBookMark.Text = "txtBookMark"
        '
        'butBookMark
        '
        Me.butBookMark.Location = New System.Drawing.Point(440, 72)
        Me.butBookMark.Name = "butBookMark"
        Me.butBookMark.Size = New System.Drawing.Size(80, 24)
        Me.butBookMark.TabIndex = 2
        Me.butBookMark.Text = "�����ǩ"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 120)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(56, 16)
        Me.Label3.TabIndex = 5
        Me.Label3.Text = "�����ӣ�"
        '
        'txtHyperLink
        '
        Me.txtHyperLink.Location = New System.Drawing.Point(72, 112)
        Me.txtHyperLink.Name = "txtHyperLink"
        Me.txtHyperLink.Size = New System.Drawing.Size(360, 21)
        Me.txtHyperLink.TabIndex = 6
        Me.txtHyperLink.Text = "txtHyperLink"
        '
        'butOK
        '
        Me.butOK.Location = New System.Drawing.Point(176, 168)
        Me.butOK.Name = "butOK"
        Me.butOK.Size = New System.Drawing.Size(80, 24)
        Me.butOK.TabIndex = 7
        Me.butOK.Text = "ȷ��"
        '
        'butCancel
        '
        Me.butCancel.Location = New System.Drawing.Point(296, 168)
        Me.butCancel.Name = "butCancel"
        Me.butCancel.Size = New System.Drawing.Size(80, 24)
        Me.butCancel.TabIndex = 7
        Me.butCancel.Text = "ȡ��"
        '
        'butDelete
        '
        Me.butDelete.Location = New System.Drawing.Point(440, 112)
        Me.butDelete.Name = "butDelete"
        Me.butDelete.Size = New System.Drawing.Size(80, 24)
        Me.butDelete.TabIndex = 8
        Me.butDelete.Text = "ɾ��"
        '
        'frmHyperlink
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(528, 205)
        Me.Controls.Add(Me.butDelete)
        Me.Controls.Add(Me.butOK)
        Me.Controls.Add(Me.txtHyperLink)
        Me.Controls.Add(Me.txtBookMark)
        Me.Controls.Add(Me.txtFile)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.butFile)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.butBookMark)
        Me.Controls.Add(Me.butCancel)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "frmHyperlink"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "�༭������"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub butFile_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butFile.Click
        With dlgOpen
            .ShowDialog()
            If .FileName() <> "" Then
                txtFile.Text = .FileName
                SetHyperlink()
            End If
        End With
    End Sub

    Private Sub butBookMark_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butBookMark.Click
        If Trim(txtFile.Text) = "" Then
            Exit Sub
        End If
        Dim szText As String, Sel As TextSelection
        Sel = CType(m_DTE.ActiveDocument.Selection, EnvDTE.TextSelection)

        Dim frm As frmBookMark
        frm = New frmBookMark
        With frm
            .m_bGet = True
            .m_Line = Sel.ActivePoint.Line
            .m_objSel = Sel
            .m_DTE = m_DTE

            m_DTE.ItemOperations.OpenFile(txtFile.Text, EnvDTE.Constants.vsViewKindCode).Activate()
            Sel = CType(m_DTE.ActiveDocument.Selection, EnvDTE.TextSelection)
            Dim iLine As Integer
            iLine = Sel.ActivePoint.Line
            Sel.SelectAll()
            .m_szText = Sel.Text
            Sel.GotoLine(iLine)
           
            .ShowDialog()
            If .m_szBookMark <> "" Then
                txtBookMark.Text = .m_szBookMark
                SetHyperlink()
            End If
            Sel = CType(m_DTE.ActiveDocument.Selection, EnvDTE.TextSelection)
            m_DTE.ItemOperations.OpenFile(m_szCurFile).Activate()
            Sel.GotoLine(.m_Line)
        End With
    End Sub

    Private Sub butOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butOK.Click
        Dim iCurLine As Integer, szComment As String
        If Trim(txtHyperLink.Text) <> "" Then
            iCurLine = m_objSel.ActivePoint.Line
            m_objSel.EndOfLine()
            szComment = SetComment(m_DTE)
            m_objSel.Insert(szComment & " <a href = """ & txtHyperLink.Text & """></a>")
            m_objSel.GotoLine(iCurLine)
            m_objSel.StartOfLine()
        End If
        Me.Close()
    End Sub

    Private Sub butCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butCancel.Click
        Me.Close()
    End Sub

    Private Sub frmHyperlink_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        txtFile.Text = ""
        txtBookMark.Text = ""
        txtHyperLink.Text = ""

        Dim iLine As Integer, szText As String
        iLine = m_objSel.ActivePoint.Line
        m_objSel.SelectLine()
        szText = m_objSel.Text
        m_objSel.GotoLine(iLine)

        '�޸�:ǰ�潨�������Ӻ�,���ڴ˴��ҿ�ʱ���ܲ鵽������
        Dim szPattern As String, szComment As String
        szComment = SetComment(m_DTE)
        szPattern = szComment & "\s*<a[ \t]+\w*href\s*=\s*""(?<href>[^""]*)"">[\s\w]*</a>"
        Dim r As Regex
        r = New Regex(szPattern)
        Dim m As Match
        m = r.Match(szText)
        While m.Success
            txtHyperLink.Text = m.Groups("href").Value
            m = m.NextMatch
        End While
    End Sub

    '*******************************************************************************************************
    '��������SetHyperlink
    '��  �������ó�����
    '��  ������
    '��  ����2005.7.0.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005��7��19�� 12:28:33
    '*******************************************************************************************************
    Private Sub SetHyperlink()
        Dim szPath As String, szFile As String, i As Integer
        szPath = Space(MAX_PATH)
        szFile = txtFile.Text
        i = PathRelativePath(szPath, m_szCurFile, FILE_ATTRIBUTE_NORMAL, szFile, FILE_ATTRIBUTE_NORMAL)
        szFile = Microsoft.VisualBasic.Strings.Left(szPath, i)

        If Microsoft.VisualBasic.Strings.Trim(txtBookMark.Text) <> "" Then
            txtHyperLink.Text = szFile
            txtHyperLink.Text = txtHyperLink.Text & "#" & txtBookMark.Text
        Else
            txtHyperLink.Text = szFile
        End If
    End Sub

    Private Sub txtFile_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFile.TextChanged
        SetHyperlink()
    End Sub

    Private Sub txtBookMark_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtBookMark.TextChanged
        SetHyperlink()
    End Sub

    Private Sub butDelete_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butDelete.Click
        Dim szPattern As String, Sel As TextSelection, iLine As Integer, szComment As String
        Sel = CType(m_DTE.ActiveDocument.Selection, EnvDTE.TextSelection)
        iLine = Sel.ActivePoint.Line
        Dim szTemp As String
        szTemp = Strings.Replace(txtHyperLink.Text, "\", "\\")
        szTemp = Strings.Replace(szTemp, "#", "\#")
        szComment = SetComment(m_DTE)
        szPattern = szComment & ":Wh*\<a:Wh+href:Wh*=:Wh*""" & szTemp & """\>:a*\</a\>"
        m_objSel.SelectLine()
        m_objSel.ReplacePattern(szPattern, "", EnvDTE.vsFindOptions.vsFindOptionsFromStart Or vsFindOptions.vsFindOptionsMatchInHiddenText Or EnvDTE.vsFindOptions.vsFindOptionsRegularExpression)
        m_objSel.GotoLine(iLine)
        m_objSel.StartOfLine()
        txtHyperLink.Text = ""
    End Sub
End Class
