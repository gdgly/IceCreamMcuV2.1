#include "Custom/Protocol.h"
#include "Driver/Bluetooth.h"

namespace Protocol {
	
	/**
	 * 向App报告电机的状态(取货电机, 冰箱门电机)
	 */
	void vReportMotoAction(Action pick, Action fridge)
	{
		uint8_t tmp[6];
		vCreateMotoAction(tmp, pick, fridge);
		Bluetooth::instance()->write(tmp, 6);
	}
	
	/**
	 * @brief type = 0x81
	 * sensOstep1: 磁编码器1的数据
	 * sensOstep2: 磁编码器2的数据
	 * positionSwitch: 位置开关的数据
	 */
	void vCreateStatus(uint8_t *byteArray, uint16_t sensOstep1, uint16_t sensOstep2, uint16_t positionSwitch)
	{
		uint8_t tmp[] = {
			sensOstep1 >> 7,
			sensOstep1 & 0x7F,
			sensOstep2 >> 7,
			sensOstep2 & 0x7F,
			positionSwitch >> 7,
			positionSwitch & 0x7F
		};
		vCreateCustom(byteArray, 0x81, tmp, 6);
	}
	
	/**
	 * @brief type = 0x82
	 * pick: 取货电机的动作
	 * fridge: 冰箱门电机的动作
	 */
	void vCreateMotoAction(uint8_t *byteArray, Action pick, Action fridge)
	{
		uint8_t arg = (pick << 4) + fridge;
		byteArray[0] = 0xE1;
		byteArray[1] = 6;
		byteArray[2] = 0x82;
		byteArray[3] = arg;
		byteArray[4] = arg;
		byteArray[5] = 0xEF;
		return ;
	}
	
	/**
	 * @brief 创建通用的协议命令
	 */
	void vCreateCustom(uint8_t *byteArray, uint32_t type, const uint8_t *args, uint32_t arg_count)
	{
		uint8_t s = 0;
		byteArray[0] = 0xE1;
		byteArray[1] = arg_count + 5;
		byteArray[2] = type & 0xFF;
		byteArray[arg_count + 4] = 0xEF;
		for (uint32_t i = 0; i < arg_count; i ++) {
			byteArray[i + 3] = args[i];
			s ^= args[i];
		}
		byteArray[arg_count + 3] = s;
	}
	
	/**
	 * @brief 创建通用的协议命令
	 */
	void vCreateCustom(uint8_t *byteArray, uint32_t type, uint32_t arg_count, ...)
	{
		va_list ap;
		uint8_t s = 0;
		uint8_t arg;
		va_start(ap, arg_count);
		byteArray[0] = 0xE1;
		byteArray[1] = arg_count + 5; // 协议长度
		byteArray[2] = type & 0xFF;
		for (uint32_t i = 3; i < arg_count + 3; i ++) {
			arg = va_arg(ap, uint32_t);
			byteArray[i] = arg;
			s ^= arg;
		}
		byteArray[arg_count + 3] = s;
		byteArray[arg_count + 4] = 0xEF; 
	}
	
}




