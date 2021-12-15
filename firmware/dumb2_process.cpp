#include "dumb2_process.h"

Dumb2Process::Dumb2Process(uint16_t pId, IProcessMessage* msg) : IFirmwareProcess(pId, msg){
	TRACELNF("Dumb2Process::init");
}

static IFirmwareProcess* Dumb2Process::factory(uint16_t pId, IProcessMessage* msg) {
	TRACELNF("Dumb2Process::factory");
	return new Dumb2Process(pId, msg);
}

void Dumb2Process::update(unsigned long ms) {
	if (random(50) == 10) {
		this->getHost()->sendMessage(new TaskDoneMessage(PRC_DUMB2));
	}
	else
		this->pause(450);
}

Dumb2Process::~Dumb2Process() {
	// stop process
	TRACELNF("Dumb2Process::stop")
}
