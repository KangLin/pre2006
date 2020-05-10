Attribute VB_Name = "mmain"
'本模块为主函数和数据结构定义
'作者:康林

Option Explicit

'API调用,用于写配置文件
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias "WritePrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpString As String, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Const ON_ERROR_RESUME_NEXT = 0
Public Const Pi = 3.14159265358979          'π
Public Const Rfzghr = 0.785398163397448     '二分之根号二
Public Const TB_FILE = 1 '定义工具条常数
Public Const TB_EDIT = 2
Public Const TB_MAKE = 3
Public Const TB_SNAPE = 4

Public fMainForm As frmMain   '多界面主窗体

Public Inifile As String    '配置文件
Public PaperFileName As String    '图纸类型文件名

Public Viewcolor As ColorConstants '预览颜色,即突出显示颜色
Public Coordinates As Byte '座标

Public Mouseleftdownx As Single  '暂存数据
Public Mouseleftdowny As Single
Public Mousepausex As Single
Public Mousepausey As Single

Public ChamferFirstDistance As Single '切角的参数
Public ChamferSecondDistance As Single
Public FilletRadius As Single '圆角的参数

'Public fmainform.Tcurrentoperist As String   '当前操作
Public DrawFlag As Integer '画图步骤

Private Type SaveParam    '保存参数
       mode As Integer
       Width As Single
       Style As Integer
       End Type
Public SParameter As SaveParam '保存参数

Public Type PaperType        '图纸参数
       Width As Single       '宽度
       Height As Single      '高度
            '(在图纸\选取窗口(selectpaper)中设置,保存在配置文件中)
            '(在(face.bas [paperbiglittle])中初始化)
       Color As ColorConstants  '颜色
       Units As String          '单位
                                '毫米
                                '厘米
                                '分米
                                '米
                                '毫米 (MM)
                                '厘米 (cm)
                                '分米
                                '米 (m)
                                'mm
                                'cm
                                'dm
                                'm
       Ratio As Single          '比例尺
       Ratio1 As Single         '......框1
       Ratio2 As Single         '......框2
            '(在选项窗口(foption)中设置,保存在配置文件中)
            '(在(face.bas [papertypeinitial])中初始化)
       Scalewidth As Single
       ScaleHeight As Single
       End Type
       
Public Type DeskType   '图板的参数
       Color As ColorConstants
             '(在选项窗口(foption)中设置,保存在配置文件中)
             '(在(face.bas [deskinitial])中初始化)
       Coordinates As Byte  '座标
                            '0为绝对座标
                            '1为相对座标
                            '2为极座标
       End Type
       
Public Type SelectRectangleType   '显示选取矩形
       X1 As Single               '为负数时没有选取矩形
       Y1 As Single
       X2 As Single
       Y2 As Single
       flag As Boolean
       End Type
       
Public Type CommonParameter   ' 公共参数
        Color As ColorConstants '颜色
        Width As Integer   '线宽
        Style As Integer   '线型
        End Type
        

Public Type Point     '点
        x As Single
        y As Single
        End Type

Public Type LineType   '直线结构类型
        X1 As Single   '第一点
        Y1 As Single
        X2 As Single   '第二点
        Y2 As Single
        Style As Long   '类型
                         '0为单直线
                         '1X为连画线,10为起始直线
                         '..........,12为中间直线
                         '..........,11为终止直线
                         '..........,如果封闭则中间的线段个位为4
                         '3X为三角形,31为三角形第一边,
                         '..........,32为三角形第二边
                         '..........,33为三角形第三边
                         '4X为四边形,41为四边形第一边
                         '...........,42..........二..
                         '...........,43..........三..
                         '...........,44..........四..
                         '负数为标注尺寸,当为水平标注时,-X1为左边,当为垂直标注时为第一条延长线(包含标注文字指针X为指针
                         '..............................-X2..同基线标注,连续标注的中间指向标注文字的指针(X为指针)
                         '..............................-3～～－8，为箭头,建议一般取-3,满箭头取-4
                         '..............................-9为标注线,即最后一边
                         '..............................除个位数外,其它数表示文字指针
                         '................个位数表示标注线性质,十位数以上表示文字指针
        CommonParameter As CommonParameter '公共参数
        End Type
        
        
