/**
 * Power Consuming Management Process (GROUP2)
 * for Processy Firmware Framework
 */

#ifndef _PWRCONSUMER2_PROCESS_H
#define _PWRCONSUMER2_PROCESS_H

    #include "processy.h"
    #include "processy_process.h"
    #include "processy_cfg.h"

    #include "examplefirmware.h"
    #include "messages.h"
    #include "pwrconsumer_process.h"
    #include "examplefirmware_cfg.h"

    #include "dumb2_process.h"
    
    /**
     * Process consists of 2 task, pwr switch at pin 11
     */
    class PwrConsumer2Process: public PwrConsumerProcess {
        public:
            PROCESSID(PRC_CONSUMER2);

            //@implement
            //@include "pwrconsumer_process.h"
            PwrConsumer2Process(IProcessMessage* msg): PwrConsumerProcess(11, msg) {
				addTask(PRC_DUMB2);
                TRACELNF("PwrConsumer2Process::init");
            }

            //@implement
            static IFirmwareProcess* factory(IProcessMessage* msg) {
                TRACELNF("PwrConsumer2Process::factory");
                return new PwrConsumer2Process(msg);
            }

            //@implement
            //@include "processy_cfg.h"
            bool handleMessageLogic(IProcessMessage* msg) {
                return false;
            }

            uint16_t getNextConsumerId() {
                return PRC_CONSUMER3;
            }
    };

#endif