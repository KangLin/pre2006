Attribute VB_Name = "draw"
'本模块为制图函数
'作者:康林

Option Explicit

'突出显示点
Public Sub showpoint(x As Single, y As Single, object As Object, Color As ColorConstants)
Dim xx As Long, yy As Single
Dim scol As ColorConstants, ftype As Integer
ftype = object.FillStyle '保存填充类型
scol = object.FillColor  '保存填充颜色
 '点的大小,下面两值受user.snapefield的影响
xx = snapefield / 2
yy = snapefield / 2

       object.FillStyle = 0
       object.FillColor = Color
       object.Line (x - xx, y - yy)-(x + xx, y + yy), Color, B
       object.FillStyle = ftype
       object.FillColor = scol
       
End Sub

'直线
Public Sub SingleLine(Button As Integer, x As Single, y As Single, Color As ColorConstants, object As Object)
     Dim mode
     
     If Button = VBRUN.vbLeftButton Or (fMainForm.TCurrentOperist = "连画线" And DrawFlag = 2) Then
        mode = object.DrawMode
        object.DrawMode = 7
        object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
        object.Line (Mouseleftdownx, Mouseleftdowny)-(x, y), Color
        Mousepausex = x
        Mousepausey = y
        object.DrawMode = mode
     End If
End Sub

'参考直线(单线)
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
    '清除原直线
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

'矩形
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

'三角形
Public Sub Three(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, Tline As linetype)
Dim mode
       mode = object.DrawMode
       object.DrawMode = 7
       Select Case DrawFlag
              Case 1
                   draw.SingleLine Button, x, y, Color, object
              Case 2
                   Select Case fMainForm.TCurrentOperist
                          Case "三角形"
                               With Tline
                                    '消除
                                    object.Line (.X1, .Y1)-(Mousepausex, Mousepausey), Color
                                    object.Line (.X2, .Y2)-(Mousepausex, Mousepausey), Color
                                    '重画
                                    object.Line (.X1, .Y1)-(x, y), Color
                                    object.Line (.X2, .Y2)-(x, y), Color
                               End With
                               Mousepausex = x
                               Mousepausey = y
                          Case "等边三角形"
                               '消除
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
                               ''重画
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

'正三角形
Public Sub 正三角形(object As Object, x As Single, y As Single, Button As Integer, Color As ColorConstants, flag As Boolean)
Dim mode, xx, yy, X1, X2, Y2, Y1
mode = object.DrawMode
object.DrawMode = 7
If Button = VBRUN.vbLeftButton Then
    '座标移到第一点
    xx = Mousepausex - Mouseleftdownx
    yy = Mousepausey - Mouseleftdowny
    '把第二点围绕第一点逆时针转60度
    X1 = xx / 2 - yy * Sin(Pi / 3)
    Y1 = xx * Sin(Pi / 3) + yy / 2
    '再把座标移回原点
    xx = X1 + Mouseleftdownx
    yy = Y1 + Mouseleftdowny
    object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
    object.Line -(xx, yy), Color
    object.Line -(Mouseleftdownx, Mouseleftdowny), Color
  If flag Then
    '座标移到第一点
    xx = x - Mouseleftdownx
    yy = y - Mouseleftdowny
    '把第二点围绕第一点逆时针转60度
    X1 = xx / 2 - yy * Sin(Pi / 3)
    Y1 = xx * Sin(Pi / 3) + yy / 2
    '再把座标移回原点
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

'正方形
Public Sub 正方形(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, flag As Boolean)
Dim xx, yy, x3 As Single, y3 As Single, x4 As Single, y4 As Single, mode
mode = object.DrawMode
object.DrawMode = 7
If Button = VBRUN.vbLeftButton Then
       math.samerectanglethreeandforupiont Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey, x3, y3, x4, y4
       object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
       object.Line -(x3, y3), Color
       object.Line -(x4, y4), Color
       object.Line -(Mouseleftdownx, Mouseleftdowny), Color
