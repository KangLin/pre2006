Attribute VB_Name = "snape"
'��ģ��Ϊ��׽��ѡȡ����
'����:����

Option Explicit

'API����,���ڵõ�����
'Public Const GW_HWNDFIRST = 0  '�õ�ͬ�������е���ǰ���
'Public Const GW_HWNDNEXT = 2   '�õ���һ������
'Public Declare Function GetWindow Lib "user32" (ByVal hwnd As Long, ByVal wCmd As Long) As Long
'Public Const SW_SHOWMINNOACTIVE = 7
'Public Const SW_SHOW = 5
'Public Const SW_SHOWNOACTIVATE = 4
'Public Const SW_SHOWNA = 8
'Public Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
'Public Declare Function GetWindowText Lib "user32" Alias "GetWindowTextA" (ByVal hwnd As Long, ByVal lpString As String, ByVal cch As Long) As Long
'Public Declare Function EnumChildWindows Lib "user32" (ByVal hWndParent As Long, ByVal lpEnumFunc As Long, ByVal lParam As Long) As Long
'Public Declare Function SetActiveWindow Lib "user32" (ByVal hwnd As Long) As Long
Private Type snapepoint
        x As Single
        y As Single
        r As Single
        End Type
        
Private Tline() As linetype
Private Tcircle() As CircleType
Private Tfont() As TextType

'�༭�еļ��в���
Public Function EditCut(LLine() As linetype, CCircle() As CircleType, Font() As TextType) As Boolean
Dim i As Long
With fMainForm.ActiveForm
       If EditCopy(LLine, CCircle, Font) Then
          If .GetLinePoint > 0 Then
             ReDim Preserve LLine(.GetLinePoint - 1)
             .LinePoint = -1
          End If
          If .GetCirclePoint > 0 Then
              ReDim Preserve CCircle(.GetCirclePoint - 1)
              .CirclePoint = -1
          End If
          If .GetFontpoint > 0 Then
              For i = .GetFontpoint To UBound(Font)
                  Unload .text(i)
              Next i
              ReDim Preserve Font(.GetFontpoint - 1)
              .FontPoint = -1
          End If
          EditCut = True
       Else
          EditCut = False
       End If
       If EditCut Then
          .Redraw
       End If
End With
End Function

'�༭�еĿ�������
Public Function EditCopy(LLine() As linetype, CCircle() As CircleType, Font() As TextType) As Boolean
Dim i As Long, n As Long, m As Long
ReDim Tline(0)
ReDim Tcircle(0)
ReDim Tfont(0)
With fMainForm.ActiveForm
       n = UBound(Font)
       If n > 0 And .GetFontpoint > 0 Then
          m = n - .GetFontpoint + 1
          ReDim Tfont(m)
          For i = 1 To m
              Let Tfont(i) = Font(.GetFontpoint + i - 1)
              If Tfont(i).point <> 0 Then '��ע��ָ��
                 Tfont(i).point = Tfont(i).point - .GetLinePoint + 1
              End If
          Next i
          EditCopy = True
       End If
       n = UBound(LLine)
       If n > 0 And .GetLinePoint > 0 Then
          m = n - .GetLinePoint + 1
          ReDim Tline(m)
          For i = 1 To m
              Let Tline(i) = LLine(.GetLinePoint + i - 1)
              With Tline(i) '��ע�ߵı�ע�ߴ��ָ��
                   If .Style Mod 10 = -1 Or .Style Mod 10 = -2 Then
                      .Style = .Style Mod 10 - (Int(Abs(.Style / 10) - fMainForm.ActiveForm.GetFontpoint + 1) * 10)
                   End If
              End With
          Next i
          EditCopy = True
       Else
          EditCopy = False
       End If
       n = UBound(CCircle)
       If n > 0 And .GetCirclePoint > 0 Then
          m = n - .GetCirclePoint + 1
          ReDim Tcircle(m)
          For i = 1 To m
              Let Tcircle(i) = CCircle(.GetCirclePoint + i - 1)
          Next i
          EditCopy = True
       End If
       
End With
       If EditCopy Then
          fMainForm.TB(TB_EDIT).Buttons.Item("paste").Enabled = True
          fMainForm.mnuEditPaste.Enabled = True
       End If
End Function

'�༭�е�ճ������
Public Function EditPaste(LLine() As linetype, CCircle() As CircleType, Font() As TextType) As Boolean
Dim i As Long, n As Long, m As Long
With fMainForm.ActiveForm
     n = UBound(Tfont)
     If n > 0 Then
        m = UBound(Font)
        ReDim Preserve Font(n + m)
        'For i = m To m + N
        '    Load .text(i)
        'Next i
        For i = 1 To n
            Let Font(m + i) = Tfont(i)
            Load .text(.text.Count)
            LetFont Font(m + i), .text(.text.UBound), False
            If Font(m + i).point <> 0 Then '��ע�ߵ�ָ��
               Font(m + i).point = Font(m + i).point + UBound(LLine)
            End If
        Next i
        .FontPoint = m + 1
        EditPaste = True
     End If
     n = UBound(Tline)
     If n > 0 Then
        m = UBound(LLine)
        ReDim Preserve LLine(m + n)
        For i = 1 To n
            Let LLine(m + i) = Tline(i) '��ע�ߴ��ָ��
            If LLine(m + i).Style Mod 10 = -1 Or LLine(m + i).Style Mod 10 = -2 Then
               LLine(m + i).Style = LLine(m + i).Style Mod 10 - (Int(Abs(LLine(m + i).Style / 10) + .GetFontpoint - 1) * 10)
            End If
        Next i
        .LinePoint = m + 1
        EditPaste = True
     Else
        EditPaste = False
     End If
     n = UBound(Tcircle)
     If n > 0 Then
        m = UBound(CCircle)
        ReDim Preserve CCircle(m + n)
        For i = 1 To n
            Let CCircle(m + i) = Tcircle(i)
        Next i
        .CirclePoint = m + 1
        EditPaste = True
     End If
     If EditPaste Then
        .Redraw
        fMainForm.TCurrentOperist = "pointselect"
        Enabled_Edit
     End If
End With
End Function
        
