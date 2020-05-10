Attribute VB_Name = "Face"
'此模块为界面函数
'作者:康林

Option Explicit

Private Const SRCCOPY = &HCC0020
Private Declare Function GetDC Lib "user32" (ByVal hwnd As Long) As Long
Private Declare Function CreateCompatibleBitmap Lib "gdi32" (ByVal hdc As Long, ByVal nWidth As Long, ByVal nHeight As Long) As Long
Private Declare Function CreateCompatibleDC Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function selectobject Lib "gdi32" Alias "SelectObject" (ByVal hdc As Long, ByVal hObject As Long) As Long
Private Declare Function DeleteDC Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function StretchBlt Lib "gdi32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal nSrcWidth As Long, ByVal nSrcHeight As Long, ByVal dwRop As Long) As Long
Private Declare Function GetMenu Lib "user32" (ByVal hwnd As Long) As Long
Private Declare Function SetMenuItemBitmaps Lib "user32" (ByVal hMenu As Long, ByVal nPosition As Long, ByVal wFlags As Long, ByVal hBitmapUnchecked As Long, ByVal hBitmapChecked As Long) As Long
Private Declare Function GetMenuItemCount Lib "user32" (ByVal hMenu As Long) As Long
Private Declare Function GetMenuItemID Lib "user32" (ByVal hMenu As Long, ByVal nPos As Long) As Long
Private Declare Function GetMenuString Lib "user32" Alias "GetMenuStringA" (ByVal hMenu As Long, ByVal wIDItem As Long, ByVal lpString As String, ByVal nMaxCount As Long, ByVal wFlag As Long) As Long
Private Declare Function GetMenuCheckMarkDimensions Lib "user32" () As Long
'得到由SetMenuItemBitmaps（）所要的Bitmap的大小

'Const ON_ERROR_RESUME_MEXT = 1

Public Sub PaperInit(object As Object)  '图纸初始化
'Object=子窗体中的cad控件
'If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
'End If
       
       '初始化图纸
       '加入点击新文件时,选取图纸
       selectpaper.Show 1  '把选好的图纸放入配置文件中
       '从配置文件中得到图纸的大小,并设置图纸的大小
       PaperBigLittle object
       
       
       '图纸结构的初始化
       PaperTypeInitial object
       
       '初始化图板
       DeskInitial object
       
End Sub

'从配置文件中得到图纸的大小,并设置图纸的大小
Private Sub PaperBigLittle(object As Object)
'Object=子窗体中的cad控件
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Dim i As Integer, ss As String * 20
Dim Width As Single, Height As Single
      i = GetPrivateProfileString("paper", "width", "8900", ss, 20, mmain.Inifile)
      If i = 0 Then
         ss = "8900"
      Else
          ss = left$(ss, i)
      End If
      Width = Val(ss)
      i = GetPrivateProfileString("paper", "height", "4900", ss, 20, mmain.Inifile)
      If i = 0 Then
         ss = "4800"
      Else
         ss = left$(ss, i)
      End If
      Height = Val(ss)
      object.Width = Width
      object.Height = Height
End Sub

'图纸类型结构的初始化
Private Sub PaperTypeInitial(object As Object)
'Object=子窗体中的cad控件
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Dim i, ss As String * 20, s As String
       '单位
       i = GetPrivateProfileString("选项", "单位", "mm", ss, 20, Inifile)
       If i <> 0 Then
          s = left$(ss, i)
       Else
          s = "mm"
       End If
       object.Container.Container.InputPaperUnits (s)
       '比例尺
       i = GetPrivateProfileString("选项", "比例尺", "1", ss, 20, Inifile)
       If i <> 0 Then
          ss = left$(ss, i)
       Else
          ss = "1"
       End If
       object.Container.Container.InputPaperRatio (Val(ss))
       i = GetPrivateProfileString("选项", "比例尺1", "1", ss, 20, Inifile)
       If i <> 0 Then
          ss = left$(ss, i)
       Else
          ss = "1"
       End If
       object.Container.Container.InputPaperRatio1 (Val(ss))
       i = GetPrivateProfileString("选项", "比例尺2", "1", ss, 20, Inifile)
       If i <> 0 Then
          ss = left$(ss, i)
       Else
          ss = "1"
       End If
       object.Container.Container.InputPaperRatio2 (Val(ss))
       '图纸颜色,只能放在最后,默认值是字符,赋值后就结束
       i = GetPrivateProfileString("选项", "图纸颜色", "vbWhite", ss, 20, Inifile)
       If i <> 0 Then
          object.BackColor = left$(ss, i)
       End If
