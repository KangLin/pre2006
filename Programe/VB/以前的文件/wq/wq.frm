VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Χ��"
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
   StartUpPosition =   2  '��Ļ����
   Tag             =   "0"
   WindowState     =   2  'Maximized
   Begin VB.Frame Frame3 
      Height          =   2655
      Left            =   8040
      TabIndex        =   14
      Top             =   1320
      Width           =   1455
      Begin VB.CommandButton ���� 
         Caption         =   "����"
         Height          =   375
         Left            =   720
         TabIndex        =   20
         Top             =   1680
         Width           =   615
      End
      Begin VB.CommandButton eat 
         Caption         =   "����"
         Height          =   375
         Left            =   720
         TabIndex        =   19
         Top             =   720
         Width           =   615
      End
      Begin VB.CommandButton work 
         Caption         =   "����"
         Height          =   375
         Left            =   720
         TabIndex        =   18
         Top             =   240
         Width           =   615
      End
      Begin VB.CommandButton ���¿�ʼ 
         Caption         =   "���¿�ʼ"
         Height          =   375
         Left            =   480
         TabIndex        =   17
         Top             =   2160
         Width           =   855
      End
      Begin VB.CommandButton ��ԭ 
         Caption         =   "��ԭ"
         Height          =   375
         Left            =   720
         TabIndex        =   16
         Top             =   1200
         Width           =   615
      End
      Begin VB.CommandButton ȫ�ָ��� 
         Caption         =   "ȫ�ָ���"
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
      Begin VB.PictureBox ��ʾͼ 
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
         Caption         =   "������"
         BeginProperty Font 
            Name            =   "����"
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
      Begin VB.Label tishi���� 
         AutoSize        =   -1  'True
         Caption         =   "����"
         BeginProperty Font 
            Name            =   "����"
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
         Caption         =   "ÿ��ʱ��"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   735
      End
      Begin VB.Label Label3 
         Caption         =   "����ʱ��"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   720
         Width           =   735
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "��ǰʱ��"
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
         Name            =   "����"
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
         Name            =   "����"
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
      Caption         =   "�ļ�"
      Begin VB.Menu meunsave 
         Caption         =   "����    (&S)"
      End
      Begin VB.Menu meunopen 
         Caption         =   "����    (&O)"
      End
      Begin VB.Menu installlast 
         Caption         =   "װ��������"
      End
      Begin VB.Menu meun1 
         Caption         =   "-"
      End
      Begin VB.Menu meunexit 
         Caption         =   "�˳�    (&E)"
      End
   End
   Begin VB.Menu meundo 
      Caption         =   "����"
      Begin VB.Menu meun���� 
         Caption         =   "����    (&R)"
      End
      Begin VB.Menu meun��ԭ 
         Caption         =   "��ԭ    (&H)"
      End
      Begin VB.Menu meun���� 
         Caption         =   "����    (&E)"
      End
      Begin VB.Menu meunwork 
         Caption         =   "����    (&W)"
      End
      Begin VB.Menu restart 
         Caption         =   "���¿�ʼ(&S)"
      End
   End
   Begin VB.Menu meuntool 
      Caption         =   "ѡ��"
      Begin VB.Menu meunmanandman 
         Caption         =   "���˶�ս"
         Checked         =   -1  'True
      End
      Begin VB.Menu meunmanandmachine 
         Caption         =   "�˻���ս"
         Enabled         =   0   'False
      End
      Begin VB.Menu meunshow���岽�� 
         Caption         =   "��ʾ���岽��"
      End
      Begin VB.Menu mnutime 
         Caption         =   "��ʾʱ��"
         Checked         =   -1  'True
      End
      Begin VB.Menu showtool 
         Caption         =   "��ʾ����"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu meunhlep 
      Caption         =   "����"
      Begin VB.Menu meun���� 
         Caption         =   "����    (&L)"
      End
      Begin VB.Menu meunabout 
         Caption         =   "����    (&A)"
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
Dim ���岽��(weiqistepmax) As Single
Dim ���̾�ʽ(19, 19) As Byte
Dim hadvisted(19, 19) As Byte
Dim ���ӱ�־ As Byte
Dim weiqistep As Single
Dim wqflag As Byte 'Ϊ1ʱΪ����,2ʱΪ��
Dim wqstartx As Integer
Dim wqstarty As Integer
Dim ���̾��� As Integer
Dim col As ColorConstants
Dim ������(500, 1) As Integer
Dim �����Ӳ��� As Integer
Dim show���岽�� As Boolean
Dim show���岽��1 As Boolean
Dim Tim As Date     '��ʼ����ʱ��
Dim OTim As Date 'ÿ�ֿ�ʼʱ��

