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
	m_log.Message(_T("请选择：\n... 1：半成品测试。\n... 2：成品测试。\n... 3：检查端口、升级内核并写入MAC地址。\n... 4：内核升级。\n... 5、建立模板文件。\n... ESC：退出\n(1)"));

	char c;
#if _MSC_VER >= 1300
	c = _gettch();
#else
	c = _getch();
#endif
	if(0x1b == c)
	{
		return 1;
	} // 结束 if(0x1b == c)

	CString sztmp(c);
	m_log.Message(sztmp);

	if(_T('2') == c)
	{
		CCheckHTMLFile * pf = new CCheckHTMLFile;
		if(!pf)
		{
			TRACE(_T("实例化 CCheckHTMLFile 失败。"));
			return 2;
		} // 结束 if(!pf)
		if(AddItem(pf))
		{
			return 2;
		} // 结束 if(AddItem(pf))
	} // 结束 if(_T('2') == c)

	if(_T('4') != c && _T('5') != c)
	{
		//CCheckPort * pCP = new CCheckPort;
		CCombineCheckPort * pCP = new CCombineCheckPort;
		if(!pCP)
		{
			TRACE(_T("实例化写端口检查失败。"));
			return 2;
		} // 结束 (!pCP)
		AddItem(pCP);
	} // 结束 if(_T('4') != c && _T('5') != c)

	if(_T('3') == c || _T('4') == c)
	{
		C6608TFTP * pTFTP = new C6608TFTP;
		if(!pTFTP)
		{
			TRACE(_T("实例化写TFTP失败。"));
			return 3;
		} // 结束 if(!pTFTP)
		AddItem(pTFTP);
	} // 结束 if(_T('3') == c || _T('4') == c)

	if(_T('2') != c && _T('4') != c && _T('5') != c)
	{
		CSet6608MAC * pSetMAC = new CSet6608MAC;
		if(!pSetMAC)
		{
			TRACE(_T("实例化写MAC失败。"));
			return 4;
		} // 结束 if(!pSetMAC)
		AddItem(pSetMAC);
	} // 结束 if(_T('2') != c && _T('4') != c && _T('5') != c)

	if(_T('5') == c)
	{
		CBuildRule * pb = new CBuildRule;
		if(!pb)
		{
			TRACE(_T("实例化 CBuildRule 失败。"));
			return 4;
		} // 结束 if(!pb)
		AddItem(pb);
	} // 结束 if(_T('5') == c)
	return 0;
}
