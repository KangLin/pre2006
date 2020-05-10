/*******************************************************************************************************
�ļ�����Wave.cpp
��  �ܣ���Ƶ����ʵ���ļ�
��  ��: 
        ¼��:
		1������һ��CWaveIn����:CWaveIn m_WaveIn;
		2����¼���豸������  m_WaveIn.OpenDev(this);
		3����ʼ¼����          m_WaveIn.StartRecord();
		4������¼�����ݣ����ⲿ�ļ���ʵ�ֺ�����
		   OnWaveInDataProc(char* lpData, DWORD dwSize, LPVOID lpParameter);
		5��ֹͣ¼����          m_WaveIn.StopRecord();
		6���ر�¼���豸��      m_WaveIn.CloseDev();
		���ţ�
		1������һ��CWaveOut����CWaveOut m_WaveOut;
		2���򿪲����豸��        m_WaveOut.OpenDev();
		3������������            m_WaveOut.Play(pData, uSize);
		4����ͣ����/���¿�ʼ��   m_WaveOut.Pause();
		5���رղ����豸��        m_WaveOut.Close();
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺12:19:00
*******************************************************************************************************/

#include "stdafx.h"
#include "Wave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*******************************************************************************************************
 CWave ��
*******************************************************************************************************/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWave::CWave()
{
	//����������
	m_tagDefaultWaveFormat.wFormatTag = WAVE_FORMAT_PCM; 
	//ͨ����
	m_tagDefaultWaveFormat.nChannels = 2;                
	//������,��λ(H),����������һ����Ϊ 8.0 kHz, 11.025 kHz, 22.05 kHz, and 44.1 kHz
	m_tagDefaultWaveFormat.nSamplesPerSec = 8000;        
	//����λ��
	m_tagDefaultWaveFormat.wBitsPerSample = 16;          
	//ƽ��������
	m_tagDefaultWaveFormat.nAvgBytesPerSec = m_tagDefaultWaveFormat.nSamplesPerSec \
		                               * (m_tagDefaultWaveFormat.wBitsPerSample / 8); 
	m_tagDefaultWaveFormat.nBlockAlign = m_tagDefaultWaveFormat.nChannels \
		                       * (m_tagDefaultWaveFormat.wBitsPerSample / 8);
	//�� WAVEFORMATEX �ṹ�����ӵı�ʶ��Ϣ,��λΪ�ֽ�.
	//�����Ϣ�����ڷ�PCM��ʽ�еĴ洢 wFormatTag ��չ��MMSYSERR_NOERROR��
	//��PCM��ʽ�У����ֵ�����ԡ�
	m_tagDefaultWaveFormat.cbSize = 0;
}

CWave::~CWave()
{

}

/*******************************************************************************************************
��������SetDefaultWaveFormat
��  �ܣ�����Ĭ����Ƶ��ʽ
��  ������
����ֵ������TRUE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-12
ʱ  �䣺12:07:44
*******************************************************************************************************/
//DEL BOOL CWave::SetDefaultWaveFormat()
//DEL {
//DEL 
//DEL 
//DEL 
//DEL 	return TRUE;
//DEL }


/*******************************************************************************************************
 CWaveIn ��
*******************************************************************************************************/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWaveIn::CWaveIn()
{
	m_hWaveIn = NULL;
}

CWaveIn::~CWaveIn()
{
	CloseDev();
	//FreeBuff();
}

/*******************************************************************************************************
��������AllocBuff
��  �ܣ����仺��ռ�
��  ������
����ֵ���������ɹ�����TRUE,����,����FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:27:26
*******************************************************************************************************/
BOOL CWaveIn::AllocBuff()
{
	for(int i = 0; i < BUFFNUM; i++)
	{
		m_pBuff[i] = new char[BUFFSIZE];
		if(m_pBuff[i] == NULL)
		{
			TRACE(_T("������%d����Ƶ���뻺�����\n"), i);
			return FALSE;
		}
		else
		{
			TRACE(_T("������%d����Ƶ���뻺�档\n"), i);
		}
	}

	return TRUE;
}

