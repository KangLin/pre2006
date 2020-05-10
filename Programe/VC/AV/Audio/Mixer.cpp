/*******************************************************************************************************
�ļ�����Mixer.cpp
��  �ܣ���Ƶ��ʵ���ļ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-13
ʱ  �䣺16:55:47
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
��������GetNumDevs
��  �ܣ��õ�ϵͳ�л�Ƶ��������
��  ������
����ֵ��ϵͳ�л�Ƶ��������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-13
ʱ  �䣺16:50:34
*******************************************************************************************************/
INT CMixer::GetNumDevs()
{
	return mixerGetNumDevs();
}
        
/*******************************************************************************************************
��������GetDevCaps
��  �ܣ��õ�ָ����Ƶ��������
��  ����
         UINT uMxId����Ƶ���ı�ʶ��[0, ��Ƶ��������-1]
         LPMIXERCAPS lpMaxcaps�����ܽṹ
		 typedef struct { 
			 WORD    wMid; //���̱�ʶ��
			 WORD    wPid; //��Ʒ��ʶ��
			 MMVERSION vDriverVersion; //�豸���,major (high byte), minor (low byte)
			 CHAR    szPname[MAXPNAMELEN]; //��Ʒ��
			 DWORD   fdwSupport; //�������������֧����Ϣ,����û�ж���
			 DWORD   cDestinations; //���Ƶ����������ƵĿ����(Audio Line Destinations)������
		 } MIXERCAPS; 
����ֵ���ɹ����� TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-13
ʱ  �䣺16:51:14
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
		TRACE(_T("��Ƶ����ID�õ����ʧ��.\n"));
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
		TRACE(_T("�򿪻�Ƶ��ʧ��.\n"));
		::SendMessage(m_hWnd, WM_QUIT, NULL, NULL);
		//::DestroyWindow(m_hWnd);
		return FALSE;
	}

	return TRUE;
}

/*******************************************************************************************************
��������CloseDev
��  �ܣ��رջ�Ƶ��
��  ������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-13
ʱ  �䣺16:54:00
*******************************************************************************************************/
BOOL CMixer::CloseDev()
{
	if(MMSYSERR_NOERROR == mixerClose(m_hMixer))
		return TRUE;
	TRACE(_T("�رջ�Ƶ��ʧ��.\n"));
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
��������GetLineInfo
��  �ܣ��õ�ָ�����͵�Audio Line����Ϣ
��  ����
         DWORD dwFlags��ָ��������
		 typedef struct { 
			DWORD cbStruct; //���ṹ�Ĵ�С
			DWORD dwDestination; //Ŀ���ߵ�����,��Χ[0, MIXERCAPS�еĳ�ԱcDestinations-1]
			DWORD dwSource; //���ԱdwDestination����ϵ��Դ��Ƶ�ߵ�����,
			                //����ʶMIXER_GETLINEINFOF_SOURCE������,
							//���ķ�Χ[0,��ָ��dwDestination��Ŀ���ߵ�����ֵ(��ԱdwConnections)
			DWORD dwLineID; //����ṹ�ı�ʶ��,�����Ժ�Ĳ�ѯ
			DWORD fdwLine; //��Ƶ�ߵ�״̬
			DWORD dwUser; 
			DWORD dwComponentType; //�������
			DWORD cChannels; //ͨ����
			DWORD cConnections; //��ָ����Ŀ���ߵ�������
			DWORD cControls; //��ָ����Ŀ����������Ŀ�����
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
����ֵ���ɹ�����TRUE,���򷵻�FLASE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-14
ʱ  �䣺15:10:26
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
		TRACE(_T("�õ�Line��Ϣʧ��.\n"));
		return FALSE;
	}

	TRACE(_T("Audio Line��Ϣ������:%s\n"), MixerLine.szShortName);
	m_Control.dwLineID = MixerLine.dwLineID;
	m_Control.dwChannelCount = MixerLine.cChannels;
	return TRUE;
}

/*******************************************************************************************************
��������GetControl
��  �ܣ��õ�һ��ָ�����͵Ŀ��Ƶ�����,���� m_Control ��.
��  ����
         DWORD dwFlags�����Ƶ����ͱ�ʶ
����ֵ���ɹ�����TRUE,���򷵻�FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-14
ʱ  �䣺15:05:25
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
		TRACE(_T("�õ�������Ϣʧ��.\n"));
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
��������GetCurrentVolume
��  �ܣ��õ���ǰ������
��  ������
����ֵ����ǰ������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-14
ʱ  �䣺13:58:36
*******************************************************************************************************/
DWORD CMixer::GetCurrentVolume()
{
	m_Control.dwControlID = m_ControlID.dwVolumeID;
	return GetDWORDValue();
}

/*******************************************************************************************************
��������SetCurrentVolume
��  �ܣ����õ�ǰ������
��  ����
         DWORD dwVolume����ǰ������
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-14
ʱ  �䣺14:59:59
*******************************************************************************************************/
BOOL CMixer::SetCurrentVolume(DWORD dwVolume)
{
	m_Control.dwControlID = m_ControlID.dwVolumeID;
	return SetDWORDValue(dwVolume);
}

/*******************************************************************************************************
��������GetDWORDValue
��  �ܣ��õ�һ��DWORDֵ�Ŀ��Ƶĵ�ǰֵ,
        ������Ƶ�ID��ͨ��������m_Control������
��  ������
����ֵ��һ��DWORDֵ�Ŀ��Ƶĵ�ǰֵ
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-14
ʱ  �䣺14:54:26
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
��������SetDWORDValue
��  �ܣ��õ�һ��DWORDֵ�Ŀ��Ƶĵ�ǰֵ,
        ������Ƶ�ID��ͨ��������m_Control������
��  ������
����ֵ���ɹ�����TRUE,ʧ�ܷ���FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-14
ʱ  �䣺14:56:26
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
		TRACE(_T("�õ�LineInfo:\n"));
		TRACE(_T("Ŀ����Ƶ�ߵ�����:MIXERLINE.dwDestination = %d\n"), pmxl->dwDestination);
		TRACE(_T("Դ��Ƶ�ߵ�����:MIERLINE.dwSource = %d\n"), pmxl->dwSource);
		TRACE(_T("ͨ����:MIERLINE.cChannels = %d\n"), pmxl->cChannels);
		TRACE(_T("������:MIERLINE.cConnections = %d\n"), pmxl->cConnections);
		TRACE(_T("������:MIERLINE.cControls = %d\n"), pmxl->cControls);
		TRACE(_T("��Ƶ����MIERLINE.szName = %s\n"), pmxl->szName);
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
		TRACE(_T("�õ�LineControlsInfo:\n"));
		TRACE(_T("MIXERLINECONTROLS.cControls = %s\n"), pmxlc->cControls);
		for(int i = 0; i < pmxlc->cControls; i++)
		{
			TRACE(_T("��%d������.������:%s\n"), i + 1, (MIXERCONTROL*)(pmxlc->pamxctrl + i)->szName);
		}
	}
		return result;
}
