#pragma once



// CLicense �Ի���

class CLicense : public CDialog
{
	DECLARE_DYNAMIC(CLicense)

public:
	CLicense(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLicense();

// �Ի�������
	enum { IDD = IDD_DLG_LICENSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