/*******************************************************************************************************
��������FreeBuff
��  �ܣ��ͷŷ���Ļ���ռ�
��  ������
����ֵ������ɹ�����TRUE�����򷵻�FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:28:09
*******************************************************************************************************/
BOOL CWaveIn::FreeBuff()
{
	for(int i = 0; i < BUFFNUM; i++)
	{
		if(m_pBuff[i])
		{
			delete m_pBuff[i];
		}
		else
		{
			TRACE(_T("��%d��¼�����治�ܱ��ͷ�.\n"), i);
		}
	}
	return TRUE;
}

/*******************************************************************************************************
��������GetNumDevs
��  �ܣ��õ�ϵͳ�������豸������
��  ������
����ֵ��ϵͳ�������豸������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:29:04
*******************************************************************************************************/
INT CWaveIn::GetNumDevs()
{
	return waveInGetNumDevs();
}

/*******************************************************************************************************
��������GetDevCaps
��  �ܣ��õ�ָ���豸������
��  ����
         UINT uDeviceID���豸�ı�ʶ��
         LPWAVEINCAPS pwic��WAVEINCAPS �ṹָ��
����ֵ��MMRESULT���ɹ� MMSYSERR_NOERROR�����򷵻ش���ֵ
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:39:17
*******************************************************************************************************/
MMRESULT CWaveIn::GetDevCaps(UINT uDeviceID, LPWAVEINCAPS pwic)
{
	return waveInGetDevCaps(uDeviceID, pwic, sizeof(WAVEINCAPS));
}

/*******************************************************************************************************
��������OpenDev
��  �ܣ���һ���豸�������豸����������BUFFNUM�黺��
��  ����DWORD lpUserData�������̵߳��û�����,
                          �����߳� waveInThreadProc �е��ⲿ����
						  OnWaveInDataProc(pWH->lpData, pWH->dwBytesRecorded, lpParameter);
        UINT uDeviceID��Ҫ�򿪵��豸��ʶ����
		                Ĭ��Ϊ WAVE_MAPPER,
		                ��ϵͳ�Զ��������ʺ�ָ����Ƶ��ʽ�������豸
		LPWAVEFORMATEX pwfx����Ƶ���ݸ�ʽ WAVEFORMATEX �ṹָ��
        
����ֵ���ɹ� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:40:16
*******************************************************************************************************/
BOOL CWaveIn::OpenDev(LPVOID lpUserData,
					  UINT uDeviceID,
					  LPWAVEFORMATEX pwfx
					  )
{
	if(pwfx == NULL)
	{   //��Ĭ����Ƶ��ʽ
		pwfx = &m_tagDefaultWaveFormat;
	}

	//����Ĭ���߳�
	HANDLE hThread = ::CreateThread(NULL, NULL, waveInThreadProc, lpUserData, NULL, &m_dwThreadID);
	if(NULL == hThread)
	{
		TRACE(_T("����Ĭ����Ƶ�����߳�ʧ�ܡ�\n"));
		return FALSE;
	}
	TRACE(_T("����Ĭ����Ƶ�����̳߳ɹ����߳�ID=%x��\n"), m_dwThreadID);
	CloseHandle(hThread);

	//���仺��
	if(!AllocBuff())
	{
		TRACE(_T("����¼������ʧ��.\n"));
		return FALSE;
	}
	
	//����Ƶ�����豸
	m_iErrNo = waveInOpen(&m_hWaveIn, uDeviceID, pwfx, m_dwThreadID, NULL, CALLBACK_THREAD);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("����Ƶ�����豸ʧ��.\n"));
		return FALSE;
	}

	//------------------------------------------------------------------------
	//��������� ===�ѻ��淢�͵������豸��������=== ���ܵ�����
	//
	
	for(int i = 0; i < BUFFNUM; i++)
	{   //���ýṹ��
		m_pWAVEHDR[i].lpData = m_pBuff[i];
		m_pWAVEHDR[i].dwBufferLength = BUFFSIZE;
		m_pWAVEHDR[i].dwFlags = 0;
		//Ϊ��Ƶ����׼������
		//�����������ǰ����������ֵ����Ҫ���ã��ұ���dwFlags = 0
		m_iErrNo = waveInPrepareHeader(m_hWaveIn, &m_pWAVEHDR[i], sizeof(WAVEHDR));
		if(m_iErrNo != MMSYSERR_NOERROR)
		{
			TRACE(_T("��Ƶ�����%d�黺��׼��ʧ��.\n"), i);
			return FALSE;
		}
		//����һ�����뻺��������豸��������
		//����黺��������Ӧ�ó���ᱻ֪ͨ,�յ�WIN_DATA��Ϣ��
		//WAVEHDR �ṹ�� dwFlags �� WHDR_DONE λ�����ã�
		//�� m_pWAVEHDR.dwFlags |= WHDR_DONE
		m_iErrNo = waveInAddBuffer(m_hWaveIn, &m_pWAVEHDR[i], sizeof(WAVEHDR));
		if(m_iErrNo != MMSYSERR_NOERROR)
		{
			TRACE(_T("��%d����Ƶ���뻺����뵽����ʧ��\n"), i);
			return FALSE;
		}
	}

	//
	//��������� ===�ѻ��淢�͵������豸��������=== ���ܵ�����
	//------------------------------------------------------------------------

	/*
	if(!CMixer::OpenDev((HMIXEROBJ)m_hWaveIn, MIXER_OBJECTF_HWAVEIN))
		return FALSE;

	/*******************************************************************************************************
     MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE
	 MIXERLINE_COMPONENTTYPE_DST_WAVEIN 
	*******************************************************************************************************/
	/*if(!GetLineInfo())
		return FALSE;

	if(!GetControl(MIXERCONTROL_CONTROLTYPE_VOLUME))
		return FALSE;
    */

	return TRUE;
}

