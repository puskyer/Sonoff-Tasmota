/*
  user_config_override.h - user configuration overrides user_config.h for Sonoff-Tasmota

  Copyright (C) 2018  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

// force the compiler to show a warning to confirm that this file is inlcuded
#warning **** user_config_override.h: Using Settings from this File ****

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *   (3) for platformio:
 *         define USE_CONFIG_OVERRIDE as a build flags.
 *         ie1 : export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE'
 *         ie2 : enable in file platformio.ini "build_flags = -Wl,-Tesp8266.flash.1m0.ld -DUSE_CONFIG_OVERRIDE"
 *       for Arduino IDE:
 *         enable define USE_CONFIG_OVERRIDE in user_config.h
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*********************************************************************************************\
 * Compile a minimal version if upgrade memory gets tight ONLY TO BE USED FOR UPGRADE STEP 1!
 *   To be used as step 1 during upgrade.
 *   Step 2 is re-compile with option BE_MINIMAL commented out.
\*********************************************************************************************/

#define BE_MINIMAL                               // Minimal version if upgrade memory gets tight (-45k code, -2k mem)

      
// Examples
//#ifdef CFG_HOLDER
//#undef CFG_HOLDER
//#endif
//#define CFG_HOLDER             0x20180514
                                       

#define uMQTTBroker
#undef uMQTTBroker
                                

#define ANTONIY
#undef ANTONIY

#ifdef uMQTTBroker
                                      

  #include "uMQTTBroker.h"
  #include "MQTT.h"

  unsigned int max_subscriptions = 30;
  unsigned int max_retained_topics = 30;


    void ICACHE_FLASH_ATTR data_callback(uint32_t *client /* we can ignore this */, const char* topic, uint32_t topic_len, const char *data, uint32_t lengh) {
      char topic_str[topic_len+1];
      os_memcpy(topic_str, topic, topic_len);
      topic_str[topic_len] = '\0';

      char data_str[lengh+1];
      os_memcpy(data_str, data, lengh);
      data_str[lengh] = '\0';

      Serial.print("received topic '");
      Serial.print(topic_str);
      Serial.print("' with data '");
      Serial.print(data_str);
      Serial.println("'");
    }


    bool ICACHE_FLASH_ATTR auth_data_callback(const char* username, const char *password, struct espconn *pesp_conn){
        Serial.print("username is: ");
        Serial.println(username);

       if ((String)username == (String)MQTT_USER &&  (String)password == (String)MQTT_PASS ) {
        return true;
       }else{
        return false;
      }
    }

#endif

// -- MQTT - TLS ----------------------------------
  // !!! TLS uses a LOT OF MEMORY so be careful to enable other options at the same time !!!

#ifndef  USE_MQTT_TLS
// #undef  USE_MQTT_TLS
#define USE_MQTT_TLS

#undef USE_MQTT_TLS_CA_CERT 
#define USE_MQTT_TLS_CA_CERT
#undef  MQTT_PORT
#define MQTT_PORT         8883                   // [MqttPort] MQTT port (10123 on CloudMQTT)
#endif

                            // Use TLS for MQTT connection (+53k code, +15k mem)

// -- Syslog --------------------------------------
#ifdef SYS_LOG_HOST
#undef SYS_LOG_HOST
#endif
#define SYS_LOG_HOST           "syslog"          // [LogHost] (Linux) syslog host

#ifdef  SYS_LOG_LEVEL
#undef  SYS_LOG_LEVEL
#endif
#define SYS_LOG_LEVEL          LOG_LEVEL_INFO    // [SysLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)

#ifdef  EMULATION
#undef  EMULATION
#endif
#define EMULATION              EMUL_HUE         // [Emulation] Select Belkin WeMo (single relay/light) or Hue Bridge emulation (multi relay/light) (EMUL_NONE, EMUL_WEMO or EMUL_HUE)

// -- Location ------------------------------------
#ifdef  LATITUDE
#undef  LATITUDE
#endif
#ifdef  LONGITUDE
#undef  LONGITUDE
#endif
#define LATITUDE               48.858360         // [Latitude] Your location to be used with sunrise and sunset
#define LONGITUDE              2.294442          // [Longitude] Your location to be used with sunrise and sunset

// -- Application ---------------------------------
#ifdef  APP_TIMEZONE
#undef  APP_TIMEZONE
#endif
#define APP_TIMEZONE           -4                 // [Timezone] +1 hour (Amsterdam) (-13 .. 14 = hours from UTC, 99 = use TIME_DST/TIME_STD)

// -- OTA -----------------------------------------
//#ifdef  USE_ARDUINO_OTA
//#undef  USE_ARDUINO_OTA
//#endif
//#define USE_ARDUINO_OTA                          // Add optional support for Arduino OTA (+13k code)

/*-------------------------------------------------------------------------------------------*\
 * Select ONE of possible three MQTT library types below
\*-------------------------------------------------------------------------------------------*/
  // Default MQTT driver for both non-TLS and TLS connections. Blocks network if MQTT server is unavailable.
#ifdef  MQTT_LIBRARY_TYPE
#undef  MQTT_LIBRARY_TYPE
#endif

