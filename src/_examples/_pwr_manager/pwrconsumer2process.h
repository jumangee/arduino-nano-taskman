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

    /**
     * Process consists of 2 task, pwr switch at pin 11
     */
    class PwrConsumer2Process: public PwrConsumerProcess {
        private:
            const uint16_t taskId[1] = {PRC_DUMB2};

        public:
            //@implement
            //@include "pwrconsumer_process.h"
            PwrConsumer2Process(uint16_t pId, IProcessMessage* msg): PwrConsumerProcess(11, taskId, (*(&taskId + 1) - taskId), pId, msg) {
                TRACELNF("PwrConsumer2Process::init");
            }

            //@implement
            static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg) {
                TRACELNF("PwrConsumer2Process::factory");
                return new PwrConsumer2Process(pId, msg);
            }

            //@implement
            //@include "processy_cfg.h"
            bool handleMessageLogic(IProcessMessage* msg) {
                switch (msg->getType())
                {
                    case TASKDONE_MESSAGE: { // DUMB2
                        TRACELNF("handleMessage:TASKDONE_MESSAGE")
                        this->taskDone(((TaskDoneMessage*)msg)->getTaskId());
                        break;
                    }
                }
                return false;
            }
    };

#endif