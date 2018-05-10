/*
 * Copyright (c) 2018 tick <tickelton@gmail.com>
 *
 * SPDX-License-Identifier:	ISC
 */

#include <avr/sleep.h>

#define PIN_BUZ 0
#define PIN_LED 1

int debug_led_counter = 0;

int delay_map[] = {2, 4, 4, 8, 8, 16};
//int delay_map[] = {2, 2, 2, 5, 5, 5};
volatile int delay_count = 0;

void setup() {
  setup_watchdog();
}

void loop() {

  // if watchdog has run 'delay_count' times
  if (delay_count==0) {
    // set new delay
    delay_count = delay_map[random(0,6)];

    // sound buzzer
    pinMode(PIN_BUZ, OUTPUT);
    digitalWrite(PIN_BUZ, HIGH);
    if (debug_led_counter <2 ) {
      pinMode(PIN_LED, OUTPUT);
      digitalWrite(PIN_LED, HIGH);
    }
    
    delay(1500);
    
    digitalWrite(PIN_BUZ, LOW);
    pinMode(PIN_BUZ, INPUT);
    if (debug_led_counter <2 ) {
      digitalWrite(PIN_LED, LOW);
      pinMode(PIN_LED, INPUT);
      debug_led_counter++;
    }
  }
  
  system_sleep();
}

// NOTE: Use WDTCSR for atmega328 and WDTCR for attiny85
void setup_watchdog() {
  // Reset 'Watchdoch Reset' flag
  MCUSR &= ~(1<<WDRF);
  // enable config mode
  WDTCR = (1<<WDCE)|(1<<WDE);
  // start watchdog
  //WDTCSR = (1<<WDIE) | (1<<WDP2) | (1<<WDP1);
  WDTCR = (1<<WDIE) | (1<<WDP3);
}

void system_sleep() {
  // set mode to 'power down' and enable sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  // do actual sleep
  sleep_mode();

  // execution continues here after watchdog
  sleep_disable();
}

// Watchdog Timeout Interrupt
ISR(WDT_vect) {
  delay_count--;
}
