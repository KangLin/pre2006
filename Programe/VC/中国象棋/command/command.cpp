/*******************************************************************************************************
文件名：command.cpp
功  能：实现命令。
        命令格式为：命令（long）命令长度（long）参数
        参数格式为：参数1 \0 参数2 \0 ...... \0 参数n \0
                    是以 \0 作为分隔符的字符串
                    所有其它类型的参数都转换成字符串
用  法：1。用 SetCommand 设置命令
        2。用 GetCommand 得到命令
        3。用 AddPara 设置参数
        4。用 GetPara 得到字符串参数，用 GetLongPara 得到长整型参数
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:46:03

FileName：command.cpp
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-29
Time：    19:46:03
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

//拷贝构造函数
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
函数名：GetLength
功  能：得到命令的长度
参  数：无
返回值：命令的长度
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:41:00
*******************************************************************************************************/
int CCommand::GetLength()
{
    return m_uLen;
}

/*******************************************************************************************************
函数名：GetDataRef
功  能：得到命令数据地址
参  数：无
返回值：数据指针
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:40:53
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
函数名：=
功  能：用于赋值
参  数：
         const CCommand& cmd：CCommand对象
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：17:20:02
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
函数名：=
功  能：用于设置命令
参  数：
         long command：命令
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：17:19:32
*******************************************************************************************************/
const CCommand& CCommand::operator =(long command)
{
    SetCommand(command);
    return *this;
}

/*******************************************************************************************************
函数名：SetCommand
功  能：设置命令。并重置长度
参  数：
         long command：命令
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：16:54:10
*******************************************************************************************************/
void CCommand::SetCommand(long command)
{
    m_uLen = sizeof(long);
    memcpy(m_Data, &command, m_uLen);
    m_uLen *= 2;
    int i = 0;
    memcpy(m_Data + sizeof(long), &i, sizeof(long));//设置参数串长度
}

/*******************************************************************************************************
函数名：GetCommand
功  能：得到命令
参  数：无
返回值：命令
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：16:54:30
*******************************************************************************************************/
long CCommand::GetCommand()
{
    long cmd;
    memcpy(&cmd, m_Data, sizeof(long));                 //得到命令
    long len;
    memcpy(&len, m_Data + sizeof(long), sizeof(long));
    ASSERT((m_uLen - GetCommandHeadLen()) == len);      //命令格式不对时产生断言
    memcpy(m_Data, m_Data + GetCommandHeadLen(), len);  //移除命令
    m_uLen = len;
    return cmd;
}

/*******************************************************************************************************
函数名：AddPara
功  能：增加参数
参  数：
         CString szPara：字符串参数
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：16:54:45
*******************************************************************************************************/
BOOL CCommand::AddPara(CString szPara)
{
    int i;
    i = m_uLen + szPara.GetLength() + 1;
    if(i > g_MAXBUFLEN)
    {
        TRACE(_T("%s(%d) : CCommand::AddPrar 超出缓存区长度\n"), __FILE__, __LINE__);
        return FALSE;
    }
    memcpy(m_Data + m_uLen, szPara, szPara.GetLength() + 1);
    m_uLen = i;
    //设置参数串长度
    i = m_uLen - GetCommandHeadLen();
    memcpy(m_Data + sizeof(long), &i, sizeof(long));
    return TRUE;
}

/*******************************************************************************************************
函数名：AddPara
功  能：增加加长整数参数。把长整数转为字符串
参  数：
         long lPara：长整数参数
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：16:55:19
*******************************************************************************************************/
BOOL CCommand::AddPara(long lPara)
{
    CString sztmp;
    sztmp.Format(_T("%d"), lPara);
    return AddPara(sztmp);
}

/*******************************************************************************************************
函数名：AddPara
功  能：增加加常量参数。把长整数转为字符串
参  数：
         G_COMMAND command：
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:43:59
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
        TRACE(_T("%s(%d) : CCommand::operator+=()超出缓存区\n"), __FILE__, __LINE__);
    }
    return *this;
}

const CCommand& CCommand::operator +=(long lPara)
{
    if(!AddPara(lPara))
    {
        TRACE(_T("%s(%d) : CCommand::operator+=()超出缓存区\n"), __FILE__, __LINE__);
    }
    return *this;
}

const CCommand& CCommand::operator +=(G_COMMAND cmd)
{
    if(!AddPara(cmd))
    {
        TRACE(_T("%s(%d) : CCommand::operator+=()超出缓存区\n"), __FILE__, __LINE__);
    }
    return *this;
}

/*******************************************************************************************************
函数名：GetPara
功  能：得到最前面的一个字符串。并移去这个字符串。把后面的参数向前移。
参  数：无
返回值：最前的一个字符串
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:21:49
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
        TRACE(_T("%s(%d) : CCommand::GetPara格式错误\n"), __FILE__, __LINE__);
        return CString();
    }

    CString sztmp((TCHAR*) m_Data);
    m_uLen = m_uLen - i - 1;
    memcpy(m_Data, m_Data + i + 1, m_uLen);
    return sztmp;
}

/*******************************************************************************************************
函数名：GetLongPara
功  能：得到最前的一个字符串,并把字符串转换成长整型。并把这个字符串移去。
参  数：无
返回值：整数
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:22:59
*******************************************************************************************************/
long CCommand::GetLongPara()
{
    CString sztmp;
    sztmp = GetPara();
    if(sztmp.IsEmpty())
    {
        TRACE(_T("%s(%d) : CCommand::GetLongPara得到字符错误\n"), __FILE__, __LINE__);
        return 0;
    }
    return _ttol(sztmp);    
}