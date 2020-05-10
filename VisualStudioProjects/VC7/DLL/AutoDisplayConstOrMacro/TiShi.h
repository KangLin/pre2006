/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����TiShi.h
��  ������Ϣ����û���
��  ����2005.6.0.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005-6-16
ʱ  �䣺15:13:18
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#pragma once

#define MAX_BUFFER 1024

// CTiShi

class CTiShi 
{
public:
	CTiShi();
	virtual ~CTiShi();
    CTiShi(HINSTANCE hInstance);

private:
    int m_iScreenWidth;     //��Ļ���
    int m_iScreenHeight;    //��Ļ�߶�
    int m_iTop;             //��ʾ����ϱ�λ��
    int m_iLeft;            //��ʾ������λ��
    int m_iListWidth;       //������
    int m_iListHeight;      //����߶�
    int m_iEditWidth;       //��Ȩ��Ϣ��Ŀ��
    int m_iEditHeight;      //��Ȩ��Ϣ��ĸ߶�

    BOOL m_bShow;           //��ʾ��ʾ��

    WNDPROC lpWndProc;      //���ڴ�����

    // ��ʼ��
    BOOL Inital(void);
    // �ƶ���ʾ��
    BOOL MoveTiShi(void);
    // ��ʾTip
    void ShowTip();
    
public:
    //���̿��Ƴ���
    enum POSTION_ENUM
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        PAGEUP,
        PAGEDOWN,
        HOME,
        END
    };
    BOOL SetListPos(POSTION_ENUM pos);
    HINSTANCE m_hInstance;  //ʵ�����
    HWND m_hParent;         //�����ھ��
    HWND m_hList;           //������
    HWND m_hEditTip;        //��ʾTip���
    HWND m_hEdit;           //��Ȩ��Ϣ���
    HFONT m_hFont;          //������

    CString m_szEditText;   //��Ȩ��Ϣ
    CString m_szListText;   //
    CString m_szFont;       //������
    
    // ����ʵ�����
    void SetInstance(HINSTANCE hInstance);
    // ����������
    BOOL AddListItem(LPCTSTR lpszItem, BOOL bDirectness = FALSE);
    // ɾ��������
    BOOL DeleteListItem(LPCTSTR lpszItem);
    // ����ָ�����ַ���������ȫƥ�䣩
    BOOL FindString(LPCTSTR lpszItem);
    // �����ַ����� IDE
	virtual BOOL CopyString(TCHAR ch);
    // ���ð�Ȩ��Ϣ
    BOOL SetCopyRightInfo(LPCTSTR lpszCopyRight);
    // �������������
    BOOL SetListText(LPCTSTR lpszText);
    // ��ʾ/������ʾ��
	BOOL ShowTiShi(bool bShow, HWND hParent = NULL);
	// �õ���ʾ���Ƿ���ʾ
	BOOL Showed();

	static LRESULT CALLBACK WindowProc(HWND hWnd,
                                       UINT uMsg,
                                       WPARAM wParam,
                                       LPARAM lParam
                                       );
};


