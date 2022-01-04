/**
 * Power Consuming Management Process (GROUP3)
 * for Processy Firmware Framework
 */

#ifndef _PWRCONSUMER3_PROCESS_H
#define _PWRCONSUMER3_PROCESS_H

    #include "processy.h"
    #include "processy_process.h"
    #include "processy_cfg.h"

    #include "examplefirmware.h"
    #include "messages.h"
    #include "pwrconsumer_process.h"
    #include "examplefirmware_cfg.h"

    #include "dumb3_process.h"

    /**
     * Process consists of 2 task, pwr switch at pin 10
     */
    class PwrConsumer3Process: public PwrConsumerProcess {
        public:
            PROCESSID(PRC_CONSUMER3);

            //@implement
            //@include "pwrconsumer_process.h"
            PwrConsumer3Process(IProcessMessage* msg): PwrConsumerProcess(10, msg) { 
				addTask(PRC_MHZ19);
                TRACELNF("PwrConsumer3Process::init");
            }

            //@implement
            //@include "processy_cfg.h"
            static IFirmwareProcess* factory(IProcessMessage* msg) {
                TRACELNF("PwrConsumer3Process::factory");
                return new PwrConsumer3Process(msg);
            }

            //@implement
            //@include "processy_cfg.h"
            bool handleMessageLogic(IProcessMessage* msg) {
                return false;
            }

            uint16_t getNextConsumerId() {
                return PRC_CONSUMER1;
            }

    };

#endif