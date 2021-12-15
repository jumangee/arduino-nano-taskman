/**
 * Dumb3 process (test)
 * for Processy Firmware Framework
 */

#ifndef _DUMB3_PROCESS_H
#define _DUMB3_PROCESS_H

#include "processy.h"
#include "processy_process.h"
#include "messages.h"

#include "examplefirmware_cfg.h"

#include <Arduino.h>

class Dumb3Process: public IFirmwareProcess {
	private:
        bool active;

	public:
		//@implement
		Dumb3Process(uint16_t pId, IProcessMessage* msg): IFirmwareProcess(pId, msg) {
			TRACELNF("Dumb3Process::init");
		}
        
		//@implement
		static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg) {
			TRACELNF("Dumb3Process::factory");
			return new Dumb3Process(pId, msg);
		}

        //@implement
		void update(unsigned long ms) {
			if (random(50) == 10) {
				this->getHost()->sendMessage(new TaskDoneMessage(PRC_DUMB3));
			}
			else
				this->pause(450);
		}

		//@implement
		~Dumb3Process() {
			// stop process
			TRACELNF("Dumb3Process::stop")
		}

};

#endif
