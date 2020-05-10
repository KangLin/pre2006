VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form inputtextbox 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "文本输入"
   ClientHeight    =   3195
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6030
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin RichTextLib.RichTextBox text 
      Height          =   1695
      Left            =   240
      TabIndex        =   5
      Top             =   1080
      Width           =   5535
      _ExtentX        =   9763
      _ExtentY        =   2990
      _Version        =   393217
      DisableNoScroll =   -1  'True
      AutoVerbMenu    =   -1  'True
      TextRTF         =   $"inputtextbox.frx":0000
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "取消"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "确定"
      Height          =   375
      Left            =   4680
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "请输入你要输入的文本:"
      Height          =   180
      Left            =   480
      TabIndex        =   4
      Top             =   720
      Width           =   1890
   End
   Begin VB.Label color 
      AutoSize        =   -1  'True
      Caption         =   "字体颜色"
      Height          =   180
      Left            =   1560
      MouseIcon       =   "inputtextbox.frx":0286
      MousePointer    =   99  'Custom
      TabIndex        =   3
      Top             =   240
      Width           =   720
   End
   Begin VB.Label font 
      AutoSize        =   -1  'True
      Caption         =   "字体型号"
      Height          =   180
      Left            =   480
      MouseIcon       =   "inputtextbox.frx":0590
      MousePointer    =   99  'Custom
      TabIndex        =   2
      Top             =   240
      Width           =   720
   End
End
Attribute VB_Name = "inputtextbox"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'文本输入窗口

Option Explicit
        
Private Sub CancelButton_Click()
        Unload Me
End Sub

Private Sub color_Click()
        Form1.CommonDialog1.ShowColor
        text.SelColor = Form1.CommonDialog1.color
End Sub

Private Sub font_Click()
        Form1.CommonDialog1.ShowFont
        With text.font
             .Bold = Form1.CommonDialog1.FontBold
             .Italic = Form1.CommonDialog1.FontItalic
             .name = Form1.CommonDialog1.FontName
             .size = Form1.CommonDialog1.FontSize
             .Strikethrough = Form1.CommonDialog1.FontStrikethru
             .Underline = Form1.CommonDialog1.FontUnderline
        End With
End Sub

Private Sub Form_Load()
        text.SelColor = Form1.cad.ForeColor     '保存以前的颜色
        With text.font
             .Bold = Form1.cad.FontBold
             .Italic = Form1.cad.FontItalic
             .name = Form1.cad.FontName
             .size = Form1.cad.FontSize
             .Strikethrough = Form1.cad.FontStrikethru
             .Underline = Form1.cad.FontUnderline
        End With
End Sub

Private Sub OKButton_Click()
        Form1.cad.ForeColor = Form1.CommonDialog1.color
        With Form1.cad.font
             .Bold = Form1.CommonDialog1.FontBold
             .Italic = Form1.CommonDialog1.FontItalic
             .name = Form1.CommonDialog1.FontName
             .size = Form1.CommonDialog1.FontSize
             .Strikethrough = Form1.CommonDialog1.FontStrikethru
             .Underline = Form1.CommonDialog1.FontUnderline
        End With
        ReDim Preserve user.TextType(UBound(user.TextType) + 1)
        With user.TextType(UBound(user.textype))
             .X = Form1.cad.CurrentX
             .Y = Form1.cad.CurrentY
             .string = text.text
             .font.Bold = Form1.CommonDialog1.FontBold
             .font.Italic = Form1.CommonDialog1.FontItalic
             .font.name = Form1.CommonDialog1.FontName
             .font.size = Form1.CommonDialog1.FontSize
             .font.Strikethrough = Form1.CommonDialog1.FontStrikethru
             .font.Underline = Form1.CommonDialog1.FontUnderline
             .font.color = Form1.cad.ForeColor
              End With
        Unload Me
End Sub

