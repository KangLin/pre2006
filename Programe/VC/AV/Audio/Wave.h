/*******************************************************************************************************
文件名：Wave.h
功  能：音频处理类头文件
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-7
时  间：12:19:22
*******************************************************************************************************/

#if !defined(AFX_WAVEIN_H__FD319B78_A42C_404D_A46A_787BD557E0F5__INCLUDED_)
#define AFX_WAVEIN_H__FD319B78_A42C_404D_A46A_787BD557E0F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mixer.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm")

class CWave 
{
public:
	CWave();
	virtual ~CWave();

protected:

	WAVEFORMATEX m_tagDefaultWaveFormat;
	HWAVE m_hWave;

};

class CWaveIn : public CWave
{
public:		
	CWaveIn();
	virtual ~CWaveIn();
	INT GetNumDevs();
	MMRESULT GetDevCaps(UINT uDeviceID, LPWAVEINCAPS pwic);
	BOOL OpenDev(LPVOID lpUserData, UINT uDeviceID = WAVE_MAPPER, LPWAVEFORMATEX pwfx = NULL);
	BOOL CloseDev();
	BOOL StartRecord();
	BOOL StopRecord();
	
public:
	//缓存大小
	enum{BUFFSIZE = 1024, BUFFNUM = 10};

private:
	BOOL FreeBuff();
	BOOL AllocBuff();

	char* m_pBuff[BUFFNUM];
	WAVEHDR m_pWAVEHDR[BUFFNUM];   //注意:这个值传给录音线程后不能被释放,
	                               //因为录音线程过程中一直需要它,
	                               //直到调用  waveInUnprepareHeader 才能释放.
	                               //否则在调用waveInReset中会出错
	HWAVEIN m_hWaveIn;
	INT m_iErrNo;
	DWORD m_dwThreadID;
};
//录音线程
extern "C" DWORD WINAPI waveInThreadProc(LPVOID lpParameter);
//在外部文件中定义
extern "C" void WINAPI OnWaveInDataProc(char* lpData, DWORD dwSize, LPVOID lpParameter);

class CWaveOut : public CWave
{
public:
	BOOL OpenDev(UINT uDeviceID = WAVE_MAPPER, LPWAVEFORMATEX pwfx = NULL);
	BOOL Pause();
	BOOL CloseDev();
	BOOL Play(char * pData, UINT uSize);
	MMRESULT GetDevCaps(UINT uDeviceID, LPWAVEOUTCAPS pwoc);
	INT GetNumDevs();
	CWaveOut();
	virtual ~CWaveOut();

public:
	CMixer m_Mixer;        //混频器

private:
	INT m_iErrNo;
	HWAVEOUT m_hWaveOut;
	BOOL m_bPlaying;       //设备是否正在播放
	DWORD m_dwThreadID;    //
};

//播放线程
DWORD WINAPI waveOutThreadProc(LPVOID lpParameter);

#endif // !defined(AFX_WAVEIN_H__FD319B78_A42C_404D_A46A_787BD557E0F5__INCLUDED_)
