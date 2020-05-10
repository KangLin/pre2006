#include "stdafx.h"
#include "exportfunction.h"

/*******************************************************************************************************
函数名：ShowLicense
功  能：
参  数：无
返回值：0, 取消
        1, 下次启动时显示本对话框
        2, 确定
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-11
时  间：13:02:16
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
		} // 结束 if(license.m_m_bShow)
	}
	else
	{
		ir = 0;
	} // 结束 if(license.DoModal())
	return ir;
}