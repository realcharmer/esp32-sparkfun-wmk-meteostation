#include <Arduino.h>
#include <unity.h>
#include "WindVane.h"

WindVane wind(0); // pin not used in getDirectionFromADC()

void test_wind_direction_exact_values() {
	int adc_values[8] = {954, 2292, 3836, 3432, 2898, 1618, 204, 561};
	int expected_directions[8] = {0, 45, 90, 125, 180, 225, 270, 315};

	for (int i = 0; i < 8; i++) {
		int dir = wind.getDirectionFromADC(adc_values[i]);
		TEST_ASSERT_EQUAL_INT(expected_directions[i], dir);
	}
}

void test_wind_direction_near_values() {
	struct TestCase { int adc; int expected; };
	TestCase cases[] = {
		{960, 0},
		{2280, 45},
		{3840, 90},
		{2900, 180},
		{550, 315},
	};

	for (auto &t : cases) {
		int dir = wind.getDirectionFromADC(t.adc);
		TEST_ASSERT_EQUAL_INT(t.expected, dir);
	}
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_wind_direction_exact_values);
	RUN_TEST(test_wind_direction_near_values);
	UNITY_END();
}

void loop() {}