/*******************************************************************************************************
��������CloseDev
��  �ܣ��ر������豸
��  ������
����ֵ���ɹ����� TRUE�����򣬷��� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:45:07
*******************************************************************************************************/
BOOL CWaveIn::CloseDev()
{
	if(!m_hWaveIn)
	   return TRUE;
		
	m_iErrNo = ::waveInReset(m_hWaveIn);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("���������뻺��ʧ��.waveInReset\n"));
		return FALSE;
	}

	for(int i = 0; i < BUFFNUM; i++)
	{
		m_pWAVEHDR[i].lpData = m_pBuff[i];
		m_pWAVEHDR[i].dwBufferLength = BUFFSIZE;
		m_pWAVEHDR[i].dwFlags = 0;
		m_iErrNo = waveInUnprepareHeader(m_hWaveIn, &m_pWAVEHDR[i], sizeof(WAVEHDR));
		if(m_iErrNo != MMSYSERR_NOERROR)
		{
			TRACE(_T("�ͷ�¼�������%d��waveInUnprepareHeaderʧ��.\n"), i);
			return FALSE;
		}
	}
	
	if(!FreeBuff())
	{
		TRACE(_T("�ͷ�¼������ʧ��.\n"));
		return FALSE;
	}

	//::PostThreadMessage(m_dwThreadID, WM_QUIT, NULL, NULL);
	//Sleep(500);
	m_iErrNo = waveInClose(m_hWaveIn);	
    if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("�ر�¼���豸����.\n"));
		return FALSE;
	}
	
	m_hWaveIn = NULL;

	return TRUE;
}

/*******************************************************************************************************
��������StartRecord
��  �ܣ���ʼ¼��
��  ������
����ֵ���ɹ����� TRUE�����򣬷��� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:50:24
*******************************************************************************************************/
BOOL CWaveIn::StartRecord()
{
	m_iErrNo = waveInStart(m_hWaveIn);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("¼����ʼ����.\n"));
		return FALSE;
	}

	return TRUE;	
}

/*******************************************************************************************************
��������StopRecord
��  �ܣ�ֹͣ¼��
˵  ���������¼����������л��л���飬
		��ô��ǰ����黺�潫������Ϊ WAVEIN_DONE,
		���г�Ա dwBytesRecorded ������ʹ�û��������,
		�������յĻ�����Ա�����¼�����������
��  ������
����ֵ���ɹ����� TRUE�����򣬷��� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺11:50:45
*******************************************************************************************************/
BOOL CWaveIn::StopRecord()
{
	m_iErrNo = waveInStop(m_hWaveIn);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("ֹͣ¼������ʧ��.\n"));
		return FALSE;
	}

	return m_iErrNo;
}


