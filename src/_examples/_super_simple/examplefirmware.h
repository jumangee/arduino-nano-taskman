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

#include "messages.h"

class ExampleFirmware: public IFirmware {
	const static byte PwrMngmtPins[];

	//@cpp
const static byte ExampleFirmware::PwrMngmtPins[] = PWRMNGMTPINS;

	//@implement
	//@include <Arduino.h>
	ExampleFirmware(): IFirmware() {
		#ifdef PROCESSY_DEBUG_SERIAL
		Serial.begin(9600);
		delay(1000);		
		TRACELNF("START");
		#endif

		/* all tasks works simulatenously */
		addProcess(PRC_DUMB1);
		addProcess(PRC_DUMB2);
		addProcess(PRC_DUMB3);
	};
	
	public:
		//@implement
		ProcessFactory getFactory(uint16_t pId) {
			const static ProcessFactoryReg factoryList[] = {	//	factories list
				FACTORY(PRC_DUMB1, Dumb1Process)
				,FACTORY(PRC_DUMB2, Dumb2Process)
				,FACTORY(PRC_DUMB3, Dumb3Process)
			};

			int len = *(&factoryList + 1) - factoryList;	//TOTAL_FACTORIES_INCLUDED
			for (byte i = 0; i < len; i++) {
				if (factoryList[i].id == pId) {
					return factoryList[i].factory;
				}
			}
			return NULL;
		}

		//@implement
		static IFirmware* get() {
			if (IFirmware::instance == NULL) {
				IFirmware::instance = new ExampleFirmware();
			}
			return IFirmware::instance;
		}

};

#endif
