Attribute VB_Name = "mmain"
Option Explicit

'窗口
Public frmMain As MDIForm1
'设置窗口
Private Const GWL_STYLE = (-16)
Public Const WS_MAXIMIZEBOX = &H10000
Public Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long

'获取操作系统 API 和类型申明
Private Declare Sub GetSystemInfo Lib "kernel32" (lpSystemInfo As SYSTEM_INFO)
Private Declare Function GetVersionEx Lib "kernel32" Alias "GetVersionExA" (lpVersionInformation As OSVERSIONINFO) As Long
Private Type SYSTEM_INFO
        dwOemID As Long
        dwPageSize As Long
        lpMinimumApplicationAddress As Long
        lpMaximumApplicationAddress As Long
        dwActiveProcessorMask As Long
        dwNumberOrfProcessors As Long
        dwProcessorType As Long
        dwAllocationGranularity As Long
        dwReserved As Long
End Type
Private Type OSVERSIONINFO
        dwOSVersionInfoSize As Long   '操作系统信息结构的长度
        dwMajorVersion As Long        '主版本号
        dwMinorVersion As Long        '次版本号
        dwBuildNumber As Long
        dwPlatformId As Long          '操作系统
        szCSDVersion As String * 128  'Maintenance string for PSS usage;为维护 PSS而建立的字符串
End Type
Private Const VER_PLATFORM_WIN32_NT = 2
Private Const VER_PLATFORM_WIN32_WINDOWS = 1
Private Const VER_PLATFORM_WIN32s = 0
   
Public tySystemInformation As SYSTEM_INFO
Private Type typeMYVERSION
       lMajorVersion As Long  '主版本号
       lMinorVersion  As Long '次版本号
       lExtraInfo As Long     '操作系统
       sOS As String          '操作系统
       sOSVAll    As String   '全称
       End Type
Public tyOSVersionInformation As typeMYVERSION
Public lOSInfo As Long '用于检查版本信息,用于是否测试过

'调试标识
Public Const Run = False

Public Enum Enum_PassStyle     '密码窗口类型
            Enum_PassStyle_Add = 0
            Enum_PassStyle_AddWizard = 1
            Enum_PassStyle_Regedit = 2
            Enum_PassStyle_ModifyKeyList = 3
            Enum_PassStyle_OpenFile = 4
       End Enum

Public Enum Enum_PassLevel '密码级别
            Enum_PassLevel_Null = 0
            Enum_passLevel_User = 1 '用户级，最低
            Enum_PassLevel_Manager = 2 '管理级
            End Enum
            
Public Enum Enum_WindowsStyle
       Windows_Desktop_Enum = 0      '窗口类型为设置桌面
       Windows_ControlPanel_Enum = 1 '.............控制面板
       Windows_Security_Enum = 2     '.............安全
       End Enum

Public Enum Enum_Control '控件枚举型
       Enum_Control_Only_Text = 0 '只有文本控件
       Enum_Control_List = 1 '列表框控件
       Enum_Control_FrameInput = 2 '浏览输入框控件
       Enum_Control_DBGird = 3 '多键值的输入
       End Enum
       
Private Type typeTree '树的结构
        '建立结点所要的参数,用于frmOption.SetTreeNode
        Ralation As String
        Key As String
        Text As String '作为后面的标识
        '控件所要的参数,用于frmOption.Tree_NodeClick
        Control As Enum_Control
        PassLevel As Enum_PassLevel  '结点的安全级别
        KeyType As ENUM_REG_KEY_TYPE '键值的类型
        StartPos As Long '键值勤的起始位置
        EndPos As Long '键盘值勤的结束位置
        End Type
Public tTree() As typeTree

Private Type typeKey
        KeyRoot As Long    '根键
        MainKey As String  '主键
        SubKey As String   '子键
        KeyVal As Variant  '键值
        KeyType As Long    '键类型
        Readme As String   '说明
        ControlText As String '控件中的说明文字
        OperistSystem As Long '此键值勤适用的操作系统
           '共32位,低三位(0～2)分别为:WINDOWS95、WINDOWS98、WINDOWS2000，
           '      其它的保留给以后的操作系统
        PassLevel As Enum_PassLevel  '安全级别
        End Type
Public tKeyVal() As typeKey '键值的数组
'Public tKeyValAdd() As typeKey '用于增加窗口

Public KeyFile As String '存放键值的文件,为此应用程序的系统文件

