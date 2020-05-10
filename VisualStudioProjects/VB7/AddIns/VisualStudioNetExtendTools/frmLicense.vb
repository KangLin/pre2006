'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：frmLicense.vb
'描  述：显示协议窗口
'版  本：2005.3.*
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005-5-16
'时  间：2005-5-16 17:36:17
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'
'Copyright (C) 2005 KangLin Studio;All rights reserved.
'FileName   ：frmLicense.vb
'Description：
'Version    ：2005.3.*
'Author     ：KangLin
'E_Mail     ：kl222@126.com
'Date       ：2005-5-16
'Time       ：2005-5-16 17:36:17
'Compiler   ：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************
Public Class frmLicense
    Inherits System.Windows.Forms.Form

#Region " Windows 窗体设计器生成的代码 "

    Public Sub New()
        MyBase.New()

        '该调用是 Windows 窗体设计器所必需的。
        InitializeComponent()

        '在 InitializeComponent() 调用之后添加任何初始化
        bAgree = False

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
        Me.cmdStart.Text = "开始(&S)"
        '
        'cmdExit
        '
        Me.cmdExit.Location = New System.Drawing.Point(376, 368)
        Me.cmdExit.Name = "cmdExit"
        Me.cmdExit.Size = New System.Drawing.Size(80, 24)
        Me.cmdExit.TabIndex = 1
        Me.cmdExit.Text = "退出(&E)"
        '
        'RadioButton1
        '
        Me.RadioButton1.Location = New System.Drawing.Point(16, 336)
        Me.RadioButton1.Name = "RadioButton1"
        Me.RadioButton1.Size = New System.Drawing.Size(184, 24)
        Me.RadioButton1.TabIndex = 2
        Me.RadioButton1.Text = "我同意上述条款"
        '
        'RadioButton2
        '
        Me.RadioButton2.Location = New System.Drawing.Point(16, 368)
        Me.RadioButton2.Name = "RadioButton2"
        Me.RadioButton2.Size = New System.Drawing.Size(184, 24)
        Me.RadioButton2.TabIndex = 3
        Me.RadioButton2.Text = "我不同意"
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
        Me.Text = "许可协议"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Public bAgree As Boolean

    Private Sub frmLicense_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        RichTextBox1.LoadFile("License.txt", Windows.Forms.RichTextBoxStreamType.PlainText)
    End Sub
End Class
