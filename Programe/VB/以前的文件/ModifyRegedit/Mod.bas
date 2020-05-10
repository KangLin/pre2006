Attribute VB_Name = "mmain"
Option Explicit

'����
Public frmMain As MDIForm1
'���ô���
Private Const GWL_STYLE = (-16)
Public Const WS_MAXIMIZEBOX = &H10000
Public Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long

'��ȡ����ϵͳ API ����������
Private Declare Sub GetSystemInfo Lib "kernel32" (lpSystemInfo As SYSTEM_INFO)
Private Declare Function GetVersionEx Lib "kernel32" Alias "GetVersionExA" (lpVersionInformation As OSVERSIONINFO) As Long
Private Type SYSTEM_INFO
        dwOemID As Long
        dwPageSize As Long
        lpMinimumApplicationAddress As Long
        lpMaximumApplicationAddress As Long
        dwActiveProcessorMask As Long
        dwNumberOrfProcessors As Long
        dwProcessorType As Long
        dwAllocationGranularity As Long
        dwReserved As Long
End Type
Private Type OSVERSIONINFO
        dwOSVersionInfoSize As Long   '����ϵͳ��Ϣ�ṹ�ĳ���
        dwMajorVersion As Long        '���汾��
        dwMinorVersion As Long        '�ΰ汾��
        dwBuildNumber As Long
        dwPlatformId As Long          '����ϵͳ
        szCSDVersion As String * 128  'Maintenance string for PSS usage;Ϊά�� PSS���������ַ���
End Type
Private Const VER_PLATFORM_WIN32_NT = 2
Private Const VER_PLATFORM_WIN32_WINDOWS = 1
Private Const VER_PLATFORM_WIN32s = 0
   
Public tySystemInformation As SYSTEM_INFO
Private Type typeMYVERSION
       lMajorVersion As Long  '���汾��
       lMinorVersion  As Long '�ΰ汾��
       lExtraInfo As Long     '����ϵͳ
       sOS As String          '����ϵͳ
       sOSVAll    As String   'ȫ��
       End Type
Public tyOSVersionInformation As typeMYVERSION
Public lOSInfo As Long '���ڼ��汾��Ϣ,�����Ƿ���Թ�

'���Ա�ʶ
Public Const Run = False

Public Enum Enum_PassStyle     '���봰������
            Enum_PassStyle_Add = 0
            Enum_PassStyle_AddWizard = 1
            Enum_PassStyle_Regedit = 2
            Enum_PassStyle_ModifyKeyList = 3
            Enum_PassStyle_OpenFile = 4
       End Enum

Public Enum Enum_PassLevel '���뼶��
            Enum_PassLevel_Null = 0
            Enum_passLevel_User = 1 '�û��������
            Enum_PassLevel_Manager = 2 '����
            End Enum
            
Public Enum Enum_WindowsStyle
       Windows_Desktop_Enum = 0      '��������Ϊ��������
       Windows_ControlPanel_Enum = 1 '.............�������
       Windows_Security_Enum = 2     '.............��ȫ
       End Enum

Public Enum Enum_Control '�ؼ�ö����
       Enum_Control_Only_Text = 0 'ֻ���ı��ؼ�
       Enum_Control_List = 1 '�б��ؼ�
       Enum_Control_FrameInput = 2 '��������ؼ�
       Enum_Control_DBGird = 3 '���ֵ������
       End Enum
       
Private Type typeTree '���Ľṹ
        '���������Ҫ�Ĳ���,����frmOption.SetTreeNode
        Ralation As String
        Key As String
        Text As String '��Ϊ����ı�ʶ
        '�ؼ���Ҫ�Ĳ���,����frmOption.Tree_NodeClick
        Control As Enum_Control
        PassLevel As Enum_PassLevel  '���İ�ȫ����
        KeyType As ENUM_REG_KEY_TYPE '��ֵ������
        StartPos As Long '��ֵ�ڵ���ʼλ��
        EndPos As Long '����ֵ�ڵĽ���λ��
        End Type
Public tTree() As typeTree

Private Type typeKey
        KeyRoot As Long    '����
        MainKey As String  '����
        SubKey As String   '�Ӽ�
        KeyVal As Variant  '��ֵ
        KeyType As Long    '������
        Readme As String   '˵��
        ControlText As String '�ؼ��е�˵������
        OperistSystem As Long '�˼�ֵ�����õĲ���ϵͳ
           '��32λ,����λ(0��2)�ֱ�Ϊ:WINDOWS95��WINDOWS98��WINDOWS2000��
           '      �����ı������Ժ�Ĳ���ϵͳ
        PassLevel As Enum_PassLevel  '��ȫ����
        End Type
