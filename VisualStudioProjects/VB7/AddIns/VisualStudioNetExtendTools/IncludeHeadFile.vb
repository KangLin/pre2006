Option Strict Off
Option Explicit On 
Imports EnvDTE
#If VER_2005 Then
Imports EnvDTE80
#End If
Imports System.ComponentModel
Imports Microsoft.Win32
Imports System.Text.RegularExpressions
Imports Microsoft.VisualBasic

Public Class IncludeHeadFile
#If VER_2003 Then
    Dim m_DTE As EnvDTE.DTE
#End If
#If VER_2005 Then
    Dim m_DTE As EnvDTE80.DTE2
#End If
    Dim m_Instance As EnvDTE.AddIn
    Dim Sel As TextSelection

    Public WriteOnly Property DTE(ByVal objDTE As EnvDTE.DTE)
        Set(ByVal Value)
            m_DTE = objDTE
        End Set
    End Property


End Class
