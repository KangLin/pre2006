Attribute VB_Name = "snape"
'��ģ��Ϊ��׽��ѡȡ����
Option Explicit

'����ΪĿ�겶׽�����㷨
'ѡȡ�˵�,���ָ�����user.pointpoint��
'����user.pointpoint.point���ָ��,�����ֵΪ-4
'��û��ѡȡ����
'����user.pointpoint.flagָʾ��(X,Y)����(X0,X0)
'�����ֵΪ1,��Ϊ(user.linetype.x0,user.linetype.x0)
'..........2,��Ϊ(user.linetype.x,user.linetype.y)
Public Sub snapeendpoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
 Dim i, j, flag As Boolean
 flag = False
 Dim r As Single, k As Single, xx As Single, yy As Single
 k = user.SnapeField
 '�߶εĶ˵�
 user.PointPoint.point = -4
        j = UBound(user.LineType)
        For i = 1 To j
            r = math.twopointdirection(user.LineType(i).X, user.LineType(i).Y, X, Y)
               If r < k Then
                  k = r
                  user.PointPoint.point = i    'ָ��ָ��Сֵ
                  user.PointPoint.flag = 2 'ָ��(x,y)
               End If
            r = math.twopointdirection(user.LineType(i).x0, user.LineType(i).y0, X, Y)
               If r < k Then
                  k = r
                  user.PointPoint.point = i    'ָ��ָ��Сֵ
                  user.PointPoint.flag = 1   'ָ��(x0,y0)
               End If
        Next i
        If user.PointPoint.point <> -4 Then    '��׽���߶ζ˵�
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
        
        '�����ʾ���εĶ˵�
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
        If flag Then  '��׽���˵�
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
        
          '��׽���ĵ��ʾ���εĵ�
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
        If flag Then  '��׽���˵�
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
        
          '��׽�������εĵ�
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
        If flag Then  '��׽���˵�
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
        
        '��׽�������εĵ�
        flag = False
        j = UBound(user.SameRectangleType)
        For i = 1 To j
            Dim x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single
            '���������Ķ���
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
        If flag Then  '��׽���˵�
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
        
        '��׽���������εĵ�
        flag = False
        Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single
        j = UBound(user.SixegdeType)
        For i = 1 To j
            x1 = user.SixegdeType(i).x0
            y1 = user.SixegdeType(i).y0
            x2 = user.SixegdeType(i).X
            y2 = user.SixegdeType(i).Y
            '��������������
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
        If flag Then  '��׽���˵�
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

