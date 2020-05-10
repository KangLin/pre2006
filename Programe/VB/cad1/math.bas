Attribute VB_Name = "math"
'本模块为数学函数
Option Explicit

'弧度转换为角度
Public Function arctoangle(θ As Double) As Double
       arctoangle = 360 * θ / (2 * user.pi)
End Function

'角度转化为弧度
Public Function angletoarc(θ As Double) As Double
       angletoarc = 2 * user.pi * θ / 360
End Function

'绕任一点旋转
Public Sub roundpoint(X As Single, Y As Single, 要旋转的点x1 As Single, 要旋转的点y1 As Single, 定点x0 As Single, 定点y0 As Single, θ As Double)
Dim xx, yy
    '把座标原点移到定点(pointx,poiny),点(arrarypoinx,arrarypoiny)的座标变为(xx,yy)
    xx = 要旋转的点x1 - 定点x0
    yy = 要旋转的点y1 - 定点y0
    '行意点绕定点(poinx,poiny)旋转角度θ，θ为弧度
    X = xx * Cos(θ) - yy * Sin(θ)
    Y = xx * Sin(θ) + yy * Cos(θ)
    '再把座标移回到原点
    X = X + 定点x0
    Y = Y + 定点y0
End Sub

'求一点(x0,y0)以任一条直线(x1,y1)-(x2,y2)镜像为(x,y)
Public Sub Mirror(X As Single, Y As Single, x0 As Single, y0 As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single)
Dim k, xx, yy
    If x2 - x1 <> 0 Then
       k = Atn((y2 - y1) / (x2 - x1)) * 2
       X = x0 * Cos(k) + y0 * Sin(k) + x1 * (1 - Cos(k)) - y1 * Sin(k)
       Y = x0 * Sin(k) - y0 * Cos(k) + y1 * (1 + Cos(k)) - x1 * Sin(k)
    Else
       X = x0 - 2 * (x0 - x1)
       Y = y0
    End If
End Sub

'座标原点平移到定点(x1,y1)
Public Sub movetopoint(X As Single, Y As Single, x1 As Single, y1 As Single)
       X = X - x1
       Y = Y - y1
End Sub
 
'把座标从点(x1,y1)移回原点
Public Sub movecomezieo(X As Single, Y As Single, x1 As Single, y1 As Single)
       X = X + x1
       Y = Y + y1
End Sub

'线段与圆的交点,只用于选取线段
Public Function linemisscircle(linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single, circlex As Single, circley As Single, r As Integer) As Boolean
On Error Resume Next
Dim k As Single, d As Single, r2 As Single, xx As Single, yy As Single
    If linex1 <> linex2 And liney1 <> liney2 Then
          r2 = r * r
          k = (liney2 - liney1) / (linex2 - linex1)
          xx = Sqr(r2 / (k * k + 1)) + linex1
          yy = k * (xx - linex1) + liney1
          If linex1 > linex2 And liney1 > liney2 Then
             If xx < linex1 And xx > linex2 And yy < liney1 And yy > liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 < liney2 Then
             If xx > linex1 And xx < linex2 And yy > liney1 And yy < liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
          If linex1 > linex2 And liney1 < liney2 Then
             If xx < linex1 And xx > linex2 And yy > liney1 And yy < liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 > liney2 Then
             If xx > linex1 And xx < linex2 And yy < liney1 And yy > liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
          
          xx = -Sqr(r2 / (k * k + 1)) + linex1
          yy = k * (xx - linex1) + liney1
          If linex1 > linex2 And liney1 > liney2 Then
             If xx < linex1 And xx > linex2 And yy < liney1 And yy > liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 < liney2 Then
             If xx > linex1 And xx < linex2 And yy > liney1 And yy < liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
          If linex1 > linex2 And liney1 < liney2 Then
             If xx < linex1 And xx > linex2 And yy > liney1 And yy < liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 > liney2 Then
             If xx > linex1 And xx < linex2 And yy < liney1 And yy > liney2 Then
                linemisscircle = True
                Exit Function
             End If
          End If
    End If
    
    linemisscircle = False
          
End Function

