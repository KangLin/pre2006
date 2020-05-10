VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5175
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7080
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5175
   ScaleWidth      =   7080
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton cmdSave 
      Caption         =   "保存为"
      Height          =   375
      Left            =   6120
      TabIndex        =   7
      Top             =   720
      Width           =   855
   End
   Begin VB.Frame Frame1 
      Height          =   4335
      Left            =   240
      TabIndex        =   4
      Top             =   360
      Width           =   5775
      Begin VB.PictureBox Pic 
         AutoRedraw      =   -1  'True
         BackColor       =   &H8000000E&
         Height          =   3735
         Left            =   120
         ScaleHeight     =   3675
         ScaleWidth      =   4275
         TabIndex        =   6
         Top             =   360
         Width           =   4335
      End
      Begin MSComctlLib.Slider Sld 
         Height          =   3975
         Left            =   4800
         TabIndex        =   5
         Top             =   240
         Width           =   600
         _ExtentX        =   1058
         _ExtentY        =   7011
         _Version        =   393216
         Orientation     =   1
         TickStyle       =   1
      End
   End
   Begin MSComctlLib.StatusBar StB 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   4920
      Width           =   7080
      _ExtentX        =   12488
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   4
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            Bevel           =   2
            Enabled         =   0   'False
            Text            =   "图标总数："
            TextSave        =   "图标总数："
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            Bevel           =   2
            Text            =   "正在显示的是："
            TextSave        =   "正在显示的是："
         EndProperty
         BeginProperty Panel4 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton cmdBrow 
      Caption         =   "浏览(&B)..."
      Height          =   255
      Left            =   5520
      TabIndex        =   2
      Top             =   0
      Width           =   1095
   End
   Begin VB.TextBox txtFileName 
      Height          =   270
      Left            =   1680
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   0
      Width           =   3615
   End
   Begin MSComDlg.CommonDialog CDiag 
      Left            =   1800
      Top             =   1320
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "要提取图标的文件:"
      Height          =   180
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1530
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'Private Const SRCCOPY = &HCC0020
'Private Type Size
'        cx As Long
'        cy As Long
'End Type
Private Declare Function GetObject Lib "gdi32" Alias "GetObjectA" (ByVal hObject As Long, ByVal nCount As Long, lpObject As Any) As Long
Private Type BITMAP
        bmType As Long
        bmWidth As Long
        bmHeight As Long
        bmWidthBytes As Long
        bmPlanes As Integer
        bmBitsPixel As Integer
        bmBits As Long
End Type
'Private Declare Function DeleteDC Lib "gdi32" (ByVal hdc As Long) As Long
'Private Declare Function DeleteObject Lib "gdi32" (ByVal hObject As Long) As Long
'Private Declare Function BitBlt Lib "gdi32" (ByVal hDestDC As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal dwRop As Long) As Long
'Private Declare Function SelectObject Lib "gdi32" (ByVal hdc As Long, ByVal hObject As Long) As Long
'Private Declare Function GetBitmapDimensionEx Lib "gdi32" (ByVal hBitmap As Long, lpDimension As Size) As Long
'Private Declare Function CreateCompatibleBitmap Lib "gdi32" (ByVal hdc As Long, ByVal nWidth As Long, ByVal nHeight As Long) As Long
'Private Declare Function CreateCompatibleDC Lib "gdi32" (ByVal hdc As Long) As Long

Private Declare Function ExtractIcon Lib "shell32.dll" Alias "ExtractIconA" (ByVal hInst As Long, ByVal lpszExeFileName As String, ByVal nIconIndex As Long) As Long
Private Declare Function DrawIcon Lib "user32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal hIcon As Long) As Long
Private Declare Function GetDC Lib "user32" (ByVal hWnd As Long) As Long

Private Sub cmdBrow_Click()
With CDiag
     .DialogTitle = "要提取图标的文件"
     .Filter = "*.exe|*.exe|*.dll|*.dll|*.*|*.*"
     .ShowOpen
     If .FileName <> "" Then
        txtFileName.Text = .FileName
        OpenFile .FileName
     End If
End With
End Sub

Private Sub cmdSave_Click()
With CDiag
     .Filter = "*.bmp|*.bmp|*.*|*.*"
     .DialogTitle = "保存为"
     .FileName = ""
     .ShowSave
     If .FileName <> "" Then
        Call SavePicture(Pic.Image, .FileName)
     End If
End With
End Sub

Private Sub Form_Load()
Me.Caption = "从文件中提取图标"
txtFileName.Text = ""
With Sld
     .Min = 0
     .Max = 1
End With
End Sub

Private Sub Sld_Scroll()
Dim hIcon As Long
Pic.Cls
If txtFileName.Text <> "" Then
   hIcon = ExtractIcon(App.hInstance, txtFileName.Text, Sld.Value)
   If hIcon Then
      StB.Panels(4).Text = Sld.Value
      DrawIcon Pic.hdc, 0, 0, hIcon
   End If
End If
End Sub

Private Sub txtFileName_KeyUp(KeyCode As Integer, Shift As Integer)
If KeyCode = 13 Then
   OpenFile txtFileName.Text
End If
End Sub

Private Sub OpenFile(FileName As String)
Dim Num As Long, hWnd As Long, hdc As Long
Dim i As Long, b As BITMAP
Num = ExtractIcon(App.hInstance, FileName, -1)
Pic.Cls
If Num > 0 Then
   DrawIcon Pic.hdc, 0, 0, ExtractIcon(App.hInstance, FileName, 0)
   'hWnd = ExtractIcon(App.hInstance, txtFileName, 0)
   'hdc = GetObject(hWnd, i, B)
   'hdc = GetBitmapDimensionEx(hWnd, lpSize)
   'hWnd = CreateCompatibleBitmap(Pic.hdc, B.bmWidth, B.bmHeight)
   'hdc = CreateCompatibleDC(Pic.hdc)
   'SelectObject hdc, hWnd
   'BitBlt Pic.hdc, 0, 0, lpSize.cx, lpSize.cy, hdc, 0, 0, SRCCOPY
   'DeleteDC hdc
   StB.Panels(2).Text = Num
   StB.Panels(4).Text = 0
Else
   Num = 1
   StB.Panels(2).Text = 0
   StB.Panels(4).Text = 0
   Pic.Cls
End If
With Sld
    .Min = 0
    .Max = Num
End With
End Sub
