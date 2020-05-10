/*******************************************************************************************************
�ļ�����Wave.h
��  �ܣ���Ƶ������ͷ�ļ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺12:19:22
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
	//�����С
	enum{BUFFSIZE = 1024, BUFFNUM = 10};

private:
	BOOL FreeBuff();
	BOOL AllocBuff();

	char* m_pBuff[BUFFNUM];
	WAVEHDR m_pWAVEHDR[BUFFNUM];   //ע��:���ֵ����¼���̺߳��ܱ��ͷ�,
	                               //��Ϊ¼���̹߳�����һֱ��Ҫ��,
	                               //ֱ������  waveInUnprepareHeader �����ͷ�.
	                               //�����ڵ���waveInReset�л����
	HWAVEIN m_hWaveIn;
	INT m_iErrNo;
	DWORD m_dwThreadID;
};
//¼���߳�
extern "C" DWORD WINAPI waveInThreadProc(LPVOID lpParameter);
//���ⲿ�ļ��ж���
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
	CMixer m_Mixer;        //��Ƶ��

private:
	INT m_iErrNo;
	HWAVEOUT m_hWaveOut;
	BOOL m_bPlaying;       //�豸�Ƿ����ڲ���
	DWORD m_dwThreadID;    //
};

//�����߳�
DWORD WINAPI waveOutThreadProc(LPVOID lpParameter);

#endif // !defined(AFX_WAVEIN_H__FD319B78_A42C_404D_A46A_787BD557E0F5__INCLUDED_)
