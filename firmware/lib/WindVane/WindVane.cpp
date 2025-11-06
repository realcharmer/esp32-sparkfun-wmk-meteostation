#include <Arduino.h>
#include "WindVane.h"

WindVane::WindVane(int vanePin) {
	_vanePin = vanePin;
}

int WindVane::getDirection() {
	int raw = analogRead(_vanePin);
	int minDiff = 4096;
	int minIndex = 0;
	for (int i = 0; i < 8; i++) {
		int diff = raw - WIND_ADC[i];
		if (diff < 0) diff = -diff;
		if (diff < minDiff) {
			minDiff = diff;
			minIndex = i;
		}
	}
	return WIND_DIRECTION[minIndex];
}
