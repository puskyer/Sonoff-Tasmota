/*
  xsns_17_senseair.ino - SenseAir CO2 sensor support for Sonoff-Tasmota

<<<<<<< HEAD
  Copyright (C) 2018  Theo Arends
=======
  Copyright (C) 2019  Theo Arends
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347

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

#ifdef USE_SENSEAIR
/*********************************************************************************************\
 * SenseAir K30, K70 and S8 - CO2 sensor
 *
 * Adapted from EspEasy plugin P052 by Mikael Trieb (mikael__AT__triebconsulting.se)
 *
 * Hardware Serial will be selected if GPIO1 = [SAir Rx] and GPIO3 = [SAir Tx]
\*********************************************************************************************/

<<<<<<< HEAD
#include <TasmotaSerial.h>
=======
#define XSNS_17                      17

#define SENSEAIR_MODBUS_SPEED        9600
#define SENSEAIR_DEVICE_ADDRESS      0xFE    // Any address
#define SENSEAIR_READ_REGISTER       0x04    // Command Read
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347

#ifndef CO2_LOW
#define CO2_LOW                      800     // Below this CO2 value show green light
#endif
#ifndef CO2_HIGH
#define CO2_HIGH                     1200    // Above this CO2 value show red light
#endif

<<<<<<< HEAD
TasmotaSerial *SensairSerial;
=======
#include <TasmotaModbus.h>
TasmotaModbus *SenseairModbus;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347

const char kSenseairTypes[] PROGMEM = "Kx0|S8";

uint8_t senseair_type = 1;
char senseair_types[7];

uint16_t senseair_co2 = 0;
float senseair_temperature = 0;
float senseair_humidity = 0;

<<<<<<< HEAD
uint8_t senseair_state = 0;

/*********************************************************************************************/

void ModbusSend(uint8_t function_code, uint16_t start_address, uint16_t register_count)
{
  uint8_t frame[8];

  frame[0] = 0xFE;  // Any Address
  frame[1] = function_code;
  frame[2] = (uint8_t)(start_address >> 8);
  frame[3] = (uint8_t)(start_address);
  frame[4] = (uint8_t)(register_count >> 8);
  frame[5] = (uint8_t)(register_count);
  uint16_t crc = 0xFFFF;
  for (uint8_t pos = 0; pos < sizeof(frame) -2; pos++) {
    crc ^= (uint16_t)frame[pos];        // XOR byte into least sig. byte of crc
    for (uint8_t i = 8; i != 0; i--) {  // Loop over each bit
      if ((crc & 0x0001) != 0) {        // If the LSB is set
        crc >>= 1;                      // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else {                            // Else LSB is not set
        crc >>= 1;                      // Just shift right
      }
    }
  }
  frame[7] = (uint8_t)((crc >> 8) & 0xFF);
  frame[6] = (uint8_t)(crc & 0xFF);

  SensairSerial->flush();
  SensairSerial->write(frame, sizeof(frame));
}

bool ModbusReceiveReady()
{
  return (SensairSerial->available() >= 5);  // 5 - Error frame, 7 - Ok frame
}

uint8_t ModbusReceive(uint16_t *value)
{
  uint8_t buffer[7];

  uint8_t len = 0;
  while (SensairSerial->available() > 0) {
    buffer[len++] = (uint8_t)SensairSerial->read();
    if (3 == len) {
      if (buffer[1] & 0x80) {  // fe 84 02 f2 f1
        return buffer[2];      // 1 = Illegal Function, 2 = Illegal Data Address, 3 = Illegal Data Value
      }
    }
  }

  AddLogSerial(LOG_LEVEL_DEBUG_MORE, buffer, len);

  if (len != sizeof(buffer)) {
    return 9;                  // 9 = Unexpected result
  }
  *value = (buffer[3] << 8) | buffer[4];
  return 0;                    // 0 = No error
}

/*********************************************************************************************/
=======
//uint8_t senseair_state = 0;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347

const uint8_t start_addresses[] { 0x1A, 0x00, 0x03, 0x04, 0x05, 0x1C, 0x0A };

uint8_t senseair_read_state = 0;
uint8_t senseair_send_retry = 0;