'��׽�߶λ�Բ�����е�,�����׽��,�򻹻ز�׽���ĵ�,���򻹻���굱ǰλ��
Public Sub snapelinemidpoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
Dim i, j, m, p, r As Single, k
m = user.SnapeField   '��׽��Χ
       '�߶ε��е�
       p = user.LinePoint  '����ԭָ��
       snapeline X, Y, object  '��׽ֱ��
            If user.LinePoint > 0 Then '��ֵΪ����ʱ��ʾδ��׽����
               j = UBound(user.LineType)    'ȡ�����ֱ��
               For i = user.LinePoint To j
                   r = math.pointtolinedirection(X, Y, user.LineType(i).X, user.LineType(i).Y, user.LineType(i).x0, user.LineType(i).y0) '�㵽ֱ�ߵľ���
                   If r < m Then m = r: k = i  'mΪ��С�ľ���
               Next i
               If snapepoint.r < 0 Or _
               snapepoint.r > math.twopointdirection((user.LineType(k).X + user.LineType(k).x0) / 2, (user.LineType(k).Y + user.LineType(k).y0) / 2, X, Y) _
               Then  'ǰ�����δ��׽����
                  With snapepoint
                       .X = (user.LineType(k).X + user.LineType(k).x0) / 2
                       .Y = (user.LineType(k).Y + user.LineType(k).y0) / 2
                       .r = m
                  End With
               End If
            End If
       user.LinePoint = p '�ָ�ָ��
       
       '�����αߵ��е�
       Dim xx As Single, yy As Single, xxx As Single, yyy As Single '��Ų�׽������С��
       p = user.ThreeanglePoint   '����ѡȡ������ָ��
       snapethreeangle X, Y, object  '��׽������
       If user.ThreeanglePoint > 0 Then  '��ֵΪ����ʱ,��ʾδ��׽��������
               j = UBound(user.ThreeAngleType) 'ȡ����ı�
               For i = user.ThreeanglePoint To j
                   '��һ��
                   r = math.pointtolinedirection(X, Y, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2)
                   If r < m Then
                      m = r
                      k = i
                      xx = user.ThreeAngleType(i).x1
                      yy = user.ThreeAngleType(i).y1
                      xxx = user.ThreeAngleType(i).x2
                      yyy = user.ThreeAngleType(i).y2
                   End If
                   '�ڶ���
                   r = math.pointtolinedirection(X, Y, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1, user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3)
                   If r < m Then
                      m = r
                      k = i
                      xx = user.ThreeAngleType(i).x1
                      yy = user.ThreeAngleType(i).y1
                      xxx = user.ThreeAngleType(i).x3
                      yyy = user.ThreeAngleType(i).y3
                   End If
                   '������
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
              Then  '��׽���е�
                  With snapepoint
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
              End If
       End If
       user.ThreeanglePoint = p  '�ָ�ָ��
       
       '������αߵ��е�
       p = user.RectanglePoint '����ѡȡָ��
       snaperectangle X, Y, object '��׽����
       If user.RectanglePoint > 0 Then
         j = UBound(user.RectangleType)
         For i = user.RectanglePoint To j
           r = math.pointtolinedirection(X, Y, user.RectangleType(i).X, user.RectangleType(i).Y, user.RectangleType(i).X, user.RectangleType(i).y0)
           If r < m Then
              m = r   '��С����
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
          With snapepoint  '��׽���ߵ��е�
               .X = (xx + xxx) / 2
               .Y = (yy + yyy) / 2
               .r = m
          End With
         End If
       End If
       user.RectanglePoint = p '�ָ�ָ��
    
       '�ĵ��ʾ���ε��е�
       '   1_________2
       '   |         |
       '   |         |
       '  3|_________|4
       p = user.RectanglefourPoint '����ָ��
       snapefourrectangle X, Y, object '��׽�е��ʾ�ľ���
       If user.RectanglefourPoint > 0 Then  '��ֵΪ���� ʱ��ʾδ��׽������
          j = UBound(user.RectangleFourpointType)
          For i = user.RectanglefourPoint To j
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2)
              If r < m Then
                 m = r '��С����
                 xx = user.RectangleFourpointType(i).x1
                 yy = user.RectangleFourpointType(i).y1
                 xxx = user.RectangleFourpointType(i).x2
                 yyy = user.RectangleFourpointType(i).y2
              End If
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3)
              If r < m Then
                 m = r '��С����
                 xx = user.RectangleFourpointType(i).x1
                 yy = user.RectangleFourpointType(i).y1
                 xxx = user.RectangleFourpointType(i).x3
                 yyy = user.RectangleFourpointType(i).y3
              End If
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4)
              If r < m Then
                 m = r '��С����
                 xx = user.RectangleFourpointType(i).x3
                 yy = user.RectangleFourpointType(i).y3
                 xxx = user.RectangleFourpointType(i).x4
                 yyy = user.RectangleFourpointType(i).y4
              End If
              r = math.pointtolinedirection(X, Y, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2)
              If r < m Then
                 m = r '��С����
                 xx = user.RectangleFourpointType(i).x4
                 yy = user.RectangleFourpointType(i).y4
                 xxx = user.RectangleFourpointType(i).x2
                 yyy = user.RectangleFourpointType(i).y2
              End If
          Next i
          If snapepoint.r < 0 Or snapepoint.r > math.twopointdirection(X, Y, (xx + xxx) / 2, (yy + yyy) / 2) Then
                  With snapepoint  '��׽���ߵ��е�
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       user.RectanglefourPoint = p   '�ָ�ָ��
       
       '�����αߵ��е�
'    3 _________4
'     |        |
'     |        |
'     |        |
'    1---------- 2
       Dim x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single
       p = user.SameRectanglePoint '����ָ��
       snapesamerectangle X, Y, object  '��׽������
       If user.SameRectanglePoint > 0 Then '�� ֵ С��0��ʾδ��׽��������
          j = UBound(user.SameRectangleType)
          For i = user.SameRectanglePoint To j
              x1 = user.SameRectangleType(i).x0
              y1 = user.SameRectangleType(i).y0
              x2 = user.SameRectangleType(i).X
              y2 = user.SameRectangleType(i).Y
              '���Ķ���
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
                  With snapepoint  '��׽���ߵ��е�
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       user.SameRectanglePoint = p '�ָ�ָ��
       
       '�������ε��е�
