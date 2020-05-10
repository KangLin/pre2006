Attribute VB_Name = "math"
'��ģ��Ϊ��ѧ����
'����:����

Option Explicit

'Private Type MissPoint
'        x As Single
'        y As Single
'        End Type

'����ת��Ϊ�Ƕ�
Public Function ArcToAngle(�� As Double) As Double
       ArcToAngle = 360 * �� / (2 * Pi)
End Function

'�Ƕ�ת��Ϊ����
Public Function AngleToArc(�� As Double) As Double
       AngleToArc = 2 * Pi * �� / 360
End Function

'����һ����ת
Public Sub RoundPoint(x As Single, y As Single, Ҫ��ת�ĵ�x1 As Single, Ҫ��ת�ĵ�y1 As Single, ����x0 As Single, ����y0 As Single, �� As Double)
Dim xx, yy
    '������ԭ���Ƶ�(����x0,����y0),��(Ҫ��ת�ĵ�x1,Ҫ��ת�ĵ�y1)�������Ϊ(xx,yy)
    xx = Ҫ��ת�ĵ�x1 - ����x0
    yy = Ҫ��ת�ĵ�y1 - ����y0
    '������ƶ���(����x0,����y0)��ת�ǶȦȣ���Ϊ����
    x = xx * Cos(��) - yy * Sin(��)
    y = xx * Sin(��) + yy * Cos(��)
    '�ٰ������ƻص�ԭ��
    x = x + ����x0
    y = y + ����y0
End Sub

'              /(x,y)
'             /
'            /
'   (x0,y0) /_��_____(x0+r,y0)
'                r
'��֪ˮƽ�ߵĳ���,����(X0,Y0)�ͼн���һ��
Public Sub ArcRoundpoint(x As Single, y As Single, x0 As Single, y0 As Single, r As Single, �� As Double)
       RoundPoint x, y, x0 + r, y0, x0, y0, ��
End Sub

'���K��һ��(X0,Y0)����a��Ľ�K`
Public Function AngleroundPoint(b As Double, k As Double) As Double
Dim a As Double
a = b + k
If a > 2 * Pi Then a = a - 2 * Pi
AngleroundPoint = a
End Function

'��һ��(x0,y0)����һ��ֱ��(x1,y1)-(x2,y2)����Ϊ(x,y)
Public Sub Mirror(x As Single, y As Single, ByVal x0 As Single, ByVal y0 As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single)
Dim �� As Double, xx, yy
    If X2 - X1 <> 0 Then
       �� = Atn((Y2 - Y1) / (X2 - X1)) * 2
       xx = x0 * Cos(��) + y0 * Sin(��) + X1 * (1 - Cos(��)) - Y1 * Sin(��)
       yy = x0 * Sin(��) - y0 * Cos(��) + Y1 * (1 + Cos(��)) - X1 * Sin(��)
    Else
       xx = x0 - 2 * (x0 - X1)
       yy = y0
    End If
    x = xx
    y = yy
End Sub

'��Ǧ�����һ��ֱ��(X1,Y1)-(x2,y2)�ľ����`
Public Function AngleMirror(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, �� As Double) As Double
Dim xx As Single, yy As Single, a As Double
xx = X2 - X1
yy = Y2 - Y1
a = Angle(xx, yy)
If a > Pi Then a = a - Pi
a = 2 * a - ��
If a < 0 Then a = 2 * Pi + a
AngleMirror = a
End Function

'����ԭ��ƽ�Ƶ�����(x1,y1)
Public Sub movetopoint(x As Single, y As Single, X1 As Single, Y1 As Single)
       x = x - X1
       y = y - Y1
End Sub
 
'������ӵ�(x1,y1)�ƻ�ԭ��
Public Sub movecomezieo(x As Single, y As Single, X1 As Single, Y1 As Single)
       x = x + X1
       y = y + Y1
End Sub

'�����任,��(X,Y)���(X0,y0)����������(xb,yb)�ı����任�õ��任��ĵ�(x,y)
Public Sub RatioChange(x As Single, y As Single, x0 As Single, y0 As Single, xb As Single, yb As Single)
Dim xx As Single, yy As Single
    xx = x - x0
    yy = y - y0
    x = xb * xx
    y = yb * yy
    x = x + x0
    y = y + y0
End Sub

'Բ,Բ��,����,��Բ�ı����任
Public Sub RatioChangeArc(Radius As Single, Start As Double, Eend As Double, Aspect As Double, ByVal xb As Single, ByVal yb As Single)
Dim xxb As Long, yyb As Long, f
    xxb = xb
    yyb = yb
    xb = Abs(xb)
    yb = Abs(yb)
    If Aspect = 0 Then  'Բ,Բ��,����
       If xb > yb Then
          Aspect = yb / xb
          Radius = Radius * xb
       Else
          Aspect = yb / xb
          Radius = Radius * yb
       End If
    Else '��Բ
       If Aspect < 1 Then
          Aspect = Aspect * yb / xb
          Radius = Radius * xb
       Else
          Aspect = Aspect * yb / xb
          Radius = Radius * yb
       End If
    End If
    If Not (Start = 0 And Eend = 0) And xxb < 0 Or yyb < 0 Then
       If xxb < 0 And yyb < 0 Then
          f = Sgn(Start)
          Start = Pi + Abs(Start)
          If Start > 2 * Pi Then Start = Start - 2 * Pi
          Start = Start * f
          f = Sgn(Eend)
          Eend = Abs(Eend) + Pi
          If Eend > 2 * Pi Then Eend = Eend - 2 * Pi
          Eend = f * Eend
       Else
           If xxb < 0 Then
              f = Sgn(Start)
              Start = Pi - Abs(Start)
              If Start < 0 Then Start = 2 * Pi + Start
              Start = f * Start
              f = Sgn(Eend)
              Eend = Pi - Abs(Eend)
              If Eend < 0 Then Eend = 2 * Pi + Eend
              Eend = f * Eend
           Else
              f = Sgn(Start)
              Start = 2 * Pi - Abs(Start)
              Start = f * Start
              f = Sgn(Eend)
              Eend = 2 * Pi - Abs(Eend)
              Eend = f * Eend
           End If
      End If
    End If
