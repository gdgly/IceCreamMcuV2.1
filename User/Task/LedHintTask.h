#ifndef		__LED_HINT_TASK_H
#define		__LED_HINT_TASK_H

#include "Task/Task.h"

class LedHintTask : public Task
{
	public:
		static inline LedHintTask *instance(void) {
			static LedHintTask task;
			return &task;
		}
		
	protected:
		virtual void run(void);
	
	private:
		LedHintTask(void);
};






#endif
