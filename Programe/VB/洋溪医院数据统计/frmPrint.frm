VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmPrintPreview 
   Caption         =   "打印预览"
   ClientHeight    =   3195
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   5.636
   ScaleMode       =   7  'Centimeter
   ScaleWidth      =   8.255
   StartUpPosition =   3  '窗口缺省
   Begin VB.PictureBox picClient 
      Height          =   3015
      Left            =   0
      ScaleHeight     =   5.212
      ScaleMode       =   7  'Centimeter
      ScaleWidth      =   6.906
      TabIndex        =   2
      Top             =   -360
      Width           =   3975
      Begin VB.PictureBox m_picPrint 
         AutoRedraw      =   -1  'True
         BackColor       =   &H80000009&
         BorderStyle     =   0  'None
         Height          =   2535
         Index           =   0
         Left            =   0
         ScaleHeight     =   4.471
         ScaleMode       =   7  'Centimeter
         ScaleWidth      =   7.011
         TabIndex        =   3
         Top             =   0
         Width           =   3975
      End
   End
   Begin VB.HScrollBar HS 
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   2880
      Width           =   1215
   End
   Begin VB.VScrollBar VS 
      Height          =   2535
      Left            =   4440
      TabIndex        =   0
      Top             =   360
      Width           =   255
   End
   Begin MSComDlg.CommonDialog cd 
      Left            =   0
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Menu mnuFile 
      Caption         =   "文件(&F)"
      Begin VB.Menu mnuPrint 
         Caption         =   "打印(&P)"
      End
   End
End
Attribute VB_Name = "frmPrintPreview"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'功能:打印
'作者:康林
'时间:2005年6月

Option Explicit

Dim m_PAW As Single '纸张的宽度
Dim m_PAH As Single '纸张的大小
Dim m_objP As Printer '打印对象

Private Sub Form_Load()
Me.Icon = frmMain.Icon

'所有单位为毫米
Printer.ScaleMode = vbMillimeters
Me.ScaleMode = Printer.ScaleMode
picClient.ScaleMode = Me.ScaleMode
m_picPrint(0).ScaleMode = picClient.ScaleMode

'纸张大小
m_PAW = Printer.ScaleWidth
m_PAH = Printer.ScaleHeight
'Debug.Print "纸张大小:"; m_PAW; m_PAH, Printer.ScaleTop, Printer.ScaleLeft
'Debug.Print Printer.Width, Printer.Height

With g_Para
     .m_bPageNo = True
     .m_iPageNumber = 1
     .m_HeightBetwwenPage = 5
     .m_iPrintNumber = 1
     .m_PosHead = Enum_Postion.TopCenter
     .m_PosTitle = TopCenter
     .m_Height = Printer.ScaleHeight
     .m_Width = Printer.ScaleWidth
     .m_TopBorder = 15
     .m_LeftBorder = 15
     .m_RightBorder = .m_Width - 15
     .m_BottomBorder = .m_Height - 15
End With

If AllPageHeight() - picClient.ScaleHeight > 0 Then
   VS.Max = (AllPageHeight() - picClient.ScaleHeight) + 1
Else
   VS.Max = AllPageHeight() + 1
End If
VS.Min = 0
VS.LargeChange = 10
VS.SmallChange = 5
If AllPageWidth() - picClient.ScaleWidth > 0 Then
   HS.Max = (AllPageWidth() - picClient.ScaleWidth) + 1
Else
   HS.Max = AllPageWidth() + 1
End If
HS.Min = 0
HS.LargeChange = 10
HS.SmallChange = 5

'AddPage

AdjustPagePostion 0, 0
End Sub

Private Sub Form_Resize()
picClient.top = 0
picClient.left = 0
picClient.Width = Me.ScaleWidth - VS.Width
picClient.Height = Me.ScaleHeight - HS.Height

If AllPageWidth() < picClient.ScaleWidth Then
   HS.Visible = False
   AdjustPagePostion m_picPrint(0).top, (picClient.ScaleWidth - AllPageWidth()) / 2
