Option Strict Off
Option Explicit On 

Public Class frmAppendFile
    Inherits System.Windows.Forms.Form

    Dim m_bStop As Boolean = False

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
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents txtEnd As System.Windows.Forms.TextBox
    Friend WithEvents txtFile1 As System.Windows.Forms.TextBox
    Friend WithEvents txtFile2 As System.Windows.Forms.TextBox
    Friend WithEvents butBrower As System.Windows.Forms.Button
    Friend WithEvents butBrower1 As System.Windows.Forms.Button
    Friend WithEvents ofdlg As System.Windows.Forms.OpenFileDialog
    Friend WithEvents butBrower2 As System.Windows.Forms.Button
    Friend WithEvents butStart As System.Windows.Forms.Button
    Friend WithEvents butCancel As System.Windows.Forms.Button
    Friend WithEvents butExit As System.Windows.Forms.Button
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents labNum As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.txtEnd = New System.Windows.Forms.TextBox
        Me.txtFile1 = New System.Windows.Forms.TextBox
        Me.txtFile2 = New System.Windows.Forms.TextBox
        Me.butBrower = New System.Windows.Forms.Button
        Me.butBrower1 = New System.Windows.Forms.Button
        Me.butBrower2 = New System.Windows.Forms.Button
        Me.ofdlg = New System.Windows.Forms.OpenFileDialog
        Me.butStart = New System.Windows.Forms.Button
        Me.butCancel = New System.Windows.Forms.Button
        Me.butExit = New System.Windows.Forms.Button
        Me.Label4 = New System.Windows.Forms.Label
        Me.Label5 = New System.Windows.Forms.Label
        Me.labNum = New System.Windows.Forms.Label
        Me.Label6 = New System.Windows.Forms.Label
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 32)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(96, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "合并后的文件："
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(16, 64)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(104, 16)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "要合并的文件1："
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 96)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(104, 16)
        Me.Label3.TabIndex = 1
        Me.Label3.Text = "要合并的文件2："
        '
        'txtEnd
        '
        Me.txtEnd.Location = New System.Drawing.Point(120, 24)
        Me.txtEnd.Name = "txtEnd"
        Me.txtEnd.Size = New System.Drawing.Size(464, 21)
        Me.txtEnd.TabIndex = 2
        Me.txtEnd.Text = "txtEnd"
        '
        'txtFile1
        '
        Me.txtFile1.Location = New System.Drawing.Point(120, 56)
        Me.txtFile1.Name = "txtFile1"
        Me.txtFile1.Size = New System.Drawing.Size(464, 21)
        Me.txtFile1.TabIndex = 2
        Me.txtFile1.Text = "txtFile1"
        '
        'txtFile2
        '
        Me.txtFile2.Location = New System.Drawing.Point(120, 88)
        Me.txtFile2.Name = "txtFile2"
        Me.txtFile2.Size = New System.Drawing.Size(464, 21)
        Me.txtFile2.TabIndex = 2
        Me.txtFile2.Text = "txtFile2"
        '
        'butBrower
        '
        Me.butBrower.Location = New System.Drawing.Point(608, 24)
        Me.butBrower.Name = "butBrower"
        Me.butBrower.Size = New System.Drawing.Size(72, 24)
        Me.butBrower.TabIndex = 3
        Me.butBrower.Text = "浏览"
        '
        'butBrower1
        '
        Me.butBrower1.Location = New System.Drawing.Point(608, 56)
        Me.butBrower1.Name = "butBrower1"
        Me.butBrower1.Size = New System.Drawing.Size(72, 24)
        Me.butBrower1.TabIndex = 3
        Me.butBrower1.Text = "浏览"
        '
        'butBrower2
        '
        Me.butBrower2.Location = New System.Drawing.Point(608, 88)
        Me.butBrower2.Name = "butBrower2"
        Me.butBrower2.Size = New System.Drawing.Size(72, 24)
        Me.butBrower2.TabIndex = 3
        Me.butBrower2.Text = "浏览"
        '
        'butStart
        '
        Me.butStart.Location = New System.Drawing.Point(112, 128)
        Me.butStart.Name = "butStart"
        Me.butStart.Size = New System.Drawing.Size(112, 24)
        Me.butStart.TabIndex = 4
        Me.butStart.Text = "开始合并（&S）"
        '
        'butCancel
        '
        Me.butCancel.Location = New System.Drawing.Point(288, 128)
        Me.butCancel.Name = "butCancel"
        Me.butCancel.Size = New System.Drawing.Size(104, 24)
        Me.butCancel.TabIndex = 5
        Me.butCancel.Text = "取消（&C）"
        '
        'butExit
        '
        Me.butExit.Location = New System.Drawing.Point(448, 128)
        Me.butExit.Name = "butExit"
        Me.butExit.Size = New System.Drawing.Size(104, 24)
        Me.butExit.TabIndex = 6
        Me.butExit.Text = "退出（&E）"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(24, 168)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(648, 16)
        Me.Label4.TabIndex = 7
        Me.Label4.Text = "把文件1中的宏与文件2中的宏不重复地复制到合并后的文件中"
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(280, 200)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(32, 16)
        Me.Label5.TabIndex = 8
        Me.Label5.Text = "已有"
        '
        'labNum
        '
        Me.labNum.Location = New System.Drawing.Point(320, 200)
        Me.labNum.Name = "labNum"
        Me.labNum.Size = New System.Drawing.Size(64, 16)
        Me.labNum.TabIndex = 9
        Me.labNum.Text = "0"
        Me.labNum.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'Label6
        '
        Me.Label6.Location = New System.Drawing.Point(392, 200)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(64, 16)
        Me.Label6.TabIndex = 10
        Me.Label6.Text = "个宏"
        '
        'frmAppendFile
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(696, 229)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.labNum)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.butExit)
        Me.Controls.Add(Me.butCancel)
        Me.Controls.Add(Me.butStart)
        Me.Controls.Add(Me.butBrower)
        Me.Controls.Add(Me.txtEnd)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.txtFile1)
        Me.Controls.Add(Me.txtFile2)
        Me.Controls.Add(Me.butBrower1)
        Me.Controls.Add(Me.butBrower2)
        Me.MaximizeBox = False
        Me.Name = "frmAppendFile"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "合并文件"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub frmAppendFile_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        txtEnd.Text = ""
        txtFile1.Text = ""
        txtFile2.Text = ""
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butBrower2.Click
        ofdlg.ShowDialog()
        If ofdlg.FileName <> "" Then
            txtFile2.Text = ofdlg.FileName
        End If
    End Sub

    Private Sub butExit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butExit.Click
        Me.Close()
    End Sub

    Private Sub butBrower_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butBrower.Click
        ofdlg.ShowDialog()
        If ofdlg.FileName <> "" Then
            txtEnd.Text = ofdlg.FileName
        End If
    End Sub

    Private Sub butBrower1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butBrower1.Click
        ofdlg.ShowDialog()
        If ofdlg.FileName <> "" Then
            txtFile1.Text = ofdlg.FileName
        End If
    End Sub

    Private Sub butStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butStart.Click
        Dim szInput() As String, szTemp As String
        Dim Num As Integer, i As Long
        m_bStop = False
        ReDim szInput(0)
        butStart.Enabled = False
        Num = FreeFile()
        i = 0
        FileOpen(Num, txtFile1.Text, OpenMode.Input)
        While Not EOF(Num)
            szTemp = LineInput(Num)
            If i = 0 Then
                If Microsoft.VisualBasic.Left(szTemp, 2) <> "__" Then
                    szInput(0) = szTemp
                    i = i + 1
                End If
            Else
                If SearchBin(szTemp, szInput) Then
                    MsgBox("用户结止")
                    Exit Sub
                End If
            End If
        End While
        FileClose(Num)
        Num = FreeFile()
        FileOpen(Num, txtFile2.Text, OpenMode.Input)
        While Not EOF(Num)
            szTemp = LineInput(Num)
            If SearchBin(szTemp, szInput) Then
                MsgBox("用户结止")
                Exit Sub
            End If
        End While
        FileClose(Num)
        Num = FreeFile()
        FileOpen(Num, txtEnd.Text, OpenMode.Output)
        For i = 0 To szInput.GetUpperBound(0)
            PrintLine(Num, szInput(i))
        Next
        FileClose(Num)
        butStart.Enabled = True
        MsgBox("合并文件完成")
    End Sub

    '*******************************************************************************************************
    '函数名：SearchBin
    '描  述：折半查找
    '参  数：
    '        ByVal szInput As String   ：要添加的字符串
    '        ByRef szArrary() As String：数组
    '返回值：用户终止返回 TRUE，否则返回 FALSE。
    '版  本：1.0.*
    '作  者：康  林
    '时  间：2005-6-21 13:44:05
    '*******************************************************************************************************
    Private Function SearchBin(ByVal szInput As String, ByRef szArrary() As String) As Boolean
        Dim iFind As Integer, iLow As Long, iHeight As Long, iMid As Long
        Dim i As Long
        If Microsoft.VisualBasic.Left(szInput, 2) = "__" Then
            Return False
        End If
        iFind = -1
        i = szArrary.GetUpperBound(0)
        '折半查找
        iLow = 0
        iHeight = i
        iMid = iLow
        While iLow <= iHeight
            iMid = CLng((iLow + iHeight) / 2)
            If szInput = szArrary(iMid) Then
                Exit Function
            ElseIf szInput < szArrary(iMid) Then
                iHeight = iMid - 1
            Else
                iLow = iMid + 1
            End If
        End While
        If 0 <> iFind Then '没找到
            i = i + 1
            ReDim Preserve szArrary(i)
            labNum.Text = i
            Application.DoEvents()
            If iHeight < 0 Then
                iHeight = 0
            End If
            If szArrary(iHeight) < szInput Then
                iHeight = iHeight + 1
            End If
            For iMid = i To iHeight + 1 Step -1
                szArrary(iMid) = szArrary(iMid - 1)
            Next
            szArrary(iHeight) = szInput
        End If
        If m_bStop Then
            SearchBin = True
        Else
            SearchBin = False
        End If
    End Function

    Private Sub butCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butCancel.Click
        m_bStop = True
    End Sub
End Class
