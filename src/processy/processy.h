/**
 * Processy Firmware Framework Core
 */

#ifndef _FIRMWARE_FRAMEWORK_H
#define _FIRMWARE_FRAMEWORK_H

#include "processy_cfg.h"
#include "processy_process.h"
#include "processy_message.h"
#include <math.h>

typedef IFirmwareProcess* (*ProcessFactory)(IProcessMessage*);

#define PROCESS_REG(className) registerProcess(className::ID, &className::factory)

struct IFirmwareProcessRegistration {
	public:
		uint16_t 			id;
		ProcessFactory		factory;
		IFirmwareProcess*	prc;

		IFirmwareProcessRegistration(uint16_t pId, ProcessFactory f) {
			id = pId;
			factory = f;
			prc = NULL;
		}

		void kill() {
			if (prc != NULL) {
				delete this->prc;
				this->prc = NULL;
			}
		}

		bool isActive() {
			return prc != NULL;
		}
};

class IFirmware {
	protected:
		static IFirmware*				instance;
		IFirmwareProcessRegistration*	processList[PROCESSY_MAX_LIST];
		uint16_t						processListSize = 0;

		IFirmware() {
			#ifdef DEBUG_PRO_MS
			this->resetMsDebugTimer(millis());
			#endif
		}

	public:
		static IFirmware* get() {
			return IFirmware::instance;
		}

		//@implement
		IFirmwareProcess* getProcess(uint16_t pId) {
			int pos = this->findProcess(pId);
			return pos > -1 ? this->processList[pos]->prc : NULL;
		}

		//@implement
		void stopProcess(uint16_t pId) {
			IFirmwareProcessRegistration* reg = this->findRegistration(pId);
			if (reg != NULL && reg->isActive()) {
				reg->prc->stop();
			}
		}

		//@implement
		void pauseProcess(uint16_t pId, unsigned long pauseTime) {
			IFirmwareProcessRegistration* reg = this->findRegistration(pId);
			if (reg != NULL) {
				reg->prc->pause(pauseTime);
			}
		}

		//@implement
		void unPauseProcess(uint16_t pId) {
			IFirmwareProcessRegistration* reg = this->findRegistration(pId);
			if (reg != NULL) {
				reg->prc->unPause();
			}
		}

		//@implement
		void stopAll() {
			for (uint16_t i = 0; i < this->processListSize; i++) {
				this->processList[i]->kill();
			}
		}

		//@implement
		void soloProcess(uint16_t pId) {
			this->stopAll();
			this->addProcess(pId);
		}

		//@implement
		void sendMessage(IProcessMessage* msg) {
			if (msg == NULL) return;

			for (uint16_t i = 0; i < processListSize; i++) {
				IFirmwareProcessRegistration* reg = this->processList[i];
				if (reg->isActive()) {	// message processing stop
					if (reg->prc->handleMessage(msg) == true) {
						break;
					}
				}
			}
			delete msg;
		}

		//@implement
		//@include "processy_cfg.h"
		void run() {
			unsigned long curTime = millis();
			if (this->update(curTime)) {	// true - auto process, false - manual process
				curTime = millis();
				for (uint16_t i = 0; i < processListSize; i++) {
					IFirmwareProcessRegistration* reg = this->processList[i];
					if (reg->isActive()) {
						if (reg->prc->getState() == IFirmwareProcess::ProcessState::STOP) {
							reg->kill();
						} else if (!reg->prc->isPaused(curTime)) {
							curTime = reg->prc->run(curTime);
						}
					}
				}

				// safely kill stopped processes
				/*for (uint16_t i = 0; i < this->processListSize; i++) {
					IFirmwareProcessRegistration* reg = this->processList[i];
					if (reg->isActive() && reg->prc->getState() == IFirmwareProcess::ProcessState::STOP) {
						reg->kill();
					}
				}*/
			}
			#ifdef DEBUG_PRO_MS > 0
			unsigned long dT = curTime - msDebugTimerStart;
			if (dT >= DEBUG_PRO_PERIOD_MS) {
				// call report
				handlerProcessDebugTimer(dT);
				this->resetMsDebugTimer(millis());
			}
			#endif
		}

		//@implement
		void addProcess(uint16_t pId, IProcessMessage* msg = NULL) {
			int i = findProcess(pId);
			if (i > -1) {
				IFirmwareProcessRegistration* reg = this->processList[i];
				if (!reg->isActive()) {
					reg->prc = reg->factory(msg);
					if (msg != NULL) {
						delete msg;
					}
				}
			}
		}

	protected:
		#ifdef DEBUG_PRO_MS
		unsigned long msDebugTimerStart;

		void resetMsDebugTimer(unsigned long val) {
			this->msDebugTimerStart = val;
		}
		#endif

		//@implement
		//@include "stuff.h"
		//@include "MemoryFree.h"
		virtual void handlerProcessDebugTimer(unsigned long dT) {
			#if DEBUG_PRO_MS == 1
				#if PROCESSY_DEBUG_SERIAL == 1
				TRACEF("----- PROC SUMMARY (for ");
				TRACE(dT);
				TRACELNF("ms) -----");
				for (uint16_t i = 0; i < this->processListSize; i++) {
					IFirmwareProcessRegistration* reg = this->processList[i];
					if (reg->isActive()) {
						uint32_t used = reg->prc->getUsedMs();
						TRACE(reg->id)
						TRACEF(": ")
						TRACE(used)
						TRACEF("ms (");
						TRACE(round((used * 100) / dT))
						TRACELNF("%)");
						reg->prc->resetUsedMs();
					}
				}
				#endif
			int free = freeMemory();
			this->sendMessage(new MemUsageMessage(free));
			TRACEF("MEM FREE:");
			TRACELN(free)
			TRACELNF("--------------------------------------");
			#endif
		}

		//@implement
		bool update(unsigned long ms) {
			return true;
		};

		//@implement
		int findProcess(uint16_t pId) {
			for (uint16_t i = 0; i < processListSize; i++) {
				if (this->processList[i]->id == pId) {
					return i;
				}
			}
			return -1;
		}

		//@implement
		IFirmwareProcessRegistration* findRegistration(uint16_t pId) {
			for (uint16_t i = 0; i < processListSize; i++) {
				if (this->processList[i]->id == pId) {
					return this->processList[i];
				}
			}
			return NULL;
		}

		//@implement
		void registerProcess(uint16_t pId, ProcessFactory f) {
			this->processList[this->processListSize] = new IFirmwareProcessRegistration(pId, f);
			this->processListSize++;
		}

};

#endif
