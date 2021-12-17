/**
 * Processy Firmware Framework Core
 */

#ifndef _FIRMWARE_FRAMEWORK_H
#define _FIRMWARE_FRAMEWORK_H

#include "LinkedList/LinkedList.h"

#include "processy_cfg.h"
#include "processy_process.h"
#include "processy_message.h"
#include <math.h>

#define FACTORY(className) ProcessFactoryReg(className::ID, &className::factory)

typedef IFirmwareProcess* (*ProcessFactory)(IProcessMessage*);

class ProcessFactoryReg {
	public:
		uint16_t 		id;
		ProcessFactory	factory;

		ProcessFactoryReg(uint16_t pId, ProcessFactory f) {
			this->id = pId;
			this->factory = f;
		}
};

class IFirmware {
	protected:
		static IFirmware* instance;

		IFirmware();

	public:
		static IFirmware* get() {
			return IFirmware::instance;
		}

		virtual ProcessFactory getFactory(uint16_t pId) = 0;

		IFirmwareProcess* getProcess(uint16_t pId);

		void stopProcess(uint16_t pId);

		void pauseProcess(uint16_t pId, unsigned long pauseTime);

		void unPauseProcess(uint16_t pId);

		void stopAll();

		void soloProcess(uint16_t pId);

		void sendMessage(IProcessMessage* msg);

		void run();

		void addProcess(uint16_t pId, IProcessMessage* msg = NULL);

	protected:
		LinkedList<IFirmwareProcess*> processList;

		#ifdef DEBUG_PRO_MS
		unsigned long msDebugTimerStart;

		void resetMsDebugTimer(unsigned long val) {
			this->msDebugTimerStart = val;
		}
		#endif

		void handlerProcessDebugTimer(unsigned long dT);

		#ifdef DEBUG_PRO_MS
		void resetProcessMsTotal() {
			for (int i = 0; i < this->processList.size(); i++) {
				//IFirmwareProcess* process = ;
				this->processList.get(i)->resetUsedMs();
			}
		}
		#endif

		bool update(unsigned long ms);

		IFirmwareProcess* createProcess(uint16_t pId, IProcessMessage* msg);

		int findProcess(uint16_t pId);

};

#endif
