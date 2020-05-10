Attribute VB_Name = "Add_Mi"
Option Explicit

Private Const bDeBug = True

Private Const s���ļ����Ǽ����ļ� = "���ļ����Ǽ����ļ�"
Private Const sû�д��ļ� = "û�д��ļ�"
Private Const s��Դ�ļ��н��ĳ�ļ� = "��Դ�ļ��н��ĳ�ļ�"
Private Const s��Դ�ļ��н�������ļ� = "��Դ�ļ��н�������ļ�"

Private Type Type_File_head  '�ļ���Ϣ�ṹ
        lFilenameLength As Long
        lFileLength As Long
        dDate As Date '��������
        End Type
        
Public Type Type_File_Information '�ļ���Ϣ�ṹ
        lFilenameLength As Long
        lFileLength As Long
        dDate As Date '��������
        FileName As String '�ļ���
        End Type
        
'�������:
'1.������е������ļ�
'2.ֻ���ĳһ���ļ�
'3.��������ļ���Ϣ
'4.ֻ���ĳһ�ļ���Ϣ
Public Enum Enum_Command_para_JM
       ��Դ�ļ��н��ĳ�ļ� = 32 '�ļ����ڲ���DirectionFileName��
       ��Դ�ļ��н����N���ļ� = 64 '����DirectionFileNameΪN
       ��Դ�ļ��н�������ļ� = 128
       ��Դ�ļ��в���ĳ�ļ���Ϣ = 256
       ��Դ�ļ��в��ҵ�N���ļ���Ϣ = 512
       ��Դ�ļ��в��������ļ���Ϣ = 1024
       ��Դ�ļ��м�����Ϣ�ֽ���ļ� = 2048
       û�д��ļ� = 4096
       ���ļ����Ǽ����ļ� = 8192
End Enum

Public Enum Enum_Command_Para_Add
       ����Դ�ļ� = 0 '�����ļ�
       ɾ��Դ�ļ� = 1
       �����µ����ļ� = 2
       һһ��Ӧ�ļ� = 4
       ����Դ�ļ� = 8
End Enum

'��չ�����ļ�
'����:
'SourceFileNameΪԴ�ļ���;
'DirectionFileName="",Ϊһһ��Ӧ�����ļ�,
'��Path=""ʱΪԴ�ļ�������չ��Ϊ".JMW",
'����Ϊ���ܺ���ļ���;
'PassWordΪ��������;
'PathΪ���ܺ��ļ���·��,
'Ϊ��ʱ,�����ļ���Դ�ļ���ͬһ��Ŀ¼;
'CommandParaΪ�������,�� Enum_Command_Para_Add.
Public Function AddFileEx(SourceFilename As String, _
       Optional DirectionFileName As String = "", _
       Optional PassWord As String = "", _
       Optional Path As String = "", _
       Optional CommandPara As Enum_Command_Para_Add = Enum_Command_Para_Add.����Դ�ļ�)
Dim sF As String
If DirectionFileName = "" Then
   If Path = "" Then
      AddFile SourceFilename, , PassWord, һһ��Ӧ�ļ�
   Else
      sF = GetFileName(SourceFilename)
      AddFile SourceFilename, Path + "\" + IIf( _
              Mid(Right(sF, 4), 1, 1) = ".", _
         Left(sF, Len(sF) - 4) + ".JMW", sF & ".JMW"), _
              PassWord, һһ��Ӧ�ļ�
   End If
Else
   If Path <> "" Then
      AddFile SourceFilename, Path + "\" + DirectionFileName, PassWord
   Else
      AddFile SourceFilename, GetPath(SourceFilename) + "\" + DirectionFileName, PassWord
   End If
End If

If CommandPara And ɾ��Դ�ļ� Then
   Kill SourceFilename
End If
End Function

'�����ļ�
Public Function AddFile(SourceFilename As String, _
       Optional DirectionFileName As String = "", _
       Optional PassWord As String = "", _
       Optional CommandPara As Enum_Command_Para_Add)
Dim I As Long, J As Long, b As Byte
Dim FileFlag As String * 4 '�ļ���־
Dim SNum As Integer, DNum As Integer '�ļ���
Dim FileHead As Type_File_head '�ļ���Ϣ�ṹ
Dim FileName() As Byte 'Դ�ļ���
Dim SLen As Long, DLen As Long 'Դ�ļ����ȣ�Ŀ���ļ�����
Dim SS(16) As Byte '������

'����ֵ
Dim Mp(16) As Byte, MS(16) As Byte, PS(16) As Byte
FileFlag = "JMWJ" '�����ļ���־
Dim s As String

s = "KangLin1976!~|%)"
MS(1) = 37: MS(2) = 240: MS(3) = 179: MS(4) = 27
MS(5) = 159: MS(6) = 24: MS(7) = 17: MS(8) = 152
MS(9) = 7: MS(10) = 145: MS(11) = 14: MS(12) = 127
MS(13) = 171: MS(14) = 45: MS(15) = 114: MS(16) = 36

If DirectionFileName = "" Then
   DirectionFileName = IIf(Mid(Right(SourceFilename, 4), 1, 1) = ".", _
   Left(SourceFilename, Len(SourceFilename) - 4) & ".JMW", SourceFilename & ".JMW")
   CommandPara = CommandPara Or һһ��Ӧ�ļ�
   'If Dir(DirectionFileName) <> "" Then
   '   Err.Raise 1000, , "�����ļ��Ѿ����ڣ��Ƿ�ɾ����"
   '   Kill DirectionFileName
   'End If
End If

If Dir(DirectionFileName) <> "" And (CommandPara And һһ��Ӧ�ļ�) Then
      Err.Raise 1000, , "�����ļ��Ѿ����ڣ��Ƿ�ɾ����"
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
'1.�����ļ���־
DLen = 0
DLen = FileLen(DirectionFileName) '�õ�Ŀ���ļ�����
If DLen = 0 Then  '��Ŀ���ļ�����Ϊ0ʱ,
Open DirectionFileName For Binary As #DNum Len = Len(FileFlag)
     Put #DNum, , FileFlag '�ļ�ͷ��־"JMWJ"
Close #DNum
End If
On Error GoTo 0 '�������׽
'2.�ļ���Ϣͷ
FileName = StrConv(GetFileName(SourceFilename), vbFromUnicode)
With FileHead '���ļ���Ϣ�ṹ��ֵ
    .lFileLength = LOF(SNum) '�õ�Դ�ļ�����
    .lFilenameLength = UBound(FileName) + 1 '�õ��ļ�������
    .dDate = Date '��������
End With
'  i.�����ļ���Ϣͷ
Open DirectionFileName For Binary As #DNum Len = Len(FileHead)
     Put #DNum, LOF(DNum) + 1, FileHead '�����ļ���Ϣͷ
Close #DNum
'  ii.�����ļ���
'    c.�����ļ���
For I = 0 To UBound(FileName)
    FileName(I) = FileName(I) Xor PS(I Mod 16 + 1)
Next I
'    d.�����ļ���
Open DirectionFileName For Binary As #DNum Len = UBound(FileName) + 1
     Put #DNum, LOF(DNum) + 1, FileName '�����ļ���
Close #DNum
'3.���ݿ����
Open DirectionFileName For Binary As #DNum Len = 1
     DLen = LOF(DNum) '�õ�Ŀ���ļ�����
     Seek DNum, DLen + 1 '����Ŀ���ļ�ָ��
     While (Not EOF(SNum)) 'ȡ��Դ�ļ�������
           For I = 1 To 16
               '���С��������ݿ�С��16λ
               If EOF(SNum) Then Exit For
               Get #SNum, , SS(I)
           Next I
           If I > 16 Then '�����ļ�
              For I = 16 To 1 Step -1
                  b = SS(I) Xor PS(I)
                  Put #DNum, , b
              Next I
           Else '���С��������ݿ�С��16λ
              For J = 1 To I - 2 '�ļ�������(\0)
                  Put #DNum, , SS(J) Xor PS(J)
              Next J
           End If
     Wend
Close #DNum
Close #SNum
End Function

'�����ļ�
'����:
'1.������е������ļ�
'2.ֻ���ĳһ���ļ�
'3.��������ļ���Ϣ
'4.ֻ���ĳһ�ļ���Ϣ
'������ļ���Ϣʱ,��CommandParam=enum_command_para_jm.��Դ�ļ��м�����Ϣ�ֽ���ļ�
'                1.2���������ͬʱ����,
'����:
'SoureceFileNameΪԴ�ļ���
'FileInformationΪ�ļ���Ϣ�ṹ,���ڴ��ݲ鵽���ļ���Ϣ,����ӵ�һ����ʼ
'DirectionFileName���Ϊ���ĳһ�ļ�ʱΪ���ļ����ļ���
'Ϊ�����N���ļ�ʱΪN,Ĭ��Ϊ��������ļ�("*.*")
'��Ϊ����ļ���Ϣʱȡֵ����
'CommandParam�������� Enum_Command_Para_JM
'PassWord����
'Path����ļ������·��
'����ļ�����ŵ�λ��Ϊ��
'��PathΪ��ʱ�������Դ�ļ���ͬ��Ŀ¼��
'�������pathĿ¼��
Public Function JM_eFile(SourceFilename As String, _
       FileInformation() As Type_File_Information, _
       Optional DirectionFileName As String = "*.*", _
       Optional CommandParam As Enum_Command_para_JM, _
       Optional PassWord As String = "", _
       Optional Path As String = "")
Dim SNum As Integer, DNum As Integer
Dim SLen As Long, DLen As Long, I As Long, J As Long, b As Byte
Dim FileHead As Type_File_head '�ļ�ͷ��Ϣ
Dim FPoint As Long '�ļ�ָ��
Dim FLoop As Long
Dim FileNameB() As Byte 'Ҫ������ļ���
Dim FileName As String 'Ҫ������ļ���
Dim DFileName As String
Dim FileFlag As String * 4 '�ļ���־
Dim Flag As Integer '�ڲ���־
Dim s As String
Dim SS(16) As Byte
Dim PS(16) As Byte
Dim Mp(16) As Byte, MS(16) As Byte

'����
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
'��ʼ������
ReDim FileInformation(0)
If DirectionFileName = "*.*" Or DirectionFileName = "" Then
   CommandParam = CommandParam Or _
   Enum_Command_para_JM.��Դ�ļ��н�������ļ�
ElseIf IsNumeric(DirectionFileName) Then
   CommandParam = CommandParam Or _
   Enum_Command_para_JM.��Դ�ļ��н����N���ļ�
Else
   CommandParam = CommandParam Or _
   Enum_Command_para_JM.��Դ�ļ��н��ĳ�ļ�
End If
If Path = "" Then
   Path = GetPath(SourceFilename)
End If
SNum = FreeFile
DNum = FreeFile(SNum)
'1.����ļ���־
Open SourceFilename For Binary As #SNum Len = Len(FileFlag)
     Get #SNum, , FileFlag '�ļ�ͷ��־"JMWJ"
Close #SNum
If FileFlag <> "JMWJ" Then
   #If bDeBug Then
       MsgBox s���ļ����Ǽ����ļ�
   #End If
   JM_eFile = Enum_Command_para_JM.���ļ����Ǽ����ļ�
   Exit Function
End If
   
