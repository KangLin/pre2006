Attribute VB_Name = "math"
'本模块为数学函数
'作者:康林

Option Explicit

'Private Type MissPoint
'        x As Single
'        y As Single
'        End Type

'弧度转换为角度
Public Function ArcToAngle(θ As Double) As Double
       ArcToAngle = 360 * θ / (2 * Pi)
End Function

'角度转化为弧度
Public Function AngleToArc(θ As Double) As Double
       AngleToArc = 2 * Pi * θ / 360
End Function

'绕任一点旋转
Public Sub RoundPoint(x As Single, y As Single, 要旋转的点x1 As Single, 要旋转的点y1 As Single, 定点x0 As Single, 定点y0 As Single, θ As Double)
Dim xx, yy
    '把座标原点移到(定点x0,定点y0),点(要旋转的点x1,要旋转的点y1)的座标变为(xx,yy)
    xx = 要旋转的点x1 - 定点x0
    yy = 要旋转的点y1 - 定点y0
    '任意点绕定点(定点x0,定点y0)旋转角度θ，θ为弧度
    x = xx * Cos(θ) - yy * Sin(θ)
    y = xx * Sin(θ) + yy * Cos(θ)
    '再把座标移回到原点
    x = x + 定点x0
    y = y + 定点y0
End Sub

'              /(x,y)
'             /
'            /
'   (x0,y0) /_θ_____(x0+r,y0)
'                r
'已知水平边的长度,顶点(X0,Y0)和夹角求一点
Public Sub ArcRoundpoint(x As Single, y As Single, x0 As Single, y0 As Single, r As Single, θ As Double)
       RoundPoint x, y, x0 + r, y0, x0, y0, θ
End Sub

'求角K绕一点(X0,Y0)放置a后的角K`
Public Function AngleroundPoint(b As Double, k As Double) As Double
Dim a As Double
a = b + k
If a > 2 * Pi Then a = a - 2 * Pi
AngleroundPoint = a
End Function

'求一点(x0,y0)以任一条直线(x1,y1)-(x2,y2)镜像为(x,y)
Public Sub Mirror(x As Single, y As Single, ByVal x0 As Single, ByVal y0 As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single)
Dim θ As Double, xx, yy
    If X2 - X1 <> 0 Then
       θ = Atn((Y2 - Y1) / (X2 - X1)) * 2
       xx = x0 * Cos(θ) + y0 * Sin(θ) + X1 * (1 - Cos(θ)) - Y1 * Sin(θ)
       yy = x0 * Sin(θ) - y0 * Cos(θ) + Y1 * (1 + Cos(θ)) - X1 * Sin(θ)
    Else
       xx = x0 - 2 * (x0 - X1)
       yy = y0
    End If
    x = xx
    y = yy
End Sub

'求角θ以任一条直线(X1,Y1)-(x2,y2)的镜像θ`
Public Function AngleMirror(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, θ As Double) As Double
Dim xx As Single, yy As Single, a As Double
xx = X2 - X1
yy = Y2 - Y1
a = Angle(xx, yy)
If a > Pi Then a = a - Pi
a = 2 * a - θ
If a < 0 Then a = 2 * Pi + a
AngleMirror = a
End Function

'座标原点平移到定点(x1,y1)
Public Sub movetopoint(x As Single, y As Single, X1 As Single, Y1 As Single)
       x = x - X1
       y = y - Y1
End Sub
 
'把座标从点(x1,y1)移回原点
Public Sub movecomezieo(x As Single, y As Single, X1 As Single, Y1 As Single)
       x = x + X1
       y = y + Y1
End Sub

'比例变换,点(X,Y)相对(X0,y0)作比例因子(xb,yb)的比例变换得到变换后的点(x,y)
Public Sub RatioChange(x As Single, y As Single, x0 As Single, y0 As Single, xb As Single, yb As Single)
Dim xx As Single, yy As Single
    xx = x - x0
    yy = y - y0
    x = xb * xx
    y = yb * yy
    x = x + x0
    y = y + y0
End Sub

