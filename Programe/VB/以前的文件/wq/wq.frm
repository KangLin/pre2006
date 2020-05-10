VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "围棋"
   ClientHeight    =   6510
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   9480
   FillStyle       =   0  'Solid
   ForeColor       =   &H00404040&
   Icon            =   "wq.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   6510
   ScaleWidth      =   9480
   StartUpPosition =   2  '屏幕中心
   Tag             =   "0"
   WindowState     =   2  'Maximized
   Begin VB.Frame Frame3 
      Height          =   2655
      Left            =   8040
      TabIndex        =   14
      Top             =   1320
      Width           =   1455
      Begin VB.CommandButton 悔棋 
         Caption         =   "悔棋"
         Height          =   375
         Left            =   720
         TabIndex        =   20
         Top             =   1680
         Width           =   615
      End
      Begin VB.CommandButton eat 
         Caption         =   "提子"
         Height          =   375
         Left            =   720
         TabIndex        =   19
         Top             =   720
         Width           =   615
      End
      Begin VB.CommandButton work 
         Caption         =   "走子"
         Height          =   375
         Left            =   720
         TabIndex        =   18
         Top             =   240
         Width           =   615
      End
      Begin VB.CommandButton 重新开始 
         Caption         =   "重新开始"
         Height          =   375
         Left            =   480
         TabIndex        =   17
         Top             =   2160
         Width           =   855
      End
      Begin VB.CommandButton 还原 
         Caption         =   "还原"
         Height          =   375
         Left            =   720
         TabIndex        =   16
         Top             =   1200
         Width           =   615
      End
      Begin VB.CommandButton 全局复盘 
         Caption         =   "全局复盘"
         Enabled         =   0   'False
         Height          =   375
         Left            =   480
         TabIndex        =   15
         Top             =   1680
         Visible         =   0   'False
         Width           =   855
      End
   End
   Begin VB.Frame Frame2 
      Height          =   2415
      Left            =   8040
      TabIndex        =   10
      Top             =   4080
      Width           =   1335
      Begin VB.PictureBox 提示图 
         AutoRedraw      =   -1  'True
         AutoSize        =   -1  'True
         BackColor       =   &H00FF0000&
         FillStyle       =   0  'Solid
         Height          =   1095
         Left            =   120
         ScaleHeight     =   1035
         ScaleWidth      =   1035
         TabIndex        =   11
         Top             =   720
         Width           =   1095
      End
      Begin VB.Label tishi 
         AutoSize        =   -1  'True
         Caption         =   "黑棋走"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   18
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   360
         Left            =   120
         TabIndex        =   13
         Top             =   2040
         Width           =   1080
      End
      Begin VB.Label tishi复盘 
         AutoSize        =   -1  'True
         Caption         =   "复盘"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   18
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   360
         Left            =   240
         TabIndex        =   12
         Top             =   240
         Visible         =   0   'False
         Width           =   720
      End
   End
   Begin VB.Frame Frame1 
      Height          =   1455
      Left            =   0
      TabIndex        =   3
      Top             =   4920
      Width           =   1935
      Begin VB.TextBox Text3 
         Enabled         =   0   'False
         Height          =   270
         Left            =   960
         TabIndex        =   9
         Text            =   "Text3"
         Top             =   240
         Width           =   855
      End
      Begin VB.TextBox Text2 
         Enabled         =   0   'False
         Height          =   270
         Left            =   960
         TabIndex        =   7
         Text            =   "text2"
         Top             =   600
         Width           =   855
      End
      Begin VB.TextBox Text1 
         Enabled         =   0   'False
         Height          =   270
         Left            =   960
         TabIndex        =   4
         Top             =   960
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "每手时间"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   735
      End
      Begin VB.Label Label3 
         Caption         =   "下棋时间"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   720
         Width           =   735
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "当前时间"
         Height          =   180
         Left            =   120
         TabIndex        =   5
         Top             =   1080
         Width           =   720
      End
   End
   Begin VB.Timer Timer1 
      Interval        =   60
      Left            =   480
      Top             =   2400
   End
   Begin VB.PictureBox wqpang 
      AutoRedraw      =   -1  'True
      BackColor       =   &H0080FFFF&
      FillColor       =   &H8000000C&
      FillStyle       =   0  'Solid
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   5.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   3720
      Left            =   2160
      MouseIcon       =   "wq.frx":0442
      MousePointer    =   99  'Custom
      ScaleHeight     =   3660
      ScaleWidth      =   3915
      TabIndex        =   0
      Top             =   2400
      Width           =   3975
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H8000000E&
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   240
      Left            =   7920
      TabIndex        =   2
      Top             =   240
      Width           =   720
   End
   Begin VB.Label qipaposx 
      AutoSize        =   -1  'True
      Caption         =   "   A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T "
      Height          =   180
      Left            =   1680
      TabIndex        =   1
      Top             =   2160
      Width           =   5580
   End
   Begin VB.Menu meunfile 
      Caption         =   "文件"
      Begin VB.Menu meunsave 
         Caption         =   "保存    (&S)"
      End
      Begin VB.Menu meunopen 
         Caption         =   "复盘    (&O)"
      End
      Begin VB.Menu installlast 
         Caption         =   "装入上盘棋"
      End
      Begin VB.Menu meun1 
         Caption         =   "-"
      End
      Begin VB.Menu meunexit 
         Caption         =   "退出    (&E)"
      End
   End
   Begin VB.Menu meundo 
      Caption         =   "动作"
      Begin VB.Menu meun悔棋 
         Caption         =   "悔棋    (&R)"
      End
      Begin VB.Menu meun还原 
         Caption         =   "还原    (&H)"
      End
      Begin VB.Menu meun提子 
         Caption         =   "提子    (&E)"
      End
      Begin VB.Menu meunwork 
         Caption         =   "走子    (&W)"
      End
      Begin VB.Menu restart 
         Caption         =   "重新开始(&S)"
      End
   End
   Begin VB.Menu meuntool 
      Caption         =   "选项"
      Begin VB.Menu meunmanandman 
         Caption         =   "人人对战"
         Checked         =   -1  'True
      End
      Begin VB.Menu meunmanandmachine 
         Caption         =   "人机对战"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunshow走棋步数 
         Caption         =   "显示走棋步数"
      End
      Begin VB.Menu mnutime 
         Caption         =   "显示时间"
         Checked         =   -1  'True
      End
      Begin VB.Menu showtool 
         Caption         =   "显示工具"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunhlep 
      Caption         =   "帮助"
      Begin VB.Menu meun内容 
         Caption         =   "内容    (&L)"
      End
      Begin VB.Menu meunabout 
         Caption         =   "关于    (&A)"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Const weiqistepmax = 1000
