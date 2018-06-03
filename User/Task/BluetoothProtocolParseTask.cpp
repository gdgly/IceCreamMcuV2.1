#include "Task/BluetoothProtocolParseTask.h"
#include "Event/BluetoothEvent.h"
#include "Driver/Bluetooth.h"
#include "Driver/RobotArm1.h"
#include "Driver/RobotArm2.h"
#include "Task/RobotArmTestTask.h"


static uint64_t TaskStack[512 / 8];

BluetoothProtocolParseTask::BluetoothProtocolParseTask(void) : Task("Bluetooth", TaskStack, sizeof (TaskStack))
{
}

void BluetoothProtocolParseTask::run(void)
{
	Bluetooth *ble = Bluetooth::instance();
	BluetoothEvent env;
	
	while (true)
	{
		ble->recv(&env);
		if (!env.isCorrect()) {
			continue;
		}
		switch (env.type())
		{
			case BluetoothEvent::RobotEvent: // 机械手动作
				RobotArmTestTask::instance()->setArg(&env);
				RobotArmTestTask::instance()->start();
				break;
			
			case BluetoothEvent::ActionEvent: // 
				
				break;
			
			case BluetoothEvent::MotoEvent: // 冰箱门和取货电机
				
				break;
		}

	}
}



