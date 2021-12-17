#ifndef _EXAMPLEFIRMWARE_CFG_H
#define _EXAMPLEFIRMWARE_CFG_H

    // ---[ PROCESS IDs ]---

	#define PRC_MAIN			101
	#define PRC_CONSUMER1		221
	#define PRC_CONSUMER2		222
	#define PRC_CONSUMER3		223

    #define PRC_MHZ19			302
	#define PRC_PPD42NS			305
	#define PRC_DUMB2			902
	#define PRC_DUMB3			903

    // ---[ COMMON APP CONFIG ]---

    // ---[ PWR MNGMNT PRC CFG ]---
    #define PWRMNGMTPINS                {12, 11, 10}
    #define MAXTASKCOUNT                10      // 5?
    #define CONSUMERPROCESSTIMEOUT      10000   // 60000 is production

    // ---[ ADC MUX CFG ]---
    #define ADCMUXPINS                  {9, 8, 7, 6}
#endif