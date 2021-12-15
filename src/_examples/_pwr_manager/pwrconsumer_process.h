/**
 * Power Management Process
 * for Processy Firmware Framework
 */

#ifndef _PWRCONSUMER_PROCESS_H
#define _PWRCONSUMER_PROCESS_H

#include "processy.h"
#include "processy_process.h"

#include "pwrload_mngmnt.h"
#include "examplefirmware_cfg.h"

class PwrConsumerProcess: public IFirmwareProcess {
	public:
		enum WorkState {
			NONE,
			START,
			ACTIVE,
			DONE
		};

	private:
        byte        	keyPin;
        uint32_t    	poweredTime;
		WorkState		tasksArr[MAXTASKCOUNT];
		const uint16_t	*taskIdList;
		byte			taskCnt;

	public:
		//@implement
		//@include "processy_cfg.h"
		PwrConsumerProcess(byte keyPin, const uint16_t *idList, byte tasks, int pId, IProcessMessage* msg): IFirmwareProcess(pId, msg) {
			TRACELNF("PwrConsumerProcess::init")
			this->taskIdList = idList;
			this->taskCnt = tasks;
			this->keyPin = keyPin;
			this->poweredTime = 0;

			this->clearState();
		}

		//@implement
		void clearState() {
			for (byte i = 0; i < this->taskCnt; i++) {
				this->tasksArr[i] = NONE;
			}
		}

		//@implement
		int findProcessId(uint16_t id) {
			for (byte i = 0; i < this->taskCnt; i++) {
				if (this->taskIdList[i] == id) {
					return i;
				}
			}
			return -1;
		}

		//@implement
		void taskDone(uint16_t process_id) {
			int pos = this->findProcessId(process_id);
			if (pos == -1) return;

			this->tasksArr[pos] = DONE;
			this->getHost()->stopProcess(process_id);
		}

		/**
		 * This should be overriden by handler with logic
		 */
		virtual bool handleMessageLogic(IProcessMessage* msg) = 0;

        //@implement
		//@include "processy_cfg.h"
		//@include "pwrload_mngmnt.h"
		unsigned long run(unsigned long start) {
			if (this->poweredTime == 0) {
				this->poweredTime = PowerloadManagement::get()->requestPin(this->keyPin);
				// bit sleep - if got power - physical change state, if not - simple wait delay
				this->pause(10);
				return millis();
			}
			return IFirmwareProcess::run(start);
		}

		//@implement
		//@include "messages.h"
		void update(unsigned long ms) {
			// we got POWER! ))

			switch (this->getWorkState())
			{
				case START: {
					TRACELNF("PwrConsumerProcess: start child processes");
					for (byte i = 0; i < this->taskCnt; i++) {
						this->getHost()->addProcess(this->taskIdList[i]);
						this->tasksArr[i] = ACTIVE;
					}
					return;
				}
				case DONE: {
					// shutdown
					TRACELNF("PwrConsumerProcess: shut down");
					this->clearState();
					
					// unlock pwr key
					this->releaseLoad();
					this->getHost()->sendMessage(ProcessOrderMessage::goNextOf(this->getId()));
					return;
				}
				default: {
					// no work should be done here?
					this->pause(15);
				}
			}
		}

		//@implement
		bool handleMessage(IProcessMessage* msg) {
			if (msg->getType() == PRC_ORDER_MESSAGE)	{
				if (((ProcessOrderMessage*)msg)->getNextId() != this->getId()) {
					ProcessOrderMessage* msg = ProcessOrderMessage::goNextOf(this->getId());
					this->getHost()->addProcess(msg->getNextId());	// go to next of process list
					this->stop();
				}
				return false;
			}
			if (this->getWorkState() != ACTIVE) return false;//deepSleep || 
			return this->handleMessageLogic(msg);
		}

		PwrConsumerProcess::WorkState getWorkState() {
			byte none = 0;
			byte done = 0;

			for (byte i = 0; i < this->taskCnt; i++) {
				WorkState s = this->tasksArr[i];
				if (s == NONE) {
					none++;
				} else if (s == DONE) {
					done++;
				}
			}
			if (none == this->taskCnt) {
				return START;
			}
			if (done == this->taskCnt) {
				return DONE;
			}
			return ACTIVE;
		}

        uint32_t getPoweredTime() {
            return this->poweredTime;
        }

        //@implement
        void releaseLoad() {
            if (this->poweredTime != 0) {
				if (!PowerloadManagement::get()->releasePin(this->poweredTime)) {
					TRACELNF("PwrConsumerProcess//got FALSE");
				}
				this->poweredTime = 0;
			}
        }

		//@implement
		~PwrConsumerProcess() {
			// stop process
            this->releaseLoad();
			TRACELNF("PwrConsumerProcess::stop");
		}
};

#endif