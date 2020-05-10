#pragma once
#include "..\resource.h"       // main symbols
#include "atlcomtime.h"

// CSetDlg �Ի���

class CSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDlg();

// �Ի�������
	enum { IDD = IDD_SETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()

private:
    HICON m_hIcon;
public:
    virtual BOOL OnInitDialog();
    // ÿ�����ʱ��
    LONG m_dwStep;
    // Ӯ��ӷ�ֵ
    UINT m_uAddPoint;
    // �������ֵ
    UINT m_uIncPoint;
    //���Ի������;
    enum
    {
        Setting,
        ReceiveSet
    };
    int m_iFunction;
};
