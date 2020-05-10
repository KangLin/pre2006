VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form add 
   Caption         =   "增加"
   ClientHeight    =   6060
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   8295
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   ScaleHeight     =   6060
   ScaleWidth      =   8295
   StartUpPosition =   2  '屏幕中心
   Begin VB.PictureBox PicProperty 
      Appearance      =   0  'Flat
      BackColor       =   &H8000000D&
      DragMode        =   1  'Automatic
      ForeColor       =   &H80000008&
      Height          =   4215
      Left            =   0
      ScaleHeight     =   4185
      ScaleWidth      =   1305
      TabIndex        =   11
      Top             =   1800
      Width           =   1335
      Begin VB.PictureBox DBGrid1 
         Height          =   3975
         Left            =   0
         ScaleHeight     =   3915
         ScaleWidth      =   1275
         TabIndex        =   13
         Top             =   240
         Width           =   1335
      End
      Begin VB.CommandButton ComPropertyClose 
         Height          =   225
         Left            =   1080
         Picture         =   "add.frx":0000
         Style           =   1  'Graphical
         TabIndex        =   12
         Top             =   0
         Width           =   255
      End
      Begin VB.Label LblProperty 
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "属性"
         ForeColor       =   &H8000000E&
         Height          =   180
         Left            =   0
         TabIndex        =   15
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox PicTool 
      Appearance      =   0  'Flat
      BackColor       =   &H8000000D&
      DragMode        =   1  'Automatic
      ForeColor       =   &H80000008&
      Height          =   1215
      Left            =   120
      ScaleHeight     =   1185
      ScaleWidth      =   1065
      TabIndex        =   8
      Top             =   120
      Width           =   1095
      Begin VB.CommandButton ComToolClose 
         Height          =   225
         Left            =   840
         Picture         =   "add.frx":0442
         Style           =   1  'Graphical
         TabIndex        =   10
         Top             =   0
         Width           =   255
      End
      Begin MSComctlLib.Toolbar Tb 
         Height          =   945
         Left            =   0
         TabIndex        =   9
         Top             =   240
         Width           =   1095
         _ExtentX        =   1931
         _ExtentY        =   1667
         ButtonWidth     =   609
         ButtonHeight    =   556
         Appearance      =   1
         Style           =   1
         ImageList       =   "ImgList"
         _Version        =   393216
         BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
            NumButtons      =   7
            BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Key             =   "label"
               Object.ToolTipText     =   "标签"
               ImageKey        =   "label"
            EndProperty
            BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Key             =   "text"
               Object.ToolTipText     =   "文本框"
               ImageKey        =   "text"
            EndProperty
            BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Key             =   "command"
               Object.ToolTipText     =   "工具按钮"
               ImageKey        =   "command"
            EndProperty
            BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Key             =   "frame"
               Object.ToolTipText     =   "框架"
               ImageKey        =   "frame"
            EndProperty
            BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Key             =   "check"
               Object.ToolTipText     =   "复选框"
               ImageKey        =   "check"
            EndProperty
            BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Key             =   "option"
               Object.ToolTipText     =   "单选框"
               ImageKey        =   "option"
            EndProperty
            BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Key             =   "list"
               Object.ToolTipText     =   "列表框"
               ImageKey        =   "list"
            EndProperty
         EndProperty
      End
      Begin VB.Label LblTool 
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "工具"
         ForeColor       =   &H8000000E&
         Height          =   180
         Left            =   0
         TabIndex        =   14
         Top             =   0
         Width           =   360
      End
   End
   Begin MSComctlLib.ImageList ImgList 
      Left            =   360
      Top             =   2760
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   15
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   20
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":0884
            Key             =   "redo"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":0DC8
            Key             =   "cut"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":130C
            Key             =   "help"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":1850
            Key             =   "new"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":1D94
            Key             =   "open"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":22D8
            Key             =   "pase"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":281C
            Key             =   "zoom"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":2D60
            Key             =   "print"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":32A4
            Key             =   "undo"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":37E8
            Key             =   "save"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":3D2C
            Key             =   "copy"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":4270
            Key             =   "text"
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":4388
            Key             =   "key"
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":450C
            Key             =   "check"
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":4618
            Key             =   "label"
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":472C
            Key             =   "arrow"
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":4840
            Key             =   "command"
         EndProperty
         BeginProperty ListImage18 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":4954
            Key             =   "option"
         EndProperty
         BeginProperty ListImage19 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":4A60
            Key             =   "list"
         EndProperty
         BeginProperty ListImage20 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "add.frx":4BA8
            Key             =   "frame"
         EndProperty
      EndProperty
   End
   Begin VB.Frame fraWindow 
      Caption         =   "窗口"
      Height          =   6015
      Left            =   1440
      TabIndex        =   0
      Top             =   0
      Width           =   6855
      Begin VB.ListBox List1 
         Height          =   270
         Index           =   0
         ItemData        =   "add.frx":4CB4
         Left            =   480
         List            =   "add.frx":4CBB
         Style           =   1  'Checkbox
         TabIndex        =   7
         Top             =   960
         Visible         =   0   'False
         Width           =   1455
      End
      Begin VB.OptionButton Option1 
         Caption         =   "单选框"
         Height          =   180
         Index           =   0
         Left            =   480
         TabIndex        =   6
         Top             =   1920
         Visible         =   0   'False
         Width           =   1215
      End
      Begin VB.CheckBox Check1 
         Caption         =   "复选框"
         Height          =   255
         Index           =   0
         Left            =   480
         TabIndex        =   5
         Top             =   1440
         Visible         =   0   'False
         Width           =   1215
      End
      Begin VB.Frame Frame1 
         Caption         =   "框架"
         Height          =   1815
         Index           =   0
         Left            =   2520
         TabIndex        =   4
         Top             =   480
         Visible         =   0   'False
         Width           =   1815
      End
      Begin VB.CommandButton Command1 
         Caption         =   "命令按钮"
         Height          =   375
         Index           =   0
         Left            =   3120
         TabIndex        =   3
         Top             =   2640
         Visible         =   0   'False
         Width           =   1215
      End
      Begin VB.TextBox Text1 
         Height          =   270
         Index           =   0
         Left            =   1320
         TabIndex        =   2
         Text            =   "文本框"
         Top             =   600
         Visible         =   0   'False
         Width           =   735
      End
      Begin VB.Shape Shape1 
         BorderStyle     =   3  'Dot
         Height          =   495
         Left            =   720
         Top             =   3600
         Visible         =   0   'False
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "标签"
         Height          =   180
         Index           =   0
         Left            =   480
         TabIndex        =   1
         Top             =   600
         Visible         =   0   'False
         Width           =   360
      End
   End
   Begin VB.Menu mnuOption 
      Caption         =   "选项(&O)"
      Begin VB.Menu mnuOptionTool 
         Caption         =   "工具窗口(&T)"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuOptionProperty 
         Caption         =   "属性窗口(&P)"
         Checked         =   -1  'True
      End
   End
