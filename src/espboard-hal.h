#ifndef __ESPBOARD_HAL_H
#define __ESPBOARD_HAL_H

#include <stdint.h>

namespace ESPBoard {

    enum Button {
        A = 0,
        B
    };

    enum Led {
        Red = 0,
        Green,
        Blue
    };

    enum LedState {
        OFF = 0,
        ON
    };

    enum BtnState {
        RELEASED = 0,
        PRESSED
    };

    class HAL{
        public:
        HAL() : tempVal(0), humVal(0), btnState(0), ledVal(0) {}
        void init();
        
        float temperature();
        float humidity();
        BtnState button(Button btn);
        void led(Led led, LedState state);
        void led(uint32_t color);

#ifdef HAL_MOCK
        void setTemperature(float _temp) { tempVal = _temp; }
        void setHumidity(float _hum) { humVal = _hum; }
        void setButton(Button btn, BtnState val);
        uint32_t getLed();
#endif

        private:
        float tempVal;
        float humVal;
        uint32_t btnState;
        uint32_t ledVal;
    };
}

#endif