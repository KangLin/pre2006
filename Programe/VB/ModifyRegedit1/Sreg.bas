Attribute VB_Name = "Sreg"
Option Explicit

Private Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long
Private Declare Function RegCreateKeyEx Lib "advapi32" Alias _
"RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String _
, ByVal Reserved As Long, ByVal lpClass As String, _
ByVal dwOptions As Long, ByVal samDesired As Long, _
ByRef lpSecurityAttributes As SECURITY_ATTRIBUTES, _
ByRef phkResult As Long, ByRef lpdwDisposition As Long) As Long
Private Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" _
(ByVal hKey As Long, ByVal lpSubKey As String, _
ByVal ulOptions As Long, ByVal samDesired As Long, _
ByRef phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32" _
Alias "RegQueryValueExA" (ByVal hKey As Long, _
ByVal lpValueName As String, ByVal lpReserved As Long, _
ByRef lpType As Long, ByVal lpData As String, _
ByRef lpcbData As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" _
(ByVal hKey As Long, ByVal lpValueName As String, _
ByVal Reserved As Long, ByVal dwType As Long, _
lpData As String, ByVal cbData As Long) As Long
' Note that if you declare the lpData parameter
'as String,you must pass it By Value.
Const REG_OPTION_NON_VOLATILE = 0       ' 当系统重新启动时，关键字被保留
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
Const ERROR_NONE = 0
Const ERROR_BADKEY = 2
Const ERROR_ACCESS_DENIED = 8
Const ERROR_SUCCESS = 0
Private Type SECURITY_ATTRIBUTES
    nLength As Long    '长度
    lpSecurityDescriptor As Long '安全属性描述
    bInheritHandle As Boolean
End Type

Public Function UpdateKeys(ByVal KeyRoot As Long, _
ByVal KeyName As String, ByVal SubKeyName As String, _
SubKeyValue As String, SubKeyType As Long) As Boolean
    Dim rc As Long                     ' 返回代码
    Dim hKey As Long                   ' 处理一个注册表关键字
    Dim hDepth As Long                 '
    Dim lpAttr As SECURITY_ATTRIBUTES  ' 注册表安全类型
    
    lpAttr.nLength = 50                ' 设置安全属性为缺省值...
    lpAttr.lpSecurityDescriptor = 0    ' ...
    lpAttr.bInheritHandle = True       ' ...

    rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, REG_SZ, _
                        REG_OPTION_NON_VOLATILE, _
                        KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)
                        ' 创建/打开//KeyRoot//KeyName
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError
                                       ' 错误处理...
    If (SubKeyValue = "") Then SubKeyValue = " "
          ' 要让RegSetValueEx() 工作需要输入一个空格...
    
    ' 创建/修改关键字值
    Select Case SubKeyType
           Case REG_KEY_TYPE_ENUM.REG_DWORD
                rc = RegSetValueEx(hKey, SubKeyName, _
                       0, REG_SZ, _
                       CLng(SubKeyValue), 4)
           Case REG_KEY_TYPE_ENUM.REG_SZ, REG_KEY_TYPE_ENUM.REG_BINARY
                rc = RegSetValueEx(hKey, SubKeyName, _
                       0, SubKeyType, _
                       SubKeyValue, _
                       LenB(StrConv(SubKeyValue, _
                                    vbFromUnicode)))
    End Select
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError
                                       ' 错误处理
    rc = RegCloseKey(hKey)             ' 关闭关键字
    
    UpdateKeys = True                   ' 返回成功
    Exit Function                      ' 退出
CreateKeyError:
    UpdateKeys = False                  ' 设置错误返回代码
    rc = RegCloseKey(hKey)             ' 试图关闭关键字
End Function


