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


	ExampleFirmware();
	
	public:
		ProcessFactory getFactory(uint16_t pId);

		static IFirmware* get();

};

#endif
