# Meteostation

Source files for a simple meteostation built with [SparkFun Weather Meter Kit](https://www.sparkfun.com/products/15901) and ESP32.

## Installation

1. Install PlatformIO
2. Clone this repository
3. Build and flash firmware

Firmware is built using PlatformIO. Change your working directory to the _firmware_ folder and run `make`. You can also use PlatformIO directly with `pio -t upload`.

## Testing

The firmware has an integrated test suite. Simply run `make test` or `pio test`. The ESP32 development board has to be connected for the tests to work.

## References

- [Hookup guide](https://learn.sparkfun.com/tutorials/weather-meter-hookup-guide)
- [Datasheet](docs/datasheet.pdf)
- [Assembly](docs/assembly.pdf)
