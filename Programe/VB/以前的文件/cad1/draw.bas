Attribute VB_Name = "draw"
'��ģ��Ϊ��ͼ����
Option Explicit

Private Declare Function TextOut Lib "gdi32" Alias "TextOutA" (ByVal hdc As Long, ByVal X As Long, ByVal Y As Long, ByVal lpString As String, ByVal nCount As Long) As Long

Public Sub redraw()
'��������:
'�ػ����е�ͼ��
'On Error Resume Next
Dim filere, i, wit, mode, style, drawflag

'filere = Loc(200)
'Seek #200, 1
'Do
'Get #200, , name
'   Select Case name
'          Case "line"
'            Get #200, , linetype
'            Form1.cad.Line (linetype.x0, linetype.y0)-(linetype.X, linetype.Y), pramcol
'          Case "circle"
'            Get #200, , circletype
'            Form1.cad.Circle (circletype.X, circletype.Y), circletype.r, pramcol
'   End Select
'i = Seek(200)
'Loop While i <= filere
'Seek #200, Seek(200)
''Form1.cad.CurrentX = mouseleftdownx + 19
'Form1.cad.CurrentY = mouseleftdowny + 1
'Form1.cad.Print "f="; filere
'Form1.cad.CurrentX = mouseleftdownx
'Form1.cad.CurrentY = mouseleftdowny
'Form1.cad.Print "s="; Seek(200)
'Form1.cad.CurrentX = mouseleftdownx + 16
'Form1.cad.CurrentY = mouseleftdowny + 2
'Form1.cad.Print "i="; i ' Loc(200)
'Form1.cad.CurrentX = mouseleftdownx + 16
'Form1.cad.CurrentY = mouseleftdowny + 3
'Form1.cad.Print "l="; Loc(200)
Form1.cad.Cls                       '�����ͼ��

'��ʾѡȡ����
With user.SnapefieldType
     If .x1 >= 0 And .y1 >= 0 And .x2 >= 0 And .y2 >= 0 Then
        snape.showselectrectangle Form1.cad
     End If
End With

'If meungirl.Checked Then      '��ʾդ��
'   For i = 1 To 29
'           For j = 1 To 42
'               Form1.cad.PSet (i * 10, j * 10), snapecolor
'           Next j
'   Next i
'End If

Form1.Savecommvar               '���湫������
Form1.cad.DrawMode = VBRUN.DrawModeConstants.vbCopyPen    '����ģʽ
For i = 1 To UBound(user.LineType)             '�ػ�����ֱ��
    Form1.cad.DrawStyle = user.LineType(i).comvar.style
    Form1.cad.DrawWidth = user.LineType(i).comvar.width
    Form1.cad.Line (user.LineType(i).x0, user.LineType(i).y0)-(user.LineType(i).X, user.LineType(i).Y), user.LineType(i).comvar.col
Next i
For i = 1 To UBound(user.ThreeAngleType)       '�ػ�����������
    Form1.cad.DrawStyle = user.ThreeAngleType(i).comvar.style
    Form1.cad.DrawWidth = user.ThreeAngleType(i).comvar.width
    Form1.cad.Line (user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1)-(user.ThreeAngleType(i).x2, user.ThreeAngleType(i).y2), user.ThreeAngleType(i).comvar.col
    Form1.cad.Line -(user.ThreeAngleType(i).x3, user.ThreeAngleType(i).y3), user.ThreeAngleType(i).comvar.col
    Form1.cad.Line -(user.ThreeAngleType(i).x1, user.ThreeAngleType(i).y1), user.ThreeAngleType(i).comvar.col
Next i
    drawflag = user.drawflag             '�����־
For i = 1 To UBound(user.SameRectangleType)   '�ػ�����������
    user.drawflag = 3
    Form1.cad.DrawWidth = user.SameRectangleType(i).comvar.width
    Form1.cad.DrawStyle = user.SameRectangleType(i).comvar.style
    user.Mouseleftdownx = user.SameRectangleType(i).x0
    user.mouseleftdowny = user.SameRectangleType(i).y0
    ������ Form1.cad, VBRUN.vbLeftButton, user.SameRectangleType(i).X, user.SameRectangleType(i).Y, user.SameRectangleType(i).comvar.col