'2.ȡ�ļ���Ϣͷ��ȷ���ļ�λ��
SLen = FileLen(SourceFilename)
FLoop = 5 '�����ļ�ָ��
Flag = 0
Dim N As Long
N = 0
While (True)
   N = N + 1
   '�õ��ļ���Ϣͷ
   Open SourceFilename For Binary As #SNum Len = Len(FileHead)
        Seek #SNum, FLoop '�����ļ�ָ��
        Get #SNum, , FileHead '�õ��ļ���Ϣͷ
   Close #SNum
   '�õ��ļ���
   Open SourceFilename For Binary As #SNum Len = FileHead.lFilenameLength
        Seek SNum, FLoop + Len(FileHead) '�����ļ�ָ��
        ReDim FileNameB(FileHead.lFilenameLength - 1)
        Get #SNum, , FileNameB '�õ��ļ���
        FPoint = Seek(SNum) '����ָ��
   Close #SNum
   '�����ļ���
   For I = 0 To UBound(FileNameB)
       FileNameB(I) = FileNameB(I) Xor PS(I Mod 16 + 1)
   Next I
   FileName = StrConv(FileNameB, vbUnicode) '�ļ���
   '���ļ���Ϣ�ṹ��ֵ
   If CommandParam And Enum_Command_para_JM.��Դ�ļ��в��������ļ���Ϣ Then
      ReDim Preserve FileInformation(UBound(FileInformation) + 1)
      With FileInformation(UBound(FileInformation))
           .dDate = FileHead.dDate
           .FileName = FileName
           .lFileLength = FileHead.lFileLength
           .lFilenameLength = FileHead.lFilenameLength
           JM_eFile = Enum_Command_para_JM.��Դ�ļ��в��������ļ���Ϣ
      End With
      If CommandParam And ��Դ�ļ��м�����Ϣ�ֽ���ļ� Then
      Else
         CommandParam = CommandParam And (Not ( _
           Enum_Command_para_JM.��Դ�ļ��н�������ļ� Or _
           Enum_Command_para_JM.��Դ�ļ��н��ĳ�ļ� Or _
           Enum_Command_para_JM.��Դ�ļ��н����N���ļ�))
      End If
       Flag = 1
   ElseIf CommandParam And Enum_Command_para_JM.��Դ�ļ��в���ĳ�ļ���Ϣ _
   Or CommandParam And Enum_Command_para_JM.��Դ�ļ��в��ҵ�N���ļ���Ϣ Then
      If FileName = DirectionFileName Or N = Val(DirectionFileName) Then
         ReDim Preserve FileInformation(UBound(FileInformation) + 1)
         With FileInformation(UBound(FileInformation))
           .dDate = FileHead.dDate
           .FileName = FileName
           .lFileLength = FileHead.lFileLength
           .lFilenameLength = FileHead.lFilenameLength
         End With
         JM_eFile = Enum_Command_para_JM.��Դ�ļ��в���ĳ�ļ���Ϣ
         Exit Function
      End If
      If CommandParam And ��Դ�ļ��м�����Ϣ�ֽ���ļ� Then
      Else
         CommandParam = CommandParam And (Not ( _
          Enum_Command_para_JM.��Դ�ļ��н�������ļ� Or _
          Enum_Command_para_JM.��Դ�ļ��н��ĳ�ļ� Or _
          Enum_Command_para_JM.��Դ�ļ��н����N���ļ�))
      End If
   End If
   '�������ݿ�
   If CommandParam And Enum_Command_para_JM.��Դ�ļ��н��ĳ�ļ� Then
      If UCase(FileName) = UCase(DirectionFileName) Then
         JM_eFileBlock SourceFilename, Path + "\" + DirectionFileName, FPoint, FileHead.lFileLength, PassWord
         JM_eFile = Enum_Command_para_JM.��Դ�ļ��н��ĳ�ļ�
         If bDeBug Then
             MsgBox s��Դ�ļ��н��ĳ�ļ�
         End If
         Exit Function
      End If
   End If
   If CommandParam And Enum_Command_para_JM.��Դ�ļ��н����N���ļ� And N = Val(DirectionFileName) Then
       JM_eFileBlock SourceFilename, Path + "\" + FileName, FPoint, FileHead.lFileLength, PassWord
       JM_eFile = Enum_Command_para_JM.��Դ�ļ��н����N���ļ�
       Exit Function
   End If
   If CommandParam And Enum_Command_para_JM.��Դ�ļ��н�������ļ� Then
       JM_eFileBlock SourceFilename, Path + "\" + FileName, FPoint, FileHead.lFileLength, PassWord
       JM_eFile = Enum_Command_para_JM.��Դ�ļ��н�������ļ�
       Flag = 1
   End If
   FLoop = FLoop + Len(FileHead) + FileHead.lFileLength + FileHead.lFilenameLength '����ָ��
   If FLoop >= SLen Then
      If Flag = 0 Then
         JM_eFile = Enum_Command_para_JM.û�д��ļ�
         If bDeBug Then
            MsgBox sû�д��ļ�
         End If
      End If
      Exit Function
   End If
