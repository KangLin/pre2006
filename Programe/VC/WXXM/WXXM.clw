; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWXXMDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WXXM.h"

ClassCount=3
Class1=CWXXMApp
Class2=CWXXMDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDM_MAINMENU
Resource2=IDR_MAINFRAME
Resource3=IDD_WXXM_DIALOG
Resource4=IDR_MAINMENU
Resource5=IDM_TRAYICON
Resource6=IDD_ABOUTBOX

[CLS:CWXXMApp]
Type=0
HeaderFile=WXXM.h
ImplementationFile=WXXM.cpp
Filter=N

[CLS:CWXXMDlg]
Type=0
HeaderFile=WXXMDlg.h
ImplementationFile=WXXMDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDM_KEYPROMPT

[CLS:CAboutDlg]
Type=0
HeaderFile=WXXMDlg.h
ImplementationFile=WXXMDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177294
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308353

[DLG:IDD_WXXM_DIALOG]
Type=1
Class=CWXXMDlg
ControlCount=0

[MNU:IDR_MAINMENU]
Type=1
Command1=IDM_EXIT
Command2=IDM_ABOUT
CommandCount=2

[MNU:IDM_TRAYICON]
Type=1
Class=?
Command1=IDM_OPEN
Command2=IDM_KEYPROMPT
Command3=IDM_ABOUT
Command4=IDM_EXIT
CommandCount=4

[MNU:IDM_MAINMENU]
Type=1
Class=CWXXMDlg
Command1=IDM_EXIT
Command2=IDM_ABOUT
Command3=IDM_KEYPROMPT
CommandCount=3