'       4 ______ 5
'        /      \
'     3 /        \ 6
'       \        /
'        \      /
'       1 ------  2
       Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single
       p = user.SixegdePoint '����ָ��
       snapesixegde X, Y, object '��׽ ������
       If user.SixegdePoint > 0 Then '��ֵ Ϊ����ʱ��ʾδ��׽����������
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
                  With snapepoint  '��׽���ߵ��е�
                       .X = (xx + xxx) / 2
                       .Y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       user.SixegdePoint = p '�ָ�ָ��
       
End Sub

'��׽Բ��,�����׽��Բ��,�򻹻ز�׽���ĵ�,���򻹻����ĵ�ǰλ��
Public Sub snapecirclepoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
       Dim i, j, m
       m = 0
       Dim r As Single
       Dim k As Long
       k = user.SnapeField
       j = UBound(user.CircleType)
       
       For i = 1 To j
           r = math.twopointdirection(X, Y, user.CircleType(i).X, user.CircleType(i).Y)    '�����ľ���
           r = Abs(r - user.CircleType(i).r)
           If r < k Then
              m = i
              k = r
           End If
        Next i
        
        If m <> 0 Then  '��׽��Բ��
           If k < snapepoint.r Or snapepoint.r < 0 Then    '��׽��Բ��
              snapepoint.X = user.CircleType(m).X
              snapepoint.Y = user.CircleType(m).Y
              snapepoint.r = k   '��굽Բ�ľ���
           End If
        End If
End Sub

'��׽��Ŀ��Ľ���
Public Sub snapemisspoint(X As Single, Y As Single, object As Object, snapepoint As snapepoint)
       Dim i, j, m, p, r As Single, k
       Dim point As snapepoint
       point.r = -1
       m = user.SnapeField
       '���߶εĽ���
       p = user.LinePoint  '�����߶ε�ָ��
       snapeline X, Y, object  '��׽�����������߶�
       If p >= 0 Then '��׽���߶�,��PΪ����ʱδ��׽���߶�
          k = UBound(user.LineType)
          For i = p To k
              For j = i + 1 To k
                  With math.twolinemisspoint(user.LineType(i).X, user.LineType(i).Y, user.LineType(i).x0, user.LineType(i).y0, user.LineType(j).X, user.LineType(j).Y, user.LineType(j).x0, user.LineType(j).y0)   '�󽻵�
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
          '��׽���ĵ�
          If point.r >= 0 Then
             If snapepoint.r < 0 Or snapepoint.r > point.r Then
                snapepoint = point
             End If
          End If
       End If
      user.LinePoint = p
       
       '�߶�����ν���
       
       '�߶��������ν���
       
       '�߶��������ν���
       
       '�߶��������ν���
       
       '�߶���Բ�Ľ��㽻��
       
       '�߶���Բ������
       
       '�߶�����Բ����
       
End Sub

'����ΪѡȡĿ���㷨
'�ж�ֱ���Ƿ��ڷ�Χ��
'���㷨��ȱ��,���㷨��׽������ֱ�߶������߶�,ֻ��������׽ʱ
Private Function snapelinej(X As Single, Y As Single, linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single) As Boolean
Dim d, m, k, p, t
    If user.CurrentOperist = "fieldselectobject" Then  '������׽ʱ
       If math.mintwonum(user.Mouseleftdownx, user.Mousepausex) > math.maxtwonum(linex1, linex2) Then snapelinej = False: Exit Function
       If math.maxtwonum(user.Mouseleftdownx, user.Mousepausex) < math.mintwonum(linex1, linex2) Then snapelinej = False: Exit Function
       If math.mintwonum(user.mouseleftdowny, user.mousepausey) > math.maxtwonum(liney1, liney2) Then snapelinej = False: Exit Function
       If math.maxtwonum(user.mouseleftdowny, user.mousepausey) < math.mintwonum(liney1, liney2) Then snapelinej = False: Exit Function
       'ֱ�ߵĶ����ھ�����
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
    
        '�õ㲶׽ʱ
        '��������һ���ڷ�Χ��
        d = Sqr((X - linex1) ^ 2 + (Y - liney1) ^ 2)
        If d <= user.SnapeField Then snapelinej = True: Exit Function
        d = Sqr((X - linex2) ^ 2 + (Y - liney2) ^ 2)
        If d <= user.SnapeField Then snapelinej = True: Exit Function
        '�жϵ㵽ֱ�ߵľ���
        m = math.pointtolinedirection(X, Y, linex1, liney1, linex2, liney2)
        '�������
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
              
           'һ�����
           '�жϽ����Ƿ����߶���,ֻҪ��һ�������ھͿ���
           '�󽻵�,û���
          ' If math.linemisscircle(linex1, liney1, linex2, liney2, x, y, user.snapefield) Then
          '    snapelinej = True
          '    Exit Function
          ' End If
                   
          '���㷨����һ����ȱ��
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

