Attribute VB_Name = "RegKeys"
' ���ģ�����ڶ���дע���ؼ��֡�
' ��ͬ��VB ���ڲ�ע�����ʷ�����������
' ͨ���ַ�����ֵ������д�κ�ע���ؼ��֡�


Option Explicit
'---------------------------------------------------------------
'-ע��� API ����...
'---------------------------------------------------------------
'�ر�
Private Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long
'����
Private Declare Function RegCreateKeyEx Lib "advapi32" Alias _
"RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String _
, ByVal Reserved As Long, ByVal lpClass As String, _
ByVal dwOptions As Long, ByVal samDesired As Long, _
ByRef lpSecurityAttributes As SECURITY_ATTRIBUTES, _
ByRef phkResult As Long, ByRef lpdwDisposition As Long) As Long

'-------------------------------------------------------------
'.hkeyΪ����ֵ,Ϊ�������ֵ:
'     HKEY_CLASSES_ROOT = &H80000000
'     HKEY_CURRENT_USER = &H80000001
'     HKEY_LOCAL_MACHINE = &H80000002
'     HKEY_USERS = &H80000003
'     HKEY_PERFORMANCE_DATA = &H80000004
'-------------------------------------------
'     HKEY_DYN_DATA   ΪWIN95����ϵͳ
'     HKEY_PERFORMANCE_PATA  ΪWINNT����ϵͳ
'-------------------------------------------------------------
'.lpsubkeyΪһ��ָ�������β���ַ�����ָ��,���а�����Ҫ������
'         �򿪵��Ӽ��̵�����,���ܾ�(\)��ͷ,��ΪNULL
'-------------------------------------------------------------
'.Reserved ����,��Ϊ��
'-------------------------------------------------------------
'lpClass  ָ����������͵��ַ���,����Ѵ���,���Ըò���,Ϊ����ֵ:
'Const REG_SZ = 1                         ' Unicode���ս��ַ���
'Const REG_EXPAND_SZ = 2                  ' Unicode���ս��ַ���
'Const REG_DWORD = 4                      ' 32-bit ����
'-------------------------------------------------------------
'.dwOptionsΪ�´����ļ�����һ��������,��ȡ����ֵ:
' REG_OPTION_NON_VOLATILE �´����ļ�Ϊһ���Ƕ����Եļ���
'                       �����ݱ������ļ��У�
'REG_OPTION_VOLATILE WIN95���Ըò���
'                          �����ݱ������ڴ��У�
'REG_OPTION_BACKUP_RESTORE ����WINNT��֧��,���ṩ���ȼ�֧��
'-------------------------------------------------------------
'.samDesired �������öԼ����ʵ�Ȩ��,��ȡ����ֵ:
' KEY_CREATE_LINK ׼�����ɷ��ż�
' KEY_CREATE_SUB_KEY ׼�������Ӽ�
' KEY_ENUMERATE_SUB_KEYS ׼������ö���Ӽ�
' KEY_EXECUTE ׼����ж�д����
' KEY_QUERY_VALUE ׼���ѯ�Ӽ�
' KEY_ALL_ACCESS �ṩ��ȫ����,������ֵ�ڵ����
'-----------------------------------------------
' KEY_READ ������ֵ�ڵ����,������ֵ�����
' KEY_QUERY_VALUE
' KEY_ENVMERATE_KEYS
' KEY_NOTIFY
' KEY_SET_VALUE ׼�������Ӽ�����ֵ��
'-----------------------------------------------
' KEY_WRITE ������ֵ�ڵ����:
' KEY_SET_VALUE
' KEY_CREAT_SUB_KEY
'-------------------------------------------------------------
'.lpSecurityAttributesΪһ��ָ��SECURITY_ATTRIBVTES�ṹ��ָ��
'ȷ������ֵ�ľ���Ƿ��Ӵ�����̼̳�,��WINNT��,�ò�����Ϊ�´�
'���ļ���ȫ������
'-------------------------------------------------------------
'.phkResultΪһ��ָ���½���򿪼��ľ��ָ��
'-------------------------------------------------------------
'.lpdwDispositionָ�����Ǳ�����,���Ǳ��򿪵�,������:
' REG_CREAT_NEW_KEY ����ǰ������,���ڱ�����
' REG_OPENED_EXISTING_KEY ����ǰ�Ѵ���,���ڱ���
'-------------------------------------------------------------
'����ֵ:
'������óɹ�,�򷵻�ERROR_SUCCESS,����,����ֵ��(Visual C++)��
'Ϊ�ļ�WINERROR.H�ж����һ������Ĵ������,��ͨ������
'ERR_MAT_MESSAGE_FROM_SYSTEM��ʶFormatMessage��������ȡһ����
'�������������;��(Visual Basic)����Err.Description����ȡһ��
'�Դ������������
'---------------------------------------------------------------
'��
Private Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" _
(ByVal hKey As Long, ByVal lpSubKey As String, _
ByVal ulOptions As Long, ByVal samDesired As Long, _
ByRef phkResult As Long) As Long
'��ѯ
Private Declare Function RegQueryValueEx Lib "advapi32" _
Alias "RegQueryValueExA" (ByVal hKey As Long, _
ByVal lpValueName As String, ByVal lpReserved As Long, _
ByRef lpType As Long, ByVal lpData As String, _
ByRef lpcbData As Long) As Long
'.lpTypeΪһ��ָ���������͵�ָ��
' REG_SZ = 1      һ�������β���ַ���,���ݺ���ʹ��
'            ���ַ������͵Ĳ�ͬ������ΪUnicode���ս��ַ���,
'            ��ANSI�ַ���
' REG_EXPAND_SZ = 2               Unicode���ս��ַ���
'                         һ������δ��չ�����������ַ���
' REG_LINK     һ��UNICODE���͵�����
' REG_DWORD = 4                   32-bit ����
' REG_BINARY                      ������
' REG_DWORD_LITTLE_ENDIAN               LITTLE_ENDIAN��ʽ����
'                                       ��,��:0x12345678
'                                     ��(0x79 0x56 0x34 0x12)
'                                     ��ʽ����
' REG_DWORD_BIN_ENDIAN                 BIG_ENDIAN��ʽ�����ݣ�
'                                    ��:0x12345678��
'                                     (0x12 0x34 0x56 0x78)
'                                     ��ʽ����
'-------------------------------------------------------------
'.lpValueName�ؼ��ֱ�����
'-------------------------------------------------------------
'.lpData ���ص�����,��һ�������β���ַ���
' ��Left$(lpDate, InStr(lpDate, Chr(0)) - 1)ȡ�þ�ȷֵ
'-------------------------------------------------------------
'.lpcbData ��Ҫȡ�����ݵ���󳤶�
'-------------------------------------------------------------
'����
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" _
(ByVal hKey As Long, ByVal lpValueName As String, _
ByVal Reserved As Long, ByVal dwType As Long, _
lpData As Any, ByVal cbData As Long) As Long
' Note that if you declare the lpData parameter
'as String,you must pass it By Value.

