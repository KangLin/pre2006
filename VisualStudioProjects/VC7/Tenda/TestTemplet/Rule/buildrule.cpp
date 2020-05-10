#include "StdAfx.h"
#include ".\buildrule.h"
#include "..\CommonFunction.h"

extern CString g_INIFile;

CBuildRule::CBuildRule(void)
{
	SetName(_T("����ģ���ļ�"));

	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile;
	TCHAR szRe [1024];

	if(::GetPrivateProfileString(_T("RULEEXPRESS"), _T("INFILE"), _T(""), szRe, 1024, szPath) == 0)
	{
		TRACE(_T("��ȡ�����ļ�ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("RULEEXPRESS"), _T("INFILE"), _T(""), szRe, 1024, szPath) == 0)
	m_szInFile = GetCurrentDir() + _T("\\");
	m_szInFile += szRe;

	if(::GetPrivateProfileString(_T("RULEEXPRESS"), _T("OUTFILE"), _T(""), szRe, 1024, szPath) == 0)
	{
		TRACE(_T("��ȡ����ļ�ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("RULEEXPRESS"), _T("OUTFILE"), _T(""), szRe, 1024, szPath) == 0)
	m_szOutFile = GetCurrentDir() + _T("\\");
	m_szOutFile += szRe;
}

CBuildRule::~CBuildRule(void)
{
}

int CBuildRule::DoTest()
{
	TRY
	{
		CFile inf(m_szInFile, CFile::modeRead);
		CFile outf(m_szOutFile, CFile::modeWrite | CFile::modeCreate);
		TCHAR inch, outch[2];
		while(inf.Read(&inch, 1))
		{
			switch(inch)
			{
			case _T('.'):
			case _T('['):
			case _T(']'):
			case _T('^'):
			case _T('?'):
			case _T('+'):
			case _T('*'):
			case _T('('):
			case _T(')'):
			case _T('{'):
			case _T('}'):
			case _T('\\'):
			case _T('$'):
			case _T('|'):
			case _T('!'):
				outch[0] = _T('\\');
				outch[1]=inch;
				outf.Write(outch, 2);
				break;
			default:
				outf.Write(&inch, 1);
			} // ���� switch(ch)
		} // ���� while(inf.Read(&inch, 1))
		inf.Close();
		outf.Close();
		return 0;
	}
	CATCH(CFileException, e)
	{
		m_plog->Error(_T("�ļ�����"));
		return 1;
	}
	END_CATCH

	return 0;
}