End Sub

'初始化图板
Private Sub DeskInitial(object As Object)
'Object=子窗体中的cad控件
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Dim i, ss As String * 20
        
        '图板的颜色
        '从配置文件中得到图板的颜色,只能放在最后,默认值是字符,赋值后就结束
        i = GetPrivateProfileString("选项", "图板颜色", "vbBlue", ss, 20, Inifile)
        If i <> 0 Then
           object.Container.BackColor = left$(ss, i)
        End If
End Sub


'液动条
Public Sub Scroll(object As Object, HScrol As Single, Vscrol As Single)
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
'Object输入的的是子窗体
'坚直液动条
If object.cad.Height > object.desk.ScaleHeight Then
       object.Vscroll.Visible = True
       With object.Vscroll
            .Min = 0
            .Max = object.cad.Height - object.desk.ScaleHeight
            .SmallChange = .Max / 10
            .LargeChange = .Max / 5
            If Vscrol > 0 Then Vscrol = 0
            If .Max < -Vscrol Then Vscrol = -.Max
            .Value = -Vscrol
       End With
Else
       object.Vscroll.Visible = False
       object.cad.top = (object.desk.ScaleHeight - object.cad.Height) / 2
End If
'水平液动条
If object.cad.Width > object.desk.Scalewidth Then
       object.HScroll.Visible = True
       With object.HScroll
            .Min = 0
            .Max = object.cad.Width - object.desk.Scalewidth
            .SmallChange = .Max / 10
            .LargeChange = .Max / 5
            If HScrol > 0 Then HScrol = 0
            If -HScrol > .Max Then HScrol = -.Max
            .Value = -HScrol
        End With
Else
        object.HScroll.Visible = False
        object.cad.left = (object.desk.ScaleHeight - object.cad.Height) / 2
End If

'object.ViewLimit
End Sub

'鼠标变换
Public Sub MouseChange_OK(i As Integer, object As Object)
With object '传递的是子窗体
     Select Case i
            Case 0, 4 '比例变换,左上角右下角
                 .cad.MousePointer = vbSizeNWSE
            Case 1, 5 '比例变换,上中点,下中点
                 .cad.MousePointer = vbSizeNS
            Case 2, 6 '比例变换,右上角,左下角
                 .cad.MousePointer = vbSizeNESW
            Case 3, 7 '比例变换,右中点,左中点
                 .cad.MousePointer = vbSizeWE
            Case 8 '移动
                .cad.MousePointer = vbSizeAll
     End Select
Select Case .Mousestyle
       Case "大十字光标"
            .Line2.Visible = False
            .Line1.Visible = False
       Case "圆形光标"
             .Smouse.Visible = False
End Select
End With
End Sub

'取消变换光标
Public Sub MouseChange_Undo(object As Object)
With object '传递的是子窗体
     Select Case .Mousestyle
            Case "箭形光标"
                 .cad.MousePointer = vbArrow
            Case "小十字光标"
                 .cad.MousePointer = vbCrosshair
            Case "大十字光标"
                 .cad.MousePointer = vbCrosshair
                 .Line1.Visible = True
                 .Line2.Visible = True
            Case "圆形光标"
                  .cad.MousePointer = vbCrosshair
                  .Smouse.Visible = True
     End Select
End With
End Sub

