Attribute VB_Name = "mmain"
'��ģ��Ϊ�����������ݽṹ����
'����:����

Option Explicit

'API����,����д�����ļ�
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias "WritePrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpString As String, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Const ON_ERROR_RESUME_NEXT = 0
Public Const Pi = 3.14159265358979          '��
Public Const Rfzghr = 0.785398163397448     '����֮���Ŷ�
Public Const TB_FILE = 1 '���幤��������
Public Const TB_EDIT = 2
Public Const TB_MAKE = 3
Public Const TB_SNAPE = 4

Public fMainForm As frmMain   '�����������

Public Inifile As String    '�����ļ�
Public PaperFileName As String    'ͼֽ�����ļ���

Public Viewcolor As ColorConstants 'Ԥ����ɫ,��ͻ����ʾ��ɫ
Public Coordinates As Byte '����

Public Mouseleftdownx As Single  '�ݴ�����
Public Mouseleftdowny As Single
Public Mousepausex As Single
Public Mousepausey As Single

Public ChamferFirstDistance As Single '�нǵĲ���
Public ChamferSecondDistance As Single
Public FilletRadius As Single 'Բ�ǵĲ���

'Public fmainform.Tcurrentoperist As String   '��ǰ����
Public DrawFlag As Integer '��ͼ����

Private Type SaveParam    '�������
       mode As Integer
       Width As Single
       Style As Integer
       End Type
Public SParameter As SaveParam '�������

Public Type PaperType        'ͼֽ����
       Width As Single       '���
       Height As Single      '�߶�
            '(��ͼֽ\ѡȡ����(selectpaper)������,�����������ļ���)
            '(��(face.bas [paperbiglittle])�г�ʼ��)
       Color As ColorConstants  '��ɫ
       Units As String          '��λ
                                '����
                                '����
                                '����
                                '��
                                '���� (MM)
                                '���� (cm)
                                '����
                                '�� (m)
                                'mm
                                'cm
                                'dm
                                'm
       Ratio As Single          '������
       Ratio1 As Single         '......��1
       Ratio2 As Single         '......��2
            '(��ѡ���(foption)������,�����������ļ���)
            '(��(face.bas [papertypeinitial])�г�ʼ��)
       Scalewidth As Single
       ScaleHeight As Single
       End Type
       
Public Type DeskType   'ͼ��Ĳ���
       Color As ColorConstants
             '(��ѡ���(foption)������,�����������ļ���)
             '(��(face.bas [deskinitial])�г�ʼ��)
       Coordinates As Byte  '����
                            '0Ϊ��������
                            '1Ϊ�������
                            '2Ϊ������
       End Type
       
Public Type SelectRectangleType   '��ʾѡȡ����
       X1 As Single               'Ϊ����ʱû��ѡȡ����
       Y1 As Single
       X2 As Single
       Y2 As Single
       flag As Boolean
       End Type
       
Public Type CommonParameter   ' ��������
        Color As ColorConstants '��ɫ
        Width As Integer   '�߿�
        Style As Integer   '����
        End Type
        

Public Type Point     '��
        x As Single
        y As Single
        End Type

Public Type LineType   'ֱ�߽ṹ����
        X1 As Single   '��һ��
        Y1 As Single
        X2 As Single   '�ڶ���
        Y2 As Single
        Style As Long   '����
                         '0Ϊ��ֱ��
                         '1XΪ������,10Ϊ��ʼֱ��
                         '..........,12Ϊ�м�ֱ��
                         '..........,11Ϊ��ֱֹ��
                         '..........,���������м���߶θ�λΪ4
                         '3XΪ������,31Ϊ�����ε�һ��,
                         '..........,32Ϊ�����εڶ���
                         '..........,33Ϊ�����ε�����
                         '4XΪ�ı���,41Ϊ�ı��ε�һ��
                         '...........,42..........��..
                         '...........,43..........��..
                         '...........,44..........��..
                         '����Ϊ��ע�ߴ�,��Ϊˮƽ��עʱ,-X1Ϊ���,��Ϊ��ֱ��עʱΪ��һ���ӳ���(������ע����ָ��XΪָ��
                         '..............................-X2..ͬ���߱�ע,������ע���м�ָ���ע���ֵ�ָ��(XΪָ��)
                         '..............................-3������8��Ϊ��ͷ,����һ��ȡ-3,����ͷȡ-4
                         '..............................-9Ϊ��ע��,�����һ��
                         '..............................����λ����,��������ʾ����ָ��
                         '................��λ����ʾ��ע������,ʮλ�����ϱ�ʾ����ָ��
        CommonParameter As CommonParameter '��������
        End Type
        
        
