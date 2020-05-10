Imports System.Diagnostics

Public Class frmAbout
    Inherits System.Windows.Forms.Form

    Public Declare Unicode Function GetDLLPath Lib "Syntax" (ByRef szPath As String) As Integer

#Region " Windows 窗体设计器生成的代码 "

    Public Sub New()
        MyBase.New()

        '该调用是 Windows 窗体设计器所必需的。
        InitializeComponent()

        '在 InitializeComponent() 调用之后添加任何初始化

    End Sub

    '窗体重写 dispose 以清理组件列表。
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改此过程。
    '不要使用代码编辑器修改它。
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents labTitle As System.Windows.Forms.Label
    Friend WithEvents labAuthor As System.Windows.Forms.Label
    Friend WithEvents labDate As System.Windows.Forms.Label
    Friend WithEvents labDescription As System.Windows.Forms.Label
    Friend WithEvents labCompany As System.Windows.Forms.Label
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents labEMail As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmAbout))
        Me.PictureBox1 = New System.Windows.Forms.PictureBox
        Me.labTitle = New System.Windows.Forms.Label
        Me.labAuthor = New System.Windows.Forms.Label
        Me.labDate = New System.Windows.Forms.Label
        Me.labDescription = New System.Windows.Forms.Label
        Me.labCompany = New System.Windows.Forms.Label
        Me.Button1 = New System.Windows.Forms.Button
        Me.labEMail = New System.Windows.Forms.Label
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
        Me.labDate.Location = New System.Drawing.Point(8, 240)
        Me.labDate.Name = "labDate"
        Me.labDate.Size = New System.Drawing.Size(480, 16)
        Me.labDate.TabIndex = 1
        Me.labDate.Text = "labDate"
        Me.labDate.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'labDescription
        '
        Me.labDescription.Location = New System.Drawing.Point(8, 272)
        Me.labDescription.Name = "labDescription"
        Me.labDescription.Size = New System.Drawing.Size(480, 64)
        Me.labDescription.TabIndex = 1
        Me.labDescription.Text = "labDescription"
        Me.labDescription.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'labCompany
        '
        Me.labCompany.Location = New System.Drawing.Point(8, 208)
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
        Me.Button1.Text = "确定（&O）"
        '
        'labEMail
        '
        Me.labEMail.Location = New System.Drawing.Point(8, 176)
        Me.labEMail.Name = "labEMail"
        Me.labEMail.Size = New System.Drawing.Size(480, 16)
        Me.labEMail.TabIndex = 1
        Me.labEMail.Text = "labEMail"
        Me.labEMail.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
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
        Me.Controls.Add(Me.labEMail)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmAbout"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "关于"
        Me.ResumeLayout(False)

    End Sub

#End Region

    '*******************************************************************************************************
    '过程名：frmAbout_Load
    '描  述：关于对话框初始化
    '参  数：
    '        ByVal sender As System.Object：
    '        ByVal e As System.EventArgs  ：
    '版  本：2005.6.1.0
    '作  者：康  林
    '时  间：2005年7月4日 17:47:23
    '*******************************************************************************************************
    Private Sub frmAbout_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim szFile As String, szPath As String
#If _VBNET_ Then
        szFile = "\VisualStudioNetExtendTools.dll"
#Else
        szFile = "\MicrosoftDevelopmentEnvironmentExtendTools.dll"
#End If
        Me.Text = "关于 - " & Application.ProductName
        GetDLLPath(szPath)
        Dim f As FileVersionInfo = FileVersionInfo.GetVersionInfo(Application.StartupPath & szFile)

        'labTitle.Text = Application.ProductName & " (版本号：" & Application.ProductVersion & ")"
        labTitle.Text = Application.ProductName & " (版本号：" & f.FileVersion & ")"
        labAuthor.Text = "作  者：康  林"
        labEMail.Text = "EMail：kl222@126.com"
        labDate.Text = "时  间：" & FileDateTime(Application.StartupPath & szFile).ToLongDateString
        labCompany.Text = Application.CompanyName
        labDescription.Text = "版权所有（C）2004-" & Year(FileDateTime(Application.StartupPath & szFile)) & " 康林工作室；保留所有权力"
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Me.Close()
    End Sub

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
            GetFilePath = Microsoft.VisualBasic.Strings.Left(szFileName, iPos - 1)
        End If
    End Function

End Class