Dim 走棋步数(weiqistepmax) As Single
Dim 棋盘局式(19, 19) As Byte
Dim hadvisted(19, 19) As Byte
Dim 吃子标志 As Byte
Dim weiqistep As Single
Dim wqflag As Byte '为1时为白棋,2时为黑
Dim wqstartx As Integer
Dim wqstarty As Integer
Dim 棋盘距离 As Integer
Dim col As ColorConstants
Dim 被提子(500, 1) As Integer
Dim 被提子步数 As Integer
Dim show走棋步数 As Boolean
Dim show走棋步数1 As Boolean
Dim Tim As Date     '开始下棋时间
Dim OTim As Date '每手开始时间

Public Sub eat_Click()
    吃子标志 = 1
    提示
End Sub

Private Sub Form_Initialize()
Dim i
'wqpang.BackColor = &H80FFFF
wqpang.Top = 1000 'Form1.Height / 22 * 2
wqpang.Left = 2500 ' Form1.Width / 22 * 2
wqpang.Height = 5400 'Form1.Height / 22 * 20
wqpang.Width = 5400 ' Form1.Width / 22 * 20
If wqpang.Height < wqpang.Width Then
     棋盘距离 = wqpang.Height / 20
     wqstartx = wqpang.Height / 20
     wqstarty = wqpang.Height / 20
Else
     棋盘距离 = wqpang.Width / 20
End If
col = QBColor(9)
For i = 1 To 19
    If i = 1 Or i = 19 Then
             wqpang.DrawWidth = 4
    Else
             wqpang.DrawWidth = 2
    End If
    wqpang.Line (wqstartx + i * 棋盘距离, 棋盘距离 + wqstarty)-(wqstartx + i * 棋盘距离, wqstarty + 19 * 棋盘距离), col
    wqpang.Line (wqstartx + 棋盘距离, wqstarty + i * 棋盘距离)-(wqstartx + 19 * 棋盘距离, wqstarty + i * 棋盘距离), col
Next i
wqpang.DrawWidth = 4
wqpang.Circle (wqstartx + 4 * 棋盘距离, wqstarty + 4 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 10 * 棋盘距离, wqstarty + 4 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 16 * 棋盘距离, wqstarty + 4 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 4 * 棋盘距离, wqstarty + 10 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 10 * 棋盘距离, wqstarty + 10 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 16 * 棋盘距离, wqstarty + 10 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 4 * 棋盘距离, wqstarty + 16 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 10 * 棋盘距离, wqstarty + 16 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 16 * 棋盘距离, wqstarty + 16 * 棋盘距离), 棋盘距离 / 8, col
提示
End Sub

