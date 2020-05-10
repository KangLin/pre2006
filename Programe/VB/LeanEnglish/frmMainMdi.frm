VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.MDIForm frmMainMdi 
   BackColor       =   &H8000000C&
   Caption         =   "MDIForm1"
   ClientHeight    =   6510
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   6285
   LinkTopic       =   "MDIForm1"
   Picture         =   "frmMainMdi.frx":0000
   StartUpPosition =   2  '屏幕中心
   WindowState     =   2  'Maximized
   Begin MSComDlg.CommonDialog ComD 
      Left            =   2400
      Top             =   2280
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   630
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   6285
      _ExtentX        =   11086
      _ExtentY        =   1111
      ButtonWidth     =   1138
      ButtonHeight    =   953
      Appearance      =   1
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   11
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "打开"
            Key             =   "open"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "增加"
            Key             =   "add"
            Style           =   1
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "删除"
            Key             =   "delete"
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "同义词"
            Key             =   "same"
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "反义词"
            Key             =   "de"
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "相似词"
            Key             =   "like"
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "关联词"
            Key             =   "relation"
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "日期"
            Key             =   "date"
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "全部"
            Key             =   "all"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "文件(&F)"
      Begin VB.Menu mnuOpen 
         Caption         =   "打开(&O)"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "退出(&E)"
      End
   End
   Begin VB.Menu mnuTool 
      Caption         =   "工具(&T)"
      Begin VB.Menu mnuToolOption 
         Caption         =   "选项(&O)"
      End
      Begin VB.Menu mnuToolBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolBar 
         Caption         =   "工具栏(&B)"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu mnuWindows 
      Caption         =   "窗口(&W)"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowsT 
         Caption         =   "平铺(&T)"
      End
      Begin VB.Menu mnuWindowsC 
         Caption         =   "层叠(&C)"
      End
      Begin VB.Menu mnuWindowsArrory 
         Caption         =   "排列图标(&A)"
      End
   End
End
Attribute VB_Name = "frmMainMdi"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Const meCaption = "学习英语"
Private Declare Function BitBlt Lib "gdi32" (ByVal hDestDC As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal dwRop As Long) As Long

Private Sub MDIForm_Load()
On Error GoTo mdiform_loaderror

Dim Rst As Recordset
Dim fmBrow As frmBrow
        Me.Caption = meCaption
        Set fmBrow = New frmBrow
        Set Dbs = OpenDatabase(App.Path + "\data.mdb")
        Set Rst = Dbs.OpenRecordset("SELECT * FROM " & Table)
        fmBrow.Show
        ActiveForm.InputRst Rst
        Set ActiveForm.Data1.Recordset = ActiveForm.Rst
        ActiveForm.Caption = "浏览"
        ActiveForm.Data1.Caption = ActiveForm.Rst(0).Value
        If OptionsVal.Backmap <> "" Then
           Me.Picture = LoadPicture(OptionsVal.Backmap)
        End If
        Exit Sub
        
mdiform_loaderror:
    If Err.Number = 3024 Then
        MsgBox Err.Description
        With ComD
             .Filter = "*.mdb|*.mdb|*.*|*.*"
             .DialogTitle = "打开"
             .ShowOpen
             If .FileName <> "" Then
                Set Dbs = OpenDatabase(.FileName)
             Else
                Unload Me
             End If
        End With
     End If
     Resume Next
End Sub

Private Sub MDIForm_Unload(Cancel As Integer)
        Dbs.Close
End Sub

Public Sub mnuExit_Click()
        Unload Me
End Sub

Private Sub mnuOpen_Click()
Dim fmBrow As frmBrow
        Screen.MousePointer = VBRUN.MousePointerConstants.vbHourglass
        Me.Caption = meCaption
        Set fmBrow = New frmBrow
        fmBrow.Show
        'Set Dbs = OpenDatabase(App.Path + "\data.mdb")
        ActiveForm.InputRst Dbs.OpenRecordset("SELECT * FROM " & Table)
        Set ActiveForm.Data1.Recordset = ActiveForm.Rst
        ActiveForm.Caption = "浏览"
        ActiveForm.Data1.Caption = ActiveForm.Rst(0).Value
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolBar_Click()
        mnuToolBar.Checked = Not mnuToolBar.Checked
        Toolbar1.Visible = mnuToolBar.Checked
End Sub

Public Sub mnuToolOption_Click()
       frmOptions.Show 1
End Sub

Public Sub mnuWindowsArrory_Click()
          Me.Arrange 3
End Sub

Public Sub mnuWindowsC_Click()
        Me.Arrange 0
End Sub

Public Sub mnuWindowsT_Click()
          Me.Arrange 2
End Sub

Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)
With ActiveForm
        Select Case Button.Key
               Case "open"
                    mnuOpen_Click
               Case "add"
                    .mnuEditAdd_Click
               Case "delete"
                    .mnuEditDelete_Click
               Case "same"
                    .mnuToolFindSame_Click
               Case "de"
                    .mnuToolFind反义词_Click
               Case "like"
                    .mnuToolFIndAs_Click
               Case "relation"
                    .mnuToolFindRalation_Click
               Case "date"
                    .mnuToolFindDate_Click
        End Select
End With
End Sub
