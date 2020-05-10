VERSION 5.00
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Begin VB.Form frmShowDateReport 
   Caption         =   "显示数据报表"
   ClientHeight    =   6135
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8085
   LinkTopic       =   "Form1"
   ScaleHeight     =   6135
   ScaleWidth      =   8085
   StartUpPosition =   1  '所有者中心
   Begin VB.CheckBox chkAll 
      Caption         =   "选择所有医生"
      Height          =   255
      Left            =   240
      TabIndex        =   11
      Top             =   1200
      Width           =   2055
   End
   Begin MSDataGridLib.DataGrid dg 
      Height          =   4455
      Left            =   0
      TabIndex        =   10
      Top             =   1680
      Width           =   8055
      _ExtentX        =   14208
      _ExtentY        =   7858
      _Version        =   393216
      HeadLines       =   1
      RowHeight       =   15
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
   Begin VB.CommandButton cmdExit 
      Caption         =   "退出(&E)"
      Height          =   375
      Left            =   6480
      TabIndex        =   9
      Top             =   1080
      Width           =   1335
   End
   Begin VB.CommandButton cmdPreview 
      Caption         =   "预览(&V)"
      Height          =   375
      Left            =   4560
      TabIndex        =   8
      Top             =   1080
      Width           =   1335
   End
   Begin VB.CommandButton cmdPrint 
      Caption         =   "打印(&P)"
      Height          =   375
      Left            =   2760
      TabIndex        =   7
      Top             =   1080
      Width           =   1215
   End
   Begin VB.Frame framSelect 
      Height          =   735
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   7575
      Begin VB.ComboBox cbDoctor 
         Height          =   300
         ItemData        =   "frmShowDateReport.frx":0000
         Left            =   1080
         List            =   "frmShowDateReport.frx":0002
         TabIndex        =   3
         Text            =   "cbDoctor"
         Top             =   240
         Width           =   1695
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
      Begin VB.ComboBox cbNo 
         Height          =   300
         Left            =   3840
         TabIndex        =   1
         Text            =   "cbNo"
         Top             =   240
         Width           =   1455
      End
      Begin VB.Label Label1 
         Caption         =   "选择医生："
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   240
         Width           =   1095
      End
      Begin VB.Label Label2 
         Caption         =   "医生编号："
         Height          =   255
         Left            =   2880
         TabIndex        =   5
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label3 
         Caption         =   "日期："
         Height          =   255
         Left            =   5400
         TabIndex        =   4
         Top             =   240
         Width           =   615
      End
   End
End
Attribute VB_Name = "frmShowDateReport"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'功能:显示数报表
'作者:康林
'时间:2005年6月

Option Explicit

Dim frmP As frmPrintPreview
Dim rs As ADODB.Recordset

Private Sub chkAll_Click()
If chkAll.Value = vbChecked Then
   cbDoctor.Enabled = False
   cbNo.Enabled = False
Else
  cbDoctor.Enabled = True
   cbNo.Enabled = True
End If
Find
End Sub

Private Sub cmdExit_Click()
Unload Me
End Sub

Private Sub cmdPreview_Click()
cmdPrint_Click
frmP.Show vbModal, Me
End Sub

Private Sub cmdPrint_Click()
PrintTable
frmP.Show vbModal, Me
End Sub

Private Sub Form_Load()
Me.Icon = frmMain.Icon
Set frmP = New frmPrintPreview
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
txtDate.Text = Date
Set dg.DataSource = frmMain.Ado
End Sub

Private Sub Form_Unload(Cancel As Integer)
Unload frmP
End Sub

Private Sub txtDate_Change()
If Not IsDate(txtDate.Text) Then
   Exit Sub
End If
Find
End Sub

Private Sub Find()
Dim sql As String
If chkAll.Value = vbChecked Then
   sql = "Select doctor.医生 as 医生, data.* From data, doctor Where data.编号 = doctor.编号 and data.日期 = CDate('" _
          & txtDate.Text & "') Order by data.编号 asc"
Else
   sql = "Select * From data Where 编号 = CINT(" _
                     & cbNo.Text & ") and 日期 = CDate('" & txtDate.Text & "')"
End If
With frmMain.Ado
     .RecordSource = sql
     .Refresh
     Set rs = .Recordset
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

Private Sub PrintTable()
Dim i As Integer, w As Single, h As Single, cury As Integer
w = Printer.TextWidth("00000.00")
h = Printer.TextHeight("00000.00")
cury = Printer.CurrentY
With frmP
     For i = 0 To rs.Fields.Count - 1
         .Print1 rs.Fields(i).Name
         .CurrentX1 = Printer.CurrentX + w
         .CurrentY1 = Printer.CurrentY - h
     Next
End With
End Sub