<<<<<<< HEAD
void Senseair50ms()              // Every 50 mSec
{
  senseair_state++;
  if (6 == senseair_state) {     // Every 300 mSec
    senseair_state = 0;

    uint16_t value = 0;
    bool data_ready = ModbusReceiveReady();

    if (data_ready) {
      uint8_t error = ModbusReceive(&value);
      if (error) {
        snprintf_P(log_data, sizeof(log_data), PSTR(D_LOG_DEBUG "SenseAir response error %d"), error);
        AddLog(LOG_LEVEL_DEBUG);
=======
void Senseair250ms(void)              // Every 250 mSec
{
//  senseair_state++;
//  if (6 == senseair_state) {     // Every 300 mSec
//    senseair_state = 0;

    uint16_t value = 0;
    bool data_ready = SenseairModbus->ReceiveReady();

    if (data_ready) {
      uint8_t error = SenseairModbus->Receive16BitRegister(&value);
      if (error) {
        AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_DEBUG "SenseAir response error %d"), error);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      } else {
        switch(senseair_read_state) {
          case 0:                // 0x1A (26) READ_TYPE_LOW - S8: fe 04 02 01 77 ec 92
            senseair_type = 2;
<<<<<<< HEAD
            snprintf_P(log_data, sizeof(log_data), PSTR(D_LOG_DEBUG "SenseAir type id low %04X"), value);
            AddLog(LOG_LEVEL_DEBUG);
            break;
          case 1:                // 0x00 (0) READ_ERRORLOG - fe 04 02 00 00 ad 24
            if (value) {
              snprintf_P(log_data, sizeof(log_data), PSTR(D_LOG_DEBUG "SenseAir error %04X"), value);
              AddLog(LOG_LEVEL_DEBUG);
=======
            AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_DEBUG "SenseAir type id low %04X"), value);
            break;
          case 1:                // 0x00 (0) READ_ERRORLOG - fe 04 02 00 00 ad 24
            if (value) {
              AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_DEBUG "SenseAir error %04X"), value);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
            }
            break;
          case 2:                // 0x03 (3) READ_CO2 - fe 04 02 06 2c af 59
            senseair_co2 = value;
            LightSetSignal(CO2_LOW, CO2_HIGH, senseair_co2);
            break;
          case 3:                // 0x04 (4) READ_TEMPERATURE - S8: fe 84 02 f2 f1 - Illegal Data Address
            senseair_temperature = ConvertTemp((float)value / 100);
            break;
          case 4:                // 0x05 (5) READ_HUMIDITY - S8: fe 84 02 f2 f1 - Illegal Data Address
<<<<<<< HEAD
            senseair_humidity = (float)value / 100;
=======
            senseair_humidity = ConvertHumidity((float)value / 100);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
            break;
          case 5:                // 0x1C (28) READ_RELAY_STATE - S8: fe 04 02 01 54 ad 4b - firmware version
          {
            bool relay_state = value >> 8 & 1;
<<<<<<< HEAD
            snprintf_P(log_data, sizeof(log_data), PSTR(D_LOG_DEBUG "SenseAir relay state %d"), relay_state);
            AddLog(LOG_LEVEL_DEBUG);
            break;
          }
          case 6:                // 0x0A (10) READ_TEMP_ADJUSTMENT - S8: fe 84 02 f2 f1 - Illegal Data Address
            snprintf_P(log_data, sizeof(log_data), PSTR(D_LOG_DEBUG "SenseAir temp adjustment %d"), value);
            AddLog(LOG_LEVEL_DEBUG);
=======
            AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_DEBUG "SenseAir relay state %d"), relay_state);
            break;
          }
          case 6:                // 0x0A (10) READ_TEMP_ADJUSTMENT - S8: fe 84 02 f2 f1 - Illegal Data Address
            AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_DEBUG "SenseAir temp adjustment %d"), value);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
            break;
        }
      }
      senseair_read_state++;
      if (2 == senseair_type) {  // S8
        if (3 == senseair_read_state) {
          senseair_read_state = 1;
        }
      } else {                   // K30, K70
        if (sizeof(start_addresses) == senseair_read_state) {
          senseair_read_state = 1;
        }
      }
    }

    if (0 == senseair_send_retry || data_ready) {
      senseair_send_retry = 5;
<<<<<<< HEAD
      ModbusSend(0x04, (uint16_t)start_addresses[senseair_read_state], 1);
=======
      SenseairModbus->Send(SENSEAIR_DEVICE_ADDRESS, SENSEAIR_READ_REGISTER, (uint16_t)start_addresses[senseair_read_state], 1);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
    } else {
      senseair_send_retry--;
    }

<<<<<<< HEAD
  }
=======
//  }
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
}

/*********************************************************************************************/