Public tKeyVal() As typeKey '��ֵ������
'Public tKeyValAdd() As typeKey '�������Ӵ���

Public KeyFile As String '��ż�ֵ���ļ�,Ϊ��Ӧ�ó����ϵͳ�ļ�

Private Type typeModifyKey
        KeyRoot As Long    '����
        MainKey As String  '����
        SubKey As String   '�Ӽ�
        KeyVal As Variant  '��ֵ
        KeyType As Long    '������
        Readme As String   '˵��
        End Type
Public Key() As typeModifyKey 'Ҫ�޸ĵļ�ֵ������

Private Sub init()
    ReDim Key(0)
    '�Ӳ��Ҳ���ϵͳ
    tyOSVersionInformation = WindowsVersion()
    
    '��ʼ���ṹ����
    ReDim tTree(0)
    ReDim tTreeNode(0)
    ReDim tControl(0)
    ReDim tKeyVal(0)
    ReDim tKeyValAdd(0)
    
    '��ʼ����Ӧ�ó����ϵͳ�ļ�
    KeyFile = App.Path & "\�޸�ע���.dat"
    OpenKeyFile   '���ļ�
    
End Sub

Sub main()
Dim Style As Long
    init
    Set frmMain = New MDIForm1
    Style = GetWindowLong(frmMain.hwnd, GWL_STYLE)
    Style = Style Xor WS_MAXIMIZEBOX
    SetWindowLong frmMain.hwnd, GWL_STYLE, Style
    frmMain.Show
    
    If Not Run Then
       frmAdd.Show 1
    End If
    '��������֤
    
End Sub


'�õ��汾��Ϣ
Private Function WindowsVersion() As typeMYVERSION
Dim myOS As OSVERSIONINFO, WinVer As typeMYVERSION
Dim lResult As Long

    myOS.dwOSVersionInfoSize = Len(myOS)    'Ӧ���� 148
    
    lResult = GetVersionEx(myOS)
        
    '�������Ϣ����û�����
    WinVer.lMajorVersion = myOS.dwMajorVersion
    WinVer.lMinorVersion = myOS.dwMinorVersion
    '����ϵͳ��Ϣ��
        If WinVer.lMajorVersion = 4 Then
            If myOS.dwPlatformId = VER_PLATFORM_WIN32_NT Then
                WinVer.sOS = "Windows NT �汾 : "
            ElseIf myOS.dwPlatformId = VER_PLATFORM_WIN32_WINDOWS Then
                WinVer.sOS = "Windows 95 �汾 : "
            End If
        Else
            WinVer.sOS = "Windows �汾 : "
        End If
        WinVer.sOSVAll = WinVer.sOS & WinVer.lMajorVersion & "." & WinVer.lMinorVersion
    WindowsVersion = WinVer

End Function



'����
Public Function PassWord(sStyle As Enum_PassStyle) As Boolean
'�������������ȷ,�򷵻�True,����,����False
If Run Then
       Select Case sStyle
              Case Enum_PassStyle_Regedit
                   '�û���������ʱ����
                   '��������Ϊע���༭���Ƿ񱻹ر�
                   
              Case Enum_PassStyle_ModifyKeyList
                   '��Ϊ����Ա��
                   
              Case Enum_PassStyle_OpenFile
              
       End Select
Else '����
   PassWord = True
End If
End Function

Public Function AddToSameKey(KeyRoot As Long, _
     SubKey As String, MainKey As String, _
     KeyVal As Variant, Optional KeyType As ENUM_REG_KEY_TYPE = REG_BOOL, _
     Optional Readme As String = vbNullString)
