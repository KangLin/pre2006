VERSION 5.00
Begin VB.Form frmSingleShow 
   Caption         =   "Form1"
   ClientHeight    =   4635
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   6825
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4635
   ScaleWidth      =   6825
   Begin VB.CommandButton cmdAdd 
      Caption         =   "����"
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   4080
      Visible         =   0   'False
      Width           =   855
   End
   Begin VB.Data Data1 
      Caption         =   "Data1"
      Connect         =   "Access"
      DatabaseName    =   ""
      DefaultCursorType=   0  'ȱʡ�α�
      DefaultType     =   2  'ʹ�� ODBC
      Exclusive       =   0   'False
      Height          =   405
      Left            =   1440
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   1  'Dynaset
      RecordSource    =   ""
      Top             =   4080
      Width           =   3495
   End
   Begin VB.ComboBox cmbText 
      DataSource      =   "Data1"
      Height          =   345
      Index           =   0
      Left            =   1560
      Style           =   1  'Simple Combo
      TabIndex        =   1
      Text            =   "Combo1"
      Top             =   240
      Width           =   4815
   End
   Begin VB.Label lbnum 
      Caption         =   "Label1"
      Height          =   300
      Left            =   5280
      TabIndex        =   3
      Top             =   4080
      Width           =   1380
   End
   Begin VB.Label lbField 
      Caption         =   "Label1    "
      Height          =   180
      Index           =   0
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   900
   End
   Begin VB.Menu mnuFile 
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu munClose 
         Caption         =   "�ر�(&C)"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "�˳�(&E)"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "�༭(&E)"
      Begin VB.Menu mnuEditModify 
         Caption         =   "�޸�(&M)"
      End
      Begin VB.Menu mnumodifybar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditAdd 
         Caption         =   "����(&A)"
      End
      Begin VB.Menu mnuEditDelete 
         Caption         =   "ɾ��(&C)"
      End
   End
   Begin VB.Menu mnuTool 
      Caption         =   "����(&T)"
      Begin VB.Menu mnuToolFInd 
         Caption         =   "����(&F)"
      End
      Begin VB.Menu mnuToolFindSame 
         Caption         =   "����ͬ���(&S)"
      End
      Begin VB.Menu mnuToolFind����� 
         Caption         =   "���ҷ����(&D)"
      End
      Begin VB.Menu mnuToolFIndAs 
         Caption         =   "�������ƴ�(&l)"
      End
      Begin VB.Menu mnuToolFindRalation 
         Caption         =   "���ҹ�����(&R)"
      End
      Begin VB.Menu mnuToolFindDate 
         Caption         =   "��������(&E)"
      End
      Begin VB.Menu mnuToolFIndL 
         Caption         =   "��������ϵ�Ĵ�(&T)"
      End
      Begin VB.Menu mnuToolbar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolFindAll 
         Caption         =   "ȫ���г�(&A)"
      End
      Begin VB.Menu mnutoolBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolOption 
         Caption         =   "ѡ��(&O)"
      End
      Begin VB.Menu mnuToolbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolbarr 
         Caption         =   "������(&B)"
      End
   End
   Begin VB.Menu mnuWindows 
      Caption         =   "����(&W)"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowT 
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
Attribute VB_Name = "frmSingleShow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Rst As Recordset
Attribute Rst.VB_VarHelpID = -1
Dim ttop As Single
Dim lleft As Single
Dim wid As Single
Dim hheight As Single
Dim ChangeFlag As Boolean
Dim AddFlag As Boolean
Dim HideFlag As Boolean
Dim ReturnFlag As Boolean

Public Function InputRst(Rec As Recordset)
       Set Rst = Rec
End Function

Public Function InputHideFlag(Flag As Boolean)
       HideFlag = Flag
End Function

Private Sub cmbText_Change(Index As Integer)
'On Error Resume Next

        If ReturnFlag And HideFlag Then '���ڲ��ҵ����ַ�������dbgBrow��
           With frmMain.ActiveForm.dbgBrow
                .Col = Index
                .Text = cmbText(Index).Text
           End With
        End If
