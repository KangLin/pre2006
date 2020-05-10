// EepromUtility.cpp: implementation of the EepromUtility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "EepromUtility.h"
#include "AdapterFun.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int EEPROM_SZ = 0x80;
#define ETHERID0 0x10
#define ETHERID1 0x12
#define ETHERID2 0x14

char EEItem[128][15] = {
		"(01-00h)","(03-02h)","(05-04h)","(07-06h)",
		"(09-08h)","(0B-0Ah)","(0D-0Ch)","(0F-0Eh)",
		"(11-10h)","(13-12h)","(15-14h)","(17-16h)",
		"(19-18h)","(1B-1Ah)","(1D-1Ch)","(1F-1Eh)",
		"(21-20h)","(23-22h)","(25-24h)","(27-26h)",
		"(29-28h)","(2B-2Ah)","(2D-2Ch)","(2F-2Eh)",
		"(31-30h)","(33-32h)","(35-34h)","(37-36h)",
		"(39-38h)","(3B-3Ah)","(3D-3Ch)","(3F-3Eh)",
		"(41-40h)","(43-42h)","(45-44h)","(47-46h)",
		"(49-48h)","(4B-4Ah)","(4D-4Ch)","(4F-4Eh)",
		"(51-50h)","(53-52h)","(55-54h)","(57-56h)",
		"(59-58h)","(5B-5Ah)","(5D-5Ch)","(5F-5Eh)",
		"(61-60h)","(63-62h)","(65-64h)","(67-66h)",
		"(69-68h)","(6B-6Ah)","(6D-6Ch)","(6F-6Eh)",
		"(71-70h)","(73-72h)","(75-74h)","(77-76h)",
		"(79-78h)","(7B-7Ah)","(7D-7Ch)","(7F-7Eh)",
		"(80-81h) CIS30","(82-83h) CIS32","(84-85h) CIS34","(86-87h) CIS36",
		"(88-89h) CIS38","(8A-8Bh) CIS3A","(8C-8Dh) CIS3C","(8E-8Fh) CIS3E",
		"(90-91h) CIS40","(92-93h) CIS42","(94-95h) CIS44","(96-97h) CIS46",
		"(98-99h) CIS48","(9A-9Bh) CIS4A","(9C-9Dh) CIS4C","(9E-9Fh) CIS4E",
		"(A0-A1h) CIS50","(A2-A3h) CIS52","(A4-A5h) CIS54","(A6-A7h) CIS56",
		"(A8-A9h) CIS58","(AA-ABh) CIS5A","(AC-ADh) CIS5C","(AE-AFh) CIS5E",
		"(B0-B1h) CIS60","(B2-B3h) CIS62","(B4-B5h) CIS64","(B6-B7h) CIS66",
		"(B8-B9h) CIS68","(BA-BBh) CIS6A","(BC-BDh) CIS6C","(BE-BFh) CIS6E",
		"(C0-C1h) CIS70","(C2-C3h) CIS72","(C4-C5h) CIS74","(C6-C7h) CIS76",
		"(C8-C9h) CIS78","(CA-CBh) CIS7A","(CC-CDh) CIS7C","(CE-CFh) CIS7E",
		"(D0-D1h) CIS80","(D2-D3h) CIS82","(D4-D5h) CIS84","(D6-D7h) CIS86",
		"(D8-D9h) CIS88","(DA-DBh) CIS8A","(DC-DDh) CIS8C","(DE-DFh) CIS8E",
		"(E0-E1h) CIS90","(E2-E3h) CIS92","(E4-E5h) CIS94","(E6-E7h) CIS96",
		"(E8-E9h) CIS98","(EA-EBh) CIS9A","(EC-EDh) CIS9C","(EE-EFh) CIS9E",
		"(F0-F1h) CISA0","(F2-F3h) CISA2","(F4-F5h) CISA4","(F6-F7h) CISA6",
		"(F8-F9h) CISA8","(FA-FBh) CISAA","(FC-FDh) CISAC","(FE-FFh) CISAE"
		};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EepromUtility::EepromUtility()
{
    
}

EepromUtility::~EepromUtility()
{

}

bool EepromUtility::UpdateMacAddr(char * pMac)
{
    if (pMac == NULL || strlen(pMac) != 12)
        return false;

	char pM[24];
	ReadMacAddr(pM);
	_tprintf("写入前MAC地址:%s\n", pM);

	WORD addr0 = (WORD)HexStrToDWORD(pMac, 4);
    WORD addr1 = (WORD)HexStrToDWORD(pMac+4, 4);
	WORD addr2 = (WORD)HexStrToDWORD(pMac+8, 4);
	UpdateMacAddr(addr0, addr1, addr2);
    Sleep(500);
	ReadMacAddr(pM);	
	_tprintf("写入后芯片中的MAC地址:%s\n", pM);
	for (int i=0; i< 12;i++)
	{
		if(*(pM+i)!=*(pMac+i))
		{
			return false;
		}
	}
    return true;
}