End
Attribute VB_Name = "add"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function GetCursorPos Lib "user32" (lpPoint As POINTAPI) As Long
Private Type POINTAPI
        x As Long
        y As Long
End Type
Dim Button_Click As Boolean '工具按钮被按下的标志
Dim Button_Style As String  '工具栏按下的工具类型
Dim GetForceControl As Object  '得到焦点的控件
Dim MouseDownX As Single    '鼠标在键按下时的位置X
Dim MouseDownY As Single    '....................Y

'使工具按钮弹起
Private Sub Toolbar_Button_Unpressed(Optional 卸载已加载的控件 As Boolean = True)
Dim i As Long
    If Button_Click Then
        For i = 1 To Tb.Buttons.Count
            If Tb.Buttons.Item(i).Value = tbrPressed Then
               If 卸载已加载的控件 Then
                  Select Case Tb.Buttons.Item(i).Key
                         Case "label"
                               Unload Label1(Label1.UBound)
                         Case "text"
                               Unload Text1(Text1.UBound)
                         Case "frame"
                               Unload Frame1(Frame1.UBound)
                         Case "check"
                               Unload Check1(Check1.UBound)
                         Case "option"
                               Unload Option1(Option1.UBound)
                         Case "list"
                               Unload List1(List1.UBound)

                  End Select
                  Set GetForceControl = Nothing
               End If
               Tb.Buttons.Item(i).Value = tbrUnpressed
           
             End If
        Next i
        Tb.Refresh
        Button_Click = False
    End If