'����ΪĿ�겶׽�����㷨
'ѡȡ�˵�,���ָ�����pointpoint��
'����pointpoint.point���ָ��,�����ֵΪ-4
'��û��ѡȡ����
'����pointpoint.flagָʾ��(X,Y)����(X0,X0)
'�����ֵΪ1,��Ϊ(linetype.x0,linetype.x0)
'..........2,��Ϊ(linetype.x,linetype.y)
Public Sub snapeendpoint(x As Single, y As Single, object As Object, snapepoint As snapepoint)
 Dim i, j, flag As Boolean
 flag = False
 Dim r As Single, k As Single, xx As Single, yy As Single
 k = snapefield
 '�߶εĶ˵�
 PointPoint.point = -4
        j = UBound(linetype)
        For i = 1 To j
            r = math.TwoPointDirection(linetype(i).x, linetype(i).y, x, y)
               If r < k Then
                  k = r
                  PointPoint.point = i    'ָ��ָ��Сֵ
                  PointPoint.flag = 2 'ָ��(x,y)
               End If
            r = math.TwoPointDirection(linetype(i).x0, linetype(i).y0, x, y)
               If r < k Then
                  k = r
                  PointPoint.point = i    'ָ��ָ��Сֵ
                  PointPoint.flag = 1   'ָ��(x0,y0)
               End If
        Next i
        If PointPoint.point <> -4 Then    '��׽���߶ζ˵�
           With snapepoint
           If PointPoint.flag = 1 Then
              .x = linetype(PointPoint.point).x0
              .y = linetype(PointPoint.point).y0
              .r = k
           End If
           If PointPoint.flag = 2 Then
              .x = linetype(PointPoint.point).x
              .y = linetype(PointPoint.point).y
              .r = k
           End If
           End With
        End If
        
        '�����ʾ���εĶ˵�
        flag = False
        j = UBound(RectangleType)
        For i = 1 To j
            r = math.TwoPointDirection(x, y, RectangleType(i).x, RectangleType(i).y)
            If r < k Then
               k = r
               xx = RectangleType(i).x
               yy = RectangleType(i).y
               flag = True
            End If
            r = math.TwoPointDirection(x, y, RectangleType(i).x0, RectangleType(i).y0)
            If r < k Then
               k = r
               flag = True
               xx = RectangleType(i).x0
               yy = RectangleType(i).y0
            End If
            r = math.TwoPointDirection(x, y, RectangleType(i).x, RectangleType(i).y0)
            If r < k Then
               flag = True
               k = r
               xx = RectangleType(i).x
               yy = RectangleType(i).y0
            End If
            r = math.TwoPointDirection(x, y, RectangleType(i).x0, RectangleType(i).y)
            If r < k Then
               flag = True
               k = r
               xx = RectangleType(i).x0
               yy = RectangleType(i).y
            End If
        Next i
        If flag Then  '��׽���˵�
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.x = xx
              snapepoint.y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.x = xx
                 snapepoint.y = yy
              End If
          End If
        End If
        
          '��׽���ĵ��ʾ���εĵ�
        flag = False
        j = UBound(RectangleFourpointType)
        For i = 1 To j
            r = math.TwoPointDirection(x, y, RectangleFourpointType(i).X1, RectangleFourpointType(i).Y1)
            If r < k Then
               k = r
               xx = RectangleFourpointType(i).X1
               yy = RectangleFourpointType(i).Y1
               flag = True
            End If
            r = math.TwoPointDirection(x, y, RectangleFourpointType(i).X2, RectangleFourpointType(i).Y2)
            If r < k Then
               k = r
               flag = True
               xx = RectangleFourpointType(i).X2
               yy = RectangleFourpointType(i).Y2
            End If
            r = math.TwoPointDirection(x, y, RectangleFourpointType(i).x3, RectangleFourpointType(i).y3)
            If r < k Then
               flag = True
               k = r
               xx = RectangleFourpointType(i).x3
               yy = RectangleFourpointType(i).y3
            End If
            r = math.TwoPointDirection(x, y, RectangleFourpointType(i).x4, RectangleFourpointType(i).y4)
            If r < k Then
               flag = True
               k = r
               xx = RectangleFourpointType(i).x4
               yy = RectangleFourpointType(i).y4
            End If
        Next i
        If flag Then  '��׽���˵�
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.x = xx
              snapepoint.y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.x = xx
                 snapepoint.y = yy
              End If
          End If
        End If
        
          '��׽�������εĵ�
        flag = False
        j = UBound(ThreeAngleType)
        For i = 1 To j
            r = math.TwoPointDirection(x, y, ThreeAngleType(i).X1, ThreeAngleType(i).Y1)
            If r < k Then
               k = r
               xx = ThreeAngleType(i).X1
               yy = ThreeAngleType(i).Y1
               flag = True
            End If
            r = math.TwoPointDirection(x, y, ThreeAngleType(i).X2, ThreeAngleType(i).Y2)
            If r < k Then
               k = r
               flag = True
               xx = ThreeAngleType(i).X2
               yy = ThreeAngleType(i).Y2
            End If
            r = math.TwoPointDirection(x, y, ThreeAngleType(i).x3, ThreeAngleType(i).y3)
            If r < k Then
               flag = True
               k = r
               xx = ThreeAngleType(i).x3
               yy = ThreeAngleType(i).y3
            End If
        Next i
        If flag Then  '��׽���˵�
           If snapepoint.r < 0 Then
              snapepoint.r = k
              snapepoint.x = xx
              snapepoint.y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.x = xx
                 snapepoint.y = yy
              End If
          End If
        End If
        
        '��׽�������εĵ�
        flag = False
        j = UBound(SameRectangleType)
        For i = 1 To j
            Dim X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single
            '���������Ķ���
            math.samerectanglethreeandforupiont SameRectangleType(i).x0, SameRectangleType(i).y0, SameRectangleType(i).x, SameRectangleType(i).y, x3, y3, x4, y4
            r = math.TwoPointDirection(x, y, SameRectangleType(i).x, SameRectangleType(i).y)
            If r < k Then
               k = r
               xx = SameRectangleType(i).x
               yy = SameRectangleType(i).y
               flag = True
            End If
            r = math.TwoPointDirection(x, y, SameRectangleType(i).x0, SameRectangleType(i).y0)
            If r < k Then
               k = r
               flag = True
               xx = SameRectangleType(i).x0
               yy = SameRectangleType(i).y0
            End If
            r = math.TwoPointDirection(x, y, x3, y3)
            If r < k Then
               flag = True
               k = r
               xx = x3
               yy = y3
            End If
            r = math.TwoPointDirection(x, y, x4, y4)
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
              snapepoint.x = xx
              snapepoint.y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.x = xx
                 snapepoint.y = yy
              End If
          End If
        End If
        
        '��׽���������εĵ�
        flag = False
        Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single
        j = UBound(SixegdeType)
        For i = 1 To j
            X1 = SixegdeType(i).x0
            Y1 = SixegdeType(i).y0
            X2 = SixegdeType(i).x
            Y2 = SixegdeType(i).y
            '��������������
            math.sixegdefour X1, Y1, X2, Y2, x3, y3, x4, y4, x5, y5, x6, y6
            r = math.TwoPointDirection(x, y, X1, Y1)
            If r < k Then
               k = r
               xx = X1
               yy = Y1
               flag = True
            End If
            r = math.TwoPointDirection(x, y, X2, Y2)
            If r < k Then
               k = r
               flag = True
               xx = X2
               yy = Y2
            End If
            r = math.TwoPointDirection(x, y, x3, y3)
            If r < k Then
               flag = True
               k = r
               xx = x3
               yy = y3
            End If
            r = math.TwoPointDirection(x, y, x4, y4)
            If r < k Then
               flag = True
               k = r
               xx = x4
               yy = y4
            End If
            r = math.TwoPointDirection(x, y, x5, y5)
            If r < k Then
               flag = True
               k = r
               xx = x5
               yy = y5
            End If
            r = math.TwoPointDirection(x, y, x6, y6)
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
              snapepoint.x = xx
              snapepoint.y = yy
           Else
              If snapepoint.r > k Then
                 snapepoint.r = k
                 snapepoint.x = xx
                 snapepoint.y = yy
              End If
          End If
        End If
        
End Sub

'��׽�߶λ�Բ�����е�,�����׽��,�򻹻ز�׽���ĵ�,���򻹻���굱ǰλ��
Public Sub snapelinemidpoint(x As Single, y As Single, object As Object, snapepoint As snapepoint)
Dim i, j, m, p, r As Single, k
m = snapefield   '��׽��Χ
       '�߶ε��е�
       p = LinePoint  '����ԭָ��
       snapeline x, y, object  '��׽ֱ��
            If LinePoint > 0 Then '��ֵΪ����ʱ��ʾδ��׽����
               j = UBound(linetype)    'ȡ�����ֱ��
               For i = LinePoint To j
                   r = math.PointToLineDirection(x, y, linetype(i).x, linetype(i).y, linetype(i).x0, linetype(i).y0) '�㵽ֱ�ߵľ���
                   If r < m Then m = r: k = i  'mΪ��С�ľ���
               Next i
               If snapepoint.r < 0 Or _
               snapepoint.r > math.TwoPointDirection((linetype(k).x + linetype(k).x0) / 2, (linetype(k).y + linetype(k).y0) / 2, x, y) _
               Then  'ǰ�����δ��׽����
                  With snapepoint
                       .x = (linetype(k).x + linetype(k).x0) / 2
                       .y = (linetype(k).y + linetype(k).y0) / 2
                       .r = m
                  End With
               End If
            End If
       LinePoint = p '�ָ�ָ��
       
       '�����αߵ��е�
       Dim xx As Single, yy As Single, xxx As Single, yyy As Single '��Ų�׽������С��
       p = ThreeanglePoint   '����ѡȡ������ָ��
       snapethreeangle x, y, object  '��׽������
       If ThreeanglePoint > 0 Then  '��ֵΪ����ʱ,��ʾδ��׽��������
               j = UBound(ThreeAngleType) 'ȡ����ı�
               For i = ThreeanglePoint To j
                   '��һ��
                   r = math.PointToLineDirection(x, y, ThreeAngleType(i).X1, ThreeAngleType(i).Y1, ThreeAngleType(i).X2, ThreeAngleType(i).Y2)
                   If r < m Then
                      m = r
                      k = i
                      xx = ThreeAngleType(i).X1
                      yy = ThreeAngleType(i).Y1
                      xxx = ThreeAngleType(i).X2
                      yyy = ThreeAngleType(i).Y2
                   End If
                   '�ڶ���
                   r = math.PointToLineDirection(x, y, ThreeAngleType(i).X1, ThreeAngleType(i).Y1, ThreeAngleType(i).x3, ThreeAngleType(i).y3)
                   If r < m Then
                      m = r
                      k = i
                      xx = ThreeAngleType(i).X1
                      yy = ThreeAngleType(i).Y1
                      xxx = ThreeAngleType(i).x3
                      yyy = ThreeAngleType(i).y3
                   End If
                   '������
                   r = math.PointToLineDirection(x, y, ThreeAngleType(i).x3, ThreeAngleType(i).y3, ThreeAngleType(i).X2, ThreeAngleType(i).Y2)
                   If r < m Then
                      m = r
                      k = i
                      xx = ThreeAngleType(i).x3
                      yy = ThreeAngleType(i).y3
                      xxx = ThreeAngleType(i).X2
                      yyy = ThreeAngleType(i).Y2
                   End If
              Next i
              If snapepoint.r < 0 Or snapepoint.r > _
              math.TwoPointDirection(x, y, (xx + xxx) / 2, (yy + yyy) / 2) _
              Then  '��׽���е�
                  With snapepoint
                       .x = (xx + xxx) / 2
                       .y = (yy + yyy) / 2
                       .r = m
                  End With
              End If
       End If
       ThreeanglePoint = p  '�ָ�ָ��
       
       '������αߵ��е�
       p = RectanglePoint '����ѡȡָ��
       snaperectangle x, y, object '��׽����
       If RectanglePoint > 0 Then
         j = UBound(RectangleType)
         For i = RectanglePoint To j
           r = math.PointToLineDirection(x, y, RectangleType(i).x, RectangleType(i).y, RectangleType(i).x, RectangleType(i).y0)
           If r < m Then
              m = r   '��С����
              xx = RectangleType(i).x
              yy = RectangleType(i).y
              xxx = xx
              yyy = RectangleType(i).y0
           End If
           r = math.PointToLineDirection(x, y, RectangleType(i).x, RectangleType(i).y, RectangleType(i).x0, RectangleType(i).y)
           If r < m Then
              m = r
              xx = RectangleType(i).x
              yy = RectangleType(i).y
              xxx = RectangleType(i).x0
              yyy = yy
           End If
           r = math.PointToLineDirection(x, y, RectangleType(i).x, RectangleType(i).y0, RectangleType(i).x0, RectangleType(i).y0)
           If r < m Then
              m = r
              xx = RectangleType(i).x
              yy = RectangleType(i).y0
              xxx = RectangleType(i).x0
              yyy = yy
           End If
           r = math.PointToLineDirection(x, y, RectangleType(i).x0, RectangleType(i).y, RectangleType(i).x0, RectangleType(i).y0)
           If r < m Then
              m = r
              xx = RectangleType(i).x0
              yy = RectangleType(i).y
              xxx = xx
              yyy = RectangleType(i).y0
           End If
         Next i
         If snapepoint.r < 0 Or snapepoint.r > math.TwoPointDirection(x, y, (xx + xxx) / 2, (yy + yyy) / 2) Then
          With snapepoint  '��׽���ߵ��е�
               .x = (xx + xxx) / 2
               .y = (yy + yyy) / 2
               .r = m
          End With
         End If
       End If
       RectanglePoint = p '�ָ�ָ��
    
       '�ĵ��ʾ���ε��е�
       '   1_________2
       '   |         |
       '   |         |
       '  3|_________|4
       p = RectanglefourPoint '����ָ��
       snapefourrectangle x, y, object '��׽�е��ʾ�ľ���
       If RectanglefourPoint > 0 Then  '��ֵΪ���� ʱ��ʾδ��׽������
          j = UBound(RectangleFourpointType)
          For i = RectanglefourPoint To j
              r = math.PointToLineDirection(x, y, RectangleFourpointType(i).X1, RectangleFourpointType(i).Y1, RectangleFourpointType(i).X2, RectangleFourpointType(i).Y2)
              If r < m Then
                 m = r '��С����
                 xx = RectangleFourpointType(i).X1
                 yy = RectangleFourpointType(i).Y1
                 xxx = RectangleFourpointType(i).X2
                 yyy = RectangleFourpointType(i).Y2
              End If
              r = math.PointToLineDirection(x, y, RectangleFourpointType(i).X1, RectangleFourpointType(i).Y1, RectangleFourpointType(i).x3, RectangleFourpointType(i).y3)
              If r < m Then
                 m = r '��С����
                 xx = RectangleFourpointType(i).X1
                 yy = RectangleFourpointType(i).Y1
                 xxx = RectangleFourpointType(i).x3
                 yyy = RectangleFourpointType(i).y3
              End If
              r = math.PointToLineDirection(x, y, RectangleFourpointType(i).x3, RectangleFourpointType(i).y3, RectangleFourpointType(i).x4, RectangleFourpointType(i).y4)
              If r < m Then
                 m = r '��С����
                 xx = RectangleFourpointType(i).x3
                 yy = RectangleFourpointType(i).y3
                 xxx = RectangleFourpointType(i).x4
                 yyy = RectangleFourpointType(i).y4
              End If
              r = math.PointToLineDirection(x, y, RectangleFourpointType(i).x4, RectangleFourpointType(i).y4, RectangleFourpointType(i).X2, RectangleFourpointType(i).Y2)
              If r < m Then
                 m = r '��С����
                 xx = RectangleFourpointType(i).x4
                 yy = RectangleFourpointType(i).y4
                 xxx = RectangleFourpointType(i).X2
                 yyy = RectangleFourpointType(i).Y2
              End If
          Next i
          If snapepoint.r < 0 Or snapepoint.r > math.TwoPointDirection(x, y, (xx + xxx) / 2, (yy + yyy) / 2) Then
                  With snapepoint  '��׽���ߵ��е�
                       .x = (xx + xxx) / 2
                       .y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       RectanglefourPoint = p   '�ָ�ָ��
       
       '�����αߵ��е�
