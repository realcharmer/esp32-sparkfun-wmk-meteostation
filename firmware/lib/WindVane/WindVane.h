#ifndef WIND_H
#define WIND_H

class WindVane {
public:
	WindVane(int vanePin);
	int getDirection();
private:
	int _vanePin;
	const int WIND_DIRECTION[8] = {0, 45, 90, 125, 180, 225, 270, 315};
	const int WIND_ADC[8] = { 954, 2292, 3836, 3432, 2898, 1618, 204, 561 };
};

#endif