Public Sub eat_Click()
    ���ӱ�־ = 1
    ��ʾ
End Sub

Private Sub Form_Initialize()
Dim i
'wqpang.BackColor = &H80FFFF
wqpang.Top = 1000 'Form1.Height / 22 * 2
wqpang.Left = 2500 ' Form1.Width / 22 * 2
wqpang.Height = 5400 'Form1.Height / 22 * 20
wqpang.Width = 5400 ' Form1.Width / 22 * 20
If wqpang.Height < wqpang.Width Then
     ���̾��� = wqpang.Height / 20
     wqstartx = wqpang.Height / 20
     wqstarty = wqpang.Height / 20
Else
     ���̾��� = wqpang.Width / 20
End If
col = QBColor(9)
For i = 1 To 19
    If i = 1 Or i = 19 Then
             wqpang.DrawWidth = 4
    Else
             wqpang.DrawWidth = 2
    End If
    wqpang.Line (wqstartx + i * ���̾���, ���̾��� + wqstarty)-(wqstartx + i * ���̾���, wqstarty + 19 * ���̾���), col
    wqpang.Line (wqstartx + ���̾���, wqstarty + i * ���̾���)-(wqstartx + 19 * ���̾���, wqstarty + i * ���̾���), col
Next i
wqpang.DrawWidth = 4
wqpang.Circle (wqstartx + 4 * ���̾���, wqstarty + 4 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 10 * ���̾���, wqstarty + 4 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 16 * ���̾���, wqstarty + 4 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 4 * ���̾���, wqstarty + 10 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 10 * ���̾���, wqstarty + 10 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 16 * ���̾���, wqstarty + 10 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 4 * ���̾���, wqstarty + 16 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 10 * ���̾���, wqstarty + 16 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 16 * ���̾���, wqstarty + 16 * ���̾���), ���̾��� / 8, col
��ʾ
End Sub

Private Sub Form_Load()
Dim i, j
Tim = Time
OTim = Tim
For i = 0 To 19
 For j = 0 To 19
 ���̾�ʽ(i, j) = 0
 Next j
Next i
For i = 0 To weiqistepmax
    ���岽��(i) = 0
Next i
���ӱ�־ = 0
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
     ���̾��� = wqpang.Height / 20
     wqstartx = wqpang.Height / 20
     wqstarty = wqpang.Height / 20
Else
     ���̾��� = wqpang.Width / 20
End If
For i = 1 To 19
    Form1.CurrentX = wqpang.Left - ���̾���
    Form1.CurrentY = wqpang.Top + i * ���̾��� - ���̾��� / 4
    Print i
Next i
col = QBColor(9)
For i = 1 To 19
    If i = 1 Or i = 19 Then
             wqpang.DrawWidth = 4
    Else
             wqpang.DrawWidth = 2
    End If
    wqpang.Line (wqstartx + i * ���̾���, ���̾��� + wqstarty)-(wqstartx + i * ���̾���, wqstarty + 19 * ���̾���), col
    wqpang.Line (wqstartx + ���̾���, wqstarty + i * ���̾���)-(wqstartx + 19 * ���̾���, wqstarty + i * ���̾���), col
Next i
wqpang.DrawWidth = 4
wqpang.Circle (wqstartx + 4 * ���̾���, wqstarty + 4 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 10 * ���̾���, wqstarty + 4 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 16 * ���̾���, wqstarty + 4 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 4 * ���̾���, wqstarty + 10 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 10 * ���̾���, wqstarty + 10 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 16 * ���̾���, wqstarty + 10 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 4 * ���̾���, wqstarty + 16 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 10 * ���̾���, wqstarty + 16 * ���̾���), ���̾��� / 8, col
wqpang.Circle (wqstartx + 16 * ���̾���, wqstarty + 16 * ���̾���), ���̾��� / 8, col
��ʾ
If Not (show���岽��1) Then
   password    '����
Else
   Form1.Tag = 0
   If show���岽�� Then
      meunshow���岽��.Checked = True
   Else
      meunshow���岽��.Checked = False
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
Label1.Caption = "�㻹����" + dd1 + "��"
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
   show���岽��1 = True
End If
End Sub

Private Sub installlast_Click()
'        Unload Me
        ����.Tag = 1
        meunopen_Click
   ����.Caption = "װ��������"
   ����.Label4.Caption = "������"
End Sub

Private Sub meunabout_Click()
        �������ڶԻ���.Show 1, Form1
End Sub

Public Sub meunexit_Click()
On Error Resume Next
 Dim exi
 If weiqistep >= 1 Then
exi = MsgBox("��Ҫ������?", vbYesNo + vbQuestion + vbDefaultButton1, "�Ƿ����")
If exi = vbYes Then
  meunsave_Click
End If
End If
Kill "save���"
Kill "weiqitiz.dat"
End
End Sub

Public Sub meunopen_Click()
Dim Y As String
If weiqistep <> 0 Then
If ����.Tag = 0 Then
  Y = MsgBox("��ȷʵ�븴����?", vbYesNo + vbQuestion + vbDefaultButton2, "�Ƿ���")
Else
  Y = MsgBox("��ȷʵ��װ����������?", vbYesNo + vbQuestion + vbDefaultButton2, "�Ƿ�װ��������")
End If
  If Y = vbNo Then
   Exit Sub
   Else
    ���¿�ʼ_Click
End If
End If
   ����.Caption = "����"
   ����.Label4.Caption = "�����ļ�"
  ����.Show
End Sub

Private Sub meunsave_Click()
  save���.Show 1, Form1
End Sub

Private Sub meunshow���岽��_Click()
        If meunshow���岽��.Checked Then
            meunshow���岽��.Checked = False
            show���岽�� = False
        Else
            meunshow���岽��.Checked = True
            show���岽�� = True
            wqflag = 2 '��������
            ȫ�ָ���_Click
        End If
End Sub

Private Sub meunwork_Click()
    work_Click
End Sub

Private Sub meun��ԭ_Click()
RedoWeiqi
End Sub

Private Sub meun����_Click()
     undoweiqi
End Sub

Private Sub meun����_Click()
�������ڶԻ���.Label1.Visible = False
�������ڶԻ���.Label2.Visible = False
�������ڶԻ���.Label3.Visible = False
�������ڶԻ���.Label4.Visible = False
�������ڶԻ���.Label5.Visible = False
�������ڶԻ���.Label6.Visible = True
�������ڶԻ���.Caption = "��������"
�������ڶԻ���.Show 1, Form1
�������ڶԻ���.Label1.Visible = True
�������ڶԻ���.Label2.Visible = True
�������ڶԻ���.Label3.Visible = True
�������ڶԻ���.Label4.Visible = True
�������ڶԻ���.Label5.Visible = True
�������ڶԻ���.Label6.Visible = False
�������ڶԻ���.Caption = "�汾��Ϣ"
End Sub

Private Sub meun����_Click()
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
    ���¿�ʼ_Click
End Sub

Private Sub showtool_Click()
        If showtool.Checked Then
            showtool.Checked = False
            ����.Visible = False
            work.Visible = False
            ��ԭ.Visible = False
            eat.Visible = False
            ���¿�ʼ.Visible = False
            Frame3.Visible = False
        Else
            Frame3.Visible = True
            showtool.Checked = True
            ����.Visible = True
            work.Visible = True
            ��ԭ.Visible = True
            eat.Visible = True
            ���¿�ʼ.Visible = True
        End If
End Sub

Private Sub Timer1_Timer()
        Text1.Text = Format(Time, "hh:mm:ss")
        Text2.Text = Format(Time - Tim, "hh:mm:ss")
        'ÿ��ʱ��
        Text3.Text = Format(Time - OTim, "hh:mm:ss")
End Sub

Public Sub work_Click()
 ���ӱ�־ = 0
 ��ʾ
End Sub

