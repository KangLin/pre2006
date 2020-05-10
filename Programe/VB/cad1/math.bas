Attribute VB_Name = "math"
'��ģ��Ϊ��ѧ����
Option Explicit

'����ת��Ϊ�Ƕ�
Public Function arctoangle(�� As Double) As Double
       arctoangle = 360 * �� / (2 * user.pi)
End Function

'�Ƕ�ת��Ϊ����
Public Function angletoarc(�� As Double) As Double
       angletoarc = 2 * user.pi * �� / 360
End Function

'����һ����ת
Public Sub roundpoint(X As Single, Y As Single, Ҫ��ת�ĵ�x1 As Single, Ҫ��ת�ĵ�y1 As Single, ����x0 As Single, ����y0 As Single, �� As Double)
Dim xx, yy
    '������ԭ���Ƶ�����(pointx,poiny),��(arrarypoinx,arrarypoiny)�������Ϊ(xx,yy)
    xx = Ҫ��ת�ĵ�x1 - ����x0
    yy = Ҫ��ת�ĵ�y1 - ����y0
    '������ƶ���(poinx,poiny)��ת�ǶȦȣ���Ϊ����
    X = xx * Cos(��) - yy * Sin(��)
    Y = xx * Sin(��) + yy * Cos(��)
    '�ٰ������ƻص�ԭ��
    X = X + ����x0
    Y = Y + ����y0
End Sub

'��һ��(x0,y0)����һ��ֱ��(x1,y1)-(x2,y2)����Ϊ(x,y)
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

'����ԭ��ƽ�Ƶ�����(x1,y1)
Public Sub movetopoint(X As Single, Y As Single, x1 As Single, y1 As Single)
       X = X - x1
       Y = Y - y1
End Sub
 
'������ӵ�(x1,y1)�ƻ�ԭ��
Public Sub movecomezieo(X As Single, Y As Single, x1 As Single, y1 As Single)
       X = X + x1
       Y = Y + y1
End Sub

'�߶���Բ�Ľ���,ֻ����ѡȡ�߶�
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

'��ֱ�ߵĽ���
Public Function twolinemisspoint(onelinex As Single, oneliney As Single, onelinex1 As Single, oneliney1 As Single, twolinex As Single, twoliney As Single, twolinex1 As Single, twoliney1 As Single) As point
       Dim k1 As Single, k2 As Single
       With twolinemisspoint
       If (twolinex - twolinex1 <> 0) And (onelinex - onelinex1 <> 0) Then
          k1 = (oneliney - oneliney1) / (onelinex - onelinex1)
          k2 = (twoliney - twoliney1) / (twolinex - twolinex1)
          If k1 = k2 Then
             Exit Function  'ƽ��
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

'�㵽ֱ�ߵľ���
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

'�����ľ���
Public Function twopointdirection(X As Single, Y As Single, x1 As Single, y1 As Single) As Single
Dim d, m
       d = X - x1
       m = Y - y1
       twopointdirection = Sqr(d ^ 2 + m ^ 2)
End Function

