/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Synatx.cpp
��  ����C++ �ʷ�������
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��13��
ʱ  �䣺13:42:27
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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
��������ShowAll
��  �������ڵ���ʱ��ʾ�����б����ݡ�
��  ����
        void����
����ֵ������Ϊ void ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��12�� 16:00:01
*******************************************************************************************************/
void CSynatx::ShowAll(void)
{
	TRACE(_T("DebugShowAll\n"));
	TRACE(_T("��:\n"));
	ShowListAll(m_lsClass);
	TRACE(_T("���Ͷ���:\n"));
	ShowListAll(m_lsDataType);
	TRACE(_T("�ṹ����:\n"));
	ShowListStruct(m_lsStruct);
	TRACE(_T("Enum����:\n"));
	ShowListStruct(m_lsEnum);		
	TRACE(_T("ö�ٶ���:\n"));
	ShowListStruct(m_lsUnion);
	TRACE(_T("��������:\n"));
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
��������CSynatx
��  ������ָ�����ļ�װ�ش���
��  ����
        LPCSTR lpszFileName���ļ���
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��13�� 13:45:07
*******************************************************************************************************/
CSynatx::CSynatx(LPCSTR lpszFileName)
{
	LoadCode(lpszFileName);
}

/*******************************************************************************************************
��������CSynatx
��  ������ָ�����ڴ洦���ش���
��  ����
        LPCTSTR lpszCode������
		LONG nLen       �����볤��
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��13�� 13:45:42
*******************************************************************************************************/
CSynatx::CSynatx(LPCTSTR lpszCode, LONG nLen)
{
	LoadCode(lpszCode, nLen);
}

/*******************************************************************************************************
��������LoadCode
��  ������ָ���ڴ���װ�ش���
��  ����
        LPCTSTR lpszCode�������ַ
		LONG nLen       �����볤��
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��13�� 18:43:24
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
	} // ���� if(!m_lpszCode)
	_tcscpy(m_lpszCode, lpszCode);
	InitPoint();
	return TRUE;
}

/*******************************************************************************************************
��������LoadCode
��  ������ָ���ļ���װ�ش���
��  ����
        LPCTSTR lpszFileName���ļ���
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��13�� 18:43:54
*******************************************************************************************************/
BOOL CSynatx::LoadCode(LPCTSTR lpszFileName)
{
	ClearCode();
	ASSERT(lpszFileName != NULL);
	if(!lpszFileName)
	{
		TRACE(_T("%s(%d) : δָ���ļ���\n"), __FILE__, __LINE__);
		return FALSE; 
	} // ���� if(!lpszFileName)
	TRY
	{
		CFile f(lpszFileName, CFile::modeReadWrite); 
		m_nCodeLen = f.GetLength(); 
		m_lpszCode = new TCHAR[m_nCodeLen + sizeof(TCHAR)];
		if(!m_lpszCode)
		{
			return FALSE;
		} // ���� if(!m_lpszCode)
		f.Read(m_lpszCode, m_nCodeLen); 
		f.Close();
		InitPoint();
		m_szFileName = lpszFileName;
	}
	CATCH(CFileException, e)
	{
		TRACE(_T("%s(%d) : �ļ�����\n"), __FILE__, __LINE__);
		e->ReportError();
		CString szError(_T("���ܴ��ļ�"));
		Error(szError + lpszFileName);
	}
	END_CATCH

	return TRUE;
}

/*******************************************************************************************************
��������LoadKeyWord
��  �������عؼ���
��  ����
        LPCTSTR lpszFileName�������ؼ��ֵ��ļ���
����ֵ������Ϊ BOOL ���ɹ����� TRUE �����򷵻� FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��2�� 8:19:54
*******************************************************************************************************/
BOOL CSynatx::LoadKeyWord(LPCTSTR lpszFileName)
{
	TRY
	{
		CStdioFile sf(lpszFileName, CFile::modeRead);
		CString szIn;
		while(sf.ReadString(szIn))
		{
		
		} // ���� while(sf.ReadString(szIn))
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH
	return 0;
}

/*******************************************************************************************************
��������InitPoint
��  ������ʼ����ָ��
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��13�� 18:48:10
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
��������ClearCode
��  ����������뻺��
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��13�� 18:47:50
*******************************************************************************************************/
void CSynatx::ClearCode()
{
	if(m_lpszCode)
	{
		delete []m_lpszCode;
		m_lpszCode = NULL;
	} // ���� if(m_lpszCode)
	m_nCodeLen = 0;
	m_nLine = 0;
	m_szFileName = _T("");

	m_nEnum=0;
	m_nStruct=0;
	m_nUnion=0;
	m_nClass=0;
}

/*******************************************************************************************************
��������Error
��  ����������ʾ
��  ����
        CString szError��������Ϣ
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��2�� 10:34:36
*******************************************************************************************************/
int CSynatx::Error(CString szError)
{
	//����:��������ʾ
	return 0;
}

/*******************************************************************************************************
��������Space
��  ����ȥ�����ڵĶ���Ŀո�
��  ����
        LPTSTR* lppIn�������ַ���ָ��
����ֵ����ǰָ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��13�� 18:26:30
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
		} // ���� if(*m_lpCur == _T(CR) && *(m_lpCur + 1) == _T(LF))
		m_lpCur++;
	} // ���� while((*m_lpCur == _T(' ') || *m_lpCur == _T(TAB) || *m_lpCur == _T(CR) || *m_lpCur == _T(LF)) && (m_lpCur < m_lpszCode + m_nCodeLen))
	return m_lpCur;
}

/*******************************************************************************************************
��������Comment
��  ����ȥ�������е�ע��
��  ������
����ֵ������Ϊ CString ��
        ""Ϊ�﷨����û�н���ע�ͷ���
		"/"Ϊ����ע�͡�
		����Ϊע�ͣ�����ע�ͷ����ڡ�
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��17�� 18:27:17
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
    } // ���� if(*(m_lpCur + 1) == '*')
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
        } // ���� if(*m_lpCur == end[0] && *(m_lpCur + 1) == end[1])
        m_lpCur++;
		szOut += *m_lpCur;
    } // ���� while(m_lpCur < m_lpszCode + m_nCodeLen)
	TRACE(_T("%s(%d) : ����,ȱ��ע�ͽ�������%c%c\n"), __FILE__, __LINE__, end[0], end[1]);
	CString szError(_T("����,ȱ��ע�ͽ�������"));
	if(end[0] == CR)
	{
		szError += _T("CRLF"); 
	}
	else
	{
		szError += _T("*/");
	} // ���� if(end[0] == CR)
	Error(szError);
	szOut = _T("");
	return szOut;
}

