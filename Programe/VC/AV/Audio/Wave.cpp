/*******************************************************************************************************
文件名：Wave.cpp
功  能：音频处理实现文件
用  法: 
        录音:
		1、建立一个CWaveIn对象:CWaveIn m_WaveIn;
		2、打开录音设备，调用  m_WaveIn.OpenDev(this);
		3、开始录音：          m_WaveIn.StartRecord();
		4、处理录音数据：在外部文件中实现函数：
		   OnWaveInDataProc(char* lpData, DWORD dwSize, LPVOID lpParameter);
		5、停止录音：          m_WaveIn.StopRecord();
		6、关闭录音设备：      m_WaveIn.CloseDev();
		播放：
		1、建立一个CWaveOut对象：CWaveOut m_WaveOut;
		2、打开播放设备：        m_WaveOut.OpenDev();
		3、播放声音：            m_WaveOut.Play(pData, uSize);
		4、暂停播放/重新开始：   m_WaveOut.Pause();
		5、关闭播放设备：        m_WaveOut.Close();
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-7
时  间：12:19:00
*******************************************************************************************************/

#include "stdafx.h"
#include "Wave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*******************************************************************************************************
 CWave 类
*******************************************************************************************************/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWave::CWave()
{
	//脉冲编码调制
	m_tagDefaultWaveFormat.wFormatTag = WAVE_FORMAT_PCM; 
	//通道数
	m_tagDefaultWaveFormat.nChannels = 2;                
	//采样率,单位(H),脉冲编码调制一服可为 8.0 kHz, 11.025 kHz, 22.05 kHz, and 44.1 kHz
	m_tagDefaultWaveFormat.nSamplesPerSec = 8000;        
	//采样位数
	m_tagDefaultWaveFormat.wBitsPerSample = 16;          
	//平均采样率
	m_tagDefaultWaveFormat.nAvgBytesPerSec = m_tagDefaultWaveFormat.nSamplesPerSec \
		                               * (m_tagDefaultWaveFormat.wBitsPerSample / 8); 
	m_tagDefaultWaveFormat.nBlockAlign = m_tagDefaultWaveFormat.nChannels \
		                       * (m_tagDefaultWaveFormat.wBitsPerSample / 8);
	//在 WAVEFORMATEX 结构后增加的标识信息,单位为字节.
	//这个信息被用于非PCM格式中的存储 wFormatTag 扩展信MMSYSERR_NOERROR。
	//在PCM格式中，这个值被忽略。
	m_tagDefaultWaveFormat.cbSize = 0;
}

CWave::~CWave()
{

}

/*******************************************************************************************************
函数名：SetDefaultWaveFormat
功  能：设置默认音频格式
参  数：无
返回值：返回TRUE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-12
时  间：12:07:44
*******************************************************************************************************/
//DEL BOOL CWave::SetDefaultWaveFormat()
//DEL {
//DEL 
//DEL 
//DEL 
//DEL 	return TRUE;
//DEL }


/*******************************************************************************************************
 CWaveIn 类
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
函数名：AllocBuff
功  能：分配缓存空间
参  数：无
返回值：如果分配成功返回TRUE,否则,返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:27:26
*******************************************************************************************************/
BOOL CWaveIn::AllocBuff()
{
	for(int i = 0; i < BUFFNUM; i++)
	{
		m_pBuff[i] = new char[BUFFSIZE];
		if(m_pBuff[i] == NULL)
		{
			TRACE(_T("建立第%d块音频输入缓存出错。\n"), i);
			return FALSE;
		}
		else
		{
			TRACE(_T("建立第%d块音频输入缓存。\n"), i);
		}
	}

	return TRUE;
}

/*******************************************************************************************************
函数名：FreeBuff
功  能：释放分配的缓存空间
参  数：无
返回值：如果成功返回TRUE，否则返回FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:28:09
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
			TRACE(_T("第%d块录音缓存不能被释放.\n"), i);
		}
	}
	return TRUE;
}

/*******************************************************************************************************
函数名：GetNumDevs
功  能：得到系统中输入设备的数量
参  数：无
返回值：系统中输入设备的数量
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:29:04
*******************************************************************************************************/
INT CWaveIn::GetNumDevs()
{
	return waveInGetNumDevs();
}

