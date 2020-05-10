Option Strict Off
Option Explicit On 

Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If
Imports System.ComponentModel
Imports Microsoft.Win32

Public Class frmOtherSettings
    Inherits System.Windows.Forms.Form

    Public m_objComment As Comment
    Friend WithEvents chkDoxgenComment As System.Windows.Forms.CheckBox
    Public m_objEvent As Events

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
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents chbEndIf As System.Windows.Forms.CheckBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents txtEndif As System.Windows.Forms.TextBox
    Friend WithEvents butOK As System.Windows.Forms.Button
    Friend WithEvents butCancel As System.Windows.Forms.Button
    Friend WithEvents chbAddEndIf As System.Windows.Forms.CheckBox
    Friend WithEvents labEndif As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmOtherSettings))
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.labEndif = New System.Windows.Forms.Label
        Me.txtEndif = New System.Windows.Forms.TextBox
        Me.Label1 = New System.Windows.Forms.Label
        Me.chbEndIf = New System.Windows.Forms.CheckBox
        Me.chbAddEndIf = New System.Windows.Forms.CheckBox
        Me.butOK = New System.Windows.Forms.Button
        Me.butCancel = New System.Windows.Forms.Button
        Me.chkDoxgenComment = New System.Windows.Forms.CheckBox
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.labEndif)
        Me.GroupBox1.Controls.Add(Me.txtEndif)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.chbEndIf)
        Me.GroupBox1.Controls.Add(Me.chbAddEndIf)
        Me.GroupBox1.Location = New System.Drawing.Point(16, 24)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(464, 88)
        Me.GroupBox1.TabIndex = 0
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "结束块注释："
        '
        'labEndif
        '
        Me.labEndif.Location = New System.Drawing.Point(264, 56)
        Me.labEndif.Name = "labEndif"
        Me.labEndif.Size = New System.Drawing.Size(176, 16)
        Me.labEndif.TabIndex = 3
        Me.labEndif.Text = "Label2"
        '
        'txtEndif
        '
        Me.txtEndif.Location = New System.Drawing.Point(96, 56)
        Me.txtEndif.Name = "txtEndif"
        Me.txtEndif.Size = New System.Drawing.Size(112, 21)
        Me.txtEndif.TabIndex = 2
        Me.txtEndif.Text = "txtEndif"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 56)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(80, 16)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "结束块标识："
        '
        'chbEndIf
        '
        Me.chbEndIf.Location = New System.Drawing.Point(264, 24)
        Me.chbEndIf.Name = "chbEndIf"
        Me.chbEndIf.Size = New System.Drawing.Size(184, 24)
        Me.chbEndIf.TabIndex = 0
        Me.chbEndIf.Text = "任何情况下自动修改结束注释"
        '
        'chbAddEndIf
        '
        Me.chbAddEndIf.Location = New System.Drawing.Point(32, 24)
        Me.chbAddEndIf.Name = "chbAddEndIf"
        Me.chbAddEndIf.Size = New System.Drawing.Size(184, 24)
        Me.chbAddEndIf.TabIndex = 0
        Me.chbAddEndIf.Text = "任何情况下自动增加结束注释"
        '
        'butOK
        '
        Me.butOK.Location = New System.Drawing.Point(152, 368)
        Me.butOK.Name = "butOK"
        Me.butOK.Size = New System.Drawing.Size(80, 24)
        Me.butOK.TabIndex = 1
        Me.butOK.Text = "确定"
        '
        'butCancel
        '
        Me.butCancel.Location = New System.Drawing.Point(280, 368)
        Me.butCancel.Name = "butCancel"
        Me.butCancel.Size = New System.Drawing.Size(80, 24)
        Me.butCancel.TabIndex = 1
        Me.butCancel.Text = "取消"
        '
        'chkDoxgenComment
        '
        Me.chkDoxgenComment.AutoSize = True
        Me.chkDoxgenComment.Checked = True
        Me.chkDoxgenComment.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkDoxgenComment.Location = New System.Drawing.Point(48, 128)
        Me.chkDoxgenComment.Name = "chkDoxgenComment"
        Me.chkDoxgenComment.Size = New System.Drawing.Size(216, 16)
        Me.chkDoxgenComment.TabIndex = 2
        Me.chkDoxgenComment.Text = "采用doxgen注释，自动生成帮助文档"
        Me.chkDoxgenComment.UseVisualStyleBackColor = True
        '
        'frmOtherSettings
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(496, 405)
        Me.Controls.Add(Me.chkDoxgenComment)
        Me.Controls.Add(Me.butOK)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.butCancel)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "frmOtherSettings"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "其它设置"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

#End Region

    Private Sub butCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butCancel.Click
        Me.Close()
    End Sub

    Private Sub butOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butOK.Click
        Dim m_Key As RegistryKey, szKey As String, szSubKey As String
        szKey = "SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\"
        Try
            szSubKey = szKey + "结束块注释"
            m_Key = Registry.LocalMachine.OpenSubKey(szSubKey, True)
            If m_Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(szSubKey)
            End If
            m_Key.SetValue("修改时任何情况下自动修改结束注释", chbEndIf.Checked)
            m_objEvent.m_AutoFormatCode.m_bEndIf = chbEndIf.Checked
            m_Key.SetValue("格式化时自动增加结束块注释", chbAddEndIf.Checked)
            m_objEvent.m_AutoFormatCode.m_bAddEndIf = chbAddEndIf.Checked
            m_Key.SetValue("结束注释块字符", txtEndif.Text)
            m_objEvent.m_AutoFormatCode.m_szEndIf = txtEndif.Text
            m_Key.Close()

            szSubKey = szKey + "VC"
            m_Key = Registry.LocalMachine.OpenSubKey(szSubKey, True)
            If m_Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(szSubKey)
            End If
            m_Key.SetValue("DoxgenComment", chkDoxgenComment.Checked)
            m_objComment.g_bDoxygen = chkDoxgenComment.Checked
            m_Key.Close()
        Catch ex As Exception
            Debug.WriteLine(ex.Message)
        End Try
        Me.Close()
    End Sub

    Private Sub frmOtherSettings_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        txtEndif.Text = m_objEvent.m_AutoFormatCode.m_szEndIf
        chbEndIf.Checked = m_objEvent.m_AutoFormatCode.m_bEndIf
        chbAddEndIf.Checked = m_objEvent.m_AutoFormatCode.m_bAddEndIf
        chkDoxgenComment.Checked = m_objComment.g_bDoxygen
    End Sub

    Private Sub txtEndif_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtEndif.TextChanged
        labEndif.Text = "// " & txtEndif.Text & " if ......"
    End Sub
End Class
