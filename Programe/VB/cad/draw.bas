Attribute VB_Name = "draw"
'��ģ��Ϊ��ͼ����
'����:����

Option Explicit

'ͻ����ʾ��
Public Sub showpoint(x As Single, y As Single, object As Object, Color As ColorConstants)
Dim xx As Long, yy As Single
Dim scol As ColorConstants, ftype As Integer
ftype = object.FillStyle '�����������
scol = object.FillColor  '���������ɫ
 '��Ĵ�С,������ֵ��user.snapefield��Ӱ��
xx = snapefield / 2
yy = snapefield / 2

       object.FillStyle = 0
       object.FillColor = Color
       object.Line (x - xx, y - yy)-(x + xx, y + yy), Color, B
       object.FillStyle = ftype
       object.FillColor = scol
       
End Sub

'ֱ��
Public Sub SingleLine(Button As Integer, x As Single, y As Single, Color As ColorConstants, object As Object)
     Dim mode
     
     If Button = VBRUN.vbLeftButton Or (fMainForm.TCurrentOperist = "������" And DrawFlag = 2) Then
        mode = object.DrawMode
        object.DrawMode = 7
        object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
        object.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color
        Mousepausex = x
        Mousepausey = y
        object.DrawMode = mode
     End If
End Sub

'�ο�ֱ��(����)
Public Sub TiShiLine(x As Single, y As Single, Button As Integer, object As Object, Color As ColorConstants, Optional flag As Boolean = True)
Dim m As Integer, w As Integer, s As Integer
With object
     m = .DrawMode
     w = .DrawWidth
     s = .DrawStyle
     .DrawMode = 7
     .DrawWidth = 1
     .DrawStyle = 2
End With
    '���ԭֱ��
    object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
    If flag Then
       object.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color
    Mousepausex = x
    Mousepausey = y
    End If
With object
     .DrawMode = m
     .DrawWidth = w
     .DrawStyle = s
End With
End Sub

'����
Public Sub Rectangle(object As Object, x As Single, y As Single, Color As ColorConstants, Button As Integer)
Dim mode, Sy, w
       If Button = VBRUN.vbLeftButton Then
          mode = object.DrawMode
          object.DrawMode = 7
          If fMainForm.TCurrentOperist = "fieldselectobject" Then
             Sy = object.DrawStyle
             w = object.DrawWidth
             object.DrawStyle = 0
             object.DrawWidth = 1
          End If
          object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color, B
          object.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color, B
          Mousepausex = x
          Mousepausey = y
          object.DrawMode = mode
          If fMainForm.TCurrentOperist = "fieldselectobject" Then
             object.DrawStyle = Sy
             object.DrawWidth = w
          End If
      End If
End Sub

'������
Public Sub Three(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, Tline As linetype)
Dim mode
       mode = object.DrawMode
       object.DrawMode = 7
       Select Case DrawFlag
              Case 1
                   draw.SingleLine Button, x, y, Color, object
              Case 2
                   Select Case fMainForm.TCurrentOperist
                          Case "������"
                               With Tline
                                    '����
                                    object.Line (.X1, .Y1)-(Mousepausex, Mousepausey), Color
                                    object.Line (.X2, .Y2)-(Mousepausex, Mousepausey), Color
                                    '�ػ�
                                    object.Line (.X1, .Y1)-(x, y), Color
                                    object.Line (.X2, .Y2)-(x, y), Color
                               End With
                               Mousepausex = x
                               Mousepausey = y
                          Case "�ȱ�������"
                               '����
                               'Dim k, xx, yy
                               'k = user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).x1
                               'If k <> 0 Then
                               '   k = -(user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).y1 / k)
                               'End If
                               'xx = (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).x1) / 2
                               'yy = user.MousePauseY - (user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).y1) / 2
                               'k = k * yy + xx
                               'object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(k, user.MousePauseY), Color
                               'object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(k, user.MousePauseY), Color
                               ''�ػ�
                               'k = user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).x1
                               'If k <> 0 Then
                               '   k = -(user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).y1 / k)
                               'End If
                               'xx = (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).x1) / 2
                               'yy = Y - (user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).y1) / 2
                               'k = k * yy + xx
                               'object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(k, Y), Color
                               'object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(k, Y), Color
                               
                              ' user.MousePauseY = Y
                   End Select
       End Select
       object.DrawMode = mode