'圆,圆弧,扇形,椭圆的比例变换
Public Sub RatioChangeArc(Radius As Single, Start As Double, Eend As Double, Aspect As Double, ByVal xb As Single, ByVal yb As Single)
Dim xxb As Long, yyb As Long, f
    xxb = xb
    yyb = yb
    xb = Abs(xb)
    yb = Abs(yb)
    If Aspect = 0 Then  '圆,圆弧,扇形
       If xb > yb Then
          Aspect = yb / xb
          Radius = Radius * xb
       Else
          Aspect = yb / xb
          Radius = Radius * yb
       End If
    Else '椭圆
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

'两条二次曲线的交点
Public Function TwoCircleMissPoint(Circle1 As CircleType, Circle2 As CircleType, Point1 As point, Point2 As point, Point3 As point, POint4 As point)
Dim r As Single
    r = TwoPointDirection(Circle1.x0, Circle1.y0, Circle2.x0, Circle2.y0)
    If r > Circle1.Radius + Circle2.Radius Then
       TwoCircleMissPoint = 0
       Exit Function
    End If
    
    TwoCircleMissPoint = 0
End Function

'两直线的交点
Public Function TwoLineMissPoint1(Onelinex As Single, Oneliney As Single, Onelinex1 As Single, Oneliney1 As Single, Twolinex As Single, Twoliney As Single, Twolinex1 As Single, Twoliney1 As Single) As point
       Dim k1 As Single, k2 As Single
  With TwoLineMissPoint
       If (Twolinex - Twolinex1 <> 0) And (Onelinex - Onelinex1 <> 0) Then
          k1 = (Oneliney - Oneliney1) / (Onelinex - Onelinex1)
          k2 = (Twoliney - Twoliney1) / (Twolinex - Twolinex1)
          If k1 = k2 Then
             Exit Function  '平行
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

'两直线的交点
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
       If (Twolinex - Twolinex1 <> 0) And (Onelinex - Onelinex1 <> 0) Then '一般情况
          k1 = (Oneliney - Oneliney1) / (Onelinex - Onelinex1)
          k2 = (Twoliney - Twoliney1) / (Twolinex - Twolinex1)
          If k1 = k2 Then
             TwoLineMissPoint = 1
             Exit Function  '平行
          End If
            .x = ((Twoliney - Oneliney) + k1 * Onelinex - k2 * Twolinex) / (k1 - k2)
            .y = k1 * (.x - Onelinex) + Oneliney
       End If
       '特殊情况
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
 '是否在线段内
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

'直线与二次曲线的的交点
'返回值:
'0没有交点
'1为交点在point1中,'是切点时,两值相同
'2 为交点在point2中
'3为两交点都有效
'4两交点无效
Public Function LineMissCirclePoint(line As linetype, Arc As CircleType, Point1 As point, Point2 As point) As Long
Dim r As Single, k As Long, a As Double

    r = PointToLineDirection(Arc.x0, Arc.y0, line.X1, line.Y1, line.X2, line.Y2)
    If r > Arc.Radius Then
       LineMissCirclePoint = 0
       Exit Function
    End If
    
    k = PointToLineVerticalPoint(Point1.x, Point1.y, Arc.x0, Arc.y0, line.X1, line.Y1, line.X2, line.Y2) '求切点
    If r = Arc.Radius Then '切线
       With Arc
          If k Then
             If .Start = 0 And .end = 0 And .Aspect = 0 Then '圆
                 LineMissCirclePoint = 1
             Else
                 If .Aspect = 0 Then '圆弧,扇形
                    a = Angle(Point1.x - .x0, Point1.y - .y0)
                    If Abs(.Start) > Abs(.end) Then
                       If a > Abs(.Start) And a < Abs(.end) Then LineMissCirclePoint = 1
                    Else
                        If a < Abs(.end) Or (a < 2 * Pi And a > Abs(.Start)) Then LineMissCirclePoint = 1
                    End If
                 Else '椭圆
                 
                 End If
             End If
          End If
       End With
       Point2 = Point1 '是切点时,两值相同
       Exit Function
    End If
    
    '交线
    k = PointOnLineOfLong(Point1, Point2, Point1, Sqr(Arc.Radius ^ 2 - r ^ 2), line)
    If k = 0 Or k = 4 Then '交点无效
       LineMissCirclePoint = k
       Exit Function
    Else
       With Arc
            If .Start = 0 And .end = 0 And .Aspect = 0 Then ' 圆
               LineMissCirclePoint = k
            Else
               If .Aspect = 0 Then '圆弧,扇形
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
               Else '椭圆
               
               End If
            End If
       End With
    End If
    