/*******************************************************************************************************
函数名：GetDevCaps
功  能：得到指定设备的描述
参  数：
         UINT uDeviceID：设备的标识符
         LPWAVEINCAPS pwic：WAVEINCAPS 结构指针
返回值：MMRESULT，成功 MMSYSERR_NOERROR，否则返回错误值
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:39:17
*******************************************************************************************************/
MMRESULT CWaveIn::GetDevCaps(UINT uDeviceID, LPWAVEINCAPS pwic)
{
	return waveInGetDevCaps(uDeviceID, pwic, sizeof(WAVEINCAPS));
}

/*******************************************************************************************************
函数名：OpenDev
功  能：打开一个设备，并向设备驱动程序发送BUFFNUM块缓存
参  数：DWORD lpUserData：传给线程的用户数据,
                          用于线程 waveInThreadProc 中的外部函数
						  OnWaveInDataProc(pWH->lpData, pWH->dwBytesRecorded, lpParameter);
        UINT uDeviceID：要打开的设备标识符，
		                默认为 WAVE_MAPPER,
		                由系统自动查找最适合指定音频格式的输入设备
		LPWAVEFORMATEX pwfx：音频数据格式 WAVEFORMATEX 结构指针
        
返回值：成功 TRUE，否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:40:16
*******************************************************************************************************/
BOOL CWaveIn::OpenDev(LPVOID lpUserData,
					  UINT uDeviceID,
					  LPWAVEFORMATEX pwfx
					  )
{
	if(pwfx == NULL)
	{   //用默认音频格式
		pwfx = &m_tagDefaultWaveFormat;
	}

	//建立默认线程
	HANDLE hThread = ::CreateThread(NULL, NULL, waveInThreadProc, lpUserData, NULL, &m_dwThreadID);
	if(NULL == hThread)
	{
		TRACE(_T("建立默认音频输入线程失败。\n"));
		return FALSE;
	}
	TRACE(_T("建立默认音频输入线程成功，线程ID=%x。\n"), m_dwThreadID);
	CloseHandle(hThread);

	//分配缓存
	if(!AllocBuff())
	{
		TRACE(_T("分配录音缓存失败.\n"));
		return FALSE;
	}
	
	//打开音频输入设备
	m_iErrNo = waveInOpen(&m_hWaveIn, uDeviceID, pwfx, m_dwThreadID, NULL, CALLBACK_THREAD);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("打开音频输入设备失败.\n"));
		return FALSE;
	}

	//------------------------------------------------------------------------
	//以下是完成 ===把缓存发送到输入设备驱动程序=== 功能的语句块
	//
	
	for(int i = 0; i < BUFFNUM; i++)
	{   //设置结构，
		m_pWAVEHDR[i].lpData = m_pBuff[i];
		m_pWAVEHDR[i].dwBufferLength = BUFFSIZE;
		m_pWAVEHDR[i].dwFlags = 0;
		//为音频输入准备缓存
		//调用这个函数前，上面三个值必须要设置，且必须dwFlags = 0
		m_iErrNo = waveInPrepareHeader(m_hWaveIn, &m_pWAVEHDR[i], sizeof(WAVEHDR));
		if(m_iErrNo != MMSYSERR_NOERROR)
		{
			TRACE(_T("音频输入第%d块缓存准备失败.\n"), i);
			return FALSE;
		}
		//发送一块输入缓存给输入设备驱动程序，
		//当这块缓存填满后，应用程序会被通知,收到WIN_DATA消息。
		//WAVEHDR 结构的 dwFlags 的 WHDR_DONE 位被设置，
		//即 m_pWAVEHDR.dwFlags |= WHDR_DONE
		m_iErrNo = waveInAddBuffer(m_hWaveIn, &m_pWAVEHDR[i], sizeof(WAVEHDR));
		if(m_iErrNo != MMSYSERR_NOERROR)
		{
			TRACE(_T("第%d块音频输入缓存加入到队列失败\n"), i);
			return FALSE;
		}
	}

	//
	//以上是完成 ===把缓存发送到输入设备驱动程序=== 功能的语句块
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
函数名：CloseDev
功  能：关闭输入设备
参  数：无
返回值：成功返回 TRUE，否则，返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:45:07
*******************************************************************************************************/
BOOL CWaveIn::CloseDev()
{
	if(!m_hWaveIn)
	   return TRUE;
		
	m_iErrNo = ::waveInReset(m_hWaveIn);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("重设置输入缓存失败.waveInReset\n"));
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
			TRACE(_T("释放录音缓存第%d块waveInUnprepareHeader失败.\n"), i);
			return FALSE;
		}
	}
	
	if(!FreeBuff())
	{
		TRACE(_T("释放录音缓存失败.\n"));
		return FALSE;
	}

	//::PostThreadMessage(m_dwThreadID, WM_QUIT, NULL, NULL);
	//Sleep(500);
	m_iErrNo = waveInClose(m_hWaveIn);	
    if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("关闭录音设备出错.\n"));
		return FALSE;
	}
	
	m_hWaveIn = NULL;

	return TRUE;
}

