VERSION 5.00
Begin VB.Form selectpaper 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "ѡȡͼֽ"
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
   StartUpPosition =   1  '����������
   Tag             =   "0"
   Begin VB.CommandButton Command3 
      Caption         =   "�޸�"
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
      Caption         =   "��ʾ������(&S)"
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
'����:����

Option Explicit

Private Type PaperType
     name As String
     Width As Single
     Height As Single
     End Type
Private PaperStype() As PaperType  '�ڴ��м�¼ͼֽ����
Private n As Integer
Private CurrentPaper As String   '���õ�ͼֽ
Private CurrentPaperIndex As Long   '��ǰװ��ͼֽ�ĺ�

Private Sub chkLoadTipsAtStartup_Click()
Dim i
    ' �������´�����ʱ�Ƿ���ʾ�˴���
    i = WritePrivateProfileString("ѡ��", "������ʱ��ʾѡȡͼֽ����", CStr(chkLoadTipsAtStartup.Value), Inifile)
End Sub

Private Sub Form_Load()
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    Dim ShowAtStartup As Long
    Dim i As Long, ss As String * 20
    ' �쿴������ʱ�Ƿ񽫱���ʾ
    i = GetPrivateProfileString("ѡ��", "������ʱ��ʾѡȡͼֽ����", "1", ss, 10, Inifile)
    If i = 0 Then
       ShowAtStartup = 1
    Else
       ShowAtStartup = Val(left$(ss, i))
    End If
    If ShowAtStartup = 0 Then     '����ʾ
       Unload Me
       Exit Sub
    Else
    End If
    
    ' ���ø�ѡ��ǿ�н�ֵд�ص�ע���
    If ShowAtStartup <> 0 Then
       Me.chkLoadTipsAtStartup.Value = vbChecked
    End If
    
    '������ʾ�б��Ĭ��ֵ
    TakePaperStype   '����ͼֽ����
    
    For i = 1 To n    '��ʾͼֽ�߶ȺͿ��
        With PaperStype(i)
             If .name = CurrentPaper Then
                Text1.text = .Width
                Text2.text = .Height
                List1.ListIndex = CurrentPaperIndex
                Exit For
             End If
        End With
    Next i
    
    Text1.Enabled = False   ' �������һ�㲻��������
    Text2.Enabled = False   'ֻ��������ʱ�Ž�������
        
End Sub

Private Sub List1_Click()   'ͼֽ��������
Dim i As Long
      For i = 1 To n
          With PaperStype(i)
               If List1.List(List1.ListIndex) = .name Then
                  Text1.text = .Width  '��ʾ�߶�
                  Text2.text = .Height '....���
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
       
       For i = 1 To n    '�ѵ�ǰѡȡ��ͼֽ���ͷ��������ļ���
           If PaperStype(i).name = List1.List(List1.ListIndex) Then
              i = WritePrivateProfileString("paper", "width", CStr(PaperStype(i).Width), Inifile)
              i = WritePrivateProfileString("paper", "height", CStr(PaperStype(i).Height), Inifile)
              Unload Me
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
        n = n + 1
        ReDim Preserve PaperStype(n)
        PaperStype(n).name = InputBox("�����µ�ͼֽ��")
        If PaperStype(n).name = "" Then   '��ȡ��ʱ
           n = n - 1
           ReDim Preserve PaperStype(n)
           Exit Sub
        End If
        List1.AddItem (PaperStype(n).name)  '����Ԫ��
        List1.ListIndex = n - 1   '��ʾ�б��е�ѡȡԪ��,��Ϊ�б��0��ʼ,paperstype���ݴ�1��ʼ
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
        For i = 1 To n
            If List1.List(List1.ListIndex) = PaperStype(i).name Then
                    List1.RemoveItem (List1.ListIndex)    'ɾȥѡ����Ԫ��
                    If List1.ListIndex > 0 Then
                       List1.ListIndex = i - 1
                    End If
                    For j = i To n - 1     '��������ɾ��
                        PaperStype(j) = PaperStype(j + 1)
                    Next j
                    flag = True
                    Exit For
            End If
        Next i
        If flag Then
           flag = False  '
           n = n - 1    ' ��������ɾ��
           ReDim Preserve PaperStype(n)
           For i = 1 To n  'ɾ����ָ���ͼֽ
               With PaperStype(i)
                    If List1.List(List1.ListIndex) = .name Then
                       flag = True
                       Text1.text = .Width
                       Text2.text = .Height
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

'���ļ���ȡ��ͼֽ����
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

'ͼֽ��С��ʾ
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

'ͼֽ��С��ʾ
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
