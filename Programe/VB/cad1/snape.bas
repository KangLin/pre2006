Attribute VB_Name = "snape"
'本模块为捕捉、选取函数
Option Explicit

'以下为目标捕捉操作算法
'选取端点,点的指针放在user.pointpoint内
'其中user.pointpoint.point存放指针,如果其值为-4
'则没有选取到点
'其中user.pointpoint.flag指示是(X,Y)还是(X0,X0)
'如果其值为1,则为(user.linetype.x0,user.linetype.x0)
'..........2,则为(user.linetype.x,user.linetype.y)
Public Sub snapeendpoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
 Dim i, j, flag As Boolean
 flag = False
 Dim r As Single, k As Single, xx As Single, yy As Single
 k = user.SnapeField
 '线段的端点
 user.PointPoint.point = -4
        j = UBound(user.LineType)
        For i = 1 To j
            r = math.twopointdirection(user.LineType(i).X, user.LineType(i).Y, X, Y)
               If r < k Then
                  k = r
                  user.PointPoint.point = i    '指针指向小值
                  user.PointPoint.flag = 2 '指向(x,y)
               End If
            r = math.twopointdirection(user.LineType(i).x0, user.LineType(i).y0, X, Y)
               If r < k Then
                  k = r
                  user.PointPoint.point = i    '指针指向小值
                  user.PointPoint.flag = 1   '指向(x0,y0)
               End If
        Next i
        If user.PointPoint.point <> -4 Then    '捕捉到线段端点
           With snapepoint
           If user.PointPoint.flag = 1 Then
              .X = user.LineType(user.PointPoint.point).x0
              .Y = user.LineType(user.PointPoint.point).y0
              .r = k
           End If
           If user.PointPoint.flag = 2 Then
              .X = user.LineType(user.PointPoint.point).X
              .Y = user.LineType(user.PointPoint.point).Y
              .r = k
           End If
           End With
        End If
        
        '两点表示矩形的端点
        flag = False
        j = UBound(user.RectangleType)
        For i = 1 To j
            r = math.twopointdirection(X, Y, user.RectangleType(i).X, user.RectangleType(i).Y)
            If r < k Then
               k = r
               xx = user.RectangleType(i).X
               yy = user.RectangleType(i).Y
               flag = True
            End If
            r = math.twopointdirection(X, Y, user.RectangleType(i).x0, user.RectangleType(i).y0)
            If r < k Then
               k = r
               flag = True
               xx = user.RectangleType(i).x0
               yy = user.RectangleType(i).y0
            End If
            r = math.twopointdirection(X, Y, user.RectangleType(i).X, user.RectangleType(i).y0)
            If r < k Then
               flag = True
               k = r
               xx = user.RectangleType(i).X
               yy = user.RectangleType(i).y0
            End If
            r = math.twopointdirection(X, Y, user.RectangleType(i).x0, user.RectangleType(i).Y)
            If r < k Then
               flag = True
               k = r
               xx = user.RectangleType(i).x0
               yy = user.RectangleType(i).Y
            End If
        Next i
        If flag Then  '捕捉到端点
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.X = xx
              snapepoint.Y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.X = xx
                 snapepoint.Y = yy
              End If
          End If
        End If
        
          '捕捉到四点表示矩形的点
        flag = False
        j = UBound(user.RectangleFourpointType)
        For i = 1 To j
            r = math.twopointdirection(X, Y, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1)
            If r < k Then
               k = r
               xx = user.RectangleFourpointType(i).x1
               yy = user.RectangleFourpointType(i).y1
               flag = True
            End If
            r = math.twopointdirection(X, Y, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2)
            If r < k Then
               k = r
               flag = True
               xx = user.RectangleFourpointType(i).x2
               yy = user.RectangleFourpointType(i).y2
            End If
            r = math.twopointdirection(X, Y, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3)
            If r < k Then
               flag = True
               k = r
               xx = user.RectangleFourpointType(i).x3
               yy = user.RectangleFourpointType(i).y3
            End If
            r = math.twopointdirection(X, Y, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4)
            If r < k Then
               flag = True
               k = r
               xx = user.RectangleFourpointType(i).x4
               yy = user.RectangleFourpointType(i).y4
            End If
        Next i
        If flag Then  '捕捉到端点
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.X = xx
              snapepoint.Y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.X = xx
                 snapepoint.Y = yy
              End If
          End If
        End If
        
          '捕捉到三角形的点
        flag = False
        j = UBound(user.ThreeAngleType)
        For i = 1 To j
            r = math.twopointdirection(X, Y, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1)
            If r < k Then
               k = r
               xx = user.ThreeAngleType(i).x1
               yy = user.ThreeAngleType(i).y1
               flag = True
            End If
            r = math.twopointdirection(X, Y, user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2)
            If r < k Then
               k = r
               flag = True
               xx = user.ThreeAngleType(i).x2
               yy = user.ThreeAngleType(i).y2
            End If
            r = math.twopointdirection(X, Y, user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3)
            If r < k Then
               flag = True
               k = r
               xx = user.ThreeAngleType(i).x3
               yy = user.ThreeAngleType(i).y3
            End If
        Next i
        If flag Then  '捕捉到端点
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.X = xx
              snapepoint.Y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.X = xx
                 snapepoint.Y = yy
              End If
          End If
        End If
        
        '捕捉到正方形的点
        flag = False
        j = UBound(user.SameRectangleType)
        For i = 1 To j
            Dim x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single
            '求正方形四顶点
            math.samerectanglethreeandforupiont user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4
            r = math.twopointdirection(X, Y, user.SameRectangleType(i).X, user.SameRectangleType(i).Y)
            If r < k Then
               k = r
               xx = user.SameRectangleType(i).X
               yy = user.SameRectangleType(i).Y
               flag = True
            End If
            r = math.twopointdirection(X, Y, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0)
            If r < k Then
               k = r
               flag = True
               xx = user.SameRectangleType(i).x0
               yy = user.SameRectangleType(i).y0
            End If
            r = math.twopointdirection(X, Y, x3, y3)
            If r < k Then
               flag = True
               k = r
               xx = x3
               yy = y3
            End If
            r = math.twopointdirection(X, Y, x4, y4)
            If r < k Then
               flag = True
               k = r
               xx = x4
               yy = y4
            End If
        Next i
        If flag Then  '捕捉到端点
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.X = xx
              snapepoint.Y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.X = xx
                 snapepoint.Y = yy
              End If
          End If
        End If
        
        '捕捉到正六边形的点
        flag = False
        Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single
        j = UBound(user.SixegdeType)
        For i = 1 To j
            x1 = user.SixegdeType(i).x0
            y1 = user.SixegdeType(i).y0
            x2 = user.SixegdeType(i).X
            y2 = user.SixegdeType(i).Y
            '求六边形六顶点
            math.sixegdefour x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6
            r = math.twopointdirection(X, Y, x1, y1)
            If r < k Then
               k = r
               xx = x1
               yy = y1
               flag = True
            End If
            r = math.twopointdirection(X, Y, x2, y2)
            If r < k Then
               k = r
               flag = True
               xx = x2
               yy = y2
            End If
            r = math.twopointdirection(X, Y, x3, y3)
            If r < k Then
               flag = True
               k = r
               xx = x3
               yy = y3
            End If
            r = math.twopointdirection(X, Y, x4, y4)
            If r < k Then
               flag = True
               k = r
               xx = x4
               yy = y4
            End If
            r = math.twopointdirection(X, Y, x5, y5)
            If r < k Then
               flag = True
               k = r
               xx = x5
               yy = y5
            End If
            r = math.twopointdirection(X, Y, x6, y6)
            If r < k Then
               flag = True
               k = r
               xx = x6
               yy = y6
            End If
        Next i
        If flag Then  '捕捉到端点
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.X = xx
              snapepoint.Y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.X = xx
                 snapepoint.Y = yy
              End If
          End If
        End If
        