/*******************************************************************************************************
  CWaveOut ��
*******************************************************************************************************/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWaveOut::CWaveOut()
{
	m_hWaveOut = NULL;
	m_bPlaying = FALSE;
}

CWaveOut::~CWaveOut()
{
	CloseDev();
}

/*******************************************************************************************************
��������GetNumDevs
��  �ܣ��õ�����豸������
��  ������
����ֵ������豸������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺12:21:07
*******************************************************************************************************/
INT CWaveOut::GetNumDevs()
{
	return waveOutGetNumDevs();
}

/*******************************************************************************************************
��������GetDevCaps
��  �ܣ��õ�����豸������
��  ����
         UINT uDeviceID������豸�ı�ʶ��
         LPWAVEOUTCAPS pwoc������豸�������ṹ WAVEOUTCAPS ��ָ��
����ֵ���ɹ�MMSYSERR_NOERROR ���򷵻�һ������ֵ
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺12:24:17
*******************************************************************************************************/
MMRESULT CWaveOut::GetDevCaps(UINT uDeviceID, LPWAVEOUTCAPS pwoc)
{
	return waveOutGetDevCaps(uDeviceID, pwoc, sizeof(WAVEOUTCAPS));
}

/*******************************************************************************************************
��������OpenDev
��  �ܣ�����Ƶ����豸
��  ����
         UINT uDeviceID������豸�ı�ʶ��,Ĭ��Ϊ WAVE_MAPPER,ϵͳ�Զ���ѯָ����Ƶ��ʽ������豸
         LPWAVEFORMATEX pwfx����Ƶ��ʽָ��
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-7
ʱ  �䣺19:30:59
*******************************************************************************************************/
BOOL CWaveOut::OpenDev(UINT uDeviceID, LPWAVEFORMATEX pwfx)
{
	if(pwfx == NULL)
		pwfx = &m_tagDefaultWaveFormat;
	
	HANDLE hThread = ::CreateThread(NULL, NULL, waveOutThreadProc, NULL, NULL, &m_dwThreadID);
	if(hThread)
	{
		TRACE(_T("Ĭ����Ƶ����߳̽����ɹ�.�߳�ID=%x\n"), m_dwThreadID);
	}
	else 
	{
		TRACE(_T("Ĭ����Ƶ����߳̽���ʧ��.\n"));
		return FALSE;
	}	
    CloseHandle(hThread);
	m_iErrNo = waveOutOpen(&m_hWaveOut, uDeviceID, pwfx, m_dwThreadID, NULL, CALLBACK_THREAD);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("��Ƶ����豸��ʧ��.\n"));
		return FALSE;
	}

	//�򿪻�Ƶ��������������
	if(!m_Mixer.OpenDev((HMIXEROBJ)m_hWaveOut, MIXER_OBJECTF_HWAVEOUT))
		return FALSE;

	/*******************************************************************************************************
     MIXERLINE_COMPONENTTYPE_DST_SPEAKERS:�õ� Volume
	 MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT:�õ� Wave
	*******************************************************************************************************/
	if(!m_Mixer.GetLineInfo(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS))
		return FALSE;

	if(!m_Mixer.GetControl(MIXERCONTROL_CONTROLTYPE_VOLUME))
		return FALSE;

	return TRUE;
}

