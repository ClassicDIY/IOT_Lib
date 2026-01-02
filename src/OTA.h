#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "Log.h"
#include "IOT_Defines.h"


namespace CLASSICDIY
{
	class OTA
	{
	public:
		OTA() {};
		void begin(AsyncWebServer* asyncServer);

	private:
        AsyncWebServer* _pAsyncServer;
	};


}