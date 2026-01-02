#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "IOTEnumerations.h"
#include "IOTCallbackInterface.h"

namespace CLASSICDIY
{
   class IOTServiceInterface
   {
   public:
      virtual void Init(IOTCallbackInterface *iotCB);
      virtual void Run();
      virtual void PostWeb(const String &msg);
      virtual String getThingName() = 0;
#ifdef HasMQTT
      // MQTT related methods
      virtual boolean Publish(const char *subtopic, const char *value, boolean retained) = 0;
      virtual boolean Publish(const char *subtopic, float value, boolean retained) = 0;
      virtual boolean PublishMessage(const char *topic, JsonDocument &payload, boolean retained) = 0;
      virtual String getRootTopicPrefix() = 0;
      virtual u_int getUniqueId() = 0;

#endif
#ifdef HasModbus
      // Modbus related methods
      virtual uint16_t getMBBaseAddress(IOTypes type) = 0;
      virtual void registerMBTCPWorkers(FunctionCode fc, MBSworker worker) = 0;
#endif
   };
} // namespace CLASSICDIY