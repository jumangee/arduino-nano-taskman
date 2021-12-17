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

/**
 * @brief Power management process: controls state and then ready - starts child processes, which do the work
 */
class PwrConsumerProcess: public IFirmwareProcess {
	public:
		enum WorkState {
			NONE,
			START,
			ACTIVE,
			DONE
		};

	protected:
        byte        	keyPin;
        uint32_t    	poweredTime;
		WorkState		tasksArr[MAXTASKCOUNT];
		const uint16_t	*taskIdList;
		byte			taskCnt;

	public:
		PwrConsumerProcess(byte keyPin, const uint16_t *idList, byte tasks, IProcessMessage* msg);

		void clearState();

		int findProcessId(uint16_t id);

		void taskDone(uint16_t process_id);

		/**
		 * This should be overriden by handler with logic
		 */
		virtual bool handleMessageLogic(IProcessMessage* msg) = 0;

		unsigned long run(unsigned long start);

		void update(unsigned long ms);

		bool handleMessage(IProcessMessage* msg);

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

        void releaseLoad();

		~PwrConsumerProcess();
};

#endif