Next i
For i = 1 To UBound(user.SixegdeType)   '�ػ���������
    user.drawflag = 3
    Form1.cad.DrawWidth = user.SixegdeType(i).comvar.width
    Form1.cad.DrawStyle = user.SixegdeType(i).comvar.style
    user.Mouseleftdownx = user.SixegdeType(i).x0
    user.mouseleftdowny = user.SixegdeType(i).y0
    �������� Form1.cad, VBRUN.vbLeftButton, user.SixegdeType(i).X, user.SixegdeType(i).Y, user.SixegdeType(i).comvar.col
Next i
    user.drawflag = drawflag         '�ָ���־
For i = 1 To UBound(user.RectangleType)    '�ػ����е������ʾ�ľ���
    Form1.cad.DrawStyle = user.RectangleType(i).comvar.style
    Form1.cad.DrawWidth = user.RectangleType(i).comvar.width
    Form1.cad.Line (user.RectangleType(i).x0, user.RectangleType(i).y0)-(user.RectangleType(i).X, user.RectangleType(i).y0), user.RectangleType(i).comvar.col
    Form1.cad.Line -(user.RectangleType(i).X, user.RectangleType(i).Y), user.RectangleType(i).comvar.col
    Form1.cad.Line -(user.RectangleType(i).x0, user.RectangleType(i).Y), user.RectangleType(i).comvar.col
    Form1.cad.Line -(user.RectangleType(i).x0, user.RectangleType(i).y0), user.RectangleType(i).comvar.col
Next i
For i = 1 To UBound(user.RectangleFourpointType)   '�ػ������ĵ��ʾ�ľ���
    draw.drawforuegde Form1.cad, user.RectangleFourpointType(i).x1, user.RectangleFourpointType(i).y1, user.RectangleFourpointType(i).x2, user.RectangleFourpointType(i).y2, user.RectangleFourpointType(i).x3, user.RectangleFourpointType(i).y3, user.RectangleFourpointType(i).x4, user.RectangleFourpointType(i).y4, user.RectangleFourpointType(i).comvar.col
Next i
For i = 1 To UBound(user.CircleType)     '�ػ�����Բ
    Form1.cad.DrawWidth = user.CircleType(i).comvar.width
    Form1.cad.DrawStyle = user.CircleType(i).comvar.style
    Form1.cad.Circle (user.CircleType(i).X, user.CircleType(i).Y), user.CircleType(i).r, user.CircleType(i).comvar.col
Next i
For i = 1 To UBound(user.EllipseType)       '�ػ����е���Բ
    Form1.cad.DrawStyle = user.EllipseType(i).comvar.style
    Form1.cad.DrawWidth = user.EllipseType(i).comvar.width
    Form1.cad.Circle (user.EllipseType(i).X, user.EllipseType(i).Y), user.EllipseType(i).r, user.EllipseType(i).comvar.col, , , user.EllipseType(i).asp
Next i
For i = 1 To UBound(user.ArcType)           '�ػ����е�Բ��
    Form1.cad.DrawStyle = user.ArcType(i).comvar.style
    Form1.cad.DrawWidth = user.ArcType(i).comvar.width
    Form1.cad.Circle (user.ArcType(i).X, user.ArcType(i).Y), user.ArcType(i).r, user.ArcType(i).comvar.col, user.ArcType(i).start, user.ArcType(i).end
Next i
'������ʾ�ı�
Dim f As user.font    '�������
        With Form1.cad.font
             f.Bold = .Bold
             f.Italic = .Italic
             f.name = .name
             f.size = .size
             f.Strikethrough = .Strikethrough
             f.Underline = .Underline
             f.color = Form1.cad.ForeColor
        End With