Private Sub wqpang_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim i, xx, yy, x0, y0
OTim = Time '��ʼ��ÿ����ʱ��
wqpang.DrawWidth = 1
'If wqpang.Point(x, y) = QBColor(15) Or wqpang.Point(x, y) = QBColor(0) Then Beep: Exit Sub
If Button = VBRUN.MouseButtonConstants.vbLeftButton Then '����
   '����λ��
   If (X - wqstartx) / ���̾��� - Int((X - wqstartx) / ���̾���) < 0.5 Then
       xx = Int((X - wqstartx) / ���̾���) * ���̾��� + wqstartx
       x0 = Int((X - wqstartx) / ���̾���)
        ���岽��(weiqistep) = Int((X - wqstartx) / ���̾���) * 100
       'Print weiqistep; ���岽��(weiqistep)
   Else
       xx = Int((X - wqstartx) / ���̾���) * ���̾��� + ���̾��� + wqstartx
       ���岽��(weiqistep) = Int((X - wqstartx) / ���̾��� + 1) * 100
       x0 = Int((X - wqstartx) / ���̾���) + 1
       'Print weiqistep; ���岽��(weiqistep)
   End If
   
   If (Y - wqstarty) / ���̾��� - Int((Y - wqstarty) / ���̾���) < 0.5 Then
          yy = Int((Y - wqstarty) / ���̾���) * ���̾��� + wqstarty
         ���岽��(weiqistep) = ���岽��(weiqistep) + Int((Y - wqstarty) / ���̾���)
         y0 = Int((Y - wqstarty) / ���̾���)
        ' Print weiqistep; ���岽��(weiqistep); "y0:"; y0
   Else
       yy = Int((Y - wqstarty) / ���̾���) * ���̾��� + wqstarty + ���̾���
        ���岽��(weiqistep) = ���岽��(weiqistep) + Int((Y - wqstarty) / ���̾���) + 1
        y0 = Int((Y - wqstarty) / ���̾���) + 1
       'Print weiqistep; ���岽��(weiqistep); "y0:"; y0
   End If
    
   '����
    If ���ӱ�־ = 1 Then
       wqpang.DrawWidth = 1
       wqpang.FillColor = wqpang.BackColor
       wqpang.Circle (xx, yy), ���̾��� / 2.1, wqpang.BackColor
       ClearWeiqiPang xx, yy, x0, y0
       ���̾�ʽ(x0, y0) = 0 '������
     
     Else
        If x0 > 19 Or x0 < 1 Or y0 > 19 Or y0 < 1 Then Beep: Exit Sub
        If ���̾�ʽ(x0, y0) = 1 Or ���̾�ʽ(x0, y0) = 2 Then Beep: Exit Sub
  
        '����
        If wqflag = True Then  ' ��wqflag=tureʱΪ����,����Ϊ����
           wqpang.FillColor = QBColor(15)
           wqpang.Circle (xx, yy), ���̾��� / 2.2, QBColor(15)
           ���̾�ʽ(x0, y0) = 1 '����
          'Print ���̾�ʽ(x0, y0)
          wqflag = False
          'Print "w:"; wqflag
        Else
            wqpang.FillColor = QBColor(0)
            wqpang.Circle (xx, yy), ���̾��� / 2.2
            ���̾�ʽ(x0, y0) = 2 '����
            wqflag = True
            'Print "b:"; wqflag
        End If
        If meunshow���岽��.Checked Then
           With wqpang
                .CurrentX = xx - ���̾��� / 1.5
                .CurrentY = yy - ���̾��� / 3
                wqpang.Print weiqistep
           End With
        End If
      End If

      Χ������ x0, y0

       weiqistep = weiqistep + 1
       If weiqistep = weiqistepmax + 1 Then ssave���: weiqistep = 0
End If

��ʾ

If Button = VBRUN.vbRightButton Then '��ݲ˵�
   If Y < wqstarty + 4 * ���̾��� Then
      presswindows.Top = Y + Form1.wqpang.Top
   Else
      presswindows.Top = Y
   End If
      presswindows.presswin X, Y
End If
End Sub