Public Type CircleType           '����,Բ��,��Բ�����ͽṹ
       x0 As Single           'Բ��
       y0 As Single
       Radius As Single       '�뾶
       Start As Double         '��ʼ��(Ϊ����ʱΪ����)
       end  As Double         '��ֹ��(Ϊ����ʱΪ����)
       Aspect As Double        '������
       CommonParameter As CommonParameter
       End Type
       
Public Type FontType           '��������
       name As String          '��������
       Size As Integer         '�����С
       Color As ColorConstants '������ɫ
       Bold As Boolean         '�Ƿ��Ǵ���
       Italic As Boolean
       Strikethru As Boolean
       Transparent As Boolean  '�Ƿ�͸��
       Underline As Boolean    '�Ƿ����»���
       End Type
       
Public Type TextType               '��������
       Text As String              '����
       x As Single                 '���ֵ��е�
       y As Single
       flag As Boolean             'ѡ�б�־
       Posion As Integer           '��עλ��
       Height As Single            '�߶�
       Width As Single             '���
       Angle As Double             '�Ƕ�,����״̬
       'Style As Integer            '����,�Ǳ�ע���ǵ�������
       Point As Long               '��Ϊ��עʱ,ָ���ע��,Ϊ����ʱΪ0
       Font As FontType            '
       End Type
       
Private PFont As FontType     '�����������
       
Public Type DimensionType    '��ע����
       AutoDimension As Integer    '�Ƿ��Զ���ע
       DimensionUnits As Integer  '�Ƿ��Զ���ע��λ
       Font As FontType      '��ע����
       FontState As Integer '����״̬,0Ϊˮƽ
                            '........,1Ϊ��ֱ
                            '........,2Ϊ����λ��,���ע��ƽ��
       Style As String  'ѡ���б�ע����,0Ϊˮƽ��ע
                              '.........1Ϊ��ֱ��ע
                              '.........2Ϊͬ����ע
                              '.........3Ϊ������ע
                              '.........4Ϊ�뾶��ע
                              '.........5Ϊֱ����ע
                              '.........6Ϊ��ע�ߴ�
                              '.........7Ϊ�Ƕȳߴ�
       Position As Integer     '0��עλ���ڱ�ע���Ϸ�
                              '1................����
                              '2................��
       LeftArrowHead As Integer   '���ͷ
       RightArrowHead As Integer  '�Ҽ�ͷ,0Ϊ�޼�ͷ
                                  '      ,1Ϊ����ͷ(30��)
                                  '      ,2Ϊ���ڼ�ͷ(30��)
                                  '      ,3Ϊ���..........
                                  '......,4Ϊ����ͷ(45��)
                                  '......,5Ϊ������ͷ(45��)
                                  '.......6Ϊ��ռ�ͷ......
                                  '......,7Ϊ���߶�
       ArrowSize As Single        '��ͷ�Ĵ�С
       FirstDimension As Integer    '��һ����ע��
       SecondDimension As Integer   '�ڶ�����ע��,�������ע
       OutsideDimension As Integer     '���ע��
       DimensionColor As ColorConstants '��ע����ɫ
       FirstExtensinonLine As Integer    '��һ���ӳ���
       SecondExtensioneLine As Integer    '�ڶ����ӳ���
       ExtensioneLineColor As ColorConstants '�ӳ�����ɫ
       End Type
Public Dimension As DimensionType    '�����ע����
       
Public Type ArrowType '��ͷ
       x3 As Single        '       (x3,y3)            (x5,y5)
       y3 As Single        '      /                      \
       x4 As Single      '(x1,y1)/________________________\ (x2,y2)
       y4 As Single        '     \                        /
       x5 As Single        '      \ (x4,y4)              /(x6,y6)
       y5 As Single
       x6 As Single
       y6 As Single
       End Type
       
