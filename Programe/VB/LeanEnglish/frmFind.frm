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
   StartUpPosition =   1  '所有者中心
   Begin VB.CheckBox Check1 
      Caption         =   "自动列出可能值"
      Height          =   255
      Left            =   1080
      TabIndex        =   12
      Top             =   960
      Value           =   1  'Checked
      Width           =   2535
   End
   Begin VB.CommandButton cmdCanal 
      Caption         =   "取消"
      Height          =   375
      Left            =   2280
      TabIndex        =   9
      Top             =   2160
      Width           =   1215
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定"
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
         Caption         =   "全部有联系的词"
         Height          =   255
         Index           =   5
         Left            =   120
         TabIndex        =   10
         Top             =   2040
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "同日期的词"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   7
         Top             =   1680
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "关联词"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   6
         Top             =   1320
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "相似词"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   5
         Top             =   960
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "反义词"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   4
         Top             =   600
         Width           =   1815
      End
      Begin VB.OptionButton Oper 
         Caption         =   "同义词"
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
      Caption         =   "当查找多个词时,每个词之间用逗号分隔"
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
      Caption         =   "查找"
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
           Me.Caption = "查找 " & Cmb.Text & " 的" & Oper(Index).Caption
        End If
    Next

End Sub

Private Sub Cmb_Click()
Dim Index
    For Index = 0 To Oper.UBound
        If Oper(Index).Value Then
           Me.Caption = "查找 " & Cmb.Text & " 的" & Oper(Index).Caption
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
                      ss = Rst("同义词").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 1
                While Not Rst.EOF
                      ss = Rst("反义词").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 2
                While Not Rst.EOF
                      ss = Rst("相似词").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 3
                While Not Rst.EOF
                      ss = Rst("关联词").Value
                      If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                      Rst.MoveNext
                Wend
           Case 4
                While Not Rst.EOF
                     ss = Rst("日期").Value
                     If Trim(ss) <> "" Then
                         Cmb.AddItem ss
                      End If
                     Rst.MoveNext
                Wend
           Case 5
                While Not Rst.EOF
                      ss = Rst("单词").Value
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
        LB(1).Caption = LB(1).Caption & Chr$(13) & "日期要用长格式表示,例如:2000年8月12日"
        Set Rst = Dbs.OpenRecordset("select * from " & Table)
        Screen.MousePointer = vbDefault
End Sub

Private Sub Oper_Click(Index As Integer)
On Error Resume Next
    
    Rst.MoveFirst
    If Not Check1.Value Then
        Check1_Click
    End If
    Me.Caption = "查找 " & Cmb.Text & " 的" & Oper(Index).Caption

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
              Case 0 '同义词
                   Same ss
              Case 1 '反义词
                   Same ss, "反义词"
              Case 2 '相似词
                   Same ss, "相似词"
              Case 3 '关联词
                   Same ss, "关联词"
              Case 4 '日期
                   Same ss, "日期"
              Case 5 '全部
              
              Case Else
                   'ss(0) = "--"
                   
                   ShowFind Me.Caption, Find(ss)
       End Select
       Screen.MousePointer = vbDefault
       Unload Me
End Sub

Sub Same(ss() As String, Optional Field As String = "同义词")
On Error Resume Next

Dim i, s() As String
ReDim s(0)

If Field = "日期" Then
    For i = 1 To UBound(ss)
        SplitString Dbs.OpenRecordset("select " & Field & " from " & Table & " where 日期 = '" & ss(i) & "'")(0), s, , , 防止得到重复字符串
    Next i

   ShowFind Me.Caption, Find(s, "=", "日期", True)
Else
    For i = 1 To UBound(ss)
        SplitString Dbs.OpenRecordset("select " & Field & " from " & Table & " where 单词 = '" & ss(i) & "'")(0), s, , , 防止得到重复字符串
    Next i

    ShowFind Me.Caption, Find(s)
End If
End Sub
