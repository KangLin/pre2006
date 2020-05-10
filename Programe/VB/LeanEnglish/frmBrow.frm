VERSION 5.00
Object = "{00028C01-0000-0000-0000-000000000046}#1.0#0"; "DBGRID32.OCX"
Begin VB.Form frmBrow 
   Caption         =   "Form1"
   ClientHeight    =   5595
   ClientLeft      =   165
   ClientTop       =   165
   ClientWidth     =   5835
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   5595
   ScaleWidth      =   5835
   Begin MSDBGrid.DBGrid dbgBrow 
      Bindings        =   "frmBrow.frx":0000
      Height          =   4095
      Left            =   120
      OleObjectBlob   =   "frmBrow.frx":0014
      TabIndex        =   0
      Top             =   120
      Width           =   4575
   End
   Begin VB.Data Data1 
      Connect         =   "Access"
      DatabaseName    =   ""
      DefaultCursorType=   0  '缺省游标
      DefaultType     =   2  '使用 ODBC
      Exclusive       =   0   'False
      Height          =   375
      Left            =   240
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   1  'Dynaset
      RecordSource    =   ""
      Top             =   4560
      Width           =   2775
   End
   Begin VB.Label lbnum 
      Caption         =   "Label1"
      Height          =   300
      Left            =   3240
      TabIndex        =   1
      Top             =   4560
      Width           =   1500
   End
   Begin VB.Menu mnuFile 
      Caption         =   "文件(&F)"
      Begin VB.Menu mnuFileClose 
         Caption         =   "关闭(&C)"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "退出(&E)"
      End
   End
   Begin VB.Menu mnuPrev 
      Caption         =   "后退(&P)"
      Enabled         =   0   'False
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "编辑(&E)"
      Begin VB.Menu mnuEditAdd 
         Caption         =   "增加(&A)"
      End
      Begin VB.Menu mnuEditDelete 
         Caption         =   "删除(&D)"
      End
      Begin VB.Menu mnuEditbar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSort 
         Caption         =   "排序(&S)"
      End
   End
   Begin VB.Menu mnuTool 
      Caption         =   "工具(&T)"
      Begin VB.Menu menToolFind 
         Caption         =   "查找(&F)"
      End
      Begin VB.Menu mnuToolFindSame 
         Caption         =   "查找同义词(&S)"
      End
      Begin VB.Menu mnuToolFind反义词 
         Caption         =   "查找反义词(&D)"
      End
      Begin VB.Menu mnuToolFindAs 
         Caption         =   "查找相似词(&L)"
      End
      Begin VB.Menu mnuToolFindRalation 
         Caption         =   "查找关联词(&R)"
      End
      Begin VB.Menu mnuToolFindDate 
         Caption         =   "查找日期(&E)"
      End
      Begin VB.Menu mnuToolAllRalation 
         Caption         =   "查找有联系的词(&T)"
      End
      Begin VB.Menu mnuToolBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolAllShow 
         Caption         =   "全部列出(&A)"
      End
      Begin VB.Menu mnuToolbar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolOption 
         Caption         =   "选项(&O)"
      End
      Begin VB.Menu mnuToolbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolBarr 
         Caption         =   "工具栏(&B)"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "视图(&V)"
      Begin VB.Menu mnuViewSingle 
         Caption         =   "详细资料"
      End
      Begin VB.Menu mnuViewAll 
         Caption         =   "全部资料"
      End
   End
   Begin VB.Menu mnuWindows 
      Caption         =   "窗口(&W)"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowst 
         Caption         =   "平铺(&T)"
      End
      Begin VB.Menu mnuWindowsC 
         Caption         =   "层叠(&C)"
      End
      Begin VB.Menu mnuWindowsArrary 
         Caption         =   "排列图标(&A)"
      End
   End
End
Attribute VB_Name = "frmBrow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public Rst As Recordset
Dim AddFlag As Boolean
Dim frmSingle As frmSingleShow
Dim frmSingl() As frmSingleShow

Public Function InputRst(Rec As Recordset)
       Set Rst = Rec
End Function

Private Sub Data1_Reposition() '重新定位
On Error Resume Next
        Data1.Caption = Rst(0).Value
        lbnum.Caption = Rst.AbsolutePosition + 1 & " / " & Rst.RecordCount
End Sub

Private Sub dbgBrow_AfterInsert()
        frmSingle.cmdAdd_Click
End Sub

