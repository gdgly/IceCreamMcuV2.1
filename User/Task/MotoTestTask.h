#ifndef		__MOTO_TEST_TASK_H
#define		__MOTO_TEST_TASK_H

#include "Task/Task.h"
#include "Event/BluetoothEvent.h"

class MotoTestTask : public Task
{
	public:
		static inline MotoTestTask *instance(void) {
			static MotoTestTask task;
			return &task;
		}
	
	private:
		virtual void run(void);
		
	private:
		MotoTestTask(void);
	
	
};



#endif