'标注线上文字的位置,修改此处时,注意同时修改旋转部分的相应的地方
Public Sub Text_Position(Tfont As TextType, object As Object)
With object
Select Case Dimension.Position
       Case 0
           .left = Tfont.x - Tfont.Width / 2
           .top = Tfont.y - Tfont.Height
       Case 1
              
       Case 2
           .left = Tfont.x - Tfont.Width / 2
           .top = Tfont.y - Tfont.Height
End Select
End With
End Sub

'使编辑工具不响应事件
Public Sub NoEnabled_Edit()
       With fMainForm
            .mnuEditCut.Enabled = False
            .mnuEditCopy = False
            '.mnuEditPaste = False
            .mnuEditDelete = False
            .mnuEditMakeMove = False
            .mnuEditMakeCopy = False
            .mnuEditMakeMirror = False
            .mnuEditMakeMirrorSave = False
            .mnuEditMakeRound = False
            .mnuEditModefiyArrayCircle = False
            .mnuEditModefiyArrayRectangle = False
            '.mnuEditModifyBreak = False
            '.mnuEditModifyChamfer = False
            '.mnuEditModifyFillet = False
            .mnuEditModifyRatioChange = False
            '.mnuEditModifyTrim = False
       End With
       With fMainForm.TB(TB_EDIT).Buttons
            .Item("cut").Enabled = False
            .Item("copy").Enabled = False
            '.Item("paste").Enabled = False
            .Item("delete").Enabled = False
            .Item("undo").Enabled = False
            .Item(9).Enabled = False
       End With
End Sub

'使编辑工具响应事件
Public Sub Enabled_Edit()
       With fMainForm
            .mnuEditCut.Enabled = True
            .mnuEditCopy = True
            '.mnuEditPaste = True
            .mnuEditDelete = True
            .mnuEditMakeMove = True
            .mnuEditMakeCopy = True
            .mnuEditMakeMirror = True
            .mnuEditMakeMirrorSave = True
            .mnuEditMakeRound = True
            .mnuEditModefiyArrayCircle = True
            .mnuEditModefiyArrayRectangle = True
            '.mnuEditModifyBreak = True
            '.mnuEditModifyChamfer = True
            '.mnuEditModifyFillet = True
            .mnuEditModifyRatioChange = True
            '.mnuEditModifyTrim = True
       End With
       With fMainForm.TB(TB_EDIT).Buttons
            .Item("cut").Enabled = True
            .Item("copy").Enabled = True
            '.Item("paste").Enabled = True
            .Item("delete").Enabled = True
            .Item("undo").Enabled = True
            .Item(9).Enabled = True
       End With
End Sub

'给菜单加上图片
Public Sub Inital_Menu(object As Object)
Dim ss As String * 30, n As Long, i As Long, L As Long
Dim hMenu As Long, ID As Long, Menu As control
Dim s As String

    'hMenu = GetMenu(object.hwnd)
