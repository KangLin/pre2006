// 许可协议\License.cpp : 实现文件
//

#include "..\Syntax.h"
#include "License.h"

// CLicense 对话框

IMPLEMENT_DYNAMIC(CLicense, CDialog)
CLicense::CLicense(CWnd* pParent /*=NULL*/)
	: CDialog(CLicense::IDD, pParent)
{
}

CLicense::~CLicense()
{
}

void CLicense::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLicense, CDialog)
END_MESSAGE_MAP()


// CLicense 消息处理程序
