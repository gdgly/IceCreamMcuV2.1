#ifndef		__POSITION_SWITCH_H
#define		__POSITION_SWITCH_H

#include "stm32f4xx.h"
#include "Event/Sender.h"

class PositionSwitch : public Sender
{
	public:
		enum Mask {
			ICE_DOOR_SW1 = 0x02, // 冰箱门上微动开关
			ICE_DOOR_SW2 = 0x04, // 冰箱门下微动开关
			CAT_SW3 = 0x04, 
			CAT_SW4 = 0x08, 
			CAT_SW = 0x10, // 商品抓取限位开关
			DOOR_SW5 = 0x10, // 门禁开关
			KYJ_SW6 = 0x20, // 空压机压力开关
			YL1 = 0x40,
			YL2 = 0x80,
		};
	
	public:
		static inline PositionSwitch *instance(void) {
			static PositionSwitch instance;
			return &instance;
		}
		
		uint8_t xGetValue(void);
		
	private:
		PositionSwitch(void);
};





#endif