'    3 _________4
'     |        |
'     |        |
'     |        |
'    1---------- 2
       Dim X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single
       p = SameRectanglePoint '����ָ��
       snapesamerectangle x, y, object  '��׽������
       If SameRectanglePoint > 0 Then '�� ֵ С��0��ʾδ��׽��������
          j = UBound(SameRectangleType)
          For i = SameRectanglePoint To j
              X1 = SameRectangleType(i).x0
              Y1 = SameRectangleType(i).y0
              X2 = SameRectangleType(i).x
              Y2 = SameRectangleType(i).y
              '���Ķ���
              math.samerectanglethreeandforupiont X1, Y1, X2, Y2, x3, y3, x4, y4
              r = math.PointToLineDirection(x, y, X1, Y1, X2, Y2)
              If r < m Then
                 m = r
                 xx = X1
                 yy = Y1
                 xxx = X2
                 yyy = Y2
              End If
              r = math.PointToLineDirection(x, y, X1, Y1, x3, y3)
              If r < m Then
                 m = r
                 xx = X1
                 yy = Y1
                 xxx = x3
                 yyy = y3
              End If
              r = math.PointToLineDirection(x, y, x4, y4, X2, Y2)
              If r < m Then
                 m = r
                 xx = x4
                 yy = y4
                 xxx = X2
                 yyy = Y2
              End If
              r = math.PointToLineDirection(x, y, x3, y3, x4, y4)
              If r < m Then
                 m = r
                 xx = x3
                 yy = y3
                 xxx = x4
                 yyy = y4
              End If
          Next i
          If snapepoint.r < 0 Or snapepoint.r > math.TwoPointDirection(x, y, (xx + xxx) / 2, (yy + yyy) / 2) Then
                  With snapepoint  '��׽���ߵ��е�
                       .x = (xx + xxx) / 2
                       .y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       SameRectanglePoint = p '�ָ�ָ��
       
       '�������ε��е�
'       4 ______ 5
'        /      \
'     3 /        \ 6
'       \        /
'        \      /
'       1 ------  2
       Dim x5 As Single, y5 As Single, x6 As Single, y6 As Single
       p = SixegdePoint '����ָ��
       snapesixegde x, y, object '��׽ ������
       If SixegdePoint > 0 Then '��ֵ Ϊ����ʱ��ʾδ��׽����������
          j = UBound(SixegdeType)
          For i = SixegdePoint To j
              X1 = SixegdeType(i).x0
              Y1 = SixegdeType(i).y0
              X2 = SixegdeType(i).x
              Y2 = SixegdeType(i).y
              math.sixegdefour X1, Y1, X2, Y2, x3, y3, x4, y4, x5, y5, x6, y6
              r = math.PointToLineDirection(x, y, X1, Y1, X2, Y2)
              If r < m Then
                 m = r
                 xx = X1
                 yy = Y1
                 xxx = X2
                 yyy = Y2
              End If
              r = math.PointToLineDirection(x, y, X1, Y1, x3, y3)
              If r < m Then
                 m = r
                 xx = X1
                 yy = Y1
                 xxx = x3
                 yyy = y3
              End If
              r = math.PointToLineDirection(x, y, x3, y3, x4, y4)
              If r < m Then
                 m = r
                 xx = x3
                 yy = y3
                 xxx = x4
                 yyy = y4
              End If
              r = math.PointToLineDirection(x, y, x4, y4, x5, y5)
              If r < m Then
                 m = r
                 xx = x5
                 yy = y5
                 xxx = x4
                 yyy = y4
              End If
              r = math.PointToLineDirection(x, y, x6, y6, x5, y5)
              If r < m Then
                 m = r
                 xx = x5
                 yy = y5
                 xxx = x6
                 yyy = y6
              End If
              r = math.PointToLineDirection(x, y, x6, y6, X2, Y2)
              If r < m Then
                 m = r
                 xx = x6
                 yy = y6
                 xxx = X2
                 yyy = Y2
              End If
          Next i
          If snapepoint.r < 0 Or snapepoint.r > math.TwoPointDirection(x, y, (xx + xxx) / 2, (yy + yyy) / 2) Then
                  With snapepoint  '��׽���ߵ��е�
                       .x = (xx + xxx) / 2
                       .y = (yy + yyy) / 2
                       .r = m
                  End With
          End If
       End If
       SixegdePoint = p '�ָ�ָ��
       
End Sub

'��׽Բ��,�����׽��Բ��,�򻹻ز�׽���ĵ�,���򻹻����ĵ�ǰλ��
Public Sub snapecirclepoint(x As Single, y As Single, object As Object, snapepoint As snapepoint)
       Dim i, j, m
       m = 0
       Dim r As Single
       Dim k As Long
       k = snapefield
       j = UBound(CircleType)
       
       For i = 1 To j
           r = math.TwoPointDirection(x, y, CircleType(i).x, CircleType(i).y)    '�����ľ���
           r = Abs(r - CircleType(i).r)
           If r < k Then
              m = i
              k = r
           End If
        Next i
        
        If m <> 0 Then  '��׽��Բ��
           If k < snapepoint.r Or snapepoint.r < 0 Then    '��׽��Բ��
              snapepoint.x = CircleType(m).x
              snapepoint.y = CircleType(m).y
              snapepoint.r = k   '��굽Բ�ľ���
           End If
        End If
End Sub

