#include "pwrconsumer3process.h"
#include "pwrconsumer_process.h"
#include "processy_cfg.h"

PwrConsumer3Process::PwrConsumer3Process(uint16_t pId, IProcessMessage* msg) : PwrConsumerProcess(10, taskId, (*(&taskId + 1) - taskId), pId, msg){
    TRACELNF("PwrConsumer3Process::init");
}

static IFirmwareProcess* PwrConsumer3Process::factory(uint16_t pId, IProcessMessage* msg) {
    TRACELNF("PwrConsumer3Process::factory");
    return new PwrConsumer3Process(pId, msg);
}

bool PwrConsumer3Process::handleMessageLogic(IProcessMessage* msg) {
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
