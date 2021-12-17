#include "examplefirmware_main.h"
#include <SSD1306AsciiWire.h>

DisplayServiceProcess::DisplayServiceProcess(IProcessMessage* msg) : IFirmwareProcess(msg){
	TRACELNF("DisplayServiceProcess::start");
	Wire.setClock(400000L);
	oled.begin(&Adafruit128x64, OLED_ADDR);
	oled.clear();
	oled.setFont(MAIN_FONT);
	//oled.print(F("CTAPT..."));	// no chars in font ((
	this->curPrcId = String(F("0"));
	this->updateScreen = true;
}

static IFirmwareProcess* DisplayServiceProcess::factory(IProcessMessage* msg) {
	return new DisplayServiceProcess(msg);
}

void DisplayServiceProcess::update(unsigned long ms) {
	if (this->updateScreen) {
		this->render();
		this->updateScreen = false;
	}
	this->pause(10);
}

void DisplayServiceProcess::render() {
	oled.clear();
	prn2X(this->curPrcId);
}

bool DisplayServiceProcess::handleMessage(IProcessMessage* msg) {
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
	}
	return false;
}
