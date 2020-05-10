VERSION 5.00
Begin VB.Form selectpaper 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "选取图纸"
   ClientHeight    =   4500
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6030
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4500
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton Command3 
      Caption         =   "修改"
      Height          =   375
      Left            =   4680
      TabIndex        =   13
      Top             =   2400
      Width           =   1215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "点击新文件时显示"
      Height          =   255
      Left            =   480
      TabIndex        =   12
      Top             =   4080
      Width           =   2175
   End
   Begin VB.TextBox Text2 
      Height          =   270
      Left            =   3600
      TabIndex        =   10
      Top             =   3000
      Width           =   975
   End
   Begin VB.TextBox Text1 
      Height          =   270
      Left            =   1920
      MultiLine       =   -1  'True
      TabIndex        =   8
      Top             =   3000
      Width           =   975
   End
   Begin VB.CheckBox chkLoadTipsAtStartup 
      Caption         =   "在启动时显示(&S)"
      Height          =   315
      Left            =   480
      TabIndex        =   5
      Top             =   3720
      Width           =   2055
   End
   Begin VB.ListBox List1 
      Height          =   2580
      ItemData        =   "selectpaper.frx":0000
      Left            =   480
      List            =   "selectpaper.frx":0002
      TabIndex        =   4
      Top             =   120
      Width           =   3375
   End
   Begin VB.CommandButton Command2 
      Caption         =   "删除"
      Height          =   375
      Left            =   4680
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "增加"
      Height          =   375
      Left            =   4680
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   1200
      Width           =   1215
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "取消"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "确定"
      Height          =   375
      Left            =   4680
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H0000FFFF&
      Caption         =   "用上下光标键或Tab键来选择高度或宽度,用空格键确定选取值"
      Height          =   180
      Left            =   480
      TabIndex        =   11
      Top             =   3480
      Visible         =   0   'False
      Width           =   4860
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "高度:"
      Height          =   180
      Left            =   3120
      TabIndex        =   9
      Top             =   3120
      Width           =   450
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "宽度:"
      Height          =   180
      Left            =   1440
      TabIndex        =   7
      Top             =   3120
      Width           =   450
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "纸的大小"
      Height          =   180
      Left            =   480
      TabIndex        =   6
      Top             =   3120
      Width           =   720
   End
End
Attribute VB_Name = "selectpaper"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'图纸的类型选取
Option Explicit

Private PaperFileName As String    '图纸文件名
Public showthiswindowsflag As Boolean   '强行显示本窗口标志
Private Type papertype
     name As String
     width As Single
     height As Single
     End Type
Private PaperStype() As papertype
Private N As Integer
Private CurrentPaper As String   '设置的图纸
Private currentpaperindex As Long   '当前装入图纸的号

Private Sub Check1_Click()
    ' 保存在下次点击新文件时时是否显示此窗体
    SaveSetting App.EXEName, "Options", "在点击新文件时显示", Check1.Value
End Sub

Private Sub chkLoadTipsAtStartup_Click()
    ' 保存在下次启动时是否显示此窗体
    SaveSetting App.EXEName, "Options", "在启动时显示", chkLoadTipsAtStartup.Value
End Sub

Private Sub Form_Load()
'On Error Resume Next
    Dim ShowAtStartup As Long
    Dim i As Long
    PaperFileName = App.Path + "\" + "papertype.cad"
    If showthiswindowsflag Then GoTo seclectpaperform1ladshowthiswindows    '强行显示本窗口
    ' 察看在启动时是否将被显示
    ShowAtStartup = GetSetting(App.EXEName, "Options", "在启动时显示", 1)
    If ShowAtStartup = 0 And Not user.Showselectpaperform Then     '不显示
        Unload Me
        Exit Sub
    End If
    
    ' 察看在点击新文件时是否将被显示
    ShowAtStartup = GetSetting(App.EXEName, "Options", "在点击新文件时显示", 1)
    If ShowAtStartup = 0 And user.Showselectpaperform Then      '不显示
        Unload Me
        Exit Sub
    End If

