VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form formcad 
   BackColor       =   &H00C0C0C0&
   Caption         =   "��ͼ"
   ClientHeight    =   6795
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9480
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   6795
   ScaleWidth      =   9480
   WindowState     =   2  'Maximized
   Begin MSComctlLib.Slider SliderV 
      Height          =   2055
      Left            =   120
      TabIndex        =   5
      Top             =   360
      Width           =   225
      _ExtentX        =   397
      _ExtentY        =   3625
      _Version        =   393216
      Orientation     =   1
   End
   Begin MSComctlLib.Slider SliderH 
      Height          =   240
      Left            =   720
      TabIndex        =   4
      Top             =   240
      Width           =   4095
      _ExtentX        =   7223
      _ExtentY        =   423
      _Version        =   393216
   End
   Begin VB.VScrollBar Vscroll 
      Height          =   2055
      Left            =   4320
      TabIndex        =   3
      Top             =   600
      Width           =   255
   End
   Begin VB.HScrollBar HScroll 
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   2880
      Width           =   4455
   End
   Begin VB.PictureBox desk 
      BackColor       =   &H00C00000&
      Height          =   1695
      Left            =   360
      ScaleHeight     =   1635
      ScaleWidth      =   3795
      TabIndex        =   0
      Top             =   960
      Width           =   3855
      Begin VB.PictureBox cad 
         AutoRedraw      =   -1  'True
         BackColor       =   &H80000009&
         ClipControls    =   0   'False
         Height          =   1455
         Left            =   120
         MousePointer    =   2  'Cross
         ScaleHeight     =   1395
         ScaleWidth      =   3195
         TabIndex        =   1
         Top             =   120
         Width           =   3255
         Begin VB.Line GIRDl 
            DrawMode        =   10  'Mask Pen
            Index           =   0
            Visible         =   0   'False
            X1              =   240
            X2              =   240
            Y1              =   840
            Y2              =   1200
         End
         Begin VB.Line Line1 
            Visible         =   0   'False
            X1              =   720
            X2              =   1680
            Y1              =   1080
            Y2              =   1080
         End
         Begin VB.Label Text 
            AutoSize        =   -1  'True
            BackColor       =   &H80000009&
            Caption         =   "text"
            Height          =   180
            Index           =   0
            Left            =   960
            TabIndex        =   6
            Tag             =   "0"
            Top             =   480
            Visible         =   0   'False
            Width           =   360
         End
         Begin VB.Shape SSnape 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H00FF0000&
            FillColor       =   &H00FF8080&
            FillStyle       =   0  'Solid
            Height          =   135
            Left            =   0
            Top             =   0
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   8
            Left            =   2160
            Top             =   480
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   7
            Left            =   1680
            Top             =   480
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   6
            Left            =   1680
            Top             =   840
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   5
            Left            =   2160
            Top             =   840
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   4
            Left            =   2520
            Top             =   840
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   3
            Left            =   2520
            Top             =   480
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   2
            Left            =   2520
            Top             =   240
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   1
            Left            =   2160
            Top             =   240
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Shape1 
            BackColor       =   &H0000FFFF&
            BorderColor     =   &H0000FF00&
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   135
            Index           =   0
            Left            =   1680
            Top             =   240
            Visible         =   0   'False
            Width           =   135
         End
         Begin VB.Shape Smouse 
            Height          =   255
            Left            =   360
            Shape           =   3  'Circle
            Top             =   480
            Visible         =   0   'False
            Width           =   375
         End
         Begin VB.Shape SPshow 
            BorderColor     =   &H0000FFFF&
            BorderStyle     =   2  'Dash
            Height          =   495
            Left            =   1800
            Top             =   360
            Visible         =   0   'False
            Width           =   855
         End
         Begin VB.Line Line2 
            BorderColor     =   &H00004040&
            Visible         =   0   'False
            X1              =   1080
            X2              =   1080
            Y1              =   720
            Y2              =   1440
         End
      End
   End
End
Attribute VB_Name = "formcad"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'����:����

Option Explicit

Private Declare Function ShowCursor Lib "user32" (ByVal bShow As Long) As Long

Public Mousestyle As String '��ǰ���������Form_Activate��

Private CurrentOperistFlag As Boolean '���ļ��Ƿ�����˲���

Private Type LimitType   '��������,�����Զ��ƶ�ͼֽ
        X1 As Single
        Y1 As Single
        X2 As Single
        Y2 As Single
        End Type
Private Limit As LimitType '�����Զ��ƶ�ͼֽ

Public EditFlag As Boolean   '���ڱ༭ʱ�����ɫ
Private ShowObjectColor As ColorConstants  'ͻ����ʾ��ɫ
Private SelectField As Integer   'ѡȡ����
Private SelectRectangle As SelectRectangleType  '��ʾѡȡ����

Private LineColor As ColorConstants   '������ɫ
        '���ͻ����߿������,��cad.drawwidth��cad.drawstyle��
Private Paper As PaperType    'ͼֽ,������ɫδ��ֵ
 
Private Tline() As linetype   '�߶�����
Private Tcircle() As CircleType 'Բ������
Private Tfont() As TextType     '��������
Public LinePoint As Long    'ѡȡֱ��ָ��
Public CirclePoint As Long 'Բ��ָ��
Public FontPoint As Long   '����ָ��,�������½�EdirNew�����к���תEditRound������

Private Type snapepoint  '��׽��
        x As Single
        y As Single
        r As Single    'r<0δ��׽����
        End Type

Private p_Editselect As Long  'ʹ��ֱ���ཻʱѡȡ����ֱ��ָ��

'��ѡ����������������
Public Sub InputMouseStyle(Mouse As String)
       Mousestyle = Mouse
End Sub

'��������״
Public Function GetMouseStyle() As String
       GetMouseStyle = Mousestyle
End Function

'��ѡ����������ɫֵ
Public Sub InputDrawColor(Color As ColorConstants)
       LineColor = Color
End Sub

'�����ɫ��ѡ��
Public Function GetLineColor() As ColorConstants
       GetLineColor = LineColor
End Function

'��ѡ���еõ�ͻ����ʾ��ɫ
Public Sub InputShowObjectColor(Color As ColorConstants)
       ShowObjectColor = Color
End Sub

'���ͻ����ɫ��ѡ��
Public Function GetShowObjectColor() As ColorConstants
       GetShowObjectColor = ShowObjectColor
End Function

'��ѡ�������뵥λ
Public Sub InputPaperUnits(Units As String)
       Paper.Units = Units
End Sub

'�����λ��ѡ��
Public Function GetPaperUnits() As String
       GetPaperUnits = Paper.Units
End Function

'���������
Public Sub InputPaperRatio(Ratio As Single)  '
       Paper.Ratio = Ratio
End Sub

'���������
Public Function GetPaperRatio() As Single
       GetPaperRatio = Paper.Ratio
End Function

'��������߿�1
Public Sub InputPaperRatio1(Ratio1 As Single)
       Paper.Ratio1 = Ratio1
End Sub

'���������1
Public Function GetPaperRatio1() As Single
       GetPaperRatio1 = Paper.Ratio1
End Function

'��������߿�2
Public Sub InputPaperRatio2(Ratio2 As Single)
       Paper.Ratio2 = Ratio2
End Sub

'���������
Public Function GetPaperRatio2() As Single
       GetPaperRatio2 = Paper.Ratio2
End Function

'Public Function GetLineNum() As Long '�õ�ֱ�ߵ�����
'       GetLineNum = UBound(Tfont)
'End Function

'Public Function GetCircleNum() As Long '�õ�Բ������
'       GetCircleNum = UBound(Tcircle)
'End Function

'Public Function GetFontNum() As Long '�õ����������
'       GetFontNum = UBound(Tfont)
'End Function

Public Function GetLinePoint() As Long '�õ�ֱ�������ָ��
       GetLinePoint = LinePoint
End Function

Public Function GetCirclePoint() As Long '�õ�Բ�������ָ��
    GetCirclePoint = CirclePoint
End Function

Public Function GetFontpoint() As Long '�õ����������ָ��
       GetFontpoint = FontPoint
End Function

Private Sub cad_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim i As Integer, point As snapepoint, Lp As Long, CP As Long
Dim scol As ColorConstants

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Button = vbLeftButton Then MovePaper x, y '�Զ��ƶ�ͼֽ
     
With point    '��׽Ŀ��
     .x = x
     .y = y
     .r = -1
     
     Lp = LinePoint '����ԭָ��
     CP = CirclePoint
     
     If fMainForm.mnuToolSnapeEndPoint.Checked Then
        i = snapeendpoint(x, y, point)
     End If
     
     If fMainForm.mnuToolSnapeMiddlePoint.Checked Then
        i = SnapeMiddlePoint(x, y, point)
     End If
     
     If fMainForm.mnuToolSnapeCentrPoint.Checked Then
        i = SnapeCentrPoint(x, y, point)
     End If
     
     If fMainForm.mnuToolSnapeMissPoint.Checked Then
        i = snapemisspoint(x, y, point)
     End If
     
     '��ʾ��׽����
     If .r > 0 Then
           SSnape.top = .y - SSnape.Height / 2
           SSnape.left = .x - SSnape.Width / 2
           SSnape.Visible = True
     Else
        SSnape.Visible = False
     End If
     
     LinePoint = Lp '�ָ�ԭָ��
     CirclePoint = CP
     
x = .x
y = .y
End With '��׽Ŀ��

     Select Case fMainForm.TCurrentOperist
            Case "������"
                 Select Case DrawFlag
                        Case 1    '����һ��ʱ��ȡ������,�����㲻ȡֵ
                             If Button = VBRUN.vbLeftButton Then
                                Mousepausex = x
                                Mouseleftdownx = x
                                Mousepausey = y
                                Mouseleftdowny = y
                             End If
                  End Select
            Case "ˮƽ��ע", "���㵽Բ������"
                 '����ֵ
            Case "�ƶ�"
                  scol = ShowObjectColor
                  ShowObjectColor = cad.BackColor '��Ϊͼֽɫ
                  ShowObject False, True
                  ShowObjectColor = scol
                  ShowObject True, True
                  Mouseleftdownx = x
                  Mouseleftdowny = y
                  Mousepausex = x
                  Mousepausey = y
            Case "����"
                 EditNew
                 Mousepausex = x
                 Mousepausey = y
                 ShowObject False, False
                 ShowObject True, True
            Case "������ԭͼ"
                 EditNew
                 Mouseleftdownx = x
                 Mouseleftdowny = y
                 Mousepausex = x
                 Mousepausey = y
            Case "��ת"
                 scol = ShowObjectColor
                 ShowObjectColor = cad.BackColor '��Ϊͼֽɫ
                 SelectRectangle.flag = False
                 ShowObject False, True
                 ShowObjectColor = scol
                 ShowObject True, True
                 EditNew
                 Mouseleftdownx = x
                 Mouseleftdowny = y
                 Mousepausex = x
                 Mousepausey = y
            Case "��������"
                 With SelectRectangle
                      If .flag Then
                         Mouseleftdownx = (.X1 + .X2) / 2
                         Mouseleftdowny = (.Y1 + .Y2) / 2
                         Mousepausex = Mouseleftdownx
                         Mousepausey = Mouseleftdowny
                      End If
                 End With
            Case "Բ������"
                 If DrawFlag <> 2 Then
                    With SelectRectangle
                         If .flag Then
                             Mouseleftdownx = (.X1 + .X2) / 2
                             Mouseleftdowny = (.Y1 + .Y2) / 2
                             Mousepausex = Mouseleftdownx
                             Mousepausey = Mouseleftdowny
                             DrawFlag = 1
                         End If
                    End With
                 End If
            Case "pointselect"
                 If Val(cad.Tag) Then
                    For i = 0 To 8
                        If (y - Shape1.Item(i).top) >= 0 And (y - Shape1.Item(i).top) < Shape1.Item(i).Width And (x - Shape1.Item(i).left) >= 0 And (x - Shape1.Item(i).left) < Shape1.Item(i).Height Then
                            MouseChange_OK i, Me
                            cad.Tag = 1
                             Exit For
                        End If
                    Next i
                    If i <> 8 Then
                       DrawFlag = i + 1
                       fMainForm.TCurrentOperist = "�����任"
                       With SelectRectangle
                            Mousepausex = .X2
                            Mousepausey = .Y2
                            Mouseleftdownx = .X1
                            Mouseleftdowny = .Y1
                            '.flag = False
                       End With
                       'showselectrectangle
                       TiShiSelectRectangle x, y, Button, ShowObjectColor, False, cad
                    Else
                       '�ƶ�
                          DrawFlag = 9
                          fMainForm.TCurrentOperist = "�ƶ�"
                          scol = ShowObjectColor
                          ShowObjectColor = cad.BackColor '��Ϊͼֽɫ
                          SelectRectangle.flag = False
                          ShowObject False, True
                          ShowObjectColor = scol
                          ShowObject True, True
                          Mouseleftdownx = x
                          Mouseleftdowny = y
                          Mousepausex = x
                          Mousepausey = y
                    End If
                 End If
            Case "�ж�", "��ֱ�߶�"
                 If DrawFlag = 1 Then
                    Mouseleftdownx = x
                    Mouseleftdowny = y
                    Mousepausex = x
                    Mousepausey = y
                 End If
            Case Else
               If Button = vbLeftButton Then
                    Mouseleftdownx = x
                    Mouseleftdowny = y
                    Mousepausex = x
                    Mousepausey = y
               End If
     End Select
End Sub

Private Sub cad_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Color As ColorConstants, Vx As Single, Vy As Single

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Color = Viewcolor  'Ԥ����ɫ,����ʾ��ɫ

Select Case Mousestyle
       Case "��ʮ�ֹ��" '��ʮ�ֹ��
            With Line1
                 .X1 = 0
                 .Y1 = y
                 .X2 = cad.Width
                 .Y2 = y
            End With
            With Line2
                 .X1 = x
                 .Y1 = 0
                 .X2 = x
                 .Y2 = cad.Height
            End With
       Case "Բ�ι��"
             With Smouse
                  .top = y - SelectField / 2
                  .left = x - SelectField / 2
                  .Height = SelectField
                  .Width = SelectField
             End With
End Select

If Shift = vbShiftMask Then   '��Shift������ʱ
   If Button = vbLeftButton Then
      If Abs(x - Mouseleftdownx) > Abs(y - Mouseleftdowny) Then
         y = Mouseleftdowny
      Else
         x = Mouseleftdownx
      End If
   End If
End If

'TiShi x, y  '��ʾ

If Button = vbLeftButton Then
   MovePaper x, y '�Զ��ƶ�ͼֽ
End If
   
   Select Case fMainForm.TCurrentOperist
        Case "line"
             If Button = vbLeftButton Then
                draw.SingleLine Button, x, y, Color, cad
             End If
        Case "��ֱ�߶�"
             If DrawFlag = 2 Then
                VerticalLine p_Editselect, x, y, True
             End If
        Case "������"
             draw.SingleLine Button, x, y, Color, cad
        Case "���㵽Բ������"
             If DrawFlag = 2 Then
                TiShiLine x, y, vbLeftButton, cad, Color
             End If
        Case "������"
             draw.Three cad, Button, x, y, Color, Tline(UBound(Tline))
        Case "��������"
             draw.�������� cad, x, y, Button, Color, True
        Case "����"
             draw.Rectangle cad, x, y, Color, Button
        Case "������"
             draw.������ cad, Button, x, y, Color, True
        Case "��������"
             draw.�������� cad, Button, x, y, Color, True
        Case "Բ"
             draw.SingleCircle Button, x, y, Color, cad
        Case "Բ��"
             draw.Arc cad, Button, x, y, Color, Tcircle(UBound(Tcircle))
        Case "����"
             draw.Arc cad, Button, x, y, Color, Tcircle(UBound(Tcircle))
        Case "��Բ"
             draw.Ellipse cad, x, y, Button, Color, Tcircle(UBound(Tcircle))
        Case "ˮƽ��ע", "����ˮƽ��ע"
              DimensionHorizontal x, y, Color, True
        Case "��ֱ��ע", "������ֱ��ע"
              DimensionVertical x, y, Color, True
              
        'ע��������Щ��ɫҪ����ʾɫ,�����Color����ͼԤ��ɫ
        Case "�ƶ�", "����"
              EditMove x, y, Button
        Case "��ת"
              EditRound x, y, Button, False
        Case "����", "������ԭͼ"
              EditMirror x, y, Button, False
        Case "��������"
             TiShiSelectRectangle x, y, Button, ShowObjectColor, True, cad
        Case "Բ������"
             Select Case DrawFlag
                    Case 1
                         TiShiCircle Button, x, y, ShowObjectColor, cad, True
                    Case 2
                         TiShiLine x, y, vbLeftButton, cad, ShowObjectColor, True
             End Select
        Case "�����任"
             If DrawFlag = 0 Then
                
             Else
                EditRatioChange x, y, Button, ShowObjectColor, cad, False '�˴���ɫҪ�����ɫ
             End If
        Case "pointselect"
             If DrawFlag = 0 Then MouseChange Button, x, y, Shift
        Case "�ж�"
             If DrawFlag = 2 Then EditBreak x, y, True
   End Select

End Sub

Private Sub cad_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim Color As ColorConstants, rad As Double, xx As Single, yy As Single, Lp As Long, CP As Long
Dim m, i, scol As ColorConstants, point As snapepoint
Dim L As Long
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Shift = vbShiftMask And (fMainForm.TCurrentOperist.text <> "pointselect") Then  '��Shift������ʱ
   If Button = vbLeftButton Then
      If Abs(x - Mouseleftdownx) > Abs(y - Mouseleftdowny) Then
         y = Mouseleftdowny
      Else
         x = Mouseleftdownx
      End If
   End If
End If

If Button = vbRightButton Then   '��ݲ˵�
   QuikMenu x, y
End If

With point    '��׽Ŀ��
     .x = x
     .y = y
     .r = -1
     
     Lp = LinePoint '����ԭָ��
     CP = CirclePoint
     
     If fMainForm.mnuToolSnapeEndPoint.Checked Then
        i = snapeendpoint(x, y, point)
     End If
     
     If fMainForm.mnuToolSnapeMiddlePoint.Checked Then
        i = SnapeMiddlePoint(x, y, point)
     End If
     
     If fMainForm.mnuToolSnapeCentrPoint.Checked Then
        i = SnapeCentrPoint(x, y, point)
     End If
     
     If fMainForm.mnuToolSnapeMissPoint.Checked Then
        i = snapemisspoint(x, y, point)
     End If
     
     '��ʾ��׽����
     If .r > 0 Then
           SSnape.top = .y - SSnape.Height / 2
           SSnape.left = .x - SSnape.Width / 2
           SSnape.Visible = True
     Else
        SSnape.Visible = False
     End If
     
     LinePoint = Lp '�ָ�ԭָ��
     CirclePoint = CP
     
x = .x
y = .y
End With '��׽Ŀ��

If Button = vbLeftButton Then
   Color = Viewcolor
   SaveParameter cad  '�������
   
   '��ֹ��Բ���ĵ�������������������,����ֱ��
   If (fMainForm.TCurrentOperist = "Բ��" Or fMainForm.TCurrentOperist = "����") And DrawFlag = 2 Then
       DrawFlag = 4
   End If
   
   Select Case fMainForm.TCurrentOperist
       Case "line"
                '����ο�ֱ��
                cad.DrawMode = 7
                cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
                '��ʾȷ����ֱ��
                cad.DrawMode = VBRUN.vbCopyPen
                cad.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), LineColor
                '�洢ֱ�߲���
                ReDim Preserve Tline(UBound(Tline) + 1)
                With Tline(UBound(Tline))
                     .X2 = Mousepausex
                     .Y2 = Mousepausey
                End With
                SaveCommonParameter "line"   '���湫������
        Case "��ֱ�߶�"
             Select Case DrawFlag
                    Case 1
                         p_Editselect = 0
                         p_Editselect = EditSelectLine(x, y)
                         If p_Editselect Then
                            DrawFlag = 2
                            EditSelectLineShow p_Editselect, True
                         End If
                    Case 2
                         cad.DrawMode = vbXorPen
                         cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), ShowObjectColor '���ԭͼ��
                         With Tline(p_Editselect)
                              VerticalPoint xx, yy, x, y, .X1, .Y1, .X2, .Y2 'xx,yy Ϊ����
                         End With
                         cad.DrawMode = vbCopyPen
                         cad.Line (xx, yy)-(x, y), LineColor
                         Mouseleftdownx = xx
                         Mouseleftdowny = yy
                         ReDim Preserve Tline(UBound(Tline) + 1)
                         With Tline(UBound(Tline))
                              .X2 = x
                              .Y2 = y
                         End With
                         SaveCommonParameter "line"
                         EditSelectLineShow p_Editselect, True
                         DrawFlag = 1
             End Select
        Case "������"   '���һ�ߵ�ȷ���ڹ���(Public Sub ȷ�����������ֱ��(flag As String))��
             Select Case DrawFlag
                    Case 1
                            '����ο�ֱ��
                            cad.DrawMode = 7
                            cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
                            '��ʾȷ����ֱ��
                            cad.DrawMode = VBRUN.DrawModeConstants.vbNotXorPen
                            cad.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), LineColor
                            '�洢ֱ�߲���
                            ReDim Preserve Tline(UBound(Tline) + 1)
                            With Tline(UBound(Tline))
                                 .X2 = x  '�洢�����ߵĵڶ���
                                 .Y2 = y
                                 .Style = 10  '��ʼֱ��
                            End With
                            SaveCommonParameter "������"  '���������Ĵ洢,���������ߵĵ�һ��
                            DrawFlag = 2     '����һ����־
                    Case 2
                            '����ο�ֱ��
                            cad.DrawMode = 7
                            cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
                            '��ʾȷ����ֱ��
                            cad.DrawMode = VBRUN.vbCopyPen
                            cad.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), LineColor
                            '�洢ֱ�߲���
                            ReDim Preserve Tline(UBound(Tline) + 1)
                            With Tline(UBound(Tline))
                                 .X2 = x   '�洢��һ��
                                 .Y2 = y
                                 .Style = 12 ' �м�ֱ��
                            End With
                            SaveCommonParameter "������"  '���������Ĵ洢,����ǰһ��
            End Select
            '����һֱ����㸳ֵ
            Mouseleftdownx = x
            Mouseleftdowny = y
        Case "���㵽Բ������"
             Select Case DrawFlag
                    Case 1
                         ReDim Preserve Tline(UBound(Tline) + 1)
                         Mouseleftdownx = x
                         Mouseleftdowny = y
                         Mousepausex = x
                         Mousepausey = y
                         SaveCommonParameter "line"
                         DrawFlag = 2
                    Case 2
                         p_Editselect = 0
                         p_Editselect = EditSelectCircle(x, y)
                         If p_Editselect Then
                            If PointToCircleTanLine(p_Editselect, x, y) Then
                               DrawFlag = 1
                            End If
                         End If
             End Select
        Case "������"
               Select Case DrawFlag
                   Case 1
                       '����ο�ֱ��
                       cad.DrawMode = 7
                       cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
                       '��ʾȷ����ֱ��
                       'cad.DrawMode = VBRUN.vbCopyPen
                       cad.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), LineColor
                       '�洢�����β���
                        ReDim Preserve Tline(UBound(Tline) + 1)
                        '�������
                        With Tline(UBound(Tline))
                             .X2 = x   '�ڶ���
                             .Y2 = y
                        End With
                        SaveCommonParameter "������"
                        DrawFlag = 2  '��������
                   Case 2
                        cad.DrawMode = 7
                        With Tline(UBound(Tline))
                            '�����ο���
                             cad.Line (.X1, .Y1)-(Mousepausex, Mousepausey), Color
                             cad.Line (.X2, .Y2)-(Mousepausex, Mousepausey), Color
                            'ȷ��������
                            cad.DrawMode = VBRUN.vbCopyPen
                            cad.Line (.X1, .Y1)-(x, y), LineColor
                            cad.Line (.X2, .Y2)-(x, y), LineColor
                        End With
                        ReDim Preserve Tline(UBound(Tline) + 1)
                        With Tline(UBound(Tline))
                            '�������
                            .X2 = x
                            .Y2 = y
                        End With
                        SaveCommonParameter "������"
                        DrawFlag = 1 '��������
                            'redraw
               End Select
        Case "��������"
             �������� cad, x, y, Button, Color, False '����ο�ͼ��
             ReDim Preserve Tline(UBound(Tline) + 1)
             '�������
             With Tline(UBound(Tline))
                 .X2 = x
                 .Y2 = y
             End With
             SaveCommonParameter "��������"
             cad.DrawMode = vbCopyPen
             For i = UBound(Tline) To UBound(Tline) - 2 Step -1
                 With Tline(i)
                      cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
                 End With
             Next i
        Case "������"
            ������ cad, Button, x, y, Color, False
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X2 = x
                 .Y2 = y
            End With
            SaveCommonParameter "������"
            cad.DrawMode = vbCopyPen
            For i = UBound(Tline) To UBound(Tline) - 3 Step -1
                With Tline(i)
                     cad.Line (.X1, .Y1)-(.X2, .Y2), LineColor
                End With
            Next i
        Case "����"
            cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color, B
            Mousepausex = x
            Mousepausey = y
            SaveCommonParameter "����"
            cad.DrawMode = vbCopyPen
            cad.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), LineColor, B
        Case "��������"
            �������� cad, Button, x, y, Color, False '����ο�ͼ��
            ReDim Preserve Tline(UBound(Tline) + 1)
            ''�������
            With Tline(UBound(Tline))
                 .X2 = x
                 .Y2 = y
            End With
            SaveCommonParameter "��������"
            'ȷ��ͼ��
            cad.DrawMode = vbCopyPen
            For i = UBound(Tline) To UBound(Tline) - 5 Step -1
                With Tline(i)
                     cad.Line (.X1, .Y1)-(.X2, .Y2), LineColor
                End With
            Next i
        Case "Բ"
             cad.DrawMode = vbXorPen
             cad.Circle (Mouseleftdownx, Mouseleftdowny), TwoPointDirection(Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey), Color
             ReDim Preserve Tcircle(UBound(Tcircle) + 1)
             rad = TwoPointDirection(Mouseleftdownx, Mouseleftdowny, x, y)
             cad.DrawMode = vbCopyPen
             Tcircle(UBound(Tcircle)).Radius = rad
             cad.Circle (Mouseleftdownx, Mouseleftdowny), rad, LineColor
             SaveCommonParameter "Բ"
        Case "Բ��", "����"
             cad.DrawMode = vbXorPen
             Select Case DrawFlag
                     Case 1    '�ο�Բ
                          ReDim Preserve Tcircle(UBound(Tcircle) + 1)
                          'ȷ��Բ�뾶
                          rad = Sqr((Mouseleftdownx - x) ^ 2 + _
                                    (Mouseleftdowny - y) ^ 2)
                          '�洢Բ���Ĳ���
                          Tcircle(UBound(Tcircle)).Radius = rad '�뾶
                          SaveCommonParameter "Բ��"  '���������Ĵ洢
                          '�ο�ֱ��
                          cad.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color
                          Mousepausex = x
                          Mousepausey = y
                          DrawFlag = 2
                     Case 4  '���������ǰ��,�ο�ֱ��,�ο�Բ��,��ʼ��
                           '��ֹ��Բ���ĵ�������������������,����ֱ��
                           xx = x - Tcircle(UBound(Tcircle)).x0
                           yy = y - Tcircle(UBound(Tcircle)).y0
                           If fMainForm.TCurrentOperist = "Բ��" Then
                              rad = math.Angle(xx, yy)  '����ʼ��
                           Else   '����
                              rad = -math.Angle(xx, yy)  '����ʼ��
                           End If
                           Tcircle(UBound(Tcircle)).Start = rad
                           DrawFlag = 3
                     Case 3 '�ο�ֱ��,�ο�Բ��,��ֹ��
                          '�����ο���
                          'cad.DrawMode = 7
                          With Tcircle(UBound(Tcircle))
                               cad.Line (.x0, .y0)-(Mousepausex, Mousepausey), Color
                               xx = x - .x0
                               yy = y - .y0
                               If fMainForm.TCurrentOperist = "Բ��" Then
                                  rad = math.Angle(xx, yy)  '�������
                               Else '����
                                  rad = -math.Angle(xx, yy)  '�������
                               End If
                               .end = rad
                               'ȷ��Բ��
                               cad.DrawMode = VBRUN.vbCopyPen
                               cad.Circle (.x0, .y0), .Radius, .Commonparameter.Color, .Start, .end
                          End With
                          DrawFlag = 1
             End Select
        Case "��Բ"
            If DrawFlag = 1 Then
               ReDim Preserve Tcircle(UBound(Tcircle) + 1)
               'ȷ��Բ�뾶
               rad = Sqr((Mouseleftdownx - x) ^ 2 + _
                     (Mouseleftdowny - y) ^ 2)
               '�洢��Բ�Ĳ���
               Tcircle(UBound(Tcircle)).Radius = rad   '�뾶
               SaveCommonParameter "Բ��"  '���������Ĵ洢
               Mousepausex = 1       '��ʱ���������
               DrawFlag = 2
            Else
               With Tcircle(UBound(Tcircle))
                    '����ο�ͼ��
                    cad.Circle (.x0, .y0), .Radius, Color, , , Mousepausex
                    .Aspect = Abs((y - .y0) / .Radius)
                    'ȷ����Բ
                    cad.DrawMode = vbCopyPen
                    cad.Circle (.x0, .y0), .Radius, .Commonparameter.Color, , , .Aspect
               End With
               DrawFlag = 1
            End If
        Case "����"
             With InputText
                  .xx = x
                  .yy = y
                  .Show 1
             End With
        Case "ˮƽ��ע", "����ˮƽ��ע"
             DimensionHorizontalSaveParameter x, y, Color
        Case "��ֱ��ע", "������ֱ��ע"
              DimensionVerticalSaveParameter x, y, Color
        
        'ѡȡĿ��,ע�������е���ɫҪ����ʾɫ,�����Color�е���ɫ����ͼԤ��ɫ
        Case "pointselect" '��ѡ
              SelectPointObject x, y, Shift, True
        
        Case "�ƶ�", "����"
              scol = ShowObjectColor
              ShowObjectColor = cad.BackColor
              ShowObject False, True   '��Ϊͼֽɫ
              ShowObjectColor = scol
              ShowObject True, True    '��Ϊͻ��ɫ
              fMainForm.TCurrentOperist = "pointselect"
              DrawFlag = 0
        Case "��ת"
              scol = ShowObjectColor
              ShowObjectColor = cad.BackColor
              ShowObject False, True
              ShowObjectColor = scol
              EditRound x, y, Button, True
              ShowObject True, True    '��Ϊͻ��ɫ
        Case "����"
              EditMirror x, y, Button, True
        Case "������ԭͼ"
              EditMirror x, y, Button, True
        Case "��������"
              TiShiSelectRectangle x, y, Button, ShowObjectColor, False, cad
              Set FrmArray.object = Me
              FrmArray.Option1.Value = True
              FrmArray.Show 1
        Case "Բ������"
             Select Case DrawFlag
                    Case 1
                        Set FrmArray.object = Me
                        With FrmArray
                             .Option2.Value = True
                             .Text1.text = CStr(x)
                             .Text5.text = CStr(y)
                        End With
                         TiShiLine x, y, vbLeftButton, cad, ShowObjectColor, False 'Ϊ��������ο�ֱ��
                         DrawFlag = 2
                    Case 2
                         DrawFlag = 1
                         TiShiLine x, y, Button, cad, ShowObjectColor, False '����ο�ֱ��
                         With SelectRectangle
                              Mousepausex = (.X1 + .X2) / 2
                              Mousepausey = (.Y1 + .Y2) / 2
                         End With
                         With FrmArray
                              xx = x - Mouseleftdownx
                              yy = y - Mouseleftdowny
                              rad = Angle(xx, yy)
                              xx = Mousepausex - Mouseleftdownx
                              yy = Mousepausey - Mouseleftdowny
                              rad = rad - Angle(xx, yy)
                              .Text4.text = CStr(ArcToAngle(rad))
                              .Show 1
                         End With
             End Select
        Case "�����任"
             EditRatioChange x, y, Button, ShowObjectColor, cad, True
             fMainForm.TCurrentOperist.text = "pointselect"
             DrawFlag = 0  '�任��������Ϊѡȡ
        Case "�ж�"
             Select Case DrawFlag
                    Case 1
                         EditBreakSelect x, y, 0
                         DrawFlag = 2
                    Case 2
                         EditBreak x, y, False
                         EditBreak_Ok x, y
                         EditBreakShow False
                         DrawFlag = 1
             End Select
        Case "Բ��"
             Select Case DrawFlag
                    Case 1
                         p_Editselect = 0
                         p_Editselect = EditSelectLine(x, y)
                         If p_Editselect Then
                             EditSelectLineShow p_Editselect, True
                             DrawFlag = 2
                         End If
                    Case 2
                         L = EditSelectLine(x, y)
                         If L Then
                            EditFillet x, y, p_Editselect, L
                            DrawFlag = 1
                         End If
             End Select
        Case "�н�"
             Select Case DrawFlag
                    Case 1
                         p_Editselect = 0
                         p_Editselect = EditSelectLine(x, y)
                         If p_Editselect Then
                             EditSelectLineShow p_Editselect, True
                             DrawFlag = 2
                         End If
                    Case 2
                         L = EditSelectLine(x, y)
                         If L Then
                            EditChamfer x, y, p_Editselect, L
                            DrawFlag = 1
                         End If
             End Select
        Case "�޸�����"
             EditModifyText x, y
        Case "ʹ��ֱ���ཻ"
             Select Case DrawFlag
                    Case 1
                         p_Editselect = 0 '��ʼ��
                         p_Editselect = EditSelectLine(x, y)
                         If p_Editselect Then
                            DrawFlag = 2
                            EditSelectLineShow p_Editselect, True
                         End If
                    Case 2
                         L = 0 '��ʼ��
                         L = EditSelectLine(x, y)
                         If L Then
                            EditTwoLineMiss L, p_Editselect
                            DrawFlag = 1
                         End If
             End Select
   End Select
End If
RedoParameter cad   '�ָ�����
End Sub

Private Sub cad_Resize()
'        Paper_Gird cad     'դ��
End Sub

'��ʼ��դ��
Public Sub Paper_Gird(object As Object)
Dim i
        For i = 1 To 20
            Load GIRDl(GIRDl.Count)
            With GIRDl.Item(GIRDl.UBound)
                 .X1 = i * 100
                 .X2 = i * 100
                 .Y1 = 0
                 .Y2 = object.Height
                 .Visible = True
            End With
        Next i
   
End Sub

Private Sub Initial() '��ʼ��
Dim i, ss As String * 20

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
    
    '�����ֵ�ɴ������ļ��еõ�
    i = GetPrivateProfileString("ѡ��", "�����״", "Сʮ�ֹ��", ss, 20, Inifile)
    If i = 0 Then ss = "Сʮ�ֹ��"
     '����ʼ��״,��Ϊ�ڹ���Form_Activate�з���,���Կ��Ե���,���Form_Activate
    Mousestyle = left$(ss, i / 2) '����2����Ϊ�������ļ�ʱ,���İ�2���ֽڼ���
    '�Զ��������ɫ
    i = GetPrivateProfileString("ѡ��", "�Զ��������ɫ", "0", ss, 20, Inifile)
    If i <> 0 Then
       Line1.BorderColor = Val(left$(ss, i))
       Line2.BorderColor = Line1.BorderColor
       'Smouse.BorderColor = Line1.BorderColor
    End If
    'ͻ����ʾ��ɫ
    i = GetPrivateProfileString("ѡ��", "ͻ����ʾ��ɫ", "65535", ss, 20, Inifile)
    If i = 0 Then
       ss = "65535"  '��ɫ
    Else
       ss = left$(ss, i)
    End If
    ShowObjectColor = Val(ss)
    For i = 0 To 8
        With Shape1(i)
             .BorderColor = ShowObjectColor
             .FillColor = ShowObjectColor
        End With
    Next i
    SPshow.BorderColor = ShowObjectColor
    
    SelectField = 250
    
    SelectRectangle.flag = False
    
    PaperInit cad           'ͼֽ��ʼ��
    
    With Paper                   'ͼֽ�Ĵ�С
         .Width = cad.Width
         .Height = cad.Height
    End With
    ReDim Tline(0)               '���ٴ洢��
    ReDim Tcircle(0)
    ReDim Tfont(0)
    
    LineColor = vbBlack          ' ���Ͳ���
      
End Sub

Private Sub Form_Load()
    
    Initial
    
    Form_Resize  '�����С�ĸı�

End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

     If CurrentOperistFlag Then
        Cancel = MsgBox("Ҫ���� " + Me.Caption + " ��?", vbQuestion + vbYesNoCancel, "���� " + Me.Caption)
        Select Case Cancel
               Case vbYes  '�Ǳ����ļ�
                    fMainForm.mnuFileSave_Click
                    Cancel = 0    '��ֵΪ0ж�ش���,��Ϊ0��ж�ش���,��ֵ���ݸ�Form_Unload(Cancel as Integer)����
               Case vbCancel  'ȡ��,���˳�����
                    fMainForm.CloseAllWindowFlag = False
               Case Else    '�������ļ��˳�����
                    Cancel = 0
        End Select
     End If
End Sub

Private Sub Form_Resize()  '�����С�ĸı�
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
    'ͼ��
    desk.Move 255, 255, Me.Scalewidth - 500, Me.ScaleHeight - 500
    '��������С.λ��
    HScroll.Move desk.left, Me.ScaleHeight - 255, desk.Width, 255      '������
    Vscroll.Move Me.Scalewidth - 255, desk.top, 255, desk.Height
    Scroll Me, Abs(cad.left), Abs(cad.top)
    '���
    SliderH.Move desk.left, 0, desk.Width, 255
    SliderV.Move 0, desk.top, 255, desk.Height
End Sub

Public Sub Form_Activate()  '�����˵��е������״�ĸ�ѡ��
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

       '�����Ϊ�����ʱ����
        Select Case Mousestyle
               Case "���ι��"     '���ι��
                    fMainForm.mnuViewMouseArrow_Click
               Case "Сʮ�ֹ��"      'Сʮ�ֹ��
                    fMainForm.mnuViewMouseLittleCross_Click
               Case "��ʮ�ֹ��"  '��ʮ�ֹ��
                    fMainForm.mnuViewMouseBigCross_Click
               Case "Բ�ι��"
                    fMainForm.mnuViewMouseCircle_Click
        End Select
End Sub

Private Sub HScroll_Change()
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

        cad.left = -HScroll.Value
        ViewLimit
End Sub

Private Sub HScroll_Scroll()
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

        cad.left = -HScroll.Value
        ViewLimit
End Sub

Private Sub Vscroll_Change()
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

        cad.top = -Vscroll.Value
        ViewLimit
End Sub

Private Sub Vscroll_Scroll()
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

        cad.top = -Vscroll.Value
        ViewLimit
End Sub

Public Sub ViewLimit()  '�Զ��ƶ�ͼֽ�����ȷ��
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

       With cad
            If .left >= 0 Then
                Limit.X1 = 0
            Else
                Limit.X1 = cad.ScaleX(desk.Scalewidth / 15) - .left
            End If
            
            If .top >= 0 Then
               Limit.Y1 = 0
            Else
               Limit.Y1 = cad.ScaleY(desk.ScaleHeight / 15) - .top
            End If
            
            If .left + .Width <= cad.ScaleX(desk.Scalewidth) Then
                Limit.X2 = .Width
            Else
                Limit.X2 = cad.ScaleX(desk.Scalewidth * 14 / 15) + Limit.X1 ' - .left
            End If
            
            If .top + .Height <= cad.ScaleY(desk.ScaleHeight) Then
               Limit.Y2 = .Height
            Else
               Limit.Y2 = cad.ScaleY(desk.ScaleHeight * 14 / 15) + Limit.Y1 '- .top
            End If
       End With
End Sub

Private Sub MovePaper(x As Single, y As Single)  '�Զ��ƶ�ͼֽ
Dim n As Single
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

   With Limit
        If x < .X1 Then
           n = cad.left + cad.ScaleX(desk.Scalewidth / 15)
           If n > 0 Then n = 0
           Scroll Me, n, cad.top
        End If
        If x > .X2 Then
           n = cad.left - cad.ScaleX(desk.Scalewidth / 15)
           If n + cad.Width < cad.ScaleX(desk.Scalewidth) Then n = cad.ScaleX(desk.Scalewidth) - cad.Width
           Scroll Me, n, cad.top
        End If
        If y < .Y1 Then
           n = cad.top + cad.ScaleY(desk.ScaleHeight / 15)
           If n > 0 Then n = 0
           Scroll Me, cad.left, n
        End If
        If y > .Y2 Then
           n = cad.top - cad.ScaleY(desk.ScaleHeight / 15)
           If n + cad.Height < cad.ScaleY(desk.ScaleHeight) Then n = cad.ScaleY(desk.ScaleHeight) - cad.Height
           Scroll Me, cad.left, n
        End If
   End With
End Sub

Private Sub Text_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        cad_MouseMove Button, Shift, x + text(Index).left, y + text(Index).top
End Sub

Private Sub Text_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        cad_MouseUp Button, Shift, x + text(Index).left, y + text(Index).top
End Sub

Private Sub Text_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        cad_MouseDown Button, Shift, x + text(Index).left, y + text(Index).top
End Sub

'��������
Public Sub AddText(x As Single, y As Single, Word As String, Style As Integer, point As Long)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        ReDim Preserve Tfont(UBound(Tfont) + 1)
        With Tfont(UBound(Tfont))
             .x = x
             .y = y
             .text = Word
             '.Style = Style
             .point = 0    '��Ϊ�ǵ�������,��ָ��
             .Height = cad.TextHeight(Word)
             .Width = cad.TextWidth(Word)
             .Font.Color = cad.ForeColor
             .Font.Bold = cad.Font.Bold
             .Font.Italic = cad.Font.Italic
             .Font.name = cad.Font.name
             .Font.Size = cad.Font.Size
             .Font.Strikethru = cad.Font.Strikethrough
             .Font.Transparent = cad.FontTransparent
             .Font.Underline = cad.Font.Underline
        End With
        Load text(text.Count) '�����µ�����Ԫ��
        With text(text.UBound)
             .Font = cad.Font
             .top = y
             .left = x
             .Caption = Word
             .BackColor = cad.BackColor
             .ForeColor = cad.ForeColor
             .Visible = True
             .Font.Bold = cad.Font.Bold
             .Font.Italic = cad.Font.Italic
             .Font.name = cad.Font.name
             .Font.Size = cad.Font.Size
             .Font.Strikethrough = cad.Font.Strikethrough
             .Font.Underline = cad.Font.Underline
        End With
End Sub

