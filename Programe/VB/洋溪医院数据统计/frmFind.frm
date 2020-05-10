VERSION 5.00
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Begin VB.Form frmFind 
   Caption         =   "查找"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7230
   Icon            =   "frmFind.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   7230
   StartUpPosition =   1  '所有者中心
   WindowState     =   2  'Maximized
   Begin MSDataGridLib.DataGrid dg 
      Height          =   1935
      Left            =   120
      TabIndex        =   4
      Top             =   840
      Width           =   6135
      _ExtentX        =   10821
      _ExtentY        =   3413
      _Version        =   393216
      AllowUpdate     =   0   'False
      AllowArrows     =   -1  'True
      HeadLines       =   1
      RowHeight       =   15
      TabAction       =   2
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
   Begin VB.Frame fram 
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   6975
      Begin VB.CommandButton cmdFind 
         Caption         =   "查询(&F)"
         Default         =   -1  'True
         Height          =   420
         Left            =   5880
         TabIndex        =   3
         Top             =   240
         Width           =   855
      End
      Begin VB.TextBox txtSQL 
         Height          =   270
         Left            =   1080
         TabIndex        =   2
         Text            =   "txtSQL"
         Top             =   240
         Width           =   4455
      End
      Begin VB.Label Label1 
         Caption         =   "SQL语句："
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   855
      End
   End
End
Attribute VB_Name = "frmFind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'功能:查找数据窗体
'作者:康林
'时间:2005年6月

Option Explicit

Private Sub cmdFind_Click()
With frmMain.Ado
     .RecordSource = txtSQL.Text
     .Refresh
End With
dg.Visible = True
End Sub

Private Sub Form_Load()
Me.Icon = frmMain.Icon
Set dg.DataSource = frmMain.Ado
dg.Visible = False
txtSQL.Text = ""
End Sub

Private Sub Form_Resize()
fram.left = (Me.ScaleWidth - fram.Width) / 2
With dg
     .Height = Me.ScaleHeight - .top
     .Width = Me.ScaleWidth
     .left = 0
End With
End Sub
