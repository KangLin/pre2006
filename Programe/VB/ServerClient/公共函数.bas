Attribute VB_Name = "��������"
'*****************************************************************************
'      ��      ��      ��      ��     ��      ��      ��      ��
'                                �� ��:  �� ��
'*****************************************************************************
Option Explicit

'����:���ڷ�������:<string1><NULL><string2><NULL>����<NULL><NULL>���ַ���
'����:sString��������ַ���.�����Ϊʣ�µ��ַ���:<string2><NULL>����<NULL><NULL>
'����ֵ:����������ַ���<string1>
'       �������,�򷵻�vbNullString
Public Function fSplitString(ByRef sString As String) As String
Dim i As Integer
i = InStr(1, sString, Chr$(0))
If i > 1 Then
   fSplitString = Left(sString, i - 1)
   sString = Right(sString, Len(sString) - i)
Else
   fSplitString = vbNullString
End If
End Function
