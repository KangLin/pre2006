/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    DefineCommand.h
\brief   命令宏定义
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年8月14日  18:51:11
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __DEFINECOMMAND_H_KL_2008_8_14__
#define __DEFINECOMMAND_H_KL_2008_8_14__

#pragma once

#define CMD_QUERY_PROCESS_MODULE                           10    //!<查询指定进程（包括模块）信息
#define CMD_ANSWER_PROCESS_MODULE                          11    //!<应答查询指定进程（包括模块）信息
#define CMD_QUERY_ALL_PROCESS_MODULE                       12    //!<查询所有进程（包括模块）信息
#define CMD_ANSWER_ALL_PROCESS_MODULE                      13    //!<应答所有进程（包括模块）信息
#define CMD_QUERY_PROCESS                                  14    //!<查询指定进程信息
#define CMD_ANSWER_PROCESS                                 15    //!<应答查询指定进程信息
#define CMD_QUERY_ALL_PROCESS                              16    //!<查询所有进程信息
#define CMD_ANSWER_ALL_PROCESS                             17    //!<应答所有进程信息
#define CMD_QUERY_PROCESS_PATH                             18    //!<得到指定进程的全路径
#define CMD_ANSWER_PROCESS_PATH                            19    //!<应答得到指定进程的全路径

#define CMD_QUERY_WMI_WIN32_OPERATING_SYSTEM_INFORMATION   50    //!<WMI方式查询操作系统信息
#define CMD_ANSWER_WMI_WIN32_OPERATING_SYSTEM_INFORMATION  51    //!<应答WMI方式查询操作系统信息
#define CMD_QUERY_WMI_COMPUTER_SYSTEM_INFORMATION          52    //!<2.2.3	WMI方式计算机系统信息
#define CMD_ANSWER_WMI_COMPUTER_SYSTEM_INFORMATION         53    //!<2.2.4	应答WMI方式计算机系统信息
#define CMD_QUERY_WMI_SYSTEM_PROCESSOR                     54    //!<2.2.5	WMI方式查询系统处理器
#define CMD_ANSWER_WMI_SYSTEM_PROCESSOR                    55    //!<2.2.6	应答WMI方式查询系统处理器
#define CMD_QUERY_WMI_MEMORY                               56    //!<2.2.7	WMI方式查询内存信息
#define CMD_WMI_ANSWER_MEMORY                              57    //!<2.2.8	应答WMI方式查询内存信息
#define CMD_QUERY_WMI_BIOS                                 58    //!<2.2.9	WMI方式查询系统BIOS
#define CMD_ANSWER_WMI_BIOS                                59    //!<2.2.10	应答WMI方式查询系统BIOS
#define CMD_QUERY_WMI_VIDEOCONROLLER                       60    //!<2.2.11	WMI方式查询显示卡信息
#define CMD_ANSWER_WMI_VIDEOCONROLLER                      61    //!<2.2.12	应答WMI方式查询显示卡信息
#define CMD_QUERY_WMI_ALL_PROCESS                          62    //!<2.2.13	WMI方式查询所有进程信息
#define CMD_ANSWER_WMI_ALL_PROCESS                         63    //!<2.2.14	应答WMI方式查询所有进程信息

#define CMD_QUERY_WMI_SERVICE_INFORMATION                  80    //!<2.2.15	WMI方式查询服务信息
#define CMD_ANSWER_WMI_SERVICE_INFORMATION                 81    //!<2.2.16	应答WMI方式查询服务信息


#define CMD_LOGIN                                          1000  //!<1.1	登录
#define CMD_ANSWER_LOGIN                                   1001  //!<1.2	应答登录
#define CMD_LOGOUT                                         1002  //!<1.3	注消
#define CMD_ANSWER_LOGOUT                                  1003  //!<1.4	应答注消
#define CMD_TEST_ECHO                                      1004  //!<1.5	测试回显
#define CMD_ANSWER_ECHO                                    1005  //!<1.6	应答测试回显



#endif //__DEFINECOMMAND_H_KL_2008_8_14__
