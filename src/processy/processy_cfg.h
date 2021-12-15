#ifndef _PROCESSY_CFG_H
#define _PROCESSY_CFG_H

    /*** processy config ***/
    #define DEBUG_PRO_MS
    #define DEBUG_PRO_PERIOD_MS 10000

	#define PROCESSY_DEBUG_SERIAL

    /*** processy inlines ***/
    #define S(t) String(t)
    #define SF(t) String(F(t))
    #define SFC(t) String(F(t)).c_str()
	
	#ifdef PROCESSY_DEBUG_SERIAL
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