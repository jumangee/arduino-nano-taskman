/**
 * MHZ19 sensor process
 * for Processy Firmware Framework
 */
 
#ifndef _MHZ19_SENSOR_PROCESS_H
#define _MHZ19_SENSOR_PROCESS_H

#include "processy.h"
#include "processy_process.h"

#include "examplefirmware_cfg.h"

#define WAIT_READ_TIMES	100
#define WAIT_READ_DELAY	10

#define MHZ19_RXPIN 4
#define MHZ19_TXPIN 5
#define MHZ19_CMDSIZE 9

#include "SoftwareSerial.h"

class MHZ19SensorProcess: public IFirmwareProcess {
    protected:
		bool			mhz19active;
        SoftwareSerial  swSerial = SoftwareSerial(MHZ19_RXPIN, MHZ19_TXPIN);

        int co2 = 0;
        int temp = 0;
        int status = -1;

        static uint8_t CMD_GETPPM[MHZ19_CMDSIZE];
        static uint8_t CMD_SETRNG[MHZ19_CMDSIZE];
        static uint8_t CMD_AUTOCALOFF[MHZ19_CMDSIZE];


	public:
        PROCESSID(PRC_MHZ19);

		MHZ19SensorProcess(IProcessMessage* msg);

		static IFirmwareProcess* factory(IProcessMessage* msg);

		void update(unsigned long ms);
    
    protected:
        void sendCommand(uint8_t cmd[], uint8_t* response = NULL);

        void getResponse();

};

#endif