Public Type CircleType           '扇形,圆弧,椭圆的类型结构
       x0 As Single           '圆心
       y0 As Single
       Radius As Single       '半径
       Start As Double         '起始角(为负数时为扇形)
       end  As Double         '终止角(为负数时为扇形)
       Aspect As Double        '离心率
       CommonParameter As CommonParameter
       End Type
       
Public Type FontType           '字体类型
       name As String          '字体名称
       Size As Integer         '字体大小
       Color As ColorConstants '字体颜色
       Bold As Boolean         '是否是粗体
       Italic As Boolean
       Strikethru As Boolean
       Transparent As Boolean  '是否透明
       Underline As Boolean    '是否有下划线
       End Type
       
Public Type TextType               '文字类型
       Text As String              '文字
       x As Single                 '文字的中点
       y As Single
       flag As Boolean             '选中标志
       Posion As Integer           '标注位置
       Height As Single            '高度
       Width As Single             '宽度
       Angle As Double             '角度,字体状态
       'Style As Integer            '类型,是标注还是单独文字
       Point As Long               '当为标注时,指向标注线,为文字时为0
       Font As FontType            '
       End Type
       
Private PFont As FontType     '保存字体参数
       
Public Type DimensionType    '标注类型
       AutoDimension As Integer    '是否自动标注
       DimensionUnits As Integer  '是否自动标注单位
       Font As FontType      '标注字体
       FontState As Integer '文字状态,0为水平
                            '........,1为垂直
                            '........,2为任意位置,与标注线平行
       Style As String  '选项中标注类型,0为水平标注
                              '.........1为垂直标注
                              '.........2为同基标注
                              '.........3为连续标注
                              '.........4为半径标注
                              '.........5为直径标注
                              '.........6为旁注尺寸
                              '.........7为角度尺寸
       Position As Integer     '0标注位置在标注线上方
                              '1................外面
                              '2................上
       LeftArrowHead As Integer   '左箭头
       RightArrowHead As Integer  '右箭头,0为无箭头
                                  '      ,1为满箭头(30度)
                                  '      ,2为开口箭头(30度)
                                  '      ,3为封闭..........
                                  '......,4为满箭头(45度)
                                  '......,5为开口艏头(45度)
                                  '.......6为封闭箭头......
                                  '......,7为短线段
       ArrowSize As Single        '箭头的大小
       FirstDimension As Integer    '第一条标注线
       SecondDimension As Integer   '第二条标注线,用于外标注
       OutsideDimension As Integer     '外标注线
       DimensionColor As ColorConstants '标注线颜色
       FirstExtensinonLine As Integer    '第一条延长线
       SecondExtensioneLine As Integer    '第二条延长线
       ExtensioneLineColor As ColorConstants '延长线颜色
       End Type
Public Dimension As DimensionType    '定义标注变量
       
Public Type ArrowType '箭头
       x3 As Single        '       (x3,y3)            (x5,y5)
       y3 As Single        '      /                      \
       x4 As Single      '(x1,y1)/________________________\ (x2,y2)
       y4 As Single        '     \                        /
       x5 As Single        '      \ (x4,y4)              /(x6,y6)
       y5 As Single
       x6 As Single
       y6 As Single
       End Type
       
Private Sub Initial()  '初始化
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

