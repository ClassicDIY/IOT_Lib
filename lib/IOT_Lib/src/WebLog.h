#pragma once

#include <Arduino.h>
#include "esp_log.h"
#include <time.h>
#include "IOT_Defines.h"
#include <ESPAsyncWebServer.h>

class WebLog
{
public:
	WebLog() {};
	void begin(AsyncWebServer *pwebServer);
	void end();
	void process();

private:
	uint32_t _lastHeap = 0;
};
