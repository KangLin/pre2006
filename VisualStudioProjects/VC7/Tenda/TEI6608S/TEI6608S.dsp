# Microsoft Developer Studio Project File - Name="TEI6608S" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TEI6608S - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TEI6608S.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TEI6608S.mak" CFG="TEI6608S - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TEI6608S - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TEI6608S - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TEI6608S - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "TEI6608S - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TEI6608S - Win32 Release"
# Name "TEI6608S - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\6608STest.cpp
# End Source File
# Begin Source File

SOURCE=.\6608TFTP.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\Rule\buildrule.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\CheckPort\CCombineCheckPort.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\HTML\checkhtmlfile.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\CheckPort\CheckPort.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\CommonFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\ICMP\ICMP.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\Logon.cpp
# End Source File
# Begin Source File

SOURCE=.\Set6608MAC.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\WriteMAC\SetMAC.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\SetTestSock.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TEI6608S.cpp
# End Source File
# Begin Source File

SOURCE=.\TEI6608S.rc
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\Test.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\TestItem.cpp
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\TFTP\TFTP.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\6608STest.h
# End Source File
# Begin Source File

SOURCE=.\6608TFTP.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\Rule\buildrule.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\HTML\checkhtmlfile.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\CheckPort\CheckPort.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\CheckPort\CombineCheckPort.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\CommonFunction.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\ICMP\ICMP.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\Logon.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Set6608MAC.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\WriteMAC\SetMAC.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\SetTestSock.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TEI6608S.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\Test.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\TestItem.h
# End Source File
# Begin Source File

SOURCE=..\TestTemplet\NET\TFTP\TFTP.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