End Sub

Private Sub Tb_ButtonClick(ByVal Button As MSComctlLib.Button)
        Toolbar_Button_Unpressed True
        Select Case Button.Key
               Case "label"
                    Load Label1(Label1.Count)
                    Set GetForceControl = Label1(Label1.UBound)
               Case "text"
                    Load Text1(Text1.Count)
                    Set GetForceControl = Text1(Text1.UBound)
               Case "frame"
                    Load Frame1(Frame1.Count)
                    Set GetForceControl = Frame1(Frame1.UBound)
               Case "check"
                    Load Check1(Check1.Count)
                    Set GetForceControl = Check1(Check1.UBound)
               Case "option"
                    Load Option1(Option1.Count)
                    Set GetForceControl = Option1(Option1.UBound)
               Case "list"
                    Load List1(List1.Count)
                    Set GetForceControl = List1(List1.UBound)

        End Select
        Button.Value = tbrPressed
        Button_Style = Button.Key
        Button_Click = True
End Sub

'控件的大小和位置
Private Sub Control_Postion(x As Single, y As Single, Start As Boolean)
Dim n As Single
        If Button_Click Then
           With Shape1   '参考形状
                If Start Then
                  .Top = y - 50
                  .Left = x - 50
                  .Height = 0
                  .Width = 0
                  .Visible = True
                Else
                  n = y - .Top
                  If n >= 0 Then
                     .Height = n + 50
                  End If
                  n = x - .Left
                  If n >= 0 Then
                     .Width = n + 50
                  End If
           End If
           End With
           
           Select Case Button_Style
                  Case "label"
                       With Label1(Label1.UBound)
                          If Start Then
                            .Visible = True
                            .Top = y
                            .Left = x
                          Else
                               n = y - .Top
                               If n >= 0 Then
                                  .Height = n
                               End If
                               n = x - .Left
                               If n >= 0 Then
                                  .Width = n
                               End If
                          End If
                       End With
                   Case "text"
                       With Text1(Text1.UBound)
                          If Start Then
                            .Visible = True
                            .Top = y
                            .Left = x
                          Else
                               n = y - .Top
                               If n >= 0 Then
                                  .Height = n
                               End If
                               n = x - .Left
                               If n >= 0 Then
                                  .Width = n
                               End If
                          End If
                       End With
                    Case "frame"
                         With Frame1(Frame1.UBound)
                          If Start Then
                            .Visible = True
                            .Top = y
                            .Left = x
                          Else
                               n = y - .Top
                               If n >= 0 Then
                                  .Height = n
                               End If
                               n = x - .Left
                               If n >= 0 Then
                                  .Width = n
                               End If
                          End If
                        End With
                    Case "command"
                          With Command1(Command1.UBound)
                                 If Start Then
                            .Visible = True
                            .Top = y
                            .Left = x
                          Else
                               n = y - .Top
                               If n >= 0 Then
                                  .Height = n
                               End If
                               n = x - .Left
                               If n >= 0 Then
                                  .Width = n
                               End If
                          End If
                          End With
                    Case "check"
                         With Check1(Check1.UBound)
                          If Start Then
                            .Visible = True
                            .Top = y
                            .Left = x
                          Else
                               n = y - .Top
                               If n >= 0 Then
                                  .Height = n
                               End If
                               n = x - .Left
                               If n >= 0 Then
                                  .Width = n
                               End If
                          End If
                         End With
                    Case "option"
                         With Option1(Option1.UBound)
                          If Start Then
                            .Visible = True
                            .Top = y
                            .Left = x
                          Else
                               n = y - .Top
                               If n >= 0 Then
                                  .Height = n
                               End If
                               n = x - .Left
                               If n >= 0 Then
                                  .Width = n
                               End If
                          End If
                        End With
                    Case "list"
                         With List1(List1.UBound)
                          If Start Then
                            .Visible = True
                            .Top = y
                            .Left = x
                          Else
                               n = y - .Top
                               If n >= 0 Then
                                  .Height = n
                               End If
                               n = x - .Left
                               If n >= 0 Then
                                  .Width = n
                               End If
                          End If
                         End With
               End Select
        End If