End Sub

'捕捉线段或圆弧的中点,如果捕捉到,则还回捕捉到的点,否则还回鼠标当前位置
Public Sub snapelinemidpoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
Dim i, j, m, p, r As Single, k
m = user.SnapeField   '捕捉范围
       '线段的中点
       p = user.LinePoint  '保存原指针
       snapeline X, Y, object  '捕捉直线
            If user.LinePoint > 0 Then '此值为负数时表示未捕捉到点
               j = UBound(user.LineType)    '取最近的直线
               For i = user.LinePoint To j
                   r = math.pointtolinedirection(X, Y, user.LineType(i).X, user.LineType(i).Y, user.LineType(i).x0, user.LineType(i).y0) '点到直线的距离
                   If r < m Then m = r: k = i  'm为最小的距离
               Next i
               If snapepoint.r < 0 Or _
               snapepoint.r > math.twopointdirection((user.LineType(k).X + user.LineType(k).x0) / 2, (user.LineType(k).Y + user.LineType(k).y0) / 2, X, Y) _
               Then  '前面操作未捕捉到点
                  With snapepoint
                       .X = (user.LineType(k).X + user.LineType(k).x0) / 2
                       .Y = (user.LineType(k).Y + user.LineType(k).y0) / 2
                       .r = m
                  End With
               End If
            End If
       user.LinePoint = p '恢复指针
       
       '三角形边的中点
       Dim xx As Single, yy As Single, xxx As Single, yyy As Single '存放捕捉到的最小边
       p = user.ThreeanglePoint   '保存选取三角形指针
       snapethreeangle X, Y, object  '捕捉三角形
       If user.ThreeanglePoint > 0 Then  '此值为负数时,表示未捕捉到三角形
               j = UBound(user.ThreeAngleType) '取最近的边
               For i = user.ThreeanglePoint To j
                   '第一边
                   r = math.pointtolinedirection(X, Y, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2)
                   If r < m Then
                      m = r
                      k = i
                      xx = user.ThreeAngleType(i).x1
                      yy = user.ThreeAngleType(i).y1
                      xxx = user.ThreeAngleType(i).x2
                      yyy = user.ThreeAngleType(i).y2
                   End If
                   '第二边
                   r = math.pointtolinedirection(X, Y, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3)
                   If r < m Then
                      m = r
                      k = i
                      xx = user.ThreeAngleType(i).x1
                      yy = user.ThreeAngleType(i).y1
                      xxx = user.ThreeAngleType(i).x3
                      yyy = user.ThreeAngleType(i).y3
                   End If
                   '第三边
                   r = math.pointtolinedirection(X, Y, user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3, user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2)
                   If r < m Then
                      m = r
                      k = i
                      xx = user.ThreeAngleType(i).x3
                      yy = user.ThreeAngleType(i).y3
                      xxx = user.ThreeAngleType(i).x2
                      yyy = user.ThreeAngleType(i).y2
                   End If
              Next i
              If snapepoint.r < 0 Or snapepoint.r > _
              math.twopointdirection(X, Y, (xx + xxx) / 2, (yy + yyy) / 2) _
              Then  '捕捉到中点
                  With snapepoint
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
              End If
       End If
       user.ThreeanglePoint = p  '恢复指针
       
       '两点矩形边的中点
       p = user.RectanglePoint '保存选取指针
       snaperectangle X, Y, object '捕捉矩形
       If user.RectanglePoint > 0 Then
         j = UBound(user.RectangleType)
         For i = user.RectanglePoint To j
           r = math.pointtolinedirection(X, Y, user.RectangleType(i).X, user.RectangleType(i).Y, user.RectangleType(i).X, user.RectangleType(i).y0)
           If r < m Then
              m = r   '最小距离
              xx = user.RectangleType(i).X
              yy = user.RectangleType(i).Y
              xxx = xx
              yyy = user.RectangleType(i).y0
           End If
           r = math.pointtolinedirection(X, Y, user.RectangleType(i).X, user.RectangleType(i).Y, user.RectangleType(i).x0, user.RectangleType(i).Y)
           If r < m Then
              m = r
              xx = user.RectangleType(i).X
              yy = user.RectangleType(i).Y
              xxx = user.RectangleType(i).x0
              yyy = yy
           End If
           r = math.pointtolinedirection(X, Y, user.RectangleType(i).X, user.RectangleType(i).y0, user.RectangleType(i).x0, user.RectangleType(i).y0)
           If r < m Then
              m = r
              xx = user.RectangleType(i).X
              yy = user.RectangleType(i).y0
              xxx = user.RectangleType(i).x0
              yyy = yy
           End If
           r = math.pointtolinedirection(X, Y, user.RectangleType(i).x0, user.RectangleType(i).Y, user.RectangleType(i).x0, user.RectangleType(i).y0)
           If r < m Then
              m = r
              xx = user.RectangleType(i).x0
              yy = user.RectangleType(i).Y
              xxx = xx
              yyy = user.RectangleType(i).y0
           End If
         Next i
         If snapepoint.r < 0 Or snapepoint.r > math.twopointdirection(X, Y, (xx + xxx) / 2, (yy + yyy) / 2) Then
          With snapepoint  '捕捉到边的中点
               .X = (xx + xxx) / 2
               .Y = (yy + yyy) / 2
               .r = m
          End With
         End If
       End If
       user.RectanglePoint = p '恢复指针
    
       '四点表示矩形的中点
       '   1_________2
       '   |         |
       '   |         |
       '  3|_________|4
       p = user.RectanglefourPoint '保存指针
       snapefourrectangle X, Y, object '捕捉中点表示的矩形
       If user.RectanglefourPoint > 0 Then  '此值为负数 时表示未捕捉到矩形
          j = UBound(user.RectangleFourpointType)
          For i = user.RectanglefourPoint To j
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2)
              If r < m Then
                 m = r '最小距离
                 xx = user.RectangleFourpointType(i).x1
                 yy = user.RectangleFourpointType(i).y1
                 xxx = user.RectangleFourpointType(i).x2
                 yyy = user.RectangleFourpointType(i).y2
              End If
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3)
              If r < m Then
                 m = r '最小距离
                 xx = user.RectangleFourpointType(i).x1
                 yy = user.RectangleFourpointType(i).y1
                 xxx = user.RectangleFourpointType(i).x3
                 yyy = user.RectangleFourpointType(i).y3
              End If
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4)
              If r < m Then
                 m = r '最小距离
                 xx = user.RectangleFourpointType(i).x3
                 yy = user.RectangleFourpointType(i).y3
                 xxx = user.RectangleFourpointType(i).x4
                 yyy = user.RectangleFourpointType(i).y4
              End If
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2)
              If r < m Then
                 m = r '最小距离
                 xx = user.RectangleFourpointType(i).x4
                 yy = user.RectangleFourpointType(i).y4
                 xxx = user.RectangleFourpointType(i).x2
                 yyy = user.RectangleFourpointType(i).y2
              End If
          Next i
          If snapepoint.r < 0 Or snapepoint.r > math.twopointdirection(X, Y, (xx + xxx) / 2, (yy + yyy) / 2) Then
                  With snapepoint  '捕捉到边的中点
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       user.RectanglefourPoint = p   '恢复指针
       
       '正方形边的中点
