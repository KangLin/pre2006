'*******************************************************************************************************
'版权所有 (C) 2005 康林工作室；保留所有权利。
'文件名：Form1.vb
'描  述：得到文件中的宏
'版  本：1.0.*
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2005-6-17
'时  间：2005-6-17 14:14:51
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************
Option Strict Off
Option Explicit On 

Imports System.IO.IOException
Imports System.IO
Imports Microsoft.VisualBasic.Strings

Public Class frmMain
    Inherits System.Windows.Forms.Form

    Dim m_bStop As Boolean

#Region " Windows 窗体设计器生成的代码 "

    Public Sub New()
        MyBase.New()

        '该调用是 Windows 窗体设计器所必需的。
        InitializeComponent()

        '在 InitializeComponent() 调用之后添加任何初始化
        lstMacro.Text = ""
        m_bStop = False

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
    Friend WithEvents DirList As Microsoft.VisualBasic.Compatibility.VB6.DirListBox
    Friend WithEvents DriveList As Microsoft.VisualBasic.Compatibility.VB6.DriveListBox
    Friend WithEvents FileList As Microsoft.VisualBasic.Compatibility.VB6.FileListBox
    Friend WithEvents lstMacro As System.Windows.Forms.ListBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents butStart As System.Windows.Forms.Button
    Friend WithEvents butStop As System.Windows.Forms.Button
    Friend WithEvents butExit As System.Windows.Forms.Button
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents mnuMain As System.Windows.Forms.MainMenu
    Friend WithEvents mnuFile As System.Windows.Forms.MenuItem
    Friend WithEvents mnuHelp As System.Windows.Forms.MenuItem
    Friend WithEvents mnuHelpAbout As System.Windows.Forms.MenuItem
    Friend WithEvents mnuToolsAppend As System.Windows.Forms.MenuItem
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents butDeleteAll As System.Windows.Forms.Button
    Friend WithEvents butDelet As System.Windows.Forms.Button
    Friend WithEvents lstDirFile As System.Windows.Forms.ListBox
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents txtTime As System.Windows.Forms.TextBox
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents txtNum As System.Windows.Forms.TextBox
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents txtFile As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmMain))
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.FileList = New Microsoft.VisualBasic.Compatibility.VB6.FileListBox
        Me.DriveList = New Microsoft.VisualBasic.Compatibility.VB6.DriveListBox
        Me.DirList = New Microsoft.VisualBasic.Compatibility.VB6.DirListBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.lstMacro = New System.Windows.Forms.ListBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.butStart = New System.Windows.Forms.Button
        Me.butStop = New System.Windows.Forms.Button
        Me.butExit = New System.Windows.Forms.Button
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.mnuMain = New System.Windows.Forms.MainMenu
        Me.mnuFile = New System.Windows.Forms.MenuItem
        Me.mnuToolsAppend = New System.Windows.Forms.MenuItem
        Me.mnuHelp = New System.Windows.Forms.MenuItem
        Me.mnuHelpAbout = New System.Windows.Forms.MenuItem
        Me.GroupBox2 = New System.Windows.Forms.GroupBox
        Me.butDeleteAll = New System.Windows.Forms.Button
        Me.butDelet = New System.Windows.Forms.Button
        Me.lstDirFile = New System.Windows.Forms.ListBox
        Me.GroupBox3 = New System.Windows.Forms.GroupBox
        Me.Label8 = New System.Windows.Forms.Label
        Me.txtTime = New System.Windows.Forms.TextBox
        Me.Label7 = New System.Windows.Forms.Label
        Me.txtNum = New System.Windows.Forms.TextBox
        Me.Label6 = New System.Windows.Forms.Label
        Me.txtFile = New System.Windows.Forms.TextBox
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.FileList)
        Me.GroupBox1.Controls.Add(Me.DriveList)
        Me.GroupBox1.Controls.Add(Me.DirList)
        Me.GroupBox1.Controls.Add(Me.Label4)
        Me.GroupBox1.Location = New System.Drawing.Point(328, 16)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(184, 392)
        Me.GroupBox1.TabIndex = 2
        Me.GroupBox1.TabStop = False
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 168)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(144, 16)
        Me.Label3.TabIndex = 4
        Me.Label3.Text = "右击选取"
        '
        'FileList
        '
        Me.FileList.HorizontalScrollbar = True
        Me.FileList.Location = New System.Drawing.Point(16, 192)
        Me.FileList.Name = "FileList"
        Me.FileList.Pattern = "*.*"
        Me.FileList.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended
        Me.FileList.Size = New System.Drawing.Size(160, 172)
        Me.FileList.TabIndex = 3
        '
        'DriveList
        '
        Me.DriveList.Location = New System.Drawing.Point(16, 17)
        Me.DriveList.Name = "DriveList"
        Me.DriveList.Size = New System.Drawing.Size(160, 22)
        Me.DriveList.TabIndex = 2
        '
        'DirList
        '
        Me.DirList.HorizontalScrollbar = True
        Me.DirList.IntegralHeight = False
        Me.DirList.Location = New System.Drawing.Point(16, 48)
        Me.DirList.Name = "DirList"
        Me.DirList.Size = New System.Drawing.Size(160, 112)
        Me.DirList.TabIndex = 1
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(16, 368)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(144, 16)
        Me.Label4.TabIndex = 4
        Me.Label4.Text = "右击选取"
        '
        'lstMacro
        '
        Me.lstMacro.HorizontalScrollbar = True
        Me.lstMacro.ItemHeight = 12
        Me.lstMacro.Location = New System.Drawing.Point(16, 200)
        Me.lstMacro.Name = "lstMacro"
        Me.lstMacro.Size = New System.Drawing.Size(288, 184)
        Me.lstMacro.Sorted = True
        Me.lstMacro.TabIndex = 4
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(16, 176)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(88, 16)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "宏："
        '
        'butStart
        '
        Me.butStart.Location = New System.Drawing.Point(32, 392)
        Me.butStart.Name = "butStart"
        Me.butStart.Size = New System.Drawing.Size(80, 24)
        Me.butStart.TabIndex = 9
        Me.butStart.Text = "开始(&S)"
        '
        'butStop
        '
        Me.butStop.Location = New System.Drawing.Point(128, 392)
        Me.butStop.Name = "butStop"
        Me.butStop.Size = New System.Drawing.Size(80, 24)
        Me.butStop.TabIndex = 10
        Me.butStop.Text = "停止(&P)"
        '
        'butExit
        '
        Me.butExit.Location = New System.Drawing.Point(224, 392)
        Me.butExit.Name = "butExit"
        Me.butExit.Size = New System.Drawing.Size(80, 24)
        Me.butExit.TabIndex = 11
        Me.butExit.Text = "退出(&E)"
        '
        'Timer1
        '
        Me.Timer1.Interval = 1000
        '
        'mnuMain
        '
        Me.mnuMain.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuFile, Me.mnuHelp})
        '
        'mnuFile
        '
        Me.mnuFile.Index = 0
        Me.mnuFile.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuToolsAppend})
        Me.mnuFile.Text = "工具(&T)"
        '
        'mnuToolsAppend
        '
        Me.mnuToolsAppend.Index = 0
        Me.mnuToolsAppend.Text = "合并文件"
        '
        'mnuHelp
        '
        Me.mnuHelp.Index = 1
        Me.mnuHelp.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuHelpAbout})
        Me.mnuHelp.Text = "帮助(&H)"
        '
        'mnuHelpAbout
        '
        Me.mnuHelpAbout.Index = 0
        Me.mnuHelpAbout.Text = "关于(&A)"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.butDeleteAll)
        Me.GroupBox2.Controls.Add(Me.butDelet)
        Me.GroupBox2.Controls.Add(Me.lstDirFile)
        Me.GroupBox2.Location = New System.Drawing.Point(8, 16)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(312, 152)
        Me.GroupBox2.TabIndex = 19
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "目录和文件:"
        '
        'butDeleteAll
        '
        Me.butDeleteAll.Location = New System.Drawing.Point(236, 104)
        Me.butDeleteAll.Name = "butDeleteAll"
        Me.butDeleteAll.Size = New System.Drawing.Size(72, 24)
        Me.butDeleteAll.TabIndex = 11
        Me.butDeleteAll.Text = "全部删除"
        '
        'butDelet
        '
        Me.butDelet.Location = New System.Drawing.Point(236, 40)
        Me.butDelet.Name = "butDelet"
        Me.butDelet.Size = New System.Drawing.Size(72, 24)
        Me.butDelet.TabIndex = 10
        Me.butDelet.Text = "删除"
        '
        'lstDirFile
        '
        Me.lstDirFile.HorizontalScrollbar = True
        Me.lstDirFile.ItemHeight = 12
        Me.lstDirFile.Location = New System.Drawing.Point(8, 24)
        Me.lstDirFile.Name = "lstDirFile"
        Me.lstDirFile.Size = New System.Drawing.Size(224, 112)
        Me.lstDirFile.TabIndex = 9
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.Label8)
        Me.GroupBox3.Controls.Add(Me.txtTime)
        Me.GroupBox3.Controls.Add(Me.Label7)
        Me.GroupBox3.Controls.Add(Me.txtNum)
        Me.GroupBox3.Controls.Add(Me.Label6)
        Me.GroupBox3.Controls.Add(Me.txtFile)
        Me.GroupBox3.Controls.Add(Me.Label5)
        Me.GroupBox3.Location = New System.Drawing.Point(-8, 416)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(552, 40)
        Me.GroupBox3.TabIndex = 20
        Me.GroupBox3.TabStop = False
        '
        'Label8
        '
        Me.Label8.Location = New System.Drawing.Point(512, 10)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(16, 16)
        Me.Label8.TabIndex = 25
        Me.Label8.Text = "秒"
        '
        'txtTime
        '
        Me.txtTime.Location = New System.Drawing.Point(456, 10)
        Me.txtTime.Name = "txtTime"
        Me.txtTime.Size = New System.Drawing.Size(48, 21)
        Me.txtTime.TabIndex = 24
        Me.txtTime.Text = "0"
        '
        'Label7
        '
        Me.Label7.Location = New System.Drawing.Point(416, 10)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(48, 16)
        Me.Label7.TabIndex = 23
        Me.Label7.Text = "用时："
        '
        'txtNum
        '
        Me.txtNum.Location = New System.Drawing.Point(320, 10)
        Me.txtNum.Name = "txtNum"
        Me.txtNum.Size = New System.Drawing.Size(80, 21)
        Me.txtNum.TabIndex = 22
        Me.txtNum.Text = "0"
        '
        'Label6
        '
        Me.Label6.Location = New System.Drawing.Point(256, 10)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(88, 16)
        Me.Label6.TabIndex = 21
        Me.Label6.Text = "找到个数："
        '
        'txtFile
        '
        Me.txtFile.Location = New System.Drawing.Point(96, 10)
        Me.txtFile.Name = "txtFile"
        Me.txtFile.Size = New System.Drawing.Size(152, 21)
        Me.txtFile.TabIndex = 20
        Me.txtFile.Text = ""
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(8, 10)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(96, 16)
        Me.Label5.TabIndex = 19
        Me.Label5.Text = "正在查找文件："
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(72, 464)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(400, 16)
        Me.Label1.TabIndex = 21
        Me.Label1.Text = "宏被保存在当前目录下的 List.txt文件中"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'frmMain
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(528, 481)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.butExit)
        Me.Controls.Add(Me.butStop)
        Me.Controls.Add(Me.butStart)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.lstMacro)
        Me.Controls.Add(Me.GroupBox1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Menu = Me.mnuMain
        Me.Name = "frmMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "得到宏"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox3.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Timer1_Tick(ByVal sender As Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        txtTime.Text = CLng(txtTime.Text) + 1
    End Sub

    Private Sub mnuHelpAbout_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuHelpAbout.Click
        Dim frm As New frmAbout
        frm.Icon = Me.Icon
        frm.ShowDialog(Me)
    End Sub

    Private Sub frmMain_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.Text = Application.ProductName
    End Sub

    Private Sub MenuItem1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuToolsAppend.Click
        Dim frm As New frmAppendFile
        frm.Icon = Me.Icon
        frm.ShowDialog()
    End Sub

    Private Sub DriveList_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles DriveList.SelectedIndexChanged
        Try
            DirList.Path = DriveList.Text
        Catch ex As IO.IOException
            MsgBox(ex.Message)
        End Try
    End Sub

    Private Sub DirList_DoubleClick(ByVal sender As Object, ByVal e As System.EventArgs) Handles DirList.DoubleClick
        FileList.Path = DirList.Path
    End Sub

    Private Sub DirList_MouseUp(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles DirList.MouseUp
        If e.Button = MouseButtons.Right Then
            If lstDirFile.FindStringExact(DirList.Path) = -1 Then
                lstDirFile.Items.Add(DirList.Path)
            End If
        End If
    End Sub

    Private Sub FileList_MouseUp(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles FileList.MouseUp
        If e.Button = MouseButtons.Right Then
            Dim i As Long
            For Each i In FileList.SelectedIndices
                If lstDirFile.FindStringExact(DirList.Path & "\" & FileList.Items(i)) = -1 Then
                    lstDirFile.Items.Add(DirList.Path & "\" & FileList.Items(i))
                End If
            Next
        End If
    End Sub

    Private Sub butExit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butExit.Click
        m_bStop = True
        Me.Close()
    End Sub

    Private Sub butDeleteAll_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butDeleteAll.Click
        lstDirFile.Items.Clear()
    End Sub

    Private Sub butDelet_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butDelet.Click
        Try
            lstDirFile.Items.RemoveAt(lstDirFile.SelectedIndex)
        Catch ex As Exception
        End Try
    End Sub

    Private Sub butStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butStop.Click
        m_bStop = True
    End Sub

    Private Sub butStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles butStart.Click
        Dim i As Integer
        butStart.Enabled = False
        FileList.SelectionMode = SelectionMode.One
        lstMacro.Items.Clear()
        For i = 0 To lstDirFile.Items.Count - 1
            Timer1.Enabled = True
            lstDirFile.SelectedIndex = i
            If FindFile(lstDirFile.Items(i)) Then
                Exit For
            End If
        Next i
        WriteFile()
        FileList.SelectionMode = SelectionMode.MultiExtended
        m_bStop = False
        Timer1.Enabled = False
        butStart.Enabled = True
        MsgBox("完成任务")
    End Sub

    Private Function FindFile(ByVal szFile As String) As Boolean
        FindFile = False
        If GetAttr(szFile) = FileAttribute.Directory Then
            '是目录
            FindFile = SearchDir(szFile)
        Else
            '是文件
            FindFile = FindHFile(szFile)
        End If
    End Function

    '*******************************************************************************************************
    '函数名：SearchDir
    '描  述：枚举文件与目录
    '参  数：
    '        ByVal szDir As String：目录名
    '返回值：用户中断返回 TRUE,正常退出返回 FALSE.
    '版  本：1.0.*
    '作  者：康  林
    '时  间：2005-6-17 13:52:36
    '*******************************************************************************************************
    Private Function SearchDir(ByVal szDir As String) As Boolean
        Dim dirs As String()
        dirs = Directory.GetDirectories(szDir)
        Dim dir As String
        SearchDir = False
        If m_bStop Then
            SearchDir = True
            Exit Function
        End If

        '查找子目录
        For Each dir In dirs
            If SearchDir(dir) Then
                SearchDir = True
                Exit Function
            End If
            Application.DoEvents()
        Next
        '查找文件
        Dim files As String()
        files = Directory.GetFiles(szDir)
        Dim file As String
        For Each file In files
            If FindHFile(file) Then
                SearchDir = True
                Exit Function
            End If
        Next
    End Function

    '*******************************************************************************************************
    '函数名：FindHFile
    '描  述：查找头文件
    '参  数：
    '        ByVal szFile As String：文件名
    '返回值：用户中断返回 TRUE,正常退出返回 FALSE
    '版  本：1.0.*
    '作  者：康  林
    '时  间：2005-6-17 13:53:36
    '*******************************************************************************************************
    Private Function FindHFile(ByVal szFile As String) As Boolean
        Dim szExt As String
        Dim Num As Integer
        Dim Words As String
        FindHFile = False
        Dim i As Long
        For i = 0 To DriveList.Items.Count - 1
            If UCase(Microsoft.VisualBasic.Strings.Left(DriveList.Items(i), InStr(DriveList.Items(i), ":"))) _
            = UCase(Microsoft.VisualBasic.Strings.Left(Path.GetPathRoot(szFile), InStr(Path.GetPathRoot(szFile), ":"))) Then
                DriveList.SelectedIndex = i
            End If
        Next i
        DirList.Path = Path.GetDirectoryName(szFile)
        FileList.Path = DirList.Path
        FileList.SelectedIndex = FileList.FindStringExact(Path.GetFileName(szFile))
        szExt = Path.GetExtension(szFile)
        txtFile.Text = Path.GetFileName(szFile)
        Application.DoEvents()
        If LCase(szExt) = ".h" Then
            Num = FreeFile()

            Try
                FileOpen(Num, szFile, OpenMode.Binary)
                Words = Space(LOF(Num))
                FileGet(Num, Words)
                FileClose(Num)
            Catch ex As Exception
            End Try
            FindHFile = FindMarcoInFile(Words)
        End If
    End Function

    '*******************************************************************************************************
    '函数名：FindMarcoInFile
    '描  述：在代码中查找宏
    '参  数：
    '        ByVal szWords As String：代码
    '返回值：用户中断返回 TRUE,正常退出返回 FALSE
    '版  本：1.0.*
    '作  者：康  林
    '时  间：2005-6-17 13:54:27
    '*******************************************************************************************************
    Private Function FindMarcoInFile(ByVal szWords As String) As Boolean
        Dim sztemp As String, szBefore As String, szBack As String
        Dim i As Integer
        sztemp = szWords
        i = ValidCCode(sztemp)
        sztemp = Microsoft.VisualBasic.Strings.Left(sztemp, i)
        Debug.WriteLine(sztemp)
        FindMarcoInFile = False
        If m_bStop Then
            FindMarcoInFile = True
            Exit Function
        End If
        While MatchSplitSymbol(sztemp, "#define ", " ", szBefore, szBack) > 0
            sztemp = Trim(sztemp)
            If Microsoft.VisualBasic.Strings.Left(sztemp, 2) <> "__" Then
                i = InStr(sztemp, "(")
                If i Then
                    sztemp = Microsoft.VisualBasic.Strings.Left(sztemp, i - 1)
                End If

                i = lstMacro.FindStringExact(sztemp)
                If i = ListBox.NoMatches Then
                    lstMacro.SelectedIndex = lstMacro.Items.Add(sztemp)
                    txtNum.Text = CLng(txtNum.Text) + 1
                    Application.DoEvents()
                Else
                    'If lstMacro.Items(i) <> sztemp Then
                    '    Debug.WriteLine("lst:" & lstMacro.Items(i) & " sztemp:" & sztemp)
                    '    lstMacro.Items.Add(sztemp)
                    'End If
                End If
            End If
            sztemp = szBack
            Application.DoEvents()
        End While

        i = InStr(sztemp, "#define ")
        If i Then
            sztemp = Microsoft.VisualBasic.Strings.Right(sztemp, Len(sztemp) - (i + Len("#define ") - 1))
            i = lstMacro.FindStringExact(sztemp)
            If i = ListBox.NoMatches Then
                If Microsoft.VisualBasic.Strings.Left(sztemp, 2) <> "__" Then
                    lstMacro.SelectedIndex = lstMacro.Items.Add(sztemp)
                    txtNum.Text = CLng(txtNum.Text) + 1
                    Application.DoEvents()
                End If
            Else
                'If lstMacro.Items(i) <> sztemp Then
                '    Debug.WriteLine("lst:" & lstMacro.Items(i) & " sztemp:" & sztemp)
                '    lstMacro.Items.Add(sztemp)
                'End If
            End If
        End If

    End Function

    '*******************************************************************************************************
    '函数名：WriteFile
    '描  述：把宏写入文件：List.txt
    '参  数：无
    '返回值：用户中断返回 TRUE,正常退出返回 FALSE
    '版  本：1.0.*
    '作  者：康  林
    '时  间：2005-6-17 13:55:06
    '*******************************************************************************************************
    Private Function WriteFile() As Boolean
        Dim Num As Integer, i As Integer
        Num = FreeFile()
        FileOpen(Num, "list.txt", OpenMode.Output)
        For i = 0 To lstMacro.Items.Count - 1
            PrintLine(Num, lstMacro.Items(i))
        Next
        FileClose(Num)

    End Function

    Private Sub mnuFile_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuFile.Click

    End Sub
End Class
