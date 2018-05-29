#include "stm32f4xx.h"
#include "Task/Task.h"
#include "Driver/MicroWaveOvenUart.h"

static uint64_t UartTaskStack[512 / 8];

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
			MicroWaveOvenUart *uart = MicroWaveOvenUart::instance();
			MessageReceiver recv;
			while (true)
			{
				uart->getMessage(&recv);
				uart->write(recv.data(), recv.size());
			}
		}
};



int main(void)
{
	osKernelInitialize();
	NVIC_SetPriorityGrouping(7);
	UartTask::instance()->start();
	osKernelStart();
	
	while (true)
	{
		
	}
}