'��ע����
Private Sub DimensionText(x As Single, y As Single, Word As String, point As Long)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        ReDim Preserve Tfont(UBound(Tfont) + 1)
        With Tfont(UBound(Tfont))
             .text = Word
             '.Style = Style
             .point = point
             .x = x
             .y = y
             .Font.Color = Dimension.Font.Color
             .Font.Bold = Dimension.Font.Bold
             .Font.Italic = Dimension.Font.Italic
             .Font.name = Dimension.Font.name
             .Font.Size = Dimension.Font.Size
             .Font.Strikethru = Dimension.Font.Strikethru
             .Font.Transparent = Dimension.Font.Transparent
             .Font.Underline = Dimension.Font.Underline
             
             desk.Font.Bold = Dimension.Font.Bold
             desk.Font.Italic = Dimension.Font.Italic
             desk.Font.name = Dimension.Font.name
             desk.Font.Size = Dimension.Font.Size
             desk.Font.Strikethrough = Dimension.Font.Strikethru
             desk.Font.Underline = Dimension.Font.Underline
             .Height = desk.TextHeight(Word)
             .Width = desk.TextWidth(Word)
        End With
        Load text(text.Count) '�����µ�����Ԫ��
        With text(text.UBound)
             .Font = cad.Font
             .top = y - .Height / 2
             .left = x - .WhatsThisHelpID / 2
             .Caption = Word
             .BackColor = cad.BackColor
             .ForeColor = Dimension.Font.Color
             .Visible = True
             .Font.Bold = Dimension.Font.Bold
             .Font.Italic = Dimension.Font.Italic
             .Font.name = Dimension.Font.name
             .Font.Size = Dimension.Font.Size
             .Font.Strikethrough = Dimension.Font.Strikethru
             .Font.Underline = Dimension.Font.Underline
        End With
End Sub

Public Sub SaveFile(FileName As String)    '�����ļ�
Dim num '�ļ���
Dim n As Long, i As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

    CurrentOperistFlag = False   '�ļ������,��Ϊ�޲���
    num = FreeFile
    Open FileName For Output As #num
    Print #num, "�������ͼ,���:����"  '�ļ���־
    Print #num, "2001.6"
    With Paper
         Print #num, .Color
         Print #num, .Height
         Print #num, .Ratio
         Print #num, .Ratio1
         Print #num, .Ratio2
         Print #num, .ScaleHeight
         Print #num, .Scalewidth
         Print #num, .Units
         Print #num, .Width
    End With
    n = UBound(Tline)
    If n > 0 Then
       Print #num, "line"
       Print #num, n
       For i = 1 To n
            With Tline(i)
                 Print #num, .X1
                 Print #num, .Y1
                 Print #num, .X2
                 Print #num, .Y2
                 Print #num, .Style
                 Print #num, .Commonparameter.Color
                 Print #num, .Commonparameter.Style
                 Print #num, .Commonparameter.Width
            End With
       Next i
    End If
    n = UBound(Tcircle)
    If n > 0 Then
       Print #num, "arc"
       Print #num, n
       For i = 1 To n
           With Tcircle(i)
                Print #num, .x0
                Print #num, .y0
                Print #num, .Radius
                Print #num, .Start
                Print #num, .end
                Print #num, .Aspect
                Print #num, .Commonparameter.Color
                Print #num, .Commonparameter.Style
                Print #num, .Commonparameter.Width
           End With
       Next i
    End If
    n = UBound(Tfont)
    If n > 0 Then
       Print #num, "font"
       Print #num, n
       For i = 1 To n
           With Tfont(i)
                Print #num, .Angle
                Print #num, .flag
                Print #num, .Font.Bold
                Print #num, .Font.Color
                Print #num, .Font.Italic
                Print #num, .Font.name
                Print #num, .Font.Size
                Print #num, .Font.Strikethru
                Print #num, .Font.Transparent
                Print #num, .Font.Underline
                Print #num, .Height
                Print #num, .point
                Print #num, .Posion
                Print #num, .text
                Print #num, .Width
                Print #num, .x
                Print #num, .y
           End With
       Next i
    End If
    Close #num
End Sub

Public Sub OpenFile(FileName As String) '���ļ�
Dim num, n, i, ss As String

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

num = FreeFile
    Open FileName For Input As #num
    Line Input #num, ss
    If ss <> "�������ͼ,���:����" Then '�ļ���־
       i = MsgBox("�ļ����Ͳ���.", vbCritical, App.Title)
       Close #num
       Exit Sub
    End If
    Input #num, ss
    If ss <> "2001.6" Then
       i = MsgBox("�ļ����Ͳ���.")
       Exit Sub
    End If
    With Paper
         Input #num, .Color
         Input #num, .Height
         Input #num, .Ratio
         Input #num, .Ratio1
         Input #num, .Ratio2
         Input #num, .ScaleHeight
         Input #num, .Scalewidth
         Input #num, .Units
         Input #num, .Width
    End With
    While Not (EOF(num))
          Input #num, ss
          Select Case ss
                 Case "line"
                      Input #num, n
                      ReDim Preserve Tline(n)
                      For i = 1 To n
                          With Tline(i)
                               Input #num, .X1
                               Input #num, .Y1
                               Input #num, .X2
                               Input #num, .Y2
                               Input #num, .Style
                               Input #num, .Commonparameter.Color
                               Input #num, .Commonparameter.Style
                               Input #num, .Commonparameter.Width
                          End With
                      Next i
                Case "arc"
                      Input #num, n
                      ReDim Preserve Tcircle(n)
                      For i = 1 To n
                          With Tcircle(i)
                               Input #num, .x0
                               Input #num, .y0
                               Input #num, .Radius
                               Input #num, .Start
                               Input #num, .end
                               Input #num, .Aspect
                               Input #num, .Commonparameter.Color
                               Input #num, .Commonparameter.Style
                               Input #num, .Commonparameter.Width
                          End With
                      Next i
                Case "font"
                     Input #num, n
                     ReDim Preserve Tfont(n)
                     For i = 1 To n
                         With Tfont(i)
                              Input #num, .Angle
                              Input #num, .flag
                              Input #num, .Font.Bold
                              Input #num, .Font.Color
                              Input #num, .Font.Italic
                              Input #num, .Font.name
                              Input #num, .Font.Size
                              Input #num, .Font.Strikethru
                              Input #num, .Font.Transparent
                              Input #num, .Font.Underline
                              Input #num, .Height
                              Input #num, .point
                              Input #num, .Posion
                              Input #num, .text
                              Input #num, .Width
                              Input #num, .x
                              Input #num, .y
                              Load text(text.Count)
                              LetFont Tfont(i), text(text.UBound), False
                         End With
                     Next i
          End Select
     Wend
     Close #num
     Redraw
End Sub

Private Sub SaveCommonParameter(name As String)    '���湫������
Dim X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Select Case name
       Case "line"
            With Tline(UBound(Tline))
                 .X1 = Mouseleftdownx
                 .Y1 = Mouseleftdowny
                 .Style = 0     'ֱ��
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
            End With
       Case "������"
            With Tline(UBound(Tline))
                 .X1 = Mouseleftdownx
                 .Y1 = Mouseleftdowny
                 '.Style ��cad_moveup�и�ֵ��Public Sub ȷ�����������ֱ��(flag As String)�и�ֵ
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
            End With
       Case "������"
                       '     1 /\
                       '      /  \
                       '  31 /    \33
                       '    /      \
                       ' 2 /________\3
                       '      32
            Select Case DrawFlag
                   Case 1
                        With Tline(UBound(Tline))
                             .X1 = Mouseleftdownx
                             .Y1 = Mouseleftdowny
                             .Commonparameter.Color = LineColor
                             .Commonparameter.Style = cad.DrawStyle
                             .Commonparameter.Width = cad.DrawWidth
                             .Style = 31   ' ��һ��
                        End With
                   Case 2
                        With Tline(UBound(Tline))
                             .X1 = Tline(UBound(Tline) - 1).X2
                             .Y1 = Tline(UBound(Tline) - 1).Y2
                             .Commonparameter.Color = LineColor
                             .Commonparameter.Style = cad.DrawStyle
                             .Commonparameter.Width = cad.DrawWidth
                             .Style = 32  '�ڶ���
                        End With
                        ReDim Preserve Tline(UBound(Tline) + 1)
                        With Tline(UBound(Tline))
                             .X1 = Tline(UBound(Tline) - 1).X2
                             .Y1 = Tline(UBound(Tline) - 1).Y2
                             .X2 = Tline(UBound(Tline) - 2).X1
                             .Y2 = Tline(UBound(Tline) - 2).Y1
                             .Commonparameter.Color = LineColor
                             .Commonparameter.Style = cad.DrawStyle
                             .Commonparameter.Width = cad.DrawWidth
                             .Style = 33  '������
                        End With
            End Select
       Case "��������"
            With Tline(UBound(Tline))
                 .X1 = Mouseleftdownx
                 .Y1 = Mouseleftdowny
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 31   ' ��һ��
            math.SamethreeThirdVertex Mouseleftdownx, Mouseleftdowny, .X2, .Y2, x3, y3
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = Tline(UBound(Tline) - 1).X2
                 .Y1 = Tline(UBound(Tline) - 1).Y2
                 .X2 = x3
                 .Y2 = y3
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 32  '�ڶ���
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
                  With Tline(UBound(Tline))
                       .X1 = x3
                       .Y1 = y3
                       .X2 = Mouseleftdownx
                       .Y2 = Mouseleftdowny
                       .Commonparameter.Color = LineColor
                       .Commonparameter.Style = cad.DrawStyle
                       .Commonparameter.Width = cad.DrawWidth
                       .Style = 33  '������
                   End With
       Case "����"
            X1 = Mouseleftdownx: Y1 = Mouseleftdowny
            x3 = Mousepausex: y3 = Mousepausey
            X2 = x3: Y2 = Y1
            x4 = X1: y4 = y3
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = X1
                 .Y1 = Y1
                 .X2 = X2
                 .Y2 = Y2
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 41   ' ��һ��
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = X2
                 .Y1 = Y2
                 .X2 = x3
                 .Y2 = y3
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 42   ' �ڶ���
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x3
                 .Y1 = y3
                 .X2 = x4
                 .Y2 = y4
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 43   ' ������
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x4
                 .Y1 = y4
                 .X2 = Mouseleftdownx
                 .Y2 = Mouseleftdowny
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 44   ' ���ı�
            End With
       Case "������"
            With Tline(UBound(Tline))
                 .X1 = Mouseleftdownx
                 .Y1 = Mouseleftdowny
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 41   ' ��һ��
            math.samerectanglethreeandforupiont Mouseleftdownx, Mouseleftdowny, .X2, .Y2, x3, y3, x4, y4
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = Tline(UBound(Tline) - 1).X2
                 .Y1 = Tline(UBound(Tline) - 1).Y2
                 .X2 = x3
                 .Y2 = y3
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 42   ' �ڶ���
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x3
                 .Y1 = y3
                 .X2 = x4
                 .Y2 = y4
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 43   ' ������
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x4
                 .Y1 = y4
                 .X2 = Mouseleftdownx
                 .Y2 = Mouseleftdowny
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 44   ' ���ı�
            End With
       Case "��������"
            With Tline(UBound(Tline))
                 .X1 = Mouseleftdownx
                 .Y1 = Mouseleftdowny
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 61   ' ��һ��
            math.sixegdefour Mouseleftdownx, Mouseleftdowny, .X2, .Y2, x3, y3, x4, y4, x5, y5, x6, y6
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = Tline(UBound(Tline) - 1).X2
                 .Y1 = Tline(UBound(Tline) - 1).Y2
                 .X2 = x3
                 .Y2 = y3
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 62   ' �ڶ���
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x3
                 .Y1 = y3
                 .X2 = x4
                 .Y2 = y4
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 63   ' ������
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x4
                 .Y1 = y4
                 .X2 = x5
                 .Y2 = y5
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 64  ' ���ı�
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x5
                 .Y1 = y5
                 .X2 = x6
                 .Y2 = y6
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 65  ' �����
            End With
            ReDim Preserve Tline(UBound(Tline) + 1)
            With Tline(UBound(Tline))
                 .X1 = x6
                 .Y1 = y6
                 .X2 = Mouseleftdownx
                 .Y2 = Mouseleftdowny
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
                 .Style = 66  ' ������
            End With
       Case "Բ", "Բ��"
            With Tcircle(UBound(Tcircle))
                 .x0 = Mouseleftdownx
                 .y0 = Mouseleftdowny
                 .Commonparameter.Color = LineColor
                 .Commonparameter.Style = cad.DrawStyle
                 .Commonparameter.Width = cad.DrawWidth
            End With
       'Case "����"
       '       With .cad
       '            text(text.ubound).Font.Bold = .FontBold
       '            text(text.ubound).ForeColor = .ForeColor
       '            text(text.ubound).FontItalic = .FontItalic
       '            text(text.ubound).Font.name = .FontName
       '            text(text.ubound).FontSize = .FontSize
       '            text(text.ubound).FontStrikethru = .FontStrikethru
       '            text(text.ubound).FontTransparent = .FontTransparent
       '            text(text.ubound).FontUnderline = .FontUnderline
       '       End With
       Case "��ע"     '��������ɫ������
            Select Case DrawFlag
                   Case 1, 2 '�ӳ���
                        With Tline(UBound(Tline))
                             If Dimension.FirstExtensinonLine And DrawFlag = 1 Then
                                .Commonparameter.Color = Dimension.ExtensioneLineColor
                             ElseIf Dimension.SecondExtensioneLine And DrawFlag = 2 Then
                                .Commonparameter.Color = Dimension.ExtensioneLineColor
                             Else
                                .Commonparameter.Color = cad.BackColor
                             End If
                             .Commonparameter.Style = 0
                             .Commonparameter.Width = 1
                        End With
                   Case 3   '��ע��
                        With Tline(UBound(Tline))
                             .Commonparameter.Color = Dimension.DimensionColor
                             .Commonparameter.Style = 0
                             .Commonparameter.Width = 1
                        End With
                  Case 4 '������ע
                       With Tline(UBound(Tline))
                            If .Style Mod 10 = -2 Or .Style Mod 10 = -9 Then
                                .Commonparameter.Color = Dimension.DimensionColor
                                .Commonparameter.Style = 0
                                .Commonparameter.Width = 1
                            Else
                               If Dimension.SecondExtensioneLine Then
                                  .Commonparameter.Color = Dimension.ExtensioneLineColor
                               Else
                                   .Commonparameter.Color = cad.BackColor
                               End If
                               .Commonparameter.Style = 0
                               .Commonparameter.Width = 1
                            End If
                       End With
            End Select
             
End Select
CurrentOperistFlag = True   '��ǰ�����˲���
End Sub

Public Sub ȷ�����������ֱ��(flag As String)     '
Dim n As Long, i As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

       Select Case flag
              Case "end"
                   Tline(UBound(Tline)).Style = 11  '���ֱ��
                   Redraw
              Case "close"
                    n = UBound(Tline) + 1
                    ReDim Preserve Tline(n)
                    With Tline(n)
                         .X1 = Tline(n - 1).X2  '���ֱ�ߵ����
                         .Y1 = Tline(n - 1).Y2
                         .Style = 11          '���ֱ��
                         i = n - 1
                         While (Tline(i).Style Mod 10 <> 0)
                                Tline(i).Style = 14    '�м�ֱ�߱�Ϊ���
                                i = i - 1
                         Wend
                         .X2 = Tline(i).X1    '���ֱ�ߵ��յ�
                         .Y2 = Tline(i).Y1
                         .Commonparameter.Color = LineColor
                         .Commonparameter.Style = cad.DrawStyle
                         .Commonparameter.Width = cad.DrawWidth
                     End With
                     Redraw
              Case "undo"
                   i = UBound(Tline)
                   While (Tline(i).Style Mod 10 <> 0)
                          i = i - 1
                   Wend
                   ReDim Preserve Tline(i - 1)
                   Redraw
        End Select
End Sub

'��ֱ�߶�
Private Sub VerticalLine(Line1 As Long, x As Single, y As Single, flag As Boolean)
Dim m, s, w, Vx As Single, Vy As Single
With cad
     m = .DrawMode
     s = .DrawStyle
     w = .DrawWidth
End With
     With Tline(Line1)
             cad.DrawMode = vbXorPen
             cad.DrawWidth = .Commonparameter.Width
             cad.DrawStyle = .Commonparameter.Style
             '���ԭͼ
             cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), ShowObjectColor
             VerticalPoint Vx, Vy, x, y, .X1, .Y1, .X2, .Y2
          If flag Then 'ͻ����ʾ
             '��ͼ
             cad.Line (x, y)-(Vx, Vy), ShowObjectColor
             Mouseleftdownx = x
             Mouseleftdowny = y
             Mousepausex = Vx
             Mousepausey = Vy
          End If
     End With
End Sub

'���㵽Բ������
Private Function PointToCircleTanLine(CP As Long, x As Single, y As Single) As Boolean
Dim p1 As point, p2 As point, xx As Single, yy As Single, i
    TiShiLine x, y, vbLeftButton, cad, Viewcolor, False
    With Tline(UBound(Tline))
         i = TanLineToArcPoint(.X1, .Y1, Tcircle(CP), p1, p2)
    End With
    If i Then
       With Tline(UBound(Tline))
            xx = TwoPointDirection(x, y, p1.x, p1.y)
            yy = TwoPointDirection(x, y, p2.x, p2.y)
            If xx < yy Then
              .X2 = p1.x
              .Y2 = p1.y
            Else
              .X2 = p2.x
              .Y2 = p2.y
            End If
            '��ʾֱ��
            cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
            PointToCircleTanLine = True
        End With
    Else
            ReDim Preserve Tline(UBound(Tline) - 1)
            DrawFlag = 1
            PointToCircleTanLine = False
    End If
End Function

'ȡ������
Public Sub MakeUndo(Style As String)
       Select Case Style
              Case "���㵽Բ������", "line"
                   If UBound(Tline) > 0 And Tline(UBound(Tline)).Style = 0 Then
                      TiShiLine 1, 1, vbLeftButton, cad, Viewcolor, False
                      ReDim Preserve Tline(UBound(Tline) - 1)
                      DrawFlag = 1
                      Redraw
                   End If
                   
       End Select
End Sub

Public Sub EditClear(flag As Boolean)
Dim i As Long, j As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If flag Then  'Ϊ��ʱ���,Ϊ��ʱȡ��
       '�������' λ�ò��ܵ���,������ֱ�������ǰ,��Ϊ��Ҫ�޸�ָ��ֱ�ߵ�ָ��
       If FontPoint > 0 Then
          i = FontPoint
          j = UBound(Tfont)
          While (i <= j)
                 If Tfont(i).flag Then
                     For j = i To UBound(Tfont) - 1 '�����������
                         Tfont(j) = Tfont(j + 1)
                         LetFont Tfont(j), text(j), False
                         If Tfont(j).point <> 0 Then '�޸ı�ע�ߵ�ָ��
                            Tline(Tfont(j).point).Style = -j * 10 - 1
                         End If
                     Next j
                     ReDim Preserve Tfont(UBound(Tfont) - 1)
                     j = UBound(Tfont)
                     Unload text(text.UBound)   '����ı������
                 Else
                     i = i + 1
                 End If
          Wend
       End If
       If LinePoint > 0 Then ' λ�ò��ܵ���
          ReDim Preserve Tline(LinePoint - 1)
       End If
       If CirclePoint > 0 Then
          ReDim Preserve Tcircle(CirclePoint - 1)
       End If
End If
       LinePoint = -1
       CirclePoint = -1
       FontPoint = -1
       For i = 1 To UBound(Tfont) '�������
           Tfont(i).flag = 0
       Next i
       
       SelectRectangle.flag = False
       
       NoEnabled_Edit '�༭����Ӧ
       
       Redraw
End Sub

Public Sub EditCut()
       Call snape.EditCut(Tline, Tcircle, Tfont)
End Sub

Public Sub EditCopy()
       Call snape.EditCopy(Tline, Tcircle, Tfont)
End Sub

Public Sub EditPaste()
       Call snape.EditPaste(Tline, Tcircle, Tfont)
End Sub

Public Sub Redraw()  '�ػ�
Dim i, scol As ColorConstants
Dim m As Integer, w As Integer, s As Integer

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

With cad
     m = .DrawMode
     w = .DrawWidth
     s = .DrawStyle
End With

cad.Cls
SSnape.Visible = False '�����׽Ŀ��
'SaveParameter cad  '�������Ͳ���
cad.DrawMode = vbCopyPen
       For i = 1 To UBound(Tline)  '�ػ�ֱ��
           With Tline(i)
                cad.DrawWidth = .Commonparameter.Width
                cad.DrawStyle = .Commonparameter.Style
                cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
           End With
       Next i
                
       For i = 1 To UBound(Tcircle)   ' �ػ����е�Բ,Բ��,����,��Բ
           With Tcircle(i)
                cad.DrawWidth = .Commonparameter.Width
                cad.DrawStyle = .Commonparameter.Style
                If .Start = 0 And .end = 0 And .Aspect = 0 Then
                    cad.Circle (.x0, .y0), .Radius, .Commonparameter.Color
                Else
                    If .Aspect = 0 Then
                       cad.Circle (.x0, .y0), .Radius, .Commonparameter.Color, .Start, .end
                    Else
                       cad.Circle (.x0, .y0), .Radius, .Commonparameter.Color, .Start, .end, .Aspect
                    End If
                End If
           End With
       Next i
       
       SaveFont cad '����ʾ��������
       For i = 1 To UBound(Tfont)
           text(i).BackColor = cad.BackColor
           If Not Tfont(i).flag Then
              text(i).ForeColor = Tfont(i).Font.Color
           End If
           With Tfont(i)
                If .point = 0 Then '��������
                   text(i).left = .x
                   text(i).top = .y
                   text(i).Caption = .text
                Else '��ע����
                   Select Case .Posion '���ֵ�λ��
                          Case 0   '�ڱ�ע������
                               text(i).top = .y - .Height
                               text(i).left = .x - .Width / 2
                          Case 1
                          
                          Case 2 '�ڱ�ע����
                               text(i).top = .y - .Height / 2
                               text(i).left = .x - .Width / 2
                   End Select
                End If
           End With
       Next i
       RedoFont cad
