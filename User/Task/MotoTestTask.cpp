#include "Task/MotoTestTask.h"
#include "Driver/Fridge.h"
#include "Driver/PickMoto.h"
#include "Custom/Protocol.h"

static uint64_t MotoTestTaskStack[512 / 8];

MotoTestTask::MotoTestTask(void) : Task("MotoTestTask", MotoTestTaskStack, sizeof(MotoTestTaskStack))
{
	
}


void MotoTestTask::run(void)
{
	const BluetoothEvent *env = (const BluetoothEvent *) arg();
	uint16_t arg1 = env->arg(1);
	uint16_t fridge_sp = env->arg(2); // 升降电机的速度
	uint16_t pick_sp = env->arg(3); // 冰箱门电机的速度
	uint8_t fridge = (arg1 >> 4) & 0x07; // 冰箱门
	uint8_t pick = arg1 & 0x07; // 升降电机
	
	PickMoto::instance()->runUp(pick_sp); // 升降电机先上升
	
	switch (fridge) {
		case 0x01: Fridge::instance()->runUp(fridge_sp); break; // 冰箱门电机打开
		case 0x02: Fridge::instance()->runDown(fridge_sp); break; // 冰箱门关闭
	}
	
	switch (pick) {
		case 0x01: PickMoto::instance()->runUp(pick_sp); break; // 冰箱门电机打开
		case 0x02: PickMoto::instance()->runDown(pick_sp); break; // 冰箱门电机关闭
	}
}