'- ע��� Api ����...
'---------------------------------------------------------------
' Reg Data Types...,������...
Public Enum REG_KEY_TYPE_ENUM
       REG_SZ = 1       ' Unicode���ս��ַ���
       REG_BINARY = 3    '������ֵ
       REG_DWORD = 4   ' 32-bit ����
       REG_EXPAND_SZ = 2   'Unicode���ս��ַ���
       End Enum
'.lpTypeΪһ��ָ���������͵�ָ��
' REG_SZ = 1      һ�������β���ַ���,���ݺ���ʹ��
'            ���ַ������͵Ĳ�ͬ������ΪUnicode���ս��ַ���,
'            ��ANSI�ַ���
' REG_EXPAND_SZ = 2               Unicode���ս��ַ���
'                         һ������δ��չ�����������ַ���
' REG_LINK     һ��UNICODE���͵�����
' REG_DWORD = 4                   32-bit ����
' REG_BINARY                      ������
' REG_DWORD_LITTLE_ENDIAN               LITTLE_ENDIAN��ʽ����
'                                       ��,��:0x12345678
'                                     ��(0x79 0x56 0x34 0x12)
'                                     ��ʽ����
' REG_DWORD_BIN_ENDIAN                 BIG_ENDIAN��ʽ�����ݣ�
'                                    ��:0x12345678��
'                                     (0x12 0x34 0x56 0x78)
'                                     ��ʽ����


' ע���������ֵ...
Const REG_OPTION_NON_VOLATILE = 0       ' ��ϵͳ��������ʱ���ؼ��ֱ�����

' ע���ؼ��ְ�ȫѡ��...
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
                     
' ע���ؼ��ָ�����...
Public Const HKEY_CLASSES_ROOT = &H80000000
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_LOCAL_MACHINE = &H80000002
Public Const HKEY_USERS = &H80000003
Public Const HKEY_PERFORMANCE_DATA = &H80000004

' ����ֵ...
Const ERROR_NONE = 0
Const ERROR_BADKEY = 2
Const ERROR_ACCESS_DENIED = 8
Const ERROR_SUCCESS = 0

'---------------------------------------------------------------
'- ע���ȫ��������...
'---------------------------------------------------------------
Private Type SECURITY_ATTRIBUTES
    nLength As Long    '����
    lpSecurityDescriptor As Long '��ȫ��������
    bInheritHandle As Boolean
End Type

'-------------------------------------------------------------------------------------------------
'sample usage - Debug.Print UpdateKey(HKEY_CLASSES_ROOT, "keyname", "newvalue")
'-------------------------------------------------------------------------------------------------
'����ע���
'-------------------------------------------------------------------------------------------------
Public Function UpdateKey(ByVal KeyRoot As Long, _
ByVal KeyName As String, ByVal SubKeyName As String, _
SubKeyValue As Variant, SubKeyType As Long) As Boolean
'����:
'KeyRoot:Ϊע������ֵ
'KeyName:�ؼ�����
'SubKeyName:�ӹؼ�����
'SubKeyType:�ӹؼ��ֵ���������
'SubKeyValue:�ؼ���ֵ
    Dim rc As Long                     ' ���ش���
    Dim hKey As Long                   ' ����һ��ע���ؼ���
    Dim hDepth As Long                 '
    Dim lpAttr As SECURITY_ATTRIBUTES  ' ע���ȫ����
    Dim DataLong As Long               '���ݵĳ���
    Dim sSubKeyValue As String         '�ַ����Ͳ���
    
    lpAttr.nLength = 50                ' ���ð�ȫ����Ϊȱʡֵ...
    lpAttr.lpSecurityDescriptor = 0    ' ...
    lpAttr.bInheritHandle = True       ' ...

    '------------------------------------------------------------
    '- ����/��ע���ؼ���...
    '------------------------------------------------------------
    'rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, REG_SZ, _
                        REG_OPTION_NON_VOLATILE, _
                        KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)
                        ' ����/��//KeyRoot//KeyName
    rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, SubKeyType, _
                        REG_OPTION_NON_VOLATILE, _
                        KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)
                        ' ����/��//KeyRoot//KeyName
    
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError
                                       ' ������...
    
    '------------------------------------------------------------
    '- ����/�޸Ĺؼ���ֵ...
    '------------------------------------------------------------
    If (SubKeyValue = "") Then SubKeyValue = " "
          ' Ҫ��RegSetValueEx() ������Ҫ����һ���ո�...
    
    ' ����/�޸Ĺؼ���ֵ
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
                                       ' ������
    '------------------------------------------------------------
    '- �ر�ע���ؼ���...
    '------------------------------------------------------------
    rc = RegCloseKey(hKey)             ' �رչؼ���
    
    UpdateKey = True                   ' ���سɹ�
    Exit Function                      ' �˳�
CreateKeyError:
    UpdateKey = False                  ' ���ô��󷵻ش���
    rc = RegCloseKey(hKey)             ' ��ͼ�رչؼ���
End Function

'-------------------------------------------------------------------------------------------------
'sample usage - Debug.Print GetKeyValue(HKEY_CLASSES_ROOT, "COMCTL.ListviewCtrl.1\CLSID", "")
'-------------------------------------------------------------------------------------------------
'�õ�ע����ֵ
'-------------------------------------------------------------------------------------------------
Public Function GetKeyValue(KeyRoot As Long, KeyName As String, SubKeyRef As String, Optional bFlag As Boolean = False) As String
'����:
'KeyRoot:Ϊע������ֵ
'KeyName:�ؼ�����
'SubKeyRef:lpValueName,�ؽ��ֱ�������

    Dim i As Long                 ' ѭ��������
    Dim rc As Long                ' ���ش���
    Dim hKey As Long              ' ����򿪵�ע���ؼ���
    Dim hDepth As Long            '
    Dim sKeyVal As String
    Dim lKeyValType As Long       ' ע���ؼ�����������
    Dim tmpVal As String          ' ע���ؼ��ֵ���ʱ�洢��
    Dim KeyValSize As Long        ' ע���ؼ��ֱ����ߴ�
    
    ' �� KeyRoot {HKEY_LOCAL_MACHINE...} �´�ע���ؼ���
    '------------------------------------------------------------
    rc = RegOpenKeyEx(KeyRoot, KeyName, 0, KEY_ALL_ACCESS, _
                      hKey) ' ��ע���ؼ���
    
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError ' �������...
    
    tmpVal = String$(1024, 0)        ' ��������ռ�
    KeyValSize = 1024                ' ��Ǳ����ߴ�
    
    '------------------------------------------------------------
    ' ����ע���ؼ��ֵ�ֵ...
    '------------------------------------------------------------
    rc = RegQueryValueEx(hKey, SubKeyRef, 0, _
                         lKeyValType, tmpVal, KeyValSize)
                         ' ���/�����ؼ��ֵ�ֵ
                        
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError '������
      
    tmpVal = Left$(tmpVal, InStr(tmpVal, Chr(0)) - 1)

    '------------------------------------------------------------
    ' �����ؼ���ֵ��ת������...
    '------------------------------------------------------------
    Select Case lKeyValType     ' ������������...
    Case REG_SZ, REG_EXPAND_SZ  ' �ַ���ע���ؼ�����������
        sKeyVal = tmpVal        ' �����ַ�����ֵ
    Case REG_DWORD              ' ���ֽ�ע���ؼ�����������
        For i = Len(tmpVal) To 1 Step -1 ' ת��ÿһλ
            sKeyVal = sKeyVal + Hex(Asc(Mid(tmpVal, i, 1)))
                         ' һ���ַ�һ���ַ�������ֵ��
        Next
        sKeyVal = Format$("&h" + sKeyVal)
                     ' ת�����ֽ�Ϊ�ַ���
    Case REG_BINARY
        For i = Len(tmpVal) To 1 Step -1 ' ת��ÿһλ
            sKeyVal = sKeyVal + Str(Asc(Mid(tmpVal, i, 1)))
                         ' һ���ַ�һ���ַ�������ֵ��
        Next
        sKeyVal = Format$(sKeyVal)
                     ' ת�����ֽ�Ϊ�ַ���
         
    End Select
    
    GetKeyValue = sKeyVal     ' ����ֵ
    rc = RegCloseKey(hKey)    ' �ر�ע���ؼ���
    Exit Function             ' �˳�
    
GetKeyError:    ' ����������������...
    GetKeyValue = vbNullString ' ���÷���ֵΪ���ַ���
    rc = RegCloseKey(hKey)     ' �ر�ע���ؼ���
End Function

'�Ѹ���ֵת�����ַ������ʽ
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

'�Ѽ�ֵ����ת��Ϊ�ַ������ʽ
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
