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
Const REG_OPTION_NON_VOLATILE = 0       ' ��ϵͳ��������ʱ���ؼ��ֱ�����
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
    nLength As Long    '����
    lpSecurityDescriptor As Long '��ȫ��������
    bInheritHandle As Boolean
End Type

Public Function UpdateKeys(ByVal KeyRoot As Long, _
ByVal KeyName As String, ByVal SubKeyName As String, _
SubKeyValue As String, SubKeyType As Long) As Boolean
    Dim rc As Long                     ' ���ش���
    Dim hKey As Long                   ' ����һ��ע���ؼ���
    Dim hDepth As Long                 '
    Dim lpAttr As SECURITY_ATTRIBUTES  ' ע���ȫ����
    
    lpAttr.nLength = 50                ' ���ð�ȫ����Ϊȱʡֵ...
    lpAttr.lpSecurityDescriptor = 0    ' ...
    lpAttr.bInheritHandle = True       ' ...

    rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, REG_SZ, _
                        REG_OPTION_NON_VOLATILE, _
                        KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)
                        ' ����/��//KeyRoot//KeyName
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError
                                       ' ������...
    If (SubKeyValue = "") Then SubKeyValue = " "
          ' Ҫ��RegSetValueEx() ������Ҫ����һ���ո�...
    
    ' ����/�޸Ĺؼ���ֵ
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
                                       ' ������
    rc = RegCloseKey(hKey)             ' �رչؼ���
    
    UpdateKeys = True                   ' ���سɹ�
    Exit Function                      ' �˳�
CreateKeyError:
    UpdateKeys = False                  ' ���ô��󷵻ش���
    rc = RegCloseKey(hKey)             ' ��ͼ�رչؼ���
End Function


