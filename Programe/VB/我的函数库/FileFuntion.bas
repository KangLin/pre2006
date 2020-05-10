Attribute VB_Name = "FileFuntion"
Option Explicit

'API调用,用于写配置文件
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias "WritePrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpString As String, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long

'函数名:ReadIniFile
'参  数:
'       szFileName:配置文件名
'       szSelection:段名
'       szKey:关键字名
'返回值:配置值
Public Function ReadIniFile(ByVal szFileName As String, ByVal szSelection As String, ByVal szKey As String) As String
Dim i As Integer, iSize  As Integer
Dim szString As String * 1024
iSize = 1024
i = GetPrivateProfileString(szSelection, szKey, "", szString, iSize, szFileName)
If i > 0 Then
   ReadIniFile = Left(szString, i)
Else
   ReadIniFile = ""
End If
End Function

Public Function WriteIniFile(ByVal szFileName As String, ByVal szSelection As String, ByVal szKey As String, ByVal szVal As String) As Boolean
Dim i As Integer
i = WritePrivateProfileString(szSelection, szKey, szVal, szFileName)
If i = 0 Then
   WriteIniFile = False
Else
   WriteIniFile = True
End If
End Function