'RedoParameter cad  '�ָ����Ͳ���
With cad
     .DrawMode = m
     .DrawWidth = w
     .DrawStyle = s
End With

scol = ShowObjectColor
ShowObjectColor = cad.BackColor
ShowObject False, True
ShowObjectColor = scol
SelectRectangle.flag = False
ShowObject True, True 'ͻ����ʾ

End Sub


'ͻ����ʾ
Private Sub ShowObject(DrawFlag As Boolean, ColorFlag As Boolean)
Dim i, Color As ColorConstants
Dim m As Integer, w As Integer, s As Integer

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

'drawflagȷ���ʵ�ģʽ
'colorflagȷ����ɫ��showobjectcolor,�����ñ�ɫ
'��Ϊshowobjectcolorɫ,��Ϊ��ɫ
'ͻ����ʾ��ɫΪѡȡ��ɫ��ͼֽ���õ�
With cad
     m = .DrawMode
     w = .DrawWidth
     s = .DrawStyle
End With
'  SaveParameter cad
  If DrawFlag Then
     cad.DrawMode = 7
  Else
     cad.DrawMode = 13
  End If
  
     If LinePoint > 0 Then 'ֱ��
        For i = LinePoint To UBound(Tline)  '�ػ�ֱ��
           With Tline(i)
                cad.DrawWidth = .Commonparameter.Width
                cad.DrawStyle = .Commonparameter.Style
                If ColorFlag Then
                   Color = ShowObjectColor
                Else
                   Color = .Commonparameter.Color
                End If
                cad.Line (.X1, .Y1)-(.X2, .Y2), Color
           End With
           With SelectRectangle
                If Not .flag Then
                    .X1 = MinTwoNum(Tline(i).X1, Tline(i).X2)
                    .X2 = MaxTwoNum(Tline(i).X1, Tline(i).X2)
                    .Y1 = MinTwoNum(Tline(i).Y1, Tline(i).Y2)
                    .Y2 = MaxTwoNum(Tline(i).Y1, Tline(i).Y2)
                    .flag = True
                Else
                    .X1 = MinThreeNum(Tline(i).X1, Tline(i).X2, .X1)
                    .X2 = MaxThreeNum(Tline(i).X1, Tline(i).X2, .X2)
                    .Y1 = MinThreeNum(Tline(i).Y1, Tline(i).Y2, .Y1)
                    .Y2 = MaxThreeNum(Tline(i).Y1, Tline(i).Y2, .Y2)
                    .flag = True
                End If
           End With
       Next i
    End If
    
    If CirclePoint > 0 Then 'Բ,Բ��������Բ
       For i = CirclePoint To UBound(Tcircle) ' �ػ����е�Բ,Բ��,����,��Բ
           With Tcircle(i)
                cad.DrawWidth = .Commonparameter.Width '��������
                cad.DrawStyle = .Commonparameter.Style
                If ColorFlag Then             '��ɫ
                   Color = ShowObjectColor
                Else
                   Color = .Commonparameter.Color
                End If
           End With
                If Tcircle(i).Start = 0 And Tcircle(i).end = 0 And Tcircle(i).Aspect = 0 Then 'Բ
                    cad.Circle (Tcircle(i).x0, Tcircle(i).y0), Tcircle(i).Radius, Color
                    With SelectRectangle
                         If Not .flag Then
                            .X1 = MinTwoNum(Tcircle(i).x0 + Tcircle(i).Radius, Tcircle(i).x0 - Tcircle(i).Radius)
                            .X2 = MaxTwoNum(Tcircle(i).x0 + Tcircle(i).Radius, Tcircle(i).x0 - Tcircle(i).Radius)
                            .Y1 = MinTwoNum(Tcircle(i).y0 + Tcircle(i).Radius, Tcircle(i).y0 - Tcircle(i).Radius)
                            .Y2 = MaxTwoNum(Tcircle(i).y0 + Tcircle(i).Radius, Tcircle(i).y0 - Tcircle(i).Radius)
                            .flag = True
                         Else
                            .X1 = MinThreeNum(Tcircle(i).x0 + Tcircle(i).Radius, Tcircle(i).x0 - Tcircle(i).Radius, .X1)
                            .X2 = MaxThreeNum(Tcircle(i).x0 + Tcircle(i).Radius, Tcircle(i).x0 - Tcircle(i).Radius, .X2)
                            .Y1 = MinThreeNum(Tcircle(i).y0 + Tcircle(i).Radius, Tcircle(i).y0 - Tcircle(i).Radius, .Y1)
                            .Y2 = MaxThreeNum(Tcircle(i).y0 + Tcircle(i).Radius, Tcircle(i).y0 - Tcircle(i).Radius, .Y2)
                            .flag = True
                         End If
                    End With
                Else 'Բ��,����,��Բ
                    Dim Xmax As Single, Ymax As Single, Xmin As Single, Ymin As Single
                    ' �ػ����е�Բ��,����,��Բ
                    With Tcircle(i)
                        If .Aspect = 0 Then  'Բ��,����
                            cad.Circle (.x0, .y0), .Radius, Color, .Start, .end
                            ArcMaxMin Xmax, Ymax, Xmin, Ymin, .x0, .y0, .Radius, .Start, .end
                        Else '��Բ
                           cad.Circle (.x0, .y0), .Radius, Color, .Start, .end, .Aspect
                           EllipseMaxMin Xmax, Xmin, Ymax, Ymin, .x0, .y0, .Radius, .Start, .end, .Aspect
                        End If
                        If Not SelectRectangle.flag Then
                           SelectRectangle.X1 = Xmin
                           SelectRectangle.X2 = Xmax
                           SelectRectangle.Y1 = Ymin
                           SelectRectangle.Y2 = Ymax
                           SelectRectangle.flag = True
                        Else
                           SelectRectangle.X1 = MinTwoNum(Xmin, SelectRectangle.X1)
                           SelectRectangle.X2 = MaxTwoNum(Xmax, SelectRectangle.X2)
                           SelectRectangle.Y1 = MinTwoNum(Ymin, SelectRectangle.Y1)
                           SelectRectangle.Y2 = MaxTwoNum(Ymax, SelectRectangle.Y2)
                           SelectRectangle.flag = True
                        End If
                    End With
                End If
       Next i
    End If
    
    If FontPoint > 0 Then
       For i = FontPoint To UBound(Tfont)
           If ColorFlag Then
              If Tfont(i).flag Then
                 text(i).ForeColor = ShowObjectColor Xor cad.BackColor '��Ϊͻ��ɫΪ��ɫ�뱳��ɫ������
              With SelectRectangle
                   If Not .flag Then
                      .X1 = text(i).left
                      .Y1 = text(i).top
                      .X2 = text(i).left + text(i).Width
                      .Y2 = text(i).top + text(i).Height
                      .flag = True
                   Else
                      .X1 = MinTwoNum(text(i).left, .X1)
                      .Y1 = MinTwoNum(text(i).top, .Y1)
                      .X2 = MaxTwoNum(text(i).left + text(i).Width, .X2)
                      .Y2 = MaxTwoNum(text(i).top + text(i).Height, .Y2)
                      .flag = True
                   End If
              End With
              End If
           Else
              If Tfont(i).flag Then
                 text(i).ForeColor = Tfont(i).Font.Color
              End If
           End If
       Next i
    End If
    showselectrectangle     '��ʾѡȡ����

With cad
      .DrawMode = m
      .DrawWidth = w
      .DrawStyle = s
End With

'RedoParameter cad
End Sub

Private Sub showselectrectangle()
Dim m, s, w, i

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

'With cad
'     m = .DrawMode
'     s = .DrawStyle
'     w = .DrawWidth
'     .DrawWidth = 1
'     .DrawStyle = 2
'     .DrawMode = 7
'End With
    With SelectRectangle '��ʾѡȡ����
         If .flag Then
            SPshow.top = .Y1   '����
            SPshow.left = .X1
            SPshow.Height = .Y2 - .Y1
            SPshow.Width = .X2 - .X1
            SPshow.Visible = True
            SPshow.BorderColor = vbBlue
            '��
            Shape1(0).top = .Y1 - Shape1(0).Height / 2 '���ϵ�
            Shape1(0).left = .X1 - Shape1(0).Width / 2
            Shape1(1).top = .Y1 - Shape1(1).Height / 2 '���е�
            Shape1(1).left = (.X1 + .X2) / 2 - Shape1(1).Width / 2
            Shape1(2).top = .Y1 - Shape1(2).Height / 2 '���ϵ�
            Shape1(2).left = .X2 - Shape1(2).Width / 2
            Shape1(3).top = (.Y1 + .Y2) / 2 - Shape1(3).Height / 2 '���е�
            Shape1(3).left = .X2 - Shape1(3).Width / 2
            Shape1(4).top = .Y2 - Shape1(4).Height / 2 '���µ�
            Shape1(4).left = .X2 - Shape1(4).Width / 2
            Shape1(5).top = .Y2 - Shape1(5).Height / 2 '���е�
            Shape1(5).left = (.X1 + .X2) / 2 - Shape1(5).Width / 2
            Shape1(6).top = .Y2 - Shape1(6).Height / 2 '���µ�
            Shape1(6).left = .X1 - Shape1(6).Width / 2
            Shape1(7).top = (.Y1 + .Y2) / 2 - Shape1(7).Height / 2 '���е�
            Shape1(7).left = .X1 - Shape1(7).Width / 2
            Shape1(8).top = (.Y1 + .Y2) / 2 - Shape1(8).Height / 2 '�м��
            Shape1(8).left = (.X1 + .X2) / 2 - Shape1(8).Width / 2
            For i = 0 To 8
                Shape1(i).Visible = True
            Next i
            
            'cad.Line (.x1, .y1)-(.x2, .y2), ShowObjectColor, B
         Else
            For i = 0 To 8
                Shape1(i).Visible = False
            Next i
            SPshow.Visible = False
            
         End If
    End With
'With cad
'     .DrawWidth = w
'     .DrawStyle = s
'     .DrawMode = m
'End With
End Sub

Public Sub Select_All() 'ȫѡ
Dim i As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

             DrawFlag = 0
             If UBound(Tline) > 0 Then
                LinePoint = 1
             End If
             If UBound(Tcircle) > 0 Then
                CirclePoint = 1
             End If
             For i = 1 To UBound(Tfont)
                 Tfont(i).flag = True
                 FontPoint = 1
             Next i
             Redraw
        'ʹ�༭������Ӧ�¼�
        If LinePoint > 0 Or CirclePoint > 0 Or FontPoint > 0 Then
              Enabled_Edit
        End If

End Sub

Private Sub SelectPointObject(x As Single, y As Single, Shift As Integer, flag As Boolean)  'ѡȡĿ��
Dim i As Long, scol As ColorConstants

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        If flag Then ShowObject False, False
        If Shift = 0 Then   '���ԭѡȡ����Ŀ��
           LinePoint = -1
           CirclePoint = -1
           FontPoint = -1
           For i = 1 To UBound(Tfont)
               Tfont(i).flag = 0
           Next i
        End If
        SelectRectangle.flag = False
        Select_Text x, y, Shift  '����ѡȡ��������ǰ,λ�ò��ܵ���
        Select_Line x, y, Shift
        Select_Circle x, y, Shift
        If flag Then
           scol = ShowObjectColor
           ShowObjectColor = cad.BackColor
           ShowObject False, True
           ShowObjectColor = scol
           ShowObject True, True
        End If
        'ʹ�༭������Ӧ�¼�
        If LinePoint > 0 Or CirclePoint > 0 Or FontPoint > 0 Then
              Enabled_Edit
        End If
End Sub

'ѡȡ����
Private Sub Select_Text(x As Single, y As Single, Shift As Integer)
Dim i As Long, j As Long
        
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

If Shift = vbShiftMask Then '������ĵ�λ���λ����
   If FontPoint < 0 Then
      j = UBound(Tfont)
   Else
      j = FontPoint - 1
   End If
Else
   j = UBound(Tfont)
End If
If Shift = vbCtrlMask Then '�Ӹ�λ���λ����
   If FontPoint < 0 Then
      Exit Sub
   Else
      j = FontPoint
      i = UBound(Tfont)
   End If
Else
    i = 1
End If
    
        While (i <= j And Shift <> vbCtrlMask) Or (i >= j And Shift = vbCtrlMask And FontPoint > 0)
            With Tfont(i)
                 If .point = 0 And .x <= x And .x + .Width >= x And .y <= y And .y + .Height >= y And .point = 0 Then
                       Tfont(i).flag = 1 '��Ϊѡ��
                       Swape_Text i, j, Shift
                 ElseIf .x - .Width / 2 <= x And .x + .Width / 2 >= x And .y - .Height / 2 <= y And .y + .Height / 2 >= y And .point <> 0 Then
                            Tfont(i).flag = 1 '��Ϊѡ��
                            Swape_Text i, j, Shift
                     ElseIf Shift = vbCtrlMask Then
                            i = i - 1
                         Else
                            i = i + 1
                 End If
            End With
        Wend
End Sub

'��������
Private Sub Swape_Text(i As Long, j As Long, Shift As Integer)
Dim TF As TextType, TT As Label, s As Integer

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Shift = vbCtrlMask Then '�Ӹ�λ���λ����
   Tfont(i).flag = False '��Ϊδѡ��
   If j <> i Then
      TF = Tfont(j)
      Tfont(j) = Tfont(i)
      Tfont(i) = TF
   End If
   If FontPoint < UBound(Tfont) Then '��ָ�븳ֵ
      FontPoint = FontPoint + 1
   Else
      FontPoint = -1
   End If
Else '�ӵ�λ���λ����
       TF = Tfont(j)
       Tfont(j) = Tfont(i)
       Tfont(i) = TF
       FontPoint = j '��ָ�븳ֵ
End If
       LetFont Tfont(i), text(i), False ' ������ؼ���ֵ
       LetFont Tfont(j), text(j), False
       
       If Tfont(i).point <> 0 Then '�޸ı�ע��ָ��
          s = Tline(Tfont(i).point).Style Mod 10
          Tline(Tfont(i).point).Style = s - i * 10
       End If
       If Tfont(j).point <> 0 Then  '�޸ı�ע��ָ��
          s = Tline(Tfont(j).point).Style Mod 10
          Tline(Tfont(j).point).Style = s - j * 10
       End If
If Shift = vbCtrlMask Then '�޸ıȽϵ�λ��
   j = j + 1 '�˳�ѡ��,ָ��������
Else
   j = j - 1 '����ѡ��,ָ��������
End If
End Sub

'ѡȡ����
Private Sub Select_Line(x As Single, y As Single, Shift As Integer)
Dim i As Long, Lp As Long
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
If Shift = vbShiftMask Then '�ӵ�λ���λ����,����ѡ��Ŀ����
   If LinePoint < 0 Then
      Lp = UBound(Tline)
   Else
      Lp = LinePoint - 1
   End If
Else
   Lp = UBound(Tline)
End If
If Shift = vbCtrlMask Then '�Ӹ�λ���λ����,ȥ��ѡ�е�Ŀ��
   If LinePoint < 0 Then
      Exit Sub
   Else
      Lp = LinePoint
      i = UBound(Tline)
   End If
Else
    i = 1
End If

    While (i <= Lp And Shift <> vbCtrlMask) Or (i >= Lp And Shift = vbCtrlMask And Lp > 0)
          With Tline(i)
               If (.Style Mod 10 = -1) Or (.Style Mod 10 = -2) Then
                  '�������ֿ��Ǳ�ע�����.ɾ��
                  If (Tfont(Int(Abs(.Style / 10))).flag And Shift <> vbCtrlMask) Or (Not Tfont(Int(Abs(.Style / 10))).flag And Shift = vbCtrlMask) Then
                        i = Swape_Line(i, Lp, Shift)
                  ElseIf Select_Line_Ok(x, y, .X1, .Y1, .X2, .Y2, SelectField) Then
                        i = Swape_Line(i, Lp, Shift)
                      Else
                        If Shift = vbCtrlMask Then
                           i = i - 1
                        Else
                           i = i + 1
                        End If
                  End If
               ElseIf Select_Line_Ok(x, y, .X1, .Y1, .X2, .Y2, SelectField) Then
                        i = Swape_Line(i, Lp, Shift)
                   Else
                        If Shift = vbCtrlMask Then
                           i = i - 1
                        Else
                           i = i + 1
                        End If
               End If
          End With
    Wend
    
    '���ı�ע�ߵ�����ָ��
    If LinePoint > 0 Then
       For i = 1 To UBound(Tline)
           With Tline(i)
                If (.Style Mod 10 = -1) Or (.Style Mod 10 = -2) Then
                   Tfont(Int(Abs(.Style) / 10)).point = i 'ûѡ�еı�ע����
                   Tfont(Int(Abs(.Style) / 10)).flag = False
                   If i >= LinePoint Then
                      Tfont(Int(Abs(.Style) / 10)).flag = True 'ѡ�еı�ע����
                      If FontPoint > 1 Then
                         Lp = FontPoint - 1
                      Else
                         Lp = UBound(Tfont)
                      End If
                         If Int(Abs(.Style) / 10) < FontPoint Or FontPoint < 0 Then
                            Swape_Text Int(Abs(.Style) / 10), Lp, Shift
                         End If
                   End If
                End If
           End With
       Next i
    End If
End Sub

'����ֱ��
Private Function Swape_Line(i As Long, Lp As Long, Shift As Integer) As Long    '��������
Dim m As Long, n As Long, Style As Long, j As Long, k As Long
Dim SwapD As linetype

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

    Style = Int(Tline(i).Style / 10) Mod 10
    
    Select Case Style
           Case 0  'ֱ��
                m = i: n = i
           Case 1 '������
                Style = Tline(i).Style Mod 10
                m = i: n = i
                Select Case Style '��λ��,���MMAIN�еĶ���
                       Case 2, 4
                            While (Tline(m).Style Mod 10 <> 0)
                                   m = m - 1
                            Wend
                            While (Tline(n).Style Mod 10 <> 1)
                                   n = n + 1
                            Wend
                       Case 0
                            While (Tline(n).Style Mod 10 <> 1)
                                   n = n + 1
                            Wend
                       Case 1
                            While (Tline(m).Style Mod 10 <> 0)
                                   m = m - 1
                            Wend
                 End Select
           Case Is < 0 '��ע��
                m = i: n = i
                While (Tline(m).Style Mod 10 <> -1)
                       m = m - 1
                Wend
                While (Tline(n).Style Mod 10 <> -9)
                      n = n + 1
                Wend
           Case Else
                j = Tline(i).Style
                m = i - (j Mod 10) + 1
                n = Int(j / 10) - (j Mod 10) + i
    End Select
    
    If Shift = vbCtrlMask Then '�Ӹ�λ���λ����,��ѡ�е�Ŀ���г�ȥ
       If Lp < m Then
          For k = m To n
              Lp = Lp + 1
              For j = k To Lp Step -1
                 SwapD = Tline(j)
                 Tline(j) = Tline(j - 1)
                 Tline(j - 1) = SwapD
              Next j
          Next k
       Else
          Lp = n + 1
       End If
       If Lp < UBound(Tline) Then
          LinePoint = Lp
       Else
          LinePoint = -1
       End If
       Swape_Line = n
    Else ' �ӵ�λ���λ����,���뵽ѡ�е�Ŀ����ȥ
       If Lp <> n Then
          For k = n To m Step -1
              Lp = Lp - 1 '�Ѻ��������ǰ��һλ
              For j = k To Lp
                 SwapD = Tline(j)
                 Tline(j) = Tline(j + 1)
                 Tline(j + 1) = SwapD
              Next j
          Next k
       Else
          Lp = Lp - (n - m) - 1
       End If
    
       LinePoint = Lp + 1
       
       Swape_Line = m
    
    End If
    
End Function

'ѡȡԲ��
Private Sub Select_Circle(x As Single, y As Single, Shift As Integer)
Dim i As Long, n As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Shift = vbShiftMask Then '�ӵ�λ���λ����
   If CirclePoint < 0 Then
      n = UBound(Tcircle)
   Else
      n = CirclePoint - 1
   End If
Else
   n = UBound(Tcircle)
End If
If Shift = vbCtrlMask Then '�Ӹ�λ���λ����
   If CirclePoint < 0 Then
      Exit Sub
   Else
      i = UBound(Tcircle)
      n = CirclePoint
   End If
Else
    i = 1
End If
    While (i <= n And Shift <> vbCtrlMask) Or (i >= n And Shift = vbCtrlMask And n > 0)
          With Tcircle(i)
               If .Start = 0 And .end = 0 And .Aspect = 0 Then 'ѡȡԲ
                  If Select_Circle_Ok(x, y, .x0, .y0, .Radius, SelectField) Then
                         Swape_Circle i, n, Shift
                  Else
                     If Shift = vbCtrlMask Then
                        i = i - 1
                     Else
                        i = i + 1
                     End If
                  End If
               Else 'ѡȡԲ��,����,��Բ
                  If Select_Arc_Ok(x, y, .x0, .y0, .Radius, .Start, .end, .Aspect, SelectField) Then
                        Swape_Circle i, n, Shift
                  Else
                        If Shift = vbCtrlMask Then
                           i = i - 1
                        Else
                           i = i + 1
                        End If
                  End If
              End If
          End With
    Wend
End Sub

'����Բ��
Private Sub Swape_Circle(i, j, Shift As Integer)
Dim jh As CircleType

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Shift = vbCtrlMask Then '�Ӹ�λ���λ����
   If i <> j Then
       jh = Tcircle(j)
       Tcircle(j) = Tcircle(i)
       Tcircle(i) = jh
   End If
   j = j + 1
   If CirclePoint < UBound(Tcircle) Then
      CirclePoint = CirclePoint + 1
   Else
      CirclePoint = -1
   End If