i = 1
For Each Menu In object
    If TypeName(Menu) = "Menu" Then
       'L = GetMenuString(hMenu, i, ss, 30, 1)
           's = left$(ss, L)
           's = left$(StrConv(b, vbFromUnicode), L)
           s = Menu.name
           Select Case s
                  Case "mnuFileNew" '"新文件  (&N) Ctrl+N  "
                       SetMenu object, i, "new"
                  Case "mnuFileOpen" ' "打开文件(&O)... Ctrl+O     "
                       SetMenu object, i, "open"
                  Case "mnuFileSave"
                       SetMenu object, i, "save"
                  Case "mnuFilePrint"
                       SetMenu object, i, "print"
                  Case "mnuEditDelete"
                       SetMenu object, i, "delete"
                  Case "mnuEditRedraw"
                       SetMenu object, i, "redo"
                  Case "mnuEditMakeMove"
                       SetMenu object, i, "move"
                  Case "mnuEditMakeRound"
                       SetMenu object, i, "round"
                  Case "mnuEditMakeMirror"
                       SetMenu object, i, "mirror"
                  Case "mnuEditCut"
                       SetMenu object, i, "cut"
                  Case "mnuEditCopy"
                       SetMenu object, i, "copy"
                  Case "mnuEditPaste"
                       SetMenu object, i, "paste"
                  Case "mnuEditUndo", "mnuMakeUndo"
                       SetMenu object, i, "undo"
                  Case "mnuEditSelectPoint"
                       SetMenu object, i, "select"
                  Case "mnuMakeLine线段"
                       SetMenu object, i, "line"
                  Case "mnuMake连画线"
                       SetMenu object, i, "连画线"
                  Case "mnuMaketext"
                       SetMenu object, i, "文字"
                  Case "mnuMakeDim水平标注"
                       SetMenu object, i, "水平标注"
                  Case "mnuMakeDim连续水平标注"
                       SetMenu object, i, "连续水平标注"
                  Case "mnuMakeDim垂直标注"
                       SetMenu object, i, "垂直标注"
                  Case "mnuMakeDim连续垂直标注"
                       SetMenu object, i, "连续垂直标注"
                  Case "mnuMake矩形"
                       SetMenu object, i, "rectangle"
                  Case "mnuMake圆"
                       SetMenu object, i, "mcircle"
                  Case "mnuMake椭圆"
                       SetMenu object, i, "ellipse"
                  Case "mnuMake圆弧"
                       SetMenu object, i, "arc"
                  Case "mnuMake三角形"
                        SetMenu object, i, "m三角形"
                  Case "mnuMake正三角形"
                       SetMenu object, i, "m正三角形"
                  Case "mnuMake正方形"
                       SetMenu object, i, "m正方形"
                  Case "mnuMake正六边形"
                      SetMenu object, i, "m正六边形"
                  Case "mnuMake扇形"
                      SetMenu object, i, "m扇形"
                  Case "mnuViewMouseArrow"
                        SetMenu object, i, "arrow"
                  Case "mnuViewMouseCircle"
                        SetMenu object, i, "mcirclecross"
                  
           End Select
       i = i + 1
       'Open App.Path + "\menu" For Append As #1
       'Print #1, s
       'Close #1
    End If
Next Menu
End Sub

'给菜单加上图片
Private Sub SetMenu(object As Object, Postion As Long, hBitmap As String)
Dim hMenu As Long
    hMenu = GetMenu(object.hwnd)
    Call SetMenuItemBitmaps(hMenu, Postion, 0, GetBitMapHandle(object, fMainForm.imlToolbarIcons.ListImages.Item(hBitmap).PicTure), GetBitMapHandle(object, fMainForm.imlToolbarIcons.ListImages.Item(hBitmap).PicTure))
End Sub

'得到图片的句柄
Private Function GetBitMapHandle(object As Object, PicTure As StdPicture) As Long
Dim dstWidth As Long, dstHeight As Long
Dim srcWidth As Long, srcHeight As Long
Dim x As Long, y As Long
Dim Pic As New StdPicture
Dim hDC1 As Long, i As Long
Dim hBitmap As Long
Dim hDstDc As Long
Set Pic = PicTure '设置图形
hDC1 = CreateCompatibleDC(0) '建立MEMORY DC
i = selectobject(hDC1, Pic.Handle) '在该MEMORY DC 上放上BITMAP图
i = GetMenuCheckMarkDimensions '得到SETMENUITEMBITMAPS所要的BITMAP大小
'建立一个dstWidth*dstHeight 大小的图片BITMAP
dstWidth = i Mod 2 ^ 16 '高位是图片的宽
dstHeight = i / 2 ^ 16  '低位是图片的高
hBitmap = CreateCompatibleBitmap(GetDC(object.hwnd), dstWidth, dstHeight)
hDstDc = CreateCompatibleDC(GetDC(object.hwnd))
'建立MEMORY DC
'设该.........绘图区的大小=该BITMAP的大小
'且在该MEMORY DC的绘图是该BITMAP图上画图
selectobject hDstDc, hBitmap
srcHeight = Screen.ActiveForm.ScaleY(Pic.Height, vbHimetric, vbPixels)
srcWidth = Screen.ActiveForm.ScaleX(Pic.Width, vbHimetric, vbPixels)
Call StretchBlt(hDstDc, 0, 0, dstWidth, dstHeight, hDC1, 0, 0, srcWidth, srcHeight, SRCCOPY)
GetBitMapHandle = hBitmap
Call DeleteDC(hDC1)
Call DeleteDC(hDstDc)
End Function

