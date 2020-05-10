#include <stdafx.h>
#include ".\CharConver.h"

/*******************************************************************************************************
函数名：CharToASCII
描  述：把字符串转换成相应的 ACSII 码的字符串
参  数：
        char * pStr：要转换的字符串
返回值：类型为 char * 。ACSII 码的字符串。由调用者释放内存。
版  本：1.0.0.1
作  者：康  林
*******************************************************************************************************/
char * CharToASCII(char * pStr)
{
	char * p, *pOut = NULL;
	int nLen = 0;
	if(NULL == pStr)
	{
		return NULL;
	} // 结束 if(NULL == pStr)
	nLen = strlen(pStr);
	pOut = new char[nLen * 10];
	if(pOut == NULL)
	{
		return NULL;
	}// 结束 if(pOut == NULL)
	
	memset(pOut, 0, nLen * 4);
	p = pStr;
	while(*p != '\0')
	{
		strcat(pOut, CharToHex(*p++));
		strcat(pOut, " ");
	}
	return pOut;
}

/*******************************************************************************************************
函数名：CharToHex
描  述：把字符转换成十六进行的数。
参  数：
        char Ch：字符
返回值：类型为 char * 。十六进行制的字符串。
版  本：1.0.0.1
作  者：康  林
*******************************************************************************************************/
char * CharToHex(char Ch)
{
	static char dst[100];
	itoa(Ch, dst, 16);
	return dst + strlen(dst) - 2;
}

/*******************************************************************************************************
函数名：HexStrToChar
描  述：从用字符串表示的十六进制转换为DWORD
参  数：
        char * str：十六进制的数字字符串
				int nSize ：要转换的长度
返回值：类型为 char 。
版  本：1.0
作  者：康  林
时  间：2005年11月4日 21:28:34
*******************************************************************************************************/
char HexStrToChar(char * str, int nSize)
{
	char value = 0;
	int i;

	for(i = 0; i < nSize; ++i)
    {
		if(str[i] >= '0' && str[i] <= '9')
        {
    	    value <<= 4;
    	    value += (str[i] - '0');
        }
        else
        {
			value <<= 4;
			if(str[i] >= _T('a') && str[i] <= _T('f'))
			{
				value += (str[i] - _T('a') + 10);
			}				
			else
			{
				if(str[i] >= _T('A') && str[i] <= _T('F'))
				{
					value += (str[i] - _T('A') + 10);
				} // 结束 if(str[i] >= _T('A') && str[i] <= _T('F'))
			} // 结束 if(str[i] >= _T('a') && str[i] <= _T('f'))
        }
    }

    return value;
}

/*******************************************************************************************************
函数名：ASCToString
描  述：从 ASCII 码字符转换成字符串
参  数：
        char * pStr：ASCII 码字符串
返回值：类型为 char* 。转换后的字符串，用完后由调用者释放内存。
版  本：1.0
作  者：康  林
*******************************************************************************************************/
char * ASCToString(char * pStr)
{
	char *pOut = NULL, *pTmp = NULL, *p;
	int nLen;

	if(NULL == pStr)
	{
		return NULL;
	}
	nLen = strlen(pStr) + 1;
#ifdef __cplusplus
	pOut = new char[nLen];
#else
	pOut = malloc(nLen);
#endif
	memset(pOut, 0, nLen);
	if(NULL == pOut)
	{
		return NULL;
	}// 结束 if(NULL == pOut)
	p = pOut;
	pTmp = strtok(pStr, " ");
	while (pTmp)
	{
		if(strlen(pTmp) > 2) //判断是否是正确的 ACSII 码
		{
#ifdef __cplusplus
			delete []pOut;
#else
			free(pOut);
#endif
			return NULL;
		} // 结束 if(strlen(pTmp) > 2)
		*p = (char)HexStrToChar(pTmp, strlen(pTmp));
		p++;
		pTmp = strtok(NULL, " ");
	}
	
	return pOut;
}

/*******************************************************************************************************
函数名：TrimL
描  述：去掉字符串左边的空格。
参  数：
        char * pStr：输入字符串
返回值：类型为 char * 。去掉左边空格后的字符串的指针。
版  本：1.0
作  者：康  林
*******************************************************************************************************/
char * TrimL(char * pStr)
{
	char * p;
	if(pStr == NULL)
	{
		return NULL;
	}// 结束 if(pStr == NULL)
	p = pStr;
	
	while((*p == ' ') && (*p != '\0'))
	{
		p++;
	} // 结束 while((*p == ' ') && (*p != '\0'))
	return p;
}

/*******************************************************************************************************
函数名：TrimR
描  述：去掉字符串右边的空格
参  数：
        char * pStr：输入字符串
返回值：类型为 char * 。去掉右边空格后的字符串的指针。
版  本：1.0
作  者：康  林
*******************************************************************************************************/
char * TrimR(char * pStr)
{
	char * p;
	if(NULL == pStr)
	{
		return NULL;
	}// 结束 if(NULL == pStr)
	p = pStr + strlen(pStr);
	while(' ' == *p && p > pStr)
	{
		p--;
	} // 结束 while(' ' == *p && p > pStr)
	if(*p != '\0')
	{
		*(p + 1) = '\0';
	} // 结束 if(*p != '\0')
	return pStr;
}

/*******************************************************************************************************
函数名：Trim
描  述：去掉字符串中的前导后导空格。
参  数：
        char * pStr：输入字符串
返回值：类型为 char * 。去掉前后导空格的字符串
版  本：1.0
作  者：康  林
*******************************************************************************************************/
char * Trim(char * pStr)
{
	return TrimR(TrimL(pStr));
}