#include <Arduino.h>
#include "Wind.h"

Wind windSensor(35);

void setup() {
	Serial.begin(115200);
	analogReadResolution(12);
}

void loop() {
	Serial.println(windSensor.getDirection());
	delay(1000);
}
