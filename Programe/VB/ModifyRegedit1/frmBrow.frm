VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form frmBrow 
   Caption         =   "���"
   ClientHeight    =   5490
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7770
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5490
   ScaleWidth      =   7770
   StartUpPosition =   2  '��Ļ����
   Begin MSComctlLib.ProgressBar Pro 
      Height          =   495
      Left            =   1080
      TabIndex        =   12
      Top             =   3120
      Visible         =   0   'False
      Width           =   5775
      _ExtentX        =   10186
      _ExtentY        =   873
      _Version        =   393216
      Appearance      =   1
   End
   Begin VB.ComboBox cmbModify 
      Height          =   300
      ItemData        =   "frmBrow.frx":0000
      Left            =   1440
      List            =   "frmBrow.frx":000A
      Style           =   2  'Dropdown List
      TabIndex        =   11
      Top             =   120
      Visible         =   0   'False
      Width           =   2535
   End
   Begin MSComctlLib.StatusBar StatBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   9
      Top             =   5115
      Visible         =   0   'False
      Width           =   7770
      _ExtentX        =   13705
      _ExtentY        =   661
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
      EndProperty
   End
   Begin VB.Frame Frame1 
      Caption         =   "������"
      Height          =   615
      Left            =   120
      TabIndex        =   7
      Top             =   0
      Width           =   3855
      Begin VB.DriveListBox Drive1 
         Height          =   300
         Left            =   0
         TabIndex        =   8
         Top             =   240
         Width           =   3855
      End
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "ȷ��"
      Height          =   255
      Left            =   4560
      TabIndex        =   5
      Top             =   4920
      Width           =   735
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "ȡ��"
      CausesValidation=   0   'False
      Height          =   255
      Left            =   5520
      TabIndex        =   4
      Top             =   4920
      Width           =   735
   End
   Begin VB.CommandButton cmdApply 
      Caption         =   "Ӧ��"
      Height          =   255
      Left            =   6480
      TabIndex        =   3
      Top             =   4920
      Width           =   735
   End
   Begin VB.TextBox Text1 
      Height          =   270
      Left            =   120
      TabIndex        =   2
      Text            =   "Text1"
      Top             =   4920
      Width           =   3855
   End
   Begin VB.FileListBox File1 
      Height          =   1890
      Left            =   120
      TabIndex        =   1
      Top             =   2880
      Width           =   3855
   End
   Begin VB.DirListBox Dir1 
      Height          =   1980
      Left            =   120
      TabIndex        =   0
      Top             =   600
      Width           =   3855
   End
   Begin MSFlexGridLib.MSFlexGrid MSFlist 
      Height          =   4695
      Left            =   120
      TabIndex        =   6
      Top             =   480
      Visible         =   0   'False
      Width           =   7455
      _ExtentX        =   13150
      _ExtentY        =   8281
      _Version        =   393216
      Cols            =   5
      WordWrap        =   -1  'True
      AllowUserResizing=   3
   End
   Begin VB.Label LblModify 
      Caption         =   "ѡ������"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   240
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.Image Img 
      Height          =   4575
      Left            =   4440
      Stretch         =   -1  'True
      Top             =   120
      Width           =   2775
   End
End
Attribute VB_Name = "frmBrow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim sWindowCaption As String '���ڱ���

Public Sub InputWindowCaption(WindowCaption As String)
       sWindowCaption = WindowCaption
End Sub

Private Sub cmdApply_Click()
'���޸�ע���

End Sub

Private Sub cmdCancel_Click()
        Unload Me
End Sub

Private Sub cmdOk_Click()
        frmOption.txtInput.Text = Text1.Text
        Unload Me
End Sub

Private Sub Dir1_Change()
        File1.Path = Dir1
End Sub

Private Sub Drive1_Change()
        Dir1.Path = Drive1
End Sub

Private Sub File1_Click()
        Text1.Text = File1.Path + "\" + File1
        Img.Picture = LoadPicture(Text1.Text)
End Sub

Private Sub Text1_KeyDown(KeyCode As Integer, Shift As Integer)
On Error Resume Next

        If KeyCode = 13 Then '����Enter��
           Drive1 = Text1.Text
           Dir1 = Text1.Text
           File1 = Text1.Text
        End If
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
Dim i As Integer
If sWindowCaption = "�޸ļ�ֵ" Then
   i = MsgBox("Ҫ�����������޸���?", vbYesNoCancel, Me.Caption)
   If i = vbYes Then
      SaveKeyFile
   ElseIf i = vbCancel Then
      Cancel = i
   End If
End If
End Sub

