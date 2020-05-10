Attribute VB_Name = "user"
'本模块为主函数和数据结构定义

Option Explicit

'API调用,用于写配置文件
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias "WritePrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpString As String, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public inifile As String    '配置文件

Public Const rfzghr = 0.785398163397448     '二分之根号二
Public Const pi = 3.1415926   'П

Public Showselectpaperform As Boolean '用于显示是否在起动时显示选取图纸窗体
Public 座标 As Integer '保存当前所选的座标
Public Savemode As Integer     '保存当前的线型模式
Public Mouseleftdownx As Single, mouseleftdowny As Single   '第一点
Public Mousepausex As Single, mousepausey As Single        '暂存点
Public Usermouse形状 As Object      '存储当前鼠标的形状,菜单中鼠标选项的复选框
Public UserMouseColor As ColorConstants  '自定义鼠标的颜色
Public Pramcol As ColorConstants  '参考形状的颜色
Public Snapecolor As ColorConstants '捕捉到目标显示的颜色
Public Mousesnape As String        '捕捉时鼠标的形状
Public SnapeMouseFlag As Integer   '捕捉时鼠标形状的标志,
                                   '决定是否清除原来的鼠标形状
                                   '影响snapemouse过程,在meunexitsnape中修改
Public SnapeField As Integer      '目标捕捉范围
Public Type snapepoint       '捕捉到点的类型
       X As Single     '当前捕捉到点的座标
       Y As Single
       r As Single     '距离,r为负数时,表示没有捕捉到点
       End Type
'snapepoint类型是为了当多种捕捉操作同时进行时而设置的
'它是为了传递前面捕捉操作捕捉到的点和鼠标到点的距离
'具体算法见snape中的捕捉函数和form1.cad.mouseup过程和form1.cad.mousedown过程
Public Type SnapefieldType      '捕捉到目标的范围,矩形捕捉
       x1 As Single    '起点
       y1 As Single    '
       x2 As Single     '终点
       y2 As Single
       End Type
Public SnapefieldType As SnapefieldType

Private Type pointpointtype
        point As Integer
        flag As Integer
        End Type
Public PointPoint As pointpointtype   '捕捉端点的指针
Public LinePoint As Integer '捕捉直线指针
Public ThreeanglePoint As Integer '捕捉三角形的指针
Public RectanglePoint As Integer '捕捉矩形指针
Public RectanglefourPoint As Integer '捕捉四点表示的矩形指针
Public SameRectanglePoint As Integer '正方形指针
Public SixegdePoint As Integer '正六边形指针
Public CirclePoint As Integer '捕捉圆的指针
Public ArcPoint As Integer '捕捉圆弧的指针

Public Type paper                 '制图区起始区域,即图纸的大小
       name As String        '图纸的名称
       scaleheigt As Single          '当制图区放缩后,
       scalewidth As Single          '便于恢复原来的制图区
       scalemode As Integer
       top As Single
       left As Single
       width As Single
       height As Single
       until As Single
       color As ColorConstants
       End Type
Public paper As paper
Public Ratio As Double     '比例尺
Public Ratio1 As Single    '比例尺的第一个输入框
Public Ratio2 As Single     '比例尺的第二个输入框
Public HeightZoomnum As Single  '纸的高度缩放系数
Public WidthZoomnum As Single   '....宽度缩放系数
Public Deskx1 As Single, Desky1 As Single '图板区域左上角,主要作用为:用来判断当鼠标移动到视图边界时,自动移动图纸,在过程user.movepaper中
Public Deskx2 As Single, Desky2 As Single  '图板区域右下角,用来自动移动图纸,在过程user.movepaper中

Public SnapeOperist As String   '捕捉的类型
Public name As String  '图形元素的名称
Public CurrentOperist As String  '当前的操作的类型
Public CurrentOperistFlag As Boolean   '记录当前时否进行了操作,用文件保存,打开新文件
Public drawflag As Integer '图形当前操作标志位,即当前操作的步骤
'drawflag的取值如下:
'-1表示目标只要两点就能确定的,在用键盘输入时,当为-1时确定第二点,
'-2表示确定圆的半径,在用键盘输入时,
'其正值为鼠标输入
'1表示目标要多点确定时,做第一步
'2表示做条二步
'3表示佬第三步
'详见keyinputdara过程,及form1.cad_mouseup,form1.cad_mousedown过程


'定义图形元素储存结构
'1.在此定义结构类型
'2.在此定义结构变量
'3.在过程inimemeroy中开辟储存区
'4.在过程savepraam中存储公共参数
'5.所有数组都从1开始存储
Public Type Commvar    '公共参数;其初始化在过程initiale中
       col As ColorConstants '颜色
       width As Single   '线形宽度
       style As Integer '线形
       End Type
Public Commvar As Commvar   '公共参数变量
Public Savecommvar As Commvar  '保存公共参数变量
Public Type point          '点(顶点、端点交点)
       X As Single
       Y As Single
       End Type
Public Type pointstruct       '点的参数结构
       X As Single
       Y As Single
       col As ColorConstants
       PointType As Byte    '点的类型
       End Type
Public PointType() As pointstruct   '点的储存数组
Public Type LineType   '线形参数结构
       x0 As Single    '起点
       y0 As Single    '
       X As Single     '终点
       Y As Single
       comvar As Commvar
       End Type
Public LineType() As LineType '直线储存数组
Public RectangleType() As LineType  '钜形存储数组
Public SameRectangleType() As LineType '正方形存储数组
Public SixegdeType() As LineType   '正六边形存储数组
Public Type RectangleFourpointType  '用四点存储矩形
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
        
Public Type ThreeAngleType       '三角形参数结构
       x1 As Single    '第一点
       y1 As Single    '
       x2 As Single     '第二点
       y2 As Single
       x3 As Single   '第三点
       y3 As Single
       comvar As Commvar
       End Type
