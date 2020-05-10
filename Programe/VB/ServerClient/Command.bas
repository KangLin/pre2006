Attribute VB_Name = "Command"
'*****************************************************************************
'       服           务          客          户       命          令
'                                设 计:  康 林
'*****************************************************************************
Option Explicit

'====================================================================================
'                  命                          令
'====================================================================================
'命令结构
'把命令转化为字符。Str (lngcommand)
'   例如：Str(lngCommand) & <NULL> &  sPara1 & <NULL>
'         & sPara2 & <NULL> & ……& <NULL><NULL>
'命令参数,各参数以一个<NULL>分开,以两个<NULL>结束

'功能：无命令
Public Const cCmdNull As Long = 0

'功能：取消正在进行的命令.
Public Const cCmdCancel As Long = cCmdNull

'功能:数据传送结束
Public Const cCmdDataSendEnd As Long = 1

'------------------------------------------------------------------------
'                   文        件        命         令
'------------------------------------------------------------------------
'功能：取得本地的所有驱动器。
'参数: 无参数。
'返回：本地的所有驱动器及其属性（类型），取驱动器类型常量一：。
'发送格式：<C:><NULL><D:><NULL><NULL>
'        盘符用一个<NULL>区分，以两个<NULL>结束。
'        仍以sckCmdServer发送。
'错误：没有逻辑驱动器（cNoLogicalDrives=10000）。
Public Const cCmdGetLogicalDrives As Long = 100
'没有逻辑驱动器
Public Const cCmdErrorNoLogicalDrives As Long = 10000

'功能：打开指定的目录，但不遍历其子目录。
'参数: 目录名。
'      客户端的IP地址
'      客户端的端口
'参数格式：<目录><NULL><客户端数据接收WinSock的IP地址><NULL> _
           <客户数据接收WinSock的端口><NULL><NULL>
'返回值: 所有目录和文件组合成的字符串。格式为:
'        <目录1><NULL><文件2><NULL>……<NULL><NULL>。
'        以一个vbNullChar分隔目录或文件，以两个vbNullChar作结束符。
'错误：1、目录名不存在(cCmdErrorNoDirectory)。
'2 、无返回值。
'发送:以sckDataServer发送。
Public Const cCmdOpenDirectory As Long = 101

'功能：遍历指定的目录。
'参数: 目录名。
'      客户端的IP地址
'      客户端的端口
'参数格式：<目录><NULL><客户端数据接收WinSock的IP地址><NULL> _
           <客户数据接收WinSock的端口><NULL><NULL>
'返回值: 所有目录和文件组合成的字符串。格式为:
'        <目录1><NULL><文件2><NULL>……<NULL><NULL>。
'        以一个vbNullChar分隔目录或文件，以两个vbNullChar作结束符。
'错误：1、目录名不存在(cCmdErrorNoDirectory)。
'2 、无返回值。
'发送:以sckDataServer发送。
Public Const cCmdTraverseDirectory As Long = 102

'功能：在指定的范围内查找指定的文件。
'参数：1、要查找的文件，包含通配符（*、？）。
'      2 、指定查找的范围。
'          A、 指定的目录。
'          B、 指定的驱动器。
'          C、 所有驱动器
'      3、客户端的IP地址
'      4 、 客户端的端口
'参数格式:<要查找的文件名><NULL><指定查找的范围><NULL> _
          <客户端数据接收WinSock的IP地址><NULL> _
          <客户端数据接收WinSock的端口><NULL><NULL>
'返回值:找到的所有路径的组合。格式为:
'       <目录1><NULL><目录2><NULL>……<NULL><NULL>。
'       以一个vbNullChar分隔目录，以两个vbNullChar作结束符。
'错误：1、目录名不存在。(cCmdErrorNoDirectory)
'      2 、无返回值。
'发送：1、以sckDataServer发送。
'      2、以sckCmdServer发送文件查找结束(cCmdFindFileEnd)和找到的个数
Public Const cCmdFindFile As Long = 103
'文件查找结束
Public Const cCmdFindFileEnd As Long = 104

'功能：结束目录操作
'发送结束
Public Const cCmdDirectoryEnd As Long = 105
'目录不存在
Public Const cCmdErrorNoDirectory As Long = 10001

