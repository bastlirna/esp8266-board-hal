#include "espboard-hal.h"
#include <unity.h>

#include "test-main.h"
#include "colors.h"

using namespace ESPBoard;

HAL hal;

#ifdef HAL_MOCK

static void test_temperature(void) {
    double temp = 25.4;
    
    hal.setTemperature(temp);
    TEST_ASSERT_EQUAL(temp, hal.temperature());

    temp = 50;
    hal.setTemperature(temp);
    TEST_ASSERT_EQUAL(temp, hal.temperature());
}

static void test_humidity(void) {
    double hum = 20;
    
    hal.setHumidity(hum);
    TEST_ASSERT_EQUAL(hum, hal.humidity());

    hum = 50;
    hal.setHumidity(hum);
    TEST_ASSERT_EQUAL(hum, hal.humidity());
}

static void test_buttons(void) {
    
    hal.setButton(Button::A, BtnState::RELEASED);
    hal.setButton(Button::B, BtnState::RELEASED);

    TEST_ASSERT_EQUAL(BtnState::RELEASED, hal.button(Button::A));
    TEST_ASSERT_EQUAL(BtnState::RELEASED, hal.button(Button::B));

    hal.setButton(Button::A, BtnState::PRESSED);
    TEST_ASSERT_EQUAL(BtnState::PRESSED, hal.button(Button::A));
    TEST_ASSERT_EQUAL(BtnState::RELEASED, hal.button(Button::B));

    hal.setButton(Button::B, BtnState::PRESSED);
    TEST_ASSERT_EQUAL(BtnState::PRESSED, hal.button(Button::A));
    TEST_ASSERT_EQUAL(BtnState::PRESSED, hal.button(Button::B));

    hal.setButton(Button::A, BtnState::RELEASED);
    TEST_ASSERT_EQUAL(BtnState::RELEASED, hal.button(Button::A));
    TEST_ASSERT_EQUAL(BtnState::PRESSED, hal.button(Button::B));

}

static void test_leds(void) {
    
    hal.led(ESPBoard::Led::Red, LedState::OFF);
    hal.led(ESPBoard::Led::Green, LedState::OFF);
    hal.led(ESPBoard::Led::Blue, LedState::OFF);
    TEST_ASSERT_EQUAL_HEX32(0x000000, hal.getLed());

    hal.led(ESPBoard::Led::Red, LedState::ON);
    hal.led(ESPBoard::Led::Green, LedState::OFF);
    hal.led(ESPBoard::Led::Blue, LedState::OFF);
    TEST_ASSERT_EQUAL_HEX32(0xFF0000, hal.getLed());

    hal.led(ESPBoard::Led::Red, LedState::OFF);
    hal.led(ESPBoard::Led::Green, LedState::ON);
    hal.led(ESPBoard::Led::Blue, LedState::OFF);
    TEST_ASSERT_EQUAL_HEX32(0x00FF00, hal.getLed());

    hal.led(ESPBoard::Led::Red, LedState::OFF);
    hal.led(ESPBoard::Led::Green, LedState::OFF);
    hal.led(ESPBoard::Led::Blue, LedState::ON);
    TEST_ASSERT_EQUAL_HEX32(0x0000FF, hal.getLed());

}

static void test_color(void) {
    
    hal.led(COLOR_BLACK);
    TEST_ASSERT_EQUAL_HEX32(COLOR_BLACK, hal.getLed());

    hal.led(COLOR_RED);
    TEST_ASSERT_EQUAL_HEX32(COLOR_RED, hal.getLed());

    hal.led(COLOR_BLUE);
    TEST_ASSERT_EQUAL_HEX32(COLOR_BLUE, hal.getLed());

    hal.led(COLOR_GREEN);
    TEST_ASSERT_EQUAL_HEX32(COLOR_GREEN, hal.getLed());

    hal.led(COLOR_WHITE);
    TEST_ASSERT_EQUAL_HEX32(COLOR_WHITE, hal.getLed());

}
#else

static void test_temperature_hw(void) {
    TEST_ASSERT_FLOAT_WITHIN(120, 40, hal.temperature());
}

static void test_humidity_hw(void) {
    TEST_ASSERT_FLOAT_WITHIN(100, 50, hal.humidity());
}

static void test_btn_hw(void) {
    TEST_ASSERT_EQUAL(BtnState::RELEASED, hal.button(Button::A));
    TEST_ASSERT_EQUAL(BtnState::RELEASED, hal.button(Button::B));
}

#endif



void runTest() {

    UNITY_BEGIN();    // IMPORTANT LINE!
    
    hal.init();

#ifdef HAL_MOCK
    RUN_TEST(test_temperature);
    RUN_TEST(test_humidity);
    RUN_TEST(test_buttons);
    RUN_TEST(test_leds);
    RUN_TEST(test_color);
#else 
    RUN_TEST(test_temperature_hw);
    RUN_TEST(test_humidity_hw);
    RUN_TEST(test_btn_hw);
#endif

    UNITY_END(); // stop unit testing

}


// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }
