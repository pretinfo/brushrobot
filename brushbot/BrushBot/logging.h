#ifndef LOGGING_H
#define LOGGING_H

//#ifdef LOGGING

// logging is enabled
#include <stdarg.h>

#include <stdio.h>
#include <string.h>

#define PRINT_FILE_LINE() do { 						\
		Serial.print("[");Serial.print(__FILE__);		\
		Serial.print("::");Serial.print(__LINE__);Serial.print("]");\
}while (0);



#define INFO(format, args...) do { \
	char buf[250];	\
	sprintf(buf, format, args); \
	Serial.println(buf); \
} while(0);

#define INFO1(x) do {} while(0);

/*
#define INFO1(x) do { PRINT_FILE_LINE() Serial.print("-I-");\
		Serial.println(x);    			\
}while (0);
*/

#define INFO2(x,y) do { PRINT_FILE_LINE() Serial.print("-I-");\
		Serial.print(x,16);Serial.print(",");Serial.println(y,16); \
}while (0);


/*
//#else

#define INFO1(x) do {} while(0);
#define INFO2(x,y) do {} while(0);
#define INFO(format, args...) do {} while(0);
//#endif
*/
#endif