'    3 _________4
'     |        |
'     |        |
'     |        |
'    1---------- 2
       Dim x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single
       p = user.SameRectanglePoint '保存指针
       snapesamerectangle X, Y, object  '捕捉正方形
       If user.SameRectanglePoint > 0 Then '此 值 小于0表示未捕捉到正方形
          j = UBound(user.SameRectangleType)
          For i = user.SameRectanglePoint To j
              x1 = user.SameRectangleType(i).x0
              y1 = user.SameRectangleType(i).y0
              x2 = user.SameRectangleType(i).X
              y2 = user.SameRectangleType(i).Y
              '求四顶点
              math.samerectanglethreeandforupiont x1, y1, x2, y2, x3, y3, x4, y4
              r = math.pointtolinedirection(X, Y, x1, y1, x2, y2)
              If r < m Then
                 m = r
                 xx = x1
                 yy = y1
                 xxx = x2
                 yyy = y2
              End If
              r = math.pointtolinedirection(X, Y, x1, y1, x3, y3)
              If r < m Then
                 m = r
                 xx = x1
                 yy = y1
                 xxx = x3
                 yyy = y3
              End If
              r = math.pointtolinedirection(X, Y, x4, y4, x2, y2)
              If r < m Then
                 m = r
                 xx = x4
                 yy = y4
                 xxx = x2
                 yyy = y2
              End If
              r = math.pointtolinedirection(X, Y, x3, y3, x4, y4)
              If r < m Then
                 m = r
                 xx = x3
                 yy = y3
                 xxx = x4
                 yyy = y4
              End If
          Next i
          If snapepoint.r < 0 Or snapepoint.r > math.twopointdirection(X, Y, (xx + xxx) / 2, (yy + yyy) / 2) Then
                  With snapepoint  '捕捉到边的中点
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       user.SameRectanglePoint = p '恢复指针
       
       '正六边形的中点
'       4 ______ 5
'        /      \
'     3 /        \ 6
'       \        /
'        \      /
'       1 ------  2
       Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single
       p = user.SixegdePoint '保存指针
       snapesixegde X, Y, object '捕捉 主边形
       If user.SixegdePoint > 0 Then '此值 为负数时表示未捕捉到正六边形
          j = UBound(user.SixegdeType)
          For i = user.SixegdePoint To j
              x1 = user.SixegdeType(i).x0
              y1 = user.SixegdeType(i).y0
              x2 = user.SixegdeType(i).X
              y2 = user.SixegdeType(i).Y
              math.sixegdefour x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6
              r = math.pointtolinedirection(X, Y, x1, y1, x2, y2)
              If r < m Then
                 m = r
                 xx = x1
                 yy = y1
                 xxx = x2
                 yyy = y2
              End If
              r = math.pointtolinedirection(X, Y, x1, y1, x3, y3)
              If r < m Then
                 m = r
                 xx = x1
                 yy = y1
                 xxx = x3
                 yyy = y3
              End If
              r = math.pointtolinedirection(X, Y, x3, y3, x4, y4)
              If r < m Then
                 m = r
                 xx = x3
                 yy = y3
                 xxx = x4
                 yyy = y4
              End If
              r = math.pointtolinedirection(X, Y, x4, y4, x5, y5)
              If r < m Then
                 m = r
                 xx = x5
                 yy = y5
                 xxx = x4
                 yyy = y4
              End If
              r = math.pointtolinedirection(X, Y, x6, y6, x5, y5)
              If r < m Then
                 m = r
                 xx = x5
                 yy = y5
                 xxx = x6
                 yyy = y6
              End If
              r = math.pointtolinedirection(X, Y, x6, y6, x2, y2)
              If r < m Then
                 m = r
                 xx = x6
                 yy = y6
                 xxx = x2
                 yyy = y2
              End If
          Next i
          If snapepoint.r < 0 Or snapepoint.r > math.twopointdirection(X, Y, (xx + xxx) / 2, (yy + yyy) / 2) Then
                  With snapepoint  '捕捉到边的中点
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       user.SixegdePoint = p '恢复指针
       
End Sub

'捕捉圆心,如果捕捉到圆心,则还回捕捉到的点,否则还回鼠标的当前位置
Public Sub snapecirclepoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
       Dim i, j, m
       m = 0
       Dim r As Single
       Dim k As Long
       k = user.SnapeField
       j = UBound(user.CircleType)
       
       For i = 1 To j
           r = math.twopointdirection(X, Y, user.CircleType(i).X, user.CircleType(i).Y)    '两点间的距离
           r = Abs(r - user.CircleType(i).r)
           If r < k Then
              m = i
              k = r
           End If
        Next i
        
        If m <> 0 Then  '捕捉到圆心
           If k < snapepoint.r Or snapepoint.r < 0 Then    '捕捉到圆心
              snapepoint.X = user.CircleType(m).X
              snapepoint.Y = user.CircleType(m).Y
              snapepoint.r = k   '鼠标到圆的距离
           End If
        End If
End Sub

'捕捉两目标的交点
Public Sub snapemisspoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
       Dim i, j, m, p, r As Single, k
       Dim point As snapepoint
       point.r = -1
       m = user.SnapeField
       '两线段的交点
       p = user.LinePoint  '保存线段的指针
       snapeline X, Y, object  '捕捉满足条件的线段
       If p >= 0 Then '捕捉到线段,当P为负数时未捕捉到线段
          k = UBound(user.LineType)
          For i = p To k
              For j = i + 1 To k
                  With math.twolinemisspoint(user.LineType(i).X, user.LineType(i).Y, user.LineType(i).x0, user.LineType(i).y0, user.LineType(j).X, user.LineType(j).Y, user.LineType(j).x0, user.LineType(j).y0)   '求交点
                       r = math.twopointdirection(X, Y, .X, .Y)
                       If r < m Then
                          point.X = .X
                          point.Y = .Y
                          point.r = r
                          m = r
                       End If
                  End With
              Next j
          Next i
          '捕捉到的点
          If point.r >= 0 Then
             If snapepoint.r < 0 Or snapepoint.r > point.r Then
                snapepoint = point
             End If
          End If
       End If
      user.LinePoint = p
       
       '线段与矩形交点
       
       '线段与三角形交点
       
       '线段与六边形交点
       
       '线段与正方形交点
       
       '线段与圆的交点交点
       
       '线段与圆弧交点
       
       '线段与椭圆交点
       
End Sub

