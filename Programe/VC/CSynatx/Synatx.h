/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Synatx.h
��  ����C++ �ʷ�������
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��13��
ʱ  �䣺13:41:53
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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
	} // ���� while(pos)
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
	} // ���� while(pos)
}

template < class T > 
void ShowListStruct(CList < T *, T * > &para)
{
	POSITION pos = para.GetHeadPosition();
	while(pos)
	{
		T * key = para.GetNext(pos);
		TRACE(_T("%s\n"), key->szName);
		TRACE(_T("Ԫ��\n"));
		POSITION pos = key->m_lsItem.GetHeadPosition();
		while(pos)
		{
			CString key1 = key->m_lsItem.GetNext(pos);
			TRACE(_T("%s\n"), key1);
		} // ���� while(pos)
		TRACE(_T("Ԫ��end\n"));
	} // ���� while(pos)
}
#endif

class CSynatx  
{
public:
	static const int TAB = 9;    //�Ʊ��
	static const int CR = 13;    //�س���
	static const int LF = 10;    //���з�
	enum ENUM_TYPE
	{
		NO = 0,
		KEYWORD,         //�ؼ���
		DATATYPEDEFINE,  //�������͵Ķ���
		VARIABLE,        //�����Ķ���
		FLOWCONTROL,     //���̿���
		FUNCTION,        //����
		FUNCTIONDEFINE,
		CLASS,           //��
		CLASSDEFINE,
		STRUCT,          //�ṹ
		STRUCTDEFINE,
		ENUM,            //ö��
		ENUMDEFINE,
		UNION,           //����
		UNIONDEFINE,
		NAMESPACE,       //�����ռ�
		NAMESPACEDEFINE,
		COMMENT,         //ע��
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
		SEMICOLON,    //�ֺ�
		COMMA,        //����
		DOT,          //���
		ADD,          //�Ӻ�
		SUBTRACTION,  //����
		MULTIPLY,     //�˺�
		DIVISION,     //����
		BIG,          //���ں�
		LESS,         //С�ں�
		EQUAL,        //�Ⱥ�
		RIGHTBIGBRACKET,     //�Ҵ�����
		LEFTBIGBRACKET,      //�������
		RIGHTLITTLEBRACKET,  //��С����
		LEFTLITTLEBRACKET,   //��С����
		RIGHTMIDBRACKET,     //��������
		LEFTMIDBRACKET       //��������
	};

	CSynatx(LPCSTR lpszCode, LONG nLen);
	CSynatx(LPCSTR lpszFileName);
	CSynatx();
	virtual ~CSynatx();
	BOOL LoadCode(LPCTSTR lpszCode, LONG nLen);
    BOOL LoadCode(LPCTSTR lpszFileName);
	
private:
	LPTSTR m_lpszCode;     //���뻺����
	LONG m_nCodeLen;       //���볤��

	LPTSTR m_lpCur;
	LPTSTR m_lpWord;

	CString m_szFileName;  //�ļ���
	INT m_nLine;           //�к�

	void Init();
	void InitPoint();      //��ʼ����ָ��
	void ClearCode();      //������뻺��

	int m_nEnum;
	int m_nStruct;
	int m_nUnion;
	int m_nClass;
	
public:

	struct _IDENTIFIER
	{
		CString szName;  // ����
		CString szArea;  //��
	};
	CList < _IDENTIFIER *, _IDENTIFIER * > m_lsIdentifier;  //��ʶ��
	class _STRUCT : public _IDENTIFIER
	{
	public:
		CList < CString, CString > m_lsItem;
	};
	typedef _STRUCT _UNION, _ENUM;
	CList < _STRUCT *, _STRUCT * > m_lsStruct;  //�ṹ
	CList < _UNION *, _UNION * > m_lsUnion;     //����
	CList < _ENUM *, _ENUM * > m_lsEnum;        //ö�� 

	class _DATATYPE : public _IDENTIFIER
	{
	public:
		CString szVal;      //ֵ
		CString szComment;  //ע��
	};
	typedef _DATATYPE _VARIABLE;
	CList < _DATATYPE *, _DATATYPE * > m_lsDataType;  //����
	CList < _VARIABLE *, _VARIABLE * > m_lsVariable;  //����
	class _FUNCTION : public _IDENTIFIER
	{
	public:
		CString szDeclare;  //����
		CString szComment;  //ע��
	};
	CList < _FUNCTION*, _FUNCTION* > m_lsFunction;    //����
	class _CLASS : public _FUNCTION
	{
	public:
		CList < _IDENTIFIER*, _IDENTIFIER* > m_lsIdentifier;  //��ʶ��
		CList < _STRUCT *, _STRUCT * > m_lsStruct;            //�ṹ
		CList < _UNION *, _UNION * > m_lsUnion;               //����
		CList < _ENUM *, _ENUM * > m_lsEnum;                  //ö�� 
		CList < _DATATYPE *, _DATATYPE * > m_lsDataType;      //����
		CList < _VARIABLE *, _VARIABLE * > m_lsVariable;      //����
		CList < _FUNCTION *, _FUNCTION * > m_lsFunction;      //����
		CList < _CLASS*, _CLASS* > m_lsClass;                 //��
		~_CLASS(void);
	};
	CList < _CLASS *, _CLASS * > m_lsClass;  //��

	/*******************************************************************************************************
	��������SearchList
	��  ������������ָ��Ԫ��
	��  ����
	        CList< T, T >&para��
			RT reval          ��
			CString szWord    ��Ԫ������
	����ֵ������Ϊ INT ��
	��  ����1.0.0.1
	��  �ߣ���  ��
	ʱ  �䣺2005��8��12�� 18:19:51
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
			} // ���� if(key.szName = szWord)
		} // ���� while(pos)
		return NO;
	}

	/*******************************************************************************************************
	��������SearchList
	��  ������������ָ��Ԫ��
	��  ����
	        CList< T *, T * >&para��
			RT reval              ��
			CString szWord        ��Ԫ������
	����ֵ������Ϊ INT ��
	��  ����1.0.0.1
	��  �ߣ���  ��
	ʱ  �䣺2005��8��12�� 18:20:27
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
			} // ���� if(key.szName = szWord)
		} // ���� while(pos)
		return NO;
	}

	/*******************************************************************************************************
	��������AddElement
	��  �����������м����µ�Ԫ��
	��  ����
	        CList< T *, T * >& p���б�
	����ֵ������Ϊ INT ��
	��  ����1.0.0.1
	��  �ߣ���  ��
	ʱ  �䣺2005��8��12�� 18:17:06
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
						TRACE(_T("%s(%d) : ����ɹ���\n"), __FILE__, __LINE__);
					}
					return 1;
				case COMMA:
					{
						T * key = new T;
						key->szName = szWord;
						p.AddTail(key);
						TRACE(_T("%s(%d) : ����ɹ���\n"), __FILE__, __LINE__);
					}
					continue;
				default:
					TRACE(_T("%s(%d) : �﷨����,�������롰,�� �� ��;��\n"), __FILE__, __LINE__);
					Error(_T("�﷨����, �������롰, �� �� ��; ��"));
					return 0;
				} // ���� switch(GetWordType(szIn))
			}
			else
			{
				if(GetWordType(szWord) != SEMICOLON)
				{
					TRACE(_T("%s(%d) : �﷨���󡣷����Ѿ����塣����(typedef)�������%s\n"), __FILE__, __LINE__, szWord);
					Error(_T("�﷨���󡣷����Ѿ����塣") + szWord);
				} // ���� if(GetWordType(szWord) != SEMICOLON)
				return 0;
			} // ���� if(GetWordType(szWord) == NO)
		} // ���� while(1)
		return 0;
	}

	/*******************************************************************************************************
	��������AddStruct
	��  ������ṹ�б��������µ�Ԫ�ء�
	��  ����
	        CList< T *, T * >&para���ṹ����
			CString szName        ��������Ԫ������
	����ֵ������Ϊ INT ��
	��  ����1.0.0.1
	��  �ߣ���  ��
	ʱ  �䣺2005��8��12�� 18:16:53
	*******************************************************************************************************/
	template < class T > 
		INT AddStruct(CList < T *, T * > &para, CString szName)
	{
		CString szWord = GetWord();
		T * p = new T;
		if(!p)
		{
			TRACE(_T("%s(%d) : �ڴ����ʧ�ܡ�\n"), __FILE__, __LINE__);
			return 0;
		} // ���� if(!p)
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
							} // ���� if(et == SEMICONLON)
							continue;
						} // ���� if(et == COMMA || et == SEMICONLON)
					}
					else
					{
						delete p;
						TRACE(_T("%s(%d) : �﷨������ʶ���Ѷ��塣%s\n"), __FILE__, __LINE__, szWord);
						Error(_T("�﷨������ʶ���Ѷ��塣") + szWord);
						return 0;
					} // ���� if(GetWordType(szWord) == NO)
				} // ���� while(1)
				break;
			default:
				delete p;
				TRACE(_T("%s(%d) : �﷨�������������������͡�%s\n"), __FILE__, __LINE__, szWord);
				Error(_T("�﷨�������������������͡�") + szWord);
				return 0;
			} // ���� switch(GetWordType(szWord))
			szWord = GetWord();
		} // ���� while(GetWordType(szWord) != LEFTBIGBRACKET)

		para.AddTail(p);
		return 1;
	}

	/*******************************************************************************************************
	��������AddEnum
	��  ���������б���������Ԫ��
	��  ����
	        CList< T *, T * >&para������Ԫ�ء�
			CString szName = ""   ��������Ԫ������
	����ֵ������Ϊ INT ��
	��  ����1.0.0.1
	��  �ߣ���  ��
	ʱ  �䣺2005��8��12�� 18:18:48
	*******************************************************************************************************/
	template < class T > 
		INT AddEnum(CList < T *, T * > &para, CString szName = "")
	{
		T * p = new T;
		if(!p)
		{
			TRACE(_T("%s(%d) : �ڴ����ʧ�ܡ�\n"), __FILE__, __LINE__);
			return 0;
		} // ���� if(!p)
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
				} // ���� if(et == RIGHTBIGBRACKET)
			}
			else
			{
				TRACE(_T("%s(%d) : ����,�������롰,����}����%s\n"), __FILE__, __LINE__, szIn);
				Error(_T("����,�������롰,����}����"));
			} // ���� if(et == COMMA || et == RIGHTBIGBRACKET)
			szWord = GetWord();
		} // ���� while(GetWordType(szWord) != RIGHTBIGBRACKET)
			
		para.AddTail(p);
		return 1;
	}

public:
	INT Working();
	LPTSTR Space();
	CString Comment();
	CString Quotation();
	// �õ���ǰ����
	CString GetWord();
	// �жϵ�ǰ�����ַ��Ƿ��ǵ��ʽ��
	INT LimitChar(void);
	// �õ���������
	ENUM_TYPE GetWordType(CString szWord);
	// ���عؼ���
	BOOL LoadKeyWord(LPCTSTR lpszFileName);
	int fTypedef(void);
	// ������ʾ
	int Error(CString szError);
	// �ؼ��� class �Ĳ���
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
