Attribute VB_Name = "edit"
Option Explicit

'自己的前粘板
Public Ipointype() As pointstruct
Public IlineType() As LineType
Public Irectangletype() As LineType
Public Irectanglefourpointtype() As RectangleFourpointType
Public Icircletype() As CircleType
Public Iellipsetype() As EllipseType
Public Iarctype() As ArcType
Public Ithreeangletype() As ThreeAngleType
Public Isamerectangletype() As LineType
Public Isixegdetype() As LineType
Public Itext() As text

Public Sub Init()  '数组初始化

       ReDim Ipointype(0)    '开辟点的存储区
       ReDim IlineType(0)   '开辟直线存储区
       ReDim Irectangletype(0)  '开辟钜形存储区
       ReDim Irectanglefourpointtype(0)  '开辟四点表示矩形讴
       ReDim Icircletype(0)    '开辟圆存储区
       ReDim Iellipsetype(0)   '开辟椭圆存储区
       ReDim Iarctype(0)      '开辟圆弧的存储区
       ReDim Ithreeangletype(0)    '开辟三角形的存储区
       ReDim Isamerectangletype(0)   '开辟正方形存储区
       ReDim Isixegdetype(0)       '开辟正六边形存储区
       ReDim Itext(0)      '开辟文本存储区

End Sub

Public Function Mecopy() As Boolean
Dim i As Long, N As Long, j As Long
       
       Init
       j = user.LinePoint
       If j > 0 Then
          N = UBound(user.LineType) - j + 1
          ReDim Preserve IlineType(N)
          For i = 1 To N
              IlineType(i) = user.LineType(j + i - 1)
          Next i
       End If
       
       j = user.RectanglePoint
       If j > 0 Then
          N = UBound(user.RectangleType) - j + 1
          ReDim Preserve Irectangletype(N)
          For i = 1 To N
              Irectangletype(i) = user.RectangleType(j + i - 1)
          Next i
       End If
       
       j = user.RectanglefourPoint
       If j > 0 Then
          N = UBound(user.RectangleFourpointType) - j + 1
          ReDim Preserve Irectanglefourpointtype(N)
          For i = 1 To N
              Irectanglefourpointtype(i) = user.RectangleFourpointType(j + i - 1)
          Next i
       End If
       
       j = user.CirclePoint
       If j > 0 Then
          N = UBound(user.CircleType) - j + 1
          ReDim Preserve Icircletype(N)
          For i = 1 To N
              Icircletype(i) = user.CircleType(j + i - 1)
          Next i
       End If
       
       j = user.ArcPoint
       If j > 0 Then
          N = UBound(user.ArcType) - j + 1
          ReDim Preserve Iarctype(N)
          For i = 1 To N
              Iarctype(i) = user.ArcType(j + i - 1)
          Next i
       End If
       
       j = user.ThreeanglePoint
       If j > 0 Then
          N = UBound(user.ThreeAngleType) - j + 1
          ReDim Preserve Ithreeangletype(N)
          For i = 1 To N
              Ithreeangletype(i) = user.ThreeAngleType(j + i - 1)
          Next i
       End If
       
       j = user.SameRectanglePoint
       If j > 0 Then
          N = UBound(user.SameRectangleType) - j + 1
          ReDim Preserve Isamerectangletype(N)
          For i = 1 To N
              Isamerectangletype(i) = user.SameRectangleType(j + i - 1)
          Next i
       End If
       
       j = user.SixegdePoint
       If j > 0 Then
          N = UBound(user.SixegdeType) - j + 1
          ReDim Preserve Isixegdetype(N)
          For i = 1 To N
              Isixegdetype(i) = user.SixegdeType(j + i - 1)
          Next i
       End If
       
End Function

'粘贴
Public Sub Mepase()
Dim i As Long, N As Long, j As Long
       j = UBound(IlineType)
       user.LinePoint = -4
       If j >= 1 Then
          N = UBound(user.LineType)
          user.LinePoint = N + 1  '赋指针
          ReDim Preserve user.LineType(N + j)
          For i = 1 To j
              user.LineType(i + N) = IlineType(i)
          Next i
       End If
       
       user.RectanglePoint = -4
       j = UBound(Irectangletype)
       If j >= 1 Then
          N = UBound(user.RectangleType)
          user.RectanglePoint = N + 1
          ReDim Preserve user.RectangleType(N + j)
          For i = 1 To j
              user.RectangleType(N + i) = Irectangletype(i)
          Next i
       End If
       
       user.RectanglefourPoint = -4
       j = UBound(Irectanglefourpointtype)
       If j > 0 Then
          N = UBound(user.RectangleFourpointType)
          user.RectanglefourPoint = N + 1
          ReDim Preserve user.RectangleFourpointType(j + N)
          For i = 1 To j
              user.RectangleFourpointType(N + i) = Irectanglefourpointtype(i)
          Next i
       End If
       
       user.CirclePoint = -4
       j = UBound(Icircletype)
       If j > 0 Then
          N = UBound(user.CircleType)
          user.CirclePoint = N + 1
          ReDim Preserve user.CircleType(N + j)
          For i = 1 To j
              user.CircleType(N + i) = Icircletype(i)
          Next i
       End If
       
       user.ArcPoint = -4
       j = UBound(Iarctype)
       If j > 0 Then
          N = UBound(user.ArcType)
          user.ArcPoint = N + 1
          ReDim Preserve user.ArcType(N + j)
          For i = 1 To j
              user.ArcType(N + i) = Iarctype(i)
          Next i
       End If
       
       user.ThreeanglePoint = -4
       j = UBound(Ithreeangletype)
       If j > 0 Then
          N = UBound(user.ThreeAngleType)
          user.ThreeanglePoint = N + 1
          ReDim Preserve user.ThreeAngleType(N + j)
          For i = 1 To j
              user.ThreeAngleType(N + i) = Ithreeangletype(i)
          Next i
       End If
       
       user.SameRectanglePoint = -4
       j = UBound(Isamerectangletype)
       If j > 0 Then
          N = UBound(user.SameRectangleType)
          user.SameRectanglePoint = N + 1
          ReDim Preserve user.SameRectangleType(N + j)
          For i = 1 To j
              user.SameRectangleType(N + i) = Isamerectangletype(i)
          Next i
       End If
       
       user.SixegdePoint = -4
       j = UBound(Isixegdetype)
       If j > 0 Then
          N = UBound(user.SixegdeType)
          user.SixegdePoint = N + 1
          ReDim Preserve user.SixegdeType(N + j)
          For i = 1 To j
              user.SixegdeType(N + i) = Isixegdetype(i)
          Next i
       End If
                
       draw.redraw
       'snape.showselectobject Form1.cad, True
