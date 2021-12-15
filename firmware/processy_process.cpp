#include "processy_process.h"
#include "processy_cfg.h"
#include "stuff.h"
#include <Arduino.h>
#include "processy.h"

IFirmwareProcess::IFirmwareProcess(uint16_t pId, IProcessMessage* msg) {
	this->processId = pId;
	this->lastUpdate = millis();
	#ifdef DEBUG_PRO_MS
	this->resetUsedMs();
	#endif
	this->pausedUpTo = 0;
	this->state = ProcessState::ACTIVE;
	this->handleMessage(msg);
}

bool IFirmwareProcess::isId(int compareTo) {
	return this->processId == compareTo;
}

void IFirmwareProcess::stop() {
	this->state = ProcessState::STOP;
}

unsigned long IFirmwareProcess::run(unsigned long start) {
	unsigned long ms = start - this->lastUpdate;
	this->update(ms);
	unsigned long endTime = millis();
	#ifdef DEBUG_PRO_MS
	this->usedMs += endTime - start;
	#endif
	this->lastUpdate = endTime;
	return endTime;
}

void IFirmwareProcess::pause(unsigned long upTo = 0) {
	if (this->state == ProcessState::STOP) return;
	this->state = ProcessState::PAUSE;
	this->pausedUpTo = millis() + upTo;
}

void IFirmwareProcess::unPause() {
	if (this->state == ProcessState::STOP) return;
	this->state = ProcessState::ACTIVE;
	this->pausedUpTo = 0;
}

bool IFirmwareProcess::handleMessage(IProcessMessage* msg) {
	return false;
};

IFirmware* IFirmwareProcess::getHost() {
	return IFirmware::get();
}