Private Sub Form_Load()
Dim cot As Control, i As Long
     Me.Caption = sWindowCaption
     Select Case sWindowCaption
            Case "���ͼƬ"
                 File1.Pattern = "*.bmp;*.jpg;*.ico;*.cur"
                 Text1.Text = "*.bmp;*.jpg;*.ico;*.cur"
            Case "�޸�ֵ�б�"
                 For Each cot In Me
                     cot.Visible = False
                 Next cot
                 With MSFlist
                     .Top = 0
                     .Cols = 6
                     .Left = (Me.ScaleWidth - .Width) / 2
                     .Height = Me.ScaleHeight
                      For i = 0 To 5
                          .ColWidth(i) = .Width / 6 - 20
                      Next i
                     .Clear
                     .Rows = 1
                     .Row = 0
                     .Col = 0
                     .Text = "˵��"
                     .Col = 1
                     .Text = "����"
                     .Col = 2
                     .Text = "����"
                     .Col = 3
                     .Text = "�Ӽ�"
                     .Col = 4
                     .Text = "��ֵ"
                     .Col = 5
                     .Text = "����"
                     For i = 1 To UBound(Key)
                         .AddItem Key(i).Readme
                         .Row = i
                         .Col = 1
                         .Text = f_sChangeRootKey(Key(i).KeyRoot)
                         .Col = 2
                         .Text = Key(i).MainKey
                         .Col = 3
                         .Text = Key(i).SubKey
                         .Col = 4
                         .Text = Key(i).KeyVal
                         .Col = 5
                         .Text = f_sChangeKeyType(Key(i).KeyType)
                     Next i
                    .Visible = True
                 End With
                 StatBar.Visible = True
            Case "�޸ļ�ֵ"
                 For Each cot In Me
                     cot.Visible = False
                 Next cot
                 LblModify.Visible = True
                 With MSFlist
                     .Top = 480
                     .Left = (Me.ScaleWidth - .Width) / 2
                     .Height = Me.ScaleHeight - 480
                     .Clear
                     .Visible = True
                 End With
                 cmbModify.Visible = True
                 cmbModify.ListIndex = 0
                 StatBar.Visible = True
                 
    End Select
End Sub

Private Sub MSFlist_RowColChange()
        StatBar.SimpleText = MSFlist.Text
End Sub

'˫��ʱ�޸�
Private Sub MSFlist_DblClick()
Dim s As String, ss As String, i As Long
If sWindowCaption = "�޸ļ�ֵ" Then
   i = MSFlist.Row
   With MSFlist
        .Row = 0
        ss = .Text
        .Row = i
   End With
   
   Select Case cmbModify.ListIndex
          Case 0 'tTree
               If MSFlist.Col = 0 Then
                  'DeleteLine tTree(i)
                  Exit Sub
               End If
               s = InputBox("�ѵ� " & i & " �е�" & _
                      ss & ":" & MSFlist.Text & _
                "�޸�Ϊ:", "�޸�" & ss, MSFlist.Text)
                If s = "" Then Exit Sub
               Select Case MSFlist.Col
                      Case 1
                           tTree(i).Ralation = s
                      Case 2
                           tTree(i).Key = s
                      Case 3
                           tTree(i).Text = s
               End Select
               MSFlist.Text = s
          Case 1 'tTreeNode
               If MSFlist.Col = 0 Then
                  'DeleteLine tTreeNode(i)
                  Exit Sub
               End If
               Select Case MSFlist.Col
                      Case 1
                          s = InputBox("�ѵ� " & i & " �е�" & _
                      ss & ":" & MSFlist.Text & _
                     "�޸�Ϊ:", "�޸�" & ss, MSFlist.Text)
                           
                           If s = "" Then Exit Sub
                           'tTreeNode(i).Text = s
                      Case 2
                      s = InputBox("�б�ؼ�:Enum_Control_List=" & _
                                    Enum_Control_List & Chr(13) & _
                                   "�����:  Enum_Control_FrameInput=" & _
                             Enum_Control_FrameInput & Chr(13) & _
                                   "���:    Enum_Control_DBGird=" & _
                             Enum_Control_DBGird & Chr(13) & _
                             "�ѵ� " & i & " �е�" & _
                             ss & ": " & MSFlist.Text & _
                             " �޸�Ϊ:", "�޸�" & ss, MSFlist.Text)
                           
                           If s = "" Then Exit Sub
                           'tTreeNode(i).Control = s
                      Case 3
                      s = InputBox("��ȫ����:" & Chr(13) & "��:     Enum_PassLevel_Null=" & Enum_PassLevel_Null & Chr(13) & _
                                   "�û�����:Enum_PassLevel_User=" & Enum_passLevel_User & Chr(13) & _
                                   "������:Enum_PassLevel_Manger=" & Enum_PassLevel_Manager & "�ѵ� " & i & " �е�" & _
                      ss & ": " & MSFlist.Text & _
                " �޸�Ϊ:", "�޸�" & ss, MSFlist.Text)
                           
                           If s = "" Then Exit Sub
                           'tTreeNode(i).PassLevel = s
               End Select
          Case 2 'tControl
          
          Case 3 'tKeyVal
    
   End Select