'��׽��Ŀ��Ľ���
Public Sub snapemisspoint(x As Single, y As Single, object As Object, snapepoint As snapepoint)
       Dim i, j, m, p, r As Single, k
       Dim point As snapepoint
       point.r = -1
       m = snapefield
       '���߶εĽ���
       p = LinePoint  '�����߶ε�ָ��
       snapeline x, y, object  '��׽�����������߶�
       If p >= 0 Then '��׽���߶�,��PΪ����ʱδ��׽���߶�
          k = UBound(linetype)
          For i = p To k
              For j = i + 1 To k
                  With math.TwoLineMissPoint(linetype(i).x, linetype(i).y, linetype(i).x0, linetype(i).y0, linetype(j).x, linetype(j).y, linetype(j).x0, linetype(j).y0)   '�󽻵�
                       r = math.TwoPointDirection(x, y, .x, .y)
                       If r < m Then
                          point.x = .x
                          point.y = .y
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
      LinePoint = p
       
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
Public Function Select_Line_Ok(x As Single, y As Single, linex1 As Single, liney1 As Single, linex2 As Single, liney2 As Single, snapefield As Integer) As Boolean
Dim d, m, k, p, t

    If fMainForm.TCurrentOperist = "fieldselectobject" Then  '������׽ʱ
       If math.MinTwoNum(Mouseleftdownx, Mousepausex) > math.MaxTwoNum(linex1, linex2) Then Select_Line_Ok = False: Exit Function
       If math.MaxTwoNum(Mouseleftdownx, Mousepausex) < math.MinTwoNum(linex1, linex2) Then Select_Line_Ok = False: Exit Function
       If math.MinTwoNum(Mouseleftdowny, Mousepausey) > math.MaxTwoNum(liney1, liney2) Then Select_Line_Ok = False: Exit Function
       If math.MaxTwoNum(Mouseleftdowny, Mousepausey) < math.MinTwoNum(liney1, liney2) Then Select_Line_Ok = False: Exit Function
       'ֱ�ߵĶ����ھ�����
       If math.pointinrectangle(linex1, liney1, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey) Or math.pointinrectangle(linex2, liney2, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey) Then
          Select_Line_Ok = True
          Exit Function
       End If
       k = (liney2 - liney1) / (linex2 - linex1)
       If k < 0 Then
          d = math.MinTwoNum(Mouseleftdownx, Mousepausex)
          m = math.MinTwoNum(Mouseleftdowny, Mousepausey)
          p = math.MaxTwoNum(Mouseleftdownx, Mousepausex)
          t = math.MaxTwoNum(Mouseleftdowny, Mousepausey)
          If Sgn((m - liney2) / (d - linex2) - k) = Sgn((t - liney2) / (p - linex2) - k) Then
             Select_Line_Ok = False
             Exit Function
          End If
       End If
       If k > 0 Then
          d = math.MinTwoNum(Mouseleftdownx, Mousepausex)
          m = math.MaxTwoNum(Mouseleftdowny, Mousepausey)
          p = math.MaxTwoNum(Mouseleftdownx, Mousepausex)
          t = math.MinTwoNum(Mouseleftdowny, Mousepausey)
          If Sgn((m - liney2) / (d - linex2) - k) = Sgn((t - liney2) / (p - linex2) - k) Then
             Select_Line_Ok = False
             Exit Function
          End If
       End If
       Select_Line_Ok = True
       Exit Function
    End If
    
        '�õ㲶׽ʱ
        '��������һ���ڷ�Χ��
        d = Sqr((x - linex1) ^ 2 + (y - liney1) ^ 2)
        If d <= snapefield Then Select_Line_Ok = True: Exit Function
        d = Sqr((x - linex2) ^ 2 + (y - liney2) ^ 2)
        If d <= snapefield Then Select_Line_Ok = True: Exit Function
        '�жϵ㵽ֱ�ߵľ���
        m = math.PointToLineDirection(x, y, linex1, liney1, linex2, liney2)
        '�������
        If m <= snapefield Then
           If linex1 = linex2 Then  '
              If (y < liney1 And y > liney2) Or (y > liney1 And y < liney2) Then
                    Select_Line_Ok = True
                    Exit Function
              End If
           End If
           If liney1 = liney2 Then
              If (x < linex1 And x > linex2) Or (x > linex1 And x < linex2) Then
                    Select_Line_Ok = True
                    Exit Function
              End If
           End If
              
           'һ�����
           '�жϽ����Ƿ����߶���,ֻҪ��һ�������ھͿ���
           '�󽻵�,û���
          ' If math.linemisscircle(linex1, liney1, linex2, liney2, x, y, snapefield) Then
          '    Select_line_ok = True
          '    Exit Function
          ' End If
                   
          '���㷨����һ����ȱ��
          If linex1 > linex2 And liney1 > liney2 Then
             If x < linex1 And x > linex2 And y < liney1 And y > liney2 Then
                Select_Line_Ok = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 < liney2 Then
             If x > linex1 And x < linex2 And y > liney1 And y < liney2 Then
                Select_Line_Ok = True
                Exit Function
             End If
          End If
          If linex1 > linex2 And liney1 < liney2 Then
             If x < linex1 And x > linex2 And y > liney1 And y < liney2 Then
                Select_Line_Ok = True
                Exit Function
             End If
          End If
          If linex1 < linex2 And liney1 > liney2 Then
             If x > linex1 And x < linex2 And y < liney1 And y > liney2 Then
                Select_Line_Ok = True
                Exit Function
             End If
          End If
          
        Else
           Select_Line_Ok = False
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
Private Sub insertline(i, j, LinePoint As Integer, linetype As linetype)
Dim k, n, m, p
Dim jh As linetype
Dim jhj() As linetype
       k = i
       While (k + 1 <= j)  '��������ߵĽ���λ��
             If Not (linetype(k).x = linetype(k + 1).x0 And linetype(k).y = linetype(k + 1).y0) Then
                GoTo insertlineloop    '�˳�
             End If
             k = k + 1
       Wend
insertlineloop:
       If k > j Then k = j   '�������������ֵʱ,ȡ��������ֵ
       m = i
       While (m - 1 > 0)   '��������ߵ���ʼλ��
             If Not (linetype(m - 1).x = linetype(m).x0 And linetype(m - 1).y = linetype(m).y0) Then
                GoTo insertlineloop3    '�˳�
             End If
             m = m - 1
       Wend
insertlineloop3:
       If m < 1 Then m = 1   '��С��������Сֵʱȡ������Сֵ
       
       ReDim jhj(k - m) As linetype
       For n = 0 To k - m '�������ݴ�����
           jhj(n) = linetype(m + n)
       Next n
       For n = 0 To j - k - 1 '�Ѻ�ߵ���ǰ��
           linetype(m + n) = linetype(k + 1 + n)
       Next n
       For n = 0 To k - m    '���ݴ������е�ֵ�ƻ������е����
           linetype(j - (k - m) + n) = jhj(n)
       Next n
       j = j - (k - m)   'ȡ�ò�׽����Ŀ�����
       i = m        '������I�������ߵ���ʼ��
       LinePoint = j   '�ò�׽ֱ��ָ��
       j = j - 1    '��������Ľ���
End Sub

'��׽ֱ��
'���㷨��ȱ��,���㷨��׽������ֱ�߶������߶�,ֻ��������׽ʱ
Public Sub snapeline(x As Single, y As Single, object As Object, linetype As linetype, LinePoint As Integer)
Dim i, j
       j = UBound(linetype)
       For i = 1 To j
           If j < i Then Exit For 'GoTo snapelineloop  '�˳�
           If Select_Line_Ok(x, y, linetype(i).x0, linetype(i).y0, linetype(i).x, linetype(i).y) Then
              insertline i, j, object
              If j < i Then Exit For ' GoTo snapelineloop  '�˳�
              i = i - 1    '�ؼ�ֹλ
           End If
       Next i
       'If i > UBound(linetype) Then linepoint = -4: Exit Sub
snapelineloop:
End Sub

'�ж��Ƿ�׽������
Private Function snaperectangle1(x As Single, y As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single) As Boolean
If fMainForm.TCurrentOperist = "fieldselectobject" Then
   If math.pointinrectangle(X1, Y1, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey) And math.pointinrectangle(X2, Y2, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey) Then
      snaperectangle1 = True
      Exit Function
   End If
   snaperectangle1 = False
   Exit Function
End If
        If (x > X1 - snapefield And x < X2 + snapefield) Or (x < X1 + snapefield And x > X2 - snapefield) Then
           If (y > Y1 - snapefield And y < Y2 + snapefield) Or (y < Y1 + snapefield And y < Y2 - snapefield) Then
              If Abs(x - X1) < snapefield Or Abs(x - X2) < snapefield Or Abs(y - Y1) < snapefield Or Abs(y - Y2) < snapefield Then snaperectangle1 = True: Exit Function
           End If
        End If
        snaperectangle1 = False
End Function

'���뵽������������
Private Sub insertrectangle(i, j)
Dim jh As linetype
       jh = RectangleType(j)
       RectangleType(j) = RectangleType(i)
       RectangleType(i) = jh
       RectanglePoint = j
       j = j - 1
End Sub

'��׽�����ʾ�ľ���
Public Sub snaperectangle(x As Single, y As Single, object As Object)
Dim i, j
       j = UBound(RectangleType)
       For i = 1 To j
           If j < i Then GoTo snaperectangleloop
           If snaperectangle1(x, y, RectangleType(i).x0, RectangleType(i).y0, RectangleType(i).x, RectangleType(i).y) Then
              insertrectangle i, j
              If j < i Then GoTo snaperectangleloop
              i = i - 1
           End If
       Next i
snaperectangleloop:
       'If i > UBound(rectangletype) Then rectanglepoint = -4: Exit Sub 'û�в�׽�����˳�
End Sub

'�ж��Ƿ�׽���ĵ��ʾ�ľ���
Private Function snaperectanglefourpoint1(x As Single, y As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single) As Boolean
        If Select_Line_Ok(x, y, X1, Y1, X2, Y2) Then snaperectanglefourpoint1 = True: Exit Function
        If Select_Line_Ok(x, y, X1, Y1, x3, y3) Then snaperectanglefourpoint1 = True: Exit Function
        If Select_Line_Ok(x, y, x4, y4, X2, Y2) Then snaperectanglefourpoint1 = True: Exit Function
        If Select_Line_Ok(x, y, x3, y3, x4, y4) Then snaperectanglefourpoint1 = True: Exit Function
        snaperectanglefourpoint1 = False
