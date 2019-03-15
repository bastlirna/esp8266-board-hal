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
    
    hal.setButton(BTN_A, BTN_RELEASED);
    hal.setButton(BTN_B, BTN_RELEASED);

    TEST_ASSERT_EQUAL(BTN_RELEASED, hal.button(BTN_A));
    TEST_ASSERT_EQUAL(BTN_RELEASED, hal.button(BTN_B));

    hal.setButton(BTN_A, BTN_PRESSED);
    TEST_ASSERT_EQUAL(BTN_PRESSED, hal.button(BTN_A));
    TEST_ASSERT_EQUAL(BTN_RELEASED, hal.button(BTN_B));

    hal.setButton(BTN_B, BTN_PRESSED);
    TEST_ASSERT_EQUAL(BTN_PRESSED, hal.button(BTN_A));
    TEST_ASSERT_EQUAL(BTN_PRESSED, hal.button(BTN_B));

    hal.setButton(BTN_A, BTN_RELEASED);
    TEST_ASSERT_EQUAL(BTN_RELEASED, hal.button(BTN_A));
    TEST_ASSERT_EQUAL(BTN_PRESSED, hal.button(BTN_B));

}

static void test_leds(void) {
    
    hal.led(LED_R, LED_OFF);
    hal.led(LED_G, LED_OFF);
    hal.led(LED_B, LED_OFF);
    TEST_ASSERT_EQUAL_HEX32(0x000000, hal.getLed());

    hal.led(LED_R, LED_ON);
    hal.led(LED_G, LED_OFF);
    hal.led(LED_B, LED_OFF);
    TEST_ASSERT_EQUAL_HEX32(0xFF0000, hal.getLed());

    hal.led(LED_R, LED_OFF);
    hal.led(LED_G, LED_ON);
    hal.led(LED_B, LED_OFF);
    TEST_ASSERT_EQUAL_HEX32(0x00FF00, hal.getLed());

    hal.led(LED_R, LED_OFF);
    hal.led(LED_G, LED_OFF);
    hal.led(LED_B, LED_ON);
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
    TEST_ASSERT_EQUAL(BTN_RELEASED, hal.button(BTN_A));
    TEST_ASSERT_EQUAL(BTN_RELEASED, hal.button(BTN_B));
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