Private Type typeModifyKey
        KeyRoot As Long    '根键
        MainKey As String  '主键
        SubKey As String   '子键
        KeyVal As Variant  '键值
        KeyType As Long    '键类型
        Readme As String   '说明
        End Type
Public Key() As typeModifyKey '要修改的键值的数组

Private Sub init()
    ReDim Key(0)
    '加查找操作系统
    tyOSVersionInformation = WindowsVersion()
    
    '初始化结构数组
    ReDim tTree(0)
    ReDim tTreeNode(0)
    ReDim tControl(0)
    ReDim tKeyVal(0)
    ReDim tKeyValAdd(0)
    
    '初始化此应用程序的系统文件
    KeyFile = App.Path & "\修改注册表.dat"
    OpenKeyFile   '打开文件
    
End Sub

Sub main()
Dim Style As Long
    init
    Set frmMain = New MDIForm1
    Style = GetWindowLong(frmMain.hwnd, GWL_STYLE)
    Style = Style Xor WS_MAXIMIZEBOX
    SetWindowLong frmMain.hwnd, GWL_STYLE, Style
    frmMain.Show
    
    If Not Run Then
       frmAdd.Show 1
    End If
    '加密码验证
    
End Sub


'得到版本信息
Private Function WindowsVersion() As typeMYVERSION
Dim myOS As OSVERSIONINFO, WinVer As typeMYVERSION
Dim lResult As Long

    myOS.dwOSVersionInfoSize = Len(myOS)    '应该是 148
    
    lResult = GetVersionEx(myOS)
        
    '用相关信息填充用户类型
    WinVer.lMajorVersion = myOS.dwMajorVersion
    WinVer.lMinorVersion = myOS.dwMinorVersion
    '操作系统信息。
        If WinVer.lMajorVersion = 4 Then
            If myOS.dwPlatformId = VER_PLATFORM_WIN32_NT Then
                WinVer.sOS = "Windows NT 版本 : "
            ElseIf myOS.dwPlatformId = VER_PLATFORM_WIN32_WINDOWS Then
                WinVer.sOS = "Windows 95 版本 : "
            End If
        Else
            WinVer.sOS = "Windows 版本 : "
        End If
        WinVer.sOSVAll = WinVer.sOS & WinVer.lMajorVersion & "." & WinVer.lMinorVersion
    WindowsVersion = WinVer

End Function



'密码
Public Function PassWord(sStyle As Enum_PassStyle) As Boolean
'如果密码输入正确,则返回True,否则,返回False
If Run Then
       Select Case sStyle
              Case Enum_PassStyle_Regedit
                   '用户设有密码时才用
                   '测试条件为注册表编辑器是否被关闭
                   
              Case Enum_PassStyle_ModifyKeyList
                   '仅为程序员用
                   
              Case Enum_PassStyle_OpenFile
              
       End Select
Else '调试
   PassWord = True
End If
End Function

Public Function AddToSameKey(KeyRoot As Long, _
     SubKey As String, MainKey As String, _
     KeyVal As Variant, Optional KeyType As ENUM_REG_KEY_TYPE = REG_BOOL, _
     Optional Readme As String = vbNullString)
'参数:
'KeyRoot 根键值
'SubKey  子健名
'MainKey 主键名
'KeyVal  键值
'KeyType 键值类型,缺省值为REG_BOOL=-1,表示这个值为Boolean值
'Readme  说明
Dim i As Long, M As Long, vall As String
          M = UBound(Key)
          For i = 1 To M
              '修改的键已在Key内
              If SubKey = Key(i).SubKey Then
                 If MainKey = Key(i).MainKey And _
                    KeyRoot = Key(i).KeyRoot Then
                    If KeyType = REG_BOOL Then
                       If CBool(KeyVal) Then
                          Key(i).KeyVal = Key(i).KeyVal Or _
                          2 ^ (Asc(UCase(Left(Right$ _
                          (Readme, 3), 1))) - Asc(UCase("a")))
                          '当为Boolean时,真值为1
                       Else
                          Key(i).KeyVal = Key(i).KeyVal Xor _
                          2 ^ (Asc(UCase(Left(Right$ _
                          (Readme, 3), 1))) - Asc(UCase("a")))
                       End If
                    Else
                       Key(i).KeyVal = KeyVal
                    End If
                    Exit Function
                 End If
              End If
          Next i
          '修改的键不在Key内
          ReDim Preserve Key(M + 1)
          With Key(M + 1)
              .KeyRoot = KeyRoot
              .MainKey = MainKey
              .SubKey = SubKey
              vall = GetKeyValue(HKEY_CURRENT_USER, "Software\Microsoft\Windows\CurrentVersion\Policies\Explorer", "NoDrives")
              If KeyType = REG_BOOL Then
                 If CBool(KeyVal) Then
                    Key(i).KeyVal = CLng(vall) Or _
                     2 ^ (Asc(UCase(Left(Right$ _
                    (Readme, 3), 1))) - Asc(UCase("a")))
                    '当为Boolean时,真值为1
                 Else
                    Key(i).KeyVal = CLng(vall) And ( _
                    Not (CLng(0)) Xor 2 ^ _
                    (Asc(UCase(Left(Right$ _
                    (Readme, 3), 1))) - Asc(UCase("a"))))
                 End If
               Else
                 Key(i).KeyVal = KeyVal
               End If
              If KeyType = REG_BOOL Then
                 .KeyType = REG_DWORD
              Else
                 .KeyType = KeyType
              End If
              .Readme = Readme
          End With