End Function

'�Ѳ�׽�����ĵ��ʾ�ľ��β��뵽��������
Private Sub insertrectanglefourpoint(i, j)
Dim jh As RectangleFourpointType
       jh = RectangleFourpointType(j)
       RectangleFourpointType(j) = RectangleFourpointType(i)
       RectangleFourpointType(i) = jh
       RectanglefourPoint = j
       j = j - 1
End Sub

'��׽�ĵ��ʾ�ľ���
       '   1_________2
       '   |         |
       '   |         |
       '  3|_________|4
Public Sub snapefourrectangle(x As Single, y As Single, object As Object)
Dim i, j
       j = UBound(RectangleFourpointType)
       For i = 1 To j
           If j < i Then Exit For 'GoTo snaperectangleloop
           If snaperectanglefourpoint1(x, y, RectangleFourpointType(i).X1, RectangleFourpointType(i).Y1, RectangleFourpointType(i).X2, RectangleFourpointType(i).Y2, RectangleFourpointType(i).x3, RectangleFourpointType(i).y3, RectangleFourpointType(i).x4, RectangleFourpointType(i).y4) Then
              insertrectanglefourpoint i, j
              If j < i Then Exit For 'GoTo snaperectangleloop
              i = i - 1
           End If
       Next i
snaperectangleloop:
       'If i > UBound(rectanglefourpointtype) Then rectanglefourpoint = -4: Exit Sub  'û�в�׽�����˳�
       
End Sub

'��׽���������β����������
Private Sub insertthreeangle(i, j)
Dim jh As ThreeAngleType
       jh = ThreeAngleType(j)
       ThreeAngleType(j) = ThreeAngleType(i)
       ThreeAngleType(i) = jh
       ThreeanglePoint = j
       j = j - 1
End Sub

'�ж��Ƿ�׽��������
Private Function snapetrheeangle1(x As Single, y As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single, x3 As Single, y3 As Single) As Boolean
        If Select_Line_Ok(x, y, X1, Y1, X2, Y2) Then snapetrheeangle1 = True: Exit Function
        If Select_Line_Ok(x, y, X1, Y1, x3, y3) Then snapetrheeangle1 = True: Exit Function
        If Select_Line_Ok(x, y, x3, y3, X2, Y2) Then snapetrheeangle1 = True: Exit Function
        snapetrheeangle1 = False
End Function

'��׽������
Public Sub snapethreeangle(x As Single, y As Single, object As Object)
Dim i, j
       j = UBound(ThreeAngleType)
       For i = 1 To j
           If j < i Then GoTo snapethreeangleloop
           If snapetrheeangle1(x, y, ThreeAngleType(i).X1, ThreeAngleType(i).Y1, ThreeAngleType(i).X2, ThreeAngleType(i).Y2, ThreeAngleType(i).x3, ThreeAngleType(i).y3) Then
              insertthreeangle i, j
              If j < i Then GoTo snapethreeangleloop
              i = i - 1
           End If
       Next i
snapethreeangleloop:
       'If i > UBound(threeangletype) Then threeanglepoint = -4: Exit Sub 'û�в�׽�����˳�
End Sub

'�ж��Ƿ�׽��������
Private Function snapsamerectanglej(x As Single, y As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single) As Boolean
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single
        If Select_Line_Ok(x, y, X1, Y1, X2, Y2) Then snapsamerectanglej = True: Exit Function
        '��֪�����ε�������������
        math.samerectanglethreeandforupiont X1, Y1, X2, Y2, x3, y3, x4, y4
        If Select_Line_Ok(x, y, X1, Y1, x3, y3) Then snapsamerectanglej = True: Exit Function
        If Select_Line_Ok(x, y, x4, y4, X2, Y2) Then snapsamerectanglej = True: Exit Function
        If Select_Line_Ok(x, y, x4, y4, x3, y3) Then snapsamerectanglej = True: Exit Function
        snapsamerectanglej = False
End Function

'�Ѳ�׽���������β�����������
Private Sub insersamerectangle(i, j)
Dim jh As linetype
       jh = SameRectangleType(j)
       SameRectangleType(j) = SameRectangleType(i)
       SameRectangleType(i) = jh
       SameRectanglePoint = j
       j = j - 1
End Sub

'��׽������
Public Sub snapesamerectangle(x As Single, y As Single, object As Object)
Dim i, j, x3 As Single, y3 As Single, x4 As Single, y4 As Single
       j = UBound(SameRectangleType)
       For i = 1 To j
           If j < i Then GoTo snapesamerectangleloop  '�˳�
           If snapsamerectanglej(x, y, SameRectangleType(i).x0, SameRectangleType(i).y0, SameRectangleType(i).x, SameRectangleType(i).y) Then
              insersamerectangle i, j
              If j < i Then GoTo snapesamerectangleloop  '�˳�
              i = i - 1    '�ؼ�ֹλ
           End If
       Next i
       'If i > UBound(samerectangletype) Then samerectanglepoint = -4: Exit Sub
snapesamerectangleloop:
End Sub

'�ж��Ƿ�׽����������
Private Function snapesixegdej(x As Single, y As Single, X1 As Single, Y1 As Single, X2 As Single, Y2 As Single) As Boolean
Dim x3 As Single, y3 As Single, x4 As Single, y4  As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
        If Select_Line_Ok(x, y, X1, Y1, X2, Y2) Then snapesixegdej = True: Exit Function
        '��֪�����������ĵ�
        math.sixegdefour X1, Y1, X2, Y2, x3, y3, x4, y4, x5, y5, x6, y6
        If Select_Line_Ok(x, y, X1, Y1, x3, y3) Then snapesixegdej = True: Exit Function
        If Select_Line_Ok(x, y, x6, y6, X2, Y2) Then snapesixegdej = True: Exit Function
        If Select_Line_Ok(x, y, x3, y3, x4, y4) Then snapesixegdej = True: Exit Function
        If Select_Line_Ok(x, y, x4, y4, x5, y5) Then snapesixegdej = True: Exit Function
        If Select_Line_Ok(x, y, x5, y5, x6, y6) Then snapesixegdej = True: Exit Function
        snapesixegdej = False
End Function

'�Ѳ�׽�����������β����ҵ����
Private Sub insertsixegde(i, j)
Dim jh As linetype
       jh = SixegdeType(j)
       SixegdeType(j) = SixegdeType(i)
       SixegdeType(i) = jh
       SixegdePoint = j
       j = j - 1
End Sub

'��׽��������
Public Sub snapesixegde(x As Single, y As Single, object As Object)
Dim i, j, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
       j = UBound(SixegdeType)
       For i = 1 To j
           If j < i Then GoTo snapesixegdeloop  '�˳�
           If snapesixegdej(x, y, SixegdeType(i).x0, SixegdeType(i).y0, SixegdeType(i).x, SixegdeType(i).y) Then
              insertsixegde i, j
              If j < i Then GoTo snapesixegdeloop  '�˳�
              i = i - 1    '�ؼ�ֹλ
           End If
       Next i
       If i > UBound(SixegdeType) Then SixegdePoint = -4: Exit Sub
snapesixegdeloop:
                                   
End Sub

'�ж��Ƿ�׽��Բ
Public Function Select_Circle_Ok(x As Single, y As Single, X1 As Single, Y1 As Single, r As Single, snapefield As Integer) As Boolean
Dim d, k
If fMainForm.TCurrentOperist = "fieldselectobject" Then
   If math.pointinrectangle(X1 - r, Y1 - r, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey) And math.pointinrectangle(X1 + r, Y1 + r, Mouseleftdownx, Mouseleftdowny, Mousepausex, Mousepausey) Then
      Select_Circle_Ok = True
      Exit Function
   End If
   Select_Circle_Ok = False
   Exit Function
End If
        k = math.TwoPointDirection(x, y, X1, Y1)
        d = Abs(k - r)
        If d < snapefield Then
           Select_Circle_Ok = True
        Else
           Select_Circle_Ok = False
        End If
End Function

'����Բ��������
Public Sub InsertCircle(i, j)
Dim jh As CircleType
       jh = CircleType(j)
       CircleType(j) = CircleType(i)
       CircleType(i) = jh
       CirclePoint = j
       j = j - 1
End Sub

'��׽Բ
Public Sub snapecircle(x As Single, y As Single, object As Object)
Dim i, j
       j = UBound(CircleType)
       For i = 1 To j
           If j < i Then GoTo snapecircleloop
           If Select_Circle_Ok(x, y, CircleType(i).x, CircleType(i).y, CircleType(i).r) Then
              InsertCircle i, j
              If j < i Then GoTo snapecircleloop
              i = i - 1
           End If
       Next i
snapecircleloop:
       'If i > UBound(circletype) Then circlepoint = -4: Exit Sub 'û�в�׽�����˳�
End Sub

'�ж��Ƿ�׽��Բ��
Private Function snapearc1(x As Single, y As Single, X1 As Single, Y1 As Single, r As Single, Start, enda) As Boolean
Dim xx, yy, a
'If fmainform.Tcurrentoperist = "fieldselectobject" Then
   
