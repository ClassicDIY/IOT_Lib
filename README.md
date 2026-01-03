# IOT_Lib
Supports Network setup, MQTT and Modbus for the ESP32, S3

Platformio.ini Build Flags to enable feature & configuration

<ul>
<li>APP_VERSION:         Application version displayed in header</li>
<li>APP_LOG_TAG:         Log Tag & default thing name</li>
<li>APP_LOG_LEVEL:       Verbose, Debug, Info, Warn, Error log level</li>
<li>LOG_TO_SERIAL_PORT:  Log to serial port</li>

<li>WIFI_STATUS_PIN:     Led pin, blink led, fast : NotConnected slow: AP connected On: Station connected</li>
<li>FACTORY_RESET_PIN:   Digital input pin for factory reset, used when GPIO0 button is not available</li>

<li>Has_Display:         Device has a display, tft or oled...</li>
<li>UseLittleFS:         HTML pages are store in ESP FS</li>
<li>HasOTA:              Enable OTA link in setup page</li>

<li>HasEthernet:         Include Ethernet, requires esp-idf framework</li>
<li>HasLTE:              Include 4G modem, requires esp-idf framework</li>

<li>HasMQTT:             Enable MQTT</li>

<li>HasModbus:           Enable Modbus, requires miq19/eModbus</li>
<li>HasCoils:            Include Modbus Coils</li>
<li>HasInputRegisters:   Include Modbus Input Registers</li>
<li>HasDiscretes:        Include Modbus Discretes</li>
<li>HoldingRegisters:    INclude Modbus Registers</li>

<li>HasRS485:           Include support for Modbus RTU</li>
<li>RS485_RTS:           Modbus RTU Serial port pins</li>
<li>RS485_RXD</li>
<li>RS485_TXD</li>

</ul>
