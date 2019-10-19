/*
  xsns_01_counter.ino - Counter sensors (water meters, electricity meters etc.) sensor support for Sonoff-Tasmota

<<<<<<< HEAD
  Copyright (C) 2018  Maarten Damen and Theo Arends
=======
  Copyright (C) 2019  Maarten Damen and Theo Arends
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

<<<<<<< HEAD
=======
#ifdef USE_COUNTER
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
/*********************************************************************************************\
 * Counter sensors (water meters, electricity meters etc.)
\*********************************************************************************************/

<<<<<<< HEAD
unsigned long last_counter_timer[MAX_COUNTERS]; // Last counter time in milli seconds

void CounterUpdate(byte index)
{
  unsigned long counter_debounce_time = millis() - last_counter_timer[index -1];
  if (counter_debounce_time > Settings.pulse_counter_debounce) {
    last_counter_timer[index -1] = millis();
=======
#define XSNS_01             1

unsigned long last_counter_timer[MAX_COUNTERS]; // Last counter time in micro seconds

#ifndef ARDUINO_ESP8266_RELEASE_2_3_0       // Fix core 2.5.x ISR not in IRAM Exception
void CounterUpdate(uint8_t index) ICACHE_RAM_ATTR;
void CounterUpdate1(void) ICACHE_RAM_ATTR;
void CounterUpdate2(void) ICACHE_RAM_ATTR;
void CounterUpdate3(void) ICACHE_RAM_ATTR;
void CounterUpdate4(void) ICACHE_RAM_ATTR;
#endif  // ARDUINO_ESP8266_RELEASE_2_3_0

void CounterUpdate(uint8_t index)
{
  unsigned long counter_debounce_time = micros() - last_counter_timer[index -1];
  if (counter_debounce_time > Settings.pulse_counter_debounce * 1000) {
    last_counter_timer[index -1] = micros();
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
    if (bitRead(Settings.pulse_counter_type, index -1)) {
      RtcSettings.pulse_counter[index -1] = counter_debounce_time;
    } else {
      RtcSettings.pulse_counter[index -1]++;
    }

<<<<<<< HEAD
//    snprintf_P(log_data, sizeof(log_data), PSTR("CNTR: Interrupt %d"), index);
//    AddLog(LOG_LEVEL_DEBUG);
  }
}

void CounterUpdate1()
=======
//    AddLog_P2(LOG_LEVEL_DEBUG, PSTR("CNTR: Interrupt %d"), index);
  }
}

void CounterUpdate1(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  CounterUpdate(1);
}

<<<<<<< HEAD
void CounterUpdate2()
=======
void CounterUpdate2(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  CounterUpdate(2);
}

<<<<<<< HEAD
void CounterUpdate3()
=======
void CounterUpdate3(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  CounterUpdate(3);
}

<<<<<<< HEAD
void CounterUpdate4()
=======
void CounterUpdate4(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  CounterUpdate(4);
}

/********************************************************************************************/