End Sub

'目标移动
Public Sub Move(X As Single, Y As Single, object As Object, Button As Integer)
Dim xx, yy, i, mode, styp, widt
Form1.Savecommvar  '保存线型参数
   If Button = VBRUN.vbLeftButton Then
       
       object.DrawMode = VBRUN.vbNotXorPen
       xx = X - user.Mouseleftdownx
       yy = Y - user.mouseleftdowny
       
       EditStype xx, yy, object, user.Snapecolor, 0
       
       xx = user.Mousepausex - user.Mouseleftdownx
       yy = user.mousepausey - user.mouseleftdowny
       
       EditStype xx, yy, object, user.Snapecolor, 0
       user.Mousepausex = X
       user.mousepausey = Y
       
    End If
    Form1.redocommvar '恢复线型参数
End Sub

'确定移动后的图形
Public Sub Moveadd(X As Single, Y As Single, object As Object, copy As Boolean)
Dim xx, yy
       xx = X - user.Mouseleftdownx
       yy = Y - user.mouseleftdowny
       If copy Then
          Addmove xx, yy, 1 '更新移动后的数组值
       Else
          Addmove xx, yy, 0
       End If
       Form1.Savecommvar   '保存参数
       object.DrawMode = VBRUN.vbCopyPen
       EditStype 0, 0, object, vbBlack, 1
       Form1.redocommvar '恢复参数
       draw.redraw
End Sub


'移动后改变数组值
'当flag=1时拷贝图形
Private Sub Addmove(xx, yy, flag)
Dim i, j, k, m
'With user.snapefieldtype
'     .x1 = .x1 + xx
'     .y1 = .y1 + yy
'     .x2 = .x2 + xx
'     .y2 = .y2 + yy
'     End With
If flag = 1 Then   '拷贝
       i = user.LinePoint
       If i > 0 Then
       j = UBound(user.LineType)
       m = j + 1
       ReDim Preserve user.LineType(j + (j - i) + 1)
       k = j + j - i + 1
       user.LinePoint = m    '把捕捉指针赋为拷贝目标
       While (m <= k And i > 0)
             user.LineType(m) = user.LineType(i)   '赋公共值
             With user.LineType(m)
                  .x0 = .x0 + xx
                  .y0 = .y0 + yy
                  .X = .X + xx
                  .Y = .Y + yy
             End With
             m = m + 1
             i = i + 1
       Wend
       End If
       '三角形
       i = user.ThreeanglePoint
       If i > 0 Then
       j = UBound(user.ThreeAngleType)
           ReDim Preserve user.ThreeAngleType(j + (j - i) + 1)
           k = j + j - i + 1
           m = j + 1
           user.ThreeanglePoint = m
       While (m <= k And i > 0)
              user.ThreeAngleType(m) = user.ThreeAngleType(i)
              With user.ThreeAngleType(m)
                   .x1 = .x1 + xx
                   .x2 = .x2 + xx
                   .x3 = .x3 + xx
                   .y1 = .y1 + yy
                   .y2 = .y2 + yy
                   .y3 = .y3 + yy
              End With
              i = i + 1
              m = m + 1
       Wend
       End If
       '矩形
       i = user.RectanglePoint
       If i > 0 Then
       j = UBound(user.RectangleType)
           ReDim Preserve user.RectangleType(j + (j - i) + 1)
           k = j + j - i + 1
           m = j + 1
           user.RectanglePoint = m
       While (m <= k And i > 0)
             user.RectangleType(m) = user.RectangleType(i)
              With user.RectangleType(m)
                   .X = .X + xx
                   .x0 = .x0 + xx
                   .Y = .Y + yy
                   .y0 = .y0 + yy
              End With
              i = i + 1
              m = m + 1
       Wend
       End If
       '四点表示的矩形
       i = user.RectanglefourPoint
       If i > 0 Then
          m = UBound(user.RectangleFourpointType) + 1
          ReDim Preserve user.RectangleFourpointType(UBound(user.RectangleFourpointType) * 2 - i + 1)
          user.RectanglefourPoint = m
       While (m <= UBound(user.RectangleFourpointType) And i > 0)
             With user.RectangleFourpointType(m)
                  user.RectangleFourpointType(m) = user.RectangleFourpointType(i)
                  .x1 = .x1 + xx
                  .x2 = .x2 + xx
                  .x3 = .x3 + xx
                  .x4 = .x4 + xx
                  .y1 = .y1 + yy
                  .y2 = .y2 + yy
                  .y3 = .y3 + yy
                  .y4 = .y4 + yy
                  End With
            i = i + 1
            m = m + 1
      Wend
      End If
       '圆
       i = user.CirclePoint
       If i > 0 Then
       j = UBound(user.CircleType)
           ReDim Preserve user.CircleType(j + (j - i) + 1)
           k = j + j - i + 1
           m = j + 1
           user.CirclePoint = m
       While (m <= k And i > 0)
              user.CircleType(m) = user.CircleType(i)
             With user.CircleType(m)
                  .X = .X + xx
                  .Y = .Y + yy
             End With
             i = i + 1
             m = m + 1
       Wend
       End If
       '圆弧
       i = user.ArcPoint
       If i > 0 Then
       j = UBound(user.ArcType)
           ReDim Preserve user.ArcType(j + (j - i) + 1)
           k = j + j - i + 1
           m = j + 1
           user.ArcPoint = m
       While (m <= k And i > 0)
           user.ArcType(m) = user.ArcType(i)
             With user.ArcType(m)
                  .X = .X + xx
                  .Y = .Y + yy
             End With
             i = i + 1
             m = m + 1
       Wend
       End If
       '椭圆
       
       '正方形
       i = user.SameRectanglePoint
       If i > 0 Then
       j = UBound(user.SameRectangleType)
           ReDim Preserve user.SameRectangleType(j + (j - i) + 1)
           k = j + j - i + 1
           m = j + 1
           user.SameRectanglePoint = m
       While (m <= k And i > 0)
             '求顶点
             user.SameRectangleType(m) = user.SameRectangleType(i)
             With user.SameRectangleType(m)
                  .X = .X + xx
                  .x0 = .x0 + xx
                  .Y = .Y + yy
                  .y0 = .y0 + yy
             End With
             i = i + 1
             m = m + 1
       Wend
       End If
       '正六边形
       i = user.SixegdePoint
       If i > 0 Then
       j = UBound(user.SixegdeType)
           ReDim Preserve user.SixegdeType(j + (j - i) + 1)
           k = j + j - i + 1
           m = j + 1
           user.SixegdePoint = m
       While (m <= k And i > 0)
           user.SixegdeType(m) = user.SixegdeType(i)
              '求顶点
              With user.SixegdeType(m)
                   .X = .X + xx
                   .Y = .Y + yy
                   .x0 = .x0 + xx
                   .y0 = .y0 + yy
              End With
              i = i + 1
              m = m + 1
       Wend
       End If
