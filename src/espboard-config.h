#ifndef __ESPBOARD_CONFIG_H
#define __ESPBOARD_CONFIG_H

#define PWM_MAX 1023
#define LED_PIN_R 14
#define LED_PIN_G 12
#define LED_PIN_B 16

#define BTN_A_PIN 4
#define BTN_B_PIN 5

#define DHT_PIN 13

#ifndef DHT_TYPE 
#define DHT_TYPE DHT11
#endif

#define DEBOUNCE_NUM_TO_KEEP 10

#endif