#define MQTT_LIBRARY_TYPE      MQTT_PUBSUBCLIENT   // Use PubSubClient library
  // Alternative MQTT driver does not block network when MQTT server is unavailable. No TLS support
//#define MQTT_LIBRARY_TYPE      MQTT_TASMOTAMQTT    // Use TasmotaMqtt library (+4k4 code, +4k mem) - non-TLS only
  // Alternative MQTT driver does not block network when MQTT server is unavailable. No TLS support
//#define MQTT_LIBRARY_TYPE      MQTT_ESPMQTTARDUINO // Use (patched) esp-mqtt-arduino library (+4k8 code, +4k mem) - non-TLS only


// -- HTTP ----------------------------------------
//#define USE_WEBSERVER                            // Enable web server and Wifi Manager (+66k code, +8k mem)
//  #define WEB_PORT             80                // Web server Port for User and Admin mode
//  #define WEB_USERNAME         "admin"           // Web server Admin mode user name
//  #define USE_EMULATION                          // Enable Belkin WeMo and Hue Bridge emulation for Alexa (+16k code, +2k mem)

// -- mDNS ----------------------------------------
//#define USE_DISCOVERY                            // Enable mDNS for the following services (+8k code, +0.3k mem)
//  #define WEBSERVER_ADVERTISE                    // Provide access to webserver by name <Hostname>.local/
//  #define MQTT_HOST_DISCOVERY                    // Find MQTT host server (overrides MQTT_HOST if found)

  

#ifdef ANTONIY

  #ifdef STA_SSID1
  #undef STA_SSID1
  #endif

  #define STA_SSID1              "Virus2"

  #ifdef STA_PASS1
  #undef STA_PASS1
  #endif
  #define STA_PASS1              "IvanAntoniy"  // [Password1] Wifi password

  #ifdef STA_SSID2
  #undef STA_SSID2
  #endif
  #define STA_SSID2              "Virus2"      // [Ssid2] Optional alternate AP Wifi SSID

  #ifdef STA_PASS2
  #undef STA_PASS2
  #endif
  #define STA_PASS2              "IvanAntoniy"  // [Password2] Optional alternate AP Wifi password

  #ifdef WEB_PASSWORD
  #undef WEB_PASSWORD
  #endif
  #define WEB_PASSWORD           "WEBAntoniy"   // [WebPassword] Web server Admin mode Password for WEB_USERNAME (empty string = Disable)


  #ifdef USE_MQTT_TLS
    #ifdef MQTT_HOST
    #undef MQTT_HOST
    #undef MQTT_USER
    #undef MQTT_PASS
    #endif
    #define MQTT_HOST            "riccio.asuscomm.com"  // [MqttHost]
    #define MQTT_USER            "mqttUser"      // [MqttUser] Mandatory user
    #define MQTT_PASS            "MqttPass"  // [MqttPassword] Mandatory password
  #else
    #ifdef MQTT_HOST
    #undef MQTT_HOST
    #undef MQTT_USER
    #undef MQTT_PASS
    #endif
    #define MQTT_HOST            "mqtt"          // [MqttHost]
    #define MQTT_USER            "mqttUser"       // [MqttUser] Optional user
    #define MQTT_PASS            "MqttPass"       // [MqttPassword] Optional password
  #endif

  #else

  #ifdef STA_SSID1
  #undef STA_SSID1
  #endif

  #define STA_SSID1              "MQTTAP"

  #ifdef STA_PASS1
  #undef STA_PASS1
  #endif
  #define STA_PASS1              "MqttAPpass$"  // [Password1] Wifi password

  #ifdef STA_SSID2
  #undef STA_SSID2
  #endif
  #define STA_SSID2              "MQTTAP"      // [Ssid2] Optional alternate AP Wifi SSID

  #ifdef STA_PASS2
  #undef STA_PASS2
  #endif
  #define STA_PASS2              "MqttAPpass$"  // [Password2] Optional alternate AP Wifi password

  #ifdef WEB_PASSWORD
  #undef WEB_PASSWORD
  #endif
  #define WEB_PASSWORD           "MqttW3Bpass$"   // [WebPassword] Web server Admin mode Password for WEB_USERNAME (empty string = Disable)


  #ifdef USE_MQTT_TLS
    #ifdef MQTT_HOST
    #undef MQTT_HOST
    #undef MQTT_USER
    #undef MQTT_PASS
    #endif
    #define MQTT_HOST            "mqtttls"  // [MqttHost]
    #define MQTT_USER            "mqttUser"      // [MqttUser] Mandatory user
    #define MQTT_PASS            "MqttPass"  // [MqttPassword] Mandatory password
  #else
    #ifdef MQTT_HOST
    #undef MQTT_HOST
    #undef MQTT_USER
    #undef MQTT_PASS
    #endif
    #define MQTT_HOST            "mqtt"          // [MqttHost]
    #define MQTT_USER            "mqttUser"       // [MqttUser] Optional user
    #define MQTT_PASS            "MqttPass"       // [MqttPassword] Optional password
  #endif

#endif

#endif  // _USER_CONFIG_OVERRIDE_H_
