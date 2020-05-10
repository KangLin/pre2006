Option Strict Off
Option Explicit On 
Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If
Imports Microsoft.Win32
Imports System.Windows.Forms
Imports System.Text.RegularExpressions

Public Class frmBookMark
    Inherits System.Windows.Forms.Form

    Public m_szText As String
    Public m_szBookMark As String
    Public m_objSel As TextSelection
    Public m_Line As Integer
    Public m_bGet As Boolean = False
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
    Friend WithEvents lstBookMark As System.Windows.Forms.ListBox
    Friend WithEvents butOK As System.Windows.Forms.Button
    Friend WithEvents butCancel As System.Windows.Forms.Button
    Friend WithEvents txtBookMark As System.Windows.Forms.TextBox
    Friend WithEvents butAdd As System.Windows.Forms.Button
    Friend WithEvents butDelete As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmBookMark))
        Me.Label1 = New System.Windows.Forms.Label
        Me.lstBookMark = New System.Windows.Forms.ListBox
        Me.txtBookMark = New System.Windows.Forms.TextBox
        Me.butOK = New System.Windows.Forms.Button
        Me.butCancel = New System.Windows.Forms.Button
        Me.butAdd = New System.Windows.Forms.Button
        Me.butDelete = New System.Windows.Forms.Button
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 24)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(96, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Ҫ�������ǩ��"
        '
        'lstBookMark
        '
        Me.lstBookMark.ItemHeight = 12
        Me.lstBookMark.Location = New System.Drawing.Point(16, 72)
        Me.lstBookMark.Name = "lstBookMark"
        Me.lstBookMark.Size = New System.Drawing.Size(384, 268)
        Me.lstBookMark.TabIndex = 1
        '
        'txtBookMark
        '
        Me.txtBookMark.Location = New System.Drawing.Point(120, 24)
        Me.txtBookMark.Name = "txtBookMark"
        Me.txtBookMark.Size = New System.Drawing.Size(360, 21)
        Me.txtBookMark.TabIndex = 2
        Me.txtBookMark.Text = "txtBookMark"
        '
        'butOK
        '
        Me.butOK.Location = New System.Drawing.Point(144, 368)
        Me.butOK.Name = "butOK"
        Me.butOK.Size = New System.Drawing.Size(80, 24)
        Me.butOK.TabIndex = 3
        Me.butOK.Text = "ȷ��"
        '
        'butCancel
        '
        Me.butCancel.Location = New System.Drawing.Point(264, 368)
        Me.butCancel.Name = "butCancel"
        Me.butCancel.Size = New System.Drawing.Size(80, 24)
        Me.butCancel.TabIndex = 3
        Me.butCancel.Text = "ȡ��"
        '
        'butAdd
        '
        Me.butAdd.Location = New System.Drawing.Point(408, 96)
        Me.butAdd.Name = "butAdd"
        Me.butAdd.Size = New System.Drawing.Size(80, 24)
        Me.butAdd.TabIndex = 4
        Me.butAdd.Text = "���"
        '
        'butDelete
        '
        Me.butDelete.Location = New System.Drawing.Point(408, 304)
        Me.butDelete.Name = "butDelete"
        Me.butDelete.Size = New System.Drawing.Size(80, 24)
        Me.butDelete.TabIndex = 4
        Me.butDelete.Text = "ɾ��"
        '
        'frmBookMark
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(496, 405)
        Me.Controls.Add(Me.butAdd)
        Me.Controls.Add(Me.butOK)
        Me.Controls.Add(Me.txtBookMark)
        Me.Controls.Add(Me.lstBookMark)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.butCancel)
        Me.Controls.Add(Me.butDelete)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "frmBookMark"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "��ǩ"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub frmBookMark_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        txtBookMark.Text = m_szBookMark
        GetAllBookMark(m_szText)
        If m_bGet Then
            butAdd.Visible = False
            butDelete.Visible = False
        End If
    End Sub

    Private Sub butAdd_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butAdd.Click
        If lstBookMark.FindStringExact(txtBookMark.Text) <> -1 Then
            MsgBox("Ҫ�������ǩ�Ѵ��ڣ���Ϊ��ǩ��ȡ����", MsgBoxStyle.OKOnly Or MsgBoxStyle.Exclamation)
            Return
        End If
        If Trim(txtBookMark.Text) = "" Then
            MsgBox("���ܲ������ǩ�������ǩȡ������", MsgBoxStyle.Exclamation Or MsgBoxStyle.OKOnly)
            Return
        End If
        lstBookMark.Items.Add(txtBookMark.Text)
        m_objSel.GotoLine(m_Line)
        m_objSel.EndOfLine()
        Dim szBook As String, szComment As String
        szComment = SetComment(m_DTE)
        szBook = szComment & " <a name = """ & txtBookMark.Text & """></a>"
        m_objSel.Insert(szBook, EnvDTE.vsInsertFlags.vsInsertFlagsInsertAtEnd)
        m_objSel.Collapse()
    End Sub

    Private Sub butDelete_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butDelete.Click
        Dim szPattern As String, szComment As String
        szComment = SetComment(m_DTE)
        szPattern = szComment & ":Wh*\<a:Wh+name:Wh*=:Wh*""" & txtBookMark.Text & """\>:a*\</a\>"
        m_objSel.SelectAll()
        m_objSel.ReplacePattern(szPattern, "", EnvDTE.vsFindOptions.vsFindOptionsFromStart Or vsFindOptions.vsFindOptionsMatchInHiddenText Or EnvDTE.vsFindOptions.vsFindOptionsRegularExpression)
        m_objSel.GotoLine(m_Line)
        lstBookMark.Items.Remove(txtBookMark.Text)
    End Sub

    Private Sub butOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butOK.Click
        m_szBookMark = txtBookMark.Text
        m_objSel.GotoLine(m_Line)
        Me.Close()
    End Sub

    Private Sub butCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butCancel.Click
        m_szBookMark = ""
        m_objSel.GotoLine(m_Line)
        Me.Close()
    End Sub

    '*******************************************************************************************************
    '��������GetAllBookMark
    '��  �����õ������е�������ǩ
    '��  ����
    '        ByVal szText As String������
    '��  ����2005.7.0.0
    '��  �ߣ���  ��
    'ʱ  �䣺2005��7��18�� 11:31:27
    '*******************************************************************************************************
    Private Sub GetAllBookMark(ByVal szText As String)
        Dim szPattern As String, szComment As String
        szComment = SetComment(m_DTE)
        szPattern = szComment & "\s*<a[ \t]+name\s*=\s*""(?<book>[^""]*)"">[\s\w]*</a>"
        Dim r As Regex
        r = New Regex(szPattern)
        Dim m As Match
        m = r.Match(szText)
        While m.Success
            lstBookMark.Items.Add(m.Groups("book").Value)
            m = m.NextMatch
        End While
    End Sub

    Private Sub lstBookMark_DoubleClick(ByVal sender As Object, ByVal e As System.EventArgs) Handles lstBookMark.DoubleClick
        txtBookMark.Text = lstBookMark.Items(lstBookMark.SelectedIndex)
    End Sub
End Class