'两直线的交点
Public Function twolinemisspoint(onelinex As Single, oneliney As Single, onelinex1 As Single, oneliney1 As Single, twolinex As Single, twoliney As Single, twolinex1 As Single, twoliney1 As Single) As point
       Dim k1 As Single, k2 As Single
       With twolinemisspoint
       If (twolinex - twolinex1 <> 0) And (onelinex - onelinex1 <> 0) Then
          k1 = (oneliney - oneliney1) / (onelinex - onelinex1)
          k2 = (twoliney - twoliney1) / (twolinex - twolinex1)
          If k1 = k2 Then
             Exit Function  '平行
          End If
            .X = ((twoliney - oneliney) + k1 * onelinex - k2 * twolinex) / (k1 - k2)
            .Y = k1 * (.X - onelinex) + oneliney
       End If
       
       If (onelinex - onelinex1 = 0) And (twolinex - twolinex1 = 0) Then Exit Function
       
       If (onelinex - onelinex1 = 0) And (twolinex - twolinex1 <> 0) Then
           k2 = (twoliney - twoliney1) / (twolinex - twolinex1)
           .X = onelinex
            .Y = k2 * (.X - twolinex) + twoliney
       End If
       
       If (onelinex - onelinex1 <> 0) And (twolinex - twolinex1 = 0) Then
          k1 = (oneliney - oneliney1) / (onelinex - onelinex1)
          .X = twolinex
          .Y = k1 * (.X - onelinex) + oneliney
       End If
           End With
End Function

'点到直线的距离
Public Function pointtolinedirection(pointx As Single, pointy As Single, linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single) As Single
Dim k, d, Y
       If linex2 - linex1 <> 0 Then
          k = (liney2 - liney1) / (linex2 - linex1)
          Y = k * (pointx - linex1) + liney1
          d = Abs(Y - pointy)
          k = Sqr((linex1 - linex2) ^ 2 + (liney1 - liney2) ^ 2)
          pointtolinedirection = d * Abs(linex1 - linex2) / k
       Else
          pointtolinedirection = Abs(linex1 - pointx)
       End If
End Function

'两点间的距离
Public Function twopointdirection(X As Single, Y As Single, x1 As Single, y1 As Single) As Single
Dim d, m
       d = X - x1
       m = Y - y1
       twopointdirection = Sqr(d ^ 2 + m ^ 2)
End Function

