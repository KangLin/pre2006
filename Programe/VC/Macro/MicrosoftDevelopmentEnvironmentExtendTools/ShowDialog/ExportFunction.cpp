#include "stdafx.h"
#include "exportfunction.h"

/*******************************************************************************************************
��������ShowLicense
��  �ܣ�
��  ������
����ֵ��0, ȡ��
        1, �´�����ʱ��ʾ���Ի���
        2, ȷ��
��  �ߣ���  ��
��  ����4.0.0.0
��  �ڣ�2005-7-11
ʱ  �䣺13:02:16
*******************************************************************************************************/
LONG ShowLicense()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	AfxEnableControlContainer();
	CLicense license; 
	int ir = 0;
	if(license.DoModal() == IDOK)
	{
		ir = 2; 
		if(license.m_m_bShow)
		{
			ir |= 1; 
		} // ���� if(license.m_m_bShow)
	}
	else
	{
		ir = 0;
	} // ���� if(license.DoModal())
	return ir;
}