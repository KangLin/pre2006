VERSION 5.00
Begin VB.Form selectpaper 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "ѡȡͼֽ"
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
   StartUpPosition =   1  '����������
   Begin VB.CommandButton Command3 
      Caption         =   "�޸�"
      Height          =   375
      Left            =   4680
      TabIndex        =   13
      Top             =   2400
      Width           =   1215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "������ļ�ʱ��ʾ"
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
      Caption         =   "������ʱ��ʾ(&S)"
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
      Caption         =   "ɾ��"
      Height          =   375
      Left            =   4680
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "����"
      Height          =   375
      Left            =   4680
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   1200
      Width           =   1215
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "ȡ��"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "ȷ��"
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
      Caption         =   "�����¹�����Tab����ѡ��߶Ȼ���,�ÿո��ȷ��ѡȡֵ"
      Height          =   180
      Left            =   480
      TabIndex        =   11
      Top             =   3480
      Visible         =   0   'False
      Width           =   4860
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "�߶�:"
      Height          =   180
      Left            =   3120
      TabIndex        =   9
      Top             =   3120
      Width           =   450
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "���:"
      Height          =   180
      Left            =   1440
      TabIndex        =   7
      Top             =   3120
      Width           =   450
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "ֽ�Ĵ�С"
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
'ͼֽ������ѡȡ
Option Explicit

Private PaperFileName As String    'ͼֽ�ļ���
Public showthiswindowsflag As Boolean   'ǿ����ʾ�����ڱ�־
Private Type papertype
     name As String
     width As Single
     height As Single
     End Type
Private PaperStype() As papertype
Private N As Integer
Private CurrentPaper As String   '���õ�ͼֽ
Private currentpaperindex As Long   '��ǰװ��ͼֽ�ĺ�

Private Sub Check1_Click()
    ' �������´ε�����ļ�ʱʱ�Ƿ���ʾ�˴���
    SaveSetting App.EXEName, "Options", "�ڵ�����ļ�ʱ��ʾ", Check1.Value
End Sub

Private Sub chkLoadTipsAtStartup_Click()
    ' �������´�����ʱ�Ƿ���ʾ�˴���
    SaveSetting App.EXEName, "Options", "������ʱ��ʾ", chkLoadTipsAtStartup.Value
End Sub

Private Sub Form_Load()
'On Error Resume Next
    Dim ShowAtStartup As Long
    Dim i As Long
    PaperFileName = App.Path + "\" + "papertype.cad"
    If showthiswindowsflag Then GoTo seclectpaperform1ladshowthiswindows    'ǿ����ʾ������
    ' �쿴������ʱ�Ƿ񽫱���ʾ
    ShowAtStartup = GetSetting(App.EXEName, "Options", "������ʱ��ʾ", 1)
    If ShowAtStartup = 0 And Not user.Showselectpaperform Then     '����ʾ
        Unload Me
        Exit Sub
    End If
    
    ' �쿴�ڵ�����ļ�ʱ�Ƿ񽫱���ʾ
    ShowAtStartup = GetSetting(App.EXEName, "Options", "�ڵ�����ļ�ʱ��ʾ", 1)
    If ShowAtStartup = 0 And user.Showselectpaperform Then      '����ʾ
        Unload Me
        Exit Sub
    End If

seclectpaperform1ladshowthiswindows:
    ' ���ø�ѡ��ǿ�н�ֵд�ص�ע���
    ShowAtStartup = GetSetting(App.EXEName, "Options", "������ʱ��ʾ", 1)
    If ShowAtStartup <> 0 Then
       Me.chkLoadTipsAtStartup.Value = vbChecked
    End If
    
    ' ���ø�ѡ��ǿ�н�ֵд�ص�ע���
    ShowAtStartup = GetSetting(App.EXEName, "Options", "�ڵ�����ļ�ʱ��ʾ", 1)
    If ShowAtStartup <> 0 Then
       Me.Check1.Value = vbChecked
    End If
    
    '������ʾ�б��Ĭ��ֵ
    TakePaperStype   '����ͼֽ����
    
    'If Not (user.showselectpaperform) Then
       '����ʱ����
       If List1.ListCount <> 0 Then
