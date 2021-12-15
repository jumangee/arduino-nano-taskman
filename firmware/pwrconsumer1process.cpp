#include "pwrconsumer1process.h"
#include "pwrconsumer_process.h"
#include "processy_cfg.h"

PwrConsumer1Process::PwrConsumer1Process(uint16_t pId, IProcessMessage* msg) : PwrConsumerProcess(12, taskId, (*(&taskId + 1) - taskId), pId, msg){
    TRACELNF("PwrConsumer1Process::init")
}

static IFirmwareProcess* PwrConsumer1Process::factory(uint16_t pId, IProcessMessage* msg) {
    TRACELNF("PwrConsumer1Process::factory");
    return new PwrConsumer1Process(pId, msg);
}

bool PwrConsumer1Process::handleMessageLogic(IProcessMessage* msg) {
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