Private Sub Form_Load()
Dim i, j
Tim = Time
OTim = Tim
For i = 0 To 19
 For j = 0 To 19
 棋盘局式(i, j) = 0
 Next j
Next i
For i = 0 To weiqistepmax
    走棋步数(i) = 0
Next i
吃子标志 = 0
weiqistep = 0
wqflag = 2

'wqpang.BackColor = &H80FFFF
wqpang.Top = 1000 'Form1.Height / 22 * 2
wqpang.Left = 2500 ' Form1.Width / 22 * 2
wqpang.Height = 5400 'Form1.Height / 22 * 20
wqpang.Width = 5400 ' Form1.Width / 22 * 20
qipaposx.Top = wqpang.Top - qipaposx.Height
qipaposx.Width = wqpang.Width
qipaposx.Left = wqpang.Left
'qpposy.Top = wqpang.Top
'qpposy.Left = wqpang.Left - qpposy.Width
'qpposy.Height = wqpang.Height
If wqpang.Height < wqpang.Width Then
     棋盘距离 = wqpang.Height / 20
     wqstartx = wqpang.Height / 20
     wqstarty = wqpang.Height / 20
Else
     棋盘距离 = wqpang.Width / 20
End If
For i = 1 To 19
    Form1.CurrentX = wqpang.Left - 棋盘距离
    Form1.CurrentY = wqpang.Top + i * 棋盘距离 - 棋盘距离 / 4
    Print i
Next i
col = QBColor(9)
For i = 1 To 19
    If i = 1 Or i = 19 Then
             wqpang.DrawWidth = 4
    Else
             wqpang.DrawWidth = 2
    End If
    wqpang.Line (wqstartx + i * 棋盘距离, 棋盘距离 + wqstarty)-(wqstartx + i * 棋盘距离, wqstarty + 19 * 棋盘距离), col
    wqpang.Line (wqstartx + 棋盘距离, wqstarty + i * 棋盘距离)-(wqstartx + 19 * 棋盘距离, wqstarty + i * 棋盘距离), col
Next i
wqpang.DrawWidth = 4
wqpang.Circle (wqstartx + 4 * 棋盘距离, wqstarty + 4 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 10 * 棋盘距离, wqstarty + 4 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 16 * 棋盘距离, wqstarty + 4 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 4 * 棋盘距离, wqstarty + 10 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 10 * 棋盘距离, wqstarty + 10 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 16 * 棋盘距离, wqstarty + 10 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 4 * 棋盘距离, wqstarty + 16 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 10 * 棋盘距离, wqstarty + 16 * 棋盘距离), 棋盘距离 / 8, col
wqpang.Circle (wqstartx + 16 * 棋盘距离, wqstarty + 16 * 棋盘距离), 棋盘距离 / 8, col
提示
If Not (show走棋步数1) Then
   password    '密码
Else
   Form1.Tag = 0
   If show走棋步数 Then
      meunshow走棋步数.Checked = True
   Else
      meunshow走棋步数.Checked = False
   End If
End If
Dim d As Date
Dim d1 As Date
Dim dd
Dim dd1 As String
Open Form2.nam For Random As #1
Get #1, 2, d
Close #1
d1 = Date
dd = d1 - d
dd = 15 - dd
dd1 = dd
Label1.Caption = "你还能用" + dd1 + "天"
End Sub

Private Sub Form_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = VBRUN.vbRightButton Then
presswindows.Label7.Top = 0
presswindows.Top = Y + presswindows.Label7.Height
presswindows.Left = X
presswindows.Height = presswindows.Label7.Height
presswindows.Show
End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
If Form1.Tag <> 1 Then
   meunexit_Click
Else
   Form1.Tag = 0
   show走棋步数1 = True
End If
End Sub

Private Sub installlast_Click()
'        Unload Me
        复盘.Tag = 1
        meunopen_Click
   复盘.Caption = "装入上盘棋"
   复盘.Label4.Caption = "上盘棋"
End Sub

Private Sub meunabout_Click()
        帮助关于对话框.Show 1, Form1
End Sub

Public Sub meunexit_Click()
On Error Resume Next
 Dim exi
 If weiqistep >= 1 Then
exi = MsgBox("你要存盘吗?", vbYesNo + vbQuestion + vbDefaultButton1, "是否存盘")
If exi = vbYes Then
  meunsave_Click
End If
End If
Kill "save棋局"
Kill "weiqitiz.dat"
End
End Sub

Public Sub meunopen_Click()
Dim Y As String
If weiqistep <> 0 Then
If 复盘.Tag = 0 Then
  Y = MsgBox("你确实想复盘吗?", vbYesNo + vbQuestion + vbDefaultButton2, "是否复盘")
Else
  Y = MsgBox("你确实想装入上盘棋吗?", vbYesNo + vbQuestion + vbDefaultButton2, "是否装入上盘棋")
