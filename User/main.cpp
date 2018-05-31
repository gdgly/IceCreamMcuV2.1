#include "stm32f4xx.h"
#include "Task/Task.h"
#include "Driver/MicroWaveOvenUart.h"
#include "Driver/Bluetooth.h"

static uint64_t UartTaskStack[512 / 8];
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
				uart->write(env.msg(), env.size());
			}
		}
};

class UartTask: public Task
{
	public:
		static UartTask *instance(void) {
			static UartTask task;
			return &task;
		}
	
		UartTask(void) : Task("", UartTaskStack, 512)
		{

		}
		
	protected:
		virtual void run(void)
		{
			Bluetooth *uart = Bluetooth::instance();
			BluetoothEvent recv;
			while (true)
			{
				uart->recv(&recv);
				uart->write(recv.msg(), recv.size());
			}
		}
};



int main(void)
{
	osKernelInitialize();
	NVIC_SetPriorityGrouping(7);
	UartTask::instance()->start();
	MicroWaveOvenTask::instance()->start();
	osKernelStart();
	
	while (true)
	{
		
	}
}
