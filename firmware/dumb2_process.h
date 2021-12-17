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

		Dumb2Process(IProcessMessage* msg);
        
		static IFirmwareProcess* factory(IProcessMessage* msg);

		void update(unsigned long ms);
};

#endif
