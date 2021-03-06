/**
 * Application class (examplefirmware)
 * for Processy Firmware Framework
 */
#ifndef _EXAMPLEFIRMWARE_H
#define _EXAMPLEFIRMWARE_H

#include "examplefirmware_cfg.h"
#include "processy_cfg.h"
#include "processy.h"

// ---[ PROCESSES ]---
#include "dumb1_process.h"
#include "dumb2_process.h"
#include "dumb3_process.h"
// -------------------

class ExampleFirmware: public IFirmware {
	//@implement
	//@include <Arduino.h>
	ExampleFirmware(): IFirmware() {
		#ifdef PROCESSY_DEBUG_SERIAL
		Serial.begin(9600);
		delay(1000);		
		TRACELNF("START");
		#endif
		
		PROCESS_REG(Dumb1Process);
		PROCESS_REG(Dumb2Process);
		PROCESS_REG(Dumb3Process);

		/* all tasks works simulatenously */
		addProcess(PRC_DUMB1);
		addProcess(PRC_DUMB2);
		addProcess(PRC_DUMB3);
	};
	
	public:
		//@implement
		static IFirmware* get() {
			if (IFirmware::instance == NULL) {
				IFirmware::instance = new ExampleFirmware();
			}
			return IFirmware::instance;
		}

};

#endif
