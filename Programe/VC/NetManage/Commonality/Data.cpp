/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    Data.cpp
\brief   ���ڷ���/�������ݣ�ȷ������/���յ����ݵ���ȷ�ԣ����ն����Э����/�����
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��14��  15:12:44
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#include "StdAfx.h"
#include "Data.h"
#include ".\command.h"

CData::CData()
{
	m_nLength = 0;
	m_nMaxLength = 0;
	m_pBuffer = NULL;
	m_pHead = NULL;
}

CData::~CData()
{
	Clear();
}

/*!
\brief   ������������ͷ��ڴ�
\param   ��
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻�S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-13 12:21:23
*/
int CData::Clear()
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// ���� if(m_pBuffer)
	m_nLength = 0;
	m_nMaxLength = 0;
	m_pBuffer = NULL;
	m_pHead = NULL;
	return S_OK;
}

CSendData::CSendData()
{
	m_nSended = 0;
}

CSendData::~CSendData()
{
	Clear();
}

/*!
\brief   ��ʼ���������ʱ�����ȵ��ô˺���������������沢��ʼ����ͷ�ͱ���
\param   int nLength�����ĳ���
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻�S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-13 12:17:20
*/
int CSendData::InitializePackage(int nLength)
{
	Clear();

	m_nLength = sizeof(PACKAGEHEAD);
	m_nMaxLength = nLength + m_nLength;
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		return S_FALSE;
	} // ���� if(NULL == m_pBuffer)

	m_pHead = (PPACKAGEHEAD)m_pBuffer;
	memset(m_pHead, 0, m_nLength);
	m_pHead->nSign = PACKAGE_SIGN;
	m_pHead->dwVersion = 1;
	m_pHead->dwLength = 0;

	return S_OK;
}

/*!
\brief   �������������������
\param   const void * pBuf��Ҫ���ӵ�����ָ��
\param   int nLength      �����ݵĳ��ȣ���λ���ֽڣ�
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻�S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-13 12:18:51
*/
int CSendData::AddContent(const void * pBuf, int nLength)
{
	char * pBuffer = NULL;

	//ASSERT(pBuf && nLength > 0);
	if(NULL == pBuf || nLength < 0)
	{
		return S_FALSE;
	} // ���� if(NULL == pBuf || nLength < 0)

	if(m_nLength + nLength > m_nMaxLength)
	{
		//���·����ڴ�
		m_nMaxLength = m_nMaxLength + nLength + nLength;
		pBuffer = new char[m_nMaxLength];
		if(NULL == pBuffer)
		{
			return S_FALSE;
		}// ���� if(NULL == pBuffer)

		memcpy(pBuffer, m_pBuffer, m_nLength);

		delete []m_pBuffer;
		m_pBuffer = pBuffer;
		m_pHead = (PPACKAGEHEAD)m_pBuffer;
	}// ���� if(m_nLength + nLength > m_nMaxLength)

	memcpy(m_pBuffer + m_nLength, pBuf, nLength);
	m_nLength += nLength;
	m_pHead->dwLength += nLength;
	return S_OK;
}

/*!
\brief   Ҫ�������ݵ�ָ��
\param   ��
\return  ����Ϊ char * ��Ҫ�������ݵ�ָ��
\version 1.0
\author  ��  ��
\date    2007-8-13 12:19:46
*/
char * CSendData::GetBuffer()
{
	return (m_pBuffer + m_nSended);
}

/*!
\brief   Ҫ�������ݵĳ���
\param   ��
\return  ����Ϊ int ��Ҫ�������ݵĳ���
\version 1.0
\author  ��  ��
\date    2007-8-13 12:20:24
*/
int CSendData::GetLength()
{
	return (m_nLength - m_nSended);
}

/*!
\brief   �����Ѿ��������ݵĳ���
\param   int nLength���Ѿ��������ݵĳ���
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻�S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-13 12:20:54
*/
int CSendData::SetSended(int nLength)
{
	m_nSended += nLength;
	return S_OK;
}

/*!
\brief   ������������ͷ��ڴ�
\param   ��
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻�S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-13 12:21:23
*/
int CSendData::Clear()
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// ���� if(m_pBuffer)
	m_nLength = 0;
	m_nMaxLength = 0;
	m_nSended = 0;
	m_pBuffer = NULL;
	m_pHead = NULL;
	return S_OK;
}

CReceiveData::CReceiveData(Network::CSocket * pSocket)
{
	ASSERT(pSocket);
	m_pSocket = pSocket;

	m_nState = ISNULL;

	m_pBuffer = NULL;
	m_nLength = 0;
	m_nReceive = 0;
	m_nReceivePackHead = 0;
}

CReceiveData::~CReceiveData(void)
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// ���� if(m_pBuffer)
	m_pBuffer = NULL;
	m_nLength = 0;
	m_nReceive = 0;
	m_nReceivePackHead = 0;
}