正方形loop:
  If flag Then
       math.samerectanglethreeandforupiont Mouseleftdownx, Mouseleftdowny, x, y, x3, y3, x4, y4
       '把座标移到第一点
       'xx = x - user.mouseleftdownx
       'yy = y - user.mouseleftdowny
       '把第二点绕第一点转90度,得到第三点
       'x3 = -yy
       'y3 = xx
       '把座标移回到原点,得到第三点
       'x3 = x3 + user.mouseleftdownx
       'y3 = y3 + user.mouseleftdowny
       '把座标移到第三点
       'xx = user.mouseleftdownx - x3
       'yy = user.mouseleftdowny - y3
       '把第一点绕第三点转90度
       'x4 = -yy
       'y4 = xx
       '把座标移回到原点
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

'正六边形
Public Sub 正六边形(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, flag As Boolean)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single, modec, xx As Single, yy As Single
Dim mode
mode = object.DrawMode
object.DrawMode = 7
If Button = VBRUN.vbLeftButton Then
                    '把座标移到第一点
          'xx = user.mousepausex - user.mouseleftdownx
          'yy = user.mousepausey - user.mouseleftdowny
          '旋转120度,即2*pi/3
          'x3 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y3 = xx * Sin(2 * user.pi / 3) - yy / 2
           '把座标移回原点
          'x3 = x3 + user.mouseleftdownx
          'y3 = y3 + user.mouseleftdowny
          '把痤标移到第三点
          'xx = user.mouseleftdownx - x3
          'yy = user.mouseleftdowny - y3
          '旋转120度
          'x4 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y4 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标移回原点
          'x4 = x4 + x3
          'y4 = y4 + y3
          '把座标移到第四点
          'xx = x3 - x4
          'yy = y3 - y4
          '旋转120度
          'x5 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y5 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标称回到原点
          'x5 = x5 + x4
          'y5 = y5 + y4
          '把座标移到第五点
          'xx = x4 - x5
          'yy = y4 - y5
          '旋转120度
          'x6 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y6 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标称回到原点
          'x6 = x6 + x5
          'y6 = y6 + y5
          math.sixegdefour Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey, x3, y3, x4, y4, x5, y5, x6, y6
          object.Line (Mouseleftdownx, Mouseleftdowny)-(Mousepausex, Mousepausey), Color
          object.Line -(x3, y3), Color
          object.Line -(x4, y4), Color
          object.Line -(x5, y5), Color
          object.Line -(x6, y6), Color
          object.Line -(Mouseleftdownx, Mouseleftdowny), Color
          '把座标移到第一点
          'xx = x - user.mouseleftdownx
          'yy = y - user.mouseleftdowny
          '旋转120度,即2*pi/3
          'x3 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y3 = xx * Sin(2 * user.pi / 3) - yy / 2
           '把座标移回原点
          'x3 = x3 + user.mouseleftdownx
          'y3 = y3 + user.mouseleftdowny
          '把痤标移到第三点
          'xx = user.mouseleftdownx - x3
          'yy = user.mouseleftdowny - y3
          '旋转120度
          'x4 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y4 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标移回原点
          'x4 = x4 + x3
          'y4 = y4 + y3
          '把座标移到第四点
          'xx = x3 - x4
          'yy = y3 - y4
          '旋转120度
          'x5 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y5 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标称回到原点
          'x5 = x5 + x4
          'y5 = y5 + y4
          '把座标移到第五点
          'xx = x4 - x5
          'yy = y4 - y5
          '旋转120度
          'x6 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          'y6 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标称回到原点
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

'圆
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

'参考圆,定点与动圆心
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
If flag Then '消除原图形
   rad = Sqr((Mouseleftdownx - Mousepausex) ^ 2 _
          + (Mouseleftdowny - Mousepausey) ^ 2)
   object.Circle (Mouseleftdownx, Mouseleftdowny), rad, Color
   '显示
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

