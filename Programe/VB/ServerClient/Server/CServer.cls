VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CServer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
'*****************************************************************************
'                    服           务          端           类
'                                设 计:  康 林
'*****************************************************************************
Option Explicit

Dim lngCurrentCommand As Long '存放当前命令
Dim bCommandCancel As Boolean '用于取消当前命令的执行

'保持属性值的局部变量
Private m_sckDataServer As Winsock '局部复制
Public Property Set sckDataServer(ByVal vData As Winsock)
'向属性指派对象时使用，位于 Set 语句的左边。
'Syntax: Set x.sckDataServer = Form1
    Set m_sckDataServer = vData
End Property

Public Property Get sckDataServer() As Winsock
'检索属性值时使用，位于赋值语句的右边。
'Syntax: Debug.Print X.sckDataServer
    Set sckDataServer = m_sckDataServer
End Property

'-------------------------------------------------------------------------------
'功能：命令处理函数。
'参数:sckCmdServer:接收命令的WinSock.
'     bytesTotal:接收的总的字节数.
'-------------------------------------------------------------------------------
Public Function fCommmand(sckCmdServer As Winsock, ByVal bytesTotal As Long)
Dim lngCommand As Long, sPara As String, sGetString As String
bCommandCancel = False '初始化取消变量
sckCmdServer.GetData sGetString
lngCommand = CLng(Val(fSplitString(sGetString)))
If lngCurrentCommand <> cCmdNull And lngCommand <> cCmdCancel Then
   Exit Function
Else
   lngCurrentCommand = lngCommand
End If
Select Case lngCommand
       Case cCmdCancel '取消正在执行的命令
            bCommandCancel = True
       Case cCmdGetLogicalDrives '得到本地的所有驱动器
            Call fGetLogicalDrives(sckCmdServer)
       Case cCmdOpenDirectory '打开指定的目录,不遍历其子目录
            Call fDirectory(sckCmdServer, sGetString, False)
       Case cCmdTraverseDirectory '遍历指定的目录
            Call fDirectory(sckCmdServer, sGetString)
       Case cCmdFindFile '在指定的范围内查找指定的文件。
            Call fFindFile(sckCmdServer, sGetString)
                        
End Select
lngCurrentCommand = cCmdNull '命令执行结束
End Function

'-------------------------------------------------------------------------------
'功能：得到本地逻辑驱动器.并以格式:
'发送格式：<C:><NULL><驱动器属性><D:><NULL><驱动器属性><NULL><NULL>
'          盘符与属性之间用一个<NULL>区分，以两个<NULL>结束。
'          仍以sckCmdServer发送。
'参数:sckCmdServer:接收命令的WinSock.
Private Function fGetLogicalDrives(sckCmdServer As Winsock) As Long
Dim lngSize As Long, lngMaxSize As Long, strDrives As String * 256
Dim iStartPos As Integer, iMidPos As Integer
Dim strSingleDrive As String, strDriveString As String
Dim sSendFormat As String, lngDriveProper As Long

    lngMaxSize = 256: iStartPos = 1: iMidPos = 0: sSendFormat = vbNullString
    '得到本地逻辑驱动器
    lngSize = GetLogicalDriveStrings(lngMaxSize, strDrives)
    If lngSize Then
       If lngSize < lngMaxSize Then '得到正确的当前系统的驱动器字符串
                                    '字符串的格式为: c:\<null>d:\<null><null>
                                    'lngSize不包括最后一个终结符(NULL)
          Do   '分离出单一的驱动器符，并传递给事件fGetCurrenDriveEvent()
            iMidPos = InStr(iStartPos, strDrives, Chr$(0))
            strDriveString = vbNullString
            strDriveString = Mid(strDrives, iStartPos, iMidPos - (iStartPos))
            strDriveString = Trim(strDriveString) & Chr$(0)
            '把驱动器字符放入发送格式中
            sSendFormat = sSendFormat & strDriveString
            '得到本驱动器的属性
            lngDriveProper = GetDriveType(Trim$(strDriveString))
            sSendFormat = sSendFormat & Str(lngDriveProper) & Chr$(0)
            
            iStartPos = iMidPos + 1
          Loop While iStartPos < lngSize
          'fGetLogicalDriveStrings = 0
       Else '最大尺寸小于所需要的实际尺寸
       
            '修改最大尺寸值(lngMaxsize)
            
       End If
    Else '函数调用出错
        fGetLogicalDrives = GetLastError()
    End If
          
    '发送:
    '加入结束符<NULL><NULL>
    sSendFormat = sSendFormat & Chr$(0)
    sckCmdServer.SendData sSendFormat
