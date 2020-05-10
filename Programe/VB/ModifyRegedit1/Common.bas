Attribute VB_Name = "Common"
Option Explicit

'得到驱动器类型API
Private Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long
'得到所有驱动器API
Private Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long
Private Declare Function GetLogicalDrives Lib "kernel32" () As Long
'驱动器类型常数
Private Const DRIVE_CDROM = 5 '光驱
Private Const DRIVE_FIXED = 3
Private Const DRIVE_RAMDISK = 6
Private Const DRIVE_REMOTE = 4
Private Const DRIVE_REMOVABLE = 2

'设置注册表API
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpData As Any, ByVal cbData As Long) As Long

'得到驱动器
Public Function GetDrive(Optional Object As Object)
Dim sDrive As String * 1024, sD As String, s As String
Dim j As Long, i As Long
      
      If Not Object Is Nothing Then
          i = GetLogicalDriveStrings(1024, sDrive)
          If i <> 0 Then  '分离出驱动器
             sD = Left$(sDrive, i)
             While Not (sD = "")
                   j = InStr(1, sD, Chr$(0))
                   s = Left(sD, j - 1)
                   Select Case GetDriveType(s)
                          Case DRIVE_CDROM
                               Object.AddItem "显示驱动器: 光驱" & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_FIXED
                               Object.AddItem "显示驱动器: 硬盘" & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_RAMDISK
                               Object.AddItem "显示驱动器: " & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_REMOTE
                               Object.AddItem "显示驱动器: " & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_REMOVABLE
                               Object.AddItem "显示驱动器: 软驱" & s
                               BoolShowDrive Object, Left$(s, 1)

                   End Select
                   sD = Right$(sD, Len(sD) - j)
             Wend
          End If
       End If
End Function

'在列表中显示驱动器是否被隐藏
Private Function BoolShowDrive(Object As Object, szDrive As String) As Boolean
'参数:
'sDrive显示的信息
'Object列表框
'szDrive驱动器号
If Run Then On Error Resume Next
Dim i As Long, vall As String
        With Object
             For i = 1 To UBound(Key)
                 If Key(i).SubKey = "NoDrives" Then
                    .Selected(.ListCount - 1) = Not (CBool(CLng(Key(i).KeyVal) And CLng(2 ^ (Asc(UCase(szDrive)) - Asc(UCase("a"))))))
                    Exit Function
                 End If
             Next i
             vall = GetKeyValue(HKEY_CURRENT_USER, "Software\Microsoft\Windows\CurrentVersion\Policies\Explorer", "NoDrives")
             
             If (CLng(vall) And CLng(2 ^ (Asc(UCase(szDrive)) - Asc(UCase("a"))))) = 0 Then
                .Selected(.ListCount - 1) = True
             End If
        End With
End Function

'DOWORD类型设值
Public Function dwUpdateKey(KeyRoot As Long, _
KeyName As String, SubKeyName As String, _
SubKeyValue As Long) As Boolean
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
                        0, REG_DWORD, _
                        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)                   ' 创建/打开//KeyRoot//KeyName
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' 错误处理...
    
    '------------------------------------------------------------
    '- 创建/修改关键字值...
    '------------------------------------------------------------
    ' 创建/修改关键字值
    rc = RegSetValueEx(hKey, SubKeyName, _
                       0, ENUM_REG_KEY_TYPE.REG_DWORD, _
                       SubKeyValue, 4)
                       
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' 错误处理
    '------------------------------------------------------------
    '- 关闭注册表关键字...
    '------------------------------------------------------------
    rc = RegCloseKey(hKey)                              ' 关闭关键字
    
    dwUpdateKey = True                                    ' 返回成功
    Exit Function                                       ' 退出
CreateKeyError:
    dwUpdateKey = False                                  ' 设置错误返回代码
    rc = RegCloseKey(hKey)                              ' 试图关闭关键字
End Function