End If
  If Y = vbNo Then
   Exit Sub
   Else
    重新开始_Click
End If
End If
   复盘.Caption = "复盘"
   复盘.Label4.Caption = "复盘文件"
  复盘.Show
End Sub

Private Sub meunsave_Click()
  save棋局.Show 1, Form1
End Sub

Private Sub meunshow走棋步数_Click()
        If meunshow走棋步数.Checked Then
            meunshow走棋步数.Checked = False
            show走棋步数 = False
        Else
            meunshow走棋步数.Checked = True
            show走棋步数 = True
            wqflag = 2 '黑棋先走
            全局复盘_Click
        End If
End Sub

Private Sub meunwork_Click()
    work_Click
End Sub

Private Sub meun还原_Click()
RedoWeiqi
End Sub

Private Sub meun悔棋_Click()
     undoweiqi
End Sub

Private Sub meun内容_Click()
帮助关于对话框.Label1.Visible = False
帮助关于对话框.Label2.Visible = False
帮助关于对话框.Label3.Visible = False
帮助关于对话框.Label4.Visible = False
帮助关于对话框.Label5.Visible = False
帮助关于对话框.Label6.Visible = True
帮助关于对话框.Caption = "帮助内容"
帮助关于对话框.Show 1, Form1
帮助关于对话框.Label1.Visible = True
帮助关于对话框.Label2.Visible = True
帮助关于对话框.Label3.Visible = True
帮助关于对话框.Label4.Visible = True
帮助关于对话框.Label5.Visible = True
帮助关于对话框.Label6.Visible = False
帮助关于对话框.Caption = "版本信息"
End Sub

Private Sub meun提子_Click()
eat_Click
End Sub

Private Sub mnutime_Click()
        If mnutime.Checked Then
           mnutime.Checked = False
           Frame1.Visible = False
        Else
           mnutime.Checked = True
           Frame1.Visible = True
        End If
End Sub

Private Sub restart_Click()
    重新开始_Click
End Sub

Private Sub showtool_Click()
        If showtool.Checked Then
            showtool.Checked = False
            悔棋.Visible = False
            work.Visible = False
            还原.Visible = False
            eat.Visible = False
            重新开始.Visible = False
            Frame3.Visible = False
        Else
            Frame3.Visible = True
            showtool.Checked = True
            悔棋.Visible = True
            work.Visible = True
            还原.Visible = True
            eat.Visible = True
            重新开始.Visible = True
        End If
End Sub

Private Sub Timer1_Timer()
        Text1.Text = Format(Time, "hh:mm:ss")
        Text2.Text = Format(Time - Tim, "hh:mm:ss")
        '每手时间
        Text3.Text = Format(Time - OTim, "hh:mm:ss")
End Sub

Public Sub work_Click()
 吃子标志 = 0
 提示
End Sub

