Attribute VB_Name = "Face"
'��ģ��Ϊ���溯��
'����:����

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
'�õ���SetMenuItemBitmaps������Ҫ��Bitmap�Ĵ�С

'Const ON_ERROR_RESUME_MEXT = 1

Public Sub PaperInit(object As Object)  'ͼֽ��ʼ��
'Object=�Ӵ����е�cad�ؼ�
'If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
'End If
       
       '��ʼ��ͼֽ
       '���������ļ�ʱ,ѡȡͼֽ
       selectpaper.Show 1  '��ѡ�õ�ͼֽ���������ļ���
       '�������ļ��еõ�ͼֽ�Ĵ�С,������ͼֽ�Ĵ�С
       PaperBigLittle object
       
       
       'ͼֽ�ṹ�ĳ�ʼ��
       PaperTypeInitial object
       
       '��ʼ��ͼ��
       DeskInitial object
       
End Sub

'�������ļ��еõ�ͼֽ�Ĵ�С,������ͼֽ�Ĵ�С
Private Sub PaperBigLittle(object As Object)
'Object=�Ӵ����е�cad�ؼ�
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

'ͼֽ���ͽṹ�ĳ�ʼ��
Private Sub PaperTypeInitial(object As Object)
'Object=�Ӵ����е�cad�ؼ�
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Dim i, ss As String * 20, s As String
       '��λ
       i = GetPrivateProfileString("ѡ��", "��λ", "mm", ss, 20, Inifile)
       If i <> 0 Then
          s = left$(ss, i)
       Else
          s = "mm"
       End If
       object.Container.Container.InputPaperUnits (s)
       '������
       i = GetPrivateProfileString("ѡ��", "������", "1", ss, 20, Inifile)
       If i <> 0 Then
          ss = left$(ss, i)
       Else
          ss = "1"
       End If
       object.Container.Container.InputPaperRatio (Val(ss))
       i = GetPrivateProfileString("ѡ��", "������1", "1", ss, 20, Inifile)
       If i <> 0 Then
          ss = left$(ss, i)
       Else
          ss = "1"
       End If
       object.Container.Container.InputPaperRatio1 (Val(ss))
       i = GetPrivateProfileString("ѡ��", "������2", "1", ss, 20, Inifile)
       If i <> 0 Then
          ss = left$(ss, i)
       Else
          ss = "1"
       End If
       object.Container.Container.InputPaperRatio2 (Val(ss))
       'ͼֽ��ɫ,ֻ�ܷ������,Ĭ��ֵ���ַ�,��ֵ��ͽ���
       i = GetPrivateProfileString("ѡ��", "ͼֽ��ɫ", "vbWhite", ss, 20, Inifile)
       If i <> 0 Then
          object.BackColor = left$(ss, i)
       End If
End Sub

'��ʼ��ͼ��
Private Sub DeskInitial(object As Object)
'Object=�Ӵ����е�cad�ؼ�
#If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
#End If

Dim i, ss As String * 20
        
        'ͼ�����ɫ
        '�������ļ��еõ�ͼ�����ɫ,ֻ�ܷ������,Ĭ��ֵ���ַ�,��ֵ��ͽ���
        i = GetPrivateProfileString("ѡ��", "ͼ����ɫ", "vbBlue", ss, 20, Inifile)
        If i <> 0 Then
           object.Container.BackColor = left$(ss, i)
        End If
End Sub


'Һ����
Public Sub Scroll(object As Object, HScrol As Single, Vscrol As Single)
If ON_ERROR_RESUME_NEXT Then
    On Error Resume Next
End If
'Object����ĵ����Ӵ���
'��ֱҺ����
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
'ˮƽҺ����
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

'���任
Public Sub MouseChange_OK(i As Integer, object As Object)
With object '���ݵ����Ӵ���
     Select Case i
            Case 0, 4 '�����任,���Ͻ����½�
                 .cad.MousePointer = vbSizeNWSE
            Case 1, 5 '�����任,���е�,���е�
                 .cad.MousePointer = vbSizeNS
            Case 2, 6 '�����任,���Ͻ�,���½�
                 .cad.MousePointer = vbSizeNESW
            Case 3, 7 '�����任,���е�,���е�
                 .cad.MousePointer = vbSizeWE
            Case 8 '�ƶ�
                .cad.MousePointer = vbSizeAll
     End Select
Select Case .Mousestyle
       Case "��ʮ�ֹ��"
            .Line2.Visible = False
            .Line1.Visible = False
       Case "Բ�ι��"
             .Smouse.Visible = False
End Select
End With
End Sub

'ȡ���任���
Public Sub MouseChange_Undo(object As Object)
With object '���ݵ����Ӵ���
     Select Case .Mousestyle
            Case "���ι��"
                 .cad.MousePointer = vbArrow
            Case "Сʮ�ֹ��"
                 .cad.MousePointer = vbCrosshair
            Case "��ʮ�ֹ��"
                 .cad.MousePointer = vbCrosshair
                 .Line1.Visible = True
                 .Line2.Visible = True
            Case "Բ�ι��"
                  .cad.MousePointer = vbCrosshair
                  .Smouse.Visible = True
     End Select
