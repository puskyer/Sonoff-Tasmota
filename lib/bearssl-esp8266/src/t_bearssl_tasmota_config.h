// do not delete

#ifndef BEARSSL_TASMOTA_CONFIG
#define BEARSSL_TASMOTA_CONFIG

#ifndef __ets__
#define __ets__
#endif

#ifndef ICACHE_FLASH
#define ICACHE_FLASH
#endif

#ifndef ESP8266
#define ESP8266
#endif

#ifndef BR_SLOW_MUL15
#define BR_SLOW_MUL15 1         // shrinks EC code by 8.5k
#endif

#ifndef BR_MAX_RSA_SIZE
#define BR_MAX_RSA_SIZE 2048    // max 2048 bits RSA keys
#endif

#ifndef BR_MAX_EC_SIZE
#define BR_MAX_EC_SIZE 256      // max 256 bits EC keys
#endif

#endif