Else    '移动
       '直线
       i = user.LinePoint
       j = UBound(user.LineType)
       While (i <= j And i > 0)
             With user.LineType(i)
                  .x0 = .x0 + xx
                  .y0 = .y0 + yy
                  .X = .X + xx
                  .Y = .Y + yy
             End With
             i = i + 1
       Wend
       '三角形
       i = user.ThreeanglePoint
       j = UBound(user.ThreeAngleType)
       If flag = 1 Then
           i = j + 1
           ReDim Preserve user.ThreeAngleType(j + (j - i) + 1)
           j = j + j - i + 1
       End If
       While (i <= j And i > 0)
              With user.ThreeAngleType(i)
                   .x1 = .x1 + xx
                   .x2 = .x2 + xx
                   .x3 = .x3 + xx
                   .y1 = .y1 + yy
                   .y2 = .y2 + yy
                   .y3 = .y3 + yy
              End With
              i = i + 1
       Wend
       '矩形
       i = user.RectanglePoint
       j = UBound(user.RectangleType)
       If flag = 1 Then
           i = j + 1
           ReDim Preserve user.RectangleType(j + (j - i) + 1)
           j = j + j - i + 1
       End If
       While (i <= j And i > 0)
              With user.RectangleType(i)
                   .X = .X + xx
                   .x0 = .x0 + xx
                   .Y = .Y + yy
                   .y0 = .y0 + yy
              End With
              i = i + 1
       Wend
       '四点表示的矩形
       i = user.RectanglefourPoint
       While (i <= UBound(user.RectangleFourpointType) And i > 0)
             With user.RectangleFourpointType(i)
                  .x1 = .x1 + xx
                  .x2 = .x2 + xx
                  .x3 = .x3 + xx
                  .x4 = .x4 + xx
                  .y1 = .y1 + yy
                  .y2 = .y2 + yy
                  .y3 = .y3 + yy
                  .y4 = .y4 + yy
                  End With
            i = i + 1
      Wend
       '圆
       i = user.CirclePoint
       j = UBound(user.CircleType)
       If flag = 1 Then
           i = j + 1
           ReDim Preserve user.CircleType(j + (j - i) + 1)
           j = j + j - i + 1
       End If
       While (i <= j And i > 0)
             With user.CircleType(i)
                  .X = .X + xx
                  .Y = .Y + yy
             End With
             i = i + 1
       Wend
       '圆弧
       i = user.ArcPoint
       j = UBound(user.ArcType)
       If flag = 1 Then
           i = j + 1
           ReDim Preserve user.ArcType(j + (j - i) + 1)
           j = j + j - i + 1
       End If
       While (i <= j And i > 0)
             With user.ArcType(i)
                  .X = .X + xx
                  .Y = .Y + yy
             End With
             i = i + 1
       Wend
       '椭圆
       
       '正方形
       i = user.SameRectanglePoint
       j = UBound(user.SameRectangleType)
       If flag = 1 Then
           i = j + 1
           ReDim Preserve user.SameRectangleType(j + (j - i) + 1)
           j = j + j - i + 1
       End If
       While (i <= j And i > 0)
             '求顶点
             With user.SameRectangleType(i)
                  .X = .X + xx
                  .x0 = .x0 + xx
                  .Y = .Y + yy
                  .y0 = .y0 + yy
             End With
             i = i + 1
       Wend
       '正六边形
       i = user.SixegdePoint
       j = UBound(user.SixegdeType)
       If flag = 1 Then
           i = j + 1
           ReDim Preserve user.SixegdeType(j + (j - i) + 1)
           j = j + j - i + 1
       End If
       While (i <= j And i > 0)
              '求顶点
              With user.SixegdeType(i)
                   .X = .X + xx
                   .Y = .Y + yy
                   .x0 = .x0 + xx
                   .y0 = .y0 + yy
              End With
              i = i + 1
       Wend
End If
End Sub

