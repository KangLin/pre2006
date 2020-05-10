// NetManageViewDoc.h : interface of the CNetManageViewDoc class
//


#pragma once

#include "..\Commonality\ManageServer.h"
#include "..\..\System\Communicate\TcpSocket.h"

class CNetManageViewDoc : public CDocument, public CManageServer
{
protected: // create from serialization only
	CNetManageViewDoc();
	DECLARE_DYNCREATE(CNetManageViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

	//处理解包后的命令
	virtual int ProcessCommand(CCommand & cmd, PCONNECT pConnect = NULL);

// Implementation
public:
	virtual ~CNetManageViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	Network::CTcpSocket * m_pSocket;

	virtual void OnCloseDocument();

	afx_msg void OnRefreshProcess();
	afx_msg void OnRefreshProcessModule();

};


