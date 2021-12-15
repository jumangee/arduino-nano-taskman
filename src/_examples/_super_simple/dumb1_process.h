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
		//@implement
		Dumb1Process(uint16_t pId, IProcessMessage* msg): IFirmwareProcess(pId, msg) {
			TRACELNF("Dumb1Process::init");
            randomSeed(analogRead(0));
		}
        
		//@implement
		static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg) {
			TRACELNF("Dumb1Process::factory");
			return new Dumb1Process(pId, msg);
		}

        //@implement
		void update(unsigned long ms) {
			TRACELNF("Dumb1Process::update");
		}

		//@implement
		~Dumb1Process() {
			// stop process
			TRACELNF("Dumb1Process::stop");
		}

};

#endif
