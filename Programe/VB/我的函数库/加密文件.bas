Attribute VB_Name = "Add_Mi"
Option Explicit

Private Const bDeBug = True

Private Const s此文件不是加密文件 = "此文件不是加密文件"
Private Const s没有此文件 = "没有此文件"
Private Const s从源文件中解出某文件 = "从源文件中解出某文件"
Private Const s从源文件中解出所有文件 = "从源文件中解出所有文件"

Private Type Type_File_head  '文件信息结构
        lFilenameLength As Long
        lFileLength As Long
        dDate As Date '存入日期
        End Type
        
Public Type Type_File_Information '文件信息结构
        lFilenameLength As Long
        lFileLength As Long
        dDate As Date '存入日期
        FileName As String '文件名
        End Type
        
'命令参数:
'1.解出库中的所有文件
'2.只解出某一个文件
'3.解出所有文件信息
'4.只解出某一文件信息
Public Enum Enum_Command_para_JM
       从源文件中解出某文件 = 32 '文件名在参数DirectionFileName中
       从源文件中解出第N个文件 = 64 '参数DirectionFileName为N
       从源文件中解出所有文件 = 128
       从源文件中查找某文件信息 = 256
       从源文件中查找第N个文件信息 = 512
       从源文件中查找所有文件信息 = 1024
       从源文件中即查信息又解出文件 = 2048
       没有此文件 = 4096
       此文件不是加密文件 = 8192
End Enum

Public Enum Enum_Command_Para_Add
       保留源文件 = 0 '加密文件
       删除源文件 = 1
       加入致到库文件 = 2
       一一对应文件 = 4
       加密源文件 = 8
End Enum

'扩展加密文件
'参数:
'SourceFileName为源文件名;
'DirectionFileName="",为一一对应加密文件,
'当Path=""时为源文件名的扩展名为".JMW",
'否则为加密后的文件名;
'PassWord为加密密码;
'Path为加密后文件的路径,
'为空时,加密文件与源文件在同一个目录;
'CommandPara为命令参数,见 Enum_Command_Para_Add.
Public Function AddFileEx(SourceFilename As String, _
       Optional DirectionFileName As String = "", _
       Optional PassWord As String = "", _
       Optional Path As String = "", _
       Optional CommandPara As Enum_Command_Para_Add = Enum_Command_Para_Add.保留源文件)
Dim sF As String
If DirectionFileName = "" Then
   If Path = "" Then
      AddFile SourceFilename, , PassWord, 一一对应文件
   Else
      sF = GetFileName(SourceFilename)
      AddFile SourceFilename, Path + "\" + IIf( _
              Mid(Right(sF, 4), 1, 1) = ".", _
         Left(sF, Len(sF) - 4) + ".JMW", sF & ".JMW"), _
              PassWord, 一一对应文件
   End If
Else
   If Path <> "" Then
      AddFile SourceFilename, Path + "\" + DirectionFileName, PassWord
   Else
      AddFile SourceFilename, GetPath(SourceFilename) + "\" + DirectionFileName, PassWord
   End If
End If

If CommandPara And 删除源文件 Then
   Kill SourceFilename
End If
End Function

'加密文件
Public Function AddFile(SourceFilename As String, _
       Optional DirectionFileName As String = "", _
       Optional PassWord As String = "", _
       Optional CommandPara As Enum_Command_Para_Add)
Dim I As Long, J As Long, b As Byte
Dim FileFlag As String * 4 '文件标志
Dim SNum As Integer, DNum As Integer '文件号
Dim FileHead As Type_File_head '文件信息结构
Dim FileName() As Byte '源文件名
Dim SLen As Long, DLen As Long '源文件长度，目标文件长度
Dim SS(16) As Byte '缓冲区

'密码值
Dim Mp(16) As Byte, MS(16) As Byte, PS(16) As Byte
FileFlag = "JMWJ" '加密文件标志
Dim s As String