Else
   HS.Visible = True
   HS.Max = (AllPageWidth() - picClient.ScaleWidth) + 1
   AdjustPagePostion m_picPrint(0).top, m_picPrint(0).left
End If
If AllPageHeight() < picClient.ScaleHeight Then
   VS.Visible = False
   AdjustPagePostion (picClient.ScaleHeight - AllPageHeight()) / 2, m_picPrint(0).left
Else
   VS.Visible = True
   VS.Max = (AllPageHeight - picClient.ScaleWidth) + 1
   AdjustPagePostion m_picPrint(0).top, m_picPrint(0).left
End If
With VS
     .left = Me.ScaleWidth - .Width
     .top = 0
     .Height = Me.ScaleHeight - HS.Height
End With
With HS
     .top = Me.ScaleHeight - .Height
     .Width = Me.ScaleWidth - VS.Width
     .left = 0
End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
Printer.KillDoc
End Sub

Private Sub mnuPrint_Click()
Printer.EndDoc
End Sub

Private Sub HS_Change()
AdjustPagePostion m_picPrint(0).top, -HS.Value
End Sub

Private Sub HS_Scroll()
AdjustPagePostion m_picPrint(0).top, -HS.Value
End Sub

Private Sub VS_Change()
AdjustPagePostion -VS.Value, m_picPrint(0).left
End Sub

Private Sub VS_Scroll()
AdjustPagePostion -VS.Value, m_picPrint(0).left
End Sub

'调整所有页的位置
Private Function AdjustPagePostion(ByVal top As Single, ByVal left As Single)
Dim Max As Integer, i As Integer

Max = m_picPrint.UBound
For i = 0 To Max
    m_picPrint(i).top = top + i * (m_PAH + g_Para.m_HeightBetwwenPage)
    m_picPrint(i).left = left
    m_picPrint(i).Height = m_PAH
    m_picPrint(i).Width = m_PAW
Next i

If -top > 0 Then
   VS.Value = -top
End If
If -left > 0 Then
   HS.Value = -left
End If
End Function

'增加一页
Private Function AddPage()
Load m_picPrint(m_picPrint.Count)
m_picPrint(m_picPrint.UBound).Visible = True '控件运行时加载,默认为FALSE
g_Para.m_iPageNumber = m_picPrint.Count

If AllPageHeight() - picClient.ScaleHeight > 0 Then
   VS.Max = (AllPageHeight() - picClient.ScaleHeight) + 1
Else
   VS.Max = AllPageHeight() + 1
End If
If AllPageWidth() - picClient.ScaleWidth > 0 Then
   HS.Max = (AllPageWidth() - picClient.ScaleWidth) + 1
Else
   HS.Max = AllPageWidth() + 1
End If
VS.Min = 0
HS.Min = 0

AdjustPagePostion m_picPrint(0).top, m_picPrint(0).left
Me.Refresh
End Function

'所有页的总长度
Private Function AllPageHeight() As Single
Dim Max As Integer
Max = g_Para.m_iPageNumber
AllPageHeight = Max * m_PAH + g_Para.m_HeightBetwwenPage * (Max - 1)
End Function

Private Function AllPageWidth() As Single
AllPageWidth = m_PAW
End Function

'打印属性
Public Property Get CurrentX1() As Single
CurrentX1 = Printer.CurrentX
End Property

Public Property Let CurrentX1(ByVal X As Single)
Printer.CurrentX = X
m_picPrint(m_picPrint.UBound).CurrentX = X
End Property

Public Property Get CurrentY1() As Single
CurrentY1 = Printer.CurrentY
End Property

Public Property Let CurrentY1(ByVal Y As Single)
Printer.CurrentY = Y
m_picPrint(m_picPrint.UBound).CurrentY = Y
End Property

Public Sub Print1(ByVal Str As String)
m_picPrint(m_picPrint.UBound).Print Str
Printer.Print Str
End Sub

Public Sub NewPage()
Printer.NewPage
AddPage
End Sub

Public Sub EndDoc()
Printer.EndDoc
End Sub