Sub ClearWeiqiPang(X, Y, xx, yy)
    wqpang.DrawWidth = 2
    wqpang.Line (X - ���̾��� / 2, Y)-(X + ���̾��� / 2, Y), QBColor(9)
    wqpang.Line (X, Y - ���̾��� / 2)-(X, Y + ���̾��� / 2), QBColor(9)
    
    If xx = 4 And (yy = 4 Or yy = 10 Or yy = 16) Then
        wqpang.DrawWidth = 4
        wqpang.Circle (X, Y), ���̾��� / 8, col
    End If
    If xx = 10 And (yy = 4 Or yy = 10 Or yy = 16) Then
        wqpang.DrawWidth = 4
        wqpang.Circle (X, Y), ���̾��� / 8, col
    End If
    If xx = 16 And (yy = 4 Or yy = 10 Or yy = 16) Then
        wqpang.DrawWidth = 4
        wqpang.Circle (X, Y), ���̾��� / 8, col
    End If
    'Print "dis:"; ���̾���; "col:"; col
    
    If xx = 1 Then
       wqpang.DrawWidth = 4
       wqpang.Line (X, Y)-(X - ���̾��� / 2, Y), wqpang.BackColor
       If yy = 1 Then
          wqpang.Line (X, Y + ���̾��� / 2)-(X, Y), col
       Else
         If yy = 19 Then
            wqpang.Line (X, Y)-(X, Y - ���̾��� / 2), col
         Else
            wqpang.Line (X, Y + ���̾��� / 2)-(X, Y - ���̾��� / 2), col
         End If
       End If
    End If
    If xx = 19 Then
         wqpang.DrawWidth = 4
         wqpang.Line (X, Y)-(X + ���̾��� / 2, Y), wqpang.BackColor
       If yy = 1 Then
          wqpang.Line (X, Y + ���̾��� / 2)-(X, Y), col
       Else
         If yy = 19 Then
            wqpang.Line (X, Y)-(X, Y - ���̾��� / 2), col
         Else
            wqpang.Line (X, Y + ���̾��� / 2)-(X, Y - ���̾��� / 2), col
         End If
       End If
    End If
    If yy = 1 Then
       wqpang.DrawWidth = 4
            wqpang.Line (X, Y)-(X, Y - ���̾��� / 2), wqpang.BackColor
       If xx = 1 Then
            wqpang.Line (X + ���̾��� / 2, Y)-(X, Y), col
       Else
         If xx = 19 Then
            wqpang.Line (X - ���̾��� / 2, Y)-(X, Y), col
         Else
            wqpang.Line (X + ���̾��� / 2, Y)-(X - ���̾��� / 2, Y), col
         End If
       End If
    End If
    If yy = 19 Then
       wqpang.DrawWidth = 4
       wqpang.Line (X, Y)-(X, Y + ���̾��� / 2), wqpang.BackColor
       If xx = 1 Then
            wqpang.Line (X + ���̾��� / 2, Y)-(X, Y), col
       Else
         If xx = 19 Then
            wqpang.Line (X - ���̾��� / 2, Y)-(X, Y), col
         Else
            wqpang.Line (X + ���̾��� / 2, Y)-(X - ���̾��� / 2, Y), col
         End If
       End If
    End If

   End Sub
Private Sub ��ʾ()
If ���ӱ�־ = 1 Then
   tishi.ForeColor = &HFF
   tishi.Caption = "����"
   ��ʾͼ.Visible = False
Else
  If wqflag = True Then
   tishi.ForeColor = QBColor(15)
   tishi.Caption = "������"
   ��ʾͼ.Visible = True
   '��ʾͼ.DrawWidth = 1
   ��ʾͼ.FillColor = QBColor(15)
   ��ʾͼ.Circle (��ʾͼ.Height / 2, ��ʾͼ.Height / 2), ��ʾͼ.Height / 3, QBColor(15)
  Else
   tishi.ForeColor = QBColor(0)
   tishi.Caption = "������"
   ��ʾͼ.Visible = True
   '��ʾͼ.DrawWidth = 1
   ��ʾͼ.FillColor = QBColor(0)
   ��ʾͼ.Circle (��ʾͼ.Height / 2, ��ʾͼ.Height / 2), ��ʾͼ.Height / 3
  End If
End If
End Sub

