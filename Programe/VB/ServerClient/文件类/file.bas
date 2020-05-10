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
'文件属性
Private Const FILE_ATTRIBUTE_ARCHIVE = &H20
Private Const FILE_ATTRIBUTE_COMPRESSED = &H800
Private Const FILE_ATTRIBUTE_DIRECTORY = &H10
Private Const FILE_ATTRIBUTE_HIDDEN = &H2
Private Const FILE_ATTRIBUTE_NORMAL = &H80
Private Const FILE_ATTRIBUTE_READONLY = &H1
Private Const FILE_ATTRIBUTE_SYSTEM = &H4
Private Const FILE_ATTRIBUTE_TEMPORARY = &H100

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
Private Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Private Declare Function GetLastError Lib "kernel32" () As Long

'驱动器类型(属性)
Private Const DRIVE_CDROM = 5            '光驱
Private Const DRIVE_FIXED = 3            '硬盘
Private Const DRIVE_RAMDISK = 6          '内存虚拟驱动器
Private Const DRIVE_REMOTE = 4           '网络驱动器
Private Const DRIVE_REMOVABLE = 2        '软驱

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
Private Declare Function GetLogicalDrives Lib "kernel32" () As Long

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
Private Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

'------------------------------------------------------------------------------------------
'功能：得到指定驱动器的类型（属性）
'参数:nDrive:指定的驱动器盘符.
'返回值:为驱动器的类型.
'------------------------------------------------------------------------------------------
Private Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long

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
'                      "\\?\C:\myworld\private" is seen as "C:\myworld\private",
'                      and "\\?\UNC\bill_g_1\hotstuff\coolapps" is seen as
'                      "\\bill_g_1\hotstuff\coolapps".
'                   Windows 95:
'                      The lpFileName string must not exceed MAX_PATH characters.
'                      Windows 95 does not support the "\\?\" prefix
'返回值：如果成功，则返回指定文件或目录的有效常数。
'        如果失败，则返0xFFFFFFFF。
'------------------------------------------------------------------------------------------
Private Declare Function GetFileAttributes Lib "kernel32" Alias "GetFileAttributesA" (ByVal lpFileName As String) As Long

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
Private Declare Function GetFileTitle Lib "comdlg32.dll" Alias "GetFileTitleA" (ByVal lpszFile As String, ByVal lpszTitle As String, ByVal cbBuf As Integer) As Integer
Private Declare Function GetFullPathName Lib "kernel32" Alias "GetFullPathNameA" (ByVal lpFileName As String, ByVal nBufferLength As Long, ByVal lpBuffer As String, ByVal lpFilePart As String) As Long

'==========================================================================================
'                事               件               声              明
'==========================================================================================
'------------------------------------------------------------------------------------------
'功能:此事件由函数FindAllFiles激活,通过它传递给用户需要的文件名,用户响应此事件完成指定的功能.
'参数:strFoundFileName:找到的文件名.
'     iFileCount:找到的文件个数.
'     bCancel:当用户不要再查找时,置为True,则函数FindAllFiles停止继续查找.
'用法:用户先把要查找的文件名作为函数FindAllFiles的参数,并调用它以激活此事件,然后再响应此事件
'     完成所要完成的任务.
'说明:此事件与函数FindAllFiles配套使用.
'------------------------------------------------------------------------------------------
Public Event fFoundFilesEvent(ByVal strFoundFileName As String, ByRef iFileCount As Integer, ByRef bCancel As Boolean)

'------------------------------------------------------------------------------------------
'功能:此事件由函数fGetLogicalDriveStrings()激活,通过它传递给用户要得到的当前系统有效的
'     驱动器字符,用户响应此事件完成指定的功能.
'参数:strDrive:当前系统有效驱动器字符,格式为:c:\
'说明:此事件与函数fGetLogicalDriveStrings()配套使用.
'------------------------------------------------------------------------------------------
Public Event fGetCurrentDriveEvent(ByVal strDrive As String)

