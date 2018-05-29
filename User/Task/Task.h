#ifndef		__TASK_TASK_H
#define		__TASK_TASK_H

#include <rtx_os.h>


class Task
{	
	public:
		Task(const char *name, uint64_t *stack, uint32_t stackSize, osPriority_t priority = osPriorityHigh);
		
		void start(void);
	
		void stop(void);
	
	protected:
		virtual void run(void) = 0;
	
	private:
		static void startThreadFun(void *arg);
	
	private:
		uint64_t aCbMem[(osRtxThreadCbSize + 7) / 8]; // 线程控制块
		osThreadAttr_t sAttr; // 线程属性
		osThreadId_t sId; // 线程Id
};





#endif
