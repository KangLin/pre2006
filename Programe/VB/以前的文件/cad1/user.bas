Attribute VB_Name = "user"
'��ģ��Ϊ�����������ݽṹ����

Option Explicit

'API����,����д�����ļ�
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias "WritePrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpString As String, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public inifile As String    '�����ļ�

Public Const rfzghr = 0.785398163397448     '����֮���Ŷ�
Public Const pi = 3.1415926   '��

Public Showselectpaperform As Boolean '������ʾ�Ƿ�����ʱ��ʾѡȡͼֽ����
Public ���� As Integer '���浱ǰ��ѡ������
Public Savemode As Integer     '���浱ǰ������ģʽ
Public Mouseleftdownx As Single, mouseleftdowny As Single   '��һ��
Public Mousepausex As Single, mousepausey As Single        '�ݴ��
Public Usermouse��״ As Object      '�洢��ǰ������״,�˵������ѡ��ĸ�ѡ��
Public UserMouseColor As ColorConstants  '�Զ���������ɫ
Public Pramcol As ColorConstants  '�ο���״����ɫ
Public Snapecolor As ColorConstants '��׽��Ŀ����ʾ����ɫ
Public Mousesnape As String        '��׽ʱ������״
Public SnapeMouseFlag As Integer   '��׽ʱ�����״�ı�־,
                                   '�����Ƿ����ԭ���������״
                                   'Ӱ��snapemouse����,��meunexitsnape���޸�
Public SnapeField As Integer      'Ŀ�겶׽��Χ
Public Type snapepoint       '��׽���������
       X As Single     '��ǰ��׽���������
       Y As Single
       r As Single     '����,rΪ����ʱ,��ʾû�в�׽����
       End Type
'snapepoint������Ϊ�˵����ֲ�׽����ͬʱ����ʱ�����õ�
'����Ϊ�˴���ǰ�沶׽������׽���ĵ����굽��ľ���
'�����㷨��snape�еĲ�׽������form1.cad.mouseup���̺�form1.cad.mousedown����
Public Type SnapefieldType      '��׽��Ŀ��ķ�Χ,���β�׽
       x1 As Single    '���
       y1 As Single    '
       x2 As Single     '�յ�
       y2 As Single
       End Type
Public SnapefieldType As SnapefieldType

Private Type pointpointtype
        point As Integer
        flag As Integer
        End Type
Public PointPoint As pointpointtype   '��׽�˵��ָ��
Public LinePoint As Integer '��׽ֱ��ָ��
Public ThreeanglePoint As Integer '��׽�����ε�ָ��
Public RectanglePoint As Integer '��׽����ָ��
Public RectanglefourPoint As Integer '��׽�ĵ��ʾ�ľ���ָ��
Public SameRectanglePoint As Integer '������ָ��
Public SixegdePoint As Integer '��������ָ��
Public CirclePoint As Integer '��׽Բ��ָ��
Public ArcPoint As Integer '��׽Բ����ָ��

Public Type paper                 '��ͼ����ʼ����,��ͼֽ�Ĵ�С
       name As String        'ͼֽ������
       scaleheigt As Single          '����ͼ��������,
       scalewidth As Single          '���ڻָ�ԭ������ͼ��
       scalemode As Integer
       top As Single
       left As Single
       width As Single
       height As Single
       until As Single
       color As ColorConstants
       End Type
Public paper As paper
Public Ratio As Double     '������
Public Ratio1 As Single    '�����ߵĵ�һ�������
Public Ratio2 As Single     '�����ߵĵڶ��������
Public HeightZoomnum As Single  'ֽ�ĸ߶�����ϵ��
Public WidthZoomnum As Single   '....�������ϵ��
Public Deskx1 As Single, Desky1 As Single 'ͼ���������Ͻ�,��Ҫ����Ϊ:�����жϵ�����ƶ�����ͼ�߽�ʱ,�Զ��ƶ�ͼֽ,�ڹ���user.movepaper��
Public Deskx2 As Single, Desky2 As Single  'ͼ���������½�,�����Զ��ƶ�ͼֽ,�ڹ���user.movepaper��

Public SnapeOperist As String   '��׽������
Public name As String  'ͼ��Ԫ�ص�����
Public CurrentOperist As String  '��ǰ�Ĳ���������
Public CurrentOperistFlag As Boolean   '��¼��ǰʱ������˲���,���ļ�����,�����ļ�
Public drawflag As Integer 'ͼ�ε�ǰ������־λ,����ǰ�����Ĳ���
'drawflag��ȡֵ����:
'-1��ʾĿ��ֻҪ�������ȷ����,���ü�������ʱ,��Ϊ-1ʱȷ���ڶ���,
'-2��ʾȷ��Բ�İ뾶,���ü�������ʱ,
'����ֵΪ�������
'1��ʾĿ��Ҫ���ȷ��ʱ,����һ��
'2��ʾ��������
'3��ʾ�е�����
'���keyinputdara����,��form1.cad_mouseup,form1.cad_mousedown����


'����ͼ��Ԫ�ش���ṹ
'1.�ڴ˶���ṹ����
'2.�ڴ˶���ṹ����
'3.�ڹ���inimemeroy�п��ٴ�����
'4.�ڹ���savepraam�д洢��������
'5.�������鶼��1��ʼ�洢
Public Type Commvar    '��������;���ʼ���ڹ���initiale��
       col As ColorConstants '��ɫ
       width As Single   '���ο��
       style As Integer '����
       End Type
Public Commvar As Commvar   '������������
Public Savecommvar As Commvar  '���湫����������
Public Type point          '��(���㡢�˵㽻��)
       X As Single
       Y As Single
       End Type
Public Type pointstruct       '��Ĳ����ṹ
       X As Single
       Y As Single
       col As ColorConstants
       PointType As Byte    '�������
       End Type
Public PointType() As pointstruct   '��Ĵ�������
Public Type LineType   '���β����ṹ
       x0 As Single    '���
       y0 As Single    '
       X As Single     '�յ�
       Y As Single
       comvar As Commvar
       End Type
Public LineType() As LineType 'ֱ�ߴ�������
Public RectangleType() As LineType  '���δ洢����
Public SameRectangleType() As LineType '�����δ洢����
Public SixegdeType() As LineType   '�������δ洢����
Public Type RectangleFourpointType  '���ĵ�洢����
        x1 As Single
        y1 As Single
        x2 As Single          '1_________  2
        y2 As Single          ' |        |
        x3 As Single          ' |        |
        y3 As Single          '3|________|4
        x4 As Single
        y4 As Single
        comvar As Commvar
        End Type
Public RectangleFourpointType() As RectangleFourpointType
        
Public Type ThreeAngleType       '�����β����ṹ
       x1 As Single    '��һ��
       y1 As Single    '
       x2 As Single     '�ڶ���
       y2 As Single
       x3 As Single   '������
       y3 As Single
       comvar As Commvar
       End Type
Public ThreeAngleType() As ThreeAngleType    '�����δ洢����
Public Type CircleType  'Բ�β����ṹ
       X As Single      'Բ��
       Y As Single
       r As Single      '�뾶
       comvar As Commvar
       End Type
Public CircleType() As CircleType   'Բ�洢����
Public Type EllipseType   '��Բ�ṹ����
       X As Single       'Բ��
       Y As Single
       r As Single       '�뾶
       asp As Single      '������
       comvar As Commvar
       End Type
Public EllipseType() As EllipseType   '��Բ�洢����
Public Type ArcType                  'Բ���ṹ����
       X As Single          'Բ��
       Y As Single
       r As Single          '�뾶
       start As Single      '��ʼ��,��λ����
       end As Single        '��ֹ��,........
       comvar As Commvar
       End Type