End Sub

Private Sub cmbText_GotFocus(Index As Integer)
If Not ChangeFlag Then
        cmbText(Index).SelLength = 0
        cmbText(Index).SelStart = 0
        cmbText(Index).SelText = ""
End If
End Sub

Private Sub cmbText_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyDelete And Not ChangeFlag Or lbField(Index).Caption = "����" Then
           KeyCode = 0
        End If
End Sub

Public Sub cmbText_KeyPress(Index As Integer, KeyAscii As Integer)
On Error Resume Next

Dim i, Rec As Recordset, j As Long, ss() As String, k
Dim Flag As Boolean
        
        If HideFlag Then
           ReturnFlag = True '���ڲ��ҵ����ַ�������dbgBrow��
        End If
        
        ReDim ss(0)
        If KeyAscii = vbKeyTab Or KeyAscii = 13 Then
           If AddFlag Then
              Screen.MousePointer = vbHourglass
              Select Case lbField(Index).Caption
                     Case "����"
                          AutoFind
                     Case "����"
                          AutoFind "ͬ���", "����"
                     Case "ͬ���"
                          AutoFind "ͬ���", "ͬ���"
                     Case "�����"
                          AutoFind "�����", "�����"
                     Case "���ƴ�"
                          AutoFind "���ƴ�", "���ƴ�"
                     Case "������"
                          AutoFind "������", "������"
              End Select
              Screen.MousePointer = vbDefault
           End If
           KeyAscii = 0
           SendKeys "{tab}"
        End If
        If Not ChangeFlag Or lbField(Index).Caption = "����" Then
           KeyAscii = 0
        End If
        
        If HideFlag Then
           ReturnFlag = False
        End If
End Sub

Private Sub Data1_Reposition()
On Error Resume Next
        Data1.Caption = Rst(0).Value
        If Err <> 0 Then
           Data1.Caption = ""
        End If
        lbnum.Caption = Data1.Recordset.AbsolutePosition + 1 & " / " & Data1.Recordset.RecordCount
End Sub

Private Sub Form_Activate()
        mnuToolbarr.Checked = frmMain.Toolbar1.Visible
        If mnuEditAdd.Checked Then
           frmMain.Toolbar1.Buttons("add").Value = tbrPressed
        Else
           frmMain.Toolbar1.Buttons("add").Value = tbrUnpressed
        End If
End Sub

Private Sub Form_Load()
On Error Resume Next
Dim i
        With Me
             .Caption = Rst(0).Value & " ��ϸ����"
            Set Data1.Recordset = Rst
            For i = 0 To Rst.Fields.Count - 1
                 If i <> 0 Then
                    Load .lbField(i)
                    Load .cmbText(i)
                 End If
                 lbField(i).Visible = True
                 cmbText(i).Visible = True
                 cmbText(i).Text = ""
                 lbField(i).Caption = Rst(i).Name
                 lbField(i).DataField = Rst(i).Name
                 cmbText(i).DataField = lbField(i) ' Rst(i).Name
             Next i
        End With
End Sub

Private Sub Form_Resize()
On Error Resume Next

Dim h As Single, i
        h = (Me.ScaleHeight - cmbText(0).Height * lbField.Count - 400 - Data1.Height) / lbField.Count
        If h < 0 Then
           With Me
                If .Width < lbField(0).Width + cmbText(0).Width + 500 Then
                   .Width = lbField(0).Width + cmbText(0).Width + 500
                End If
                .Height = cmbText(0).Height * cmbText.Count + 400 + Data1.Height
                h = (Me.ScaleHeight - cmbText(0).Height * lbField.Count - 400 - Data1.Height) / lbField.Count
           End With
        End If
        For i = 0 To lbField.Count - 1
            With lbField(i)
                 .Left = 200
                 If i = 0 Then
                    .Top = h + 200
                 Else
                    .Top = lbField(i - 1).Top + h + cmbText(i).Height
                 End If
            End With
            With cmbText(i)
                 .Left = lbField(i).Left + lbField(i).Width + 200
                 .Width = Me.ScaleWidth - 600 - lbField(i).Width
                 .Top = lbField(i).Top
            End With
        Next i
        Data1.Top = Me.ScaleHeight - 200 - Data1.Height
        Data1.Width = cmbText(i - 1).Width - lbnum.Width
        Data1.Left = cmbText(i - 1).Left
        cmdAdd.Top = Data1.Top
        cmdAdd.Left = lbField(i - 1).Left
        lbnum.Top = Data1.Top + Data1.Height - lbnum.Height
        lbnum.Left = Data1.Left + Data1.Width
