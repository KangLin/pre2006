VERSION 5.00
Begin VB.Form FrmArray 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "����"
   ClientHeight    =   3195
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   7740
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   7740
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '����������
   Begin VB.TextBox Text5 
      Height          =   270
      Left            =   3720
      TabIndex        =   14
      Top             =   1680
      Visible         =   0   'False
      Width           =   735
   End
   Begin VB.TextBox Text4 
      Height          =   270
      Left            =   6240
      TabIndex        =   13
      Top             =   2160
      Width           =   855
   End
   Begin VB.TextBox Text3 
      Height          =   270
      Left            =   6240
      TabIndex        =   11
      Top             =   1680
      Width           =   855
   End
   Begin VB.TextBox Text2 
      Height          =   270
      Left            =   2160
      TabIndex        =   9
      Top             =   2160
      Width           =   855
   End
   Begin VB.TextBox Text1 
      Height          =   270
      Left            =   2160
      TabIndex        =   7
      Top             =   1680
      Width           =   855
   End
   Begin VB.Frame Frame1 
      Caption         =   "ѡ�����з�ʽ"
      Height          =   1095
      Left            =   600
      TabIndex        =   2
      Top             =   240
      Width           =   1815
      Begin VB.OptionButton Option2 
         Caption         =   "Բ������"
         Height          =   180
         Left            =   360
         TabIndex        =   4
         Top             =   720
         Width           =   1215
      End
      Begin VB.OptionButton Option1 
         Caption         =   "��������"
         Height          =   255
         Left            =   360
         TabIndex        =   3
         Top             =   360
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "ȡ��"
      Height          =   375
      Left            =   6120
      TabIndex        =   1
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "ȷ��"
      Height          =   375
      Left            =   6120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label7 
      Caption         =   "Y:"
      Height          =   255
      Left            =   3360
      TabIndex        =   16
      Top             =   1680
      Visible         =   0   'False
      Width           =   135
   End
   Begin VB.Label Label6 
      Caption         =   "X:"
      Height          =   375
      Left            =   1800
      TabIndex        =   15
      Top             =   1680
      Visible         =   0   'False
      Width           =   135
   End
   Begin VB.Label Label5 
      Caption         =   "Label5"
      Height          =   255
      Left            =   4800
      TabIndex        =   12
      Top             =   2160
      Width           =   1335
   End
   Begin VB.Label Label4 
      Caption         =   "Label4"
      Height          =   255
      Left            =   4800
      TabIndex        =   10
      Top             =   1680
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Label3"
      Height          =   255
      Left            =   600
      TabIndex        =   8
      Top             =   2160
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Label2"
      Height          =   255
      Left            =   600
      TabIndex        =   6
      Top             =   1680
      Width           =   1575
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "label "
      Height          =   180
      Left            =   600
      TabIndex        =   5
      Top             =   2640
      Width           =   540
   End
End
Attribute VB_Name = "FrmArray"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'����:����

Option Explicit

Public object As formcad

Private Sub CancelButton_Click()
        Unload Me
End Sub

Private Sub Form_Load()
If Option1.Value Then   '��������
        Option1_Click
        Text3.text = CStr(Mousepausex - Mouseleftdownx)
        Text4.text = CStr(Mousepausey - Mouseleftdowny)
End If
If Option2.Value Then  'Բ������
        Option2_Click
        Text2.text = "2"
        
End If
End Sub

Private Sub OKButton_Click()
If Option2.Value Then
   Mouseleftdownx = Val(Text1.text)
   Mouseleftdowny = Val(Text5.text)
End If
        object.EditArray
        fMainForm.mnuEditUndo_Click
        fMainForm.TCurrentOperist.text = "pointselect"
        Unload Me
End Sub

Private Sub Option1_Click()
        Label1.Caption = "�оࡢ�о�Ϊ����ʱ,���Ƶ�ͼ����ԭͼ���ϡ��������У���Ϊ������" + Chr$(13) + _
                         "                 ���ɰ�ͼ���¡��������С�"
        Label2.Caption = "����:"
        Label3.Caption = "����:"
        Label4.Caption = "�о�:"
        Label5.Caption = "�о�:"
        Text1.text = "2"
        Text2.text = "2"
        Label6.Visible = False
        Label7.Visible = False
        Text5.Visible = False
        Text3.Visible = True
        Label4.Visible = True
End Sub

Private Sub Option2_Click()
        Label1.Caption = "���з�Χ�нǣ���ʱ��Ϊ����˳ʱ��Ϊ�������нǣ���ʱ��Ϊ����˳ʱ��Ϊ��"
        Label2.Caption = "��������:"
        Label3.Caption = "��������:"
        Label4.Visible = False
        Text3.Visible = False
        Label5.Caption = "���н�:"
        Label6.Visible = True
        Label7.Visible = True
        Text5.Visible = True
End Sub