s = "KangLin1976!~|%)"
MS(1) = 37: MS(2) = 240: MS(3) = 179: MS(4) = 27
MS(5) = 159: MS(6) = 24: MS(7) = 17: MS(8) = 152
MS(9) = 7: MS(10) = 145: MS(11) = 14: MS(12) = 127
MS(13) = 171: MS(14) = 45: MS(15) = 114: MS(16) = 36

If DirectionFileName = "" Then
   DirectionFileName = IIf(Mid(Right(SourceFilename, 4), 1, 1) = ".", _
   Left(SourceFilename, Len(SourceFilename) - 4) & ".JMW", SourceFilename & ".JMW")
   CommandPara = CommandPara Or 一一对应文件
   'If Dir(DirectionFileName) <> "" Then
   '   Err.Raise 1000, , "加密文件已经存在，是否删除？"
   '   Kill DirectionFileName
   'End If
End If

If Dir(DirectionFileName) <> "" And (CommandPara And 一一对应文件) Then
      Err.Raise 1000, , "加密文件已经存在，是否删除？"
      Kill DirectionFileName
End If

On Error Resume Next
   For I = 1 To 8
       PS(I) = MidByte(PassWord, I)
       PS(16 - I + 1) = PS(I)
   Next I
For I = 1 To 16
    Mp(I) = PS(I) Xor MS(I)
    MS(I) = Asc(Mid(s, I, 1))
    PS(I) = MS(I) Xor Mp(I)
Next I

SNum = FreeFile()
DNum = FreeFile(SNum)
Open SourceFilename For Binary As #SNum Len = 1
'1.存入文件标志
DLen = 0
DLen = FileLen(DirectionFileName) '得到目标文件长度
If DLen = 0 Then  '当目标文件长度为0时,
Open DirectionFileName For Binary As #DNum Len = Len(FileFlag)
     Put #DNum, , FileFlag '文件头标志"JMWJ"
Close #DNum
End If
On Error GoTo 0 '清除错误捕捉
'2.文件信息头
FileName = StrConv(GetFileName(SourceFilename), vbFromUnicode)
With FileHead '给文件信息结构赋值
    .lFileLength = LOF(SNum) '得到源文件长度
    .lFilenameLength = UBound(FileName) + 1 '得到文件名长度
    .dDate = Date '加密日期
End With
'  i.存入文件信息头
Open DirectionFileName For Binary As #DNum Len = Len(FileHead)
     Put #DNum, LOF(DNum) + 1, FileHead '存入文件信息头
Close #DNum
'  ii.存入文件名
'    c.加密文件名
For I = 0 To UBound(FileName)
    FileName(I) = FileName(I) Xor PS(I Mod 16 + 1)
Next I
'    d.存入文件名
Open DirectionFileName For Binary As #DNum Len = UBound(FileName) + 1
     Put #DNum, LOF(DNum) + 1, FileName '存入文件名
Close #DNum
'3.数据块加密
Open DirectionFileName For Binary As #DNum Len = 1
     DLen = LOF(DNum) '得到目标文件长度
     Seek DNum, DLen + 1 '设置目标文件指针
     While (Not EOF(SNum)) '取出源文件的数据
           For I = 1 To 16
               '如果小于最后数据块小于16位
               If EOF(SNum) Then Exit For
               Get #SNum, , SS(I)
           Next I
           If I > 16 Then '加密文件
              For I = 16 To 1 Step -1
                  b = SS(I) Xor PS(I)
                  Put #DNum, , b
              Next I
           Else '如果小于最后数据块小于16位
              For J = 1 To I - 2 '文件结束符(\0)
                  Put #DNum, , SS(J) Xor PS(J)
              Next J
           End If
     Wend
Close #DNum
Close #SNum
End Function

