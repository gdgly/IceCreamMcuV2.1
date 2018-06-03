#ifndef		__STATUS_REPORT_TASK_H
#define		__STATUS_REPORT_TASK_H

#include "Task/Task.h"


class StatusReportTask : public Task
{
	public:
		static inline StatusReportTask *instance(void) {
			static StatusReportTask task;
			return &task;
		}
		
	protected:
		virtual void run(void);
		
	private:
		StatusReportTask(void);
};







#endif
