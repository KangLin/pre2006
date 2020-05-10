/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Synatx.cpp
描  述：C++ 词法分析类
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月13日
时  间：13:42:27
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/

#include "stdafx.h"
#include "Synatx.h"
#include ".\synatx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#ifdef _DEBUG 
/*******************************************************************************************************
函数名：ShowAll
描  述：用于调试时显示所有列表数据。
参  数：
        void：无
返回值：类型为 void 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月12日 16:00:01
*******************************************************************************************************/
void CSynatx::ShowAll(void)
{
	TRACE(_T("DebugShowAll\n"));
	TRACE(_T("类:\n"));
	ShowListAll(m_lsClass);
	TRACE(_T("类型定义:\n"));
	ShowListAll(m_lsDataType);
	TRACE(_T("结构定义:\n"));
	ShowListStruct(m_lsStruct);
	TRACE(_T("Enum定义:\n"));
	ShowListStruct(m_lsEnum);		
	TRACE(_T("枚举定义:\n"));
	ShowListStruct(m_lsUnion);
	TRACE(_T("变量定义:\n"));
	ShowListAll(m_lsVariable);
}
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSynatx::CSynatx()
{
	Init();
	InitPoint();

	m_nEnum=0;
	m_nStruct=0;
	m_nUnion=0;
	m_nClass=0;
}

CSynatx::~CSynatx()
{
	ClearCode();

	DeleteList(m_lsClass);
	DeleteList(m_lsStruct);
	DeleteList(m_lsUnion);
	DeleteList(m_lsEnum);
	DeleteList(m_lsDataType);
	DeleteList(m_lsVariable);
	DeleteList(m_lsFunction);
}

CSynatx::_CLASS::~_CLASS(void)
{
	DeleteList(m_lsClass);
	DeleteList(m_lsIdentifier);
	DeleteList(m_lsStruct);
	DeleteList(m_lsUnion);
	DeleteList(m_lsEnum);
	DeleteList(m_lsDataType);
	DeleteList(m_lsVariable);
	DeleteList(m_lsFunction);
}

/*******************************************************************************************************
函数名：CSynatx
描  述：从指定的文件装载代码
参  数：
        LPCSTR lpszFileName：文件名
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月13日 13:45:07
*******************************************************************************************************/
CSynatx::CSynatx(LPCSTR lpszFileName)
{
	LoadCode(lpszFileName);
}

/*******************************************************************************************************
函数名：CSynatx
描  述：从指定的内存处加载代码
参  数：
        LPCTSTR lpszCode：代码
		LONG nLen       ：代码长度
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月13日 13:45:42
*******************************************************************************************************/
CSynatx::CSynatx(LPCTSTR lpszCode, LONG nLen)
{
	LoadCode(lpszCode, nLen);
}

/*******************************************************************************************************
函数名：LoadCode
描  述：从指定内存区装载代码
参  数：
        LPCTSTR lpszCode：代码地址
		LONG nLen       ：代码长度
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月13日 18:43:24
*******************************************************************************************************/
BOOL CSynatx::LoadCode(LPCTSTR lpszCode, LONG nLen)
{
	ClearCode();
	ASSERT(nLen != 0);
	m_nCodeLen = nLen;
	m_lpszCode = new TCHAR[nLen + sizeof(TCHAR)];
	if(!m_lpszCode)
	{
		return FALSE;
	} // 结束 if(!m_lpszCode)
	_tcscpy(m_lpszCode, lpszCode);
	InitPoint();
	return TRUE;
}

