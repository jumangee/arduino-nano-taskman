/**
 * Dumb2 process (test)
 * for Processy Firmware Framework
 */

#ifndef _DUMB2_PROCESS_H
#define _DUMB2_PROCESS_H

#include "processy.h"
#include "processy_process.h"

#include "examplefirmware_cfg.h"

#include <Arduino.h>

class Dumb2Process: public IFirmwareProcess {
	private:
        bool active;

	public:
		//@implement
		Dumb2Process(uint16_t pId, IProcessMessage* msg): IFirmwareProcess(pId, msg) {
			TRACELNF("Dumb2Process::init");
		}
        
		//@implement
		static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg) {
			TRACELNF("Dumb2Process::factory");
			return new Dumb2Process(pId, msg);
		}

        //@implement
		void update(unsigned long ms) {
			TRACELNF("Dumb2Process::update");
		}

		//@implement
		~Dumb2Process() {
			// stop process
			TRACELNF("Dumb2Process::stop")
		}

};

#endif
