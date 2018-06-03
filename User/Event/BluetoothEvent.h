#ifndef		__BLUETOOTH_EVENT_H
#define		__BLUETOOTH_EVENT_H

#include "Event/Event.h"
#include <rtx_os.h>


/**
 * @brief
 * 蓝牙数据接收处理
 * 0xE1 len type arg1 arg2 arg3 ... check 0xEF
 * len 表示整条命令的长度, 参数的个数 = len - 5
 */
class BluetoothEvent : public Event
{	
	public:
		enum EventId {
			ActionEvent = 0x02, // 电机动作命令
			RobotEvent = 0x03, // 机械手命令
			MotoEvent = 0x04, // 冰箱门和取货电机
			EventEnd,
		};
		
		inline EventId type(void) const {
			return (EventId) pMsg[2];
		}
};

#endif