Wend
End Function

'�˹���ֻ�����ļ��е����ݿ�
'����ǰҪ���ú��ļ�ָ��(FilePoint),
'���ļ�����(FileLength)
'����Ϊ:Դ�ļ���(SourceFileName)
'��Ŀ���ļ���(DirectioinFileName),PassWordΪ����
Private Function JM_eFileBlock(SourceFilename As String, _
        DirectionFileName As String, FilePoint As Long, _
        FileLength As Long, Optional PassWord As String = "")
Dim SNum As Integer, DNum As Integer
Dim DLen As Long, I As Long, J As Long, b As Byte
Dim s As String
Dim SS(16) As Byte
Dim PS(16) As Byte
Dim Mp(16) As Byte, MS(16) As Byte

'����
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
     'DLen = LOF(DNum) '�õ�Ŀ���ļ�����
     Seek #SNum, FilePoint '����Դ�ļ�ָ�루ָ���ļ����ݿ飩
     '����
     Do While (Seek(SNum) - FilePoint < FileLength) 'ȡ��Դ�ļ�������
           For I = 1 To 16
               '���С��������ݿ�С��8λ
               If Seek(SNum) - FilePoint >= FileLength Then Exit For
               Get #SNum, , SS(I)
           Next I
           If I > 16 Then '�����ļ�
              For I = 16 To 1 Step -1
                     b = SS(I) Xor PS(16 - I + 1)
                  Put #DNum, , b
              Next I
           Else '���С��������ݿ�С��8λ
              For J = 1 To I - 2
                  Put #DNum, , SS(J) Xor PS(J)
              Next J
              'Exit Do
           End If
     Loop
Close #SNum
Close #DNum
End Function

'�õ��ļ�·��
Public Function GetPath(FileName As String) As String
Dim J As Long
'�õ��ļ��е�·��
J = ReverseFindSubStringByte(LTrim(RTrim(FileName)), "\") '�ҵ��ļ�����λ��
'���λ��Ϊ0,�򲻺�·��,������·��
GetPath = IIf(J, LeftByte(LTrim(RTrim( _
        FileName)), J - 1), "")
End Function

'�Ӻ���·�����ļ��еõ����ļ���
Public Function GetFileName(FileName As String) As String
Dim I As Long
'    a.ȥ���ļ��е�·��
I = ReverseFindSubStringByte(LTrim(RTrim(FileName)), "\") '�ҵ��ļ�����λ��
'    b.���λ��Ϊ0,�򲻺�·��,����ȥ��·��
GetFileName = IIf(I, MidByte(LTrim(RTrim(FileName)), I + 1, _
                LenByte(FileName, False) - I), _
                LTrim(RTrim(FileName)))
End Function

'��SourceFileNameString�з���������ļ���
Public Function sGetAllFile(SourceFileNameString As String, FileName() As String)
Dim I As Long, J As Long
Dim Path As String
'��һ���ָ�����λ��
I = InStr(1, SourceFileNameString, Chr(0))
If I = 0 Then 'ֻ��һ���ļ�ʱ
   ReDim FileName(1)
   FileName(1) = SourceFileNameString
   Exit Function
End If
'������ļ�ʱ
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
