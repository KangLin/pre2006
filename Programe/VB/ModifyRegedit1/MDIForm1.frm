VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.MDIForm MDIForm1 
   BackColor       =   &H8000000C&
   Caption         =   "MDIForm1"
   ClientHeight    =   6030
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   8340
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   2  '��Ļ����
   Begin MSComctlLib.ImageList Img 
      Left            =   480
      Top             =   2040
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   15
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   15
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":0544
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":0A88
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":0FCC
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":1510
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":1A54
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":1F98
            Key             =   "mycomputer"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":23EC
            Key             =   "closedec"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":2840
            Key             =   "opendec"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":2C94
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":30E8
            Key             =   ""
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":362C
            Key             =   ""
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":3B70
            Key             =   ""
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":40B4
            Key             =   ""
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIForm1.frx":45F8
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.StatusBar StatB 
      Align           =   2  'Align Bottom
      Height          =   240
      Left            =   0
      TabIndex        =   0
      Top             =   5790
      Width           =   8340
      _ExtentX        =   14711
      _ExtentY        =   423
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   11280
            MinWidth        =   3528
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            Object.Width           =   1587
            MinWidth        =   1587
            TextSave        =   "01-8-10"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            Object.Width           =   1235
            MinWidth        =   1235
            TextSave        =   "16:20"
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog CommD 
      Left            =   3000
      Top             =   1920
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Menu mnuFile 
      Caption         =   "�ļ�(&F)"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "���ϴε�����(&O)"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "��������(&S)"
      End
      Begin VB.Menu mnuFileBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "�˳�(&E)"
      End
   End
   Begin VB.Menu mnuOption 
      Caption         =   "ѡ��(&O)"
      Begin VB.Menu mnuOptionDesktop 
         Caption         =   "����(&D)"
      End
      Begin VB.Menu mnuOptionNet 
         Caption         =   "�������(&C)"
      End
      Begin VB.Menu mnuOptionSecurity 
         Caption         =   "��ȫ(&S)"
      End
   End
   Begin VB.Menu mnuTool 
      Caption         =   "����(&T)"
      Begin VB.Menu mnuToolAdd 
         Caption         =   "����(&A)"
      End
      Begin VB.Menu mnuToolAddWizard 
         Caption         =   "������(&W)"
      End
      Begin VB.Menu mnuToolModify 
         Caption         =   "�޸�(&M)"
      End
      Begin VB.Menu mnuToolbar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolModifyList 
         Caption         =   "�޸�ֵ�б�(&L)"
      End
      Begin VB.Menu mnuToolbar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolSystemRegedit 
         Caption         =   "ע���༭��(&R)"
      End
   End
End
Attribute VB_Name = "MDIForm1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub MDIForm_Load()
        Me.Caption = "�޸�ע���"
        StatB.Panels(1).Text = "��ǰ����ϵͳ: " & tyOSVersionInformation.sOSVAll
End Sub

Private Sub mnuFileExit_Click()
        Unload Me
End Sub

Private Sub mnuFileOpen_Click()
        If OpenFile Then
           ModifyKey
        End If
End Sub

Private Sub mnuFileSave_Click()
        SaveFile
End Sub

Private Sub mnuOptionDesktop_Click()
        With frmOption
             .InputWindowsStyle Windows_Desktop_Enum
             .Show
        End With
End Sub

Private Sub mnuOptionNet_Click()
        With frmOption
             .InputWindowsStyle Windows_ControlPanel_Enum
             .Show
        End With
End Sub

Private Sub mnuOptionSecurity_Click()
        With frmOption
             .InputWindowsStyle Windows_Security_Enum
             .Show
        End With
End Sub

Private Sub mnuToolAdd_Click()
        If PassWord(Enum_PassStyle_Add) Then
           add.Show 1, Me
        End If
End Sub

Private Sub mnuToolAddWizard_Click()
        If PassWord(Enum_PassStyle_AddWizard) Then
           frmAdd.Show 1, Me
        End If
End Sub

Private Sub mnuToolModify_Click()
        If PassWord(Enum_PassStyle_AddWizard) Then
        With frmBrow
             .InputWindowCaption "�޸ļ�ֵ"
             .Show 1
         End With
        End If
End Sub

'�޸�ֵ�б�
Private Sub mnuToolModifyList_Click()
      If PassWord(Enum_PassStyle_ModifyKeyList) Then
         With frmBrow
             .InputWindowCaption "�޸�ֵ�б�"
             .Show 1
         End With
      End If
End Sub

'����ע���༭��
Private Sub mnuToolSystemRegedit_Click()
On Error Resume Next
        If PassWord(Enum_PassStyle_Regedit) Then
           Shell "regedit.exe", vbNormalFocus
           If Err <> 0 Then
              With CommD
                   .Filter = "(regedit.exe)|regedit.exe)"
                   .ShowOpen
                   If .FileName <> "" Then
                      Shell .FileName, vbNormalFocus
                   End If
              End With
           End If
        End If
End Sub
