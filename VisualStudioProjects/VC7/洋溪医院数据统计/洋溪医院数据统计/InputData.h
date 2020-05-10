#pragma once
#include "afxwin.h"


// CInputData �Ի���

class CInputData : public CDialog
{
	DECLARE_DYNAMIC(CInputData)

public:
	CInputData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputData();

// �Ի�������
	enum { IDD = IDD_INPUTDATA };

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
    HICON m_hIcon;
    CStatic m_Group;

	DECLARE_MESSAGE_MAP()
    
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    CComboBox m_cbDoctor;
};
