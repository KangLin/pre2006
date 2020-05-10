VERSION 5.00
Begin VB.Form frmAddDoctor 
   Caption         =   "增加医生"
   ClientHeight    =   2280
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   Icon            =   "frmAddDoctor.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   2280
   ScaleWidth      =   4680
   StartUpPosition =   1  '所有者中心
   Begin VB.Frame fmDel 
      Height          =   1215
      Left            =   1680
      TabIndex        =   7
      Top             =   120
      Visible         =   0   'False
      Width           =   2535
      Begin VB.ComboBox cbNo 
         Height          =   300
         Left            =   240
         TabIndex        =   9
         Text            =   "cbNo"
         Top             =   720
         Width           =   2055
      End
      Begin VB.ComboBox cbDoc 
         Height          =   300
         Left            =   240
         TabIndex        =   8
         Text            =   "cbDoc"
         Top             =   240
         Width           =   2055
      End
   End
   Begin VB.Frame fmAdd 
      Height          =   1215
      Left            =   1800
      TabIndex        =   4
      Top             =   120
      Width           =   2295
      Begin VB.TextBox txtDoc 
         Height          =   270
         Left            =   240
         TabIndex        =   6
         Text            =   "txtDoc"
         Top             =   240
         Width           =   1815
      End
      Begin VB.TextBox txtNO 
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   2052
            SubFormatType   =   1
         EndProperty
         Height          =   270
         Left            =   240
         TabIndex        =   5
         Text            =   "txtNO"
         Top             =   840
         Width           =   1815
      End
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "退出(&E)"
      Height          =   375
      Left            =   2880
      TabIndex        =   3
      Top             =   1560
      Width           =   1095
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "增加(&A)"
      Height          =   375
      Left            =   480
      TabIndex        =   2
      Top             =   1560
      Width           =   1095
   End
   Begin VB.Label Label2 
      Caption         =   "编号："
      Height          =   255
      Left            =   960
      TabIndex        =   1
      Top             =   960
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "医生："
      Height          =   255
      Left            =   960
      TabIndex        =   0
      Top             =   360
      Width           =   855
   End
End
Attribute VB_Name = "frmAddDoctor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'功能:增加/删除医生标识窗体
'作者:康林
'时间:2005年6月

Option Explicit

Public m_bAdd As Boolean

Private Sub cmdAdd_Click()
Dim sql As String, rs As ADODB.Recordset

If m_bAdd Then
   sql = "select 医生,编号 from doctor"
   With frmMain.Ado
        .RecordSource = sql
        .Refresh
        With .Recordset
             .AddNew
             .Fields("医生") = txtDoc.Text
             .Fields("编号") = txtNO.Text
             .Update
        End With
   End With
   GetMaxNo
Else
   With frmMain.Ado
        sql = "select * from doctor where 编号 = cint('" & cbNo.Text & "')"
        .RecordSource = sql
        .Refresh
        With .Recordset
             .Delete
             .Update
        End With
   End With
   cbNo.Clear
   cbDoc.Clear
   With frmMain.Ado
     .RecordSource = "Select 编号,医生 From doctor"
     .Refresh
     Set rs = .Recordset
     While Not rs.EOF
          cbNo.AddItem rs.Fields("编号")
          cbDoc.AddItem rs.Fields("医生")
          rs.MoveNext
     Wend
   End With
   If cbNo.ListCount > 0 Then
      cbNo.ListIndex = 0
   End If
   If cbDoc.ListCount > 0 Then
      cbDoc.ListIndex = 0
   End If
End If
End Sub

Private Sub cmdExit_Click()
Unload Me
End Sub

Private Sub Form_Load()
Dim rs As ADODB.Recordset
GetMaxNo
Me.Icon = frmMain.Icon
If Not m_bAdd Then
   cmdAdd.Caption = "删除(&D)"
   Me.Caption = "删除医生"
   fmAdd.Visible = False
   fmDel.Visible = True
   With frmMain.Ado
     .RecordSource = "Select 编号,医生 From doctor"
     .Refresh
     Set rs = .Recordset
     While Not rs.EOF
          cbNo.AddItem rs.Fields("编号")
          cbDoc.AddItem rs.Fields("医生")
          rs.MoveNext
     Wend
End With
If cbNo.ListCount > 0 Then
   cbNo.ListIndex = 0
End If
If cbDoc.ListCount > 0 Then
   cbDoc.ListIndex = 0
End If
End If
End Sub

Private Function GetMaxNo() As Integer
Dim sql As String

sql = "select max(编号) from doctor"
With frmMain.Ado
     .RecordSource = sql
     .Refresh
     If IsNull(.Recordset.Fields(0)) Then
        GetMaxNo = 1
     Else
        GetMaxNo = .Recordset.Fields(0) + 1
     End If
End With
txtNO.Text = GetMaxNo
txtDoc.Text = ""
End Function

Private Sub cbNo_Click()
FindDoc
End Sub

Private Function FindDoc() As String
With frmMain.Ado
     .RecordSource = "Select 医生 From doctor Where 编号 = CINT(" _
                     & cbNo.Text & ")"
     .Refresh
     cbDoc.Text = .Recordset.Fields.Item("医生")
End With
End Function

Private Sub cbDoc_Click()
FindNo
End Sub

Private Function FindNo() As Integer
With frmMain.Ado
     .RecordSource = "Select 编号 From doctor Where 医生 = '" _
                     & cbDoc.Text & "'"
     .Refresh
     cbNo.Text = .Recordset.Fields.Item("编号")
End With
End Function


