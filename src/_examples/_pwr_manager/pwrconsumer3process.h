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
            //@implement
            //@include "pwrconsumer_process.h"
            PwrConsumer3Process(uint16_t pId, IProcessMessage* msg): PwrConsumerProcess(10, taskId, (*(&taskId + 1) - taskId), pId, msg) { 
                TRACELNF("PwrConsumer3Process::init");
            }

            //@implement
            //@include "processy_cfg.h"
            static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg) {
                TRACELNF("PwrConsumer3Process::factory");
                return new PwrConsumer3Process(pId, msg);
            }

            //@implement
            //@include "processy_cfg.h"
            bool handleMessageLogic(IProcessMessage* msg) {
                switch (msg->getType())
                {
                    case TASKDONE_MESSAGE: { // DUMB3
                        TRACELNF("handleMessage:TASKDONE_MESSAGE")
                        this->taskDone(((TaskDoneMessage*)msg)->getTaskId());
                        break;
                    }
                }
                return false;
            }

    };

#endif