For i = 1 To UBound(user.TextType)   '��ʾ�ı�
    With user.TextType(i)
         Form1.cad.CurrentX = .X
         Form1.cad.CurrentY = .Y
         With Form1.cad.font
             .Bold = user.TextType(i).font.Bold
             .Italic = user.TextType(i).font.Italic
             .name = user.TextType(i).font.name
             .size = user.TextType(i).font.size
             .Strikethrough = user.TextType(i).font.Strikethrough
             .Underline = user.TextType(i).font.Underline
         End With
         Form1.cad.ForeColor = user.TextType(i).font.color
         'Form1.cad.Print .string       '��ʾ�ı�
         wit = TextOut(Form1.cad.hdc, user.TextType(i).X, user.TextType(i).Y, user.TextType(i).string, Len(user.TextType(i).string))
         'Load inputtextbox.text(inputtextbox.text.Count + 1)
         'With inputtextbox.text(inputtextbox.text.Count + 1)
              '.Container = Form1.cad
              '.top = user.texttype(i).y
              '.left = user.texttype(i).x
              '.text = user.texttype(i).string
              '.font = user.texttype(i).font
         'End With
    End With
Next i
With Form1.cad.font        '�ָ�����
             .Bold = f.Bold
             .Italic = f.Italic
             .name = f.name
             .size = f.size
             .Strikethrough = f.Strikethrough
             .Underline = f.Underline
End With
Form1.cad.ForeColor = f.color
Form1.redocommvar               '��ԭ��������
End Sub

'ͻ����ʾ��
Public Sub showpoint(X As Single, Y As Single, object As Object, col As ColorConstants)
Dim xx As Long, yy As Single
Dim scol As ColorConstants, ftype As Integer
ftype = object.FillStyle '�����������
scol = object.FillColor  '���������ɫ
 '��Ĵ�С,������ֵ��user.snapefield��Ӱ��
xx = user.SnapeField / 2
yy = user.SnapeField / 2

       object.FillStyle = 0
       object.FillColor = col
       object.Line (X - xx, Y - yy)-(X + xx, Y + yy), col, B
       object.FillStyle = ftype
       object.FillColor = scol
       
End Sub

'ֱ��
Public Sub singleline(Button As Integer, X As Single, Y As Single, col As ColorConstants, object As Object)
     Dim mode
     
     If Button = VBRUN.vbLeftButton Or (user.CurrentOperist = "������" And user.drawflag = 2) Then
        mode = object.DrawMode
        object.DrawMode = 7
        object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(user.Mousepausex, user.mousepausey), col
        object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
        user.Mousepausex = X
        user.mousepausey = Y
        object.DrawMode = mode
     End If
End Sub

'����
Public Sub rectangle(object As Object, X As Single, Y As Single, col As ColorConstants, Button As Integer)
Dim mode, sy, w
       If Button = VBRUN.vbLeftButton Then
          mode = object.DrawMode
          object.DrawMode = 7
          If user.CurrentOperist = "fieldselectobject" Then
             sy = object.DrawStyle
             w = object.DrawWidth
             object.DrawStyle = 0
             object.DrawWidth = 1
          End If
          object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(user.Mousepausex, user.mouseleftdowny), col
          object.Line -(user.Mousepausex, user.mousepausey), col
          object.Line -(user.Mouseleftdownx, user.mousepausey), col
          object.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
          
          object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, user.mouseleftdowny), col
          object.Line -(X, Y), col
          object.Line -(user.Mouseleftdownx, Y), col
          object.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
          user.Mousepausex = X
          user.mousepausey = Y
          object.DrawMode = mode
          If user.CurrentOperist = "fieldselectobject" Then
             object.DrawStyle = sy
             object.DrawWidth = w
          End If
      End If
End Sub