/*******************************************************************************************************
函数名：StartRecord
功  能：开始录音
参  数：无
返回值：成功返回 TRUE，否则，返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:50:24
*******************************************************************************************************/
BOOL CWaveIn::StartRecord()
{
	m_iErrNo = waveInStart(m_hWaveIn);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("录音开始错误.\n"));
		return FALSE;
	}

	return TRUE;	
}

/*******************************************************************************************************
函数名：StopRecord
功  能：停止录音
说  明：如果在录音缓存队列中还有缓存块，
		那么当前的这块缓存将被设置为 WAVEIN_DONE,
		其中成员 dwBytesRecorded 包含已使用缓存的数量,
		而其它空的缓存块仍保留在录音缓存队列中
参  数：无
返回值：成功返回 TRUE，否则，返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：11:50:45
*******************************************************************************************************/
BOOL CWaveIn::StopRecord()
{
	m_iErrNo = waveInStop(m_hWaveIn);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("停止录音操作失败.\n"));
		return FALSE;
	}

	return m_iErrNo;
}


/*******************************************************************************************************
  CWaveOut 类
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
函数名：GetNumDevs
功  能：得到输出设备的数量
参  数：无
返回值：输出设备的数量
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：12:21:07
*******************************************************************************************************/
INT CWaveOut::GetNumDevs()
{
	return waveOutGetNumDevs();
}

/*******************************************************************************************************
函数名：GetDevCaps
功  能：得到输出设备的描述
参  数：
         UINT uDeviceID：输出设备的标识符
         LPWAVEOUTCAPS pwoc：输出设备的描述结构 WAVEOUTCAPS 的指针
返回值：成功MMSYSERR_NOERROR 否则返回一个错误值
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：12:24:17
*******************************************************************************************************/
MMRESULT CWaveOut::GetDevCaps(UINT uDeviceID, LPWAVEOUTCAPS pwoc)
{
	return waveOutGetDevCaps(uDeviceID, pwoc, sizeof(WAVEOUTCAPS));
}

/*******************************************************************************************************
函数名：OpenDev
功  能：打开音频输出设备
参  数：
         UINT uDeviceID：输出设备的标识符,默认为 WAVE_MAPPER,系统自动查询指定音频格式的输出设备
         LPWAVEFORMATEX pwfx：音频格式指针
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-7
时  间：19:30:59
*******************************************************************************************************/
BOOL CWaveOut::OpenDev(UINT uDeviceID, LPWAVEFORMATEX pwfx)
{
	if(pwfx == NULL)
		pwfx = &m_tagDefaultWaveFormat;
	
	HANDLE hThread = ::CreateThread(NULL, NULL, waveOutThreadProc, NULL, NULL, &m_dwThreadID);
	if(hThread)
	{
		TRACE(_T("默认音频输出线程建立成功.线程ID=%x\n"), m_dwThreadID);
	}
	else 
	{
		TRACE(_T("默认音频输出线程建立失败.\n"));
		return FALSE;
	}	
    CloseHandle(hThread);
	m_iErrNo = waveOutOpen(&m_hWaveOut, uDeviceID, pwfx, m_dwThreadID, NULL, CALLBACK_THREAD);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("音频输出设备打开失败.\n"));
		return FALSE;
	}

	//打开混频器（调整音量）
	if(!m_Mixer.OpenDev((HMIXEROBJ)m_hWaveOut, MIXER_OBJECTF_HWAVEOUT))
		return FALSE;

	/*******************************************************************************************************
     MIXERLINE_COMPONENTTYPE_DST_SPEAKERS:得到 Volume
	 MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT:得到 Wave
	*******************************************************************************************************/
	if(!m_Mixer.GetLineInfo(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS))
		return FALSE;

	if(!m_Mixer.GetControl(MIXERCONTROL_CONTROLTYPE_VOLUME))
		return FALSE;

	return TRUE;
}