Public Sub RedoWeiqi() '�ָ�����
Dim X, Y, xx, yy, pangduanflag
pangduanflag = 0
'Print weiqistep
'Print ���岽��(weiqistep)
    If ���岽��(weiqistep) = 0 Then Beep: Exit Sub
    X = Int(���岽��(weiqistep) / 100)
    Y = ���岽��(weiqistep) Mod 100
    xx = wqstartx + X * ���̾���
    yy = wqstarty + Y * ���̾���
    '����
   If wqflag = True Then
      wqpang.FillColor = QBColor(15)
      wqpang.DrawWidth = 1
      wqpang.Circle (xx, yy), ���̾��� / 2.2, QBColor(15)
      ���̾�ʽ(X, Y) = 1 '����
      'Print ���̾�ʽ(x0, y0)
      wqflag = False
      'Print "w:"; wqflag
   Else
      wqpang.FillColor = QBColor(0)
      wqpang.DrawWidth = 1
      wqpang.Circle (xx, yy), ���̾��� / 2.2
      ���̾�ʽ(X, Y) = 2 '����
      wqflag = True
      'Print "b:"; wqflag
   End If
   
   Χ������ X, Y
   weiqistep = weiqistep + 1
   ��ʾ
End Sub

Private Sub undoweiqi() 'ȡ��
    Dim X, Y, xx, yy
    weiqistep = weiqistep - 1
    If weiqistep < 0 Then weiqistep = 0: Beep: Exit Sub
    X = Int(���岽��(weiqistep) / 100)
    Y = ���岽��(weiqistep) Mod 100
    ���̾�ʽ(X, Y) = 0
    xx = wqstartx + X * ���̾���
    yy = wqstarty + Y * ���̾���
      wqpang.FillColor = wqpang.BackColor
      wqpang.Circle (xx, yy), ���̾��� / 2.2, wqpang.BackColor
      ClearWeiqiPang xx, yy, X, Y
    If wqflag = False Then  '����Χ��־
       wqflag = True
    Else
       wqflag = False
    End If
    '�ָ��������
    If �����Ӳ��� - 1 >= 0 Then
    If ������(�����Ӳ��� - 1, 0) = weiqistep Then
       �����Ӳ��� = �����Ӳ��� - 1
       undo������
    End If
    End If
    ��ʾ
End Sub

Private Sub undo������()
'���ڵ�������:
'���Լ������Լ�ʱ���岻����ȷ����
   Dim i, j, a, X, Y, xx, yy
   Open "weiqitiz.dat" For Input As #1
   Open "weiqitiz.daf" For Output As #2
   For i = 0 To �����Ӳ��� - 1
       For j = 1 To ������(i, 1)
           Input #1, a
           Print #2, a
       Next j
   Next i
   For j = 1 To ������(�����Ӳ���, 1)
       '�ָ�������
       Input #1, a
        X = a \ 100 Mod 100
        Y = a Mod 100
        xx = wqstartx + X * ���̾���
        yy = wqstarty + Y * ���̾���
        Select Case a \ 10000
          Case 1
            wqpang.DrawWidth = 1
            wqpang.FillColor = QBColor(15)
            wqpang.Circle (xx, yy), ���̾��� / 2.2, QBColor(15)
            ���̾�ʽ(X, Y) = 1 '����
          Case 2
           wqpang.DrawWidth = 1
           wqpang.FillColor = QBColor(0)
           wqpang.Circle (xx, yy), ���̾��� / 2.2
           ���̾�ʽ(X, Y) = 2 '����
        End Select
   Next j
   Close #1
   Close #2
   If a \ 10000 = 1 And wqflag = True Or (a \ 10000 = 2 _
   And wqflag = False) Then
      wqpang.DrawWidth = 1
      wqpang.FillColor = wqpang.BackColor
      wqpang.Circle (xx, yy), ���̾��� / 2.2, wqpang.BackColor
      ClearWeiqiPang xx, yy, X, Y
      ���̾�ʽ(X, Y) = 0
   End If
  FileCopy "weiqitiz.daf", "weiqitiz.dat"
  Kill "weiqitiz.daf"
End Sub

Private Sub �ж��Ƿ�Χ��(X, Y, flag, fflag)
On Error Resume Next
If flag = 1 Then Exit Sub
hadvisted(X, Y) = 1
'Form1.Cls
'Form1.CurrentX = 8
'Form1.CurrentY = 1
'Print "x="; X; "y="; Y; hadvisted(X, Y)
If Y - 1 > 0 Then
If fflag <> 2 And hadvisted(X, Y - 1) <> 1 Then
   Select Case ���̾�ʽ(X, Y - 1)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