End Sub

'�����������ߵĽ���
Public Function TwoCircleMissPoint(Circle1 As CircleType, Circle2 As CircleType, Point1 As point, Point2 As point, Point3 As point, POint4 As point)
Dim r As Single
    r = TwoPointDirection(Circle1.x0, Circle1.y0, Circle2.x0, Circle2.y0)
    If r > Circle1.Radius + Circle2.Radius Then
       TwoCircleMissPoint = 0
       Exit Function
    End If
    
    TwoCircleMissPoint = 0
End Function

'��ֱ�ߵĽ���
Public Function TwoLineMissPoint1(Onelinex As Single, Oneliney As Single, Onelinex1 As Single, Oneliney1 As Single, Twolinex As Single, Twoliney As Single, Twolinex1 As Single, Twoliney1 As Single) As point
       Dim k1 As Single, k2 As Single
  With TwoLineMissPoint
       If (Twolinex - Twolinex1 <> 0) And (Onelinex - Onelinex1 <> 0) Then
          k1 = (Oneliney - Oneliney1) / (Onelinex - Onelinex1)
          k2 = (Twoliney - Twoliney1) / (Twolinex - Twolinex1)
          If k1 = k2 Then
             Exit Function  'ƽ��
          End If
            .x = ((Twoliney - Oneliney) + k1 * Onelinex - k2 * Twolinex) / (k1 - k2)
            .y = k1 * (.x - Onelinex) + Oneliney
       End If
       
       If (Onelinex - Onelinex1 = 0) And (Twolinex - Twolinex1 = 0) Then Exit Function
       
       If (Onelinex - Onelinex1 = 0) And (Twolinex - Twolinex1 <> 0) Then
           k2 = (Twoliney - Twoliney1) / (Twolinex - Twolinex1)
           .x = Onelinex
            .y = k2 * (.x - Twolinex) + Twoliney
       End If
       
       If (Onelinex - Onelinex1 <> 0) And (Twolinex - Twolinex1 = 0) Then
          k1 = (Oneliney - Oneliney1) / (Onelinex - Onelinex1)
          .x = Twolinex
          .y = k1 * (.x - Onelinex) + Oneliney
       End If
 End With
End Function

'��ֱ�ߵĽ���
Public Function TwoLineMissPoint(Line1 As linetype, Line2 As linetype, point As point) As Integer
Dim k1 As Single, k2 As Single
Dim Onelinex As Single, Oneliney As Single, Twolinex As Single, Twoliney As Single
Dim Onelinex1 As Single, Oneliney1 As Single, Twolinex1 As Single, Twoliney1 As Single
With Line1
     Onelinex = .X1
     Onelinex1 = .X2
     Oneliney = .Y1
     Oneliney1 = .Y2
End With
With Line2
     Twolinex = .X1
     Twolinex1 = .X2
     Twoliney = .Y1
     Twoliney1 = .Y2
End With
  With point
       If (Twolinex - Twolinex1 <> 0) And (Onelinex - Onelinex1 <> 0) Then 'һ�����
          k1 = (Oneliney - Oneliney1) / (Onelinex - Onelinex1)
          k2 = (Twoliney - Twoliney1) / (Twolinex - Twolinex1)
          If k1 = k2 Then
             TwoLineMissPoint = 1
             Exit Function  'ƽ��
          End If
            .x = ((Twoliney - Oneliney) + k1 * Onelinex - k2 * Twolinex) / (k1 - k2)
            .y = k1 * (.x - Onelinex) + Oneliney
       End If
       '�������
       If (Onelinex - Onelinex1 = 0) And (Twolinex - Twolinex1 = 0) Then TwoLineMissPoint = False: Exit Function
       
       If (Onelinex - Onelinex1 = 0) And (Twolinex - Twolinex1 <> 0) Then
           k2 = (Twoliney - Twoliney1) / (Twolinex - Twolinex1)
           .x = Onelinex
           .y = k2 * (.x - Twolinex) + Twoliney
       End If
       
       If (Onelinex - Onelinex1 <> 0) And (Twolinex - Twolinex1 = 0) Then
          k1 = (Oneliney - Oneliney1) / (Onelinex - Onelinex1)
          .x = Twolinex
          .y = k1 * (.x - Onelinex) + Oneliney
       End If
 End With
 '�Ƿ����߶���
 With Line1
      If (.X1 >= point.x And .X2 <= point.x) Or (.X1 <= point.x And .X2 >= point.x) Then
         TwoLineMissPoint = True
      Else
         TwoLineMissPoint = False
         Exit Function
      End If
 End With
 
 With Line2
      If (.X1 >= point.x And .X2 <= point.x) Or (.X1 <= point.x And .X2 >= point.x) Then
         TwoLineMissPoint = True
      Else
         TwoLineMissPoint = False
      End If
 End With
 End Function

