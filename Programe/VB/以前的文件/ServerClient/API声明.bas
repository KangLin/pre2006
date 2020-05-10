Attribute VB_Name = "API声明"
'*****************************************************************************
'       服           务          客          户       API 声明
'                                设 计:  康 林
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
'文件属性
Public Const FILE_ATTRIBUTE_ARCHIVE = &H20
Public Const FILE_ATTRIBUTE_COMPRESSED = &H800
Public Const FILE_ATTRIBUTE_DIRECTORY = &H10
Public Const FILE_ATTRIBUTE_HIDDEN = &H2
Public Const FILE_ATTRIBUTE_NORMAL = &H80
Public Const FILE_ATTRIBUTE_READONLY = &H1
Public Const FILE_ATTRIBUTE_SYSTEM = &H4
Public Const FILE_ATTRIBUTE_TEMPORARY = &H100

'------------------------------------------------------------------------------------------
'功能:查找给定的文件,(The FindFirstFile function searches a directory for
'     a file whose name matches the specified filename. FindFirstFile examines
'     subdirectory names as well as filenames.)
'参数:lpFileName:一个有效的目录、路径、文件名。可用"*"或"?"代替查找任意字符或单一字符.
'     lpFindFileData:Pointer to the WIN32_FIND_DATA structure that receives information
'                    about the found file or subdirectory. The structure can be used in
'                    subsequent calls to the FindNextFile or FindClose function to refer
'                    to the file or subdirectory.
'返回值:如果成功,返回值为一个后继调用FindNextFile()的句柄.
'       如果失败,则返回INVALID_HANDLE_VALUE.
'示例1:fFoundFilesEvent()
'------------------------------------------------------------------------------------------
Public Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Public Declare Function GetLastError Lib "kernel32" () As Long

'驱动器类型(属性)
Public Const DRIVE_CDROM = 5            '光驱
Public Const DRIVE_FIXED = 3            '硬盘
Public Const DRIVE_RAMDISK = 6          '内存虚拟驱动器
Public Const DRIVE_REMOTE = 4           '网络驱动器
Public Const DRIVE_REMOVABLE = 2        '软驱

'------------------------------------------------------------------------------------------
'功能：得到当前有效的逻辑驱动器的掩码.
'返回值:如果函数成功调用,则返回当前有效逻辑驱器的掩码.比特0位表示驱动器A:，
'       比特1位表示驱动器B:，比特2位表示驱动器C:，……
'         ……   4   3   2   1
'       ________________________
'       | …… | 1 | 1 | 1 | 1 |
'       ------------------------
'         ……   ^   ^   ^   ^
'         ……   |   |   |   |
'         ……   D:  C:  B:  A;
'------------------------------------------------------------------------------------------
Public Declare Function GetLogicalDrives Lib "kernel32" () As Long

'------------------------------------------------------------------------------------------
'功能:得到包含当前有效的逻辑驱动器的字符串.
'参数:nBufferLength:指定lpBuffer的最大尺寸.这个尺寸不包含终结符(NULL)"\0"
'     lpBuffer:接收当前系统的有效驱动器字符串,以两个终结符结束.驱动器符以一个终结符结束.
'             例如:c:\<null>d:\<null><null>
'返回值:如果调用失败,则返回0.
'       如果成功,则返回字符串的大小,不包括最后的终结符.
'       如果lpBuffer比所需的实际空间小,则返回比nBufferLength大的值,此值是所需要的实际尺寸.
'示例2: fGetLogicalDriveStrings()
'------------------------------------------------------------------------------------------
Public Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

'------------------------------------------------------------------------------------------
'功能：得到指定驱动器的类型（属性）
'参数:nDrive:指定的驱动器盘符.
'返回值:为驱动器的类型.
'------------------------------------------------------------------------------------------
Public Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long

'------------------------------------------------------------------------------------------
'功能：得到给定文件或目录的属性。
'参数： lpFileName：给定的文件或目录名。
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
'返回值：如果成功，则返回指定文件或目录的有效常数。
'        如果失败，则返0xFFFFFFFF。
'------------------------------------------------------------------------------------------
Public Declare Function GetFileAttributes Lib "kernel32" Alias "GetFileAttributesA" (ByVal lpFileName As String) As Long

'------------------------------------------------------------------------------------------
'功能:返回给定带路径的文件名的文件名.
'参数:lpszFile:给定的带路径的文件名.
'     lpszTitle:分离出来的文件名.以NULL("\0")结束.
'     cbBuf:用以指定lpszTitle的尺寸.
'返回值:如果成功,则返回0.
'       如果lpszFile是不全的,则返回一个负数.
'       如果cbBuf太小,则返回lpszTitle所需要的实际值.
'示例3:fGetFileTitle()
'------------------------------------------------------------------------------------------
Public Declare Function GetFileTitle Lib "comdlg32.dll" Alias "GetFileTitleA" (ByVal lpszFile As String, ByVal lpszTitle As String, ByVal cbBuf As Integer) As Integer
Public Declare Function GetFullPathName Lib "kernel32" Alias "GetFullPathNameA" (ByVal lpFileName As String, ByVal nBufferLength As Long, ByVal lpBuffer As String, ByVal lpFilePart As String) As Long


