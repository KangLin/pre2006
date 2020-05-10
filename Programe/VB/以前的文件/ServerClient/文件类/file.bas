VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CFile1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Const MAX_PATH = 260
Private Const INVALID_HANDLE_VALUE = -1
Private Type FILETIME
        dwLowDateTime As Long
        dwHighDateTime As Long
End Type
Private Type WIN32_FIND_DATA
        dwFileAttributes As Long
        ftCreationTime As FILETIME
        ftLastAccessTime As FILETIME
        ftLastWriteTime As FILETIME
        nFileSizeHigh As Long
        nFileSizeLow As Long
        dwReserved0 As Long
        dwReserved1 As Long
        cFileName As String * MAX_PATH
        cAlternate As String * 14
End Type
'�ļ�����
Private Const FILE_ATTRIBUTE_ARCHIVE = &H20
Private Const FILE_ATTRIBUTE_COMPRESSED = &H800
Private Const FILE_ATTRIBUTE_DIRECTORY = &H10
Private Const FILE_ATTRIBUTE_HIDDEN = &H2
Private Const FILE_ATTRIBUTE_NORMAL = &H80
Private Const FILE_ATTRIBUTE_READONLY = &H1
Private Const FILE_ATTRIBUTE_SYSTEM = &H4
Private Const FILE_ATTRIBUTE_TEMPORARY = &H100

'------------------------------------------------------------------------------------------
'����:���Ҹ������ļ�,(The FindFirstFile function searches a directory for
'     a file whose name matches the specified filename. FindFirstFile examines
'     subdirectory names as well as filenames.)
'����:lpFileName:һ����Ч��Ŀ¼��·�����ļ���������"*"��"?"������������ַ���һ�ַ�.
'     lpFindFileData:Pointer to the WIN32_FIND_DATA structure that receives information
'                    about the found file or subdirectory. The structure can be used in
'                    subsequent calls to the FindNextFile or FindClose function to refer
'                    to the file or subdirectory.
'����ֵ:����ɹ�,����ֵΪһ����̵���FindNextFile()�ľ��.
'       ���ʧ��,�򷵻�INVALID_HANDLE_VALUE.
'ʾ��1:fFoundFilesEvent()
'------------------------------------------------------------------------------------------
Private Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Private Declare Function GetLastError Lib "kernel32" () As Long

'����������(����)
Private Const DRIVE_CDROM = 5            '����
Private Const DRIVE_FIXED = 3            'Ӳ��
Private Const DRIVE_RAMDISK = 6          '�ڴ�����������
Private Const DRIVE_REMOTE = 4           '����������
Private Const DRIVE_REMOVABLE = 2        '����

'------------------------------------------------------------------------------------------
'���ܣ��õ���ǰ��Ч���߼�������������.
'����ֵ:��������ɹ�����,�򷵻ص�ǰ��Ч�߼�����������.����0λ��ʾ������A:��
'       ����1λ��ʾ������B:������2λ��ʾ������C:������
'         ����   4   3   2   1
'       ________________________
'       | ���� | 1 | 1 | 1 | 1 |
'       ------------------------
'         ����   ^   ^   ^   ^
'         ����   |   |   |   |
'         ����   D:  C:  B:  A;
'------------------------------------------------------------------------------------------
Private Declare Function GetLogicalDrives Lib "kernel32" () As Long

'------------------------------------------------------------------------------------------
'����:�õ�������ǰ��Ч���߼����������ַ���.
'����:nBufferLength:ָ��lpBuffer�����ߴ�.����ߴ粻�����ս��(NULL)"\0"
'     lpBuffer:���յ�ǰϵͳ����Ч�������ַ���,�������ս������.����������һ���ս������.
'             ����:c:\<null>d:\<null><null>
'����ֵ:�������ʧ��,�򷵻�0.
'       ����ɹ�,�򷵻��ַ����Ĵ�С,�����������ս��.
'       ���lpBuffer�������ʵ�ʿռ�С,�򷵻ر�nBufferLength���ֵ,��ֵ������Ҫ��ʵ�ʳߴ�.
'ʾ��2: fGetLogicalDriveStrings()
'------------------------------------------------------------------------------------------
Private Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

'------------------------------------------------------------------------------------------
'���ܣ��õ�ָ�������������ͣ����ԣ�
'����:nDrive:ָ�����������̷�.
'����ֵ:Ϊ������������.
'------------------------------------------------------------------------------------------
Private Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long