'解密文件
'功能:
'1.解出库中的所有文件
'2.只解出某一个文件
'3.解出所有文件信息
'4.只解出某一文件信息
'当解出文件信息时,当CommandParam=enum_command_para_jm.从源文件中即查信息又解出文件
'                1.2两种情况才同时存在,
'参数:
'SoureceFileName为源文件名
'FileInformation为文件信息结构,用于传递查到的文件信息,数组从第一个开始
'DirectionFileName如果为解出某一文件时为此文件的文件名
'为解出第N个文件时为N,默认为解出所有文件("*.*")
'当为解出文件信息时取值如上
'CommandParam解出命令见 Enum_Command_Para_JM
'PassWord密码
'Path解出文件放入的路径
'解出文件所存放的位置为：
'当Path为空时存放在与源文件相同的目录下
'否则放在path目录下
Public Function JM_eFile(SourceFilename As String, _
       FileInformation() As Type_File_Information, _
       Optional DirectionFileName As String = "*.*", _
       Optional CommandParam As Enum_Command_para_JM, _
       Optional PassWord As String = "", _
       Optional Path As String = "")
Dim SNum As Integer, DNum As Integer
Dim SLen As Long, DLen As Long, I As Long, J As Long, b As Byte
Dim FileHead As Type_File_head '文件头信息
Dim FPoint As Long '文件指针
Dim FLoop As Long
Dim FileNameB() As Byte '要解出的文件名
Dim FileName As String '要解出的文件名
Dim DFileName As String
Dim FileFlag As String * 4 '文件标志
Dim Flag As Integer '内部标志
Dim s As String
Dim SS(16) As Byte
Dim PS(16) As Byte
Dim Mp(16) As Byte, MS(16) As Byte

'密码
MS(1) = 37: MS(2) = 240: MS(3) = 179: MS(4) = 27
MS(5) = 159: MS(6) = 24: MS(7) = 17: MS(8) = 152
MS(9) = 7: MS(10) = 145: MS(11) = 14: MS(12) = 127
MS(13) = 171: MS(14) = 45: MS(15) = 114: MS(16) = 36
On Error Resume Next
   For I = 1 To 8
       PS(I) = Asc(Mid(PassWord, I, 1))
       PS(16 - I + 1) = PS(I)
   Next I
On Error GoTo 0
s = "KangLin1976!~|%)"
For I = 1 To 16
    Mp(I) = PS(I) Xor MS(I)
    MS(I) = Asc(Mid(s, I, 1))
    PS(I) = MS(I) Xor Mp(I)
Next I
'初始化参数
ReDim FileInformation(0)
If DirectionFileName = "*.*" Or DirectionFileName = "" Then
   CommandParam = CommandParam Or _
   Enum_Command_para_JM.从源文件中解出所有文件
ElseIf IsNumeric(DirectionFileName) Then
   CommandParam = CommandParam Or _
   Enum_Command_para_JM.从源文件中解出第N个文件
Else
   CommandParam = CommandParam Or _
   Enum_Command_para_JM.从源文件中解出某文件
End If
If Path = "" Then
   Path = GetPath(SourceFilename)
End If
SNum = FreeFile
DNum = FreeFile(SNum)
'1.检查文件标志
Open SourceFilename For Binary As #SNum Len = Len(FileFlag)
     Get #SNum, , FileFlag '文件头标志"JMWJ"
Close #SNum
If FileFlag <> "JMWJ" Then
   #If bDeBug Then
       MsgBox s此文件不是加密文件
   #End If
   JM_eFile = Enum_Command_para_JM.此文件不是加密文件
   Exit Function
End If
   
