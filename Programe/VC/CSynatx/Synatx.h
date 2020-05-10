/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Synatx.h
描  述：C++ 词法分析类
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月13日
时  间：13:41:53
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/

#if !defined(AFX_SYNATX_H__0FABDB8A_B153_4BDA_A5C3_970F487EA566__INCLUDED_)
#define AFX_SYNATX_H__0FABDB8A_B153_4BDA_A5C3_970F487EA566__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Afxtempl.h>
#include <algorithm>

template < class T > 
void DeleteList(CList < T *, T * > &para)
{
	POSITION pos = para.GetHeadPosition();
	while(pos)
	{
		T * key = para.GetNext(pos);
		delete key;
	} // 结束 while(pos)
	para.RemoveAll();
}

#ifdef _DEBUG
template < class T > 
void ShowListAll(CList < T *, T * > &para)
{
	POSITION pos = para.GetHeadPosition();
	while(pos)
	{
		T * key = para.GetNext(pos);
		TRACE(_T("%s\n"), key->szName);
	} // 结束 while(pos)
}

template < class T > 
void ShowListStruct(CList < T *, T * > &para)
{
	POSITION pos = para.GetHeadPosition();
	while(pos)
	{
		T * key = para.GetNext(pos);
		TRACE(_T("%s\n"), key->szName);
		TRACE(_T("元素\n"));
		POSITION pos = key->m_lsItem.GetHeadPosition();
		while(pos)
		{
			CString key1 = key->m_lsItem.GetNext(pos);
			TRACE(_T("%s\n"), key1);
		} // 结束 while(pos)
		TRACE(_T("元素end\n"));
	} // 结束 while(pos)
}
#endif

class CSynatx  
{
public:
	static const int TAB = 9;    //制表符
	static const int CR = 13;    //回车符
	static const int LF = 10;    //换行符
	enum ENUM_TYPE
	{
		NO = 0,
		KEYWORD,         //关键字
		DATATYPEDEFINE,  //数据类型的定义
		VARIABLE,        //变量的定义
		FLOWCONTROL,     //流程控制
		FUNCTION,        //函数
		FUNCTIONDEFINE,
		CLASS,           //类
		CLASSDEFINE,
		STRUCT,          //结构
		STRUCTDEFINE,
		ENUM,            //枚举
		ENUMDEFINE,
		UNION,           //联合
		UNIONDEFINE,
		NAMESPACE,       //命名空间
		NAMESPACEDEFINE,
		COMMENT,         //注释
		TYPEDEF,
		IF,
		ELSE,
		ENDIF,
		FOR,
		SWITCH,
		CASE,
		DEFAULT,
		BREAK,
		CONTINUE,
		WHILE,
		DO,
		GOTO,
		RETURN,
		SIZEOF,
		SEMICOLON,    //分号
		COMMA,        //逗号
		DOT,          //句号
		ADD,          //加号
		SUBTRACTION,  //减号
		MULTIPLY,     //乘号
		DIVISION,     //除号
		BIG,          //大于号
		LESS,         //小于号
		EQUAL,        //等号
		RIGHTBIGBRACKET,     //右大括号
		LEFTBIGBRACKET,      //左大括号
		RIGHTLITTLEBRACKET,  //右小括号
		LEFTLITTLEBRACKET,   //左小括号
		RIGHTMIDBRACKET,     //右中括号
		LEFTMIDBRACKET       //左中括号
	};

	CSynatx(LPCSTR lpszCode, LONG nLen);
	CSynatx(LPCSTR lpszFileName);
	CSynatx();
	virtual ~CSynatx();
	BOOL LoadCode(LPCTSTR lpszCode, LONG nLen);
    BOOL LoadCode(LPCTSTR lpszFileName);
	
private:
	LPTSTR m_lpszCode;     //代码缓存区
	LONG m_nCodeLen;       //代码长度

	LPTSTR m_lpCur;
	LPTSTR m_lpWord;

	CString m_szFileName;  //文件名
	INT m_nLine;           //行号

	void Init();
	void InitPoint();      //初始化各指针
	void ClearCode();      //清除代码缓存

	int m_nEnum;
	int m_nStruct;
	int m_nUnion;
	int m_nClass;
	
public:

	struct _IDENTIFIER
	{
		CString szName;  // 名字
		CString szArea;  //域
	};
	CList < _IDENTIFIER *, _IDENTIFIER * > m_lsIdentifier;  //标识符
	class _STRUCT : public _IDENTIFIER
	{
	public:
		CList < CString, CString > m_lsItem;
	};
	typedef _STRUCT _UNION, _ENUM;
	CList < _STRUCT *, _STRUCT * > m_lsStruct;  //结构
	CList < _UNION *, _UNION * > m_lsUnion;     //联合
	CList < _ENUM *, _ENUM * > m_lsEnum;        //枚举 

