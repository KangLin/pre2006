/*******************************************************************************************************
�ļ�����Mixer.h
��  �ܣ���Ƶ��ͷ�ļ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-13
ʱ  �䣺16:56:20
*******************************************************************************************************/

#if !defined(AFX_MIXER_H__CE21F5D2_5342_4542_9384_5A1F5CBE703E__INCLUDED_)
#define AFX_MIXER_H__CE21F5D2_5342_4542_9384_5A1F5CBE703E__INCLUDED_

#include <mmsystem.h>

#pragma comment(lib, "winmm")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	WND_CLASS_NAME  "Wave Output Volume Msg Wnd Class"
#define	WND_NAME		"Wave Output Volume Msg Wnd"

class CMixer  
{
public:
	MMRESULT GetLineControls(HMIXEROBJ hmxobj,  LPMIXERLINECONTROLS pmxlc,  DWORD fdwControls );
	MMRESULT GetLineInfo(HMIXEROBJ hmxobj,  LPMIXERLINE pmxl,  DWORD fdwInfo );
    BOOL GetControl(DWORD dwFlags);
	BOOL GetLineInfo(DWORD dwFlags);

	DWORD GetCurrentVolume();
	BOOL SetCurrentVolume(DWORD dwVolume);
	
	BOOL OpenDev(HMIXEROBJ hMixerObj, DWORD dwFlags);
	BOOL CloseDev();
	
	INT GetNumDevs();
	BOOL GetDevCaps(UINT uMxId, LPMIXERCAPS lpMaxcaps);
	
	CMixer();
	virtual ~CMixer();

	static	LRESULT CALLBACK MixerWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
	DWORD GetDWORDValue();
	BOOL SetDWORDValue(DWORD dwValue);	

protected:
	//���ֿ��Ƶ�IDֵ
	struct tagControlID
	{
		DWORD dwVolumeID;     //�������Ƶ�IDֵ
	}m_ControlID;
	
	//����,ע��:�ڶԶԴ˽ṹ����ǰ��Ҫ���ó�ԱdwControlID��ֵ
	struct tagControl 
	{
		DWORD dwLineID;         //Audio Line �� ID ֵ
		DWORD dwControlID;      //���Ƶ�ID,�ڶԴ˽ṹ����ǰ��Ҫ���ñ���Ա��ֵ
		DWORD dwChannelCount;   //���Ƶ�ͨ����
		DWORD dwMinimalValue;   //���Ʒ�Χ����Сֵ
		DWORD dwMaximalValue;   //���Ʒ�Χ�����ֵ
		DWORD dwStepValue;      //���Ʒ�Χ��ÿ����С
	}m_Control;	

protected:
	HMIXER m_hMixer;   //��Ƶ���ľ��
	UINT m_uMixerID;   //��Ƶ����IDֵ
	HWND m_hWnd;       //��Ƶ���ص����ڵľ��
	
};

#endif // !defined(AFX_MIXER_H__CE21F5D2_5342_4542_9384_5A1F5CBE703E__INCLUDED_)
