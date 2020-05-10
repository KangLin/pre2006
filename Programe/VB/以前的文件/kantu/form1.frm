VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  '����ȱʡ
   WindowState     =   2  'Maximized
   Begin VB.Frame FraCom 
      Caption         =   "�ļ�"
      Height          =   6735
      Left            =   9240
      TabIndex        =   1
      Top             =   0
      Width           =   1695
      Begin VB.CommandButton Cmd 
         Caption         =   "ת��(&T)"
         Height          =   375
         Left            =   360
         TabIndex        =   6
         Top             =   6120
         Width           =   1095
      End
      Begin VB.TextBox Text1 
         Height          =   270
         Left            =   240
         TabIndex        =   5
         Text            =   "Text1"
         Top             =   5520
         Width           =   1215
      End
      Begin VB.DriveListBox Drive1 
         Height          =   300
         Left            =   240
         TabIndex        =   4
         Top             =   240
         Width           =   1335
      End
      Begin VB.DirListBox Dir1 
         Height          =   1770
         Left            =   240
         TabIndex        =   3
         Top             =   720
         Width           =   1335
      End
      Begin VB.FileListBox File1 
         Height          =   2610
         Left            =   240
         TabIndex        =   2
         Top             =   2640
         Width           =   1335
      End
   End
   Begin VB.PictureBox Pic 
      Height          =   6735
      Left            =   0
      ScaleHeight     =   6675
      ScaleWidth      =   7875
      TabIndex        =   0
      Top             =   0
      Width           =   7935
   End
   Begin MSComDlg.CommonDialog Comm 
      Left            =   4800
      Top             =   4560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Menu mnuFIle 
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu mnuFileOPen 
         Caption         =   "��(&O)"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "����(&S)"
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "���Ϊ(&A)"
      End
      Begin VB.Menu mnuFileBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFIleExit 
         Caption         =   "�˳�(&E)"
      End
   End
   Begin VB.Menu mnuuEdit 
      Caption         =   "�༭(&E)"
      Begin VB.Menu mnuEditCut 
         Caption         =   "����(&C)"
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "����(&O)"
      End
      Begin VB.Menu mnuEditPase 
         Caption         =   "ճ��(&P)"
      End
      Begin VB.Menu mnuEditBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSelect 
         Caption         =   "ѡȡ(&S)"
         Begin VB.Menu mnuEditSelectRect 
            Caption         =   "����ѡȡ(&R)"
         End
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim sFileName As String

Private Sub Cmd_Click()
With Comm
     .Filter = "*.bmp|*.bmp|*.*|*.*"
     .ShowOpen
     If .FileName <> "" Then
       Call SavePicture(Pic.Image, .FileName) 'Image1.Picture, .FileName)
     End If
End With
End Sub

Private Sub Dir1_Change()
File1.Path = Dir1.Path
End Sub

Private Sub Drive1_Change()
Dir1.Path = Drive1
End Sub

Private Sub File1_Click()
Text1.Text = File1.Path + "\" + File1.FileName
End Sub

Private Sub File1_DblClick()
On Error GoTo File1_DblClick_Error
Dim FileName As String
Dim p As StdPicture
FileName = Dir1.Path + "\" + File1.FileName
Text1.Text = FileName
Set p = LoadPicture(FileName)
'Set Image1.Picture = p
Pic.Cls
If p.Width > Pic.ScaleWidth Or p.Height > Pic.ScaleHeight Then
   If p.Width > p.Height Then
      Pic.PaintPicture p, 0, 0, _
          Pic.ScaleWidth, _
          Pic.ScaleWidth / p.Width * p.Height ', _
          0, 0, Pic.ScaleWidth, Pic.ScaleHeight
   Else
      Pic.PaintPicture p, 0, 0, _
          Pic.ScaleHeight / p.Height * Pic.ScaleWidth, _
          Pic.ScaleHeight, 0, 0 ', _
          p.Width, p.Handle
   End If
Else
   Set Pic.Picture = p
End If
Exit Sub
File1_DblClick_Error:
MsgBox Err.Description
End Sub

Private Sub File1_KeyUp(KeyCode As Integer, Shift As Integer)
If KeyCode = 13 Then
   File1_DblClick
End If
End Sub

Private Sub File1_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
Text1 = File1.FileName
If Button = vbRightButton Then
   File1_DblClick
End If
End Sub

Private Sub Form_Load()
Me.Caption = "ͼƬ�����"
Me.Width = Screen.Width
Me.Height = Screen.Height
Pic.AutoRedraw = True
With FraCom
     .Caption = ""
     .Top = 0
     .Left = Me.ScaleWidth - .Width
     .Height = Me.ScaleHeight
     Cmd.Top = .Height - Cmd.Height - 500
     Text1.Top = Cmd.Top - 500 - Text1.Height
     File1.Height = Text1.Top - 1000 - Dir1.Top - Dir1.Height
     File1.Top = Dir1.Top + Dir1.Height + 500
     .Visible = False
     Text1.Text = ""
End With
With Pic
     .ScaleMode = VBRUN.ScaleModeConstants.vbPixels
     If FraCom.Visible Then
        .Width = Me.ScaleWidth - FraCom.Width
     Else
        .Width = Me.ScaleWidth
     End If
     .Height = Me.ScaleHeight
     .Top = 0
     .Left = 0
End With
End Sub

Private Sub mnuFileOPen_Click()
With Comm
     .FileName = ""
     .Filter = "ͼƬ�ļ�(*.BMP;*.JPG)|*.BMP;*.JPG|�����ļ�(*.*)|*.*"
     .DialogTitle = "���ļ�"
     .Flags = mscomdlg.FileOpenConstants.cdlOFNExplorer + FileOpenConstants.cdlOFNHideReadOnly
     .ShowOpen
     If .FileName <> "" Then
        sFileName = .FileName
     End If
End With
End Sub

Private Sub Text1_KeyUp(KeyCode As Integer, Shift As Integer)
If KeyCode = 13 Then
   Drive1 = Text1
   Dir1.Path = Text1
   File1.FileName = Text1.Text
   File1_DblClick
End If
End Sub