'------------------------------------------------------------------------------------------
'���ܣ��õ������ļ���Ŀ¼�����ԡ�
'������ lpFileName���������ļ���Ŀ¼����
'                   Windows NT:
'                      There is a default string size limit for paths of MAX_PATH
'                      characters. This limit is related to how the GetFileAttributes
'                      function parses paths. An application can transcend this limit
'                      and send in paths longer than MAX_PATH characters by calling
'                      the wide (W) version of GetFileAttributes and prepending "\\?\"
'                      to the path. The "\\?\" tells the function to turn off path
'                      parsing; it lets paths longer than MAX_PATH be used with
'                      GetFileAttributesW. However, each component in the path cannot
'                      be more than MAX_PATH characters long. This also works with UNC
'                      names. The "\\?\" is ignored as part of the path. For example,
'                      "\\?\C:\myworld\private" is seen as "C:\myworld\private",
'                      and "\\?\UNC\bill_g_1\hotstuff\coolapps" is seen as
'                      "\\bill_g_1\hotstuff\coolapps".
'                   Windows 95:
'                      The lpFileName string must not exceed MAX_PATH characters.
'                      Windows 95 does not support the "\\?\" prefix
'����ֵ������ɹ����򷵻�ָ���ļ���Ŀ¼����Ч������
'        ���ʧ�ܣ���0xFFFFFFFF��
'------------------------------------------------------------------------------------------
Private Declare Function GetFileAttributes Lib "kernel32" Alias "GetFileAttributesA" (ByVal lpFileName As String) As Long

'------------------------------------------------------------------------------------------
'����:���ظ�����·�����ļ������ļ���.
'����:lpszFile:�����Ĵ�·�����ļ���.
'     lpszTitle:����������ļ���.��NULL("\0")����.
'     cbBuf:����ָ��lpszTitle�ĳߴ�.
'����ֵ:����ɹ�,�򷵻�0.
'       ���lpszFile�ǲ�ȫ��,�򷵻�һ������.
'       ���cbBuf̫С,�򷵻�lpszTitle����Ҫ��ʵ��ֵ.
'ʾ��3:fGetFileTitle()
'------------------------------------------------------------------------------------------
Private Declare Function GetFileTitle Lib "comdlg32.dll" Alias "GetFileTitleA" (ByVal lpszFile As String, ByVal lpszTitle As String, ByVal cbBuf As Integer) As Integer
Private Declare Function GetFullPathName Lib "kernel32" Alias "GetFullPathNameA" (ByVal lpFileName As String, ByVal nBufferLength As Long, ByVal lpBuffer As String, ByVal lpFilePart As String) As Long

'==========================================================================================
'                ��               ��               ��              ��
'==========================================================================================
'------------------------------------------------------------------------------------------
'����:���¼��ɺ���FindAllFiles����,ͨ�������ݸ��û���Ҫ���ļ���,�û���Ӧ���¼����ָ���Ĺ���.
'����:strFoundFileName:�ҵ����ļ���.
'     iFileCount:�ҵ����ļ�����.
'     bCancel:���û���Ҫ�ٲ���ʱ,��ΪTrue,����FindAllFilesֹͣ��������.
'�÷�:�û��Ȱ�Ҫ���ҵ��ļ�����Ϊ����FindAllFiles�Ĳ���,���������Լ�����¼�,Ȼ������Ӧ���¼�
'     �����Ҫ��ɵ�����.
'˵��:���¼��뺯��FindAllFiles����ʹ��.
'------------------------------------------------------------------------------------------
Public Event fFoundFilesEvent(ByVal strFoundFileName As String, ByRef iFileCount As Integer, ByRef bCancel As Boolean)

'------------------------------------------------------------------------------------------
'����:���¼��ɺ���fGetLogicalDriveStrings()����,ͨ�������ݸ��û�Ҫ�õ��ĵ�ǰϵͳ��Ч��
'     �������ַ�,�û���Ӧ���¼����ָ���Ĺ���.
'����:strDrive:��ǰϵͳ��Ч�������ַ�,��ʽΪ:c:\
'˵��:���¼��뺯��fGetLogicalDriveStrings()����ʹ��.
'------------------------------------------------------------------------------------------
Public Event fGetCurrentDriveEvent(ByVal strDrive As String)

'==========================================================================================

'ʾ��1:��FindFirstFile()��FindNextFile()��FindClose()��ʾ��
'-----------------------------------------------------------------------------
'���ܣ��������ļ���Ŀ¼,������������ļ�Ŀ¼��
'����: strDirNmae:������Ŀ¼��
'      iFileCount:�ҵ����ļ���.
'      bCancel:���ݸ��¼�fFoundFiles,���ڿ����Ƿ��������ļ�.
'�÷�:���ȵ��ô˹���,����ӦfFoundFiles�¼�,��fFoundFiles�¼����������.
'˵��:�˺�������fFoundFiles�¼�,���ѵõ����ļ����������¼�.
'-----------------------------------------------------------------------------
Public Function FindAllFiles(ByVal strDirName As String, Optional iFileCount As Integer = 0, _
  Optional bCancel As Boolean = False) As Long