End Function

'-------------------------------------------------------------------------------
'功能：遍历指定的目录.并以格式:
'      <目录1><NULL><文件2><NULL>……<NULL><NULL>。
'      以一个vbNullChar分隔目录或文件，以两个vbNullChar作结束符。
'参数: sckCmdServer:命令发送Winsock
'      sPara:指定的目录、数据发送到的IP地址和端口.
'        <目录><NULL><IP><NULL><Port><NULL><NULL>
'      bTraverseDirectory:是否遍历其子目录
'返回值: 所有目录和文件组合成的字符串。格式为:
'        <目录1><NULL><文件2><NULL>……<NULL><NULL>。
'        以一个vbNullChar分隔目录或文件，以两个vbNullChar作结束符。
'错误：1、目录名不存在(cCmdErrorNoDirectory)。
'      2 、无返回值。
'发送:以sckDataServer发送。
Private Function fDirectory(ByVal sckCmdServer As Winsock, _
        ByVal sPara As String, _
        Optional bTraverseDirectory As Boolean = True)
Dim sRemoteHost As String, lngRemotePort As Long, iFileTotle As Integer
Dim sDirectoryName As String
iFileTotle = 0
sDirectoryName = fSplitString(sPara) '得到指定的目录
If sDirectoryName = vbNullString Then
   Exit Function
End If
If ((GetFileAttributes(sDirectoryName) And FILE_ATTRIBUTE_DIRECTORY) _
   <> FILE_ATTRIBUTE_DIRECTORY) Or (GetFileAttributes(sDirectoryName) _
   = INVALID_HANDLE_VALUE) Then
   'A、如果给定的不是目录，返回错误cCmdErrorNoDirectory
   sckCmdServer.SendData Str(cCmdErrorNoDirectory) & vbNullChar & vbNullChar
   Exit Function
End If
sRemoteHost = fSplitString(sPara) 'B、得到接收数据WinSock的IP地址
lngRemotePort = CLng(Val(fSplitString(sPara))) 'B、得到接收数据WinSock的端口
With m_sckDataServer 'C、联接接收数据Winsock
     .RemoteHost = sRemoteHost
     .RemotePort = lngRemotePort
     .Connect
     While (.State <> sckConnected)
            DoEvents
     Wend
