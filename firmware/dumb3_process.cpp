#include "dumb3_process.h"

Dumb3Process::Dumb3Process(IProcessMessage* msg) : IFirmwareProcess(msg){
	TRACELNF("Dumb3Process::init");
}

static IFirmwareProcess* Dumb3Process::factory(IProcessMessage* msg) {
	TRACELNF("Dumb3Process::factory");
	return new Dumb3Process(msg);
}

void Dumb3Process::update(unsigned long ms) {
	if (random(50) == 10) {
		this->getHost()->sendMessage(new TaskDoneMessage(this));
	}
	else
		this->pause(450);
}
