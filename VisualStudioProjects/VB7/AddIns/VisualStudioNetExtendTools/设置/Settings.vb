'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：Settings.vb
'描  述：设置函数注释功能中的参数的窗口
'版  本：2005.3.*
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005-5-16
'时  间：2005-5-16 17:35:32
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'
'Copyright (C) 2005 KangLin Studio;All rights reserved.
'FileName   ：Settings.vb
'Description：
'Version    ：2005.3.*
'Author     ：KangLin
'E_Mail     ：kl222@126.com
'Date       ：2005-5-16
'Time       ：2005-5-16 17:35:32
'Compiler   ：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************
Option Strict Off
Option Explicit On 
Imports Microsoft.Win32

Public Class frmSettings
    Inherits System.Windows.Forms.Form

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
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents txtAuthor As System.Windows.Forms.TextBox
    Friend WithEvents txtEAuthor As System.Windows.Forms.TextBox
    Friend WithEvents txtCop As System.Windows.Forms.TextBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents txtECop As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents txtSubName As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents txtFunctionName As System.Windows.Forms.TextBox
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents txtDescription As System.Windows.Forms.TextBox
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents txtPara As System.Windows.Forms.TextBox
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents txtVersion As System.Windows.Forms.TextBox
    Friend WithEvents txtReturnVal As System.Windows.Forms.TextBox
    Friend WithEvents txtDate As System.Windows.Forms.TextBox
    Friend WithEvents txtFAuthor As System.Windows.Forms.TextBox
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox4 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox5 As System.Windows.Forms.GroupBox
    Friend WithEvents ckbAuthor As System.Windows.Forms.CheckBox
    Friend WithEvents ckbVersion As System.Windows.Forms.CheckBox
    Friend WithEvents ckbDate As System.Windows.Forms.CheckBox
    Friend WithEvents ckbEnglish As System.Windows.Forms.CheckBox
    Friend WithEvents ckbChinese As System.Windows.Forms.CheckBox
    Friend WithEvents butOK As System.Windows.Forms.Button
    Friend WithEvents butCancel As System.Windows.Forms.Button
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents txtEmail As System.Windows.Forms.TextBox
    Friend WithEvents Label12 As System.Windows.Forms.Label
    Friend WithEvents txtClassName As System.Windows.Forms.TextBox
    Friend WithEvents ckbShow As System.Windows.Forms.CheckBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmSettings))
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.ckbChinese = New System.Windows.Forms.CheckBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.txtCop = New System.Windows.Forms.TextBox
        Me.txtAuthor = New System.Windows.Forms.TextBox
        Me.Label1 = New System.Windows.Forms.Label
        Me.GroupBox2 = New System.Windows.Forms.GroupBox
        Me.txtECop = New System.Windows.Forms.TextBox
        Me.txtEAuthor = New System.Windows.Forms.TextBox
        Me.ckbEnglish = New System.Windows.Forms.CheckBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.txtSubName = New System.Windows.Forms.TextBox
        Me.Label5 = New System.Windows.Forms.Label
        Me.txtFunctionName = New System.Windows.Forms.TextBox
        Me.Label6 = New System.Windows.Forms.Label
        Me.txtDescription = New System.Windows.Forms.TextBox
        Me.Label7 = New System.Windows.Forms.Label
        Me.txtPara = New System.Windows.Forms.TextBox
        Me.Label8 = New System.Windows.Forms.Label
        Me.Label9 = New System.Windows.Forms.Label
        Me.txtVersion = New System.Windows.Forms.TextBox
        Me.txtReturnVal = New System.Windows.Forms.TextBox
        Me.txtDate = New System.Windows.Forms.TextBox
        Me.txtFAuthor = New System.Windows.Forms.TextBox
        Me.Label10 = New System.Windows.Forms.Label
        Me.Label11 = New System.Windows.Forms.Label
        Me.GroupBox3 = New System.Windows.Forms.GroupBox
        Me.Label12 = New System.Windows.Forms.Label
        Me.GroupBox4 = New System.Windows.Forms.GroupBox
        Me.txtEmail = New System.Windows.Forms.TextBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.GroupBox5 = New System.Windows.Forms.GroupBox
        Me.ckbAuthor = New System.Windows.Forms.CheckBox
        Me.ckbVersion = New System.Windows.Forms.CheckBox
        Me.ckbDate = New System.Windows.Forms.CheckBox
        Me.butOK = New System.Windows.Forms.Button
        Me.butCancel = New System.Windows.Forms.Button
        Me.ckbShow = New System.Windows.Forms.CheckBox
        Me.txtClassName = New System.Windows.Forms.TextBox
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.GroupBox4.SuspendLayout()
        Me.GroupBox5.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.ckbChinese)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.txtCop)
        Me.GroupBox1.Controls.Add(Me.txtAuthor)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Location = New System.Drawing.Point(24, 16)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(224, 80)
        Me.GroupBox1.TabIndex = 0
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "中文"
        '
        'ckbChinese
        '
        Me.ckbChinese.Location = New System.Drawing.Point(192, 32)
        Me.ckbChinese.Name = "ckbChinese"
        Me.ckbChinese.Size = New System.Drawing.Size(16, 16)
        Me.ckbChinese.TabIndex = 2
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 48)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(48, 16)
        Me.Label3.TabIndex = 3
        Me.Label3.Text = "公司："
        '
        'txtCop
        '
        Me.txtCop.Location = New System.Drawing.Point(64, 48)
        Me.txtCop.Name = "txtCop"
        Me.txtCop.Size = New System.Drawing.Size(112, 21)
        Me.txtCop.TabIndex = 5
        Me.txtCop.Text = "txtCop"
        '
        'txtAuthor
        '
        Me.txtAuthor.Location = New System.Drawing.Point(64, 16)
        Me.txtAuthor.Name = "txtAuthor"
        Me.txtAuthor.Size = New System.Drawing.Size(112, 21)
        Me.txtAuthor.TabIndex = 1
        Me.txtAuthor.Text = "txtAuthor"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 16)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "作者："
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.txtECop)
        Me.GroupBox2.Controls.Add(Me.txtEAuthor)
        Me.GroupBox2.Controls.Add(Me.ckbEnglish)
        Me.GroupBox2.Location = New System.Drawing.Point(304, 16)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(144, 80)
        Me.GroupBox2.TabIndex = 0
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "英文"
        '
        'txtECop
        '
        Me.txtECop.Location = New System.Drawing.Point(8, 48)
        Me.txtECop.Name = "txtECop"
        Me.txtECop.Size = New System.Drawing.Size(104, 21)
        Me.txtECop.TabIndex = 6
        Me.txtECop.Text = "txtECop"
        '
        'txtEAuthor
        '
        Me.txtEAuthor.Location = New System.Drawing.Point(8, 16)
        Me.txtEAuthor.Name = "txtEAuthor"
        Me.txtEAuthor.Size = New System.Drawing.Size(104, 21)
        Me.txtEAuthor.TabIndex = 3
        Me.txtEAuthor.Text = "txtEAuthor"
        '
        'ckbEnglish
        '
        Me.ckbEnglish.Location = New System.Drawing.Point(120, 32)
        Me.ckbEnglish.Name = "ckbEnglish"
        Me.ckbEnglish.Size = New System.Drawing.Size(16, 16)
        Me.ckbEnglish.TabIndex = 4
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(24, 24)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(64, 16)
        Me.Label4.TabIndex = 3
        Me.Label4.Text = "过程名："
        '
        'txtSubName
        '
        Me.txtSubName.Location = New System.Drawing.Point(103, 24)
        Me.txtSubName.Name = "txtSubName"
        Me.txtSubName.Size = New System.Drawing.Size(103, 21)
        Me.txtSubName.TabIndex = 8
        Me.txtSubName.Text = "txtSubName"
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(264, 24)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(56, 16)
        Me.Label5.TabIndex = 5
        Me.Label5.Text = "函数名："
        '
        'txtFunctionName
        '
        Me.txtFunctionName.Location = New System.Drawing.Point(344, 24)
        Me.txtFunctionName.Name = "txtFunctionName"
        Me.txtFunctionName.Size = New System.Drawing.Size(104, 21)
        Me.txtFunctionName.TabIndex = 9
        Me.txtFunctionName.Text = "txtFunctionName"
        '
        'Label6
        '
        Me.Label6.Location = New System.Drawing.Point(22, 88)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(64, 16)
        Me.Label6.TabIndex = 7
        Me.Label6.Text = "描  述："
        '
        'txtDescription
        '
        Me.txtDescription.Location = New System.Drawing.Point(102, 88)
        Me.txtDescription.Name = "txtDescription"
        Me.txtDescription.Size = New System.Drawing.Size(104, 21)
        Me.txtDescription.TabIndex = 10
        Me.txtDescription.Text = "txtDescription"
        '
        'Label7
        '
        Me.Label7.Location = New System.Drawing.Point(264, 56)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(56, 16)
        Me.Label7.TabIndex = 8
        Me.Label7.Text = "参  数："
        '
        'txtPara
        '
        Me.txtPara.Location = New System.Drawing.Point(344, 56)
        Me.txtPara.Name = "txtPara"
        Me.txtPara.Size = New System.Drawing.Size(104, 21)
        Me.txtPara.TabIndex = 11
        Me.txtPara.Text = "txtPara"
        '
        'Label8
        '
        Me.Label8.Location = New System.Drawing.Point(22, 120)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(64, 16)
        Me.Label8.TabIndex = 7
        Me.Label8.Text = "返回值："
        '
        'Label9
        '
        Me.Label9.Location = New System.Drawing.Point(264, 88)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(56, 16)
        Me.Label9.TabIndex = 8
        Me.Label9.Text = "版  本："
        '
        'txtVersion
        '
        Me.txtVersion.Location = New System.Drawing.Point(344, 88)
        Me.txtVersion.Name = "txtVersion"
        Me.txtVersion.Size = New System.Drawing.Size(104, 21)
        Me.txtVersion.TabIndex = 13
        Me.txtVersion.Text = "txtVersion"
        '
        'txtReturnVal
        '
        Me.txtReturnVal.Location = New System.Drawing.Point(102, 120)
        Me.txtReturnVal.Name = "txtReturnVal"
        Me.txtReturnVal.Size = New System.Drawing.Size(104, 21)
        Me.txtReturnVal.TabIndex = 12
        Me.txtReturnVal.Text = "txtReturnVal"
        '
        'txtDate
        '
        Me.txtDate.Location = New System.Drawing.Point(344, 120)
        Me.txtDate.Name = "txtDate"
        Me.txtDate.Size = New System.Drawing.Size(104, 21)
        Me.txtDate.TabIndex = 15
        Me.txtDate.Text = "txtDate"
        '
        'txtFAuthor
        '
        Me.txtFAuthor.Location = New System.Drawing.Point(102, 152)
        Me.txtFAuthor.Name = "txtFAuthor"
        Me.txtFAuthor.Size = New System.Drawing.Size(104, 21)
        Me.txtFAuthor.TabIndex = 14
        Me.txtFAuthor.Text = "txtFAuthor"
        '
        'Label10
        '
        Me.Label10.Location = New System.Drawing.Point(22, 152)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(64, 16)
        Me.Label10.TabIndex = 7
        Me.Label10.Text = "作  者："
        '
        'Label11
        '
        Me.Label11.Location = New System.Drawing.Point(264, 120)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(56, 16)
        Me.Label11.TabIndex = 8
        Me.Label11.Text = "时  间："
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.txtClassName)
        Me.GroupBox3.Controls.Add(Me.Label12)
        Me.GroupBox3.Controls.Add(Me.txtReturnVal)
        Me.GroupBox3.Controls.Add(Me.txtDate)
        Me.GroupBox3.Controls.Add(Me.Label11)
        Me.GroupBox3.Controls.Add(Me.txtFAuthor)
        Me.GroupBox3.Controls.Add(Me.Label4)
        Me.GroupBox3.Controls.Add(Me.txtSubName)
        Me.GroupBox3.Controls.Add(Me.Label10)
        Me.GroupBox3.Controls.Add(Me.Label5)
        Me.GroupBox3.Controls.Add(Me.txtFunctionName)
        Me.GroupBox3.Controls.Add(Me.Label6)
        Me.GroupBox3.Controls.Add(Me.txtDescription)
        Me.GroupBox3.Controls.Add(Me.Label7)
        Me.GroupBox3.Controls.Add(Me.txtPara)
        Me.GroupBox3.Controls.Add(Me.Label8)
        Me.GroupBox3.Controls.Add(Me.Label9)
        Me.GroupBox3.Controls.Add(Me.txtVersion)
        Me.GroupBox3.Location = New System.Drawing.Point(8, 152)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(480, 181)
        Me.GroupBox3.TabIndex = 9
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "用于函数注释中的变量。用所用语言翻译。"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(22, 56)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(53, 12)
        Me.Label12.TabIndex = 16
        Me.Label12.Text = "类  名："
        '
        'GroupBox4
        '
        Me.GroupBox4.Controls.Add(Me.txtEmail)
        Me.GroupBox4.Controls.Add(Me.Label2)
        Me.GroupBox4.Controls.Add(Me.GroupBox1)
        Me.GroupBox4.Controls.Add(Me.GroupBox2)
        Me.GroupBox4.Location = New System.Drawing.Point(8, 8)
        Me.GroupBox4.Name = "GroupBox4"
        Me.GroupBox4.Size = New System.Drawing.Size(480, 136)
        Me.GroupBox4.TabIndex = 0
        Me.GroupBox4.TabStop = False
        Me.GroupBox4.Text = "用于文件注释中的变量。"
        '
        'txtEmail
        '
        Me.txtEmail.Location = New System.Drawing.Point(88, 104)
        Me.txtEmail.Name = "txtEmail"
        Me.txtEmail.Size = New System.Drawing.Size(360, 21)
        Me.txtEmail.TabIndex = 7
        Me.txtEmail.Text = "txtEmail"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(24, 112)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(72, 16)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "电子信箱："
        '
        'GroupBox5
        '
        Me.GroupBox5.Controls.Add(Me.ckbAuthor)
        Me.GroupBox5.Controls.Add(Me.ckbVersion)
        Me.GroupBox5.Controls.Add(Me.ckbDate)
        Me.GroupBox5.Location = New System.Drawing.Point(8, 333)
        Me.GroupBox5.Name = "GroupBox5"
        Me.GroupBox5.Size = New System.Drawing.Size(480, 48)
        Me.GroupBox5.TabIndex = 11
        Me.GroupBox5.TabStop = False
        '
        'ckbAuthor
        '
        Me.ckbAuthor.Location = New System.Drawing.Point(168, 16)
        Me.ckbAuthor.Name = "ckbAuthor"
        Me.ckbAuthor.Size = New System.Drawing.Size(152, 24)
        Me.ckbAuthor.TabIndex = 17
        Me.ckbAuthor.Text = "函数注释中加入作者。"
        '
        'ckbVersion
        '
        Me.ckbVersion.Location = New System.Drawing.Point(320, 16)
        Me.ckbVersion.Name = "ckbVersion"
        Me.ckbVersion.Size = New System.Drawing.Size(152, 24)
        Me.ckbVersion.TabIndex = 18
        Me.ckbVersion.Text = "函数注释中加入版本。"
        '
        'ckbDate
        '
        Me.ckbDate.Location = New System.Drawing.Point(16, 14)
        Me.ckbDate.Name = "ckbDate"
        Me.ckbDate.Size = New System.Drawing.Size(152, 32)
        Me.ckbDate.TabIndex = 16
        Me.ckbDate.Text = "函数注释中加入日期。"
        '
        'butOK
        '
        Me.butOK.Location = New System.Drawing.Point(256, 389)
        Me.butOK.Name = "butOK"
        Me.butOK.Size = New System.Drawing.Size(80, 24)
        Me.butOK.TabIndex = 20
        Me.butOK.Text = "确定(&O)"
        '
        'butCancel
        '
        Me.butCancel.Location = New System.Drawing.Point(376, 389)
        Me.butCancel.Name = "butCancel"
        Me.butCancel.Size = New System.Drawing.Size(80, 24)
        Me.butCancel.TabIndex = 21
        Me.butCancel.Text = "取消(&C)"
        '
        'ckbShow
        '
        Me.ckbShow.Checked = True
        Me.ckbShow.CheckState = System.Windows.Forms.CheckState.Checked
        Me.ckbShow.Location = New System.Drawing.Point(24, 389)
        Me.ckbShow.Name = "ckbShow"
        Me.ckbShow.Size = New System.Drawing.Size(184, 24)
        Me.ckbShow.TabIndex = 19
        Me.ckbShow.Text = "总是显示本窗口"
        '
        'txtClassName
        '
        Me.txtClassName.Location = New System.Drawing.Point(102, 55)
        Me.txtClassName.Name = "txtClassName"
        Me.txtClassName.Size = New System.Drawing.Size(104, 21)
        Me.txtClassName.TabIndex = 17
        Me.txtClassName.Text = "txtClassName"
        '
        'frmSettings
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(496, 428)
        Me.Controls.Add(Me.ckbShow)
        Me.Controls.Add(Me.butOK)
        Me.Controls.Add(Me.GroupBox5)
        Me.Controls.Add(Me.GroupBox4)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.butCancel)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "frmSettings"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "设置"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox3.PerformLayout()
        Me.GroupBox4.ResumeLayout(False)
        Me.GroupBox4.PerformLayout()
        Me.GroupBox5.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Public m_objComment As Comment
    Dim m_szFile As String
    Dim m_szPath As String
    Dim m_szFullName As String
    Dim m_Key As RegistryKey
    Dim m_szKeyItem As String

    Private Sub Settings_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load
        m_szKeyItem = "SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect\"
        Try
            m_Key = Registry.LocalMachine.OpenSubKey("SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect", True)
            If Not m_Key Is Nothing Then
                ckbShow.Checked = m_Key.GetValue("Show", True)
                m_Key.Close()
            End If

            m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "文件注释", True)
            If m_Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(m_szKeyItem & "文件注释")
                m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "文件注释", True)
            End If
            txtAuthor.Text = m_Key.GetValue("作者", m_objComment.g_szAuthor)
            txtCop.Text = m_Key.GetValue("公司", m_objComment.g_szCorporation)
            txtEAuthor.Text = m_Key.GetValue("Author", m_objComment.g_szEAuthor)
            txtECop.Text = m_Key.GetValue("Corporation", m_objComment.g_szECorporation)
            txtEmail.Text = m_Key.GetValue("EMail", m_objComment.g_szEmail)
            ckbChinese.Checked = m_Key.GetValue("中文", m_objComment.g_iLanguage And 1)
            ckbEnglish.Checked = m_Key.GetValue("英文", m_objComment.g_iLanguage And 2)
            m_Key.Close()

            m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "函数注释", True)
            If m_Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(m_szKeyItem & "函数注释")
                m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "函数注释", True)
            End If
            txtSubName.Text = m_Key.GetValue("过程名", m_objComment.m_szSubName)
            txtFunctionName.Text = m_Key.GetValue("函数名", m_objComment.m_szFunctionName)
            txtClassName.Text = m_Key.GetValue("类名", m_objComment.m_szClassName)
            txtDescription.Text = m_Key.GetValue("描述", m_objComment.m_szDescription)
            txtPara.Text = m_Key.GetValue("参数", m_objComment.m_szPara)
            txtReturnVal.Text = m_Key.GetValue("返回值", m_objComment.m_szReturnVal)
            txtVersion.Text = m_Key.GetValue("版本", m_objComment.m_szVersion)
            txtFAuthor.Text = m_Key.GetValue("作者", m_objComment.m_szAuthor)
            txtDate.Text = m_Key.GetValue("日期", m_objComment.m_szDate)
            ckbVersion.Checked = m_Key.GetValue("加入版本", m_objComment.g_bFunctionVersion)
            ckbAuthor.Checked = m_Key.GetValue("加入作者", m_objComment.g_bFunctionAuthor)
            ckbDate.Checked = m_Key.GetValue("加入日期", m_objComment.g_bFunctionDate)
            m_Key.Close()
        Catch ex As Exception
            Debug.WriteLine(ex.Message)
        End Try

    End Sub

    Private Sub butOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butOK.Click
        Try
            m_Key = Registry.LocalMachine.OpenSubKey("SoftWare\Microsoft\VisualStudio\7.1\AddIns\VisualStudioNetExtendTools.Connect", True)
            If Not m_Key Is Nothing Then
                m_Key.SetValue("Show", ckbShow.Checked)
                m_Key.Close()
            End If

            m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "文件注释", True)
            If m_Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(m_szKeyItem & "文件注释")
                m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "文件注释", True)
            End If
            m_objComment.g_szAuthor = txtAuthor.Text
            m_Key.SetValue("作者", m_objComment.g_szAuthor)
            m_objComment.g_szCorporation = txtCop.Text
            m_Key.SetValue("公司", m_objComment.g_szCorporation)
            m_objComment.g_szEAuthor = txtEAuthor.Text
            m_Key.SetValue("Author", m_objComment.g_szEAuthor)
            m_objComment.g_szECorporation = txtECop.Text
            m_Key.SetValue("Corporation", m_objComment.g_szECorporation)
            m_objComment.g_szEmail = txtEmail.Text
            m_Key.SetValue("EMail", m_objComment.g_szEmail)
            If ckbChinese.Checked Then
                m_objComment.g_iLanguage = 1
            Else
                m_objComment.g_iLanguage = 0
            End If
            m_Key.SetValue("中文", m_objComment.g_iLanguage)
            If ckbEnglish.Checked Then
                m_objComment.g_iLanguage = m_objComment.g_iLanguage + 2
                m_Key.SetValue("英文", 2)
            Else
                m_Key.SetValue("英文", 0)
            End If

            m_Key.Close()

            m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "函数注释", True)
            If m_Key Is Nothing Then
                Registry.LocalMachine.CreateSubKey(m_szKeyItem & "函数注释")
                m_Key = Registry.LocalMachine.OpenSubKey(m_szKeyItem & "函数注释", True)
            End If
            m_objComment.m_szSubName = txtSubName.Text
            m_Key.SetValue("过程名", m_objComment.m_szSubName)
            m_objComment.m_szFunctionName = txtFunctionName.Text
            m_Key.SetValue("函数名", m_objComment.m_szFunctionName)
            m_objComment.m_szClassName = txtClassName.Text
            m_Key.SetValue("类名", m_objComment.m_szClassName)
            m_objComment.m_szDescription = txtDescription.Text
            m_Key.SetValue("描述", m_objComment.m_szDescription)
            m_objComment.m_szPara = txtPara.Text
            m_Key.SetValue("参数", m_objComment.m_szPara)
            m_objComment.m_szReturnVal = txtReturnVal.Text
            m_Key.SetValue("返回值", m_objComment.m_szReturnVal)
            m_objComment.m_szVersion = txtVersion.Text
            m_Key.SetValue("版本", m_objComment.m_szVersion)
            m_objComment.m_szAuthor = txtFAuthor.Text
            m_Key.SetValue("作者", m_objComment.m_szAuthor)
            m_objComment.m_szDate = txtDate.Text
            m_Key.SetValue("日期", m_objComment.m_szDate)
            m_objComment.g_bFunctionVersion = ckbVersion.Checked
            m_Key.SetValue("加入版本", m_objComment.g_bFunctionVersion)
            m_objComment.g_bFunctionAuthor = ckbAuthor.Checked
            m_Key.SetValue("加入作者", m_objComment.g_bFunctionAuthor)
            m_objComment.g_bFunctionDate = ckbDate.Checked
            m_Key.SetValue("加入日期", m_objComment.g_bFunctionDate)
            m_Key.Close()
        Catch ex As Exception
            Debug.WriteLine(ex.Message)
        End Try

        Me.Close()
    End Sub

    Private Sub butCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butCancel.Click
        Me.Close()
    End Sub

    Private Sub GroupBox4_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles GroupBox4.Enter

    End Sub

  
End Class