End Sub

Private Sub ComToolClose_Click() '关闭工具窗口
        PicTool.Visible = False
        mnuOptionTool.Checked = False
End Sub

Private Sub ComPropertyClose_Click() '关闭属性窗口
        PicProperty.Visible = False
        mnuOptionProperty.Checked = False
End Sub

Private Sub Form_Click()
        Toolbar_Button_Unpressed  '使工具栏上的按钮弹起
End Sub

Private Sub Form_DragDrop(Source As Control, x As Single, y As Single)
        With Source
             .Top = y
             .Left = x
        End With
End Sub

Private Sub Form_Load()
        With PicTool
             .Visible = mnuOptionTool.Checked
             Tb.Top = .Height - Tb.Height
        End With
End Sub

Private Sub fraWindow_DragDrop(Source As Control, x As Single, y As Single)
        With Source
             .Top = y
             .Left = x
        End With
End Sub

Private Sub fraWindow_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
        Control_Postion x, y, True
        '取消得到焦点的控件
        If Not Button_Click Then Set GetForceControl = Nothing
End Sub

Private Sub fraWindow_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
        If Button = vbLeftButton Then '调整控件的大小
           Control_Postion x, y, False
        End If
End Sub

Private Sub fraWindow_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
           Toolbar_Button_Unpressed False
           Control_Postion x, y, False
End Sub

Private Sub mnuOptionProperty_Click()
        mnuOptionProperty.Checked = Not mnuOptionProperty.Checked
        PicProperty.Visible = mnuOptionProperty.Checked
End Sub

Private Sub mnuOptionTool_Click()
        mnuOptionTool.Checked = Not mnuOptionTool.Checked
        PicTool.Visible = mnuOptionTool.Checked
End Sub

Private Function MouseChangeState(Object As Object, x As Single, y As Single, Optional Button As Integer) As Single
Dim k As Single, Pos As POINTAPI
    If Object Is GetForceControl Then
        If x <= 50 Or (x <= Object.Width And x >= Object.Width - 100) Then
           Object.MousePointer = vbSizeWE
           MouseChangeState = True
           If Button = vbLeftButton Then
              With Object
                   GetCursorPos Pos
                   k = .Width + Pos.x - MouseDownX
                   If k >= 0 Then
                      .Width = k
                      MouseDownX = Pos.x
                      Shape1.Width = Object.Width + 50
                   End If
              End With
           End If
        ElseIf y <= 50 Or (y <= Object.Height And y >= Object.Height - 100) Then
           Object.MousePointer = vbSizeNS
           MouseChangeState = True
           If Button = vbLeftButton Then
              With Object
                   GetCursorPos Pos
                   k = .Height + Pos.y - MouseDownY
                   If k >= 0 Then
                      .Height = k
                      MouseDownY = Pos.y
                      Shape1.Height = Object.Height - 50
                   End If
              End With
           End If
        Else
           Object.MousePointer = vbDefault
        End If
    Else
        Object.MousePointer = vbDefault
    End If
End Function

Private Sub Label1_Click(Index As Integer)
        Set GetForceControl = Label1(Index)
        Shape1.Top = Label1(Index).Top - 50
        Shape1.Left = Label1(Index).Left - 50
        Shape1.Width = Label1(Index).Width + 100
        Shape1.Height = Label1(Index).Height + 100
