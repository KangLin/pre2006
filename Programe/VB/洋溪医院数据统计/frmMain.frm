VERSION 5.00
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Begin VB.Form frmMain 
   Caption         =   "洋溪医院数据统计"
   ClientHeight    =   6510
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9420
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6510
   ScaleWidth      =   9420
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton cmdPrint 
      Caption         =   "打印(&P)"
      Height          =   375
      Left            =   4320
      TabIndex        =   6
      Top             =   960
      Width           =   1695
   End
   Begin MSDataGridLib.DataGrid DG 
      Height          =   1935
      Left            =   2280
      TabIndex        =   5
      Top             =   1560
      Width           =   4815
      _ExtentX        =   8493
      _ExtentY        =   3413
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
   Begin VB.CommandButton cmdShowDataReport 
      Caption         =   "显示数据报表(&S)"
      Height          =   375
      Left            =   2280
      TabIndex        =   4
      Top             =   960
      Width           =   1695
   End
   Begin VB.CommandButton cmdDelDoc 
      Caption         =   "删除医生(&D)"
      Height          =   375
      Left            =   720
      TabIndex        =   3
      Top             =   2760
      Width           =   1335
   End
   Begin VB.CommandButton cmdAddDoctor 
      Caption         =   "增加医生(&A)"
      Height          =   375
      Left            =   720
      TabIndex        =   2
      Top             =   2160
      Width           =   1335
   End
   Begin VB.CommandButton cmdFind 
      Caption         =   "数据查询(&F)"
      Height          =   375
      Left            =   720
      TabIndex        =   1
      Top             =   1560
      Width           =   1335
   End
   Begin MSAdodcLib.Adodc Ado 
      Height          =   495
      Left            =   600
      Top             =   3720
      Visible         =   0   'False
      Width           =   3495
      _ExtentX        =   6165
      _ExtentY        =   873
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   8
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   1
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   ""
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   ""
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   "select * from data"
      Caption         =   "Ado"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
   End
   Begin VB.CommandButton cmdInputData 
      Caption         =   "数据输入(&I)"
      Height          =   375
      Left            =   720
      TabIndex        =   0
      Top             =   960
      Width           =   1335
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'功能:主窗体
'作者:康林
'时间:2005年6月

Option Explicit

Dim conn As New ADODB.Connection
Dim cmd As New ADODB.Command
Dim rs As ADODB.Recordset

Private Sub Form_Load()
Dim file As String
file = App.Path & "\data.mdb"
Ado.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & file & ";Persist Security Info=False"
End Sub

Private Sub cmdAddDoctor_Click()
With frmAddDoctor
     .m_bAdd = True
     .Show vbModal, Me
End With
Me.SetFocus
End Sub

Private Sub cmdDelDoc_Click()
With frmAddDoctor
     .m_bAdd = False
     .Show vbModal, Me
End With
Me.SetFocus
End Sub

Private Sub cmdFind_Click()
frmFind.Show vbModal, Me
Me.SetFocus
End Sub

Private Sub cmdInputData_Click()
frmInputData.Show vbModal, Me
Me.SetFocus
End Sub

Private Sub cmdShowDataReport_Click()
frmShowDateReport.Show vbModal, Me
Me.SetFocus
End Sub

Private Sub cmdPrint_Click()
frmPrintPreview.Show vbModal, Me
Me.SetFocus
End Sub

