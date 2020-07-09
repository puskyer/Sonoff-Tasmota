/*
  user_config_override.h - user configuration overrides user_config.h for Sonoff-Tasmota

  Copyright (C) 2017  Theo Arends

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

/*****************************************************************************************************\
 * ATTENTION: - Changes to most PARAMETER defines will only override flash settings if you change
 *              define CFG_HOLDER.
 *            - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *            - You still need to update user_config.h for major defines MODULE and USE_MQTT_TLS.
 *            - Changing MODULE defines are not being tested for validity as they are in user_config.h.
 *            - Most parameters can be changed online using commands via MQTT, WebConsole or serial.
 *            - So I see no use in this but anyway, your on your own.
\*****************************************************************************************************/

//#define BE_MINIMAL                               // Minimal version if upgrade memory gets tight (-45k code, -2k mem)


// Examples
#ifdef CFG_HOLDER
#undef CFG_HOLDER
#endif

#define CFG_HOLDER             0x20180514

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

#define USE_MQTT_TLS                             // Use TLS for MQTT connection (+53k code, +15k mem)
#define USE_MQTT_TLS_CA_CERT                   // Use LetsEncrypt Certificate from sonoff_letsencrypt.h - Not supported with core 2.3.0

#ifdef  USE_MQTT_TLS
#undef  USE_MQTT_TLS
#undef  USE_MQTT_TLS_CA_CERT
#endif


// -- Syslog --------------------------------------
#ifdef SYS_LOG_HOST
#undef SYS_LOG_HOST
#endif
#define SYS_LOG_HOST           "syslog.local"          // [LogHost] (Linux) syslog host

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
    #define MQTT_HOST            "mqtttls.local"  // [MqttHost]
    #define MQTT_USER            "mqtt_user"      // [MqttUser] Mandatory user
    #define MQTT_PASS            "MqttAntoniy"  // [MqttPassword] Mandatory password
  #else
    #ifdef MQTT_HOST
    #undef MQTT_HOST
    #undef MQTT_USER
    #undef MQTT_PASS
    #endif
    #define MQTT_HOST            "mqtt.local"          // [MqttHost]
    #define MQTT_USER            "mqtt_user"       // [MqttUser] Optional user
    #define MQTT_PASS            "MqttAntoniy"       // [MqttPassword] Optional password
  #endif
  
  #else
  
  #ifdef STA_SSID1
  #undef STA_SSID1
  #endif
  
  #define STA_SSID1              "MQTT"
  
  #ifdef STA_PASS1
  #undef STA_PASS1
  #endif
  #define STA_PASS1              "Mqtt_pass$"  // [Password1] Wifi password
  
  #ifdef STA_SSID2
  #undef STA_SSID2
  #endif
  #define STA_SSID2              "MQTTAP"      // [Ssid2] Optional alternate AP Wifi SSID
  
  #ifdef STA_PASS2
  #undef STA_PASS2
  #endif
  #define STA_PASS2              "Mqtt_pass$"  // [Password2] Optional alternate AP Wifi password
  
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
    #define MQTT_HOST            "mqtttls.local"  // [MqttHost]
    #define MQTT_USER            "mqtt_user"      // [MqttUser] Mandatory user
    #define MQTT_PASS            "MqttPass"  // [MqttPassword] Mandatory password
  #else
    #ifdef MQTT_HOST
    #undef MQTT_HOST
    #undef MQTT_USER
    #undef MQTT_PASS
    #endif
    #define MQTT_HOST            "mqtt.local"          // [MqttHost]
    #define MQTT_USER            "mqtt_user"       // [MqttUser] Optional user
    #define MQTT_PASS            "MqttPass"       // [MqttPassword] Optional password
  #endif

#endif

#endif  // _USER_CONFIG_OVERRIDE_H_
