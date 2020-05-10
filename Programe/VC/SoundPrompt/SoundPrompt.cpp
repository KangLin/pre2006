// SoundPrompt.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "SoundPrompt.h"

#include <atlbase.h>

//�Ȱ�װ������,������ͷ�ļ�Ŀ¼�Ϳ��ļ�Ŀ¼
#include <sapi.h>
#include <sphelper.h>
#pragma comment(lib,"ole32.lib")  //CoInitialize CoCreateInstance��Ҫ����ole32.dll
#pragma comment(lib,"sapi.lib")   //sapi.lib��SDK��libĿ¼,������ȷ����

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*******************************************************************************************************
ȫ�ֱ���
*******************************************************************************************************/
HHOOK g_hHook;        //���Ӿ��
HINSTANCE g_hInstance; //DLL��ʵ��
//CComPtr<ISpVoice> g_pVoice;
ISpVoice* g_pVoice;

static AFX_EXTENSION_MODULE SoundPromptDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
	
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{		
			// Extension DLL one-time initialization
			if (!AfxInitExtensionModule(SoundPromptDLL, hInstance))
				return 0;
			
			// Insert this DLL into the resource chain
			// NOTE: If this Extension DLL is being implicitly linked to by
			//  an MFC Regular DLL (such as an ActiveX Control)
			//  instead of an MFC application, then you will want to
			//  remove this line from DllMain and put it in a separate
			//  function exported from this Extension DLL.  The Regular DLL
			//  that uses this Extension DLL should then explicitly call that
			//  function to initialize this Extension DLL.  Otherwise,
			//  the CDynLinkLibrary object will not be attached to the
			//  Regular DLL's resource chain, and serious problems will
			//  result.
			
			g_hHook = NULL;
			g_hInstance = hInstance;
			g_pVoice = NULL;
			
			//*COM��ʼ����
			if (FAILED(::CoInitialize(NULL)))
			{
				TRACE(_T("COM��ʼ��ʧ��.\n"));
				return FALSE;
			}
			
			//��ȡISpVoice�ӿڣ�
			HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&g_pVoice);
			if(! SUCCEEDED( hr ) )
			{
				TRACE(_T("��ȡ�ӿ�ISpVoiceʧ��.\n"));
				return FALSE;
			}
			//g_pVoice->SetRate(20);
			//*/
	        
			TRACE0("SOUNDPROMPT.DLL ��ʼ��!\n");
			new CDynLinkLibrary(SoundPromptDLL);
		}
		break;
	case DLL_THREAD_ATTACH:	
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		{
			//*
			//g_pVoice = NULL;
			//g_pVoice->Release();
			::CoUninitialize(); //*/	

			TRACE0("SOUNDPROMPT.DLL ��ֹ!\n");
			// Terminate the library before destructors are called
			AfxTermExtensionModule(SoundPromptDLL);			
		}
		break;
	}
	return 1;   // ok
}

/*******************************************************************************************************
��������InstallHook
��  �ܣ�װ�ع���
��  ������
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-5
ʱ  �䣺14:43:04
*******************************************************************************************************/
extern "C" BOOL _stdcall InstallHook()
{
	g_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hInstance, NULL);
	if(g_hHook)
		return TRUE;
	else
		return FALSE;
}

/*******************************************************************************************************
��������UnInstallHook
��  �ܣ�ж�ع���
��  ������
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-5
ʱ  �䣺14:43:01
*******************************************************************************************************/
extern "C" BOOL _stdcall UnInstallHook()
{
	return UnhookWindowsHookEx(g_hHook);
}

/*******************************************************************************************************
��������Speak
��  �ܣ���������
��  ����
         WCHAR* Text��Ҫ���ŵ��ı�
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-6
ʱ  �䣺14:20:08
*******************************************************************************************************/
void Speak(WCHAR* Text)
{
	g_pVoice->Speak(Text, SPF_ASYNC, NULL);
	//g_pVoice = NULL;
			//::CoUninitialize(); //*/	

}