End With
'D、遍历指定目录（FindAllFiles），并在FindAllFiles通过sckDataServer发送查到的目录。
Call FindAllFiles(sDirectoryName & "\", iFileTotle, bCommandCancel, bTraverseDirectory)
m_sckDataServer.SendData vbNullChar 'E、发送结束符
m_sckDataServer.Close  'F、关闭联接
'G、发送数据传送结束命令(cCmdDirectoryEnd)和得到文件的总个数
sckCmdServer.SendData Trim(Str(cCmdDirectoryEnd)) & vbNullChar & Trim(iFileTotle) & vbNullChar & vbNullChar
End Function

'示例1:是FindFirstFile()、FindNextFile()、FindClose()的示例
'-----------------------------------------------------------------------------
'功能：给定的文件的目录,则遍历给定的文件目录。
'参数: strDirNmae:给定的目录名
'      iFileCount:找到的文件数.
'      bCancel:传递给事件fFoundFiles,用于控制是否继续查对文件.
'-----------------------------------------------------------------------------
Private Function FindAllFiles(ByVal strDirName As String, Optional iFileCount As Integer = 0, _
Optional bCancel As Boolean = False, Optional bTraverseDirectory As Boolean = True) As Long
Dim hFind As Long, WFD As WIN32_FIND_DATA
Dim strText As String

strText = strDirName + "*"
hFind = FindFirstFile(strText, WFD) '得到第一个文件
If (hFind <> INVALID_HANDLE_VALUE) Then
   Do
     iFileCount = iFileCount + 1
     m_sckDataServer.SendData strDirName & GetRightFileName(WFD.cFileName) _
                              & vbNullChar
     DoEvents '允许调用其它线程
     If bCancel Then Exit Function
     If bTraverseDirectory Then
        If Not (GetRightFileName(WFD.cFileName) = "." Or _
           GetRightFileName(WFD.cFileName) = "..") _
           And (WFD.dwFileAttributes And FILE_ATTRIBUTE_DIRECTORY) Then
           strText = strDirName + GetRightFileName(WFD.cFileName) + "\"
           Call FindAllFiles(strText, iFileCount, bCancel)
        End If
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

'功能：在指定的范围内查找指定的文件。并以格式:
'      <目录1><NULL><目录2><NULL>……<NULL><NULL>
'      以一个vbNullChar分隔目录或文件，以两个vbNullChar作结束符。
'参数: sckCmdServer:命令发送Winsock
'      sPara:包括指定目录和要查找的文件名、数据发送到的IP地址
'            和端口.<IP><NULL><Port><NULL><NULL>
'返回值: 所有目录和文件组合成的字符串。格式为:
'        <目录1><NULL><目录2><NULL>……<NULL><NULL>。
'        以一个vbNullChar分隔目录或文件，以两个vbNullChar作结束符。
'错误：1、目录名不存在(cCmdErrorNoDirectory)。
'      2 、无返回值。
'发送:以sckDataServer发送。
Private Function fFindFile(ByVal sckCmdServer As Winsock, _
        ByVal sPara As String)
Dim sDirectory As String, sFile As String
Dim hFind As Long, WFD As WIN32_FIND_DATA
Dim strText As String, iFileCount As Integer
iFileCount = 0
'A、分离出参数中的要查找的文件名
sFile = fSplitString(sPara)
If sFile = vbNullChar Then Exit Function
'B、分离出参数中指定的目录名
sDirectory = fSplitString(sPara)
If ((GetFileAttributes(sDirectory) And FILE_ATTRIBUTE_DIRECTORY) _
   <> FILE_ATTRIBUTE_DIRECTORY) Or (GetFileAttributes(sDirectory) _
   = INVALID_HANDLE_VALUE Or sDirectory = vbNullString) Then
   '如果给定的不是目录，返回错误cCmdErrorNoDirectory
   sckCmdServer.SendData Str(cCmdErrorNoDirectory) & vbNullChar & vbNullChar
   Exit Function
End If
'C、联接接收数据Winsock
With m_sckDataServer
     .RemoteHost = fSplitString(sPara) '得到接收数据WinSock的IP地址
     .RemotePort = CLng(Val(fSplitString(sPara)))  '得到接收数据WinSock的端口
     .Connect
     While (.State <> sckConnected)
            DoEvents
     Wend
End With
'D、查找指定的文件,并通过sckDataSever发送查到的目录
Call fFindFileDirectory(sDirectory & "\", sFile, iFileCount, bCommandCancel)
m_sckDataServer.SendData vbNullChar 'E、发送结束符
m_sckDataServer.Close  'F、关闭联接
'G、发送数据传送结束命令(cCmdDirectoryEnd)和得到文件的总个数
sckCmdServer.SendData Trim(Str(cCmdFindFileEnd)) & vbNullChar & Trim(iFileCount) & vbNullChar & vbNullChar
End Function

'参数: strDirNmae:给定的目录名
'      sFileName:要查找的文件名
'      iFileCount:找到的文件数.
'      bCancel:传递给事件fFoundFiles,用于控制是否继续查对文件.
'-----------------------------------------------------------------------------
Private Function fFindFileDirectory(ByVal strDirName As String, _
ByVal sFileName As String, Optional iFileCount As Integer = 0, _
Optional bCancel As Boolean = False) As Long
Dim hFind As Long, WFD As WIN32_FIND_DATA
Dim strText As String

strText = strDirName + "*"
hFind = FindFirstFile(strText, WFD) '得到第一个文件
If (hFind <> INVALID_HANDLE_VALUE) Then
   Do
     If UCase(GetRightFileName(WFD.cFileName)) Like UCase(sFileName) Then
        iFileCount = iFileCount + 1
        m_sckDataServer.SendData strDirName & GetRightFileName(WFD.cFileName) _
                              & vbNullChar
     End If
     DoEvents '允许调用其它线程
     If bCancel Then Exit Function
     If Not (GetRightFileName(WFD.cFileName) = "." Or _
        GetRightFileName(WFD.cFileName) = "..") _
        And (WFD.dwFileAttributes And FILE_ATTRIBUTE_DIRECTORY) Then
           strText = strDirName + GetRightFileName(WFD.cFileName) + "\"
           Call fFindFileDirectory(strText, sFileName, iFileCount, bCancel)
     End If
   Loop While (FindNextFile(hFind, WFD))
   FindClose (hFind)
End If
End Function


