#pragma once

class CData
{
public:
	CData(void);
	virtual ~CData(void);

	//�������
	virtual int Clear();

protected:
	char * m_pBuffer;  //����ָ��
	int m_nMaxLen;     //������󳤶�
	int m_nLength;     //���ݳ���

};
