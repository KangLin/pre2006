Attribute VB_Name = "RegKey"
Option Explicit
'---------------------------------------------------------------
'-ע��� API ����...
'---------------------------------------------------------------
Public Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long
Public Declare Function RegCreateKeyEx Lib "advapi32" Alias "RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal Reserved As Long, ByVal lpClass As String, ByVal dwOptions As Long, ByVal samDesired As Long, ByRef lpSecurityAttributes As SECURITY_ATTRIBUTES, ByRef phkResult As Long, ByRef lpdwDisposition As Long) As Long
Public Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, ByRef phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, ByRef lpType As Long, ByVal lpData As String, ByRef lpcbData As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByVal lpData As String, ByVal cbData As Long) As Long

'---------------------------------------------------------------
'- ע��� Api ����...
'---------------------------------------------------------------
' Reg Data Types...
Public Enum ENUM_REG_KEY_TYPE
       REG_BOOL = -1 '�����Լ������,��һ��Booleanֵ
       REG_SZ = 1   ' Unicode���ս��ַ���
       REG_EXPAND_SZ = 2 ' Unicode���ս��ַ���
       REG_BINARY = 3
       REG_DWORD = 4  '32-bit ����
       End Enum


Public Enum KEY_VALUE_ENUM
       ' ע���������ֵ...
       REG_OPTION_NON_VOLATILE = 0       ' ��ϵͳ��������ʱ���ؼ��ֱ�����

       ' ע���ؼ��ְ�ȫѡ��...
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
       ' ����ֵ...
       ERROR_NONE = 0
       ERROR_BADKEY = 2
       ERROR_ACCESS_DENIED = 8
       ERROR_SUCCESS = 0
       End Enum
' ע���ؼ��ָ�����...
Public Enum KEYROOT_ENUM
       HKEY_CLASSES_ROOT = &H80000000
       HKEY_CURRENT_USER = &H80000001
       HKEY_LOCAL_MACHINE = &H80000002
       HKEY_USERS = &H80000003
       HKEY_PERFORMANCE_DATA = &H80000004
       End Enum
       
'---------------------------------------------------------------
'- ע���ȫ��������...
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
    Dim rc As Long                                      ' ���ش���
    Dim hKey As Long                                    ' ����һ��ע���ؼ���
    Dim hDepth As Long                                  '
    Dim lpAttr As SECURITY_ATTRIBUTES                   ' ע���ȫ����
    
    lpAttr.nLength = 50                                 ' ���ð�ȫ����Ϊȱʡֵ...
    lpAttr.lpSecurityDescriptor = 0                     ' ...
    lpAttr.bInheritHandle = True                        ' ...

    '------------------------------------------------------------
    '- ����/��ע���ؼ���...
    '------------------------------------------------------------
    rc = RegCreateKeyEx(KeyRoot, KeyName, _
                        0, REG_SZ, _
                        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)                   ' ����/��//KeyRoot//KeyName
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' ������...
    
    '------------------------------------------------------------
    '- ����/�޸Ĺؼ���ֵ...
    '------------------------------------------------------------
    If (SubKeyValue = "") Then SubKeyValue = " "        ' Ҫ��RegSetValueEx() ������Ҫ����һ���ո�...
    
    ' ����/�޸Ĺؼ���ֵ
    rc = RegSetValueEx(hKey, SubKeyName, _
                       0, REG_SZ, _
                       SubKeyValue, LenB(StrConv(SubKeyValue, vbFromUnicode)))
                       
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' ������
    '------------------------------------------------------------
    '- �ر�ע���ؼ���...
    '------------------------------------------------------------
    rc = RegCloseKey(hKey)                              ' �رչؼ���
    
    szUpdateKey = True                                    ' ���سɹ�
    Exit Function                                       ' �˳�
CreateKeyError:
    szUpdateKey = False                                   ' ���ô��󷵻ش���
    rc = RegCloseKey(hKey)                              ' ��ͼ�رչؼ���
End Function

'-------------------------------------------------------------------------------------------------
'sample usage - Debug.Print GetKeyValue(HKEY_CLASSES_ROOT, "COMCTL.ListviewCtrl.1\CLSID", "")
'-------------------------------------------------------------------------------------------------
Public Function GetKeyValue(KeyRoot As Long, _
KeyName As String, SubKeyRef As String) As String
    Dim i As Long                                           ' ѭ��������
    Dim rc As Long                                          ' ���ش���
    Dim hKey As Long                                        ' ����򿪵�ע���ؼ���
    Dim hDepth As Long                                      '
    Dim sKeyVal As String
    Dim lKeyValType As Long                                 ' ע���ؼ�����������
    Dim tmpVal As String                                    ' ע���ؼ��ֵ���ʱ�洢��
    Dim KeyValSize As Long                                  ' ע���ؼ��ֱ����ߴ�
    
    ' �� KeyRoot {HKEY_LOCAL_MACHINE...} �´�ע���ؼ���
    '------------------------------------------------------------
    rc = RegOpenKeyEx(KeyRoot, KeyName, 0, KEY_ALL_ACCESS, hKey) ' ��ע���ؼ���
    
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError          ' �������...
    
    tmpVal = String$(1024, 0)                             ' ��������ռ�
    KeyValSize = 1024                                       ' ��Ǳ����ߴ�
    
    '------------------------------------------------------------
    ' ����ע���ؼ��ֵ�ֵ...
    '------------------------------------------------------------
    rc = RegQueryValueEx(hKey, SubKeyRef, 0, _
                         lKeyValType, tmpVal, KeyValSize)    ' ���/�����ؼ��ֵ�ֵ
                        
    If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError          ' ������
      
    tmpVal = Left$(tmpVal, InStr(tmpVal, Chr(0)) - 1)
    
    '------------------------------------------------------------
    ' �����ؼ���ֵ��ת������...
    '------------------------------------------------------------
    Select Case lKeyValType                                  ' ������������...
    Case REG_SZ, REG_EXPAND_SZ                              ' �ַ���ע���ؼ�����������
        sKeyVal = tmpVal                                     ' �����ַ�����ֵ
    Case REG_DWORD                        ' ���ֽ�ע���ؼ�����������
        For i = Len(tmpVal) To 1 Step -1          ' ת��ÿһλ
            sKeyVal = sKeyVal + Hex(Asc(Mid(tmpVal, i, 1)))
            ' һ���ַ�һ���ַ�������ֵ��
        Next
        sKeyVal = Format$("&h" + sKeyVal) ' ת�����ֽ�Ϊ�ַ���
        If sKeyVal = "&h" Then sKeyVal = 0
    End Select
    
    GetKeyValue = sKeyVal                                   ' ����ֵ
    rc = RegCloseKey(hKey)                                  ' �ر�ע���ؼ���
    Exit Function                                           ' �˳�
    
GetKeyError:    ' ����������������...
    GetKeyValue = vbNullString                              ' ���÷���ֵΪ���ַ���
    rc = RegCloseKey(hKey)                                  ' �ر�ע���ؼ���
End Function


'�Ѹ���ֵת�����ַ������ʽ
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

'���ַ�������ת��Ϊ����ֵ
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

'�Ѽ�ֵ����ת��Ϊ�ַ������ʽ
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

'���ַ���ת��Ϊ��ֵ
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