Private Sub dbgBrow_BeforeColEdit(ByVal ColIndex As Integer, ByVal KeyAscii As Integer, Cancel As Integer)
        If Rst(ColIndex).Name = "日期" Then
           Cancel = True
        End If
End Sub

Private Sub dbgBrow_BeforeColUpdate(ByVal ColIndex As Integer, OldValue As Variant, Cancel As Integer)
On Error GoTo beforecolupdateerror
        With frmSingle
             .cmbText(ColIndex).Text = dbgBrow.Text
             .cmbText_KeyPress ColIndex, vbKeyTab
        End With
        Exit Sub
        
beforecolupdateerror:
    MsgBox Err.Description
End Sub

Private Sub Form_Activate()
        mnuToolBarr.Checked = frmMain.Toolbar1.Visible
        If mnuEditAdd.Checked Then
           frmMain.Toolbar1.Buttons("add").Value = tbrPressed
        Else
           frmMain.Toolbar1.Buttons("add").Value = tbrUnpressed
        End If
End Sub

Public Sub mnuEditAdd_Click()
On Error GoTo AddErr

   mnuEditAdd.Checked = Not mnuEditAdd.Checked
   If mnuEditAdd.Checked Then
      frmMain.Toolbar1.Buttons("add").Value = tbrPressed
   Else
      frmMain.Toolbar1.Buttons("add").Value = tbrUnpressed
   End If
   If mnuEditAdd.Checked Then
        Set frmSingle = New frmSingleShow
        frmSingle.InputRst Rst
        frmSingle.InputHideFlag True
        frmSingle.Hide
        frmSingle.mnuEditAdd_Click
        dbgBrow.AllowAddNew = True
        dbgBrow.AllowUpdate = True
        Rst.MoveLast
   Else
        Unload frmSingle
        dbgBrow.AllowAddNew = False
        dbgBrow.AllowUpdate = False
   End If
   
Exit Sub
   
AddErr:
  MsgBox Err.Description
        
End Sub

Private Sub dbgBrow_OnAddNew()
'MsgBox "onaddnew"
End Sub

Private Sub dbgBrow_UnboundAddData(ByVal RowBuf As MSDBGrid.RowBuffer, NewRowBookmark As Variant)
MsgBox "unboundadddata"
End Sub

Private Sub Form_Load()

     ReDim frmSingl(0)
     With dbgBrow
          .AllowAddNew = False
          .AllowDelete = False
          .AllowUpdate = False
     End With
End Sub

Private Sub Form_Resize()
On Error Resume Next
        With dbgBrow
             .Top = 200
             .Left = 200
             .Width = Me.ScaleWidth - 400
             .Height = Me.ScaleHeight - Data1.Height - 600
        End With
        With Data1
             .Top = dbgBrow.Top + dbgBrow.Height + 200
             .Left = dbgBrow.Left
             .Width = dbgBrow.Width - lbnum.Width
             lbnum.Top = .Top + .Height - lbnum.Height
             lbnum.Left = .Left + .Width
        End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
On Error Resume Next
Dim i
        Rst.Close
        Unload frmSingle
        For i = 1 To UBound(frmSingl)
            Unload frmSingl(i)
        Next
        
End Sub

Private Sub menToolFind_Click()
Dim i As Long, sTmp As String

  frmFindForm.lstFields.Clear
  For i = 0 To Rst.Fields.Count - 1
      frmFindForm.lstFields.AddItem Rst.Fields(i).Name
  Next i
  If Rst.Fields.Count > 0 Then frmFindForm.lstFields.ListIndex = 0
  frmFindForm.Show 1
  
  '搜索记录
  If Rst(gsFindField).Type = dbText Or Rst(gsFindField).Type = dbMemo Then
        sTmp = Rst(gsFindField).Name & " " & gsFindOp & " '" & gsFindExpr & "'"
  ElseIf Rst(gsFindField).Type = dbDate Then
        sTmp = Rst(gsFindField).Name & " " & gsFindOp & " #" & gsFindExpr & "#"
  Else
        sTmp = Rst(gsFindField).Name & gsFindOp & Val(gsFindExpr)
  End If
  If gnFindType = 4 Then
     sTmp = "select * from " & Table & " where " & sTmp ' & gsFindField & " " & gsFindOp & " " & "'" & gsFindExpr & "'"
  End If
  Select Case gnFindType
    Case 0
      Rst.FindFirst sTmp
    Case 1
      Rst.FindNext sTmp
    Case 2
      Rst.FindPrevious sTmp
    Case 3
      Rst.FindLast sTmp
    Case 4
      Set Rst = Dbs.OpenRecordset(sTmp)
  End Select
  ShowFind "查找到:", Rst
  