Else '�Ӹ�λ���λ����
       jh = Tcircle(j)
       Tcircle(j) = Tcircle(i)
       Tcircle(i) = jh
       CirclePoint = j
       j = j - 1
End If
End Sub
        
'�ƶ�
Private Sub EditMove(x As Single, y As Single, Button As Integer)
Dim i As Long, xx As Single, yy As Single

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Button = vbLeftButton Then
   '���ԭͼ��
   ShowObject True, True
   'SaveParameter cad
   'cad.DrawMode = 7
   'ͼ�α任
   xx = x - Mousepausex
   yy = y - Mousepausey
   If LinePoint > 0 Then
      For i = LinePoint To UBound(Tline)
          With Tline(i)
              .X1 = .X1 + xx
              .Y1 = .Y1 + yy
              .X2 = .X2 + xx
              .Y2 = .Y2 + yy
          End With
      Next i
   End If
   If CirclePoint > 0 Then
   For i = CirclePoint To UBound(Tcircle)
       With Tcircle(i)
            .x0 = .x0 + xx
            .y0 = .y0 + yy
       End With
   Next i
   End If
   
   If FontPoint > 0 Then '��������
      For i = FontPoint To UBound(Tfont)
          With text(i)
               If Tfont(i).flag Then
                  Tfont(i).x = Tfont(i).x + xx
                  Tfont(i).y = Tfont(i).y + yy
                  If Tfont(i).point <> 0 Then
                     Text_Position Tfont(i), text(i)
                  Else
                     .left = Tfont(i).x
                     .top = Tfont(i).y
                  End If
               End If
          End With
      Next i
   End If
   
   SelectRectangle.flag = False
   
   'RedoParameter cad  '�ָ�����
   ShowObject True, True  '��ʾ�任���ͼ��
   Mousepausex = x
   Mousepausey = y
End If
End Sub

Private Sub EditNew()  '������Ԫ��,�ٵ����ƶ�����
Dim i As Long, n As Long, j As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        '���ֱ��������ǰ
        '������������
        If fMainForm.TCurrentOperist.text <> "��ת" Then
           If FontPoint > 0 Then
              n = UBound(Tfont)
              ReDim Preserve Tfont(n + n - FontPoint + 1)
              For i = n + 1 To n + n - FontPoint + 1 '�����µ����ֱ���ؼ�
                  Load text(i)
                  text(i).Visible = True
              Next i
              For i = 1 To n - FontPoint + 1
                  Tfont(n + i) = Tfont(i + FontPoint - 1)
                  LetFont Tfont(n + i), text(n + i), False '������
              Next i
              FontPoint = n + 1
            End If
        End If
        
        If LinePoint > 0 Then
           n = UBound(Tline)
           ReDim Preserve Tline(n + n - LinePoint + 1)
           For i = 1 To n - LinePoint + 1
               Tline(n + i) = Tline(i + LinePoint - 1)
               '�޸ı�ע��ָ�����ֵ�ָ�������ָ���ע�ߵ�ָ��
               If fMainForm.TCurrentOperist.text <> "��ת" Then
                  If (Tline(n + i).Style Mod 10 = -1) Or (Tline(n + i).Style Mod 10 = -2) Then
                     j = UBound(Tfont) - FontPoint + Int(Abs(Tline(n + i).Style / 10)) + 1
                     Tfont(j).point = n + i
                     Tline(n + i).Style = -10 * j + (Tline(n + i).Style Mod 10)
                  End If
               End If
           Next i
           LinePoint = n + 1
        End If
        
        If CirclePoint > 0 Then
           n = UBound(Tcircle)
           ReDim Preserve Tcircle(n + n - CirclePoint + 1)
           For i = 1 To n - CirclePoint + 1
               Tcircle(n + i) = Tcircle(CirclePoint + i - 1)
           Next i
           CirclePoint = n + 1
        End If
End Sub

Private Sub EditRound(x As Single, y As Single, Button As Integer, flag As Boolean) '��ת
Dim xx As Single, yy As Single, i As Long, a As Double
Dim Lp As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Button = vbLeftButton Then
   xx = x - Mouseleftdownx
   yy = y - Mouseleftdowny
   a = 2 * Pi - Angle(xx, yy)
   
   If flag Then    'ȷ����ת���ͼ��
      ShowObject True, True '���ԭͼ��
      If LinePoint > 0 Then   'ֱ��
         Lp = LinePoint - (UBound(Tline) - LinePoint + 1)
         For i = 0 To UBound(Tline) - LinePoint
             With Tline(i + Lp)
                  RoundPoint .X1, .Y1, .X1, .Y1, Mouseleftdownx, Mouseleftdowny, a
                  RoundPoint .X2, .Y2, .X2, .Y2, Mouseleftdownx, Mouseleftdowny, a
             End With
         Next i
         ReDim Preserve Tline(LinePoint - 1)
         LinePoint = Lp
      End If
      If CirclePoint > 0 Then
         Lp = CirclePoint - (UBound(Tcircle) - CirclePoint + 1)
         For i = 0 To UBound(Tcircle) - CirclePoint
             With Tcircle(i + Lp)
                  If .Start = 0 And .end = 0 And .Aspect = 0 Then 'Բ
                     RoundPoint .x0, .y0, .x0, .y0, Mouseleftdownx, Mouseleftdowny, a
                  Else '��Բ��,����,��Բ
                     RoundPoint .x0, .y0, .x0, .y0, Mouseleftdownx, Mouseleftdowny, a
                     If .Aspect = 0 Then 'Բ��,����
                        .Start = AngleroundPoint(.Start, a)
                        .end = AngleroundPoint(.end, a)
                     Else '��Բ
                  
                     End If
                  End If
             End With
         Next i
         ReDim Preserve Tcircle(CirclePoint - 1)
         CirclePoint = Lp
      End If
      
      If FontPoint > 0 Then   '����
         For i = FontPoint To UBound(Tfont)
             If Tfont(i).flag Then
                With Tfont(i)
                     RoundPoint .x, .y, .x, .y, Mouseleftdownx, Mouseleftdowny, a
                     If Tfont(i).point <> 0 Then
                        Text_Position Tfont(i), text(i)
                     Else
                        text(i).left = .x
                        text(i).top = .y
                     End If
                End With
             End If
         Next i
      End If
      
      SelectRectangle.flag = False
      
      ShowObject True, True
   Else   '�ο�ͼ��
      ShowObject True, True '���ԭͼ��
      If LinePoint > 0 Then 'ֱ��
         Lp = LinePoint - (UBound(Tline) - LinePoint + 1)
         For i = 0 To UBound(Tline) - LinePoint
             With Tline(i + LinePoint)
                  RoundPoint .X1, .Y1, Tline(Lp + i).X1, Tline(Lp + i).Y1, Mouseleftdownx, Mouseleftdowny, a
                  RoundPoint .X2, .Y2, Tline(Lp + i).X2, Tline(Lp + i).Y2, Mouseleftdownx, Mouseleftdowny, a
             End With
         Next i
      End If
      If CirclePoint > 0 Then
         Lp = CirclePoint - (UBound(Tcircle) - CirclePoint + 1)
         For i = 0 To UBound(Tcircle) - CirclePoint
             With Tcircle(i + CirclePoint)
                  If .Start = 0 And .end = 0 And .Aspect = 0 Then 'Բ
                     RoundPoint .x0, .y0, Tcircle(Lp + i).x0, Tcircle(i + Lp).y0, Mouseleftdownx, Mouseleftdowny, a
                  Else '��Բ��,����,��Բ
                     RoundPoint .x0, .y0, Tcircle(Lp + i).x0, Tcircle(Lp + i).y0, Mouseleftdownx, Mouseleftdowny, a
                     If .Aspect = 0 Then  'Բ��,����
                        .Start = AngleroundPoint(.Start, a)
                        .end = AngleroundPoint(.end, a)
                     Else '��Բ
                     
                     End If
                  End If
             End With
         Next i
      End If
            
      If FontPoint > 0 Then
         For i = FontPoint To UBound(Tfont)
             With Tfont(i)
                  RoundPoint xx, yy, .x, .y, Mouseleftdownx, Mouseleftdowny, a
                  If Tfont(i).point <> 0 Then
                     'Text_Position Tfont(i), text(i)
                    Select Case Dimension.Position
                           Case 0
                                text(i).left = xx - Tfont(i).Width / 2
                                text(i).top = yy - Tfont(i).Height / 2
                           Case 1
              
                           Case 2
                                text(i).left = xx - Tfont(i).Width / 2
                                text(i).top = yy - Tfont(i).Height
                    End Select

                  Else
                     text(i + Lp).left = xx
                     text(i + Lp).top = yy
                  End If
              End With
          Next i
      End If
       
      SelectRectangle.flag = False
      
      ShowObject True, True
   End If
   
End If
End Sub

Private Sub EditMirror(x As Single, y As Single, Button As Integer, flag As Boolean)  ' "����"
Dim i As Long, xx As Single, yy As Single, a As Double
Dim scol As ColorConstants

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If flag Then 'ȷ��������ͼ��
   'ShowObject True
   SaveParameter cad  '����ο�ֱ��
   cad.DrawMode = 7
   cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), ShowObjectColor
   RedoParameter cad
   If fMainForm.TCurrentOperist.text = "������ԭͼ" Then
      ShowObject False, False
      EditNew
   Else
      scol = ShowObjectColor
      ShowObjectColor = cad.BackColor
      ShowObject False, True
      ShowObjectColor = scol
   End If
   If LinePoint > 0 Then
      For i = LinePoint To UBound(Tline)
          With Tline(i)
               Mirror xx, yy, .X1, .Y1, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey
               .X1 = xx
               .Y1 = yy
               Mirror xx, yy, .X2, .Y2, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey
               .X2 = xx
               .Y2 = yy
          End With
      Next i
   End If
   If CirclePoint > 0 Then
      For i = CirclePoint To UBound(Tcircle)
          With Tcircle(i)
               If .Start = 0 And .end = 0 And .Aspect = 0 Then
                   Mirror xx, yy, .x0, .y0, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey
                   .x0 = xx
                   .y0 = yy
               Else '��Բ��,����,��Բ
                    If .Aspect = 0 Then
                       Mirror xx, yy, .x0, .y0, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey
                       .x0 = xx
                       .y0 = yy
                       xx = Sgn(.Start)
                       yy = Sgn(.end)
                       a = xx * AngleMirror(Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey, Abs(.Start))
                      .Start = yy * AngleMirror(Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey, Abs(.end))
                      .end = a
                    Else
                    
                    End If
               End If
          End With
      Next i
   End If
   
   If FontPoint > 0 Then
      For i = FontPoint To UBound(Tfont)
          With Tfont(i)
               Mirror xx, yy, .x, .y, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey
               .x = xx
               .y = yy
               If .flag Then
                  Text_Position Tfont(i), text(i)
               Else
                  text(i).left = xx
                  text(i).top = yy
               End If
           End With
      Next i
   End If
   
   SelectRectangle.flag = False
   
   ShowObject True, True
Else   '�ο�ͼ��
   SingleLine Button, x, y, ShowObjectColor, cad
End If
Mousepausex = x
Mousepausey = y
End Sub

Public Sub EditArray() '����
Dim row As Long, col As Long, rowd As Long, cold As Long, a As Double
Dim i As Long, Lp As Long, CP As Long, j As Long
Dim Fp As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        With FrmArray
             If .Option1.Value Then  '��������
                row = Val(.Text1.text)
                col = Val(.Text2.text)
                rowd = Val(.Text3.text)
                cold = Val(.Text4.text)
                Lp = LinePoint
                CP = CirclePoint
                Fp = FontPoint
                For i = 1 To row - 1
                    EditNew
                    EditMove Mousepausex + rowd, Mousepausey, vbLeftButton
                Next i
                LinePoint = Lp
                CirclePoint = CP
                FontPoint = Fp
                For i = 1 To col - 1
                    EditNew
                    EditMove Mousepausex, Mousepausey + cold, vbLeftButton
                Next i
                CirclePoint = CP
                LinePoint = Lp
                FontPoint = Fp
                ShowObject False, False
             End If
             If .Option2.Value Then 'Բ������
                 row = Val(.Text2.text)
                 a = -AngleToArc(Val(.Text4.text))
                 Lp = LinePoint
                 CP = CirclePoint
                 Fp = FontPoint
                 For j = 1 To row - 1
                     EditNew
                     
                     If LinePoint > 0 Then   'ֱ��
                     For i = LinePoint To UBound(Tline)
                         With Tline(i)
                              RoundPoint .X1, .Y1, .X1, .Y1, Mouseleftdownx, Mouseleftdowny, a
                              RoundPoint .X2, .Y2, .X2, .Y2, Mouseleftdownx, Mouseleftdowny, a
                         End With
                     Next i
                     End If
                     If CirclePoint > 0 Then
                     For i = CirclePoint To UBound(Tcircle)
                        With Tcircle(i)
                             If .Start = 0 And .end = 0 And .Aspect = 0 Then
                                RoundPoint .x0, .y0, .x0, .y0, Mouseleftdownx, Mouseleftdowny, a
                             Else '��Բ,Բ��,����,��Բ
                             
                             End If
                        End With
                     Next i
                     End If
                                 
                     If FontPoint > 0 Then '����
                        For i = FontPoint To UBound(Tfont)
                            With Tfont(i)
                                 RoundPoint .x, .y, .x, .y, Mouseleftdownx, Mouseleftdowny, a
                                 If .point <> 0 Then '��ע����
                                    Text_Position Tfont(i), text(i)
                                 Else '��������
                                    text(i).left = .x
                                    text(i).top = .y
                                 End If
                            End With
                        Next i
                     End If
                  Next j
                  LinePoint = Lp
                  CirclePoint = CP
                  FontPoint = Fp
                  ShowObject False, False
            End If
        End With
End Sub

'�����任
Private Sub EditRatioChange(x As Single, y As Single, Button As Integer, Color As ColorConstants, object As Object, flag As Boolean)
Dim xb As Single, yb As Single, i As Long, n As Long
Dim SColor As ColorConstants

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Button = vbLeftButton Then
   If flag Then
      SColor = ShowObjectColor
      ShowObjectColor = object.BackColor
      ShowObject False, True  '���ԭͼ��
      ShowObjectColor = SColor '�ָ�ԭ��ʾɫ
      With SelectRectangle
           If .X1 <> .X2 And .Y1 <> .Y2 Then
               xb = (Mousepausex - Mouseleftdownx) / (.X2 - .X1)
               yb = (Mousepausey - Mouseleftdowny) / (.Y2 - .Y1)
           End If
      End With
      If LinePoint > 0 Then
         For i = LinePoint To UBound(Tline)
             With Tline(i)
                  Select Case DrawFlag
                         Case 4, 5 'ˮƽ�ұ�����,���½�����
                              RatioChange .X1, .Y1, Mouseleftdownx, Mouseleftdowny, xb, yb
                              RatioChange .X2, .Y2, Mouseleftdownx, Mouseleftdowny, xb, yb
                         Case 8    'ˮƽ�������
                              RatioChange .X1, .Y1, Mousepausex, Mousepausey, xb, yb
                              RatioChange .X2, .Y2, Mousepausex, Mousepausey, xb, yb
                         Case 2, 1  '��ֱ�ϱ�����,���Ͻ�����
                              RatioChange .X1, .Y1, Mousepausex, Mousepausey, xb, yb
                              RatioChange .X2, .Y2, Mousepausex, Mousepausey, xb, yb
                         Case 6  '�±�����
                              RatioChange .X1, .Y1, Mouseleftdownx, Mouseleftdowny, xb, yb
                              RatioChange .X2, .Y2, Mouseleftdownx, Mouseleftdowny, xb, yb
                         Case 3 '���Ͻ�
                              RatioChange .X1, .Y1, Mouseleftdownx, Mousepausey, xb, yb
                              RatioChange .X2, .Y2, Mouseleftdownx, Mousepausey, xb, yb
                         Case 7  '���½�����
                              RatioChange .X1, .Y1, Mousepausex, Mouseleftdowny, xb, yb
                              RatioChange .X2, .Y2, Mousepausex, Mouseleftdowny, xb, yb
                  End Select
             End With
         Next i
      End If
      'Բ
      If CirclePoint > 0 Then
         For i = CirclePoint To UBound(Tcircle)
             With Tcircle(i) ',Բ��,����,��Բ
                  Select Case DrawFlag
                         Case 4, 5 'ˮƽ�ұ�����,���½�����
                              RatioChange .x0, .y0, Mouseleftdownx, Mouseleftdowny, xb, yb
                              RatioChangeArc .Radius, .Start, .end, .Aspect, xb, yb
                         Case 8    'ˮƽ�������
                              RatioChange .x0, .y0, Mousepausex, Mousepausey, xb, yb
                              RatioChangeArc .Radius, .Start, .end, .Aspect, xb, yb
                         Case 2, 1  '��ֱ�ϱ�����,���Ͻ�����
                              RatioChange .x0, .y0, Mousepausex, Mousepausey, xb, yb
                              RatioChangeArc .Radius, .Start, .end, .Aspect, xb, yb
                         Case 6  '�±�����
                              RatioChange .x0, .y0, Mouseleftdownx, Mouseleftdowny, xb, yb
                              RatioChangeArc .Radius, .Start, .end, .Aspect, xb, yb
                         Case 3 '���Ͻ�
                              RatioChange .x0, .y0, Mouseleftdownx, Mousepausey, xb, yb
                              RatioChangeArc .Radius, .Start, .end, .Aspect, xb, yb
                         Case 7  '���½�����
                              RatioChange .x0, .y0, Mousepausex, Mouseleftdowny, xb, yb
                              RatioChangeArc .Radius, .Start, .end, .Aspect, xb, yb
                  End Select
             End With
         Next i
         
      End If
            
      SelectRectangle.flag = False
      TiShiSelectRectangle x, y, Button, Color, False, object
      ShowObject True, True
   Else  '�ο�ͼ��
       If SelectRectangle.flag Then
          SelectRectangle.flag = False
          showselectrectangle
       End If
       Select Case DrawFlag
              Case 4  'ˮƽ�ұ�����
                   TiShiSelectRectangle x, SelectRectangle.Y2, Button, Color, True, object
              Case 8 'ˮƽ�������
                   TiShiSelectRectangle x, x, Button, Color, False, object
                   Mouseleftdownx = x
                   TiShiSelectRectangle x, y, Button, Color, False, object
              Case 2 ''��ֱ�ϱ�����
                   TiShiSelectRectangle x, y, Button, Color, False, object
                   Mouseleftdowny = y
                   TiShiSelectRectangle x, y, Button, Color, False, object
              Case 6  '��ֱ�±�����
                   TiShiSelectRectangle SelectRectangle.X2, y, Button, Color, True, object
              Case 3 '���Ͻ�����
                   TiShiSelectRectangle x, y, Button, Color, False, object
                   Mousepausex = x
                   Mouseleftdowny = y
                   TiShiSelectRectangle x, y, Button, Color, False, object
              Case 5 '���½�����
                   TiShiSelectRectangle x, y, Button, Color, True, object
              Case 1 '���Ͻ�����
                   TiShiSelectRectangle x, y, Button, Color, False, object
                   Mouseleftdownx = x
                   Mouseleftdowny = y
                   TiShiSelectRectangle x, y, Button, Color, False, object
              Case 7 '���½�����
                   TiShiSelectRectangle x, y, Button, Color, False, object
                   Mouseleftdownx = x
                   Mousepausey = y
                   TiShiSelectRectangle x, y, Button, Color, False, object
                   
       End Select
   End If
End If
End Sub

Public Sub MouseChange(Button As Integer, x As Single, y As Single, Shift As Integer) '���仯,�ڱ����任���Զ�ʵ��
'cad.tag�б�������Ƿ����仯
Dim i As Integer

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

If Button <> vbLeftButton Then
  If Shift = 0 Then  '��Shift��Ctrl��������ʱ,��겻�����仯
   If DrawFlag = 0 Then 'drawflag�д洢���ı仯,��һ��Ҫ��ʲô
      If SelectRectangle.flag Then
         For i = 0 To 8  '�����任
             If (y - Shape1.Item(i).top) >= 0 And (y - Shape1.Item(i).top) < Shape1.Item(i).Width And (x - Shape1.Item(i).left) >= 0 And (x - Shape1.Item(i).left) < Shape1.Item(i).Height Then
                MouseChange_OK i, Me
                cad.Tag = 1
                Exit Sub
             End If
         Next i
         '�ƶ�
         'If x > SelectRectangle.X1 And x < SelectRectangle.X2 And y > SelectRectangle.Y1 And y < SelectRectangle.Y2 Then
         '   MouseChange_OK 8, Me
         '   cad.Tag = 1
         '   Exit Sub
         'End If
      End If
   End If
 End If
   If Val(cad.Tag) Then
       MouseChange_Undo Me
       cad.Tag = 0
   End If
End If
End Sub

'ѡȡ�ж�Ŀ��
Private Sub EditBreakSelect(x As Single, y As Single, Shift As Integer)
Dim Rl As Single, Ra As Single, m As Long, n As Long, i As Long
Dim r As Single

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

