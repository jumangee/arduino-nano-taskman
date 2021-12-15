#ifndef _PINSWITCHMNGR_H
#define _PINSWITCHMNGR_H

    #include <Arduino.h>
    #include "processy_cfg.h"

    #define USEDPIN_NONE 255

    class PinSwitchManager {
        protected:
            PinSwitchManager(byte *pins, byte keysCnt) {
                this->keyPins = pins;
                this->pinsCnt = keysCnt;
                this->currentPin = USEDPIN_NONE;
                this->useStarted = 0;

                for (byte i = 0; i < this->pinsCnt; i++) {
                    TRACELNF("PinSwitchManager:pinMode LOW")
                    pinMode(this->keyPins[i], OUTPUT);
                }

                this->closeAll();
            }

        public:
            /**
             * Request to use pin (start transaction)
             * 0 - fail, >0 - success (open time)
             */
            uint32_t requestPin(byte targetPin);

            /**
             * Turn off previosly opened pin by key from requestPin, or forcibly off any pin
             * (force off: key = 0)
             * true - ok, false - nothing changed!
             */
            bool releasePin(uint32_t & key);

        protected:
            byte                *keyPins;  // arr
            byte                pinsCnt;   // cnt
            uint32_t            useStarted;
            byte                currentPin;

            void closeAll();

            virtual void usePin(byte num);
    };

#endif