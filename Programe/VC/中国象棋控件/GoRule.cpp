/*******************************************************************************************************
�ļ�����GoRule.cpp
��  �ܣ��������
˼  ·��������������Ϸ���������������·���
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺21:38:52
*******************************************************************************************************/

#include "stdafx.h"
#include "�й�����ؼ�.h"
#include "GoRule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGoRule::CGoRule()
{

}

CGoRule::~CGoRule()
{

}

/*******************************************************************************************************
��������GoChess
��  �ܣ��ж��ܷ�ӵ㣨ifrom, jfrom�����㣨ito, jto������
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ�������桢JIANGDUIMIAN,�н���BEIJIANGJUN,������JIANGJUN,
        �������塢RETURNTRUE���������塢RETURNFALSE,    
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:34:32
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::GoChess(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	ENUM_ReturnValue m_RV;
	ENUM_QiZi m_GoneChessBoard[9][10];

	m_RV = ChessRule(ito, jto, ifrom, jfrom, ChessBoard);
	if(m_RV == RETURNTRUE)
	{
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 10; j++)
				m_GoneChessBoard[i][j] = ChessBoard[i][j];
		//��������
		m_GoneChessBoard[ito][jto] = m_GoneChessBoard[ifrom][jfrom];
		m_GoneChessBoard[ifrom][jfrom] = NoQiZi;
		//�жϽ����桢�н�������
		m_RV = JiangJun(ito, jto, ifrom, jfrom, m_GoneChessBoard);
	}

	return m_RV;
}

/*******************************************************************************************************
��������ChessRule
��  �ܣ��ֱ��жϸ������߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:53:57
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::ChessRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	switch(ChessBoard[ifrom][jfrom])
	{
	case BChe:
	case RChe:
		return CheRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BMa:
	case RMa:
		return MaRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BXiang:
	case RXiang:
		return XiangRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BShi:
	case RShi:
		return ShiRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BShuai:
	case RShuai:
		return ShuaiRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BPao:
	case RPao:
		return PaoRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BBing:
	case RBing:
		return BingRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	default:
		return RETURNFALSE;
	}
	return RETURNTRUE;
}

/*******************************************************************************************************
��������CheRule
��  �ܣ������߷�
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:30:51
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::CheRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(ito == ifrom)
	{
		for(;jfrom != jto;)
		{
			jfrom += sig(jto - jfrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (jfrom != jto))
				return RETURNFALSE;			
		}
		return RETURNTRUE;
	}
	if(jto == jfrom)
	{
		for(;ifrom != ito;)
		{
			ifrom += sig(ito - ifrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (ifrom != ito))
				return RETURNFALSE;
			
		}
		return RETURNTRUE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������MaRule
��  �ܣ�����߷�
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:36:05
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::MaRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(abs(ito - ifrom) == 1 && abs(jto - jfrom) == 2)
	{
		if(ChessBoard[ifrom][jfrom + sig(jto - jfrom)] == NoQiZi)
			return RETURNTRUE;
		else
			return RETURNFALSE;	
	}
	if(abs(ito - ifrom) == 2 && abs(jto - jfrom) == 1)
	{
		if(ChessBoard[ifrom + sig(ito - ifrom)][jfrom] == NoQiZi)
			return RETURNTRUE;
		else
			return RETURNFALSE;	
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������XiangRule
��  �ܣ�����߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:49:54
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::XiangRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(abs(ito - ifrom) == 2 
		&& abs(jfrom - jto) == 2 
		&& ChessBoard[ifrom + sig(ito - ifrom)][jfrom + sig(jto - jfrom)] == NoQiZi)
	{
		if(GetQiZiSide(ChessBoard[ifrom][jfrom]) == RQi && jto <=4)
			return RETURNTRUE;
		if(GetQiZiSide(ChessBoard[ifrom][jfrom]) == BQi && jto >=5)
			return RETURNTRUE;
		else
			return RETURNFALSE;
	}
	else
	{
		return RETURNFALSE;
	}
}

/*******************************************************************************************************
��������ShiRule
��  �ܣ�ʿ���߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:07:29
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::ShiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(abs(ifrom - ito) == 1
		&& abs(jfrom - jto) == 1)
	{
		if(GetQiZiSide(ChessBoard[ifrom][jfrom]) == RQi
			&& ito >= 3 && ito <= 5 && jto >=0 && jto <= 2)
			return RETURNTRUE;
        if(GetQiZiSide(ChessBoard[ifrom][jfrom]) == BQi
			&& ito >= 3 && ito <= 5 && jto >=7 && jto <= 9)
			return RETURNTRUE;
		else
			return RETURNFALSE;
		
	}
	else
	{
		return RETURNFALSE;
	}
}

/*******************************************************************************************************
��������ShuaiRule
��  �ܣ������߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:15:40
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::ShuaiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
		if(GetQiZiSide(ChessBoard[ifrom][jfrom]) == RQi
			&& ito >= 3 && ito <= 5 && jto >=0 && jto <= 2 
			&& ((abs(ito - ifrom) == 1 && jto == jfrom)
			     || (abs(jto - jfrom) == 1 && ito == ifrom)))
			return RETURNTRUE;
        if(GetQiZiSide(ChessBoard[ifrom][jfrom]) == BQi
			&& ito >= 3 && ito <= 5 && jto >=7 && jto <= 9
			&& ((abs(ito - ifrom) == 1 && jto == jfrom)
			     || (abs(jto - jfrom) == 1 && ito == ifrom)))
			return RETURNTRUE;
		else
			return RETURNFALSE;
}

/*******************************************************************************************************
��������PaoRule
��  �ܣ��ڵ��߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:24:18
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::PaoRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(ito == ifrom)
	{
		int iNum = 0;
		for(;jfrom != jto;)
		{
			jfrom += sig(jto - jfrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (jfrom != jto))
				iNum++;
		}
		switch(iNum)
		{
		case 0:
			if(ChessBoard[ito][jto] == NoQiZi)
				return RETURNTRUE;
		    else
				return RETURNFALSE;
			break;
		case 1:
			if(ChessBoard[ito][jto] == NoQiZi)
				return RETURNFALSE;
		    else
				return RETURNTRUE;
			break;
		default:
			return RETURNFALSE;
		}
	}
	if(jto == jfrom)
	{
		int iNum = 0;
		for(;ifrom != ito;)
		{
			ifrom += sig(ito - ifrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (ifrom != ito))
				iNum++;
			
		}
		switch(iNum)
		{
		case 0:
			if(ChessBoard[ito][jto] == NoQiZi)
				return RETURNTRUE;
		    else
				return RETURNFALSE;
			break;
		case 1:
			if(ChessBoard[ito][jto] == NoQiZi)
				return RETURNFALSE;
		    else
				return RETURNTRUE;
			break;
		default:
			return RETURNFALSE;
		}
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������BingRule
��  �ܣ������߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:38:32
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::BingRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	switch(GetQiZiSide(ChessBoard[ifrom][jfrom]))
	{
	case RQi:
		if(jto - jfrom == 1 && ito == ifrom)
			return RETURNTRUE;
		if(jfrom > 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
			return RETURNTRUE;
		else
			return RETURNFALSE;
		break;
	case BQi:
		if(jto - jfrom == -1 && ito == ifrom)		
			return RETURNTRUE;
		if(jfrom <= 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
			return RETURNTRUE;
		else
			return RETURNFALSE;
		break;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������JiangJun
��  �ܣ��жϽ����桢�н�������
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         ENUM_QiZi ChessBoard[][10]����������
����ֵ������ JIANGDUIMIAN��BEIJIANGJUN��JIANGJUN, RETURNTRUE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-2
ʱ  �䣺9:02:54
*******************************************************************************************************/
ENUM_ReturnValue CGoRule::JiangJun(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	int iRShuai, jRShuai, iBShuai, jBShuai;
	//�Һ�˧
	for(iBShuai = 3; iBShuai < 6; iBShuai++)
	{
		for(jBShuai = 7; jBShuai < 10; jBShuai++)
		{
			if(ChessBoard[iBShuai][jBShuai] == BShuai)
				break;
		}
		if(ChessBoard[iBShuai][jBShuai] == BShuai)
			break;		
	}
	//�Һ�˧
	for(iRShuai = 3; iRShuai < 6; iRShuai++)
	{
		for(jRShuai = 0; jRShuai < 3; jRShuai++)
		{
			if(ChessBoard[iRShuai][jRShuai] == RShuai)
				break;
		}
		if(ChessBoard[iRShuai][jRShuai] == RShuai)
			break;		
	}

	//�жϽ�����
	int i = 0, j;
	if(iBShuai == iRShuai)
	{
		j = jRShuai;
		while(j != jBShuai)
		{
			j++;
			if(ChessBoard[iRShuai][j] != NoQiZi && j != jBShuai)
			{
				i++;
				break;
			}
		}
		if(i == 0)
			return JIANGDUIMIAN;
	}

	//�жϱ��������жϽ���
	switch(GetQiZiSide(ChessBoard[ito][jto]))
	{	
	case RQi:
		//����
		i = iRShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		j = jRShuai;
        for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;		
		//��
		i = iRShuai - 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai - 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

        //����
		i = iBShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  JIANGJUN;
		j = jBShuai;
		for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  JIANGJUN;
		//��
		i = iBShuai - 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai - 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		
		
	case BQi:
		//����
		i = iBShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		j = jBShuai;
		for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		//��
		i = iBShuai - 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai - 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		
		
		//����
		i = iRShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return JIANGJUN;
		j = jRShuai;
        for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return JIANGJUN;		
        
		//��
		i = iRShuai - 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai - 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		
		break;
	}

	return RETURNTRUE;
}
