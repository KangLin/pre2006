Option Strict Off
Option Explicit On 

Module API

    Public Const FILE_ATTRIBUTE_DIRECTORY = &H10
    Public Const FILE_ATTRIBUTE_NORMAL = &H80
    Public Const MAX_PATH = 260

    Public Declare Sub Show Lib "Syntax" (ByVal sz As String)
    Public Declare Function ShowLicense Lib "Syntax" () As Boolean
    Public Declare Function FormatVCCode Lib "Syntax" (ByVal szInCode As String, ByVal szOutCode As String) As Integer
    Public Declare Function GetRelativePath Lib "Syntax" (Optional ByVal szDes As String = Nothing, Optional ByVal szSor As String = Nothing, Optional ByVal bChipboard As Boolean = True) As Integer
    Public Declare Function PathRelativePathTo Lib "shlwapi" Alias "PathRelativePathToA" (ByVal pszPath As String, ByVal pszFrom As String, ByVal dwAttrFrom As Integer, ByVal pszTo As String, ByVal dwAttrTo As Integer) As Boolean
    Public Declare Function GetModuleFileName Lib "kernel32" Alias "GetModuleFileNameA" (ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Long
    Public Declare Function SetHook Lib "AutoDisplayConstOrMacro" () As Boolean
    Public Declare Function UnHook Lib "AutoDisplayConstOrMacro" () As Boolean
    Public Declare Function AddListItem Lib "AutoDisplayConstOrMacro" (ByVal szItem As String) As Boolean
    Public Declare Function DeleteListItem Lib "AutoDisplayConstOrMacro" (ByVal szItem As String) As Boolean
    Public Declare Function AddTempList Lib "AutoDisplayConstOrMacro" (ByVal szItem As String) As Boolean
    Public Declare Function DeleteTempList Lib "AutoDisplayConstOrMacro" () As Boolean
    Public Declare Function ValidCCode Lib "Syntax" (ByVal szCode As String) As Integer
End Module
