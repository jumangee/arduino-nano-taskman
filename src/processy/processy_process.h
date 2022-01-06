/*
* Processy Framework
*/

#ifndef _FIRMWARE_FRAMEWORK_PROCESS_H
#define _FIRMWARE_FRAMEWORK_PROCESS_H

class IProcessMessage;
class IFirmware;

#include "processy_cfg.h"
#include <Arduino.h>

#define PROCESSID(num) const static uint16_t ID = num; uint16_t getId() {return num;}

class IFirmwareProcess {
	public:
		enum ProcessState {
			DUMMY	= 0,
			ACTIVE	= 1,
			PAUSE	= 2,
			STOP	= 3
		};
	private:
 		ProcessState state;

	public:
		//@implement
		//@include "processy_cfg.h"
		//@include "stuff.h"
		//@include <Arduino.h>
		IFirmwareProcess(IProcessMessage* msg) {
			//this->processId = pId;
			this->lastUpdate = millis();
			#ifdef DEBUG_PRO_MS
			this->resetUsedMs();
			#endif
			this->pausedUpTo = 0;
			this->state = ProcessState::ACTIVE;
			this->handleMessage(msg);
		}

		IFirmwareProcess::ProcessState getState() {
			return this->state;
		}

		static IFirmwareProcess* factory(IProcessMessage* msg);

		/**
		 * @brief Get the Id of the process
		 * 
		 * @return uint16_t 
		 */
		virtual uint16_t getId() {};

		//@implement
		void stop() {
			this->state = ProcessState::STOP;
		}

		//@implement
		virtual bool isPaused(unsigned long start) {
			if (this->state == ProcessState::PAUSE) {
				if (start < this->pausedUpTo) {
					return true;
				}
				this->unPause();
			}
			return false;
		}

		//@implement
		//@include "processy_cfg.h"
		//@include "stuff.h"
		//@include <Arduino.h>
		virtual unsigned long run(unsigned long start) {
			unsigned long ms = start - this->lastUpdate;
			this->update(ms);
			unsigned long endTime = millis();
			#ifdef DEBUG_PRO_MS
			this->usedMs += endTime - start;
			#endif
			this->lastUpdate = endTime;
			return endTime;
		}

		virtual void update(unsigned long ms) = 0;

		//@implement
		virtual void pause(unsigned long upTo = 0) {
			if (this->state == ProcessState::STOP) return;

			this->state = ProcessState::PAUSE;
			this->pausedUpTo = millis() + upTo;
		}

		//@implement
		virtual void unPause() {
			if (this->state == ProcessState::STOP) return;

			this->state = ProcessState::ACTIVE;
			this->pausedUpTo = 0;
		}

		//@implement
		virtual bool handleMessage(IProcessMessage* msg) {
			return false;
		};

		//@implement
		void sendMessage(IProcessMessage* msg) {
			if (msg != NULL) {
				this->getHost()->sendMessage(msg);
			}
		};

	private:
		//uint16_t processId;
		unsigned long lastUpdate;
		unsigned long pausedUpTo;

		#ifdef DEBUG_PRO_MS
		unsigned long usedMs;
		#endif

	protected:
		//@implement
		//@include "processy.h"
		IFirmware* getHost(){
			return IFirmware::get();
		}

	public:
		#ifdef DEBUG_PRO_MS
		unsigned long getUsedMs() {
		  return this->usedMs;
		}

		void resetUsedMs() {
		  this->usedMs = 0;
		}
		#endif
};


#endif
