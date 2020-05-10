; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCrackPasswordDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CrackPassword.h"

ClassCount=3
Class1=CCrackPasswordApp
Class2=CCrackPasswordDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CRACKPASSWORD_DIALOG

[CLS:CCrackPasswordApp]
Type=0
HeaderFile=CrackPassword.h
ImplementationFile=CrackPassword.cpp
Filter=N

[CLS:CCrackPasswordDlg]
Type=0
HeaderFile=CrackPasswordDlg.h
ImplementationFile=CrackPasswordDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_PASSWORD

[CLS:CAboutDlg]
Type=0
HeaderFile=CrackPasswordDlg.h
ImplementationFile=CrackPasswordDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CRACKPASSWORD_DIALOG]
Type=1
Class=CCrackPasswordDlg
ControlCount=5
Control1=IDC_BUTTON_START,button,1342242816
Control2=IDC_BUTTON_END,button,1342242816
Control3=IDC_BUTTON_PAUSE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_PASSWORD,edit,1350631552

