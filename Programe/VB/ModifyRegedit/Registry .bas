Attribute VB_Name = "RegKey"
Option Explicit
'---------------------------------------------------------------
'-注册表 API 声明...
'---------------------------------------------------------------
Public Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long
Public Declare Function RegCreateKeyEx Lib "advapi32" Alias "RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal Reserved As Long, ByVal lpClass As String, ByVal dwOptions As Long, ByVal samDesired As Long, ByRef lpSecurityAttributes As SECURITY_ATTRIBUTES, ByRef phkResult As Long, ByRef lpdwDisposition As Long) As Long
Public Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, ByRef phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, ByRef lpType As Long, ByVal lpData As String, ByRef lpcbData As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByVal lpData As String, ByVal cbData As Long) As Long

'---------------------------------------------------------------
'- 注册表 Api 常数...
'---------------------------------------------------------------
' Reg Data Types...
Public Enum ENUM_REG_KEY_TYPE
       REG_BOOL = -1 '这是自己定义的,是一个Boolean值
       REG_SZ = 1   ' Unicode空终结字符串
       REG_EXPAND_SZ = 2 ' Unicode空终结字符串
       REG_BINARY = 3
       REG_DWORD = 4  '32-bit 数字
       End Enum


Public Enum KEY_VALUE_ENUM
       ' 注册表创建类型值...
       REG_OPTION_NON_VOLATILE = 0       ' 当系统重新启动时，关键字被保留

       ' 注册表关键字安全选项...
       READ_CONTROL = &H20000
       KEY_QUERY_VALUE = &H1
       KEY_SET_VALUE = &H2
       KEY_CREATE_SUB_KEY = &H4
       KEY_ENUMERATE_SUB_KEYS = &H8
       KEY_NOTIFY = &H10
       KEY_CREATE_LINK = &H20
       KEY_READ = KEY_QUERY_VALUE + KEY_ENUMERATE_SUB_KEYS + KEY_NOTIFY + READ_CONTROL
       KEY_WRITE = KEY_SET_VALUE + KEY_CREATE_SUB_KEY + READ_CONTROL
       KEY_EXECUTE = KEY_READ
       End Enum
Public Const KEY_ALL_ACCESS = KEY_QUERY_VALUE + KEY_SET_VALUE + _
                       KEY_CREATE_SUB_KEY + KEY_ENUMERATE_SUB_KEYS + _
                       KEY_NOTIFY + KEY_CREATE_LINK + READ_CONTROL

Public Enum ERROR_ENUM
       ' 返回值...
       ERROR_NONE = 0
       ERROR_BADKEY = 2
       ERROR_ACCESS_DENIED = 8
       ERROR_SUCCESS = 0
       End Enum
' 注册表关键字根类型...
Public Enum KEYROOT_ENUM
       HKEY_CLASSES_ROOT = &H80000000
       HKEY_CURRENT_USER = &H80000001
       HKEY_LOCAL_MACHINE = &H80000002
       HKEY_USERS = &H80000003
       HKEY_PERFORMANCE_DATA = &H80000004
       End Enum
       
'---------------------------------------------------------------
'- 注册表安全属性类型...
'---------------------------------------------------------------
Public Type SECURITY_ATTRIBUTES
    nLength As Long
    lpSecurityDescriptor As Long
    bInheritHandle As Boolean
End Type

'-------------------------------------------------------------------------------------------------
'sample usage - Debug.Print UpodateKey(HKEY_CLASSES_ROOT, "keyname", "newvalue")
'-------------------------------------------------------------------------------------------------
Public Function szUpdateKey(KeyRoot As Long, _
KeyName As String, SubKeyName As String, _
SubKeyValue As String) As Boolean
    Dim rc As Long                                      ' 返回代码
    Dim hKey As Long                                    ' 处理一个注册表关键字
    Dim hDepth As Long                                  '
    Dim lpAttr As SECURITY_ATTRIBUTES                   ' 注册表安全类型
    
    lpAttr.nLength = 50                                 ' 设置安全属性为缺省值...
    lpAttr.lpSecurityDescriptor = 0                     ' ...
    lpAttr.bInheritHandle = True                        ' ...

    '------------------------------------------------------------
    '- 创建/打开注册表关键字...
    '------------------------------------------------------------
    rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, REG_SZ, _
                        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)                   ' 创建/打开//KeyRoot//KeyName
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' 错误处理...
    
    '------------------------------------------------------------
    '- 创建/修改关键字值...
    '------------------------------------------------------------
    If (SubKeyValue = "") Then SubKeyValue = " "        ' 要让RegSetValueEx() 工作需要输入一个空格...
    
    ' 创建/修改关键字值
    rc = RegSetValueEx(hKey, SubKeyName, _
                       0, REG_SZ, _
                       SubKeyValue, LenB(StrConv(SubKeyValue, vbFromUnicode)))
                       
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' 错误处理
    '------------------------------------------------------------
    '- 关闭注册表关键字...
    '------------------------------------------------------------
    rc = RegCloseKey(hKey)                              ' 关闭关键字
    
    szUpdateKey = True                                    ' 返回成功
    Exit Function                                       ' 退出