'����׽��ֱ��ʱ,���뵽��׽ֱ�߶�����
'����ʽ��:�Ѳ�׽����ֱ�߷ŵ�ֱ����������,���Ѳ�׽ֱ��ָ������
'���Ѳ�׽����ֱ�߷���ֱ����������
'��Ϊֱ�������а���ֱ�ߺ�������,���Է�Ϊ����:
'1.�Ѳ�׽����ֱ�߷����ݴ�����
'2.�Ѳ�׽����ֱ�ߺ����Ԫ����ǰ��
'3.�ٰ��ݴ������еĲ�׽����ֱ���Ƶ���������
'�������ָ���I,Jֵ
Private Sub insertline(i, j)
Dim k, N, m, p
Dim jh As user.LineType
Dim jhj() As user.LineType
       k = i
       While (k + 1 <= j)  '��������ߵĽ���λ��
             If Not (user.LineType(k).X = user.LineType(k + 1).x0 And user.LineType(k).Y = user.LineType(k + 1).y0) Then
                GoTo insertlineloop    '�˳�
             End If
             k = k + 1
       Wend
insertlineloop:
       If k > j Then k = j   '�������������ֵʱ,ȡ��������ֵ
       m = i
       While (m - 1 > 0)   '��������ߵ���ʼλ��
             If Not (user.LineType(m - 1).X = user.LineType(m).x0 And user.LineType(m - 1).Y = user.LineType(m).y0) Then
                GoTo insertlineloop3    '�˳�
             End If
             m = m - 1
       Wend
insertlineloop3:
       If m < 1 Then m = 1   '��С��������Сֵʱȡ������Сֵ
       
       ReDim jhj(k - m) As user.LineType
       For N = 0 To k - m '�������ݴ�����
           jhj(N) = user.LineType(m + N)
       Next N
       For N = 0 To j - k - 1 '�Ѻ�ߵ���ǰ��
           user.LineType(m + N) = user.LineType(k + 1 + N)
       Next N
       For N = 0 To k - m    '���ݴ������е�ֵ�ƻ������е����
           user.LineType(j - (k - m) + N) = jhj(N)
       Next N
       j = j - (k - m)   'ȡ�ò�׽����Ŀ�����
       i = m        '������I�������ߵ���ʼ��
       user.LinePoint = j   '�ò�׽ֱ��ָ��
       j = j - 1    '��������Ľ���
End Sub

'��׽ֱ��
'���㷨��ȱ��,���㷨��׽������ֱ�߶������߶�,ֻ��������׽ʱ
Public Sub snapeline(X As Single, Y As Single, object As Object)
Dim i, j
       j = UBound(user.LineType)
       For i = 1 To j
           If j < i Then Exit For 'GoTo snapelineloop  '�˳�
           If snapelinej(X, Y, user.LineType(i).x0, user.LineType(i).y0, user.LineType(i).X, user.LineType(i).Y) Then
              insertline i, j
              If j < i Then Exit For ' GoTo snapelineloop  '�˳�
              i = i - 1    '�ؼ�ֹλ
           End If
       Next i
       'If i > UBound(user.linetype) Then user.linepoint = -4: Exit Sub
snapelineloop:
End Sub

'�ж��Ƿ�׽������
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

'���뵽������������
Private Sub insertrectangle(i, j)
Dim jh As user.LineType
       jh = user.RectangleType(j)
       user.RectangleType(j) = user.RectangleType(i)
       user.RectangleType(i) = jh
       user.RectanglePoint = j
       j = j - 1
End Sub

'��׽�����ʾ�ľ���
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
       'If i > UBound(user.rectangletype) Then user.rectanglepoint = -4: Exit Sub 'û�в�׽�����˳�
End Sub

'�ж��Ƿ�׽���ĵ��ʾ�ľ���
Private Function snaperectanglefourpoint1(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single) As Boolean
        If snapelinej(X, Y, x1, y1, x2, y2) Then snaperectanglefourpoint1 = True: Exit Function
        If snapelinej(X, Y, x1, y1, x3, y3) Then snaperectanglefourpoint1 = True: Exit Function
        If snapelinej(X, Y, x4, y4, x2, y2) Then snaperectanglefourpoint1 = True: Exit Function
        If snapelinej(X, Y, x3, y3, x4, y4) Then snaperectanglefourpoint1 = True: Exit Function
        snaperectanglefourpoint1 = False