End Sub

Private Sub mnuExit_Click()
        frmMain.mnuExit_Click
End Sub

Public Sub cmdAdd_Click()
Dim i
    If AddFlag Then
        SendKeys "{tab}"
        Rst.AddNew
        For i = 1 To cmbText.UBound
            If lbField(i).Caption = "����" Then
               cmbText(i).Text = FormatDateTime(Date, vbLongDate)
            End If
        Next i
        Rst.MoveLast
    End If
End Sub

Public Sub mnuEditAdd_Click()
Dim i
        mnuEditAdd.Checked = Not mnuEditAdd.Checked
        If mnuEditAdd.Checked Then
           frmMain.Toolbar1.Buttons("add").Value = tbrPressed
        Else
           frmMain.Toolbar1.Buttons("add").Value = tbrUnpressed
        End If
        AddFlag = mnuEditAdd.Checked
        cmdAdd.Visible = AddFlag
        If AddFlag Then
           Rst.MoveLast
           Rst.AddNew
           cmdAdd.TabIndex = 0
           ChangeFlag = True
           For i = 1 To cmbText.UBound
               If lbField(i).Caption = "����" Then
                  cmbText(i).Text = FormatDateTime(Date, vbLongDate)
               End If
           Next i
        End If
End Sub

Public Sub mnuEditDelete_Click()
On Error GoTo modifydeleterror
   With Rst
        .Delete
        .MoveNext
        If .EOF Then .MoveLast
   End With
   Exit Sub

modifydeleterror:
     MsgBox Err.Description
End Sub

Private Sub mnuEditModify_Click()
        mnuEditModify.Checked = Not mnuEditModify.Checked
        ChangeFlag = mnuEditModify.Checked
End Sub

Private Sub mnuToolbarr_Click()
        frmMain.mnuToolBar_Click
        mnuToolbarr.Checked = frmMain.Toolbar1.Visible
End Sub

Private Sub mnuToolFind_Click()
On Error Resume Next
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

Private Sub mnuToolFindAll_Click()
On Error Resume Next
        Set Rst = Dbs.OpenRecordset("select * from " & Table)
        Set Data1.Recordset = Rst

End Sub

Public Sub mnuToolFind�����_Click()
On Error Resume Next
Dim exi As Integer
        exi = MsgBox("�г� " & Rst("����").Value & " �����?", vbQuestion + vbYesNoCancel, "�г� " & Rst("����").Value & " �ķ����")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           DifferentWord Rst
        ElseIf exi = vbNo Then
            
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
            
        End If
        Screen.MousePointer = vbDefault
        Exit Sub
finddateerror:


End Sub

Private Sub mnuToolFindL_Click()
On Error Resume Next
Dim ext As Integer
        Screen.MousePointer = vbHourglass
        ext = MsgBox("�г��� " & Rst("����").Value & " ����ϵ�Ĵ�?", vbQuestion + vbYesNoCancel, "�г��� " & Rst("����").Value & " ����ϵ�Ĵ�")
        If ext = vbYes Then
           AllRalation Rst, True
        ElseIf ext = vbNo Then
        
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
            
        End If
        Screen.MousePointer = vbDefault

End Sub

Public Sub mnuToolFindSame_Click()
On Error Resume Next
Dim exi As Integer
        exi = MsgBox("�г� " & Rst("����").Value & " ��ͬ���?", vbQuestion + vbYesNoCancel, "�г� " & Rst("����").Value & " ��ͬ���")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           SameWord Rst
        ElseIf exi = vbNo Then
            
        End If
        Screen.MousePointer = vbDefault
