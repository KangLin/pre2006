// ���Э��\License.cpp : ʵ���ļ�
//

#include "..\Syntax.h"
#include "License.h"

// CLicense �Ի���

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


// CLicense ��Ϣ�������
