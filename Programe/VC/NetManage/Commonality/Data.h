/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    data.h
\brief   用于发送/接收数据，确保发送/接收的数据的正确性，按照定义的协议打包/解包。\n
         完成的功能：\n
		 \li 接收数据
		 \li 发送数据
		 \li 数据包的组装与分解

\note	 包格式：
<pre>
		________________________________________________
		| WORD       |     DWORD     | DWORD|..........|
		|-----------------------------------------------
		|标志(kl)    |报文内容的长度 |版本号| 报文内容 |
		------------------------------------------------
</pre>

\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年7月13日  17:45:44
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#pragma once

#define PACKAGE_SIGN 'kl'

class CCommand;

/*!
\class   CData
\brief   数据类
\version 1.0
\author  康  林
\date    2007-8-14 14:36:46
*/
class CData
{
public:
	CData();
	virtual ~CData();

	//清除缓存
	virtual int Clear();

protected:
	typedef struct _PACKAGEHEAD
	{
		WORD nSign;                      //!< 标志
		DWORD dwLength;                  //!< 包内容长度
		DWORD dwVersion;                 //!< 版本号
	}PACKAGEHEAD, *PPACKAGEHEAD;

	PPACKAGEHEAD m_pHead;                //!< 包头指针
	char * m_pBuffer;                    //!< 包缓存区
	int m_nMaxLength;                    //!< 缓存区最大长度
	int m_nLength;                       //!< 内容长度
};

/*!
\class   CSendData
\brief   发送数据类
\version 1.0
\author  康  林
\date    2007-8-14 14:37:04
*/
class CSendData : public CData
{
public:
	CSendData();
	virtual ~CSendData();

	//初始化包
	int InitializePackage(int nLength = 1024);
	//加入内容
	int AddContent(const void * pBuf, int nLength);
	//得到要发送数据的指针
	char * GetBuffer();
	//得到要发送数据的长度
	int GetLength();
	//设置已发送的数据
	int SetSended(int nLength);
	//清除缓存
	virtual int Clear();

private:
	int m_nSended;                       //!< 已发送数据的长度
	
};

/*!
\class   CReceiveData
\brief   接收数据类
\version 1.0
\author  康  林
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
		ISNULL,                          //!< 空，刚初始化
		ISOK,                            //!< 读出数据成功，生成了一条命令
		ISERROR,                         //!< 读出错
		ISHEADCONTINE,                   //!< 只读出部分包头数据,要继续读包头
		ISOKHEADCONTINE,                 //!< 数据已读出,下一个包头没有读完
		ISCONTINUE,                      //!< 只读出部分数据，要继续读
		ISNEXT,                          //!< 读出数据成功，生成了一条命令。但缓冲区中还有数据，下面还有命令
		NOALLOCATEBUFFER                 //!< 分配缓存出错
	};

private:
	int m_nReceive;                      //!< 已接收的长度
	int m_nState;                        //!< 当前接收数据的状态
	PACKAGEHEAD m_PackHead;              //!< 包头
	int m_nReceivePackHead;              //!< 已接收的包头大小

	Network::CSocket * m_pSocket;

	int CheckPackageHead(PPACKAGEHEAD pPackageHead);
	int ReceiveMessage();

};

/*!
\class   CSend
\brief   发送类
\version 1.0
\author  康  林
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
