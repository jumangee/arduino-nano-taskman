#include "processy.h"

IFirmware* IFirmware::instance = NULL;
#include <Arduino.h>
#include "processy_cfg.h"
#include "stuff.h"
#include "MemoryFree.h"

IFirmware::IFirmware() {
	this->processList = LinkedList<IFirmwareProcess*>();
	#ifdef DEBUG_PRO_MS
	this->resetMsDebugTimer(millis());
	#endif
}

IFirmwareProcess* IFirmware::getProcess(uint16_t pId) {
	int pos = this->findProcess(pId);
	if (pos > -1) {
		return this->processList.get(pos);
	}
	return NULL;
}

void IFirmware::stopProcess(uint16_t pId) {
	int pos = this->findProcess(pId);
	if (pos > -1) {
		this->processList.get(pos)->stop();
	}
}

void IFirmware::pauseProcess(uint16_t pId, unsigned long pauseTime) {
	int pos = this->findProcess(pId);
	if (pos > -1) {
		this->processList.get(pos)->pause(pauseTime);
	}
}

void IFirmware::unPauseProcess(uint16_t pId) {
	int pos = this->findProcess(pId);
	if (pos > -1) {
		IFirmwareProcess *process = this->processList.get(pos);
		process->unPause();
	}
}

void IFirmware::stopAll() {
	this->processList.clear();
}

void IFirmware::soloProcess(uint16_t pId) {
	this->stopAll();
	this->addProcess(pId);
}

void IFirmware::sendMessage(IProcessMessage* msg) {
	if (msg == NULL) return;
	for (int i = 0; i < processList.size(); i++) {
		if (this->processList.get(i)->handleMessage(msg) == true) {	// message processing stop
			break;
		}
	}
	delete msg;
}

void IFirmware::run() {
	if (this->processList.size() == 0) {
		#ifdef DEFAULT_PROCESS
			this->addProcess(F(DEFAULT_PROCESS));
		#else
			TRACELNF("NOTHING TO DO!")
			return;
		#endif
	}
	unsigned long curTime = millis();
	if (this->update(curTime)) {	// true - auto process, false - manual process
		curTime = millis();
		for (int i = 0; i < this->processList.size(); i++) {
			IFirmwareProcess *p = this->processList.get(i);
			if (p->getState() != IFirmwareProcess::ProcessState::STOP && !p->isPaused(curTime)) {
				curTime = p->run(curTime);
			}
		}
		// safely kill stopped processes
		for (int i = this->processList.size()-1; i >= 0; i--) {
			if (this->processList.get(i)->getState() == IFirmwareProcess::ProcessState::STOP) {
				delete this->processList.remove(i);
			}
		}
	}
	#ifdef DEBUG_PRO_MS
	unsigned long dT = curTime - msDebugTimerStart;
	if (dT >= DEBUG_PRO_PERIOD_MS) {
		// call report
		handlerProcessDebugTimer(dT);
		this->resetMsDebugTimer(millis());
	}
	#else
		handlerProcessDebugTimer(0);
	#endif
}

void IFirmware::addProcess(uint16_t pId, IProcessMessage* msg = NULL) {
	if (this->findProcess(pId) > -1) {
		return;	// only 1 instance of process
	}
	IFirmwareProcess* newProcess = this->createProcess(pId, msg);
	if (msg != NULL) {
		delete msg;
	}
	if (newProcess == NULL) {
        		TRACELNF("IFirmware::addProcess ERR")
		return;
	}
	this->processList.add(newProcess);
}

		//*** OVERRIDE THIS ***/
void IFirmware::handlerProcessDebugTimer(unsigned long dT) {
	#ifdef DEBUG_PRO_MS
	{
		TRACEF("----- PROC SUMMARY (for ");
		TRACE(dT);
		TRACELNF("ms) -----");
	}
	for (int i = 0; i < this->processList.size(); i++) {
		IFirmwareProcess* process = processList.get(i);
		{
			uint32_t used = process->getUsedMs();
			TRACE(process->getId())
			TRACEF(": ")
			TRACE(used)
			TRACEF("ms (");
			TRACE(round((used * 100) / dT))
			TRACELNF("%)");
		}
		process->resetUsedMs();
	}
	#endif
	TRACEF("MEM FREE:");
	{
		int free = freeMemory();
		this->sendMessage(new MemUsageMessage(free));
		TRACELN(free)
	}
	TRACELNF("--------------------------------------");
}

bool IFirmware::update(unsigned long ms) {
	return true;
};

IFirmwareProcess* IFirmware::createProcess(uint16_t pId, IProcessMessage* msg) {
	ProcessFactory factory = this->getFactory(pId);
	if (factory != NULL) {
		IFirmwareProcess* t = factory(msg);
		return t;
	}
	return NULL;
}

int IFirmware::findProcess(uint16_t pId) {
	for (int i = 0; i < this->processList.size(); i++) {
		if (this->processList.get(i)->getId() == pId) {
			return i;
		}
	}
	return -1;
}