End With
End Sub

'��ע�������ֵ�λ��,�޸Ĵ˴�ʱ,ע��ͬʱ�޸���ת���ֵ���Ӧ�ĵط�
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

'ʹ�༭���߲���Ӧ�¼�
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

'ʹ�༭������Ӧ�¼�
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

'���˵�����ͼƬ
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
                  Case "mnuFileNew" '"���ļ�  (&N) Ctrl+N  "
                       SetMenu object, i, "new"
                  Case "mnuFileOpen" ' "���ļ�(&O)... Ctrl+O     "
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
                  Case "mnuMakeLine�߶�"
                       SetMenu object, i, "line"
                  Case "mnuMake������"
                       SetMenu object, i, "������"
                  Case "mnuMaketext"
                       SetMenu object, i, "����"
                  Case "mnuMakeDimˮƽ��ע"
                       SetMenu object, i, "ˮƽ��ע"
                  Case "mnuMakeDim����ˮƽ��ע"
                       SetMenu object, i, "����ˮƽ��ע"
                  Case "mnuMakeDim��ֱ��ע"
                       SetMenu object, i, "��ֱ��ע"
                  Case "mnuMakeDim������ֱ��ע"
                       SetMenu object, i, "������ֱ��ע"
                  Case "mnuMake����"
                       SetMenu object, i, "rectangle"
                  Case "mnuMakeԲ"
                       SetMenu object, i, "mcircle"
                  Case "mnuMake��Բ"
                       SetMenu object, i, "ellipse"
                  Case "mnuMakeԲ��"
                       SetMenu object, i, "arc"
                  Case "mnuMake������"
                        SetMenu object, i, "m������"
                  Case "mnuMake��������"
                       SetMenu object, i, "m��������"
                  Case "mnuMake������"
                       SetMenu object, i, "m������"
                  Case "mnuMake��������"
                      SetMenu object, i, "m��������"
                  Case "mnuMake����"
                      SetMenu object, i, "m����"
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

'���˵�����ͼƬ
Private Sub SetMenu(object As Object, Postion As Long, hBitmap As String)
Dim hMenu As Long
    hMenu = GetMenu(object.hwnd)
    Call SetMenuItemBitmaps(hMenu, Postion, 0, GetBitMapHandle(object, fMainForm.imlToolbarIcons.ListImages.Item(hBitmap).PicTure), GetBitMapHandle(object, fMainForm.imlToolbarIcons.ListImages.Item(hBitmap).PicTure))
End Sub

'�õ�ͼƬ�ľ��
Private Function GetBitMapHandle(object As Object, PicTure As StdPicture) As Long
Dim dstWidth As Long, dstHeight As Long
Dim srcWidth As Long, srcHeight As Long
Dim x As Long, y As Long
Dim Pic As New StdPicture
Dim hDC1 As Long, i As Long
Dim hBitmap As Long
Dim hDstDc As Long
Set Pic = PicTure '����ͼ��
hDC1 = CreateCompatibleDC(0) '����MEMORY DC
i = selectobject(hDC1, Pic.Handle) '�ڸ�MEMORY DC �Ϸ���BITMAPͼ
i = GetMenuCheckMarkDimensions '�õ�SETMENUITEMBITMAPS��Ҫ��BITMAP��С
'����һ��dstWidth*dstHeight ��С��ͼƬBITMAP
dstWidth = i Mod 2 ^ 16 '��λ��ͼƬ�Ŀ�
dstHeight = i / 2 ^ 16  '��λ��ͼƬ�ĸ�
hBitmap = CreateCompatibleBitmap(GetDC(object.hwnd), dstWidth, dstHeight)
hDstDc = CreateCompatibleDC(GetDC(object.hwnd))
'����MEMORY DC
'���.........��ͼ���Ĵ�С=��BITMAP�Ĵ�С
'���ڸ�MEMORY DC�Ļ�ͼ�Ǹ�BITMAPͼ�ϻ�ͼ
selectobject hDstDc, hBitmap
srcHeight = Screen.ActiveForm.ScaleY(Pic.Height, vbHimetric, vbPixels)
srcWidth = Screen.ActiveForm.ScaleX(Pic.Width, vbHimetric, vbPixels)
Call StretchBlt(hDstDc, 0, 0, dstWidth, dstHeight, hDC1, 0, 0, srcWidth, srcHeight, SRCCOPY)
GetBitMapHandle = hBitmap
Call DeleteDC(hDC1)
Call DeleteDC(hDstDc)
End Function

'ʹ��ť�ָ�
Public Sub UnPressButton(ToolBar As ToolBar)
Dim i
    For i = 1 To ToolBar.Buttons.Count
        ToolBar.Buttons.Item(i).Value = tbrUnpressed
    Next i
    ToolBar.Refresh  '���¹�����
End Sub

