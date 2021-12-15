#include "pwrconsumer2process.h"
#include "pwrconsumer_process.h"
#include "processy_cfg.h"

PwrConsumer2Process::PwrConsumer2Process(uint16_t pId, IProcessMessage* msg) : PwrConsumerProcess(11, taskId, (*(&taskId + 1) - taskId), pId, msg){
    TRACELNF("PwrConsumer2Process::init");
}

static IFirmwareProcess* PwrConsumer2Process::factory(uint16_t pId, IProcessMessage* msg) {
    TRACELNF("PwrConsumer2Process::factory");
    return new PwrConsumer2Process(pId, msg);
}

bool PwrConsumer2Process::handleMessageLogic(IProcessMessage* msg) {
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
