#include "stm32f4xx.h"
#include "Task/Task.h"
#include "Driver/MicroWaveOvenUart.h"
#include "Driver/Bluetooth.h"
#include "Task/LedHintTask.h"
#include "Task/StatusReportTask.h"
#include "Task/BluetoothProtocolParseTask.h"
#include "Driver/RobotArm1.h"
#include "Driver/RobotArm2.h"
#include "Driver/Fridge.h"
#include "Driver/PickMoto.h"
#include "Driver/PositionSwitch.h"


static uint64_t MicroWaveTaskStack[512 / 8];

class MicroWaveOvenTask : public Task 
{
	public:
		MicroWaveOvenTask(void) : Task("", MicroWaveTaskStack, 512) {}
		
		static MicroWaveOvenTask *instance(void) {
			static MicroWaveOvenTask task;
			return &task;
		}
		
	protected:
		virtual void run(void)
		{
			MicroWaveOvenUart *uart = MicroWaveOvenUart::instance();
			MicroWaveOvenUartEvent env;
			while (true)
			{
				uart->recv(&env);
				switch (env.msg()[0])
				{
					case 0:
						uart->write("ack\r\n");
						Fridge::instance()->runUp(50);
						
						break;
					case 1:
						uart->write("ack\r\n");
						Fridge::instance()->runDown(40);
						
						break;
				}
//				uint16_t v = PositionSwitch::instance()->xGetValue();
//				uart->write("count=%0X\r\n", v);
//				osDelay(500);
			}
		}
};


int main(void)
{
	osKernelInitialize();
	NVIC_SetPriorityGrouping(7);
	PickMoto::instance()->vSetDir(PickMoto::Brake);
	Fridge::instance()->vSetDir(Fridge::Brake);
	RobotArm1::instance()->vSetDir(RobotArm1::Brake);
	RobotArm2::instance()->vSetDir(RobotArm2::Brake);
	LedHintTask::instance()->start();
	MicroWaveOvenTask::instance()->start();
	StatusReportTask::instance()->start();
	BluetoothProtocolParseTask::instance()->start();
	osKernelStart();
	
	while (true)
	{
		
	}
}