Private Sub Initial()  '��ʼ��
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

Dim i, ss As String * 20
    Inifile = App.Path + "\" + "computercad.ini" '�����ļ���
    PaperFileName = App.Path + "\" + "papertype.cad"  'ͼֽ�����ļ�
    
    '�����������ļ��б���
    i = GetPrivateProfileString("ѡ��", "��ɫ", "65535", ss, 20, Inifile)
    If i = 0 Then
       ss = 65535 '��ɫ,��Ϊ�������,������ʾΪ��ɫ
    Else
       ss = left$(ss, i)
    End If
    Viewcolor = Val(ss) 'Ԥ����ɫ
    i = GetPrivateProfileString("ѡ��", "����", "0", ss, 20, Inifile)
    ss = left$(ss, i)
    Coordinates = Val(ss) '0Ϊ��������,1Ϊ�������,2Ϊ������
    
    '�нǺ�Բ�ǵĲ�����ʼ��
    i = GetPrivateProfileString("Բ�Ǻ��нǵĲ���", "�нǵĵ�һ������", "100", ss, 20, Inifile)
    If i = 0 Then ss = "100"
    ChamferFirstDistance = Val(ss)
    i = GetPrivateProfileString("Բ�Ǻ��нǵĲ���", "�нǵĵڶ�������", "100", ss, 20, Inifile)
    If i = 0 Then ss = "100"
    ChamferSecondDistance = Val(ss)
    i = GetPrivateProfileString("Բ�Ǻ��нǵĲ���", "Բ�ǵİ뾶", "100", ss, 20, Inifile)
    If i = 0 Then ss = "100"
    FilletRadius = Val(ss)
    
End Sub
        
Sub Main()
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
    
    Initial    '��ʼ��
    Set fMainForm = New frmMain
    
    fMainForm.Show
    
    '��ʼ����ע
    With Dimension.Font
         .Bold = fMainForm.ActiveForm.cad.Font.Bold
         .Italic = fMainForm.ActiveForm.cad.Font.Italic
         .name = fMainForm.ActiveForm.cad.Font.name
         .Size = fMainForm.ActiveForm.cad.Font.Size
         .Strikethru = fMainForm.ActiveForm.cad.Font.Strikethrough
         .Underline = fMainForm.ActiveForm.cad.Font.Underline
    End With
    With Dimension
         .ArrowSize = 100
         .AutoDimension = 1
         .DimensionUnits = 1
         .FirstExtensinonLine = 1
         .SecondExtensioneLine = 1
         .LeftArrowHead = 2  '����(30��)
         .RightArrowHead = 2
         .Style = "ˮƽ��ע"
    End With
End Sub

Public Sub SaveParameter(object As Object)   '�������
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       With SParameter
            .mode = object.DrawMode
            .Width = object.DrawWidth
            .Style = object.DrawStyle
       End With
End Sub

Public Sub RedoParameter(object As Object)    '�ָ�����
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       With SParameter
            object.DrawMode = .mode
            object.DrawWidth = .Width
            object.DrawStyle = .Style
       End With
End Sub

Public Sub SaveFont(object As Object)   '��������
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       With object
            PFont.Bold = .FontBold
            PFont.Italic = .FontItalic
            PFont.name = .FontName
            PFont.Size = .FontSize
            PFont.Strikethru = .FontStrikethru
            PFont.Transparent = .FontTransparent
            PFont.Underline = .FontUnderline
            PFont.Color = .ForeColor
       End With
End Sub

Public Sub RedoFont(object As Object)   '�ָ�����
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       With object
            .FontBold = PFont.Bold
            .FontItalic = PFont.Italic
            .Font.name = PFont.name
            .FontSize = PFont.Size
            .FontStrikethru = PFont.Strikethru
            .FontTransparent = PFont.Transparent
            .FontUnderline = PFont.Underline
            .ForeColor = PFont.Color
       End With
End Sub