End Sub

Private Sub mnuToolOption_Click()
        frmMain.mnuToolOption_Click
End Sub

Public Sub mnuToolFindRalation_Click()
On Error Resume Next
Dim exi As Integer
        exi = MsgBox("�г� " & Rst("����").Value & " �Ĺ�����?", vbQuestion + vbYesNoCancel, "�г� " & Rst("����").Value & " �Ĺ�����")
        Screen.MousePointer = vbHourglass
        If exi = vbYes Then
           RalationWord Rst
        ElseIf exi = vbNo Then
            
        End If
        Screen.MousePointer = vbDefault

End Sub

Private Sub mnuWindowsArrary_Click()
        frmMain.mnuWindowsArrory_Click
End Sub

Private Sub mnuWindowsC_Click()
        frmMain.mnuWindowsC_Click
End Sub

Private Sub mnuWindowT_Click()
        frmMain.mnuWindowsT_Click
End Sub

Private Sub munClose_Click()
        Unload Me
End Sub

Function AutoFind(Optional NeedAddField As String = "���ƴ�", Optional IfField As String = "����")
On Error Resume Next

Dim Addi, Ifi, ss() As String, sString As String
Dim s As String, s1 As String, s2 As String, s3 As String
Dim Rec As Recordset
Dim i

ReDim ss(0)
For Addi = 0 To cmbText.UBound
    If lbField(Addi).Caption = NeedAddField Then 'Ҫ��ӵ��ֶ�
       For Ifi = 0 To cmbText.UBound
           If lbField(Ifi).Caption = IfField Then '�����ֶ�
              sString = Trim(cmbText(Ifi).Text)
              Exit For
           End If
       Next Ifi
       Select Case IfField '��������
              Case "����"
                   ss(0) = "*" & sString & "*"
                   Set Rec = Find(ss)  '�������������ļ�¼
              Case "����"
                   SplitString sString, ss, , SpS����붺��, ͬ���
                   For i = 0 To UBound(ss) - 1
                       ss(i) = ss(i + 1)
                   Next i
                   Set Rec = Find(ss, , "����")
              Case "ͬ���", "�����", "���ƴ�", "������"
                   SplitString sString, ss
                   For i = 0 To UBound(ss) - 1
                       ss(i) = ss(i + 1)
                   Next i
                   Set Rec = Find(ss)
       End Select
       Rec.MoveFirst
       If Err <> 0 Then Exit For  '������
       While (Not Rec.EOF)
              Select Case IfField '��������
                     Case "����"
                          s = Rec("����").Value & "," & Rec("���ƴ�").Value
                          s1 = "���ƴ�"
                          s2 = cmbText(Ifi).Text
                     Case "����"
                          s = Rec("����").Value & "," & Rec("ͬ���").Value
                          s1 = "ͬ���"
                          s2 = cmbText(0).Text
                     Case "ͬ���"
                          s = Rec("����").Value & "," & Rec("ͬ���")
                          s1 = "ͬ���"
                          s2 = cmbText(0).Text
                     Case "�����"
                          s = Rec("����").Value & "," & Rec("�����")
                          s1 = "ͬ���"
                          s2 = cmbText(0).Text
                     Case "���ƴ�"
                          s = Rec("����").Value & "," & Rec("���ƴ�")
                          s1 = "ͬ���"
                          s2 = cmbText(0).Text
                     Case "������"
                          s = Rec("����").Value & "," & Rec("������")
                          s1 = "ͬ���"
                          s2 = cmbText(0).Text
              End Select
              '�ڱ���¼�м���鵽��
              InsertString cmbText(Addi), s
              '�޸Ĳ鵽�ļ�¼
              Rec.Edit
              InsertString Rec(s1), s2
              Rec.Update
              Rec.MoveNext
       Wend
       Exit For
    End If
Next
End Function
