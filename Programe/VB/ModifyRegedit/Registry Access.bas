Attribute VB_Name = "RegKeys"
' 这个模块用于读和写注册表关键字。
' 不同于VB 的内部注册表访问方法，它可以
' 通过字符串的值来读和写任何注册表关键字。


Option Explicit
'---------------------------------------------------------------
'-注册表 API 声明...
'---------------------------------------------------------------
'关闭
Private Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long
'建立
Private Declare Function RegCreateKeyEx Lib "advapi32" Alias _
"RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String _
, ByVal Reserved As Long, ByVal lpClass As String, _
ByVal dwOptions As Long, ByVal samDesired As Long, _
ByRef lpSecurityAttributes As SECURITY_ATTRIBUTES, _
ByRef phkResult As Long, ByRef lpdwDisposition As Long) As Long

'-------------------------------------------------------------
'.hkey为主键值,为下面五个值:
'     HKEY_CLASSES_ROOT = &H80000000
'     HKEY_CURRENT_USER = &H80000001
'     HKEY_LOCAL_MACHINE = &H80000002
'     HKEY_USERS = &H80000003
'     HKEY_PERFORMANCE_DATA = &H80000004
'-------------------------------------------
'     HKEY_DYN_DATA   为WIN95操作系统
'     HKEY_PERFORMANCE_PATA  为WINNT操作系统
'-------------------------------------------------------------
'.lpsubkey为一个指向以零结尾的字符串的指针,其中包含将要创建或
'         打开的子键盘的名称,不能经(\)开头,可为NULL
'-------------------------------------------------------------
'.Reserved 保留,设为零
'-------------------------------------------------------------
'lpClass  指向包含键类型的字符串,如果已存在,忽略该参数,为以下值:
'Const REG_SZ = 1                         ' Unicode空终结字符串
'Const REG_EXPAND_SZ = 2                  ' Unicode空终结字符串
'Const REG_DWORD = 4                      ' 32-bit 数字
'-------------------------------------------------------------
'.dwOptions为新创建的键设置一定的属性,可取以下值:
' REG_OPTION_NON_VOLATILE 新创建的键为一个非短暂性的键盘
'                       （数据保存在文件中）
'REG_OPTION_VOLATILE WIN95忽略该参数
'                          （数据保存在内存中）
'REG_OPTION_BACKUP_RESTORE 仅在WINNT中支持,可提供优先级支持
'-------------------------------------------------------------
'.samDesired 用来设置对键访问的权限,可取下列值:
' KEY_CREATE_LINK 准许生成符号键
' KEY_CREATE_SUB_KEY 准许生成子键
' KEY_ENUMERATE_SUB_KEYS 准许生成枚举子键
' KEY_EXECUTE 准许进行读写操作
' KEY_QUERY_VALUE 准许查询子键
' KEY_ALL_ACCESS 提供完全访问,是上面值勤的组合
'-----------------------------------------------
' KEY_READ 是下面值勤的组合,是下面值的组合
' KEY_QUERY_VALUE
' KEY_ENVMERATE_KEYS
' KEY_NOTIFY
' KEY_SET_VALUE 准许设置子键的数值勤
'-----------------------------------------------
' KEY_WRITE 是下面值勤的组合:
' KEY_SET_VALUE
' KEY_CREAT_SUB_KEY
'-------------------------------------------------------------
'.lpSecurityAttributes为一个指向SECURITY_ATTRIBVTES结构的指针
'确定返回值的句柄是否被子处理过程继承,在WINNT中,该参数可为新创
'建的键安全的描述
'-------------------------------------------------------------
'.phkResult为一个指向新建或打开键的句柄指针
'-------------------------------------------------------------
'.lpdwDisposition指明键是被创建,还是被打开的,可以是:
' REG_CREAT_NEW_KEY 键先前不存在,现在被创建
' REG_OPENED_EXISTING_KEY 键先前已存在,现在被打开
'-------------------------------------------------------------
'返回值:
'如果调用成功,则返回ERROR_SUCCESS,否则,返回值在(Visual C++)中
'为文件WINERROR.H中定义的一个非零的错误代码,可通过设置
'ERR_MAT_MESSAGE_FROM_SYSTEM标识FormatMessage函数来获取一个对
'错误的总体描述;在(Visual Basic)中用Err.Description来获取一个
'对错误的总体描述
'---------------------------------------------------------------
'打开
Private Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" _
(ByVal hKey As Long, ByVal lpSubKey As String, _
ByVal ulOptions As Long, ByVal samDesired As Long, _
ByRef phkResult As Long) As Long
'查询
Private Declare Function RegQueryValueEx Lib "advapi32" _
Alias "RegQueryValueExA" (ByVal hKey As Long, _
ByVal lpValueName As String, ByVal lpReserved As Long, _
ByRef lpType As Long, ByVal lpData As String, _
ByRef lpcbData As Long) As Long
'.lpType为一个指向数据类型的指针
' REG_SZ = 1      一个以零结尾的字符串,根据函数使用
'            的字符集类型的不同而设置为Unicode空终结字符串,
'            或ANSI字符串
' REG_EXPAND_SZ = 2               Unicode空终结字符串
'                         一个包含未扩展环境变量的字符串
' REG_LINK     一个UNICODE类型的链接
' REG_DWORD = 4                   32-bit 数字
' REG_BINARY                      二进制
' REG_DWORD_LITTLE_ENDIAN               LITTLE_ENDIAN格式的数
'                                       据,例:0x12345678
'                                     以(0x79 0x56 0x34 0x12)
'                                     方式保存
' REG_DWORD_BIN_ENDIAN                 BIG_ENDIAN格式的数据，
'                                    例:0x12345678以
'                                     (0x12 0x34 0x56 0x78)
'                                     方式保存
'-------------------------------------------------------------
'.lpValueName关键字变量名
'-------------------------------------------------------------
'.lpData 返回的数据,是一个以零结尾的字符串
' 用Left$(lpDate, InStr(lpDate, Chr(0)) - 1)取得精确值
'-------------------------------------------------------------
'.lpcbData 将要取得数据的最大长度
'-------------------------------------------------------------
'设置
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" _
(ByVal hKey As Long, ByVal lpValueName As String, _
ByVal Reserved As Long, ByVal dwType As Long, _
lpData As Any, ByVal cbData As Long) As Long
' Note that if you declare the lpData parameter
'as String,you must pass it By Value.