End Function

'把修改过的值加入到修改组Key中
Public Function AddToKey(KeyRoot As Long, _
     SubKey As String, MainKey As String, _
     KeyVal As Variant, Optional KeyType As ENUM_REG_KEY_TYPE = REG_BOOL, _
     Optional Readme As String = vbNullString)
'参数:
'KeyRoot 根键值
'SubKey  子健名
'MainKey 主键名
'KeyVal  键值
'KeyType 键值类型,缺省值为REG_BOOL=-1,表示这个值为Boolean值
'Readme  说明
Dim i As Long, M As Long
          M = UBound(Key)
          For i = 1 To M
              '修改的键已在Key内
              If SubKey = Key(i).SubKey Then
                 If MainKey = Key(i).MainKey And _
                    KeyRoot = Key(i).KeyRoot Then
                    If KeyType = REG_BOOL Then
                       If CBool(KeyVal) Then
                          Key(i).KeyVal = 1 '当为Boolean时,真值为1
                       Else
                          Key(i).KeyVal = KeyVal
                       End If
                    Else
                       Key(i).KeyVal = KeyVal
                    End If
                    Exit Function
                 End If
              End If
          Next i
          '修改的键不在Key内
          ReDim Preserve Key(M + 1)
          With Key(M + 1)
              .KeyRoot = KeyRoot
              .MainKey = MainKey
              .SubKey = SubKey
              If KeyType = REG_BOOL Then
                 If CBool(KeyVal) Then
                    Key(i).KeyVal = 1 '当为Boolean时,真值为1
                 Else
                    Key(i).KeyVal = KeyVal
                 End If
              Else
                    Key(i).KeyVal = KeyVal
              End If
              If KeyType = REG_BOOL Then
                 .KeyType = REG_DWORD
              Else
                 .KeyType = KeyType
              End If
              .Readme = Readme
          End With
End Function

'修改注册表
Public Function ModifyKey()
If Run Then On Error Resume Next
Dim i As Long, sVal As String
      For i = 1 To UBound(Key)
          With Key(i)
               If .KeyType = REG_SZ Then
                  sVal = .KeyVal
                  szUpdateKey .KeyRoot, .MainKey, .SubKey, sVal
               ElseIf .KeyType = REG_DWORD Then
                  dwUpdateKey .KeyRoot, .MainKey, .SubKey, CLng(.KeyVal)
               End If
          End With
      Next i
End Function

'文件输入输出下两个函数为打开和保存修改的键值
Public Function OpenFile() As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, FileName As String, ss As String
Dim i As Long, n As Long
    If PassWord(Enum_PassStyle_OpenFile) Then
       With frmMain.CommD
            .FileName = ""
            .Filter = "*.da0|*.da0|*.*|*.*"
            .ShowOpen
            If .FileName = "" Then Exit Function
            FileName = .FileName
       End With
       Num = FreeFile
       Open FileName For Input As #Num
            Line Input #Num, ss
            If ss <> "修改注册表,设计者:康林" Then
               MsgBox "文件类型不对", , App.FileDescription ' "修改注册表"
               OpenFile = False
               Exit Function
            End If
            Input #Num, ss '版本号
            Input #Num, n
            ReDim Key(0)
            For i = 1 To n
                ReDim Preserve Key(i)
                With Key(i)
                     Input #Num, .KeyRoot
                     Input #Num, .MainKey
                     Input #Num, .SubKey
                     Input #Num, .KeyType
                     Input #Num, .KeyVal
                     Input #Num, .Readme
                End With
            Next i
       Close #Num
       OpenFile = True
    Else
       OpenFile = False
    End If