seclectpaperform1ladshowthiswindows:
    ' 设置复选框，强行将值写回到注册表
    ShowAtStartup = GetSetting(App.EXEName, "Options", "在启动时显示", 1)
    If ShowAtStartup <> 0 Then
       Me.chkLoadTipsAtStartup.Value = vbChecked
    End If
    
    ' 设置复选框，强行将值写回到注册表
    ShowAtStartup = GetSetting(App.EXEName, "Options", "在点击新文件时显示", 1)
    If ShowAtStartup <> 0 Then
       Me.Check1.Value = vbChecked
    End If
    
    '设置显示列表的默认值
    TakePaperStype   '加载图纸类型
    
    'If Not (user.showselectpaperform) Then
       '从起动时加载
       If List1.ListCount <> 0 Then
'          For i = 1 To N
 '             If PaperStype(i).name = crrentpaper Then
                 List1.ListIndex = currentpaperindex
       End If
    'Else
       '从新文件加载
    '   For i = 1 To N
    '       If List1.List(i) = user.paper.name Then
    '          List1.ListIndex = i
    '       End If
    '   Next i
    'End If
    
    For i = 1 To N    '显示图纸高度和宽度
        With PaperStype(i)
             If .name = CurrentPaper Then
                Text1.text = .width
                Text2.text = .height
                Exit For
             End If
        End With
    Next i
    
    Text1.Enabled = False   ' 两输入框一般不接收数据
    Text2.Enabled = False   '只有在增加时才接收数据
        
End Sub

Private Sub List1_Click()
Dim i As Long
      For i = 1 To N
          With PaperStype(i)
               If List1.List(List1.ListIndex) = .name Then
                  Text1.text = .width  '显示高度
                  Text2.text = .height '....宽度
                  Exit For
               End If
          End With
      Next i
End Sub

Private Sub OKButton_Click()   '确定控扭
Dim i As Long
       'list(index)是一个函数
       'If List1.List(List1.ListIndex) = "e" Then '取出选取的元素
       '   MsgBox ("ok")
       'End If
       CurrentPaper = List1.List(List1.ListIndex)
       SavePaperStype    '保存图纸类型
       For i = 1 To N
           If PaperStype(i).name = List1.List(List1.ListIndex) Then
              With user.paper   '给图纸参数赋值
                   .width = PaperStype(i).width
                   .height = PaperStype(i).height
              End With
              If Not (showthiswindowsflag) Then
                 'Load frmOptions  '当从程序起动或点击新文件时,给图纸赋值
                  With PaperStype(i)  '从选项中时,给图纸赋值
                       frmOptions.pwidth.text = .width
                       frmOptions.pheight.text = .height
                  End With
                 frmOptions.cmdOK_Click
              Else
                  With PaperStype(i)  '从选项中时,给图纸赋值
                       frmOptions.pwidth.text = .width
                       frmOptions.pheight.text = .height
                  End With
              End If
              Unload Me
              Exit Sub
            End If
       Next i
       Unload Me
End Sub

Private Sub CancelButton_Click()  '取消按扭
        Unload Me
End Sub

Private Sub Command3_Click()  '修改图纸类型
Dim control As control
For Each control In selectpaper.Controls
    control.Enabled = False
Next control
Text1.Enabled = True   '允许输入框响应事件,进行数据输入
Text2.Enabled = True
Label4.Visible = True   '提示
Text1.SetFocus
End Sub

Private Sub Command1_Click()  '增加图纸类型
Dim control As control
        N = N + 1
        ReDim Preserve PaperStype(N)
        PaperStype(N).name = InputBox("输入新的图纸名")
        If PaperStype(N).name = "" Then   '当取消时
           N = N - 1
           ReDim Preserve PaperStype(N)
           Exit Sub
        End If
        List1.AddItem (PaperStype(N).name)  '增加元素
        List1.ListIndex = N - 1   '显示列表中的选取元素,因为列表从0开始,paperstype宽容从1开始
        For Each control In selectpaper.Controls   '禁止所有控件响应事件
            control.Enabled = False                '为的是只让输入框输入数据
        Next control
        Text1.Enabled = True   '允许输入框响应事件,进行数据输入
        Text2.Enabled = True
        Label4.Visible = True '提示
        Text1.SetFocus
