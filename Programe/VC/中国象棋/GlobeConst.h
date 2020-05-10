#ifndef _CHINESCHESS_GLOBECONST_BY_KANGLIN_2004_12_12_
#define _CHINESCHESS_GLOBECONST_BY_KANGLIN_2004_12_12_

#pragma once

const LONG g_MAXBUFLEN = 1024;      //最大缓存区数
const LONG g_SERVERPORT = 6791;     //服务器端口
const LONG g_DESKNUMBER = 48;       //桌子数
const WORD g_wVerMajor = 1;    //主版本号
const WORD g_wVerMinor = 0;    //次版本号

typedef enum{
    g_cmdNoCommand = 0,        //无命令
    g_cmdLogon = 100,          //登录
    g_cmdLogonSuccess,         //密码正确
    g_cmdLogonPasswordError,   //密码错误
    g_cmdLogonNoUser,          //无此用户
    g_cmdLogonVersionUpdate,   //有新的版本
    g_cmdLogonDownNewVersion,  //必须下载新的客户端版本
    g_cmdUserInfoHead,         //向新登录用户发送用户信息头
    g_cmdUserInfo,             //向新登录用户发送所有已登录用户的信息
    g_cmdChairInfo,            //向新登录用户发送椅子信息
    g_cmdRegist,               //注册
    g_cmdRegistSuccess,        //注册成功
    g_cmdRegistHadUser,        //此用户已经存在
    g_cmdSendTextMessage,      //发送文本消息
    g_cmdSetDown,              //入坐
    g_cmdHadMan,               //此坐位已有人
    g_cmdLeaveChair,           //离开坐位
    g_cmdStart,                //同意开始下棋
    g_cmdSetPara,              //设置象棋参数
    g_cmdOtherNoMan,           //对面没人
    g_cmdOtherSetDown,         //对面有人入坐但没有同意开始
    g_cmdOtherStart,           //对面入坐且同意开始
    g_cmdPlayChess,            //开始下棋
    g_cmdChessSock,            //象棋sock信息
    g_cmdChess,                //棋子
    g_cmdHand,                 //握手
    g_cmdReceivedPara,         //接收参数确定
    g_cmdRepent,               //悔棋
    g_cmdReceiveRepent,        //接受悔棋
    g_cmdStandOff,             //求和
    g_cmdReceivedStandOff,     //接受和棋
    g_cmdGiveup,               //认输
    g_cmdReceiveGiveup,        //从服务器向客户端发回用户信息
    g_cmdVideoConn,            //视频连接
    g_cmdAudioConn,            //音频连接
    g_cmdAgreeVideoConn,       //同意视频连接
    g_cmdAgreeAudioConn,       //同意音频连接
    g_cmdNoVideo,              //不同意视频连接
    g_cmdNoAudio,              //不同意音频连接
    g_cmdVideoHand,            //视频握手
    g_cmdAudioHand,            //音频握手
    g_cmdExit                  //程序退出
} G_COMMAND;

#endif //#ifndef _CHINESCHESS_GLOBECONST_BY_KANGLIN_2004_12_12_