Public Sub QuikMenu(x As Single, y As Single)   '��ݲ˵�
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       Select Case fMainForm.TCurrentOperist.Text
              Case "������", "����ˮƽ��ע", "������ֱ��ע"
                   With fMainForm
                        .mnuMakebar1.Visible = True
                        .mnuMakeEnd.Visible = True
                        .mnuMakeUndo.Visible = True
                        If fMainForm.TCurrentOperist.Text = "������" Then
                          .mnuMakeClose.Visible = True
                        Else
                           .mnuMakeClose = False
                        End If
                        .PopupMenu .mnuMake
                   End With
              Case "line", "������", "��������", "����", "������", "��������", "Բ", "Բ��", "����", "��Բ", "���㵽Բ������"
                   With fMainForm
                        .mnuMakeClose.Visible = False
                        .mnuMakeEnd.Visible = False
                        .mnuMakeUndo.Visible = True
                        .mnuMakebar1.Visible = True
                        .PopupMenu fMainForm.mnuMake
                   End With
              Case "pointselect"
                   fMainForm.PopupMenu fMainForm.mnuEdit
       End Select
End Sub

Public Sub TiShi(x As Single, y As Single)   '��ʾ
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

       With fMainForm
            .Tishi2.Caption = "X��:"
            .tishi3.Text = CStr(x)
            .tishi4.Caption = "Y��:"
            .tishi5.Text = CStr(y)
       End With
End Sub

'������
Public Sub LetFont(Text As TextType, object As Object, flag As Integer)
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

If flag Then  '�ӱ���ؼ��������������и�ֵ,��������ֵ
   With Text.Font
        .Bold = object.Font.Bold
        .Italic = object.Font.Italic
        .name = object.Font.name
        .Size = object.Font.Size
        '.Transparent = object.Transparent
        .Underline = object.Font.Underline
        If TypeName(object) = "RichTextBox" Then
           .Color = object.SelColor
        End If
   End With
Else '�����������������ؼ��и�ֵ,��������ֵ��,��������ֵ,��ɫֵ
   If TypeName(object) = "Label" Then
       object.Caption = Text.Text
       object.ForeColor = Text.Font.Color
   ElseIf TypeName(object) = "IRichText" Then
       object.SelText = Text.Text
       object.SelStart = 0
       object.SelLength = Len(object.SelText)
       object.SelColor = Text.Font.Color
       object.Refresh
   End If
   With Text.Font
        object.BackColor = fMainForm.ActiveForm.cad.BackColor
        object.Font.Bold = .Bold
        object.Font.Italic = .Italic
        object.Font.name = .name
        object.Font.Size = .Size
        object.Font.Strikethrough = .Strikethru
        object.Font.Underline = .Underline
        object.Visible = True
        If Text.Point <> 0 Then
           Select Case Dimension.Position
               Case 0 '�ڱ�ע���Ϸ�
                    object.left = Text.x - Text.Width / 2 '������ˮƽʱ
                    object.top = Text.y - Text.Height
               Case 1
               
               Case 2 '�ڱ�ע����
                    object.left = Text.x - Text.Width / 2 '������ˮƽʱ
                    object.top = Text.y - Text.Height / 2
           End Select
        Else
            object.left = Text.x '������ˮƽʱ
            object.top = Text.y
        End If
   End With
End If
End Sub

'��ʾʵ���б�
Public Sub ObjectList(Tline() As LineType, Tcircle() As CircleType, Tfont() As TextType, Index As Integer)
Dim i, ss As String * 20
   If Index = -1 Then
      i = GetPrivateProfileString("ʵ���б�", "ʵ������", "0", ss, 20, Inifile)
      If left$(ss, i) <> "0" And i <> 0 Then
         Select Case left$(ss, i / 2)
                Case "�߶�"
                     ObjectListLine Tline, Tfont
                     fList.CB.ListIndex = 0
                Case "����"
                     ObjectListCircle Tcircle
                     fList.CB.ListIndex = 1
                Case "����"
                     ObjectListFont Tfont, Tline
                     fList.CB.ListIndex = 2
         End Select
      Else
         If UBound(Tline) Then
            ObjectListLine Tline, Tfont
            fList.CB.ListIndex = 0
         ElseIf UBound(Tcircle) Then
            ObjectListCircle Tcircle
            fList.CB.ListIndex = 1
         ElseIf UBound(Tfont) Then
            ObjectListFont Tfont, Tline
            fList.CB.ListIndex = 2
         End If
      End If
   Else
      Select Case Index
             Case 0 '"line"
                  ObjectListLine Tline, Tfont
             Case 1 '"circle"
                  ObjectListCircle Tcircle
             Case 2 '"font"
                  ObjectListFont Tfont, Tline
      End Select
   End If
   fList.Show , fMainForm