'编辑移动类型
'标志位用来判断颜色为col值还是本身和颜色
'当flag=1时用本身的颜色,否则用col值
Private Sub EditStype(xx, yy, object As Object, col As ColorConstants, flag)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
Dim styp, widt, i
       '显示捕捉矩形
       styp = object.DrawStyle
       widt = object.DrawWidth
       object.DrawStyle = 1
       object.DrawWidth = 1
       draw.drawrectangle object, user.SnapefieldType.x1 + xx, user.SnapefieldType.y1 + yy, user.SnapefieldType.x2 + xx, user.SnapefieldType.y2 + yy, user.Snapecolor
       object.DrawStyle = styp
       '直线
       i = user.LinePoint
       While (i <= UBound(user.LineType) And i > 0)
             If flag = 1 Then col = user.LineType(i).comvar.col
            object.DrawWidth = user.LineType(i).comvar.width
            object.DrawStyle = user.LineType(i).comvar.style
           object.Line (user.LineType(i).X + xx, user.LineType(i).Y + yy)-(user.LineType(i).x0 + xx, user.LineType(i).y0 + yy), col
           i = i + 1
       Wend
       '三角形
       i = user.ThreeanglePoint
       While (i <= UBound(user.ThreeAngleType) And i > 0)
              If flag = 1 Then col = user.ThreeAngleType(i).comvar.col
           object.DrawWidth = user.ThreeAngleType(i).comvar.width
           object.DrawStyle = user.ThreeAngleType(i).comvar.style
              draw.drawthreeangle object, user.ThreeAngleType(i).x1 + xx, user.ThreeAngleType(i).y1 + yy, user.ThreeAngleType(i).x2 + xx, user.ThreeAngleType(i).y2 + yy, user.ThreeAngleType(i).x3 + xx, user.ThreeAngleType(i).y3 + yy, col
              i = i + 1
       Wend
       '矩形
       i = user.RectanglePoint
       While (i <= UBound(user.RectangleType) And i > 0)
              If flag = 1 Then col = user.RectangleType(i).comvar.col
           object.DrawWidth = user.RectangleType(i).comvar.width
           object.DrawStyle = user.RectangleType(i).comvar.style
              draw.drawrectangle object, user.RectangleType(i).x0 + xx, user.RectangleType(i).y0 + yy, user.RectangleType(i).X + xx, user.RectangleType(i).Y + yy, col
              i = i + 1
       Wend
       '四点表示的矩形
       i = user.RectanglefourPoint
       While (i <= UBound(user.RectangleFourpointType) And i > 0)
             object.DrawWidth = user.RectangleFourpointType(i).comvar.width
             object.DrawStyle = user.RectangleFourpointType(i).comvar.style
             draw.drawforuegde object, user.RectangleFourpointType(i).x1 + xx, yy + user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2 + xx, user.RectangleFourpointType(i).y2 + yy, xx + user.RectangleFourpointType(i).x3, yy + user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4 + xx, yy + user.RectangleFourpointType(i).y4, col
       i = i + 1
       Wend
       '圆
       i = user.CirclePoint
       While (i <= UBound(user.CircleType) And i > 0)
              If flag = 1 Then col = user.CircleType(i).comvar.col
            object.DrawWidth = user.CircleType(i).comvar.width
            object.DrawStyle = user.CircleType(i).comvar.style
            object.Circle (user.CircleType(i).X + xx, user.CircleType(i).Y + yy), user.CircleType(i).r, col
            i = i + 1
       Wend
       '圆弧
       i = user.ArcPoint
       While (i <= UBound(user.ArcType) And i > 0)
              If flag = 1 Then col = user.ArcType(i).comvar.col
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           object.Circle (user.ArcType(i).X + xx, user.ArcType(i).Y + yy), user.ArcType(i).r, col, user.ArcType(i).start, user.ArcType(i).end
           i = i + 1
       Wend
       '椭圆
       
       '正方形
       i = user.SameRectanglePoint
       While (i <= UBound(user.SameRectangleType) And i > 0)
              If flag = 1 Then col = user.SameRectangleType(i).comvar.col
             '求顶点
           object.DrawWidth = user.SameRectangleType(i).comvar.width
           object.DrawStyle = user.SameRectangleType(i).comvar.style
             math.samerectanglethreeandforupiont user.SameRectangleType(i).x0 + xx, user.SameRectangleType(i).y0 + yy, user.SameRectangleType(i).X + xx, user.SameRectangleType(i).Y + yy, x3, y3, x4, y4
            draw.drawforuegde object, user.SameRectangleType(i).x0 + xx, user.SameRectangleType(i).y0 + yy, user.SameRectangleType(i).X + xx, user.SameRectangleType(i).Y + yy, x3, y3, x4, y4, col
             i = i + 1
       Wend
       '正六边形
       i = user.SixegdePoint
       While (i <= UBound(user.SixegdeType) And i > 0)
              If flag = 1 Then col = user.SixegdeType(i).comvar.col
              '求顶点
              math.sixegdefour user.SixegdeType(i).x0 + xx, user.SixegdeType(i).y0 + yy, user.SixegdeType(i).X + xx, user.SixegdeType(i).Y + yy, x3, y3, x4, y4, x5, y5, x6, y6
           object.DrawWidth = user.SixegdeType(i).comvar.width
           object.DrawStyle = user.SixegdeType(i).comvar.style
              draw.drawsixegde object, user.SixegdeType(i).x0 + xx, user.SixegdeType(i).y0 + yy, user.SixegdeType(i).X + xx, user.SixegdeType(i).Y + yy, x3, y3, x4, y4, x5, y5, x6, y6, col
              i = i + 1
       Wend
End Sub

'水平翻转
Public Sub Roundh(object As Object, col As ColorConstants)
Dim yy
    yy = (user.SnapefieldType.y1 + user.SnapefieldType.y2) / 2
       Form1.Savecommvar '保存参数
       object.DrawMode = VBRUN.vbNotXorPen
       Mirrorstype 0, 0, 1, 1, object, col, 0
       Mirrorstype 0, 2 * yy, 1, -1, object, col, 1
       Form1.redocommvar '恢复参数
       draw.redraw
End Sub

'垂直翻转
Public Sub Roundv(object As Object, col As ColorConstants)
Dim xx
    xx = (user.SnapefieldType.x1 + user.SnapefieldType.x2) / 2
       Form1.Savecommvar '保存参数
       object.DrawMode = VBRUN.vbNotXorPen
       Mirrorstype 0, 0, 1, 1, object, col, 0
       Mirrorstype 2 * xx, 0, -1, 1, object, col, 1
       Form1.redocommvar '恢复参数
     draw.redraw
End Sub