'          For i = 1 To N
 '             If PaperStype(i).name = crrentpaper Then
                 List1.ListIndex = currentpaperindex
       End If
    'Else
       '�����ļ�����
    '   For i = 1 To N
    '       If List1.List(i) = user.paper.name Then
    '          List1.ListIndex = i
    '       End If
    '   Next i
    'End If
    
    For i = 1 To N    '��ʾͼֽ�߶ȺͿ��
        With PaperStype(i)
             If .name = CurrentPaper Then
                Text1.text = .width
                Text2.text = .height
                Exit For
             End If
        End With
    Next i
    
    Text1.Enabled = False   ' �������һ�㲻��������
    Text2.Enabled = False   'ֻ��������ʱ�Ž�������
        
End Sub

Private Sub List1_Click()
Dim i As Long
      For i = 1 To N
          With PaperStype(i)
               If List1.List(List1.ListIndex) = .name Then
                  Text1.text = .width  '��ʾ�߶�
                  Text2.text = .height '....���
                  Exit For
               End If
          End With
      Next i
End Sub

Private Sub OKButton_Click()   'ȷ����Ť
Dim i As Long
       'list(index)��һ������
       'If List1.List(List1.ListIndex) = "e" Then 'ȡ��ѡȡ��Ԫ��
       '   MsgBox ("ok")
       'End If
       CurrentPaper = List1.List(List1.ListIndex)
       SavePaperStype    '����ͼֽ����
       For i = 1 To N
           If PaperStype(i).name = List1.List(List1.ListIndex) Then
              With user.paper   '��ͼֽ������ֵ
                   .width = PaperStype(i).width
                   .height = PaperStype(i).height
              End With
              If Not (showthiswindowsflag) Then
                 'Load frmOptions  '���ӳ����𶯻������ļ�ʱ,��ͼֽ��ֵ
                  With PaperStype(i)  '��ѡ����ʱ,��ͼֽ��ֵ
                       frmOptions.pwidth.text = .width
                       frmOptions.pheight.text = .height
                  End With
                 frmOptions.cmdOK_Click
              Else
                  With PaperStype(i)  '��ѡ����ʱ,��ͼֽ��ֵ
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

Private Sub CancelButton_Click()  'ȡ����Ť
        Unload Me
End Sub

Private Sub Command3_Click()  '�޸�ͼֽ����
Dim control As control
For Each control In selectpaper.Controls
    control.Enabled = False
Next control
Text1.Enabled = True   '�����������Ӧ�¼�,������������
Text2.Enabled = True
Label4.Visible = True   '��ʾ
Text1.SetFocus
End Sub

Private Sub Command1_Click()  '����ͼֽ����
Dim control As control
        N = N + 1
        ReDim Preserve PaperStype(N)
        PaperStype(N).name = InputBox("�����µ�ͼֽ��")
        If PaperStype(N).name = "" Then   '��ȡ��ʱ
           N = N - 1
           ReDim Preserve PaperStype(N)
           Exit Sub
        End If
        List1.AddItem (PaperStype(N).name)  '����Ԫ��
        List1.ListIndex = N - 1   '��ʾ�б��е�ѡȡԪ��,��Ϊ�б��0��ʼ,paperstype���ݴ�1��ʼ
        For Each control In selectpaper.Controls   '��ֹ���пؼ���Ӧ�¼�
            control.Enabled = False                'Ϊ����ֻ���������������
        Next control
        Text1.Enabled = True   '�����������Ӧ�¼�,������������
        Text2.Enabled = True
        Label4.Visible = True '��ʾ
        Text1.SetFocus
End Sub

Private Sub Command2_Click()   'ɾ��ͼֽ����
Dim flag As Boolean
        Dim i As Long, j
        For i = 1 To N
            If List1.List(List1.ListIndex) = PaperStype(i).name Then
                    List1.RemoveItem (List1.ListIndex)    'ɾȥѡ����Ԫ��
                    If List1.ListIndex > 0 Then
                       List1.ListIndex = i - 1
                    End If
                    For j = i To N - 1     '��������ɾ��
                        PaperStype(j) = PaperStype(j + 1)
                    Next j
                    flag = True
                    Exit For
            End If
        Next i
        If flag Then
           flag = False  '
           N = N - 1    ' ��������ɾ��
           ReDim Preserve PaperStype(N)
           For i = 1 To N  'ɾ����ָ���ͼֽ
               With PaperStype(i)
                    If List1.List(List1.ListIndex) = .name Then
                       flag = True
                       Text1.text = .width
                       Text2.text = .height
                    End If
               End With
           Next i
           If Not (flag) Then  '��ָ��ͼֽ,��Ϊ��
              Text1.text = ""
              Text2.text = ""
           End If
        End If
End Sub

'����ͼֽ����
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

'ȡ��ͼֽ����
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