End Sub

Public Sub mnuEditDelete_Click()
On Error GoTo DeleteErr
  With Rst
    .Delete
    .MoveNext
    If .EOF Then .MoveLast
  End With
  Exit Sub

DeleteErr:
  MsgBox Err.Description
End Sub

Private Sub mnuFileClose_Click()
        Unload Me
End Sub

Private Sub mnuFileExit_Click()
        Rst.Close
        frmMain.mnuExit_Click
End Sub

Private Sub mnuToolAllShow_Click()
On Error Resume Next
        Set Rst = Dbs.OpenRecordset("select * from " & Table)
        Set Data1.Recordset = Rst
End Sub

Private Sub mnuToolbarr_Click()
       frmMain.mnuToolBar_Click
       mnuToolBarr.Checked = frmMain.Toolbar1.Visible
End Sub

Private Sub mnuToolOption_Click()
        frmMain.mnuToolOption_Click
End Sub

Public Sub mnuToolFindSame_Click()
On Error Resume Next
Dim exi As Integer
        exi = MsgBox("列出 " & Rst("单词").Value & " 的同义词?", vbQuestion + vbYesNoCancel, "列出 " & Rst("单词").Value & " 的同义词")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           SameWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 .Oper(0).Value = True
                 .Cmb.Text = Rst("同义词").Value
                 
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFind反义词_Click()
On Error Resume Next
Dim exi As Integer
        exi = MsgBox("列出 " & Rst("单词").Value & " 反义词?", vbQuestion + vbYesNoCancel, "列出 " & Rst("单词").Value & " 的反义词")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           DifferentWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 .Oper(1).Value = True
                 .Cmb.Text = Rst("反义词")
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFIndAs_Click()
On Error Resume Next

Dim exi As Integer
        exi = MsgBox("列出 " & Rst("单词").Value & " 的相似词?", vbQuestion + vbYesNoCancel, "列出 " & Rst("单词").Value & " 的相似词")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           LikeWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 '.InputRst Rst
                 .Oper(2).Value = True
                 .Cmb.Text = Rst("相似词")
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFindRalation_Click()
On Error Resume Next

Dim exi As Integer
        exi = MsgBox("列出 " & Rst("单词").Value & " 的关联词?", vbQuestion + vbYesNoCancel, "列出 " & Rst("单词").Value & " 的关联词")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           RalationWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 '.InputRst Rst
                 .Oper(3).Value = True
                 .Cmb.Text = Rst("关联词")
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFindDate_Click()
On Error GoTo finddateerror
Dim exi As Integer
        exi = MsgBox("列出在 " & Rst("日期").Value & " 学习的词?", vbQuestion + vbYesNoCancel, "列出在 " & Rst("日期").Value & " 学习的词")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           Dateword Rst
        ElseIf exi = vbNo Then
            With frmFind
                 '.InputRst Rst
                 .Oper(4).Value = True
                 .Cmb.Text = Rst("日期")
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
        Exit Sub

finddateerror:
        MsgBox Err.Description
        Screen.MousePointer = vbDefault

End Sub

Private Sub mnuToolAllRalation_Click()
On Error Resume Next

Dim ext As Integer
        Screen.MousePointer = vbHourglass
        ext = MsgBox("列出与 " & Rst("单词").Value & " 有联系的词?", vbQuestion + vbYesNoCancel, "列出与 " & Rst("单词").Value & " 有联系的词")
        If ext = vbYes Then
           AllRalation Rst, True
        ElseIf ext = vbNo Then
            With frmFind
                 .Oper(5).Value = True
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Private Sub mnuViewAll_Click()
'
End Sub

Private Sub mnuViewSingle_Click()
        ReDim Preserve frmSingl(UBound(frmSingl) + 1)
        
        Set frmSingl(UBound(frmSingl)) = New frmSingleShow
        With frmSingl(UBound(frmSingl))
             .InputRst Rst
             .Show
        End With
End Sub

Private Sub mnuWindowsArrary_Click()
        frmMain.mnuWindowsArrory_Click
End Sub

Private Sub mnuWindowsC_Click()
        frmMain.mnuWindowsC_Click
End Sub

Private Sub mnuWindowsT_Click()
        frmMain.mnuWindowsT_Click
End Sub
