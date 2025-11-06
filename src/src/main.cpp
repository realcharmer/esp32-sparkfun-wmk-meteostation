#include <Arduino.h>
#include "Anemometer.h"
#include "Wind.h"

Anemometer anemometer(14);
Wind windSensor(35);

void setup() {
	Serial.begin(115200);
	analogReadResolution(12);
	anemometer.begin();
}

void loop() {

	Serial.print("Direction: ");
	Serial.println(windSensor.getDirection());

	anemometer.update();
	uint16_t ws = anemometer.getWindSpeed();
	uint16_t gust = anemometer.getGust();

	Serial.print("Wind Speed: ");
	Serial.print(ws / 100);
	Serial.print(".");
	Serial.print(ws % 100);
	Serial.print(" km/h, Gust: ");
	Serial.print(gust / 100);
	Serial.print(".");
	Serial.print(gust % 100);
	Serial.println(" km/h");

	delay(1000);
}