'       Print ���̾�ʽ(X, Y); "y-1"
            �ж��Ƿ�Χ�� X, Y - 1, flag, 1
            If flag = 1 Then Exit Sub
   End Select
End If
End If

If Y + 1 < 20 Then
If fflag <> 1 And hadvisted(X, Y + 1) <> 1 Then
   Select Case ���̾�ʽ(X, Y + 1)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
 '      Print ���̾�ʽ(X, Y); "y+1"
               �ж��Ƿ�Χ�� X, Y + 1, flag, 2
               If flag = 1 Then Exit Sub
   End Select
End If
End If

If X - 1 > 0 Then
If fflag <> 4 And hadvisted(X - 1, Y) <> 1 Then
   Select Case ���̾�ʽ(X - 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
  '          Print ���̾�ʽ(X, Y); "x-1"
                 �ж��Ƿ�Χ�� X - 1, Y, flag, 3
                 If flag = 1 Then Exit Sub
   End Select
End If
End If

If X + 1 < 20 Then
If fflag <> 3 And hadvisted(X + 1, Y) <> 1 Then
   Select Case ���̾�ʽ(X + 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
   '    Print ���̾�ʽ(X, Y); "x+1"
            �ж��Ƿ�Χ�� X + 1, Y, flag, 4
If flag = 1 Then Exit Sub
   End Select
End If
End If
If ���̾�ʽ(X, Y) = 0 Then flag = 1
End Sub

Private Sub Χ��eat(X, Y, flag, fflag, num)
'numΪ����ʱ,��¼������ӵĸ���
On Error Resume Next
Dim xx, yy
hadvisted(X, Y) = 1
 If Y - 1 > 0 Then
 If fflag <> 2 And hadvisted(X, Y - 1) <> 1 Then
   Select Case ���̾�ʽ(X, Y - 1)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
'       Print ���̾�ʽ(X, Y); "y-1"
            Χ��eat X, Y - 1, flag, 1, num
   End Select
End If
End If

If Y + 1 < 20 Then
If fflag <> 1 And hadvisted(X, Y + 1) <> 1 Then
   Select Case ���̾�ʽ(X, Y + 1)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
 '      Print ���̾�ʽ(X, Y); "y+1"
            Χ��eat X, Y + 1, flag, 2, num
   End Select
End If
End If

If X - 1 > 0 Then
If fflag <> 4 And hadvisted(X - 1, Y) <> 1 Then
   Select Case ���̾�ʽ(X - 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
  '          Print ���̾�ʽ(X, Y); "x-1"
             Χ��eat X - 1, Y, flag, 3, num
   End Select
   End If
End If

If X + 1 < 20 Then
If fflag <> 3 And hadvisted(X + 1, Y) <> 1 Then
   Select Case ���̾�ʽ(X + 1, Y)
       Case 0
            flag = 1
            Exit Sub
       Case ���̾�ʽ(X, Y)
   '    Print ���̾�ʽ(X, Y); "x+1"
            Χ��eat X + 1, Y, flag, 4, num
   End Select
End If
End If
    xx = wqstartx + X * ���̾���
    yy = wqstarty + Y * ���̾���
      wqpang.FillColor = wqpang.BackColor
      wqpang.Circle (xx, yy), ���̾��� / 2.2, wqpang.BackColor
      ClearWeiqiPang xx, yy, X, Y
      'numΪ����ʱ,��¼������ӵĸ���
      num = num + 1
      '�����Ӽ�¼���ļ�weiqitiz.dat ��
      Open "weiqitiz.dat" For Append As #1
      Print #1, ���̾�ʽ(X, Y) * 10000 + X * 100 + Y
      Close #1
      ���̾�ʽ(X, Y) = 0
End Sub

Private Sub Χ������(X, Y)
Dim flag, i, j, numbel 'numbelΪ�˴α�������
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If X - 1 > 0 Then
�ж��Ƿ�Χ�� X - 1, Y, flag, 0
'Print flag
If flag = 0 And ���̾�ʽ(X, Y) <> ���̾�ʽ(X - 1, Y) Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
Χ��eat X - 1, Y, flag, 0, numbel
������(�����Ӳ���, 0) = weiqistep '���������ڲ���
������(�����Ӳ���, 1) = numbel '�����ӵĸ���
�����Ӳ��� = �����Ӳ��� + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If X + 1 < 20 Then
�ж��Ƿ�Χ�� X + 1, Y, flag, 0
'Print flag
If flag = 0 And ���̾�ʽ(X, Y) <> ���̾�ʽ(X + 1, Y) Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
Χ��eat X + 1, Y, flag, 0, numbel
������(�����Ӳ���, 0) = weiqistep
������(�����Ӳ���, 1) = numbel
�����Ӳ��� = �����Ӳ��� + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If Y + 1 < 20 Then
�ж��Ƿ�Χ�� X, Y + 1, flag, 0
'Print flag
If ���̾�ʽ(X, Y) <> ���̾�ʽ(X, 1 + Y) And flag = 0 Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
Χ��eat X, Y + 1, flag, 0, numbel
������(�����Ӳ���, 0) = weiqistep
������(�����Ӳ���, 1) = numbel
�����Ӳ��� = �����Ӳ��� + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
 If Y - 1 > 0 Then
�ж��Ƿ�Χ�� X, Y - 1, flag, 0
'Print flag
If ���̾�ʽ(X, Y) <> ���̾�ʽ(X, Y - 1) And flag = 0 Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
Χ��eat X, Y - 1, flag, 0, numbel
������(�����Ӳ���, 0) = weiqistep '���������ڲ���
������(�����Ӳ���, 1) = numbel   '�����ӵĸ���
�����Ӳ��� = �����Ӳ��� + 1
End If
End If

For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
 flag = 0
�ж��Ƿ�Χ�� X, Y, flag, 0
'Print flag
If flag = 0 Then
For i = 0 To 19
    For j = 0 To 19
    hadvisted(i, j) = 0
    Next j
Next i
Χ��eat X, Y, flag, 0, numbel
������(�����Ӳ���, 0) = weiqistep
������(�����Ӳ���, 1) = numbel
�����Ӳ��� = �����Ӳ��� + 1
End If
End Sub
Private Sub ��ԭ_Click()
RedoWeiqi
End Sub

Public Sub ����_Click()
undoweiqi
End Sub

Public Sub ȫ�ָ���_Click()
     'wqpang.ForeColor = QBColor(9)
     weiqistep = 0
     Do
       RedoWeiqi
       weiqistep = weiqistep - 1
       If weiqistep < 0 Then Exit Sub
       wqpang.CurrentX = (���岽��(weiqistep) _
                        \ 100) * ���̾��� + wqstartx - ���̾��� / 1.5
       wqpang.CurrentY = (���岽��(weiqistep) _
                         Mod 100) * ���̾��� + wqstarty - ���̾��� / 3
       weiqistep = weiqistep + 1
       If show���岽�� Then
            wqpang.Print weiqistep
       End If
     Loop Until ���岽��(weiqistep) = 0
End Sub

Public Sub ���¿�ʼ_Click()
Form1.Tag = 1
    Unload Me
    Form1.Show
End Sub
Public Sub openfile()
     Dim i
     On Error Resume Next
     FileCopy "save���", save���.Text1.Text
     If Dir("save���", vbNormal) <> "" Then
     Open save���.Text1.Text For Append As #1
     Else
     Open save���.Text1.Text For Output As #1
     End If
     Do
       Print #1, ���岽��(i)
       i = i + 1
     Loop Until ���岽��(i) = 0
     Close #1
End Sub

Public Sub open����()
     Dim i
     i = 0
     On Error Resume Next
     Open ����.Text1.Text For Input As #1
    Do
    Input #1, ���岽��(i)
       i = i + 1
    Loop Until EOF(1)
     Close #1
     ���岽��(i) = 0 'end flag
End Sub

 Sub ssave���()
 On Error Resume Next
 Dim i
 Open "save���" For Output As #1
 Do
   Print #1, ���岽��(i)
   i = i + 1
 Loop While i > weiqistepmax
 Close #1
 End Sub

Sub password()
Dim pass As String
   pass = InputBox("����������:", "����")
   If pass = "kanglinweiqi2001" Then
   Else
     End
   End If
End Sub

