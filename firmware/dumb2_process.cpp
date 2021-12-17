#include "dumb2_process.h"

Dumb2Process::Dumb2Process(IProcessMessage* msg) : IFirmwareProcess(msg){
	TRACELNF("Dumb2Process::init");
}

static IFirmwareProcess* Dumb2Process::factory(IProcessMessage* msg) {
	TRACELNF("Dumb2Process::factory");
	return new Dumb2Process(msg);
}

void Dumb2Process::update(unsigned long ms) {
	if (random(50) == 10) {
		this->getHost()->sendMessage(new TaskDoneMessage(this));
	}
	else
		this->pause(450);
}