<<<<<<< HEAD
void CounterSaveState()
{
  for (byte i = 0; i < MAX_COUNTERS; i++) {
=======
void CounterSaveState(void)
{
  for (uint32_t i = 0; i < MAX_COUNTERS; i++) {
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
    if (pin[GPIO_CNTR1 +i] < 99) {
      Settings.pulse_counter[i] = RtcSettings.pulse_counter[i];
    }
  }
}

<<<<<<< HEAD
void CounterInit()
=======
void CounterInit(void)
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
{
  typedef void (*function) () ;
  function counter_callbacks[] = { CounterUpdate1, CounterUpdate2, CounterUpdate3, CounterUpdate4 };

<<<<<<< HEAD
  for (byte i = 0; i < MAX_COUNTERS; i++) {
    if (pin[GPIO_CNTR1 +i] < 99) {
      pinMode(pin[GPIO_CNTR1 +i], INPUT_PULLUP);
=======
  for (uint32_t i = 0; i < MAX_COUNTERS; i++) {
    if (pin[GPIO_CNTR1 +i] < 99) {
      pinMode(pin[GPIO_CNTR1 +i], bitRead(counter_no_pullup, i) ? INPUT : INPUT_PULLUP);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      attachInterrupt(pin[GPIO_CNTR1 +i], counter_callbacks[i], FALLING);
    }
  }
}

#ifdef USE_WEBSERVER
const char HTTP_SNS_COUNTER[] PROGMEM =
<<<<<<< HEAD
  "%s{s}" D_COUNTER "%d{m}%s%s{e}";  // {s} = <tr><th>, {m} = </th><td>, {e} = </td></tr>
#endif  // USE_WEBSERVER

void CounterShow(boolean json)
{
  char stemp[10];
  char counter[16];

  byte dsxflg = 0;
  byte header = 0;
  for (byte i = 0; i < MAX_COUNTERS; i++) {
    if (pin[GPIO_CNTR1 +i] < 99) {
      if (bitRead(Settings.pulse_counter_type, i)) {
        dtostrfd((double)RtcSettings.pulse_counter[i] / 1000, 3, counter);
      } else {
        dsxflg++;
        dtostrfd(RtcSettings.pulse_counter[i], 0, counter);
=======
  "{s}" D_COUNTER "%d{m}%s%s{e}";  // {s} = <tr><th>, {m} = </th><td>, {e} = </td></tr>
#endif  // USE_WEBSERVER

void CounterShow(bool json)
{
  char stemp[10];

  uint8_t dsxflg = 0;
  uint8_t header = 0;
  for (uint32_t i = 0; i < MAX_COUNTERS; i++) {
    if (pin[GPIO_CNTR1 +i] < 99) {
      char counter[33];
      if (bitRead(Settings.pulse_counter_type, i)) {
        dtostrfd((double)RtcSettings.pulse_counter[i] / 1000000, 6, counter);
      } else {
        dsxflg++;
        snprintf_P(counter, sizeof(counter), PSTR("%lu"), RtcSettings.pulse_counter[i]);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      }

      if (json) {
        if (!header) {
<<<<<<< HEAD
          snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s,\"COUNTER\":{"), mqtt_data);
          stemp[0] = '\0';
        }
        header++;
        snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s%s\"C%d\":%s"), mqtt_data, stemp, i +1, counter);
        strcpy(stemp, ",");
=======
          ResponseAppend_P(PSTR(",\"COUNTER\":{"));
          stemp[0] = '\0';
        }
        header++;
        ResponseAppend_P(PSTR("%s\"C%d\":%s"), stemp, i +1, counter);
        strlcpy(stemp, ",", sizeof(stemp));
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
#ifdef USE_DOMOTICZ
        if ((0 == tele_period) && (1 == dsxflg)) {
          DomoticzSensor(DZ_COUNT, RtcSettings.pulse_counter[i]);
          dsxflg++;
        }
#endif  // USE_DOMOTICZ
#ifdef USE_WEBSERVER
      } else {
<<<<<<< HEAD
        snprintf_P(mqtt_data, sizeof(mqtt_data), HTTP_SNS_COUNTER, mqtt_data, i +1, counter, (bitRead(Settings.pulse_counter_type, i)) ? " " D_UNIT_SECOND : "");
#endif  // USE_WEBSERVER
      }
    }
  }
  if (json) {
    if (header) {
      snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("%s}"), mqtt_data);
=======
        WSContentSend_PD(HTTP_SNS_COUNTER, i +1, counter, (bitRead(Settings.pulse_counter_type, i)) ? " " D_UNIT_SECOND : "");
#endif  // USE_WEBSERVER
      }
    }
    if (bitRead(Settings.pulse_counter_type, i)) {
      RtcSettings.pulse_counter[i] = 0xFFFFFFFF;  // Set Timer to max in case of no more interrupts due to stall of measured device
    }
  }
  if (json) {
    if (header) {
      ResponseJsonEnd();
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
    }
  }
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

<<<<<<< HEAD
#define XSNS_01

boolean Xsns01(byte function)
{
  boolean result = false;
=======
bool Xsns01(uint8_t function)
{
  bool result = false;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347

  switch (function) {
    case FUNC_INIT:
      CounterInit();
      break;
    case FUNC_JSON_APPEND:
      CounterShow(1);
      break;
#ifdef USE_WEBSERVER
<<<<<<< HEAD
    case FUNC_WEB_APPEND:
=======
    case FUNC_WEB_SENSOR:
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      CounterShow(0);
      break;
#endif  // USE_WEBSERVER
    case FUNC_SAVE_BEFORE_RESTART:
<<<<<<< HEAD
=======
    case FUNC_SAVE_AT_MIDNIGHT:
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
      CounterSaveState();
      break;
  }
  return result;
}
<<<<<<< HEAD
=======

#endif  // USE_COUNTER
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347
