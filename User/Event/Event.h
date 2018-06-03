#ifndef		__EVENT_H
#define		__EVENT_H

#include <rtx_os.h>

class Event
{
	public:
		Event(void) : pMsg(NULL), nMsgCount(0) {}
		Event(const uint8_t *msg, uint32_t count) : pMsg(msg), nMsgCount(count) {}
	
		inline void set(const uint8_t *msg, uint32_t count) {
			pMsg = msg;
			nMsgCount = count;
		}
		
		inline const uint8_t *msg(void) const {
			return pMsg;
		}
		
		inline uint8_t size(void) const {
			return nMsgCount;
		}
		
		inline uint8_t arg(uint8_t index) const {
			return pMsg[index + 2];
		}
		
		/**
		 * 判断接收的数据是否正确
		 */
		bool isCorrect(void) const;
		
	protected:
		const uint8_t *pMsg;
		uint32_t nMsgCount;
	
	private:
		uint8_t check(void) const;
};


#endif
