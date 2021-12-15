/**
 * Dumb2 process (test)
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
		Dumb3Process(uint16_t pId, IProcessMessage* msg);
        
		static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg);

		void update(unsigned long ms);

		~Dumb3Process();

};

#endif
