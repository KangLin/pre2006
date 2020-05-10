; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChessView
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "中国象棋.h"
LastPage=0
CDK=Y

ClassCount=24
Class1=CStaticEx
Class2=CUDPSocket
Class3=CButtonST
Class4=CCoolTabCtrl
Class5=CCoolBar
Class6=CSizingControlBar
Class7=CSCBMiniDockFrameWnd
Class8=CToolBarEx
Class9=CVideo
Class10=CVideoConnectDlg
Class11=CChessView
Class12=CChildFrame
Class13=CDesk
Class14=CDeskView
Class15=CLogonDlg
Class16=CRegistDlg
Class17=CMainFrame
Class18=CTextMessage
Class19=CUserInfo
Class20=CChessApp
Class21=CAboutDlg
Class22=CChessDoc
Class23=CChair

ResourceCount=13
Resource1=IDD_DESKVIEW_FORM
Resource2=IDR_MAINFRAME
Resource3=IDR_DESKVIEW_TMPL
Resource4=IDD_CHESS_FORM
Resource5=IDD_VIDEOCONNECTDLG_DIALOG
Resource6=IDD_ABOUTBOX
Resource7=IDM_CHAIR
Resource8=IDD_USERINFO
Resource9=IDD_REGISTDLG_DIALOG
Resource10=IDD_LOGONDLG_DIALOG
Resource11=IDD_VIDEO
Class24=CTiShi
Resource12=IDD_TEXTMESSAGE
Resource13=IDD_SETDLG

[CLS:CStaticEx]
Type=0
BaseClass=CWnd
HeaderFile=\Programe\VC\Controls\CStaticEx\staticex.h
ImplementationFile=\Programe\VC\Controls\CStaticEx\staticex.cpp
LastObject=CStaticEx

[CLS:CChair]
Type=0
HeaderFile=desk\desk.h
ImplementationFile=desk\desk.cpp
BaseClass=CStaticEx
;Filter=W
LastObject=CChair
Filter=W
VirtualFilter=WC

[CLS:CUDPSocket]
Type=0
BaseClass=CSocket
HeaderFile=\Programe\VC\UDPSock\UDPSocket.h
ImplementationFile=\Programe\VC\UDPSock\UDPSocket.cpp

[CLS:CButtonST]
Type=0
BaseClass=CButton
HeaderFile=\Programe\VC\库\Control\ButtonST\BtnST.h
ImplementationFile=\Programe\VC\库\Control\ButtonST\BtnST.cpp

[CLS:CCoolTabCtrl]
Type=0
BaseClass=CWnd
HeaderFile=\Programe\VC\库\Control\CoolTabContrl\CoolTabCtrl.h
ImplementationFile=\Programe\VC\库\Control\CoolTabContrl\CoolTabCtrl.cpp
LastObject=CCoolTabCtrl

[CLS:CCoolBar]
Type=0
BaseClass=baseCCoolBar
HeaderFile=\Programe\VC\库\Control\SizeBarControl\scbarg.h
ImplementationFile=\Programe\VC\库\Control\SizeBarControl\scbarg.cpp
LastObject=CCoolBar

[CLS:CSizingControlBar]
Type=0
BaseClass=baseCSizingControlBar
HeaderFile=\Programe\VC\库\Control\SizeBarControl\sizecbar.h
ImplementationFile=\Programe\VC\库\Control\SizeBarControl\sizecbar.cpp

[CLS:CSCBMiniDockFrameWnd]
Type=0
BaseClass=baseCSCBMiniDockFrameWnd
HeaderFile=\Programe\VC\库\Control\SizeBarControl\sizecbar.h
ImplementationFile=\Programe\VC\库\Control\SizeBarControl\sizecbar.cpp

[CLS:CToolBarEx]
Type=0
BaseClass=CToolBar
HeaderFile=\Programe\VC\库\Control\ToolBar\ToolBarEx\ToolBarEx.h
ImplementationFile=\Programe\VC\库\Control\ToolBar\ToolBarEx\ToolBarEx.cpp
LastObject=CToolBarEx

[CLS:CVideo]
Type=0
BaseClass=CDialog
HeaderFile=AV\video.h
ImplementationFile=AV\video.cpp

[CLS:CVideoConnectDlg]
Type=0
BaseClass=CDialog
HeaderFile=AV\VideoConnectDlg.h
ImplementationFile=AV\VideoConnectDlg.cpp

[CLS:CChessView]
Type=0
BaseClass=CFormView
HeaderFile=Chess\中国象棋View.h
ImplementationFile=Chess\中国象棋View.cpp
LastObject=CChessView
Filter=D
VirtualFilter=VWC

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CDesk]
Type=0
BaseClass=CWnd
HeaderFile=Desk\desk.h
ImplementationFile=Desk\desk.cpp
LastObject=CDesk

[CLS:CDeskView]
Type=0
BaseClass=CScrollView
HeaderFile=Desk\deskview.h
ImplementationFile=Desk\DeskView.cpp
LastObject=CDeskView
Filter=C
VirtualFilter=VWC

