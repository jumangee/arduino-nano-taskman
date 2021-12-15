#include "pinswitch_mngmnt.h"

uint32_t PinSwitchManager::requestPin(byte targetPin) {
    /*TRACEF("PinSwitchManager//requestPin: ")
    TRACE(targetPin)
    TRACEF(", cur=")
    TRACELN(currentPin)*/
    if (currentPin == USEDPIN_NONE) {
        this->usePin(targetPin);
        return this->useStarted;
    }
    return 0;
}

bool PinSwitchManager::releasePin(uint32_t & key) {
    /*TRACEF("PinSwitchManager//release: ")
    TRACE(key)
    TRACEF(", current: ")
    TRACELN(this->useStarted)*/
    if (key == 0 || key == this->useStarted) {
        this->closeAll();   // fully off
        //TRACELNF("PinSwitchManager//USEDPIN_NONE")
        return true;
    }
    return false; // nothing changed!
}

void PinSwitchManager::closeAll() {
    for (byte i = 0; i < this->pinsCnt; i++) {
        byte pin = this->keyPins[i];
        /*TRACEF("PinSwitchManager//pinOff: ")
        TRACELN(pin)*/
        digitalWrite(pin, LOW);
    }
    this->useStarted = 0;
    this->currentPin = USEDPIN_NONE;
}

void PinSwitchManager::usePin(byte num) {
    // fully off, then make
    this->closeAll();
    for (byte i = 0; i < this->pinsCnt; i++) {
        byte pin = this->keyPins[i];
        /*TRACEF("PinSwitchManager//check pin=")
        TRACE(pin)
        TRACEF(", to=")
        TRACELN(num)*/
        if (num == pin) {
            digitalWrite(num, HIGH);
            this->currentPin = num;
            this->useStarted = millis();
            /*TRACEF("PinSwitchManager//used pin=")
            TRACELN(currentPin)*/
        }
    }
}
