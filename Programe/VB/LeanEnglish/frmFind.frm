VERSION 5.00
Begin VB.Form frmFind 
   Caption         =   "Form1"
   ClientHeight    =   2745
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6135
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2745
   ScaleWidth      =   6135
   StartUpPosition =   1  '����������
   Begin VB.CheckBox Check1 
      Caption         =   "�Զ��г�����ֵ"
      Height          =   255
      Left            =   1080
      TabIndex        =   12
      Top             =   960
      Value           =   1  'Checked
      Width           =   2535
   End
   Begin VB.CommandButton cmdCanal 
      Caption         =   "ȡ��"
      Height          =   375
      Left            =   2280
      TabIndex        =   9
      Top             =   2160
      Width           =   1215
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "ȷ��"
      Default         =   -1  'True
      Height          =   375
      Left            =   360
      TabIndex        =   8
      Top             =   2160
      Width           =   1095
   End
   Begin VB.Frame Frm 
      Height          =   2415
      Left            =   3840
      TabIndex        =   2
      Top             =   0
      Width           =   2055
      Begin VB.OptionButton Oper 
         Caption         =   "ȫ������ϵ�Ĵ�"
         Height          =   255
         Index           =   5
         Left            =   120
         TabIndex        =   10
         Top             =   2040
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "ͬ���ڵĴ�"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   7
         Top             =   1680
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "������"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   6
         Top             =   1320
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "���ƴ�"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   5
         Top             =   960
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "�����"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   4
         Top             =   600
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "ͬ���"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   3
         Top             =   240
         Width           =   1815
      End
   End
   Begin VB.ComboBox Cmb 
      Height          =   300
      Left            =   1080
      TabIndex        =   0
      Top             =   480
      Width           =   2535
   End
   Begin VB.Label LB 
      AutoSize        =   -1  'True
      Caption         =   "�����Ҷ����ʱ,ÿ����֮���ö��ŷָ�"
      ForeColor       =   &H000000FF&
      Height          =   180
      Index           =   1
      Left            =   480
      TabIndex        =   11
      Top             =   1320
      Width           =   3150
   End
   Begin VB.Label LB 
      AutoSize        =   -1  'True
      Caption         =   "����"
      Height          =   180
      Index           =   0
      Left            =   480
      TabIndex        =   1
      Top             =   600
      Width           =   360
   End
End
Attribute VB_Name = "frmFind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Rst As Recordset

Public Function InputRst(Rec As Recordset)
       Set Rst = Rec
End Function

Public Sub Cmb_Change()
Dim Index
    For Index = 0 To Oper.UBound
        If Oper(Index).Value Then
           Me.Caption = "���� " & Cmb.Text & " ��" & Oper(Index).Caption
        End If
    Next

End Sub

Private Sub Cmb_Click()
Dim Index
    For Index = 0 To Oper.UBound
        If Oper(Index).Value Then
           Me.Caption = "���� " & Cmb.Text & " ��" & Oper(Index).Caption
        End If
    Next

End Sub

Private Sub Check1_Click()
On Error Resume Next

Dim ss As String
Dim Index
If Check1.Value Then
    For Index = 0 To Oper.UBound
        If Oper(Index).Value Then Exit For
    Next
        Cmb.Clear
        Rst.MoveFirst
    Select Case Index
           Case 0
                While Not Rst.EOF
                      ss = Rst("ͬ���").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 1
                While Not Rst.EOF
                      ss = Rst("�����").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 2
                While Not Rst.EOF
                      ss = Rst("���ƴ�").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 3
                While Not Rst.EOF
                      ss = Rst("������").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 4
                While Not Rst.EOF
                     ss = Rst("����").Value
                     If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                     Rst.MoveNext
                Wend
           Case 5
                While Not Rst.EOF
                      ss = Rst("����").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
    End Select
    Cmb.ListIndex = 0
End If
End Sub

Private Sub cmdCanal_Click()
        Unload Me
End Sub

Private Sub Form_Load()
On Error Resume Next
Dim i
        LB(1).Caption = LB(1).Caption & Chr$(13) & "����Ҫ�ó���ʽ��ʾ,����:2000��8��12��"
        Set Rst = Dbs.OpenRecordset("select * from " & Table)
        Screen.MousePointer = vbDefault
End Sub

Private Sub Oper_Click(Index As Integer)
On Error Resume Next
    
    Rst.MoveFirst
    If Not Check1.Value Then
        Check1_Click
    End If
    Me.Caption = "���� " & Cmb.Text & " ��" & Oper(Index).Caption

End Sub

Private Sub cmdOK_Click()
Dim i, ss() As String
      
       Screen.MousePointer = VBRUN.MousePointerConstants.vbHourglass
       ReDim ss(0)
       For i = 0 To Oper.UBound
           If Oper(i).Value Then
              Exit For
           End If
       Next i
       SplitString Cmb.Text, ss
       Select Case i
              Case 0 'ͬ���
                   Same ss
              Case 1 '�����
                   Same ss, "�����"
              Case 2 '���ƴ�
                   Same ss, "���ƴ�"
              Case 3 '������
                   Same ss, "������"
              Case 4 '����
                   Same ss, "����"
              Case 5 'ȫ��
              
              Case Else
                   'ss(0) = "--"
                   
                   ShowFind Me.Caption, Find(ss)
       End Select
       Screen.MousePointer = vbDefault
       Unload Me
End Sub

Sub Same(ss() As String, Optional Field As String = "ͬ���")
On Error Resume Next

Dim i, s() As String
ReDim s(0)

If Field = "����" Then
    For i = 1 To UBound(ss)
        SplitString Dbs.OpenRecordset("select " & Field & " from " & Table & " where ���� = '" & ss(i) & "'")(0), s, , , ��ֹ�õ��ظ��ַ���
    Next i

   ShowFind Me.Caption, Find(s, "=", "����", True)
Else
    For i = 1 To UBound(ss)
        SplitString Dbs.OpenRecordset("select " & Field & " from " & Table & " where ���� = '" & ss(i) & "'")(0), s, , , ��ֹ�õ��ظ��ַ���
    Next i

    ShowFind Me.Caption, Find(s)
End If
End Sub