'ֱ����������ߵĵĽ���
'����ֵ:
'0û�н���
'1Ϊ������point1��,'���е�ʱ,��ֵ��ͬ
'2 Ϊ������point2��
'3Ϊ�����㶼��Ч
'4��������Ч
Public Function LineMissCirclePoint(line As linetype, Arc As CircleType, Point1 As point, Point2 As point) As Long
Dim r As Single, k As Long, a As Double

    r = PointToLineDirection(Arc.x0, Arc.y0, line.X1, line.Y1, line.X2, line.Y2)
    If r > Arc.Radius Then
       LineMissCirclePoint = 0
       Exit Function
    End If
    
    k = PointToLineVerticalPoint(Point1.x, Point1.y, Arc.x0, Arc.y0, line.X1, line.Y1, line.X2, line.Y2) '���е�
    If r = Arc.Radius Then '����
       With Arc
          If k Then
             If .Start = 0 And .end = 0 And .Aspect = 0 Then 'Բ
                 LineMissCirclePoint = 1
             Else
                 If .Aspect = 0 Then 'Բ��,����
                    a = Angle(Point1.x - .x0, Point1.y - .y0)
                    If Abs(.Start) > Abs(.end) Then
                       If a > Abs(.Start) And a < Abs(.end) Then LineMissCirclePoint = 1
                    Else
                        If a < Abs(.end) Or (a < 2 * Pi And a > Abs(.Start)) Then LineMissCirclePoint = 1
                    End If
                 Else '��Բ
                 
                 End If
             End If
          End If
       End With
       Point2 = Point1 '���е�ʱ,��ֵ��ͬ
       Exit Function
    End If
    
    '����
    k = PointOnLineOfLong(Point1, Point2, Point1, Sqr(Arc.Radius ^ 2 - r ^ 2), line)
    If k = 0 Or k = 4 Then '������Ч
       LineMissCirclePoint = k
       Exit Function
    Else
       With Arc
            If .Start = 0 And .end = 0 And .Aspect = 0 Then ' Բ
               LineMissCirclePoint = k
            Else
               If .Aspect = 0 Then 'Բ��,����
                   Select Case k
                          Case 1
                               a = Angle(Point1.x - .x0, Point1.y - .y0)
                               If Abs(.Start) < Abs(.end) Then
                                  If a > Abs(.Start) And a < Abs(.end) Then LineMissCirclePoint = 1
                               Else
                                  If a < Abs(.end) Or (a < 2 * Pi And a > Abs(.Start)) Then LineMissCirclePoint = 1
                               End If
                          Case 2
                               a = Angle(Point2.x - .x0, Point2.y - .y0)
                               If Abs(.Start) < Abs(.end) Then
                                  If a > Abs(.Start) And a < Abs(.end) Then LineMissCirclePoint = 2
                               Else
                                  If a < Abs(.end) Or (a < 2 * Pi And a > Abs(.Start)) Then LineMissCirclePoint = 2
                               End If
                          Case 3
                               a = Angle(Point1.x - .x0, Point1.y - .y0)
                               If Abs(.Start) < Abs(.end) Then
                                  If a > Abs(.Start) And a < Abs(.end) Then LineMissCirclePoint = 1
                               Else
                                  If a < Abs(.end) Or (a < 2 * Pi And a > Abs(.Start)) Then LineMissCirclePoint = 1
                               End If
                               a = Angle(Point2.x - .x0, Point2.y - .y0)
                               If Abs(.Start) < Abs(.end) Then
                                  If a > Abs(.Start) And a < Abs(.end) Then
                                     If LineMissCirclePoint = 1 Then
                                        LineMissCirclePoint = 3
                                     Else
                                         LineMissCirclePoint = 2
                                     End If
                                  End If
                               Else
                                  If a < Abs(.end) Or (a < 2 * Pi And a > Abs(.Start)) Then
                                     If LineMissCirclePoint = 1 Then
                                        LineMissCirclePoint = 3
                                     Else
                                        LineMissCirclePoint = 2
                                     End If
                                  End If
                               End If
                    End Select
               Else '��Բ
               
               End If
            End If
       End With
    End If
    
End Function