Public ArcType() As ArcType         'Բ���洢����
Public Type font   '����
        name As String           '������
        Bold As Boolean
        Italic As Boolean
        size As Integer
        Strikethrough As Boolean
        Underline As Boolean
        color As ColorConstants
        End Type

Public Type text   '�ı��ṹ����
       X As Single   '���
       Y As Single
       string As String  '�ı���
       font As font      '��������
       End Type
Public TextType() As text   '�ı�����

Public Sub Inimemeroy() '��ʼ���洢��
       ReDim point(0)    '���ٵ�Ĵ洢��
       ReDim LineType(0)   '����ֱ�ߴ洢��
       ReDim RectangleType(0)  '�������δ洢��
       ReDim RectangleFourpointType(0)  '�����ĵ��ʾ����ک
       ReDim CircleType(0)    '����Բ�洢��
       ReDim EllipseType(0)   '������Բ�洢��
       ReDim ArcType(0)      '����Բ���Ĵ洢��
       ReDim ThreeAngleType(0)    '���������εĴ洢��
       ReDim SameRectangleType(0)   '���������δ洢��
       ReDim SixegdeType(0)       '�����������δ洢��
       ReDim TextType(0)      '�����ı��洢��
End Sub

Public Sub Savepraam()      '���������Ĵ洢
Select Case name
       Case "line"      'ֱ�߹�������
            LineType(UBound(LineType)).x0 = Mouseleftdownx
            LineType(UBound(LineType)).y0 = mouseleftdowny
            LineType(UBound(LineType)).comvar = Commvar
       Case "rectangle"  '���ι�������
            RectangleType(UBound(RectangleType)).x0 = Mouseleftdownx
            RectangleType(UBound(RectangleType)).y0 = mouseleftdowny
            RectangleType(UBound(RectangleType)).comvar = Commvar
       Case "������"     '�����εĹ�������
            ThreeAngleType(UBound(ThreeAngleType)).x1 = Mouseleftdownx
            ThreeAngleType(UBound(ThreeAngleType)).y1 = mouseleftdowny
            ThreeAngleType(UBound(ThreeAngleType)).comvar = Commvar
       Case "������"
            SameRectangleType(UBound(SameRectangleType)).x0 = Mouseleftdownx
            SameRectangleType(UBound(SameRectangleType)).y0 = mouseleftdowny
            SameRectangleType(UBound(SameRectangleType)).comvar = Commvar
       Case "��������"
            SixegdeType(UBound(SixegdeType)).x0 = user.Mouseleftdownx
            SixegdeType(UBound(SixegdeType)).y0 = user.mouseleftdowny
            SixegdeType(UBound(SixegdeType)).comvar = Commvar
       Case "circle"     'Բ��������
            CircleType(UBound(CircleType)).X = Mouseleftdownx
            CircleType(UBound(CircleType)).Y = mouseleftdowny
            CircleType(UBound(CircleType)).comvar = Commvar
       Case "ellipse"    '��Բ��������
            EllipseType(UBound(EllipseType)).X = Mouseleftdownx
            EllipseType(UBound(EllipseType)).Y = mouseleftdowny
            EllipseType(UBound(EllipseType)).comvar = Commvar
       Case "arc"         'Բ���Ĺ�������
            ArcType(UBound(ArcType)).X = Mouseleftdownx
            ArcType(UBound(ArcType)).Y = mouseleftdowny
            ArcType(UBound(ArcType)).comvar = Commvar
             
End Select
End Sub

Public Sub Initiale()      '�����ʼ��
Dim i, j
On Error Resume Next

'��ȡ�����ļ�
       ReadIniFile
'��ʼ������
       Form1.height = Screen.height
       Form1.width = Screen.width
'��ʼ��ͼ����,������
       Form1.desk.Move 0, Form1.Toolbar1.height, Form1.scalewidth - 17, Form1.ScaleHeight - Form1.Toolbar1.height * 2 - 17
'��ʼ����ͼ��
       'form1.cad.top,form1.cad.left,
       'form1.cad.width��form1.cad.height
       '�����������Ķ�����λΪ��λ��,����Ҫ����ת��
       Form1.cad.Move 0, 0, Form1.ScaleX(paper.width, 6, 3), Form1.ScaleY(paper.height, 6, 3)
'��ʼ��Һ����
       Scrollbar (Form1.cad.width - Form1.desk.scalewidth) / 2, (Form1.cad.height - Form1.desk.ScaleHeight) / 2
'��ʼ����ʾ��
'       tishiinitale 0
'��ʼ����ͼ��,�����Զ��ƶ�ͼֽ,�˴�һ������ͼ��������ͼ����
       Deskx1 = Form1.desk.ScaleX(Form1.desk.width / 20 - Form1.cad.left, Form1.desk.scalemode, Form1.cad.scalemode)
       Deskx2 = Form1.desk.ScaleX(Form1.desk.width * 19 / 20 - Form1.cad.left, Form1.desk.scalemode, Form1.cad.scalemode)
       Desky1 = Form1.desk.ScaleY(Form1.desk.height / 20 - Form1.cad.top, Form1.desk.scalemode, Form1.cad.scalemode)
       Desky2 = Form1.desk.ScaleY(Form1.desk.height * 19 / 20 - Form1.cad.top, Form1.desk.scalemode, Form1.cad.scalemode)
'������ͼ����ʼ����,����ͼ��������,���ڻָ�ԭ������ͼ��,��ͼֽ�Ĵ�С
       With paper
           .height = Form1.cad.height
           .width = Form1.cad.width
           .top = Form1.cad.top
           .left = Form1.cad.left
           .scaleheigt = Form1.cad.ScaleHeight
           .scalewidth = Form1.cad.scalewidth
           .until = Form1.cad.scalemode
           .color = Form1.cad.FillColor
           .scalemode = Form1.cad.scalemode
           End With
'��ʼ����ͼ������ɫ

'��ʼ��������
       Ratio = 1
       Ratio1 = 1
       Ratio2 = 1

'��ʼ����׽����
       user.SnapeField = 2  '��ֵӰ��draw.showpoint����,���
                            'Ҫ�޸Ĵ�ֵ,��Ҫ��Ӧdraaw.showpoint���Թ���
                            '��ֵ����ͼ�����ŵ�Ӱ��
'��ʼ����ǰ����
       ���� = 1    '1Ϊ��������,2Ϊ�������,3Ϊ������
'��ʼ����ͼ�������״
       UserMouseColor = vbYellow '�����ɫ
       Form1.cad.MousePointer = ccCross  '�����״
       Set Usermouse��״ = Form1.meunmousecross '�˵��������״�еĸ�ѡ��
       Usermouse��״.Checked = True
'��ʼ��Ŀ�겶׽����
       SnapeOperist = "null"
       Form1.meunselecttool.Checked = False  '��ʾĿ��ѡȡ��Ŀ�겶׽�й�
       Form1.meunshowsnapetool_Click     '��ʾĿ�겶׽������
       Form1.meunselecttool.Checked = True
'��־�Ƿ�����˲���,�����ļ�����,���ļ�
       CurrentOperistFlag = False
 '��ʼ���ο��ε���ɫ
       Pramcol = vbYellow
'��ʼ����׽����Ŀ����ɫ
       Snapecolor = VBRUN.vbYellow
'��ʾդ��
     If Form1.meungirl.Checked Then
       For i = 1 To 29
           For j = 1 To 42
               Form1.cad.PSet (i * 10, j * 10), Snapecolor
           Next j
        Next i
     End If
 '��ʼ���洢��
       Inimemeroy
       edit.Init
'��ʼ����������
       Commvar.col = vbBlack
       Commvar.style = 0
       Commvar.width = 1
End Sub

