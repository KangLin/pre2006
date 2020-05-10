Public Class frmAbout
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
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents labTitle As System.Windows.Forms.Label
    Friend WithEvents labAuthor As System.Windows.Forms.Label
    Friend WithEvents labDate As System.Windows.Forms.Label
    Friend WithEvents labDescription As System.Windows.Forms.Label
    Friend WithEvents labCompany As System.Windows.Forms.Label
    Friend WithEvents Button1 As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmAbout))
        Me.PictureBox1 = New System.Windows.Forms.PictureBox
        Me.labTitle = New System.Windows.Forms.Label
        Me.labAuthor = New System.Windows.Forms.Label
        Me.labDate = New System.Windows.Forms.Label
        Me.labDescription = New System.Windows.Forms.Label
        Me.labCompany = New System.Windows.Forms.Label
        Me.Button1 = New System.Windows.Forms.Button
        Me.SuspendLayout()
        '
        'PictureBox1
        '
        Me.PictureBox1.Image = CType(resources.GetObject("PictureBox1.Image"), System.Drawing.Image)
        Me.PictureBox1.Location = New System.Drawing.Point(232, 32)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(32, 32)
        Me.PictureBox1.TabIndex = 0
        Me.PictureBox1.TabStop = False
        '
        'labTitle
        '
        Me.labTitle.Location = New System.Drawing.Point(8, 112)
        Me.labTitle.Name = "labTitle"
        Me.labTitle.Size = New System.Drawing.Size(480, 16)
        Me.labTitle.TabIndex = 1
        Me.labTitle.Text = "labTitle"
        Me.labTitle.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'labAuthor
        '
        Me.labAuthor.Location = New System.Drawing.Point(8, 144)
        Me.labAuthor.Name = "labAuthor"
        Me.labAuthor.Size = New System.Drawing.Size(480, 16)
        Me.labAuthor.TabIndex = 1
        Me.labAuthor.Text = "labAuthor"
        Me.labAuthor.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'labDate
        '
        Me.labDate.Location = New System.Drawing.Point(8, 208)
        Me.labDate.Name = "labDate"
        Me.labDate.Size = New System.Drawing.Size(480, 16)
        Me.labDate.TabIndex = 1
        Me.labDate.Text = "labDate"
        Me.labDate.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'labDescription
        '
        Me.labDescription.Location = New System.Drawing.Point(8, 240)
        Me.labDescription.Name = "labDescription"
        Me.labDescription.Size = New System.Drawing.Size(480, 64)
        Me.labDescription.TabIndex = 1
        Me.labDescription.Text = "labDescription"
        Me.labDescription.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'labCompany
        '
        Me.labCompany.Location = New System.Drawing.Point(8, 176)
        Me.labCompany.Name = "labCompany"
        Me.labCompany.Size = New System.Drawing.Size(480, 16)
        Me.labCompany.TabIndex = 1
        Me.labCompany.Text = "labCompany"
        Me.labCompany.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(216, 368)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(80, 24)
        Me.Button1.TabIndex = 2
        Me.Button1.Text = "ȷ����&O��"
        '
        'frmAbout
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(494, 403)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.labTitle)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.labAuthor)
        Me.Controls.Add(Me.labDate)
        Me.Controls.Add(Me.labDescription)
        Me.Controls.Add(Me.labCompany)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmAbout"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "����"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub frmAbout_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.Text = "���� - " & Application.ProductName
        labTitle.Text = Application.ProductName & " (�汾�ţ�" & Application.ProductVersion & ")"
        labAuthor.Text = "��  �ߣ���  ��"
        labDate.Text = "ʱ  �䣺2005��6��17��"
        labCompany.Text = Application.CompanyName
        labDescription.Text = "��Ȩ���У�C��2005 ���ֹ����ң���������Ȩ��"
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Me.Close()
    End Sub

    Private Sub labTitle_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles labTitle.Click

    End Sub
End Class
