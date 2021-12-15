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
            //@implement
            //@include "pwrconsumer_process.h"
            PwrConsumer1Process(uint16_t pId, IProcessMessage* msg): PwrConsumerProcess(12, taskId, (*(&taskId + 1) - taskId), pId, msg) {
                TRACELNF("PwrConsumer1Process::init")
            }

            //@implement
            //@include "processy_cfg.h"
            static IFirmwareProcess* factory(uint16_t pId, IProcessMessage* msg) {
                TRACELNF("PwrConsumer1Process::factory");
                return new PwrConsumer1Process(pId, msg);
            }

            //@implement
            bool handleMessageLogic(IProcessMessage* msg) {
                switch (msg->getType())
                {
                    case TASKDONE_MESSAGE: { // DUMB1
                        TRACELNF("handleMessage:TASKDONE_MESSAGE")
                        this->taskDone(((TaskDoneMessage*)msg)->getTaskId());
                        break;
                    }
                }
                return false;
            }
    };

#endif