CreateKeyError:
    szUpdateKey = False                                   ' 设置错误返回代码
    rc = RegCloseKey(hKey)                              ' 试图关闭关键字
End Function

'-------------------------------------------------------------------------------------------------
'sample usage - Debug.Print GetKeyValue(HKEY_CLASSES_ROOT, "COMCTL.ListviewCtrl.1\CLSID", "")
'-------------------------------------------------------------------------------------------------
Public Function GetKeyValue(KeyRoot As Long, _
KeyName As String, SubKeyRef As String) As String
    Dim i As Long                                           ' 循环计数器
    Dim rc As Long                                          ' 返回代码
    Dim hKey As Long                                        ' 处理打开的注册表关键字
    Dim hDepth As Long                                      '
    Dim sKeyVal As String
    Dim lKeyValType As Long                                 ' 注册表关键字数据类型
    Dim tmpVal As String                                    ' 注册表关键字的临时存储器
    Dim KeyValSize As Long                                  ' 注册表关键字变量尺寸
    
    ' 在 KeyRoot {HKEY_LOCAL_MACHINE...} 下打开注册表关键字
    '------------------------------------------------------------
    rc = RegOpenKeyEx(KeyRoot, KeyName, 0, KEY_ALL_ACCESS, hKey) ' 打开注册表关键字
    
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError          ' 处理错误...
    
    tmpVal = String$(1024, 0)                             ' 分配变量空间
    KeyValSize = 1024                                       ' 标记变量尺寸
    
    '------------------------------------------------------------
    ' 检索注册表关键字的值...
    '------------------------------------------------------------
    rc = RegQueryValueEx(hKey, SubKeyRef, 0, _
                         lKeyValType, tmpVal, KeyValSize)    ' 获得/创建关键字的值
                        
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError          ' 错误处理
      
    tmpVal = Left$(tmpVal, InStr(tmpVal, Chr(0)) - 1)
    
    '------------------------------------------------------------
    ' 决定关键字值的转换类型...
    '------------------------------------------------------------
    Select Case lKeyValType                                  ' 搜索数据类型...
    Case REG_SZ, REG_EXPAND_SZ                              ' 字符串注册表关键字数据类型
        sKeyVal = tmpVal                                     ' 复制字符串的值
    Case REG_DWORD                        ' 四字节注册表关键字数据类型
        For i = Len(tmpVal) To 1 Step -1          ' 转换每一位
            sKeyVal = sKeyVal + Hex(Asc(Mid(tmpVal, i, 1)))
            ' 一个字符一个字符地生成值。
        Next
        sKeyVal = Format$("&h" + sKeyVal) ' 转换四字节为字符串
        If sKeyVal = "&h" Then sKeyVal = 0
    End Select
    
    GetKeyValue = sKeyVal                                   ' 返回值
    rc = RegCloseKey(hKey)                                  ' 关闭注册表关键字
    Exit Function                                           ' 退出
    
GetKeyError:    ' 错误发生过后进行清除...
    GetKeyValue = vbNullString                              ' 设置返回值为空字符串
    rc = RegCloseKey(hKey)                                  ' 关闭注册表关键字
End Function


'把根键值转换成字符串表达式
Public Function f_sChangeRootKey(RootKey As Long) As String
       Select Case RootKey
              Case HKEY_CLASSES_ROOT
                   f_sChangeRootKey = "HKEY_CLASSES_ROOT"
              Case HKEY_CURRENT_USER
                   f_sChangeRootKey = "HKEY_CURRENT_USER"
              Case HKEY_LOCAL_MACHINE
                   f_sChangeRootKey = "HKEY_LOCAL_MACHINE"
              Case HKEY_USERS
                   f_sChangeRootKey = "HKEY_USERS"
              Case HKEY_PERFORMANCE_DATA
                   f_sChangeRootKey = "HKEY_PERFORMANCE_DATA"
       End Select
End Function

'把字符串根键转化为根键值
Public Function f_lChangeRootKey(RootKey As String) As Long
       Select Case RootKey
              Case "HKEY_CLASSES_ROOT"
                   f_lChangeRootKey = HKEY_CLASSES_ROOT
              Case "HKEY_CURRENT_USER"
                   f_lChangeRootKey = HKEY_CURRENT_USER
              Case "HKEY_LOCAL_MACHINE"
                   f_lChangeRootKey = HKEY_LOCAL_MACHINE
              Case "HKEY_USERS"
                   f_lChangeRootKey = HKEY_USERS
              Case "HKEY_PERFORMANCE_DATA"
                   f_lChangeRootKey = HKEY_PERFORMANCE_DATA
       End Select
End Function

'把键值类型转化为字符串表达式
Public Function f_sChangeKeyType(KeyType As Long) As String
       Select Case KeyType
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

'把字符串转化为键值
Public Function f_lChangeKeyType(KeyType As String) As ENUM_REG_KEY_TYPE
       Select Case KeyType
              Case "REG_SZ"
                   f_lChangeKeyType = REG_SZ
              Case "REG_BINARY"
                   f_lChangeKeyType = REG_BINARY
              Case "REG_DWORD"
                   f_lChangeKeyType = REG_DWORD
              Case "REG_EXPAND_SZ"
                   f_lChangeKeyType = REG_EXPAND_SZ
       End Select
End Function
