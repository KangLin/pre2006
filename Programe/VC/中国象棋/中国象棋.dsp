# Microsoft Developer Studio Project File - Name="�й�����" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=�й����� - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "�й�����.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "�й�����.mak" CFG="�й����� - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "�й����� - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "�й����� - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "�й����� - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "�й����� - Win32 Debug"

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

# Name "�й����� - Win32 Release"
# Name "�й����� - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobeFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XQ\xq.cpp
# End Source File
# Begin Source File

SOURCE=".\�й�����.cpp"
# End Source File
# Begin Source File

SOURCE=".\�й�����.rc"
# End Source File
# Begin Source File

SOURCE=".\�й�����Doc.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\GlobeConst.h
# End Source File
# Begin Source File

SOURCE=.\GlobeFunction.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XQ\xq.h
# End Source File
# Begin Source File

SOURCE=".\�й�����.h"
# End Source File
# Begin Source File

SOURCE=".\�й�����Doc.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\picture\ARW09LT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\picture\BShuai.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture\Close.ico
# End Source File
# Begin Source File

SOURCE=.\res\picture\Exit.ico
# End Source File
# Begin Source File

SOURCE=.\res\picture\HELP.BMP
# End Source File
# Begin Source File

SOURCE=.\res\picture\HELP.CUR
# End Source File
# Begin Source File

SOURCE=.\res\picture\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\picture\idr_desk.ico
# End Source File
# Begin Source File

SOURCE=.\res\picture\idr_main.ico
# End Source File
# Begin Source File

SOURCE=".\res\picture\Key manager.ico"
# End Source File
# Begin Source File

SOURCE=.\res\picture\KL.BMP
# End Source File
# Begin Source File

SOURCE=.\res\picture\MAIL12.ICO
# End Source File
# Begin Source File

SOURCE=.\res\picture\NETHOOD.ICO
# End Source File
# Begin Source File

SOURCE=.\res\picture\RShuai.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture\Sky.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture\start1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture\Time.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture\Undo.ico
# End Source File
# Begin Source File

SOURCE=.\res\picture\Video.ico
# End Source File
# Begin Source File

SOURCE=".\res\picture\�ݵ�.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\����1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\ֹͣ1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\����.ICO"
# End Source File
# Begin Source File

SOURCE=".\res\picture\�ұ�����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�й�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�й�����.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\�й�����Doc.ico"
# End Source File
# Begin Source File

SOURCE=".\res\picture\����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\picture\�������.bmp"
# End Source File
# End Group
# Begin Group "chess"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Chess\tishi.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Chess\tishi.h
# End Source File
# Begin Source File

SOURCE=".\Chess\�й�����View.cpp"
# End Source File
# Begin Source File

SOURCE=".\Chess\�й�����View.h"
# End Source File
# End Group
# Begin Group "Desk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Desk\desk.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Desk\desk.h
# End Source File
# Begin Source File

SOURCE=.\Desk\DeskView.cpp
# End Source File
# Begin Source File

SOURCE=.\Desk\deskview.h
# End Source File
# End Group
# Begin Group "TextMessage"

# PROP Default_Filter ""
# Begin Group "RichText"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RichText\font.cpp
# End Source File
# Begin Source File

SOURCE=.\RichText\font.h
# End Source File
# Begin Source File

SOURCE=.\RichText\oleobject.cpp
# End Source File
# Begin Source File

SOURCE=.\RichText\oleobject.h
# End Source File
# Begin Source File

SOURCE=.\RichText\oleobjects.cpp
# End Source File
# Begin Source File

SOURCE=.\RichText\oleobjects.h
# End Source File
# Begin Source File

SOURCE=.\RichText\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\RichText\picture.h
# End Source File
# Begin Source File

SOURCE=.\RichText\richtext.cpp
# End Source File
# Begin Source File

SOURCE=.\RichText\richtext.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TextMessage\textmessage.cpp
# End Source File
# Begin Source File

SOURCE=.\TextMessage\textmessage.h
# End Source File
# End Group
# Begin Group "Video"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AV\ctrvideo.cpp
# End Source File
# Begin Source File

SOURCE=.\AV\ctrvideo.h
# End Source File
# Begin Source File

SOURCE=.\AV\displayvideo.cpp
# End Source File
# Begin Source File

SOURCE=.\AV\displayvideo.h
# End Source File
# Begin Source File

SOURCE=.\AV\video.cpp
# End Source File
# Begin Source File

SOURCE=.\AV\video.h
# End Source File
# Begin Source File

SOURCE=.\AV\VideoConnectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AV\VideoConnectDlg.h
# End Source File
# End Group
# Begin Group "UserInfo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UserInfo\userinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\UserInfo\userinfo.h
# End Source File
# End Group
# Begin Group "InterFace"

# PROP Default_Filter ""
# Begin Group "Button"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\��\Control\ButtonST\BCMenu.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\BCMenu.h"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\BtnST.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\BtnST.h"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\CeXDib.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\CeXDib.h"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\ShadeButtonST.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\ShadeButtonST.h"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\WinXPButtonST.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ButtonST\WinXPButtonST.h"
# End Source File
# End Group
# Begin Group "CoolControl"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\��\Control\CoolTabContrl\CoolTabCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\CoolTabContrl\CoolTabCtrl.h"
# End Source File
# Begin Source File

SOURCE="..\��\Control\SizeBarControl\scbarg.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\SizeBarControl\scbarg.h"
# End Source File
# Begin Source File

SOURCE="..\��\Control\SizeBarControl\sizecbar.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\SizeBarControl\sizecbar.h"
# End Source File
# End Group
# Begin Group "ToolBarEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\��\Control\ToolBar\ToolBarEx\ToolBarEx.cpp"
# End Source File
# Begin Source File

SOURCE="..\��\Control\ToolBar\ToolBarEx\ToolBarEx.h"
# End Source File
# End Group
# Begin Group "CStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Controls\CStaticEx\staticex.cpp
# ADD CPP /I "..\..\�й�����"
# End Source File
# Begin Source File

SOURCE=..\Controls\CStaticEx\staticex.h
# End Source File
# End Group
# Begin Group "CPicture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Picture\CIPicture\CIPicture.cpp
# End Source File
# Begin Source File

SOURCE=..\Picture\CIPicture\CIPicture.h
# End Source File
# End Group
# End Group
# Begin Group "sock"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\UDPSock\UDPSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\UDPSock\UDPSocket.h
# End Source File
# End Group
# Begin Group "logon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\logon\LogonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\logon\LogonDlg.h
# End Source File
# Begin Source File

SOURCE=.\logon\RegistDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\logon\RegistDlg.h
# End Source File
# End Group
# Begin Group "command"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\command\command.cpp
# End Source File
# Begin Source File

SOURCE=.\command\command.h
# End Source File
# End Group
# Begin Group "XQ"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section �й����� : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture1
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section �й����� : {E64CBBBF-1B35-4334-B97A-F04207F383D8}
# 	2:5:Class:CXQ
# 	2:10:HeaderFile:xq.h
# 	2:8:ImplFile:xq.cpp
# End Section
# Section �й����� : {071AD322-22BA-45BF-9E1F-154EFAF4E42B}
# 	2:21:DefaultSinkHeaderFile:xq.h
# 	2:16:DefaultSinkClass:CXQ
# End Section