/*******************************************************************************************************
��������QuotationC
��  �������������е��ַ�
��  ����
         LPTSTR* lppIn �������ַ���ָ��
         LPTSTR* lppOut������ַ���ָ��
		 BOOL bQutation���Ƿ������ź�����֮������ݣ�Ĭ��Ϊ TRUE��������FALSE��������
����ֵ������Ϊ CString ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-21 13:35:14
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
        } // ���� if(*m_lpCur == _T('\\') && (*(m_lpCur + 1) == _T('\'') || *(m_lpCur + 1) == _T('\"') || *(m_lpCur + 1) == _T('\\')))
        if(*m_lpCur == ch)
		{
			szOut += *m_lpCur;
			m_lpCur++;
            return szOut;
		} // ���� if(*m_lpCur == ch)
        m_lpCur++;
		szOut += *m_lpCur;
	} // ���� while(*m_lpCur != NULL)
	szOut = _T("");
	TRACE(_T("%s(%d) : �﷨����ȱ��������:%c\n"), __FILE__, __LINE__, ch);
	Error(_T("�﷨����ȱ�������š�"));
}

/*******************************************************************************************************
��������GetWord
��  ������������
��  ������
����ֵ������Ϊ CString ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��1�� 15:56:42
*******************************************************************************************************/
CString CSynatx::GetWord()
{
	//ȥ���ո��Ʊ����ע��
	while(m_lpCur < m_lpszCode + m_nCodeLen)
	{
		switch(*m_lpCur)
		{
		case _T(CR):
			if(*(m_lpCur + 1) == _T(LF))
			{
				m_nLine++;
				m_lpCur += 2;
			} // ���� if(*(m_lpCur + 1) == _T(LF))
		case _T(LF):
		case _T(' '):
		case _T(TAB):
			Space();
			continue;
		case _T('/'):			
			if(Comment() == _T(""))
			{
				TRACE(_T("%s(%d) : �õ����ʳ���\n"), __FILE__, __LINE__);
				return _T("");
			} // ���� if(Comment() == _T(""))
			continue;
		case _T('\"'):
		case _T('\''):
			//�޸�:ע���Ƿ񷵻�
			return Quotation();			
		default:
			break;
		} // ���� switch(*m_lpCur)
		break;
	} // ���� while(m_lpCur < m_lpszCode + m_nCodeLen)

	CString szWord("");
	while(m_lpCur < m_lpszCode + m_nCodeLen)
	{
		switch(LimitChar())
		{
		case 0:        //���ǵ��ʷֽ��
			szWord += *m_lpCur;
			m_lpCur++;
			continue;
		case _T(':'):
			if(*(m_lpCur + 1) == _T(':'))
			{
				szWord += _T("::");
				m_lpCur += 2;
				continue;
			} // ���� if(*(m_lpCur + 1) == _T(':'))
		case _T('-'):  //����:�Ǹ���ʱ
		case _T('.'):  //����:��С��ʱ
		case _T('^'):  //����:��ָ��ʱ
		default:
			break;
		} // ���� switch(LimitChar())
		break;
	} // ���� while(m_lpCur < m_lpszCode + m_nCodeLen)
	if(szWord == _T(""))
	{
		szWord = *m_lpCur;
		m_lpCur++;
	} // ���� if(szWord == _T(""))
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
			TRACE(_T("%s(%d) : �﷨���󡣲�����������䡣%s\n"), __FILE__, __LINE__, szIn);
			Error(_T("�﷨���󡣲�����������䡣") + szIn);
			m_lpCur++;
		} // ���� ()
		szIn = GetWord();
	} // ���� while(m_lpCur < m_lpszCode + m_nCodeLen && szIn != _T(""))

	return 0;
}

