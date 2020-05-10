; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSearchView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Search.h"
LastPage=0

ClassCount=8
Class1=CSearchApp
Class2=CSearchDoc
Class3=CSearchView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_SEARCHTYPE
Resource2=IDR_MAINFRAME
Resource3=IDD_SEARCH_FORM
Class5=CChildFrame
Class6=CAboutDlg
Class7=CPromp
Resource4=IDD_ABOUTBOX
Class8=CPrompt
Resource5=IDD_PROMPT_DIALOG

[CLS:CSearchApp]
Type=0
HeaderFile=Search.h
ImplementationFile=Search.cpp
Filter=N

[CLS:CSearchDoc]
Type=0
HeaderFile=SearchDoc.h
ImplementationFile=SearchDoc.cpp
Filter=N
LastObject=CSearchDoc

[CLS:CSearchView]
Type=0
HeaderFile=SearchView.h
ImplementationFile=SearchView.cpp
Filter=D
LastObject=CSearchView
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=Search.cpp
ImplementationFile=Search.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_SEARCHTYPE]
Type=1
Class=CSearchView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=IDM_TOOL_FINDFILE
Command18=IDM_TOOL_WORD
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_SEARCH_FORM]
Type=1
Class=CSearchView
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PATH,edit,1350631552
Control3=IDC_BROWE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FILENAME,edit,1350631552
Control6=IDC_SEARCH,button,1342242816
Control7=IDC_FILE,listbox,1352728835

[CLS:CPromp]
Type=0
HeaderFile=Promp.h
ImplementationFile=Promp.cpp
BaseClass=CDialog
Filter=D
LastObject=CPromp

[DLG:IDD_PROMPT_DIALOG]
Type=1
Class=CPrompt
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:CPrompt]
Type=0
HeaderFile=Prompt.h
ImplementationFile=Prompt.cpp
BaseClass=CDialog
Filter=D
LastObject=CPrompt