End Sub

Private Sub Command2_Click()   '删除图纸类型
Dim flag As Boolean
        Dim i As Long, j
        For i = 1 To N
            If List1.List(List1.ListIndex) = PaperStype(i).name Then
                    List1.RemoveItem (List1.ListIndex)    '删去选定的元素
                    If List1.ListIndex > 0 Then
                       List1.ListIndex = i - 1
                    End If
                    For j = i To N - 1     '从数组中删除
                        PaperStype(j) = PaperStype(j + 1)
                    Next j
                    flag = True
                    Exit For
            End If
        Next i
        If flag Then
           flag = False  '
           N = N - 1    ' 从数组中删除
           ReDim Preserve PaperStype(N)
           For i = 1 To N  '删除后指向的图纸
               With PaperStype(i)
                    If List1.List(List1.ListIndex) = .name Then
                       flag = True
                       Text1.text = .width
                       Text2.text = .height
                    End If
               End With
           Next i
           If Not (flag) Then  '无指向图纸,则为空
              Text1.text = ""
              Text2.text = ""
           End If
        End If
End Sub

'保存图纸类型
Public Sub SavePaperStype()
Dim num As Long, i As Long, j, ss As Single
num = FreeFile
If N > 0 Then
       Open PaperFileName For Output As #num
       Print #num, N
       Print #num, CurrentPaper
       For i = 1 To N
           With PaperStype(i)
                Print #num, .name
                If .name = CurrentPaper Then
                   If Check1.Value = Unchecked Or chkLoadTipsAtStartup.Value = Unchecked Then
                      ss = CStr(.width)
                      j = WritePrivateProfileString("paper", "width", ss, user.inifile)
                      ss = CStr(.height)
                      j = WritePrivateProfileString("paper", "height", ss, user.inifile)
                   End If
                End If
                Print #num, .width
                Print #num, .height
           End With
      Next i
      Close #num
End If
End Sub

'取出图纸类型
Public Sub TakePaperStype()
On Error Resume Next
Dim num As Integer
Dim i As Long
num = FreeFile
       Open PaperFileName For Input As #num
       Input #num, N
       If N > 0 Then
          ReDim Preserve PaperStype(N)
          Input #num, CurrentPaper
          For i = 1 To N
             With PaperStype(i)
                  Input #num, .name
                  Input #num, .width
                  Input #num, .height
                  List1.AddItem (.name)
                  If .name = CurrentPaper Then
                      currentpaperindex = i - 1
                  End If
             End With
          Next i
        End If
        Close #num
End Sub

Private Sub Text1_KeyUp(KeyCode As Integer, Shift As Integer)
On Error Resume Next
Dim control As control, i As Long
Select Case KeyCode
       Case vbKeySpace
            For i = 1 To N
                If PaperStype(i).name = List1.List(List1.ListIndex) Then
                   PaperStype(i).width = Text1.text
                   PaperStype(i).height = Text2.text
                End If
            Next i
            For Each control In selectpaper.Controls
                control.Enabled = True
            Next control
            Text1.Enabled = False
            Text2.Enabled = False
            Label4.Visible = False
       Case vbKeyDown, vbKeyUp
            Text2.SetFocus
End Select
End Sub

Private Sub Text2_KeyUp(KeyCode As Integer, Shift As Integer)
On Error Resume Next
Dim control As control, i As Long
Select Case KeyCode
       Case vbKeySpace
            For i = 1 To N
                If PaperStype(i).name = List1.List(List1.ListIndex) Then
                   PaperStype(i).width = Text1.text
                   PaperStype(i).height = Text2.text
                End If
            Next i
            For Each control In selectpaper.Controls
                control.Enabled = True
            Next control
            Text1.Enabled = False
            Text2.Enabled = False
            Label4.Visible = False
       Case vbKeyUp, vbKeyDown
            Text1.SetFocus
End Select
End Sub
