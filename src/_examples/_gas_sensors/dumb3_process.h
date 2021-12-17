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
		PROCESSID(PRC_DUMB3);

		//@implement
		Dumb3Process(IProcessMessage* msg): IFirmwareProcess(msg) {
			TRACELNF("Dumb3Process::init");
		}
        
		//@implement
		static IFirmwareProcess* factory(IProcessMessage* msg) {
			TRACELNF("Dumb3Process::factory");
			return new Dumb3Process(msg);
		}

        //@implement
		void update(unsigned long ms) {
			if (random(50) == 10) {
				this->getHost()->sendMessage(new TaskDoneMessage(this));
			}
			else
				this->pause(450);
		}
};

#endif
