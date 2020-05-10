#pragma once

class CEnum
{
public:
	CEnum(void);
	~CEnum(void);


	/*!
	\brief   枚举函数的回调函数
	\param   LPCTSTR pszValue：传给函数的参数
	\return  类型为 INT 。成功返回 0，失败返回非零。
	\version 1.0
	\author  康  林
	\date    2007-7-13 9:56:41
	*/
	typedef INT(*ENUMOPERATE)(LPCTSTR pszValue);

	/*!
	\brief   枚举函数
	\param   LPCTSTR pszItem：枚举项
	\param   ENUMOPERATE eo ：枚举操作
	\return  类型为 virtual INT 。成功返回 0， 失败返回非 0
	\version 1.0
	\author  康  林
	\date    2007-7-13 9:55:26
	*/
	virtual INT Enum(LPCTSTR pszItem, ENUMOPERATE eo) = 0;

};
