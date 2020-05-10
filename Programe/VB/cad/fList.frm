VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form fList 
   Caption         =   "实体列表"
   ClientHeight    =   5445
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7635
   LinkTopic       =   "Form1"
   MinButton       =   0   'False
   ScaleHeight     =   5445
   ScaleWidth      =   7635
   StartUpPosition =   1  '所有者中心
   Begin VB.CheckBox CK 
      Caption         =   "在配置文件中保存选取的实体类型"
      Height          =   255
      Left            =   3960
      TabIndex        =   6
      Top             =   240
      Width           =   3735
   End
   Begin VB.ComboBox CB 
      Height          =   345
      Left            =   1440
      TabIndex        =   4
      Text            =   "Combo1"
      Top             =   120
      Width           =   2535
   End
   Begin VB.CommandButton command_candle 
      Caption         =   "取消"
      Height          =   375
      Left            =   5040
      TabIndex        =   3
      Top             =   4440
      Width           =   1575
   End
   Begin VB.CommandButton OK_command 
      Caption         =   "确定"
      Default         =   -1  'True
      Height          =   375
      Left            =   840
      TabIndex        =   2
      Top             =   4440
      Width           =   1335
   End
   Begin MSComctlLib.StatusBar StB 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   5190
      Visible         =   0   'False
      Width           =   7635
      _ExtentX        =   13467
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ListView LV 
      Height          =   3615
      Left            =   240
      TabIndex        =   0
      Top             =   600
      Width           =   6975
      _ExtentX        =   12303
      _ExtentY        =   6376
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.Label Lb 
      AutoSize        =   -1  'True
      Caption         =   "实体类型:"
      Height          =   180
      Left            =   240
      TabIndex        =   5
      Top             =   240
      Width           =   810
   End
End
Attribute VB_Name = "fList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'作者:康林

Option Explicit
Dim fHeight As Single
Dim fWidth As Single
Dim lvTop As Single
Dim lvLeft As Single
Dim lvWidth As Single
Dim lvHeight As Single
Dim cbTop  As Single
Dim cbLeft As Single
Dim okTop As Single
Dim okLeft As Single
Dim lbtop As Single
Dim lbleft As Single
Dim ckTop As Single
Dim ckLeft As Single
Dim ccTop As Single
Dim ccLeft As Single

Private Sub CB_Click()
        fMainForm.ActiveForm.ObjectList CB.ListIndex
End Sub

Private Sub CK_Click()
Dim i
       i = WritePrivateProfileString("实体列表", "保存实体列表", CStr(CK.Value), Inifile)
End Sub

Private Sub command_candle_Click()
        Unload Me
End Sub

Private Sub Form_Load()
Dim i, ss As String * 20
        CB.AddItem "线段"
        CB.AddItem "曲线"
        CB.AddItem "文字"
        CB.text = "线段"
        With Me
             fHeight = .Height
             fWidth = .Width
        End With
        With LV
             lvTop = .top
             lvLeft = .left
             lvWidth = .Width
             lvHeight = .Height
        End With
        With CB
             cbTop = .top
             cbLeft = .left
        End With
        With LB
             lbtop = .top
             lbleft = .left
        End With
        With CK
             ckTop = .top
             ckLeft = .left
        End With
        With Me.OK_command
             okTop = .top
             okLeft = .left
        End With
        With Me.command_candle
             ccTop = .top
             ccLeft = .left
        End With
        i = GetPrivateProfileString("实体列表", "保存实体列表", "0", ss, 20, Inifile)
        If i = 0 Then
           CK.Value = 0
        Else
           CK.Value = Val(left$(ss, i))
        End If
End Sub

Private Sub Form_Resize()
If Me.Height < fHeight Or Me.Width < fWidth Then
     With Me
          .Height = fHeight
          .Width = fWidth
     End With
     With LV
          .Height = lvHeight
          .Width = lvWidth
          .top = lvTop
          .left = lvLeft
     End With
     With CB
          .top = cbTop
          .left = cbLeft
     End With
     With Me.OK_command
          .top = okTop
          .left = okLeft
     End With
     With Me.command_candle
          .top = ccTop
          .left = ccLeft
     End With
     With LB
          .top = lbtop
          .left = lbleft
     End With
     With CK
          .top = ckTop
          .left = ckLeft
     End With
Else
        LV.left = 200
        With OK_command
             .left = LV.left + 200
             .top = Me.ScaleHeight - StB.Height - 600
        End With
        Me.command_candle.left = Me.Scalewidth - 200 - Me.command_candle.Width
        Me.command_candle.top = Me.OK_command.top
        CB.top = 200
        LB.top = CB.top
        CK.top = LB.top
        LV.top = CB.Height + CB.top + 200
        LV.Width = Me.Scalewidth - 400
        'LV.Height = Me.ScaleHeight - LV.top - StB.Height - OK_command.top - 200
End If
End Sub

Private Sub OK_command_Click()
Dim i
        If CK.Value Then
           i = WritePrivateProfileString("实体列表", "实体类型", CB.text, Inifile)
        End If
        Unload Me
End Sub
