#ifndef ANEMOMETER_H
#define ANEMOMETER_H

#include <Arduino.h>

class Anemometer {
public:
	// kmhPerTick is in hundredths of km/h, e.g., 2.4 km/h -> 240
	Anemometer(uint8_t pin, uint16_t kmhPerTickHundredths = 240, uint32_t gustWindowMs = 5000);

	void begin();
	void tickISR();
	void update();

	uint16_t getWindSpeed() const;
	uint16_t getGust() const;

private:
	uint8_t _pin;
	uint16_t _kmhPerTick;

	volatile uint32_t _lastTickTime;
	volatile uint32_t _tickInterval;

	uint16_t _windSpeed;
	uint16_t _gust;

	uint32_t _gustWindow;
	struct GustRecord {
		uint32_t timestamp;
		uint16_t speed;
	};
	GustRecord* _gustBuffer;
	uint8_t _gustIndex;
	uint8_t _gustCount;
	const uint8_t _maxGustSamples = 50;

	static Anemometer* instance;
	static void ISRHandler();
};

#endif