'����:
'KeyRoot ����ֵ
'SubKey  �ӽ���
'MainKey ������
'KeyVal  ��ֵ
'KeyType ��ֵ����,ȱʡֵΪREG_BOOL=-1,��ʾ���ֵΪBooleanֵ
'Readme  ˵��
Dim i As Long, M As Long, vall As String
          M = UBound(Key)
          For i = 1 To M
              '�޸ĵļ�����Key��
              If SubKey = Key(i).SubKey Then
                 If MainKey = Key(i).MainKey And _
                    KeyRoot = Key(i).KeyRoot Then
                    If KeyType = REG_BOOL Then
                       If CBool(KeyVal) Then
                          Key(i).KeyVal = Key(i).KeyVal Or _
                          2 ^ (Asc(UCase(Left(Right$ _
                          (Readme, 3), 1))) - Asc(UCase("a")))
                          '��ΪBooleanʱ,��ֵΪ1
                       Else
                          Key(i).KeyVal = Key(i).KeyVal Xor _
                          2 ^ (Asc(UCase(Left(Right$ _
                          (Readme, 3), 1))) - Asc(UCase("a")))
                       End If
                    Else
                       Key(i).KeyVal = KeyVal
                    End If
                    Exit Function
                 End If
              End If
          Next i
          '�޸ĵļ�����Key��
          ReDim Preserve Key(M + 1)
          With Key(M + 1)
              .KeyRoot = KeyRoot
              .MainKey = MainKey
              .SubKey = SubKey
              vall = GetKeyValue(HKEY_CURRENT_USER, "Software\Microsoft\Windows\CurrentVersion\Policies\Explorer", "NoDrives")
              If KeyType = REG_BOOL Then
                 If CBool(KeyVal) Then
                    Key(i).KeyVal = CLng(vall) Or _
                     2 ^ (Asc(UCase(Left(Right$ _
                    (Readme, 3), 1))) - Asc(UCase("a")))
                    '��ΪBooleanʱ,��ֵΪ1
                 Else
                    Key(i).KeyVal = CLng(vall) And ( _
                    Not (CLng(0)) Xor 2 ^ _
                    (Asc(UCase(Left(Right$ _
                    (Readme, 3), 1))) - Asc(UCase("a"))))
                 End If
               Else
                 Key(i).KeyVal = KeyVal
               End If
              If KeyType = REG_BOOL Then
                 .KeyType = REG_DWORD
              Else
                 .KeyType = KeyType
              End If
              .Readme = Readme
          End With
End Function

'���޸Ĺ���ֵ���뵽�޸���Key��
Public Function AddToKey(KeyRoot As Long, _
     SubKey As String, MainKey As String, _
     KeyVal As Variant, Optional KeyType As ENUM_REG_KEY_TYPE = REG_BOOL, _
     Optional Readme As String = vbNullString)
'����:
'KeyRoot ����ֵ
'SubKey  �ӽ���
'MainKey ������
'KeyVal  ��ֵ
'KeyType ��ֵ����,ȱʡֵΪREG_BOOL=-1,��ʾ���ֵΪBooleanֵ
'Readme  ˵��
Dim i As Long, M As Long
          M = UBound(Key)
          For i = 1 To M
              '�޸ĵļ�����Key��
              If SubKey = Key(i).SubKey Then
                 If MainKey = Key(i).MainKey And _
                    KeyRoot = Key(i).KeyRoot Then
                    If KeyType = REG_BOOL Then
                       If CBool(KeyVal) Then
                          Key(i).KeyVal = 1 '��ΪBooleanʱ,��ֵΪ1
                       Else
                          Key(i).KeyVal = KeyVal
                       End If
                    Else
                       Key(i).KeyVal = KeyVal
                    End If
                    Exit Function
                 End If
              End If
          Next i
          '�޸ĵļ�����Key��
          ReDim Preserve Key(M + 1)
          With Key(M + 1)
              .KeyRoot = KeyRoot
              .MainKey = MainKey
              .SubKey = SubKey
              If KeyType = REG_BOOL Then
                 If CBool(KeyVal) Then
                    Key(i).KeyVal = 1 '��ΪBooleanʱ,��ֵΪ1
                 Else
                    Key(i).KeyVal = KeyVal
                 End If
              Else
                    Key(i).KeyVal = KeyVal
              End If
              If KeyType = REG_BOOL Then
                 .KeyType = REG_DWORD
              Else
                 .KeyType = KeyType
              End If
              .Readme = Readme
          End With
End Function

'�޸�ע���
Public Function ModifyKey()
If Run Then On Error Resume Next
Dim i As Long, sVal As String
      For i = 1 To UBound(Key)
          With Key(i)
               If .KeyType = REG_SZ Then
                  sVal = .KeyVal
                  szUpdateKey .KeyRoot, .MainKey, .SubKey, sVal
               ElseIf .KeyType = REG_DWORD Then
                  dwUpdateKey .KeyRoot, .MainKey, .SubKey, CLng(.KeyVal)
               End If
          End With
      Next i
End Function

'�ļ������������������Ϊ�򿪺ͱ����޸ĵļ�ֵ
Public Function OpenFile() As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, FileName As String, ss As String
Dim i As Long, n As Long
    If PassWord(Enum_PassStyle_OpenFile) Then
       With frmMain.CommD
            .FileName = ""
            .Filter = "*.da0|*.da0|*.*|*.*"
            .ShowOpen
            If .FileName = "" Then Exit Function
            FileName = .FileName
       End With
       Num = FreeFile
       Open FileName For Input As #Num
            Line Input #Num, ss
            If ss <> "�޸�ע���,�����:����" Then
               MsgBox "�ļ����Ͳ���", , App.FileDescription ' "�޸�ע���"
               OpenFile = False
               Exit Function
            End If
            Input #Num, ss '�汾��
            Input #Num, n
            ReDim Key(0)
            For i = 1 To n
                ReDim Preserve Key(i)
                With Key(i)
                     Input #Num, .KeyRoot
                     Input #Num, .MainKey
                     Input #Num, .SubKey
                     Input #Num, .KeyType
                     Input #Num, .KeyVal
                     Input #Num, .Readme
                End With
            Next i
       Close #Num
       OpenFile = True
    Else
       OpenFile = False
    End If