'��֪һֱ�ߺ�ֱ���ϵĵ�,����Ե㳤��Ϊr��ֱ���ϵĵ�
'����:
'Qpoint1,Qpoint2Ϊ�����ֵ
'Point0 Ϊֱ���ϵ�һ��
'����ֵ:
'0Ϊ������
'1ΪֻQpoint1�е�ֵ���߶���
'2Ϊֻ��Qpont2�е�ֵ���߶���
'3Ϊ�����е�ֵ�����߶���
'4Ϊ�����е�ֵ�������߶���
Public Function PointOnLineOfLong(QPoint1 As point, QPoint2 As point, Point0 As point, d As Single, line As linetype) As Long
Dim k As Single, point As point
point = Point0

       With line
            If .X1 - .X2 = 0 Or .Y1 - .Y2 = 0 Then '�������
                If .X1 - .X2 = 0 And .Y1 - .Y2 = 0 Then
                    PointOnLineOfLong = 0
                    Exit Function
                Else
                    If .X1 - .X2 = 0 Then
                       If point.x <> .X1 Then PointOnLineOfLong = 0: Exit Function
                       QPoint1.x = .X1
                       QPoint2.x = .X1
                       QPoint1.y = point.y - d
                       QPoint2.y = point.y + d
                    Else
                       If point.y <> .Y1 Then PointOnLineOfLong = 0: Exit Function
                       QPoint1.x = point.x - d
                       QPoint2.x = point.x + d
                       QPoint1.y = .Y1
                       QPoint2.y = .Y1
                    End If
                End If
            Else 'һ�����
                k = (.Y1 - .Y2) / (.X1 - .X2)
                If Abs((point.y - .Y1 - k * (point.x - .X1))) > 0.001 Then PointOnLineOfLong = 0: Exit Function
                QPoint1.x = point.x - Sqr(d * d / (k * k + 1))
                QPoint1.y = k * (QPoint1.x - .X1) + .Y1
                QPoint2.x = point.x + Sqr(d * d / (k * k + 1))
                QPoint2.y = k * (QPoint2.x - .X1) + .Y1
            End If
            
            If (QPoint1.x < .X1 And QPoint1.x > .X2) Or (QPoint1.x > .X1 And QPoint1.x < .X2) Then
               If (QPoint2.x < .X1 And QPoint2.x > .X2) Or (QPoint2.x > .X1 And QPoint2.x < .X2) Then
                  PointOnLineOfLong = 3
               Else
                  PointOnLineOfLong = 1
               End If
            Else
               If (QPoint2.x < .X1 And QPoint2.x > .X2) Or (QPoint2.x > .X1 And QPoint2.x < .X2) Then
                   PointOnLineOfLong = 2
               Else
                   PointOnLineOfLong = 4
               End If
            End If
       End With
       
End Function

'�㵽ֱ�ߵĴ���,����������߶��ڷ�����,���򷵻ؼ�
Public Function PointToLineVerticalPoint(Vx As Single, Vy As Single, x As Single, y As Single, linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single) As Boolean
Dim k As Single
If linex1 - linex2 <> 0 And liney1 - liney2 <> 0 Then
   k = (liney2 - liney1) / (linex2 - linex1)
   Vx = (k * (y - liney1) + k * k * linex1 + x) / (k * k + 1)
   Vy = k * (Vx - linex1) + liney1
Else
    If linex1 - linex2 = 0 Then
       Vx = linex1
       If y >= liney1 And y <= liney2 Or (y <= liney1 And y >= liney2) Then
          Vy = y
       Else
          Vy = y
          PointToLineVerticalPoint = False
          Exit Function
       End If
    Else
       Vx = x
       Vy = liney1
    End If
End If
If Vx >= linex1 And Vx <= linex2 Or (Vx <= linex1 And Vx >= linex2) Then
   PointToLineVerticalPoint = True
Else
   If Abs(Vx - linex1) < Abs(Vx - linex2) Then
      Vx = linex1
      Vy = liney1
   Else
      Vx = linex2
      Vy = liney2
   End If
   PointToLineVerticalPoint = False
End If
End Function

'�㵽ֱ�ߵĴ���,����ֵΪ��,������߶���,����,�����߶���,�����߶���
Public Function VerticalPoint(Vx As Single, Vy As Single, x As Single, y As Single, linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single) As Boolean
Dim k As Single
If linex1 - linex2 <> 0 And liney1 - liney2 <> 0 Then
   k = (liney2 - liney1) / (linex2 - linex1)
   Vx = (k * (y - liney1) + k * k * linex1 + x) / (k * k + 1)
   Vy = k * (Vx - linex1) + liney1
Else
    If linex1 - linex2 = 0 Then
       Vx = linex1
       If y >= liney1 And y <= liney2 Or (y <= liney1 And y >= liney2) Then
          Vy = y
       Else
          Vy = y
          VerticalPoint = False
          Exit Function
       End If
    Else
       Vx = x
       Vy = liney1
    End If
End If
If Vx >= linex1 And Vx <= linex2 Or (Vx <= linex1 And Vx >= linex2) Then
   VerticalPoint = True
Else
   VerticalPoint = False
End If
End Function

Public Function PointToLineVerticalPointType(Point0 As point, line As linetype, point As point) As Boolean
       PointToLineVerticalPointType = PointToLineVerticalPoint(point.x, point.y, Point0.x, Point0.y, line.X1, line.Y1, line.X2, line.Y2)
End Function

'�㵽ֱ�ߵľ���
Public Function PointToLineDirection(Pointx As Single, Pointy As Single, linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single) As Single
Dim k, d, y
       If linex2 - linex1 <> 0 Then
          k = (liney2 - liney1) / (linex2 - linex1)
          y = k * (Pointx - linex1) + liney1
          d = Abs(y - Pointy)
          k = Sqr((linex1 - linex2) ^ 2 + (liney1 - liney2) ^ 2)
          PointToLineDirection = d * Abs(linex1 - linex2) / k
       Else
          PointToLineDirection = Abs(linex1 - Pointx)
       End If