r = -1: m = -1: n = -1
        SelectPointObject x, y, Shift, False 'ѡȡĿ��
        
        If LinePoint > 0 Then
           For i = LinePoint To UBound(Tline)
               With Tline(i)
                    If r < 0 And .Style >= 0 Then '��ע�߲����ж�
                       m = i
                       r = PointToLineDirection(x, y, .X1, .Y1, .X2, .Y2)
                    Else
                       Rl = PointToLineDirection(x, y, .X1, .Y1, .X2, .Y2)
                       If r > Rl And .Style >= 0 Then
                          m = i
                          r = Rl
                       End If
                    End If
               End With
          Next i
       End If
                    
       If CirclePoint > 0 Then
          If r < 0 Then
             With Tcircle(CirclePoint)
                  If .Aspect = 0 Then 'Բ,Բ��,����
                      r = Abs(TwoPointDirection(x, y, .x0, .y0) - .Radius)
                      n = CirclePoint
                  Else '��Բ
             
                  End If
             End With
             Rl = CirclePoint + 1
          Else
             Rl = CirclePoint
          End If
          For i = Rl To UBound(Tcircle)
              With Tcircle(i)
                   Ra = Abs(TwoPointDirection(x, y, .x0, .y0) - .Radius)
                   If r > Ra Then
                      n = i
                      r = Ra
                   End If
              End With
          Next i
       End If
       
       
       If n > 0 Then
          LinePoint = -1
          CirclePoint = n
          Swape_Circle n, UBound(Tcircle), Shift
       Else
          CirclePoint = -1
          LinePoint = m
       End If
       
       'ͻ����ʾ
       EditBreakShow True
End Sub

Private Sub EditBreakShow(flag As Boolean) '�ж�
'ͻ����ʾ
Dim m, w As Single, s

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

With cad
     m = .DrawMode
     w = .DrawWidth
     s = .DrawStyle
End With
       'SaveParameter cad '�������
       If CirclePoint > 0 Then
          With Tcircle(CirclePoint)
               cad.DrawMode = 7
               cad.DrawWidth = .Commonparameter.Width
               cad.DrawStyle = .Commonparameter.Style
               If .Aspect = 0 And .Start = 0 And .end = 0 Then  'Բ
                   cad.Circle (.x0, .y0), .Radius, ShowObjectColor
               Else
                  If .Aspect = 0 Then 'Բ��,����
                     cad.Circle (.x0, .y0), .Radius, ShowObjectColor, .Start, .end
                     If Not flag Then
                        If CirclePoint <> UBound(Tcircle) Then 'Բ�ж�ΪԲ��ʱ
                           cad.DrawMode = vbCopyPen
                           cad.Circle (Tcircle(UBound(Tcircle)).x0, Tcircle(UBound(Tcircle)).y0), Tcircle(UBound(Tcircle)).Radius, Tcircle(UBound(Tcircle)).Commonparameter.Color, Tcircle(UBound(Tcircle)).Start, Tcircle(UBound(Tcircle)).end
                        End If
                     End If
                  Else
                     cad.Circle (.x0, .y0), .Radius, ShowObjectColor, .Start, .end, .Aspect
                     If Not flag Then
                        cad.Circle (Tcircle(UBound(Tcircle)).x0, Tcircle(UBound(Tcircle)).y0), Tcircle(UBound(Tcircle)).Radius, ShowObjectColor, Tcircle(UBound(Tcircle)).Start, Tcircle(UBound(Tcircle)).end, Tcircle(UBound(Tcircle)).Aspect
                     End If
                  End If
               End If
           End With
       End If
       If LinePoint > 0 Then
           With Tline(LinePoint)  'ͻ����ʾ
               cad.DrawMode = 7
               cad.DrawWidth = .Commonparameter.Width
               cad.DrawStyle = .Commonparameter.Style
               cad.Line (.X1, .Y1)-(.X2, .Y2), ShowObjectColor
               If Not flag Then
                  cad.Line (Tline(UBound(Tline)).X1, Tline(UBound(Tline)).Y1)-(Tline(UBound(Tline)).X2, Tline(UBound(Tline)).Y2), ShowObjectColor
               End If
          End With
       End If
With cad
     .DrawMode = m
     .DrawWidth = w
     .DrawStyle = s
End With
      'RedoParameter cad '�ָ�����
End Sub

Private Sub EditBreak(ByVal x As Single, ByVal y As Single, flag As Boolean) '�ж�
Dim Color As ColorConstants, i As Boolean
Dim Vx As Single, Vy As Single
Dim m As Integer, w As Single, s

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Color = ShowObjectColor
'SaveParameter cad
With cad
      m = .DrawMode
      w = .DrawWidth
      s = .DrawStyle
     .DrawMode = vbXorPen
     .DrawWidth = 1
     .DrawStyle = 0
End With
If LinePoint > 0 Then
   If PointToLineVerticalPoint(Vx, Vy, x, y, Tline(LinePoint).X1, Tline(LinePoint).Y1, Tline(LinePoint).X2, Tline(LinePoint).Y2) Then
          cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
      If flag Then '
         cad.Line (x, y)-(Vx, Vy), Color
         Mouseleftdownx = x
         Mouseleftdowny = y
         Mousepausex = Vx
         Mousepausey = Vy
      End If
   End If
End If
If CirclePoint > 0 Then
   Dim a As Double
   With Tcircle(CirclePoint)
        a = Angle(x - .x0, y - .y0)
        If (Abs(.Start) < Abs(.end) And Abs(.Start) < a And Abs(.end) > a) Or ((Abs(.Start) = 0 And Abs(.end) = 0) Or Abs(.end) < Abs(.Start) And ((a > Abs(.Start) And a < 2 * Pi) Or (a > 0 And a < Abs(.end)))) Then
           cad.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
           If .Aspect = 0 Or .Aspect = 1 Then ' Բ,Բ��,����
              x = .x0 + .Radius * Cos(a)
              y = .y0 - .Radius * Sin(a)  'Y�ᷴ��
           Else '��Բ
              If .Aspect < 1 Then
                  x = .x0 + .Radius * Cos(a)
                  y = .y0 - .Radius * .Aspect * Sin(a) 'Y�ᷴ��
              Else
                  x = .x0 + .Radius * Cos(a) / .Aspect
                  y = .y0 - .Radius * Sin(a) 'Y�ᷴ��
              End If
           End If
           If flag Then
              cad.Line (x, y)-(.x0, .y0), Color
              Mouseleftdownx = .x0
              Mouseleftdowny = .y0
              Mousepausex = x
              Mousepausey = y
           End If
        End If
   End With
End If
With cad
     .DrawMode = m
     .DrawWidth = w
     .DrawStyle = s
End With
'RedoParameter cad
End Sub

'ȷ���ж�
Private Sub EditBreak_Ok(x As Single, y As Single)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Dim m, n, i
       
If LinePoint > 0 Then 'ֱ��
   Dim Vx As Single, Vy As Single
   If PointToLineVerticalPoint(Vx, Vy, x, y, Tline(LinePoint).X1, Tline(LinePoint).Y1, Tline(LinePoint).X2, Tline(LinePoint).Y2) Then
      ReDim Preserve Tline(UBound(Tline) + 1)
      Tline(UBound(Tline)) = Tline(LinePoint)
      Tline(UBound(Tline)).Style = 0
      With Tline(LinePoint)
           If .Style = 0 Then 'ֱ��
              .X2 = Vx
              .Y2 = Vy
              Tline(UBound(Tline)).X1 = Vx
              Tline(UBound(Tline)).Y1 = Vy
              Exit Sub
           End If
           '��������Ϊֱ��
           m = Int(.Style / 10)  'ʮλ
           n = .Style Mod 10  '��λ
      End With
           i = LinePoint - n + 1
           Tline(LinePoint).X2 = Vx
           Tline(LinePoint).Y2 = Vy
           Tline(UBound(Tline)).X1 = Vx
           Tline(UBound(Tline)).Y1 = Vy
           While (i <= LinePoint + (m - n))
                Tline(i).Style = 0
                i = i + 1
           Wend
   End If
End If
If CirclePoint > 0 Then '����
   Dim a As Double
   With Tcircle(CirclePoint)
        a = Angle(x - .x0, y - .y0)
        If Abs(.Start) = 0 And Abs(.end) = 0 Then 'Բ,��Բ
           .Start = a
           .end = a - Pi / 1000000000000#
           Exit Sub
        End If
   End With
        'Բ��,����,��Բ
        If (Abs(Tcircle(CirclePoint).Start) < Abs(Tcircle(CirclePoint).end) And Abs(Tcircle(CirclePoint).Start) < a And Abs(Tcircle(CirclePoint).end) > a) Or (Abs(Tcircle(CirclePoint).end) < Abs(Tcircle(CirclePoint).Start) And ((a > Abs(Tcircle(CirclePoint).Start) And a < 2 * Pi) Or (a > 0 And a < Abs(Tcircle(CirclePoint).end)))) Then
           ReDim Preserve Tcircle(UBound(Tcircle) + 1)
           Tcircle(UBound(Tcircle)) = Tcircle(CirclePoint)
           Tcircle(UBound(Tcircle)).Start = a * Sgn(Tcircle(CirclePoint).Start)
           Tcircle(CirclePoint).end = a * Sgn(Tcircle(CirclePoint).end)
        End If
End If
End Sub

' ʹ��ֱ���ཻ,ѡȡֱ��
'�������ֵΪ0,��δѡȡֱ��
'��ѡ��ע��
Private Function EditSelectLine(x As Single, y As Single) As Long
Dim i As Long, r As Single, m As Single
    If UBound(Tline) > 0 Then
       r = -1
       For i = 1 To UBound(Tline)
           If Tline(i).Style >= 0 Then
               With Tline(i)
                    If Select_Line_Ok(x, y, .X1, .Y1, .X2, .Y2, SelectField) Then
                       m = PointToLineDirection(x, y, .X1, .Y1, .X2, .Y2)
                       If r = -1 Then
                          r = m
                       Else
                          If r < m Then
                             m = r
                          End If
                       End If
                       EditSelectLine = i
                    End If
               End With
           End If
       Next i
Else
           EditSelectLine = 0
End If
End Function

'ѡȡ����
'����ֵ:ָ��ѡȡ������
'0Ϊδѡȡ
Private Function EditSelectCircle(x As Single, y As Single, Optional Style As Integer = 0) As Long
Dim i As Long, r As Single, m As Single, L As Long
r = -1
        For i = 1 To UBound(Tcircle)
            With Tcircle(i)
                 If .Aspect = 0 And .Start = 0 And .end = 0 Then 'Բ
                     If Select_Circle_Ok(x, y, .x0, .y0, .Radius, SelectField) Then
                        m = Abs(TwoPointDirection(x, y, .x0, .y0) - .Radius)
                        If r < 0 Then
                           r = m
                           L = i
                        ElseIf m < r Then
                            r = m
                            L = i
                        End If
                     End If
                 Else
                 
                 End If
            End With
        Next i
        EditSelectCircle = L
End Function

'ʹѡȡ����ֱ��ͻ����ʾ
Private Sub EditSelectLineShow(i As Long, flag As Boolean)
Dim m, s, w
     With cad '�������
          m = .DrawMode
          s = .DrawStyle
          w = .DrawWidth
          .DrawMode = vbXorPen
          .DrawStyle = Tline(i).Commonparameter.Style
          .DrawWidth = Tline(i).Commonparameter.Width
     End With
     With Tline(i)
        If flag Then 'ͻ����ʾ
           cad.Line (.X1, .Y1)-(.X2, .Y2), ShowObjectColor
        Else '��ԭɫ��ʾ
           cad.DrawMode = vbCopyPen
           cad.Line (.X1, .Y1)-(.X2, .Y2), cad.BackColor
        End If
     End With
     With cad '�ָ�����
          .DrawMode = m
          .DrawWidth = w
          .DrawStyle = s
     End With
End Sub

'Բ��(No writed)
Private Sub EditFillet(x As Single, y As Single, Line1 As Long, Line2 As Long)
Dim f As Single, s As Single
f = ChamferFirstDistance '�����нǵ�����
s = ChamferSecondDistance
    '��Բ�ǵ㵽�е�ĳ���
    
    '��Բ�ǵ��е�
    EditChamfer x, y, Line1, Line2, True
    '��Բ�ǵ�Բ��
    ReDim Preserve Tcircle(UBound(Tcircle) + 1)
    
ChamferFirstDistance = f '�ָ��нǵ�����
ChamferSecondDistance = s
End Sub

'�н�
Private Sub EditChamfer(x As Single, y As Single, Line1 As Long, Line2 As Long, Optional FilletFlag As Boolean = False)
Dim m, s, w, p3 As point
Dim p As point, p1 As point, p2 As point, r As Single

        If EditTwoLineMiss(Line1, Line2) Then
           '���ԭͼ��
           With cad '�������
                m = .DrawMode
                s = .DrawStyle
                w = .DrawWidth
           End With
           EditSelectLineShow Line1, False
           EditSelectLineShow Line2, False
           '����ֱ�ߵĽ���
           TwoLineMissPoint Tline(Line1), Tline(Line2), p
           With Tline(Line1)
              Select Case PointOnLineOfLong(p1, p2, p, ChamferFirstDistance, Tline(Line1))
                  Case 1
                       p3.x = .X1
                       p3.y = .Y1
                       If p3.x = p.x And p3.y = p.y Then
                          .X1 = p1.x
                          .Y1 = p1.y
                       Else
                           .X2 = p1.x
                           .Y2 = p1.y
                       End If
                       Mouseleftdownx = p1.x
                       Mouseleftdowny = p1.y
                                cad.DrawMode = vbCopyPen
                                cad.DrawWidth = .Commonparameter.Width
                                cad.DrawStyle = .Commonparameter.Style
                                cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
                  Case 2
                       p3.x = .X1
                       p3.y = .Y1
                       If p3.x = p.x And p3.y = p.y Then
                          .X1 = p2.x
                          .Y1 = p2.y
                       Else
                           .X2 = p2.x
                           .Y2 = p2.y
                       End If
                       Mouseleftdownx = p2.x
                       Mouseleftdowny = p2.y
                                cad.DrawMode = vbCopyPen
                                cad.DrawWidth = .Commonparameter.Width
                                cad.DrawStyle = .Commonparameter.Style
                                cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
              End Select
           End With
           With Tline(Line2)
              Select Case PointOnLineOfLong(p1, p2, p, ChamferSecondDistance, Tline(Line2))
                  Case 1
                       p3.x = .X1
                       p3.y = .Y1
                       If p3.x = p.x And p3.y = p.y Then
                          .X1 = p1.x
                          .Y1 = p1.y
                       Else
                           .X2 = p1.x
                           .Y2 = p1.y
                       End If
                       Mousepausex = p1.x
                       Mousepausey = p1.y
                                cad.DrawMode = vbCopyPen
                                cad.DrawWidth = .Commonparameter.Width
                                cad.DrawStyle = .Commonparameter.Style
                                cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
                                
                  Case 2
                       p3.x = .X1
                       p3.y = .Y1
                       If p3.x = p.x And p3.y = p.y Then
                          .X1 = p2.x
                          .Y1 = p2.y
                       Else
                           .X2 = p2.x
                           .Y2 = p2.y
                       End If
                       Mousepausex = p2.x
                       Mousepausey = p2.y
                                cad.DrawMode = vbCopyPen
                                cad.DrawWidth = .Commonparameter.Width
                                cad.DrawStyle = .Commonparameter.Style
                                cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
              End Select
           End With
           
           With cad '�ָ�����
                .DrawWidth = w
                .DrawStyle = s
           End With
           If Not FilletFlag Then '�н�
              ReDim Preserve Tline(UBound(Tline) + 1) '�нǵ�����
              With Tline(UBound(Tline))
                   .X2 = Mousepausex
                   .Y2 = Mousepausey
                   SaveCommonParameter "line"
                   cad.DrawMode = vbCopyPen
                   cad.Line (.X1, .Y1)-(.X2, .Y2), LineColor
              End With
              cad.DrawMode = m
           End If
        End If
End Sub

'�޸�����
Private Sub EditModifyText(x As Single, y As Single)
Dim i As Long, j As Long, flag As Boolean
i = 1: j = UBound(Tfont) 'ѡȡҪ�޸ĵ�����
        Do While (i <= j)
            With Tfont(i)
                 If .point = 0 And .x <= x And .x + .Width >= x And .y <= y And .y + .Height >= y And .point = 0 Then
                       Tfont(i).flag = 1 '��Ϊѡ��
                       flag = True
                       Exit Do
                 ElseIf .x - .Width / 2 <= x And .x + .Width / 2 >= x And .y - .Height / 2 <= y And .y + .Height / 2 >= y And .point <> 0 Then
                        Tfont(i).flag = 1 '��Ϊѡ��
                        flag = True
                        Exit Do
                     Else
                         i = i + 1
                 End If
            End With
        Loop
        If flag Then
           InputText.ModifyFlag = flag
           LetFont Tfont(i), InputText.rt, False
           InputText.Show 1, fMainForm
           Tfont(i).text = InputText.rt.text
           LetFont Tfont(i), InputText.rt, True
           LetFont Tfont(i), text(i), False
           InputText.ModifyFlag = False
           Unload InputText
        End If
End Sub

' ʹ��ֱ���ཻ
Private Function EditTwoLineMiss(Line1 As Long, Line2 As Long) As Boolean
Dim p As point, r As Single, m, s, w
        If TwoLineMissPoint(Tline(Line1), Tline(Line2), p) <> 1 And Tline(Line1).Style >= 0 And Tline(Line2).Style >= 0 Then
           '���ԭͼ��
           With cad
                m = .DrawMode
                s = .DrawStyle
                w = .DrawWidth
           End With
           EditSelectLineShow Line1, False
           EditSelectLineShow Line2, False
           With Tline(Line1)
                r = TwoPointDirection(p.x, p.y, .X1, .Y1)
                If TwoPointDirection(p.x, p.y, .X2, .Y2) > r Then
                   .X1 = p.x
                   .Y1 = p.y
                Else
                   .X2 = p.x
                   .Y2 = p.y
                End If
                cad.DrawMode = vbCopyPen
                cad.DrawWidth = .Commonparameter.Width
                cad.DrawStyle = .Commonparameter.Style
                cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
           End With
           With Tline(Line2)
                r = TwoPointDirection(p.x, p.y, .X1, .Y1)
                If TwoPointDirection(p.x, p.y, .X2, .Y2) > r Then
                   .X1 = p.x
                   .Y1 = p.y
                Else
                   .X2 = p.x
                   .Y2 = p.y
                End If
                cad.DrawWidth = .Commonparameter.Width
                cad.DrawStyle = .Commonparameter.Style
                cad.Line (.X1, .Y1)-(.X2, .Y2), .Commonparameter.Color
           End With
           'Redraw
           With cad
                .DrawMode = m
                .DrawWidth = w
                .DrawStyle = s
           End With
           '������ת��Ϊֱ��
           Dim i As Long
           If Tline(Line1).Style > 0 Then
              m = Int(Tline(Line1).Style / 10) 'ʮλ
              s = Tline(Line1).Style Mod 10 '��λ
              i = Line1 - s + 1
              While (i <= Line1 + (m - s))
                    Tline(i).Style = 0
                    i = i + 1
              Wend
           End If
           If Tline(Line2).Style > 0 Then
              m = Int(Tline(Line2).Style / 10) 'ʮλ
              s = Tline(Line2).Style Mod 10 '��λ
              i = Line2 - s + 1
              While (i <= Line2 + (m - s))
                    Tline(i).Style = 0
                    i = i + 1
              Wend
           End If
           EditTwoLineMiss = True
        Else
           EditTwoLineMiss = False
        End If
End Function

'��׽ֱ�߻�Բ���Ķ˵�
Private Function snapeendpoint(x As Single, y As Single, snapepoint As snapepoint) As Boolean
Dim i As Long, r As Single

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
        
        'SelectPointObject x, y, 0, False  'ѡȡĿ��
           
    If UBound(Tline) > 0 Then  'ֱ��
       For i = 1 To UBound(Tline)
           If Select_Line_Ok(x, y, Tline(i).X1, Tline(i).Y1, Tline(i).X2, Tline(i).Y2, SelectField) Then
               With Tline(i)
                    r = TwoPointDirection(x, y, .X1, .Y1)
                    If snapepoint.r < 0 Then
                       snapepoint.r = r
                       snapepoint.x = .X1
                       snapepoint.y = .Y1
                    ElseIf r < snapepoint.r Then
                           snapepoint.r = r
                           snapepoint.x = .X1
                           snapepoint.y = .Y1
                    End If
                    r = TwoPointDirection(x, y, .X2, .Y2)
                    If r < snapepoint.r Then
                       snapepoint.r = r
                       snapepoint.x = .X2
                       snapepoint.y = .Y2
                    End If
               End With
           End If
        Next i
    End If
        
        If UBound(Tcircle) > 0 Then  'Բ��
           Dim xx As Single, yy As Single, k As Boolean
           For i = 1 To UBound(Tcircle)
               If Select_Circle_Ok(x, y, Tcircle(i).x0, Tcircle(i).y0, Tcircle(i).Radius, SelectField) Then
                  With Tcircle(i)
                    If .Start <> 0# Or .end <> 0# Then '����Բ
                       k = AnglePointInArc(Abs(.Start), Tcircle(i), xx, yy) '���
                       r = TwoPointDirection(xx, yy, x, y)
                       If snapepoint.r < 0 Then
                          snapepoint.r = r
                          snapepoint.x = xx
                          snapepoint.y = yy
                       Else
                          If r < snapepoint.r Then
                             snapepoint.r = r
                             snapepoint.x = xx
                             snapepoint.y = yy
                          End If
                       End If
                       k = AnglePointInArc(Abs(.end), Tcircle(i), xx, yy) '�յ�
                       r = TwoPointDirection(xx, yy, x, y)
                       If snapepoint.r < 0 Then
                          snapepoint.r = r
                          snapepoint.x = xx
                          snapepoint.y = yy
                       Else
                          If r < snapepoint.r Then
                             snapepoint.r = r
                             snapepoint.x = xx
                             snapepoint.y = yy
                          End If
                       End If
                    End If
                  End With
               End If
           Next i
        End If
        
        With snapepoint
             If .r < 0 Then
                .x = x
                .y = y
                snapeendpoint = False
             Else
                snapeendpoint = True
             End If
        End With
        
