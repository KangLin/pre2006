VERSION 5.00
Begin VB.Form selectpaper 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "选取图纸"
   ClientHeight    =   4185
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6030
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4185
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Tag             =   "0"
   Begin VB.CommandButton Command3 
      Caption         =   "修改"
      Height          =   375
      Left            =   4680
      TabIndex        =   12
      Top             =   2400
      Width           =   1215
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
      Caption         =   "显示本窗口(&S)"
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
'作者:康林

Option Explicit

Private Type PaperType
     name As String
     Width As Single
     Height As Single
     End Type
Private PaperStype() As PaperType  '内存中记录图纸类型
Private n As Integer
Private CurrentPaper As String   '设置的图纸
Private CurrentPaperIndex As Long   '当前装入图纸的号

Private Sub chkLoadTipsAtStartup_Click()
Dim i
    ' 保存在下次启动时是否显示此窗体
    i = WritePrivateProfileString("选项", "在启动时显示选取图纸窗口", CStr(chkLoadTipsAtStartup.Value), Inifile)
End Sub

Private Sub Form_Load()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    Dim ShowAtStartup As Long
    Dim i As Long, ss As String * 20
    ' 察看在启动时是否将被显示
    i = GetPrivateProfileString("选项", "在启动时显示选取图纸窗口", "1", ss, 10, Inifile)
    If i = 0 Then
       ShowAtStartup = 1
    Else
       ShowAtStartup = Val(left$(ss, i))
    End If
    If ShowAtStartup = 0 Then     '不显示
       Unload Me
       Exit Sub
    Else
    End If
    
    ' 设置复选框，强行将值写回到注册表
    If ShowAtStartup <> 0 Then
       Me.chkLoadTipsAtStartup.Value = vbChecked
    End If
    
    '设置显示列表的默认值
    TakePaperStype   '加载图纸类型
    
    For i = 1 To n    '显示图纸高度和宽度
        With PaperStype(i)
             If .name = CurrentPaper Then
                Text1.text = .Width
                Text2.text = .Height
                List1.ListIndex = CurrentPaperIndex
                Exit For
             End If
        End With
    Next i
    
    Text1.Enabled = False   ' 两输入框一般不接收数据
    Text2.Enabled = False   '只有在增加时才接收数据
        
End Sub

Private Sub List1_Click()   '图纸类型例表
Dim i As Long
      For i = 1 To n
          With PaperStype(i)
               If List1.List(List1.ListIndex) = .name Then
                  Text1.text = .Width  '显示高度
                  Text2.text = .Height '....宽度
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
       
       For i = 1 To n    '把当前选取的图纸类型放入配置文件中
           If PaperStype(i).name = List1.List(List1.ListIndex) Then
              i = WritePrivateProfileString("paper", "width", CStr(PaperStype(i).Width), Inifile)
              i = WritePrivateProfileString("paper", "height", CStr(PaperStype(i).Height), Inifile)
              Unload Me
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
        n = n + 1
        ReDim Preserve PaperStype(n)
        PaperStype(n).name = InputBox("输入新的图纸名")
        If PaperStype(n).name = "" Then   '当取消时
           n = n - 1
           ReDim Preserve PaperStype(n)
           Exit Sub
        End If
        List1.AddItem (PaperStype(n).name)  '增加元素
        List1.ListIndex = n - 1   '显示列表中的选取元素,因为列表从0开始,paperstype宽容从1开始
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
        For i = 1 To n
            If List1.List(List1.ListIndex) = PaperStype(i).name Then
                    List1.RemoveItem (List1.ListIndex)    '删去选定的元素
                    If List1.ListIndex > 0 Then
                       List1.ListIndex = i - 1
                    End If
                    For j = i To n - 1     '从数组中删除
                        PaperStype(j) = PaperStype(j + 1)
                    Next j
                    flag = True
                    Exit For
            End If
        Next i
        If flag Then
           flag = False  '
           n = n - 1    ' 从数组中删除
           ReDim Preserve PaperStype(n)
           For i = 1 To n  '删除后指向的图纸
               With PaperStype(i)
                    If List1.List(List1.ListIndex) = .name Then
                       flag = True
                       Text1.text = .Width
                       Text2.text = .Height
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
Dim num As Long, i As Long, j As Long, ss As Single
num = FreeFile
If n > 0 Then
       Open PaperFileName For Output As #num
       Print #num, n
       Print #num, CurrentPaper
       For i = 1 To n
           With PaperStype(i)
                Print #num, .name
                Print #num, .Width
                Print #num, .Height
           End With
      Next i
      Close #num
End If
End Sub

'从文件中取出图纸类型
Public Sub TakePaperStype()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
Dim num As Integer
Dim i As Long
num = FreeFile
       Open PaperFileName For Input As #num
       Input #num, n
       If n > 0 Then
          ReDim Preserve PaperStype(n)
          Input #num, CurrentPaper
          For i = 1 To n
             With PaperStype(i)
                  Input #num, .name
                  Input #num, .Width
                  Input #num, .Height
                  List1.AddItem (.name)
                  If .name = CurrentPaper Then
                      CurrentPaperIndex = i - 1
                  End If
             End With
          Next i
        End If
        Close #num
End Sub

'图纸大小显示
Private Sub Text1_KeyUp(KeyCode As Integer, Shift As Integer)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
Dim control As control, i As Long
Select Case KeyCode
       Case vbKeySpace
            For i = 1 To n
                If PaperStype(i).name = List1.List(List1.ListIndex) Then
                   PaperStype(i).Width = Text1.text
                   PaperStype(i).Height = Text2.text
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

'图纸大小显示
Private Sub Text2_KeyUp(KeyCode As Integer, Shift As Integer)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
Dim control As control, i As Long
Select Case KeyCode
       Case vbKeySpace
            For i = 1 To n
                If PaperStype(i).name = List1.List(List1.ListIndex) Then
                   PaperStype(i).Width = Text1.text
                   PaperStype(i).Height = Text2.text
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
