# Microsoft Developer Studio Project File - Name="中国象棋服务器" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=中国象棋服务器 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "中国象棋服务器.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "中国象棋服务器.mak" CFG="中国象棋服务器 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "中国象棋服务器 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "中国象棋服务器 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "中国象棋服务器 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "中国象棋服务器 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "中国象棋服务器 - Win32 Release"
# Name "中国象棋服务器 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\GlobeFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\中国象棋服务器.rc"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\GlobeConst.h
# End Source File
# Begin Source File

SOURCE=..\GlobeFunction.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=".\res\中国象棋服务器.ico"
# End Source File
# Begin Source File

SOURCE=".\res\中国象棋服务器.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\中国象棋服务器Doc.ico"
# End Source File
# End Group
# Begin Group "DataGrid"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataGrid\column.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\column.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\columns.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\columns.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\dataformatdisp.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\dataformatdisp.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\datagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\datagrid.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\font.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\font.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\picture.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\selbookmarks.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\selbookmarks.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\split.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\split.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\splits.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\splits.h
# End Source File
# Begin Source File

SOURCE=.\DataGrid\stddataformatsdisp.cpp
# End Source File
# Begin Source File

SOURCE=.\DataGrid\stddataformatsdisp.h
# End Source File
# End Group
# Begin Group "MainFrame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=".\中国象棋服务器.cpp"
# End Source File
# Begin Source File

SOURCE=".\中国象棋服务器.h"
# End Source File
# Begin Source File

SOURCE=".\中国象棋服务器Doc.cpp"
# End Source File
# Begin Source File

SOURCE=".\中国象棋服务器Doc.h"
# End Source File
# Begin Source File

SOURCE=".\中国象棋服务器View.cpp"
# End Source File
# Begin Source File

SOURCE=".\中国象棋服务器View.h"
# End Source File
# End Group
# Begin Group "Ado"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\库\Database\Ado\Ado.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\库\Database\Ado\Ado.h"
# End Source File
# Begin Source File

SOURCE="..\..\库\Database\Ado\AdoCommand.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\库\Database\Ado\AdoCommand.h"
# End Source File
# Begin Source File

SOURCE="..\..\库\Database\Ado\AdoRecordSet.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\库\Database\Ado\AdoRecordSet.h"
# End Source File
# End Group
# Begin Group "UDPSocket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\UDPSock\UDPSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UDPSock\UDPSocket.h
# End Source File
# End Group
# Begin Group "Process"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Process\Process.cpp
# End Source File
# Begin Source File

SOURCE=.\Process\Process.h
# End Source File
# End Group
# Begin Group "command"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\command\command.cpp
# End Source File
# Begin Source File

SOURCE=..\command\command.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section 中国象棋服务器 : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section 中国象棋服务器 : {CDE57A41-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CDataGrid
# 	2:10:HeaderFile:datagrid.h
# 	2:8:ImplFile:datagrid.cpp
# End Section
# Section 中国象棋服务器 : {CDE57A50-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumns
# 	2:10:HeaderFile:columns.h
# 	2:8:ImplFile:columns.cpp
# End Section
# Section 中国象棋服务器 : {CDE57A54-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplit
# 	2:10:HeaderFile:split.h
# 	2:8:ImplFile:split.cpp
# End Section
# Section 中国象棋服务器 : {E675F3F0-91B5-11D0-9484-00A0C91110ED}
# 	2:5:Class:CDataFormatDisp
# 	2:10:HeaderFile:dataformatdisp.h
# 	2:8:ImplFile:dataformatdisp.cpp
# End Section
# Section 中国象棋服务器 : {99FF4676-FFC3-11D0-BD02-00C04FC2FB86}
# 	2:5:Class:CStdDataFormatsDisp
# 	2:10:HeaderFile:stddataformatsdisp.h
# 	2:8:ImplFile:stddataformatsdisp.cpp
# End Section
# Section 中国象棋服务器 : {CDE57A4F-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumn
# 	2:10:HeaderFile:column.h
# 	2:8:ImplFile:column.cpp
# End Section
# Section 中国象棋服务器 : {CDE57A53-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplits
# 	2:10:HeaderFile:splits.h
# 	2:8:ImplFile:splits.cpp
# End Section
# Section 中国象棋服务器 : {CDE57A43-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:21:DefaultSinkHeaderFile:datagrid.h
# 	2:16:DefaultSinkClass:CDataGrid
# End Section
# Section 中国象棋服务器 : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section 中国象棋服务器 : {CDE57A52-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSelBookmarks
# 	2:10:HeaderFile:selbookmarks.h
# 	2:8:ImplFile:selbookmarks.cpp
# End Section
