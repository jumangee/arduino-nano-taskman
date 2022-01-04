/**
 * Power Consuming Management Process (GROUP1)
 * for Processy Firmware Framework
 */

#ifndef _PWRCONSUMER1_PROCESS_H
#define _PWRCONSUMER1_PROCESS_H

    #include "processy.h"
    #include "processy_process.h"
    #include "processy_cfg.h"

    #include "examplefirmware_cfg.h"
    #include "examplefirmware.h"
    #include "messages.h"
    #include "pwrconsumer_process.h"

    /**
     * Process consists of 1 task, pwr switch at pin 12
     */
    class PwrConsumer1Process: public PwrConsumerProcess {
        public:
            PROCESSID(PRC_CONSUMER1);
            
            //@implement
            //@include "pwrconsumer_process.h"
            PwrConsumer1Process(IProcessMessage* msg): PwrConsumerProcess(12, msg) {
				addTask(PRC_PPD42NS);
                TRACELNF("PwrConsumer1Process::init")
            }

            //@implement
            //@include "processy_cfg.h"
            static IFirmwareProcess* factory(IProcessMessage* msg) {
                TRACELNF("PwrConsumer1Process::factory");
                return new PwrConsumer1Process(msg);
            }

            //@implement
            bool handleMessageLogic(IProcessMessage* msg) {
                return false;
            }

            uint16_t getNextConsumerId() {
                return PRC_CONSUMER2;
            }
    };

#endif