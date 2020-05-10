#include <stdafx.h>
#include ".\CharConver.h"

/*******************************************************************************************************
��������CharToASCII
��  �������ַ���ת������Ӧ�� ACSII ����ַ���
��  ����
        char * pStr��Ҫת�����ַ���
����ֵ������Ϊ char * ��ACSII ����ַ������ɵ������ͷ��ڴ档
��  ����1.0.0.1
��  �ߣ���  ��
*******************************************************************************************************/
char * CharToASCII(char * pStr)
{
	char * p, *pOut = NULL;
	int nLen = 0;
	if(NULL == pStr)
	{
		return NULL;
	} // ���� if(NULL == pStr)
	nLen = strlen(pStr);
	pOut = new char[nLen * 10];
	if(pOut == NULL)
	{
		return NULL;
	}// ���� if(pOut == NULL)
	
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
��������CharToHex
��  �������ַ�ת����ʮ�����е�����
��  ����
        char Ch���ַ�
����ֵ������Ϊ char * ��ʮ�������Ƶ��ַ�����
��  ����1.0.0.1
��  �ߣ���  ��
*******************************************************************************************************/
char * CharToHex(char Ch)
{
	static char dst[100];
	itoa(Ch, dst, 16);
	return dst + strlen(dst) - 2;
}

/*******************************************************************************************************
��������HexStrToChar
��  ���������ַ�����ʾ��ʮ������ת��ΪDWORD
��  ����
        char * str��ʮ�����Ƶ������ַ���
				int nSize ��Ҫת���ĳ���
����ֵ������Ϊ char ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��4�� 21:28:34
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
				} // ���� if(str[i] >= _T('A') && str[i] <= _T('F'))
			} // ���� if(str[i] >= _T('a') && str[i] <= _T('f'))
        }
    }

    return value;
}

/*******************************************************************************************************
��������ASCToString
��  ������ ASCII ���ַ�ת�����ַ���
��  ����
        char * pStr��ASCII ���ַ���
����ֵ������Ϊ char* ��ת������ַ�����������ɵ������ͷ��ڴ档
��  ����1.0
��  �ߣ���  ��
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
	}// ���� if(NULL == pOut)
	p = pOut;
	pTmp = strtok(pStr, " ");
	while (pTmp)
	{
		if(strlen(pTmp) > 2) //�ж��Ƿ�����ȷ�� ACSII ��
		{
#ifdef __cplusplus
			delete []pOut;
#else
			free(pOut);
#endif
			return NULL;
		} // ���� if(strlen(pTmp) > 2)
		*p = (char)HexStrToChar(pTmp, strlen(pTmp));
		p++;
		pTmp = strtok(NULL, " ");
	}
	
	return pOut;
}

/*******************************************************************************************************
��������TrimL
��  ����ȥ���ַ�����ߵĿո�
��  ����
        char * pStr�������ַ���
����ֵ������Ϊ char * ��ȥ����߿ո����ַ�����ָ�롣
��  ����1.0
��  �ߣ���  ��
*******************************************************************************************************/
char * TrimL(char * pStr)
{
	char * p;
	if(pStr == NULL)
	{
		return NULL;
	}// ���� if(pStr == NULL)
	p = pStr;
	
	while((*p == ' ') && (*p != '\0'))
	{
		p++;
	} // ���� while((*p == ' ') && (*p != '\0'))
	return p;
}

/*******************************************************************************************************
��������TrimR
��  ����ȥ���ַ����ұߵĿո�
��  ����
        char * pStr�������ַ���
����ֵ������Ϊ char * ��ȥ���ұ߿ո����ַ�����ָ�롣
��  ����1.0
��  �ߣ���  ��
*******************************************************************************************************/
char * TrimR(char * pStr)
{
	char * p;
	if(NULL == pStr)
	{
		return NULL;
	}// ���� if(NULL == pStr)
	p = pStr + strlen(pStr);
	while(' ' == *p && p > pStr)
	{
		p--;
	} // ���� while(' ' == *p && p > pStr)
	if(*p != '\0')
	{
		*(p + 1) = '\0';
	} // ���� if(*p != '\0')
	return pStr;
}

/*******************************************************************************************************
��������Trim
��  ����ȥ���ַ����е�ǰ���󵼿ո�
��  ����
        char * pStr�������ַ���
����ֵ������Ϊ char * ��ȥ��ǰ�󵼿ո���ַ���
��  ����1.0
��  �ߣ���  ��
*******************************************************************************************************/
char * Trim(char * pStr)
{
	return TrimR(TrimL(pStr));
}