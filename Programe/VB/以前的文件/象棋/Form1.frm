VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form Form2 
   Caption         =   "Form2"
   ClientHeight    =   6240
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9285
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   ScaleHeight     =   6240
   ScaleWidth      =   9285
   StartUpPosition =   3  '窗口缺省
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   5985
      Width           =   9285
      _ExtentX        =   16378
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin MSFlexGridLib.MSFlexGrid MSF 
      Height          =   4575
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   8775
      _ExtentX        =   15478
      _ExtentY        =   8070
      _Version        =   393216
   End
   Begin VB.Label Lab 
      Caption         =   "Label1"
      Height          =   615
      Left            =   240
      TabIndex        =   2
      Top             =   120
      Width           =   8535
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Const s形势分析表 = "形势分析表"
Const s位置 = "位置"
Const s甲方有 = "甲方有"
Const s乙方有 = "乙方有"
Const s棋 = "棋"

Public Function WindowsCommand(Param As Enum_Windows_style, iQiJu() As Integer)
Call fXinShiFenXiBiao(iQiJu)
Me.Caption = s形势分析表
Me.Show , Form1
End Function

Private Sub fXinShiFenXiBiao(iQiJu() As Integer)
Dim I As Integer, j As Integer, K As Long
Dim XinShiBiao(9, 10) As Type_XinShiFenXiBiao
Dim jQZ() As Integer, yQZ() As Integer
Call XinShiFenXi(iQiJu, XinShiBiao, jQZ, yQZ)
With Lab
     .Top = 0
     .Left = MSF.Left
     .Width = MSF.Width
     .Caption = s甲方有 & UBound(jQZ) & s棋 & ":"
     For K = 1 To UBound(jQZ)
         .ForeColor = vbRed
         .Caption = .Caption & Read_QiZhi(QiJuBianMa(I, j, jQZ(K), 进行解码))
         .ForeColor = vbBlack
         .Caption = .Caption & "(" & s横座标 & I & s纵座标 & j & ")"
     Next K
     .Caption = .Caption & Chr$(10) & Chr$(13) & s乙方有 & UBound(jQZ) & s棋 & ":"
     For K = 1 To UBound(yQZ)
         .ForeColor = vbBlue
         .Caption = .Caption & Read_QiZhi(QiJuBianMa(I, j, yQZ(K), 进行解码))
         .ForeColor = vbBlack
         .Caption = .Caption & "(" & s横座标 & I & s纵座标 & j & ")"
     Next K
     .Visible = True
End With
With MSF
     .AllowUserResizing = flexResizeBoth
     .Clear
     .Top = Lab.Height + 100
     .Rows = 1
     .Cols = 10
     .Row = 0
     For I = 1 To 9
         .Col = I
         .Text = I
     Next I
     For I = 1 To 10
         .AddItem I
     Next I
     For I = 1 To 9
         For j = 1 To 10
             .Col = I
             .Row = j
             .Text = Read_QiZhi(iQiJu(I, j)) & ";" & Read_Controled(XinShiBiao(I, j).XinShi) & "(" & XinShiBiao(I, j).XinShi & ")"
         Next j
     Next I
End With
End Sub
