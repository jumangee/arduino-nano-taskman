#ifndef _EXAMPLEFIRMWARE_MESSAGES_H
#define _EXAMPLEFIRMWARE_MESSAGES_H

class IFirmwareProcess;

#include "processy_message.h"
#include <Arduino.h>
#include <math.h>

#include "examplefirmware_cfg.h"

//--- MSG TYPES -------------------
#define PRC_ORDER_MESSAGE		1001
#define TASKDONE_MESSAGE		1002
//---------------------------------

/**
 * @brief ProcessOrderMessage => IFirmware (process list control)
 */
class ProcessOrderMessage: public IProcessMessage {
	public:
		static ProcessOrderMessage* start() {
			return new ProcessOrderMessage();
		}

		static ProcessOrderMessage* goNextOf(uint16_t currentId) {
			return new ProcessOrderMessage(currentId);
		}

		uint16_t getNextId() {
			return this->nextId;
		}

	private:
		uint16_t nextId;

		/**
		 * @brief Definition of process start order
		 */
		uint16_t processOrderList[3] = {PRC_CONSUMER1, PRC_CONSUMER2, PRC_CONSUMER3};

		//@implement
		ProcessOrderMessage(const uint16_t lastPid = 0): IProcessMessage(NULL, PRC_ORDER_MESSAGE) {
			byte len = sizeof(this->processOrderList)/sizeof(this->processOrderList[0]);

			byte pos = 0;
			if (lastPid != 0) {
				for (byte i = 1; i < (len+1); i++) {
					uint16_t pid = this->processOrderList[i-1];
					if (lastPid == pid) {
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
};

/**
 * @brief task => pwrconsumer_process (task is done)
 */
class TaskDoneMessage: public IProcessMessage {
	public:
		TaskDoneMessage(uint16_t id): IProcessMessage(NULL, TASKDONE_MESSAGE) {
			this->taskId = id;
		}

		uint16_t getTaskId() {
			return this->taskId;
		}

	private:
		uint16_t	taskId;
};

#endif
