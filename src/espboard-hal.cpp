#include "espboard-hal.h"
#include "espboard-config.h"
#include "colors.h"


#ifndef HAL_MOCK
#include <Arduino.h>
#include <DHT.h>
#include <DebouncedInput.h>
#endif

using namespace ESPBoard;

#ifndef HAL_MOCK
DHT dht(DHT_PIN, DHT_TYPE);
DebouncedInput buttons[] { 
    DebouncedInput(BTN_A, 20, true, DEBOUNCE_NUM_TO_KEEP), 
    DebouncedInput(BTN_B, 20, true, DEBOUNCE_NUM_TO_KEEP)
};
#endif

static void ledColor(uint32_t color);
static void ledInner(uint8_t pin, uint8_t intensity);

void HAL::init() 
{
    ledColor(COLOR_BLACK);

    #ifndef HAL_MOCK
    pinMode(LED_PIN_R, OUTPUT);
    pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_B, OUTPUT);

    dht.begin();
    buttons[0].begin();
    buttons[1].begin();
    #endif
}

BtnState HAL::button(Button btn) 
{ 
#ifndef HAL_MOCK
    if (buttons[(uint8_t) btn].changedTo(LOW)) {
        return BtnState::PRESSED;
    }

    return BtnState::RELEASED; 
#else
    if((btnState & (1 << (uint32_t)btn)) != 0) {
        return BtnState::PRESSED;
    }

    return BtnState::RELEASED; 
#endif
}

#ifdef HAL_MOCK
void HAL::setButton(Button btn, BtnState val) 
{ 
    
    btnState &= ~(1 << (uint32_t)btn);

    if (val) {
        btnState |= (1 << (uint32_t)btn);
    }
}
#endif

void HAL::led(Led led, LedState state)
{
    uint16_t bitpos = 16 - (uint32_t)led * 8;
    ledVal &= ~(0xFF << bitpos);
    if (state == LedState::ON) {
        ledVal |= (0xFF << bitpos);
    }
    ledColor(ledVal);
}

void HAL::led(uint32_t color)
{
    ledVal = color & 0xFFFFFF;
    ledColor(ledVal);
}

#ifdef HAL_MOCK
uint32_t HAL::getLed()
{
    return ledVal;
}
#endif


float HAL::temperature() 
{ 
#ifndef HAL_MOCK
    return dht.readTemperature();
#else
    return tempVal; 
#endif
}

float HAL::humidity() 
{ 
#ifndef HAL_MOCK
    return dht.readHumidity();
#else
    return humVal; 
#endif
}

static void ledColor(uint32_t color) 
{
#ifndef HAL_MOCK

    ledInner(LED_PIN_B, color & 0xFF);
    ledInner(LED_PIN_G, (color >> 8) & 0xFF);
    ledInner(LED_PIN_R, (color >> 16) & 0xFF);

#endif
}

static void ledInner(uint8_t pin, uint8_t intensity) 
{
#ifndef HAL_MOCK

    if (intensity == 0) {
        digitalWrite(pin, 1);
    } else if (intensity == 0xFF) {
        digitalWrite(pin, 0);
    } else {
        analogWrite(pin, ((float)intensity / 255.0) * (float)PWM_MAX);
    }

#endif
}
