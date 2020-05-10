#ifndef _CHINESCHESS_GLOBEFUNCTION_BY_KANGLIN_2004_12_12_
#define _CHINESCHESS_GLOBEFUNCTION_BY_KANGLIN_2004_12_12_

int SplitString(LPVOID lpInData, INT* iInLen, LPVOID lpOutData, INT* iOutLen);
CString SplitString(LPVOID lpInData, INT *iInLen);
long GetCommand(LPVOID lpBuf, int* iLen);
int GetCommandHeadLen();
long GetPara(int iLen);
void WriteCommandParaLen(LPVOID lpBuf, int iLen);

void TransparentBlt2( HDC hdcDest,      // Ŀ��DC
					 int nXOriginDest,  // Ŀ��Xƫ��
					 int nYOriginDest,  // Ŀ��Yƫ��
					 int nWidthDest,    // Ŀ����
					 int nHeightDest,   // Ŀ��߶�
					 HDC hdcSrc,        // ԴDC
					 int nXOriginSrc,   // ԴX���
					 int nYOriginSrc,   // ԴY���
					 int nWidthSrc,     // Դ���
					 int nHeightSrc,    // Դ�߶�
					 UINT crTransparent // ͸��ɫ,COLORREF����
					 );

#endif //#ifndef _CHINESCHESS_GLOBEFUNCTION_BY_KANGLIN_2004_12_12_