<<<<<<< HEAD
void SenseairInit()
{
  senseair_type = 0;
  if ((pin[GPIO_SAIR_RX] < 99) && (pin[GPIO_SAIR_TX] < 99)) {
    SensairSerial = new TasmotaSerial(pin[GPIO_SAIR_RX], pin[GPIO_SAIR_TX], 1);
    if (SensairSerial->begin(9600)) {
      if (SensairSerial->hardwareSerial()) { ClaimSerial(); }
=======
void SenseairInit(void)
{
  senseair_type = 0;
  if ((pin[GPIO_SAIR_RX] < 99) && (pin[GPIO_SAIR_TX] < 99)) {
    SenseairModbus = new TasmotaModbus(pin[GPIO_SAIR_RX], pin[GPIO_SAIR_TX]);
    uint8_t result = SenseairModbus->Begin(SENSEAIR_MODBUS_SPEED);
    if (result) {
      if (2 == result) { ClaimSerial(); }
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      senseair_type = 1;
    }
  }
}

<<<<<<< HEAD
void SenseairShow(boolean json)
{
  char temperature[10];
  char humidity[10];
  dtostrfd(senseair_temperature, Settings.flag2.temperature_resolution, temperature);
=======
void SenseairShow(bool json)
{
  char temperature[33];
  dtostrfd(senseair_temperature, Settings.flag2.temperature_resolution, temperature);
  char humidity[33];
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
  dtostrfd(senseair_humidity, Settings.flag2.temperature_resolution, humidity);
  GetTextIndexed(senseair_types, sizeof(senseair_types), senseair_type -1, kSenseairTypes);

  if (json) {
<<<<<<< HEAD
    snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s,\"%s\":{\"" D_JSON_CO2 "\":%d"), mqtt_data, senseair_types, senseair_co2);
    if (senseair_type != 2) {
      snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s,\"" D_JSON_TEMPERATURE "\":%s,\"" D_JSON_HUMIDITY "\":%s"), mqtt_data, temperature, humidity);
    }
    snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s}"), mqtt_data);
=======
    ResponseAppend_P(PSTR(",\"%s\":{\"" D_JSON_CO2 "\":%d"), senseair_types, senseair_co2);
    if (senseair_type != 2) {
      ResponseAppend_P(PSTR(",\"" D_JSON_TEMPERATURE "\":%s,\"" D_JSON_HUMIDITY "\":%s"), temperature, humidity);
    }
    ResponseJsonEnd();
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#ifdef USE_DOMOTICZ
    if (0 == tele_period) DomoticzSensor(DZ_AIRQUALITY, senseair_co2);
#endif  // USE_DOMOTICZ
#ifdef USE_WEBSERVER
  } else {
<<<<<<< HEAD
    snprintf_P(mqtt_data, sizeof(mqtt_data), HTTP_SNS_CO2, mqtt_data, senseair_types, senseair_co2);
    if (senseair_type != 2) {
      snprintf_P(mqtt_data, sizeof(mqtt_data), HTTP_SNS_TEMP, mqtt_data, senseair_types, temperature, TempUnit());
      snprintf_P(mqtt_data, sizeof(mqtt_data), HTTP_SNS_HUM, mqtt_data, senseair_types, humidity);
=======
    WSContentSend_PD(HTTP_SNS_CO2, senseair_types, senseair_co2);
    if (senseair_type != 2) {
      WSContentSend_PD(HTTP_SNS_TEMP, senseair_types, temperature, TempUnit());
      WSContentSend_PD(HTTP_SNS_HUM, senseair_types, humidity);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
    }
#endif  // USE_WEBSERVER
  }
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

<<<<<<< HEAD
#define XSNS_17

boolean Xsns17(byte function)
{
  boolean result = false;
=======
bool Xsns17(uint8_t function)
{
  bool result = false;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347

  if (senseair_type) {
    switch (function) {
      case FUNC_INIT:
        SenseairInit();
        break;
<<<<<<< HEAD
      case FUNC_EVERY_50_MSECOND:
        Senseair50ms();
=======
      case FUNC_EVERY_250_MSECOND:
        Senseair250ms();
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
        break;
      case FUNC_JSON_APPEND:
        SenseairShow(1);
        break;
#ifdef USE_WEBSERVER
<<<<<<< HEAD
      case FUNC_WEB_APPEND:
=======
      case FUNC_WEB_SENSOR:
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
        SenseairShow(0);
        break;
#endif  // USE_WEBSERVER
    }
  }
  return result;
}

#endif  // USE_SENSEAIR