'End If
        If Select_Circle_Ok(x, y, X1, Y1, r) Then
           xx = x - X1
           yy = y - Y1
           a = math.Angle(xx, yy)
           'Բ��
           If enda > Start And Start > 0 Then
              If a > Abs(Start) And a < Abs(enda) Then snapearc1 = True: Exit Function
           End If
           If enda < Start And enda > 0 Then
              If (a > Start And a <= Pi * 2) Or (a >= 0 And a < enda) Then snapearc1 = True: Exit Function
           End If
           '����
           If enda < 0 And Start < 0 Then
              If Start < enda Then
                 If (a > Abs(Start) And a < Pi * 2) Or (a >= 0 And a < Abs(enda)) Then snapearc1 = True: Exit Function
              Else
                 If a < Abs(enda) And a > Abs(Start) Then snapearc1 = True: Exit Function
              End If
           End If
        End If
        snapearc1 = False
End Function

'���뵽Բ���������
Private Sub insertarc(i, j)
Dim jh As ArcType
       jh = ArcType(j)
       ArcType(j) = ArcType(i)
       ArcType(i) = jh
       Arcpoint = j
       j = j - 1
End Sub

'��׽Բ��
Public Sub snapearc(x As Single, y As Single, object As Object)
Dim i, j
       j = UBound(ArcType)
       For i = 1 To j
           If j < i Then GoTo snapearcloop
           If snapearc1(x, y, ArcType(i).x, ArcType(i).y, ArcType(i).r, ArcType(i).Start, ArcType(i).end) Then
              insertarc i, j
              If j < i Then GoTo snapearcloop
              i = i - 1
           End If
       Next i
snapearcloop:
       If i > UBound(ArcType) Then Arcpoint = -4: Exit Sub 'û�в�׽�����˳�
       'ͻ����ʾ
       Form1.Savecommvar '�������Ͳ���
       object.DrawMode = VBRUN.vbXorPen
       For i = Arcpoint To UBound(ArcType)
           object.DrawWidth = ArcType(i).comvar.Width
           object.DrawStyle = ArcType(i).comvar.Style
           object.Circle (ArcType(i).x, ArcType(i).y), ArcType(i).r, Snapecolor, ArcType(i).Start, ArcType(i).end
       Next i
       Form1.redocommvar '�ָ����Ͳ���
End Sub

'��ѡȡĿ��ǰ���ǰ����ѡ��Ŀ��
Public Sub selectobjectclare(x As Single, y As Single, object As Object)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
Dim i
    Form1.Savecommvar '�������Ͳ���
    object.DrawMode = VBRUN.vbCopyPen
    'ֱ��
    If LinePoint > 0 Then
       For i = LinePoint To UBound(linetype)
            object.DrawWidth = linetype(i).comvar.Width
            object.DrawStyle = linetype(i).comvar.Style
           object.Line (linetype(i).x, linetype(i).y)-(linetype(i).x0, linetype(i).y0), linetype(i).comvar.col  'snapecolor
       Next i
    End If
    'Բ
    If CirclePoint > 0 Then
       For i = CirclePoint To UBound(CircleType)
            object.DrawWidth = CircleType(i).comvar.Width
            object.DrawStyle = CircleType(i).comvar.Style
           object.Circle (CircleType(i).x, CircleType(i).y), CircleType(i).r, CircleType(i).comvar.col 'snapecolor
       Next i
    End If
    '������
    If ThreeanglePoint > 0 Then
       For i = ThreeanglePoint To UBound(ThreeAngleType)
           object.DrawWidth = ThreeAngleType(i).comvar.Width
           object.DrawStyle = ThreeAngleType(i).comvar.Style
           object.Line (ThreeAngleType(i).X1, ThreeAngleType(i).Y1)-(ThreeAngleType(i).X2, ThreeAngleType(i).Y2), ThreeAngleType(i).comvar.col 'snapecolor
           object.Line -(ThreeAngleType(i).x3, ThreeAngleType(i).y3), ThreeAngleType(i).comvar.col 'snapecolor
           object.Line -(ThreeAngleType(i).X1, ThreeAngleType(i).Y1), ThreeAngleType(i).comvar.col  'snapecolor
       Next i
    End If
    '����
    If RectanglePoint > 0 Then
       For i = RectanglePoint To UBound(RectangleType)
           object.DrawWidth = RectangleType(i).comvar.Width
           object.DrawStyle = RectangleType(i).comvar.Style
           object.Line (RectangleType(i).x0, RectangleType(i).y0)-(RectangleType(i).x, RectangleType(i).y0), RectangleType(i).comvar.col 'snapecolor
           object.Line -(RectangleType(i).x, RectangleType(i).y), RectangleType(i).comvar.col 'snapecolor
           object.Line -(RectangleType(i).x0, RectangleType(i).y), RectangleType(i).comvar.col ' snapecolor
           object.Line -(RectangleType(i).x0, RectangleType(i).y0), RectangleType(i).comvar.col ' snapecolor
       Next i
    End If
    '�ĵ��ʾ�ľ���
    If RectanglefourPoint > 0 Then
       For i = RectanglefourPoint To UBound(RectangleFourpointType)
           object.DrawWidth = RectangleFourpointType(i).comvar.Width
           object.DrawStyle = RectangleFourpointType(i).comvar.Style
           draw.DrawForuegde object, RectangleFourpointType(i).X1, RectangleFourpointType(i).Y1, RectangleFourpointType(i).X2, RectangleFourpointType(i).Y2, RectangleFourpointType(i).x3, RectangleFourpointType(i).y3, RectangleFourpointType(i).x4, RectangleFourpointType(i).y4, RectangleFourpointType(i).comvar.col
       Next i
   End If
    '������
    If SameRectanglePoint > 0 Then
       For i = SameRectanglePoint To UBound(SameRectangleType)
           object.DrawWidth = SameRectangleType(i).comvar.Width
           object.DrawStyle = SameRectangleType(i).comvar.Style
           math.samerectanglethreeandforupiont SameRectangleType(i).x0, SameRectangleType(i).y0, SameRectangleType(i).x, SameRectangleType(i).y, x3, y3, x4, y4
           draw.DrawForuegde object, SameRectangleType(i).x0, SameRectangleType(i).y0, SameRectangleType(i).x, SameRectangleType(i).y, x3, y3, x4, y4, SameRectangleType(i).comvar.col 'snapecolor
       Next i
    End If
           '��������
    If SixegdePoint > 0 Then
       For i = SixegdePoint To UBound(SixegdeType)
           math.sixegdefour SixegdeType(i).x0, SixegdeType(i).y0, SixegdeType(i).x, SixegdeType(i).y, x3, y3, x4, y4, x5, y5, x6, y6
           object.DrawWidth = SixegdeType(i).comvar.Width
           object.DrawStyle = SixegdeType(i).comvar.Style
           draw.drawsixegde object, SixegdeType(i).x0, SixegdeType(i).y0, SixegdeType(i).x, SixegdeType(i).y, x3, y3, x4, y4, x5, y5, x6, y6, SixegdeType(i).comvar.col  'snapecolor
       Next i
    End If
    'Բ��
    If Arcpoint > 0 Then
       For i = Arcpoint To UBound(ArcType)
           object.DrawWidth = ArcType(i).comvar.Width
           object.DrawStyle = ArcType(i).comvar.Style
           object.Circle (ArcType(i).x, ArcType(i).y), ArcType(i).r, ArcType(i).comvar.col, ArcType(i).Start, ArcType(i).end
       Next i
    End If
    Form1.redocommvar '�ָ����Ͳ���
       
    'If linepoint = -4 Or _
    circlepoint = -4 Or _
    threeanglepoint = -4 Or _
    rectanglepoint = -4 Or _
    arcpoint = -4 Or _
    samerectanglepoint = -4 Or _
    sixegdepoint <> -4 Or _
    rectanglefourpoint <> -4 Then
       '�����׽����
       Form1.Savecommvar '�������Ͳ���
       object.DrawMode = VBRUN.vbXorPen
       object.DrawStyle = 1
       object.DrawWidth = 1
       'draw.drawrectangle object, snapefieldtype.x1, snapefieldtype.y1, snapefieldtype.x2, snapefieldtype.y2, snapecolor
       Dim fil
       fil = object.FillStyle
       object.FillStyle = 1
       '��׽����
       With SnapefieldType
         If .X1 >= 0 And .Y1 >= 0 And .X2 >= 0 And .Y2 >= 0 Then
           object.Line (SnapefieldType.X1, SnapefieldType.Y1)-(SnapefieldType.X2, SnapefieldType.Y2), Snapecolor, B
           object.FillStyle = fil
            draw.showpoint .X1, .Y1, object, Snapecolor  '��׽���εĵ�
            draw.showpoint .X2, .Y2, object, Snapecolor
            draw.showpoint .X1, .Y2, object, Snapecolor
            draw.showpoint .X2, .Y1, object, Snapecolor
            .X1 = -1    '�����ǰ�Ĳ�׽����
            .X2 = -1
            .Y1 = -1
            .Y2 = -1
         End If
       End With
       Form1.redocommvar '��ԭ���Ͳ���
       
    'End If
     Clearpoint
End Sub

'���ѡȡ��ָ��
Public Sub Clearpoint()
    LinePoint = -4
    CirclePoint = -4
    ThreeanglePoint = -4
    RectanglePoint = -4
    Arcpoint = -4
    SameRectanglePoint = -4
    SixegdePoint = -4
    RectanglefourPoint = -4
End Sub

