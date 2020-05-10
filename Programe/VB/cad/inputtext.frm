VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form InputText 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "输入文字"
   ClientHeight    =   4260
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6630
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4260
   ScaleWidth      =   6630
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton Command1 
      Caption         =   "取消"
      Height          =   375
      Left            =   5040
      TabIndex        =   4
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton okbutton 
      Caption         =   "确定"
      Height          =   375
      Left            =   5040
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin RichTextLib.RichTextBox rt 
      Height          =   1995
      Left            =   1200
      TabIndex        =   2
      Top             =   1560
      Width           =   3000
      _ExtentX        =   5292
      _ExtentY        =   3519
      _Version        =   393217
      Enabled         =   -1  'True
      ScrollBars      =   3
      TextRTF         =   $"inputtext.frx":0000
   End
   Begin VB.Label textcolor 
      AutoSize        =   -1  'True
      Caption         =   "字体颜色"
      Height          =   180
      Left            =   3120
      MouseIcon       =   "inputtext.frx":023A
      MousePointer    =   99  'Custom
      TabIndex        =   1
      Top             =   360
      Width           =   720
   End
   Begin VB.Label text 
      AutoSize        =   -1  'True
      Caption         =   "字体"
      Height          =   180
      Left            =   960
      MouseIcon       =   "inputtext.frx":0544
      MousePointer    =   99  'Custom
      TabIndex        =   0
      Top             =   360
      Width           =   360
   End
End
Attribute VB_Name = "InputText"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'功能:文字输入
'作者:康林

Option Explicit

Public xx As Single
Public yy As Single
Public TPoint As Long
Public ModifyFlag As Boolean '从修改文字中调用

Private Sub Command1_Click()
        Unload Me
End Sub

Private Sub Form_Load()
        Form_Resize
End Sub

Private Sub Form_Resize()
If Not ModifyFlag Then
        With rt
             .Font = fMainForm.ActiveForm.cad.Font
             .BackColor = fMainForm.ActiveForm.cad.BackColor
             .SelColor = fMainForm.ActiveForm.cad.ForeColor
        End With
End If
        rt.Move 300, 1200, 6000, 2800
End Sub

Private Sub OKButton_Click()
If ModifyFlag Then
   Me.Hide
Else
     If Not TPoint Then
        With fMainForm.ActiveForm.cad
             fMainForm.ActiveForm.AddText xx, yy, rt.text, 0, 0
             .Font = rt.Font
             .ForeColor = rt.SelColor
        End With
        Unload Me
     Else
        fMainForm.ActiveForm.DimensionText xx, yy, rt.text, TPoint
     End If
End If
End Sub

Private Sub text_Click()
        With fOption.CommonDialog1
             .FontBold = fMainForm.ActiveForm.cad.FontBold
             .FontItalic = fMainForm.ActiveForm.cad.FontItalic
             .FontName = fMainForm.ActiveForm.cad.FontName
             .FontSize = fMainForm.ActiveForm.cad.FontSize
             .FontStrikethru = fMainForm.ActiveForm.cad.FontStrikethru
             .FontUnderline = fMainForm.ActiveForm.cad.FontUnderline
             .Color = fMainForm.ActiveForm.cad.ForeColor
             .Flags = 3
             .FontName = rt.Font.name
             .FontSize = rt.Font.Size
             .ShowFont
             rt.Font.Bold = .FontBold    ' fMainForm.ActiveForm.cad.Font
             rt.Font.name = .FontName
             rt.Font.Size = .FontSize
             rt.Font.Italic = .FontItalic
             rt.Font.Underline = .FontUnderline
             rt.Font.Strikethrough = .FontStrikethru
        End With
End Sub

Private Sub textcolor_Click()
   With fOption.CommonDialog1
        .Flags = 3
        rt.SelStart = 0
        rt.SelLength = Len(rt.text)
        .Color = rt.SelColor
       ' .Color = fMainForm.ActiveForm.cad.ForeColor
        .ShowColor
        rt.BackColor = fMainForm.ActiveForm.cad.BackColor
        rt.SelColor = .Color
        rt.Refresh
        rt.SelLength = 0
   End With
End Sub