'使按钮恢复
Public Sub UnPressButton(ToolBar As ToolBar)
Dim i
    For i = 1 To ToolBar.Buttons.Count
        ToolBar.Buttons.Item(i).Value = tbrUnpressed
    Next i
    ToolBar.Refresh  '更新工具条
End Sub

Public Sub FileToolBar(object As Object) '文件工具栏
       With object.TB(TB_FILE).Buttons
            .Clear
            .Add 1, "new", , , "new"
            .Item("new").ToolTipText = "新文件"
            .Add 2, "open", , , "open"
            .Item("open").ToolTipText = "打开文件"
            .Add 3, "save", , , "save"
            .Item("save").ToolTipText = "保存文件"
            .Add 4, "print", , , "print"
            .Item("print").ToolTipText = "打印文件"
       End With
End Sub

Public Sub EditToolBar(object As Object) '编辑工具栏
       Load object.TB(TB_EDIT)
       With object.TB(TB_EDIT).Buttons
            .Clear
            .Add 1, "cut", , , "cut"
            With .Item("cut")
                 .ToolTipText = "剪切"
            End With
            .Add 2, "copy", , , "copy"
            With .Item("copy")
                 .ToolTipText = "复制"
            End With
            .Add 3, "paste", , , "paste"
            With .Item("paste")
                 .ToolTipText = "粘贴"
            End With
            .Add 4, "delete", , , "delete"
            With .Item("delete")
                 .ToolTipText = "删除"
            End With
            .Add 5, "undo", , , "undo"
            With .Item("undo")
                 .ToolTipText = "取消"
            End With
            .Add , , , tbrSeparator '空格符
            .Add , "redo", , , "redo"
            .Item("redo").ToolTipText = "重画"
            .Add , "select", , , "select"
            .Item("select").ToolTipText = "选取"
            .Add , "ccopy", , tbrDropdown, "ccopy"
                 .Item("ccopy").ToolTipText = "复制"
            With .Item("ccopy").ButtonMenus
                 .Add , "ccopy", "复制"
                 .Add , "round", "旋转"
                 .Add , "mirror", "镜像"
            End With
            .Add , "break", , tbrDropdown, "break"
            .Item("break").ToolTipText = "切断"
            With .Item("break").ButtonMenus
                 .Add , "break", "切断"
                 .Add , "chamfer", "切角"
                 .Add , "text", "修改文字"
            End With
       End With
End Sub

Public Sub MakeToolBar(object As Object) '制图工具栏
       Load object.TB(TB_MAKE)
       With object.TB(TB_MAKE).Buttons
            .Clear
            .Add 1, "line", , tbrDropdown, "line"
            .Item("line").ToolTipText = "直线"
            With .Item("line").ButtonMenus
                  .Clear
                  .Add , "line", "直线"
                  .Add , "垂直线段", "垂直线段"
                  .Add , "连画线", "连画线"
                  .Add , "tan", "定点到圆的切线"
                  .Add , "twolinemiss", "使两直线相交"
                  .Add , "line style", "线型"
            End With
            .Add 2, "三角形", , tbrDropdown, "三角形"
            .Item("三角形").ToolTipText = "三角形"
            With .Item("三角形").ButtonMenus
                 .Clear
                 .Add 1, "三角形", "三角形"
                 .Add 2, "正三角形", "正三角形"
                 .Add 3, "rectangle", "矩形"
                 .Add 4, "正方形", "正方形"
                 .Add 5, "正六边形", "正六边形"
            End With
            .Add 3, "circle", , tbrDropdown, "circle"
            .Item("circle").ToolTipText = "圆"
            With .Item("circle").ButtonMenus
                 .Add 1, "circle", "圆"
                 .Add 2, "arc", "圆弧"
                 .Add 3, "扇形", "扇形"
                 .Add 4, "ellipse", "椭圆"
            End With
            .Add 4, "水平标注", , tbrDropdown, "水平标注"
            .Item("水平标注").ToolTipText = "水平标注"
            With .Item("水平标注").ButtonMenus
                 .Add 1, "水平标注", "水平标注"
                 .Add 2, "连续水平标注", "连续水平标注"
                 .Add 3, "垂直标注", "垂直标注"
                 .Add 4, "连续垂直标注", "连续垂直标注"
            End With
            .Add 5, "文字", , , "文字"
            .Item("文字").ToolTipText = "文字"
       End With