/*!
\brief   ������������
\param   CCommand * pCmd���������ݳɹ��������ʵ��
\return  ����Ϊ int �����ص�ǰ�Ľ���״̬��
\version 1.0
\author  ��  ��
\date    2007-7-15 10:28:14
*/
int CReceiveData::Receive(CCommand * pCmd)
{
	int nLen = 0;
	char * pBuf = NULL;

	ASSERT(pCmd);

	switch(m_nState)
	{
	case ISCONTINUE:
		nLen = m_pSocket->Receive(m_pBuffer + m_nReceive, m_nLength - m_nReceive);
		if(SOCKET_ERROR == nLen || 0 == nLen)
		{
			return ISERROR;
		}// ���� if(SOCKET_ERROR == nLen || 0 == nLen)
		if(m_nLength - m_nReceive == nLen)
		{
			m_nState = ISOK;
		}
		else
		{	
			m_nState = ISCONTINUE;
		} // ���� if(m_nLength - m_nReceive == nLen)
		m_nReceive += nLen;
		break;
	case ISHEADCONTINE:
	case ISOKHEADCONTINE:
		nLen = m_pSocket->Receive(((char * )&m_PackHead) + m_nReceivePackHead, sizeof(PACKAGEHEAD) - m_nReceivePackHead);
		if(SOCKET_ERROR == nLen || 0 == nLen)
		{
			m_nState = ISERROR;
			break;
		}// ���� if(SOCKET_ERROR == nLen || 0 == nLen)
		if(nLen < sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		{
			m_nState = ISHEADCONTINE;
			break;
		}// ���� if(nLen < sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		if(nLen == sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		{
			if(CheckPackageHead(&m_PackHead) != S_OK)
			{
				TRACE(_T("��ͷ��־����! \n"));
				m_nState = ISERROR;
				break;
			}// ���� (_T("��ͷ��־����! n"))

			//���ĳ���
			m_nLength = m_PackHead.dwLength;
			//���ձ���
			m_nState = ReceiveMessage();
		} // ���� if(nLen == sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		break;
	case ISNEXT:
		//���ձ���
		m_nState = ReceiveMessage();
		break;
	default:
		//�õ����ĵ�ͷ
		nLen = m_pSocket->Receive(&m_PackHead, sizeof(PACKAGEHEAD));
		if(SOCKET_ERROR == nLen || 0 == nLen)
		{
			return ISERROR;
		}// ���� if(SOCKET_ERROR == nLen || 0 == nLen)
		if(nLen < sizeof(PACKAGEHEAD))
		{
			TRACE(_T("��ͷ��С����!"));
			m_nState = ISHEADCONTINE;
			break;
		} // ���� if(nLen < sizeof(PACKAGEHEAD))
		if(CheckPackageHead(&m_PackHead) != S_OK)
		{
			TRACE(_T("��ͷ��־����! \n"));
			m_nState = ISERROR;
			break;
		}// ���� if(CheckPackageHead(&m_nReceivePackHead) != S_OK)

		//���ĳ���
		m_nLength = m_PackHead.dwLength;
		//���ձ���
		m_nState = ReceiveMessage();

		break;
	} // ���� switch(m_nState)

	//��ʼ������ʵ��
	if(ISOK == m_nState)
	{
		if(pCmd->SetCommand(m_pBuffer, m_nLength) == S_OK)
		{
			//m_nState = ISOK;

			//����Ƿ�����һ�鱨��
			nLen = m_pSocket->Receive(&m_PackHead, sizeof(PACKAGEHEAD));
			if(SOCKET_ERROR != nLen)
			{
				if(nLen < sizeof(PACKAGEHEAD))
				{
					TRACE(_T("��ͷ��С����!"));
					m_nState = ISOKHEADCONTINE;
				} // ���� if(nLen < sizeof(PACKAGEHEAD))
				if(CheckPackageHead(&m_PackHead) == S_OK)
				{
					m_nLength = m_PackHead.dwLength;
					m_nState = ISNEXT;
				}
				else
				{
					TRACE(_T("��ͷ��־����! \n"));
					m_nState = ISERROR;
				} // ���� if(CheckPackageHead(&packHead) == S_OK)
			}// ���� if(SOCKET_ERROR != nLen)
		}
		else
		{
			m_nState = ISERROR;
		}// ���� if(pCmd->SetCommand(m_pBuffer, m_nLength) == S_OK)
	} // ���� if(ISOK == m_nState)
	return m_nState;
}

