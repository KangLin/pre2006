'*******************************************************************************************************
'��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
'�ļ�����frmLicense.vb
'��  ������ʾЭ�鴰��
'��  ����2005.3.*
'��  �ߣ���  ��
'E_Mail��kl222@126.com
'��  �ڣ�2005-5-16
'ʱ  �䣺2005-5-16 17:36:17
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
'
'Copyright (C) 2005 KangLin Studio;All rights reserved.
'FileName   ��frmLicense.vb
'Description��
'Version    ��2005.3.*
'Author     ��KangLin
'E_Mail     ��kl222@126.com
'Date       ��2005-5-16
'Time       ��2005-5-16 17:36:17
'Compiler   ��Microsoft Development Environment 7.10 ���� Basic 7.10
'*******************************************************************************************************
Public Class frmLicense
    Inherits System.Windows.Forms.Form

#Region " Windows ������������ɵĴ��� "

    Public Sub New()
        MyBase.New()

        '�õ����� Windows ���������������ġ�
        InitializeComponent()

        '�� InitializeComponent() ����֮������κγ�ʼ��
        bAgree = False

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
    Friend WithEvents RichTextBox1 As System.Windows.Forms.RichTextBox
    Friend WithEvents cmdStart As System.Windows.Forms.Button
    Friend WithEvents cmdExit As System.Windows.Forms.Button
    Friend WithEvents RadioButton1 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton2 As System.Windows.Forms.RadioButton
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox
        Me.cmdStart = New System.Windows.Forms.Button
        Me.cmdExit = New System.Windows.Forms.Button
        Me.RadioButton1 = New System.Windows.Forms.RadioButton
        Me.RadioButton2 = New System.Windows.Forms.RadioButton
        Me.SuspendLayout()
        '
        'RichTextBox1
        '
        Me.RichTextBox1.Location = New System.Drawing.Point(0, 16)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.Size = New System.Drawing.Size(496, 312)
        Me.RichTextBox1.TabIndex = 0
        Me.RichTextBox1.Text = "RichTextBox1"
        '
        'cmdStart
        '
        Me.cmdStart.Location = New System.Drawing.Point(248, 368)
        Me.cmdStart.Name = "cmdStart"
        Me.cmdStart.Size = New System.Drawing.Size(80, 24)
        Me.cmdStart.TabIndex = 1
        Me.cmdStart.Text = "��ʼ(&S)"
        '
        'cmdExit
        '
        Me.cmdExit.Location = New System.Drawing.Point(376, 368)
        Me.cmdExit.Name = "cmdExit"
        Me.cmdExit.Size = New System.Drawing.Size(80, 24)
        Me.cmdExit.TabIndex = 1
        Me.cmdExit.Text = "�˳�(&E)"
        '
        'RadioButton1
        '
        Me.RadioButton1.Location = New System.Drawing.Point(16, 336)
        Me.RadioButton1.Name = "RadioButton1"
        Me.RadioButton1.Size = New System.Drawing.Size(184, 24)
        Me.RadioButton1.TabIndex = 2
        Me.RadioButton1.Text = "��ͬ����������"
        '
        'RadioButton2
        '
        Me.RadioButton2.Location = New System.Drawing.Point(16, 368)
        Me.RadioButton2.Name = "RadioButton2"
        Me.RadioButton2.Size = New System.Drawing.Size(184, 24)
        Me.RadioButton2.TabIndex = 3
        Me.RadioButton2.Text = "�Ҳ�ͬ��"
        '
        'frmLicense
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(496, 405)
        Me.Controls.Add(Me.RadioButton2)
        Me.Controls.Add(Me.RadioButton1)
        Me.Controls.Add(Me.cmdStart)
        Me.Controls.Add(Me.RichTextBox1)
        Me.Controls.Add(Me.cmdExit)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Name = "frmLicense"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "���Э��"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Public bAgree As Boolean

    Private Sub frmLicense_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        RichTextBox1.LoadFile("License.txt", Windows.Forms.RichTextBoxStreamType.PlainText)
    End Sub
End Class