'以下为选取目标算法
'判断直线是否在范围内
'本算法有缺陷,此算法捕捉到的是直线而不是线段,只在用区域捕捉时
Private Function snapelinej(X As Single, Y As Single, linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single) As Boolean
Dim d, m, k, p, t
    If user.CurrentOperist = "fieldselectobject" Then  '用区域捕捉时
       If math.mintwonum(user.Mouseleftdownx, user.Mousepausex) > math.maxtwonum(linex1, linex2) Then snapelinej = False: Exit Function
       If math.maxtwonum(user.Mouseleftdownx, user.Mousepausex) < math.mintwonum(linex1, linex2) Then snapelinej = False: Exit Function
       If math.mintwonum(user.mouseleftdowny, user.mousepausey) > math.maxtwonum(liney1, liney2) Then snapelinej = False: Exit Function
       If math.maxtwonum(user.mouseleftdowny, user.mousepausey) < math.mintwonum(liney1, liney2) Then snapelinej = False: Exit Function
       '直线的顶点在矩形内
       If math.pointinrectangle(linex1, liney1, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey) Or math.pointinrectangle(linex2, liney2, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey) Then
          snapelinej = True
          Exit Function
       End If
       k = (liney2 - liney1) / (linex2 - linex1)
       If k < 0 Then
          d = math.mintwonum(user.Mouseleftdownx, user.Mousepausex)
          m = math.mintwonum(user.mouseleftdowny, user.mousepausey)
          p = math.maxtwonum(user.Mouseleftdownx, user.Mousepausex)
          t = math.maxtwonum(user.mouseleftdowny, user.mousepausey)
          If Sgn((m - liney2) / (d - linex2) - k) = Sgn((t - liney2) / (p - linex2) - k) Then
             snapelinej = False
             Exit Function
          End If
       End If
       If k > 0 Then
          d = math.mintwonum(user.Mouseleftdownx, user.Mousepausex)
          m = math.maxtwonum(user.mouseleftdowny, user.mousepausey)
          p = math.maxtwonum(user.Mouseleftdownx, user.Mousepausex)
          t = math.mintwonum(user.mouseleftdowny, user.mousepausey)
          If Sgn((m - liney2) / (d - linex2) - k) = Sgn((t - liney2) / (p - linex2) - k) Then
             snapelinej = False
             Exit Function
          End If
       End If
       snapelinej = True
       Exit Function
    End If
    
        '用点捕捉时
        '两顶点中一点在范围内
        d = Sqr((X - linex1) ^ 2 + (Y - liney1) ^ 2)
        If d <= user.SnapeField Then snapelinej = True: Exit Function
        d = Sqr((X - linex2) ^ 2 + (Y - liney2) ^ 2)
        If d <= user.SnapeField Then snapelinej = True: Exit Function
        '判断点到直线的距离
        m = math.pointtolinedirection(X, Y, linex1, liney1, linex2, liney2)
        '特殊情况
        If m <= user.SnapeField Then
           If linex1 = linex2 Then  '
              If (Y < liney1 And Y > liney2) Or (Y > liney1 And Y < liney2) Then
                    snapelinej = True
                    Exit Function
              End If
           End If
           If liney1 = liney2 Then
              If (X < linex1 And X > linex2) Or (X > linex1 And X < linex2) Then
                    snapelinej = True
                    Exit Function
              End If
           End If
              
           '一般情况
           '判断交点是否在线段上,只要有一个交点在就可以
           '求交点,没解决
          ' If math.linemisscircle(linex1, liney1, linex2, liney2, x, y, user.snapefield) Then
          '    snapelinej = True
          '    Exit Function
          ' End If
                   
          '此算法存在一定的缺陷
          If linex1 > linex2 And liney1 > liney2 Then
             If X < linex1 And X > linex2 And Y < liney1 And Y > liney2 Then
                snapelinej = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 < liney2 Then
             If X > linex1 And X < linex2 And Y > liney1 And Y < liney2 Then
                snapelinej = True
                Exit Function
             End If
          End If
          If linex1 > linex2 And liney1 < liney2 Then
             If X < linex1 And X > linex2 And Y > liney1 And Y < liney2 Then
                snapelinej = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 > liney2 Then
             If X > linex1 And X < linex2 And Y < liney1 And Y > liney2 Then
                snapelinej = True
                Exit Function
             End If
          End If
          
        Else
           snapelinej = False
        End If
End Function

'当捕捉到直线时,插入到捕捉直线队列中
'其形式是:把捕捉到的直线放到直线数组的最后,并把捕捉直线指针向它
'即把捕捉到的直线放入直线数组的最后
'因为直线数组中包含直线和连画线,所以分为三步:
'1.把捕捉到的直线放入暂存数组
'2.把捕捉到的直线后面的元素向前移
'3.再把暂存数组中的捕捉到的直线移到数组的最后
'最后重置指针和I,J值
Private Sub insertline(i, j)
Dim k, N, m, p
Dim jh As user.LineType
Dim jhj() As user.LineType
       k = i
       While (k + 1 <= j)  '求得连画线的结束位置
             If Not (user.LineType(k).X = user.LineType(k + 1).x0 And user.LineType(k).Y = user.LineType(k + 1).y0) Then
                GoTo insertlineloop    '退出
             End If
             k = k + 1
       Wend
insertlineloop:
       If k > j Then k = j   '当大于数组最大值时,取数组的最大值
       m = i
       While (m - 1 > 0)   '求得连画线的起始位置
             If Not (user.LineType(m - 1).X = user.LineType(m).x0 And user.LineType(m - 1).Y = user.LineType(m).y0) Then
                GoTo insertlineloop3    '退出
             End If
             m = m - 1
       Wend
insertlineloop3:
       If m < 1 Then m = 1   '当小于数组最小值时取数组最小值
       
       ReDim jhj(k - m) As user.LineType
       For N = 0 To k - m '交换到暂存数组
           jhj(N) = user.LineType(m + N)
       Next N
       For N = 0 To j - k - 1 '把后边的向前移
           user.LineType(m + N) = user.LineType(k + 1 + N)
       Next N
       For N = 0 To k - m    '把暂存数组中的值移回数组中的最后
           user.LineType(j - (k - m) + N) = jhj(N)
       Next N
       j = j - (k - m)   '取得捕捉到的目标起点
       i = m        '重置置I到连画线的起始处
       user.LinePoint = j   '置捕捉直线指针
       j = j - 1    '重置数组的结束
End Sub

'捕捉直线
'本算法有缺陷,此算法捕捉到的是直线而不是线段,只在用区域捕捉时
Public Sub snapeline(X As Single, Y As Single, object As Object)
Dim i, j
       j = UBound(user.LineType)
       For i = 1 To j
           If j < i Then Exit For 'GoTo snapelineloop  '退出
           If snapelinej(X, Y, user.LineType(i).x0, user.LineType(i).y0, user.LineType(i).X, user.LineType(i).Y) Then
              insertline i, j
              If j < i Then Exit For ' GoTo snapelineloop  '退出
              i = i - 1    '重检止位
           End If
       Next i
       'If i > UBound(user.linetype) Then user.linepoint = -4: Exit Sub
snapelineloop:
End Sub

'判断是否捕捉到矩形
Private Function snaperectangle1(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single) As Boolean
If user.CurrentOperist = "fieldselectobject" Then
   If math.pointinrectangle(x1, y1, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey) And math.pointinrectangle(x2, y2, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey) Then
      snaperectangle1 = True
      Exit Function
   End If
   snaperectangle1 = False
   Exit Function
End If
        If (X > x1 - user.SnapeField And X < x2 + user.SnapeField) Or (X < x1 + user.SnapeField And X > x2 - user.SnapeField) Then
           If (Y > y1 - user.SnapeField And Y < y2 + user.SnapeField) Or (Y < y1 + user.SnapeField And Y < y2 - user.SnapeField) Then
              If Abs(X - x1) < user.SnapeField Or Abs(X - x2) < user.SnapeField Or Abs(Y - y1) < user.SnapeField Or Abs(Y - y2) < user.SnapeField Then snaperectangle1 = True: Exit Function
           End If
        End If
        snaperectangle1 = False
End Function

'插入到矩形数组的最后
Private Sub insertrectangle(i, j)
Dim jh As user.LineType
       jh = user.RectangleType(j)
       user.RectangleType(j) = user.RectangleType(i)
       user.RectangleType(i) = jh
       user.RectanglePoint = j
       j = j - 1
End Sub

'捕捉两点表示的矩形
Public Sub snaperectangle(X As Single, Y As Single, object As Object)
Dim i, j
       j = UBound(user.RectangleType)
       For i = 1 To j
           If j < i Then GoTo snaperectangleloop
           If snaperectangle1(X, Y, user.RectangleType(i).x0, user.RectangleType(i).y0, user.RectangleType(i).X, user.RectangleType(i).Y) Then
              insertrectangle i, j
              If j < i Then GoTo snaperectangleloop
              i = i - 1
           End If
       Next i
snaperectangleloop:
       'If i > UBound(user.rectangletype) Then user.rectanglepoint = -4: Exit Sub '没有捕捉到则退出
End Sub

'判断是否捕捉到四点表示的矩形
Private Function snaperectanglefourpoint1(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single) As Boolean
        If snapelinej(X, Y, x1, y1, x2, y2) Then snaperectanglefourpoint1 = True: Exit Function
        If snapelinej(X, Y, x1, y1, x3, y3) Then snaperectanglefourpoint1 = True: Exit Function
        If snapelinej(X, Y, x4, y4, x2, y2) Then snaperectanglefourpoint1 = True: Exit Function
        If snapelinej(X, Y, x3, y3, x4, y4) Then snaperectanglefourpoint1 = True: Exit Function
        snaperectanglefourpoint1 = False
End Function