Private Sub wqpang_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim i, xx, yy, x0, y0
OTim = Time '初始化每手棋时间
wqpang.DrawWidth = 1
'If wqpang.Point(x, y) = QBColor(15) Or wqpang.Point(x, y) = QBColor(0) Then Beep: Exit Sub
If Button = VBRUN.MouseButtonConstants.vbLeftButton Then '下子
   '计算位置
   If (X - wqstartx) / 棋盘距离 - Int((X - wqstartx) / 棋盘距离) < 0.5 Then
       xx = Int((X - wqstartx) / 棋盘距离) * 棋盘距离 + wqstartx
       x0 = Int((X - wqstartx) / 棋盘距离)
        走棋步数(weiqistep) = Int((X - wqstartx) / 棋盘距离) * 100
       'Print weiqistep; 走棋步数(weiqistep)
   Else
       xx = Int((X - wqstartx) / 棋盘距离) * 棋盘距离 + 棋盘距离 + wqstartx
       走棋步数(weiqistep) = Int((X - wqstartx) / 棋盘距离 + 1) * 100
       x0 = Int((X - wqstartx) / 棋盘距离) + 1
       'Print weiqistep; 走棋步数(weiqistep)
   End If
   
   If (Y - wqstarty) / 棋盘距离 - Int((Y - wqstarty) / 棋盘距离) < 0.5 Then
          yy = Int((Y - wqstarty) / 棋盘距离) * 棋盘距离 + wqstarty
         走棋步数(weiqistep) = 走棋步数(weiqistep) + Int((Y - wqstarty) / 棋盘距离)
         y0 = Int((Y - wqstarty) / 棋盘距离)
        ' Print weiqistep; 走棋步数(weiqistep); "y0:"; y0
   Else
       yy = Int((Y - wqstarty) / 棋盘距离) * 棋盘距离 + wqstarty + 棋盘距离
        走棋步数(weiqistep) = 走棋步数(weiqistep) + Int((Y - wqstarty) / 棋盘距离) + 1
        y0 = Int((Y - wqstarty) / 棋盘距离) + 1
       'Print weiqistep; 走棋步数(weiqistep); "y0:"; y0
   End If
    
   '吃子
    If 吃子标志 = 1 Then
       wqpang.DrawWidth = 1
       wqpang.FillColor = wqpang.BackColor
       wqpang.Circle (xx, yy), 棋盘距离 / 2.1, wqpang.BackColor
       ClearWeiqiPang xx, yy, x0, y0
       棋盘局式(x0, y0) = 0 '无棋子
     
     Else
        If x0 > 19 Or x0 < 1 Or y0 > 19 Or y0 < 1 Then Beep: Exit Sub
        If 棋盘局式(x0, y0) = 1 Or 棋盘局式(x0, y0) = 2 Then Beep: Exit Sub
  
        '落子
        If wqflag = True Then  ' 当wqflag=ture时为白棋,否则为黑棋
           wqpang.FillColor = QBColor(15)
           wqpang.Circle (xx, yy), 棋盘距离 / 2.2, QBColor(15)
           棋盘局式(x0, y0) = 1 '白棋
          'Print 棋盘局式(x0, y0)
          wqflag = False
          'Print "w:"; wqflag
        Else
            wqpang.FillColor = QBColor(0)
            wqpang.Circle (xx, yy), 棋盘距离 / 2.2
            棋盘局式(x0, y0) = 2 '黑棋
            wqflag = True
            'Print "b:"; wqflag
        End If
        If meunshow走棋步数.Checked Then
           With wqpang
                .CurrentX = xx - 棋盘距离 / 1.5
                .CurrentY = yy - 棋盘距离 / 3
                wqpang.Print weiqistep
           End With
        End If
      End If

      围死提子 x0, y0

       weiqistep = weiqistep + 1
       If weiqistep = weiqistepmax + 1 Then ssave棋局: weiqistep = 0
End If

提示

If Button = VBRUN.vbRightButton Then '快捷菜单
   If Y < wqstarty + 4 * 棋盘距离 Then
      presswindows.Top = Y + Form1.wqpang.Top
   Else
      presswindows.Top = Y
   End If
      presswindows.presswin X, Y
End If
End Sub

Sub ClearWeiqiPang(X, Y, xx, yy)
    wqpang.DrawWidth = 2
    wqpang.Line (X - 棋盘距离 / 2, Y)-(X + 棋盘距离 / 2, Y), QBColor(9)
    wqpang.Line (X, Y - 棋盘距离 / 2)-(X, Y + 棋盘距离 / 2), QBColor(9)
    
    If xx = 4 And (yy = 4 Or yy = 10 Or yy = 16) Then
        wqpang.DrawWidth = 4
        wqpang.Circle (X, Y), 棋盘距离 / 8, col
    End If
    If xx = 10 And (yy = 4 Or yy = 10 Or yy = 16) Then
        wqpang.DrawWidth = 4
        wqpang.Circle (X, Y), 棋盘距离 / 8, col
    End If
    If xx = 16 And (yy = 4 Or yy = 10 Or yy = 16) Then
        wqpang.DrawWidth = 4
        wqpang.Circle (X, Y), 棋盘距离 / 8, col
    End If
    'Print "dis:"; 棋盘距离; "col:"; col
    
    If xx = 1 Then
       wqpang.DrawWidth = 4
       wqpang.Line (X, Y)-(X - 棋盘距离 / 2, Y), wqpang.BackColor
       If yy = 1 Then
          wqpang.Line (X, Y + 棋盘距离 / 2)-(X, Y), col
       Else
         If yy = 19 Then
            wqpang.Line (X, Y)-(X, Y - 棋盘距离 / 2), col
         Else
            wqpang.Line (X, Y + 棋盘距离 / 2)-(X, Y - 棋盘距离 / 2), col
         End If
       End If
    End If
    If xx = 19 Then
         wqpang.DrawWidth = 4
         wqpang.Line (X, Y)-(X + 棋盘距离 / 2, Y), wqpang.BackColor
       If yy = 1 Then
          wqpang.Line (X, Y + 棋盘距离 / 2)-(X, Y), col
       Else
         If yy = 19 Then
            wqpang.Line (X, Y)-(X, Y - 棋盘距离 / 2), col
         Else
            wqpang.Line (X, Y + 棋盘距离 / 2)-(X, Y - 棋盘距离 / 2), col
         End If
       End If
    End If
    If yy = 1 Then
       wqpang.DrawWidth = 4
            wqpang.Line (X, Y)-(X, Y - 棋盘距离 / 2), wqpang.BackColor
       If xx = 1 Then
            wqpang.Line (X + 棋盘距离 / 2, Y)-(X, Y), col
       Else
         If xx = 19 Then
            wqpang.Line (X - 棋盘距离 / 2, Y)-(X, Y), col
         Else
            wqpang.Line (X + 棋盘距离 / 2, Y)-(X - 棋盘距离 / 2, Y), col
         End If
       End If
    End If
    If yy = 19 Then
       wqpang.DrawWidth = 4
       wqpang.Line (X, Y)-(X, Y + 棋盘距离 / 2), wqpang.BackColor
       If xx = 1 Then
            wqpang.Line (X + 棋盘距离 / 2, Y)-(X, Y), col
       Else
         If xx = 19 Then
            wqpang.Line (X - 棋盘距离 / 2, Y)-(X, Y), col
         Else
            wqpang.Line (X + 棋盘距离 / 2, Y)-(X - 棋盘距离 / 2, Y), col
         End If
       End If
    End If

   End Sub
