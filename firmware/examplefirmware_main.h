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

class DisplayServiceProcess: public IFirmwareProcess {
	private:
		SSD1306AsciiWire oled;
		bool	updateScreen;
		String	curPrcId;

	public:
		PROCESSID(PRC_MAIN);

		DisplayServiceProcess(IProcessMessage* msg);

		static IFirmwareProcess* factory(IProcessMessage* msg);

		void update(unsigned long ms);

		void prn2X(String s) {
			oled.set2X();
			oled.print(s);
			oled.set1X();
		}

		void render();

		bool handleMessage(IProcessMessage* msg);


		void prn(char c) {
			oled.print(c);
		}
};

#endif