End Sub

Private Sub Label1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        MouseChangeState Label1(Index), x, y, Button
End Sub

Private Sub Label1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Pos As POINTAPI
        If Button = vbLeftButton Then
           GetCursorPos Pos
           MouseDownX = Pos.x
           MouseDownY = Pos.y
        End If
End Sub

Private Sub Text1_Click(Index As Integer)
        Set GetForceControl = Text1(Index)
        With Text1(Index)
             Shape1.Top = .Top - 50
             Shape1.Left = .Left - 50
             Shape1.Width = .Width + 100
             Shape1.Height = .Height + 100
        End With
End Sub

Private Sub Text1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Pos As POINTAPI
        If Button = vbLeftButton Then
           GetCursorPos Pos
           MouseDownX = Pos.x
           MouseDownY = Pos.y
        End If
End Sub

Private Sub Text1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        MouseChangeState Text1(Index), x, y, Button
End Sub

Private Sub List1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        MouseChangeState List1(Index), x, y, Button
End Sub

Private Sub List1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Pos As POINTAPI
        If Button = vbLeftButton Then
           Set GetForceControl = List1(Index)
           With List1(Index)
                Shape1.Top = .Top - 50
                Shape1.Left = .Left - 50
                Shape1.Width = .Width + 100
                Shape1.Height = .Height + 100
           End With
        End If
        If Button = vbLeftButton Then
           GetCursorPos Pos
           MouseDownX = Pos.x
           MouseDownY = Pos.y
        End If
End Sub
Private Sub Check1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        MouseChangeState Check1(Index), x, y, Button
End Sub
Private Sub Check1_Click(Index As Integer)
        Set GetForceControl = Check1(Index)
        With Check1(Index)
             Shape1.Top = .Top - 50
             Shape1.Left = .Left - 50
             Shape1.Width = .Width + 100
             Shape1.Height = .Height + 100
        End With
End Sub

Private Sub Check1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Pos As POINTAPI
        If Button = vbLeftButton Then
           GetCursorPos Pos
           MouseDownX = Pos.x
           MouseDownY = Pos.y
        End If
End Sub

Private Sub Option1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        MouseChangeState Option1(Index), x, y, Button
End Sub

Private Sub Option1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Pos As POINTAPI
        If Button = vbLeftButton Then
           GetCursorPos Pos
           MouseDownX = Pos.x
           MouseDownY = Pos.y
        End If
End Sub

Private Sub Option1_Click(Index As Integer)
        Set GetForceControl = Option1(Index)
        With Option1(Index)
             Shape1.Top = .Top - 50
             Shape1.Left = .Left - 50
             Shape1.Width = .Width + 100
             Shape1.Height = .Height + 100
        End With
End Sub

Private Sub Frame1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        MouseChangeState Frame1(Index), x, y, Button
End Sub

Private Sub Frame1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Pos As POINTAPI
        If Button = vbLeftButton Then
           GetCursorPos Pos
           MouseDownX = Pos.x
           MouseDownY = Pos.y
        End If
End Sub

Private Sub Frame1_Click(Index As Integer)
        Set GetForceControl = Frame1(Index)
        With Frame1(Index)
             Shape1.Top = .Top - 50
             Shape1.Left = .Left - 50
             Shape1.Width = .Width + 100
             Shape1.Height = .Height + 100
        End With
End Sub


Private Sub Command1_Click(Index As Integer)
        Set GetForceControl = Command1(Index)
        With Command1(Index)
             Shape1.Top = .Top - 50
             Shape1.Left = .Left - 50
             Shape1.Width = .Width + 100
             Shape1.Height = .Height + 100
        End With
End Sub

Private Sub Command1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        MouseChangeState Command1(Index), x, y, Button
End Sub

Private Sub Command1_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Pos As POINTAPI
        If Button = vbLeftButton Then
           GetCursorPos Pos
           MouseDownX = Pos.x
           MouseDownY = Pos.y
        End If
End Sub