'点(X!,Y!)绕点(X0,Y0)旋转90度得到的新点(X,Y)
Public Sub 旋转90度(X As Single, Y As Single, x1 As Single, y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = x1 - x0
       yy = y1 - y0
       X = -yy
       Y = xx
       X = X + x0
       Y = Y + y0
End Sub

'点(X!,Y!)绕点(X0,Y0)旋转-90度得到的新点(X,Y)
Public Sub 旋转负90度(X As Single, Y As Single, x1 As Single, y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = x1 - x0
       yy = y1 - 0
       X = yy
       Y = -xx
       X = X + x0
       Y = Y + y0
End Sub

'点(X!,Y!)绕点(X0,Y0)旋转180度得到的新点(X,Y)
Public Sub 旋转180度(X As Single, Y As Single, x1 As Single, y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = x1 - x0
       yy = y1 - 0
       X = -xx
       Y = yy
       X = X + x0
       Y = Y + y0
End Sub


'已知正方形的两顶点求另外两点已知(X1,Y1)和(X2,Y2)
Public Sub samerectanglethreeandforupiont(x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single)
Dim xx, yy
'    3 _________4
'     |        |
'     |        |
'     |        |
'    1---------- 2
        '把座标移到第一点
       xx = x2 - x1
       yy = y2 - y1
       '把第二点绕第一点转90度,得到第三点
       x3 = -yy
       y3 = xx
       '把座标移回到原点,得到第三点
       x3 = x3 + x1
       y3 = y3 + y1
       '把座标移到第三点
       xx = x1 - x3
       yy = y1 - y3
       '把第一点绕第三点转90度
       x4 = -yy
       y4 = xx
       '把座标移回到原点
       x4 = x4 + x3
       y4 = y4 + y3
End Sub

'已知正六边形的两点求另外四点已知(X1,Y1)和(X2,Y2)
'       4 ______ 5
'        /      \
'     3 /        \ 6
'       \        /
'        \      /
'       1 ------  2
Public Sub sixegdefour(x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single)
Dim xx As Single, yy As Single
          '把座标移到第一点
          xx = x2 - x1
          yy = y2 - y1
          '旋转120度,即2*pi/3
          x3 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y3 = xx * Sin(2 * user.pi / 3) - yy / 2
           '把座标移回原点
          x3 = x3 + x1
          y3 = y3 + y1
          '把痤标移到第三点
          xx = x1 - x3
          yy = y1 - y3
          '旋转120度
          x4 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y4 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标移回原点
          x4 = x4 + x3
          y4 = y4 + y3
          '把座标移到第四点
          xx = x3 - x4
          yy = y3 - y4
          '旋转120度
          x5 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y5 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标称回到原点
          x5 = x5 + x4
          y5 = y5 + y4
          '把座标移到第五点
          xx = x4 - x5
          yy = y4 - y5
          '旋转120度
          x6 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y6 = xx * Sin(2 * user.pi / 3) - yy / 2
          '把座标称回到原点
          x6 = x6 + x5
          y6 = y6 + y5
End Sub

'求以原点为中心的旋转角
'xx,yy 分别为定点到原点的矢量x0x1,y0y1
'即xx=x1-x0
'  yy=y1-y0
Public Function angle(xx, yy)         '求以原点为中心的旋转角
Dim rad
                 '计算结束角,注意Y轴不同
                        If xx > 0 And yy >= 0 Then
                           rad = 8 * user.rfzghr - Atn(yy / xx)
                        Else
                            If xx > 0 And yy < 0 Then
                               rad = Abs(Atn(yy / xx))
                            Else
                                If xx < 0 And yy > 0 Then
                                    rad = Abs(Atn(yy / xx)) + 4 * user.rfzghr
                                Else
                                    If xx < 0 And yy < 0 Then
                                       rad = 4 * user.rfzghr - Atn(yy / xx)
                                    End If
                                End If
                             End If
                        End If
                        If xx = 0 Then rad = user.pi / 2
 angle = rad
End Function

'求一点是否在一矩形区域内
Public Function pointinrectangle(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single) As Boolean
       If X <= maxtwonum(x1, x2) And X >= mintwonum(x1, x2) And Y <= maxtwonum(y1, y2) And Y >= mintwonum(y1, y2) Then
          pointinrectangle = True
          Exit Function
       End If
          pointinrectangle = False
End Function

'求两个数中的小的数
Public Function mintwonum(x1 As Single, x2 As Single) As Single
       If x1 >= x2 Then
          mintwonum = x2
       Else
          mintwonum = x1
       End If
End Function

'求两个数中的大的数
Public Function maxtwonum(x1 As Single, x2 As Single) As Single
       If x1 >= x2 Then
          maxtwonum = x1
       Else
          maxtwonum = x2
       End If
End Function

'求三个数中的最小的数
Public Function minthreenum(x1 As Single, x2 As Single, x3 As Single) As Single
       minthreenum = mintwonum(mintwonum(x1, x2), x3)
End Function

'求三个数中的取大的数
Public Function maxthreenum(x1 As Single, x2 As Single, x3 As Single) As Single
       maxthreenum = maxtwonum(maxtwonum(x1, x2), x3)
End Function

'制图区的缩放
Public Sub zoom(object As Object, X As Single, Y As Single)
On Error GoTo zoomloop
Dim top As Single, left As Single, w As Single, h As Single, sw As Single, sh As Single
       With object
            top = .top
            left = .left
            w = .width
            h = .height
            sw = .scalewidth
            sh = .ScaleHeight
            .top = Form1.desk.ScaleY(-Y * user.HeightZoomnum, 6, 3)
            .left = Form1.desk.ScaleX(-X * user.WidthZoomnum, 6, 3)
            .width = user.WidthZoomnum * .width
            .height = .height * user.HeightZoomnum
            .ScaleHeight = .ScaleHeight / user.HeightZoomnum
            .scalewidth = .scalewidth / user.WidthZoomnum
            user.Scrollbar Abs(.left), Abs(.top)  '置滚动条
            Exit Sub
zoomloop:    '当出错时的处理
               .top = top
               .left = .left
               .width = w
               .height = h
               .scalewidth = sw
               .ScaleHeight = sh
             user.Scrollbar Abs(.left), Abs(.top)  '置滚动条
       End With
End Sub

'处理字符
Public Sub disstring(object As Object, sstring As String)
Dim i, j, X, Y
X = object.CurrentX
Y = object.CurrentY
j = Len(sstring)
object = Form1.cad
    For i = 1 To j
           If Mid$(sstring, i, 1) <> Chr$(13) Then
              object.Print Mid$(sstring, i, 1);
           Else
              object.Print Chr$(13)
              object.CurrentX = X
           End If
    Next i
End Sub