Public ThreeAngleType() As ThreeAngleType    '三角形存储数组
Public Type CircleType  '圆形参数结构
       X As Single      '圆心
       Y As Single
       r As Single      '半径
       comvar As Commvar
       End Type
Public CircleType() As CircleType   '圆存储数组
Public Type EllipseType   '椭圆结构类型
       X As Single       '圆心
       Y As Single
       r As Single       '半径
       asp As Single      '离心率
       comvar As Commvar
       End Type
Public EllipseType() As EllipseType   '椭圆存储数组
Public Type ArcType                  '圆弧结构类型
       X As Single          '圆心
       Y As Single
       r As Single          '半径
       start As Single      '起始角,单位弧度
       end As Single        '终止角,........
       comvar As Commvar
       End Type
Public ArcType() As ArcType         '圆弧存储数组
Public Type font   '字体
        name As String           '字体名
        Bold As Boolean
        Italic As Boolean
        size As Integer
        Strikethrough As Boolean
        Underline As Boolean
        color As ColorConstants
        End Type

Public Type text   '文本结构类型
       X As Single   '起点
       Y As Single
       string As String  '文本串
       font As font      '字体类型
       End Type
Public TextType() As text   '文本数组

Public Sub Inimemeroy() '初始化存储区
       ReDim point(0)    '开辟点的存储区
       ReDim LineType(0)   '开辟直线存储区
       ReDim RectangleType(0)  '开辟钜形存储区
       ReDim RectangleFourpointType(0)  '开辟四点表示矩形讴
       ReDim CircleType(0)    '开辟圆存储区
       ReDim EllipseType(0)   '开辟椭圆存储区
       ReDim ArcType(0)      '开辟圆弧的存储区
       ReDim ThreeAngleType(0)    '开辟三角形的存储区
       ReDim SameRectangleType(0)   '开辟正方形存储区
       ReDim SixegdeType(0)       '开辟正六边形存储区
       ReDim TextType(0)      '开辟文本存储区
End Sub

Public Sub Savepraam()      '公共参数的存储
Select Case name
       Case "line"      '直线公共参数
            LineType(UBound(LineType)).x0 = Mouseleftdownx
            LineType(UBound(LineType)).y0 = mouseleftdowny
            LineType(UBound(LineType)).comvar = Commvar
       Case "rectangle"  '钜形公共参数
            RectangleType(UBound(RectangleType)).x0 = Mouseleftdownx
            RectangleType(UBound(RectangleType)).y0 = mouseleftdowny
            RectangleType(UBound(RectangleType)).comvar = Commvar
       Case "三角形"     '三角形的公共参数
            ThreeAngleType(UBound(ThreeAngleType)).x1 = Mouseleftdownx
            ThreeAngleType(UBound(ThreeAngleType)).y1 = mouseleftdowny
            ThreeAngleType(UBound(ThreeAngleType)).comvar = Commvar
       Case "正方形"
            SameRectangleType(UBound(SameRectangleType)).x0 = Mouseleftdownx
            SameRectangleType(UBound(SameRectangleType)).y0 = mouseleftdowny
            SameRectangleType(UBound(SameRectangleType)).comvar = Commvar
       Case "正六边形"
            SixegdeType(UBound(SixegdeType)).x0 = user.Mouseleftdownx
            SixegdeType(UBound(SixegdeType)).y0 = user.mouseleftdowny
            SixegdeType(UBound(SixegdeType)).comvar = Commvar
       Case "circle"     '圆公共参数
            CircleType(UBound(CircleType)).X = Mouseleftdownx
            CircleType(UBound(CircleType)).Y = mouseleftdowny
            CircleType(UBound(CircleType)).comvar = Commvar
       Case "ellipse"    '椭圆公共参数
            EllipseType(UBound(EllipseType)).X = Mouseleftdownx
            EllipseType(UBound(EllipseType)).Y = mouseleftdowny
            EllipseType(UBound(EllipseType)).comvar = Commvar
       Case "arc"         '圆弧的公共参数
            ArcType(UBound(ArcType)).X = Mouseleftdownx
            ArcType(UBound(ArcType)).Y = mouseleftdowny
            ArcType(UBound(ArcType)).comvar = Commvar
             
End Select
End Sub

Public Sub Initiale()      '程序初始化
Dim i, j
On Error Resume Next

'读取配置文件
       ReadIniFile
'初始化窗体
       Form1.height = Screen.height
       Form1.width = Screen.width
'初始化图板区,即桌面
       Form1.desk.Move 0, Form1.Toolbar1.height, Form1.scalewidth - 17, Form1.ScaleHeight - Form1.Toolbar1.height * 2 - 17
'初始化制图区
       'form1.cad.top,form1.cad.left,
       'form1.cad.width和form1.cad.height
       '都是以容器的度量单位为单位的,所以要进行转换
       Form1.cad.Move 0, 0, Form1.ScaleX(paper.width, 6, 3), Form1.ScaleY(paper.height, 6, 3)
'初始化液动条
       Scrollbar (Form1.cad.width - Form1.desk.scalewidth) / 2, (Form1.cad.height - Form1.desk.ScaleHeight) / 2
'初始化揭示栏
'       tishiinitale 0
'初始化视图区,用以自动移动图纸,此处一定放在图板区和制图区后
       Deskx1 = Form1.desk.ScaleX(Form1.desk.width / 20 - Form1.cad.left, Form1.desk.scalemode, Form1.cad.scalemode)
       Deskx2 = Form1.desk.ScaleX(Form1.desk.width * 19 / 20 - Form1.cad.left, Form1.desk.scalemode, Form1.cad.scalemode)
       Desky1 = Form1.desk.ScaleY(Form1.desk.height / 20 - Form1.cad.top, Form1.desk.scalemode, Form1.cad.scalemode)
       Desky2 = Form1.desk.ScaleY(Form1.desk.height * 19 / 20 - Form1.cad.top, Form1.desk.scalemode, Form1.cad.scalemode)
