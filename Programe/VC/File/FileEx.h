/*******************************************************************************************************
�ļ�����FileEx.h
��  ����1������һ���ļ�������һ��ʵ����
           CFileEx fe(_T("C:\\windows\\system\\text.txt"));
           ��
           CFileEx fe; //���Զ��õ���ǰִ���ļ����ļ�����
		2���õ���ǰִ���ļ����ļ�����(���Բ�ִ��1)
		   ע�⣺��������������ļ����ͳ�Ϊ��ǰִ�е��ļ�������
		         �Ժ������õĺ������Ƕ������ִ���ļ����������ġ�
		   fe.GetModuleFileName(...);
		3���õ��ļ����⣺fe.GetFileTitle(...);
		4���õ��ļ�·����fe.GetFilePath(...);
        5���õ��ļ�����  fe.GetFileName(...);
        6���õ��ļ���չ����fe.GetFileExt(...);
        7���õ����·����fe.GetRelativePath(...);
		
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:01:37
*******************************************************************************************************/

#if !defined(AFX_FILEEX_H__624F4E7E_7EC6_4BE0_8569_FD9705EEF834__INCLUDED_)
#define AFX_FILEEX_H__624F4E7E_7EC6_4BE0_8569_FD9705EEF834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileEx : public CFile  
{
public:
	CFileEx(LPCTSTR pszFileName);
    CFileEx();
	virtual ~CFileEx();

	INT SetFile(LPCTSTR pszFileName);
    INT GetFileTitle(LPTSTR szFileTitle, INT iFileLen = MAX_PATH);
    INT GetFileTitle(CString & szFileTitle);
    
    INT GetFileName(LPTSTR szFileName, INT iFileLen = MAX_PATH);
    INT GetFileName(CString& szFileName);
   
    INT GetFileExt(LPTSTR szFileExt, INT iFileLen = MAX_PATH);
    INT GetFileExt(CString& szFileExt);
    
	INT GetFilePath(LPTSTR szFilePath, INT iLength = MAX_PATH);
    INT GetFilePath(CString & szFilePath);

    CString GetFileTitle();
    CString GetFileName();
    CString GetFileExt();
    CString GetFilePath();

    INT GetModuleFileName(LPTSTR szFileName, INT iFileLen = MAX_PATH);
    INT GetModuleFileName();
    static BOOL GetRelativePath(LPTSTR lpszRelativePath, LPCTSTR lpcszFrom, LPCTSTR lpcszTo, DWORD dwAttrFrom = FILE_ATTRIBUTE_DIRECTORY, DWORD dwAttrTo = FILE_ATTRIBUTE_NORMAL);
	
private:
	//�ļ�����ע�⣺������GetModuleFileName��
	//�ʹ洢�����ִ���ļ�������
	CString m_szFileName;
};

#endif // !defined(AFX_FILEEX_H__624F4E7E_7EC6_4BE0_8569_FD9705EEF834__INCLUDED_)
