/*******************************************************************************************************
文件名：Mixer.h
功  能：混频器头文件
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-13
时  间：16:56:20
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
	//各种控制的ID值
	struct tagControlID
	{
		DWORD dwVolumeID;     //音量控制的ID值
	}m_ControlID;
	
	//控制,注意:在对对此结构操作前先要设置成员dwControlID的值
	struct tagControl 
	{
		DWORD dwLineID;         //Audio Line 的 ID 值
		DWORD dwControlID;      //控制的ID,在对此结构操作前先要设置本成员的值
		DWORD dwChannelCount;   //控制的通道数
		DWORD dwMinimalValue;   //控制范围的最小值
		DWORD dwMaximalValue;   //控制范围的最大值
		DWORD dwStepValue;      //控制范围的每步大小
	}m_Control;	

protected:
	HMIXER m_hMixer;   //混频器的句柄
	UINT m_uMixerID;   //混频器的ID值
	HWND m_hWnd;       //混频器回调窗口的句柄
	
};

#endif // !defined(AFX_MIXER_H__CE21F5D2_5342_4542_9384_5A1F5CBE703E__INCLUDED_)