End Function

'已知一直线和直线上的点,求相对点长度为r的直线上的点
'参数:
'Qpoint1,Qpoint2为所求的值
'Point0 为直线上的一点
'返回值:
'0为不存在
'1为只Qpoint1中的值在线段上
'2为只有Qpont2中的值在线段上
'3为两者中的值都在线段上
'4为两者中的值都不在线段上
Public Function PointOnLineOfLong(QPoint1 As point, QPoint2 As point, Point0 As point, d As Single, line As linetype) As Long
Dim k As Single, point As point
point = Point0

       With line
            If .X1 - .X2 = 0 Or .Y1 - .Y2 = 0 Then '特殊情况
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
            Else '一般情况
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

'点到直线的垂点,如果交点在线段内返回真,否则返回假
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

'点到直线的垂点,返回值为真,则点在线段上,否则,不在线段上,即在线段外
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

'点到直线的距离
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

'两点间的距离
Public Function TwoPointDirection(x As Single, y As Single, X1 As Single, Y1 As Single) As Single
Dim d, m
       d = x - X1
       m = y - Y1
       TwoPointDirection = Sqr(d ^ 2 + m ^ 2)
End Function

'点(X!,Y!)绕点(X0,Y0)旋转90度得到的新点(X,Y)
Public Sub 旋转90度(x As Single, y As Single, X1 As Single, Y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = X1 - x0
       yy = Y1 - y0
       x = -yy
       y = xx
       x = x + x0
       y = y + y0
End Sub

'点(X!,Y!)绕点(X0,Y0)旋转-90度得到的新点(X,Y)
Public Sub 旋转负90度(x As Single, y As Single, X1 As Single, Y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = X1 - x0
       yy = Y1 - 0
       x = yy
       y = -xx
       x = x + x0
       y = y + y0
End Sub

'点(X!,Y!)绕点(X0,Y0)旋转180度得到的新点(X,Y)
Public Sub 旋转180度(x As Single, y As Single, X1 As Single, Y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = X1 - x0
       yy = Y1 - 0
       x = -xx
       y = yy
       x = x + x0
       y = y + y0
End Sub

'已知正三角形的两顶点求第三个顶点
Public Sub SamethreeThirdVertex(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single)
'             1
'             /\
'            /  \
'           /    \
'          /      \
'        2/________\3
Dim xx As Single, yy As Single
            '把座标移到第一点
            xx = X2 - X1
            yy = Y2 - Y1
            '把第二点围绕第一点逆时针转60度
            x3 = xx / 2 - yy * Sin(Pi / 3)
            y3 = xx * Sin(Pi / 3) + yy / 2
            '再把座标移回原点
            x3 = x3 + X1
            y3 = y3 + Y1
End Sub


'已知正方形的两顶点求另外两点已知(X1,Y1)和(X2,Y2)
Public Sub samerectanglethreeandforupiont(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single)
Dim xx As Single, yy As Single
'    4 _________3
'     |        |
'     |        |
'     |        |
'    1---------- 2
        '把座标移到第一点
       xx = X2 - X1
       yy = Y2 - Y1
       '把第二点绕第一点转90度,得到第四点
       x4 = -yy
       y4 = xx
       '把座标移回到原点,得到第四点
       x4 = x4 + X1
       y4 = y4 + Y1
       '把座标移到第四点
       xx = X1 - x4
       yy = Y1 - y4
       '把第一点绕第四点转90度
       x3 = -yy
       y3 = xx
       '把座标移回到原点,得到第三点
       x3 = x3 + x4
       y3 = y3 + y4
End Sub

'已知正六边形的两点求另外四点已知(X1,Y1)和(X2,Y2)
'       5 ______ 4
'        /      \
'     6 /        \ 3
'       \        /
'        \      /
'       1 ------  2
Public Sub sixegdefour(X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single)
Dim xx As Single, yy As Single
          '把座标移到第一点
          xx = X2 - X1
          yy = Y2 - Y1
          '旋转120度,即2*pi/3
          x6 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y6 = xx * Sin(2 * Pi / 3) - yy / 2
           '把座标移回原点
          x6 = x6 + X1
          y6 = y6 + Y1
          '把痤标移到第六点
          xx = X1 - x6
          yy = Y1 - y6
          '旋转120度
          x5 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y5 = xx * Sin(2 * Pi / 3) - yy / 2
          '把座标移回原点
          x5 = x5 + x6
          y5 = y5 + y6
          '把座标移到第五点
          xx = x6 - x5
          yy = y6 - y5
          '旋转120度
          x4 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y4 = xx * Sin(2 * Pi / 3) - yy / 2
          '把座标称回到原点
          x4 = x4 + x5
          y4 = y4 + y5
          '把座标移到第四点
          xx = x5 - x4
          yy = y5 - y4
          '旋转120度
          x3 = -xx / 2 - yy * Sin(2 * Pi / 3)
          y3 = xx * Sin(2 * Pi / 3) - yy / 2
          '把座标称回到原点
          x3 = x3 + x4
          y3 = y3 + y4
End Sub

'求以原点为中心的旋转角,已考虑了特殊情况
'是与水平轴(X轴)的夹角,范围(0 -- 2Π)
'xx,yy 分别为定点到原点的矢量x0x1,y0y1
'即xx=x1-x0
'  yy=y1-y0
Public Function Angle(xx, yy) As Double  '求以原点为中心的旋转角
Dim rad As Double
    '计算结束角,注意Y轴不同(向下为正)
    If xx = 0 And yy = 0 Then Angle = 0: Exit Function '当起点时,即鼠标刚按下时,旋转角是0度,不是270度,因为用下面公式求的是270度
    If xx > 0 And yy > 0 Then
       rad = 8 * Rfzghr - Atn(yy / xx)  '范围 (3*PI/2--2*PI)
    Else
       If xx > 0 And yy <= 0 Then
          rad = Abs(Atn(yy / xx)) '范围 [0--PI/2)
       Else
          If xx < 0 And yy >= 0 Then
             rad = Abs(Atn(yy / xx)) + 4 * Rfzghr '范围 [PI--3*PI/2)
          Else
             If xx < 0 And yy < 0 Then
                 rad = 4 * Rfzghr - Atn(yy / xx) '范围 (PI/2--PI)
             End If
          End If
       End If
     End If
     If xx = 0 And yy > 0 Then Angle = Pi / 2: Exit Function 'Y轴反向
     If xx = 0 And yy < 0 Then rad = 3 * Pi / 2
     Angle = rad
End Function

'求一点是否在一矩形区域内
Public Function pointinrectangle(x As Single, y As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single) As Boolean
       If x <= MaxTwoNum(X1, X2) And x >= MinTwoNum(X1, X2) And y <= MaxTwoNum(Y1, Y2) And y >= MinTwoNum(Y1, Y2) Then
          pointinrectangle = True
          Exit Function
       End If
          pointinrectangle = False
End Function

'求两个数中的小的数
Public Function MinTwoNum(X1 As Single, X2 As Single) As Single
       If X1 >= X2 Then
          MinTwoNum = X2
       Else
          MinTwoNum = X1
       End If
End Function

'求两个数中的大的数
Public Function MaxTwoNum(X1 As Single, X2 As Single) As Single
       If X1 >= X2 Then
          MaxTwoNum = X1
       Else
          MaxTwoNum = X2
       End If
End Function

'求三个数中的最小的数
Public Function MinThreeNum(X1 As Single, X2 As Single, x3 As Single) As Single
       MinThreeNum = MinTwoNum(MinTwoNum(X1, X2), x3)
End Function

'求三个数中的取大的数
Public Function MaxThreeNum(X1 As Single, X2 As Single, x3 As Single) As Single
       MaxThreeNum = MaxTwoNum(MaxTwoNum(X1, X2), x3)
End Function

'制图区的缩放
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
            user.Scrollbar Abs(.left), Abs(.top)  '置滚动条
            Exit Sub
zoomloop:    '当出错时的处理
               .top = top
               .left = .left
               .Width = w
               .Height = h
               .Scalewidth = sw
               .ScaleHeight = sh
             user.Scrollbar Abs(.left), Abs(.top)  '置滚动条
       End With
End Sub

'处理字符,没写完
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

'求圆弧,扇形的最大,最小值
Public Sub ArcMaxMin(Xmax As Single, Ymax As Single, Xmin As Single, Ymin As Single, x0 As Single, y0 As Single, Radius As Single, ByVal Start As Double, ByVal Eend As Double)
Dim s As Double, e As Double
s = Start
e = Eend
Start = Abs(Start)
Eend = Abs(Eend)
'求Xmax   x=r*cos(θ),,当k=0度时取最大
If ((Start = 0 Or Eend = 2 * Pi) And (Start < Eend)) Or ((Start > Eend) And (Eend >= 0) And (Start <= 2 * Pi)) Then
   Xmax = x0 + Radius
Else
      Xmax = MaxTwoNum(x0 + Radius * Cos(Start), x0 + Radius * Cos(Eend))
      If (s < 0 Or e < 0) And Xmax < x0 Then Xmax = x0
End If
'求Xmin   x=r*cos(θ),发x=180度时取最小
If ((Start < Eend) And (Eend >= Pi And Start <= Pi)) Or ((Start > Eend) And ((Start <= Pi And Eend <= Pi) Or (Start >= Pi And Eend >= Pi))) Then
   Xmin = x0 - Radius
Else
      Xmin = MinTwoNum(x0 + Radius * Cos(Start), x0 + Radius * Cos(Eend))
      If (s < 0 And e < 0) And Xmin > x0 Then Xmin = x0
End If
'求Ymin   y=r*sin(θ)  ,当K=90时取最大K=270度时取最小
If (Start < Eend And Start <= Pi / 2 And Eend >= Pi / 2) Or (Start > Eend And ((Start >= Pi / 2 And Eend >= Pi / 2) Or (Start <= Pi / 2 And Eend <= Pi / 2))) Then
    Ymin = y0 - Radius
Else
       Ymin = MinTwoNum(y0 - Radius * Sin(Start), y0 - Radius * Sin(Eend))
        If (s < 0 And e < 0) And Ymin > y0 Then Ymin = y0
End If
'求Ymax
If (Start < Eend And Start <= 3 * Pi / 2 And 3 * Pi / 2 <= Eend) Or (Start > Eend And ((Start >= 3 * Pi / 2 And Eend >= 3 * Pi / 2) Or (Start <= 3 * Pi / 2 And Eend <= 3 * Pi / 2))) Then
    Ymax = y0 + Radius
Else
    Ymax = MaxTwoNum(y0 - Radius * Sin(Start), y0 - Radius * Sin(Eend))
    If (s < 0 Or e < 0) And Ymax < y0 Then Ymax = y0
End If
End Sub

'求椭圆弧的最在值和最小值
Public Sub EllipseMaxMin(Xmax As Single, Xmin As Single, Ymax As Single, Ymin As Single, x0 As Single, y0 As Single, Radius As Single, ByVal Start As Double, ByVal Eend As Double, Aspect As Double)
'求Xmax   x=r*cos(θ),,当k=0度时取最大
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
'求Xmin   x=r*cos(θ),发x=180度时取最小
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
'求Ymin   y=r*sin(θ)  ,当K=90时取最大K=270度时取最小
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
'求Ymax
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

'已知曲线的角,求当角Angle时曲线上的点(x,y)
Public Function AnglePointInArc(Angle As Double, CT As CircleType, 曲线上的点x As Single, 曲线上的点y As Single) As Boolean
       With CT
           If .Aspect = 0 Then   '圆,圆弧,扇形
              曲线上的点x = .x0 + .Radius * Cos(Angle)
              曲线上的点y = .y0 - .Radius * Sin(Angle) 'Y轴反向
           Else '椭圆
               If .Aspect < 1 Then
                  曲线上的点x = .x0 + .Radius * Cos(Angle)
                  曲线上的点y = .y0 - .Radius * .Aspect * Sin(Angle) 'Y轴反向
               Else
                  曲线上的点x = .x0 + .Radius * Cos(Angle) / .Aspect
                  曲线上的点y = .y0 - .Radius * Sin(Angle) 'Y轴反向
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

'定点到圆的切线
'返回值:
'0为没有切线
Public Function TanLineToArcPoint(Pointx As Single, Pointy As Single, Tcircle As CircleType, ReturnPoint1 As point, ReturnPoint2 As point) As Integer  '切线
Dim xx As Single, yy As Single, a As Double, p As point, A1 As Double, A3 As Double, k As Double
       xx = TwoPointDirection(Pointx, Pointy, Tcircle.x0, Tcircle.y0) '点到圆心的距离
       If xx < Tcircle.Radius Then TanLineToArcPoint = 0: Exit Function '没有切点
       If xx = Tcircle.Radius Then '该点为切点
          ReturnPoint1.x = Pointx
          ReturnPoint1.y = Pointy
          ReturnPoint2.x = Pointx
          ReturnPoint2.y = Pointy
          TanLineToArcPoint = 1
          Exit Function
       End If
       yy = Sqr(xx ^ 2 - Tcircle.Radius ^ 2) '点到切点的长度
       a = Pi - Angle(Tcircle.Radius, yy)  '半径与点到圆心线段的夹角
       A1 = Angle(Tcircle.x0 - Pointx, Tcircle.y0 - Pointy) '点到圆心的线段的角度
       A3 = A1 - a '
       With Tcircle
            If .Aspect = 0 Then
                If .Start = 0 And .end = 0 Then '圆
                   TanLineToArcPoint = 1
                ElseIf (Abs(.Start) < Abs(.end) And Abs(.Start) < A3 And Abs(.end) > A3) _
                     Or (Abs(.Start) > Abs(.end) And Abs(.end) > 0 And Abs(.Start) > 0 _
                     And (Abs(.Start) > A3 Or (Abs(.end) < A3 And A3 < 2 * Pi))) Then  '圆弧和扇形
                     TanLineToArcPoint = 1
                End If
                ReturnPoint1.x = Tcircle.x0 + Tcircle.Radius * Cos(A3)
                ReturnPoint1.y = Tcircle.y0 - Tcircle.Radius * Sin(A3)
                'AnglePointInArc A3, Tcircle, ReturnPoint1.x, ReturnPoint1.y
            Else '椭圆
            
            End If
       End With
       A3 = A1 + a
       With Tcircle
            If .Aspect = 0 Then
                If .Start = 0 And .end = 0 Then '圆
                   If TanLineToArcPoint Then
                      TanLineToArcPoint = 3
                   Else
                      TanLineToArcPoint = 2
                   End If
                ElseIf (Abs(.Start) < Abs(.end) And Abs(.Start) < A3 And Abs(.end) > A3) _
                     Or (Abs(.Start) > Abs(.end) And Abs(.end) > 0 And Abs(.Start) > 0 _
                     And (Abs(.Start) > A3 Or (Abs(.end) < A3 And A3 < 2 * Pi))) Then  '圆弧和扇形
                       If TanLineToArcPoint Then
                          TanLineToArcPoint = 3
                       Else
                          TanLineToArcPoint = 2
                       End If
                End If
                ReturnPoint2.x = Tcircle.x0 + Tcircle.Radius * Cos(A3)
                ReturnPoint2.y = Tcircle.y0 - Tcircle.Radius * Sin(A3)
                'AnglePointInArc A3, Tcircle, ReturnPoint2.x, ReturnPoint2.y
            Else '椭圆
            
            End If
       End With
       
End Function