End Function

Private Function SnapeMiddlePoint(x As Single, y As Single, point As snapepoint) As Boolean
Dim i As Long, r As Single, xx As Single, yy As Single, a As Double

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        'SelectPointObject x, y, 0, False 'ѡȡĿ��
        
    If UBound(Tline) > 0 Then 'ֱ��
        For i = 1 To UBound(Tline)
           If Select_Line_Ok(x, y, Tline(i).X1, Tline(i).Y1, Tline(i).X2, Tline(i).Y2, SelectField) Then
               With Tline(i)
                    xx = (.X1 + .X2) / 2
                    yy = (.Y1 + .Y2) / 2
               End With
               r = TwoPointDirection(x, y, xx, yy)
               With point
                    If .r < 0 Then
                       .r = r
                       .x = xx
                       .y = yy
                    Else
                        If r < .r Then
                           .r = r
                           .x = xx
                           .y = yy
                        End If
                    End If
               End With
           End If
        Next i
    End If
        
    If UBound(Tcircle) > 0 Then 'Բ��,����
        Dim k
        For i = 1 To UBound(Tcircle)
           If Select_Circle_Ok(x, y, Tcircle(i).x0, Tcircle(i).y0, Tcircle(i).Radius, SelectField) Then
               With Tcircle(i)
                    If .Start <> 0 And .end <> 0 Then
                       If Abs(.Start) < Abs(.end) Then '���е�
                          k = AnglePointInArc((Abs(.Start) + Abs(.end)) / 2, Tcircle(i), xx, yy)
                       Else
                          a = (Abs(.Start) + 2 * Pi + Abs(.end)) / 2
                          If a > 2 * Pi Then a = a - 2 * Pi
                          k = AnglePointInArc(a, Tcircle(i), xx, yy)
                       End If
                       r = TwoPointDirection(xx, yy, x, y)
                       If point.r < 0 Then
                          point.r = r
                          point.x = xx
                          point.y = yy
                       Else
                           If point.r > r Then
                              point.r = r
                              point.x = xx
                              point.y = yy
                           End If
                       End If
                       If .Start < 0 Or .end < 0 Then
                          k = AnglePointInArc(Abs(.Start), Tcircle(i), xx, yy)
                          xx = (xx + .x0) / 2
                          yy = (yy + .y0) / 2
                          r = TwoPointDirection(xx, yy, x, y)
                          If point.r > r Then
                              point.r = r
                              point.x = xx
                              point.y = yy
                          End If
                          k = AnglePointInArc(Abs(.end), Tcircle(i), xx, yy)
                          xx = (xx + .x0) / 2
                          yy = (yy + .y0) / 2
                          r = TwoPointDirection(xx, yy, x, y)
                          If point.r > r Then
                              point.r = r
                              point.x = xx
                              point.y = yy
                          End If
                       End If
                    End If
               End With
           End If
        Next i
    End If
        
        With point
             If .r < 0 Then
                .x = x
                .y = y
                SnapeMiddlePoint = False
             Else
                SnapeMiddlePoint = True
             End If
        End With
        
End Function

Private Function SnapeCentrPoint(x As Single, y As Single, point As snapepoint) As Boolean
Dim r As Single, i As Long

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        'SelectPointObject x, y, 0, True 'ѡȡĿ��
        'Select_Circle x, y, 0
        
        If UBound(Tcircle) > 0 Then
           For i = 1 To UBound(Tcircle)
            If Select_Circle_Ok(x, y, Tcircle(i).x0, Tcircle(i).y0, Tcircle(i).Radius, SelectField) Then
               With Tcircle(i)
                    r = TwoPointDirection(x, y, .x0, .y0)
                    If point.r < 0 Then
                       point.r = r
                       point.x = .x0
                       point.y = .y0
                    Else
                       If r < point.r Then
                          point.r = r
                          point.x = .x0
                          point.y = .y0
                       End If
                    End If
               End With
            End If
           Next i
        End If

        With point
             If .r < 0 Then
                .x = x
                .y = y
                SnapeCentrPoint = False
             Else
                SnapeCentrPoint = True
             End If
        End With
        
End Function

Private Function snapemisspoint(x As Single, y As Single, point As snapepoint) As Boolean
Dim i As Long, j As Long, r As Single, f As Boolean, k
Dim PPoint As point, Point1 As point, Point2 As point, Point3 As point, POint4 As point
Dim lt As linetype

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

        'SelectPointObject x, y, 0, False  '  True 'ѡȡĿ��
        
If UBound(Tline) > 0 Then 'ֱ���ཻ
    For i = 1 To UBound(Tline) - 1
        If Select_Line_Ok(x, y, Tline(i).X1, Tline(i).Y1, Tline(i).X2, Tline(i).Y2, SelectField) Then
           For j = i + 1 To UBound(Tline)
               If Select_Line_Ok(x, y, Tline(j).X1, Tline(j).Y1, Tline(j).X2, Tline(j).Y2, SelectField) Then
                   If TwoLineMissPoint(Tline(i), Tline(j), PPoint) = True Then
                      With PPoint
                           r = TwoPointDirection(x, y, .x, .y)
                           If point.r < 0 Then
                              point.r = r
                              point.x = .x
                              point.y = .y
                           Else
                              If r < point.r Then
                                 point.r = r
                                 point.x = .x
                                 point.y = .y
                              End If
                           End If
                      End With
                   End If
               End If
           Next j
        End If
    Next i
End If
                