DWORD EepromUtility::HexStrToDWORD(char * str, int nSize)
{
    DWORD value=0;

    for(int i=0; i<nSize; ++i)
    {
		if(str[i] >= '0' && str[i] <= '9')
        {
    	    value <<= 4;
    	    value += (str[i] - '0');
        }
        else
        {
    	    value <<= 4;
            if (str[i]>='a' && str[i] <='f')
    	        value += (str[i]-'a' + 10);
            else
                value += (str[i]-'A' + 10);
        }
    }

    return value;
}

bool EepromUtility::WriteListData()
{
    return WriteListData(0, data, EEPROM_SZ/2);
}

bool EepromUtility::WriteListData(BYTE offset, WORD * pValue, int nSize)
{
    if (pValue == NULL || ((int)offset+nSize) > EEPROM_SZ/2)
        return false;
    
    for (int i=0; i<nSize; i++)
    {
	    AFun_WriteEEPROM(offset+i, pValue[i], AFun_pAdapter);
    }
    return true;
}

bool EepromUtility::ReadListData(BYTE offset, WORD *pValue, int nSize)
{
    if (pValue == NULL || ((int)offset+nSize) > EEPROM_SZ/2)
        return false;

	for(int i=0; i<nSize; i++)
    {
		pValue[i] = AFun_ReadEEPROM(offset+i, AFun_pAdapter);
	}
    return true;
}

void EepromUtility::UpdateMacAddr(WORD addr0, WORD addr1, WORD addr2)
{
    AFun_WriteEEPROM(ETHERID0/2,
                    ((addr0 & 0xff)<<8)|(addr0 >> 8),
                    AFun_pAdapter);

	AFun_WriteEEPROM(ETHERID1/2,
                    ((addr1 & 0xff)<<8)|(addr1 >> 8),
                    AFun_pAdapter);

    AFun_WriteEEPROM(ETHERID2/2,
                    ((addr2 & 0xff)<<8)|(addr2 >> 8),
                    AFun_pAdapter);
}

void EepromUtility::ReadMacAddr(char *pMac)
{
    if (pMac == NULL)
        return;
    WORD addr[3];
    ReadListData(ETHERID0/2, addr, 3);
    sprintf(pMac, "%02X%02X%02X%02X%02X%02X", 
			addr[0] & 0xFF, addr[0] >>8,
			addr[1] & 0xFF,	addr[1] >>8,
			addr[2] & 0xFF, addr[2] >>8);
}

bool EepromUtility::ReadProfile(char *pBuf, char *pSection,
                                char *pKeyName,
                                char * pFileName)
{
	//read ini file can not lost
	bool bRet = (GetPrivateProfileString(pSection,
                     pKeyName, "-1", pBuf,
                     5, pFileName) == 4);
	return bRet;
}

bool EepromUtility::WriteProfile(char *pBuf, char *pSection, char *pKeyName, char *pFileName)
{
     return  WritePrivateProfileString(pSection,pKeyName,pBuf,pFileName);
}

bool EepromUtility::LoadDataFromFile()
{
    return LoadDataFromFile(data, romfile);
}

bool EepromUtility::LoadDataFromFile(WORD * datas, char *pFileName)
{
    char buf[6];
    bool bRet = true;
    for (int i=0; i<EEPROM_SZ/2; i++)
    {
		if (!ReadProfile(buf, "EEPROM", EEItem[i], pFileName))
        {
		    bRet = false;
            break;
		}
        datas[i] = (WORD) HexStrToDWORD(buf, 4);
	}

    return bRet;
}

bool EepromUtility::WriteDataFile(WORD *datas, char *pFileName)
{
    char buf[6];
	bool bRet = true;

	for (int i=0; i<EEPROM_SZ/2; i++)
    {
	    sprintf(buf, "%04X", datas[i]);
		if (!WriteProfile(buf, "EEPROM", EEItem[i], pFileName))
        {
		    bRet = false;
            break;
		}    
	}
	return bRet;
}

bool EepromUtility::ReadMacFromFile(char * pBuf)
{
    return ReadMacFromFile(pBuf, macfile);
}

bool EepromUtility::ReadMacFromFile(char *pBuf, char *pFileName)
{
    if (pBuf == NULL || pFileName == NULL)
        return false;

    if (GetPrivateProfileString("MACADDR", 
                     "MAC_PRE_HEADER", "-1", pBuf,
                     7, pFileName) != 6)
        return false;

    if (GetPrivateProfileString("MACADDR", 
                     "MAC_CURR_ADDR", "-1", pBuf+6,
                     7, pFileName) != 6)
        return false;
    DWORD nextAddr = HexStrToDWORD(pBuf+6, 6);
    nextAddr++;
    sprintf(pBuf+6, "%06X", nextAddr);
    pBuf[12] = '\0';
    BOOL bRet = WritePrivateProfileString("MACADDR",
                     "MAC_CURR_ADDR", pBuf+6, pFileName);
    return true;
}

void EepromUtility::SetFilePath(char * rom, char * mac)
{
    if (mac != NULL)
        strcpy(macfile, mac);
    if (rom != NULL)
        strcpy(romfile, rom);
}


