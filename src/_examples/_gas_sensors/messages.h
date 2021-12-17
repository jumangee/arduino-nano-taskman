#ifndef _EXAMPLEFIRMWARE_MESSAGES_H
#define _EXAMPLEFIRMWARE_MESSAGES_H

#include "processy_message.h"
#include <Arduino.h>
#include <math.h>

#include "pwrconsumer1process.h"
#include "pwrconsumer2process.h"
#include "pwrconsumer3process.h"

#include "processy_process.h"

//--- MSG TYPES -------------------
#define PRC_ORDER_MESSAGE		1001
#define TASKDONE_MESSAGE		1002
#define PPD42NS_MESSAGE			1025
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
};

class ParticlePPD42Message: public IProcessMessage {
	public:
		ParticlePPD42Message(float ratioPm1, float concentrationPm1, float ratioPm2, float concentrationPm2): IProcessMessage(NULL, PPD42NS_MESSAGE) {
			this->ratioPm1 = ratioPm1;
			this->ratioPm2 = ratioPm2;
			this->concentrationPm1 = concentrationPm1;
			this->concentrationPm2 = concentrationPm2;
		}

		float ratioPm1;
		float ratioPm2;
		float concentrationPm1;
		float concentrationPm2;
};

/**
 * @brief task => pwrconsumer_process (task is done)
 */
class TaskDoneMessage: public IProcessMessage {
	public:
		TaskDoneMessage(IFirmwareProcess* prc): IProcessMessage(NULL, TASKDONE_MESSAGE) {
			this->taskId = prc->getId();
		}

		uint16_t getTaskId() {
			return this->taskId;
		}

	private:
		uint16_t	taskId;
};

#endif