/*******************************************************************************************************
��������LimitChar
��  �����жϵ�ǰ�����ַ��Ƿ��ǵ��ʷֽ��
��  ����
        void����
����ֵ������Ϊ INT ���Ƿ��طֽ�����񷵻� 0
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��1�� 17:13:42
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
	} // ���� switch(*m_lpCur)
	return 0;
}

/*******************************************************************************************************
��������GetWordType
��  �����õ���������
��  ����
        void����
����ֵ������Ϊ INT ���������͡�
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��2�� 7:46:37
*******************************************************************************************************/
CSynatx::ENUM_TYPE CSynatx::GetWordType(CString szWord)
{
	if(_T(";") == szWord)
	{
		return SEMICOLON;
	} // ���� if(_T(";") == szWord)
	if(_T(",") == szWord)
	{
		return COMMA;
	} // ���� if(_T(",") == szWord)
	if(_T("(") == szWord)
	{
		return LEFTLITTLEBRACKET;
	} // ���� if(_T("(") == szWord)
	if(_T(")") == szWord)
	{
		return RIGHTLITTLEBRACKET;
	} // ���� if(_T(")") == szWord)
	if(_T("[") == szWord)
	{
		return LEFTMIDBRACKET;
	} // ���� if(_T("[") == szWord)
	if(_T("]") == szWord)
	{
		return RIGHTMIDBRACKET;
	} // ���� if(_T("]") == szWord)
	if(_T("{") == szWord)
	{
		return LEFTBIGBRACKET;
	} // ���� if(_T("{") == szWord)
	if(_T("}") == szWord)
	{
		return RIGHTBIGBRACKET;
	} // ���� if(_T("}") == szWord)
	
	if(_T("if") == szWord)
	{
		return IF;
	} // ���� if(_T("if") == szWord)
	if(_T("else") == szWord)
	{
		return ELSE;
	} // ���� if(_T("else") == szWord)
	if(_T("endif") == szWord)
	{
		return ENDIF;
	} // ���� if(_T("endif") == szWord)
	if(_T("for") == szWord)
	{
		return FOR;
	} // ���� if(_T("for") == szWord)
	if(_T("switch") == szWord)
	{
		return SWITCH;
	} // ���� if(_T("switch") == szWord)
	if(_T("case") == szWord)
	{
		return CASE;
	} // ���� if(_T("case") == szWord)
	if(_T("default") == szWord)
	{
		return DEFAULT;
	} // ���� if(_T("default") == szWord)
	if(_T("break") == szWord)
	{
		return BREAK;
	} // ���� if(_T("break") == szWord)
	if(_T("continue") == szWord)
	{
		return CONTINUE;
	} // ���� if(_T("continue") == szWord)
	if(_T("while") == szWord)
	{
		return WHILE;
	} // ���� if(_T("while") == szWord)
	if(_T("do") == szWord)
	{
		return DO;
	} // ���� if(_T("do") == szWord)
	if(_T("goto") == szWord)
	{
		return GOTO;
	} // ���� if(_T("goto") == szWord)
	if(_T("return") == szWord)
	{
		return RETURN;
	} // ���� if(_T("return") == szWord)
	if(_T("sizeof") == szWord)
	{
		return SIZEOF;
	} // ���� if(_T("sizeof") == szWord)
	if(_T("typedef") == szWord)
	{
		return TYPEDEF;
	} // ���� if(_T("typedef") == szWord)
	if(_T("class") == szWord)
	{
		return CLASS;
	} // ���� if(_T("class") == szWord)
	if(_T("struct") == szWord)
	{
		return STRUCT;
	} // ���� if(_T("struct") == szWord)
	if(_T("enum") == szWord)
	{
		return ENUM;
	} // ���� if(_T("enum") == szWord)
	if(_T("union") == szWord)
	{
		return UNION;
	} // ���� if(_T("union") == szWord)
	if(_T("+") == szWord)
	{
		return ADD;
	} // ���� if(_T("+") == szWord)
	if(_T("-") == szWord)
	{
		return SUBTRACTION;
	} // ���� if(_T("-") == szWord)
	if(_T("*") == szWord)
	{
		return MULTIPLY;
	} // ���� if(_T("*") == szWord)
	if(_T("/") == szWord)
	{
		return DIVISION;
	} // ���� if(_T("/") == szWord)
	if(_T(".") == szWord)
	{
		return DOT;
	} // ���� if(_T(".") == szWord)
	if(_T(">") == szWord)
	{
		return BIG;
	} // ���� if(_T(">") == szWord)
	if(_T("<") == szWord)
	{
		return LESS;
	} // ���� if(_T("<") == szWord)
	if(_T("=") == szWord)
	{
		return EQUAL;
	} // ���� if(_T("=") == szWord)

	//�ؼ�������
	if(_T("char") == szWord || _T("int") == szWord || _T("short") == szWord || _T("long") == szWord || _T("double") == szWord || _T("bool") == szWord || _T("float") == szWord)
	{
		return DATATYPEDEFINE;
	} // ���� if(_T("char") == szWord || _T("int") == szWord || _T("short") == szWord || _T("long") == szWord || _T("double") == szWord || _T("bool") == szWord || _T("float") == szWord)

	ENUM_TYPE reval = SearchList(m_lsDataType, DATATYPEDEFINE, szWord);

	if(reval != NO)
	{
		return reval;
	} // ���� if(reval != NO)

	reval = SearchList(m_lsClass, CLASSDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // ���� if(reval != NO)

	reval = SearchList(m_lsStruct, STRUCTDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // ���� if(reval != NO)

	reval = SearchList(m_lsUnion, UNIONDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // ���� if(reval != NO)

	reval = SearchList(m_lsEnum, ENUMDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // ���� if(reval != NO)

	reval = SearchList(m_lsVariable, VARIABLE, szWord);
	if(reval != NO)
	{
		return reval;
	} // ���� if(reval != NO)

	reval = SearchList(m_lsFunction, FUNCTIONDEFINE, szWord);
	if(reval != NO)
	{
		return reval;
	} // ���� if(reval != NO)

	return NO;
}

/*******************************************************************************************************
��������fTypedef
��  �����ؼ��� typedef ������
��  ����
        void����
����ֵ������Ϊ int ���ɹ����ط��㣬ʧ�ܷ��� 0 ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��2�� 11:27:20
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
		} // ���� if(fEnum())		
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
		TRACE(_T("%s(%d) : �﷨��������(typedef)�������%s\n"), __FILE__, __LINE__, szWord);
		Error(_T("�﷨��������(typedef)�������") + szWord);
		return 0;
	} // ���� switch(GetWordType(szIn))
	return 1;
}

/*******************************************************************************************************
��������fClass
��  �����ؼ��� class �Ĳ�����
��  ����
        void����
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��2�� 15:28:55
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
	} // ���� switch(GetWordType(szWord))
	return 0;
}

/*******************************************************************************************************
��������fEnum
��  �����ؼ��� enum �Ĳ�����
��  ����
        BOOL bVar��TRUE���������塣FALSE�������Ǳ������壬ֻ���� enum ��
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��12�� 9:52:10
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
				TRACE(_T("%s(%d) : �﷨�����������롰{����%s\n"), __FILE__, __LINE__, szIn);
				Error(_T(" �﷨�����������롰{����") + szIn);
				reval = 0;
			} // ���� if(GetWordType(szIn) == LEFTBIGBRACKET)
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
		Error(_T("�﷨����(enum)") + szWord);
		TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, _T("�﷨����(enum)") + szWord);
		reval = 0;
	} // ���� switch(GetWordType(szWord))

	//enum��������
	if(bVar)
	{
		reval = AddElement(m_lsVariable);
	} // ���� if(bVar)
	return reval;
}

/*******************************************************************************************************
��������fStruct
��  �����ؼ��� struct �Ĳ���
��  ����
        BOOL bVar��
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��12�� 15:52:35
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
				TRACE(_T("%s(%d) : �﷨�����������롰{����%s\n"), __FILE__, __LINE__, szIn);
				Error(_T(" �﷨�����������롰{����") + szIn);
				reval = 0;
			} // ���� if(GetWordType(szIn) == LEFTBIGBRACKET)
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
		Error(_T("�﷨����(struct)") + szWord);
		TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, _T("�﷨����(struct)") + szWord);
		reval = 0;
	} // ���� switch(GetWordType(szWord))

	//��������
	if(bVar)
	{
		reval = AddElement(m_lsVariable);
	} // ���� if(bVar)
	return reval;
}

/*******************************************************************************************************
��������fUnion
��  �����ؼ��� union �Ĳ�����
��  ����
        BOOL bVar��
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��12�� 15:53:09
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
				TRACE(_T("%s(%d) : �﷨�����������롰{����%s\n"), __FILE__, __LINE__, szIn);
				Error(_T(" �﷨�����������롰{����") + szIn);
				reval = 0;
			} // ���� if(GetWordType(szIn) == LEFTBIGBRACKET)
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
		Error(_T("�﷨����(union)") + szWord);
		TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, _T("�﷨����(union)") + szWord);
		reval = 0;
	} // ���� switch(GetWordType(szWord))

	//��������
	if(bVar)
	{
		reval = AddElement(m_lsVariable);
	} // ���� if(bVar)
	return reval;
}

/*******************************************************************************************************
��������fFunction
��  �������������������/������
��  ����
        void����
����ֵ������Ϊ int ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��8��12�� 15:59:12
*******************************************************************************************************/
int CSynatx::fFunction(void)
{
	LPCTSTR p = m_lpCur;
	CString szWord;
	szWord = GetWord();
	switch(GetWordType(szWord))
	{
	case NO:
		//��ǰ����
		CString szIn = GetWord();
		if(GetWordType(szIn) == LEFTLITTLEBRACKE)
		{
			//����:�������������

		}
		else
		{
			//��������
			m_lpCur = p;
			return AddElement(m_lsVariable);
		} // ���� if(GetWordType(szIn) == LEFTLITTLEBRACKE)
		break;
	case FUNCTIONDECLEARKEYWORD:
		break;
	default:
		TRACE(_T("%s(%d) : �﷨���󡣶������%s\n"), __FILE__, __LINE__, szWord);
		Error(_T("�﷨���󡣶������") + szWord);
		retrun 0;
	} // ���� switch(GetWordType(szWord))
	
	return 0;
}
