#include "test-main.h"

#ifdef ARDUINO

#include <Arduino.h>

void setup() {
    delay(2000);

    runTest();
}

void loop() {
    
}

#else

int main() {
    runTest();
}

#endif
