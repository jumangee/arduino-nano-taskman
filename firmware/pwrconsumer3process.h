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

    /**
     * Process consists of 2 task, pwr switch at pin 10
     */
    class PwrConsumer3Process: public PwrConsumerProcess {
        private:
            const uint16_t taskId[1] = {PRC_DUMB3};

        public:
            PwrConsumer3Process(uint16_t pId, IProcessMessage* msg);

            static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg);

            bool handleMessageLogic(IProcessMessage* msg);

    };

#endif