'==========================================================================================

'示例1:是FindFirstFile()、FindNextFile()、FindClose()的示例
'-----------------------------------------------------------------------------
'功能：给定的文件的目录,则遍历给定的文件目录。
'参数: strDirNmae:给定的目录名
'      iFileCount:找到的文件数.
'      bCancel:传递给事件fFoundFiles,用于控制是否继续查对文件.
'用法:首先调用此过程,并响应fFoundFiles事件,在fFoundFiles事件中完成任务.
'说明:此函数激活fFoundFiles事件,并把得到的文件名传给此事件.
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
'功能:从给定的字符串中得到正确的文件名.
'------------------------------------------------------------------------------------------
Private Function GetRightFileName(sString As String) As String
GetRightFileName = Left(sString, InStr(1, sString, Chr(0)) - 1)
End Function

'------------------------------------------------------------------------------------------
'示例2.是API函数GetLogicalDriveStrings()的示例
'功能：得到当前系统的所有有效驱动器,并把它传给事件fGetCurrenDriveEvent(),
'      并激活此事件,
'说明: 用户只要调用用本过程,并在事件fGetCurrenDriveEvent()中完成指定的功能.
'------------------------------------------------------------------------------------------
Public Function fGetLogicalDriveStrings()
Dim lngSize As Long, lngMaxSize As Long, strDrives As String * 256
Dim iStartPos As Integer, iMidPos As Integer
Dim strSingleDrive As String, strDriveString As String
lngMaxSize = 256: iStartPos = 1: iMidPos = 0
    lngSize = GetLogicalDriveStrings(lngMaxSize, strDrives)
    If lngSize Then
       If lngSize < lngMaxSize Then '得到正确的当前系统的驱动器字符串
                                    '字符串的格式为: c:\<null>d:\<null><null>
                                    'lngSize不包括最后一个终结符(NULL)
          Do   '分离出单一的驱动器符，并传递给事件fGetCurrenDriveEvent()
            iMidPos = InStr(iStartPos, strDrives, Chr$(0))
            strDriveString = Mid(strDrives, iStartPos, iMidPos - (iStartPos))
            RaiseEvent fGetCurrentDriveEvent(strDriveString)
            iStartPos = iMidPos + 1
          Loop While iStartPos < lngSize
       Else '最大尺寸小于所需要的实际尺寸
       
            '修改最大尺寸值(lngMaxsize)
            
       End If
    Else '函数调用出错
        Err.Raise Description:="得到当前系统的有效驱动器-出错", Number:=GetLastError()
    End If
End Function

'------------------------------------------------------------------------------------------
'示例3.是API函数GetLogicalDriveStrings()的示例
'功能:返回给定带路径的文件名的文件名.
'参数:lpszFile:给定的带路径的文件名.
'返回值:分离出来的文件名.
'------------------------------------------------------------------------------------------
Public Function fGetFileTitle(ByVal strFileName As String) As String
Dim iLen As Integer, strFileTitle As String * 256
Dim iReturn As Integer
iLen = 256
iReturn = GetFileTitle(strFileName, strFileTitle, iLen)
If iReturn = 0 Then '成功,strFileTitle是以NULL("\0")结束的
   fGetFileTitle = Left(strFileTitle, InStr(1, strFileTitle, Chr$(0)))
ElseIf iReturn > 0 Then '原来的iLen小于lpszTitle所需要的大小
    iLen = iReturn
    strFileTitle = Space(iLen)
    iReturn = GetFileTitle(strFileName, strFileTitle, iLen)
    fGetFileTitle = Left(strFileTitle, InStr(1, strFileTitle, Chr$(0)))
Else 'lpszFile是不全的,则返回一个负数.
    Err.Raise Description:="文件名不全.", Number:=VbVarType.vbError + 8000
End If

End Function
