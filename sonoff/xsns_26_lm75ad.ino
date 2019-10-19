/*
  xsns_26_lm75ad.ino - Support for I2C LM75AD Temperature Sensor

<<<<<<< HEAD
  Copyright (C) 2018  Andre Thomas and Theo Arends
=======
  Copyright (C) 2019  Andre Thomas and Theo Arends
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

#ifdef USE_I2C
#ifdef USE_LM75AD

/*********************************************************************************************\
 * LM75AD - Temperature
 *
 * Docs at https://www.nxp.com/docs/en/data-sheet/LM75A.pdf
 *
 * I2C Address: 0x48 - 0x4F
\*********************************************************************************************/

<<<<<<< HEAD
=======
#define XSNS_26                 26

>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#define LM75AD_ADDRESS1					0x48
#define LM75AD_ADDRESS2					0x49
#define LM75AD_ADDRESS3					0x4A
#define LM75AD_ADDRESS4					0x4B
#define LM75AD_ADDRESS5					0x4C
#define LM75AD_ADDRESS6					0x4D
#define LM75AD_ADDRESS7					0x4E
#define LM75AD_ADDRESS8					0x4F

#define LM75_TEMP_REGISTER      0x00
#define LM75_CONF_REGISTER      0x01
#define LM75_THYST_REGISTER     0x02
#define LM75_TOS_REGISTER       0x03

uint8_t lm75ad_type = 0;
uint8_t lm75ad_address;
uint8_t lm75ad_addresses[] = { LM75AD_ADDRESS1, LM75AD_ADDRESS2, LM75AD_ADDRESS3, LM75AD_ADDRESS4, LM75AD_ADDRESS5, LM75AD_ADDRESS6, LM75AD_ADDRESS7, LM75AD_ADDRESS8 };

<<<<<<< HEAD
void LM75ADDetect()
{
  uint8_t buffer;

  if (lm75ad_type) { return; }

  for (byte i = 0; i < sizeof(lm75ad_addresses); i++) {
    lm75ad_address = lm75ad_addresses[i];
    if (I2cValidRead8(&buffer, lm75ad_address, LM75_CONF_REGISTER)) {
      lm75ad_type = 1;
      snprintf_P(log_data, sizeof(log_data), S_LOG_I2C_FOUND_AT, "LM75AD", lm75ad_address);
      AddLog(LOG_LEVEL_DEBUG);
      break;
=======
void LM75ADDetect(void)
{
  if (lm75ad_type) { return; }

  uint16_t buffer;
  for (uint32_t i = 0; i < sizeof(lm75ad_addresses); i++) {
    lm75ad_address = lm75ad_addresses[i];
    if (I2cValidRead16(&buffer, lm75ad_address, LM75_THYST_REGISTER)) {
      if (buffer == 0x4B00) {
        lm75ad_type = 1;
        AddLog_P2(LOG_LEVEL_DEBUG, S_LOG_I2C_FOUND_AT, "LM75AD", lm75ad_address);
        break;
      }
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
    }
  }
}

<<<<<<< HEAD
float LM75ADGetTemp() {
=======
float LM75ADGetTemp(void) {
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
  int16_t sign = 1;

  uint16_t t = I2cRead16(lm75ad_address, LM75_TEMP_REGISTER);
  if (t & 0x8000) { // we are getting a negative temperature value
    t = (~t) +0x20;
    sign = -1;
  }
  t = t >> 5; // shift value into place (5 LSB not used)
  return ConvertTemp(sign * t * 0.125);
}

<<<<<<< HEAD
void LM75ADShow(boolean json)
{
  if (lm75ad_type) {
    char temperature[10];

    float t = LM75ADGetTemp();
    dtostrfd(t, Settings.flag2.temperature_resolution, temperature);

    if (json) {
      snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s,\"LM75AD\":{\"" D_JSON_TEMPERATURE "\":%s}"), mqtt_data, temperature);
=======
void LM75ADShow(bool json)
{
  if (lm75ad_type) {
    float t = LM75ADGetTemp();
    char temperature[33];
    dtostrfd(t, Settings.flag2.temperature_resolution, temperature);

    if (json) {
      ResponseAppend_P(PSTR(",\"LM75AD\":{\"" D_JSON_TEMPERATURE "\":%s}"), temperature);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#ifdef USE_DOMOTICZ
      if (0 == tele_period) DomoticzSensor(DZ_TEMP, temperature);
#endif  // USE_DOMOTICZ
#ifdef USE_WEBSERVER
    } else {
<<<<<<< HEAD
      snprintf_P(mqtt_data, sizeof(mqtt_data), HTTP_SNS_TEMP, mqtt_data, "LM75AD", temperature, TempUnit());
=======
      WSContentSend_PD(HTTP_SNS_TEMP, "LM75AD", temperature, TempUnit());
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#endif  // USE_WEBSERVER
    }
  }
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

<<<<<<< HEAD
#define XSNS_26

boolean Xsns26(byte function)
{
  boolean result = false;

  if (i2c_flg) {
    switch (function) {
      case FUNC_PREP_BEFORE_TELEPERIOD:
=======
bool Xsns26(uint8_t function)
{
  bool result = false;

  if (i2c_flg) {
    switch (function) {
      case FUNC_EVERY_SECOND:
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
        LM75ADDetect();
        break;
      case FUNC_JSON_APPEND:
        LM75ADShow(1);
        break;
#ifdef USE_WEBSERVER
<<<<<<< HEAD
      case FUNC_WEB_APPEND:
=======
      case FUNC_WEB_SENSOR:
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
        LM75ADShow(0);
        break;
#endif  // USE_WEBSERVER
    }
  }
  return result;
}

#endif  // USE_LM75AD
#endif  // USE_I2C