'编辑翻转类型
Private Sub Mirrorstype(xx, yy, nx, ny, object As Object, col As ColorConstants, flag)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single, i
Dim x1 As Single, x2 As Single, y1 As Single, y2 As Single         '直线
       i = user.LinePoint
       While (i <= UBound(user.LineType) And i > 0)
            object.DrawWidth = user.LineType(i).comvar.width
            object.DrawStyle = user.LineType(i).comvar.style
            If flag = 1 Then
               With user.LineType(i)
                    .X = .X * nx + xx
                    .Y = .Y * ny + yy
                    .x0 = .x0 * nx + xx
                    .y0 = .y0 * ny + yy
               End With
            End If
           object.Line (nx * user.LineType(i).X + xx, ny * user.LineType(i).Y + yy)-(nx * user.LineType(i).x0 + xx, ny * user.LineType(i).y0 + yy), col
           i = i + 1
       Wend
       '三角形
       i = user.ThreeanglePoint
       While (i <= UBound(user.ThreeAngleType) And i > 0)
           object.DrawWidth = user.ThreeAngleType(i).comvar.width
           object.DrawStyle = user.ThreeAngleType(i).comvar.style
           If flag = 1 Then
               With user.ThreeAngleType(i)
                    .x1 = .x1 * nx + xx
                    .x2 = .x2 * nx + xx
                    .x3 = .x3 * nx + xx
                    .y1 = .y1 * ny + yy
                    .y2 = .y2 * ny + yy
                    .y3 = .y3 * ny + yy
                    End With
           End If
              draw.drawthreeangle object, user.ThreeAngleType(i).x1 * nx + xx, ny * user.ThreeAngleType(i).y1 + yy, user.ThreeAngleType(i).x2 * nx + xx, ny * user.ThreeAngleType(i).y2 + yy, nx * user.ThreeAngleType(i).x3 + xx, user.ThreeAngleType(i).y3 * ny + yy, col
              i = i + 1
       Wend
       '矩形
       i = user.RectanglePoint
       While (i <= UBound(user.RectangleType) And i > 0)
           object.DrawWidth = user.RectangleType(i).comvar.width
           object.DrawStyle = user.RectangleType(i).comvar.style
           If flag = 1 Then
              With user.RectangleType(i)
                    .X = .X * nx + xx
                    .Y = .Y * ny + yy
                    .x0 = .x0 * nx + xx
                    .y0 = .y0 * ny + yy
               End With
            End If
              draw.drawrectangle object, nx * user.RectangleType(i).x0 + xx, ny * user.RectangleType(i).y0 + yy, user.RectangleType(i).X * nx + xx, user.RectangleType(i).Y * ny + yy, col
              i = i + 1
       Wend
       '四点表示的矩形
       i = user.RectanglefourPoint
       While (i <= UBound(user.RectangleFourpointType) And i > 0)
              object.DrawWidth = user.RectangleFourpointType(i).comvar.width
              object.DrawStyle = user.RectangleFourpointType(i).comvar.style
              If flag = 1 Then
              With user.RectangleFourpointType(i)
                .x1 = .x1 * nx + xx
                .y1 = .y1 * ny + yy
                .x2 = .x2 * nx + xx
                .y2 = .y2 * ny + yy
                .x3 = .x3 * nx + xx
                .y3 = .y3 * ny + yy
                .x4 = .x4 * nx + xx
                .y4 = .y4 * ny + yy
              End With
           End If
           With user.RectangleFourpointType(i)
                x1 = .x1 * nx + xx
                x2 = .x2 * nx + xx
                x3 = .x3 * nx + xx
                x4 = .x4 * nx + xx
                y1 = .y1 * ny + yy
                y2 = .y2 * ny + yy
                y3 = .y3 * ny + yy
                y4 = .y4 * ny + yy
           End With
           draw.drawforuegde object, x1, y1, x2, y2, x3, y3, x4, y4, col
              i = i + 1
        Wend
             '圆
       i = user.CirclePoint
       While (i <= UBound(user.CircleType) And i > 0)
            object.DrawWidth = user.CircleType(i).comvar.width
            object.DrawStyle = user.CircleType(i).comvar.style
            If flag = 1 Then
                With user.CircleType(i)
                     .X = .X * nx + xx
                     .Y = .Y * ny + yy
                     End With
            End If
            object.Circle (nx * user.CircleType(i).X + xx, ny * user.CircleType(i).Y + yy), user.CircleType(i).r, col
             i = i + 1
       Wend
       '圆弧
       i = user.ArcPoint
       While (i <= UBound(user.ArcType) And i > 0)
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           If flag = 1 Then
                With user.ArcType(i)
                     .X = .X * nx + xx
                     .Y = .Y * ny + yy
                     End With
           End If
           object.Circle (nx * user.ArcType(i).X + xx, ny * user.ArcType(i).Y + yy), user.ArcType(i).r, col, user.ArcType(i).start, user.ArcType(i).end
           i = i + 1
       Wend
       '椭圆
       
       '正方形
       i = user.SameRectanglePoint
       While (i <= UBound(user.SameRectangleType) And i > 0)
             '求顶点
           object.DrawWidth = user.SameRectangleType(i).comvar.width
           object.DrawStyle = user.SameRectangleType(i).comvar.style
            math.samerectanglethreeandforupiont user.SameRectangleType(i).x0 * nx + xx, ny * user.SameRectangleType(i).y0 + yy, user.SameRectangleType(i).X * nx + xx, ny * user.SameRectangleType(i).Y + yy, x3, y3, x4, y4
            If flag = 1 Then
               With user.SameRectangleType(i)
                     .X = .X * nx + xx
                    .Y = .Y * ny + yy
                    .x0 = .x0 * nx + xx
                    .y0 = .y0 * ny + yy
               End With
            End If
            draw.drawforuegde object, nx * user.SameRectangleType(i).x0 + xx, ny * user.SameRectangleType(i).y0 + yy, nx * user.SameRectangleType(i).X + xx, user.SameRectangleType(i).Y * ny + yy, x3, y3, x4, y4, col
             i = i + 1
       Wend
       '正六边形
       i = user.SixegdePoint
       While (i <= UBound(user.SixegdeType) And i > 0)
              '求顶点
           math.sixegdefour nx * user.SixegdeType(i).x0 + xx, ny * user.SixegdeType(i).y0 + yy, nx * user.SixegdeType(i).X + xx, ny * user.SixegdeType(i).Y + yy, x3, y3, x4, y4, x5, y5, x6, y6
           object.DrawWidth = user.SixegdeType(i).comvar.width
           object.DrawStyle = user.SixegdeType(i).comvar.style
           If flag = 1 Then
           With user.SixegdeType(i)
                    .X = .X * nx + xx
                    .Y = .Y * ny + yy
                    .x0 = .x0 * nx + xx
                    .y0 = .y0 * ny + yy
               End With
            End If
           draw.drawsixegde object, nx * user.SixegdeType(i).x0 + xx, ny * user.SixegdeType(i).y0 + yy, user.SixegdeType(i).X * nx + xx, user.SixegdeType(i).Y * ny + yy, x3, y3, x4, y4, x5, y5, x6, y6, col
              i = i + 1
       Wend
End Sub