	class _DATATYPE : public _IDENTIFIER
	{
	public:
		CString szVal;      //值
		CString szComment;  //注释
	};
	typedef _DATATYPE _VARIABLE;
	CList < _DATATYPE *, _DATATYPE * > m_lsDataType;  //类型
	CList < _VARIABLE *, _VARIABLE * > m_lsVariable;  //变量
	class _FUNCTION : public _IDENTIFIER
	{
	public:
		CString szDeclare;  //声明
		CString szComment;  //注释
	};
	CList < _FUNCTION*, _FUNCTION* > m_lsFunction;    //函数
	class _CLASS : public _FUNCTION
	{
	public:
		CList < _IDENTIFIER*, _IDENTIFIER* > m_lsIdentifier;  //标识符
		CList < _STRUCT *, _STRUCT * > m_lsStruct;            //结构
		CList < _UNION *, _UNION * > m_lsUnion;               //联合
		CList < _ENUM *, _ENUM * > m_lsEnum;                  //枚举 
		CList < _DATATYPE *, _DATATYPE * > m_lsDataType;      //类型
		CList < _VARIABLE *, _VARIABLE * > m_lsVariable;      //变量
		CList < _FUNCTION *, _FUNCTION * > m_lsFunction;      //函数
		CList < _CLASS*, _CLASS* > m_lsClass;                 //类
		~_CLASS(void);
	};
	CList < _CLASS *, _CLASS * > m_lsClass;  //类

	/*******************************************************************************************************
	函数名：SearchList
	描  述：查找列中指定元素
	参  数：
	        CList< T, T >&para：
			RT reval          ：
			CString szWord    ：元素名。
	返回值：类型为 INT 。
	版  本：1.0.0.1
	作  者：康  林
	时  间：2005年8月12日 18:19:51
	*******************************************************************************************************/
	template < class T, class RT > 
		ENUM_TYPE SearchList(CList < T, T > &para, RT reval, CString szWord)
	{
		POSITION pos = para.GetHeadPosition();
		while(pos)
		{
			T key = para.GetNext(pos);
			if(key.szName == szWord)
			{
				return reval;
			} // 结束 if(key.szName = szWord)
		} // 结束 while(pos)
		return NO;
	}

	/*******************************************************************************************************
	函数名：SearchList
	描  述：查找列中指定元素
	参  数：
	        CList< T *, T * >&para：
			RT reval              ：
			CString szWord        ：元素名。
	返回值：类型为 INT 。
	版  本：1.0.0.1
	作  者：康  林
	时  间：2005年8月12日 18:20:27
	*******************************************************************************************************/
	template < class T, class RT > 
		ENUM_TYPE SearchList(CList < T *, T * > &para, RT reval, CString szWord)
	{
		POSITION pos = para.GetHeadPosition();
		while(pos)
		{
			T * key = para.GetNext(pos);
			if(key->szName == szWord)
			{
				return reval;
			} // 结束 if(key.szName = szWord)
		} // 结束 while(pos)
		return NO;
	}

	/*******************************************************************************************************
	函数名：AddElement
	描  述：向链表中加入新的元素
	参  数：
	        CList< T *, T * >& p：列表
	返回值：类型为 INT 。
	版  本：1.0.0.1
	作  者：康  林
	时  间：2005年8月12日 18:17:06
	*******************************************************************************************************/
	template < class T > 
		INT AddElement(CList < T *, T * > & p)
	{
		while(1)
		{
			CString szWord = GetWord();
			if(GetWordType(szWord) == NO)
			{
				CString szIn = GetWord();
				switch(GetWordType(szIn))
				{
				case SEMICOLON:
					{
						T * key = new T;
						key->szName = szWord;
						p.AddTail(key);
						TRACE(_T("%s(%d) : 加入成功。\n"), __FILE__, __LINE__);
					}
					return 1;
				case COMMA:
					{
						T * key = new T;
						key->szName = szWord;
						p.AddTail(key);
						TRACE(_T("%s(%d) : 加入成功。\n"), __FILE__, __LINE__);
					}
					continue;
				default:
					TRACE(_T("%s(%d) : 语法错误,期望输入“,” 或 “;”\n"), __FILE__, __LINE__);
					Error(_T("语法错误, 期望输入“, ” 或 “; ”"));
					return 0;
				} // 结束 switch(GetWordType(szIn))
			}
			else
			{
				if(GetWordType(szWord) != SEMICOLON)
				{
					TRACE(_T("%s(%d) : 语法错误。符号已经定义。类型(typedef)定义出错。%s\n"), __FILE__, __LINE__, szWord);
					Error(_T("语法错误。符号已经定义。") + szWord);
				} // 结束 if(GetWordType(szWord) != SEMICOLON)
				return 0;
			} // 结束 if(GetWordType(szWord) == NO)
		} // 结束 while(1)
		return 0;
	}

