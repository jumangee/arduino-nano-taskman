#ifndef _PWRLOADCNTRL_H
#define _PWRLOADCNTRL_H

    #include <Arduino.h>
    #include "processy_cfg.h"
    #include "pinswitch_mngmnt.h"
    
    class PowerloadManagement: public PinSwitchManager {
        protected:
            PowerloadManagement(byte *pins, byte keysCnt): PinSwitchManager(pins, keysCnt) {
            }

            static PowerloadManagement* instance;

        public:
            static PowerloadManagement* get() {
                return PowerloadManagement::instance;
            }

            //static void init(const byte pins[], byte cnt) {
            static void init(byte *pins, byte cnt) {
                if (!PowerloadManagement::instance) {
                    PowerloadManagement::instance = new PowerloadManagement(pins, cnt);
                }
            }
    };
       
#endif