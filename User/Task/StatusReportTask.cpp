#include "Task/StatusReportTask.h"
#include "Driver/RobotArm1.h"
#include "Driver/RobotArm2.h"
#include "Driver/PositionSwitch.h"
#include "Driver/Bluetooth.h"
#include "Custom/Protocol.h"

static uint64_t TaskStack[512 / 8];

StatusReportTask::StatusReportTask(void) : Task("Status", TaskStack, sizeof (TaskStack))
{
	
}

void StatusReportTask::run(void)
{
	RobotArm1 *const r1 = RobotArm1::instance();
	RobotArm2 *const r2 = RobotArm2::instance();
	PositionSwitch *const sw = PositionSwitch::instance();
	uint8_t bytes[11];
	osDelay(100);
	r1->vSetPosition();
	r2->vSetPosition();
	osDelay(100);
	
	uint16_t p1, p2, s1;
	
	while (true)
	{
		p1 = r1->xGetPosition();
		p2 = r2->xGetPosition();
		s1 = sw->xGetValue();
		Protocol::vCreateStatus(bytes, p1, p2, s1);
		Bluetooth::instance()->write(bytes, 11);
		osDelay(500);
	}
}