End Function

Public Sub SaveFile()
If Run Then On Error Resume Next
Dim Num As Integer, FileName As String
Dim i As Long, n As Long
       With frmMain.CommD
            .FileName = ""
            .Filter = "*.da0|*.da0|*.*|*.*"
            .ShowSave
            If .FileName = "" Then Exit Sub
            FileName = .FileName
       End With
       Num = FreeFile
       Open FileName For Output As #Num
            Print #Num, "修改注册表,设计者:康林"
            Print #Num, App.Major & "." & App.Minor '版本号
            n = UBound(Key)
            Print #Num, n
            For i = 1 To n
                With Key(i)
                     Print #Num, .KeyRoot
                     Print #Num, .MainKey
                     Print #Num, .SubKey
                     Print #Num, .KeyType
                     Print #Num, .KeyVal
                     Print #Num, .Readme
                End With
            Next i
       Close #Num
End Sub

'下两个为系统的结构
Public Function OpenKeyFile(Optional boolFile As Boolean = False, Optional FileName As String = vbNullString) As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, ss As String, i As Long, n As Long
       Num = FreeFile
       Open KeyFile For Input As #Num
            Line Input #Num, ss
            If ss <> "修改注册表,设计者:康林" Then
               MsgBox "文件类型不对", , App.FileDescription ' "修改注册表"
               OpenKeyFile = False
               Exit Function
            End If
            Input #Num, ss '版本号
            Input #Num, ss
            
            Line Input #Num, ss '保留
            Line Input #Num, ss '保留
            Line Input #Num, ss '保留
            Line Input #Num, ss '保留
            Line Input #Num, ss '保留
            
            Input #Num, n
            ReDim tTree(n)
            For i = 1 To n
                With tTree(i)
                     Input #Num, .Ralation
                     Input #Num, .Key
                     Input #Num, .Text
                     Input #Num, .Control
                     Input #Num, .PassLevel
                     Input #Num, .KeyType
                     Input #Num, .StartPos
                     Input #Num, .EndPos
                End With
            Next i
            
            Input #Num, n
            ReDim tKeyVal(n)
            For i = 1 To n
                With tKeyVal(i)
                     Input #Num, .ControlText
                     Input #Num, .KeyRoot
                     Input #Num, .KeyType
                     Input #Num, .KeyVal
                     Input #Num, .MainKey
                     Input #Num, .OperistSystem
                     Input #Num, .PassLevel
                     Input #Num, .Readme
                     Input #Num, .SubKey
                End With
            Next i
       Close #Num
End Function

Public Sub SaveKeyFile(Optional boolFile As Boolean = False, Optional FileName As String = vbNullString)
If Run Then On Error Resume Next
Dim Num As Integer, i As Long, n As Long
       Num = FreeFile
       Open KeyFile For Output As #Num
            Print #Num, "修改注册表,设计者:康林"
            Print #Num, App.Major '主版本号
            Print #Num, App.Minor '次版本号
            
            Print #Num, "" '保留
            Print #Num, ""
            Print #Num, ""
            Print #Num, ""
            Print #Num, ""
            
            n = UBound(tTree)
            Print #Num, n
            For i = 1 To n
                With tTree(i)
                     Print #Num, .Ralation
                     Print #Num, .Key
                     Print #Num, .Text
                     Print #Num, .Control
                     Print #Num, .PassLevel
                     Print #Num, .KeyType
                     Print #Num, .StartPos
                     Print #Num, .EndPos
                End With
            Next i
            
            n = UBound(tKeyVal)
            Print #Num, n
            For i = 1 To n
                With tKeyVal(i)
                     Print #Num, .ControlText
                     Print #Num, .KeyRoot
                     Print #Num, .KeyType
                     Print #Num, .KeyVal
                     Print #Num, .MainKey
                     Print #Num, .OperistSystem
                     Print #Num, .PassLevel
                     Print #Num, .Readme
                     Print #Num, .SubKey
                End With
            Next i
       Close #Num
End Sub