End Sub

'��������
Public Sub ��������(object As Object, x As Single, y As Single, Button As Integer, Color As ColorConstants, flag As Boolean)
Dim mode, xx, yy, X1, X2, Y2, Y1
mode = object.DrawMode
object.DrawMode = 7
If Button = VBRUN.vbLeftButton Then
    '�����Ƶ���һ��
    xx = Mousepausex - Mouseleftdownx
    yy = Mousepausey - Mouseleftdowny
    '�ѵڶ���Χ�Ƶ�һ����ʱ��ת60��
    X1 = xx / 2 - yy * Sin(Pi / 3)
    Y1 = xx * Sin(Pi / 3) + yy / 2
    '�ٰ������ƻ�ԭ��
    xx = X1 + Mouseleftdownx
    yy = Y1 + Mouseleftdowny
    object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
    object.Line -(xx, yy), Color
    object.Line -(Mouseleftdownx, Mouseleftdowny), Color
  If flag Then
    '�����Ƶ���һ��
    xx = x - Mouseleftdownx
    yy = y - Mouseleftdowny
    '�ѵڶ���Χ�Ƶ�һ����ʱ��ת60��
    X1 = xx / 2 - yy * Sin(Pi / 3)
    Y1 = xx * Sin(Pi / 3) + yy / 2
    '�ٰ������ƻ�ԭ��
    xx = X1 + Mouseleftdownx
    yy = Y1 + Mouseleftdowny
    object.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color
    object.Line -(xx, yy), Color
    object.Line -(Mouseleftdownx, Mouseleftdowny), Color
    
    Mousepausex = x
    Mousepausey = y
 End If
End If
object.DrawMode = mode
End Sub

'������
Public Sub ������(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, flag As Boolean)
Dim xx, yy, x3 As Single, y3 As Single, x4 As Single, y4 As Single, mode
mode = object.DrawMode
object.DrawMode = 7
If Button = VBRUN.vbLeftButton Then
       math.samerectanglethreeandforupiont Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey, x3, y3, x4, y4
       object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
       object.Line -(x3, y3), Color
       object.Line -(x4, y4), Color
       object.Line -(Mouseleftdownx, Mouseleftdowny), Color
������loop:
  If flag Then
       math.samerectanglethreeandforupiont Mouseleftdownx, Mouseleftdowny, x, y, x3, y3, x4, y4
       '�������Ƶ���һ��
       'xx = x - user.mouseleftdownx
       'yy = y - user.mouseleftdowny
       '�ѵڶ����Ƶ�һ��ת90��,�õ�������
       'x3 = -yy
       'y3 = xx
       '�������ƻص�ԭ��,�õ�������
       'x3 = x3 + user.mouseleftdownx
       'y3 = y3 + user.mouseleftdowny
       '�������Ƶ�������
       'xx = user.mouseleftdownx - x3
       'yy = user.mouseleftdowny - y3
       '�ѵ�һ���Ƶ�����ת90��
       'x4 = -yy
       'y4 = xx
       '�������ƻص�ԭ��
       'x4 = x4 + x3
       'y4 = y4 + y3
       object.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color
       object.Line -(x3, y3), Color
       object.Line -(x4, y4), Color
       object.Line -(Mouseleftdownx, Mouseleftdowny), Color
       Mousepausex = x
       Mousepausey = y
   End If
End If
object.DrawMode = mode
End Sub