If UBound(Tline) > 0 And UBound(Tcircle) > 0 Then 'ֱ���������ཻ
   For i = 1 To UBound(Tline)
       If Select_Line_Ok(x, y, Tline(i).X1, Tline(i).Y1, Tline(i).X2, Tline(i).Y2, SelectField) Then
          For j = 1 To UBound(Tcircle)
              If Select_Circle_Ok(x, y, Tcircle(j).x0, Tcircle(j).y0, Tcircle(j).Radius, SelectField) Then
                   k = LineMissCirclePoint(Tline(i), Tcircle(j), Point1, Point2)
                   Select Case k
                          Case 1
                               r = TwoPointDirection(Point1.x, Point1.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = Point1.x
                                  point.y = Point1.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = Point1.x
                                     point.y = Point1.y
                                  End If
                               End If
                          Case 2
                               r = TwoPointDirection(Point2.x, Point2.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = Point2.x
                                  point.y = Point2.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = Point2.x
                                     point.y = Point2.y
                                  End If
                               End If
                          Case 3
                               r = TwoPointDirection(Point1.x, Point1.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = Point1.x
                                  point.y = Point1.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = Point1.x
                                     point.y = Point1.y
                                  End If
                               End If
                               r = TwoPointDirection(Point2.x, Point2.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = Point2.x
                                  point.y = Point2.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = Point2.x
                                     point.y = Point2.y
                                  End If
                               End If
                   End Select
                   With Tcircle(j)
                        If .Start < 0 Then '����
                           If AnglePointInArc(Abs(.Start), Tcircle(j), lt.X1, lt.Y1) Then
                              lt.X2 = .x0
                              lt.Y2 = .y0
                              If TwoLineMissPoint(Tline(i), lt, PPoint) = True Then
                                 r = TwoPointDirection(x, y, PPoint.x, PPoint.y)
                                 If point.r < 0 Then
                                  point.r = r
                                  point.x = PPoint.x
                                  point.y = PPoint.y
                                 Else
                                    If r < point.r Then
                                        point.r = r
                                        point.x = PPoint.x
                                        point.y = PPoint.y
                                    End If
                                 End If
                              End If
                           End If
                           If AnglePointInArc(Abs(.end), Tcircle(j), lt.X1, lt.Y1) Then
                              lt.X2 = .x0
                              lt.Y2 = .y0
                              If TwoLineMissPoint(Tline(i), lt, PPoint) = True Then
                                 r = TwoPointDirection(x, y, PPoint.x, PPoint.y)
                                 If point.r < 0 Then
                                  point.r = r
                                  point.x = PPoint.x
                                  point.y = PPoint.y
                                 Else
                                    If r < point.r Then
                                        point.r = r
                                        point.x = PPoint.x
                                        point.y = PPoint.y
                                    End If
                                 End If
                              End If
                           End If
                        End If
                   End With
              End If
          Next j
       End If
   Next i
 End If
        
If UBound(Tcircle) > 0 Then '�����ཻ
   For i = 1 To UBound(Tcircle)
       If Select_Circle_Ok(x, y, Tcircle(i).x0, Tcircle(i).y0, Tcircle(i).Radius, SelectField) Then
          For j = i + 1 To UBound(Tcircle)
              If Select_Circle_Ok(x, y, Tcircle(j).x0, Tcircle(j).y0, Tcircle(j).Radius, SelectField) Then
                   k = TwoCircleMissPoint(Tcircle(i), Tcircle(j), Point1, Point2, Point3, POint4)
                   If k = 1 Or k = 5 Then
                               r = TwoPointDirection(Point1.x, Point1.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = Point1.x
                                  point.y = Point1.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = Point1.x
                                     point.y = Point1.y
                                  End If
                               End If
                   End If
                   If k = 2 Or k = 5 Then
                               r = TwoPointDirection(Point2.x, Point2.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = Point2.x
                                  point.y = Point2.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = Point2.x
                                     point.y = Point2.y
                                  End If
                               End If
                   End If
                   If k = 3 Or k = 5 Then
                               r = TwoPointDirection(Point3.x, Point3.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = Point3.x
                                  point.y = Point3.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = Point3.x
                                     point.y = Point3.y
                                  End If
                               End If
                   End If
                   If k = 4 Or k = 5 Then
                               r = TwoPointDirection(POint4.x, POint4.y, x, y)
                               If point.r < 0 Then
                                  point.r = r
                                  point.x = POint4.x
                                  point.y = POint4.y
                               Else
                                  If r < point.r Then
                                     point.r = r
                                     point.x = POint4.x
                                     point.y = POint4.y
                                  End If
                               End If
                   End If
              End If
          Next j
      End If
   Next i
 End If
        
        With point
             If .r < 0 Then
                .x = x
                .y = y
                snapemisspoint = False
             Else
                snapemisspoint = True
             End If
        End With
End Function

'ˮƽ��ע
Public Sub DimensionHorizontal(ByVal x As Single, ByVal y As Single, ByVal Color As ColorConstants, flag As Boolean)
Dim m As Integer, s As Integer, w As Integer, n As Long, a As Double, ss As String
Dim Arrow As ArrowType

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

With cad  '�������
     m = .DrawMode
     s = .DrawStyle
     w = .DrawWidth
     .DrawMode = vbXorPen
     .DrawWidth = 1
     .DrawStyle = 0
End With
      Select Case DrawFlag
             Case 2
                  SingleLine vbLeftButton, x, y, Color, cad
             Case 3
                  n = UBound(Tline) '�ڶ����ӳ���
                  If Tline(n - 1).X1 < Tline(n).X1 Then
                     a = 0
                  Else
                     a = Pi
                  End If
                  '���ԭͼ��
                  If Dimension.FirstExtensinonLine Then
                     cad.Line (Tline(n - 1).X1, Tline(n - 1).Y1)-(Tline(n - 1).X1, Mousepausey), Color '�ӳ���
                  End If
                  If Dimension.SecondExtensioneLine Then
                     cad.Line (Tline(n).X1, Tline(n).Y1)-(Tline(n).X1, Mousepausey), Color
                  End If
                  cad.Line (Tline(n - 1).X1, Mousepausey)-(Tline(n).X1, Mousepausey), Color '��ע��
                  DrawArrow cad, Color, Tline(n - 1).X1, Mousepausey, Tline(n).X1, Mousepausey, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a '��ͷ
                  '��ͼ
                  If Not flag Then '�ӳ���
                     cad.DrawMode = vbCopyPen
                     Color = Dimension.ExtensioneLineColor
                  End If
                  If Dimension.FirstExtensinonLine Then
                     cad.Line (Tline(n - 1).X1, Tline(n - 1).Y1)-(Tline(n - 1).X1, y), Color '�ӳ���
                  End If
                  If Dimension.SecondExtensioneLine Then
                     cad.Line (Tline(n).X1, Tline(n).Y1)-(Tline(n).X1, y), Color
                  End If
                  If Not flag Then Color = Dimension.DimensionColor '��ע��
                  cad.Line (Tline(n - 1).X1, y)-(Tline(n).X1, y), Color
                  With Dimension '��ͷ��ɫ���ע����ɫһ��
                       Arrow = DrawArrow(cad, Color, Tline(n - 1).X1, y, Tline(n).X1, y, .LeftArrowHead, .RightArrowHead, .ArrowSize, True, a)
                       '��ע����
                       If .AutoDimension Then
                           Select Case .Position  '��עλ��
                                  Case 0 '0��עλ���ڱ�ע���Ϸ�
                                      text(text.UBound).left = Tfont(UBound(Tfont)).x - Tfont(UBound(Tfont)).Width / 2
                                      text(text.UBound).top = y - Abs(Arrow.y3 - y) - Tfont(UBound(Tfont)).Height
                                  Case 1 '1................����
                                        
                                  Case 2 '2................��
                                      text(text.UBound).left = Tfont(UBound(Tfont)).x - Tfont(UBound(Tfont)).Width / 2
                                      text(text.UBound).top = y - Abs(Arrow.y3 - y) - Tfont(UBound(Tfont)).Height / 2
                           End Select
                       End If
                  End With
                  Mousepausey = y
                  Mousepausex = x
            Case 4 '����ˮƽ��ע
                 n = UBound(Tline) '��ע��
                 With Tline(n)
                      If (.X1 - .X2 > 0 And .X2 - x > 0) _
                      Or (.X1 - .X2 < 0 And .X2 - x < 0) Then
                         If .X2 - x < 0 Then
                            a = 0
                         Else
                            a = Pi
                         End If
                         '���ԭͼ��
                         If Dimension.SecondExtensioneLine Then '�ڶ����ӳ���
                            cad.Line (Mousepausex, .Y2)-(Mousepausex, Mousepausey), Color
                         End If
                         '��ע��
                         cad.Line (Mousepausex, .Y2)-(.X2, .Y2), Color
                         '��ͷ
                         DrawArrow cad, Color, .X2, .Y2, Mousepausex, .Y2, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                         '��ͼ
                         If Dimension.SecondExtensioneLine Then '�ڶ����ӳ���
                            cad.Line (x, .Y2)-(x, y), Color
                         End If
                         If Not flag Then Color = Dimension.DimensionColor
                         cad.Line (x, .Y2)-(.X2, .Y2), Color '��ע��
                         '��ͷ
                         DrawArrow cad, Color, .X2, .Y2, x, .Y2, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                       With Dimension
                         '��ע����
                           If .AutoDimension Then
                              ss = CStr(Abs(Tline(n).X2 - x) * Paper.Ratio)
                              If .DimensionUnits Then
                                  ss = ss & Paper.Units '��ע��λ
                              End If
                              Tfont(UBound(Tfont)).text = ss
                              text(text.UBound).Caption = ss
                              Tfont(UBound(Tfont)).x = (Tline(n).X2 + x) / 2
                           Select Case .Position  '��עλ��
                                  Case 0 '0��עλ���ڱ�ע���Ϸ�
                                      text(text.UBound).left = Tfont(UBound(Tfont)).x - Tfont(UBound(Tfont)).Width / 2
                                      text(text.UBound).top = Tline(n).Y2 - Tfont(UBound(Tfont)).Height
                                  Case 1 '1................����
                                        
                                  Case 2 '2................��
                                      text(text.UBound).left = Tfont(UBound(Tfont)).x - Tfont(UBound(Tfont)).Width / 2
                                      text(text.UBound).top = Tline(n).Y2 - Tfont(UBound(Tfont)).Height / 2
                           End Select
                           End If
                       End With
                       Mousepausex = x
                       Mousepausey = y
                      End If
                 End With
      End Select
      
With cad '�ָ�����
     .DrawMode = m
     .DrawStyle = s
     .DrawWidth = w
End With
End Sub

'����ˮƽ��ע����
Private Sub DimensionHorizontalSaveParameter(ByVal x As Single, ByVal y As Single, ByVal Color As ColorConstants)
Dim n As Long, ss As String
Dim Arrow As ArrowType

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

             Select Case DrawFlag
                    Case 1, 2  'ȷ����һ��/�ߺ͵ڶ���/��
                         ReDim Preserve Tline(UBound(Tline) + 1) '�ӳ���
                         With Tline(UBound(Tline))
                              .X1 = x
                              .Y1 = y
                              '.Style = -DrawFlag - (UBound(Tfont) + 1) * 10  '����λ����,����ָʾ��ע�ߴ������������������λ��
                         End With
                         SaveCommonParameter "��ע"
                         If DrawFlag Then
                            Mouseleftdownx = x
                            Mouseleftdowny = y
                            Mousepausex = x
                            Mousepausey = y
                         End If
                         If DrawFlag = 2 Then  '���ԭͼ��
                            cad.DrawMode = vbXorPen
                            cad.DrawWidth = 1
                            cad.DrawStyle = 0
                            cad.Line (Mouseleftdownx, Mouseleftdowny)-(Tline(UBound(Tline) - 1).X1, Tline(UBound(Tline) - 1).Y1), Color '���ԭͼ��,�ο�ֱ��
                            With Tline(UBound(Tline) - 1)
                                 cad.Line (.X1, Mousepausey)-(Tline(UBound(Tline)).X1, Mousepausey), Color '�����ע��,Ϊ��һ�������׼��
                                 If Dimension.FirstExtensinonLine Then
                                    cad.Line (.X1, .Y1)-(.X1, Mousepausey), Color    'Ϊ��һ������ӳ�����׼��
                                 End If
                            End With
                            Dim a As Double
                            n = UBound(Tline)
                            If Tline(n - 1).X1 < Tline(n).X1 Then
                               a = 0
                            Else
                               a = Pi
                            End If
                            With Dimension
                                 DrawArrow cad, Color, Tline(n - 1).X1, y, Tline(n).X1, y, .LeftArrowHead, .RightArrowHead, .ArrowSize, True, a '�ο���ͷ,Ϊ��һ�������׼��
                                 If .AutoDimension Then
                                    '�ӱ�ע�ߴ������
                                    ss = CStr(Abs(Tline(n - 1).X1 - Tline(n).X1) * Paper.Ratio)
                                    If .DimensionUnits Then  '��ע��λ
                                       ss = ss & Paper.Units
                                    End If
                                    DimensionText (Tline(n - 1).X1 + Tline(n).X1) / 2, y, ss, n - 1 '(x,y)Ϊ���ֵ��е�
                                 End If
                            End With
                         End If
                         DrawFlag = DrawFlag + 1
                    Case 3   '���ȷ����ע��
                         '���ԭͼ��ȷ��ͼ��
                         DimensionHorizontal x, y, Viewcolor, False 'ע��˴���ɫҪ����ͼԤ��ɫ
                         n = UBound(Tline) '�ӳ���
                         With Tline(n - 1)
                              .X2 = .X1
                              .Y2 = y
                              .Style = -1 - 10 * UBound(Tfont) '��ע�ߵ���ʼ
                         End With
                         With Tline(n)
                              .X2 = .X1
                              .Y2 = y
                              .Style = -3
                         End With
                         '��ͷ, ��ע��,��ע����λ��
                         SaveDimensionParameter Tline(n - 1).X2, y, Tline(n).X2, y
                         If fMainForm.TCurrentOperist = "ˮƽ��ע" Then
                            DrawFlag = 1
                         Else '����ˮƽ��ע
                            cad.DrawMode = vbXorPen
                            cad.DrawWidth = 1
                            cad.DrawStyle = 0
                            DrawFlag = 4
                            '��һ����ע�ߵı�ע����
                            With Dimension
                               If .AutoDimension Then
                                  ss = CStr(Abs(Tline(UBound(Tline)).X2 - x) / 2)
                                  If .DimensionUnits Then
                                     ss = ss & Paper.Units
                                  End If
                               End If
                               DimensionText Tline(UBound(Tline)).X2, Tline(UBound(Tline)).Y2, ss, UBound(Tline)
                            End With
                            Tline(UBound(Tline)).Style = -2 - UBound(Tfont) * 10
                            With Tline(UBound(Tline))
                               If .X2 < x Then
                                  a = 0
                               Else
                                  a = Pi
                               End If
                               'Ϊ�Ժ����ͼ�е������׼��
                               cad.Line (.X2, .Y2)-(x, .Y2), Color '��ע��
                               DrawArrow cad, Color, .X2, .Y2, x, .Y2, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                            End With
                         End If
                    Case 4 '����ˮƽ��ע
                         n = UBound(Tline) 'ֻ�еڶ����ӳ���
                         ReDim Preserve Tline(n + 1) '��һ����ע��
                         With Tline(n + 1) '�ڶ����ӳ���
                              .X2 = x
                              .Y2 = Tline(n).Y2
                              .Style = -3
                              SaveCommonParameter "��ע"
                         End With
                         If (Tline(n).X1 - Tline(n + 1).X2 > 0 And Tline(n).X2 - x > 0) _
                         Or (Tline(n).X1 - Tline(n + 1).X2 < 0 And Tline(n).X2 - x < 0) Then
                            Tline(n + 1).X1 = x
                            Tline(n + 1).Y1 = y
                         Else
                              ReDim Preserve Tline(n)
                              Tline(n).Style = -9
                              Beep
                              Exit Sub
                         End If
                         '��ͷ, ��ע��,��ע����λ��
                          SaveDimensionParameter Tline(n).X2, Tline(n).Y2, x, Tline(n + 1).Y2
                          cad.DrawMode = vbXorPen
                         cad.DrawWidth = 1
                         cad.DrawStyle = 0
                          '��һ����ע�ߵı�ע����
                          With Dimension
                               If .AutoDimension Then
                                  ss = CStr(Abs(Tline(UBound(Tline)).X2 - x) / 2)
                                  If .DimensionUnits Then
                                     ss = ss & Paper.Units
                                  End If
                               End If
                               DimensionText Tline(UBound(Tline)).X2, Tline(UBound(Tline)).Y2, ss, UBound(Tline)
                          End With
                          Tline(UBound(Tline)).Style = -2 - UBound(Tfont) * 10 '����������ע�ߵ�����
                         With Tline(UBound(Tline))
                               If .X2 < x Then
                                  a = 0
                               Else
                                  a = Pi
                               End If
                               'Ϊ�Ժ����ͼ�е������׼��
                               cad.Line (x, y)-(.X2, .Y2), Color '�ӳ���
                               cad.Line (.X2, .Y2)-(x, .Y2), Color '��ע��
                               DrawArrow cad, Color, .X2, .Y2, x, .Y2, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                          End With
             End Select
End Sub

'ȷ������ˮƽ��ע������ע��
Public Sub HorizontalEnd(Style As String)
Dim i As Long
Dim j As Long
       Select Case Style
              Case "end"
                      ReDim Preserve Tfont(UBound(Tfont) - 1)
                      Unload text(text.UBound)
                      Tline(UBound(Tline)).Style = -9 - Int(Abs(Tline(UBound(Tline)).Style / 10)) * 10
                      Redraw
              Case "undo"
                   If Not DrawFlag Then
                      i = UBound(Tline)
                      While (Tline(i).Style Mod 10 <> -1)
                            i = i - 1
                      Wend
                      If DrawFlag = 2 Or DrawFlag = 3 Then
                         ReDim Preserve Tline(UBound(Tline) - DrawFlag + 1)
                         If DrawFlag = 3 Then
                            Unload text(text.UBound)
                            ReDim Preserve Tfont(UBound(Tfont) - 1)
                         End If
                         Redraw
                         Exit Sub
                      End If
                      '��ȥ���ֱ���ؼ�
                      If (Tline(i).Style / 10 < 0) And (Tline(i).Style Mod 10 = -1) Then
                          For j = Int(Abs(Tline(i).Style / 10)) To text.UBound  '��ȥ����
                              Unload text(j)
                          Next j
                          ReDim Preserve Tfont(Int(Abs(Tline(i).Style / 10)) - 1) '��ȥ��������
                      End If
                      ReDim Preserve Tline(i - 1)
                      Redraw
                   End If
       End Select
End Sub

''�����ͷ����,'��ע��,�ɹ���
Private Sub SaveDimensionParameter(ByVal X1 As Single, ByVal Y1 As Single, ByVal X2 As Single, ByVal Y2 As Single) '�����ͷ����
Dim a As Double, L As Long, r As Long
Dim Arrow As ArrowType

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

With Dimension
     a = Angle(X2 - X1, Y2 - Y1)
     '���ͷ����
     Arrow = DrawArrow(cad, Color, X1, Y1, X2, Y2, .LeftArrowHead, .RightArrowHead, .ArrowSize, False, a)
     L = UBound(Tline)
     Select Case .LeftArrowHead
            Case 0 '����ֵ,�޼�ͷ
            Case 1, 4, 6, 3 '����ͷ,��ռ�ͷ
                 ReDim Preserve Tline(L + 3)
                 With Tline(L + 1)
                      .X1 = X1
                      .Y1 = Y1
                      .X2 = Arrow.x3
                      .Y2 = Arrow.y3
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 With Tline(L + 2)
                      .X1 = X1
                      .Y1 = Y1
                      .X2 = Arrow.x4
                      .Y2 = Arrow.y4
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 With Tline(L + 3)
                      .X1 = Arrow.x3
                      .Y1 = Arrow.y3
                      .X2 = Arrow.x4
                      .Y2 = Arrow.y4
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 If .LeftArrowHead = 1 Or .LeftArrowHead = 4 Then
                     Tline(L + 1).Style = -4
                     Tline(L + 2).Style = -4
                     Tline(L + 3).Style = -4
                 Else
                     Tline(L + 1).Style = -3
                     Tline(L + 2).Style = -3
                     Tline(L + 3).Style = -3
                 End If
            Case 7 '���߶�
                 ReDim Preserve Tline(L + 1)
                 With Tline(L + 1)
                      .X1 = Arrow.x3
                      .Y1 = Arrow.y3
                      .X2 = Arrow.x4
                      .Y2 = Arrow.y4
                      .Style = -3
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
            Case 2, 5 '�������ڼ�ͷ
                 ReDim Preserve Tline(L + 2)
                 With Tline(L + 1)
                      .X1 = X1
                      .Y1 = Y1
                      .X2 = Arrow.x3
                      .Y2 = Arrow.y3
                      .Style = -3
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 With Tline(L + 2)
                      .X1 = X1
                      .Y1 = Y1
                      .X2 = Arrow.x4
                      .Y2 = Arrow.y4
                      .Style = -3
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                                     
     End Select
     r = UBound(Tline)
     Select Case .RightArrowHead
            Case 0 '����ֵ,�޼�ͷ
            Case 1, 4, 3, 6 '����ͷ,��ռ�ͷ
                 ReDim Preserve Tline(r + 3)
                 With Tline(r + 1)
                      .X1 = X2
                      .Y1 = Y2
                      .X2 = Arrow.x5
                      .Y2 = Arrow.y5
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 With Tline(r + 2)
                      .X1 = X2
                      .Y1 = Y2
                      .X2 = Arrow.x6
                      .Y2 = Arrow.y6
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 With Tline(r + 3)
                      .X1 = Arrow.x5
                      .Y1 = Arrow.y5
                      .X2 = Arrow.x6
                      .Y2 = Arrow.y6
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 If .RightArrowHead = 1 Or .RightArrowHead = 4 Then '����ͷ
                     Tline(r + 1).Style = -4
                     Tline(r + 2).Style = -4
                     Tline(r + 3).Style = -4
                 Else
                     Tline(r + 1).Style = -3
                     Tline(r + 2).Style = -3
                     Tline(r + 3).Style = -3
                 End If
                 
            Case 7 '���߶�
                 ReDim Preserve Tline(r + 1)
                 With Tline(r + 1)
                      .X1 = Arrow.x5
                      .Y1 = Arrow.y5
                      .X2 = Arrow.x6
                      .Y2 = Arrow.y6
                      .Style = -3
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
            Case 2, 5 '�������ڼ�ͷ
                 ReDim Preserve Tline(r + 2)
                 With Tline(r + 1)
                      .X1 = X2
                      .Y1 = Y2
                      .X2 = Arrow.x5
                      .Y2 = Arrow.y5
                      .Style = -3
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
                 With Tline(r + 2)
                      .X1 = X2
                      .Y1 = Y2
                      .X2 = Arrow.x6
                      .Y2 = Arrow.y6
                      .Style = -3
                      .Commonparameter.Color = Dimension.DimensionColor
                      .Commonparameter.Style = 0
                      .Commonparameter.Width = 1
                 End With
     End Select
End With
                         
     ReDim Preserve Tline(UBound(Tline) + 1) '����ڱ�ע�ߵ����
     With Tline(UBound(Tline)) '��ע��
          .X1 = X1
          .X2 = X2
          .Y1 = Y1
          .Y2 = Y2
          .Style = -9 - UBound(Tfont) * 10
          SaveCommonParameter "��ע"
     End With
                                                  
     '��ע����
     With Dimension
          Tfont(UBound(Tfont)).Posion = .Position
          If .AutoDimension Then
              Tfont(UBound(Tfont)).y = (Y1 + Y2) / 2
              Tfont(UBound(Tfont)).x = (X1 + X2) / 2
              Tfont(UBound(Tfont)).point = L - 1
          Else    '���Զ���עʱ
              InputText.xx = (X1 + X2) / 2
              InputText.yy = (Y1 + Y2) / 2
              InputText.TPoint = L - 1 'ָ���ע�ߵĵ�һ���ӳ���
              InputText.Show 1
              Tfont(UBound(Tfont)).Posion = .Position
              Select Case .Position  '��עλ��
                     Case 0 '0��עλ���ڱ�ע���Ϸ�
                         text(text.UBound).top = (Y1 + Y2) / 2 - Tfont(UBound(Tfont)).Height
                         text(text.UBound).left = (X1 + X1) / 2 - Tfont(UBound(Tfont)).Width / 2
                     Case 1 '1................����
                                
                     Case 2 '2................��
                          text(text.UBound).top = (Y1 - Y2) / 2 - Tfont(UBound(Tfont)).Height / 2
                          text(text.UBound).left = (X1 + X2) / 2 - Tfont(UBound(Tfont)).Width / 2
               End Select
          End If
     End With
                                                                           
End Sub

'��ֱ��ע
Public Sub DimensionVertical(ByVal x As Single, ByVal y As Single, ByVal Color As ColorConstants, flag As Boolean)

Dim m As Integer, s As Integer, w As Integer, n As Long, a As Double
Dim Arrow As ArrowType, ss As String

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

With cad  '�������
     m = .DrawMode
     s = .DrawStyle
     w = .DrawWidth
     .DrawMode = vbXorPen
     .DrawWidth = 1
     .DrawStyle = 0
End With
      Select Case DrawFlag
             Case 2
                  SingleLine vbLeftButton, x, y, Color, cad
             Case 3
                  n = UBound(Tline) '�ڶ����ӳ���
                  If Tline(n - 1).Y1 < Tline(n).Y1 Then
                     a = Pi / 2
                  Else
                     a = Pi * 3 / 2
                  End If
                  '���ԭͼ��
                  If Dimension.FirstExtensinonLine Then
                     cad.Line (Tline(n - 1).X1, Tline(n - 1).Y1)-(Mousepausex, Tline(n - 1).Y1), Color '�ӳ���
                  End If
                  If Dimension.SecondExtensioneLine Then
                     cad.Line (Tline(n).X1, Tline(n).Y1)-(Mousepausex, Tline(n).Y1), Color
                  End If
                  cad.Line (Mousepausex, Tline(n - 1).Y1)-(Mousepausex, Tline(n).Y1), Color '��ע��
                  DrawArrow cad, Color, Mousepausex, Tline(n - 1).Y1, Mousepausex, Tline(n).Y1, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a '��ͷ
                  '��ͼ
                  If Not flag Then '�ӳ���
                     cad.DrawMode = vbCopyPen
                     Color = Dimension.ExtensioneLineColor
                  End If
                  If Dimension.FirstExtensinonLine Then
                     cad.Line (Tline(n - 1).X1, Tline(n - 1).Y1)-(x, Tline(n - 1).Y1), Color '�ӳ���
                  End If
                  If Dimension.SecondExtensioneLine Then
                     cad.Line (Tline(n).X1, Tline(n).Y1)-(x, Tline(n).Y1), Color
                  End If
                  If Not flag Then Color = Dimension.DimensionColor '��ע��
                  cad.Line (x, Tline(n - 1).Y1)-(x, Tline(n).Y1), Color
                  With Dimension '��ͷ��ɫ���ע����ɫһ��
                       Arrow = DrawArrow(cad, Color, x, Tline(n - 1).Y1, x, Tline(n).Y1, .LeftArrowHead, .RightArrowHead, .ArrowSize, True, a)
                       '��ע����
                       'If .AutoDimension Then
                       '    Select Case .Position  '��עλ��
                       '           Case 0 '0��עλ���ڱ�ע���Ϸ�
                       '               Text(Text.UBound).left = x
                       '               Text(Text.UBound).top = y - Abs(Arrow.y3 - y) - Tfont(UBound(Tfont)).Height
                       '           Case 1 '1................����
                       '
                       '           Case 2 '2................��
                       '               Text(Text.UBound).left = Tfont(UBound(Tfont)).x - Tfont(UBound(Tfont)).Width / 2
                       '               Text(Text.UBound).top = y - Abs(Arrow.y3 - y) - Tfont(UBound(Tfont)).Height / 2
                       '    End Select
                       'End If
                       text(text.UBound).left = x - Tfont(UBound(Tfont)).Width / 2
                       text(text.UBound).top = Tfont(UBound(Tfont)).y - Tfont(UBound(Tfont)).Height / 2
                  End With
                  Mousepausey = y
                  Mousepausex = x
            Case 4 '������ֱ��ע
                   n = UBound(Tline) '��ע��
                   With Tline(n)
                        If (.Y1 - .Y2 > 0 And .Y2 - y > 0) _
                        Or (.Y1 - .Y2 < 0 And .Y2 - y < 0) Then
                           If .Y2 - y < 0 Then
                              a = Pi / 2
                           Else
                              a = Pi * 3 / 2
                           End If
                           '���ԭͼ��
                           If Dimension.SecondExtensioneLine Then '�ڶ����ӳ���
                              cad.Line (Mousepausex, Mousepausey)-(.X2, Mousepausey), Color
                           End If
                           '��ע��
                           cad.Line (.X2, Mousepausey)-(.X2, .Y2), Color
                           '��ͷ
                           DrawArrow cad, Color, .X2, .Y2, .X2, Mousepausey, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                           '��ͼ
                           If Dimension.SecondExtensioneLine Then '�ڶ����ӳ���
                              cad.Line (x, y)-(.X2, y), Color
                           End If
                           If Not flag Then Color = Dimension.DimensionColor
                           cad.Line (.X2, y)-(.X2, .Y2), Color '��ע��
                           '��ͷ
                           DrawArrow cad, Color, .X2, .Y2, .X2, y, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                           With Dimension
                               '��ע����
                                If .AutoDimension Then
                                   ss = CStr(Abs(Tline(n).Y2 - y) * Paper.Ratio)
                                   If .DimensionUnits Then
                                      ss = ss & Paper.Units '��ע��λ
                                   End If
                                   Tfont(UBound(Tfont)).text = ss
                                   text(text.UBound).Caption = ss
                                   Tfont(UBound(Tfont)).y = (Tline(n).Y2 + y) / 2
                                   text(text.UBound).top = Tfont(UBound(Tfont)).y - Tfont(UBound(Tfont)).Height / 2
                                   text(text.UBound).left = Tfont(UBound(Tfont)).x - Tfont(UBound(Tfont)).Width / 2
                                End If
                           End With
                           Mousepausex = x
                           Mousepausey = y
                        End If
                   End With
      End Select
      
With cad '�ָ�����
     .DrawMode = m
     .DrawStyle = s
     .DrawWidth = w
End With
End Sub

'���洹ֱ��ע����
Private Sub DimensionVerticalSaveParameter(ByVal x As Single, ByVal y As Single, ByVal Color As ColorConstants)
Dim n As Long, ss As String
Dim Arrow As ArrowType

#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

             Select Case DrawFlag
                    Case 1, 2  'ȷ����һ��/�ߺ͵ڶ���/��
                         ReDim Preserve Tline(UBound(Tline) + 1) '�ӳ���
                         With Tline(UBound(Tline))
                              .X1 = x
                              .Y1 = y
                              '.Style = -DrawFlag - (UBound(Tfont) + 1) * 10  '����λ����,����ָʾ��ע�ߴ������������������λ��
                         End With
                         SaveCommonParameter "��ע"
                         If DrawFlag Then
                            Mouseleftdownx = x
                            Mouseleftdowny = y
                            Mousepausex = x
                            Mousepausey = y
                         End If
                         If DrawFlag = 2 Then  '���ԭͼ��
                            cad.DrawMode = vbXorPen
                            cad.DrawWidth = 1
                            cad.DrawStyle = 0
                            cad.Line (Mouseleftdownx, Mouseleftdowny)-(Tline(UBound(Tline) - 1).X1, Tline(UBound(Tline) - 1).Y1), Color '���ԭͼ��,�ο�ֱ��
                            With Tline(UBound(Tline) - 1)
                                 cad.Line (Mousepausex, .Y1)-(Mousepausex, Tline(UBound(Tline)).Y1), Color  '�����ע��,Ϊ��һ�������׼��
                                 If Dimension.FirstExtensinonLine Then
                                    cad.Line (.X1, .Y1)-(Mousepausex, .Y1), Color     'Ϊ��һ������ӳ�����׼��
                                 End If
                            End With
                            Dim a As Double
                            n = UBound(Tline)
                            If Tline(n - 1).Y1 < Tline(n).Y1 Then
                               a = Pi / 2
                            Else
                               a = Pi * 3 / 2
                            End If
                            With Dimension
                                 DrawArrow cad, Color, x, Tline(n - 1).Y1, x, Tline(n).Y1, .LeftArrowHead, .RightArrowHead, .ArrowSize, True, a '�ο���ͷ,Ϊ��һ�������׼��
                                 If .AutoDimension Then
                                    '�ӱ�ע�ߴ������
                                    ss = CStr(Abs(Tline(n - 1).Y1 - Tline(n).Y1) * Paper.Ratio)
                                    If .DimensionUnits Then  '��ע��λ
                                       ss = ss & Paper.Units
                                    End If
                                    DimensionText x, (Tline(n - 1).Y1 + Tline(n).Y1) / 2, ss, n - 1 '(x,y)Ϊ���ֵ��е�
                                 End If
                            End With
                         End If
                         DrawFlag = DrawFlag + 1
                    Case 3   '���ȷ����ע��
                         '���ԭͼ��ȷ��ͼ��
                         DimensionVertical x, y, Viewcolor, False 'ע��˴���ɫҪ����ͼԤ��ɫ
                         n = UBound(Tline) '�ӳ���
                         With Tline(n - 1)
                              .X2 = x
                              .Y2 = .Y1
                              .Style = -1 - 10 * UBound(Tfont) '��ע�ߵ���ʼ
                         End With
                         With Tline(n)
                              .X2 = x
                              .Y2 = .Y1
                              .Style = -3
                         End With
                         '��ͷ, ��ע��,��ע����λ��
                         SaveDimensionParameter x, Tline(n - 1).Y2, x, Tline(n).Y2
                         If fMainForm.TCurrentOperist = "��ֱ��ע" Then
                            DrawFlag = 1
                         Else '������ֱ��ע
                            cad.DrawMode = vbXorPen
                            cad.DrawWidth = 1
                            cad.DrawStyle = 0
                            DrawFlag = 4
                            '��һ����ע�ߵı�ע����
                            With Dimension
                                 If .AutoDimension Then
                                    ss = CStr(Abs(Tline(UBound(Tline)).Y2 - y) / 2)
                                    If .DimensionUnits Then
                                       ss = ss & Paper.Units
                                    End If
                                 End If
                                 DimensionText Tline(UBound(Tline)).X2, Tline(UBound(Tline)).Y2, ss, UBound(Tline)
                            End With
                            Tline(UBound(Tline)).Style = -2 - UBound(Tfont) * 10
                            With Tline(UBound(Tline))
                                 If .Y2 < y Then
                                    a = Pi / 2
                                 Else
                                    a = Pi * 3 / 2
                                 End If
                                 'Ϊ�Ժ����ͼ�е������׼��
                                 cad.Line (.X2, .Y2)-(.X2, y), Color '��ע��
                                 DrawArrow cad, Color, .X2, .Y2, .X2, y, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                            End With
                         End If
                Case 4 '������ֱ��ע
                        n = UBound(Tline) 'ֻ�еڶ����ӳ���
                        ReDim Preserve Tline(n + 1) '�ڶ����ӳ���
                        With Tline(n + 1) '�ڶ����ӳ���
                              .X2 = Tline(n).X2
                              .Y2 = y
                              .Style = -3
                              SaveCommonParameter "��ע"
                         End With
                         If (Tline(n).Y1 - Tline(n + 1).Y2 > 0 And Tline(n).Y2 - y > 0) _
                         Or (Tline(n).Y1 - Tline(n + 1).Y2 < 0 And Tline(n).Y2 - y < 0) Then
                            Tline(n + 1).X1 = x
                            Tline(n + 1).Y1 = y
                         Else
                              ReDim Preserve Tline(n)
                              Tline(n).Style = -9
                              Beep
                              Exit Sub
                         End If
                         '��ͷ, ��ע��,��ע����λ��
                          SaveDimensionParameter Tline(n).X2, Tline(n).Y2, Tline(n + 1).X2, y
                          cad.DrawMode = vbXorPen
                          cad.DrawWidth = 1
                          cad.DrawStyle = 0
                          '��һ����ע�ߵı�ע����
                          With Dimension
                               If .AutoDimension Then
                                  ss = CStr(Abs(Tline(UBound(Tline)).Y2 - y) / 2)
                                  If .DimensionUnits Then
                                     ss = ss & Paper.Units
                                  End If
                               End If
                               DimensionText Tline(UBound(Tline)).X2, Tline(UBound(Tline)).Y2, ss, UBound(Tline)
                          End With
                          Tline(UBound(Tline)).Style = -2 - UBound(Tfont) * 10 '����������ע�ߵ�����
                          With Tline(UBound(Tline))
                               If .Y2 < y Then
                                  a = Pi / 2
                               Else
                                  a = Pi * 3 / 2
                               End If
                               'Ϊ�Ժ����ͼ�е������׼��
                               cad.Line (x, y)-(.X2, .Y2), Color '�ӳ���
                               cad.Line (.X2, .Y2)-(.X2, y), Color  '��ע��
                               DrawArrow cad, Color, .X2, .Y2, .X2, y, Dimension.LeftArrowHead, Dimension.RightArrowHead, Dimension.ArrowSize, True, a
                          End With
             End Select
End Sub

'
Public Sub ObjectList(Optional Index As Integer = -1)
       mmain.ObjectList Tline, Tcircle, Tfont, Index
End Sub
