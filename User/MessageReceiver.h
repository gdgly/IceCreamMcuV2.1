#ifndef		__MESSAGE_RECEIVER_H
#define		__MESSAGE_RECEIVER_H

#include <rtx_os.h>


class MessageReceiver
{
	public:
		MessageReceiver(void);
		MessageReceiver(const uint8_t *data, uint32_t size);
	
		inline void set(const uint8_t *data, uint32_t size) {
			pData = data;
			nDataSize = size;
		}
		
		inline const uint8_t *data(void) {
			return pData;
		}
		
		inline uint32_t size(void) {
			return nDataSize;
		}
		
	private:
		const uint8_t *pData;
		uint32_t nDataSize;
};





#endif