'��������
Public Sub ��������(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, flag As Boolean)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single, modec, xx As Single, yy As Single
Dim mode
mode = object.DrawMode
object.DrawMode = 7
If Button = VBRUN.vbLeftButton Then
                    '�������Ƶ���һ��
          'xx = user.mousepausex - user.mouseleftdownx
          'yy = user.mousepausey - user.mouseleftdowny
          '��ת120��,��2*pi/3
          'x3 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y3 = xx * Sin(2 * user.pi / 3) - yy / 2
           '�������ƻ�ԭ��
          'x3 = x3 + user.mouseleftdownx
          'y3 = y3 + user.mouseleftdowny
          '������Ƶ�������
          'xx = user.mouseleftdownx - x3
          'yy = user.mouseleftdowny - y3
          '��ת120��
          'x4 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y4 = xx * Sin(2 * user.pi / 3) - yy / 2
          '�������ƻ�ԭ��
          'x4 = x4 + x3
          'y4 = y4 + y3
          '�������Ƶ����ĵ�
          'xx = x3 - x4
          'yy = y3 - y4
          '��ת120��
          'x5 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y5 = xx * Sin(2 * user.pi / 3) - yy / 2
          '������ƻص�ԭ��
          'x5 = x5 + x4
          'y5 = y5 + y4
          '�������Ƶ������
          'xx = x4 - x5
          'yy = y4 - y5
          '��ת120��
          'x6 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y6 = xx * Sin(2 * user.pi / 3) - yy / 2
          '������ƻص�ԭ��
          'x6 = x6 + x5
          'y6 = y6 + y5
          math.sixegdefour Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey, x3, y3, x4, y4, x5, y5, x6, y6
          object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
          object.Line -(x3, y3), Color
          object.Line -(x4, y4), Color
          object.Line -(x5, y5), Color
          object.Line -(x6, y6), Color
          object.Line -(Mouseleftdownx, Mouseleftdowny), Color
          '�������Ƶ���һ��
          'xx = x - user.mouseleftdownx
          'yy = y - user.mouseleftdowny
          '��ת120��,��2*pi/3
          'x3 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y3 = xx * Sin(2 * user.pi / 3) - yy / 2
           '�������ƻ�ԭ��
          'x3 = x3 + user.mouseleftdownx
          'y3 = y3 + user.mouseleftdowny
          '������Ƶ�������
          'xx = user.mouseleftdownx - x3
          'yy = user.mouseleftdowny - y3
          '��ת120��
          'x4 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y4 = xx * Sin(2 * user.pi / 3) - yy / 2
          '�������ƻ�ԭ��
          'x4 = x4 + x3
          'y4 = y4 + y3
          '�������Ƶ����ĵ�
          'xx = x3 - x4
          'yy = y3 - y4
          '��ת120��
          'x5 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y5 = xx * Sin(2 * user.pi / 3) - yy / 2
          '������ƻص�ԭ��
          'x5 = x5 + x4
          'y5 = y5 + y4
          '�������Ƶ������
          'xx = x4 - x5
          'yy = y4 - y5
          '��ת120��
          'x6 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y6 = xx * Sin(2 * user.pi / 3) - yy / 2
          '������ƻص�ԭ��
          'x6 = x6 + x5
          'y6 = y6 + y5
    If flag Then
          math.sixegdefour Mouseleftdownx, Mouseleftdowny, x, y, x3, y3, x4, y4, x5, y5, x6, y6
          object.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color
          object.Line -(x3, y3), Color
          object.Line -(x4, y4), Color
          object.Line -(x5, y5), Color
          object.Line -(x6, y6), Color
          object.Line -(Mouseleftdownx, Mouseleftdowny), Color
    
          Mousepausex = x
          Mousepausey = y
    End If
    
End If
object.DrawMode = mode
End Sub

