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
#include "beeper_process.h"
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
		
		PROCESS_REG(DisplayProcess);
		addProcess(PRC_BEEPER);
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
