/*******************************************************************************************************
��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
�ļ�����TiShi.h
��  ����
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2007��5��5��
ʱ  �䣺14:13:04
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/

#ifndef __TISHI_H__
#define __TISHI_H__

#pragma once

typedef int(*EnterFun)(LPCTSTR lpcszText);

/*******************************************************************************************************
��������KeyPressFun
��  �������̴���ص���������Ҫ�����Զ��崦���б�ؼ���ѡ�к�ȷ����Ӧ��Ϣ��
��  ����
        UINT nChar  �����뷨�ļ�
		UINT nRepCnt���ظ�����
		UINT nFlags ����־(Ctrl��Alt��Shift)
����ֵ������Ϊ int������0������OnKeyUp�в����κζ�����������ط��㣬��������ʾ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��5�� 13:42:05
*******************************************************************************************************/
typedef int(*KeyPressFun)(UINT nChar, UINT nRepCnt, UINT nFlags);
/*******************************************************************************************************
��������ShowTipFun
��  �����ص��������˻ص������� ShowTip ���á�
��  ����
        UINT nIndex       ��ѡ����Ŀ�������š�
		LPCTSTR lpcszText ��ѡ����Ŀ�����ݡ�
		LPTSTR* lpszInText���˻ص�������ɺ󷵻ظ�������ַ�����Ҳ����Ҫ�ڰ�����ʾ������ʾ���ı�����
		                    �ص�����ֻҪ�����ڴ棬ShowTip �Ḻ���ͷ��ڴ�ġ�
����ֵ������Ϊ int ���ɹ����� 0�����󷵻ط��㡣
*******************************************************************************************************/
typedef int(*ShowTipFun)(UINT nIndex, LPCTSTR lpcszText, LPTSTR* lpszInText);

// CTiShi

class CTiShi : public CListBox
{
	DECLARE_DYNAMIC(CTiShi)

public:
	CTiShi();
	virtual ~CTiShi();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CEdit m_Edit;               //��Ȩ��Ϣ��ʾ��
	CEdit m_edTip;              //��ѡ�����ע�Ϳ�

	CFont m_Font;               //����

	int m_iScreenWidth;         //��Ļ���
    int m_iScreenHeight;        //��Ļ�߶�
    int m_iTop;                 //��ʾ����ϱ�λ��
    int m_iLeft;                //��ʾ������λ��
	int m_iListWidth;           //��Ŀ��ʾ��Ŀ��
	int m_iListHeight;          //��Ŀ��ʾ��ĸ߶�
    int m_iEditWidth;           //��Ȩ��Ϣ��Ŀ��
    int m_iEditHeight;          //��Ȩ��Ϣ��ĸ߶�

	BOOL m_bVerTiShi;           //�Ƿ���ʾ��Ȩ��Ϣ��ʾ��
	
	BOOL m_bKeyUp;              //���Ƿ�ſ�

	EnterFun m_EnterFun;        //����Ŀ��ʾ��ѡ��ȷ����ѡ��ʱ�Ļص�����
	KeyPressFun m_KeyPressFun;  //���������Ϣ�ص�����
	ShowTipFun m_ShowTipFun;    //��ʾ��Ŀ��ʾ�������ʾ��ǰ�Ļص�����

protected:
	CString m_szInput;          //�����ַ���
	HWND m_hParent;             //�����ڵľ��
	BOOL m_bShow;               //��ʾ���Ƿ���ʾ

public:
	// ��������
	int SetFont(LPCTSTR lpszFacename = _T("����"),
		        int nHeight = 12,
				int nWidth = 0,
				int nEscapement = 0,
				int nOrientation = 0,
				int nWeight = 0,
				BYTE bItalic = FALSE,
				BYTE bUnderline = FALSE,
				BYTE cStrikeOut = FALSE,
				BYTE nCharSet = DEFAULT_CHARSET,
				BYTE nOutPrecision = DEFAULT_QUALITY,
				BYTE nClipPrecision = DEFAULT_QUALITY,
				BYTE nQuality = DEFAULT_QUALITY,
				BYTE nPitchAndFamily = FIXED_PITCH + FF_SWISS
				);
	int SetFont(CFont * pFont);
	int SetSize(int nWidth, int nHeight);

	// �ƶ���ʾ��
	BOOL Move(LPCTSTR lpszText);
	BOOL Move(TCHAR ch);
	BOOL Move(UINT nCh);
	BOOL Move(void);
	// ��ʾ��ʾ��
	BOOL Show(HWND hParent, BOOL bShow = TRUE, LPCTSTR lpcszInput = NULL);
	BOOL Show(BOOL bShow = TRUE);
	BOOL IsShow();
	// ��ʾѡ�����ע�Ϳ� Tip
	int ShowTip(LPCTSTR lpszText);

	// ���ð�Ȩ��Ϣ,����Ϣ��ʾ�ڰ�Ȩ��Ϣ��ʾ����
	int SetCopyRight(LPCTSTR lpszCopyRight);
	// �Ƿ���ʾ��Ȩ��Ϣ��ʾ��
	int ShowCopyRight(BOOL bShow = FALSE);

	BOOL SetKeyUp(BOOL bKey);

	// �õ���Ŀ��ʾ����ѡ������ı�
	virtual CString GetString(void);

	BOOL RegisterEnterFun(EnterFun fun);
	BOOL RegisterKeyPress(KeyPressFun fun);
	BOOL RegisterShowTip(ShowTipFun fun);
	
	virtual BOOL CreateEx(HWND hParent = NULL);

	//�¼�
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	// �������¼�
	virtual void OnLeftButtonEvents(LPCTSTR lpszText);	
	// Enter ���¼�����Ҫ�����Զ��崦���б�ؼ���ѡ�к�ȷ����Ӧ��Ϣ��
	virtual int OnEnter(LPCTSTR lpszText);
	// ��ʾTip�¼�
	virtual int OnShowTip(UINT nIndex, LPCTSTR lpcszText, /*[out]*/LPTSTR * lpszInText);
	
	// �����ַ���
	virtual int FindText();
	virtual int FindText(LPCTSTR lpcszText);

public:
	virtual int Load();
	// ���ļ��м�������
	virtual int LoadString(LPCTSTR lpszFileName);
	
	//------------------------------------------------------------------------
	//��������� === ToolTip === ���ܵ�����
	//
private:
	CToolTipCtrl m_ToolTip;
	void InitToolTip();
public:
	BOOL SetToolTipText(int nText, BOOL bActivate = TRUE);
	BOOL SetToolTipText(LPCTSTR lpszText, BOOL bActivate = TRUE);
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//
	//��������� === ToolTip === ���ܵ�����
	//------------------------------------------------------------------------

protected:
	// �õ�ָ������Ĵ�С
	int GetFontSize(HWND hWnd, LPCTSTR lpszText, LPSIZE lpSize);
};

#endif // ���� #ifdef __TISHI_H__