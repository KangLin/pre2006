'*******************************************************************************************************
'�ļ�����OpenFile.vb
'��  �ܣ����ļ��Ի���
'��  ����2005.3.*
'��  �ߣ���  ��
'        ��Ȩ����  ��������Ȩ��
'E_Mail��kl222@126.com
'��  �ڣ�2005-5-14
'ʱ  �䣺2005-5-14 21:27:02
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
'
'FileName��OpenFile.vb
'Function��Open file Dialog
'Author  ��KangLin
'          Copyright 2005 KangLin
'E_Mail  ��kl222@126.com
'Date    ��2005-5-14
'Time    ��2005-5-14 21:27:02
'Compiler��Microsoft Development Environment 7.10 ���� Basic 7.10
'*******************************************************************************************************

Public Class frmOpenPath
    Inherits System.Windows.Forms.Form

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
    Friend WithEvents butBrowe As System.Windows.Forms.Button
    Friend WithEvents butOK As System.Windows.Forms.Button
    Friend WithEvents butCacenl As System.Windows.Forms.Button
    Friend WithEvents dlgOpen As System.Windows.Forms.OpenFileDialog
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmOpenPath))
        Me.Label1 = New System.Windows.Forms.Label
        Me.txtFile = New System.Windows.Forms.TextBox
        Me.butBrowe = New System.Windows.Forms.Button
        Me.butOK = New System.Windows.Forms.Button
        Me.butCacenl = New System.Windows.Forms.Button
        Me.dlgOpen = New System.Windows.Forms.OpenFileDialog
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 32)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "�ļ���"
        '
        'txtFile
        '
        Me.txtFile.Location = New System.Drawing.Point(64, 24)
        Me.txtFile.Name = "txtFile"
        Me.txtFile.Size = New System.Drawing.Size(360, 21)
        Me.txtFile.TabIndex = 1
        Me.txtFile.Text = "TextBox1"
        '
        'butBrowe
        '
        Me.butBrowe.Location = New System.Drawing.Point(440, 24)
        Me.butBrowe.Name = "butBrowe"
        Me.butBrowe.Size = New System.Drawing.Size(80, 24)
        Me.butBrowe.TabIndex = 2
        Me.butBrowe.Text = "�����&B��"
        '
        'butOK
        '
        Me.butOK.Location = New System.Drawing.Point(168, 80)
        Me.butOK.Name = "butOK"
        Me.butOK.Size = New System.Drawing.Size(80, 24)
        Me.butOK.TabIndex = 3
        Me.butOK.Text = "ȷ��(&O)"
        '
        'butCacenl
        '
        Me.butCacenl.Location = New System.Drawing.Point(296, 80)
        Me.butCacenl.Name = "butCacenl"
        Me.butCacenl.Size = New System.Drawing.Size(80, 24)
        Me.butCacenl.TabIndex = 3
        Me.butCacenl.Text = "ȡ��(&C)"
        '
        'frmOpenPath
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(528, 117)
        Me.Controls.Add(Me.butOK)
        Me.Controls.Add(Me.butBrowe)
        Me.Controls.Add(Me.txtFile)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.butCacenl)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "frmOpenPath"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "���ļ�"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Public szFilePath As String

    Private Sub butBrowe_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butBrowe.Click
        With dlgOpen
            .Filter = "ͷ�ļ�(*.h)|*.h|�����ļ�(*.*)|*.*"
            .ShowDialog()
            If .FileName <> "" Then
                szFilePath = .FileName
                txtFile.Text = szFilePath
            End If

        End With
    End Sub

    Private Sub butOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butOK.Click
        Me.Close()
    End Sub

    Private Sub butCacenl_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butCacenl.Click
        szFilePath = ""
        txtFile.Text = ""
        Me.Close()
    End Sub

    Private Sub frmOpenPath_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load
        szFilePath = ""
        txtFile.Text = szFilePath
    End Sub
End Class
