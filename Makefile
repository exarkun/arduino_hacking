ARDUINO_DIR  = /home/exarkun/Downloads/arduino-1.0.5
BOARDS_TXT   = /home/exarkun/Downloads/arduino-1.0.5/hardware/Microduino/boards.txt

TARGET       = CLItest
ARDUINO_LIBS = OneWire NRF24 SPI

BOARD_TAG    = 644pa16m
VARIANT      = microduino
# MCU          = atmega644p
# F_CPU        = 16000000L
ARDUINO_PORT = /dev/ttyUSB0

include /usr/share/arduino/Arduino.mk