Private Sub 提示()
If 吃子标志 = 1 Then
   tishi.ForeColor = &HFF
   tishi.Caption = "提子"
   提示图.Visible = False
Else
  If wqflag = True Then
   tishi.ForeColor = QBColor(15)
   tishi.Caption = "白棋走"
   提示图.Visible = True
   '提示图.DrawWidth = 1
   提示图.FillColor = QBColor(15)
   提示图.Circle (提示图.Height / 2, 提示图.Height / 2), 提示图.Height / 3, QBColor(15)
  Else
   tishi.ForeColor = QBColor(0)
   tishi.Caption = "黑棋走"
   提示图.Visible = True
   '提示图.DrawWidth = 1
   提示图.FillColor = QBColor(0)
   提示图.Circle (提示图.Height / 2, 提示图.Height / 2), 提示图.Height / 3
  End If
End If
End Sub

Public Sub RedoWeiqi() '恢复棋子
Dim X, Y, xx, yy, pangduanflag
pangduanflag = 0
'Print weiqistep
'Print 走棋步数(weiqistep)
    If 走棋步数(weiqistep) = 0 Then Beep: Exit Sub
    X = Int(走棋步数(weiqistep) / 100)
    Y = 走棋步数(weiqistep) Mod 100
    xx = wqstartx + X * 棋盘距离
    yy = wqstarty + Y * 棋盘距离
    '落子
   If wqflag = True Then
      wqpang.FillColor = QBColor(15)
      wqpang.DrawWidth = 1
      wqpang.Circle (xx, yy), 棋盘距离 / 2.2, QBColor(15)
      棋盘局式(X, Y) = 1 '白棋
      'Print 棋盘局式(x0, y0)
      wqflag = False
      'Print "w:"; wqflag
   Else
      wqpang.FillColor = QBColor(0)
      wqpang.DrawWidth = 1
      wqpang.Circle (xx, yy), 棋盘距离 / 2.2
      棋盘局式(X, Y) = 2 '黑棋
      wqflag = True
      'Print "b:"; wqflag
   End If
   
   围死提子 X, Y
   weiqistep = weiqistep + 1
   提示
End Sub

Private Sub undoweiqi() '取消
    Dim X, Y, xx, yy
    weiqistep = weiqistep - 1
    If weiqistep < 0 Then weiqistep = 0: Beep: Exit Sub
    X = Int(走棋步数(weiqistep) / 100)
    Y = 走棋步数(weiqistep) Mod 100
    棋盘局式(X, Y) = 0
    xx = wqstartx + X * 棋盘距离
    yy = wqstarty + Y * 棋盘距离
      wqpang.FillColor = wqpang.BackColor
      wqpang.Circle (xx, yy), 棋盘距离 / 2.2, wqpang.BackColor
      ClearWeiqiPang xx, yy, X, Y
    If wqflag = False Then  '重设围标志
       wqflag = True
    Else
       wqflag = False
    End If
    '恢复被提的子
    If 被提子步数 - 1 >= 0 Then
    If 被提子(被提子步数 - 1, 0) = weiqistep Then
       被提子步数 = 被提子步数 - 1
       undo被提子
    End If
    End If
    提示
End Sub

