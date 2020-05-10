#pragma once

class CData
{
public:
	CData(void);
	virtual ~CData(void);

	//清除数据
	virtual int Clear();

protected:
	char * m_pBuffer;  //缓存指针
	int m_nMaxLen;     //缓存最大长度
	int m_nLength;     //内容长度

};