'圆弧
Public Sub Arc(object As Object, Button As Integer, x As Single, y As Single, Color As ColorConstants, Tcircle As CircleType)
Dim xx, yy, mode, rad As Double
       mode = object.DrawMode       '保存模式
       object.DrawMode = 7
       Select Case DrawFlag
              Case 1      '显示参考圆
                   SingleCircle Button, x, y, Color, object
              Case 2      '显示参考直线
                   '显示参考直线
                   object.Line (Tcircle.x0, Tcircle.y0)-(Mousepausex, Mousepausey), Color
                   object.Line (Tcircle.x0, Tcircle.y0)-(x, y), Color
                   Mousepausex = x
                   Mousepausey = y
              Case 3      '显示参考圆弧和参考直线
                   '参考直线
                   With Tcircle
                        object.Line (.x0, .y0)-(Mousepausex, Mousepausey), Color
                        object.Line (.x0, .y0)-(x, y), Color
                       '参考圆弧
                        object.DrawMode = VBRUN.vbXorPen
                        xx = Mousepausex - .x0
                        yy = Mousepausey - .y0
                        rad = math.Angle(xx, yy)   '求结束角
                        object.Circle (.x0, .y0), .Radius, Color, .Start, rad
                        xx = x - .x0
                        yy = y - .y0
                        rad = math.Angle(xx, yy)   '求结束角
                        object.Circle (.x0, .y0), .Radius, Color, .Start, rad
                   End With
                   Mousepausex = x
                   Mousepausey = y
       End Select
       
       mode = object.DrawMode      '恢复模式
End Sub

'椭圆
Public Sub Ellipse(object As Object, x As Single, y As Single, Button As Integer, Color As ColorConstants, Tcircle As CircleType)
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If
Dim asp, mode
       Select Case DrawFlag
              Case 1
                   draw.SingleCircle Button, x, y, Color, object
              Case 2
                   '离心率
                   With Tcircle
                        asp = (y - .y0) / .Radius
                        asp = Abs(asp)
                        mode = object.DrawMode
                        object.DrawMode = 7
                        object.Circle (.x0, .y0), .Radius, Color, , , Mousepausex
                        object.Circle (.x0, .y0), .Radius, Color, , , asp
                        Mousepausex = asp    '保存上次的离心率
                   End With
       End Select
End Sub

'已知三点画三角形
Public Sub drawthreeangle(object As Object, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, Color As ColorConstants)
       object.Line (X1, Y1)-(X2, Y2), Color
       object.Line -(x3, y3), Color
       object.Line -(X1, Y1), Color
End Sub

'已知四点画四边形
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

'已知两点画矩形
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

'已知六边形六点画六边形
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

Public Sub TiShiSelectRectangle(x, y, Button, Color As ColorConstants, flag As Boolean, object As Object) '用于区域选取的参考矩形
'flag用于是否是清除选取参考矩形
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
   '清除原造型矩形
   object.Line (Mousepausex, Mousepausey)-(Mouseleftdownx, Mouseleftdowny), Color, B
   If flag Then     '用于是否是清除选取参考矩形
      '显示矩形
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

'画标注线上的箭头
Public Function DrawArrow(object As Object, Color As ColorConstants, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, LStyle As Integer, RStyle As Integer, Size As Single, flag As Boolean, DimLineAngle As Double) As ArrowType
'右箭头,0为无箭头
'      ,1为满箭头(30度)
'      ,2为开口箭头(30度)
'      ,3为封闭..........
'......,4为满箭头(45度)
'......,5为开口艏头(45度)
'.......6为封闭箭头......
'......,7为短线段
'DimLineAngle 为标注线的角度
'Public Type ArrowType '箭头
'       X3 As Single        '       (x3,y3)            (x5,y5)
'       Y3 As Single        '      /                      \
'       X4 As Single      '(x1,y1)/________________________\ (x2,y2)
'       Y4 As Single        '     \                        /
'       X5 As Single        '      \ (x4,y4)              /(x6,y6)
'       Y5 As Single
'       X6 As Single
'       Y6 As Single
'       End Type

'当flag为假时,不画图形,只计算值

Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, a As Double
Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single

   Select Case LStyle
          Case 2, 3, 1
               a = DimLineAngle + AngleToArc(30) 'Y轴反向
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
               a = DimLineAngle + AngleToArc(45) 'Y轴反向
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
               a = DimLineAngle + AngleToArc(45 + 90) 'Y轴反向
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

