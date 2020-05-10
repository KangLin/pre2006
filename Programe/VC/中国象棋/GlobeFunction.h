#ifndef _CHINESCHESS_GLOBEFUNCTION_BY_KANGLIN_2004_12_12_
#define _CHINESCHESS_GLOBEFUNCTION_BY_KANGLIN_2004_12_12_

int SplitString(LPVOID lpInData, INT* iInLen, LPVOID lpOutData, INT* iOutLen);
CString SplitString(LPVOID lpInData, INT *iInLen);
long GetCommand(LPVOID lpBuf, int* iLen);
int GetCommandHeadLen();
long GetPara(int iLen);
void WriteCommandParaLen(LPVOID lpBuf, int iLen);

void TransparentBlt2( HDC hdcDest,      // 目标DC
					 int nXOriginDest,  // 目标X偏移
					 int nYOriginDest,  // 目标Y偏移
					 int nWidthDest,    // 目标宽度
					 int nHeightDest,   // 目标高度
					 HDC hdcSrc,        // 源DC
					 int nXOriginSrc,   // 源X起点
					 int nYOriginSrc,   // 源Y起点
					 int nWidthSrc,     // 源宽度
					 int nHeightSrc,    // 源高度
					 UINT crTransparent // 透明色,COLORREF类型
					 );

#endif //#ifndef _CHINESCHESS_GLOBEFUNCTION_BY_KANGLIN_2004_12_12_