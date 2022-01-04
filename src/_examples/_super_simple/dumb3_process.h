/**
 * Dumb3 process (test)
 * for Processy Firmware Framework
 */

#ifndef _DUMB3_PROCESS_H
#define _DUMB3_PROCESS_H

#include "processy.h"
#include "processy_process.h"

#include "examplefirmware_cfg.h"

#include <Arduino.h>

class Dumb3Process: public IFirmwareProcess {
	public:
		PROCESSID(PRC_DUMB2);

		//@implement
		Dumb3Process(IProcessMessage* msg): IFirmwareProcess(msg) {
			TRACELNF("Dumb3Process::init");
		}
        
		//@implement
		static IFirmwareProcess* factory(IProcessMessage* msg) {
			return new Dumb3Process(msg);
		}

        //@implement
		void update(unsigned long ms) {
			TRACELNF("Dumb3Process::update");
		}

};

#endif
