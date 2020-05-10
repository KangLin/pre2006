/*******************************************************************************************************
文件名：Mixer.cpp
功  能：混频器实现文件
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-13
时  间：16:55:47
*******************************************************************************************************/

#include "stdafx.h"
#include "Mixer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMixer::CMixer()
{

}

CMixer::~CMixer()
{

}

/*******************************************************************************************************
函数名：GetNumDevs
功  能：得到系统中混频器的数量
参  数：无
返回值：系统中混频器的数量
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-13
时  间：16:50:34
*******************************************************************************************************/
INT CMixer::GetNumDevs()
{
	return mixerGetNumDevs();
}
        
/*******************************************************************************************************
函数名：GetDevCaps
功  能：得到指定混频器的性能
参  数：
         UINT uMxId：混频器的标识符[0, 混频器的数量-1]
         LPMIXERCAPS lpMaxcaps：性能结构
		 typedef struct { 
			 WORD    wMid; //厂商标识符
			 WORD    wPid; //产品标识符
			 MMVERSION vDriverVersion; //设备版号,major (high byte), minor (low byte)
			 CHAR    szPname[MAXPNAMELEN]; //产品名
			 DWORD   fdwSupport; //驱动程序多样的支持信息,现在没有定义
			 DWORD   cDestinations; //与混频器相连的音频目的线(Audio Line Destinations)的数量
		 } MIXERCAPS; 
返回值：成功返回 TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-13
时  间：16:51:14
*******************************************************************************************************/
BOOL CMixer::GetDevCaps(UINT uMxId, LPMIXERCAPS lpMaxcaps)
{
	ASSERT(uMxId >= 0 && uMxId < mixerGetNumDevs() && lpMaxcaps != NULL);
	return mixerGetDevCaps(uMxId, lpMaxcaps, sizeof(MIXERCAPS));
}

BOOL CMixer::OpenDev(HMIXEROBJ hMixerObj, DWORD dwFlags)
{
	if(mixerGetID((HMIXEROBJ)hMixerObj, &m_uMixerID, dwFlags) != MMSYSERR_NOERROR)
	{
		TRACE(_T("混频器从ID得到句柄失败.\n"));
		return FALSE;
	}

	WNDCLASSEX wcx;
	memset(&wcx, 0, sizeof(WNDCLASSEX));	
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.lpszClassName = WND_CLASS_NAME;
	wcx.lpfnWndProc = (WNDPROC)MixerWndProc;
	::RegisterClassEx(&wcx);
	m_hWnd = CreateWindow(WND_CLASS_NAME,
							WND_NAME,
							WS_POPUP | WS_VISIBLE,
							0, 0, 0, 0,
							NULL, NULL, NULL, NULL );
	if(!m_hWnd)
	{	
		return FALSE;
	}
	::ShowWindow(m_hWnd, SW_HIDE);
    MMRESULT mmResult = mixerOpen((LPHMIXER)&m_hMixer, m_uMixerID, (DWORD)m_hWnd, NULL, CALLBACK_WINDOW);
	if(mmResult != MMSYSERR_NOERROR)
	{			
		TRACE(_T("打开混频器失败.\n"));
		::SendMessage(m_hWnd, WM_QUIT, NULL, NULL);
		//::DestroyWindow(m_hWnd);
		return FALSE;
	}

	return TRUE;
}

/*******************************************************************************************************
函数名：CloseDev
功  能：关闭混频器
参  数：无
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-13
时  间：16:54:00
*******************************************************************************************************/
BOOL CMixer::CloseDev()
{
	if(MMSYSERR_NOERROR == mixerClose(m_hMixer))
		return TRUE;
	TRACE(_T("关闭混频器失败.\n"));
	return FALSE;
}

LRESULT CALLBACK CMixer::MixerWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( uMsg == MM_MIXM_CONTROL_CHANGE )
	{
	
	}
	return ::DefWindowProc( hwnd, uMsg, wParam, lParam);
}

/*******************************************************************************************************
函数名：GetLineInfo
功  能：得到指定类型的Audio Line的信息
参  数：
         DWORD dwFlags：指定的类型
		 typedef struct { 
			DWORD cbStruct; //本结构的大小
			DWORD dwDestination; //目的线的索引,范围[0, MIXERCAPS中的成员cDestinations-1]
			DWORD dwSource; //与成员dwDestination相联系的源音频线的索引,
			                //当标识MIXER_GETLINEINFOF_SOURCE被设置,
							//它的范围[0,与指定dwDestination的目的线的相连值(成员dwConnections)
			DWORD dwLineID; //这个结构的标识符,用于以后的查询
			DWORD fdwLine; //音频线的状态
			DWORD dwUser; 
			DWORD dwComponentType; //组合类型
			DWORD cChannels; //通道数
			DWORD cConnections; //与指定的目的线的连接数
			DWORD cControls; //与指定的目的线相连天的控制数
			CHAR  szShortName[MIXER_SHORT_NAME_CHARS]; 
			CHAR  szName[MIXER_LONG_NAME_CHARS]; 
			struct { 
				DWORD     dwType; 
				DWORD     dwDeviceID; 
				WORD      wMid; 
				WORD      wPid; 
				MMVERSION vDriverVersion; 
				CHAR      szPname[MAXPNAMELEN]; 
			} Target; 
		} MIXERLINE; 
返回值：成功返回TRUE,否则返回FLASE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-14
时  间：15:10:26
*******************************************************************************************************/
BOOL CMixer::GetLineInfo(DWORD dwFlags)
{
	MIXERLINE MixerLine;
	memset( &MixerLine, 0, sizeof(MixerLine) );
	MixerLine.cbStruct = sizeof(MixerLine);
	MixerLine.dwComponentType = dwFlags;
    MMRESULT mmResult = mixerGetLineInfo((HMIXEROBJ)m_hMixer, &MixerLine, 
		MIXER_GETLINEINFOF_COMPONENTTYPE);
	if ( mmResult != MMSYSERR_NOERROR )
	{	
		TRACE(_T("得到Line信息失败.\n"));
		return FALSE;
	}

	TRACE(_T("Audio Line信息的描述:%s\n"), MixerLine.szShortName);
	m_Control.dwLineID = MixerLine.dwLineID;
	m_Control.dwChannelCount = MixerLine.cChannels;
	return TRUE;
}

/*******************************************************************************************************
函数名：GetControl
功  能：得到一个指定类型的控制的属性,存于 m_Control 中.
参  数：
         DWORD dwFlags：控制的类型标识
返回值：成功返回TRUE,否则返回FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-14
时  间：15:05:25
*******************************************************************************************************/
BOOL CMixer::GetControl(DWORD dwFlags)
{
	MIXERCONTROL Control;
	memset(&Control, 0, sizeof(MIXERCONTROL));
	Control.cbStruct = sizeof(MIXERCONTROL);

	MIXERLINECONTROLS LineControls;
	memset(&LineControls, 0, sizeof(MIXERLINECONTROLS));
	LineControls.cbStruct = sizeof(MIXERLINECONTROLS);

	LineControls.dwControlType = dwFlags;
	LineControls.dwLineID = m_Control.dwLineID;
	LineControls.cControls = 1;
	LineControls.cbmxctrl = sizeof(MIXERCONTROL);
	LineControls.pamxctrl = &Control;
	MMRESULT mmResult = mixerGetLineControls( (HMIXEROBJ)m_hMixer, 
		&LineControls, MIXER_GETLINECONTROLSF_ONEBYTYPE);
	if ( mmResult != MMSYSERR_NOERROR )
	{
		TRACE(_T("得到控制信息失败.\n"));
		return FALSE;
	}
	
	m_Control.dwMinimalValue = Control.Bounds.dwMinimum;
	m_Control.dwMaximalValue = Control.Bounds.dwMaximum;
	m_Control.dwStepValue = Control.Metrics.cSteps;
	switch(dwFlags)
	{
	case MIXERCONTROL_CONTROLTYPE_VOLUME:
		m_ControlID.dwVolumeID = Control.dwControlID;
		break;
	}
	
	return TRUE;
}

/*******************************************************************************************************
函数名：GetCurrentVolume
功  能：得到当前的音量
参  数：无
返回值：当前的音量
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-14
时  间：13:58:36
*******************************************************************************************************/
DWORD CMixer::GetCurrentVolume()
{
	m_Control.dwControlID = m_ControlID.dwVolumeID;
	return GetDWORDValue();
}

/*******************************************************************************************************
函数名：SetCurrentVolume
功  能：设置当前的音量
参  数：
         DWORD dwVolume：当前的音量
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-14
时  间：14:59:59
*******************************************************************************************************/
BOOL CMixer::SetCurrentVolume(DWORD dwVolume)
{
	m_Control.dwControlID = m_ControlID.dwVolumeID;
	return SetDWORDValue(dwVolume);
}

