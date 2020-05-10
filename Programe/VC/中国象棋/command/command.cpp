/*******************************************************************************************************
�ļ�����command.cpp
��  �ܣ�ʵ�����
        �����ʽΪ�����long������ȣ�long������
        ������ʽΪ������1 \0 ����2 \0 ...... \0 ����n \0
                    ���� \0 ��Ϊ�ָ������ַ���
                    �����������͵Ĳ�����ת�����ַ���
��  ����1���� SetCommand ��������
        2���� GetCommand �õ�����
        3���� AddPara ���ò���
        4���� GetPara �õ��ַ����������� GetLongPara �õ������Ͳ���
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:46:03

FileName��command.cpp
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-29
Time��    19:46:03
*******************************************************************************************************/

#include "stdafx.h"
#include "command.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommand::CCommand()
{
    m_uLen = GetCommandHeadLen();
    memset(m_Data, g_cmdNoCommand, m_uLen);
}

//�������캯��
CCommand::CCommand(const CCommand &cmd)
{
    m_uLen = cmd.m_uLen;
    memcpy(m_Data, cmd.m_Data, m_uLen);
}

CCommand::CCommand(LPVOID lpBuf, int iLen)
{
    m_uLen = iLen;
    memcpy(m_Data, lpBuf, iLen);    
}

CCommand::~CCommand()
{
    Free();
}

void CCommand::Free()
{
    m_uLen = GetCommandHeadLen();
    memset(m_Data, g_cmdNoCommand, m_uLen);
}

/*******************************************************************************************************
��������GetLength
��  �ܣ��õ�����ĳ���
��  ������
����ֵ������ĳ���
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:41:00
*******************************************************************************************************/
int CCommand::GetLength()
{
    return m_uLen;
}

/*******************************************************************************************************
��������GetDataRef
��  �ܣ��õ��������ݵ�ַ
��  ������
����ֵ������ָ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:40:53
*******************************************************************************************************/
LPVOID CCommand::GetDataRef()
{
    return m_Data;
}

int CCommand::GetCommandHeadLen()
{
    return sizeof(long) * 2;
}

/*******************************************************************************************************
��������=
��  �ܣ����ڸ�ֵ
��  ����
         const CCommand& cmd��CCommand����
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺17:20:02
*******************************************************************************************************/
const CCommand& CCommand::operator =(const CCommand& cmd)
{
    if(this == &cmd)
    {
        return *this;
    }
    m_uLen = cmd.m_uLen;
    memcpy(m_Data, cmd.m_Data, m_uLen);
    return *this;
}

/*******************************************************************************************************
��������=
��  �ܣ�������������
��  ����
         long command������
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺17:19:32
*******************************************************************************************************/
const CCommand& CCommand::operator =(long command)
{
    SetCommand(command);
    return *this;
}

/*******************************************************************************************************
��������SetCommand
��  �ܣ�������������ó���
��  ����
         long command������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺16:54:10
*******************************************************************************************************/
void CCommand::SetCommand(long command)
{
    m_uLen = sizeof(long);
    memcpy(m_Data, &command, m_uLen);
    m_uLen *= 2;
    int i = 0;
    memcpy(m_Data + sizeof(long), &i, sizeof(long));//���ò���������
}

/*******************************************************************************************************
��������GetCommand
��  �ܣ��õ�����
��  ������
����ֵ������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺16:54:30
*******************************************************************************************************/
long CCommand::GetCommand()
{
    long cmd;
    memcpy(&cmd, m_Data, sizeof(long));                 //�õ�����
    long len;
    memcpy(&len, m_Data + sizeof(long), sizeof(long));
    ASSERT((m_uLen - GetCommandHeadLen()) == len);      //�����ʽ����ʱ��������
    memcpy(m_Data, m_Data + GetCommandHeadLen(), len);  //�Ƴ�����
    m_uLen = len;
    return cmd;
}

/*******************************************************************************************************
��������AddPara
��  �ܣ����Ӳ���
��  ����
         CString szPara���ַ�������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺16:54:45
*******************************************************************************************************/
BOOL CCommand::AddPara(CString szPara)
{
    int i;
    i = m_uLen + szPara.GetLength() + 1;
    if(i > g_MAXBUFLEN)
    {
        TRACE(_T("%s(%d) : CCommand::AddPrar ��������������\n"), __FILE__, __LINE__);
        return FALSE;
    }
    memcpy(m_Data + m_uLen, szPara, szPara.GetLength() + 1);
    m_uLen = i;
    //���ò���������
    i = m_uLen - GetCommandHeadLen();
    memcpy(m_Data + sizeof(long), &i, sizeof(long));
    return TRUE;
}

/*******************************************************************************************************
��������AddPara
��  �ܣ����Ӽӳ������������ѳ�����תΪ�ַ���
��  ����
         long lPara������������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺16:55:19
*******************************************************************************************************/
BOOL CCommand::AddPara(long lPara)
{
    CString sztmp;
    sztmp.Format(_T("%d"), lPara);
    return AddPara(sztmp);
}

/*******************************************************************************************************
��������AddPara
��  �ܣ����Ӽӳ����������ѳ�����תΪ�ַ���
��  ����
         G_COMMAND command��
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:43:59
*******************************************************************************************************/
BOOL CCommand::AddPara(G_COMMAND command)
{
    CString sztmp;
    sztmp.Format(_T("%d"), command);
    return AddPara(sztmp);
}

const CCommand& CCommand::operator +=(CString szPara)
{
    if(!AddPara(szPara))
    {
        TRACE(_T("%s(%d) : CCommand::operator+=()����������\n"), __FILE__, __LINE__);
    }
    return *this;
}

const CCommand& CCommand::operator +=(long lPara)
{
    if(!AddPara(lPara))
    {
        TRACE(_T("%s(%d) : CCommand::operator+=()����������\n"), __FILE__, __LINE__);
    }
    return *this;
}

const CCommand& CCommand::operator +=(G_COMMAND cmd)
{
    if(!AddPara(cmd))
    {
        TRACE(_T("%s(%d) : CCommand::operator+=()����������\n"), __FILE__, __LINE__);
    }
    return *this;
}

/*******************************************************************************************************
��������GetPara
��  �ܣ��õ���ǰ���һ���ַ���������ȥ����ַ������Ѻ���Ĳ�����ǰ�ơ�
��  ������
����ֵ����ǰ��һ���ַ���
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:21:49
*******************************************************************************************************/
CString CCommand::GetPara()
{
    int i = 0;
    while(m_Data[i] != 0 && i < m_uLen)
    {
        i ++;
    }
    if(i >= m_uLen)
    {
        TRACE(_T("%s(%d) : CCommand::GetPara��ʽ����\n"), __FILE__, __LINE__);
        return CString();
    }

    CString sztmp((TCHAR*) m_Data);
    m_uLen = m_uLen - i - 1;
    memcpy(m_Data, m_Data + i + 1, m_uLen);
    return sztmp;
}

/*******************************************************************************************************
��������GetLongPara
��  �ܣ��õ���ǰ��һ���ַ���,�����ַ���ת���ɳ����͡���������ַ�����ȥ��
��  ������
����ֵ������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:22:59
*******************************************************************************************************/
long CCommand::GetLongPara()
{
    CString sztmp;
    sztmp = GetPara();
    if(sztmp.IsEmpty())
    {
        TRACE(_T("%s(%d) : CCommand::GetLongPara�õ��ַ�����\n"), __FILE__, __LINE__);
        return 0;
    }
    return _ttol(sztmp);    
}