'ѡȡĿ��
Public Sub selectobject(x As Single, y As Single, object As Object)   '����ѡȡĿ��
 Dim i
       snape.snapeline x, y, object  'ֱ��
       snape.snapecircle x, y, object 'Բ
       snape.snaperectangle x, y, object '�����ʾ�ľ���
       snape.snapefourrectangle x, y, object '�ĵ��ʾ�ľ���
       snapethreeangle x, y, object  ' ������
       snapearc x, y, object    'Բ��������
       snapesamerectangle x, y, object '������
       snapesixegde x, y, object '��������
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
    If LinePoint > 0 Then
       For i = LinePoint To UBound(linetype)
           '����׽��ʾ���θ�ֵ
           With SnapefieldType
                If .X1 = -1 And .X2 = -1 And .Y1 = -1 And .Y2 = -1 Then
                   .X1 = math.MinTwoNum(linetype(i).x, linetype(i).x0)
                   .X2 = math.MaxTwoNum(linetype(i).x, linetype(i).x0)
                   .Y1 = math.MinTwoNum(linetype(i).y0, linetype(i).y)
                   .Y2 = math.MaxTwoNum(linetype(i).y0, linetype(i).y)
                Else
                   .X1 = math.MinThreeNum(.X1, linetype(i).x0, linetype(i).x)
                   .X2 = math.MaxThreeNum(.X2, linetype(i).x0, linetype(i).x)
                   .Y1 = math.MinThreeNum(.Y1, linetype(i).y0, linetype(i).y)
                   .Y2 = math.MaxThreeNum(.Y2, linetype(i).y0, linetype(i).y)
               End If
            End With
            If flag Then '��ʾĿ��
               object.DrawWidth = linetype(i).comvar.Width
               object.DrawStyle = linetype(i).comvar.Style
               object.Line (linetype(i).x, linetype(i).y)-(linetype(i).x0, linetype(i).y0), Snapecolor
            End If
       Next i
    End If
    
       'ͻ����ʾѡȡ�ľ���
    If RectanglePoint > 0 Then
       For i = RectanglePoint To UBound(RectangleType)
           '����׽��ʾ���θ�ֵ
           With SnapefieldType
           If .X1 = -1 And .X2 = -1 And .Y1 = -1 And .Y2 = -1 Then
                .X1 = math.MinTwoNum(RectangleType(i).x0, RectangleType(i).x)
                .X2 = math.MaxTwoNum(RectangleType(i).x0, RectangleType(i).x)
                .Y1 = math.MinTwoNum(RectangleType(i).y0, RectangleType(i).y)
                .Y2 = math.MaxTwoNum(RectangleType(i).y0, RectangleType(i).y)
           Else
                .X1 = math.MinThreeNum(.X1, RectangleType(i).x0, RectangleType(i).x)
                .X2 = math.MaxThreeNum(.X2, RectangleType(i).x0, RectangleType(i).x)
                .Y1 = math.MinThreeNum(.Y1, RectangleType(i).y0, RectangleType(i).y)
                .Y2 = math.MaxThreeNum(.Y2, RectangleType(i).y0, RectangleType(i).y)
           End If
           End With
            If flag Then
               object.DrawWidth = RectangleType(i).comvar.Width
               object.DrawStyle = RectangleType(i).comvar.Style
               object.Line (RectangleType(i).x0, RectangleType(i).y0)-(RectangleType(i).x, RectangleType(i).y0), Snapecolor
               object.Line -(RectangleType(i).x, RectangleType(i).y), Snapecolor
               object.Line -(RectangleType(i).x0, RectangleType(i).y), Snapecolor
               object.Line -(RectangleType(i).x0, RectangleType(i).y0), Snapecolor
            End If
       Next i
    End If
    
       'ͻ����ʾ�ĵ��ʾ�ľ���
    If RectanglefourPoint > 0 Then
       For i = RectanglefourPoint To UBound(RectangleFourpointType)
           '����׽��ʾ���θ�ֵ
           With SnapefieldType
           If .X1 = -1 And .X2 = -1 And .Y1 = -1 And .Y2 = -1 Then
                .X1 = math.MinTwoNum(RectangleFourpointType(i).X1, RectangleFourpointType(i).X2)
                .X1 = math.MinThreeNum(.X1, RectangleFourpointType(i).x3, RectangleFourpointType(i).x4)
                .X2 = math.MaxTwoNum(RectangleFourpointType(i).X1, RectangleFourpointType(i).X2)
                .X2 = math.MaxThreeNum(.X2, RectangleFourpointType(i).x3, RectangleFourpointType(i).x4)
                .Y1 = math.MinTwoNum(RectangleFourpointType(i).Y1, RectangleFourpointType(i).Y2)
                .Y1 = math.MinThreeNum(.Y1, RectangleFourpointType(i).y3, RectangleFourpointType(i).y4)
                .Y2 = math.MaxTwoNum(RectangleFourpointType(i).Y1, RectangleFourpointType(i).Y2)
                .Y2 = math.MaxThreeNum(.Y2, RectangleFourpointType(i).y3, RectangleFourpointType(i).y4)
            Else
                .X1 = math.MinThreeNum(.X1, RectangleFourpointType(i).X1, RectangleFourpointType(i).X2)
                .X1 = math.MinThreeNum(.X1, RectangleFourpointType(i).x3, RectangleFourpointType(i).x4)
                .X2 = math.MaxThreeNum(.X2, RectangleFourpointType(i).X1, RectangleFourpointType(i).X2)
                .X2 = math.MaxThreeNum(.X2, RectangleFourpointType(i).x3, RectangleFourpointType(i).x4)
                .Y1 = math.MinThreeNum(.Y1, RectangleFourpointType(i).Y1, RectangleFourpointType(i).Y2)
                .Y1 = math.MinThreeNum(.Y1, RectangleFourpointType(i).y3, RectangleFourpointType(i).y4)
                .Y2 = math.MaxThreeNum(.Y2, RectangleFourpointType(i).Y1, RectangleFourpointType(i).Y2)
                .Y2 = math.MaxThreeNum(.Y2, RectangleFourpointType(i).y3, RectangleFourpointType(i).y4)
            End If
            End With
            If flag Then '��ʾĿ��
               object.DrawWidth = RectangleFourpointType(i).comvar.Width
               object.DrawStyle = RectangleFourpointType(i).comvar.Style
               draw.DrawForuegde object, RectangleFourpointType(i).X1, RectangleFourpointType(i).Y1, RectangleFourpointType(i).X2, RectangleFourpointType(i).Y2, RectangleFourpointType(i).x3, RectangleFourpointType(i).y3, RectangleFourpointType(i).x4, RectangleFourpointType(i).y4, Snapecolor
            End If
       Next i
    End If

       'ͻ����ʾ������
    If ThreeanglePoint > 0 Then
       For i = ThreeanglePoint To UBound(ThreeAngleType)
           '����׽��ʾ���θ�ֵ
           With SnapefieldType
           If .X1 = -1 And .X2 = -1 And .Y1 = -1 And .Y2 = -1 Then
                .X1 = math.MinThreeNum(ThreeAngleType(i).x3, ThreeAngleType(i).X1, ThreeAngleType(i).X2)
                .X2 = math.MaxThreeNum(ThreeAngleType(i).x3, ThreeAngleType(i).X1, ThreeAngleType(i).X2)
                .Y1 = math.MinThreeNum(ThreeAngleType(i).y3, ThreeAngleType(i).Y1, ThreeAngleType(i).Y2)
                .Y2 = math.MaxThreeNum(ThreeAngleType(i).y3, ThreeAngleType(i).Y1, ThreeAngleType(i).Y2)
           Else
                .X1 = math.MinThreeNum(.X1, ThreeAngleType(i).X1, ThreeAngleType(i).X2)
                .X1 = math.MinTwoNum(.X1, ThreeAngleType(i).x3)
                .X2 = math.MaxThreeNum(.X2, ThreeAngleType(i).X1, ThreeAngleType(i).X2)
                .X2 = math.MaxTwoNum(.X2, ThreeAngleType(i).x3)
                .Y1 = math.MinThreeNum(.Y1, ThreeAngleType(i).Y1, ThreeAngleType(i).Y2)
                .Y1 = math.MinTwoNum(.Y1, ThreeAngleType(i).y3)
                .Y2 = math.MaxThreeNum(.Y2, ThreeAngleType(i).Y1, ThreeAngleType(i).Y2)
                .Y2 = math.MaxTwoNum(.Y2, ThreeAngleType(i).y3)
           End If
           End With
           If flag Then '��ʾĿ��
              object.DrawWidth = ThreeAngleType(i).comvar.Width
              object.DrawStyle = ThreeAngleType(i).comvar.Style
              object.Line (ThreeAngleType(i).X1, ThreeAngleType(i).Y1)-(ThreeAngleType(i).X2, ThreeAngleType(i).Y2), Snapecolor
              object.Line -(ThreeAngleType(i).x3, ThreeAngleType(i).y3), Snapecolor
              object.Line -(ThreeAngleType(i).X1, ThreeAngleType(i).Y1), Snapecolor
           End If
       Next i
    End If

       'ͻ����ʾѡ����������
    If SameRectanglePoint > 0 Then
    Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
       For i = SameRectanglePoint To UBound(SameRectangleType)
           math.samerectanglethreeandforupiont SameRectangleType(i).x0, SameRectangleType(i).y0, SameRectangleType(i).x, SameRectangleType(i).y, x3, y3, x4, y4
           With SnapefieldType  '��ѡȡ��Χ��ֵ
           If .X1 = -1 And .X2 = -1 And .Y1 = -1 And .Y2 = -1 Then
                .X1 = math.MinTwoNum(math.MinThreeNum(SameRectangleType(i).x0, SameRectangleType(i).x, x3), x4)
                .X2 = math.MaxTwoNum(math.MaxThreeNum(SameRectangleType(i).x0, SameRectangleType(i).x, x3), x4)
                .Y1 = math.MinTwoNum(math.MinThreeNum(SameRectangleType(i).y0, SameRectangleType(i).y, y3), y4)
                .Y2 = math.MaxTwoNum(math.MaxThreeNum(SameRectangleType(i).y0, SameRectangleType(i).y, y3), y4)
           Else
                .X1 = math.MinThreeNum(.X1, math.MinThreeNum(SameRectangleType(i).x0, SameRectangleType(i).x, x3), x4)
                .X2 = math.MaxThreeNum(.X2, math.MaxThreeNum(SameRectangleType(i).x0, SameRectangleType(i).x, x3), x4)
                .Y1 = math.MinThreeNum(.Y1, math.MinThreeNum(SameRectangleType(i).y0, SameRectangleType(i).y, y3), y4)
                .Y2 = math.MaxThreeNum(.Y2, math.MaxThreeNum(SameRectangleType(i).y0, SameRectangleType(i).y, y3), y4)
           End If
           End With
           If flag Then '��ʾĿ��
              object.DrawWidth = SameRectangleType(i).comvar.Width
              object.DrawStyle = SameRectangleType(i).comvar.Style
              draw.DrawForuegde object, SameRectangleType(i).x0, SameRectangleType(i).y0, SameRectangleType(i).x, SameRectangleType(i).y, x3, y3, x4, y4, Snapecolor
           End If
       Next i
    End If
       
       'ͻ����ʾѡ������������
    If SixegdePoint > 0 Then
       For i = SixegdePoint To UBound(SixegdeType)
           math.sixegdefour SixegdeType(i).x0, SixegdeType(i).y0, SixegdeType(i).x, SixegdeType(i).y, x3, y3, x4, y4, x5, y5, x6, y6
           With SnapefieldType   '��ѡȡ��Χ��ֵ
           If .X1 = -1 And .X2 = -1 And .Y1 = -1 And .Y2 = -1 Then
                .X1 = math.MinTwoNum(math.MinThreeNum(SixegdeType(i).x0, SixegdeType(i).x, x3), math.MinThreeNum(x4, x5, x6))
                .X2 = math.MaxTwoNum(math.MaxThreeNum(SixegdeType(i).x0, SixegdeType(i).x, x3), math.MaxThreeNum(x4, x5, x6))
                .Y1 = math.MinTwoNum(math.MinThreeNum(SixegdeType(i).y0, SixegdeType(i).y, y3), math.MinThreeNum(y4, y5, y6))
                .Y2 = math.MaxTwoNum(math.MaxThreeNum(SixegdeType(i).y0, SixegdeType(i).y, y3), math.MaxThreeNum(y4, y5, y6))
           Else
                .X1 = math.MinThreeNum(.X1, math.MinThreeNum(SixegdeType(i).x0, SixegdeType(i).x, x3), math.MinThreeNum(x4, x5, x6))
                .X2 = math.MaxThreeNum(.X2, math.MaxThreeNum(SixegdeType(i).x0, SixegdeType(i).x, x3), math.MaxThreeNum(x4, x5, x6))
                .Y1 = math.MinThreeNum(.Y1, math.MinThreeNum(SixegdeType(i).y0, SixegdeType(i).y, y3), math.MinThreeNum(y4, y5, y6))
                .Y2 = math.MaxThreeNum(.Y2, math.MaxThreeNum(SixegdeType(i).y0, SixegdeType(i).y, y3), math.MaxThreeNum(y4, y5, y6))
           End If
           End With
           If flag Then '��ʾĿ��
               object.DrawWidth = SixegdeType(i).comvar.Width
               object.DrawStyle = SixegdeType(i).comvar.Style
               draw.drawsixegde object, SixegdeType(i).x0, SixegdeType(i).y0, SixegdeType(i).x, SixegdeType(i).y, x3, y3, x4, y4, x5, y5, x6, y6, Snapecolor
            End If
       Next i
    End If
       
       'ͻ����ʾѡȡ����Բ
    If CirclePoint > 0 Then
       For i = CirclePoint To UBound(CircleType)
            With SnapefieldType
            If .X1 = -1 And .X2 = -1 And .Y1 = -1 And .Y2 = -1 Then
                 .X1 = math.MinTwoNum(CircleType(i).x + CircleType(i).r, CircleType(i).x - CircleType(i).r)
                 .X2 = math.MaxTwoNum(CircleType(i).x + CircleType(i).r, CircleType(i).x - CircleType(i).r)
                 .Y1 = math.MinTwoNum(CircleType(i).y + CircleType(i).r, CircleType(i).y - CircleType(i).r)
                 .Y2 = math.MaxTwoNum(CircleType(i).y + CircleType(i).r, CircleType(i).y - CircleType(i).r)
            Else
                 .X1 = math.MinThreeNum(.X1, CircleType(i).x + CircleType(i).r, CircleType(i).x - CircleType(i).r)
                 .X2 = math.MaxThreeNum(.X2, CircleType(i).x + CircleType(i).r, CircleType(i).x - CircleType(i).r)
                 .Y1 = math.MinThreeNum(.Y1, CircleType(i).y + CircleType(i).r, CircleType(i).y - CircleType(i).r)
                 .Y2 = math.MaxThreeNum(.Y2, CircleType(i).y + CircleType(i).r, CircleType(i).y - CircleType(i).r)
            End If
            End With
            If flag Then '��ʾĿ��
               object.DrawWidth = CircleType(i).comvar.Width
               object.DrawStyle = CircleType(i).comvar.Style
               object.Circle (CircleType(i).x, CircleType(i).y), CircleType(i).r, Snapecolor
            End If
       Next i
    End If
       
       '��ʾ��׽����
       object.DrawWidth = 1
       object.DrawStyle = 1
       Dim fil
       fil = object.FillStyle
       object.FillStyle = 1
       'draw.drawrectangle object, snapefieldtype.x1, snapefieldtype.y1, snapefieldtype.x2, snapefieldtype.y2, snapecolor
       object.Line (SnapefieldType.X1, SnapefieldType.Y1)-(SnapefieldType.X2, SnapefieldType.Y2), Snapecolor, B
       object.FillStyle = fil
       With SnapefieldType
            draw.showpoint .X1, .Y1, object, Snapecolor
            draw.showpoint .X2, .Y2, object, Snapecolor
            draw.showpoint .X1, .Y2, object, Snapecolor
            draw.showpoint .X2, .Y1, object, Snapecolor
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
       'draw.drawrectangle object, snapefieldtype.x1, snapefieldtype.y1, snapefieldtype.x2, snapefieldtype.y2, snapecolor
       object.Line (SnapefieldType.X1, SnapefieldType.Y1)-(SnapefieldType.X2, SnapefieldType.Y2), Snapecolor, B
       object.FillStyle = fil
       With SnapefieldType
            draw.showpoint .X1, .Y1, object, Snapecolor
            draw.showpoint .X2, .Y2, object, Snapecolor
            draw.showpoint .X1, .Y2, object, Snapecolor
            draw.showpoint .X2, .Y1, object, Snapecolor
       End With
       Form1.redocommvar  '��ԭ���Ͳ���

