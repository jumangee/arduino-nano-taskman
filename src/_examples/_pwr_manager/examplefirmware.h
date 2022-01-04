/**
 * Application class (examplefirmware)
 * for Processy Firmware Framework
 */
#ifndef _EXAMPLEFIRMWARE_H
#define _EXAMPLEFIRMWARE_H

#include "examplefirmware_cfg.h"
#include "processy_cfg.h"
#include "processy.h"

#include "pwrload_mngmnt.h"

// ---[ PROCESSES ]---
#include "examplefirmware_main.h"
#include "pwrconsumer_process.h"
#include "pwrconsumer1process.h"
#include "pwrconsumer2process.h"
#include "pwrconsumer3process.h"
#include "dumb1_process.h"
#include "dumb2_process.h"
#include "dumb3_process.h"
// -------------------

#include "messages.h"

//#include "stuff.h"

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

		analogReference(EXTERNAL);	// important for EcoSense@clock scheme

		PowerloadManagement::init(ARR2PTR(ExampleFirmware::PwrMngmtPins));

		PROCESS_REG(MainProcess);

		PROCESS_REG(PwrConsumer1Process);
		PROCESS_REG(PwrConsumer2Process);
		PROCESS_REG(PwrConsumer3Process);

		PROCESS_REG(Dumb1Process);
		PROCESS_REG(Dumb2Process);
		PROCESS_REG(Dumb3Process);

		// one pwr manager process should be started to handle start message
		addProcess(PRC_CONSUMER1);

		TRACELNF("Power management: STARTED");
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
