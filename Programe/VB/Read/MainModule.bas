Attribute VB_Name = "MainModule"
Option Explicit

Public szIniFile As String

Sub Main()
#If Not bDebug Then
On Error Resume Next
#End If
Dim szFilePath As String, szFile As String
Dim szReader As String, szReadFile As String

szFile = "Read.Ini"
szFilePath = App.Path
szIniFile = szFilePath & "\" & szFile
szReader = ReadIniFile(szIniFile, "����", "�Ķ���")
If szReader = "" Then
   frmReadSet.Show vbModal
   szReader = ReadIniFile(szIniFile, "����", "�Ķ���")
End If
szReadFile = ReadIniFile(szIniFile, "����", "�ļ�")
If szReadFile = "" Then
   frmReadSet.Show vbModal
   szReadFile = ReadIniFile(szIniFile, "����", "�ļ�")
End If
Shell szReader & " " & szFilePath & "\" & szReadFile
End Sub