'2.取文件信息头，确定文件位置
SLen = FileLen(SourceFilename)
FLoop = 5 '设置文件指针
Flag = 0
Dim N As Long
N = 0
While (True)
   N = N + 1
   '得到文件信息头
   Open SourceFilename For Binary As #SNum Len = Len(FileHead)
        Seek #SNum, FLoop '设置文件指针
        Get #SNum, , FileHead '得到文件信息头
   Close #SNum
   '得到文件名
   Open SourceFilename For Binary As #SNum Len = FileHead.lFilenameLength
        Seek SNum, FLoop + Len(FileHead) '设置文件指针
        ReDim FileNameB(FileHead.lFilenameLength - 1)
        Get #SNum, , FileNameB '得到文件名
        FPoint = Seek(SNum) '保留指针
   Close #SNum
   '解密文件名
   For I = 0 To UBound(FileNameB)
       FileNameB(I) = FileNameB(I) Xor PS(I Mod 16 + 1)
   Next I
   FileName = StrConv(FileNameB, vbUnicode) '文件名
   '给文件信息结构赋值
   If CommandParam And Enum_Command_para_JM.从源文件中查找所有文件信息 Then
      ReDim Preserve FileInformation(UBound(FileInformation) + 1)
      With FileInformation(UBound(FileInformation))
           .dDate = FileHead.dDate
           .FileName = FileName
           .lFileLength = FileHead.lFileLength
           .lFilenameLength = FileHead.lFilenameLength
           JM_eFile = Enum_Command_para_JM.从源文件中查找所有文件信息
      End With
      If CommandParam And 从源文件中即查信息又解出文件 Then
      Else
         CommandParam = CommandParam And (Not ( _
           Enum_Command_para_JM.从源文件中解出所有文件 Or _
           Enum_Command_para_JM.从源文件中解出某文件 Or _
           Enum_Command_para_JM.从源文件中解出第N个文件))
      End If
       Flag = 1
   ElseIf CommandParam And Enum_Command_para_JM.从源文件中查找某文件信息 _
   Or CommandParam And Enum_Command_para_JM.从源文件中查找第N个文件信息 Then
      If FileName = DirectionFileName Or N = Val(DirectionFileName) Then
         ReDim Preserve FileInformation(UBound(FileInformation) + 1)
         With FileInformation(UBound(FileInformation))
           .dDate = FileHead.dDate
           .FileName = FileName
           .lFileLength = FileHead.lFileLength
           .lFilenameLength = FileHead.lFilenameLength
         End With
         JM_eFile = Enum_Command_para_JM.从源文件中查找某文件信息
         Exit Function
      End If
      If CommandParam And 从源文件中即查信息又解出文件 Then
      Else
         CommandParam = CommandParam And (Not ( _
          Enum_Command_para_JM.从源文件中解出所有文件 Or _
          Enum_Command_para_JM.从源文件中解出某文件 Or _
          Enum_Command_para_JM.从源文件中解出第N个文件))
      End If
   End If
   '解密数据块
   If CommandParam And Enum_Command_para_JM.从源文件中解出某文件 Then
      If UCase(FileName) = UCase(DirectionFileName) Then
         JM_eFileBlock SourceFilename, Path + "\" + DirectionFileName, FPoint, FileHead.lFileLength, PassWord
         JM_eFile = Enum_Command_para_JM.从源文件中解出某文件
         If bDeBug Then
             MsgBox s从源文件中解出某文件
         End If
         Exit Function
      End If
   End If
   If CommandParam And Enum_Command_para_JM.从源文件中解出第N个文件 And N = Val(DirectionFileName) Then
       JM_eFileBlock SourceFilename, Path + "\" + FileName, FPoint, FileHead.lFileLength, PassWord
       JM_eFile = Enum_Command_para_JM.从源文件中解出第N个文件
       Exit Function
   End If
   If CommandParam And Enum_Command_para_JM.从源文件中解出所有文件 Then
       JM_eFileBlock SourceFilename, Path + "\" + FileName, FPoint, FileHead.lFileLength, PassWord
       JM_eFile = Enum_Command_para_JM.从源文件中解出所有文件
       Flag = 1
   End If
   FLoop = FLoop + Len(FileHead) + FileHead.lFileLength + FileHead.lFilenameLength '重设指针
   If FLoop >= SLen Then
      If Flag = 0 Then
         JM_eFile = Enum_Command_para_JM.没有此文件
         If bDeBug Then
            MsgBox s没有此文件
         End If
      End If
      Exit Function
   End If
Wend
End Function

'此过程只解密文件中的数据块
'调用前要设置好文件指针(FilePoint),
'和文件长度(FileLength)
'参数为:源文件名(SourceFileName)
'和目标文件名(DirectioinFileName),PassWord为密码
Private Function JM_eFileBlock(SourceFilename As String, _
        DirectionFileName As String, FilePoint As Long, _
        FileLength As Long, Optional PassWord As String = "")