'Բ
Public Sub SingleCircle(Button As Integer, x As Single, y As Single, Color As ColorConstants, object As Object)
Dim rad As Double
Dim mode
If Button = VBRUN.vbLeftButton Then
   mode = object.DrawMode
   object.DrawMode = 7
   rad = Sqr((Mouseleftdownx - Mousepausex) ^ 2 _
          + (Mouseleftdowny - Mousepausey) ^ 2)
   object.Circle (Mouseleftdownx, Mouseleftdowny), rad, Color
   rad = Sqr((Mouseleftdownx - x) ^ 2 + _
             (Mouseleftdowny - y) ^ 2)
   object.Circle (Mouseleftdownx, Mouseleftdowny), rad, Color
   Mousepausex = x
   Mousepausey = y
   object.DrawMode = mode
End If
End Sub

'�ο�Բ,�����붯Բ��
Public Sub TiShiCircle(Button As Integer, x As Single, y As Single, Color As ColorConstants, object As Object, flag As Boolean)
Dim w As Integer, s As Integer, rad As Double, m As Integer
If Button = vbLeftButton Then
With object
     w = .DrawWidth
     s = .DrawStyle
     m = .DrawMode
     .DrawWidth = 1
     .DrawStyle = 2
     .DrawMode = 7
End With
If flag Then '����ԭͼ��
   rad = Sqr((Mouseleftdownx - Mousepausex) ^ 2 _
          + (Mouseleftdowny - Mousepausey) ^ 2)
   object.Circle (Mouseleftdownx, Mouseleftdowny), rad, Color
   '��ʾ
   rad = Sqr((x - Mousepausex) ^ 2 _
          + (y - Mousepausey) ^ 2)
   object.Circle (x, y), rad, Color
Else
   rad = Sqr((Mouseleftdownx - Mousepausex) ^ 2 _
          + (Mouseleftdowny - Mousepausey) ^ 2)
   object.Circle (Mouseleftdownx, Mouseleftdowny), rad, Color
End If
With object
     .DrawWidth = w
     .DrawStyle = s
     .DrawMode = m
End With
   Mouseleftdownx = x
   Mouseleftdowny = y
End If
End Sub

'Բ��
Public Sub Arc(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, Tcircle As CircleType)
Dim xx, yy, mode, rad As Double
       mode = object.DrawMode       '����ģʽ
       object.DrawMode = 7
       Select Case DrawFlag
              Case 1      '��ʾ�ο�Բ
                   SingleCircle Button, x, y, Color, object
              Case 2      '��ʾ�ο�ֱ��
                   '��ʾ�ο�ֱ��
                   object.Line (Tcircle.x0, Tcircle.y0)-(Mousepausex, Mousepausey), Color
                   object.Line (Tcircle.x0, Tcircle.y0)-(x, y), Color
                   Mousepausex = x
                   Mousepausey = y
              Case 3      '��ʾ�ο�Բ���Ͳο�ֱ��
                   '�ο�ֱ��
                   With Tcircle
                        object.Line (.x0, .y0)-(Mousepausex, Mousepausey), Color
                        object.Line (.x0, .y0)-(x, y), Color
                       '�ο�Բ��
                        object.DrawMode = VBRUN.vbXorPen
                        xx = Mousepausex - .x0
                        yy = Mousepausey - .y0
                        rad = math.Angle(xx, yy)   '�������
                        object.Circle (.x0, .y0), .Radius, Color, .Start, rad
                        xx = x - .x0
                        yy = y - .y0
                        rad = math.Angle(xx, yy)   '�������
                        object.Circle (.x0, .y0), .Radius, Color, .Start, rad
                   End With
                   Mousepausex = x
                   Mousepausey = y
       End Select
       
       mode = object.DrawMode      '�ָ�ģʽ
End Sub

'��Բ
Public Sub Ellipse(object As Object, x As Single, y As Single, Button As Integer, Color As ColorConstants, Tcircle As CircleType)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
Dim asp, mode
       Select Case DrawFlag
              Case 1
                   draw.SingleCircle Button, x, y, Color, object
              Case 2
                   '������
                   With Tcircle
                        asp = (y - .y0) / .Radius
                        asp = Abs(asp)
                        mode = object.DrawMode
                        object.DrawMode = 7
                        object.Circle (.x0, .y0), .Radius, Color, , , Mousepausex
                        object.Circle (.x0, .y0), .Radius, Color, , , asp
                        Mousepausex = asp    '�����ϴε�������
                   End With
       End Select