Dim hFind As Long, WFD As WIN32_FIND_DATA
Dim strText As String

strText = strDirName + "*"
hFind = FindFirstFile(strText, WFD)
If (hFind <> INVALID_HANDLE_VALUE) Then
   Do
     'Debug.Print DirName + GetRightFileName(WFD.cFileName)
     iFileCount = iFileCount + 1
     RaiseEvent fFoundFilesEvent(strDirName & GetRightFileName(WFD.cFileName), iFileCount, bCancel)
     If bCancel Then Exit Function
     If Not (GetRightFileName(WFD.cFileName) = "." Or GetRightFileName(WFD.cFileName) = "..") _
       And (WFD.dwFileAttributes And FILE_ATTRIBUTE_DIRECTORY) Then
        strText = strDirName + GetRightFileName(WFD.cFileName) + "\"
        Call FindAllFiles(strText, iFileCount, bCancel)
     End If
   Loop While (FindNextFile(hFind, WFD))
   FindClose (hFind)
End If
End Function

'------------------------------------------------------------------------------------------
'����:�Ӹ������ַ����еõ���ȷ���ļ���.
'------------------------------------------------------------------------------------------
Private Function GetRightFileName(sString As String) As String
GetRightFileName = Left(sString, InStr(1, sString, Chr(0)) - 1)
End Function

'------------------------------------------------------------------------------------------
'ʾ��2.��API����GetLogicalDriveStrings()��ʾ��
'���ܣ��õ���ǰϵͳ��������Ч������,�����������¼�fGetCurrenDriveEvent(),
'      ��������¼�,
'˵��: �û�ֻҪ�����ñ�����,�����¼�fGetCurrenDriveEvent()�����ָ���Ĺ���.
'------------------------------------------------------------------------------------------
Public Function fGetLogicalDriveStrings()
Dim lngSize As Long, lngMaxSize As Long, strDrives As String * 256
Dim iStartPos As Integer, iMidPos As Integer
Dim strSingleDrive As String, strDriveString As String
lngMaxSize = 256: iStartPos = 1: iMidPos = 0
    lngSize = GetLogicalDriveStrings(lngMaxSize, strDrives)
    If lngSize Then
       If lngSize < lngMaxSize Then '�õ���ȷ�ĵ�ǰϵͳ���������ַ���
                                    '�ַ����ĸ�ʽΪ: c:\<null>d:\<null><null>
                                    'lngSize���������һ���ս��(NULL)
          Do   '�������һ�����������������ݸ��¼�fGetCurrenDriveEvent()
            iMidPos = InStr(iStartPos, strDrives, Chr$(0))
            strDriveString = Mid(strDrives, iStartPos, iMidPos - (iStartPos))
            RaiseEvent fGetCurrentDriveEvent(strDriveString)
            iStartPos = iMidPos + 1
          Loop While iStartPos < lngSize
       Else '���ߴ�С������Ҫ��ʵ�ʳߴ�
       
            '�޸����ߴ�ֵ(lngMaxsize)
            
       End If
    Else '�������ó���
        Err.Raise Description:="�õ���ǰϵͳ����Ч������-����", Number:=GetLastError()
    End If
End Function

'------------------------------------------------------------------------------------------
'ʾ��3.��API����GetLogicalDriveStrings()��ʾ��
'����:���ظ�����·�����ļ������ļ���.
'����:lpszFile:�����Ĵ�·�����ļ���.
'����ֵ:����������ļ���.
'------------------------------------------------------------------------------------------
Public Function fGetFileTitle(ByVal strFileName As String) As String
Dim iLen As Integer, strFileTitle As String * 256
Dim iReturn As Integer
iLen = 256
iReturn = GetFileTitle(strFileName, strFileTitle, iLen)
If iReturn = 0 Then '�ɹ�,strFileTitle����NULL("\0")������
   fGetFileTitle = Left(strFileTitle, InStr(1, strFileTitle, Chr$(0)))
ElseIf iReturn > 0 Then 'ԭ����iLenС��lpszTitle����Ҫ�Ĵ�С
    iLen = iReturn
    strFileTitle = Space(iLen)
    iReturn = GetFileTitle(strFileName, strFileTitle, iLen)
    fGetFileTitle = Left(strFileTitle, InStr(1, strFileTitle, Chr$(0)))
Else 'lpszFile�ǲ�ȫ��,�򷵻�һ������.
    Err.Raise Description:="�ļ�����ȫ.", Number:=VbVarType.vbError + 8000
End If

End Function
