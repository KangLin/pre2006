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
'                    ��           ��          ��           ��
'                                �� ��:  �� ��
'*****************************************************************************
Option Explicit

Dim lngCurrentCommand As Long '��ŵ�ǰ����
Dim bCommandCancel As Boolean '����ȡ����ǰ�����ִ��

'��������ֵ�ľֲ�����
Private m_sckDataServer As Winsock '�ֲ�����
Public Property Set sckDataServer(ByVal vData As Winsock)
'������ָ�ɶ���ʱʹ�ã�λ�� Set ������ߡ�
'Syntax: Set x.sckDataServer = Form1
    Set m_sckDataServer = vData
End Property

Public Property Get sckDataServer() As Winsock
'��������ֵʱʹ�ã�λ�ڸ�ֵ�����ұߡ�
'Syntax: Debug.Print X.sckDataServer
    Set sckDataServer = m_sckDataServer
End Property

'-------------------------------------------------------------------------------
'���ܣ������������
'����:sckCmdServer:���������WinSock.
'     bytesTotal:���յ��ܵ��ֽ���.
'-------------------------------------------------------------------------------
Public Function fCommmand(sckCmdServer As Winsock, ByVal bytesTotal As Long)
Dim lngCommand As Long, sPara As String, sGetString As String
bCommandCancel = False '��ʼ��ȡ������
sckCmdServer.GetData sGetString
lngCommand = CLng(Val(fSplitString(sGetString)))
If lngCurrentCommand <> cCmdNull And lngCommand <> cCmdCancel Then
   Exit Function
Else
   lngCurrentCommand = lngCommand
End If
Select Case lngCommand
       Case cCmdCancel 'ȡ������ִ�е�����
            bCommandCancel = True
       Case cCmdGetLogicalDrives '�õ����ص�����������
            Call fGetLogicalDrives(sckCmdServer)
       Case cCmdOpenDirectory '��ָ����Ŀ¼,����������Ŀ¼
            Call fDirectory(sckCmdServer, sGetString, False)
       Case cCmdTraverseDirectory '����ָ����Ŀ¼
            Call fDirectory(sckCmdServer, sGetString)
       Case cCmdFindFile '��ָ���ķ�Χ�ڲ���ָ�����ļ���
            Call fFindFile(sckCmdServer, sGetString)
                        
End Select
lngCurrentCommand = cCmdNull '����ִ�н���
End Function

'-------------------------------------------------------------------------------
'���ܣ��õ������߼�������.���Ը�ʽ:
'���͸�ʽ��<C:><NULL><����������><D:><NULL><����������><NULL><NULL>
'          �̷�������֮����һ��<NULL>���֣�������<NULL>������
'          ����sckCmdServer���͡�
'����:sckCmdServer:���������WinSock.
Private Function fGetLogicalDrives(sckCmdServer As Winsock) As Long
Dim lngSize As Long, lngMaxSize As Long, strDrives As String * 256
Dim iStartPos As Integer, iMidPos As Integer
Dim strSingleDrive As String, strDriveString As String
Dim sSendFormat As String, lngDriveProper As Long

    lngMaxSize = 256: iStartPos = 1: iMidPos = 0: sSendFormat = vbNullString
    '�õ������߼�������
    lngSize = GetLogicalDriveStrings(lngMaxSize, strDrives)
    If lngSize Then
       If lngSize < lngMaxSize Then '�õ���ȷ�ĵ�ǰϵͳ���������ַ���
                                    '�ַ����ĸ�ʽΪ: c:\<null>d:\<null><null>
                                    'lngSize���������һ���ս��(NULL)
          Do   '�������һ�����������������ݸ��¼�fGetCurrenDriveEvent()
            iMidPos = InStr(iStartPos, strDrives, Chr$(0))
            strDriveString = vbNullString
            strDriveString = Mid(strDrives, iStartPos, iMidPos - (iStartPos))
            strDriveString = Trim(strDriveString) & Chr$(0)
            '���������ַ����뷢�͸�ʽ��
            sSendFormat = sSendFormat & strDriveString
            '�õ���������������
            lngDriveProper = GetDriveType(Trim$(strDriveString))
            sSendFormat = sSendFormat & Str(lngDriveProper) & Chr$(0)
            
            iStartPos = iMidPos + 1
          Loop While iStartPos < lngSize
          'fGetLogicalDriveStrings = 0
       Else '���ߴ�С������Ҫ��ʵ�ʳߴ�
       
            '�޸����ߴ�ֵ(lngMaxsize)
            
       End If
    Else '�������ó���
        fGetLogicalDrives = GetLastError()
    End If
          
    '����:
    '���������<NULL><NULL>
    sSendFormat = sSendFormat & Chr$(0)
    sckCmdServer.SendData sSendFormat