'保存制图区初始区域,当制图区放缩后,便于恢复原来的制图区,即图纸的大小
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
'初始化制图区的颜色

'初始化比例尺
       Ratio = 1
       Ratio1 = 1
       Ratio2 = 1

'初始化捕捉区域
       user.SnapeField = 2  '此值影响draw.showpoint过程,如果
                            '要修改此值,则要相应draaw.showpoint个性过程
                            '此值受视图中缩放的影响
'初始化当前座标
       座标 = 1    '1为绝对座标,2为相对座标,3为极座标
'初始化制图区鼠标形状
       UserMouseColor = vbYellow '鼠标颜色
       Form1.cad.MousePointer = ccCross  '鼠标形状
       Set Usermouse形状 = Form1.meunmousecross '菜单中鼠标形状中的复选框
       Usermouse形状.Checked = True
'初始化目标捕捉操作
       SnapeOperist = "null"
       Form1.meunselecttool.Checked = False  '显示目标选取与目标捕捉有关
       Form1.meunshowsnapetool_Click     '显示目标捕捉工具栏
       Form1.meunselecttool.Checked = True
'标志是否进行了操作,用于文件保存,新文件
       CurrentOperistFlag = False
 '初始化参考形的颜色
       Pramcol = vbYellow
'初始化捕捉到的目标颜色
       Snapecolor = VBRUN.vbYellow
'显示栅格
     If Form1.meungirl.Checked Then
       For i = 1 To 29
           For j = 1 To 42
               Form1.cad.PSet (i * 10, j * 10), Snapecolor
           Next j
        Next i
     End If
 '初始化存储区
       Inimemeroy
       edit.Init
'初始化公共参数
       Commvar.col = vbBlack
       Commvar.style = 0
       Commvar.width = 1
End Sub

Sub Main()    '主过程
On Error Resume Next
' frmSplash.Show
 'frmSplash.Refresh
 inifile = App.Path + "\computercad.ini"
 Initiale   '程序初始化
 'Open "drawcad.cad" For Random As #200
 
 Form1.Show
 frmTip.Show 1, Form1  '显示日积月累窗口
 selectpaper.Show 1, Form1   '显示选取图纸窗口
 'Unload frmSplash
End Sub

Public Sub Scrollbar(hvalue, vvalue)   '初始化液动条
'滚动条的几个主要参数
'Max存放滚动的最大值
'Min存放滚动条的最小值
'SmallChange存放当鼠标点击按扭时,滚动条移动的大小,即小的变化
'LargeChange存放当鼠标点滚动槽时,滚动条移动的大小,即大的
'value存放滚动的变化,即控件距容器的距离
Dim top As Single, left As Single '保存旧的顶点
    'top = Form1.desk.ScaleX(Form1.deskvscroll.Value - vvalue, Form1.desk.scalemode, Form1.cad.scalemode)
    'left = Form1.desk.ScaleY(Form1.deskHScroll.Value - hvalue, Form1.desk.scalemode, Form1.cad.scalemode)
    'Deskx1 = Deskx1 + top    '给自动移动图纸赋值
    'Deskx2 = Deskx2 + top
    'Desky1 = Desky1 + left
    'Desky2 = Desky2 + left
    
       Form1.deskvscroll.width = 17     '竖直滚动条的宽度
       Form1.deskHScroll.height = 17    '水平滚动条的高度
       '滚动大小
       Form1.deskHScroll.Move Form1.desk.left, Form1.desk.top + Form1.desk.ScaleHeight, Form1.desk.width
       Form1.deskvscroll.Move Form1.desk.left + Form1.desk.width, Form1.desk.top, Form1.deskvscroll.width, Form1.desk.height
       If Form1.desk.ScaleHeight > Form1.cad.height Then
          Form1.deskvscroll.Visible = False
          '把制图区置中
          Form1.cad.top = (Form1.desk.ScaleHeight - Form1.cad.height) / 2
       Else
          Form1.deskvscroll.Visible = True
          Form1.deskvscroll.Max = Form1.cad.height - Form1.desk.ScaleHeight
          Form1.deskvscroll.Min = 0
          Form1.deskvscroll.Value = vvalue   '竖直滚动条
          Form1.deskvscroll.SmallChange = Form1.deskvscroll.Max / 10
          Form1.deskvscroll.LargeChange = Form1.deskvscroll.Max / 5
       End If
       If Form1.desk.scalewidth > Form1.cad.width Then
          Form1.deskHScroll.Visible = False
          '把制图区置中
          Form1.cad.left = (Form1.desk.scalewidth - Form1.cad.width) / 2
       Else
          Form1.deskHScroll.Visible = True    '水平滚动条
          Form1.deskHScroll.Max = Form1.cad.width - Form1.desk.scalewidth
          Form1.deskHScroll.Min = 0
          Form1.deskHScroll.Value = hvalue    '水平滚动条
          Form1.deskHScroll.SmallChange = Form1.deskHScroll.Max / 10
          Form1.deskHScroll.LargeChange = Form1.deskHScroll.Max / 5
       End If
End Sub

