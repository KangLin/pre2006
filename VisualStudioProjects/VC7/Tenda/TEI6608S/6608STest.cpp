#include "stdafx.h"
#include ".\6608stest.h"
#include "..\TestTemplet\CheckPort\CheckPort.h"
#include "..\TestTemplet\CheckPort\CombineCheckPort.h"
#include "6608TFTP.h"
#include "..\TestTemplet\WriteMAC\SetMAC.h"
#include "Set6608MAC.h"
#include <conio.h> 
#include "..\TestTemplet\NET\HTML\checkhtmlfile.h"
#include "..\TestTemplet\Rule\buildrule.h"

C6608STest::C6608STest(void)
{
}

C6608STest::~C6608STest(void)
{
}

int C6608STest::DoPrepare(void)
{
	m_log.Message(_T("��ѡ��\n... 1�����Ʒ���ԡ�\n... 2����Ʒ���ԡ�\n... 3�����˿ڡ������ں˲�д��MAC��ַ��\n... 4���ں�������\n... 5������ģ���ļ���\n... ESC���˳�\n(1)"));

	char c;
#if _MSC_VER >= 1300
	c = _gettch();
#else
	c = _getch();
#endif
	if(0x1b == c)
	{
		return 1;
	} // ���� if(0x1b == c)

	CString sztmp(c);
	m_log.Message(sztmp);

	if(_T('2') == c)
	{
		CCheckHTMLFile * pf = new CCheckHTMLFile;
		if(!pf)
		{
			TRACE(_T("ʵ���� CCheckHTMLFile ʧ�ܡ�"));
			return 2;
		} // ���� if(!pf)
		if(AddItem(pf))
		{
			return 2;
		} // ���� if(AddItem(pf))
	} // ���� if(_T('2') == c)

	if(_T('4') != c && _T('5') != c)
	{
		//CCheckPort * pCP = new CCheckPort;
		CCombineCheckPort * pCP = new CCombineCheckPort;
		if(!pCP)
		{
			TRACE(_T("ʵ����д�˿ڼ��ʧ�ܡ�"));
			return 2;
		} // ���� (!pCP)
		AddItem(pCP);
	} // ���� if(_T('4') != c && _T('5') != c)

	if(_T('3') == c || _T('4') == c)
	{
		C6608TFTP * pTFTP = new C6608TFTP;
		if(!pTFTP)
		{
			TRACE(_T("ʵ����дTFTPʧ�ܡ�"));
			return 3;
		} // ���� if(!pTFTP)
		AddItem(pTFTP);
	} // ���� if(_T('3') == c || _T('4') == c)

	if(_T('2') != c && _T('4') != c && _T('5') != c)
	{
		CSet6608MAC * pSetMAC = new CSet6608MAC;
		if(!pSetMAC)
		{
			TRACE(_T("ʵ����дMACʧ�ܡ�"));
			return 4;
		} // ���� if(!pSetMAC)
		AddItem(pSetMAC);
	} // ���� if(_T('2') != c && _T('4') != c && _T('5') != c)

	if(_T('5') == c)
	{
		CBuildRule * pb = new CBuildRule;
		if(!pb)
		{
			TRACE(_T("ʵ���� CBuildRule ʧ�ܡ�"));
			return 4;
		} // ���� if(!pb)
		AddItem(pb);
	} // ���� if(_T('5') == c)
	return 0;
}
