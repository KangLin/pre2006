#pragma once

class CTask
{
public:
	CTask();
	virtual ~CTask(void);

	enum
	{
		EXIT = 0,        //任务退出
		ERR = 1,       //出错
		INSERT_BACK = 2  //任务重新插入到线程池中的任务队列后
	};

	//派生类中实现此函数，以完成特定的功能
	//如果任务在这一次运行完成后,还需要运行,则函数返回INSERT_BACK,
	//那么此任务将插入到线程池任务队列未尾
	//如果此任务只执行一次,则返回EXIT
	virtual int Run() = 0;
};
