#pragma once

class CTask
{
public:
	CTask();
	virtual ~CTask(void);

	enum
	{
		EXIT = 0,        //�����˳�
		ERR = 1,       //����
		INSERT_BACK = 2  //�������²��뵽�̳߳��е�������к�
	};

	//��������ʵ�ִ˺�����������ض��Ĺ���
	//�����������һ��������ɺ�,����Ҫ����,��������INSERT_BACK,
	//��ô�����񽫲��뵽�̳߳��������δβ
	//���������ִֻ��һ��,�򷵻�EXIT
	virtual int Run() = 0;
};