/*******************************************************************************************************
函数名：GetDWORDValue
功  能：得到一个DWORD值的控制的当前值,
        这个控制的ID和通道都已在m_Control中设置
参  数：无
返回值：一个DWORD值的控制的当前值
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-14
时  间：14:54:26
*******************************************************************************************************/
DWORD CMixer::GetDWORDValue()
{
	MIXERCONTROLDETAILS_UNSIGNED* pDetails;
	pDetails = new MIXERCONTROLDETAILS_UNSIGNED[m_Control.dwChannelCount];
	if ( !pDetails )
		return -1;

	MIXERCONTROLDETAILS ControlDetails;
	memset( &ControlDetails, 0, sizeof(MIXERCONTROLDETAILS));
	ControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	ControlDetails.dwControlID = m_Control.dwControlID;
	ControlDetails.cChannels = m_Control.dwChannelCount;
	ControlDetails.cMultipleItems = 0;
	ControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	ControlDetails.paDetails = pDetails;
	MMRESULT mmResult = mixerGetControlDetails( (HMIXEROBJ)m_hMixer, &ControlDetails, MIXER_GETCONTROLDETAILSF_VALUE);
	if ( mmResult != MMSYSERR_NOERROR )
	{
		return -1;
	}

	DWORD dwValue = pDetails[0].dwValue;
	delete []pDetails;
	
	return dwValue;
}

/*******************************************************************************************************
函数名：SetDWORDValue
功  能：得到一个DWORD值的控制的当前值,
        这个控制的ID和通道都已在m_Control中设置
参  数：无
返回值：成功返回TRUE,失败返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-14
时  间：14:56:26
*******************************************************************************************************/
BOOL CMixer::SetDWORDValue(DWORD dwValue)
{
	if(dwValue < m_Control.dwMinimalValue || dwValue > m_Control.dwMaximalValue)
		return FALSE;

	MIXERCONTROLDETAILS_UNSIGNED* pDetails;
	pDetails = new MIXERCONTROLDETAILS_UNSIGNED[m_Control.dwChannelCount];
	if ( !pDetails )
		return FALSE;
	for (DWORD i = 0; i < m_Control.dwChannelCount; i++ )
	{
		pDetails[i].dwValue = dwValue;
	}
	MIXERCONTROLDETAILS ControlDetails;
	memset( &ControlDetails, 0, sizeof(MIXERCONTROLDETAILS));
	ControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	ControlDetails.dwControlID = m_Control.dwControlID;
	ControlDetails.cChannels = m_Control.dwChannelCount;
	ControlDetails.cMultipleItems = 0;
	ControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	ControlDetails.paDetails = &pDetails[0];
	MMRESULT mmResult = mixerSetControlDetails( (HMIXEROBJ)m_hMixer, &ControlDetails, MIXER_SETCONTROLDETAILSF_VALUE);
	delete []pDetails;
	if ( mmResult != MMSYSERR_NOERROR )
	{
		return FALSE;
	}
	return TRUE;
}


MMRESULT CMixer::GetLineInfo(HMIXEROBJ hmxobj, LPMIXERLINE pmxl, DWORD fdwInfo)
{
	MMRESULT result;
	result = mixerGetLineInfo(hmxobj, pmxl, fdwInfo);
	if(MMSYSERR_NOERROR == result)
	{
		TRACE(_T("得到LineInfo:\n"));
		TRACE(_T("目的音频线的索引:MIXERLINE.dwDestination = %d\n"), pmxl->dwDestination);
		TRACE(_T("源音频线的索引:MIERLINE.dwSource = %d\n"), pmxl->dwSource);
		TRACE(_T("通道数:MIERLINE.cChannels = %d\n"), pmxl->cChannels);
		TRACE(_T("连接数:MIERLINE.cConnections = %d\n"), pmxl->cConnections);
		TRACE(_T("控制数:MIERLINE.cControls = %d\n"), pmxl->cControls);
		TRACE(_T("混频器名MIERLINE.szName = %s\n"), pmxl->szName);
		TRACE(_T("MIERLINE.Target.szPname = %s\n"), pmxl->Target.szPname);
	}
	return result;
}

MMRESULT CMixer::GetLineControls(HMIXEROBJ hmxobj, LPMIXERLINECONTROLS pmxlc, DWORD fdwControls)
{
	MMRESULT result;
	result = mixerGetLineControls(hmxobj, pmxlc, fdwControls);
	if(MMSYSERR_NOERROR == result)
	{
		TRACE(_T("得到LineControlsInfo:\n"));
		TRACE(_T("MIXERLINECONTROLS.cControls = %s\n"), pmxlc->cControls);
		for(int i = 0; i < pmxlc->cControls; i++)
		{
			TRACE(_T("第%d个控制.控制名:%s\n"), i + 1, (MIXERCONTROL*)(pmxlc->pamxctrl + i)->szName);
		}
	}
		return result;
}
