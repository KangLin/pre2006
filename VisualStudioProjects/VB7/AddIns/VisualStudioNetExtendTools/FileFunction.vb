'*******************************************************************************************************
'��Ȩ���� (C) 2006 ���ֹ����ң���������Ȩ����
'�ļ�����FileFunction.vb
'��  �����ļ����ƺ���ģ��
'��  ����2006.1.1.0
'��  �ߣ���  ��
'E_Mail��kl222@126.com
'��  �ڣ�2006��2��15��
'ʱ  �䣺8:41:34
'��������Microsoft Development Environment 7.10 ���� Basic 7.10
'*******************************************************************************************************

Option Strict Off
Option Explicit On 

Module FileFunction
    'API����,����д�����ļ�
    Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
    Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As String, ByVal lpFileName As String) As Integer
    Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias "WritePrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpString As String, ByVal lpFileName As String) As Integer
    Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Integer

    '������:ReadIniFile
    '��  ��:
    '       szFileName:�����ļ���
    '       szSelection:����
    '       szKey:�ؼ�����
    '����ֵ:����ֵ
    Public Function ReadIniFile(ByVal szFileName As String, ByVal szSelection As String, ByVal szKey As String, Optional ByVal szDefault As String = "") As String
        Dim i As Integer, iSize As Long
        Dim szString As String
        szString = Space(1024)
        iSize = 1024
        i = GetPrivateProfileString(szSelection, szKey, szDefault, szString, iSize, szFileName)
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

End Module
