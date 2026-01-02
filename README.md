# IOT_Lib
Supports Network setup, MQTT and Modbus for the ESP32, S3

Platformio.ini Build Flags to enable feature & configuration

APP_VERSION         Application version displayed in header
TAG                 Log Tag & default thing name
APP_LOG_LEVEL       Verbose, Debug, Info, Warn, Error log level
LOG_TO_SERIAL_PORT  Log to serial port

WIFI_STATUS_PIN     Led pin, blink led, fast : NotConnected slow: AP connected On: Station connected
FACTORY_RESET_PIN   Digital input pin for factory reset, used when GPIO0 button is not available

Has_Display         Device has a display
UseLittleFS         HTML pages are store in ESP FS
HasOTA              Enable OTA link in setup page

HasEthernet         Include Ethernet 
HasLTE              Include 4G modem
HasMQTT             Enable MQTT

HasModbus           Enable Modbus 
HasCoils            Include Modbus Coils
HasInputRegisters   Include Modbus Input Registers
HasDiscretes        Include Modbus Discretes
HoldingRegisters    INclude Modbus Registers

HasRS485            Include support for Modbus RTU
RS485_RTS           Modbus RTU Serial port pins
RS485_RXD
RS485_TXD