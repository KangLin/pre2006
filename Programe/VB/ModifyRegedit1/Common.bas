Attribute VB_Name = "Common"
Option Explicit

'�õ�����������API
Private Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long
'�õ�����������API
Private Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long
Private Declare Function GetLogicalDrives Lib "kernel32" () As Long
'���������ͳ���
Private Const DRIVE_CDROM = 5 '����
Private Const DRIVE_FIXED = 3
Private Const DRIVE_RAMDISK = 6
Private Const DRIVE_REMOTE = 4
Private Const DRIVE_REMOVABLE = 2

'����ע���API
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpData As Any, ByVal cbData As Long) As Long

'�õ�������
Public Function GetDrive(Optional Object As Object)
Dim sDrive As String * 1024, sD As String, s As String
Dim j As Long, i As Long
      
      If Not Object Is Nothing Then
          i = GetLogicalDriveStrings(1024, sDrive)
          If i <> 0 Then  '�����������
             sD = Left$(sDrive, i)
             While Not (sD = "")
                   j = InStr(1, sD, Chr$(0))
                   s = Left(sD, j - 1)
                   Select Case GetDriveType(s)
                          Case DRIVE_CDROM
                               Object.AddItem "��ʾ������: ����" & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_FIXED
                               Object.AddItem "��ʾ������: Ӳ��" & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_RAMDISK
                               Object.AddItem "��ʾ������: " & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_REMOTE
                               Object.AddItem "��ʾ������: " & s
                               BoolShowDrive Object, Left$(s, 1)
                          Case DRIVE_REMOVABLE
                               Object.AddItem "��ʾ������: ����" & s
                               BoolShowDrive Object, Left$(s, 1)

                   End Select
                   sD = Right$(sD, Len(sD) - j)
             Wend
          End If
       End If
End Function

'���б�����ʾ�������Ƿ�����
Private Function BoolShowDrive(Object As Object, szDrive As String) As Boolean
'����:
'sDrive��ʾ����Ϣ
'Object�б��
'szDrive��������
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

'DOWORD������ֵ
Public Function dwUpdateKey(KeyRoot As Long, _
KeyName As String, SubKeyName As String, _
SubKeyValue As Long) As Boolean
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
                        0, REG_DWORD, _
                        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, lpAttr, _
                        hKey, hDepth)                   ' ����/��//KeyRoot//KeyName
    
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' ������...
    
    '------------------------------------------------------------
    '- ����/�޸Ĺؼ���ֵ...
    '------------------------------------------------------------
    ' ����/�޸Ĺؼ���ֵ
    rc = RegSetValueEx(hKey, SubKeyName, _
                       0, ENUM_REG_KEY_TYPE.REG_DWORD, _
                       SubKeyValue, 4)
                       
    If (rc <> ERROR_SUCCESS) Then GoTo CreateKeyError   ' ������
    '------------------------------------------------------------
    '- �ر�ע���ؼ���...
    '------------------------------------------------------------
    rc = RegCloseKey(hKey)                              ' �رչؼ���
    
    dwUpdateKey = True                                    ' ���سɹ�
    Exit Function                                       ' �˳�
CreateKeyError:
    dwUpdateKey = False                                  ' ���ô��󷵻ش���
    rc = RegCloseKey(hKey)                              ' ��ͼ�رչؼ���
End Function


