PROJECT_DIR = $(CURDIR)
PLATFORMIO_BIN = /bin/pio

all: build upload

build:
	$(PLATFORMIO_BIN) run -d $(PROJECT_DIR)

upload:
	$(PLATFORMIO_BIN) run -d $(PROJECT_DIR) -t upload

clean:
	$(PLATFORMIO_BIN) run -d $(PROJECT_DIR) -t clean

monitor:
	$(PLATFORMIO_BIN) device monitor

.PHONY: all build upload clean monitor