'������
Public Sub three(object As Object, Button As Integer, X As Single, Y As Single, col As ColorConstants)
Dim mode
       mode = object.DrawMode
       object.DrawMode = 7
       Select Case user.drawflag
              Case 1
                   draw.singleline Button, X, Y, col, object
              Case 2
                   Select Case user.CurrentOperist
                          Case "������"
                               '����
                               Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(user.Mousepausex, user.mousepausey), col
                               Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(user.Mousepausex, user.mousepausey), col
                               '�ػ�
                               Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(X, Y), col
                               Form1.cad.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(X, Y), col
                               user.Mousepausex = X
                               user.mousepausey = Y
                          Case "�ȱ�������"
                               '����
                               Dim k, xx, yy
                               k = user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).x1
                               If k <> 0 Then
                                  k = -(user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).y1 / k)
                               End If
                               xx = (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).x1) / 2
                               yy = user.mousepausey - (user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).y1) / 2
                               k = k * yy + xx
                               object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(k, user.mousepausey), col
                               object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(k, user.mousepausey), col
                               '�ػ�
                               k = user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).x1
                               If k <> 0 Then
                                  k = -(user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 - user.ThreeAngleType(UBound(user.ThreeAngleType)).y1 / k)
                               End If
                               xx = (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).x1) / 2
                               yy = Y - (user.ThreeAngleType(UBound(user.ThreeAngleType)).y2 + user.ThreeAngleType(UBound(user.ThreeAngleType)).y1) / 2
                               k = k * yy + xx
                               object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x1, user.ThreeAngleType(UBound(user.ThreeAngleType)).y1)-(k, Y), col
                               object.Line (user.ThreeAngleType(UBound(user.ThreeAngleType)).x2, user.ThreeAngleType(UBound(user.ThreeAngleType)).y2)-(k, Y), col
                               
                               user.mousepausey = Y
                   End Select
       End Select
       object.DrawMode = mode
End Sub

'��������
Public Sub ��������(object As Object, X As Single, Y As Single, Button As Integer, col As ColorConstants)
Dim mode, xx, yy, x1, x2, y2, y1
mode = object.DrawMode
object.DrawMode = 7
If Button = VBRUN.vbLeftButton Then
    '�����Ƶ���һ��
    xx = user.Mousepausex - user.Mouseleftdownx
    yy = user.mousepausey - user.mouseleftdowny
    '�ѵڶ���Χ�Ƶ�һ����ʱ��ת60��
    x1 = xx / 2 - yy * Sin(user.pi / 3)
    y1 = xx * Sin(user.pi / 3) + yy / 2
    '�ٰ������ƻ�ԭ��
    xx = x1 + user.Mouseleftdownx
    yy = y1 + user.mouseleftdowny
    Form1.cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(user.Mousepausex, user.mousepausey), col
    Form1.cad.Line -(xx, yy), col
    Form1.cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
    '�����Ƶ���һ��
    xx = X - user.Mouseleftdownx
    yy = Y - user.mouseleftdowny
    '�ѵڶ���Χ�Ƶ�һ����ʱ��ת60��
    x1 = xx / 2 - yy * Sin(user.pi / 3)
    y1 = xx * Sin(user.pi / 3) + yy / 2
    '�ٰ������ƻ�ԭ��
    xx = x1 + user.Mouseleftdownx
    yy = y1 + user.mouseleftdowny
    Form1.cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
    Form1.cad.Line -(xx, yy), col
    Form1.cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
    
    user.Mousepausex = X
    user.mousepausey = Y
End If
object.DrawMode = mode
End Sub

'������
Public Sub ������(object As Object, Button As Integer, X As Single, Y As Single, col)
Dim xx, yy, x3 As Single, y3 As Single, x4 As Single, y4 As Single, mode
mode = object.DrawMode
object.DrawMode = 7
If user.drawflag = 3 Then GoTo ������loop   '�ػ�����������
If Button = VBRUN.vbLeftButton Then
       '�������Ƶ���һ��
       'xx = user.mousepausex - user.mouseleftdownx
       'yy = user.mousepausey - user.mouseleftdowny
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
       math.samerectanglethreeandforupiont user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey, x3, y3, x4, y4
       Form1.cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(user.Mousepausex, user.mousepausey), col
       Form1.cad.Line -(x4, y4), col
       Form1.cad.Line -(x3, y3), col
       Form1.cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
������loop:
       math.samerectanglethreeandforupiont user.Mouseleftdownx, user.mouseleftdowny, X, Y, x3, y3, x4, y4
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
       Select Case user.drawflag
              Case 2      '�������ɿ�
                   object.DrawMode = VBRUN.vbCopyPen
                   col = user.Commvar.col
                   user.drawflag = 1
              Case 3     '�ػ�������ʱ
                   object.DrawMode = VBRUN.vbCopyPen
       End Select
       
       Form1.cad.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
       Form1.cad.Line -(x4, y4), col
       Form1.cad.Line -(x3, y3), col
       Form1.cad.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
       user.Mousepausex = X
       user.mousepausey = Y
