#include "dumb3_process.h"

Dumb3Process::Dumb3Process(uint16_t pId, IProcessMessage* msg) : IFirmwareProcess(pId, msg){
	TRACELNF("Dumb3Process::init");
}

static IFirmwareProcess* Dumb3Process::factory(uint16_t pId, IProcessMessage* msg) {
	TRACELNF("Dumb3Process::factory");
	return new Dumb3Process(pId, msg);
}

void Dumb3Process::update(unsigned long ms) {
	if (random(50) == 10) {
		this->getHost()->sendMessage(new TaskDoneMessage(PRC_DUMB3));
	}
	else
		this->pause(450);
}

Dumb3Process::~Dumb3Process() {
	// stop process
	TRACELNF("Dumb3Process::stop")
}