/*!
\brief   ���ձ���
\prarm   ��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-8-14 11:37:41
*/
int CReceiveData::ReceiveMessage()
{
	int nLen = 0;

	//���뱨�Ļ�����
	if(m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}// ���� (m_pBuffer)
	m_pBuffer = new char[m_nLength];
	if(NULL == m_pBuffer)
	{
		return NOALLOCATEBUFFER;
	} // ���� if(NULL == m_pBuffer)

	//���ձ�������
	nLen = m_pSocket->Receive(m_pBuffer, m_nLength);
	if(nLen == m_nLength)
	{
		m_nState = ISOK;
		m_nReceive = nLen;
	}
	else
	{
		//��������û��ȫ������
		m_nState = ISCONTINUE;
		if(SOCKET_ERROR == nLen)
		{
			//��˵�����յ�������ʱ��δ����
			m_nReceive = 0;			
		}
		else if(0 == nLen)      //Socket �ѹر�
		{
			m_nReceive = 0;
			m_nState = ISERROR; 
		}
		else
		{
			m_nReceive = nLen;
		} // ���� if(0 == nLen)
	} // ���� if(nLen == m_nLength)

	return m_nState;
}

/*!
\brief   ����ͷ�Ƿ���ȷ
\param   PPACKAGEHEAD pPackageHead����ͷָ��
\return  ����Ϊ int �������ȷ����S_OK�����򷵻�S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-13 13:11:42
*/
int CReceiveData::CheckPackageHead(PPACKAGEHEAD pPackageHead)
{
	if((WORD)PACKAGE_SIGN == pPackageHead->nSign)
	{
		return S_OK;
	}// ���� if((WORD)PACKAGE_SIGN == pPackageHead->nSign)
	return S_FALSE;
}

CSend::CSend(Network::CSocket * pSocket)
{
	m_pSocket = pSocket;
	::InitializeCriticalSection(&m_CriticalSection);
}

CSend::~CSend()
{
	::EnterCriticalSection(&m_CriticalSection);
	list < CSendData * > ::iterator it;
	for(it = m_SendData.begin(); it != m_SendData.end(); it++)
	{
		delete * it;
	}// ���� for(it = m_SendData.begin(); it != m_SendData.end(); it++)
	m_SendData.clear();
	::LeaveCriticalSection(&m_CriticalSection);
	::DeleteCriticalSection(&m_CriticalSection);
}

/*!
\brief   �������ݣ�ʵ�����ȼ��뵽���Ͷ��У�Ȼ����� ProcessSend ���з��͡�
\param   CCommand * pCmd���������
\return  ����Ϊ int ���ɹ�����S_OK��ʧ�ܷ��� S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-14 11:50:11
*/
int CSend::Send(CCommand * pCmd)
{
	int nRet = S_OK;
	CSendData * pSendData = new CSendData();
	if(NULL == pSendData)
	{
		return S_FALSE;
	}// ���� if(NULL == pSendData)

	do 
	{
		nRet = pSendData->InitializePackage(pCmd->GetLength());
		if(S_FALSE == nRet)
		{
			break;
		}// ���� if(S_FALSE == nRet)

		nRet = pSendData->AddContent(pCmd->GetBuffer(), pCmd->GetLength());
		if(nRet == S_FALSE)
		{
			break;
		}// ���� if(nRet == S_FALSE)

		try
		{
			::EnterCriticalSection(&m_CriticalSection);
			m_SendData.push_back(pSendData);
			::LeaveCriticalSection(&m_CriticalSection);
		}
		catch (...)
		{
			TRACE(_T("�������ݼ��뵽���Ͷ��г���!"));
			::LeaveCriticalSection(&m_CriticalSection);
			nRet = S_FALSE;
			break;
		}

	} while(FALSE);

	if(S_FALSE == nRet)
	{
		delete pSendData; 
	}
	else
	{
		//����
		nRet = ProcessSend();
	} // ���� if(S_FALSE == nRet)
	
	return nRet;
}

/*!
\brief   ��������
\param   ��
\return  ����Ϊ int ���ɹ�����S_OK��ʧ�ܷ��� S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-14 11:51:18
*/
int CSend::ProcessSend()
{
	int nRet = S_OK;
	if(m_SendData.size() == 0)
	{
		return nRet;
	}// ���� if(m_SendData.size() == 0)

	CSendData * pSendData = NULL;
	pSendData = *m_SendData.begin();
	//����
	int nLen = m_pSocket->Send(pSendData->GetBuffer(), pSendData->GetLength());
	if(SOCKET_ERROR == nLen)
	{
		nRet = S_FALSE;
	}
	else if(pSendData->GetLength() == nLen)
	{
		nRet = S_OK;
		try
		{
			::EnterCriticalSection(&m_CriticalSection);
			m_SendData.pop_front();
			::LeaveCriticalSection(&m_CriticalSection);
		}
		catch (...)
		{
			::LeaveCriticalSection(&m_CriticalSection);
			nRet = S_FALSE;
		}
		delete pSendData;
	}
	else
	{
		nRet = pSendData->SetSended(nLen);
	}// ���� if(SOCKET_ERROR == nLen)

	return nRet;
}