End Function

'�Ѳ�׽�����ĵ��ʾ�ľ��β��뵽��������
Private Sub insertrectanglefourpoint(i, j)
Dim jh As user.RectangleFourpointType
       jh = user.RectangleFourpointType(j)
       user.RectangleFourpointType(j) = user.RectangleFourpointType(i)
       user.RectangleFourpointType(i) = jh
       user.RectanglefourPoint = j
       j = j - 1
End Sub

'��׽�ĵ��ʾ�ľ���
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
       'If i > UBound(user.rectanglefourpointtype) Then user.rectanglefourpoint = -4: Exit Sub  'û�в�׽�����˳�
       
End Sub

'��׽���������β����������
Private Sub insertthreeangle(i, j)
Dim jh As user.ThreeAngleType
       jh = user.ThreeAngleType(j)
       user.ThreeAngleType(j) = user.ThreeAngleType(i)
       user.ThreeAngleType(i) = jh
       user.ThreeanglePoint = j
       j = j - 1
End Sub

'�ж��Ƿ�׽��������
Private Function snapetrheeangle1(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single) As Boolean
        If snapelinej(X, Y, x1, y1, x2, y2) Then snapetrheeangle1 = True: Exit Function
        If snapelinej(X, Y, x1, y1, x3, y3) Then snapetrheeangle1 = True: Exit Function
        If snapelinej(X, Y, x3, y3, x2, y2) Then snapetrheeangle1 = True: Exit Function
        snapetrheeangle1 = False
End Function

'��׽������
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
       'If i > UBound(user.threeangletype) Then user.threeanglepoint = -4: Exit Sub 'û�в�׽�����˳�
End Sub

'�ж��Ƿ�׽��������
Private Function snapsamerectanglej(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single) As Boolean
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single
        If snapelinej(X, Y, x1, y1, x2, y2) Then snapsamerectanglej = True: Exit Function
        '��֪�����ε�������������
        math.samerectanglethreeandforupiont x1, y1, x2, y2, x3, y3, x4, y4
        If snapelinej(X, Y, x1, y1, x3, y3) Then snapsamerectanglej = True: Exit Function
        If snapelinej(X, Y, x4, y4, x2, y2) Then snapsamerectanglej = True: Exit Function
        If snapelinej(X, Y, x4, y4, x3, y3) Then snapsamerectanglej = True: Exit Function
        snapsamerectanglej = False
End Function

'�Ѳ�׽���������β�����������
Private Sub insersamerectangle(i, j)
Dim jh As user.LineType
       jh = user.SameRectangleType(j)
       user.SameRectangleType(j) = user.SameRectangleType(i)
       user.SameRectangleType(i) = jh
       user.SameRectanglePoint = j
       j = j - 1
End Sub

'��׽������
Public Sub snapesamerectangle(X As Single, Y As Single, object As Object)
Dim i, j, x3 As Single, y3 As Single, x4 As Single, y4 As Single
       j = UBound(user.SameRectangleType)
       For i = 1 To j
           If j < i Then GoTo snapesamerectangleloop  '�˳�
           If snapsamerectanglej(X, Y, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y) Then
              insersamerectangle i, j
              If j < i Then GoTo snapesamerectangleloop  '�˳�
              i = i - 1    '�ؼ�ֹλ
           End If
       Next i
       'If i > UBound(user.samerectangletype) Then user.samerectanglepoint = -4: Exit Sub
snapesamerectangleloop:
End Sub

'�ж��Ƿ�׽����������
Private Function snapesixegdej(X As Single, Y As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single) As Boolean
Dim x3 As Single, y3 As Single, x4 As Single, y4  As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
        If snapelinej(X, Y, x1, y1, x2, y2) Then snapesixegdej = True: Exit Function
        '��֪�����������ĵ�
        math.sixegdefour x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6
        If snapelinej(X, Y, x1, y1, x3, y3) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x6, y6, x2, y2) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x3, y3, x4, y4) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x4, y4, x5, y5) Then snapesixegdej = True: Exit Function
        If snapelinej(X, Y, x5, y5, x6, y6) Then snapesixegdej = True: Exit Function
        snapesixegdej = False
End Function