End Sub

Private Sub SnapeToolBar(object As Object) '捕捉工具栏
Dim t As Single
        Load object.TB(TB_SNAPE)
        'With Object
        '     t = .TB(TB_SNAPE).Width
        '     .TB(TB_SNAPE).Width = .TB(TB_SNAPE).Height
        '     .TB(TB_SNAPE).Height = t
        'End With
        Set object.TB(TB_SNAPE).Container = object.CB(1)
        With object.TB(TB_SNAPE).Buttons
             .Clear
             .Add , "snapeend", , tbrCheck, "snapeend"
             .Item("snapeend").ToolTipText = "捕捉直线或圆弧的端点"
             .Add , "snapemid", , tbrCheck, "snapemid"
             .Item("snapemid").ToolTipText = "捕捉直线或圆弧的中点"
             .Add , "snapecenter", , tbrCheck, "snapecenter"
             .Item("snapecenter").ToolTipText = "捕捉圆或椭圆的中心"
             .Add , "snapemiss", , tbrCheck, "snapemiss"
             .Item("snapemiss").ToolTipText = "捕捉交点"
             .Add , "snapeexit", , , "exit"
             .Item("snapeexit").ToolTipText = "退出捕捉"
        End With
        object.TB(TB_SNAPE).Wrappable = True
        object.TB(TB_SNAPE).Align = 3
        object.TB(TB_SNAPE).Align = 0
End Sub

'初始化工具栏
Public Sub AddToolBar(object As Object)
       object.TB(1).ImageList = object.imlToolbarIcons
       object.CB(0).Bands.Add TB_FILE, , , , , object.TB(TB_FILE)
       FileToolBar object
       object.CB(0).Bands.Item(TB_FILE).Width = object.TB(TB_FILE).Buttons.Item(1).Width * 5
       object.CB(0).Height = object.TB(TB_FILE).Height
       
       EditToolBar object
       object.CB(0).Bands.Add TB_EDIT, , , , , object.TB(TB_EDIT)
       object.CB(0).Bands.Item(TB_EDIT).Width = object.TB(TB_EDIT).Buttons.Item(1).Width * (object.TB(TB_EDIT).Buttons.Count + 2)
       
       MakeToolBar object
       object.CB(0).Bands.Add TB_MAKE, , , , , object.TB(TB_MAKE)
       object.CB(0).Bands.Item(TB_MAKE).Width = object.TB(TB_MAKE).Buttons.Item(1).Width * 7
       
       Load object.CB(1)
       object.CB(1).Bands.Clear
       SnapeToolBar object
       object.CB(1).Orientation = cc3OrientationVertical
       object.CB(1).Visible = True
       object.CB(1).Align = 3
       object.CB(1).Bands.Add 1, , , , , object.TB(TB_SNAPE)
       object.TB(TB_SNAPE).Width = object.TB(TB_SNAPE).ButtonWidth + 10
       object.CB(1).Bands.Item(1).Width = object.TB(TB_SNAPE).Buttons.Item(1).Width
       object.CB(1).Width = object.TB(TB_SNAPE).ButtonWidth + 50
       'Object.CB(1).Bands.Item(1).Height = Object.TB(TB_SNAPE).Buttons.Item(1).Height * 6
End Sub