End Sub

'��֪���㻭������
Public Sub drawthreeangle(object As Object, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, Color As ColorConstants)
       object.Line (X1, Y1)-(X2, Y2), Color
       object.Line -(x3, y3), Color
       object.Line -(X1, Y1), Color
End Sub

'��֪�ĵ㻭�ı���
'  4 ____________ 3
'   |           |
'   |           |
'   |           |
'  1------------- 2
Public Sub DrawForuegde(object As Object, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, Color As ColorConstants)
       object.Line (X1, Y1)-(X2, Y2), Color
       object.Line -(x3, y3), Color
       object.Line -(x4, y4), Color
       object.Line -(X1, Y1), Color
End Sub

'��֪���㻭����
' (x1,y1) ____________(x2,y1)
'        |           |
'        |           |
'        |           |
' (x1,y2)------------- (x2,y2)
Public Sub drawrectangle(object As Object, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, Color As ColorConstants)
       object.Line (X1, Y1)-(X2, Y1), Color
       object.Line -(X2, Y2), Color
       object.Line -(X1, Y2), Color
       object.Line -(X1, Y1), Color
End Sub

'��֪���������㻭������
'       1  _______ 2
'         /       \
'      6 /         \ 3
'        \         /
'         \_______/
'         5        4
Public Sub drawsixegde(object As Object, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single, Color As ColorConstants)
          object.Line (X1, Y1)-(X2, Y2), Color
          object.Line -(x3, y3), Color
          object.Line -(x4, y4), Color
          object.Line -(x5, y5), Color
          object.Line -(x6, y6), Color
          object.Line -(X1, Y1), Color
End Sub

Public Sub TiShiSelectRectangle(x, y, Button, Color As ColorConstants, flag As Boolean, object As Object) '��������ѡȡ�Ĳο�����
'flag�����Ƿ������ѡȡ�ο�����
Dim m As Integer, w As Integer, s As Integer
If Button = vbLeftButton Then
   With object
        m = .DrawMode
        w = .DrawWidth
        s = .DrawStyle
        .DrawMode = 7
        .DrawWidth = 1
        .DrawStyle = 2
   End With
   '���ԭ���;���
   object.Line (Mousepausex, Mousepausey)-(Mouseleftdownx, Mouseleftdowny), Color, B
   If flag Then     '�����Ƿ������ѡȡ�ο�����
      '��ʾ����
      object.Line (x, y)-(Mouseleftdownx, Mouseleftdowny), Color, B
      Mousepausex = x
      Mousepausey = y
   End If
   With object
        .DrawMode = m
        .DrawWidth = w
        .DrawStyle = s
   End With
End If
End Sub

'����ע���ϵļ�ͷ
Public Function DrawArrow(object As Object, Color As ColorConstants, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, LStyle As Integer, RStyle As Integer, Size As Single, flag As Boolean, DimLineAngle As Double) As ArrowType
'�Ҽ�ͷ,0Ϊ�޼�ͷ
'      ,1Ϊ����ͷ(30��)
'      ,2Ϊ���ڼ�ͷ(30��)
'      ,3Ϊ���..........
'......,4Ϊ����ͷ(45��)
'......,5Ϊ������ͷ(45��)
'.......6Ϊ��ռ�ͷ......
'......,7Ϊ���߶�
'DimLineAngle Ϊ��ע�ߵĽǶ�
'Public Type ArrowType '��ͷ
'       X3 As Single        '       (x3,y3)            (x5,y5)
'       Y3 As Single        '      /                      \
'       X4 As Single      '(x1,y1)/________________________\ (x2,y2)
'       Y4 As Single        '     \                        /
'       X5 As Single        '      \ (x4,y4)              /(x6,y6)
'       Y5 As Single
'       X6 As Single
'       Y6 As Single
'       End Type

