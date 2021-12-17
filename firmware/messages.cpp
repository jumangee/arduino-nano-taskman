#include "messages.h"

ProcessOrderMessage::ProcessOrderMessage(const uint16_t lastPid = 0) : IProcessMessage(NULL, PRC_ORDER_MESSAGE){
	byte len = sizeof(this->processOrderList)/sizeof(this->processOrderList[0]);
	byte pos = 0;
	if (lastPid != 0) {
		for (byte i = 1; i <= len; i++) {
			if (lastPid == this->processOrderList[i-1]) {
				if (i == len) {
					pos = 0;	// restart list
				} else {
					pos = i;
				}
				break;
			}
		}
	}
	this->nextId = this->processOrderList[pos];
	return;
}