/*******************************************************************************************************
��������Play
��  �ܣ���ʼ����
��  ����
         char *pData��ָ������Ƶ���ݿ��ָ��
         UINT uSize��������Ƶ���ݿ�Ĵ�С
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-8
ʱ  �䣺10:20:54
*******************************************************************************************************/
BOOL CWaveOut::Play(char *pData, UINT uSize)
{
	//δ��Open�������豸
	if(m_hWaveOut == NULL)
	{
#ifdef _DEBUG	
		OpenDev();
#else
		return FALSE;
#endif
	}

	LPWAVEHDR pwh = new WAVEHDR;//���·���һ���ڴ�(�ڲ��Ž�����ɾ��)
	if(pwh == NULL)
		return FALSE;
	char* p = new char[uSize];//���·���һ���ڴ�(�ڲ��Ž�����ɾ��)
	if(p == NULL)
	{
		delete pwh;
		return FALSE;
	}
	CopyMemory(p, pData, uSize);
	ZeroMemory(pwh, sizeof(WAVEHDR));
	pwh->dwBufferLength = uSize;
	pwh->lpData = p;
    //pwh->dwFlags = 0;//��ǰ������0
	m_iErrNo = waveOutPrepareHeader(m_hWaveOut, pwh, sizeof(WAVEHDR));
    if(m_iErrNo != MMSYSERR_NOERROR)
	{
		delete pwh;
		delete []p;
		return FALSE;
	}
	m_iErrNo = waveOutWrite(m_hWaveOut, pwh, sizeof(WAVEHDR));
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		delete pwh;
		delete []p;
		return FALSE;
	}
	
	m_bPlaying = TRUE;
	
	return TRUE;
}

/*******************************************************************************************************
��������Pause
��  �ܣ���ͣ�����¿�ʼ����
��  ������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-8
ʱ  �䣺10:24:30
*******************************************************************************************************/
BOOL CWaveOut::Pause()
{
	if(m_bPlaying)
	{
		m_iErrNo = waveOutPause(m_hWaveOut);
		m_bPlaying = !m_bPlaying;
	}
	else
	{
		m_iErrNo = waveOutRestart(m_hWaveOut);
		m_bPlaying = !m_bPlaying;
	}

	if(m_iErrNo == MMSYSERR_NOERROR)
		return TRUE;
	else
		return FALSE;
}

/*******************************************************************************************************
��������CloseDev
��  �ܣ��ر���Ƶ�豸
˵  �����ر��豸ǰҪ�ȵ��� waveOutReset ����ֹͣ���ţ�
        ����ʶ���Ŷ����е�δ���ŵ����ݿ�Ϊ�Ѳ��ţ�
		���ܵ��� waveOutClose ��������������
		���ڵ��� waveOutReset ��������ʱһ��,���̴߳�������Ϣ,
		����ر��豸��,���߳��е���Ϣû������,�����̵߳���ϢWOM_DONE����ʱ,
		����waveOutUnprepareHeader����ʱ,�����Ч,����.
��  ������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-8
ʱ  �䣺10:25:15
*******************************************************************************************************/
BOOL CWaveOut::CloseDev()
{
	if(m_hWaveOut == NULL)
		return TRUE;
	m_iErrNo = waveOutReset(m_hWaveOut);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("CloseDev��waveOutResetʧ��.\n"));
		return FALSE;
	}
	Sleep(500);
	m_iErrNo = waveOutClose(m_hWaveOut);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("�ر�����豸ʧ��.\n"));
		return FALSE;
	}
	else
	{
		TRACE(_T("�ɹ��ر�����豸.\n"));
		m_hWaveOut = NULL;
	}
	return TRUE;
}


/*******************************************************************************************************
 �ص�����
*******************************************************************************************************/

/*******************************************************************************************************
��������waveOutThreadProc
��  �ܣ���Ƶ����̻߳ص��ú���
��  ����
         LPVOID lpParameter�������̵߳Ĳ���,����δ��
����ֵ���ɹ��˳�����0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-8
ʱ  �䣺11:03:35
*******************************************************************************************************/
DWORD WINAPI waveOutThreadProc(LPVOID lpParameter)
{
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		switch(msg.message)
		{
		case WOM_DONE:
			{	
				WAVEHDR* pwh = (WAVEHDR*)msg.lParam;
				if((NULL == pwh) || ((HWAVEOUT)msg.wParam == NULL))
					break;
				waveOutUnprepareHeader((HWAVEOUT)msg.wParam, pwh, sizeof(WAVEHDR));
				delete []pwh->lpData;//ɾ��Play����ʱ������ڴ�
				delete pwh;          //ɾ��Play����ʱ������ڴ�
				TRACE(_T("������һ����Ƶ����,�߳��յ�WOM_DONE��Ϣ.\n"));
			}
			break;			
		case WOM_CLOSE:
			TRACE(_T("�߳��յ� WOM_CLOSE ��Ϣ,��Ƶ�����߳���ֹ��\n"));			
			return 0;
		}
	}
	TRACE(_T("��Ƶ�����߳���ֹ��\n"));
	return 0;
}

