#pragma once
#include "manage.h"
#include "ListenSock.h"
#include "ManageListen.h"
#include "ManageConnect.h"

//typedef struct _SOCKINFO
//{
//	CSocket * pSock;
//	CListenSocket * pListen;
//	CConnect * pConnect;
//	bool bIsListen;
//}SOCKINFO, *PSOCKINFO;

class CManageListen;

/*!
\class   CManageNet
\brief   管理网络类
\version 1.0
\author  康  林
\date    2007-9-24 11:43:08
*/
class CManageNet : public CManage
{
public:
	CManageNet(void);
	virtual ~CManageNet(void);

	//增加一个新监听
	virtual int AddListen(int nPort);
	//删除监听
	virtual int RemoveListen(int nFd);
	//增加连接
	virtual int AddConncet(CSocket * pSocket);
	//删除连接
	virtual int RemoveConnect(CSocket * pSock);

	virtual int Initalize(CManageConnect * pMngConnect = NULL, CManageListen * pMngListen = NULL);

private:
	CManageConnect * m_pConnect;
	CManageListen * m_pListen;
};