'��flagΪ��ʱ,����ͼ��,ֻ����ֵ

Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, a As Double
Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single

   Select Case LStyle
          Case 2, 3, 1
               a = DimLineAngle + AngleToArc(30) 'Y�ᷴ��
               RoundPoint x4, y4, X1 + Size, Y1, X1, Y1, a
               a = DimLineAngle - AngleToArc(30)
               RoundPoint x3, y3, X1 + Size, Y1, X1, Y1, a
               If flag Then
                  object.Line (X1, Y1)-(x3, y3), Color
                  object.Line (X1, Y1)-(x4, y4), Color
                  If LStyle = 3 Then
                     object.Line (x3, y3)-(x4, y4), Color
                  End If
                  If LStyle = 1 Then
               
                  End If
               End If
          Case 5, 6, 4
               a = DimLineAngle + AngleToArc(45) 'Y�ᷴ��
               RoundPoint x4, y4, X1 + Size, Y1, X1, Y1, a
               a = DimLineAngle - AngleToArc(45)
               RoundPoint x3, y3, X1 + Size, Y1, X1, Y1, a
               If flag Then
                  object.Line (X1, Y1)-(x3, y3), Color
                  object.Line (X1, Y1)-(x4, y4), Color
                  If LStyle = 6 Then
                     object.Line (x3, y3)-(x4, y4), Color
                  End If
                  If LStyle = 4 Then
               
                  End If
               End If
          Case 7
               a = DimLineAngle + AngleToArc(45 + 90) 'Y�ᷴ��
               RoundPoint x4, y4, X1 + Size, Y1, X1, Y1, a
               a = DimLineAngle - AngleToArc(45)
               RoundPoint x3, y3, X1 + Size, Y1, X1, Y1, a
               If flag Then
                  object.Line (X1, Y1)-(x3, y3), Color
                  object.Line (X1, Y1)-(x4, y4), Color
               End If
   End Select
   Select Case RStyle
          Case 2, 3, 1
               a = Pi + DimLineAngle + AngleToArc(30)
               RoundPoint x5, y5, X2 + Size, Y2, X2, Y2, a
               a = Pi + DimLineAngle - AngleToArc(30)
               RoundPoint x6, y6, X2 + Size, Y2, X2, Y2, a
               If flag Then
                  object.Line (X2, Y2)-(x5, y5), Color
                  object.Line (X2, Y2)-(x6, y6), Color
                  If RStyle = 3 Then
                     object.Line (x5, y5)-(x6, y6), Color
                  End If
                  If RStyle = 1 Then
               
                  End If
               End If
          Case 6, 5, 4
               a = Pi + DimLineAngle + AngleToArc(45)
               RoundPoint x5, y5, X2 + Size, Y2, X2, Y2, a
               a = Pi + DimLineAngle - AngleToArc(45)
               RoundPoint x6, y6, X2 + Size, Y2, X2, Y2, a
               If flag Then
                  object.Line (X2, Y2)-(x5, y5), Color
                  object.Line (X2, Y2)-(x6, y6), Color
                  If RStyle = 6 Then
                     object.Line (x5, y5)-(x6, y6), Color
                  End If
                  If RStyle = 4 Then
               
                  End If
               End If
          Case 7
               a = DimLineAngle + AngleToArc(45 + 270)
               RoundPoint x5, y5, X2 + Size, Y2, X2, Y2, a
               a = Pi + DimLineAngle - AngleToArc(45)
               RoundPoint x6, y6, X2 + Size, Y2, X2, Y2, a
               If flag Then
                  object.Line (X2, Y2)-(x5, y5), Color
                  object.Line (X2, Y2)-(x6, y6), Color
               End If
   End Select
   
        DrawArrow.x3 = x3
        DrawArrow.y3 = y3
        DrawArrow.x4 = x4
        DrawArrow.y4 = y4
        DrawArrow.x5 = x5
        DrawArrow.y5 = y5
        DrawArrow.x6 = x6
        DrawArrow.y6 = y6
   
End Function

