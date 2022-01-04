/**
 * Dumb2 process (test)
 * for Processy Firmware Framework
 */

#ifndef _DUMB2_PROCESS_H
#define _DUMB2_PROCESS_H

#include "processy.h"
#include "processy_process.h"
#include "messages.h"

#include "examplefirmware_cfg.h"

#include <Arduino.h>

class Dumb2Process: public IFirmwareProcess {
	private:
        bool active;

	public:
		PROCESSID(PRC_DUMB2);

		//@implement
		Dumb2Process(IProcessMessage* msg): IFirmwareProcess(msg) {
			TRACELNF("Dumb2Process::init");
		}
        
		//@implement
		static IFirmwareProcess* factory(IProcessMessage* msg) {
			TRACELNF("Dumb2Process::factory");
			return new Dumb2Process(msg);
		}

        //@implement
		void update(unsigned long ms) {
			if (random(50) == 10) {
				this->getHost()->sendMessage(new TaskDoneMessage(PRC_DUMB2));
			}
			else
				this->pause(450);

		}

};

#endif
