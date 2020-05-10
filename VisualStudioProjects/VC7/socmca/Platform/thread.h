#ifndef __THREAD_H_KL__
#define __THREAD_H_KL__

#pragma once

#ifdef _WIN32
#include <windows.h>
#endif // ���� #ifdef _WIN32

#ifdef __LINUX__
#include <pthread.h>
#include "tchar.h"
#endif // ���� #ifdef __LINUX__


#ifdef _WIN32
typedef HANDLE thread_t;
#endif // ���� #ifdef _WIN32

#ifdef __LINUX__
typedef pthread_t thread_t;
#endif // ���� #ifdef __LINUX__

/*******************************************************************************************************
��������thread_create
��  ���������߳�
��  ����
		thread_t * hThread            ���߳̾����
        DWORD thread_function(void * )���̺߳�����
		void * para                   �������̺߳����Ĳ�����
����ֵ������Ϊ thread_t ���ɹ������߳̾����ʧ�ܷ���NULL��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��23�� 17:33:22
*******************************************************************************************************/
int thread_create(thread_t * hThread, DWORD thread_function(void * ), void * para);

/*******************************************************************************************************
��������thread_exit
��  �����߳��˳�
��  ����
        void * retval���˳�����
����ֵ������Ϊ void ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��25�� 9:58:46
*******************************************************************************************************/
void thread_exit(DWORD dwExit);

int thread_terminate(thread_t hTread);

#endif //__THREAD_H_KL__