'- 注册表 Api 常数...
'---------------------------------------------------------------
' Reg Data Types...,键类型...
Public Enum REG_KEY_TYPE_ENUM
       REG_SZ = 1       ' Unicode空终结字符串
       REG_BINARY = 3    '二进制值
       REG_DWORD = 4   ' 32-bit 数字
       REG_EXPAND_SZ = 2   'Unicode空终结字符串
       End Enum
'.lpType为一个指向数据类型的指针
' REG_SZ = 1      一个以零结尾的字符串,根据函数使用
'            的字符集类型的不同而设置为Unicode空终结字符串,
'            或ANSI字符串
' REG_EXPAND_SZ = 2               Unicode空终结字符串
'                         一个包含未扩展环境变量的字符串
' REG_LINK     一个UNICODE类型的链接
' REG_DWORD = 4                   32-bit 数字
' REG_BINARY                      二进制
' REG_DWORD_LITTLE_ENDIAN               LITTLE_ENDIAN格式的数
'                                       据,例:0x12345678
'                                     以(0x79 0x56 0x34 0x12)
'                                     方式保存
' REG_DWORD_BIN_ENDIAN                 BIG_ENDIAN格式的数据，
'                                    例:0x12345678以
'                                     (0x12 0x34 0x56 0x78)
'                                     方式保存


' 注册表创建类型值...
Const REG_OPTION_NON_VOLATILE = 0       ' 当系统重新启动时，关键字被保留

' 注册表关键字安全选项...
Const READ_CONTROL = &H20000
Const KEY_QUERY_VALUE = &H1
Const KEY_SET_VALUE = &H2
Const KEY_CREATE_SUB_KEY = &H4
Const KEY_ENUMERATE_SUB_KEYS = &H8
Const KEY_NOTIFY = &H10
Const KEY_CREATE_LINK = &H20
Const KEY_READ = KEY_QUERY_VALUE + KEY_ENUMERATE_SUB_KEYS + KEY_NOTIFY + READ_CONTROL
Const KEY_WRITE = KEY_SET_VALUE + KEY_CREATE_SUB_KEY + READ_CONTROL
Const KEY_EXECUTE = KEY_READ
Const KEY_ALL_ACCESS = KEY_QUERY_VALUE + KEY_SET_VALUE + _
                       KEY_CREATE_SUB_KEY + KEY_ENUMERATE_SUB_KEYS + _
                       KEY_NOTIFY + KEY_CREATE_LINK + READ_CONTROL
                     