End Sub

Public Sub ObjectListLine(Tline() As LineType, Tfont() As TextType)
Dim n  As Long, i As Long
    n = UBound(Tline)
    fList.LV.ListItems.Clear
    fList.LV.ColumnHeaders.Clear
    fList.LV.GridLines = False
    If n > 0 Then
       'fList.TV.Nodes.Item("line").Visible = True
       With fList.LV
            .View = lvwReport
            .AllowColumnReorder = True
            .GridLines = True
            .ColumnHeaders.Add , "x1", "��һ��ĺ�����", 1500
            .ColumnHeaders.Add , "y1", "��һ���������", 1500
            .ColumnHeaders.Add , "x2", "�ڶ���ĺ�����", 1500
            .ColumnHeaders.Add , "y2", "�ڶ����������", 1500
            .ColumnHeaders.Add , "type", "����", 1500
            .ColumnHeaders.Add , "color", "��ɫ", 1000
            .ColumnHeaders.Add , "width", "�߿�", 1000
            .ColumnHeaders.Add , "style", "����", 1000
            .ColumnHeaders.Add , "record", "�߶κ�", 1000
            .FullRowSelect = True
       End With
            For i = 1 To n
                With Tline(i)
                     fList.LV.ListItems.Add , , CStr(.X1)
                     fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.Y1)
                     fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.X2)
                     fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.Y2)
                     With fList.LV.ListItems.Item(i).ListSubItems
                     Select Case Int(Tline(i).Style / 10)
                            Case 0
                                 .Add , , "�߶�"
                            Case 1
                                 .Add , , "������"
                            Case 3
                                 .Add , , "�����ε� " & CStr(Tline(i).Style Mod 10) & " ��"
                            Case 4
                                 .Add , , "�ı��ε� " & CStr(Tline(i).Style Mod 10) & " ��"
                            Case 6
                                 .Add , , "�����ε� " & CStr(Tline(i).Style Mod 10) & " ��"
                            Case Is < 0
                                 If Tline(i).Style Mod 10 = -1 Then
                                    .Add , , "��ע��(��ʼ)", , Tfont(Int(Abs(Tline(i).Style / 10))).Text & "  " & CStr(Int(Abs(Tline(i).Style / 10)))
                                 ElseIf Tline(i).Style Mod 10 = -2 Then
                                    .Add , , "��ע��(����)", , Tfont(Int(Abs(Tline(i).Style / 10))).Text & "  " & CStr(Int(Abs(Tline(i).Style / 10)))
                                 ElseIf Tline(i).Style Mod 10 = -9 Then
                                    .Add , , "��ע��(����)"
                                 Else
                                    .Add , , "��ע��"
                                 End If
                            Case Else
                                 .Add , , CStr(Tline(i).Style)
                     End Select
                     End With
                     fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.CommonParameter.Color)
                     fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.CommonParameter.Width)
                     With fList.LV.ListItems.Item(i).ListSubItems
                          Select Case Tline(i).CommonParameter.Style
                                 Case 0
                                      .Add , , "ʵ��"
                                 Case 1
                                      .Add , , "�̻���"
                                 Case 2
                                      .Add , , "����"
                                 Case 3
                                      .Add , , "�㻭��"
                                 Case 4
                                      .Add , , "�̵����"
                                 Case 5
                                      .Add , , "͸����"
                                 Case 6
                                      .Add , , "ʵ��"
                                 Case Else
                                      .Add , , CStr(Tline(i).CommonParameter.Style)
                          End Select
                     End With
                     fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(i)
                End With
            Next i
    End If
