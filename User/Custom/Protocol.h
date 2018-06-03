#ifndef		__PROTOCOL_H
#define		__PROTOCOL_H

#include <stdint.h>
#include <stdarg.h>



namespace Protocol {

	enum Action {
		ActionNone = 0x00, // 电机没有任何动作
		ActionUp = 0x01, 
		ActionDown = 0x02,
		ActionEnd = 0x03, // 电机动作结束
		ActionBrake = 0x04, // 电机刹车
	};
	
	void vCreateStatus(uint8_t *byteArray, uint16_t sensOstep1, uint16_t sensOstep2, uint16_t positionSwitch);
	
	void vReportMotoAction(Action pick, Action fridge);
	
	void vCreateCustom(uint8_t *byteArray, uint32_t type, uint32_t arg_count, ...);
	
	void vCreateCustom(uint8_t *byteArray, uint32_t type, const uint8_t *args, uint32_t arg_count);
	
	/**
	 * @brief type = 0x82
	 * pick: 取货电机的动作
	 * fridge: 冰箱门电机的动作
	 */
	void vCreateMotoAction(uint8_t *byteArray, Action pick, Action fridge);
}





#endif
