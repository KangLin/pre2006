#pragma once

class CEnum
{
public:
	CEnum(void);
	~CEnum(void);


	/*!
	\brief   ö�ٺ����Ļص�����
	\param   LPCTSTR pszValue�����������Ĳ���
	\return  ����Ϊ INT ���ɹ����� 0��ʧ�ܷ��ط��㡣
	\version 1.0
	\author  ��  ��
	\date    2007-7-13 9:56:41
	*/
	typedef INT(*ENUMOPERATE)(LPCTSTR pszValue);

	/*!
	\brief   ö�ٺ���
	\param   LPCTSTR pszItem��ö����
	\param   ENUMOPERATE eo ��ö�ٲ���
	\return  ����Ϊ virtual INT ���ɹ����� 0�� ʧ�ܷ��ط� 0
	\version 1.0
	\author  ��  ��
	\date    2007-7-13 9:55:26
	*/
	virtual INT Enum(LPCTSTR pszItem, ENUMOPERATE eo) = 0;

};
