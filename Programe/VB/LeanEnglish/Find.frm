VERSION 5.00
Begin VB.Form frmFindForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "查找"
   ClientHeight    =   3075
   ClientLeft      =   1995
   ClientTop       =   2595
   ClientWidth     =   5400
   HelpContextID   =   2016128
   Icon            =   "Find.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2561.969
   ScaleMode       =   0  'User
   ScaleWidth      =   5314.456
   ShowInTaskbar   =   0   'False
   Begin VB.ComboBox cobExpression 
      Height          =   300
      Left            =   3120
      TabIndex        =   13
      Top             =   360
      Width           =   2055
   End
   Begin VB.CommandButton cmdShowAllVal 
      Caption         =   "正在获取可能的值"
      Height          =   255
      Left            =   3120
      TabIndex        =   12
      Top             =   720
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "查找全部"
      Height          =   255
      Index           =   4
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   11
      Top             =   2040
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "查找最后一个"
      Height          =   255
      Index           =   3
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   8
      Top             =   1800
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "查找前一个"
      Height          =   255
      Index           =   2
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   7
      Top             =   1560
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "查找下一个"
      Height          =   255
      Index           =   1
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   6
      Top             =   1320
      Width           =   2055
   End
   Begin VB.OptionButton optFindType 
      Caption         =   "查找第一个"
      Height          =   255
      Index           =   0
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   5
      Top             =   1080
      Value           =   -1  'True
      Width           =   2055
   End
   Begin VB.ListBox lstFields 
      Height          =   1860
      ItemData        =   "Find.frx":030A
      Left            =   240
      List            =   "Find.frx":030C
      TabIndex        =   1
      Top             =   360
      Width           =   1695
   End
   Begin VB.ListBox lstOperators 
      Height          =   1860
      ItemData        =   "Find.frx":030E
      Left            =   2040
      List            =   "Find.frx":0310
      TabIndex        =   3
      Top             =   360
      Width           =   960
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定(&O)"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   372
      Left            =   600
      MaskColor       =   &H00000000&
      TabIndex        =   9
      Top             =   2520
      Width           =   1691
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "取消(&C)"
      Height          =   372
      Left            =   2879
      MaskColor       =   &H00000000&
      TabIndex        =   10
      Top             =   2520
      Width           =   1691
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "运算符："
      Height          =   180
      Index           =   1
      Left            =   2040
      TabIndex        =   2
      Top             =   120
      Width           =   720
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "字段："
      Height          =   180
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   540
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "值或表达式："
      Height          =   180
      Index           =   2
      Left            =   3120
      TabIndex        =   4
      Top             =   120
      Width           =   1080
   End
End
Attribute VB_Name = "frmFindForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "查找记录"
Const BUTTON1 = "确定(&O)"
Const BUTTON2 = "取消(&C)"
Const Label1 = "字段(&F)："
Const Label2 = "运算符(&O)："
Const LABEL3 = "值或表达式(&V)："
'>>>>>>>>>>>>>>>>>>>>>>>>

Dim mbNotFound As Integer


Private Sub cmdCancel_Click()
  'Hide
  'set the flag for the recordset/recagrid form
  gbFindFailed = True
  Unload Me
End Sub

Private Sub cmdShowAllVal_Click()
On Error GoTo GVErr
Dim rec As Recordset

  'MsgBox "正在获取可能的值"
  Screen.MousePointer = vbHourglass
  cobExpression.Clear
  Set rec = dbs.OpenRecordset("select " & lstFields.List(lstFields.ListIndex) & " from " & "dictionary")
  Do While rec.EOF = False
    If Len(Trim(rec(0))) > 0 Then
      cobExpression.AddItem rec(0).Value
    End If
    rec.MoveNext
  Loop
  rec.Close
  cobExpression.Text = cobExpression.List(0)
  cobExpression.SetFocus

  Screen.MousePointer = vbDefault
  'MsgBar vbNullString, False
  Exit Sub

GVErr:
  Screen.MousePointer = vbDefault
  'MsgBar vbNullString, False
  cobExpression.Text = vbNullString
    
End Sub

Private Sub optFindType_Click(Index As Integer)
  gnFindType = Index
End Sub

Private Sub cobExpression_Change()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(lstOperators.Text) > 0 And Len(cobExpression.Text) > 0
End Sub

Private Sub lstFields_Click()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(lstOperators.Text) > 0 And Len(cobExpression.Text) > 0
End Sub

Private Sub lstOperators_Click()
  cmdOK.Enabled = Len(lstFields.Text) > 0 And Len(lstOperators.Text) > 0 And Len(cobExpression.Text) > 0
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
'    DisplayTopic 2016128
  End If
End Sub

Private Sub Form_Load()

  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
  
  lstOperators.AddItem "="
  lstOperators.AddItem "<>"
  lstOperators.AddItem ">="
  lstOperators.AddItem "<="
  lstOperators.AddItem ">"
  lstOperators.AddItem "<"
  lstOperators.AddItem "Like"
  lstOperators.ListIndex = 0
  
  optFindType(4).Value = True
  
  mbNotFound = False
End Sub

Private Sub cmdOK_Click()
   On Error GoTo FindErr

   Dim i As Integer

   i = lstFields.ListIndex
   mbNotFound = False
   Screen.MousePointer = vbHourglass

   gsFindField = lstFields.Text
   gsFindExpr = cobExpression.Text
   gsFindOp = lstOperators.Text

   'Hide
   Screen.MousePointer = vbDefault
   Unload Me
   Exit Sub

FindErr:
   If Err <> gnEOF_ERR Then
     'ShowError
   Else
     mbNotFound = True
     Resume Next
   End If
End Sub