End If
End Sub

'ɾ��һ��
Private Sub DeleteLine(tType() As Variant)
Dim exi As Integer, t As Variant
exi = MsgBox("��Ҫɾ���� " & i & " ��?", vbYesNo, _
             "�޸ļ�ֵ")
If exi = vbYes Then
   t = tType
   
End If
End Sub

Private Sub cmbModify_Click()
Dim i As Long
Dim j As Long
Pro.Visible = True
With MSFlist
     .Clear
     .ScrollBars = flexScrollBarBoth
        Select Case cmbModify.ListIndex
               Case 0 'tTree
                    .Rows = 1
                    .Cols = 9
                    .Row = 0
                    .Col = 1
                    .Text = "��ϵ(Ralation)"
                    .Col = 2
                    .Text = "�ؼ���(Key)"
                    .Col = 3
                    .Text = "����(Text)"
                    .Col = 4
                    .Text = "�ؼ�(Control)"
                    .Col = 5
                    .Text = "��ȫ����(PassLevel)"
                    .Col = 6
                    .Text = "��ֵ����ʼλ��(StartPos)"
                    .Col = 7
                    .Text = "��ֵ�Ľ���λ��(EndPos)"
                    .Col = 8
                    .Text = "��ֵ����"
                 For i = 1 To 8
                        .ColWidth(i) = (.Width - .ColWidth(0)) / 8 - 7
                    Next i
                    For i = 1 To UBound(tTree)
                        .AddItem Str$(i)
                        .Row = i
                        .Col = 1
                        .Text = tTree(i).Ralation
                        .Col = 2
                        .Text = tTree(i).Key
                        .Col = 3
                        .Text = tTree(i).Text
                        .Col = 4
                        .Text = frmAdd.sGetControl(tTree(i).Control)
                        .Col = 5
                        .Text = frmAdd.sGetPassLevel(tTree(i).PassLevel)
                        .Col = 6
                        .Text = tTree(i).StartPos
                        .Col = 7
                        .Text = tTree(i).EndPos
                        .Col = 8
                        .Text = f_sChangeKeyType(tTree(i).KeyType)
                        Pro.Value = i * 100 / UBound(tTree)
                    Next i
               Case 1 'tKeyVal
                    .Rows = 1
                    .Cols = 10
                    .Row = 0
                    .Col = 1
                    .Text = "�ؼ�����(ControlText)"
                    .Col = 2
                    .Text = "����(KeyRoot)"
                    .Col = 3
                    .Text = "����(MainKey)"
                    .Col = 4
                    .Text = "�Ӽ�(SubKey)"
                    .Col = 5
                    .Text = "��ֵ����(KeyType)"
                    .Col = 6
                    .Text = "��ֵ����(KeyVal)"
                    .Col = 7
                    .Text = "˵��(Readme)"
                    .Col = 8
                    .Text = "��ȫ����(PassLevel)"
                    .Col = 9
                    .Text = "���õĲ���ϵͳ(OperistSystem)"
                    For i = 1 To 9
                        .ColWidth(i) = (.Width - .ColWidth(0)) / 9 - 15
                    Next i
                    For i = 1 To UBound(tKeyVal)
                        .AddItem Str$(i)
                        .Row = i
                        .Col = 1
                        .Text = tKeyVal(i).ControlText
                        .Col = 2
                        .Text = f_sChangeRootKey(tKeyVal(i).KeyRoot)
                        .Col = 3
                        .Text = tKeyVal(i).MainKey
                        .Col = 4
                        .Text = tKeyVal(i).SubKey
                        .Col = 5
                        .Text = f_sChangeKeyType(tKeyVal(i).KeyType)
                        .Col = 6
                        .Text = tKeyVal(i).KeyVal
                        .Col = 7
                        .Text = tKeyVal(i).Readme
                        .Col = 8
                        .Text = frmAdd.sGetPassLevel(tKeyVal(i).PassLevel)
                        .Col = 9
                        .Text = frmAdd.sGetOperistSystem(tKeyVal(i).OperistSystem)
                        Pro.Value = i * 100 / UBound(tKeyVal)
                    Next i
                    
        End Select
End With
Pro.Visible = False
End Sub


