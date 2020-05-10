Attribute VB_Name = "StringConversion"
Option Explicit

'从源字符串中从posStart位置开始取出长度为Length的字符串
'Length默认值为1
Public Function MidByte(SourceString As String, ByVal posStart As Long, Optional ByVal Length As Long = 1) As String
Dim b() As Byte, DB() As Byte
b = StrConv(SourceString, vbFromUnicode)
DB = MidB(b, posStart, Length)
MidByte = StrConv(DB, vbUnicode)
End Function

'从源字符串中从最左开始取出长度为Length的字符串
'Length默认值为1
Public Function LeftByte(SourceString As String, Optional ByVal Length As Long = 1) As String
Dim b() As Byte, DB() As Byte
b = StrConv(SourceString, vbFromUnicode)
DB = LeftB(b, Length)
LeftByte = StrConv(DB, vbUnicode)
End Function

'从源字符串中从最右开始取出长度为Length的字符串
'Length默认值为1
Public Function RightByte(SourceString As String, Optional ByVal Length As Long = 1) As String
Dim b() As Byte, DB() As Byte
b = StrConv(SourceString, vbFromUnicode)
DB = RightB(b, Length)
RightByte = StrConv(DB, vbUnicode)
End Function

'按字节求字符串的长度,当TrimFlag为True时取完全长度，当为False取无前导和后缀空格的长度
Public Function LenByte(SourceString As String, Optional TrimFlag As Boolean = True) As String
Dim b() As Byte
If TrimFlag Then
   b = SourceString
Else
   b = Trim(RTrim(SourceString))
End If
LenByte = LenB(StrConv(b, vbFromUnicode))
End Function

'从字节数组转换成字符串
Public Function StringFormByte(SoureByte() As Byte) As String
StringFormByte = StrConv(SoureByte, vbUnicode)
End Function

'从字符串转换成字节数组
Public Function ByteFormString(SourceString As String) As Byte
Dim b() As Byte
b = StrConv(SourceString, vbFromUnicode)
ByteFormString = b
End Function

'倒换字符串
Public Function DiaoFang_eString(SourceString As String) As String
Dim i
For i = 1 To Len(SourceString)
    DiaoFang_eString = Mid(SourceString, i, 1) & DiaoFang_eString
Next i
End Function

'按字节倒换字符串
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

'按字节从字节数组中从posStart位置开始查找子字符串,
'找到返回子字符串在主安息串中的开始位置，否则返回0
Public Function FindSubStringByte(SourceString As String, SubString As String, Optional posStart As Long = 1) As Long
Dim Sb() As Byte, b() As Byte
b = StrConv(SourceString, vbFromUnicode)
Sb = StrConv(SubString, vbFromUnicode)
FindSubStringByte = InStrB(posStart, b, Sb)
End Function

'从字符串尾部posStart位置开始查找子字符串,
'找到返回子字符串在主安息串中的开始位置，否则返回0
'返回值为按字符算
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

'按字节从字节数组尾部posStart位置开始查找子字符串,
'找到返回子字符串在主字符串中的开始位置，否则返回0
'返回值为按字节算
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
