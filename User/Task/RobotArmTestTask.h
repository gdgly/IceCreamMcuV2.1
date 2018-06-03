#ifndef		__ROBOT_ARM_TEST_TASK_H
#define		__ROBOT_ARM_TEST_TASK_H

#include "Task/Task.h"

class RobotArmTestTask : public Task
{
	public:
		static inline RobotArmTestTask *instance(void) {
			static RobotArmTestTask task;
			return &task;
		}
		
	protected:
		virtual void run(void);
		
	private:
		RobotArmTestTask(void);
};




#endif
