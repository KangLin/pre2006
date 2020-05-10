// FindEx.h: interface for the CFindEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDEX_H__F0A6FFE3_9959_43DC_B3A9_E8E0C78022F7__INCLUDED_)
#define AFX_FINDEX_H__F0A6FFE3_9959_43DC_B3A9_E8E0C78022F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFindEx : public CFile 
{
public:
	CString GetFileName(LPCSTR szFileName);
	virtual BOOL OnDirectory(LPCSTR szDir);
	virtual BOOL OnFile(LPCSTR szFile);
	virtual BOOL SearchFileAndDirectory(LPCSTR szFile, BOOL * bpStop);
	BOOL SearchDirectory(LPCSTR szDir, BOOL bStop = FALSE);
	BOOL FindWordInFile(LPCSTR FileName, LPCSTR Word);
	CFindEx();
	virtual ~CFindEx();
};

#endif // !defined(AFX_FINDEX_H__F0A6FFE3_9959_43DC_B3A9_E8E0C78022F7__INCLUDED_)
