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
	m_log.Message(_T("请选择：\n... 1：半成品测试。\n... 2：成品测试。\n... 3：建立模板文件。\n... ESC：退出\n(1)"));

	char c;
#if _MSC_VER >= 1300
	c = _gettch();
#else
	c = _getch();
#endif
	if(0x1b == c || _T('n') == c || _T('N') == c)
	{
		return 1;
	} // 结束 if(0x1b == c || _T('n') == c || _T('N') == c)

	if(_T('2') == c)
	{
		CCheckHTMLFile * phtml = new CCheckHTMLFile;
		if(!phtml)
		{
			TRACE(_T("建立 CCheckHTMLFile 对象失败。"));
			return 2;
		} // 结束 if(!phtml)
		if(AddItem(phtml))
		{
			return 2;
		} // 结束 if(!AddItem(phtml))
	} // 结束 if(_T('2') == c)

	if(_T('3') == c)
	{
		CBuildRule * pb = new CBuildRule;
		if(!pb)
		{
			TRACE(_T("建立 CBuileRule 对象失败。"));
			return 2;
		} // 结束 if(!pb)
		AddItem(pb);
	} // 结束 if(_T('3') == c)

	if(_T('3') != c)
	{
		CCombineCheckPort * pCheckPort = new CCombineCheckPort;
		if(!pCheckPort)
		{
			TRACE(_T("建立端口检查对象失败。"));
			return 1;
		} // 结束 (!pCheckPort)
		AddItem(pCheckPort);
	} // 结束 if(_T('3') != c)
	
	if(_T('2') != c && _T('3') != c)
	{
		CSetMAC * pMac = new CSetMAC;
		if(!pMac)
		{
			TRACE(_T("建立写MAC地址对象失败。"));
			return 2;
		} // 结束 if(!pMac)
		AddItem(pMac);
	} // 结束 if(_T('2') != c && _T('3') != c)
	
	return 0;
}