/*******************************************************************************************************
函数名：Play
功  能：开始播放
参  数：
         char *pData：指向波形音频数据块的指针
         UINT uSize：波形音频数据块的大小
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-8
时  间：10:20:54
*******************************************************************************************************/
BOOL CWaveOut::Play(char *pData, UINT uSize)
{
	//未用Open函数打开设备
	if(m_hWaveOut == NULL)
	{
#ifdef _DEBUG	
		OpenDev();
#else
		return FALSE;
#endif
	}

	LPWAVEHDR pwh = new WAVEHDR;//重新分配一块内存(在播放结束后删除)
	if(pwh == NULL)
		return FALSE;
	char* p = new char[uSize];//重新分配一块内存(在播放结束后删除)
	if(p == NULL)
	{
		delete pwh;
		return FALSE;
	}
	CopyMemory(p, pData, uSize);
	ZeroMemory(pwh, sizeof(WAVEHDR));
	pwh->dwBufferLength = uSize;
	pwh->lpData = p;
    //pwh->dwFlags = 0;//在前面已置0
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
函数名：Pause
功  能：暂停或重新开始播放
参  数：无
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-8
时  间：10:24:30
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
函数名：CloseDev
功  能：关闭音频设备
说  明：关闭设备前要先调用 waveOutReset 函数停止播放，
        并标识播放队列中的未播放的数据块为已播放，
		才能调用 waveOutClose 函数。否则会出错。
		而在调用 waveOutReset 函数后延时一会,让线程处理完消息,
		否则关闭设备后,在线程中的消息没处理完,当在线程的消息WOM_DONE处理时,
		调用waveOutUnprepareHeader函数时,句柄无效,死锁.
参  数：无
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-8
时  间：10:25:15
*******************************************************************************************************/
BOOL CWaveOut::CloseDev()
{
	if(m_hWaveOut == NULL)
		return TRUE;
	m_iErrNo = waveOutReset(m_hWaveOut);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("CloseDev中waveOutReset失败.\n"));
		return FALSE;
	}
	Sleep(500);
	m_iErrNo = waveOutClose(m_hWaveOut);
	if(m_iErrNo != MMSYSERR_NOERROR)
	{
		TRACE(_T("关闭输出设备失败.\n"));
		return FALSE;
	}
	else
	{
		TRACE(_T("成功关闭输出设备.\n"));
		m_hWaveOut = NULL;
	}
	return TRUE;
}


/*******************************************************************************************************
 回调函数
*******************************************************************************************************/

/*******************************************************************************************************
函数名：waveOutThreadProc
功  能：音频输出线程回调用函数
参  数：
         LPVOID lpParameter：传给线程的参数,这里未用
返回值：成功退出返回0
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-8
时  间：11:03:35
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
				delete []pwh->lpData;//删除Play调用时分配的内存
				delete pwh;          //删除Play调用时分配的内存
				TRACE(_T("播放完一块音频数据,线程收到WOM_DONE消息.\n"));
			}
			break;			
		case WOM_CLOSE:
			TRACE(_T("线程收到 WOM_CLOSE 消息,音频播放线程终止。\n"));			
			return 0;
		}
	}
	TRACE(_T("音频播放线程终止。\n"));
	return 0;
}

/*******************************************************************************************************
函数名：waveInThreadProc
功  能：音频录入线程
参  数：
         LPVOID lpParameter：传给线程的用户数据,在OpenDev参数lpUserData中传入
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-9
时  间：14:17:43
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
				TRACE(_T("录音,正在处理录音数据:%d.\n"), i);
#endif
				WAVEHDR* pWH=(WAVEHDR*)msg.lParam;
				
				if(0 == pWH->dwBytesRecorded || NULL == pWH)
					break;

				try
				{
				//在外部文件中实现，
				//用于处理录制的音频数据
				OnWaveInDataProc(pWH->lpData, pWH->dwBytesRecorded, lpParameter);
				}
				catch(...)
				{
					TRACE(_T("CWaveIn::waveInThreadProc音频处理错误.\n"));
					return 1;
				};
				waveInPrepareHeader((HWAVEIN)msg.wParam, pWH, sizeof(WAVEHDR));
				waveInAddBuffer((HWAVEIN)msg.wParam, pWH, sizeof(WAVEHDR));
#ifdef _DEBUG
				TRACE(_T("录音,正在处理录音数据结束%d.\n"), i++);
#endif
			}
			break;
		case WIM_CLOSE:
			TRACE(_T("录音线程因收到WIM_CLOSE消息而退出.\n"));
			return 0;
		}//switch(msg.message)
	}//while(GetMessage(&msg,0,0,0))	
	TRACE(_T("录音线程终止.\n"));
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