End If
object.DrawMode = mode
End Sub

'��������
Public Sub ��������(object As Object, Button As Integer, X As Single, Y As Single, col As ColorConstants)
Dim x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single, modec, xx As Single, yy As Single
Dim mode
mode = object.DrawMode
object.DrawMode = 7
If user.drawflag = 3 Then GoTo ��������loop    '�ػ�������������
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
          math.sixegdefour user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey, x3, y3, x4, y4, x5, y5, x6, y6
          object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(user.Mousepausex, user.mousepausey), col
          object.Line -(x6, y6), col
          object.Line -(x5, y5), col
          object.Line -(x4, y4), col
          object.Line -(x3, y3), col
          object.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
��������loop:
          Select Case user.drawflag
                 Case 2     '�������ɿ�
                      object.DrawMode = VBRUN.vbCopyPen
                      col = user.Commvar.col
                 Case 3     '�ػ�������������
                      object.DrawMode = VBRUN.vbCopyPen
          End Select
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
          math.sixegdefour user.Mouseleftdownx, user.mouseleftdowny, X, Y, x3, y3, x4, y4, x5, y5, x6, y6
          object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
          object.Line -(x6, y6), col
          object.Line -(x5, y5), col
          object.Line -(x4, y4), col
          object.Line -(x3, y3), col
          object.Line -(user.Mouseleftdownx, user.mouseleftdowny), col
          
          user.Mousepausex = X
          user.mousepausey = Y
       End If
object.DrawMode = mode
End Sub

'Բ
Public Sub mousecircle(Button As Integer, X As Single, Y As Single, col As ColorConstants, object As Object)
Dim rad As Double
Dim mode
If Button = VBRUN.vbLeftButton Then
   mode = object.DrawMode
   object.DrawMode = 7
   rad = Sqr((user.Mouseleftdownx - user.Mousepausex) ^ 2 _
          + (user.mouseleftdowny - user.mousepausey) ^ 2)
   object.Circle (user.Mouseleftdownx, user.mouseleftdowny), rad, col
   rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
             (user.mouseleftdowny - Y) ^ 2)
   object.Circle (user.Mouseleftdownx, user.mouseleftdowny), rad, col
   user.Mousepausex = X
   user.mousepausey = Y
   object.DrawMode = mode
End If
End Sub

'Բ��
Public Sub arc(object As Object, Button As Integer, X As Single, Y As Single, col As ColorConstants)
Dim xx, yy, mode, rad
       mode = object.DrawMode       '����ģʽ
       object.DrawMode = 7
       Select Case user.drawflag
              Case 1      '��ʾ�ο�Բ
                   mousecircle Button, X, Y, col, object
              Case 2      '��ʾ�ο�ֱ��
                   '��ʾ�ο�ֱ��
                   object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(user.Mousepausex, user.mousepausey), col
                   object.Line (user.Mouseleftdownx, user.mouseleftdowny)-(X, Y), col
                   user.Mousepausex = X
                   user.mousepausey = Y
                
              Case 3      '��ʾ�ο�Բ���Ͳο�ֱ��
                   '�ο�ֱ��
                   object.Line (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y)-(user.Mousepausex, user.mousepausey), col
                   object.Line (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y)-(X, Y), col
                   '�ο�Բ��
                   object.DrawMode = VBRUN.vbXorPen
                   xx = user.Mousepausex - user.ArcType(UBound(user.ArcType)).X
                   yy = user.mousepausey - user.ArcType(UBound(user.ArcType)).Y
                   rad = math.angle(xx, yy)   '�������
                   Form1.cad.Circle (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y), user.ArcType(UBound(user.ArcType)).r, col, user.ArcType(UBound(user.ArcType)).start, rad
                   xx = X - user.ArcType(UBound(user.ArcType)).X
                   yy = Y - user.ArcType(UBound(user.ArcType)).Y
                   rad = math.angle(xx, yy)   '�������
                   Form1.cad.Circle (user.ArcType(UBound(user.ArcType)).X, user.ArcType(UBound(user.ArcType)).Y), user.ArcType(UBound(user.ArcType)).r, col, user.ArcType(UBound(user.ArcType)).start, rad
                   user.Mousepausex = X
                   user.mousepausey = Y
       End Select
       mode = object.DrawMode      '�ָ�ģʽ
