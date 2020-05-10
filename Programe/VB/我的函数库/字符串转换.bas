Attribute VB_Name = "StringConversion"
Option Explicit

'��Դ�ַ����д�posStartλ�ÿ�ʼȡ������ΪLength���ַ���
'LengthĬ��ֵΪ1
Public Function MidByte(SourceString As String, ByVal posStart As Long, Optional ByVal Length As Long = 1) As String
Dim b() As Byte, DB() As Byte
b = StrConv(SourceString, vbFromUnicode)
DB = MidB(b, posStart, Length)
MidByte = StrConv(DB, vbUnicode)
End Function

'��Դ�ַ����д�����ʼȡ������ΪLength���ַ���
'LengthĬ��ֵΪ1
Public Function LeftByte(SourceString As String, Optional ByVal Length As Long = 1) As String
Dim b() As Byte, DB() As Byte
b = StrConv(SourceString, vbFromUnicode)
DB = LeftB(b, Length)
LeftByte = StrConv(DB, vbUnicode)
End Function

'��Դ�ַ����д����ҿ�ʼȡ������ΪLength���ַ���
'LengthĬ��ֵΪ1
Public Function RightByte(SourceString As String, Optional ByVal Length As Long = 1) As String
Dim b() As Byte, DB() As Byte
b = StrConv(SourceString, vbFromUnicode)
DB = RightB(b, Length)
RightByte = StrConv(DB, vbUnicode)
End Function

'���ֽ����ַ����ĳ���,��TrimFlagΪTrueʱȡ��ȫ���ȣ���ΪFalseȡ��ǰ���ͺ�׺�ո�ĳ���
Public Function LenByte(SourceString As String, Optional TrimFlag As Boolean = True) As String
Dim b() As Byte
If TrimFlag Then
   b = SourceString
Else
   b = Trim(RTrim(SourceString))
End If
LenByte = LenB(StrConv(b, vbFromUnicode))
End Function

'���ֽ�����ת�����ַ���
Public Function StringFormByte(SoureByte() As Byte) As String
StringFormByte = StrConv(SoureByte, vbUnicode)
End Function

'���ַ���ת�����ֽ�����
Public Function ByteFormString(SourceString As String) As Byte
Dim b() As Byte
b = StrConv(SourceString, vbFromUnicode)
ByteFormString = b
End Function

'�����ַ���
Public Function DiaoFang_eString(SourceString As String) As String
Dim i
For i = 1 To Len(SourceString)
    DiaoFang_eString = Mid(SourceString, i, 1) & DiaoFang_eString
Next i
End Function

'���ֽڵ����ַ���
Public Function DiaoFang_eStringByte(SourceString As String) As String
Dim b() As Byte, i As Long, B1 As Byte, K As Long
K = LenByte(SourceString)
b = StrConv(SourceString, vbFromUnicode)
For i = 0 To K \ 2 - 1
    B1 = b(i)
    b(i) = b(K - i - 1)
    b(K - i - 1) = B1
Next i
DiaoFang_eStringByte = StrConv(b, vbUnicode)
End Function

'���ֽڴ��ֽ������д�posStartλ�ÿ�ʼ�������ַ���,
'�ҵ��������ַ���������Ϣ���еĿ�ʼλ�ã����򷵻�0
Public Function FindSubStringByte(SourceString As String, SubString As String, Optional posStart As Long = 1) As Long
Dim Sb() As Byte, b() As Byte
b = StrConv(SourceString, vbFromUnicode)
Sb = StrConv(SubString, vbFromUnicode)
FindSubStringByte = InStrB(posStart, b, Sb)
End Function

'���ַ���β��posStartλ�ÿ�ʼ�������ַ���,
'�ҵ��������ַ���������Ϣ���еĿ�ʼλ�ã����򷵻�0
'����ֵΪ���ַ���
Public Function ReverseFindSubString(SourceString As String, SubString As String, Optional posStart As Long = 1)
Dim s As String, SS As String, K As Long
s = DiaoFang_eString(SourceString)
SS = DiaoFang_eString(SubString)
K = InStr(posStart, s, SS)
If K > 0 Then
   ReverseFindSubString = Len(SourceString) - _
                 (K + _
                  Len(SubString) - 1) + 1
Else
   ReverseFindSubString = 0
End If
End Function

'���ֽڴ��ֽ�����β��posStartλ�ÿ�ʼ�������ַ���,
'�ҵ��������ַ��������ַ����еĿ�ʼλ�ã����򷵻�0
'����ֵΪ���ֽ���
Public Function ReverseFindSubStringByte(SourceString As String, SubString As String, Optional posStart As Long = 1) As Long
Dim s As String, SS As String, K As Long
s = DiaoFang_eStringByte(SourceString)
SS = DiaoFang_eStringByte(SubString)
K = FindSubStringByte(s, SS, posStart)
If K > 0 Then
   ReverseFindSubStringByte = LenByte(SourceString) - _
                 (K + _
                  LenByte(SubString) - 1) + 1
Else
   ReverseFindSubStringByte = 0
End If
End Function