/*******************************************************************************************************
��������GetMsgProc
��  �ܣ�������Ϣ
��  ����
		int code�����Ӵ���
		WPARAM wParam�� �Ƴ���־
		LPARAM lParam����Ϣ�ĵ�ַ
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-5
ʱ  �䣺14:46:42
*******************************************************************************************************/
LRESULT CALLBACK GetMsgProc(
							int nCode,      // hook code
							WPARAM wParam,  // �Ƴ���־
							LPARAM lParam   // ��Ϣ�ĵ�ַ
							)
{
    if(nCode == HC_ACTION)
    {

        MSG* pMsg = (MSG*)lParam;
        switch(pMsg->message)
        {		
        case WM_CHAR:
            {			
                static int iInput;
                static char szChar[4];
                if(PM_NOREMOVE == wParam)
                {
                    switch(pMsg->wParam)
                    {
                    case 0x08:  // backspace 
                    case 0x0A:  // linefeed 
                    case 0x1B:  // escape 		
                    case 0x09:  // tab 		
                    case 0x0D:  // carriage return 
                    case 0x5c:  // "\"
                    case 0x26:  // &
                    case 0x23:  // #
                    case 0x40:  // @
                    case 0x21:  // !
                    case 0x71:  // ~
                    case 0x60:  // `
                        break;
                    case 0x27:  // '
                        Speak(L"������");
                        break;
                    case 0x22:  // "
                        Speak(L"����");
                        break;
                    case 0x3f:  // ?
                        Speak(L"�ʺ�");
                        break;
                    case 0x20:  // �ո�
                        Speak(L"�ո�");
                        break;
                    case '1':
                        Speak(L"һ");
                        break;
                    case '2':
                        Speak(L"��");
                        break;
                    case '3':
                        Speak(L"��");
                        break;
                    case '4':
                        Speak(L"��");
                        break;
                    case '5':
                        Speak(L"��");
                        break;
                    case '6':
                        Speak(L"��");
                        break;
                    case '7':
                        Speak(L"��");
                        break;
                    case '8':
                        Speak(L"��");
                        break;
                    case '9':
                        Speak(L"��");
                        break;
                    default:						
                        switch(iInput++)
                        {
                        case 0://ASCII					
                            szChar[1] = static_cast<TCHAR>(pMsg->wParam);
                            TRACE("szChar[1]=%x\n", szChar[1]);
                            break;
                        case 1://���ֵڶ��ֽ�
                            szChar[0] = static_cast<TCHAR>(pMsg->wParam);
                            TRACE(_T("����:szChar=%8.4x,%8.4x, szWchar=%s\n"), szChar[0], szChar[1], szChar);
                            break;
                        }                        
                    }
                }
                else
                {	
                    if(szChar[1] != 0)
                    {
                        WCHAR wch[2];
                        switch(iInput)
                        {						
                        case 1://ASCII				
                            if(::mbstowcs(wch, &szChar[1], 1) != -1)
                            {
                                wch[1] = 0;
                                TRACE(_T("UNICODE:%x%x\n"), wch[0], wch[1]);
                                Speak(wch);
                            }
                            break;
                        case 2://�Ǻ���
                            if(MultiByteToWideChar(CP_ACP, 0, szChar, 2, wch, 1))
                            {
                                wch[1] = 0;
                                TRACE(_T("UNICODE:%8.4x%8.4x\n"), wch[0], wch[1]);
                                Speak(wch);
                            }
                            break;
                        }
                        iInput = 0;				
                        memset(szChar, 0, sizeof(szChar));
                    }
                } // ���� if(PM_NOREMOVE == wParam)
            }
            break;
        default:
            break;		
        }
    } // ���� if(nCode == HC_ACTION)

	LRESULT lresult = ::CallNextHookEx(g_hHook, nCode, wParam, lParam);
	return lresult;
}