Dim SNum As Integer, DNum As Integer
Dim DLen As Long, I As Long, J As Long, b As Byte
Dim s As String
Dim SS(16) As Byte
Dim PS(16) As Byte
Dim Mp(16) As Byte, MS(16) As Byte

'密码
MS(1) = 37: MS(2) = 240: MS(3) = 179: MS(4) = 27
MS(5) = 159: MS(6) = 24: MS(7) = 17: MS(8) = 152
MS(9) = 7: MS(10) = 145: MS(11) = 14: MS(12) = 127
MS(13) = 171: MS(14) = 45: MS(15) = 114: MS(16) = 36
On Error Resume Next
   For I = 1 To 8
       PS(I) = Asc(Mid(PassWord, I, 1))
       PS(16 - I + 1) = PS(I)
   Next I
On Error GoTo 0
s = "KangLin1976!~|%)"
For I = 1 To 16
    Mp(I) = PS(I) Xor MS(I)
    MS(I) = Asc(Mid(s, I, 1))
    PS(I) = MS(I) Xor Mp(I)
Next I
SNum = FreeFile()
DNum = FreeFile(SNum)
Open SourceFilename For Binary As #SNum
Open DirectionFileName For Binary As #DNum
     'DLen = LOF(DNum) '得到目标文件长度
     Seek #SNum, FilePoint '设置源文件指针（指向文件数据块）
     '解密
     Do While (Seek(SNum) - FilePoint < FileLength) '取出源文件的数据
           For I = 1 To 16
               '如果小于最后数据块小于8位
               If Seek(SNum) - FilePoint >= FileLength Then Exit For
               Get #SNum, , SS(I)
           Next I
           If I > 16 Then '加密文件
              For I = 16 To 1 Step -1
                     b = SS(I) Xor PS(16 - I + 1)
                  Put #DNum, , b
              Next I
           Else '如果小于最后数据块小于8位
              For J = 1 To I - 2
                  Put #DNum, , SS(J) Xor PS(J)
              Next J
              'Exit Do
           End If
     Loop
Close #SNum
Close #DNum
End Function

'得到文件路径
Public Function GetPath(FileName As String) As String
Dim J As Long
'得到文件中的路径
J = ReverseFindSubStringByte(LTrim(RTrim(FileName)), "\") '找到文件名的位置
'如果位置为0,则不含路径,否则保留路径
GetPath = IIf(J, LeftByte(LTrim(RTrim( _
        FileName)), J - 1), "")
End Function

'从含有路径的文件中得到到文件名
Public Function GetFileName(FileName As String) As String
Dim I As Long
'    a.去掉文件中的路径
I = ReverseFindSubStringByte(LTrim(RTrim(FileName)), "\") '找到文件名的位置
'    b.如果位置为0,则不含路径,否则去掉路径
GetFileName = IIf(I, MidByte(LTrim(RTrim(FileName)), I + 1, _
                LenByte(FileName, False) - I), _
                LTrim(RTrim(FileName)))
End Function

'从SourceFileNameString中分离出所有文件名
Public Function sGetAllFile(SourceFileNameString As String, FileName() As String)
Dim I As Long, J As Long
Dim Path As String
'第一个分隔符的位置
I = InStr(1, SourceFileNameString, Chr(0))
If I = 0 Then '只含一个文件时
   ReDim FileName(1)
   FileName(1) = SourceFileNameString
   Exit Function
End If
'含多个文件时
Path = Left(SourceFileNameString, I - 1)
J = I
While (J)
      J = InStr(I + 1, SourceFileNameString, Chr(0))
      ReDim Preserve FileName(UBound(FileName) + 1)
      If J = 0 Then
         FileName(UBound(FileName)) = Path & "\" & Right(SourceFileNameString, Len(SourceFileNameString) - I)
      Else
         FileName(UBound(FileName)) = Path & "\" & Mid(SourceFileNameString, I + 1, J - I - 1)
      End If
      I = J
Wend
End Function