End Function

'-------------------------------------------------------------------------------
'���ܣ�����ָ����Ŀ¼.���Ը�ʽ:
'      <Ŀ¼1><NULL><�ļ�2><NULL>����<NULL><NULL>��
'      ��һ��vbNullChar�ָ�Ŀ¼���ļ���������vbNullChar����������
'����: sckCmdServer:�����Winsock
'      sPara:ָ����Ŀ¼�����ݷ��͵���IP��ַ�Ͷ˿�.
'        <Ŀ¼><NULL><IP><NULL><Port><NULL><NULL>
'      bTraverseDirectory:�Ƿ��������Ŀ¼
'����ֵ: ����Ŀ¼���ļ���ϳɵ��ַ�������ʽΪ:
'        <Ŀ¼1><NULL><�ļ�2><NULL>����<NULL><NULL>��
'        ��һ��vbNullChar�ָ�Ŀ¼���ļ���������vbNullChar����������
'����1��Ŀ¼��������(cCmdErrorNoDirectory)��
'      2 ���޷���ֵ��
'����:��sckDataServer���͡�
Private Function fDirectory(ByVal sckCmdServer As Winsock, _
        ByVal sPara As String, _
        Optional bTraverseDirectory As Boolean = True)
Dim sRemoteHost As String, lngRemotePort As Long, iFileTotle As Integer
Dim sDirectoryName As String
iFileTotle = 0
sDirectoryName = fSplitString(sPara) '�õ�ָ����Ŀ¼
If sDirectoryName = vbNullString Then
   Exit Function
End If
If ((GetFileAttributes(sDirectoryName) And FILE_ATTRIBUTE_DIRECTORY) _
   <> FILE_ATTRIBUTE_DIRECTORY) Or (GetFileAttributes(sDirectoryName) _
   = INVALID_HANDLE_VALUE) Then
   'A����������Ĳ���Ŀ¼�����ش���cCmdErrorNoDirectory
   sckCmdServer.SendData Str(cCmdErrorNoDirectory) & vbNullChar & vbNullChar
   Exit Function
End If
sRemoteHost = fSplitString(sPara) 'B���õ���������WinSock��IP��ַ
lngRemotePort = CLng(Val(fSplitString(sPara))) 'B���õ���������WinSock�Ķ˿�
With m_sckDataServer 'C�����ӽ�������Winsock
     .RemoteHost = sRemoteHost
     .RemotePort = lngRemotePort
     .Connect
     While (.State <> sckConnected)
            DoEvents
     Wend