Dim i, ss As String * 20
    Inifile = App.Path + "\" + "computercad.ini" '配置文件名
    PaperFileName = App.Path + "\" + "papertype.cad"  '图纸类型文件
    
    '可以在配置文件中保存
    i = GetPrivateProfileString("选项", "颜色", "65535", ss, 20, Inifile)
    If i = 0 Then
       ss = 65535 '黄色,因为异或运算,所以显示为蓝色
    Else
       ss = left$(ss, i)
    End If
    Viewcolor = Val(ss) '预览颜色
    i = GetPrivateProfileString("选项", "座标", "0", ss, 20, Inifile)
    ss = left$(ss, i)
    Coordinates = Val(ss) '0为绝对座标,1为相对座标,2为极座标
    
    '切角和圆角的参数初始化
    i = GetPrivateProfileString("圆角和切角的参数", "切角的第一条距离", "100", ss, 20, Inifile)
    If i = 0 Then ss = "100"
    ChamferFirstDistance = Val(ss)
    i = GetPrivateProfileString("圆角和切角的参数", "切角的第二条距离", "100", ss, 20, Inifile)
    If i = 0 Then ss = "100"
    ChamferSecondDistance = Val(ss)
    i = GetPrivateProfileString("圆角和切角的参数", "圆角的半径", "100", ss, 20, Inifile)
    If i = 0 Then ss = "100"
    FilletRadius = Val(ss)
    
End Sub
        
Sub Main()
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
    
    Initial    '初始化
    Set fMainForm = New frmMain
    
    fMainForm.Show
    
    '初始化标注
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
         .LeftArrowHead = 2  '开口(30度)
         .RightArrowHead = 2
         .Style = "水平标注"
    End With
End Sub

Public Sub SaveParameter(object As Object)   '保存参数
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       With SParameter
            .mode = object.DrawMode
            .Width = object.DrawWidth
            .Style = object.DrawStyle
       End With
End Sub

Public Sub RedoParameter(object As Object)    '恢复参数
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       With SParameter
            object.DrawMode = .mode
            object.DrawWidth = .Width
            object.DrawStyle = .Style
       End With
End Sub

Public Sub SaveFont(object As Object)   '保存字体
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

Public Sub RedoFont(object As Object)   '恢复字体
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

Public Sub QuikMenu(x As Single, y As Single)   '快捷菜单
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
       Select Case fMainForm.TCurrentOperist.Text
              Case "连画线", "连续水平标注", "连续垂直标注"
                   With fMainForm
                        .mnuMakebar1.Visible = True
                        .mnuMakeEnd.Visible = True
                        .mnuMakeUndo.Visible = True
                        If fMainForm.TCurrentOperist.Text = "连画线" Then
                          .mnuMakeClose.Visible = True
                        Else
                           .mnuMakeClose = False
                        End If
                        .PopupMenu .mnuMake
                   End With
              Case "line", "三角形", "正三角形", "矩形", "正方形", "正六边形", "圆", "圆弧", "扇形", "椭圆", "定点到圆的切线"
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

Public Sub TiShi(x As Single, y As Single)   '提示
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

       With fMainForm
            .Tishi2.Caption = "X轴:"
            .tishi3.Text = CStr(x)
            .tishi4.Caption = "Y轴:"
            .tishi5.Text = CStr(y)
       End With
End Sub

'赋文字
Public Sub LetFont(Text As TextType, object As Object, flag As Integer)
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If

If flag Then  '从标题控件中向文字数组中赋值,仅赋字体值
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
Else '从文字数组中向标题控件中赋值,除赋字体值外,还赋文字值,颜色值
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
               Case 0 '在标注线上方
                    object.left = Text.x - Text.Width / 2 '当文字水平时
                    object.top = Text.y - Text.Height
               Case 1
               
               Case 2 '在标注线上
                    object.left = Text.x - Text.Width / 2 '当文字水平时
                    object.top = Text.y - Text.Height / 2
           End Select
        Else
            object.left = Text.x '当文字水平时
            object.top = Text.y
        End If
   End With
End If
End Sub

