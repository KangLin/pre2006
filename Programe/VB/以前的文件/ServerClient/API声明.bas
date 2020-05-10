Attribute VB_Name = "API����"
'*****************************************************************************
'       ��           ��          ��          ��       API ����
'                                �� ��:  �� ��
'*****************************************************************************
Option Explicit

Public Const MAX_PATH = 260
Public Const INVALID_HANDLE_VALUE = -1
Public Type FILETIME
        dwLowDateTime As Long
        dwHighDateTime As Long
End Type
Public Type WIN32_FIND_DATA
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
Public Const FILE_ATTRIBUTE_ARCHIVE = &H20
Public Const FILE_ATTRIBUTE_COMPRESSED = &H800
Public Const FILE_ATTRIBUTE_DIRECTORY = &H10
Public Const FILE_ATTRIBUTE_HIDDEN = &H2
Public Const FILE_ATTRIBUTE_NORMAL = &H80
Public Const FILE_ATTRIBUTE_READONLY = &H1
Public Const FILE_ATTRIBUTE_SYSTEM = &H4
Public Const FILE_ATTRIBUTE_TEMPORARY = &H100

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
Public Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Public Declare Function GetLastError Lib "kernel32" () As Long

'����������(����)
Public Const DRIVE_CDROM = 5            '����
Public Const DRIVE_FIXED = 3            'Ӳ��
Public Const DRIVE_RAMDISK = 6          '�ڴ�����������
Public Const DRIVE_REMOTE = 4           '����������
Public Const DRIVE_REMOVABLE = 2        '����

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
Public Declare Function GetLogicalDrives Lib "kernel32" () As Long

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
Public Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

'------------------------------------------------------------------------------------------
'���ܣ��õ�ָ�������������ͣ����ԣ�
'����:nDrive:ָ�����������̷�.
'����ֵ:Ϊ������������.
'------------------------------------------------------------------------------------------
Public Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long

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
'                      "\\?\C:\myworld\public" is seen as "C:\myworld\public",
'                      and "\\?\UNC\bill_g_1\hotstuff\coolapps" is seen as
'                      "\\bill_g_1\hotstuff\coolapps".
'                   Windows 95:
'                      The lpFileName string must not exceed MAX_PATH characters.
'                      Windows 95 does not support the "\\?\" prefix
'����ֵ������ɹ����򷵻�ָ���ļ���Ŀ¼����Ч������
'        ���ʧ�ܣ���0xFFFFFFFF��
'------------------------------------------------------------------------------------------
Public Declare Function GetFileAttributes Lib "kernel32" Alias "GetFileAttributesA" (ByVal lpFileName As String) As Long

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
Public Declare Function GetFileTitle Lib "comdlg32.dll" Alias "GetFileTitleA" (ByVal lpszFile As String, ByVal lpszTitle As String, ByVal cbBuf As Integer) As Integer
Public Declare Function GetFullPathName Lib "kernel32" Alias "GetFullPathNameA" (ByVal lpFileName As String, ByVal nBufferLength As Long, ByVal lpBuffer As String, ByVal lpFilePart As String) As Long