/*******************************************************************************************************
函数名：LoadCode
描  述：从指定文件中装载代码
参  数：
        LPCTSTR lpszFileName：文件名
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月13日 18:43:54
*******************************************************************************************************/
BOOL CSynatx::LoadCode(LPCTSTR lpszFileName)
{
	ClearCode();
	ASSERT(lpszFileName != NULL);
	if(!lpszFileName)
	{
		TRACE(_T("%s(%d) : 未指定文件名\n"), __FILE__, __LINE__);
		return FALSE; 
	} // 结束 if(!lpszFileName)
	TRY
	{
		CFile f(lpszFileName, CFile::modeReadWrite); 
		m_nCodeLen = f.GetLength(); 
		m_lpszCode = new TCHAR[m_nCodeLen + sizeof(TCHAR)];
		if(!m_lpszCode)
		{
			return FALSE;
		} // 结束 if(!m_lpszCode)
		f.Read(m_lpszCode, m_nCodeLen); 
		f.Close();
		InitPoint();
		m_szFileName = lpszFileName;
	}
	CATCH(CFileException, e)
	{
		TRACE(_T("%s(%d) : 文件错误\n"), __FILE__, __LINE__);
		e->ReportError();
		CString szError(_T("不能打开文件"));
		Error(szError + lpszFileName);
	}
	END_CATCH

	return TRUE;
}

