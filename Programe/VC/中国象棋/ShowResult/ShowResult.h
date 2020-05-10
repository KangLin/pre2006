#pragma once

#include "..\resource.h"

// CShowResult �Ի���

class CShowResult : public CDialog
{
	DECLARE_DYNAMIC(CShowResult)

public:
	CShowResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowResult();

// �Ի�������
	enum { IDD = IDD_SHOWRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()

private:
    HICON m_hIcon;

public:
    virtual BOOL OnInitDialog();
    // Ӯ���û���
    CString m_szWin;
    // �䷽�û���
    CString m_szLoss;
    // Ӯ������
    int m_iWin;
    // �䷽����
    int m_iLoss;
    // Ӯ��ӷ�ֵ
    int m_iAdd;
    // �������ֵ
    int m_iInc;
};
