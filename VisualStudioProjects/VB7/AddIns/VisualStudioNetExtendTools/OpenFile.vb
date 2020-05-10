'*******************************************************************************************************
'文件名：OpenFile.vb
'功  能：打开文件对话框
'版  本：2005.3.*
'作  者：康  林
'        版权所有  保留所有权利
'E_Mail：kl222@126.com
'日  期：2005-5-14
'时  间：2005-5-14 21:27:02
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'
'FileName：OpenFile.vb
'Function：Open file Dialog
'Author  ：KangLin
'          Copyright 2005 KangLin
'E_Mail  ：kl222@126.com
'Date    ：2005-5-14
'Time    ：2005-5-14 21:27:02
'Compiler：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************

Public Class frmOpenPath
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
        Me.Label1.Text = "文件："
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
        Me.butBrowe.Text = "浏览（&B）"
        '
        'butOK
        '
        Me.butOK.Location = New System.Drawing.Point(168, 80)
        Me.butOK.Name = "butOK"
        Me.butOK.Size = New System.Drawing.Size(80, 24)
        Me.butOK.TabIndex = 3
        Me.butOK.Text = "确定(&O)"
        '
        'butCacenl
        '
        Me.butCacenl.Location = New System.Drawing.Point(296, 80)
        Me.butCacenl.Name = "butCacenl"
        Me.butCacenl.Size = New System.Drawing.Size(80, 24)
        Me.butCacenl.TabIndex = 3
        Me.butCacenl.Text = "取消(&C)"
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
        Me.Text = "打开文件"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Public szFilePath As String

    Private Sub butBrowe_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butBrowe.Click
        With dlgOpen
            .Filter = "头文件(*.h)|*.h|所有文件(*.*)|*.*"
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