End Sub

'��Բ
Public Sub ellipse(object As Object, X As Single, Y As Single, Button As Integer, col As ColorConstants)
On Error Resume Next
Dim asp, mode
       Select Case user.drawflag
              Case 1
                   draw.mousecircle Button, X, Y, col, object
              Case 2
                   '������
                   asp = (Y - user.EllipseType _
                         (UBound(user.EllipseType)).Y) / user. _
                          EllipseType(UBound(user.EllipseType)).r
                   asp = Abs(asp)
                   mode = object.DrawMode
                   object.DrawMode = 7
                   Form1.cad.Circle (user.EllipseType(UBound(user. _
                              EllipseType)).X, user.EllipseType _
                              (UBound(user.EllipseType)).Y), _
                              user.EllipseType(UBound(user. _
                              EllipseType)).r, col, , , _
                              user.Mousepausex
                   Form1.cad.Circle (user.EllipseType(UBound(user.EllipseType)).X, user.EllipseType(UBound(user.EllipseType)).Y), user.EllipseType(UBound(user.EllipseType)).r, col, , , asp
                   user.Mousepausex = asp    '�����ϴε�������
       End Select
End Sub

'��֪���㻭������
Public Sub drawthreeangle(object As Object, x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, col As ColorConstants)
       object.Line (x1, y1)-(x2, y2), col
       object.Line -(x3, y3), col
       object.Line -(x1, y1), col
End Sub

'��֪�ĵ㻭�ı���
'  3 ____________ 4
'   |           |
'   |           |
'   |           |
'  1------------- 2
Public Sub drawforuegde(object As Object, x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, col As ColorConstants)
       object.Line (x1, y1)-(x2, y2), col
       object.Line -(x4, y4), col
       object.Line -(x3, y3), col
       object.Line -(x1, y1), col
End Sub

'��֪���㻭����
' (x1,y1) ____________(x2,y1)
'        |           |
'        |           |
'        |           |
' (x1,y2)------------- (x2,y2)
Public Sub drawrectangle(object As Object, x1 As Single, y1 As Single, x2 As Single, y2 As Single, col As ColorConstants)
       object.Line (x1, y1)-(x2, y1), col
       object.Line -(x2, y2), col
       object.Line -(x1, y2), col
       object.Line -(x1, y1), col
End Sub

'��֪���������㻭������
'       1  _______ 2
'         /       \
'      3 /         \ 6
'        \         /
'         \_______/
'         4        5
Public Sub drawsixegde(object As Object, x1 As Single, y1 As Single, x2 As Single, y2 As Single, x3 As Single, y3 As Single, x4 As Single, y4 As Single, x5 As Single, y5 As Single, x6 As Single, y6 As Single, col As ColorConstants)
          object.Line (x1, y1)-(x2, y2), col
          object.Line -(x6, y6), col
          object.Line -(x5, y5), col
          object.Line -(x4, y4), col
          object.Line -(x3, y3), col
          object.Line -(x1, y1), col
End Sub

'��ѡ�����ž���
Public Sub selectzoomrectangle(object As Object, Button As Integer, col As ColorConstants, X As Single, Y As Single)
Dim mode, styp, width
If Button = VBRUN.vbLeftButton Then
    mode = object.DrawMode
    styp = object.DrawStyle
    width = object.DrawWidth
    With object
         .DrawMode = 7
         .DrawStyle = 1
         .DrawWidth = 1
    End With
    draw.drawrectangle object, user.Mouseleftdownx, user.mouseleftdowny, user.Mousepausex, user.mousepausey, col
    drawrectangle object, user.Mouseleftdownx, user.mouseleftdowny, X, Y, col
    user.Mousepausex = X
    user.mousepausey = Y
    With object
         .DrawMode = mode
         .DrawStyle = styp
         .DrawWidth = width
    End With
End If
End Sub