'把捕捉到的四点表示的矩形插入到数组的最后
Private Sub insertrectanglefourpoint(i, j)
Dim jh As user.RectangleFourpointType
       jh = user.RectangleFourpointType(j)
       user.RectangleFourpointType(j) = user.RectangleFourpointType(i)
       user.RectangleFourpointType(i) = jh
       user.RectanglefourPoint = j
       j = j - 1
End Sub

'捕捉四点表示的矩形
       '   1_________2
       '   |         |
       '   |         |
       '  3|_________|4
Public Sub snapefourrectangle(X As Single, Y As Single, object As Object)
Dim i, j
       j = UBound(user.RectangleFourpointType)
       For i = 1 To j
           If j < i Then Exit For 'GoTo snaperectangleloop
           If snaperectanglefourpoint1(X, Y, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4) Then
              insertrectanglefourpoint i, j
              If j < i Then Exit For 'GoTo snaperectangleloop
              i = i - 1
           End If
       Next i
snaperectangleloop:
       'If i > UBound(user.rectanglefourpointtype) Then user.rectanglefourpoint = -4: Exit Sub  '没有捕捉到则退出
       
End Sub

'捕捉到的三角形插入数组最后
Private Sub insertthreeangle(i, j)
Dim jh As user.ThreeAngleType
       jh = user.ThreeAngleType(j)
       user.ThreeAngleType(j) = user.ThreeAngleType(i)
       user.ThreeAngleType(i) = jh
       user.ThreeanglePoint = j
       j = j - 1
End Sub

'判断是否捕捉到三角形
Private Function snapetrheeangle1(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single) As Boolean
        If snapelinej(X, Y, x1, y1, x2, y2) Then snapetrheeangle1 = True: Exit Function
        If snapelinej(X, Y, x1, y1, x3, y3) Then snapetrheeangle1 = True: Exit Function
        If snapelinej(X, Y, x3, y3, x2, y2) Then snapetrheeangle1 = True: Exit Function
        snapetrheeangle1 = False
End Function

'捕捉三角形
Public Sub snapethreeangle(X As Single, Y As Single, object As Object)
Dim i, j
       j = UBound(user.ThreeAngleType)
       For i = 1 To j
           If j < i Then GoTo snapethreeangleloop
           If snapetrheeangle1(X, Y, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2, user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3) Then
              insertthreeangle i, j
              If j < i Then GoTo snapethreeangleloop
              i = i - 1
           End If
       Next i
snapethreeangleloop:
       'If i > UBound(user.threeangletype) Then user.threeanglepoint = -4: Exit Sub '没有捕捉到则退出
End Sub

'判断是否捕捉到正方形
Private Function snapsamerectanglej(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single) As Boolean
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single
        If snapelinej(X, Y, x1, y1, x2, y2) Then snapsamerectanglej = True: Exit Function
        '已知正方形的两点求另两点
        math.samerectanglethreeandforupiont x1, y1, x2, y2, x3, y3, x4, y4
        If snapelinej(X, Y, x1, y1, x3, y3) Then snapsamerectanglej = True: Exit Function
        If snapelinej(X, Y, x4, y4, x2, y2) Then snapsamerectanglej = True: Exit Function
        If snapelinej(X, Y, x4, y4, x3, y3) Then snapsamerectanglej = True: Exit Function
        snapsamerectanglej = False
End Function

'把捕捉到的正方形插入数组的最后
Private Sub insersamerectangle(i, j)
Dim jh As user.LineType
       jh = user.SameRectangleType(j)
       user.SameRectangleType(j) = user.SameRectangleType(i)
       user.SameRectangleType(i) = jh
       user.SameRectanglePoint = j
       j = j - 1
End Sub

'捕捉正方形
Public Sub snapesamerectangle(X As Single, Y As Single, object As Object)
Dim i, j, x3 As Single, y3 As Single, x4 As Single, y4 As Single
       j = UBound(user.SameRectangleType)
       For i = 1 To j
           If j < i Then GoTo snapesamerectangleloop  '退出
           If snapsamerectanglej(X, Y, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y) Then
              insersamerectangle i, j
              If j < i Then GoTo snapesamerectangleloop  '退出
              i = i - 1    '重检止位
           End If
       Next i
       'If i > UBound(user.samerectangletype) Then user.samerectanglepoint = -4: Exit Sub
snapesamerectangleloop:
End Sub

'判断是否捕捉到正六边形
Private Function snapesixegdej(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single) As Boolean
Dim x3 As Single, y3 As Single, x4 As Single, y4  As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
        If snapelinej(X, Y, x1, y1, x2, y2) Then snapesixegdej = True: Exit Function
        '已知两点求另外四点
        math.sixegdefour x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6
        If snapelinej(X, Y, x1, y1, x3, y3) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x6, y6, x2, y2) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x3, y3, x4, y4) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x4, y4, x5, y5) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x5, y5, x6, y6) Then snapesixegdej = True: Exit Function
        snapesixegdej = False
End Function

'把捕捉到的正六边形插入且的最后
Private Sub insertsixegde(i, j)
Dim jh As user.LineType
       jh = user.SixegdeType(j)
       user.SixegdeType(j) = user.SixegdeType(i)
       user.SixegdeType(i) = jh
       user.SixegdePoint = j
       j = j - 1
End Sub

'捕捉正六边形
Public Sub snapesixegde(X As Single, Y As Single, object As Object)
Dim i, j, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
       j = UBound(user.SixegdeType)
       For i = 1 To j
           If j < i Then GoTo snapesixegdeloop  '退出
           If snapesixegdej(X, Y, user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y) Then
              insertsixegde i, j
              If j < i Then GoTo snapesixegdeloop  '退出
              i = i - 1    '重检止位
           End If
       Next i
       If i > UBound(user.SixegdeType) Then user.SixegdePoint = -4: Exit Sub
snapesixegdeloop:
                                   
End Sub

'判断是否捕捉到圆
Private Function snapecircle1(X As Single, Y As Single, x1 As Single, y1 As Single, r As Single) As Boolean
Dim d, k
If user.CurrentOperist = "fieldselectobject" Then
   If math.pointinrectangle(x1 - r, y1 - r, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey) And math.pointinrectangle(x1 + r, y1 + r, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey) Then
      snapecircle1 = True
      Exit Function
   End If
   snapecircle1 = False
   Exit Function
End If
        k = math.twopointdirection(X, Y, x1, y1)
        d = Abs(k - r)
        If d < user.SnapeField Then
           snapecircle1 = True
        Else
           snapecircle1 = False
        End If
End Function

'插入圆数组的最后
Private Sub insertcircle(i, j)
Dim jh As user.CircleType
       jh = user.CircleType(j)
       user.CircleType(j) = user.CircleType(i)
       user.CircleType(i) = jh
       user.CirclePoint = j
       j = j - 1
End Sub

'捕捉圆
Public Sub snapecircle(X As Single, Y As Single, object As Object)
Dim i, j
       j = UBound(user.CircleType)
       For i = 1 To j
           If j < i Then GoTo snapecircleloop
           If snapecircle1(X, Y, user.CircleType(i).X, user.CircleType(i).Y, user.CircleType(i).r) Then
              insertcircle i, j
              If j < i Then GoTo snapecircleloop
              i = i - 1
           End If
       Next i
snapecircleloop:
       'If i > UBound(user.circletype) Then user.circlepoint = -4: Exit Sub '没有捕捉到则退出
End Sub

'判断是否捕捉到圆弧
Private Function snapearc1(X As Single, Y As Single, x1 As Single, y1 As Single, r As Single, start, enda) As Boolean
Dim xx, yy, a
'If user.currentoperist = "fieldselectobject" Then
   
