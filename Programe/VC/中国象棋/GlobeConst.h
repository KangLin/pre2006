#ifndef _CHINESCHESS_GLOBECONST_BY_KANGLIN_2004_12_12_
#define _CHINESCHESS_GLOBECONST_BY_KANGLIN_2004_12_12_

#pragma once

const LONG g_MAXBUFLEN = 1024;      //��󻺴�����
const LONG g_SERVERPORT = 6791;     //�������˿�
const LONG g_DESKNUMBER = 48;       //������
const WORD g_wVerMajor = 1;    //���汾��
const WORD g_wVerMinor = 0;    //�ΰ汾��

typedef enum{
    g_cmdNoCommand = 0,        //������
    g_cmdLogon = 100,          //��¼
    g_cmdLogonSuccess,         //������ȷ
    g_cmdLogonPasswordError,   //�������
    g_cmdLogonNoUser,          //�޴��û�
    g_cmdLogonVersionUpdate,   //���µİ汾
    g_cmdLogonDownNewVersion,  //���������µĿͻ��˰汾
    g_cmdUserInfoHead,         //���µ�¼�û������û���Ϣͷ
    g_cmdUserInfo,             //���µ�¼�û����������ѵ�¼�û�����Ϣ
    g_cmdChairInfo,            //���µ�¼�û�����������Ϣ
    g_cmdRegist,               //ע��
    g_cmdRegistSuccess,        //ע��ɹ�
    g_cmdRegistHadUser,        //���û��Ѿ�����
    g_cmdSendTextMessage,      //�����ı���Ϣ
    g_cmdSetDown,              //����
    g_cmdHadMan,               //����λ������
    g_cmdLeaveChair,           //�뿪��λ
    g_cmdStart,                //ͬ�⿪ʼ����
    g_cmdSetPara,              //�����������
    g_cmdOtherNoMan,           //����û��
    g_cmdOtherSetDown,         //��������������û��ͬ�⿪ʼ
    g_cmdOtherStart,           //����������ͬ�⿪ʼ
    g_cmdPlayChess,            //��ʼ����
    g_cmdChessSock,            //����sock��Ϣ
    g_cmdChess,                //����
    g_cmdHand,                 //����
    g_cmdReceivedPara,         //���ղ���ȷ��
    g_cmdRepent,               //����
    g_cmdReceiveRepent,        //���ܻ���
    g_cmdStandOff,             //���
    g_cmdReceivedStandOff,     //���ܺ���
    g_cmdGiveup,               //����
    g_cmdReceiveGiveup,        //�ӷ�������ͻ��˷����û���Ϣ
    g_cmdVideoConn,            //��Ƶ����
    g_cmdAudioConn,            //��Ƶ����
    g_cmdAgreeVideoConn,       //ͬ����Ƶ����
    g_cmdAgreeAudioConn,       //ͬ����Ƶ����
    g_cmdNoVideo,              //��ͬ����Ƶ����
    g_cmdNoAudio,              //��ͬ����Ƶ����
    g_cmdVideoHand,            //��Ƶ����
    g_cmdAudioHand,            //��Ƶ����
    g_cmdExit                  //�����˳�
} G_COMMAND;

#endif //#ifndef _CHINESCHESS_GLOBECONST_BY_KANGLIN_2004_12_12_