End Sub

'ѡȡԲ��,����,��Բ
Public Function Select_Arc_Ok(ByVal x As Single, ByVal y As Single, ByVal x0 As Single, ByVal y0 As Single, ByVal Radius As Single, ByVal Start As Double, ByVal Eend As Double, ByVal Aspect As Double, ByVal SelectField As Integer) As Boolean
Dim a As Double, xx As Single, yy As Single
If Aspect = 0 Then 'Բ��,����
   If TwoPointDirection(x, y, x0, y0) > (Radius + SelectField) Or ((TwoPointDirection(x, y, x0, y0) < (Radius - SelectField)) And Start > 0) Then
      Select_Arc_Ok = False
      Exit Function
   End If
   a = Angle(x - x0, y - y0)
   If Start < a And a < Eend And Start > 0 And Start < Eend Then
      Select_Arc_Ok = True
      Exit Function
   End If
   If ((Start < a And a < 2 * Pi) Or (a < Eend And a > 0)) And Eend > 0 And Start > Eend Then
      Select_Arc_Ok = True
      Exit Function
   End If
   
   If Start < 0 Then '���ε�����
      ArcRoundpoint xx, yy, x0, y0, Radius, Start
      If Select_Line_Ok(x, y, x0, y0, xx, yy, SelectField) Then
         Select_Arc_Ok = True
         Exit Function
      End If
      ArcRoundpoint xx, yy, x0, y0, Radius, Eend
      If Select_Line_Ok(x, y, x0, y0, xx, yy, SelectField) Then
         Select_Arc_Ok = True
         Exit Function
      End If
   End If
   If TwoPointDirection(x, y, x0, y0) < (Radius - SelectField) Then
      Select_Arc_Ok = False
      Exit Function
   End If
   If Abs(Start) < a And a < Abs(Eend) And Start < 0 And Start > Eend Then
      Select_Arc_Ok = True
      Exit Function
   End If
   If ((Abs(Start) < a And a < 2 * Pi) Or (a < Abs(Eend) And a > 0)) And Eend < 0 And Start < Eend Then
      Select_Arc_Ok = True
      Exit Function
   End If
   Select_Arc_Ok = False
End If
'��Բ
a = Angle(x - x0, y - y0)
If Aspect < 1 And Aspect > 0 Then
   xx = x0 + Radius * Cos(a)
   yy = y0 - Radius * Aspect * Sin(a)
Else
   If Aspect > 1 Then
    xx = x0 + (Radius / Aspect) * Cos(a)
    yy = y0 - Radius * Sin(a)
   End If
End If
If TwoPointDirection(xx, yy, x, y) <= SelectField Then
      Select_Arc_Ok = True
      Exit Function
End If
Select_Arc_Ok = False
End Function
