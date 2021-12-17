#include "pwrconsumer2process.h"
#include "pwrconsumer_process.h"
#include "processy_cfg.h"

PwrConsumer2Process::PwrConsumer2Process(IProcessMessage* msg) : PwrConsumerProcess(11, taskId, (*(&taskId + 1) - taskId), msg){
    TRACELNF("PwrConsumer2Process::init");
}

static IFirmwareProcess* PwrConsumer2Process::factory(IProcessMessage* msg) {
    TRACELNF("PwrConsumer2Process::factory");
    return new PwrConsumer2Process(msg);
}

bool PwrConsumer2Process::handleMessageLogic(IProcessMessage* msg) {
    return false;
}