'显示实体列表
Public Sub ObjectList(Tline() As LineType, Tcircle() As CircleType, Tfont() As TextType, Index As Integer)
Dim i, ss As String * 20
   If Index = -1 Then
      i = GetPrivateProfileString("实体列表", "实体类型", "0", ss, 20, Inifile)
      If left$(ss, i) <> "0" And i <> 0 Then
         Select Case left$(ss, i / 2)
                Case "线段"
                     ObjectListLine Tline, Tfont
                     fList.CB.ListIndex = 0
                Case "曲线"
                     ObjectListCircle Tcircle
                     fList.CB.ListIndex = 1
                Case "文字"
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
            .ColumnHeaders.Add , "x1", "第一点的横座标", 1500
            .ColumnHeaders.Add , "y1", "第一点的纵座标", 1500
            .ColumnHeaders.Add , "x2", "第二点的横座标", 1500
            .ColumnHeaders.Add , "y2", "第二点的纵座标", 1500
            .ColumnHeaders.Add , "type", "类型", 1500
            .ColumnHeaders.Add , "color", "颜色", 1000
            .ColumnHeaders.Add , "width", "线宽", 1000
            .ColumnHeaders.Add , "style", "线型", 1000
            .ColumnHeaders.Add , "record", "线段号", 1000
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
                                 .Add , , "线段"
                            Case 1
                                 .Add , , "连画线"
                            Case 3
                                 .Add , , "三角形第 " & CStr(Tline(i).Style Mod 10) & " 边"
                            Case 4
                                 .Add , , "四边形第 " & CStr(Tline(i).Style Mod 10) & " 边"
                            Case 6
                                 .Add , , "六边形第 " & CStr(Tline(i).Style Mod 10) & " 边"
                            Case Is < 0
                                 If Tline(i).Style Mod 10 = -1 Then
                                    .Add , , "标注线(开始)", , Tfont(Int(Abs(Tline(i).Style / 10))).Text & "  " & CStr(Int(Abs(Tline(i).Style / 10)))
                                 ElseIf Tline(i).Style Mod 10 = -2 Then
                                    .Add , , "标注线(文字)", , Tfont(Int(Abs(Tline(i).Style / 10))).Text & "  " & CStr(Int(Abs(Tline(i).Style / 10)))
                                 ElseIf Tline(i).Style Mod 10 = -9 Then
                                    .Add , , "标注线(结束)"
                                 Else
                                    .Add , , "标注线"
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
                                      .Add , , "实线"
                                 Case 1
                                      .Add , , "短划线"
                                 Case 2
                                      .Add , , "虚线"
                                 Case 3
                                      .Add , , "点画线"
                                 Case 4
                                      .Add , , "短点点线"
                                 Case 5
                                      .Add , , "透明线"
                                 Case 6
                                      .Add , , "实线"
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
            .Add , "x0", "圆心横座标", 1500
            .Add , "y0", "圆心纵座标", 1500
            .Add , "radius", "半径", 1500
            .Add , , "类型", 1500
            .Add , , "起始角", 1500
            .Add , , "终止角", 1500
            .Add , , "离心率", 1500
            .Add , "color", "颜色", 1000
            .Add , "width", "线宽", 1000
            .Add , "style", "线型", 1000
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
                                  .Add , , "椭圆型扇形"
                               Else
                                 .Add , , "椭圆曲线"
                               End If
                            Else
                                .Add , , "椭圆"
                            End If
                         ElseIf Tcircle(i).end <> 0 Or Tcircle(i).Start <> 0 Then
                             If Tcircle(i).Start < 0 Or Tcircle(i).end < 0 Then
                                .Add , , "扇形"
                             Else
                                 .Add , , "圆弧"
                             End If
                         Else
                             .Add , , "圆"
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
                                      .Add , , "实线"
                                 Case 1
                                      .Add , , "短划线"
                                 Case 2
                                      .Add , , "虚线"
                                 Case 3
                                      .Add , , "点画线"
                                 Case 4
                                      .Add , , "短点点线"
                                 Case 5
                                      .Add , , "透明线"
                                 Case 6
                                      .Add , , "实线"
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
            .Add , "text", "文字", 2000
            .Add , "x", "起点的横座标", 1500
            .Add , "y", "起点的纵座标", 1500
            .Add , "color", "颜色", 1000
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

