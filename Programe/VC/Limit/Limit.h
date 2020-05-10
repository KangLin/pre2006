/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Limit.h
��  ����
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��12��
ʱ  �䣺19:06:21
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#include < atlbase.h > 

#pragma once

class CLimit
{
public:
    CLimit(void);
    CLimit(LPCTSTR lpszKey);
	~CLimit(void);

    // �õ�Ӳ�����
	DWORD GetDiskNo(void);
	// �õ�ע����
	DWORD GetRegistNo(DWORD dwMachine = 0);
	// �õ�ע����е�ע�����ֵ 
	DWORD GetRegistNoInRegedit();
	// �û�����
	DWORD GetMachineNo();
    // ��ע��ֵд��ע���
	BOOL WriteRegist(DWORD dwRegistNo = 0);
	// �õ�ָ����ע����е�ֵ
	BOOL GetRegist(LPCTSTR lpszKey = NULL);
	// д������
	BOOL WriteDate();
	// �õ�ʣ�µ�ʹ������
	DWORD GetDays();
	// ��֤ע����
    BOOL ValidateRegistNo(DWORD dwRegistNo);
    
private:
    DWORD m_dwDiskSerialNumber;  //Ӳ�����к�
    DWORD m_dwMachineNo;         //������
    DWORD m_dwRegist;            //ע����
	DWORD m_dwRegVal;            //ע����еļ��ܵ�ע����ֵ
    CString m_szSoftName;        //�����

    DWORD m_dwXOR;
    DWORD m_dwXOR1;
    DWORD m_dwXOR2;
    DWORD m_dwXOR3;
    DWORD m_dwDay;
    DWORD m_dwMonth;
    DWORD m_dwYear;
    CRegKey m_reg;
    CString m_szRegKey;
};

extern "C" BOOL Regist(BOOL bShow = FALSE, LPCTSTR lpszKey = NULL, BOOL bTrueShow = FALSE);