End With
'D������ָ��Ŀ¼��FindAllFiles��������FindAllFilesͨ��sckDataServer���Ͳ鵽��Ŀ¼��
Call FindAllFiles(sDirectoryName & "\", iFileTotle, bCommandCancel, bTraverseDirectory)
m_sckDataServer.SendData vbNullChar 'E�����ͽ�����
m_sckDataServer.Close  'F���ر�����
'G���������ݴ��ͽ�������(cCmdDirectoryEnd)�͵õ��ļ����ܸ���
sckCmdServer.SendData Trim(Str(cCmdDirectoryEnd)) & vbNullChar & Trim(iFileTotle) & vbNullChar & vbNullChar
End Function

'ʾ��1:��FindFirstFile()��FindNextFile()��FindClose()��ʾ��
'-----------------------------------------------------------------------------
'���ܣ��������ļ���Ŀ¼,������������ļ�Ŀ¼��
'����: strDirNmae:������Ŀ¼��
'      iFileCount:�ҵ����ļ���.
'      bCancel:���ݸ��¼�fFoundFiles,���ڿ����Ƿ��������ļ�.
'-----------------------------------------------------------------------------
Private Function FindAllFiles(ByVal strDirName As String, Optional iFileCount As Integer = 0, _
Optional bCancel As Boolean = False, Optional bTraverseDirectory As Boolean = True) As Long
Dim hFind As Long, WFD As WIN32_FIND_DATA
Dim strText As String

strText = strDirName + "*"
hFind = FindFirstFile(strText, WFD) '�õ���һ���ļ�
If (hFind <> INVALID_HANDLE_VALUE) Then
   Do
     iFileCount = iFileCount + 1
     m_sckDataServer.SendData strDirName & GetRightFileName(WFD.cFileName) _
                              & vbNullChar
     DoEvents '�������������߳�
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
'����:�Ӹ������ַ����еõ���ȷ���ļ���.
'------------------------------------------------------------------------------------------
Private Function GetRightFileName(sString As String) As String
GetRightFileName = Left(sString, InStr(1, sString, Chr(0)) - 1)
End Function

'���ܣ���ָ���ķ�Χ�ڲ���ָ�����ļ������Ը�ʽ:
'      <Ŀ¼1><NULL><Ŀ¼2><NULL>����<NULL><NULL>
'      ��һ��vbNullChar�ָ�Ŀ¼���ļ���������vbNullChar����������
'����: sckCmdServer:�����Winsock
'      sPara:����ָ��Ŀ¼��Ҫ���ҵ��ļ��������ݷ��͵���IP��ַ
'            �Ͷ˿�.<IP><NULL><Port><NULL><NULL>
'����ֵ: ����Ŀ¼���ļ���ϳɵ��ַ�������ʽΪ:
'        <Ŀ¼1><NULL><Ŀ¼2><NULL>����<NULL><NULL>��
'        ��һ��vbNullChar�ָ�Ŀ¼���ļ���������vbNullChar����������
'����1��Ŀ¼��������(cCmdErrorNoDirectory)��
'      2 ���޷���ֵ��
'����:��sckDataServer���͡�
Private Function fFindFile(ByVal sckCmdServer As Winsock, _
        ByVal sPara As String)
Dim sDirectory As String, sFile As String
Dim hFind As Long, WFD As WIN32_FIND_DATA
Dim strText As String, iFileCount As Integer
iFileCount = 0
'A������������е�Ҫ���ҵ��ļ���
sFile = fSplitString(sPara)
If sFile = vbNullChar Then Exit Function
'B�������������ָ����Ŀ¼��
sDirectory = fSplitString(sPara)
If ((GetFileAttributes(sDirectory) And FILE_ATTRIBUTE_DIRECTORY) _
   <> FILE_ATTRIBUTE_DIRECTORY) Or (GetFileAttributes(sDirectory) _
   = INVALID_HANDLE_VALUE Or sDirectory = vbNullString) Then
   '��������Ĳ���Ŀ¼�����ش���cCmdErrorNoDirectory
   sckCmdServer.SendData Str(cCmdErrorNoDirectory) & vbNullChar & vbNullChar
   Exit Function
End If
'C�����ӽ�������Winsock
With m_sckDataServer
     .RemoteHost = fSplitString(sPara) '�õ���������WinSock��IP��ַ
     .RemotePort = CLng(Val(fSplitString(sPara)))  '�õ���������WinSock�Ķ˿�
     .Connect
     While (.State <> sckConnected)
            DoEvents
     Wend
End With
'D������ָ�����ļ�,��ͨ��sckDataSever���Ͳ鵽��Ŀ¼
Call fFindFileDirectory(sDirectory & "\", sFile, iFileCount, bCommandCancel)
m_sckDataServer.SendData vbNullChar 'E�����ͽ�����
m_sckDataServer.Close  'F���ر�����
'G���������ݴ��ͽ�������(cCmdDirectoryEnd)�͵õ��ļ����ܸ���
sckCmdServer.SendData Trim(Str(cCmdFindFileEnd)) & vbNullChar & Trim(iFileCount) & vbNullChar & vbNullChar
End Function

'����: strDirNmae:������Ŀ¼��
'      sFileName:Ҫ���ҵ��ļ���
'      iFileCount:�ҵ����ļ���.
'      bCancel:���ݸ��¼�fFoundFiles,���ڿ����Ƿ��������ļ�.
'-----------------------------------------------------------------------------
Private Function fFindFileDirectory(ByVal strDirName As String, _
ByVal sFileName As String, Optional iFileCount As Integer = 0, _
Optional bCancel As Boolean = False) As Long
Dim hFind As Long, WFD As WIN32_FIND_DATA
Dim strText As String

strText = strDirName + "*"
hFind = FindFirstFile(strText, WFD) '�õ���һ���ļ�
If (hFind <> INVALID_HANDLE_VALUE) Then
   Do
     If UCase(GetRightFileName(WFD.cFileName)) Like UCase(sFileName) Then
        iFileCount = iFileCount + 1
        m_sckDataServer.SendData strDirName & GetRightFileName(WFD.cFileName) _
                              & vbNullChar
     End If
     DoEvents '�������������߳�
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