Sub Main()    '������
On Error Resume Next
' frmSplash.Show
 'frmSplash.Refresh
 inifile = App.Path + "\computercad.ini"
 Initiale   '�����ʼ��
 'Open "drawcad.cad" For Random As #200
 
 Form1.Show
 frmTip.Show 1, Form1  '��ʾ�ջ����۴���
 selectpaper.Show 1, Form1   '��ʾѡȡͼֽ����
 'Unload frmSplash
End Sub

Public Sub Scrollbar(hvalue, vvalue)   '��ʼ��Һ����
'�������ļ�����Ҫ����
'Max��Ź��������ֵ
'Min��Ź���������Сֵ
'SmallChange��ŵ��������Ťʱ,�������ƶ��Ĵ�С,��С�ı仯
'LargeChange��ŵ����������ʱ,�������ƶ��Ĵ�С,�����
'value��Ź����ı仯,���ؼ��������ľ���
Dim top As Single, left As Single '����ɵĶ���
    'top = Form1.desk.ScaleX(Form1.deskvscroll.Value - vvalue, Form1.desk.scalemode, Form1.cad.scalemode)
    'left = Form1.desk.ScaleY(Form1.deskHScroll.Value - hvalue, Form1.desk.scalemode, Form1.cad.scalemode)
    'Deskx1 = Deskx1 + top    '���Զ��ƶ�ͼֽ��ֵ
    'Deskx2 = Deskx2 + top
    'Desky1 = Desky1 + left
    'Desky2 = Desky2 + left
    
       Form1.deskvscroll.width = 17     '��ֱ�������Ŀ��
       Form1.deskHScroll.height = 17    'ˮƽ�������ĸ߶�
       '������С
       Form1.deskHScroll.Move Form1.desk.left, Form1.desk.top + Form1.desk.ScaleHeight, Form1.desk.width
       Form1.deskvscroll.Move Form1.desk.left + Form1.desk.width, Form1.desk.top, Form1.deskvscroll.width, Form1.desk.height
       If Form1.desk.ScaleHeight > Form1.cad.height Then
          Form1.deskvscroll.Visible = False
          '����ͼ������
          Form1.cad.top = (Form1.desk.ScaleHeight - Form1.cad.height) / 2
       Else
          Form1.deskvscroll.Visible = True
          Form1.deskvscroll.Max = Form1.cad.height - Form1.desk.ScaleHeight
          Form1.deskvscroll.Min = 0
          Form1.deskvscroll.Value = vvalue   '��ֱ������
          Form1.deskvscroll.SmallChange = Form1.deskvscroll.Max / 10
          Form1.deskvscroll.LargeChange = Form1.deskvscroll.Max / 5
       End If
       If Form1.desk.scalewidth > Form1.cad.width Then
          Form1.deskHScroll.Visible = False
          '����ͼ������
          Form1.cad.left = (Form1.desk.scalewidth - Form1.cad.width) / 2
       Else
          Form1.deskHScroll.Visible = True    'ˮƽ������
          Form1.deskHScroll.Max = Form1.cad.width - Form1.desk.scalewidth
          Form1.deskHScroll.Min = 0
          Form1.deskHScroll.Value = hvalue    'ˮƽ������
          Form1.deskHScroll.SmallChange = Form1.deskHScroll.Max / 10
          Form1.deskHScroll.LargeChange = Form1.deskHScroll.Max / 5
       End If
End Sub

