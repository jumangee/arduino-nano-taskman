/**
 * Power Consuming Management Process (GROUP1)
 * for Processy Firmware Framework
 */

#ifndef _PWRCONSUMER1_PROCESS_H
#define _PWRCONSUMER1_PROCESS_H

    #include "processy.h"
    #include "processy_process.h"
    #include "processy_cfg.h"

    #include "examplefirmware.h"
    #include "messages.h"
    #include "pwrconsumer_process.h"
    #include "examplefirmware_cfg.h"

    /**
     * Process consists of 1 task, pwr switch at pin 12
     */
    class PwrConsumer1Process: public PwrConsumerProcess {
        private:
            const uint16_t taskId[1] = {PRC_DUMB1};

        public:
            PwrConsumer1Process(uint16_t pId, IProcessMessage* msg);

            static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg);

            bool handleMessageLogic(IProcessMessage* msg);
    };

#endif