'�Ѳ�׽�����������β����ҵ����
Private Sub insertsixegde(i, j)
Dim jh As user.LineType
       jh = user.SixegdeType(j)
       user.SixegdeType(j) = user.SixegdeType(i)
       user.SixegdeType(i) = jh
       user.SixegdePoint = j
       j = j - 1
End Sub

'��׽��������
Public Sub snapesixegde(X As Single, Y As Single, object As Object)
Dim i, j, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
       j = UBound(user.SixegdeType)
       For i = 1 To j
           If j < i Then GoTo snapesixegdeloop  '�˳�
           If snapesixegdej(X, Y, user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y) Then
              insertsixegde i, j
              If j < i Then GoTo snapesixegdeloop  '�˳�
              i = i - 1    '�ؼ�ֹλ
           End If
       Next i
       If i > UBound(user.SixegdeType) Then user.SixegdePoint = -4: Exit Sub
snapesixegdeloop:
                                   
End Sub

'�ж��Ƿ�׽��Բ
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

'����Բ��������
Private Sub insertcircle(i, j)
Dim jh As user.CircleType
       jh = user.CircleType(j)
       user.CircleType(j) = user.CircleType(i)
       user.CircleType(i) = jh
       user.CirclePoint = j
       j = j - 1
End Sub

'��׽Բ
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
       'If i > UBound(user.circletype) Then user.circlepoint = -4: Exit Sub 'û�в�׽�����˳�
End Sub

'�ж��Ƿ�׽��Բ��
Private Function snapearc1(X As Single, Y As Single, x1 As Single, y1 As Single, r As Single, start, enda) As Boolean
Dim xx, yy, a
'If user.currentoperist = "fieldselectobject" Then
   
'End If
        If snapecircle1(X, Y, x1, y1, r) Then
           xx = X - x1
           yy = Y - y1
           a = math.angle(xx, yy)
           'Բ��
           If enda > start And start > 0 Then
              If a > Abs(start) And a < Abs(enda) Then snapearc1 = True: Exit Function
           End If
           If enda < start And enda > 0 Then
              If (a > start And a <= user.pi * 2) Or (a >= 0 And a < enda) Then snapearc1 = True: Exit Function
           End If
           '����
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

'���뵽Բ���������
Private Sub insertarc(i, j)
Dim jh As user.ArcType
       jh = user.ArcType(j)
       user.ArcType(j) = user.ArcType(i)
       user.ArcType(i) = jh
       user.ArcPoint = j
       j = j - 1
End Sub

'��׽Բ��
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
       If i > UBound(user.ArcType) Then user.ArcPoint = -4: Exit Sub 'û�в�׽�����˳�
       'ͻ����ʾ
       Form1.Savecommvar '�������Ͳ���
       object.DrawMode = VBRUN.vbXorPen
       For i = user.ArcPoint To UBound(user.ArcType)
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           object.Circle (user.ArcType(i).X, user.ArcType(i).Y), user.ArcType(i).r, user.Snapecolor, user.ArcType(i).start, user.ArcType(i).end
       Next i
       Form1.redocommvar '�ָ����Ͳ���
End Sub

