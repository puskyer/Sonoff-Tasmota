/*
  xsns_05_ds18b20.ino - DS18B20 temperature sensor support for Sonoff-Tasmota

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

#ifdef USE_DS18B20
/*********************************************************************************************\
 * DS18B20 - Temperature - Single sensor
\*********************************************************************************************/

<<<<<<< HEAD
=======
#define XSNS_05              5

>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#define W1_SKIP_ROM          0xCC
#define W1_CONVERT_TEMP      0x44
#define W1_READ_SCRATCHPAD   0xBE

<<<<<<< HEAD
float ds18b20_last_temperature = 0;
uint16_t ds18b20_last_result = 0;
uint8_t ds18x20_pin = 0;
=======
float ds18b20_temperature = 0;
uint8_t ds18b20_valid = 0;
uint8_t ds18x20_pin = 0;
char ds18b20_types[] = "DS18B20";
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347

/*********************************************************************************************\
 * Embedded stripped and tuned OneWire library
\*********************************************************************************************/

<<<<<<< HEAD
uint8_t OneWireReset()
=======
uint8_t OneWireReset(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  uint8_t retries = 125;

  //noInterrupts();
<<<<<<< HEAD
  pinMode(ds18x20_pin, INPUT);
=======
#ifdef DS18B20_INTERNAL_PULLUP
  pinMode(ds18x20_pin, INPUT_PULLUP);
#else
  pinMode(ds18x20_pin, INPUT);
#endif
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
  do {
    if (--retries == 0) {
      return 0;
    }
    delayMicroseconds(2);
  } while (!digitalRead(ds18x20_pin));
  pinMode(ds18x20_pin, OUTPUT);
  digitalWrite(ds18x20_pin, LOW);
  delayMicroseconds(480);
<<<<<<< HEAD
  pinMode(ds18x20_pin, INPUT);
=======
#ifdef DS18B20_INTERNAL_PULLUP
  pinMode(ds18x20_pin, INPUT_PULLUP);
#else
  pinMode(ds18x20_pin, INPUT);
#endif
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
  delayMicroseconds(70);
  uint8_t r = !digitalRead(ds18x20_pin);
  //interrupts();
  delayMicroseconds(410);
  return r;
}

void OneWireWriteBit(uint8_t v)
{
  static const uint8_t delay_low[2] = { 65, 10 };
  static const uint8_t delay_high[2] = { 5, 55 };

  v &= 1;
  //noInterrupts();
  digitalWrite(ds18x20_pin, LOW);
  pinMode(ds18x20_pin, OUTPUT);
  delayMicroseconds(delay_low[v]);
  digitalWrite(ds18x20_pin, HIGH);
  //interrupts();
  delayMicroseconds(delay_high[v]);
}

<<<<<<< HEAD
uint8_t OneWireReadBit()
=======
uint8_t OneWireReadBit(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  //noInterrupts();
  pinMode(ds18x20_pin, OUTPUT);
  digitalWrite(ds18x20_pin, LOW);
  delayMicroseconds(3);
<<<<<<< HEAD
  pinMode(ds18x20_pin, INPUT);
=======
#ifdef DS18B20_INTERNAL_PULLUP
  pinMode(ds18x20_pin, INPUT_PULLUP);
#else
  pinMode(ds18x20_pin, INPUT);
#endif
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
  delayMicroseconds(10);
  uint8_t r = digitalRead(ds18x20_pin);
  //interrupts();
  delayMicroseconds(53);
  return r;
}

void OneWireWrite(uint8_t v)
{
  for (uint8_t bit_mask = 0x01; bit_mask; bit_mask <<= 1) {
    OneWireWriteBit((bit_mask & v) ? 1 : 0);
  }
}

<<<<<<< HEAD
uint8_t OneWireRead()
=======
uint8_t OneWireRead(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  uint8_t r = 0;

  for (uint8_t bit_mask = 0x01; bit_mask; bit_mask <<= 1) {
    if (OneWireReadBit()) {
      r |= bit_mask;
    }
  }
  return r;
}

<<<<<<< HEAD
boolean OneWireCrc8(uint8_t *addr)
=======
bool OneWireCrc8(uint8_t *addr)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  uint8_t crc = 0;
  uint8_t len = 8;

  while (len--) {
    uint8_t inbyte = *addr++;          // from 0 to 7
<<<<<<< HEAD
    for (uint8_t i = 8; i; i--) {
=======
    for (uint32_t i = 8; i; i--) {
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      uint8_t mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) {
        crc ^= 0x8C;
      }
      inbyte >>= 1;
    }
  }
  return (crc == *addr);               // addr 8
}

/********************************************************************************************/

<<<<<<< HEAD
void Ds18x20Init()
{
  ds18x20_pin = pin[GPIO_DSB];
}

void Ds18x20Convert()
=======
void Ds18b20Convert(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  OneWireReset();
  OneWireWrite(W1_SKIP_ROM);           // Address all Sensors on Bus
  OneWireWrite(W1_CONVERT_TEMP);       // start conversion, no parasite power on at the end
//  delay(750);                          // 750ms should be enough for 12bit conv
}