' 注册表关键字根类型...
Public Const HKEY_CLASSES_ROOT = &H80000000
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_LOCAL_MACHINE = &H80000002
Public Const HKEY_USERS = &H80000003
Public Const HKEY_PERFORMANCE_DATA = &H80000004

' 返回值...
Const ERROR_NONE = 0
Const ERROR_BADKEY = 2
Const ERROR_ACCESS_DENIED = 8
Const ERROR_SUCCESS = 0

'---------------------------------------------------------------
'- 注册表安全属性类型...
'---------------------------------------------------------------
Private Type SECURITY_ATTRIBUTES
    nLength As Long    '长度
    lpSecurityDescriptor As Long '安全属性描述
    bInheritHandle As Boolean
End Type

'-------------------------------------------------------------------------------------------------
'sample usage - Debug.Print UpdateKey(HKEY_CLASSES_ROOT, "keyname", "newvalue")
'-------------------------------------------------------------------------------------------------
'升级注册表
'-------------------------------------------------------------------------------------------------
Public Function UpdateKey(ByVal KeyRoot As Long, _
ByVal KeyName As String, ByVal SubKeyName As String, _
SubKeyValue As Variant, SubKeyType As Long) As Boolean
'参数:
'KeyRoot:为注册表根键值
'KeyName:关键字名
'SubKeyName:子关键字名
'SubKeyType:子关键字的数据类型
'SubKeyValue:关键字值
    Dim rc As Long                     ' 返回代码
    Dim hKey As Long                   ' 处理一个注册表关键字
    Dim hDepth As Long                 '
    Dim lpAttr As SECURITY_ATTRIBUTES  ' 注册表安全类型
    Dim DataLong As Long               '数据的长度
    Dim sSubKeyValue As String         '字符串型参数
    
    lpAttr.nLength = 50                ' 设置安全属性为缺省值...
    lpAttr.lpSecurityDescriptor = 0    ' ...
    lpAttr.bInheritHandle = True       ' ...

    '------------------------------------------------------------
    '- 创建/打开注册表关键字...
    '------------------------------------------------------------
    'rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, REG_SZ, _
                        REG_OPTION_NON_VOLATILE, _
                        KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)
                        ' 创建/打开//KeyRoot//KeyName
    rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, SubKeyType, _
                        REG_OPTION_NON_VOLATILE, _
                        KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)
                        ' 创建/打开//KeyRoot//KeyName
    
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError
                                       ' 错误处理...
    
    '------------------------------------------------------------
    '- 创建/修改关键字值...
    '------------------------------------------------------------
    If (SubKeyValue = "") Then SubKeyValue = " "
          ' 要让RegSetValueEx() 工作需要输入一个空格...
    
    ' 创建/修改关键字值
    'rc = RegSetValueEx(hKey, SubKeyName, _
                       0, REG_SZ, _
                       SubKeyValue, _
                       LenB(StrConv(SubKeyValue, _
                                    vbFromUnicode)))
    Select Case SubKeyType
           Case REG_KEY_TYPE_ENUM.REG_DWORD
                rc = RegSetValueEx(hKey, SubKeyName, _
                       0, SubKeyType, _
                       CLng(SubKeyValue), 4)
           Case REG_KEY_TYPE_ENUM.REG_SZ, REG_KEY_TYPE_ENUM.REG_BINARY
                sSubKeyValue = SubKeyValue
                rc = RegSetValueEx(hKey, SubKeyName, _
                       0, SubKeyType, _
                       sSubKeyValue, _
                       LenB(StrConv(sSubKeyValue, _
                                    vbFromUnicode)))
    End Select
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError
                                       ' 错误处理
    '------------------------------------------------------------
    '- 关闭注册表关键字...
    '------------------------------------------------------------
    rc = RegCloseKey(hKey)             ' 关闭关键字
    
    UpdateKey = True                   ' 返回成功
    Exit Function                      ' 退出
CreateKeyError:
    UpdateKey = False                  ' 设置错误返回代码
    rc = RegCloseKey(hKey)             ' 试图关闭关键字
End Function

