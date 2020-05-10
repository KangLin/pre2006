#include "StdAfx.h"
#include "..\..\TestTemplet\CheckPort\CombineCheckPort.h"
#include ".\SetMAC.h"
#include ".\6618test.h"
#include <conio.h>
#include "..\..\TestTemplet\NET\HTML\checkhtmlfile.h"
#include "..\..\TestTemplet\Rule\buildrule.h"

C6618Test::C6618Test(void)
{
}

C6618Test::~C6618Test(void)
{
}

int C6618Test::DoPrepare(void)
{
	m_log.Message(_T("��ѡ��\n... 1�����Ʒ���ԡ�\n... 2����Ʒ���ԡ�\n... 3������ģ���ļ���\n... ESC���˳�\n(1)"));

	char c;
#if _MSC_VER >= 1300
	c = _gettch();
#else
	c = _getch();
#endif
	if(0x1b == c || _T('n') == c || _T('N') == c)
	{
		return 1;
	} // ���� if(0x1b == c || _T('n') == c || _T('N') == c)

	if(_T('2') == c)
	{
		CCheckHTMLFile * phtml = new CCheckHTMLFile;
		if(!phtml)
		{
			TRACE(_T("���� CCheckHTMLFile ����ʧ�ܡ�"));
			return 2;
		} // ���� if(!phtml)
		if(AddItem(phtml))
		{
			return 2;
		} // ���� if(!AddItem(phtml))
	} // ���� if(_T('2') == c)

	if(_T('3') == c)
	{
		CBuildRule * pb = new CBuildRule;
		if(!pb)
		{
			TRACE(_T("���� CBuileRule ����ʧ�ܡ�"));
			return 2;
		} // ���� if(!pb)
		AddItem(pb);
	} // ���� if(_T('3') == c)

	if(_T('3') != c)
	{
		CCombineCheckPort * pCheckPort = new CCombineCheckPort;
		if(!pCheckPort)
		{
			TRACE(_T("�����˿ڼ�����ʧ�ܡ�"));
			return 1;
		} // ���� (!pCheckPort)
		AddItem(pCheckPort);
	} // ���� if(_T('3') != c)
	
	if(_T('2') != c && _T('3') != c)
	{
		CSetMAC * pMac = new CSetMAC;
		if(!pMac)
		{
			TRACE(_T("����дMAC��ַ����ʧ�ܡ�"));
			return 2;
		} // ���� if(!pMac)
		AddItem(pMac);
	} // ���� if(_T('2') != c && _T('3') != c)
	
	return 0;
}
