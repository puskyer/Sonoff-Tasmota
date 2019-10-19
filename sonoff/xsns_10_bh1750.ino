/*
  xsns_10_bh1750.ino - BH1750 ambient light sensor support for Sonoff-Tasmota

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

#ifdef USE_I2C
#ifdef USE_BH1750
/*********************************************************************************************\
 * BH1750 - Ambient Light Intensity
 *
 * I2C Address: 0x23 or 0x5C
\*********************************************************************************************/

<<<<<<< HEAD
=======
#define XSNS_10              10

>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#define BH1750_ADDR1         0x23
#define BH1750_ADDR2         0x5C

#define BH1750_CONTINUOUS_HIGH_RES_MODE 0x10 // Start measurement at 1lx resolution. Measurement time is approx 120ms.

uint8_t bh1750_address;
uint8_t bh1750_addresses[] = { BH1750_ADDR1, BH1750_ADDR2 };
uint8_t bh1750_type = 0;
<<<<<<< HEAD

uint16_t Bh1750ReadLux()
{
  Wire.requestFrom(bh1750_address, (uint8_t)2);
  byte msb = Wire.read();
  byte lsb = Wire.read();
  uint16_t value = ((msb << 8) | lsb) / 1.2;
  return value;
=======
uint8_t bh1750_valid = 0;
uint16_t bh1750_illuminance = 0;
char bh1750_types[] = "BH1750";

bool Bh1750Read(void)
{
  if (bh1750_valid) { bh1750_valid--; }

  if (2 != Wire.requestFrom(bh1750_address, (uint8_t)2)) { return false; }
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();
  bh1750_illuminance = ((msb << 8) | lsb) / 1.2;
  bh1750_valid = SENSOR_MAX_MISS;
  return true;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
}

/********************************************************************************************/

<<<<<<< HEAD
void Bh1750Detect()
=======
void Bh1750Detect(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  if (bh1750_type) {
    return;
  }

<<<<<<< HEAD
  for (byte i = 0; i < sizeof(bh1750_addresses); i++) {
=======
  for (uint32_t i = 0; i < sizeof(bh1750_addresses); i++) {
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
    bh1750_address = bh1750_addresses[i];
    Wire.beginTransmission(bh1750_address);
    Wire.write(BH1750_CONTINUOUS_HIGH_RES_MODE);
    if (!Wire.endTransmission()) {
      bh1750_type = 1;
<<<<<<< HEAD
      snprintf_P(log_data, sizeof(log_data), S_LOG_I2C_FOUND_AT, "BH1750", bh1750_address);
      AddLog(LOG_LEVEL_DEBUG);
=======
      AddLog_P2(LOG_LEVEL_DEBUG, S_LOG_I2C_FOUND_AT, bh1750_types, bh1750_address);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      break;
    }
  }
}

<<<<<<< HEAD
#ifdef USE_WEBSERVER
const char HTTP_SNS_ILLUMINANCE[] PROGMEM =
  "%s{s}BH1750 " D_ILLUMINANCE "{m}%d " D_UNIT_LUX "{e}";  // {s} = <tr><th>, {m} = </th><td>, {e} = </td></tr>
#endif  // USE_WEBSERVER

void Bh1750Show(boolean json)
{
  if (bh1750_type) {
    uint16_t illuminance = Bh1750ReadLux();

    if (json) {
      snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s,\"BH1750\":{\"" D_JSON_ILLUMINANCE "\":%d}"), mqtt_data, illuminance);
#ifdef USE_DOMOTICZ
      if (0 == tele_period) DomoticzSensor(DZ_ILLUMINANCE, illuminance);
#endif  // USE_DOMOTICZ
#ifdef USE_WEBSERVER
    } else {
      snprintf_P(mqtt_data, sizeof(mqtt_data), HTTP_SNS_ILLUMINANCE, mqtt_data, illuminance);
=======
void Bh1750EverySecond(void)
{
  if (90 == (uptime %100)) {
    // 1mS
    Bh1750Detect();
  }
  else {
    // 1mS
    if (bh1750_type) {
      if (!Bh1750Read()) {
        AddLogMissed(bh1750_types, bh1750_valid);
//        if (!bh1750_valid) { bh1750_type = 0; }
      }
    }
  }
}

void Bh1750Show(bool json)
{
  if (bh1750_valid) {
    if (json) {
      ResponseAppend_P(JSON_SNS_ILLUMINANCE, bh1750_types, bh1750_illuminance);
#ifdef USE_DOMOTICZ
      if (0 == tele_period) {
        DomoticzSensor(DZ_ILLUMINANCE, bh1750_illuminance);
      }
#endif  // USE_DOMOTICZ
#ifdef USE_WEBSERVER
    } else {
      WSContentSend_PD(HTTP_SNS_ILLUMINANCE, bh1750_types, bh1750_illuminance);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#endif  // USE_WEBSERVER
    }
  }
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

<<<<<<< HEAD
#define XSNS_10

boolean Xsns10(byte function)
{
  boolean result = false;

  if (i2c_flg) {
    switch (function) {
      case FUNC_PREP_BEFORE_TELEPERIOD:
        Bh1750Detect();
        break;
=======
bool Xsns10(uint8_t function)
{
  bool result = false;

  if (i2c_flg) {
    switch (function) {
      case FUNC_INIT:
        Bh1750Detect();
        break;
      case FUNC_EVERY_SECOND:
        Bh1750EverySecond();
        break;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      case FUNC_JSON_APPEND:
        Bh1750Show(1);
        break;
#ifdef USE_WEBSERVER
<<<<<<< HEAD
      case FUNC_WEB_APPEND:
=======
      case FUNC_WEB_SENSOR:
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
        Bh1750Show(0);
        break;
#endif  // USE_WEBSERVER
    }
  }
  return result;
}

#endif  // USE_BH1750
#endif  // USE_I2C
