/**
 * Dumb1 process (test)
 * for Processy Firmware Framework
 */

#ifndef _DUMB1_PROCESS_H
#define _DUMB1_PROCESS_H

#include "processy.h"
#include "processy_process.h"

#include "examplefirmware_cfg.h"

#include <Arduino.h>

class Dumb1Process: public IFirmwareProcess {
	private:
        bool active;

	public:
		PROCESSID(PRC_DUMB1);
	
		//@implement
		Dumb1Process(IProcessMessage* msg): IFirmwareProcess(msg) {
			TRACELNF("Dumb1Process::init");
            randomSeed(analogRead(0));
		}
        
		//@implement
		static IFirmwareProcess* factory(IProcessMessage* msg) {
			return new Dumb1Process(msg);
		}

        //@implement
		void update(unsigned long ms) {
			TRACELNF("Dumb1Process::update");
		}
};

#endif