End Function

Public Sub SaveFile()
If Run Then On Error Resume Next
Dim Num As Integer, FileName As String
Dim i As Long, n As Long
       With frmMain.CommD
            .FileName = ""
            .Filter = "*.da0|*.da0|*.*|*.*"
            .ShowSave
            If .FileName = "" Then Exit Sub
            FileName = .FileName
       End With
       Num = FreeFile
       Open FileName For Output As #Num
            Print #Num, "�޸�ע���,�����:����"
            Print #Num, App.Major & "." & App.Minor '�汾��
            n = UBound(Key)
            Print #Num, n
            For i = 1 To n
                With Key(i)
                     Print #Num, .KeyRoot
                     Print #Num, .MainKey
                     Print #Num, .SubKey
                     Print #Num, .KeyType
                     Print #Num, .KeyVal
                     Print #Num, .Readme
                End With
            Next i
       Close #Num
End Sub

'������Ϊϵͳ�Ľṹ
Public Function OpenKeyFile(Optional boolFile As Boolean = False, Optional FileName As String = vbNullString) As Boolean
If Run Then On Error Resume Next
Dim Num As Integer, ss As String, i As Long, n As Long
       Num = FreeFile
       Open KeyFile For Input As #Num
            Line Input #Num, ss
            If ss <> "�޸�ע���,�����:����" Then
               MsgBox "�ļ����Ͳ���", , App.FileDescription ' "�޸�ע���"
               OpenKeyFile = False
               Exit Function
            End If
            Input #Num, ss '�汾��
            Input #Num, ss
            
            Line Input #Num, ss '����
            Line Input #Num, ss '����
            Line Input #Num, ss '����
            Line Input #Num, ss '����
            Line Input #Num, ss '����
            
            Input #Num, n
            ReDim tTree(n)
            For i = 1 To n
                With tTree(i)
                     Input #Num, .Ralation
                     Input #Num, .Key
                     Input #Num, .Text
                     Input #Num, .Control
                     Input #Num, .PassLevel
                     Input #Num, .KeyType
                     Input #Num, .StartPos
                     Input #Num, .EndPos
                End With
            Next i
            
            Input #Num, n
            ReDim tKeyVal(n)
            For i = 1 To n
                With tKeyVal(i)
                     Input #Num, .ControlText
                     Input #Num, .KeyRoot
                     Input #Num, .KeyType
                     Input #Num, .KeyVal
                     Input #Num, .MainKey
                     Input #Num, .OperistSystem
                     Input #Num, .PassLevel
                     Input #Num, .Readme
                     Input #Num, .SubKey
                End With
            Next i
       Close #Num
End Function

Public Sub SaveKeyFile(Optional boolFile As Boolean = False, Optional FileName As String = vbNullString)
If Run Then On Error Resume Next
Dim Num As Integer, i As Long, n As Long
       Num = FreeFile
       Open KeyFile For Output As #Num
            Print #Num, "�޸�ע���,�����:����"
            Print #Num, App.Major '���汾��
            Print #Num, App.Minor '�ΰ汾��
            
            Print #Num, "" '����
            Print #Num, ""
            Print #Num, ""
            Print #Num, ""
            Print #Num, ""
            
            n = UBound(tTree)
            Print #Num, n
            For i = 1 To n
                With tTree(i)
                     Print #Num, .Ralation
                     Print #Num, .Key
                     Print #Num, .Text
                     Print #Num, .Control
                     Print #Num, .PassLevel
                     Print #Num, .KeyType
                     Print #Num, .StartPos
                     Print #Num, .EndPos
                End With
            Next i
            
            n = UBound(tKeyVal)
            Print #Num, n
            For i = 1 To n
                With tKeyVal(i)
                     Print #Num, .ControlText
                     Print #Num, .KeyRoot
                     Print #Num, .KeyType
                     Print #Num, .KeyVal
                     Print #Num, .MainKey
                     Print #Num, .OperistSystem
                     Print #Num, .PassLevel
                     Print #Num, .Readme
                     Print #Num, .SubKey
                End With
            Next i
       Close #Num
End Sub


