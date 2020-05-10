Public Class Form1
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
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents txt As System.Windows.Forms.TextBox
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Button4 As System.Windows.Forms.Button
    Friend WithEvents Button5 As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.txt = New System.Windows.Forms.TextBox
        Me.Button1 = New System.Windows.Forms.Button
        Me.Button2 = New System.Windows.Forms.Button
        Me.Button3 = New System.Windows.Forms.Button
        Me.Button4 = New System.Windows.Forms.Button
        Me.Button5 = New System.Windows.Forms.Button
        Me.SuspendLayout()
        '
        'txt
        '
        Me.txt.Location = New System.Drawing.Point(64, 80)
        Me.txt.Name = "txt"
        Me.txt.Size = New System.Drawing.Size(272, 21)
        Me.txt.TabIndex = 0
        Me.txt.Text = "TextBox1"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(80, 144)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(72, 24)
        Me.Button1.TabIndex = 1
        Me.Button1.Text = "引用传递"
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(200, 144)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(72, 24)
        Me.Button2.TabIndex = 1
        Me.Button2.Text = "值传递"
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(72, 192)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(72, 24)
        Me.Button3.TabIndex = 1
        Me.Button3.Text = "传入付出"
        '
        'Button4
        '
        Me.Button4.Location = New System.Drawing.Point(208, 200)
        Me.Button4.Name = "Button4"
        Me.Button4.Size = New System.Drawing.Size(80, 24)
        Me.Button4.TabIndex = 2
        Me.Button4.Text = "BSYR"
        '
        'Button5
        '
        Me.Button5.Location = New System.Drawing.Point(208, 256)
        Me.Button5.Name = "Button5"
        Me.Button5.Size = New System.Drawing.Size(72, 24)
        Me.Button5.TabIndex = 3
        Me.Button5.Text = "L"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(376, 358)
        Me.Controls.Add(Me.Button5)
        Me.Controls.Add(Me.Button4)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.txt)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button3)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Declare Unicode Sub Shows Lib "StringDLL" (ByRef szIn As String, ByRef szOut As String)
    Declare Unicode Sub ShowIn Lib "StringDLL" (ByVal szIn As String, ByRef szOut As String)
    Declare Unicode Sub ShowInOut Lib "StringDLL" (ByRef szIn As String, ByRef szOut As String)
    Declare Unicode Sub ShowBSTR Lib "StringDLL" (ByVal szIn As String, ByRef szOut As String)
    Declare Unicode Sub ShowL Lib "StringDLL" (ByVal szIn As String)

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim szIn, szOut As String
        szIn = txt.Text
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
        Shows(szIn, szOut)
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim szIn, szOut As String
        szIn = txt.Text
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
        ShowIn(szIn, szOut)
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim szIn, szOut As String
        szIn = txt.Text
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
        ShowInOut(szIn, szOut)
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Dim szIn, szOut As String
        szIn = txt.Text
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
        ShowBSTR(szIn, szOut)
        Debug.WriteLine(szIn & vbCrLf)
        Debug.WriteLine(szOut & vbCrLf)
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Dim szIn As String
        szIn = txt.Text
        ShowL(szIn)
    End Sub
End Class