'End If
        If snapecircle1(X, Y, x1, y1, r) Then
           xx = X - x1
           yy = Y - y1
           a = math.angle(xx, yy)
           '圆弧
           If enda > start And start > 0 Then
              If a > Abs(start) And a < Abs(enda) Then snapearc1 = True: Exit Function
           End If
           If enda < start And enda > 0 Then
              If (a > start And a <= user.pi * 2) Or (a >= 0 And a < enda) Then snapearc1 = True: Exit Function
           End If
           '扇形
           If enda < 0 And start < 0 Then
              If start < enda Then
                 If (a > Abs(start) And a < user.pi * 2) Or (a >= 0 And a < Abs(enda)) Then snapearc1 = True: Exit Function
              Else
                 If a < Abs(enda) And a > Abs(start) Then snapearc1 = True: Exit Function
              End If
           End If
        End If
        snapearc1 = False
End Function

'插入到圆弧数组最后
Private Sub insertarc(i, j)
Dim jh As user.ArcType
       jh = user.ArcType(j)
       user.ArcType(j) = user.ArcType(i)
       user.ArcType(i) = jh
       user.ArcPoint = j
       j = j - 1
End Sub

'捕捉圆弧
Public Sub snapearc(X As Single, Y As Single, object As Object)
Dim i, j
       j = UBound(user.ArcType)
       For i = 1 To j
           If j < i Then GoTo snapearcloop
           If snapearc1(X, Y, user.ArcType(i).X, user.ArcType(i).Y, user.ArcType(i).r, user.ArcType(i).start, user.ArcType(i).end) Then
              insertarc i, j
              If j < i Then GoTo snapearcloop
              i = i - 1
           End If
       Next i
snapearcloop:
       If i > UBound(user.ArcType) Then user.ArcPoint = -4: Exit Sub '没有捕捉到则退出
       '突出显示
       Form1.Savecommvar '保存线型参数
       object.DrawMode = VBRUN.vbXorPen
       For i = user.ArcPoint To UBound(user.ArcType)
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           object.Circle (user.ArcType(i).X, user.ArcType(i).Y), user.ArcType(i).r, user.Snapecolor, user.ArcType(i).start, user.ArcType(i).end
       Next i
       Form1.redocommvar '恢复线型参数
End Sub

'在选取目标前清除前次所选的目标
Public Sub selectobjectclare(X As Single, Y As Single, object As Object)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
Dim i
    Form1.Savecommvar '保存线型参数
    object.DrawMode = VBRUN.vbCopyPen
    '直线
    If user.LinePoint > 0 Then
       For i = user.LinePoint To UBound(user.LineType)
            object.DrawWidth = user.LineType(i).comvar.width
            object.DrawStyle = user.LineType(i).comvar.style
           object.Line (user.LineType(i).X, user.LineType(i).Y)-(user.LineType(i).x0, user.LineType(i).y0), user.LineType(i).comvar.col  'user.snapecolor
       Next i
    End If
    '圆
    If user.CirclePoint > 0 Then
       For i = user.CirclePoint To UBound(user.CircleType)
            object.DrawWidth = user.CircleType(i).comvar.width
            object.DrawStyle = user.CircleType(i).comvar.style
           object.Circle (user.CircleType(i).X, user.CircleType(i).Y), user.CircleType(i).r, user.CircleType(i).comvar.col 'user.snapecolor
       Next i
    End If
    '三角形
    If user.ThreeanglePoint > 0 Then
       For i = user.ThreeanglePoint To UBound(user.ThreeAngleType)
           object.DrawWidth = user.ThreeAngleType(i).comvar.width
           object.DrawStyle = user.ThreeAngleType(i).comvar.style
           object.Line (user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1)-(user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2), user.ThreeAngleType(i).comvar.col 'user.snapecolor
           object.Line -(user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3), user.ThreeAngleType(i).comvar.col 'user.snapecolor
           object.Line -(user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1), user.ThreeAngleType(i).comvar.col  'user.snapecolor
       Next i
    End If
    '矩形
    If user.RectanglePoint > 0 Then
       For i = user.RectanglePoint To UBound(user.RectangleType)
           object.DrawWidth = user.RectangleType(i).comvar.width
           object.DrawStyle = user.RectangleType(i).comvar.style
           object.Line (user.RectangleType(i).x0, user.RectangleType(i).y0)-(user.RectangleType(i).X, user.RectangleType(i).y0), user.RectangleType(i).comvar.col 'user.snapecolor
           object.Line -(user.RectangleType(i).X, user.RectangleType(i).Y), user.RectangleType(i).comvar.col 'user.snapecolor
           object.Line -(user.RectangleType(i).x0, user.RectangleType(i).Y), user.RectangleType(i).comvar.col ' user.snapecolor
           object.Line -(user.RectangleType(i).x0, user.RectangleType(i).y0), user.RectangleType(i).comvar.col ' user.snapecolor
       Next i
    End If
    '四点表示的矩形
    If user.RectanglefourPoint > 0 Then
       For i = user.RectanglefourPoint To UBound(user.RectangleFourpointType)
           object.DrawWidth = user.RectangleFourpointType(i).comvar.width
           object.DrawStyle = user.RectangleFourpointType(i).comvar.style
           draw.drawforuegde object, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, user.RectangleFourpointType(i).comvar.col
       Next i
   End If
    '正方形
    If user.SameRectanglePoint > 0 Then
       For i = user.SameRectanglePoint To UBound(user.SameRectangleType)
           object.DrawWidth = user.SameRectangleType(i).comvar.width
           object.DrawStyle = user.SameRectangleType(i).comvar.style
           math.samerectanglethreeandforupiont user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4
           draw.drawforuegde object, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4, user.SameRectangleType(i).comvar.col 'user.snapecolor
       Next i
    End If
           '正六边形
    If user.SixegdePoint > 0 Then
       For i = user.SixegdePoint To UBound(user.SixegdeType)
           math.sixegdefour user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6
           object.DrawWidth = user.SixegdeType(i).comvar.width
           object.DrawStyle = user.SixegdeType(i).comvar.style
           draw.drawsixegde object, user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6, user.SixegdeType(i).comvar.col  'user.snapecolor
       Next i
    End If
    '圆弧
    If user.ArcPoint > 0 Then
       For i = user.ArcPoint To UBound(user.ArcType)
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           object.Circle (user.ArcType(i).X, user.ArcType(i).Y), user.ArcType(i).r, user.ArcType(i).comvar.col, user.ArcType(i).start, user.ArcType(i).end
       Next i
    End If
    Form1.redocommvar '恢复线型参数
       
    'If user.linepoint = -4 Or _
    user.circlepoint = -4 Or _
    user.threeanglepoint = -4 Or _
    user.rectanglepoint = -4 Or _
    user.arcpoint = -4 Or _
    user.samerectanglepoint = -4 Or _
    user.sixegdepoint <> -4 Or _
    user.rectanglefourpoint <> -4 Then
       '清除捕捉矩形
       Form1.Savecommvar '保存线型参数
       object.DrawMode = VBRUN.vbXorPen
       object.DrawStyle = 1
       object.DrawWidth = 1
       'draw.drawrectangle object, user.snapefieldtype.x1, user.snapefieldtype.y1, user.snapefieldtype.x2, user.snapefieldtype.y2, user.snapecolor
       Dim fil
       fil = object.FillStyle
       object.FillStyle = 1
       '捕捉矩形
       With user.SnapefieldType
         If .x1 >= 0 And .y1 >= 0 And .x2 >= 0 And .y2 >= 0 Then
           object.Line (user.SnapefieldType.x1, user.SnapefieldType.y1)-(user.SnapefieldType.x2, user.SnapefieldType.y2), user.Snapecolor, B
           object.FillStyle = fil
            draw.showpoint .x1, .y1, object, user.Snapecolor  '捕捉矩形的点
            draw.showpoint .x2, .y2, object, user.Snapecolor
            draw.showpoint .x1, .y2, object, user.Snapecolor
            draw.showpoint .x2, .y1, object, user.Snapecolor
            .x1 = -1    '清除以前的捕捉矩形
            .x2 = -1
            .y1 = -1
            .y2 = -1
         End If
       End With
       Form1.redocommvar '还原线型参数
       
    'End If
     Clearpoint
