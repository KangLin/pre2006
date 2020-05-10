/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    data.h
\brief   ���ڷ���/�������ݣ�ȷ������/���յ����ݵ���ȷ�ԣ����ն����Э����/�����\n
         ��ɵĹ��ܣ�\n
		 \li ��������
		 \li ��������
		 \li ���ݰ�����װ��ֽ�

\note	 ����ʽ��
<pre>
		________________________________________________
		| WORD       |     DWORD     | DWORD|..........|
		|-----------------------------------------------
		|��־(kl)    |�������ݵĳ��� |�汾��| �������� |
		------------------------------------------------
</pre>

\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��7��13��  17:45:44
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#pragma once

#define PACKAGE_SIGN 'kl'

class CCommand;

/*!
\class   CData
\brief   ������
\version 1.0
\author  ��  ��
\date    2007-8-14 14:36:46
*/
class CData
{
public:
	CData();
	virtual ~CData();

	//�������
	virtual int Clear();

protected:
	typedef struct _PACKAGEHEAD
	{
		WORD nSign;                      //!< ��־
		DWORD dwLength;                  //!< �����ݳ���
		DWORD dwVersion;                 //!< �汾��
	}PACKAGEHEAD, *PPACKAGEHEAD;

	PPACKAGEHEAD m_pHead;                //!< ��ͷָ��
	char * m_pBuffer;                    //!< ��������
	int m_nMaxLength;                    //!< ��������󳤶�
	int m_nLength;                       //!< ���ݳ���
};

/*!
\class   CSendData
\brief   ����������
\version 1.0
\author  ��  ��
\date    2007-8-14 14:37:04
*/
class CSendData : public CData
{
public:
	CSendData();
	virtual ~CSendData();

	//��ʼ����
	int InitializePackage(int nLength = 1024);
	//��������
	int AddContent(const void * pBuf, int nLength);
	//�õ�Ҫ�������ݵ�ָ��
	char * GetBuffer();
	//�õ�Ҫ�������ݵĳ���
	int GetLength();
	//�����ѷ��͵�����
	int SetSended(int nLength);
	//�������
	virtual int Clear();

private:
	int m_nSended;                       //!< �ѷ������ݵĳ���
	
};

/*!
\class   CReceiveData
\brief   ����������
\version 1.0
\author  ��  ��
\date    2007-8-14 14:37:14
*/
class CReceiveData : public CData
{
public:
	CReceiveData(Network::CSocket* pSocket);
	virtual ~CReceiveData(void);

	int Receive(CCommand * pCmd);

	enum
	{
		ISNULL,                          //!< �գ��ճ�ʼ��
		ISOK,                            //!< �������ݳɹ���������һ������
		ISERROR,                         //!< ������
		ISHEADCONTINE,                   //!< ֻ�������ְ�ͷ����,Ҫ��������ͷ
		ISOKHEADCONTINE,                 //!< �����Ѷ���,��һ����ͷû�ж���
		ISCONTINUE,                      //!< ֻ�����������ݣ�Ҫ������
		ISNEXT,                          //!< �������ݳɹ���������һ��������������л������ݣ����滹������
		NOALLOCATEBUFFER                 //!< ���仺�����
	};

private:
	int m_nReceive;                      //!< �ѽ��յĳ���
	int m_nState;                        //!< ��ǰ�������ݵ�״̬
	PACKAGEHEAD m_PackHead;              //!< ��ͷ
	int m_nReceivePackHead;              //!< �ѽ��յİ�ͷ��С

	Network::CSocket * m_pSocket;

	int CheckPackageHead(PPACKAGEHEAD pPackageHead);
	int ReceiveMessage();

};

/*!
\class   CSend
\brief   ������
\version 1.0
\author  ��  ��
\date    2007-8-14 14:37:24
*/
class CSend
{
public:
	CSend(Network::CSocket * pSocket);
	virtual ~CSend();

	int Send(CCommand * pCmd);
	int ProcessSend();

private:
	list<CSendData*> m_SendData;
	Network::CSocket * m_pSocket;
	CRITICAL_SECTION m_CriticalSection;
};