'当鼠标到达视图边界时,自动移动图纸
Public Sub MovePaper(X As Single, Y As Single, object As Object)
Dim xx As Single, yy As Single  '移动的距离
    With Form1.cad
    If Form1.deskHScroll.Visible Then
       If X < Deskx1 Then   '右移
          xx = Form1.desk.ScaleX(Form1.desk.width / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'deskx1 = deskx1 - xx
          'deskx2 = deskx2 - xx
          .left = .left + xx
          Scrollbar Abs(.left), Abs(.top)  '重设滚动条
          'Exit Sub
       End If
       If X > Deskx2 Then    '左移
          xx = Form1.desk.ScaleX(Form1.desk.width / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'deskx1 = deskx1 + xx
          'deskx2 = deskx2 + xx
          .left = .left - xx
          Scrollbar Abs(.left), Abs(.top)  '重设滚动条
          'Exit Sub
       End If
    End If
    If Form1.deskvscroll.Value Then
       If Y < Desky1 Then    '下移
          yy = Form1.desk.ScaleY(Form1.desk.height / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'desky1 = desky1 - yy
          'desky1 = desky1 - xx
          .top = .top + yy
          Scrollbar Abs(.left), Abs(.top)  '重设滚动条
          'Exit Sub
       End If
       If Y > Desky2 Then   '上移
          yy = Form1.desk.ScaleY(Form1.desk.height / 20, Form1.desk.scalemode, Form1.cad.scalemode)
          'desky1 = desky1 + yy
          'desky2 = desky2 + xx
          .top = .top - yy
          Scrollbar Abs(.left), Abs(.top)  '重设滚动条
          'Exit Sub
       End If
    End If
    End With
End Sub

'显示大十字光标
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

'捕捉时的鼠标
Public Sub SnapeMouse(object As Object, X As Single, Y As Single)
Dim mode, wid
If Mousesnape = "snapecirle" Then
   mode = object.DrawMode
   wid = object.DrawWidth
   object.DrawMode = 7
   object.DrawWidth = 1
   If SnapeMouseFlag = 0 Then     '如果为0,则不要清除原图形,因为没有原图形
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
Form1.cad.Cls                       '清除制图区
For i = 1 To UBound(LineType)       '重画所有直线
    Form1.Savecommvar               '保存公共参数
    Form1.cad.DrawMode = VBRUN.DrawModeConstants.vbCopyPen
    Form1.cad.DrawStyle = LineType(i).comvar.style
    Form1.cad.DrawWidth = LineType(i).comvar.width
    Form1.cad.Line (LineType(i).x0, LineType(i).y0)-(LineType(i).X, LineType(i).Y), LineType(i).comvar.col
    Form1.redocommvar               '还原公共参数
Next i
For i = 1 To UBound(CircleType)     '重画所有圆
    Form1.Savecommvar                '保存公共参数
    Form1.cad.DrawMode = VBRUN.DrawModeConstants.vbCopyPen
    Form1.cad.DrawWidth = CircleType(i).comvar.width
    Form1.cad.DrawStyle = CircleType(i).comvar.style
    Form1.cad.Circle (CircleType(i).X, CircleType(i).Y), CircleType(i).r, CircleType(i).comvar.col
    Form1.redocommvar               '还原公共参数
Next i
End Sub

Public Sub RightChickMenu(X As Single, Y As Single)     '单击鼠标右键时显示的菜单
       '引用方式:
       'form1.PopupMenu 要显示的菜单,标志,,座标X, 座标Y,默认菜单项
       Select Case CurrentOperist
              Case "连画线"
                   Form1.meuncols.Visible = True
                   Form1.meuncolse.Visible = True
                   Form1.meunredo.Visible = True
                   Form1.meunu.Visible = True
                   Form1.PopupMenu Form1.meuntool
                   Form1.meuncols.Visible = False
                   Form1.meuncolse.Visible = False
                   Form1.meunredo.Visible = False
                   Form1.meunu.Visible = False
              Case "Line", "Rectangle", "正三角形", "正方形", "正六边形", "等边三角形"
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

'提示栏
Public Sub tishi(X As Single, Y As Single, Button As Integer)
Dim xx As Single, yy As Single, rad As Double
Dim sstring As String
xx = X * Ratio
yy = Y * Ratio
sstring = "请选取目标"
If user.CurrentOperist <> "扇形" Or user.CurrentOperist <> "Arc" Or user.CurrentOperist <> "circle" Then
       Form1.dispbar.Panels.Item(2).text = "横座标(X):"
       Form1.dispbar.Panels.Item(4).text = "纵座标(Y):"
       Form1.dispbar.Panels.Item(4).Visible = True
       Form1.dispbar.Panels.Item(5).Visible = True
End If
Select Case CurrentOperist
              Case "Line"
                   If Button = VBRUN.vbLeftButton Then
                      Select Case 座标
                             Case 1
                                  sstring = "请确定直线第二点(X2,Y2)"
                             Case 2
                                  sstring = "请确定长度:"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.dispbar.Panels.Item(2).text = "长度(L):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                      End Select
                   Else
                      sstring = "请输入直线第一点(X1,Y1)"
                   End If
              Case "连画线"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  Select Case 座标
                                         Case 1
                                              sstring = "请确定直线第二点(X2,Y2)"
                                         Case 2
                                              sstring = "请确定长度:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                  (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.dispbar.Panels.Item(2).text = "长度(L):"
                                              Form1.dispbar.Panels.Item(4).Visible = False
                                              Form1.dispbar.Panels.Item(5).Visible = False
                                  End Select
                               Else
                                  sstring = "请输入直线第一点(X1,Y1)"
                               End If
                          Case 2
                               Select Case 座标
                                      Case 1
                                           sstring = "请输入直线下一点(Xn,Yn)"
                                      Case 2
                                              sstring = "请确定长度:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                     (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.dispbar.Panels.Item(2).text = "长度(L):"
                                              Form1.dispbar.Panels.Item(4).Visible = False
                                              Form1.dispbar.Panels.Item(5).Visible = False
                                  End Select
                   End Select
              Case "Rectangle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定矩形第三点(X3,Y3)"
                   Else
                      sstring = "请输入矩形第一点(X1,Y1)"
                   End If
              Case "三角形"
                   If user.drawflag = 1 Then
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定三角形第二点(X2,Y2)"
                               Else
                                  sstring = "请输入三角形第一点(X1,Y1)"
                               End If
                   Else
                         sstring = "请输入三角形第三点"
                   End If
              Case "正三角形"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定正三角形第二点(X2,Y2)"
                   Else
                      sstring = "请输入正三角形第一点(X1,Y1)"
                   End If
              Case "等边三角形"
              Case "正方形"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定正方形第二点(X2,Y2)"
                   Else
                      sstring = "请输入正方形第一点(X1,Y1)"
                   End If
              Case "正六边形"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定正六边形第二点(X2,Y2)"
                   Else
                      sstring = "请输入正六边形第一点(X1,Y1)"
                   End If
              Case "Line Style"
              Case "Arc"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定圆弧的半径(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.dispbar.Panels.Item(2).text = "半径(R):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                               Else
                                  sstring = "请输入圆弧的圆心(X0,Y0)"
                               End If
                          Case 2
                               sstring = "请确定圆弧起始角"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               Form1.dispbar.Panels.Item(2).text = "起始角:"
                               Form1.dispbar.Panels.Item(4).Visible = False
                               Form1.dispbar.Panels.Item(5).Visible = False
                               
                          Case 3
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               
                               Form1.dispbar.Panels.Item(2).text = "起始角:"
                               Form1.dispbar.Panels.Item(4).text = "终止角:"
                               sstring = "请确定圆弧终止角"
                   End Select
              Case "扇形"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定扇形的半径(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                                  Form1.dispbar.Panels.Item(2).text = "半径(R):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                               Else
                                  sstring = "请输入扇形的圆心(X0,Y0)"
                               End If
                          Case 2
                               sstring = "请确定扇形起始角"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               Form1.dispbar.Panels.Item(2).text = "起始角:"
                               Form1.dispbar.Panels.Item(4).Visible = False
                               Form1.dispbar.Panels.Item(5).Visible = False
                               
                          Case 3
                               sstring = "请确定扇形终止角"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               
                               Form1.dispbar.Panels.Item(2).text = "起始角:"
                               Form1.dispbar.Panels.Item(4).text = "终止角:"
                   End Select
              Case "Ellipse"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定椭圆的半径(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                                  Form1.dispbar.Panels.Item(2).text = "半径(R):"
                                  Form1.dispbar.Panels.Item(4).Visible = False
                                  Form1.dispbar.Panels.Item(5).Visible = False
                               Else
                                  sstring = "请输入椭圆的圆心(X0,Y0)"
                               End If
                          Case 2
                               sstring = "请确定椭圆离心率"
                          End Select
              Case "circle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定半径(R)"
                      rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                      xx = rad * Ratio
                      Form1.dispbar.Panels.Item(2).text = "半径(R):"
                      Form1.dispbar.Panels.Item(4).Visible = False
                      Form1.dispbar.Panels.Item(5).Visible = False
                   Else
                      sstring = "请输入圆心(X0,Y0)"
                   End If
              Case "move"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定移动到的位置"
                   End If
              Case "copy"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定复制到的位置"
                   End If
              Case "round", "rounda"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定旋转角度"
                      Form1.dispbar.Panels.Item(2).text = "角度(A):"
                      Form1.dispbar.Panels.Item(4).Visible = False
                      Form1.dispbar.Panels.Item(5).Visible = False
                      xx = X - user.Mouseleftdownx
                      yy = Y - user.mouseleftdowny
                      xx = math.arctoangle(math.angle(xx, yy))
                    End If
              Case "mirror"
                    If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定镜像线的终点"
                    Else
                      sstring = "请确定镜像线的起点"
                    End If
              Case Else
                      sstring = "请选择目标"
       End Select
       Form1.dispbar.Panels.Item(3).text = xx
       Form1.dispbar.Panels.Item(5).text = yy
       Form1.dispbar.Panels.Item(1).text = sstring
End Sub

'提示栏信息
Public Sub TiShiInitale(X As Single, Y As Single, Button As Integer)
Dim xx As Single, yy As Single, rad As Double
Dim sstring As String
xx = X * Ratio
yy = Y * Ratio
sstring = "请选取目标"
'If user.currentoperist <> "扇形" Or user.currentoperist <> "Arc" Or user.currentoperist <> "circle" Then
'       Form1.tishi.Item(1).Caption = "横座标(X):"
'       Form1.tishi.Item(2).Caption = "纵座标(Y):"
'       Form1.tishitext2.Visible = True
'       Form1.tishitext1.Visible = True
'End If
Form1.tishi.Item(1).Caption = "横座标(X):"
Form1.tishi.Item(2).Caption = "纵座标(Y):"
If Button <> VBRUN.MouseButtonConstants.vbLeftButton And Not (CurrentOperist = "Arc" And drawflag = 2) And Not (CurrentOperist = "扇形" And drawflag = 2) Then
   Form1.tishi.Item(2).Visible = True
   Form1.tishitext2.Visible = True
End If
Select Case CurrentOperist
              Case "Line"
                   If Button = VBRUN.vbLeftButton Then
                      Select Case 座标
                             Case 1
                                  sstring = "请确定直线第二点(X2,Y2)"
                             Case 2
                                  sstring = "请确定长度:"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.tishi.Item(1).Caption = "长度(L):"
                                  Form1.tishi.Item(2).Visible = False
                                  Form1.tishitext2.Visible = False
                      End Select
                   Else
                      sstring = "请输入直线第一点(X1,Y1)"
                   End If
              Case "连画线"
                   Select Case drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  Select Case 座标
                                         Case 1
                                              sstring = "请确定直线第二点(X2,Y2)"
                                         Case 2
                                              sstring = "请确定长度:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                  (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.tishi.Item(1).Caption = "长度(L):"
                                              Form1.tishi.Item(2).Visible = False
                                              Form1.tishitext2.Visible = False
                                  End Select
                               Else
                                  sstring = "请输入直线第一点(X1,Y1)"
                               End If
                          Case 2
                               Select Case 座标
                                      Case 1
                                           sstring = "请输入直线下一点(Xn,Yn)"
                                      Case 2
                                              sstring = "请确定长度:"
                                              rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                                     (user.mouseleftdowny - Y) ^ 2)
                                              xx = rad * Ratio
                                              Form1.tishi.Item(1).Caption = "长度(L):"
                                              Form1.tishi.Item(2).Visible = False
                                              Form1.tishitext2.Visible = False
                                  End Select
                   End Select
              Case "Rectangle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定矩形第三点(X3,Y3)"
                   Else
                      sstring = "请输入矩形第一点(X1,Y1)"
                   End If
              Case "三角形"
                   If user.drawflag = 1 Then
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定三角形第二点(X2,Y2)"
                               Else
                                  sstring = "请输入三角形第一点(X1,Y1)"
                               End If
                   Else
                         sstring = "请输入三角形第三点"
                   End If
              Case "正三角形"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定正三角形第二点(X2,Y2)"
                   Else
                      sstring = "请输入正三角形第一点(X1,Y1)"
                   End If
              Case "等边三角形"
              Case "正方形"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定正方形第二点(X2,Y2)"
                   Else
                      sstring = "请输入正方形第一点(X1,Y1)"
                   End If
              Case "正六边形"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定正六边形第二点(X2,Y2)"
                   Else
                      sstring = "请输入正六边形第一点(X1,Y1)"
                   End If
              Case "Line Style"
              Case "Arc"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定圆弧的半径(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad * Ratio
                                  Form1.tishi.Item(1).Caption = "半径(R):"
                                  Form1.tishi.Item(2).Visible = False
                                  Form1.tishitext2.Visible = False
                               Else
                                  sstring = "请输入圆弧的圆心(X0,Y0)"
                               End If
                          Case 2
                               sstring = "请确定圆弧起始角"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               xx = rad    '弧度
                               xx = 180 * xx / pi '转化为度
                               Form1.tishi.Item(1).Caption = "起始角:"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                          Case 3
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               yy = rad    '弧度
                               yy = 180 * yy / pi '转化为度
                               xx = user.ArcType(UBound(user.ArcType)).start
                               xx = 180 * xx / pi '转化为度
                               
                               Form1.tishi.Item(1).Caption = "起始角:"
                               Form1.tishi.Item(2).Caption = "终止角:"
                               sstring = "请确定圆弧终止角"
                   End Select
              Case "扇形"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定扇形的半径(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                                  Form1.tishi.Item(1).Caption = "半径(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               Else
                                  sstring = "请输入扇形的圆心(X0,Y0)"
                               End If
                          Case 2
                               sstring = "请确定扇形起始角"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               
                               Form1.tishi.Item(1).Caption = "起始角:"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               
                          Case 3
                               sstring = "请确定扇形终止角"
                               
                               xx = X - user.ArcType(UBound(user.ArcType)).X
                               yy = Y - user.ArcType(UBound(user.ArcType)).Y
                               '计算结束角
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
                               
                               Form1.tishi.Item(1).Caption = "起始角:"
                               Form1.tishi.Item(2).Caption = "终止角:"
                               
                   End Select
              Case "Ellipse"
                    Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定椭圆的半径(R)"
                                  rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                                  xx = rad
                               Form1.tishi.Item(1).Caption = "半径(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               'Form1.tishi.Item().Visible = False
                               Else
                                  sstring = "请输入椭圆的圆心(X0,Y0)"
                               End If
                          Case 2
                               sstring = "请确定椭圆离心率"
                          End Select
              Case "circle"
                        If Button = VBRUN.vbLeftButton Then
                          sstring = "请确定半径(R)"
                           rad = Sqr((user.Mouseleftdownx - X) ^ 2 + _
                                        (user.mouseleftdowny - Y) ^ 2)
                           xx = rad * Ratio
                               Form1.tishi.Item(1).Caption = "半径(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                        Else
                          sstring = "请输入圆心(X0,Y0):"
                        End If
              Case "move"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定移动到的位置"
                   End If
              Case "copy"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定复制到的位置"
                   End If
              Case "round", "rounda"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定旋转角度"
                               Form1.tishi.Item(1).Caption = "角度(A):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               'Form1.tishi.Item(1).Visible = False
                      xx = X - user.Mouseleftdownx
                      yy = Y - user.mouseleftdowny
                      xx = math.arctoangle(math.angle(xx, yy))
                    End If
              Case "mirror"
                    If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定镜像线的终点"
                    Else
                      sstring = "请确定镜像线的起点"
                    End If
              Case Else
                      sstring = "请选择目标"
       End Select
       Form1.tishitext1.text = xx
       Form1.tishitext2.text = yy
       Form1.tishi.Item(0).Caption = sstring


End Sub

Private Sub tishiinit1(Button As Integer)

Dim sstring As String
       Form1.dispbar.Panels.Item(2).text = "横座标(X):"
       Form1.dispbar.Panels.Item(4).text = "纵座标(Y):"
       Select Case CurrentOperist
              Case "Line"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定直线第二点(x2,y2)"
                   Else
                      sstring = "请输入直线第一点(x1,y1)"
                   End If
              Case "连画线"
                   Select Case user.drawflag
                          Case 1
                               If Button = VBRUN.vbLeftButton Then
                                  sstring = "请确定直线第二点(x2,y2)"
                               Else
                                  sstring = "请输入直线第一点(x1,y1)"
                               End If
                          Case 2
                               sstring = "请输入直线第n点(xn,yn)"
                   End Select
              Case "Rectangle"
                   If Button = VBRUN.vbLeftButton Then
                      sstring = "请确定矩形第三点(x3,y3)"
                   Else
                      sstring = "请输入矩形第一点(x1,y1)"
                   End If
              Case "三角形"
                   If user.drawflag = 1 Then
                      If Button = VBRUN.vbLeftButton Then
                         sstring = "请确定第二点(x2,y2)"
                      Else
                         sstring = "请输入直线第一点(x1,y1)"
                      End If
                   Else
                   
                   End If
              Case "正三角形"
              Case "等边三角形"
              Case "正方形"
              Case "正六边形"
              Case "Line Style"
              Case "Arc"
              Case "扇形"
              Case "Ellipse"
              Case "circle"
              
              Case Else
                      sstring = "请选择目标"
       End Select
       Form1.dispbar.Panels.Item(1).text = sstring
End Sub

'从提示栏中直接输入座标数据
Public Sub KeyInputData(X As Single, Y As Single)
'drawflag的取值如下:
'-1表示目标只要两点就能确定的,当为-1时确定第二点
'-2表示确定圆的半径
'1表示目标要多点确定时,做第一步
'2表示做条二步
'3表示佬第三步
Dim mode, sty, wit
       Select Case CurrentOperist
              Case "Line", "Rectangle", "正三角形", "正方形", "正六边形", "等边三角形"
                    If drawflag = -1 Then
                       Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                       drawflag = 0
                    Else
                       Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                       drawflag = -1
                    End If
              Case "连画线"
                   Select Case drawflag
                          Case 1
                               Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                               drawflag = 2
                          Case 2
                               Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                   End Select
              Case "三角形"
                   If drawflag = 1 Then   '输入三角形的第一点
                      Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                      drawflag = 3
                   Else
                      If drawflag = 2 Then   '输入第三点
                         Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                         drawflag = 1
                      Else    '输入第二点
                         drawflag = 1
                         Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                         drawflag = 2
                      End If
                    End If
              Case "circle"
                    If drawflag = -2 Then '确定圆的半径
                       '提示信息
                          Form1.tishi.Item(0).Caption = "请输入圆心(X0,Y0)"
                          Form1.tishi.Item(1).Caption = "横座标(X):"
                          Form1.tishi.Item(2).Visible = True
                          Form1.tishitext2.Visible = True
                       drawflag = 0
                       ReDim Preserve CircleType(UBound(CircleType) + 1)
                       CircleType(UBound(CircleType)).r = X  '半径
                       name = "circle"
                       Savepraam  '公共参数的存储,包括圆心
                       '显示圆
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
                    Else   '确定圆心
                       '提示信息
                           Form1.tishi.Item(0).Caption = "请确定半径(R)"
                           Form1.tishi.Item(1).Caption = "半径(R):"
                           Form1.tishi.Item(2).Visible = False
                           Form1.tishitext2.Visible = False
                       Form1.cad_MouseDown VBRUN.vbLeftButton, 0, X, Y
                       draw.showpoint X, Y, Form1.cad, Snapecolor  '突出显示圆心
                       drawflag = -2
                       Form1.tishitext1.SetFocus
                    End If
                Case "Arc"
                   Select Case user.drawflag
                          Case 1
                               '确定圆心
                               Mouseleftdownx = X
                               mouseleftdowny = Y
                               drawflag = -2
                               '提示信息
                               Form1.tishi.Item(0).Caption = "请确定圆弧的半径(R)"
                               Form1.tishi.Item(1).Caption = "半径(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               Form1.tishitext1.SetFocus
                          Case -2
                               Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                               Form1.tishi.Item(0).Caption = "请确定圆弧起始角"
                               Form1.tishi.Item(1).Caption = "起始角(A):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               drawflag = 2
                               '存储半径
                               ReDim Preserve ArcType(UBound(ArcType) + 1)
                               With ArcType(UBound(ArcType))
                                    .r = X
                               End With
                               name = "arc"
                               Savepraam  '存储公共参数
                               
                          Case 2
                               drawflag = 3
                               Form1.tishi.Item(0).Caption = "请确定圆弧终止角"
                               Form1.tishi.Item(1).Caption = "起始角(A):"
                               Form1.tishi.Item(2).Caption = "终止角(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               Form1.tishitext1.Enabled = False
                               Form1.tishitext2.SetFocus
                               '存储起始角
                               ArcType(UBound(ArcType)).start = X * pi / 180
                          Case 3
                               drawflag = 1
                               Form1.tishi.Item(0).Caption = "请确定圆弧的圆心(X,Y):"
                               Form1.tishi.Item(1).Caption = "横座标(A):"
                               Form1.tishi.Item(2).Caption = "纵座标(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               Form1.tishitext1.Enabled = True
                               '存储终止角
                               ArcType(UBound(ArcType)).end = Y * pi / 180
                               '显示圆弧
                               '保存参数
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
              Case "扇形"
                   Select Case user.drawflag
                          Case 1
                               '确定圆心
                               Mouseleftdownx = X
                               mouseleftdowny = Y
                               drawflag = -2
                               '提示信息
                               Form1.tishi.Item(0).Caption = "请确定扇形的半径(R)"
                               Form1.tishi.Item(1).Caption = "半径(R):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               Form1.tishitext1.SetFocus
                          Case -2
                               Form1.cad_MouseUp VBRUN.vbLeftButton, 0, X, Y
                               Form1.tishi.Item(0).Caption = "请确定扇形起始角"
                               Form1.tishi.Item(1).Caption = "起始角(A):"
                               Form1.tishi.Item(2).Visible = False
                               Form1.tishitext2.Visible = False
                               drawflag = 2
                               '存储半径
                               ReDim Preserve ArcType(UBound(ArcType) + 1)
                               With ArcType(UBound(ArcType))
                                    .r = X
                               End With
                               name = "arc"
                               Savepraam  '存储公共参数
                               
                          Case 2
                               drawflag = 3
                               Form1.tishi.Item(0).Caption = "请确定扇形终止角"
                               Form1.tishi.Item(1).Caption = "起始角(A):"
                               Form1.tishi.Item(2).Caption = "终止角(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               'Form1.tishitext1.Enabled = False
                               Form1.tishitext2.SetFocus
                               '存储起始角
                               ArcType(UBound(ArcType)).start = -X * pi / 180
                          Case 3
                               drawflag = 1
                               Form1.tishi.Item(0).Caption = "请确定扇形的圆心(X,Y):"
                               Form1.tishi.Item(1).Caption = "横座标(A):"
                               Form1.tishi.Item(2).Caption = "纵座标(A):"
                               Form1.tishi.Item(2).Visible = True
                               Form1.tishitext2.Visible = True
                               'Form1.tishitext1.Enabled = True
                               '存储终止角
                               ArcType(UBound(ArcType)).end = -Y * pi / 180
                               '显示圆弧
                               '保存参数
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
             '                     sstring = "请确定椭圆的半径(R)"
              '                    rad = Sqr((user.mouseleftdownx - x) ^ 2 + _
               '                         (user.mouseleftdowny - y) ^ 2)
                '                  xx = rad
                 '              Form1.tishi.Item(1).Caption = "半径(R):"
                  '             Form1.tishi.Item(2).Visible = False
                   '            Form1.tishitext2.Visible = False
                    '           'Form1.tishi.Item().Visible = False
                     '          Else
                      '            sstring = "请输入椭圆的圆心(X0,Y0)"
                       '        End If
                        '  Case 2
                         '      sstring = "请确定椭圆离心率"
                          'End Select
      '        Case "move"
       '            If button = VBRUN.vbLeftButton Then
        '              sstring = "请确定移动到的位置"
         '          End If
          '    Case "copy"
           '        If button = VBRUN.vbLeftButton Then
            '          sstring = "请确定复制到的位置"
             '      End If
              'Case "round", "rounda"
   '                If button = VBRUN.vbLeftButton Then
    '                  sstring = "请确定旋转角度"
     '                          Form1.tishi.Item(1).Caption = "角度(A):"
      '                         Form1.tishi.Item(2).Visible = False
       '                        Form1.tishitext2.Visible = False
        '                       'Form1.tishi.Item(1).Visible = False
         '             xx = x - user.mouseleftdownx
          '            yy = y - user.mouseleftdowny
           '           xx = math.arctoangle(math.angle(xx, yy))
            '        End If
             ' Case "mirror"
              '      If button = VBRUN.vbLeftButton Then
               '       sstring = "请确定镜像线的终点"
                '    Else
       '          '     sstring = "请确定镜像线的起点"
        '            End If
         '     Case Else
          '            sstring = "请选择目标"
       End Select

End Sub

'清除捕捉到的目标图形
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

'保存文件
Public Sub SaveFile()
Dim k, i, j, ss As String
'On Error Resume Next
With Form1.CommonDialog1
     .DialogTitle = "保存为"
     .Filter = "*.kld"
     .FileName = "*.kld"
     .ShowSave
     .DialogTitle = ""
     .Filter = ""
End With
If Form1.CommonDialog1.FileName = "*.kld" Then Form1.CommonDialog1.FileName = "": Exit Sub
k = FreeFile()
Open Form1.CommonDialog1.FileName For Output As #k
ss = "计算机制图 设计:康林"
Print #k, ss
Print #k, 2001.3  '版本号

With paper         '肿存图纸参数
     Print #k, .height
     Print #k, .left
     Print #k, .top
     Print #k, .width
     Print #k, .color
     Print #k, .scaleheigt
     Print #k, .scalewidth
     Print #k, .until
     End With
     
Print #k, Ratio    '比例尺
Print #k, Ratio1
Print #k, Ratio2

     If UBound(LineType) > 0 Then   '直线
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

     j = UBound(CircleType)  '圆
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

     j = UBound(RectangleFourpointType)   '四点表示的矩形
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
    
    j = UBound(ArcType)    '圆弧
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

    j = UBound(SameRectangleType)    '正方形
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

    j = UBound(SixegdeType)    '正六边形
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

    j = UBound(RectangleType)    '两点表示的矩形
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
    j = UBound(ThreeAngleType)   '三角形
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
    j = UBound(EllipseType)   '椭圆
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
If ss <> "计算机制图 设计:康林" Then
   i = MsgBox("文件类型不对,是否重选文件?", vbQuestion + vbYesNo)
   If i = vbYes Then
      GoTo openfileloop
   End If
   Exit Sub
End If
Input #k, ver  '版本号

With paper       '图纸参数
     Input #k, .height
     Input #k, .left
     Input #k, .top
     Input #k, .width
     Input #k, .color
     Input #k, .scaleheigt
     Input #k, .scalewidth
     Input #k, .until
     End With
     
Input #k, Ratio   '比例尺
Input #k, Ratio1
Input #k, Ratio2

Inimemeroy   '清除以前的数据
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

'图纸参数
With paper
     i = GetPrivateProfileString("paper", "width", "420", sstring, 18, inifile)
     .width = left$(sstring, i)
     If Err = 13 Then .width = 420 '类型不配
     i = GetPrivateProfileString("paper", "height", "297", sstring, 18, inifile)
     .height = left$(sstring, i)
     If Err = 13 Then .height = 297  '类型不配
     i = GetPrivateProfileString("paper", "color", "0", sstring, 18, inifile)
     .color = left$(sstring, i)
     If Err = 13 Then .color = 0   '类型不配
     i = GetPrivateProfileString("paper", "left", "0", sstring, 18, inifile)
     .left = left$(sstring, i)
     If Err = 13 Then .left = 0   '类型不配
     i = GetPrivateProfileString("paper", "name", "0", sstring, 18, inifile)
     .color = left$(sstring, i)
     If Err = 13 Then .color = 0   '类型不配
     i = GetPrivateProfileString("paper", "scaleheigt", "0", sstring, 18, inifile)
     .scaleheigt = left$(sstring, i)
     If Err = 13 Then .scaleheigt = 0    '类型不配
     i = GetPrivateProfileString("paper", "scalewidth", "0", sstring, 18, inifile)
     .scalewidth = left$(sstring, i)
     If Err = 13 Then .scalewidth = 0    '类型不配
     i = GetPrivateProfileString("paper", "until", "0", sstring, 18, inifile)
     .until = left$(sstring, i)
     If Err = 13 Then .until = 0    '类型不配
     i = GetPrivateProfileString("paper", "scalemode", "0", sstring, 18, inifile)
     .scalemode = left$(sstring, i)
     If Err = 13 Then .scalemode = 0    '类型不配
End With

End Sub
