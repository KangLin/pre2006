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
      DefaultCursorType=   0  'ȱʡ�α�
      DefaultType     =   2  'ʹ�� ODBC
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
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu mnuFileClose 
         Caption         =   "�ر�(&C)"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "�˳�(&E)"
      End
   End
   Begin VB.Menu mnuPrev 
      Caption         =   "����(&P)"
      Enabled         =   0   'False
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "�༭(&E)"
      Begin VB.Menu mnuEditAdd 
         Caption         =   "����(&A)"
      End
      Begin VB.Menu mnuEditDelete 
         Caption         =   "ɾ��(&D)"
      End
      Begin VB.Menu mnuEditbar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSort 
         Caption         =   "����(&S)"
      End
   End
   Begin VB.Menu mnuTool 
      Caption         =   "����(&T)"
      Begin VB.Menu menToolFind 
         Caption         =   "����(&F)"
      End
      Begin VB.Menu mnuToolFindSame 
         Caption         =   "����ͬ���(&S)"
      End
      Begin VB.Menu mnuToolFind����� 
         Caption         =   "���ҷ����(&D)"
      End
      Begin VB.Menu mnuToolFindAs 
         Caption         =   "�������ƴ�(&L)"
      End
      Begin VB.Menu mnuToolFindRalation 
         Caption         =   "���ҹ�����(&R)"
      End
      Begin VB.Menu mnuToolFindDate 
         Caption         =   "��������(&E)"
      End
      Begin VB.Menu mnuToolAllRalation 
         Caption         =   "��������ϵ�Ĵ�(&T)"
      End
      Begin VB.Menu mnuToolBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolAllShow 
         Caption         =   "ȫ���г�(&A)"
      End
      Begin VB.Menu mnuToolbar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolOption 
         Caption         =   "ѡ��(&O)"
      End
      Begin VB.Menu mnuToolbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolBarr 
         Caption         =   "������(&B)"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "��ͼ(&V)"
      Begin VB.Menu mnuViewSingle 
         Caption         =   "��ϸ����"
      End
      Begin VB.Menu mnuViewAll 
         Caption         =   "ȫ������"
      End
   End
   Begin VB.Menu mnuWindows 
      Caption         =   "����(&W)"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowst 
         Caption         =   "ƽ��(&T)"
      End
      Begin VB.Menu mnuWindowsC 
         Caption         =   "���(&C)"
      End
      Begin VB.Menu mnuWindowsArrary 
         Caption         =   "����ͼ��(&A)"
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

Private Sub Data1_Reposition() '���¶�λ
On Error Resume Next
        Data1.Caption = Rst(0).Value
        lbnum.Caption = Rst.AbsolutePosition + 1 & " / " & Rst.RecordCount
End Sub

Private Sub dbgBrow_AfterInsert()
        frmSingle.cmdAdd_Click
End Sub

Private Sub dbgBrow_BeforeColEdit(ByVal ColIndex As Integer, ByVal KeyAscii As Integer, Cancel As Integer)
        If Rst(ColIndex).Name = "����" Then
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
  
  '������¼
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
  ShowFind "���ҵ�:", Rst
  
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
        exi = MsgBox("�г� " & Rst("����").Value & " ��ͬ���?", vbQuestion + vbYesNoCancel, "�г� " & Rst("����").Value & " ��ͬ���")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           SameWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 .Oper(0).Value = True
                 .Cmb.Text = Rst("ͬ���").Value
                 
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFind�����_Click()
On Error Resume Next
Dim exi As Integer
        exi = MsgBox("�г� " & Rst("����").Value & " �����?", vbQuestion + vbYesNoCancel, "�г� " & Rst("����").Value & " �ķ����")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           DifferentWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 .Oper(1).Value = True
                 .Cmb.Text = Rst("�����")
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFIndAs_Click()
On Error Resume Next

Dim exi As Integer
        exi = MsgBox("�г� " & Rst("����").Value & " �����ƴ�?", vbQuestion + vbYesNoCancel, "�г� " & Rst("����").Value & " �����ƴ�")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           LikeWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 '.InputRst Rst
                 .Oper(2).Value = True
                 .Cmb.Text = Rst("���ƴ�")
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFindRalation_Click()
On Error Resume Next

Dim exi As Integer
        exi = MsgBox("�г� " & Rst("����").Value & " �Ĺ�����?", vbQuestion + vbYesNoCancel, "�г� " & Rst("����").Value & " �Ĺ�����")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           RalationWord Rst
        ElseIf exi = vbNo Then
            With frmFind
                 '.InputRst Rst
                 .Oper(3).Value = True
                 .Cmb.Text = Rst("������")
                 .Show 1
            End With
        End If
        Screen.MousePointer = vbDefault
End Sub

Public Sub mnuToolFindDate_Click()
On Error GoTo finddateerror
Dim exi As Integer
        exi = MsgBox("�г��� " & Rst("����").Value & " ѧϰ�Ĵ�?", vbQuestion + vbYesNoCancel, "�г��� " & Rst("����").Value & " ѧϰ�Ĵ�")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           Dateword Rst
        ElseIf exi = vbNo Then
            With frmFind
                 '.InputRst Rst
                 .Oper(4).Value = True
                 .Cmb.Text = Rst("����")
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
        ext = MsgBox("�г��� " & Rst("����").Value & " ����ϵ�Ĵ�?", vbQuestion + vbYesNoCancel, "�г��� " & Rst("����").Value & " ����ϵ�Ĵ�")
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