/*******************************************************************************************************
��������waveInThreadProc
��  �ܣ���Ƶ¼���߳�
��  ����
         LPVOID lpParameter�������̵߳��û�����,��OpenDev����lpUserData�д���
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-9
ʱ  �䣺14:17:43
*******************************************************************************************************/
extern "C" DWORD WINAPI waveInThreadProc(LPVOID lpParameter)
{
    MSG msg;
	while(::GetMessage(&msg, NULL, NULL, NULL))
	{
		switch(msg.message)
		{
		case WIM_DATA:
			{
#ifdef _DEBUG 
				static int i;
				TRACE(_T("¼��,���ڴ���¼������:%d.\n"), i);
#endif
				WAVEHDR* pWH=(WAVEHDR*)msg.lParam;
				
				if(0 == pWH->dwBytesRecorded || NULL == pWH)
					break;

				try
				{
				//���ⲿ�ļ���ʵ�֣�
				//���ڴ���¼�Ƶ���Ƶ����
				OnWaveInDataProc(pWH->lpData, pWH->dwBytesRecorded, lpParameter);
				}
				catch(...)
				{
					TRACE(_T("CWaveIn::waveInThreadProc��Ƶ�������.\n"));
					return 1;
				};
				waveInPrepareHeader((HWAVEIN)msg.wParam, pWH, sizeof(WAVEHDR));
				waveInAddBuffer((HWAVEIN)msg.wParam, pWH, sizeof(WAVEHDR));
#ifdef _DEBUG
				TRACE(_T("¼��,���ڴ���¼�����ݽ���%d.\n"), i++);
#endif
			}
			break;
		case WIM_CLOSE:
			TRACE(_T("¼���߳����յ�WIM_CLOSE��Ϣ���˳�.\n"));
			return 0;
		}//switch(msg.message)
	}//while(GetMessage(&msg,0,0,0))	
	TRACE(_T("¼���߳���ֹ.\n"));
	return 0;
}

//DEL BOOL CWaveIn::GetLineInfo()
//DEL {
//DEL 	MIXERLINE MixerLine;
//DEL 	memset( &MixerLine, 0, sizeof(MIXERLINE) );
//DEL 	MixerLine.cbStruct = sizeof(MIXERLINE);
//DEL 	MixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
//DEL     MMRESULT mmResult = mixerGetLineInfo( (HMIXEROBJ)m_hMixer, &MixerLine, 
//DEL 		MIXER_GETLINEINFOF_COMPONENTTYPE );
//DEL 	if ( mmResult != MMSYSERR_NOERROR )
//DEL 	{	
//DEL 		return FALSE;
//DEL 	}
//DEL 
//DEL 	MIXERLINE MicrophoneLine;
//DEL 	// Retrieving Microphone Source Line
//DEL 	for ( UINT uLine = 0; uLine < MixerLine.cConnections; uLine++ )
//DEL 	{	
//DEL 		memset( &MicrophoneLine, 0, sizeof(MIXERLINE) );
//DEL 		MicrophoneLine.cbStruct = sizeof(MIXERLINE);
//DEL 		MicrophoneLine.dwDestination = MixerLine.dwDestination;
//DEL 		MicrophoneLine.dwSource = uLine;
//DEL 		mmResult = mixerGetLineInfo( (HMIXEROBJ)m_hMixer,
//DEL 			&MicrophoneLine, MIXER_GETLINEINFOF_SOURCE );
//DEL 		if ( mmResult == MMSYSERR_NOERROR )
//DEL 		{
//DEL 			if ( MicrophoneLine.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE )
//DEL 			{
//DEL 				//m_uMicrophoneSourceLineIndex = MicrophoneLine.dwSource;
//DEL 				break;
//DEL 			}
//DEL 		}
//DEL 	}
//DEL 
//DEL 	if(uLine >= MixerLine.cConnections)
//DEL 		return FALSE;
//DEL 	m_Control.dwLineID = MicrophoneLine.dwLineID;
//DEL 
//DEL 	return true;
//DEL }