'目标旋转
Public Sub Round(X As Single, Y As Single, object As Object, Button As Integer, col As ColorConstants, flag)
Dim a As Double, xx, yy
If Button = VBRUN.vbLeftButton Then
   Form1.Savecommvar   '保存参数
   object.DrawMode = VBRUN.vbNotXorPen
        '清除参考图形
           '参考直线
       draw.singleline Button, user.Mousepausex, user.mousepausey, col, object
       xx = user.Mousepausex - user.Mouseleftdownx
       yy = user.mousepausey - user.mouseleftdowny
       a = 2 * user.pi - math.angle(xx, yy)
       If xx = 0 And yy = 0 Then a = 0     '当起点时,即鼠标刚按下时,旋转角是0度,不是90度,因为用上面公式求的是90度
       EditRound user.Mouseleftdownx, user.mouseleftdowny, a, object, col, 0
       '显示参考图形
          '参考直线
       draw.singleline Button, X, Y, col, object
       xx = X - user.Mouseleftdownx
       yy = Y - user.mouseleftdowny
       a = 2 * user.pi - math.angle(xx, yy)
       If flag = 1 Then
          EditRound user.Mouseleftdownx, user.mouseleftdowny, a, object, col, 1
          draw.redraw
          Exit Sub
       End If
       EditRound user.Mouseleftdownx, user.mouseleftdowny, a, object, col, 0
       user.Mousepausex = X
       user.mousepausey = Y
  Form1.redocommvar ' 恢复参数
End If
End Sub

'选中的目标绕选中中心旋转或任一点旋转类型
Private Sub EditRound(X As Single, Y As Single, θ As Double, object As Object, col As ColorConstants, flag)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
Dim x0 As Single, y0 As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single
Dim i
       '直线
       i = user.LinePoint
       While (i <= UBound(user.LineType) And i > 0)
            object.DrawWidth = user.LineType(i).comvar.width
            object.DrawStyle = user.LineType(i).comvar.style
            math.roundpoint x0, y0, user.LineType(i).x0, user.LineType(i).y0, X, Y, θ
            math.roundpoint x1, y1, user.LineType(i).X, user.LineType(i).Y, X, Y, θ
            If flag = 1 Then
               With user.LineType(i)
                 .x0 = x0
                 .y0 = y0
                 .X = x1
                 .Y = y1
               End With
            End If
            object.Line (x0, y0)-(x1, y1), col
            i = i + 1
       Wend
       '三角形
       i = user.ThreeanglePoint
       While (i <= UBound(user.ThreeAngleType) And i > 0)
           object.DrawWidth = user.ThreeAngleType(i).comvar.width
           object.DrawStyle = user.ThreeAngleType(i).comvar.style
           math.roundpoint x1, y1, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1, X, Y, θ
           math.roundpoint x2, y2, user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2, X, Y, θ
           math.roundpoint x3, y3, user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3, X, Y, θ
           If flag = 1 Then
           With user.ThreeAngleType(i)
                .x1 = x1
                .x2 = x2
                .x3 = x3
                .y1 = y1
                .y2 = y2
                .y3 = y3
           End With
           End If
           draw.drawthreeangle object, x1, y1, x2, y2, x3, y3, col
              i = i + 1
       Wend
       '矩形
       i = user.RectanglePoint
       While (i <= UBound(user.RectangleType) And i > 0)
           object.DrawWidth = user.RectangleType(i).comvar.width
           object.DrawStyle = user.RectangleType(i).comvar.style
           math.roundpoint x1, y1, user.RectangleType(i).x0, user.RectangleType(i).y0, X, Y, θ
           math.roundpoint x4, y4, user.RectangleType(i).X, user.RectangleType(i).Y, X, Y, θ
           math.roundpoint x2, y2, user.RectangleType(i).X, user.RectangleType(i).y0, X, Y, θ
           math.roundpoint x3, y3, user.RectangleType(i).x0, user.RectangleType(i).Y, X, Y, θ
           If flag = 1 Then
           ReDim Preserve user.RectangleFourpointType(UBound(user.RectangleFourpointType) + 1)
           With user.RectangleFourpointType(UBound(user.RectangleFourpointType))
                .x1 = x1
                .y1 = y1
                .x2 = x2
                .y2 = y2
                .x3 = x3
                .y3 = y3
                .x4 = x4
                .y4 = y4
                .comvar = user.RectangleType(i).comvar
           End With
           End If
           draw.drawforuegde object, x1, y1, x2, y2, x3, y3, x4, y4, col
              i = i + 1
       Wend
       If flag = 1 And user.RectanglePoint > 0 Then   '清除已变化的矩形
          ReDim Preserve user.RectangleType(user.RectanglePoint - 1)
       End If
       '四点表示的矩形
       i = user.RectanglefourPoint
       While (i <= UBound(user.RectangleFourpointType) And i > 0)
              object.DrawWidth = user.RectangleFourpointType(i).comvar.width
              object.DrawStyle = user.RectangleFourpointType(i).comvar.style
              math.roundpoint x1, y1, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, X, Y, θ
              math.roundpoint x2, y2, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, X, Y, θ
              math.roundpoint x3, y3, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, X, Y, θ
              math.roundpoint x4, y4, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, X, Y, θ
              If flag = 1 Then
              With user.RectangleFourpointType(i)
                .x1 = x1
                .y1 = y1
                .x2 = x2
                .y2 = y2
                .x3 = x3
                .y3 = y3
                .x4 = x4
                .y4 = y4
           End With
           End If
           draw.drawforuegde object, x1, y1, x2, y2, x3, y3, x4, y4, col
              i = i + 1
       Wend
       '圆
       i = user.CirclePoint
       While (i <= UBound(user.CircleType) And i > 0)
            object.DrawWidth = user.CircleType(i).comvar.width
            object.DrawStyle = user.CircleType(i).comvar.style
            math.roundpoint x0, y0, user.CircleType(i).X, user.CircleType(i).Y, X, Y, θ
            If flag = 1 Then
              With user.CircleType(i)
                 .X = x0
                 .Y = y0
                 End With
            End If
            object.Circle (x0, y0), user.CircleType(i).r, col
             i = i + 1
       Wend
       '圆弧
       i = user.ArcPoint
       While (i <= UBound(user.ArcType) And i > 0)
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           math.roundpoint x0, y0, user.ArcType(i).X, user.ArcType(i).Y, X, Y, θ
           If flag = 1 Then
             With user.ArcType(i)
                .X = x0
                .Y = y0
                End With
            End If
           object.Circle (x0, y0), user.ArcType(i).r, col, user.ArcType(i).start, user.ArcType(i).end
           i = i + 1
       Wend
       '椭圆
       
       '正方形
       i = user.SameRectanglePoint
       While (i <= UBound(user.SameRectangleType) And i > 0)
             '求顶点
           object.DrawWidth = user.SameRectangleType(i).comvar.width
           object.DrawStyle = user.SameRectangleType(i).comvar.style
           math.roundpoint x1, y1, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, X, Y, θ
           math.roundpoint x2, y2, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, X, Y, θ
           math.samerectanglethreeandforupiont x1, y1, x2, y2, x3, y3, x4, y4
           If flag = 1 Then
              With user.SameRectangleType(i)
                .x0 = x1
                .y0 = y1
                .X = x2
                .Y = y2
                End With
           End If
           draw.drawforuegde object, x1, y1, x2, y2, x3, y3, x4, y4, col
             i = i + 1
       Wend
       '正六边形
       i = user.SixegdePoint
       While (i <= UBound(user.SixegdeType) And i > 0)
              object.DrawWidth = user.SixegdeType(i).comvar.width
              object.DrawStyle = user.SixegdeType(i).comvar.style
              '求顶点
              math.roundpoint x1, y1, user.SixegdeType(i).x0, user.SixegdeType(i).y0, X, Y, θ
              math.roundpoint x2, y2, user.SixegdeType(i).X, user.SixegdeType(i).Y, X, Y, θ
              math.sixegdefour x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6
              If flag = 1 Then
                 With user.SixegdeType(i)
                      .x0 = x1
                      .y0 = y1
                      .X = x2
                      .Y = y2
                      End With
              End If
              draw.drawsixegde object, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, col
              i = i + 1
       Wend
        
