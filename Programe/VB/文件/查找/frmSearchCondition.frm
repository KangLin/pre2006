VERSION 5.00
Begin VB.Form frmSearchCondition 
   Caption         =   "查找条件"
   ClientHeight    =   4020
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8085
   LinkTopic       =   "Form1"
   ScaleHeight     =   4020
   ScaleWidth      =   8085
   StartUpPosition =   1  '所有者中心
   Begin VB.TextBox txtMax 
      Height          =   270
      Left            =   3720
      TabIndex        =   2
      Top             =   240
      Width           =   855
   End
   Begin VB.TextBox txtMin 
      Height          =   270
      Left            =   1920
      TabIndex        =   1
      Top             =   240
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "文件大小:"
      Height          =   255
      Left            =   480
      TabIndex        =   0
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "frmSearchCondition"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