Private Sub undo被提子()
'存在的问题是:
'当自己填死自己时悔棋不能正确处理
   Dim i, j, a, X, Y, xx, yy
   Open "weiqitiz.dat" For Input As #1
   Open "weiqitiz.daf" For Output As #2
   For i = 0 To 被提子步数 - 1
       For j = 1 To 被提子(i, 1)
           Input #1, a
           Print #2, a
       Next j
   Next i
   For j = 1 To 被提子(被提子步数, 1)
       '恢复被提子
       Input #1, a
        X = a \ 100 Mod 100
        Y = a Mod 100
        xx = wqstartx + X * 棋盘距离
        yy = wqstarty + Y * 棋盘距离
        Select Case a \ 10000
          Case 1
            wqpang.DrawWidth = 1
            wqpang.FillColor = QBColor(15)
            wqpang.Circle (xx, yy), 棋盘距离 / 2.2, QBColor(15)
            棋盘局式(X, Y) = 1 '白棋
          Case 2
           wqpang.DrawWidth = 1
           wqpang.FillColor = QBColor(0)
           wqpang.Circle (xx, yy), 棋盘距离 / 2.2
           棋盘局式(X, Y) = 2 '黑棋
        End Select
   Next j
   Close #1
   Close #2
   If a \ 10000 = 1 And wqflag = True Or (a \ 10000 = 2 _
   And wqflag = False) Then
      wqpang.DrawWidth = 1
      wqpang.FillColor = wqpang.BackColor
      wqpang.Circle (xx, yy), 棋盘距离 / 2.2, wqpang.BackColor
      ClearWeiqiPang xx, yy, X, Y
      棋盘局式(X, Y) = 0
   End If
  FileCopy "weiqitiz.daf", "weiqitiz.dat"
  Kill "weiqitiz.daf"
End Sub

Private Sub 判断是否围死(X, Y, flag, fflag)
On Error Resume Next
If flag = 1 Then Exit Sub
hadvisted(X, Y) = 1
'Form1.Cls
'Form1.CurrentX = 8
'Form1.CurrentY = 1
'Print "x="; X; "y="; Y; hadvisted(X, Y)
If Y - 1 > 0 Then
If fflag <> 2 And hadvisted(X, Y - 1) <> 1 Then
   Select Case 棋盘局式(X, Y - 1)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
'       Print 棋盘局式(X, Y); "y-1"
            判断是否围死 X, Y - 1, flag, 1
            If flag = 1 Then Exit Sub
   End Select
End If
End If

If Y + 1 < 20 Then
If fflag <> 1 And hadvisted(X, Y + 1) <> 1 Then
   Select Case 棋盘局式(X, Y + 1)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
 '      Print 棋盘局式(X, Y); "y+1"
               判断是否围死 X, Y + 1, flag, 2
               If flag = 1 Then Exit Sub
   End Select
End If
End If

