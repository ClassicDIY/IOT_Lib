#include <Arduino.h>
#include <ArduinoJson.h>
#include "Log.h"
#include "WebLog.h"
#include "IOT.h"
#include "app.htm"
#include "Thing.h"

IOT _iot = IOT();

void Thing::Setup() { _iot.Init(this); }

void Thing::onSaveSetting(JsonDocument &doc) {
   doc["_appState"] = _appState;
   logd("Save app settings data: %s", formattedJson(doc).c_str());
}

void Thing::onLoadSetting(JsonDocument &doc) {
   logd("Load app settings data: %s", formattedJson(doc).c_str());
   _appState = doc["_appState"].as<String>();
}

String Thing::appTemplateProcessor(const String &var) {
   if (var == "title") {
      return String(_iot.getThingName().c_str());
   }
   if (var == "version") {
      return String(APP_VERSION);
   }
   if (var == "home_html") {
      String home;
      home.reserve(strlen(home_html));
      home += home_html;
      return home;
   }
   if (var == "home_script") {
      String script;
      script += "const gpioValues = JSON.parse(event.data);\n";
      script += "document.getElementById('AppState').innerHTML = gpioValues._appState;\n";
      return script;
   }
   if (var == "app_fields") {
      return String(app_config_fields);
   }
   if (var == "state_value") {
      return _appState;
   }
   logd("Did not find app template for: %s", var.c_str());
   return String("");
}

void Thing::Process() {
   _iot.Run();
   uint32_t now = millis();
   if ((now - _lastPublishTimeStamp) > PUBLISH_RATE_LIMIT) { // limit broadcast to rate limit
      _lastPublishTimeStamp = now;
      String s;
      JsonDocument doc;
      doc.clear();
      doc["_appState"] = _appState.c_str();
      serializeJson(doc, s);
      _iot.PostWeb(s);
      if (_lastMessagePublished == s) // anything changed?
      {
         return;
      }
      // publish to MQTT etc
#ifdef HasMQTT
      _iot.Publish("readings", s.c_str(), false);
#endif
      _lastMessagePublished = s;
      logv("Published readings: %s", s.c_str());
   }
   return;
}

void Thing::onSocketPong() {
   _lastMessagePublished.clear(); // force a broadcast
}

void Thing::onNetworkState(NetworkState state) { _networkState = state; }

#ifdef HasMQTT

void Thing::onMqttConnect(esp_mqtt_client_handle_t &client) {
   if (!_discoveryPublished) {
      // Publish Discovery ...
   }
}

void Thing::onMqttMessage(char *topic, char *payload) {
   // process incomming MQTT command
}
#endif