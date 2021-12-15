/**
 * Display process
 * for Processy Firmware Framework
 */

#ifndef _EXAMPLEFIRMWARE_MAIN_H
#define _EXAMPLEFIRMWARE_MAIN_H

#include "processy.h"
#include "processy_process.h"

#include "examplefirmware.h"
#include "messages.h"

#include <Arduino.h>

#define INCLUDE_SCROLLING 0

#include <SSD1306Ascii.h>

#undef OPTIMIZE_I2C
#define OPTIMIZE_I2C 0
#undef INCLUDE_SCROLLING
#define INCLUDE_SCROLLING 0

#include <SSD1306AsciiWire.h>

#include <math.h>
#include "stuff.h"

#define OLED_ADDR   0x3C

//#define MAIN_FONT System5x7
//#define MAIN_FONT Stang5x7
#define MAIN_FONT fixednums7x15

class MainProcess: public IFirmwareProcess {
	private:
		SSD1306AsciiWire oled;
		bool	updateScreen;
		String	curPrcId;

	public:
		//@implement
		//@include <SSD1306AsciiWire.h>
		MainProcess(uint16_t pId, IProcessMessage* msg): IFirmwareProcess(pId, msg) {
			TRACELNF("MainProcess::start");

			Wire.setClock(400000L);
			oled.begin(&Adafruit128x64, OLED_ADDR);
			oled.clear();
			oled.setFont(MAIN_FONT);
			//oled.print(F("CTAPT..."));	// no chars in font ((
			this->curPrcId = String(F("0"));

			this->updateScreen = true;
		}

		//@implement
		static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg) {
			TRACELNF("MainProcess::factory");
			return new MainProcess(pId, msg);
		}

		//@implement
		~MainProcess() {
			// stop process
			TRACELNF("MainProcess::stop");
		}

		//@implement
		void update(unsigned long ms) {
			if (this->updateScreen) {
				this->render();
				this->updateScreen = false;
			}

			this->pause(10);
		}

		void prn2X(String s) {
			oled.set2X();
			oled.print(s);
			oled.set1X();
		}

		//@implement
		//@include <SSD1306AsciiWire.h>
		void render() {
			oled.clear();
			prn2X(this->curPrcId);
		}

		//@implement
		bool handleMessage(IProcessMessage* msg) {
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


		void prn(char c) {
			oled.print(c);
		}
};

#endif
