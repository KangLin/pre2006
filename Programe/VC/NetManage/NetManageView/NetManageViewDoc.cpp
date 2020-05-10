// NetManageViewDoc.cpp : implementation of the CNetManageViewDoc class
//

#include "stdafx.h"
#include "NetManageView.h"
#include "MainFrm.h"
#include "NetManageViewDoc.h"
#include "..\Commonality\command.h"
#include ".\NetManageBaseView.h"

#ifdef _DEBUG
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


// CNetManageViewDoc

IMPLEMENT_DYNCREATE(CNetManageViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CNetManageViewDoc, CDocument)
	ON_COMMAND(ID_REFRESH_PROCESS, OnRefreshProcess)
	ON_COMMAND(ID_REFRESH_PROCESS_MODULE, OnRefreshProcessModule)
END_MESSAGE_MAP()


// CNetManageViewDoc construction/destruction

CNetManageViewDoc::CNetManageViewDoc()
{
	//��CNetManage�ͷ�
	m_pSocket = NULL;

}

CNetManageViewDoc::~CNetManageViewDoc()
{
}

BOOL CNetManageViewDoc::OnNewDocument()
{
	CNetManageViewApp * pApp = (CNetManageViewApp * )AfxGetApp();
	CString szHost;
	int nPort = 0;
	//����:���ӵ�ַ
	CMainFrame * pMainFrame = (CMainFrame * )AfxGetMainWnd();
#ifdef _DEBUG
	szHost = _T("127.0.0.1");
	nPort = 5000;
#endif // ���� #ifdef _DEBUG

	CString szMessage;
	//�޸�:Ҫ��ʾ����Ϣ
	szMessage = szHost;

	if(NULL == m_pSocket)
	{
		try
		{
			m_pSocket = new Network::CTcpSocket(szHost, nPort);
			if(pApp->m_pMagSocket)
			{
				if(S_OK != pApp->m_pMagSocket->AddConncet(m_pSocket, this))
				{
					delete m_pSocket;
					m_pSocket = NULL;
				} // ���� if(S_OK != pApp->m_pMagSocket->AddConncet(m_pSocket, this))
			} // ���� if(pApp->m_pMagSocket)
		}
		catch (CTException e)
		{
			CString szTemp;
			szTemp = e.what();
			szTemp = szTemp + _T(" ") + szMessage;
			TRACE(_T("%s\n"), szTemp);
			::MessageBox(NULL, szTemp, NULL, MB_OK);
			if(m_pSocket)
			{
				delete m_pSocket;
				m_pSocket = NULL;
			} // ���� if(pSocket)
			return FALSE;
		}

		//�����ĵ�����
		this->m_strTitle = szMessage;
	}
	else
	{
		TRACE(_T("�������ӡ�\n"));
		ASSERT(FALSE);
	} // ���� if(NULL == m_pConnect)

	if(!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	return TRUE;
}

// CNetManageViewDoc serialization

void CNetManageViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CNetManageViewDoc diagnostics

#ifdef _DEBUG
void CNetManageViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNetManageViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNetManageViewDoc commands
void CNetManageViewDoc::OnCloseDocument()
{
	CNetManageViewApp * pApp = (CNetManageViewApp * )AfxGetApp();
	if(m_pSocket)
	{
		pApp->m_pMagSocket->RemoveConnect(m_pSocket);
	} // ���� if(m_pConnect)

	CDocument::OnCloseDocument();
}

//�������������
int CNetManageViewDoc::ProcessCommand(CCommand & cmd, PCONNECT pConnect)
{
	int nRet = S_OK;
	POSITION pos = GetFirstViewPosition();
	while(pos)
	{
		CView * pView = GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CNetManageBaseView)))
		{
			((CNetManageBaseView * )pView)->ProcessCommand(cmd);
		} // ���� if(pView->IsKindOf(RUNTIME_FUNCTION(CNetManageBaseView)))
	} // ���� while(pos)
	return nRet;
}

/*!
\brief   ˢ�����н���
\param   ��
\return  ����Ϊ void ��
\version 1.0.0.1
\author  ��  ��
\date    2007-8-24 20:08:00
*/
void CNetManageViewDoc::OnRefreshProcess()
{
	CCommand cmd;
	cmd.SetCommand(CMD_QUERY_ALL_PROCESS);
	if(m_pSocket)
	{
		Send(m_pSocket, &cmd);
	} // ���� if(m_pConnect)
}

void CNetManageViewDoc::OnRefreshProcessModule()
{
	CCommand cmd;
	cmd.SetCommand(CMD_QUERY_ALL_PROCESS_MODULE);
	if(m_pSocket)
	{
		Send(m_pSocket, &cmd);
	} // ���� if(m_pConnect)
}
