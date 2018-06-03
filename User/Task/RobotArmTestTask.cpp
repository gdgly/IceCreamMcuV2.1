#include "Task/RobotArmTestTask.h"
#include "Event/BluetoothEvent.h"
#include "Driver/RobotArm1.h"
#include "Driver/RobotArm2.h"

static uint64_t TaskStack[512 / 8];

RobotArmTestTask::RobotArmTestTask(void) : Task("RobotTest", TaskStack, sizeof (TaskStack))
{
	
}


void RobotArmTestTask::run(void)
{
	const BluetoothEvent *env = (const BluetoothEvent *) arg();

	const uint16_t p1 = (env->arg(1) << 7) + env->arg(2); // 机械臂1的位置
	const uint16_t p2 = (env->arg(3) << 7) + env->arg(4); // 机械臂2的位置
	uint16_t s1 = env->arg(5);
	uint16_t s2 = env->arg(6);

	if (p1 == 518 && p1 == 518) {
		RobotArm1::instance()->runTo(p1, s1);
		RobotArm2::instance()->runTo(p2, s2);
		return;
	}
	
	RobotArm2::instance()->runTo(p2, s2);
	RobotArm1::instance()->runTo(p1, s1);
}








