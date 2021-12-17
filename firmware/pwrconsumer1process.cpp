#include "pwrconsumer1process.h"
#include "pwrconsumer_process.h"
#include "processy_cfg.h"

PwrConsumer1Process::PwrConsumer1Process(IProcessMessage* msg) : PwrConsumerProcess(12, taskId, (*(&taskId + 1) - taskId), msg){
    TRACELNF("PwrConsumer1Process::init")
}

static IFirmwareProcess* PwrConsumer1Process::factory(IProcessMessage* msg) {
    TRACELNF("PwrConsumer1Process::factory");
    return new PwrConsumer1Process(msg);
}

bool PwrConsumer1Process::handleMessageLogic(IProcessMessage* msg) {
    return false;
}
