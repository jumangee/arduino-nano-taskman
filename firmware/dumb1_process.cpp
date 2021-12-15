#include "dumb1_process.h"

Dumb1Process::Dumb1Process(uint16_t pId, IProcessMessage* msg) : IFirmwareProcess(pId, msg){
	TRACELNF("Dumb1Process::init");
            randomSeed(analogRead(0));
}

static IFirmwareProcess* Dumb1Process::factory(uint16_t pId, IProcessMessage* msg) {
	TRACELNF("Dumb1Process::factory");
	return new Dumb1Process(pId, msg);
}

void Dumb1Process::update(unsigned long ms) {
	if (random(50) == 10) {
		this->getHost()->sendMessage(new TaskDoneMessage(PRC_DUMB1));
	}
	else
		this->pause(450);
}

Dumb1Process::~Dumb1Process() {
	// stop process
	TRACELNF("Dumb1Process::stop");
}
