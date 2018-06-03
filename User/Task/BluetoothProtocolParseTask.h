#ifndef		__BLUETOOTH_PROTOCOL_PARSE_TASK_H
#define		__BLUETOOTH_PROTOCOL_PARSE_TASK_H

#include "Task/Task.h"

class BluetoothProtocolParseTask : public Task
{
	public:
		static inline BluetoothProtocolParseTask *instance(void) {
			static BluetoothProtocolParseTask task;
			return &task;
		}
		
	protected:
		virtual void run(void);
		
	private:
		BluetoothProtocolParseTask(void) ;
};




#endif