'����굽����ͼ�߽�ʱ,�Զ��ƶ�ͼֽ
Public Sub MovePaper(X As Single, Y As Single, object As Object)
Dim xx As Single, yy As Single  '�ƶ��ľ���
    With Form1.cad
    If Form1.deskHScroll.Visible Then
       If X < Deskx1 Then   '����
          xx = Form1.desk.ScaleX(Form1.desk.width / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'deskx1 = deskx1 - xx
          'deskx2 = deskx2 - xx
          .left = .left + xx
          Scrollbar Abs(.left), Abs(.top)  '���������
          'Exit Sub
       End If
       If X > Deskx2 Then    '����
          xx = Form1.desk.ScaleX(Form1.desk.width / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'deskx1 = deskx1 + xx
          'deskx2 = deskx2 + xx
          .left = .left - xx
          Scrollbar Abs(.left), Abs(.top)  '���������
          'Exit Sub
       End If
    End If
    If Form1.deskvscroll.Value Then
       If Y < Desky1 Then    '����
          yy = Form1.desk.ScaleY(Form1.desk.height / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'desky1 = desky1 - yy
          'desky1 = desky1 - xx
          .top = .top + yy
          Scrollbar Abs(.left), Abs(.top)  '���������
          'Exit Sub
       End If
       If Y > Desky2 Then   '����
          yy = Form1.desk.ScaleY(Form1.desk.height / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'desky1 = desky1 + yy
          'desky2 = desky2 + xx
          .top = .top - yy
          Scrollbar Abs(.left), Abs(.top)  '���������
          'Exit Sub
       End If
    End If
    End With
End Sub

'��ʾ��ʮ�ֹ��
Public Sub DispBigCross(object As Object, X As Single, Y As Single)
Dim mode, wid
If Form1.meunmousebigcross.Checked = True Then
   mode = object.DrawMode
   wid = object.DrawWidth
   object.DrawMode = 7
   object.DrawWidth = 1
   object.Line (Mousepausex, 0)-(Mousepausex, Form1.cad.height), UserMouseColor
   object.Line (0, mousepausey)-(Form1.cad.width, user.mousepausey), UserMouseColor
   object.Line (X, 0)-(X, Form1.cad.height), UserMouseColor
   object.Line (0, Y)-(Form1.cad.width, Y), UserMouseColor
   Mousepausex = X
   mousepausey = Y
   object.DrawMode = mode
   object.DrawWidth = wid
End If
End Sub

'��׽ʱ�����
Public Sub SnapeMouse(object As Object, X As Single, Y As Single)
Dim mode, wid
If Mousesnape = "snapecirle" Then
   mode = object.DrawMode
   wid = object.DrawWidth
   object.DrawMode = 7
   object.DrawWidth = 1
   If SnapeMouseFlag = 0 Then     '���Ϊ0,��Ҫ���ԭͼ��,��Ϊû��ԭͼ��
      SnapeMouseFlag = 1
   Else
      object.Circle (Mousepausex, mousepausey), user.SnapeField, user.UserMouseColor
   End If
   object.Circle (X, Y), user.SnapeField, user.UserMouseColor
   Mousepausex = X
   mousepausey = Y
   object.DrawMode = mode
   object.DrawWidth = wid
End If

End Sub

Public Sub redraw()
Dim filere, i, wit, mode, style
'filere = Loc(200)
'Seek #200, 1
'Do
'input #200, name
'   Select Case name
'          Case "line"
'            input #200, linetype
'            Form1.cad.Line (linetype.x0, linetype.y0)-(linetype.X, linetype.Y), pramcol
'          Case "circle"
'            input #200, , circletype
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
For i = 1 To UBound(LineType)       '�ػ�����ֱ��
    Form1.Savecommvar               '���湫������
    Form1.cad.DrawMode = VBRUN.DrawModeConstants.vbCopyPen
    Form1.cad.DrawStyle = LineType(i).comvar.style
    Form1.cad.DrawWidth = LineType(i).comvar.width
    Form1.cad.Line (LineType(i).x0, LineType(i).y0)-(LineType(i).X, LineType(i).Y), LineType(i).comvar.col
    Form1.redocommvar               '��ԭ��������
Next i
For i = 1 To UBound(CircleType)     '�ػ�����Բ
    Form1.Savecommvar                '���湫������
    Form1.cad.DrawMode = VBRUN.DrawModeConstants.vbCopyPen
    Form1.cad.DrawWidth = CircleType(i).comvar.width
    Form1.cad.DrawStyle = CircleType(i).comvar.style
    Form1.cad.Circle (CircleType(i).X, CircleType(i).Y), CircleType(i).r, CircleType(i).comvar.col
    Form1.redocommvar               '��ԭ��������
Next i
End Sub

Public Sub RightChickMenu(X As Single, Y As Single)     '��������Ҽ�ʱ��ʾ�Ĳ˵�
       '���÷�ʽ:
       'form1.PopupMenu Ҫ��ʾ�Ĳ˵�,��־,,����X, ����Y,Ĭ�ϲ˵���
       Select Case CurrentOperist
              Case "������"
                   Form1.meuncols.Visible = True
                   Form1.meuncolse.Visible = True
                   Form1.meunredo.Visible = True
                   Form1.meunu.Visible = True
                   Form1.PopupMenu Form1.meuntool
                   Form1.meuncols.Visible = False
                   Form1.meuncolse.Visible = False
                   Form1.meunredo.Visible = False
                   Form1.meunu.Visible = False
              Case "Line", "Rectangle", "��������", "������", "��������", "�ȱ�������"
                   Form1.meunredo.Visible = True
                   Form1.meunu.Visible = True
                   Form1.PopupMenu Form1.meuntool
                   Form1.meunredo.Visible = False
                   Form1.meunu.Visible = False
              Case Else
                   If SnapeOperist <> "null" Then
                      Form1.PopupMenu Form1.meunobjectsnpae
                   End If
       End Select
              
End Sub

'��ʾ��
Public Sub tishi(X As Single, Y As Single, Button As Integer)
Dim xx As Single, yy As Single, rad As Double
Dim sstring As String
xx = X * Ratio
yy = Y * Ratio
sstring = "��ѡȡĿ��"
If user.CurrentOperist <> "����" Or user.CurrentOperist <> "Arc" Or user.CurrentOperist <> "circle" Then
       Form1.dispbar.Panels.Item(2).text = "������(X):"
       Form1.dispbar.Panels.Item(4).text = "������(Y):"
       Form1.dispbar.Panels.Item(4).Visible = True
       Form1.dispbar.Panels.Item(5).Visible = True
End If
Select Case CurrentOperist
              Case "Line"
                   If Button = VBRUN.vbLeftButton Then
                      Select Case ����
                             Case 1
                                  sstring = "��ȷ��ֱ�ߵڶ���(X2,Y2)"
                             Case 2
                                  sstring = "��ȷ������:"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.dispbar.Panels.Item(2).text = "����(L):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                      End Select
                   Else
                      sstring = "������ֱ�ߵ�һ��(X1,Y1)"
                   End If
              Case "������"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  Select Case ����
                                         Case 1
                                              sstring = "��ȷ��ֱ�ߵڶ���(X2,Y2)"
                                         Case 2
                                              sstring = "��ȷ������:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                  (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.dispbar.Panels.Item(2).text = "����(L):"
                                              Form1.dispbar.Panels.Item(4).Visible = False
                                              Form1.dispbar.Panels.Item(5).Visible = False
                                  End Select
                               Else
                                  sstring = "������ֱ�ߵ�һ��(X1,Y1)"
                               End If
                          Case 2
                               Select Case ����
                                      Case 1
                                           sstring = "������ֱ����һ��(Xn,Yn)"
                                      Case 2
                                              sstring = "��ȷ������:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                     (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.dispbar.Panels.Item(2).text = "����(L):"
                                              Form1.dispbar.Panels.Item(4).Visible = False
                                              Form1.dispbar.Panels.Item(5).Visible = False
                                  End Select
                   End Select
              Case "Rectangle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�����ε�����(X3,Y3)"
                   Else
                      sstring = "��������ε�һ��(X1,Y1)"
                   End If
              Case "������"
                   If user.drawflag = 1 Then
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ�������εڶ���(X2,Y2)"
                               Else
                                  sstring = "�����������ε�һ��(X1,Y1)"
                               End If
                   Else
                         sstring = "�����������ε�����"
                   End If
              Case "��������"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ���������εڶ���(X2,Y2)"
                   Else
                      sstring = "�������������ε�һ��(X1,Y1)"
                   End If
              Case "�ȱ�������"
              Case "������"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�������εڶ���(X2,Y2)"
                   Else
                      sstring = "�����������ε�һ��(X1,Y1)"
                   End If
              Case "��������"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ���������εڶ���(X2,Y2)"
                   Else
                      sstring = "�������������ε�һ��(X1,Y1)"
                   End If
              Case "Line Style"
              Case "Arc"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ��Բ���İ뾶(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.dispbar.Panels.Item(2).text = "�뾶(R):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                               Else
                                  sstring = "������Բ����Բ��(X0,Y0)"
                               End If
                          Case 2
                               sstring = "��ȷ��Բ����ʼ��"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               xx = rad
                               Form1.dispbar.Panels.Item(2).text = "��ʼ��:"
                               Form1.dispbar.Panels.Item(4).Visible = False
                               Form1.dispbar.Panels.Item(5).Visible = False
                               
                          Case 3
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               yy = rad
                               xx = user.ArcType(UBound(user.ArcType)).start
                               
                               Form1.dispbar.Panels.Item(2).text = "��ʼ��:"
                               Form1.dispbar.Panels.Item(4).text = "��ֹ��:"
                               sstring = "��ȷ��Բ����ֹ��"
                   End Select
              Case "����"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ�����εİ뾶(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                                  Form1.dispbar.Panels.Item(2).text = "�뾶(R):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                               Else
                                  sstring = "���������ε�Բ��(X0,Y0)"
                               End If
                          Case 2
                               sstring = "��ȷ��������ʼ��"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               xx = math.arctoangle(rad)
                               Form1.dispbar.Panels.Item(2).text = "��ʼ��:"
                               Form1.dispbar.Panels.Item(4).Visible = False
                               Form1.dispbar.Panels.Item(5).Visible = False
                               
                          Case 3
                               sstring = "��ȷ��������ֹ��"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               yy = rad
                               xx = math.arctoangle(-user.ArcType(UBound(user.ArcType)).start)
                               
                               Form1.dispbar.Panels.Item(2).text = "��ʼ��:"
                               Form1.dispbar.Panels.Item(4).text = "��ֹ��:"
                   End Select
              Case "Ellipse"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ����Բ�İ뾶(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                                  Form1.dispbar.Panels.Item(2).text = "�뾶(R):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                               Else
                                  sstring = "��������Բ��Բ��(X0,Y0)"
                               End If
                          Case 2
                               sstring = "��ȷ����Բ������"
                          End Select
              Case "circle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ���뾶(R)"
                      rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                      xx = rad * Ratio
                      Form1.dispbar.Panels.Item(2).text = "�뾶(R):"
                      Form1.dispbar.Panels.Item(4).Visible = False
                      Form1.dispbar.Panels.Item(5).Visible = False
                   Else
                      sstring = "������Բ��(X0,Y0)"
                   End If
              Case "move"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ���ƶ�����λ��"
                   End If
              Case "copy"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�����Ƶ���λ��"
                   End If
              Case "round", "rounda"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ����ת�Ƕ�"
                      Form1.dispbar.Panels.Item(2).text = "�Ƕ�(A):"
                      Form1.dispbar.Panels.Item(4).Visible = False
                      Form1.dispbar.Panels.Item(5).Visible = False
                      xx = X - user.Mouseleftdownx
                      yy = Y - user.mouseleftdowny
                      xx = math.arctoangle(math.angle(xx, yy))
                    End If
              Case "mirror"
                    If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�������ߵ��յ�"
                    Else
                      sstring = "��ȷ�������ߵ����"
                    End If
              Case Else
                      sstring = "��ѡ��Ŀ��"
       End Select
       Form1.dispbar.Panels.Item(3).text = xx
       Form1.dispbar.Panels.Item(5).text = yy
       Form1.dispbar.Panels.Item(1).text = sstring
End Sub

'��ʾ����Ϣ
Public Sub TiShiInitale(X As Single, Y As Single, Button As Integer)
Dim xx As Single, yy As Single, rad As Double
Dim sstring As String
xx = X * Ratio
yy = Y * Ratio
sstring = "��ѡȡĿ��"
'If user.currentoperist <> "����" Or user.currentoperist <> "Arc" Or user.currentoperist <> "circle" Then
'       Form1.tishi.Item(1).Caption = "������(X):"
'       Form1.tishi.Item(2).Caption = "������(Y):"
'       Form1.tishitext2.Visible = True
'       Form1.tishitext1.Visible = True
'End If
Form1.tishi.Item(1).Caption = "������(X):"
Form1.tishi.Item(2).Caption = "������(Y):"
If Button <> VBRUN.MouseButtonConstants.vbLeftButton And Not (CurrentOperist = "Arc" And drawflag = 2) And Not (CurrentOperist = "����" And drawflag = 2) Then
   Form1.tishi.Item(2).Visible = True
   Form1.tishitext2.Visible = True
End If
Select Case CurrentOperist
              Case "Line"
                   If Button = VBRUN.vbLeftButton Then
                      Select Case ����
                             Case 1
                                  sstring = "��ȷ��ֱ�ߵڶ���(X2,Y2)"
                             Case 2
                                  sstring = "��ȷ������:"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.tishi.Item(1).Caption = "����(L):"
                                  Form1.tishi.Item(2).Visible = False
                                  Form1.tishitext2.Visible = False
                      End Select
                   Else
                      sstring = "������ֱ�ߵ�һ��(X1,Y1)"
                   End If
              Case "������"
                   Select Case drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  Select Case ����
                                         Case 1
                                              sstring = "��ȷ��ֱ�ߵڶ���(X2,Y2)"
                                         Case 2
                                              sstring = "��ȷ������:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                  (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.tishi.Item(1).Caption = "����(L):"
                                              Form1.tishi.Item(2).Visible = False
                                              Form1.tishitext2.Visible = False
                                  End Select
                               Else
                                  sstring = "������ֱ�ߵ�һ��(X1,Y1)"
                               End If
                          Case 2
                               Select Case ����
                                      Case 1
                                           sstring = "������ֱ����һ��(Xn,Yn)"
                                      Case 2
                                              sstring = "��ȷ������:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                     (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.tishi.Item(1).Caption = "����(L):"
                                              Form1.tishi.Item(2).Visible = False
                                              Form1.tishitext2.Visible = False
                                  End Select
                   End Select
              Case "Rectangle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�����ε�����(X3,Y3)"
                   Else
                      sstring = "��������ε�һ��(X1,Y1)"
                   End If
              Case "������"
                   If user.drawflag = 1 Then
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ�������εڶ���(X2,Y2)"
                               Else
                                  sstring = "�����������ε�һ��(X1,Y1)"
                               End If
                   Else
                         sstring = "�����������ε�����"
                   End If
              Case "��������"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ���������εڶ���(X2,Y2)"
                   Else
                      sstring = "�������������ε�һ��(X1,Y1)"
                   End If
              Case "�ȱ�������"
              Case "������"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�������εڶ���(X2,Y2)"
                   Else
                      sstring = "�����������ε�һ��(X1,Y1)"
                   End If
              Case "��������"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ���������εڶ���(X2,Y2)"
                   Else
                      sstring = "�������������ε�һ��(X1,Y1)"
                   End If
              Case "Line Style"
              Case "Arc"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ��Բ���İ뾶(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.tishi.Item(1).Caption = "�뾶(R):"
                                  Form1.tishi.Item(2).Visible = False
                                  Form1.tishitext2.Visible = False
                               Else
                                  sstring = "������Բ����Բ��(X0,Y0)"
                               End If
                          Case 2
                               sstring = "��ȷ��Բ����ʼ��"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               xx = rad    '����
                               xx = 180 * xx / pi 'ת��Ϊ��
                               Form1.tishi.Item(1).Caption = "��ʼ��:"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                          Case 3
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               yy = rad    '����
                               yy = 180 * yy / pi 'ת��Ϊ��
                               xx = user.ArcType(UBound(user.ArcType)).start
                               xx = 180 * xx / pi 'ת��Ϊ��
                               
                               Form1.tishi.Item(1).Caption = "��ʼ��:"
                               Form1.tishi.Item(2).Caption = "��ֹ��:"
                               sstring = "��ȷ��Բ����ֹ��"
                   End Select
              Case "����"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ�����εİ뾶(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                                  Form1.tishi.Item(1).Caption = "�뾶(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               Else
                                  sstring = "���������ε�Բ��(X0,Y0)"
                               End If
                          Case 2
                               sstring = "��ȷ��������ʼ��"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               
                               xx = math.arctoangle(rad)
                               
                               Form1.tishi.Item(1).Caption = "��ʼ��:"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               
                          Case 3
                               sstring = "��ȷ��������ֹ��"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '���������
                               If xx > 0 And yy > 0 Then
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
                               
                               yy = math.arctoangle(rad)
                               xx = math.arctoangle(-user.ArcType(UBound(user.ArcType)).start)
                               
                               Form1.tishi.Item(1).Caption = "��ʼ��:"
                               Form1.tishi.Item(2).Caption = "��ֹ��:"
                               
                   End Select
              Case "Ellipse"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ����Բ�İ뾶(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                               Form1.tishi.Item(1).Caption = "�뾶(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               'Form1.tishi.Item().Visible = False
                               Else
                                  sstring = "��������Բ��Բ��(X0,Y0)"
                               End If
                          Case 2
                               sstring = "��ȷ����Բ������"
                          End Select
              Case "circle"
                        If Button = VBRUN.vbLeftButton Then
                          sstring = "��ȷ���뾶(R)"
                           rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                           xx = rad * Ratio
                               Form1.tishi.Item(1).Caption = "�뾶(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                        Else
                          sstring = "������Բ��(X0,Y0):"
                        End If
              Case "move"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ���ƶ�����λ��"
                   End If
              Case "copy"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�����Ƶ���λ��"
                   End If
              Case "round", "rounda"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ����ת�Ƕ�"
                               Form1.tishi.Item(1).Caption = "�Ƕ�(A):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               'Form1.tishi.Item(1).Visible = False
                      xx = X - user.Mouseleftdownx
                      yy = Y - user.mouseleftdowny
                      xx = math.arctoangle(math.angle(xx, yy))
                    End If
              Case "mirror"
                    If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�������ߵ��յ�"
                    Else
                      sstring = "��ȷ�������ߵ����"
                    End If
              Case Else
                      sstring = "��ѡ��Ŀ��"
       End Select
       Form1.tishitext1.text = xx
       Form1.tishitext2.text = yy
       Form1.tishi.Item(0).Caption = sstring


End Sub

Private Sub tishiinit1(Button As Integer)

Dim sstring As String
       Form1.dispbar.Panels.Item(2).text = "������(X):"
       Form1.dispbar.Panels.Item(4).text = "������(Y):"
       Select Case CurrentOperist
              Case "Line"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ��ֱ�ߵڶ���(x2,y2)"
                   Else
                      sstring = "������ֱ�ߵ�һ��(x1,y1)"
                   End If
              Case "������"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "��ȷ��ֱ�ߵڶ���(x2,y2)"
                               Else
                                  sstring = "������ֱ�ߵ�һ��(x1,y1)"
                               End If
                          Case 2
                               sstring = "������ֱ�ߵ�n��(xn,yn)"
                   End Select
              Case "Rectangle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "��ȷ�����ε�����(x3,y3)"
                   Else
                      sstring = "��������ε�һ��(x1,y1)"
                   End If
              Case "������"
                   If user.drawflag = 1 Then
                      If Button = VBRUN.vbLeftButton Then
                         sstring = "��ȷ���ڶ���(x2,y2)"
                      Else
                         sstring = "������ֱ�ߵ�һ��(x1,y1)"
                      End If
                   Else
                   
                   End If
              Case "��������"
              Case "�ȱ�������"
              Case "������"
              Case "��������"
              Case "Line Style"
              Case "Arc"
              Case "����"
              Case "Ellipse"
              Case "circle"
              
              Case Else
                      sstring = "��ѡ��Ŀ��"
       End Select
       Form1.dispbar.Panels.Item(1).text = sstring
End Sub

'����ʾ����ֱ��������������
Public Sub KeyInputData(X As Single, Y As Single)
'drawflag��ȡֵ����:
'-1��ʾĿ��ֻҪ�������ȷ����,��Ϊ-1ʱȷ���ڶ���
'-2��ʾȷ��Բ�İ뾶
'1��ʾĿ��Ҫ���ȷ��ʱ,����һ��
'2��ʾ��������
'3��ʾ�е�����
Dim mode, sty, wit
       Select Case CurrentOperist
              Case "Line", "Rectangle", "��������", "������", "��������", "�ȱ�������"
                    If drawflag = -1 Then
                       Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                       drawflag = 0
                    Else
                       Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                       drawflag = -1
                    End If
              Case "������"
                   Select Case drawflag
                          Case 1
                               Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                               drawflag = 2
                          Case 2
                               Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                   End Select
              Case "������"
                   If drawflag = 1 Then   '���������εĵ�һ��
                      Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                      drawflag = 3
                   Else
                      If drawflag = 2 Then   '���������
                         Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                         drawflag = 1
                      Else    '����ڶ���
                         drawflag = 1
                         Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                         drawflag = 2
                      End If
                    End If
              Case "circle"
                    If drawflag = -2 Then 'ȷ��Բ�İ뾶
                       '��ʾ��Ϣ
                          Form1.tishi.Item(0).Caption = "������Բ��(X0,Y0)"
                          Form1.tishi.Item(1).Caption = "������(X):"
                          Form1.tishi.Item(2).Visible = True
                          Form1.tishitext2.Visible = True
                       drawflag = 0
                       ReDim Preserve CircleType(UBound(CircleType) + 1)
                       CircleType(UBound(CircleType)).r = X  '�뾶
                       name = "circle"
                       Savepraam  '���������Ĵ洢,����Բ��
                       '��ʾԲ
                       sty = Form1.cad.DrawStyle
                       wit = Form1.cad.DrawWidth
                       With CircleType(UBound(CircleType))
                            Form1.cad.DrawStyle = .comvar.style
                            Form1.cad.DrawWidth = .comvar.width
                            Form1.cad.Circle (.X, .Y), .r, .comvar.col
                       End With
                       Form1.cad.DrawStyle = sty
                       Form1.cad.DrawWidth = wit
                       Form1.tishitext1.SetFocus
                    Else   'ȷ��Բ��
                       '��ʾ��Ϣ
                           Form1.tishi.Item(0).Caption = "��ȷ���뾶(R)"
                           Form1.tishi.Item(1).Caption = "�뾶(R):"
                           Form1.tishi.Item(2).Visible = False
                           Form1.tishitext2.Visible = False
                       Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                       draw.showpoint X, Y, Form1.cad, Snapecolor  'ͻ����ʾԲ��
                       drawflag = -2
                       Form1.tishitext1.SetFocus
                    End If
                Case "Arc"
                   Select Case user.drawflag
                          Case 1
                               'ȷ��Բ��
                               Mouseleftdownx = X
                               mouseleftdowny = Y
                               drawflag = -2
                               '��ʾ��Ϣ
                               Form1.tishi.Item(0).Caption = "��ȷ��Բ���İ뾶(R)"
                               Form1.tishi.Item(1).Caption = "�뾶(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               Form1.tishitext1.SetFocus
                          Case -2
                               Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                               Form1.tishi.Item(0).Caption = "��ȷ��Բ����ʼ��"
                               Form1.tishi.Item(1).Caption = "��ʼ��(A):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               drawflag = 2
                               '�洢�뾶
                               ReDim Preserve ArcType(UBound(ArcType) + 1)
                               With ArcType(UBound(ArcType))
                                    .r = X
                               End With
                               name = "arc"
                               Savepraam  '�洢��������
                               
                          Case 2
                               drawflag = 3
                               Form1.tishi.Item(0).Caption = "��ȷ��Բ����ֹ��"
                               Form1.tishi.Item(1).Caption = "��ʼ��(A):"
                               Form1.tishi.Item(2).Caption = "��ֹ��(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               Form1.tishitext1.Enabled = False
                               Form1.tishitext2.SetFocus
                               '�洢��ʼ��
                               ArcType(UBound(ArcType)).start = X * pi / 180
                          Case 3
                               drawflag = 1
                               Form1.tishi.Item(0).Caption = "��ȷ��Բ����Բ��(X,Y):"
                               Form1.tishi.Item(1).Caption = "������(A):"
                               Form1.tishi.Item(2).Caption = "������(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               Form1.tishitext1.Enabled = True
                               '�洢��ֹ��
                               ArcType(UBound(ArcType)).end = Y * pi / 180
                               '��ʾԲ��
                               '�������
                               draw.redraw
                               sty = Form1.cad.DrawStyle
                               wit = Form1.cad.DrawWidth
                               With ArcType(UBound(ArcType))
                                    Form1.cad.DrawWidth = .comvar.width
                                    Form1.cad.DrawStyle = .comvar.style
                                    Form1.cad.Circle (.X, .Y), .r, .comvar.col, .start, .end
                               End With
                               Form1.cad.DrawWidth = wit
                               Form1.cad.DrawStyle = sty
                   End Select
              Case "����"
                   Select Case user.drawflag
                          Case 1
                               'ȷ��Բ��
                               Mouseleftdownx = X
                               mouseleftdowny = Y
                               drawflag = -2
                               '��ʾ��Ϣ
                               Form1.tishi.Item(0).Caption = "��ȷ�����εİ뾶(R)"
                               Form1.tishi.Item(1).Caption = "�뾶(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               Form1.tishitext1.SetFocus
                          Case -2
                               Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                               Form1.tishi.Item(0).Caption = "��ȷ��������ʼ��"
                               Form1.tishi.Item(1).Caption = "��ʼ��(A):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               drawflag = 2
                               '�洢�뾶
                               ReDim Preserve ArcType(UBound(ArcType) + 1)
                               With ArcType(UBound(ArcType))
                                    .r = X
                               End With
                               name = "arc"
                               Savepraam  '�洢��������
                               
                          Case 2
                               drawflag = 3
                               Form1.tishi.Item(0).Caption = "��ȷ��������ֹ��"
                               Form1.tishi.Item(1).Caption = "��ʼ��(A):"
                               Form1.tishi.Item(2).Caption = "��ֹ��(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               'Form1.tishitext1.Enabled = False
                               Form1.tishitext2.SetFocus
                               '�洢��ʼ��
                               ArcType(UBound(ArcType)).start = -X * pi / 180
                          Case 3
                               drawflag = 1
                               Form1.tishi.Item(0).Caption = "��ȷ�����ε�Բ��(X,Y):"
                               Form1.tishi.Item(1).Caption = "������(A):"
                               Form1.tishi.Item(2).Caption = "������(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               'Form1.tishitext1.Enabled = True
                               '�洢��ֹ��
                               ArcType(UBound(ArcType)).end = -Y * pi / 180
                               '��ʾԲ��
                               '�������
                               draw.redraw
                               sty = Form1.cad.DrawStyle
                               wit = Form1.cad.DrawWidth
                               With ArcType(UBound(ArcType))
                                    Form1.cad.DrawWidth = .comvar.width
                                    Form1.cad.DrawStyle = .comvar.style
                                    Form1.cad.Circle (.X, .Y), .r, .comvar.col, .start, .end
                               End With
                               Form1.cad.DrawWidth = wit
                               Form1.cad.DrawStyle = sty
                   End Select
         '     Case "Ellipse"
          '          Select Case user.drawflag
           '               Case 1
            '                   If button = VBRUN.vbLeftButton Then
             '                     sstring = "��ȷ����Բ�İ뾶(R)"
              '                    rad = Sqr((user.mouseleftdownx - x) ^ 2 + _
               '                         (user.mouseleftdowny - y) ^ 2)
                '                  xx = rad
                 '              Form1.tishi.Item(1).Caption = "�뾶(R):"
                  '             Form1.tishi.Item(2).Visible = False
                   '            Form1.tishitext2.Visible = False
                    '           'Form1.tishi.Item().Visible = False
                     '          Else
                      '            sstring = "��������Բ��Բ��(X0,Y0)"
                       '        End If
                        '  Case 2
                         '      sstring = "��ȷ����Բ������"
                          'End Select
      '        Case "move"
       '            If button = VBRUN.vbLeftButton Then
        '              sstring = "��ȷ���ƶ�����λ��"
         '          End If
          '    Case "copy"
           '        If button = VBRUN.vbLeftButton Then
            '          sstring = "��ȷ�����Ƶ���λ��"
             '      End If
              'Case "round", "rounda"
   '                If button = VBRUN.vbLeftButton Then
    '                  sstring = "��ȷ����ת�Ƕ�"
     '                          Form1.tishi.Item(1).Caption = "�Ƕ�(A):"
      '                         Form1.tishi.Item(2).Visible = False
       '                        Form1.tishitext2.Visible = False
        '                       'Form1.tishi.Item(1).Visible = False
         '             xx = x - user.mouseleftdownx
          '            yy = y - user.mouseleftdowny
           '           xx = math.arctoangle(math.angle(xx, yy))
            '        End If
             ' Case "mirror"
              '      If button = VBRUN.vbLeftButton Then
               '       sstring = "��ȷ�������ߵ��յ�"
                '    Else
       '          '     sstring = "��ȷ�������ߵ����"
        '            End If
         '     Case Else
          '            sstring = "��ѡ��Ŀ��"
       End Select

End Sub

'�����׽����Ŀ��ͼ��
Public Sub ClearObject()
If user.ArcPoint > 0 Then ReDim Preserve ArcType(ArcPoint - 1)
If user.CirclePoint > 0 Then ReDim Preserve user.CircleType(user.CirclePoint - 1)
If user.LinePoint > 0 Then ReDim Preserve user.LineType(user.LinePoint - 1)
If user.ThreeanglePoint > 0 Then ReDim Preserve user.ThreeAngleType(user.ThreeanglePoint - 1)
If user.RectanglePoint > 0 Then ReDim Preserve user.RectangleType(user.RectanglePoint - 1)
If user.SameRectanglePoint > 0 Then ReDim Preserve user.SameRectangleType(user.SameRectanglePoint - 1)
If user.SixegdePoint > 0 Then ReDim Preserve user.SixegdeType(user.SixegdePoint - 1)
If user.RectanglefourPoint > 0 Then ReDim Preserve user.RectangleFourpointType(user.RectanglefourPoint - 1)
With SnapefieldType
     .x1 = -1
     .y1 = -1
     .x2 = -1
     .y2 = -1
     End With
draw.redraw
End Sub

'�����ļ�
Public Sub SaveFile()
Dim k, i, j, ss As String
'On Error Resume Next
With Form1.CommonDialog1
     .DialogTitle = "����Ϊ"
     .Filter = "*.kld"
     .FileName = "*.kld"
     .ShowSave
     .DialogTitle = ""
     .Filter = ""
End With
If Form1.CommonDialog1.FileName = "*.kld" Then Form1.CommonDialog1.FileName = "": Exit Sub
k = FreeFile()
Open Form1.CommonDialog1.FileName For Output As #k
ss = "�������ͼ ���:����"
Print #k, ss
Print #k, 2001.3  '�汾��

With paper         '�״�ͼֽ����
     Print #k, .height
     Print #k, .left
     Print #k, .top
     Print #k, .width
     Print #k, .color
     Print #k, .scaleheigt
     Print #k, .scalewidth
     Print #k, .until
     End With
     
Print #k, Ratio    '������
Print #k, Ratio1
Print #k, Ratio2

     If UBound(LineType) > 0 Then   'ֱ��
        Print #k, "line"
        Print #k, UBound(LineType)
        For i = 1 To UBound(LineType)
            With LineType(i)
                    Print #k, .x0
                    Print #k, .y0
                    Print #k, .X
                    Print #k, .Y
                    Print #k, .comvar.col
                    Print #k, .comvar.style
                    Print #k, .comvar.width
            End With
        Next i
     End If

     j = UBound(CircleType)  'Բ
     If j > 0 Then
        Print #k, "circle"
        Print #k, j
        For i = 1 To j
            With CircleType(i)
                Print #k, .X
                Print #k, .Y
                Print #k, .r
                Print #k, .comvar.col
                Print #k, .comvar.style
                Print #k, .comvar.width
            End With
        Next i
     End If

     j = UBound(RectangleFourpointType)   '�ĵ��ʾ�ľ���
     If j > 0 Then
        Print #k, "rectanglefourpoint"
        Print #k, j
        For i = 1 To j
            With RectangleFourpointType(i)
                Print #k, .x1
                Print #k, .y1
                Print #k, .x2
                Print #k, .y2
                Print #k, .x3
                Print #k, .y3
                Print #k, .x4
                Print #k, .y4
                Print #k, .comvar.col
                Print #k, .comvar.style
                Print #k, .comvar.width
            End With
        Next i
    End If
    
    j = UBound(ArcType)    'Բ��
    If j > 0 Then
    Print #k, "arc"
    Print #k, j
    For i = 1 To j
        With ArcType(i)
            Print #k, .X
            Print #k, .Y
            Print #k, .r
            Print #k, .start
            Print #k, .end
            Print #k, .comvar.col
            Print #k, .comvar.style
            Print #k, .comvar.width
         End With
    Next i
    End If

    j = UBound(SameRectangleType)    '������
    If j > 0 Then
        Print #k, "samerectangle"
        Print #k, j
        For i = 1 To j
            With SameRectangleType(i)
                Print #k, .x0
                Print #k, .y0
                Print #k, .X
                Print #k, .Y
                Print #k, .comvar.col
                Print #k, .comvar.style
                Print #k, .comvar.width
            End With
        Next i
    End If

    j = UBound(SixegdeType)    '��������
    If j > 0 Then
        Print #k, "sixedge"
        Print #k, j
        For i = 1 To j
            With SixegdeType(i)
                    Print #k, .x0
                    Print #k, .y0
                    Print #k, .X
                    Print #k, .Y
                    Print #k, .comvar.col
                    Print #k, .comvar.style
                    Print #k, .comvar.width
            End With
        Next i
    End If

    j = UBound(RectangleType)    '�����ʾ�ľ���
    If j > 0 Then
        Print #k, "rectangle"
        Print #k, j
        For i = 1 To j
            With RectangleType(i)
                Print #k, .x0
                Print #k, .y0
                Print #k, .X
                Print #k, .Y
                Print #k, .comvar.col
                Print #k, .comvar.style
                Print #k, .comvar.width
            End With
        Next i
    End If
    j = UBound(ThreeAngleType)   '������
    If j > 0 Then
        Print #k, "threeangle"
        Print #k, j
        For i = 1 To j
            With ThreeAngleType(i)
                Print #k, .x1
                Print #k, .y1
                Print #k, .x2
                Print #k, .y2
                Print #k, .x3
                Print #k, .y3
                Print #k, .comvar.col
                Print #k, .comvar.style
                Print #k, .comvar.width
            End With
        Next i
    End If
    j = UBound(EllipseType)   '��Բ
    If j > 0 Then
        Print #k, "ellipse"
        Print #k, j
        For i = 1 To j
            With EllipseType(i)
                 Print #k, EllipseType(i).X
                 Print #k, .Y
                 Print #k, .r
                 Print #k, .asp
                 Print #k, .comvar.col
                 Print #k, .comvar.style
                 Print #k, .comvar.width
            End With
        Next i
    End If
    
Close #k
End Sub

Public Sub OpenFile()
Dim k, i, j, ss As String, a As Boolean, ver
On Error Resume Next
openfileloop:
With Form1.CommonDialog1
     .Filter = "*.kld"
     .FileName = "*.kld"
     .ShowOpen
     .Filter = ""
     End With
If Form1.CommonDialog1.FileName = "" Or Form1.CommonDialog1.FileName = "*.kld" Then Form1.CommonDialog1.FileName = "": Exit Sub
k = FreeFile()
Open Form1.CommonDialog1.FileName For Input As #k
Input #k, ss
If ss <> "�������ͼ ���:����" Then
   i = MsgBox("�ļ����Ͳ���,�Ƿ���ѡ�ļ�?", vbQuestion + vbYesNo)
   If i = vbYes Then
      GoTo openfileloop
   End If
   Exit Sub
End If
Input #k, ver  '�汾��

With paper       'ͼֽ����
     Input #k, .height
     Input #k, .left
     Input #k, .top
     Input #k, .width
     Input #k, .color
     Input #k, .scaleheigt
     Input #k, .scalewidth
     Input #k, .until
     End With
     
Input #k, Ratio   '������
Input #k, Ratio1
Input #k, Ratio2

Inimemeroy   '�����ǰ������
Clearpoint
While (Not (EOF(k)))
Input #k, ss
Select Case ss
       Case "line"
            Input #k, j
            If j >= 0 Then
               ReDim Preserve LineType(j)
               For i = 1 To j
                   With LineType(i)
                        Input #k, .x0
                        Input #k, .y0
                        Input #k, .X
                        Input #k, .Y
                        Input #k, .comvar.col
                        Input #k, .comvar.style
                        Input #k, .comvar.width
                  End With
              Next i
            End If
       Case "circle"
            Input #k, j
            If j > 0 Then
               ReDim Preserve CircleType(j)
               For i = 1 To j
                   With CircleType(i)
                        Input #k, .X
                        Input #k, .Y
                        Input #k, .r
                        Input #k, .comvar.col
                        Input #k, .comvar.style
                        Input #k, .comvar.width
                   End With
               Next i
            End If
       Case "rectanglefourpoint"
            Input #k, j
            If j > 0 Then
               ReDim Preserve RectangleFourpointType(j)
               For i = 1 To j
                   With user.RectangleFourpointType(i)
                        Input #k, .x1
                        Input #k, .y1
                        Input #k, .x2
                        Input #k, .y2
                        Input #k, .x3
                        Input #k, .y3
                        Input #k, .x4
                        Input #k, .y4
                        Input #k, .comvar.col
                        Input #k, .comvar.style
                        Input #k, .comvar.width
                   End With
               Next i
            End If
       Case "arc"
             Input #k, j
             If j > 0 Then
                ReDim Preserve ArcType(j)
                For i = 1 To j
                    With ArcType(i)
                         Input #k, .X
                         Input #k, .Y
                         Input #k, .r
                         Input #k, .start
                         Input #k, .end
                         Input #k, .comvar.col
                         Input #k, .comvar.style
                         Input #k, .comvar.width
                    End With
                Next i
             End If
      Case "samerectangle"
            Input #k, j
            If j > 0 Then
               ReDim Preserve SameRectangleType(j)
               For i = 1 To j
                   With user.SameRectangleType(i)
                        Input #k, .x0
                        Input #k, .y0
                        Input #k, .X
                        Input #k, .Y
                        Input #k, .comvar.col
                        Input #k, .comvar.style
                        Input #k, .comvar.width
                   End With
              Next i
            End If
      Case "sixedge"
            Input #k, j
            If j > 0 Then
               ReDim Preserve user.SixegdeType(j)
                For i = 1 To j
                With user.SixegdeType(i)
                     Input #k, .x0
                     Input #k, .y0
                     Input #k, .X
                     Input #k, .Y
                     Input #k, .comvar.col
                     Input #k, .comvar.style
                     Input #k, .comvar.width
                End With
                Next i
            End If
      Case "rectangle"
            Input #k, j
            If j > 0 Then
              ReDim Preserve RectangleType(j)
              For i = 1 To j
                With user.RectangleType(i)
                        Input #k, .x0
                        Input #k, .y0
                        Input #k, .X
                        Input #k, .Y
                        Input #k, .comvar.col
                        Input #k, .comvar.style
                        Input #k, .comvar.width
                End With
              Next i
            End If
      Case "threeangle"
            Input #k, j
            If j > 0 Then
                ReDim Preserve ThreeAngleType(j)
                For i = 1 To j
                   With user.ThreeAngleType(i)
                        Input #k, .x1
                        Input #k, .y1
                        Input #k, .x2
                        Input #k, .y2
                        Input #k, .x3
                        Input #k, .y3
                        Input #k, .comvar.col
                        Input #k, .comvar.style
                        Input #k, .comvar.width
                    End With
                Next i
            End If
      Case "ellipse"
            Input #k, j
            If j > 0 Then
               ReDim Preserve EllipseType(j)
                For i = 1 To j
                    With user.EllipseType(i)
                         Input #k, EllipseType(i).X
                         Input #k, .Y
                         Input #k, .r
                         Input #k, .asp
                         Input #k, .comvar.col
                         Input #k, .comvar.style
                         Input #k, .comvar.width
                    End With
                Next i
            End If
End Select
Wend
Close #k
End Sub

Private Sub ReadIniFile()
On Error Resume Next
Dim i As Long, sstring As String * 100

'ͼֽ����
With paper
     i = GetPrivateProfileString("paper", "width", "420", sstring, 18, inifile)
     .width = left$(sstring, i)
     If Err = 13 Then .width = 420 '���Ͳ���
     i = GetPrivateProfileString("paper", "height", "297", sstring, 18, inifile)
     .height = left$(sstring, i)
     If Err = 13 Then .height = 297  '���Ͳ���
     i = GetPrivateProfileString("paper", "color", "0", sstring, 18, inifile)
     .color = left$(sstring, i)
     If Err = 13 Then .color = 0   '���Ͳ���
     i = GetPrivateProfileString("paper", "left", "0", sstring, 18, inifile)
     .left = left$(sstring, i)
     If Err = 13 Then .left = 0   '���Ͳ���
     i = GetPrivateProfileString("paper", "name", "0", sstring, 18, inifile)
     .color = left$(sstring, i)
     If Err = 13 Then .color = 0   '���Ͳ���
     i = GetPrivateProfileString("paper", "scaleheigt", "0", sstring, 18, inifile)
     .scaleheigt = left$(sstring, i)
     If Err = 13 Then .scaleheigt = 0    '���Ͳ���
     i = GetPrivateProfileString("paper", "scalewidth", "0", sstring, 18, inifile)
     .scalewidth = left$(sstring, i)
     If Err = 13 Then .scalewidth = 0    '���Ͳ���
     i = GetPrivateProfileString("paper", "until", "0", sstring, 18, inifile)
     .until = left$(sstring, i)
     If Err = 13 Then .until = 0    '���Ͳ���
     i = GetPrivateProfileString("paper", "scalemode", "0", sstring, 18, inifile)
     .scalemode = left$(sstring, i)
     If Err = 13 Then .scalemode = 0    '���Ͳ���
End With

End Sub