	/*******************************************************************************************************
	函数名：AddStruct
	描  述：向结构列表中增加新的元素。
	参  数：
	        CList< T *, T * >&para：结构键表。
			CString szName        ：新增加元素名。
	返回值：类型为 INT 。
	版  本：1.0.0.1
	作  者：康  林
	时  间：2005年8月12日 18:16:53
	*******************************************************************************************************/
	template < class T > 
		INT AddStruct(CList < T *, T * > &para, CString szName)
	{
		CString szWord = GetWord();
		T * p = new T;
		if(!p)
		{
			TRACE(_T("%s(%d) : 内存分配失败。\n"), __FILE__, __LINE__);
			return 0;
		} // 结束 if(!p)
		while(GetWordType(szWord) != RIGHTBIGBRACKET)
		{
			switch(GetWordType(szWord))
			{
			case DATATYPEDEFINE:
			case CLASSDEFINE:
			case STRUCTDEFINE:
			case UNIONDEFINE:
			case ENUMDEFINE:
				while(1)
				{				
					szWord = GetWord();
					if(GetWordType(szWord) == NO)
					{
						CString szIn = GetWord();
						ENUM_TYPE et = GetWordType(szIn);
						if(et == COMMA || et == SEMICOLON)
						{
							p->szName = szName;
							p->m_lsItem.AddTail(szWord);
							if(et == SEMICOLON)
							{
								break;
							} // 结束 if(et == SEMICONLON)
							continue;
						} // 结束 if(et == COMMA || et == SEMICONLON)
					}
					else
					{
						delete p;
						TRACE(_T("%s(%d) : 语法出错，标识符已定义。%s\n"), __FILE__, __LINE__, szWord);
						Error(_T("语法出错，标识符已定义。") + szWord);
						return 0;
					} // 结束 if(GetWordType(szWord) == NO)
				} // 结束 while(1)
				break;
			default:
				delete p;
				TRACE(_T("%s(%d) : 语法出错，盼望输入数据类型。%s\n"), __FILE__, __LINE__, szWord);
				Error(_T("语法出错，盼望输入数据类型。") + szWord);
				return 0;
			} // 结束 switch(GetWordType(szWord))
			szWord = GetWord();
		} // 结束 while(GetWordType(szWord) != LEFTBIGBRACKET)

		para.AddTail(p);
		return 1;
	}

	/*******************************************************************************************************
	函数名：AddEnum
	描  述：向常量列表中增加新元素
	参  数：
	        CList< T *, T * >&para：常量元素。
			CString szName = ""   ：新增加元素名。
	返回值：类型为 INT 。
	版  本：1.0.0.1
	作  者：康  林
	时  间：2005年8月12日 18:18:48
	*******************************************************************************************************/
	template < class T > 
		INT AddEnum(CList < T *, T * > &para, CString szName = "")
	{
		T * p = new T;
		if(!p)
		{
			TRACE(_T("%s(%d) : 内存分配失败。\n"), __FILE__, __LINE__);
			return 0;
		} // 结束 if(!p)
		p->szName = szName;
		CString szWord = GetWord();
		while(GetWordType(szWord) != RIGHTBIGBRACKET)
		{
			CString szIn = GetWord();
			ENUM_TYPE et = GetWordType(szIn);
			if(et == COMMA || et == RIGHTBIGBRACKET)
			{
				p->m_lsItem.AddTail(szWord);
				if(et == RIGHTBIGBRACKET)
				{
					szWord = szIn;
					continue;
				} // 结束 if(et == RIGHTBIGBRACKET)
			}
			else
			{
				TRACE(_T("%s(%d) : 错误,盼望输入“,”或“}”。%s\n"), __FILE__, __LINE__, szIn);
				Error(_T("错误,盼望输入“,”或“}”。"));
			} // 结束 if(et == COMMA || et == RIGHTBIGBRACKET)
			szWord = GetWord();
		} // 结束 while(GetWordType(szWord) != RIGHTBIGBRACKET)
			
		para.AddTail(p);
		return 1;
	}

public:
	INT Working();
	LPTSTR Space();
	CString Comment();
	CString Quotation();
	// 得到当前单词
	CString GetWord();
	// 判断当前输入字符是否是单词界符
	INT LimitChar(void);
	// 得到单词类型
	ENUM_TYPE GetWordType(CString szWord);
	// 加载关键字
	BOOL LoadKeyWord(LPCTSTR lpszFileName);
	int fTypedef(void);
	// 出错提示
	int Error(CString szError);
	// 关键字 class 的操作
	int fClass(void);
	int fEnum(BOOL bVar = TRUE);
	int fStruct(BOOL bVar = TRUE);
	int fUnion(BOOL bVar = TRUE);


#ifdef _DEBUG
	void ShowAll(void);
#endif
	int fFunction(void);
};

#endif  // !defined(AFX_SYNATX_H__0FABDB8A_B153_4BDA_A5C3_970F487EA566__INCLUDED_)
