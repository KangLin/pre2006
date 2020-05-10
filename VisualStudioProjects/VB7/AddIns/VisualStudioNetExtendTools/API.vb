'*******************************************************************************************************
'版权所有 (C) 2006 康林工作室；保留所有权利。
'文件名：API.vb
'描  述：API接口
'版  本：2006.1.1.0
'作  者：康  林
'E_Mail：kl222@126.com
'日  期：2006年2月15日
'时  间：8:39:56
'编译器：Microsoft Development Environment 7.10 —— Basic 7.10
'*******************************************************************************************************
Option Strict Off
Option Explicit On 

Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If

Module API

    Public Const FILE_ATTRIBUTE_DIRECTORY = &H10
    Public Const FILE_ATTRIBUTE_NORMAL = &H80
    Public Const MAX_PATH = 260

    Public Const WH_KEYBOARD = 2
    Public Const WH_GETMESSAGE = 3

    Public Declare Function SetWindowsHookEx Lib "user32" Alias "SetWindowsHookExA" (ByVal idHook As Integer, ByVal lpfn As Integer, ByVal hmod As Integer, ByVal dwThreadId As Integer) As Integer
    Public Declare Function GetCurrentThreadId Lib "kernel32" Alias "GetCurrentThreadId" () As Integer
    Public Declare Function UnhookWindowsHookEx Lib "user32" Alias "UnhookWindowsHookEx" (ByVal hHook As Integer) As Integer

    Public Declare Sub Show Lib "Syntax" (ByVal sz As String)
    Public Declare Function Register Lib "Syntax" Alias "#11" (Optional ByVal bShow As Boolean = False, Optional ByVal szKey As String = vbNullString, Optional ByVal bTrueShow As Boolean = False) As Boolean
    Public Declare Function ShowLicense Lib "ShowDialog" () As Integer
    Public Declare Unicode Function GetDLLPath Lib "Syntax" (ByRef szPath As String) As Integer
    Public Declare Unicode Function ValidCCode Lib "Syntax" Alias "ValidCCodeW" (ByVal szInCode As String, ByRef szOutCode As String, Optional ByVal bQutation As Boolean = True, Optional ByVal bComment As Boolean = False) As Integer
    Public Declare Unicode Function FormatVCCode Lib "Syntax" Alias "FormatVCCodeW" (ByVal szInCode As String, ByRef szOutCode As String) As Integer
    Public Declare Unicode Function MatchSplitSymbolB Lib "Syntax" (ByRef szInCode As String, ByRef szStr1 As String, ByRef szStr2 As String, Optional ByRef szBefor As String = Nothing, Optional ByRef szBack As String = Nothing, Optional ByVal bQutation As Boolean = True, Optional ByVal bReversionQutation As Boolean = False) As Integer

    Public Declare Unicode Function GetRelativePath Lib "Syntax" (Optional ByRef szDes As String = Nothing, Optional ByVal szSor As String = Nothing, Optional ByVal bChipboard As Boolean = True) As Integer
    Public Declare Function PathRelativePathTo Lib "shlwapi" Alias "PathRelativePathToA" (ByVal pszPath As String, ByVal pszFrom As String, ByVal dwAttrFrom As Integer, ByVal pszTo As String, ByVal dwAttrTo As Integer) As Boolean
    Public Declare Unicode Function PathRelativePath Lib "Syntax" (ByRef pszPath As String, ByVal pszFrom As String, ByVal dwAttrFrom As Integer, ByVal pszTo As String, ByVal dwAttrTo As Integer) As Integer
    Public Declare Function FullPath Lib "Syntax" (ByVal pszPath As String, ByVal pszFrom As String, ByVal pszCurPath As String) As Integer
    Public Declare Function GetModuleFileName Lib "kernel32" Alias "GetModuleFileNameA" (ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Integer

    Public Declare Function HtmlHelp Lib "HHCtrl.ocx" Alias "HtmlHelpA" (ByVal hwndCaller As Long, ByVal pszFile As String, ByVal uCommand As Long, ByVal dwData As Long) As Long
    Public Declare Function ShowHelp Lib "Syntax" () As Boolean
    Public Declare Function ShowVersion Lib "Syntax" () As Boolean

    Public Declare Function SetHook Lib "AutoDisplayConstOrMacro" () As Boolean
    Public Declare Function UnHook Lib "AutoDisplayConstOrMacro" () As Boolean
    Public Declare Function AddListItem Lib "AutoDisplayConstOrMacro" (ByVal szItem As String) As Boolean
    Public Declare Function DeleteListItem Lib "AutoDisplayConstOrMacro" (ByVal szItem As String) As Boolean
    Public Declare Function AddTempList Lib "AutoDisplayConstOrMacro" (ByVal szItem As String) As Boolean
    Public Declare Function DeleteTempList Lib "AutoDisplayConstOrMacro" () As Boolean
    
    Public Declare Unicode Function InitKeyInputCom Lib "AddInsInput" Alias "Init" (ByVal DTE As EnvDTE.DTE) As Boolean
    Public Declare Sub FreeKeyInputCom Lib "AddInsInput" Alias "Free" ()
    Public Declare Unicode Function AfterKeyPress Lib "AddInsInput" (ByVal Keypress As String) As Integer
    Public Declare Unicode Function BeforeKeyPress Lib "AddInsInput" (ByVal Keypress As String) As Boolean
    Public Declare Function Sol_Open Lib "AddInsInput" () As Integer
    Public Declare Unicode Function Sol_ProjectAdded Lib "AddInsInput" (ByVal prj As Project) As Integer
    Public Declare Unicode Function Pro_ItemAdded Lib "AddInsInput" (ByVal ProjectItem As EnvDTE.ProjectItem) As Boolean
    Public Declare Function Sol_AfterClosing Lib "AddInsInput" () As Integer

End Module