'��ѡȡĿ��ǰ���ǰ����ѡ��Ŀ��
Public Sub selectobjectclare(X As Single, Y As Single, object As Object)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
Dim i
    Form1.Savecommvar '�������Ͳ���
    object.DrawMode = VBRUN.vbCopyPen
    'ֱ��
    If user.LinePoint > 0 Then
       For i = user.LinePoint To UBound(user.LineType)
            object.DrawWidth = user.LineType(i).comvar.width
            object.DrawStyle = user.LineType(i).comvar.style
           object.Line (user.LineType(i).X, user.LineType(i).Y)-(user.LineType(i).x0, user.LineType(i).y0), user.LineType(i).comvar.col  'user.snapecolor
       Next i
    End If
    'Բ
    If user.CirclePoint > 0 Then
       For i = user.CirclePoint To UBound(user.CircleType)
            object.DrawWidth = user.CircleType(i).comvar.width
            object.DrawStyle = user.CircleType(i).comvar.style
           object.Circle (user.CircleType(i).X, user.CircleType(i).Y), user.CircleType(i).r, user.CircleType(i).comvar.col 'user.snapecolor
       Next i
    End If
    '������
    If user.ThreeanglePoint > 0 Then
       For i = user.ThreeanglePoint To UBound(user.ThreeAngleType)
           object.DrawWidth = user.ThreeAngleType(i).comvar.width
           object.DrawStyle = user.ThreeAngleType(i).comvar.style
           object.Line (user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1)-(user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2), user.ThreeAngleType(i).comvar.col 'user.snapecolor
           object.Line -(user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3), user.ThreeAngleType(i).comvar.col 'user.snapecolor
           object.Line -(user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1), user.ThreeAngleType(i).comvar.col  'user.snapecolor
       Next i
    End If
    '����
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
    '�ĵ��ʾ�ľ���
    If user.RectanglefourPoint > 0 Then
       For i = user.RectanglefourPoint To UBound(user.RectangleFourpointType)
           object.DrawWidth = user.RectangleFourpointType(i).comvar.width
           object.DrawStyle = user.RectangleFourpointType(i).comvar.style
           draw.drawforuegde object, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, user.RectangleFourpointType(i).comvar.col
       Next i
   End If
    '������
    If user.SameRectanglePoint > 0 Then
       For i = user.SameRectanglePoint To UBound(user.SameRectangleType)
           object.DrawWidth = user.SameRectangleType(i).comvar.width
           object.DrawStyle = user.SameRectangleType(i).comvar.style
           math.samerectanglethreeandforupiont user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4
           draw.drawforuegde object, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4, user.SameRectangleType(i).comvar.col 'user.snapecolor
       Next i
    End If
           '��������
    If user.SixegdePoint > 0 Then
       For i = user.SixegdePoint To UBound(user.SixegdeType)
           math.sixegdefour user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6
           object.DrawWidth = user.SixegdeType(i).comvar.width
           object.DrawStyle = user.SixegdeType(i).comvar.style
           draw.drawsixegde object, user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6, user.SixegdeType(i).comvar.col  'user.snapecolor
       Next i
    End If
    'Բ��
    If user.ArcPoint > 0 Then
       For i = user.ArcPoint To UBound(user.ArcType)
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           object.Circle (user.ArcType(i).X, user.ArcType(i).Y), user.ArcType(i).r, user.ArcType(i).comvar.col, user.ArcType(i).start, user.ArcType(i).end
       Next i
    End If
    Form1.redocommvar '�ָ����Ͳ���
       
    'If user.linepoint = -4 Or _
    user.circlepoint = -4 Or _
    user.threeanglepoint = -4 Or _
    user.rectanglepoint = -4 Or _
    user.arcpoint = -4 Or _
    user.samerectanglepoint = -4 Or _
    user.sixegdepoint <> -4 Or _
    user.rectanglefourpoint <> -4 Then
       '�����׽����
       Form1.Savecommvar '�������Ͳ���
       object.DrawMode = VBRUN.vbXorPen
       object.DrawStyle = 1
       object.DrawWidth = 1
       'draw.drawrectangle object, user.snapefieldtype.x1, user.snapefieldtype.y1, user.snapefieldtype.x2, user.snapefieldtype.y2, user.snapecolor
       Dim fil
       fil = object.FillStyle
       object.FillStyle = 1
       '��׽����
       With user.SnapefieldType
         If .x1 >= 0 And .y1 >= 0 And .x2 >= 0 And .y2 >= 0 Then
           object.Line (user.SnapefieldType.x1, user.SnapefieldType.y1)-(user.SnapefieldType.x2, user.SnapefieldType.y2), user.Snapecolor, B
           object.FillStyle = fil
            draw.showpoint .x1, .y1, object, user.Snapecolor  '��׽���εĵ�
            draw.showpoint .x2, .y2, object, user.Snapecolor
            draw.showpoint .x1, .y2, object, user.Snapecolor
            draw.showpoint .x2, .y1, object, user.Snapecolor
            .x1 = -1    '�����ǰ�Ĳ�׽����
            .x2 = -1
            .y1 = -1
            .y2 = -1
         End If
       End With
       Form1.redocommvar '��ԭ���Ͳ���
       
    'End If
     Clearpoint
End Sub

'���ѡȡ��ָ��
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

'ѡȡĿ��
Public Sub selectobject(X As Single, Y As Single, object As Object)   '����ѡȡĿ��
 Dim i
       snape.snapeline X, Y, object  'ֱ��
       snape.snapecircle X, Y, object 'Բ
       snape.snaperectangle X, Y, object '�����ʾ�ľ���
       snape.snapefourrectangle X, Y, object '�ĵ��ʾ�ľ���
       snapethreeangle X, Y, object  ' ������
       snapearc X, Y, object    'Բ��������
       snapesamerectangle X, Y, object '������
       snapesixegde X, Y, object '��������
       '��Բ
       
       showselectobject object, True  'ͻ����ʾ\ѡȡ����Ŀ��
End Sub

'ͻ����ʾѡȡ����Ŀ��
Public Sub showselectobject(object As Object, flag As Boolean)
'flag��־�Ƿ�ͻ����ʾѡȡ����Ŀ��
 Dim i
    'ͻ����ʾѡ����ֱ��
    Form1.Savecommvar    '�������Ͳ���
    object.DrawMode = VBRUN.vbXorPen
    If user.LinePoint > 0 Then
       For i = user.LinePoint To UBound(user.LineType)
           '����׽��ʾ���θ�ֵ
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
            If flag Then '��ʾĿ��
               object.DrawWidth = user.LineType(i).comvar.width
               object.DrawStyle = user.LineType(i).comvar.style
               object.Line (user.LineType(i).X, user.LineType(i).Y)-(user.LineType(i).x0, user.LineType(i).y0), user.Snapecolor
            End If
       Next i
    End If
    
       'ͻ����ʾѡȡ�ľ���
    If user.RectanglePoint > 0 Then
       For i = user.RectanglePoint To UBound(user.RectangleType)
           '����׽��ʾ���θ�ֵ
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
    
       'ͻ����ʾ�ĵ��ʾ�ľ���
    If user.RectanglefourPoint > 0 Then
       For i = user.RectanglefourPoint To UBound(user.RectangleFourpointType)
           '����׽��ʾ���θ�ֵ
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
            If flag Then '��ʾĿ��
               object.DrawWidth = user.RectangleFourpointType(i).comvar.width
               object.DrawStyle = user.RectangleFourpointType(i).comvar.style
               draw.drawforuegde object, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, user.Snapecolor
            End If
       Next i
    End If

       'ͻ����ʾ������
    If user.ThreeanglePoint > 0 Then
       For i = user.ThreeanglePoint To UBound(user.ThreeAngleType)
           '����׽��ʾ���θ�ֵ
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
           If flag Then '��ʾĿ��
              object.DrawWidth = user.ThreeAngleType(i).comvar.width
              object.DrawStyle = user.ThreeAngleType(i).comvar.style
              object.Line (user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1)-(user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2), user.Snapecolor
              object.Line -(user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3), user.Snapecolor
              object.Line -(user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1), user.Snapecolor
           End If
       Next i
    End If

       'ͻ����ʾѡ����������
    If user.SameRectanglePoint > 0 Then
    Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
       For i = user.SameRectanglePoint To UBound(user.SameRectangleType)
           math.samerectanglethreeandforupiont user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4
           With user.SnapefieldType  '��ѡȡ��Χ��ֵ
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
           If flag Then '��ʾĿ��
              object.DrawWidth = user.SameRectangleType(i).comvar.width
              object.DrawStyle = user.SameRectangleType(i).comvar.style
              draw.drawforuegde object, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, x3, y3, x4, y4, user.Snapecolor
           End If
       Next i
    End If
       
       'ͻ����ʾѡ������������
    If user.SixegdePoint > 0 Then
       For i = user.SixegdePoint To UBound(user.SixegdeType)
           math.sixegdefour user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6
           With user.SnapefieldType   '��ѡȡ��Χ��ֵ
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
           If flag Then '��ʾĿ��
               object.DrawWidth = user.SixegdeType(i).comvar.width
               object.DrawStyle = user.SixegdeType(i).comvar.style
               draw.drawsixegde object, user.SixegdeType(i).x0, user.SixegdeType(i).y0, user.SixegdeType(i).X, user.SixegdeType(i).Y, x3, y3, x4, y4, x5, y5, x6, y6, user.Snapecolor
            End If
       Next i
    End If
       
       'ͻ����ʾѡȡ����Բ
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
            If flag Then '��ʾĿ��
               object.DrawWidth = user.CircleType(i).comvar.width
               object.DrawStyle = user.CircleType(i).comvar.style
               object.Circle (user.CircleType(i).X, user.CircleType(i).Y), user.CircleType(i).r, user.Snapecolor
            End If
       Next i
    End If
       
       '��ʾ��׽����
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
       Form1.redocommvar  '��ԭ���Ͳ���

End Sub

'��ʾѡȡ����
Public Sub showselectrectangle(object As Object)
       '��ʾ��׽����
       Form1.Savecommvar '�������Ͳ���
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
       Form1.redocommvar  '��ԭ���Ͳ���

End Sub

