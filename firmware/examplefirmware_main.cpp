#include "examplefirmware_main.h"
#include <SSD1306AsciiWire.h>

MainProcess::MainProcess(uint16_t pId, IProcessMessage* msg) : IFirmwareProcess(pId, msg){
	TRACELNF("MainProcess::start");
	Wire.setClock(400000L);
	oled.begin(&Adafruit128x64, OLED_ADDR);
	oled.clear();
	oled.setFont(MAIN_FONT);
	//oled.print(F("CTAPT..."));	// no chars in font ((
	this->curPrcId = String(F("0"));
	this->updateScreen = true;
}

static IFirmwareProcess* MainProcess::factory(uint16_t pId, IProcessMessage* msg) {
	TRACELNF("MainProcess::factory");
	return new MainProcess(pId, msg);
}

MainProcess::~MainProcess() {
	// stop process
	TRACELNF("MainProcess::stop");
}

void MainProcess::update(unsigned long ms) {
	if (this->updateScreen) {
		this->render();
		this->updateScreen = false;
	}
	this->pause(10);
}

void MainProcess::render() {
	oled.clear();
	prn2X(this->curPrcId);
}

bool MainProcess::handleMessage(IProcessMessage* msg) {
	//TRACELNF("HANDLE MSG (MAIN)")
	switch (msg->getType())
	{
		case PRC_ORDER_MESSAGE: {
			//TRACELNF("PRC_ORDER_MESSAGE!")
			ProcessOrderMessage* nextPrcMsg = (ProcessOrderMessage*)msg;
			curPrcId = String( ((ProcessOrderMessage*)msg)->getNextId() );
			this->updateScreen = true;
			break;
		}
		/*case CURTIME_MESSAGE: {
			this->handleTimeMsg((CurrentTimeMsg*)msg);
			return true; // dispose
		}*/
	}
	return false;
}
