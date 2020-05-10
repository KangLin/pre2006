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
szReader = ReadIniFile(szIniFile, "设置", "阅读器")
If szReader = "" Then
   frmReadSet.Show vbModal
   szReader = ReadIniFile(szIniFile, "设置", "阅读器")
End If
szReadFile = ReadIniFile(szIniFile, "设置", "文件")
If szReadFile = "" Then
   frmReadSet.Show vbModal
   szReadFile = ReadIniFile(szIniFile, "设置", "文件")
End If
Shell szReader & " " & szFilePath & "\" & szReadFile
End Sub

