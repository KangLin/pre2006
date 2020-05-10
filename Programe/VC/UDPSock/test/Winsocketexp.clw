; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWinsocketexpDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "winsocketexp.h"
LastPage=0

ClassCount=4
Class1=CWinsocketexpApp
Class2=CAboutDlg
Class3=CWinsocketexpDlg

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class4=CUDPSocket
Resource2=IDD_WINSOCKETEXP_DIALOG

[CLS:CWinsocketexpApp]
Type=0
BaseClass=CWinApp
HeaderFile=Winsocketexp.h
ImplementationFile=Winsocketexp.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=WinsocketexpDlg.cpp
ImplementationFile=WinsocketexpDlg.cpp
LastObject=CAboutDlg

[CLS:CWinsocketexpDlg]
Type=0
BaseClass=CDialog
HeaderFile=WinsocketexpDlg.h
ImplementationFile=WinsocketexpDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDITSEND

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WINSOCKETEXP_DIALOG]
Type=1
Class=CWinsocketexpDlg
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDITREMOTIP,edit,1350631552
Control8=IDC_EDITREMOTPORT,edit,1350631552
Control9=IDC_EDITLOCATEIP,edit,1350631552
Control10=IDC_EDITLOCATPORT,edit,1350631552
Control11=IDC_EDITSEND,edit,1350631552
Control12=IDC_BUTTONSEND,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_LIST1,listbox,1352728835
Control15=IDC_BUTTONCONNECT,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_LIST_SEND,listbox,1352728835

[CLS:CUDPSocket]
Type=0
HeaderFile=UDPSocket.h
ImplementationFile=UDPSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CUDPSocket
VirtualFilter=uq