If X - 1 > 0 Then
If fflag <> 4 And hadvisted(X - 1, Y) <> 1 Then
   Select Case 棋盘局式(X - 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
  '          Print 棋盘局式(X, Y); "x-1"
                 判断是否围死 X - 1, Y, flag, 3
                 If flag = 1 Then Exit Sub
   End Select
End If
End If

If X + 1 < 20 Then
If fflag <> 3 And hadvisted(X + 1, Y) <> 1 Then
   Select Case 棋盘局式(X + 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
   '    Print 棋盘局式(X, Y); "x+1"
            判断是否围死 X + 1, Y, flag, 4
If flag = 1 Then Exit Sub
   End Select
End If
End If
If 棋盘局式(X, Y) = 0 Then flag = 1
End Sub

Private Sub 围死eat(X, Y, flag, fflag, num)
'num为悔棋时,记录被提的子的个数
On Error Resume Next
Dim xx, yy
hadvisted(X, Y) = 1
 If Y - 1 > 0 Then
 If fflag <> 2 And hadvisted(X, Y - 1) <> 1 Then
   Select Case 棋盘局式(X, Y - 1)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
'       Print 棋盘局式(X, Y); "y-1"
            围死eat X, Y - 1, flag, 1, num
   End Select
End If
End If

If Y + 1 < 20 Then
If fflag <> 1 And hadvisted(X, Y + 1) <> 1 Then
   Select Case 棋盘局式(X, Y + 1)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
 '      Print 棋盘局式(X, Y); "y+1"
            围死eat X, Y + 1, flag, 2, num
   End Select
End If
End If

If X - 1 > 0 Then
If fflag <> 4 And hadvisted(X - 1, Y) <> 1 Then
   Select Case 棋盘局式(X - 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
  '          Print 棋盘局式(X, Y); "x-1"
             围死eat X - 1, Y, flag, 3, num
   End Select
   End If
End If

If X + 1 < 20 Then
If fflag <> 3 And hadvisted(X + 1, Y) <> 1 Then
   Select Case 棋盘局式(X + 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case 棋盘局式(X, Y)
   '    Print 棋盘局式(X, Y); "x+1"
            围死eat X + 1, Y, flag, 4, num
   End Select
End If
End If
    xx = wqstartx + X * 棋盘距离
    yy = wqstarty + Y * 棋盘距离
      wqpang.FillColor = wqpang.BackColor
      wqpang.Circle (xx, yy), 棋盘距离 / 2.2, wqpang.BackColor
      ClearWeiqiPang xx, yy, X, Y
      'num为悔棋时,记录被提的子的个数
      num = num + 1
      '被提子记录在文件weiqitiz.dat 中
      Open "weiqitiz.dat" For Append As #1
      Print #1, 棋盘局式(X, Y) * 10000 + X * 100 + Y
      Close #1
      棋盘局式(X, Y) = 0
End Sub

Private Sub 围死提子(X, Y)
Dim flag, i, j, numbel 'numbel为此次被提子数
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If X - 1 > 0 Then
判断是否围死 X - 1, Y, flag, 0
'Print flag
If flag = 0 And 棋盘局式(X, Y) <> 棋盘局式(X - 1, Y) Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
围死eat X - 1, Y, flag, 0, numbel
被提子(被提子步数, 0) = weiqistep '被提子所在步数
被提子(被提子步数, 1) = numbel '被提子的个数
被提子步数 = 被提子步数 + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If X + 1 < 20 Then
判断是否围死 X + 1, Y, flag, 0
'Print flag
If flag = 0 And 棋盘局式(X, Y) <> 棋盘局式(X + 1, Y) Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
围死eat X + 1, Y, flag, 0, numbel
被提子(被提子步数, 0) = weiqistep
被提子(被提子步数, 1) = numbel
被提子步数 = 被提子步数 + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If Y + 1 < 20 Then
判断是否围死 X, Y + 1, flag, 0
'Print flag
If 棋盘局式(X, Y) <> 棋盘局式(X, 1 + Y) And flag = 0 Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
围死eat X, Y + 1, flag, 0, numbel
被提子(被提子步数, 0) = weiqistep
被提子(被提子步数, 1) = numbel
被提子步数 = 被提子步数 + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If Y - 1 > 0 Then
判断是否围死 X, Y - 1, flag, 0
'Print flag
If 棋盘局式(X, Y) <> 棋盘局式(X, Y - 1) And flag = 0 Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
围死eat X, Y - 1, flag, 0, numbel
被提子(被提子步数, 0) = weiqistep '被提子所在步数
被提子(被提子步数, 1) = numbel   '被提子的个数
被提子步数 = 被提子步数 + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
判断是否围死 X, Y, flag, 0
'Print flag
If flag = 0 Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
围死eat X, Y, flag, 0, numbel
被提子(被提子步数, 0) = weiqistep
被提子(被提子步数, 1) = numbel
被提子步数 = 被提子步数 + 1
End If
End Sub
Private Sub 还原_Click()
RedoWeiqi
End Sub

Public Sub 悔棋_Click()
undoweiqi
End Sub

Public Sub 全局复盘_Click()
     'wqpang.ForeColor = QBColor(9)
     weiqistep = 0
     Do
       RedoWeiqi
       weiqistep = weiqistep - 1
       If weiqistep < 0 Then Exit Sub
       wqpang.CurrentX = (走棋步数(weiqistep) _
                        \ 100) * 棋盘距离 + wqstartx - 棋盘距离 / 1.5
       wqpang.CurrentY = (走棋步数(weiqistep) _
                         Mod 100) * 棋盘距离 + wqstarty - 棋盘距离 / 3
       weiqistep = weiqistep + 1
       If show走棋步数 Then
            wqpang.Print weiqistep
       End If
     Loop Until 走棋步数(weiqistep) = 0
End Sub

Public Sub 重新开始_Click()
Form1.Tag = 1
    Unload Me
    Form1.Show
End Sub
Public Sub openfile()
     Dim i
     On Error Resume Next
     FileCopy "save棋局", save棋局.Text1.Text
     If Dir("save棋局", vbNormal) <> "" Then
     Open save棋局.Text1.Text For Append As #1
     Else
     Open save棋局.Text1.Text For Output As #1
     End If
     Do
       Print #1, 走棋步数(i)
       i = i + 1
     Loop Until 走棋步数(i) = 0
     Close #1
End Sub

Public Sub open复盘()
     Dim i
     i = 0
     On Error Resume Next
     Open 复盘.Text1.Text For Input As #1
    Do
    Input #1, 走棋步数(i)
       i = i + 1
    Loop Until EOF(1)
     Close #1
     走棋步数(i) = 0 'end flag
End Sub

 Sub ssave棋局()
 On Error Resume Next
 Dim i
 Open "save棋局" For Output As #1
 Do
   Print #1, 走棋步数(i)
   i = i + 1
 Loop While i > weiqistepmax
 Close #1
 End Sub

Sub password()
Dim pass As String
   pass = InputBox("请输入密码:", "密码")
   If pass = "kanglinweiqi2001" Then
   Else
     End
   End If
End Sub

