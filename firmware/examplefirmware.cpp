#include "examplefirmware.h"
#include <Arduino.h>

const static byte ExampleFirmware::PwrMngmtPins[] = PWRMNGMTPINS;
ExampleFirmware::ExampleFirmware() : IFirmware(){
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

ProcessFactory ExampleFirmware::getFactory(uint16_t pId) {
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

static IFirmware* ExampleFirmware::get() {
	if (IFirmware::instance == NULL) {
		IFirmware::instance = new ExampleFirmware();
	}
	return IFirmware::instance;
}