/*******************************************************************************************************
函数名：LoadKeyWord
描  述：加载关键字
参  数：
        LPCTSTR lpszFileName：包含关键字的文件名
返回值：类型为 BOOL 。成功返回 TRUE ，否则返回 FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月2日 8:19:54
*******************************************************************************************************/
BOOL CSynatx::LoadKeyWord(LPCTSTR lpszFileName)
{
	TRY
	{
		CStdioFile sf(lpszFileName, CFile::modeRead);
		CString szIn;
		while(sf.ReadString(szIn))
		{
		
		} // 结束 while(sf.ReadString(szIn))
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH
	return 0;
}

/*******************************************************************************************************
函数名：InitPoint
描  述：初始化各指针
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月13日 18:48:10
*******************************************************************************************************/
void CSynatx::InitPoint()
{
	m_lpCur = m_lpszCode;
	m_lpWord = m_lpCur;
}

void CSynatx::Init()
{
	m_lpszCode = NULL;
	m_nCodeLen = 0;
	m_nLine = 0;
	m_szFileName = _T("");	
}

/*******************************************************************************************************
函数名：ClearCode
描  述：清除代码缓存
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月13日 18:47:50
*******************************************************************************************************/
void CSynatx::ClearCode()
{
	if(m_lpszCode)
	{
		delete []m_lpszCode;
		m_lpszCode = NULL;
	} // 结束 if(m_lpszCode)
	m_nCodeLen = 0;
	m_nLine = 0;
	m_szFileName = _T("");

	m_nEnum=0;
	m_nStruct=0;
	m_nUnion=0;
	m_nClass=0;
}

/*******************************************************************************************************
函数名：Error
描  述：出错提示
参  数：
        CString szError：错误信息
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月2日 10:34:36
*******************************************************************************************************/
int CSynatx::Error(CString szError)
{
	//增加:错误处理显示
	return 0;
}

/*******************************************************************************************************
函数名：Space
描  述：去掉相邻的多余的空格
参  数：
        LPTSTR* lppIn：输入字符串指针
返回值：当前指针
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月13日 18:26:30
*******************************************************************************************************/
LPTSTR CSynatx::Space()
{
	while((*m_lpCur == _T(' ') || *m_lpCur == _T(TAB) || *m_lpCur == _T(CR) || *m_lpCur == _T(LF))
		&& (m_lpCur < m_lpszCode + m_nCodeLen))
	{
		if(*m_lpCur == _T(CR) && *(m_lpCur + 1) == _T(LF))
		{
			m_lpCur++;
			m_nLine++;
		} // 结束 if(*m_lpCur == _T(CR) && *(m_lpCur + 1) == _T(LF))
		m_lpCur++;
	} // 结束 while((*m_lpCur == _T(' ') || *m_lpCur == _T(TAB) || *m_lpCur == _T(CR) || *m_lpCur == _T(LF)) && (m_lpCur < m_lpszCode + m_nCodeLen))
	return m_lpCur;
}

/*******************************************************************************************************
函数名：Comment
描  述：去掉代码中的注释
参  数：无
返回值：类型为 CString 。
        ""为语法错误，没有结束注释符。
		"/"为不是注释。
		其它为注释，包括注释符在内。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月17日 18:27:17
*******************************************************************************************************/
CString CSynatx::Comment()
{
	CString szOut;
	szOut = *m_lpCur;
    TCHAR end[2];
    if(*(m_lpCur + 1) == '*')
    {
        end[0] = '*';
        end[1] = '/';
    }
    else if(*(m_lpCur + 1) == '/')
    {
        end[0] = CR;
        end[1] = LF;
    }
    else
	{
        return szOut;
    } // 结束 if(*(m_lpCur + 1) == '*')
    szOut += *m_lpCur;
    m_lpCur += 2;
    while(m_lpCur < m_lpszCode + m_nCodeLen)
    {
        if(*m_lpCur == end[0] && *(m_lpCur + 1) == end[1])
        {
            m_lpCur += 2;
			szOut += end[0];
			szOut += end[1];
            return szOut;
        } // 结束 if(*m_lpCur == end[0] && *(m_lpCur + 1) == end[1])
        m_lpCur++;
		szOut += *m_lpCur;
    } // 结束 while(m_lpCur < m_lpszCode + m_nCodeLen)
	TRACE(_T("%s(%d) : 错误,缺少注释结束符：%c%c\n"), __FILE__, __LINE__, end[0], end[1]);
	CString szError(_T("错误,缺少注释结束符："));
	if(end[0] == CR)
	{
		szError += _T("CRLF"); 
	}
	else
	{
		szError += _T("*/");
	} // 结束 if(end[0] == CR)
	Error(szError);
	szOut = _T("");
	return szOut;
}

/*******************************************************************************************************
函数名：QuotationC
描  述：保留引号中的字符
参  数：
         LPTSTR* lppIn ：输入字符串指针
         LPTSTR* lppOut：输出字符串指针
		 BOOL bQutation：是否保留引号和引号之间的内容，默认为 TRUE，保留；FALSE，不保留
返回值：类型为 CString 。
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-21 13:35:14
*******************************************************************************************************/
CString CSynatx::Quotation()
{
    TCHAR ch = *m_lpCur;
	m_lpCur++;
	CString szOut(ch);
    while(*m_lpCur != NULL)
    {
		if(*m_lpCur == _T('\\')
			&& (*(m_lpCur + 1) == _T('\'') || *(m_lpCur + 1) == _T('\"') || *(m_lpCur + 1) == _T('\\')))
        {
            szOut += *m_lpCur;
			szOut += *(m_lpCur + 1);
            m_lpCur += 2;
            continue;
        } // 结束 if(*m_lpCur == _T('\\') && (*(m_lpCur + 1) == _T('\'') || *(m_lpCur + 1) == _T('\"') || *(m_lpCur + 1) == _T('\\')))
        if(*m_lpCur == ch)
		{
			szOut += *m_lpCur;
			m_lpCur++;
            return szOut;
		} // 结束 if(*m_lpCur == ch)
        m_lpCur++;
		szOut += *m_lpCur;
	} // 结束 while(*m_lpCur != NULL)
	szOut = _T("");
	TRACE(_T("%s(%d) : 语法错误，缺少右引号:%c\n"), __FILE__, __LINE__, ch);
	Error(_T("语法错误，缺少右引号。"));
}

/*******************************************************************************************************
函数名：GetWord
描  述：导出单词
参  数：无
返回值：类型为 CString 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月1日 15:56:42
*******************************************************************************************************/
CString CSynatx::GetWord()
{
	//去掉空格、制表符、注释
	while(m_lpCur < m_lpszCode + m_nCodeLen)
	{
		switch(*m_lpCur)
		{
		case _T(CR):
			if(*(m_lpCur + 1) == _T(LF))
			{
				m_nLine++;
				m_lpCur += 2;
			} // 结束 if(*(m_lpCur + 1) == _T(LF))
		case _T(LF):
		case _T(' '):
		case _T(TAB):
			Space();
			continue;
		case _T('/'):			
			if(Comment() == _T(""))
			{
				TRACE(_T("%s(%d) : 得到单词出错\n"), __FILE__, __LINE__);
				return _T("");
			} // 结束 if(Comment() == _T(""))
			continue;
		case _T('\"'):
		case _T('\''):
			//修改:注释是否返回
			return Quotation();			
		default:
			break;
		} // 结束 switch(*m_lpCur)
		break;
	} // 结束 while(m_lpCur < m_lpszCode + m_nCodeLen)

	CString szWord("");
	while(m_lpCur < m_lpszCode + m_nCodeLen)
	{
		switch(LimitChar())
		{
		case 0:        //不是单词分界符
			szWord += *m_lpCur;
			m_lpCur++;
			continue;
		case _T(':'):
			if(*(m_lpCur + 1) == _T(':'))
			{
				szWord += _T("::");
				m_lpCur += 2;
				continue;
			} // 结束 if(*(m_lpCur + 1) == _T(':'))
		case _T('-'):  //增加:是负数时
		case _T('.'):  //增加:是小数时
		case _T('^'):  //增加:是指数时
		default:
			break;
		} // 结束 switch(LimitChar())
		break;
	} // 结束 while(m_lpCur < m_lpszCode + m_nCodeLen)
	if(szWord == _T(""))
	{
		szWord = *m_lpCur;
		m_lpCur++;
	} // 结束 if(szWord == _T(""))
	return szWord;
}

INT CSynatx::Working()
{
	CString szIn = GetWord();
	while(m_lpCur < m_lpszCode + m_nCodeLen && szIn != _T(""))
	{
		switch(GetWordType(szIn))
		{
		case TYPEDEF:
			fTypedef();
			break;
		case CLASS:
			fClass();
			break;
		case ENUM:
			fEnum();
			break;
		case STRUCT:
			fStruct();
			break;
		case UNION:
			fUnion();
			break;
		case DATATYPEDEFINE:
		case CLASSDEFINE:
		case STRUCTDEFINE:
		case ENUMDEFINE:
		case UNIONDEFINE:
			fFunction();			
			break;
		default:
			TRACE(_T("%s(%d) : 语法错误。不是盼望的语句。%s\n"), __FILE__, __LINE__, szIn);
			Error(_T("语法错误。不是盼望的语句。") + szIn);
			m_lpCur++;
		} // 结束 ()
		szIn = GetWord();
	} // 结束 while(m_lpCur < m_lpszCode + m_nCodeLen && szIn != _T(""))

	return 0;
}

/*******************************************************************************************************
函数名：LimitChar
描  述：判断当前输入字符是否是单词分界符
参  数：
        void：无
返回值：类型为 INT 。是返回分界符；否返回 0
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月1日 17:13:42
*******************************************************************************************************/
INT CSynatx::LimitChar(void)
{
	switch(*m_lpCur)
	{
	case _T('~'):
	case _T('!'):
	case _T('%'):
	case _T('^'):		
	case _T('&'):
	case _T('*'):
	case _T('('):
	case _T(')'):
	case _T('{'):
	case _T('}'):
	case _T('['):
	case _T(']'):
	case _T('-'):		
	case _T('+'):
	case _T('='):
	case _T('|'):
	case _T('\\'):
	case _T(':'):
	case _T(';'):
	case _T('<'):
	case _T(','):
	case _T('.'):		
	case _T('>'):
	case _T(' '):
	case _T(TAB):
	case _T(CR):
	case _T(LF):
		return *m_lpCur;
	default:
		break;
	} // 结束 switch(*m_lpCur)
	return 0;
}

/*******************************************************************************************************
函数名：GetWordType
描  述：得到单词类型
参  数：
        void：无
返回值：类型为 INT 。单词类型。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月2日 7:46:37
*******************************************************************************************************/
CSynatx::ENUM_TYPE CSynatx::GetWordType(CString szWord)
{
	if(_T(";") == szWord)
	{
		return SEMICOLON;
	} // 结束 if(_T(";") == szWord)
	if(_T(",") == szWord)
	{
		return COMMA;
	} // 结束 if(_T(",") == szWord)
	if(_T("(") == szWord)
	{
		return LEFTLITTLEBRACKET;
	} // 结束 if(_T("(") == szWord)
	if(_T(")") == szWord)
	{
		return RIGHTLITTLEBRACKET;
	} // 结束 if(_T(")") == szWord)
	if(_T("[") == szWord)
	{
		return LEFTMIDBRACKET;
	} // 结束 if(_T("[") == szWord)
	if(_T("]") == szWord)
	{
		return RIGHTMIDBRACKET;
	} // 结束 if(_T("]") == szWord)
	if(_T("{") == szWord)
	{
		return LEFTBIGBRACKET;
	} // 结束 if(_T("{") == szWord)
	if(_T("}") == szWord)
	{
		return RIGHTBIGBRACKET;
	} // 结束 if(_T("}") == szWord)
	
	if(_T("if") == szWord)
	{
		return IF;
	} // 结束 if(_T("if") == szWord)
	if(_T("else") == szWord)
	{
		return ELSE;
	} // 结束 if(_T("else") == szWord)
	if(_T("endif") == szWord)
	{
		return ENDIF;
	} // 结束 if(_T("endif") == szWord)
	if(_T("for") == szWord)
	{
		return FOR;
	} // 结束 if(_T("for") == szWord)
	if(_T("switch") == szWord)
	{
		return SWITCH;
	} // 结束 if(_T("switch") == szWord)
	if(_T("case") == szWord)
	{
		return CASE;
	} // 结束 if(_T("case") == szWord)
	if(_T("default") == szWord)
	{
		return DEFAULT;
	} // 结束 if(_T("default") == szWord)
	if(_T("break") == szWord)
	{
		return BREAK;
	} // 结束 if(_T("break") == szWord)
	if(_T("continue") == szWord)
	{
		return CONTINUE;
	} // 结束 if(_T("continue") == szWord)
	if(_T("while") == szWord)
	{
		return WHILE;
	} // 结束 if(_T("while") == szWord)
	if(_T("do") == szWord)
	{
		return DO;
	} // 结束 if(_T("do") == szWord)
	if(_T("goto") == szWord)
	{
		return GOTO;
	} // 结束 if(_T("goto") == szWord)
	if(_T("return") == szWord)
	{
		return RETURN;
	} // 结束 if(_T("return") == szWord)
	if(_T("sizeof") == szWord)
	{
		return SIZEOF;
	} // 结束 if(_T("sizeof") == szWord)
	if(_T("typedef") == szWord)
	{
		return TYPEDEF;
	} // 结束 if(_T("typedef") == szWord)
	if(_T("class") == szWord)
	{
		return CLASS;
	} // 结束 if(_T("class") == szWord)
	if(_T("struct") == szWord)
	{
		return STRUCT;
	} // 结束 if(_T("struct") == szWord)
	if(_T("enum") == szWord)
	{
		return ENUM;
	} // 结束 if(_T("enum") == szWord)
	if(_T("union") == szWord)
	{
		return UNION;
	} // 结束 if(_T("union") == szWord)
	if(_T("+") == szWord)
	{
		return ADD;
	} // 结束 if(_T("+") == szWord)
	if(_T("-") == szWord)
	{
		return SUBTRACTION;
	} // 结束 if(_T("-") == szWord)
	if(_T("*") == szWord)
	{
		return MULTIPLY;
	} // 结束 if(_T("*") == szWord)
	if(_T("/") == szWord)
	{
		return DIVISION;
	} // 结束 if(_T("/") == szWord)
	if(_T(".") == szWord)
	{
		return DOT;
	} // 结束 if(_T(".") == szWord)
	if(_T(">") == szWord)
	{
		return BIG;
	} // 结束 if(_T(">") == szWord)
	if(_T("<") == szWord)
	{
		return LESS;
	} // 结束 if(_T("<") == szWord)
	if(_T("=") == szWord)
	{
		return EQUAL;
	} // 结束 if(_T("=") == szWord)

	//关键字类型
	if(_T("char") == szWord || _T("int") == szWord || _T("short") == szWord || _T("long") == szWord || _T("double") == szWord || _T("bool") == szWord || _T("float") == szWord)
	{
		return DATATYPEDEFINE;
	} // 结束 if(_T("char") == szWord || _T("int") == szWord || _T("short") == szWord || _T("long") == szWord || _T("double") == szWord || _T("bool") == szWord || _T("float") == szWord)

	ENUM_TYPE reval = SearchList(m_lsDataType, DATATYPEDEFINE, szWord);

	if(reval != NO)
	{
		return reval;
	} // 结束 if(reval != NO)

	reval = SearchList(m_lsClass, CLASSDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // 结束 if(reval != NO)

	reval = SearchList(m_lsStruct, STRUCTDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // 结束 if(reval != NO)

	reval = SearchList(m_lsUnion, UNIONDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // 结束 if(reval != NO)

	reval = SearchList(m_lsEnum, ENUMDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // 结束 if(reval != NO)

	reval = SearchList(m_lsVariable, VARIABLE, szWord);
	if(reval != NO)
	{
		return reval;
	} // 结束 if(reval != NO)

	reval = SearchList(m_lsFunction, FUNCTIONDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // 结束 if(reval != NO)

	return NO;
}

/*******************************************************************************************************
函数名：fTypedef
描  述：关键字 typedef 操作。
参  数：
        void：无
返回值：类型为 int 。成功返回非零，失败返回 0 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月2日 11:27:20
*******************************************************************************************************/
int CSynatx::fTypedef(void)
{
	CString szWord = GetWord();
	switch(GetWordType(szWord))
	{
	case CLASS:
		fClass();
		break;
	case STRUCT:
		fStruct(FALSE);
		break;
	case ENUM:
		if(fEnum(FALSE))
		{
			return AddElement(m_lsEnum);
		} // 结束 if(fEnum())		
		break;
	case UNION:
		fUnion(FALSE);
		break;
	case CLASSDEFINE:
		return AddElement(m_lsClass);
		break;
	case STRUCTDEFINE:
		return AddElement(m_lsStruct);
		break;
	case UNIONDEFINE:
		return AddElement(m_lsUnion);
		break;
	case ENUMDEFINE:
		return AddElement(m_lsEnum);
		break;
	case DATATYPEDEFINE:
		return AddElement(m_lsDataType);
		break;
	default:
		TRACE(_T("%s(%d) : 语法错误。类型(typedef)定义出错。%s\n"), __FILE__, __LINE__, szWord);
		Error(_T("语法错误。类型(typedef)定义出错。") + szWord);
		return 0;
	} // 结束 switch(GetWordType(szIn))
	return 1;
}

/*******************************************************************************************************
函数名：fClass
描  述：关键字 class 的操作。
参  数：
        void：无
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月2日 15:28:55
*******************************************************************************************************/
int CSynatx::fClass(void)
{
	CString szWord;
	szWord = GetWord();
	switch(GetWordType(szWord))
	{
	case NO:
		_CLASS * key = new _CLASS;
		key->szName = szWord;
		m_lsClass.AddTail(key);
		break;
	} // 结束 switch(GetWordType(szWord))
	return 0;
}

/*******************************************************************************************************
函数名：fEnum
描  述：关键字 enum 的操作。
参  数：
        BOOL bVar：TRUE，变量定义。FALSE，不考虑变量定义，只考虑 enum 。
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月12日 9:52:10
*******************************************************************************************************/
int CSynatx::fEnum(BOOL bVar)
{
	CString szWord;
	szWord = GetWord();
	INT reval = 0;
	switch(GetWordType(szWord))
	{
	case NO:
		{
			CString szIn = GetWord();
			if(GetWordType(szIn) == LEFTBIGBRACKET)
			{
				reval = AddEnum(m_lsEnum, szWord);
			}
			else
			{
				TRACE(_T("%s(%d) : 语法错误。盼望输入“{”。%s\n"), __FILE__, __LINE__, szIn);
				Error(_T(" 语法错误。盼望输入“{”。") + szIn);
				reval = 0;
			} // 结束 if(GetWordType(szIn) == LEFTBIGBRACKET)
		}
		break;
	case LEFTBIGBRACKET:
		{
			CString szIn;
			szIn.Format(_T("%d"), m_nEnum++);
			szIn = _T("_ENUM_NAME_") + szIn;
			reval = AddEnum(m_lsEnum, szIn);
		}		
		break;
	default:
		Error(_T("语法错误。(enum)") + szWord);
		TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, _T("语法错误。(enum)") + szWord);
		reval = 0;
	} // 结束 switch(GetWordType(szWord))

	//enum变量定义
	if(bVar)
	{
		reval = AddElement(m_lsVariable);
	} // 结束 if(bVar)
	return reval;
}

/*******************************************************************************************************
函数名：fStruct
描  述：关键字 struct 的操作
参  数：
        BOOL bVar：
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月12日 15:52:35
*******************************************************************************************************/
int CSynatx::fStruct(BOOL bVar)
{
	CString szWord;
	szWord = GetWord();
	INT reval = 0;
	switch(GetWordType(szWord))
	{
	case NO:
		{
			CString szIn = GetWord();
			if(GetWordType(szIn) == LEFTBIGBRACKET)
			{
				reval = AddStruct(m_lsStruct, szWord);
			}
			else
			{
				TRACE(_T("%s(%d) : 语法错误。盼望输入“{”。%s\n"), __FILE__, __LINE__, szIn);
				Error(_T(" 语法错误。盼望输入“{”。") + szIn);
				reval = 0;
			} // 结束 if(GetWordType(szIn) == LEFTBIGBRACKET)
		}
		break;
	case LEFTBIGBRACKET:
		{
			CString szIn;
			szIn.Format(_T("%d"), m_nStruct++);
			szIn = _T("_STRUCT_NAME_") + szIn;
			reval = AddStruct(m_lsStruct, szIn);
		}		
		break;
	default:
		Error(_T("语法错误。(struct)") + szWord);
		TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, _T("语法错误。(struct)") + szWord);
		reval = 0;
	} // 结束 switch(GetWordType(szWord))

	//变量定义
	if(bVar)
	{
		reval = AddElement(m_lsVariable);
	} // 结束 if(bVar)
	return reval;
}

/*******************************************************************************************************
函数名：fUnion
描  述：关键字 union 的操作。
参  数：
        BOOL bVar：
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月12日 15:53:09
*******************************************************************************************************/
int CSynatx::fUnion(BOOL bVar)
{
	CString szWord;
	szWord = GetWord();
	INT reval = 0;
	switch(GetWordType(szWord))
	{
	case NO:
		{
			CString szIn = GetWord();
			if(GetWordType(szIn) == LEFTBIGBRACKET)
			{
				reval = AddStruct(m_lsUnion, szWord);
			}
			else
			{
				TRACE(_T("%s(%d) : 语法错误。盼望输入“{”。%s\n"), __FILE__, __LINE__, szIn);
				Error(_T(" 语法错误。盼望输入“{”。") + szIn);
				reval = 0;
			} // 结束 if(GetWordType(szIn) == LEFTBIGBRACKET)
		}
		break;
	case LEFTBIGBRACKET:
		{
			CString szIn;
			szIn.Format(_T("%d"), m_nUnion++);
			szIn = _T("_UNION_NAME_") + szIn;
			reval = AddStruct(m_lsUnion, szIn);
		}		
		break;
	default:
		Error(_T("语法错误。(union)") + szWord);
		TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, _T("语法错误。(union)") + szWord);
		reval = 0;
	} // 结束 switch(GetWordType(szWord))

	//变量定义
	if(bVar)
	{
		reval = AddElement(m_lsVariable);
	} // 结束 if(bVar)
	return reval;
}

/*******************************************************************************************************
函数名：fFunction
描  述：变量定义或函数定义/声明。
参  数：
        void：无
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月12日 15:59:12
*******************************************************************************************************/
int CSynatx::fFunction(void)
{
	LPCTSTR p = m_lpCur;
	CString szWord;
	szWord = GetWord();
	switch(GetWordType(szWord))
	{
	case NO:
		//超前搜索
		CString szIn = GetWord();
		if(GetWordType(szIn) == LEFTLITTLEBRACKE)
		{
			//增加:函数定义或声明

		}
		else
		{
			//变量定义
			m_lpCur = p;
			return AddElement(m_lsVariable);
		} // 结束 if(GetWordType(szIn) == LEFTLITTLEBRACKE)
		break;
	case FUNCTIONDECLEARKEYWORD:
		break;
	default:
		TRACE(_T("%s(%d) : 语法错误。定义错误。%s\n"), __FILE__, __LINE__, szWord);
		Error(_T("语法错误。定义错误。") + szWord);
		retrun 0;
	} // 结束 switch(GetWordType(szWord))
	
	return 0;
}
