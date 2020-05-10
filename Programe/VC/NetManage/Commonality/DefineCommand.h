/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    DefineCommand.h
\brief   ����궨��
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��14��  18:51:11
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __DEFINECOMMAND_H_KL_2008_8_14__
#define __DEFINECOMMAND_H_KL_2008_8_14__

#pragma once

#define CMD_QUERY_PROCESS_MODULE                           10    //!<��ѯָ�����̣�����ģ�飩��Ϣ
#define CMD_ANSWER_PROCESS_MODULE                          11    //!<Ӧ���ѯָ�����̣�����ģ�飩��Ϣ
#define CMD_QUERY_ALL_PROCESS_MODULE                       12    //!<��ѯ���н��̣�����ģ�飩��Ϣ
#define CMD_ANSWER_ALL_PROCESS_MODULE                      13    //!<Ӧ�����н��̣�����ģ�飩��Ϣ
#define CMD_QUERY_PROCESS                                  14    //!<��ѯָ��������Ϣ
#define CMD_ANSWER_PROCESS                                 15    //!<Ӧ���ѯָ��������Ϣ
#define CMD_QUERY_ALL_PROCESS                              16    //!<��ѯ���н�����Ϣ
#define CMD_ANSWER_ALL_PROCESS                             17    //!<Ӧ�����н�����Ϣ
#define CMD_QUERY_PROCESS_PATH                             18    //!<�õ�ָ�����̵�ȫ·��
#define CMD_ANSWER_PROCESS_PATH                            19    //!<Ӧ��õ�ָ�����̵�ȫ·��

#define CMD_QUERY_WMI_WIN32_OPERATING_SYSTEM_INFORMATION   50    //!<WMI��ʽ��ѯ����ϵͳ��Ϣ
#define CMD_ANSWER_WMI_WIN32_OPERATING_SYSTEM_INFORMATION  51    //!<Ӧ��WMI��ʽ��ѯ����ϵͳ��Ϣ
#define CMD_QUERY_WMI_COMPUTER_SYSTEM_INFORMATION          52    //!<2.2.3	WMI��ʽ�����ϵͳ��Ϣ
#define CMD_ANSWER_WMI_COMPUTER_SYSTEM_INFORMATION         53    //!<2.2.4	Ӧ��WMI��ʽ�����ϵͳ��Ϣ
#define CMD_QUERY_WMI_SYSTEM_PROCESSOR                     54    //!<2.2.5	WMI��ʽ��ѯϵͳ������
#define CMD_ANSWER_WMI_SYSTEM_PROCESSOR                    55    //!<2.2.6	Ӧ��WMI��ʽ��ѯϵͳ������
#define CMD_QUERY_WMI_MEMORY                               56    //!<2.2.7	WMI��ʽ��ѯ�ڴ���Ϣ
#define CMD_WMI_ANSWER_MEMORY                              57    //!<2.2.8	Ӧ��WMI��ʽ��ѯ�ڴ���Ϣ
#define CMD_QUERY_WMI_BIOS                                 58    //!<2.2.9	WMI��ʽ��ѯϵͳBIOS
#define CMD_ANSWER_WMI_BIOS                                59    //!<2.2.10	Ӧ��WMI��ʽ��ѯϵͳBIOS
#define CMD_QUERY_WMI_VIDEOCONROLLER                       60    //!<2.2.11	WMI��ʽ��ѯ��ʾ����Ϣ
#define CMD_ANSWER_WMI_VIDEOCONROLLER                      61    //!<2.2.12	Ӧ��WMI��ʽ��ѯ��ʾ����Ϣ
#define CMD_QUERY_WMI_ALL_PROCESS                          62    //!<2.2.13	WMI��ʽ��ѯ���н�����Ϣ
#define CMD_ANSWER_WMI_ALL_PROCESS                         63    //!<2.2.14	Ӧ��WMI��ʽ��ѯ���н�����Ϣ

#define CMD_QUERY_WMI_SERVICE_INFORMATION                  80    //!<2.2.15	WMI��ʽ��ѯ������Ϣ
#define CMD_ANSWER_WMI_SERVICE_INFORMATION                 81    //!<2.2.16	Ӧ��WMI��ʽ��ѯ������Ϣ


#define CMD_LOGIN                                          1000  //!<1.1	��¼
#define CMD_ANSWER_LOGIN                                   1001  //!<1.2	Ӧ���¼
#define CMD_LOGOUT                                         1002  //!<1.3	ע��
#define CMD_ANSWER_LOGOUT                                  1003  //!<1.4	Ӧ��ע��
#define CMD_TEST_ECHO                                      1004  //!<1.5	���Ի���
#define CMD_ANSWER_ECHO                                    1005  //!<1.6	Ӧ����Ի���



#endif //__DEFINECOMMAND_H_KL_2008_8_14__
