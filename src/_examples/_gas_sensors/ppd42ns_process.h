/**
 * PPD42NS air quality sensor process
 * for Processy Firmware Framework
 */

#ifndef _PPD42NS_PROCESS_H
#define _PPD42NS_PROCESS_H

#include "processy.h"
#include "processy_process.h"
#include "messages.h"

#include "examplefirmware_cfg.h"

#include <Arduino.h>

#define MEASURE_PM1_PIN 7
#define MEASURE_PM2_PIN 6
#define SAMPLE_TIME_MS 15000

// number of reads before completion (uses average value!)
#define READS_COUNT 3

class ParticlePPD42SensorProcess: public IFirmwareProcess {
	private:
        bool active;

		byte currentSample = 0;
		byte currentMeasureMode = 0;

		struct PPD42SampleData {
			float ratioPm1;
			float ratioPm2;
			float concentrationPm1;
			float concentrationPm2;
		};

		PPD42SampleData samples[READS_COUNT];

		unsigned long lowpulseoccupancy = 0;
		unsigned long sampleTotalTime = 0;

	public:
		PROCESSID(PRC_PPD42NS);

		//@implement
		ParticlePPD42SensorProcess(IProcessMessage* msg): IFirmwareProcess(msg) {
            this->active = true;

			// pin mode
			pinMode(MEASURE_PM1_PIN,INPUT);
			pinMode(MEASURE_PM2_PIN,INPUT);

			TRACELNF("ParticlePPD42SensorProcess: pre-burn timeout")
			this->pause(60000);
		}

		//@implement
		static IFirmwareProcess* factory(IProcessMessage* msg) {
			return new ParticlePPD42SensorProcess(msg);
		}

		/**
		 * @brief Marks this process as paused, sends message to all with results and notify PRC1_CONSUMER (parent) finished
		 */
		void done() {
			this->active = false;

			// calc average result

			float resultRatioPm1 = 0;
			float resultRatioPm2 = 0;
			float resultConcPm1 = 0;
			float resultConcPm2 = 0;
			for (byte i = 0; i < READS_COUNT; i++) {
				resultRatioPm1 += samples[i].ratioPm1;
				resultRatioPm2 += samples[i].ratioPm2;
				resultConcPm1 += samples[i].concentrationPm1;
				resultConcPm2 += samples[i].concentrationPm2;
			}

			this->getHost()->sendMessage(new ParticlePPD42Message(resultRatioPm1 / READS_COUNT, resultConcPm1 / READS_COUNT, resultRatioPm2 / READS_COUNT, resultConcPm2 / READS_COUNT));

			this->getHost()->sendMessage(new TaskDoneMessage(this));
			this->pause();
		}

		void saveSampleData() {
				float ratio = this->lowpulseoccupancy/(SAMPLE_TIME_MS*10.0);  // Integer percentage 0=>100
				float concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
				
				TRACEF("mode: ");
				TRACE(this->currentMeasureMode);

				TRACEF(", lowpulseoccupancy: ");
				TRACE(lowpulseoccupancy);
				
				TRACEF(", ratio: ");
				TRACE(ratio);

				TRACEF(", concentration: ");
				TRACELN(concentration);

				if (this->currentMeasureMode == MEASURE_PM1_PIN) {
					samples[this->currentSample].ratioPm1 = ratio;
					samples[this->currentSample].concentrationPm1 = concentration;
					this->currentMeasureMode = MEASURE_PM2_PIN;
				} else {
					samples[this->currentSample].ratioPm2 = ratio;
					samples[this->currentSample].concentrationPm2 = concentration;
					this->currentMeasureMode = MEASURE_PM1_PIN;

					this->currentSample++;
					if (this->currentSample >= READS_COUNT) {
						this->currentSample = 0;

						//stop sampling and process
						this->done();
					}
				}
		}

        //@implement
		void update(unsigned long ms) {
			if (!this->active) {
				return;
			}

			/*unsigned long starttime = millis();
			do {
				TRACE(digitalRead(MEASURE_PM1_PIN))
				TRACEF(", ")
				TRACELN(digitalRead(MEASURE_PM2_PIN));
			} while (millis()-starttime < 1000);*/


			if (this->currentMeasureMode == 0) {
				this->currentMeasureMode = MEASURE_PM1_PIN;
			}

			unsigned long starttime = millis();
			this->lowpulseoccupancy += pulseIn(this->currentMeasureMode, LOW, 1000);

			this->sampleTotalTime += millis()-starttime;

			if ((this->sampleTotalTime) > SAMPLE_TIME_MS)
			{
				this->saveSampleData();

				this->lowpulseoccupancy = 0;
				this->sampleTotalTime = 0;
			}
		}
};

#endif
