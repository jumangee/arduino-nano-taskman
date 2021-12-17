#include "ppd42ns_process.h"

ParticlePPD42SensorProcess::ParticlePPD42SensorProcess(IProcessMessage* msg) : IFirmwareProcess(msg){
            this->active = true;
	// pin mode
	pinMode(MEASURE_PM1_PIN,INPUT);
	pinMode(MEASURE_PM2_PIN,INPUT);
	TRACELNF("ParticlePPD42SensorProcess: pre-burn timeout")
	this->pause(60000);
}

static IFirmwareProcess* ParticlePPD42SensorProcess::factory(IProcessMessage* msg) {
	return new ParticlePPD42SensorProcess(msg);
}

void ParticlePPD42SensorProcess::update(unsigned long ms) {
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
