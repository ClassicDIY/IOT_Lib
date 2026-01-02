#include "IOTCallbackInterface.h"
#include "IDisplayServiceInterface.h"
#include "IOTCallbackInterface.h"
#include "Enumerations.h"
#include "Log.h"
#include "FakeOled.h"

using namespace CLASSICDIY;

#define PUBLISH_RATE_LIMIT 500

class Thing : public IOTCallbackInterface {
 public:
   Thing() {};

   void Setup();
   void Process();
#ifdef HasMQTT
   void onMqttConnect(esp_mqtt_client_handle_t &client);
   void onMqttMessage(char *topic, char *payload);
#endif
#if defined(HasModbus) && defined(HasRS485)
   bool onModbusMessage(ModbusMessage &msg);
#endif
   void onNetworkState(NetworkState state);
   void onSocketPong();
   void onSaveSetting(JsonDocument &doc);
   void onLoadSetting(JsonDocument &doc);
   String appTemplateProcessor(const String &var);
   IDisplayServiceInterface& getDisplayInterface() override {  return _oled; };

 protected:
#ifdef HasMQTT
   boolean PublishDiscoverySub(IOTypes type, const char *entityName, const char *unit_of_meas = nullptr, const char *icon = nullptr);
#endif
 private:
   unsigned long _lastPublishTimeStamp = 0;
   boolean _discoveryPublished = false;
   String _lastMessagePublished;
   String _bodyBuffer;
   NetworkState _networkState = Boot;
   String _appState = "Default text";
   int _level = 0;
   FakeOled _oled = FakeOled();
};
