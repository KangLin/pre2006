#include "stdafx.h"
#include ".\6608tftp.h"
#include "..\TestTemplet\CommonFunction.h"

C6608TFTP::C6608TFTP(void)
{
	SetName(_T("升级新内核"));
}

C6608TFTP::~C6608TFTP(void)
{
}

int C6608TFTP::DoTest(void)
{
	CString sztmp;
	char FileSize [10], BlockSize [10];
	int nCount, nRepeat;
	int nRet = 0, nID = 1;
	BOOL bSuccess = FALSE;
	CString szIP;
	UINT nPort;

	CFile f;
	if(!f.Open(m_szFileName, CFile::modeRead))
	{
		sztmp.Format(_T("打开文件 %s 出错。升级"), m_szFileName);
		m_plog->Faile(sztmp);
		return 1;
	} // 结束 (!f.Open(m_szFileName, CFile::modeRead))

	m_Send = (TFTP_HEAD * )m_SendBuf;
	m_Recv = (TFTP_HEAD * )m_RecvBuf;

	m_Send->OperateCode = htons(TFTP_WRQ);
	SetFileMode(TFTP_OCTET);
	_itot(f.GetLength(), FileSize, 10);
	_itot(BLK_SIZE, BlockSize, 10);
	nCount = _stprintf(m_Send->th_u.Stuff, "%s%c%s%c%s%c%s%c%s%c%s%c",
		::GetFileName(m_szFileName), 0x00, m_szFileMode, 0x00, "blksize", 0x00, BlockSize, 0x00, "tsize", 0x00, FileSize, 0x00) + 2;
	if(nCount < 0 || nCount > BLK_SIZE)
	{
		m_plog->Faile(_T("选项数据太长。升级"));
		f.Close();
		return 2;
	} // 结束 if(nCount < 0 || nCount > BLK_SIZE)

	nRepeat = m_nMaxRepeat;
	bSuccess = FALSE;
	while(nRepeat)
	{
		nRepeat--;

		if(SOCKET_ERROR == m_Sock.SendTo(m_Send, nCount, m_nPort, m_szIP))
		{
			continue;
		} // 结束 if(SOCKET_ERROR == m_Sock.SendTo(m_Send, nCount, m_nPort, m_szIP))

		while(1)
		{
			m_Sock.SetTimeOut(m_nTimeOut);

			if(SOCKET_ERROR == m_Sock.ReceiveFrom(m_Recv, DATA_BUFFER, szIP, nPort))
			{
				m_Sock.KillTimeOut();
				if(WSAEINTR == GetLastError())
				{
					TRACE(_T("接收请求数据超时。\n"));
					break;
				}
				else
				{
					TRACE(_T("接收请求数据出错。\n"));
					continue;
				}
			} // 结束 if(SOCKET_ERROR == m_Sock.ReceiveFrom(m_Recv, DATA_BUFFER, szIP, nPort))

			if(htons(m_Recv->OperateCode) == TFTP_ACK
				|| htons(m_Recv->OperateCode) == TFTP_OACK)
			{
				bSuccess = TRUE;
				m_Sock.KillTimeOut();
				nRepeat = 0;
				break;
			} // 结束 if(htons(m_Recv->OperateCode) == TFTP_ACK && htons(m_Recv->OperateCode) == TFTP_OACK)

			m_Sock.KillTimeOut();
		} // 结束 while(1)

	} // 结束 while(nRepeat)

	if(!bSuccess)
	{
		m_plog->Faile(_T("发送请求写数据出错。升级"));
		f.Close();
		return 3;
	} // 结束 if(!bSuccess)

	bSuccess = FALSE;
	while(TRUE)
	{
		m_Send->OperateCode = htons(TFTP_DATA);
		m_Send->th_u.BlockNo = htons(nID);
		nCount = f.Read(m_Send->data, BLK_SIZE);
		if(nCount == 0)
		{
			break;
		} // 结束 if(nCount == 0)

		if(nCount < 0)
		{
			f.Close();
			m_plog->Faile(_T("读取文件数据出错。升级"));
			return 4;
		} // 结束 if(nCount < 0)

		nRepeat = m_nMaxRepeat;
		while(nRepeat)
		{
			nRepeat--;
			if(SOCKET_ERROR == m_Sock.SendTo(m_Send, nCount + 4, nPort, szIP))
			{
				continue;
			} // 结束 if(SOCKET_ERROR == m_Sock.SendTo(m_Send, nCount + 4, nPort, szIP))

			m_Sock.SetTimeOut(m_nTimeOut);

			if(SOCKET_ERROR == m_Sock.Receive(m_Recv, DATA_BUFFER)) //, szIP, nPort))
			{
				if(WSAEINTR == GetLastError())
				{
					TRACE(_T("接收超时。\n"));
				}
				else
				{
					TRACE(_T("接收数据出错。\n"));
				}

				m_Sock.KillTimeOut();
				bSuccess = FALSE;
				continue;

			} // 结束 if(SOCKET_ERROR == m_Sock.Receive(m_Recv, DATA_BUFFER))

			if(m_Recv->OperateCode == htons(TFTP_ERROR))
			{
				f.Close();
				m_Sock.KillTimeOut();
				m_plog->Faile(_T("TFTP出错。升级"));
				return 6;
			} // 结束 if(m_Recv->OperateCode == htons(TFTP_ERROR))

			if(htons(m_Recv->OperateCode) == TFTP_ACK
				&& htons(m_Recv->th_u.BlockNo) == nID)
			{
				nRepeat = 0;
				bSuccess = TRUE;
			}
			else
			{
				TRACE(_T("接收的数据有误。"));
				bSuccess = FALSE;
			} // 结束 if(htons(m_Recv->OperateCode) == TFTP_ACK &&htons(m_Recv->th_u.BlockNo) == nID)

			m_Sock.KillTimeOut();

	} // 结束 while(nRepeat)

	//升级成功
	if(nCount < BLK_SIZE)
	{
		break;
	} // 结束 if(nCount < BLK_SIZE)

	nID++;
	m_plog->Message(_T("."), FALSE);

	} // 结束 while(TRUE)

	f.Close();

	if(bSuccess)
	{
		m_plog->Success(_T("\n升级"));
		return 0;
	}
	else
	{
		m_plog->Faile(_T("\n升级"));
		return 7;
	} // 结束 if(bSuccess)
	
}