Public Sub FileToolBar(object As Object) '�ļ�������
       With object.TB(TB_FILE).Buttons
            .Clear
            .Add 1, "new", , , "new"
            .Item("new").ToolTipText = "���ļ�"
            .Add 2, "open", , , "open"
            .Item("open").ToolTipText = "���ļ�"
            .Add 3, "save", , , "save"
            .Item("save").ToolTipText = "�����ļ�"
            .Add 4, "print", , , "print"
            .Item("print").ToolTipText = "��ӡ�ļ�"
       End With
End Sub

Public Sub EditToolBar(object As Object) '�༭������
       Load object.TB(TB_EDIT)
       With object.TB(TB_EDIT).Buttons
            .Clear
            .Add 1, "cut", , , "cut"
            With .Item("cut")
                 .ToolTipText = "����"
            End With
            .Add 2, "copy", , , "copy"
            With .Item("copy")
                 .ToolTipText = "����"
            End With
            .Add 3, "paste", , , "paste"
            With .Item("paste")
                 .ToolTipText = "ճ��"
            End With
            .Add 4, "delete", , , "delete"
            With .Item("delete")
                 .ToolTipText = "ɾ��"
            End With
            .Add 5, "undo", , , "undo"
            With .Item("undo")
                 .ToolTipText = "ȡ��"
            End With
            .Add , , , tbrSeparator '�ո��
            .Add , "redo", , , "redo"
            .Item("redo").ToolTipText = "�ػ�"
            .Add , "select", , , "select"
            .Item("select").ToolTipText = "ѡȡ"
            .Add , "ccopy", , tbrDropdown, "ccopy"
                 .Item("ccopy").ToolTipText = "����"
            With .Item("ccopy").ButtonMenus
                 .Add , "ccopy", "����"
                 .Add , "round", "��ת"
                 .Add , "mirror", "����"
            End With
            .Add , "break", , tbrDropdown, "break"
            .Item("break").ToolTipText = "�ж�"
            With .Item("break").ButtonMenus
                 .Add , "break", "�ж�"
                 .Add , "chamfer", "�н�"
                 .Add , "text", "�޸�����"
            End With
       End With
End Sub

Public Sub MakeToolBar(object As Object) '��ͼ������
       Load object.TB(TB_MAKE)
       With object.TB(TB_MAKE).Buttons
            .Clear
            .Add 1, "line", , tbrDropdown, "line"
            .Item("line").ToolTipText = "ֱ��"
            With .Item("line").ButtonMenus
                  .Clear
                  .Add , "line", "ֱ��"
                  .Add , "��ֱ�߶�", "��ֱ�߶�"
                  .Add , "������", "������"
                  .Add , "tan", "���㵽Բ������"
                  .Add , "twolinemiss", "ʹ��ֱ���ཻ"
                  .Add , "line style", "����"
            End With
            .Add 2, "������", , tbrDropdown, "������"
            .Item("������").ToolTipText = "������"
            With .Item("������").ButtonMenus
                 .Clear
                 .Add 1, "������", "������"
                 .Add 2, "��������", "��������"
                 .Add 3, "rectangle", "����"
                 .Add 4, "������", "������"
                 .Add 5, "��������", "��������"
            End With
            .Add 3, "circle", , tbrDropdown, "circle"
            .Item("circle").ToolTipText = "Բ"
            With .Item("circle").ButtonMenus
                 .Add 1, "circle", "Բ"
                 .Add 2, "arc", "Բ��"
                 .Add 3, "����", "����"
                 .Add 4, "ellipse", "��Բ"
            End With
            .Add 4, "ˮƽ��ע", , tbrDropdown, "ˮƽ��ע"
            .Item("ˮƽ��ע").ToolTipText = "ˮƽ��ע"
            With .Item("ˮƽ��ע").ButtonMenus
                 .Add 1, "ˮƽ��ע", "ˮƽ��ע"
                 .Add 2, "����ˮƽ��ע", "����ˮƽ��ע"
                 .Add 3, "��ֱ��ע", "��ֱ��ע"
                 .Add 4, "������ֱ��ע", "������ֱ��ע"
            End With
            .Add 5, "����", , , "����"
            .Item("����").ToolTipText = "����"
       End With
End Sub

Private Sub SnapeToolBar(object As Object) '��׽������
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
             .Item("snapeend").ToolTipText = "��׽ֱ�߻�Բ���Ķ˵�"
             .Add , "snapemid", , tbrCheck, "snapemid"
             .Item("snapemid").ToolTipText = "��׽ֱ�߻�Բ�����е�"
             .Add , "snapecenter", , tbrCheck, "snapecenter"
             .Item("snapecenter").ToolTipText = "��׽Բ����Բ������"
             .Add , "snapemiss", , tbrCheck, "snapemiss"
             .Item("snapemiss").ToolTipText = "��׽����"
             .Add , "snapeexit", , , "exit"
             .Item("snapeexit").ToolTipText = "�˳���׽"
        End With
        object.TB(TB_SNAPE).Wrappable = True
        object.TB(TB_SNAPE).Align = 3
        object.TB(TB_SNAPE).Align = 0
End Sub

'��ʼ��������
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