End Sub

Public Sub ObjectListCircle(Tcircle() As CircleType)
Dim n  As Long, i As Long
n = UBound(Tcircle)
       With fList.LV
            .ListItems.Clear
            .View = lvwReport
            .AllowColumnReorder = True
            .GridLines = False
            .ColumnHeaders.Clear
       End With
    If n > 0 Then
       fList.LV.GridLines = True
       'fList.TV.Nodes.Item("circle").Visible = True
       With fList.LV.ColumnHeaders
            .Add , "x0", "Բ�ĺ�����", 1500
            .Add , "y0", "Բ��������", 1500
            .Add , "radius", "�뾶", 1500
            .Add , , "����", 1500
            .Add , , "��ʼ��", 1500
            .Add , , "��ֹ��", 1500
            .Add , , "������", 1500
            .Add , "color", "��ɫ", 1000
            .Add , "width", "�߿�", 1000
            .Add , "style", "����", 1000
       End With
       For i = 1 To n
           With Tcircle(i)
                    fList.LV.ListItems.Add , , CStr(.x0)
                    fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.y0)
                    fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.Radius)
                    With fList.LV.ListItems.Item(i).ListSubItems
                         If Tcircle(i).Aspect <> 0 Then
                            If Tcircle(i).Start <> 0 Or Tcircle(i).end <> 0 Then
                               If Tcircle(i).Start < 0 Or Tcircle(i).end < 0 Then
                                  .Add , , "��Բ������"
                               Else
                                 .Add , , "��Բ����"
                               End If
                            Else
                                .Add , , "��Բ"
                            End If
                         ElseIf Tcircle(i).end <> 0 Or Tcircle(i).Start <> 0 Then
                             If Tcircle(i).Start < 0 Or Tcircle(i).end < 0 Then
                                .Add , , "����"
                             Else
                                 .Add , , "Բ��"
                             End If
                         Else
                             .Add , , "Բ"
                         End If
                    End With
                    With fList.LV.ListItems.Item(i).ListSubItems
                         .Add , , CStr(ArcToAngle(Abs(Tcircle(i).Start)))
                         .Add , , CStr(ArcToAngle(Abs(Tcircle(i).end)))
                         .Add , , CStr(Tcircle(i).Aspect)
                    End With
                    fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.CommonParameter.Color)
                    fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.CommonParameter.Width)
                    With fList.LV.ListItems.Item(i).ListSubItems
                          Select Case Tcircle(i).CommonParameter.Style
                                 Case 0
                                      .Add , , "ʵ��"
                                 Case 1
                                      .Add , , "�̻���"
                                 Case 2
                                      .Add , , "����"
                                 Case 3
                                      .Add , , "�㻭��"
                                 Case 4
                                      .Add , , "�̵����"
                                 Case 5
                                      .Add , , "͸����"
                                 Case 6
                                      .Add , , "ʵ��"
                                 Case Else
                                      .Add , , CStr(Tcircle(i).CommonParameter.Style)
                          End Select
                     End With
           End With
       Next i
    End If
End Sub

Public Sub ObjectListFont(Tfont() As TextType, Tline() As LineType)
Dim n  As Long, i As Long
    n = UBound(Tfont)
    With fList.LV
            .ListItems.Clear
            .View = lvwReport
            .GridLines = False
            .AllowColumnReorder = True
            .ColumnHeaders.Clear
    End With
       If n > 0 Then
       'fList.TV.Nodes.Item("font").Visible = True
       fList.LV.GridLines = True
       With fList.LV.ColumnHeaders
            .Add , "text", "����", 2000
            .Add , "x", "���ĺ�����", 1500
            .Add , "y", "����������", 1500
            .Add , "color", "��ɫ", 1000
       End With
       For i = 1 To n
           With Tfont(i)
                    fList.LV.ListItems.Add , , .Text
                    fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.x)
                    fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.y)
                    'fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.Y2)
                    fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.Font.Color)
                    'fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.Commonparameter.Width)
                    'fList.LV.ListItems.Item(i).ListSubItems.Add , , CStr(.Commonparameter.Style)
           
           End With
       Next i
    End If
  
End Sub

