VERSION 5.00
Begin VB.Form 帮助关于对话框 
   BorderStyle     =   5  'Sizable ToolWindow
   Caption         =   "版本信息"
   ClientHeight    =   5760
   ClientLeft      =   2775
   ClientTop       =   3705
   ClientWidth     =   7320
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5760
   ScaleWidth      =   7320
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton OKButton 
      Caption         =   "退出"
      Height          =   375
      Left            =   5880
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Label6"
      ForeColor       =   &H00000000&
      Height          =   180
      Left            =   240
      TabIndex        =   6
      Top             =   120
      Visible         =   0   'False
      Width           =   540
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      Caption         =   "时间:2001年2月"
      ForeColor       =   &H00FF0000&
      Height          =   180
      Left            =   3600
      TabIndex        =   5
      Top             =   3480
      Width           =   1260
   End
   Begin VB.Label Label4 
      Caption         =   "版本：2001"
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   2160
      TabIndex        =   4
      Top             =   3480
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "开发"
      Height          =   255
      Left            =   3240
      TabIndex        =   3
      Top             =   3120
      Width           =   375
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "康林"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   41.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000080FF&
      Height          =   975
      Left            =   2520
      TabIndex        =   2
      Top             =   1920
      Width           =   2175
   End
   Begin VB.Label Label1 
      Caption         =   " 本程序由"
      Height          =   255
      Left            =   3000
      TabIndex        =   1
      Top             =   1560
      Width           =   975
   End
End
Attribute VB_Name = "帮助关于对话框"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub Form_Load()
Label6.Caption = _
"一.功能:" + Chr$(13) + _
"   此围棋程序具有自动提子功能" + Chr$(13) + _
"二.菜单功能:" + Chr$(13) + _
"   1.文件菜单:" + Chr$(13) + _
"     a.保存:" + Chr$(13) + _
"       能保存本次所下的棋,以便以后复盘;或者未下完的棋,以便以后再下" + Chr$(13) + _
"     b.复盘:" + Chr$(13) + _
"       能重复以前所下过的棋;并能显示走棋的步数" + Chr$(13) + _
"     c.装入上盘棋:" + Chr$(13) + _
"       能接着以前未下完的棋继续下" + Chr$(13) + _
"     d.退出:" + Chr$(13) + _
"   2.工具菜单:" + Chr$(13) + _
"     a.悔棋:" + Chr$(13) + _
"       当走错棋时,使用此项.此项能自动恢复被提的子" + Chr$(13) + _
"     b.还原:" + Chr$(13) + _
"       当悔错棋时使用此项" + Chr$(13) + _
"     c.提子。本程序具有自动提子功能。" + Chr$(13) + _
"     d.走子:" + Chr$(13) + _
"       当在提子环境下要走棋时,使用此项" + Chr$(13) + _
"     e.重新开始:" + Chr$(13) + _
"       当一盘棋走完,重新开始一盘棋:" + Chr$(13) + _
"     f.显示时间:" + Chr$(13) + "     g.显示工具:" + Chr$(13) + _
"       当复选标志显示时,显示工具按钮,否则隐藏工具按钮" + Chr$(13) + _
"三.鼠标右键功能:" + Chr$(13) + "    单击标右键,能显示工具菜单"
End Sub

Private Sub OKButton_Click()
Unload Me '帮助对话框
End Sub

