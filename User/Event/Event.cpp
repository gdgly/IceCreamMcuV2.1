#include "Event/Event.h"


uint8_t Event::check(void) const
{
	uint32_t end = nMsgCount - 2;
	uint8_t sum = 0;
	for (uint32_t i = 3; i < end; i ++) {
		sum ^= pMsg[i];
	}
	return sum;
}

bool Event::isCorrect(void) const
{
	if (0xE1 != pMsg[0] || 0xEF != pMsg[nMsgCount - 1]) {
		return false;
	}
	if (pMsg[1] != nMsgCount) {
		return false;
	}
	if (check() != pMsg[nMsgCount - 2]) {
		return false;
	}
	return true;
}












