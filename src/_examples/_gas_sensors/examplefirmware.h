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
#include "mhz19sensor.h"
#include "dumb2_process.h"
#include "dumb3_process.h"

#include "examplefirmware_main.h"

#include "pwrconsumer_process.h"
#include "pwrconsumer1process.h"
#include "pwrconsumer2process.h"
#include "pwrconsumer3process.h"
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

		analogReference(EXTERNAL);	// important for EcoSense@clock scheme

		PowerloadManagement::init(ARR2PTR(ExampleFirmware::PwrMngmtPins));

		addProcess(PRC_MAIN);

		// one pwr manager process should be started to handle start message
		addProcess(PRC_CONSUMER1, ProcessOrderMessage::start());

		TRACELNF("Power management: STARTED");
	};
	
	public:
		//@implement
		ProcessFactory getFactory(uint16_t pId) {
			const static ProcessFactoryReg factoryList[] = {	//	factories list
				FACTORY(DisplayServiceProcess)

				,FACTORY(PwrConsumer1Process)
				,FACTORY(PwrConsumer2Process)
				,FACTORY(PwrConsumer3Process)

				,FACTORY(MHZ19SensorProcess)
				,FACTORY(Dumb2Process)
				,FACTORY(Dumb3Process)
			};

			const static uint8_t len = *(&factoryList + 1) - factoryList;	//TOTAL_FACTORIES_INCLUDED
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