End Sub

'清除选取的指针
Public Sub Clearpoint()
    user.LinePoint = -4
    user.CirclePoint = -4
    user.ThreeanglePoint = -4
    user.RectanglePoint = -4
    user.ArcPoint = -4
    user.SameRectanglePoint = -4
    user.SixegdePoint = -4
    user.RectanglefourPoint = -4
End Sub

'选取目标
Public Sub selectobject(X As Single, Y As Single, object As Object)   '任意选取目标
 Dim i
       snape.snapeline X, Y, object  '直线
       snape.snapecircle X, Y, object '圆
       snape.snaperectangle X, Y, object '两点表示的矩形
       snape.snapefourrectangle X, Y, object '四点表示的矩形
       snapethreeangle X, Y, object  ' 三角形
       snapearc X, Y, object    '圆弧和扇形
       snapesamerectangle X, Y, object '正方形
       snapesixegde X, Y, object '正六边形
       '椭圆
       
       showselectobject object, True  '突出显示\选取到的目标
End Sub

'突出显示选取到的目标
Public Sub showselectobject(object As Object, flag As Boolean)
'flag标志是否突出显示选取到的目标
 Dim i
    '突出显示选到的直线
    Form1.Savecommvar    '保存线型参数
    object.DrawMode = VBRUN.vbXorPen
    If user.LinePoint > 0 Then
       For i = user.LinePoint To UBound(user.LineType)
           '给捕捉提示矩形赋值
           With user.SnapefieldType
                If .x1 = -1 And .x2 = -1 And .y1 = -1 And .y2 = -1 Then
                   .x1 = math.mintwonum(user.LineType(i).X, user.LineType(i).x0)
                   .x2 = math.maxtwonum(user.LineType(i).X, user.LineType(i).x0)
                   .y1 = math.mintwonum(user.LineType(i).y0, user.LineType(i).Y)
                   .y2 = math.maxtwonum(user.LineType(i).y0, user.LineType(i).Y)
                Else
                   .x1 = math.minthreenum(.x1, user.LineType(i).x0, user.LineType(i).X)
                   .x2 = math.maxthreenum(.x2, user.LineType(i).x0, user.LineType(i).X)
                   .y1 = math.minthreenum(.y1, user.LineType(i).y0, user.LineType(i).Y)
                   .y2 = math.maxthreenum(.y2, user.LineType(i).y0, user.LineType(i).Y)
               End If
            End With
            If flag Then '显示目标
               object.DrawWidth = user.LineType(i).comvar.width
               object.DrawStyle = user.LineType(i).comvar.style
               object.Line (user.LineType(i).X, user.LineType(i).Y)-(user.LineType(i).x0, user.LineType(i).y0), user.Snapecolor
            End If
       Next i
    End If
    
       '突出显示选取的矩形
    If user.RectanglePoint > 0 Then
       For i = user.RectanglePoint To UBound(user.RectangleType)
           '给捕捉提示矩形赋值
           With user.SnapefieldType
           If .x1 = -1 And .x2 = -1 And .y1 = -1 And .y2 = -1 Then
                .x1 = math.mintwonum(user.RectangleType(i).x0, user.RectangleType(i).X)
                .x2 = math.maxtwonum(user.RectangleType(i).x0, user.RectangleType(i).X)
                .y1 = math.mintwonum(user.RectangleType(i).y0, user.RectangleType(i).Y)
                .y2 = math.maxtwonum(user.RectangleType(i).y0, user.RectangleType(i).Y)
           Else
                .x1 = math.minthreenum(.x1, user.RectangleType(i).x0, user.RectangleType(i).X)
                .x2 = math.maxthreenum(.x2, user.RectangleType(i).x0, user.RectangleType(i).X)
                .y1 = math.minthreenum(.y1, user.RectangleType(i).y0, user.RectangleType(i).Y)
                .y2 = math.maxthreenum(.y2, user.RectangleType(i).y0, user.RectangleType(i).Y)
           End If
           End With
            If flag Then
               object.DrawWidth = user.RectangleType(i).comvar.width
               object.DrawStyle = user.RectangleType(i).comvar.style
               object.Line (user.RectangleType(i).x0, user.RectangleType(i).y0)-(user.RectangleType(i).X, user.RectangleType(i).y0), user.Snapecolor
               object.Line -(user.RectangleType(i).X, user.RectangleType(i).Y), user.Snapecolor
               object.Line -(user.RectangleType(i).x0, user.RectangleType(i).Y), user.Snapecolor
               object.Line -(user.RectangleType(i).x0, user.RectangleType(i).y0), user.Snapecolor
            End If
       Next i
    End If
    
       '突出显示四点表示的矩形
    If user.RectanglefourPoint > 0 Then
       For i = user.RectanglefourPoint To UBound(user.RectangleFourpointType)
           '给捕捉提示矩形赋值
           With user.SnapefieldType
           If .x1 = -1 And .x2 = -1 And .y1 = -1 And .y2 = -1 Then
                .x1 = math.mintwonum(user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).x2)
                .x1 = math.minthreenum(.x1, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).x4)
                .x2 = math.maxtwonum(user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).x2)
                .x2 = math.maxthreenum(.x2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).x4)
                .y1 = math.mintwonum(user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).y2)
                .y1 = math.minthreenum(.y1, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).y4)
                .y2 = math.maxtwonum(user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).y2)
                .y2 = math.maxthreenum(.y2, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).y4)
            Else
                .x1 = math.minthreenum(.x1, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).x2)
                .x1 = math.minthreenum(.x1, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).x4)
                .x2 = math.maxthreenum(.x2, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).x2)
                .x2 = math.maxthreenum(.x2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).x4)
                .y1 = math.minthreenum(.y1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).y2)
                .y1 = math.minthreenum(.y1, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).y4)
                .y2 = math.maxthreenum(.y2, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).y2)
                .y2 = math.maxthreenum(.y2, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).y4)
            End If
            End With
            If flag Then '显示目标
               object.DrawWidth = user.RectangleFourpointType(i).comvar.width
               object.DrawStyle = user.RectangleFourpointType(i).comvar.style
               draw.drawforuegde object, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, user.Snapecolor
            End If
       Next i
    End If

       '突出显示三角形
    If user.ThreeanglePoint > 0 Then
       For i = user.ThreeanglePoint To UBound(user.ThreeAngleType)
           '给捕捉提示矩形赋值
           With user.SnapefieldType
           If .x1 = -1 And .x2 = -1 And .y1 = -1 And .y2 = -1 Then
                .x1 = math.minthreenum(user.ThreeAngleType(i).x3, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).x2)
                .x2 = math.maxthreenum(user.ThreeAngleType(i).x3, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).x2)
                .y1 = math.minthreenum(user.ThreeAngleType(i).y3, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).y2)
                .y2 = math.maxthreenum(user.ThreeAngleType(i).y3, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).y2)
           Else
                .x1 = math.minthreenum(.x1, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).x2)
                .x1 = math.mintwonum(.x1, user.ThreeAngleType(i).x3)
                .x2 = math.maxthreenum(.x2, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).x2)
                .x2 = math.maxtwonum(.x2, user.ThreeAngleType(i).x3)
                .y1 = math.minthreenum(.y1, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).y2)
                .y1 = math.mintwonum(.y1, user.ThreeAngleType(i).y3)
                .y2 = math.maxthreenum(.y2, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).y2)
                .y2 = math.maxtwonum(.y2, user.ThreeAngleType(i).y3)
           End If
           End With
           If flag Then '显示目标
              object.DrawWidth = user.ThreeAngleType(i).comvar.width
              object.DrawStyle = user.ThreeAngleType(i).comvar.style
              object.Line (user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1)-(user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2), user.Snapecolor
              object.Line -(user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3), user.Snapecolor
              object.Line -(user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1), user.Snapecolor
           End If
       Next i
    End If

       '突出显示选到的正方形
    If user.SameRectanglePoint > 0 Then
    Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
       For i = user.SameRectanglePoint To UBound(user.SameRectangleType)
           math.samerectanglethreeandforupiont user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4
           With user.SnapefieldType  '给选取范围赋值
           If .x1 = -1 And .x2 = -1 And .y1 = -1 And .y2 = -1 Then
                .x1 = math.mintwonum(math.minthreenum(user.SameRectangleType(i).x0, user.SameRectangleType(i).X, x3), x4)
                .x2 = math.maxtwonum(math.maxthreenum(user.SameRectangleType(i).x0, user.SameRectangleType(i).X, x3), x4)
                .y1 = math.mintwonum(math.minthreenum(user.SameRectangleType(i).y0, user.SameRectangleType(i).Y, y3), y4)
                .y2 = math.maxtwonum(math.maxthreenum(user.SameRectangleType(i).y0, user.SameRectangleType(i).Y, y3), y4)
           Else
                .x1 = math.minthreenum(.x1, math.minthreenum(user.SameRectangleType(i).x0, user.SameRectangleType(i).X, x3), x4)
                .x2 = math.maxthreenum(.x2, math.maxthreenum(user.SameRectangleType(i).x0, user.SameRectangleType(i).X, x3), x4)
                .y1 = math.minthreenum(.y1, math.minthreenum(user.SameRectangleType(i).y0, user.SameRectangleType(i).Y, y3), y4)
                .y2 = math.maxthreenum(.y2, math.maxthreenum(user.SameRectangleType(i).y0, user.SameRectangleType(i).Y, y3), y4)
           End If
           End With
           If flag Then '显示目标
              object.DrawWidth = user.SameRectangleType(i).comvar.width
              object.DrawStyle = user.SameRectangleType(i).comvar.style
              draw.drawforuegde object, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4, user.Snapecolor
           End If
       Next i
    End If
       
       '突出显示选到的正六边形
    If user.SixegdePoint > 0 Then
       For i = user.SixegdePoint To UBound(user.SixegdeType)
           math.sixegdefour user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6
           With user.SnapefieldType   '给选取范围赋值
           If .x1 = -1 And .x2 = -1 And .y1 = -1 And .y2 = -1 Then
                .x1 = math.mintwonum(math.minthreenum(user.SixegdeType(i).x0, user.SixegdeType(i).X, x3), math.minthreenum(x4, x5, x6))
                .x2 = math.maxtwonum(math.maxthreenum(user.SixegdeType(i).x0, user.SixegdeType(i).X, x3), math.maxthreenum(x4, x5, x6))
                .y1 = math.mintwonum(math.minthreenum(user.SixegdeType(i).y0, user.SixegdeType(i).Y, y3), math.minthreenum(y4, y5, y6))
                .y2 = math.maxtwonum(math.maxthreenum(user.SixegdeType(i).y0, user.SixegdeType(i).Y, y3), math.maxthreenum(y4, y5, y6))
           Else
                .x1 = math.minthreenum(.x1, math.minthreenum(user.SixegdeType(i).x0, user.SixegdeType(i).X, x3), math.minthreenum(x4, x5, x6))
                .x2 = math.maxthreenum(.x2, math.maxthreenum(user.SixegdeType(i).x0, user.SixegdeType(i).X, x3), math.maxthreenum(x4, x5, x6))
                .y1 = math.minthreenum(.y1, math.minthreenum(user.SixegdeType(i).y0, user.SixegdeType(i).Y, y3), math.minthreenum(y4, y5, y6))
                .y2 = math.maxthreenum(.y2, math.maxthreenum(user.SixegdeType(i).y0, user.SixegdeType(i).Y, y3), math.maxthreenum(y4, y5, y6))
           End If
           End With
           If flag Then '显示目标
               object.DrawWidth = user.SixegdeType(i).comvar.width
               object.DrawStyle = user.SixegdeType(i).comvar.style
               draw.drawsixegde object, user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6, user.Snapecolor
            End If
       Next i
    End If
       
       '突出显示选取到的圆
    If user.CirclePoint > 0 Then
       For i = user.CirclePoint To UBound(user.CircleType)
            With user.SnapefieldType
            If .x1 = -1 And .x2 = -1 And .y1 = -1 And .y2 = -1 Then
                 .x1 = math.mintwonum(user.CircleType(i).X + user.CircleType(i).r, user.CircleType(i).X - user.CircleType(i).r)
                 .x2 = math.maxtwonum(user.CircleType(i).X + user.CircleType(i).r, user.CircleType(i).X - user.CircleType(i).r)
                 .y1 = math.mintwonum(user.CircleType(i).Y + user.CircleType(i).r, user.CircleType(i).Y - user.CircleType(i).r)
                 .y2 = math.maxtwonum(user.CircleType(i).Y + user.CircleType(i).r, user.CircleType(i).Y - user.CircleType(i).r)
            Else
                 .x1 = math.minthreenum(.x1, user.CircleType(i).X + user.CircleType(i).r, user.CircleType(i).X - user.CircleType(i).r)
                 .x2 = math.maxthreenum(.x2, user.CircleType(i).X + user.CircleType(i).r, user.CircleType(i).X - user.CircleType(i).r)
                 .y1 = math.minthreenum(.y1, user.CircleType(i).Y + user.CircleType(i).r, user.CircleType(i).Y - user.CircleType(i).r)
                 .y2 = math.maxthreenum(.y2, user.CircleType(i).Y + user.CircleType(i).r, user.CircleType(i).Y - user.CircleType(i).r)
            End If
            End With
            If flag Then '显示目标
               object.DrawWidth = user.CircleType(i).comvar.width
               object.DrawStyle = user.CircleType(i).comvar.style
               object.Circle (user.CircleType(i).X, user.CircleType(i).Y), user.CircleType(i).r, user.Snapecolor
            End If
       Next i
    End If
       
       '显示捕捉矩形
       object.DrawWidth = 1
       object.DrawStyle = 1
       Dim fil
       fil = object.FillStyle
       object.FillStyle = 1
       'draw.drawrectangle object, user.snapefieldtype.x1, user.snapefieldtype.y1, user.snapefieldtype.x2, user.snapefieldtype.y2, user.snapecolor
       object.Line (user.SnapefieldType.x1, user.SnapefieldType.y1)-(user.SnapefieldType.x2, user.SnapefieldType.y2), user.Snapecolor, B
       object.FillStyle = fil
       With user.SnapefieldType
            draw.showpoint .x1, .y1, object, user.Snapecolor
            draw.showpoint .x2, .y2, object, user.Snapecolor
            draw.showpoint .x1, .y2, object, user.Snapecolor
            draw.showpoint .x2, .y1, object, user.Snapecolor
       End With
       Form1.redocommvar  '还原线型参数

End Sub

'显示选取矩形
Public Sub showselectrectangle(object As Object)
       '显示捕捉矩形
       Form1.Savecommvar '保存线型参数
       object.DrawWidth = 1
       object.DrawStyle = 1
       object.DrawMode = 7
       Dim fil
       fil = object.FillStyle
       object.FillStyle = 1
       'draw.drawrectangle object, user.snapefieldtype.x1, user.snapefieldtype.y1, user.snapefieldtype.x2, user.snapefieldtype.y2, user.snapecolor
       object.Line (user.SnapefieldType.x1, user.SnapefieldType.y1)-(user.SnapefieldType.x2, user.SnapefieldType.y2), user.Snapecolor, B
       object.FillStyle = fil
       With user.SnapefieldType
            draw.showpoint .x1, .y1, object, user.Snapecolor
            draw.showpoint .x2, .y2, object, user.Snapecolor
            draw.showpoint .x1, .y2, object, user.Snapecolor
            draw.showpoint .x2, .y1, object, user.Snapecolor
       End With
       Form1.redocommvar  '还原线型参数

End Sub

