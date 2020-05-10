Attribute VB_Name = "公共函数"
'*****************************************************************************
'      服      务      客      户     公      共      函      数
'                                设 计:  康 林
'*****************************************************************************
Option Explicit

'功能:用于分离形如:<string1><NULL><string2><NULL>……<NULL><NULL>的字符串
'参数:sString待分离的字符串.分离后为剩下的字符串:<string2><NULL>……<NULL><NULL>
'返回值:分离出来的字符串<string1>
'       如果结束,则返回vbNullString
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