'-------------------------------------------------------------------------------------------------
'sample usage - Debug.Print GetKeyValue(HKEY_CLASSES_ROOT, "COMCTL.ListviewCtrl.1\CLSID", "")
'-------------------------------------------------------------------------------------------------
'得到注册表的值
'-------------------------------------------------------------------------------------------------
Public Function GetKeyValue(KeyRoot As Long, KeyName As String, SubKeyRef As String, Optional bFlag As Boolean = False) As String
'参数:
'KeyRoot:为注册表根键值
'KeyName:关键字名
'SubKeyRef:lpValueName,关健字变量的名

    Dim i As Long                 ' 循环计数器
    Dim rc As Long                ' 返回代码
    Dim hKey As Long              ' 处理打开的注册表关键字
    Dim hDepth As Long            '
    Dim sKeyVal As String
    Dim lKeyValType As Long       ' 注册表关键字数据类型
    Dim tmpVal As String          ' 注册表关键字的临时存储器
    Dim KeyValSize As Long        ' 注册表关键字变量尺寸
    
    ' 在 KeyRoot {HKEY_LOCAL_MACHINE...} 下打开注册表关键字
    '------------------------------------------------------------
    rc = RegOpenKeyEx(KeyRoot, KeyName, 0, KEY_ALL_ACCESS, _
                      hKey) ' 打开注册表关键字
    
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError ' 处理错误...
    
    tmpVal = String$(1024, 0)        ' 分配变量空间
    KeyValSize = 1024                ' 标记变量尺寸
    
    '------------------------------------------------------------
    ' 检索注册表关键字的值...
    '------------------------------------------------------------
    rc = RegQueryValueEx(hKey, SubKeyRef, 0, _
                         lKeyValType, tmpVal, KeyValSize)
                         ' 获得/创建关键字的值
                        
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError '错误处理
      
    tmpVal = Left$(tmpVal, InStr(tmpVal, Chr(0)) - 1)

    '------------------------------------------------------------
    ' 决定关键字值的转换类型...
    '------------------------------------------------------------
    Select Case lKeyValType     ' 搜索数据类型...
    Case REG_SZ, REG_EXPAND_SZ  ' 字符串注册表关键字数据类型
        sKeyVal = tmpVal        ' 复制字符串的值
    Case REG_DWORD              ' 四字节注册表关键字数据类型
        For i = Len(tmpVal) To 1 Step -1 ' 转换每一位
            sKeyVal = sKeyVal + Hex(Asc(Mid(tmpVal, i, 1)))
                         ' 一个字符一个字符地生成值。
        Next
        sKeyVal = Format$("&h" + sKeyVal)
                     ' 转换四字节为字符串
    Case REG_BINARY
        For i = Len(tmpVal) To 1 Step -1 ' 转换每一位
            sKeyVal = sKeyVal + Str(Asc(Mid(tmpVal, i, 1)))
                         ' 一个字符一个字符地生成值。
        Next
        sKeyVal = Format$(sKeyVal)
                     ' 转换四字节为字符串
         
    End Select
    
    GetKeyValue = sKeyVal     ' 返回值
    rc = RegCloseKey(hKey)    ' 关闭注册表关键字
    Exit Function             ' 退出
    
GetKeyError:    ' 错误发生过后进行清除...
    GetKeyValue = vbNullString ' 设置返回值为空字符串
    rc = RegCloseKey(hKey)     ' 关闭注册表关键字
End Function

'把根键值转换成字符串表达式
Public Function f_sChangeBootKey(BootKey As Long) As String
       Select Case BootKey
              Case HKEY_CLASSES_ROOT
                   f_sChangeBootKey = "HKEY_CLASSES_ROOT"
              Case HKEY_CURRENT_USER
                   f_sChangeBootKey = "HKEY_CURRENT_USER"
              Case HKEY_LOCAL_MACHINE
                   f_sChangeBootKey = "HKEY_LOCAL_MACHINE"
              Case HKEY_USERS
                   f_sChangeBootKey = "HKEY_USERS"
              Case HKEY_PERFORMANCE_DATA
                   f_sChangeBootKey = "HKEY_PERFORMANCE_DATA"
       End Select
End Function

'把键值类型转化为字符串表达式
Public Function f_sChangeKeyType(keytype As Long) As String
       Select Case keytype
              Case REG_SZ
                   f_sChangeKeyType = "REG_SZ"
              Case REG_BINARY
                   f_sChangeKeyType = "REG_BINARY"
              Case REG_DWORD
                   f_sChangeKeyType = "REG_DWORD"
              Case REG_EXPAND_SZ
                   f_sChangeKeyType = "REG_EXPAND_SZ"
       End Select
End Function