'��(X!,Y!)�Ƶ�(X0,Y0)��ת90�ȵõ����µ�(X,Y)
Public Sub ��ת90��(X As Single, Y As Single, x1 As Single, y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = x1 - x0
       yy = y1 - y0
       X = -yy
       Y = xx
       X = X + x0
       Y = Y + y0
End Sub

'��(X!,Y!)�Ƶ�(X0,Y0)��ת-90�ȵõ����µ�(X,Y)
Public Sub ��ת��90��(X As Single, Y As Single, x1 As Single, y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = x1 - x0
       yy = y1 - 0
       X = yy
       Y = -xx
       X = X + x0
       Y = Y + y0
End Sub

'��(X!,Y!)�Ƶ�(X0,Y0)��ת180�ȵõ����µ�(X,Y)
Public Sub ��ת180��(X As Single, Y As Single, x1 As Single, y1 As Single, x0 As Single, y0 As Single)
Dim xx, yy
       xx = x1 - x0
       yy = y1 - 0
       X = -xx
       Y = yy
       X = X + x0
       Y = Y + y0
End Sub


'��֪�����ε�������������������֪(X1,Y1)��(X2,Y2)
Public Sub samerectanglethreeandforupiont(x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single)
Dim xx, yy
'    3 _________4
'     |        |
'     |        |
'     |        |
'    1---------- 2
        '�������Ƶ���һ��
       xx = x2 - x1
       yy = y2 - y1
       '�ѵڶ����Ƶ�һ��ת90��,�õ�������
       x3 = -yy
       y3 = xx
       '�������ƻص�ԭ��,�õ�������
       x3 = x3 + x1
       y3 = y3 + y1
       '�������Ƶ�������
       xx = x1 - x3
       yy = y1 - y3
       '�ѵ�һ���Ƶ�����ת90��
       x4 = -yy
       y4 = xx
       '�������ƻص�ԭ��
       x4 = x4 + x3
       y4 = y4 + y3
End Sub

'��֪�������ε������������ĵ���֪(X1,Y1)��(X2,Y2)
'       4 ______ 5
'        /      \
'     3 /        \ 6
'       \        /
'        \      /
'       1 ------  2
Public Sub sixegdefour(x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single)
Dim xx As Single, yy As Single
          '�������Ƶ���һ��
          xx = x2 - x1
          yy = y2 - y1
          '��ת120��,��2*pi/3
          x3 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y3 = xx * Sin(2 * user.pi / 3) - yy / 2
           '�������ƻ�ԭ��
          x3 = x3 + x1
          y3 = y3 + y1
          '������Ƶ�������
          xx = x1 - x3
          yy = y1 - y3
          '��ת120��
          x4 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y4 = xx * Sin(2 * user.pi / 3) - yy / 2
          '�������ƻ�ԭ��
          x4 = x4 + x3
          y4 = y4 + y3
          '�������Ƶ����ĵ�
          xx = x3 - x4
          yy = y3 - y4
          '��ת120��
          x5 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y5 = xx * Sin(2 * user.pi / 3) - yy / 2
          '������ƻص�ԭ��
          x5 = x5 + x4
          y5 = y5 + y4
          '�������Ƶ������
          xx = x4 - x5
          yy = y4 - y5
          '��ת120��
          x6 = -xx / 2 - yy * Sin(2 * user.pi / 3)
          y6 = xx * Sin(2 * user.pi / 3) - yy / 2
          '������ƻص�ԭ��
          x6 = x6 + x5
          y6 = y6 + y5
End Sub

'����ԭ��Ϊ���ĵ���ת��
'xx,yy �ֱ�Ϊ���㵽ԭ���ʸ��x0x1,y0y1
'��xx=x1-x0
'  yy=y1-y0
Public Function angle(xx, yy)         '����ԭ��Ϊ���ĵ���ת��
Dim rad
                 '���������,ע��Y�᲻ͬ
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

'��һ���Ƿ���һ����������
Public Function pointinrectangle(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single) As Boolean
       If X <= maxtwonum(x1, x2) And X >= mintwonum(x1, x2) And Y <= maxtwonum(y1, y2) And Y >= mintwonum(y1, y2) Then
          pointinrectangle = True
          Exit Function
       End If
          pointinrectangle = False
End Function

'���������е�С����
Public Function mintwonum(x1 As Single, x2 As Single) As Single
       If x1 >= x2 Then
          mintwonum = x2
       Else
          mintwonum = x1
       End If
End Function

'���������еĴ����
Public Function maxtwonum(x1 As Single, x2 As Single) As Single
       If x1 >= x2 Then
          maxtwonum = x1
       Else
          maxtwonum = x2
       End If
End Function

'���������е���С����
Public Function minthreenum(x1 As Single, x2 As Single, x3 As Single) As Single
       minthreenum = mintwonum(mintwonum(x1, x2), x3)
End Function

'���������е�ȡ�����
Public Function maxthreenum(x1 As Single, x2 As Single, x3 As Single) As Single
       maxthreenum = maxtwonum(maxtwonum(x1, x2), x3)
End Function

'��ͼ��������
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
            user.Scrollbar Abs(.left), Abs(.top)  '�ù�����
            Exit Sub
zoomloop:    '������ʱ�Ĵ���
               .top = top
               .left = .left
               .width = w
               .height = h
               .scalewidth = sw
               .ScaleHeight = sh
             user.Scrollbar Abs(.left), Abs(.top)  '�ù�����
       End With
End Sub

'�����ַ�
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