End Function

'�����ľ���
Public Function TwoPointDirection(x As Single, y As Single, X1 As Single, Y1 As Single) As Single
Dim d, m
       d = x - X1
       m = y - Y1
       TwoPointDirection = Sqr(d ^ 2 + m ^ 2)
End Function

'��(X!,Y!)�Ƶ�(X0,Y0)��ת90�ȵõ����µ�(X,Y)
Public Sub ��ת90��(x As Single, y As Single, X1 As Single, Y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = X1 - x0
       yy = Y1 - y0
       x = -yy
       y = xx
       x = x + x0
       y = y + y0
End Sub

'��(X!,Y!)�Ƶ�(X0,Y0)��ת-90�ȵõ����µ�(X,Y)
Public Sub ��ת��90��(x As Single, y As Single, X1 As Single, Y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = X1 - x0
       yy = Y1 - 0
       x = yy
       y = -xx
       x = x + x0
       y = y + y0
End Sub

'��(X!,Y!)�Ƶ�(X0,Y0)��ת180�ȵõ����µ�(X,Y)
Public Sub ��ת180��(x As Single, y As Single, X1 As Single, Y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = X1 - x0
       yy = Y1 - 0
       x = -xx
       y = yy
       x = x + x0
       y = y + y0
End Sub

'��֪�������ε������������������
Public Sub SamethreeThirdVertex(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single)
'             1
'             /\
'            /  \
'           /    \
'          /      \
'        2/________\3
Dim xx As Single, yy As Single
            '�������Ƶ���һ��
            xx = X2 - X1
            yy = Y2 - Y1
            '�ѵڶ���Χ�Ƶ�һ����ʱ��ת60��
            x3 = xx / 2 - yy * Sin(Pi / 3)
            y3 = xx * Sin(Pi / 3) + yy / 2
            '�ٰ������ƻ�ԭ��
            x3 = x3 + X1
            y3 = y3 + Y1
End Sub


'��֪�����ε�������������������֪(X1,Y1)��(X2,Y2)
Public Sub samerectanglethreeandforupiont(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single)
Dim xx As Single, yy As Single
'    4 _________3
'     |        |
'     |        |
'     |        |
'    1---------- 2
        '�������Ƶ���һ��
       xx = X2 - X1
       yy = Y2 - Y1
       '�ѵڶ����Ƶ�һ��ת90��,�õ����ĵ�
       x4 = -yy
       y4 = xx
       '�������ƻص�ԭ��,�õ����ĵ�
       x4 = x4 + X1
       y4 = y4 + Y1
       '�������Ƶ����ĵ�
       xx = X1 - x4
       yy = Y1 - y4
       '�ѵ�һ���Ƶ��ĵ�ת90��
       x3 = -yy
       y3 = xx
       '�������ƻص�ԭ��,�õ�������
       x3 = x3 + x4
       y3 = y3 + y4
End Sub

'��֪�������ε������������ĵ���֪(X1,Y1)��(X2,Y2)
'       5 ______ 4
'        /      \
'     6 /        \ 3
'       \        /
'        \      /
'       1 ------  2
Public Sub sixegdefour(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single)
Dim xx As Single, yy As Single
          '�������Ƶ���һ��
          xx = X2 - X1
          yy = Y2 - Y1
          '��ת120��,��2*pi/3
          x6 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y6 = xx * Sin(2 * Pi / 3) - yy / 2
           '�������ƻ�ԭ��
          x6 = x6 + X1
          y6 = y6 + Y1
          '������Ƶ�������
          xx = X1 - x6
          yy = Y1 - y6
          '��ת120��
          x5 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y5 = xx * Sin(2 * Pi / 3) - yy / 2
          '�������ƻ�ԭ��
          x5 = x5 + x6
          y5 = y5 + y6
          '�������Ƶ������
          xx = x6 - x5
          yy = y6 - y5
          '��ת120��
          x4 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y4 = xx * Sin(2 * Pi / 3) - yy / 2
          '������ƻص�ԭ��
          x4 = x4 + x5
          y4 = y4 + y5
          '�������Ƶ����ĵ�
          xx = x5 - x4
          yy = y5 - y4
          '��ת120��
          x3 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y3 = xx * Sin(2 * Pi / 3) - yy / 2
          '������ƻص�ԭ��
          x3 = x3 + x4
          y3 = y3 + y4
End Sub

'����ԭ��Ϊ���ĵ���ת��,�ѿ������������
'����ˮƽ��(X��)�ļн�,��Χ(0 -- 2��)
'xx,yy �ֱ�Ϊ���㵽ԭ���ʸ��x0x1,y0y1
'��xx=x1-x0
'  yy=y1-y0
Public Function Angle(xx, yy) As Double  '����ԭ��Ϊ���ĵ���ת��
Dim rad As Double
    '���������,ע��Y�᲻ͬ(����Ϊ��)
    If xx = 0 And yy = 0 Then Angle = 0: Exit Function '�����ʱ,�����հ���ʱ,��ת����0��,����270��,��Ϊ�����湫ʽ�����270��
    If xx > 0 And yy > 0 Then
       rad = 8 * Rfzghr - Atn(yy / xx)  '��Χ (3*PI/2--2*PI)
    Else
       If xx > 0 And yy <= 0 Then
          rad = Abs(Atn(yy / xx)) '��Χ [0--PI/2)
       Else
          If xx < 0 And yy >= 0 Then
             rad = Abs(Atn(yy / xx)) + 4 * Rfzghr '��Χ [PI--3*PI/2)
          Else
             If xx < 0 And yy < 0 Then
                 rad = 4 * Rfzghr - Atn(yy / xx) '��Χ (PI/2--PI)
             End If
          End If
       End If
     End If
     If xx = 0 And yy > 0 Then Angle = Pi / 2: Exit Function 'Y�ᷴ��
     If xx = 0 And yy < 0 Then rad = 3 * Pi / 2
     Angle = rad
End Function

'��һ���Ƿ���һ����������
Public Function pointinrectangle(x As Single, y As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single) As Boolean
       If x <= MaxTwoNum(X1, X2) And x >= MinTwoNum(X1, X2) And y <= MaxTwoNum(Y1, Y2) And y >= MinTwoNum(Y1, Y2) Then
          pointinrectangle = True
          Exit Function
       End If
          pointinrectangle = False
End Function

'���������е�С����
Public Function MinTwoNum(X1 As Single, X2 As Single) As Single
       If X1 >= X2 Then
          MinTwoNum = X2
       Else
          MinTwoNum = X1
       End If
End Function

'���������еĴ����
Public Function MaxTwoNum(X1 As Single, X2 As Single) As Single
       If X1 >= X2 Then
          MaxTwoNum = X1
       Else
          MaxTwoNum = X2
       End If
End Function

'���������е���С����
Public Function MinThreeNum(X1 As Single, X2 As Single, x3 As Single) As Single
       MinThreeNum = MinTwoNum(MinTwoNum(X1, X2), x3)
End Function

'���������е�ȡ�����
Public Function MaxThreeNum(X1 As Single, X2 As Single, x3 As Single) As Single
       MaxThreeNum = MaxTwoNum(MaxTwoNum(X1, X2), x3)
End Function

'��ͼ��������
Public Sub zoom(object As Object, x As Single, y As Single)
On Error GoTo zoomloop
Dim top As Single, left As Single, w As Single, h As Single, sw As Single, sh As Single
       With object
            top = .top
            left = .left
            w = .Width
            h = .Height
            sw = .Scalewidth
            sh = .ScaleHeight
            .top = Form1.desk.ScaleY(-y * user.HeightZoomnum, 6, 3)
            .left = Form1.desk.ScaleX(-x * user.WidthZoomnum, 6, 3)
            .Width = user.WidthZoomnum * .Width
            .Height = .Height * user.HeightZoomnum
            .ScaleHeight = .ScaleHeight / user.HeightZoomnum
            .Scalewidth = .Scalewidth / user.WidthZoomnum
            user.Scrollbar Abs(.left), Abs(.top)  '�ù�����
            Exit Sub
zoomloop:    '������ʱ�Ĵ���
               .top = top
               .left = .left
               .Width = w
               .Height = h
               .Scalewidth = sw
               .ScaleHeight = sh
             user.Scrollbar Abs(.left), Abs(.top)  '�ù�����
       End With
End Sub

'�����ַ�,ûд��
Public Sub disstring(object As Object, sstring As String)
Dim i, j, x, y
x = object.CurrentX
y = object.CurrentY
j = Len(sstring)
object = Form1.cad
    For i = 1 To j
           If Mid$(sstring, i, 1) <> Chr$(13) Then
              object.Print Mid$(sstring, i, 1);
           Else
              object.Print Chr$(13)
              object.CurrentX = x
           End If
    Next i
End Sub

'��Բ��,���ε����,��Сֵ
Public Sub ArcMaxMin(Xmax As Single, Ymax As Single, Xmin As Single, Ymin As Single, x0 As Single, y0 As Single, Radius As Single, ByVal Start As Double, ByVal Eend As Double)
Dim s As Double, e As Double
s = Start
e = Eend
Start = Abs(Start)
Eend = Abs(Eend)
'��Xmax   x=r*cos(��),,��k=0��ʱȡ���
If ((Start = 0 Or Eend = 2 * Pi) And (Start < Eend)) Or ((Start > Eend) And (Eend >= 0) And (Start <= 2 * Pi)) Then
   Xmax = x0 + Radius
Else
      Xmax = MaxTwoNum(x0 + Radius * Cos(Start), x0 + Radius * Cos(Eend))
      If (s < 0 Or e < 0) And Xmax < x0 Then Xmax = x0
End If
'��Xmin   x=r*cos(��),��x=180��ʱȡ��С
If ((Start < Eend) And (Eend >= Pi And Start <= Pi)) Or ((Start > Eend) And ((Start <= Pi And Eend <= Pi) Or (Start >= Pi And Eend >= Pi))) Then
   Xmin = x0 - Radius
Else
      Xmin = MinTwoNum(x0 + Radius * Cos(Start), x0 + Radius * Cos(Eend))
      If (s < 0 And e < 0) And Xmin > x0 Then Xmin = x0
End If
'��Ymin   y=r*sin(��)  ,��K=90ʱȡ���K=270��ʱȡ��С
If (Start < Eend And Start <= Pi / 2 And Eend >= Pi / 2) Or (Start > Eend And ((Start >= Pi / 2 And Eend >= Pi / 2) Or (Start <= Pi / 2 And Eend <= Pi / 2))) Then
    Ymin = y0 - Radius
Else
       Ymin = MinTwoNum(y0 - Radius * Sin(Start), y0 - Radius * Sin(Eend))
        If (s < 0 And e < 0) And Ymin > y0 Then Ymin = y0
End If
'��Ymax
If (Start < Eend And Start <= 3 * Pi / 2 And 3 * Pi / 2 <= Eend) Or (Start > Eend And ((Start >= 3 * Pi / 2 And Eend >= 3 * Pi / 2) Or (Start <= 3 * Pi / 2 And Eend <= 3 * Pi / 2))) Then
    Ymax = y0 + Radius
Else
    Ymax = MaxTwoNum(y0 - Radius * Sin(Start), y0 - Radius * Sin(Eend))
    If (s < 0 Or e < 0) And Ymax < y0 Then Ymax = y0
End If
End Sub

'����Բ��������ֵ����Сֵ
Public Sub EllipseMaxMin(Xmax As Single, Xmin As Single, Ymax As Single, Ymin As Single, x0 As Single, y0 As Single, Radius As Single, ByVal Start As Double, ByVal Eend As Double, Aspect As Double)
'��Xmax   x=r*cos(��),,��k=0��ʱȡ���
Dim s As Double, e As Double
If Start = 0 And Eend = 0 Then
   If Aspect < 1 Then
      Xmax = x0 + Radius
      Xmin = x0 - Radius
      Ymax = y0 + Radius * Aspect
      Ymin = y0 - Radius * Aspect
   Else
      Xmax = x0 + Radius / Aspect
      Xmin = x0 - Radius / Aspect
      Ymax = y0 + Radius
      Ymin = y0 - Radius
   End If
   Exit Sub
End If
s = Start
e = Eend
Start = Abs(Start)
Eend = Abs(Eend)
If ((Start = 0 Or Eend = 2 * Pi) And (Start < Eend)) Or ((Start > Eend) And (Eend >= 0) And (Start <= 2 * Pi)) Then
   If Aspect < 1 Then
      Xmax = x0 + Radius
   Else
      Xmax = x0 + Radius / Aspect
   End If
Else
   If Aspect < 1 Then
      Xmax = MaxTwoNum(x0 + Radius * Cos(Start), x0 + Radius * Cos(Eend))
   Else
      Xmax = MaxTwoNum(x0 + Radius * Cos(Start) / Aspect, x0 + Radius * Cos(Eend) / Aspect)
   End If
   If (s < 0 Or e < 0) And Xmax < x0 Then Xmax = x0
End If
'��Xmin   x=r*cos(��),��x=180��ʱȡ��С
If ((Start < Eend) And (Eend >= Pi And Start <= Pi)) Or ((Start > Eend) And ((Start <= Pi And Eend <= Pi) Or (Start >= Pi And Eend >= Pi))) Then
   If Aspect < 1 Then
      Xmin = x0 - Radius
   Else
      Xmin = x0 - Radius / Aspect
   End If
Else
   If Aspect < 1 Then
      Xmin = MinTwoNum(x0 + Radius * Cos(Start), x0 + Radius * Cos(Eend))
   Else
      Xmin = MaxTwoNum(x0 + Radius * Cos(Start) / Aspect, x0 + Radius * Cos(Eend) / Aspect)
   End If
   If (s < 0 Or e < 0) And Xmin > x0 Then Xmin = x0
End If
'��Ymin   y=r*sin(��)  ,��K=90ʱȡ���K=270��ʱȡ��С
If (Start < Eend And Start <= Pi / 2 And Eend >= Pi / 2) Or (Start > Eend And ((Start >= Pi / 2 And Eend >= Pi / 2) Or (Start <= Pi / 2 And Eend <= Pi / 2))) Then
   If Aspect > 1 Then
      Ymin = y0 - Radius
   Else
      Ymin = y0 - Radius * Aspect
   End If
Else
   If Aspect > 1 Then
      Ymin = MinTwoNum(y0 - Radius * Sin(Start), y0 - Radius * Sin(Eend))
   Else
      Ymin = MinTwoNum(y0 - Aspect * Radius * Sin(Start), y0 - Radius * Sin(Eend) * Aspect)
   End If
   If (s < 0 Or e < 0) And Ymin > y0 Then Ymin = y0
End If
'��Ymax
If (Start < Eend And Start <= 3 * Pi / 2 And 3 * Pi / 2 <= Eend) Or (Start > Eend And ((Start >= 3 * Pi / 2 And Eend >= 3 * Pi / 2) Or (Start <= 3 * Pi / 2 And Eend <= 3 * Pi / 2))) Then
   If Aspect > 1 Then
      Ymax = y0 + Radius
   Else
      Ymax = y0 + Radius * Aspect
   End If
Else
   If Aspect > 1 Then
      Ymax = MaxTwoNum(y0 - Radius * Sin(Start), y0 - Radius * Sin(Eend))
   Else
      Ymax = MaxTwoNum(y0 - Aspect * Radius * Sin(Start), y0 - Radius * Sin(Eend) * Aspect)
   End If
   If (s < 0 Or e < 0) And Ymax < y0 Then Ymax = y0
End If
End Sub

'��֪���ߵĽ�,�󵱽�Angleʱ�����ϵĵ�(x,y)
Public Function AnglePointInArc(Angle As Double, CT As CircleType, �����ϵĵ�x As Single, �����ϵĵ�y As Single) As Boolean
       With CT
           If .Aspect = 0 Then   'Բ,Բ��,����
              �����ϵĵ�x = .x0 + .Radius * Cos(Angle)
              �����ϵĵ�y = .y0 - .Radius * Sin(Angle) 'Y�ᷴ��
           Else '��Բ
               If .Aspect < 1 Then
                  �����ϵĵ�x = .x0 + .Radius * Cos(Angle)
                  �����ϵĵ�y = .y0 - .Radius * .Aspect * Sin(Angle) 'Y�ᷴ��
               Else
                  �����ϵĵ�x = .x0 + .Radius * Cos(Angle) / .Aspect
                  �����ϵĵ�y = .y0 - .Radius * Sin(Angle) 'Y�ᷴ��
               End If
           End If
           
           If .Start = 0 And .end = 0 Then
              AnglePointInArc = True
           Else
              If Abs(.Start) <= Abs(.end) Then
                 If Angle >= Abs(.Start) And Angle <= Abs(.end) Then
                    AnglePointInArc = True
                 Else
                    AnglePointInArc = False
                 End If
              Else
                 If Angle <= Abs(.Start) And Angle >= Abs(.end) Then
                    AnglePointInArc = True
                 Else
                    AnglePointInArc = False
                 End If
              End If
           End If
           
        End With
        
End Function

'���㵽Բ������
'����ֵ:
'0Ϊû������
Public Function TanLineToArcPoint(Pointx As Single, Pointy As Single, Tcircle As CircleType, ReturnPoint1 As point, ReturnPoint2 As point) As Integer  '����
Dim xx As Single, yy As Single, a As Double, p As point, A1 As Double, A3 As Double, k As Double
       xx = TwoPointDirection(Pointx, Pointy, Tcircle.x0, Tcircle.y0) '�㵽Բ�ĵľ���
       If xx < Tcircle.Radius Then TanLineToArcPoint = 0: Exit Function 'û���е�
       If xx = Tcircle.Radius Then '�õ�Ϊ�е�
          ReturnPoint1.x = Pointx
          ReturnPoint1.y = Pointy
          ReturnPoint2.x = Pointx
          ReturnPoint2.y = Pointy
          TanLineToArcPoint = 1
          Exit Function
       End If
       yy = Sqr(xx ^ 2 - Tcircle.Radius ^ 2) '�㵽�е�ĳ���
       a = Pi - Angle(Tcircle.Radius, yy)  '�뾶��㵽Բ���߶εļн�
       A1 = Angle(Tcircle.x0 - Pointx, Tcircle.y0 - Pointy) '�㵽Բ�ĵ��߶εĽǶ�
       A3 = A1 - a '
       With Tcircle
            If .Aspect = 0 Then
                If .Start = 0 And .end = 0 Then 'Բ
                   TanLineToArcPoint = 1
                ElseIf (Abs(.Start) < Abs(.end) And Abs(.Start) < A3 And Abs(.end) > A3) _
                     Or (Abs(.Start) > Abs(.end) And Abs(.end) > 0 And Abs(.Start) > 0 _
                     And (Abs(.Start) > A3 Or (Abs(.end) < A3 And A3 < 2 * Pi))) Then  'Բ��������
                     TanLineToArcPoint = 1
                End If
                ReturnPoint1.x = Tcircle.x0 + Tcircle.Radius * Cos(A3)
                ReturnPoint1.y = Tcircle.y0 - Tcircle.Radius * Sin(A3)
                'AnglePointInArc A3, Tcircle, ReturnPoint1.x, ReturnPoint1.y
            Else '��Բ
            
            End If
       End With
       A3 = A1 + a
       With Tcircle
            If .Aspect = 0 Then
                If .Start = 0 And .end = 0 Then 'Բ
                   If TanLineToArcPoint Then
                      TanLineToArcPoint = 3
                   Else
                      TanLineToArcPoint = 2
                   End If
                ElseIf (Abs(.Start) < Abs(.end) And Abs(.Start) < A3 And Abs(.end) > A3) _
                     Or (Abs(.Start) > Abs(.end) And Abs(.end) > 0 And Abs(.Start) > 0 _
                     And (Abs(.Start) > A3 Or (Abs(.end) < A3 And A3 < 2 * Pi))) Then  'Բ��������
                       If TanLineToArcPoint Then
                          TanLineToArcPoint = 3
                       Else
                          TanLineToArcPoint = 2
                       End If
                End If
                ReturnPoint2.x = Tcircle.x0 + Tcircle.Radius * Cos(A3)
                ReturnPoint2.y = Tcircle.y0 - Tcircle.Radius * Sin(A3)
                'AnglePointInArc A3, Tcircle, ReturnPoint2.x, ReturnPoint2.y
            Else '��Բ
            
            End If
       End With
       
End Function