[CLS:CLogonDlg]
Type=0
BaseClass=CDialog
HeaderFile=logon\LogonDlg.h
ImplementationFile=logon\LogonDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CLogonDlg

[CLS:CRegistDlg]
Type=0
BaseClass=CDialog
HeaderFile=logon\RegistDlg.h
ImplementationFile=logon\RegistDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDITPASSWORD

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame
Filter=T
VirtualFilter=fWC

[CLS:CTextMessage]
Type=0
BaseClass=CDialog
HeaderFile=TextMessage\textmessage.h
ImplementationFile=TextMessage\textmessage.cpp
LastObject=IDC_RICHTEXTRECEIVE

[CLS:CUserInfo]
Type=0
BaseClass=CDialog
HeaderFile=UserInfo\userinfo.h
ImplementationFile=UserInfo\userinfo.cpp
Filter=D
VirtualFilter=dWC
LastObject=CUserInfo

[CLS:CChessApp]
Type=0
BaseClass=CWinApp
HeaderFile=中国象棋.h
ImplementationFile=中国象棋.cpp
LastObject=CChessApp
Filter=N

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=中国象棋.cpp
ImplementationFile=中国象棋.cpp
LastObject=CAboutDlg

[CLS:CChessDoc]
Type=0
BaseClass=CDocument
HeaderFile=中国象棋Doc.h
ImplementationFile=中国象棋Doc.cpp

[DLG:IDD_VIDEO]
Type=1
Class=CVideo
ControlCount=1
Control1=IDC_DISPLAYVIDEO,{AFD9EC81-5CED-4D82-BA94-819086C4D569},1342242816

[DLG:IDD_VIDEOCONNECTDLG_DIALOG]
Type=1
Class=CVideoConnectDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDITVIDEOCONNECTUSERNAME,edit,1350631553
Control4=IDC_STATIC,static,1342308353

[DLG:IDD_CHESS_FORM]
Type=1
Class=CChessView
ControlCount=3
Control1=IDC_REDUSERNAME,static,1073872897
Control2=IDC_BLACKUSERNAME,static,1073872897
Control3=IDC_XQ,{071AD322-22BA-45BF-9E1F-154EFAF4E42B},1342242816

[DLG:IDD_LOGONDLG_DIALOG]
Type=1
Class=CLogonDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDITREMOTEPORT,edit,1350639746
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDITUSERNAME,edit,1350631552
Control10=IDC_EDITPASSWORD,edit,1350631584
Control11=IDC_EDITVALIDATE,edit,1350639746
Control12=IDC_EDITVALIDATECODE,edit,1484857472
Control13=IDC_REGIST,button,1342242816
Control14=IDC_EDITREMOTEIP,edit,1350631552

[DLG:IDD_REGISTDLG_DIALOG]
Type=1
Class=CRegistDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDITUSERNAME,edit,1350631552
Control6=IDC_EDITPASSWORD,edit,1350631584
Control7=IDC_EDITPASSWORD2,edit,1350631584
Control8=IDC_STATIC,static,1342308352
Control9=IDC_COMBOSEX,combobox,1344340227
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDITAGE,edit,1350639744
Control12=IDC_STATIC,static,1342308352
Control13=IDC_COMBOIMAGE,combobox,1344340227

[DLG:IDD_TEXTMESSAGE]
Type=1
Class=CTextMessage
ControlCount=3
Control1=IDC_RICHTEXTRECEIVE,{3B7C8860-D78F-101B-B9B5-04021C009402},1342242816
Control2=IDC_RICHTEXTSEND,{3B7C8860-D78F-101B-B9B5-04021C009402},1342242816
Control3=IDC_USERNAME,combobox,1344340226

[DLG:IDD_USERINFO]
Type=1
Class=CUserInfo
ControlCount=0

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177294
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308481

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_FILE_LOGON
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=IDM_TEXTMESSAGE
Command6=IDM_CHESS
Command7=IDM_DESK
Command8=IDM_CHESS_START
Command9=IDM_CHESS_SET
Command10=IDM_CHESS_REPENT
Command11=IDM_CHESS_STANDOFF
Command12=IDM_CHESS_GIVEUP
Command13=IDM_CHESS_CLOSE
Command14=ID_APP_ABOUT
CommandCount=14

[MNU:IDR_DESKVIEW_TMPL]
Type=1
Class=?
Command1=IDM_FILE_LOGON
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=IDM_TEXTMESSAGE
Command6=IDM_CHESS
Command7=IDM_DESK
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDD_DESKVIEW_FORM]
Type=1
Class=?
ControlCount=0

[MNU:IDM_CHAIR]
Type=1
Class=?
Command1=IDM_CHAIR_USERINFO
Command2=IDM_CHAIR_SENDMESSAGE
CommandCount=2

[CLS:CTiShi]
Type=0
HeaderFile=chess\tishi.h
ImplementationFile=chess\tishi.cpp
BaseClass=CWnd
Filter=W
LastObject=CTiShi
VirtualFilter=WC

[DLG:IDD_SETDLG]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TIME_STEP,edit,1350631552

