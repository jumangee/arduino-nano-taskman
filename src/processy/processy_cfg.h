#ifndef _PROCESSY_CFG_H
#define _PROCESSY_CFG_H

    /*** processy config ***/
	#define	PROCESSY_MAX_LIST		30	
    
	/**
	 * @brief Add system debug info
	 * 0 - OFF
	 * 1 - Standart (ifirmware built-in)
	 * 2 - Custom (save a little of progmem)
	 */
	#define DEBUG_PRO_MS			2
    #define DEBUG_PRO_PERIOD_MS		10000

	#define PROCESSY_DEBUG_SERIAL	0

    /*** processy inlines ***/
    #define S(t) String(t)
    #define SF(t) String(F(t))
    #define SFC(t) String(F(t)).c_str()
	
	#if PROCESSY_DEBUG_SERIAL == 1
		#define TRACELN(t) Serial.println(t);
		#define TRACELNF(t) Serial.println(String(F(t)));
		#define TRACE(t) Serial.print(t);
		#define TRACEF(t) Serial.print(String(F(t)));
	#else
		#define TRACELN(t) /**/
		#define TRACELNF(t) /**/
		#define TRACE(t) /**/
		#define TRACEF(t) /**/
	#endif

#endif