<<<<<<< HEAD
boolean Ds18b20Read(float &t)
=======
bool Ds18b20Read(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  uint8_t data[9];
  int8_t sign = 1;

<<<<<<< HEAD
  if (!ds18b20_last_temperature) {
    t = NAN;
  } else {
    ds18b20_last_result++;
    if (ds18b20_last_result > 4) {     // Reset after 4 misses
      ds18b20_last_temperature = NAN;
    }
    t = ds18b20_last_temperature;
  }

/*
  if (!OneWireReadBit()) {             //check measurement end
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_DSB D_SENSOR_BUSY));
    return !isnan(t);
  }
*/
  for (uint8_t retry = 0; retry < 3; retry++) {
    OneWireReset();
    OneWireWrite(W1_SKIP_ROM);
    OneWireWrite(W1_READ_SCRATCHPAD);
    for (uint8_t i = 0; i < 9; i++) {
=======
  if (ds18b20_valid) { ds18b20_valid--; }
/*
  if (!OneWireReadBit()) {     // Check end of measurement
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_DSB D_SENSOR_BUSY));
    return;
  }
*/
  for (uint32_t retry = 0; retry < 3; retry++) {
    OneWireReset();
    OneWireWrite(W1_SKIP_ROM);
    OneWireWrite(W1_READ_SCRATCHPAD);
    for (uint32_t i = 0; i < 9; i++) {
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      data[i] = OneWireRead();
    }
    if (OneWireCrc8(data)) {
      uint16_t temp12 = (data[1] << 8) + data[0];
      if (temp12 > 2047) {
        temp12 = (~temp12) +1;
        sign = -1;
      }
<<<<<<< HEAD
      t = ConvertTemp(sign * temp12 * 0.0625);
      ds18b20_last_result = 0;
    }
    if (!isnan(t)) {
      ds18b20_last_temperature = t;
=======
      ds18b20_temperature = ConvertTemp(sign * temp12 * 0.0625);
      ds18b20_valid = SENSOR_MAX_MISS;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      return true;
    }
  }
  AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_DSB D_SENSOR_CRC_ERROR));
<<<<<<< HEAD
  return !isnan(t);
}

void Ds18b20Show(boolean json)
{
  float t;

  if (Ds18b20Read(t)) {                // Check if read failed
    char temperature[10];

    dtostrfd(t, Settings.flag2.temperature_resolution, temperature);

    if(json) {
      snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s,\"DS18B20\":{\"" D_JSON_TEMPERATURE "\":%s}"), mqtt_data, temperature);
#ifdef USE_DOMOTICZ
      if (0 == tele_period) DomoticzSensor(DZ_TEMP, temperature);
#endif  // USE_DOMOTICZ
#ifdef USE_KNX
      if (0 == tele_period) {
        KnxSensor(KNX_TEMPERATURE, t);
=======
  return false;
}

/********************************************************************************************/

void Ds18b20EverySecond(void)
{
  ds18x20_pin = pin[GPIO_DSB];
  if (uptime &1) {
    // 2mS
    Ds18b20Convert();          // Start conversion, takes up to one second
  } else {
    // 12mS
    if (!Ds18b20Read()) {      // Read temperature
      AddLogMissed(ds18b20_types, ds18b20_valid);
    }
  }
}

void Ds18b20Show(bool json)
{
  if (ds18b20_valid) {        // Check for valid temperature
    char temperature[33];
    dtostrfd(ds18b20_temperature, Settings.flag2.temperature_resolution, temperature);
    if(json) {
      ResponseAppend_P(JSON_SNS_TEMP, ds18b20_types, temperature);
#ifdef USE_DOMOTICZ
      if (0 == tele_period) {
        DomoticzSensor(DZ_TEMP, temperature);
      }
#endif  // USE_DOMOTICZ
#ifdef USE_KNX
      if (0 == tele_period) {
        KnxSensor(KNX_TEMPERATURE, ds18b20_temperature);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      }
#endif  // USE_KNX
#ifdef USE_WEBSERVER
    } else {
<<<<<<< HEAD
      snprintf_P(mqtt_data, sizeof(mqtt_data), HTTP_SNS_TEMP, mqtt_data, "DS18B20", temperature, TempUnit());
#endif  // USE_WEBSERVER
    }
  }
  Ds18x20Convert();   // Start conversion, takes up to one second
=======
      WSContentSend_PD(HTTP_SNS_TEMP, ds18b20_types, temperature, TempUnit());
#endif  // USE_WEBSERVER
    }
  }
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

<<<<<<< HEAD
#define XSNS_05

boolean Xsns05(byte function)
{
  boolean result = false;

  if (pin[GPIO_DSB] < 99) {
    switch (function) {
      case FUNC_INIT:
        Ds18x20Init();
        break;
      case FUNC_PREP_BEFORE_TELEPERIOD:
        Ds18x20Convert();   // Start conversion, takes up to one second
=======
bool Xsns05(uint8_t function)
{
  bool result = false;

  if (pin[GPIO_DSB] < 99) {
    switch (function) {
      case FUNC_EVERY_SECOND:
        Ds18b20EverySecond();
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
        break;
      case FUNC_JSON_APPEND:
        Ds18b20Show(1);
        break;
#ifdef USE_WEBSERVER
<<<<<<< HEAD
      case FUNC_WEB_APPEND:
=======
      case FUNC_WEB_SENSOR:
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
        Ds18b20Show(0);
        break;
#endif  // USE_WEBSERVER
    }
  }
  return result;
}

#endif  // USE_DS18B20