End Sub

'镜像
Public Sub Mirror(object As Object, X As Single, Y As Single, col As ColorConstants, flag)
       Form1.Savecommvar '保存参数
       object.DrawMode = VBRUN.vbXorPen
       '清除参考图形
       EditMirror user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey, object, col, 0
       If flag = 1 Then     '确定最后图形(不保存)
          object.DrawMode = VBRUN.vbCopyPen
          EditMirror user.Mouseleftdownx, user.mouseleftdowny, X, Y, object, col, 1
          draw.redraw
          Exit Sub
       End If
       If flag = 2 Then     '确定最后图形(保存)
          object.DrawMode = VBRUN.vbCopyPen
          EditMirror user.Mouseleftdownx, user.mouseleftdowny, X, Y, object, col, 2
          draw.redraw
          Exit Sub
       End If
       
       '显示参考图形
       EditMirror user.Mouseleftdownx, user.mouseleftdowny, X, Y, object, col, 0
       Form1.redocommvar '恢复参数
       user.Mousepausex = X
       user.mousepausey = Y
End Sub

'编辑镜像类型
Private Sub EditMirror(xx1 As Single, yy1 As Single, xx2 As Single, yy2 As Single, object As Object, col As ColorConstants, flag)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single
Dim x0 As Single, y0 As Single, x1 As Single, y1 As Single, x2 As Single, y2 As Single
Dim i, j
       '直线
       i = user.LinePoint
       j = UBound(user.LineType)
       While (i <= j And i > 0)
            object.DrawWidth = user.LineType(i).comvar.width
            object.DrawStyle = user.LineType(i).comvar.style
            math.Mirror x0, y0, user.LineType(i).x0, user.LineType(i).y0, xx1, yy1, xx2, yy2
            math.Mirror x1, y1, user.LineType(i).X, user.LineType(i).Y, xx1, yy1, xx2, yy2
           If flag = 1 Then
               With user.LineType(i)
                 .x0 = x0
                 .y0 = y0
                 .X = x1
                 .Y = y1
               End With
            End If
            If flag = 2 Then
               ReDim Preserve user.LineType(UBound(user.LineType) + 1)
               user.LineType(UBound(user.LineType)) = user.LineType(i)
               With user.LineType(UBound(user.LineType))
                 .x0 = x0
                 .y0 = y0
                 .X = x1
                 .Y = y1
               End With
            End If
             object.Line (x0, y0)-(x1, y1), col
            i = i + 1
       Wend
       '三角形
       i = user.ThreeanglePoint
       j = UBound(user.ThreeAngleType)
       While (i <= j And i > 0)
           object.DrawWidth = user.ThreeAngleType(i).comvar.width
           object.DrawStyle = user.ThreeAngleType(i).comvar.style
           math.Mirror x1, y1, user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1, xx1, yy1, xx2, yy2
           math.Mirror x2, y2, user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2, xx1, yy1, xx2, yy2
           math.Mirror x3, y3, user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3, xx1, yy1, xx2, yy2
           If flag = 1 Then       '不保留原图形
           With user.ThreeAngleType(i)
                .x1 = x1
                .x2 = x2
                .x3 = x3
                .y1 = y1
                .y2 = y2
                .y3 = y3
           End With
           End If
           If flag = 2 Then  '保留原图形
              ReDim Preserve user.ThreeAngleType(UBound(user.ThreeAngleType) + 1)
              user.ThreeAngleType(UBound(user.ThreeAngleType)) = user.ThreeAngleType(i)
              With user.ThreeAngleType(UBound(user.ThreeAngleType))
                .x1 = x1
                .x2 = x2
                .x3 = x3
                .y1 = y1
                .y2 = y2
                .y3 = y3
              End With
           End If
              
           draw.drawthreeangle object, x1, y1, x2, y2, x3, y3, col
              i = i + 1
       Wend
       '矩形
       i = user.RectanglePoint
       j = UBound(user.RectangleType)
       While (i <= j And i > 0)
           object.DrawWidth = user.RectangleType(i).comvar.width
           object.DrawStyle = user.RectangleType(i).comvar.style
           math.Mirror x1, y1, user.RectangleType(i).x0, user.RectangleType(i).y0, xx1, yy1, xx2, yy2
           math.Mirror x4, y4, user.RectangleType(i).X, user.RectangleType(i).Y, xx1, yy1, xx2, yy2
           math.Mirror x2, y2, user.RectangleType(i).X, user.RectangleType(i).y0, xx1, yy1, xx2, yy2
           math.Mirror x3, y3, user.RectangleType(i).x0, user.RectangleType(i).Y, xx1, yy1, xx2, yy2
           If flag = 1 Or flag = 2 Then
           ReDim Preserve user.RectangleFourpointType(UBound(user.RectangleFourpointType) + 1)
           With user.RectangleFourpointType(UBound(user.RectangleFourpointType))
                .x1 = x1
                .y1 = y1
                .x2 = x2
                .y2 = y2
                .x3 = x3
                .y3 = y3
                .x4 = x4
                .y4 = y4
                .comvar = user.RectangleType(i).comvar
           End With
           End If
           
           draw.drawforuegde object, x1, y1, x2, y2, x3, y3, x4, y4, col
              i = i + 1
       Wend
       If flag = 1 And user.RectanglePoint >= 1 Then
           ReDim Preserve user.RectangleType(user.RectanglePoint - 1)
       End If
       '四点表示的矩形
       i = user.RectanglefourPoint
       j = UBound(user.RectangleFourpointType)
       While (i <= j And i > 0)
              object.DrawWidth = user.RectangleFourpointType(i).comvar.width
              object.DrawStyle = user.RectangleFourpointType(i).comvar.style
              math.Mirror x1, y1, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, xx1, yy1, xx2, yy2
              math.Mirror x4, y4, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, xx1, yy1, xx2, yy2
              math.Mirror x2, y2, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, xx1, yy1, xx2, yy2
              math.Mirror x3, y3, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, xx1, yy1, xx2, yy2
              If flag = 1 Then
                 With user.RectangleFourpointType(i)
                      .x1 = x1
                      .y1 = y1
                      .x2 = x2
                      .y2 = y2
                      .x3 = x3
                      .y3 = y3
                      .x4 = x4
                      .y4 = y4
                 End With
             End If
             If flag = 2 Then
                ReDim Preserve user.RectangleFourpointType(UBound(user.RectangleFourpointType) + 1)
                user.RectangleFourpointType(UBound(user.RectangleFourpointType)) = user.RectangleFourpointType(i)
                 With user.RectangleFourpointType(UBound(user.RectangleFourpointType))
                      .x1 = x1
                      .y1 = y1
                      .x2 = x2
                      .y2 = y2
                      .x3 = x3
                      .y3 = y3
                      .x4 = x4
                      .y4 = y4
                 End With
             End If
           draw.drawforuegde object, x1, y1, x2, y2, x3, y3, x4, y4, col
              i = i + 1
       Wend
       '圆
       i = user.CirclePoint
       j = UBound(user.CircleType)
       While (i <= j And i > 0)
            object.DrawWidth = user.CircleType(i).comvar.width
            object.DrawStyle = user.CircleType(i).comvar.style
            math.Mirror x0, y0, user.CircleType(i).X, user.CircleType(i).Y, xx1, yy1, xx2, yy2
            If flag = 1 Then
              With user.CircleType(i)
                 .X = x0
                 .Y = y0
                 End With
            End If
            If flag = 2 Then
               ReDim Preserve user.CircleType(UBound(user.CircleType) + 1)
               user.CircleType(UBound(user.CircleType)) = user.CircleType(i)
               With user.CircleType(UBound(user.CircleType))
                 .X = x0
                 .Y = y0
                 End With
            End If
            object.Circle (x0, y0), user.CircleType(i).r, col
             i = i + 1
       Wend
       '圆弧
       i = user.ArcPoint
       j = UBound(user.ArcType)
       While (i <= j And i > 0)
           object.DrawWidth = user.ArcType(i).comvar.width
           object.DrawStyle = user.ArcType(i).comvar.style
           math.Mirror x0, y0, user.ArcType(i).X, user.ArcType(i).Y, xx1, yy1, xx2, yy2
           If flag = 1 Then
             With user.ArcType(i)
                .X = x0
                .Y = y0
                End With
            End If
            If flag = 2 Then
            ReDim Preserve user.ArcType(UBound(user.ArcType) + 1)
            user.ArcType(UBound(user.ArcType)) = user.ArcType(i)
             With user.ArcType(UBound(user.ArcType))
                .X = x0
                .Y = y0
                End With
            End If
            
           object.Circle (x0, y0), user.ArcType(i).r, col, user.ArcType(i).start, user.ArcType(i).end
           i = i + 1
       Wend
       '椭圆
       
       '正方形
       i = user.SameRectanglePoint
       j = UBound(user.SameRectangleType)
       While (i <= j And i > 0)
             '求顶点
           object.DrawWidth = user.SameRectangleType(i).comvar.width
           object.DrawStyle = user.SameRectangleType(i).comvar.style
           '因为镜像后与原图形相反旋转,所以(x!,y1)与(x2,y2)对调
           math.Mirror x2, y2, user.SameRectangleType(i).x0, user.SameRectangleType(i).y0, xx1, yy1, xx2, yy2
           math.Mirror x1, y1, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, xx1, yy1, xx2, yy2
           math.samerectanglethreeandforupiont x1, y1, x2, y2, x3, y3, x4, y4
           If flag = 1 Then
              With user.SameRectangleType(i)
                .x0 = x1
                .y0 = y1
                .X = x2
                .Y = y2
                End With
           End If
           If flag = 2 Then
           ReDim Preserve user.SameRectangleType(UBound(user.SameRectangleType) + 1)
           user.SameRectangleType(UBound(user.SameRectangleType)) = user.SameRectangleType(i)
              With user.SameRectangleType(UBound(user.SameRectangleType))
                .x0 = x1
                .y0 = y1
                .X = x2
                .Y = y2
                End With
           End If
           
           draw.drawforuegde object, x1, y1, x2, y2, x3, y3, x4, y4, col
             i = i + 1
       Wend
       '正六边形
       i = user.SixegdePoint
       j = UBound(user.SixegdeType)
       While (i <= j And i > 0)
              object.DrawWidth = user.SixegdeType(i).comvar.width
              object.DrawStyle = user.SixegdeType(i).comvar.style
              '求顶点
              '因为镜像后与原图形相反旋转,所以(x!,y1)与(x2,y2)对调
              math.Mirror x2, y2, user.SixegdeType(i).x0, user.SixegdeType(i).y0, xx1, yy1, xx2, yy2
              math.Mirror x1, y1, user.SixegdeType(i).X, user.SixegdeType(i).Y, xx1, yy1, xx2, yy2
              math.sixegdefour x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6
              If flag = 1 Then
                 With user.SixegdeType(i)
                      .x0 = x1
                      .y0 = y1
                      .X = x2
                      .Y = y2
                      End With
              End If
              If flag = 2 Then
                 ReDim Preserve user.SixegdeType(UBound(user.SixegdeType) + 1)
                 user.SixegdeType(UBound(user.SixegdeType)) = user.SixegdeType(i)
                 With user.SixegdeType(UBound(user.SixegdeType))
                      .x0 = x1
                      .y0 = y1
                      .X = x2
                      .Y = y2
                      End With
              End If
              draw.drawsixegde object, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, col
              i = i + 1
       Wend
        
End Sub

