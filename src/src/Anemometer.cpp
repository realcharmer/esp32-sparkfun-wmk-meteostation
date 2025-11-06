#include "Anemometer.h"

Anemometer* Anemometer::instance = nullptr;

Anemometer::Anemometer(uint8_t pin, uint16_t kmhPerTickHundredths, uint32_t gustWindowMs)
	: _pin(pin), _kmhPerTick(kmhPerTickHundredths), _lastTickTime(0), _tickInterval(0),
	  _windSpeed(0), _gust(0), _gustWindow(gustWindowMs), _gustIndex(0), _gustCount(0)
{
	_gustBuffer = new GustRecord[_maxGustSamples];
}

void Anemometer::begin() {
	pinMode(_pin, INPUT_PULLUP);
	instance = this;
	attachInterrupt(digitalPinToInterrupt(_pin), ISRHandler, FALLING);
}

void Anemometer::ISRHandler() {
	if (instance) instance->tickISR();
}

void Anemometer::tickISR() {
	uint32_t now = micros();

	if (_lastTickTime != 0) {
		uint32_t interval = now - _lastTickTime;
		if (interval > 0) {
			// speed = kmhPerTick / seconds; scaled to hundredths
			// interval in microseconds, so multiply numerator by 1,000,000
			_windSpeed = (_kmhPerTick * 1000000UL) / interval;
		}
	}

	_lastTickTime = now;

	// store in gust buffer
	uint32_t nowMillis = millis();
	_gustBuffer[_gustIndex].timestamp = nowMillis;
	_gustBuffer[_gustIndex].speed = _windSpeed;
	_gustIndex = (_gustIndex + 1) % _maxGustSamples;
	if (_gustCount < _maxGustSamples) _gustCount++;
}

void Anemometer::update() {
	uint32_t nowMillis = millis();
	uint32_t nowMicros = micros();

	// zero wind speed if no ticks for 2 seconds
	if (_lastTickTime != 0 && (nowMicros - _lastTickTime) > 2000000UL) {
		_windSpeed = 0;
	}

	// update gust
	_gust = 0;
	for (uint8_t i = 0; i < _gustCount; i++) {
		if (nowMillis - _gustBuffer[i].timestamp <= _gustWindow) {
			if (_gustBuffer[i].speed > _gust) _gust = _gustBuffer[i].speed;
		}
	}
}

uint16_t Anemometer::getWindSpeed() const {
	return _windSpeed;
}

uint16_t Anemometer::getGust() const {
	return _gust;
}
