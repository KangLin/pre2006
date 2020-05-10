VERSION 5.00
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmInputData 
   Caption         =   "数据输入"
   ClientHeight    =   5895
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8310
   Icon            =   "frmInputData.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5895
   ScaleWidth      =   8310
   StartUpPosition =   1  '所有者中心
   WindowState     =   2  'Maximized
   Begin MSDataGridLib.DataGrid dg 
      Height          =   3135
      Left            =   360
      TabIndex        =   8
      Top             =   1080
      Width           =   4815
      _ExtentX        =   8493
      _ExtentY        =   5530
      _Version        =   393216
      AllowUpdate     =   -1  'True
      AllowArrows     =   -1  'True
      HeadLines       =   1
      RowHeight       =   15
      TabAction       =   2
      AllowAddNew     =   -1  'True
      AllowDelete     =   -1  'True
      BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ColumnCount     =   2
      BeginProperty Column00 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   2052
            SubFormatType   =   0
         EndProperty
      EndProperty
      BeginProperty Column01 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   2052
            SubFormatType   =   0
         EndProperty
      EndProperty
      SplitCount      =   1
      BeginProperty Split0 
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
   Begin VB.Frame framSelect 
      Height          =   735
      Left            =   360
      TabIndex        =   0
      Top             =   120
      Width           =   7575
      Begin VB.ComboBox cbNo 
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   2052
            SubFormatType   =   1
         EndProperty
         Height          =   300
         Left            =   3840
         TabIndex        =   1
         Text            =   "cbNo"
         Top             =   240
         Width           =   1455
      End
      Begin VB.TextBox txtDate 
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "yyyy""年""M""月""d""日"""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   2052
            SubFormatType   =   3
         EndProperty
         Height          =   270
         Left            =   6120
         TabIndex        =   2
         Text            =   "2005-1-1"
         Top             =   240
         Width           =   1335
      End
      Begin VB.ComboBox cbDoctor 
         Height          =   300
         ItemData        =   "frmInputData.frx":000C
         Left            =   1080
         List            =   "frmInputData.frx":000E
         TabIndex        =   3
         Text            =   "cbDoctor"
         Top             =   240
         Width           =   1695
      End
      Begin VB.Label Label3 
         Caption         =   "日期："
         Height          =   255
         Left            =   5400
         TabIndex        =   6
         Top             =   240
         Width           =   615
      End
      Begin VB.Label Label2 
         Caption         =   "医生编号："
         Height          =   255
         Left            =   2880
         TabIndex        =   5
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label1 
         Caption         =   "选择医生："
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   240
         Width           =   1095
      End
   End
   Begin MSComctlLib.StatusBar sb 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   7
      Top             =   5640
      Width           =   8310
      _ExtentX        =   14658
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   5
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   1
            Object.Width           =   3889
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
         BeginProperty Panel4 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Text            =   "日期："
            TextSave        =   "日期："
         EndProperty
         BeginProperty Panel5 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            Alignment       =   1
            AutoSize        =   2
            TextSave        =   "2005-6-18"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmInputData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'功能:数据输入窗体
'作者:康林
'时间:2005年6月

Option Explicit

Dim rs As ADODB.Recordset

Private Sub Form_Load()
Dim f As Field

With frmMain.Ado
     .RecordSource = "Select 编号,医生 From doctor"
     .Refresh
     Set rs = .Recordset
     While Not rs.EOF
          cbNo.AddItem rs.Fields("编号")
          cbDoctor.AddItem rs.Fields("医生")
          rs.MoveNext
     Wend
End With
If cbNo.ListCount > 0 Then
   cbNo.ListIndex = 0
End If
If cbDoctor.ListCount > 0 Then
   cbDoctor.ListIndex = 0
End If

Set dg.DataSource = frmMain.Ado
Me.Icon = frmMain.Icon
txtDate.Text = Date
Find
End Sub

Private Sub Form_Resize()
If Me.ScaleHeight = 0 Then
   Exit Sub
End If
With framSelect
     .left = (Me.ScaleWidth - .Width) / 2
End With
With dg
     .left = 0
     .Width = Me.ScaleWidth
     .Height = Me.ScaleHeight - .top - sb.Height
End With
End Sub

Private Sub dg_RowColChange(LastRow As Variant, ByVal LastCol As Integer)
On Error Resume Next
Dim i As Integer, iCol As Integer
Debug.Print dg.Col, dg.Row, dg.Columns.Item(dg.Col).Caption
If dg.Row > -1 And dg.Col > -1 Then
   Select Case dg.Columns.Item(dg.Col).Caption
          Case "医生"
               dg.Text = cbDoctor.Text
          Case "编号"
               dg.Text = cbNo.Text
          Case "日期"
               dg.Text = CDate(txtDate.Text)
          Case Else
               If dg.Text = "" Then
                  dg.Text = 0
               End If
   End Select
End If
End Sub

Private Sub dg_BeforeColEdit(ByVal ColIndex As Integer, ByVal KeyAscii As Integer, Cancel As Integer)
If dg.Columns.Item(ColIndex).Caption = "医生" _
    Or dg.Columns.Item(ColIndex).Caption = "编号" _
    Or dg.Columns.Item(ColIndex).Caption = "日期" Then
   Cancel = True
End If
End Sub

Private Sub dg_KeyUp(KeyCode As Integer, Shift As Integer)
If KeyCode = vbKeyReturn Then
   SendKeys "{TAB}"
End If

If Shift = vbCtrlMask And KeyCode = vbKeyQ Then
   cbNo.SetFocus
End If
End Sub

Private Sub txtDate_Change()
If Not IsDate(txtDate.Text) Then
   Exit Sub
End If
Find
End Sub

Private Sub Find()
With frmMain.Ado
     .RecordSource = "Select * From data Where 编号 = CINT(" _
                     & cbNo.Text & ") and 日期 = CDate('" & txtDate.Text & "')"
     .Refresh
End With
End Sub

Private Sub cbNo_Click()
FindDoc
Find
End Sub

Private Function FindDoc() As String
With frmMain.Ado
     .RecordSource = "Select 医生 From doctor Where 编号 = CINT(" _
                     & cbNo.Text & ")"
     .Refresh
     cbDoctor.Text = .Recordset.Fields.Item("医生")
End With
End Function

Private Sub cbDoctor_Click()
FindNo
Find
End Sub

Private Function FindNo() As Integer
With frmMain.Ado
     .RecordSource = "Select 编号 From doctor Where 医生 = '" _
                     & cbDoctor.Text & "'"
     .Refresh
     cbNo.Text = .Recordset.Fields.Item("编号")
End With
End Function
