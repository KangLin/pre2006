VERSION 5.00
Begin VB.Form �������ڶԻ��� 
   BorderStyle     =   5  'Sizable ToolWindow
   Caption         =   "�汾��Ϣ"
   ClientHeight    =   5760
   ClientLeft      =   2775
   ClientTop       =   3705
   ClientWidth     =   7320
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5760
   ScaleWidth      =   7320
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '����������
   Begin VB.CommandButton OKButton 
      Caption         =   "�˳�"
      Height          =   375
      Left            =   5880
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Label6"
      ForeColor       =   &H00000000&
      Height          =   180
      Left            =   240
      TabIndex        =   6
      Top             =   120
      Visible         =   0   'False
      Width           =   540
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      Caption         =   "ʱ��:2001��2��"
      ForeColor       =   &H00FF0000&
      Height          =   180
      Left            =   3600
      TabIndex        =   5
      Top             =   3480
      Width           =   1260
   End
   Begin VB.Label Label4 
      Caption         =   "�汾��2001"
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   2160
      TabIndex        =   4
      Top             =   3480
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "����"
      Height          =   255
      Left            =   3240
      TabIndex        =   3
      Top             =   3120
      Width           =   375
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "����"
      BeginProperty Font 
         Name            =   "����"
         Size            =   41.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000080FF&
      Height          =   975
      Left            =   2520
      TabIndex        =   2
      Top             =   1920
      Width           =   2175
   End
   Begin VB.Label Label1 
      Caption         =   " ��������"
      Height          =   255
      Left            =   3000
      TabIndex        =   1
      Top             =   1560
      Width           =   975
   End
End
Attribute VB_Name = "�������ڶԻ���"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub Form_Load()
Label6.Caption = _
"һ.����:" + Chr$(13) + _
"   ��Χ���������Զ����ӹ���" + Chr$(13) + _
"��.�˵�����:" + Chr$(13) + _
"   1.�ļ��˵�:" + Chr$(13) + _
"     a.����:" + Chr$(13) + _
"       �ܱ��汾�����µ���,�Ա��Ժ���;����δ�������,�Ա��Ժ�����" + Chr$(13) + _
"     b.����:" + Chr$(13) + _
"       ���ظ���ǰ���¹�����;������ʾ����Ĳ���" + Chr$(13) + _
"     c.װ��������:" + Chr$(13) + _
"       �ܽ�����ǰδ������������" + Chr$(13) + _
"     d.�˳�:" + Chr$(13) + _
"   2.���߲˵�:" + Chr$(13) + _
"     a.����:" + Chr$(13) + _
"       ���ߴ���ʱ,ʹ�ô���.�������Զ��ָ��������" + Chr$(13) + _
"     b.��ԭ:" + Chr$(13) + _
"       ���ڴ���ʱʹ�ô���" + Chr$(13) + _
"     c.���ӡ�����������Զ����ӹ��ܡ�" + Chr$(13) + _
"     d.����:" + Chr$(13) + _
"       �������ӻ�����Ҫ����ʱ,ʹ�ô���" + Chr$(13) + _
"     e.���¿�ʼ:" + Chr$(13) + _
"       ��һ��������,���¿�ʼһ����:" + Chr$(13) + _
"     f.��ʾʱ��:" + Chr$(13) + "     g.��ʾ����:" + Chr$(13) + _
"       ����ѡ��־��ʾʱ,��ʾ���߰�ť,�������ع��߰�ť" + Chr$(13) + _
"��.����Ҽ�����:" + Chr$(13) + "    �������Ҽ�,����ʾ���߲˵�"
End Sub

Private Sub OKButton_Click()
Unload Me '�����Ի���
End Sub

