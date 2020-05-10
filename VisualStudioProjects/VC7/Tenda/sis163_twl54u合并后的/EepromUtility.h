// EepromUtility.h: interface for the EepromUtility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EEPROMUTILITY_H__1BF32D07_8688_4F72_B09C_63644870B698__INCLUDED_)
#define AFX_EEPROMUTILITY_H__1BF32D07_8688_4F72_B09C_63644870B698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EepromUtility  
{
public:
	bool WriteDataFile(WORD* datas, char* pFileName);
	bool WriteProfile(char *pBuf, char* pSection, char* pKeyName, char* pFileName);
	EepromUtility();
	virtual ~EepromUtility();

	void SetFilePath(char * rom, char * mac);
	void ReadMacAddr(char * pMac);
    bool UpdateMacAddr(char * pMac);
	void UpdateMacAddr(WORD addr0, WORD addr1, WORD addr2);
	bool ReadListData(BYTE offset, WORD * pValue, int nSize);
	bool WriteListData(BYTE offset, WORD * pValue, int nSize);
	bool ReadMacFromFile(char * pBuf, char * pFileName);
	bool LoadDataFromFile(WORD * datas, char * pFileName);
    bool LoadDataFromFile();
    bool WriteListData();
    bool ReadMacFromFile(char * pBuf);
	void SetAdapter(PVOID pAdapter) { AFun_pAdapter = pAdapter; }

protected:
    DWORD HexStrToDWORD(char * str, int nSize);
    bool ReadProfile(char * pBuf, char * pSection,
                     char * pKeyName, char * pFileName);

protected:
    PVOID   AFun_pAdapter;
    WORD    data[0x40];
    char    macfile[255];
    char    romfile[255];

};

#endif // !defined(AFX_EEPROMUTILITY_H__1BF32D07_8688_4F72_B09C_63644870B698__INCLUDED_)
