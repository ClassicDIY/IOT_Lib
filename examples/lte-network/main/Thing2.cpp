#include <Arduino.h>
#include <ArduinoJson.h>
#include "Log.h"
#include "WebLog.h"
#include "IOT.h"
#include "app.htm"
#include "Thing2.h"

IOT _iot = IOT();

void Thing2::Setup() { _iot.Init(this); }

void Thing2::onSaveSetting(JsonDocument &doc) {
   doc["_appState"] = _appState;
   doc["_level"] = _level;
   logd("Save app settings data: %s", formattedJson(doc).c_str());
}

void Thing2::onLoadSetting(JsonDocument &doc) {
   logd("Load app settings data: %s", formattedJson(doc).c_str());
   _appState = doc["_appState"].as<String>();
   _level = doc["_level"].as<int>();
}

String Thing2::appTemplateProcessor(const String &var) {
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
      script += "document.getElementById('Level').innerHTML = gpioValues._level;\n";
      return script;
   }
   if (var == "app_fields") {
      return String(app_config_fields);
   }
   if (var == "state_value") {
      return _appState;
   }
   if (var == "level_value") {
      return String(_level);
   }
   logd("Did not find app template for: %s", var.c_str());
   return String("");
}

void Thing2::Process() {
   _iot.Run();
   uint32_t now = millis();
   if ((now - _lastPublishTimeStamp) > PUBLISH_RATE_LIMIT) { // limit broadcast to rate limit
      _lastPublishTimeStamp = now;
      String s;
      JsonDocument doc;
      doc.clear();
      doc["_appState"] = _appState.c_str();
      doc["_level"] = _level;
      serializeJson(doc, s);
      _iot.PostWeb(s);
      if (_lastMessagePublished == s) // anyThing2 changed?
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

void Thing2::onSocketPong() {
   _lastMessagePublished.clear(); // force a broadcast
}

void Thing2::onNetworkState(NetworkState state) { 
   _networkState = state; 
#ifdef HasModbus
      // READ_INPUT_REGISTER
      auto modbusFC04 = [this](ModbusMessage request) -> ModbusMessage {
         ModbusMessage response;
         uint16_t addr = 0;
         uint16_t words = 0;
         request.get(2, addr);
         request.get(4, words);
         logd("READ_INPUT_REGISTER %d %d[%d]", request.getFunctionCode(), addr, words);
         addr -= _iot.getMBBaseAddress(AnalogInputs);
         if ((addr + words) == 1) { // just have the level
            response.add(request.getServerID(), request.getFunctionCode(), (uint8_t)(words * 2));
            response.add((uint16_t)_level);
         } else {
            logw("READ_INPUT_REGISTER Address overflow: %d", (addr + words));
            response.setError(request.getServerID(), request.getFunctionCode(), ILLEGAL_DATA_ADDRESS);
         }
         return response;
      };
      // READ_COIL
      // auto modbusFC01 = [this](ModbusMessage request) -> ModbusMessage {
      //    ModbusMessage response;
      //    uint16_t addr = 0;
      //    uint16_t numCoils = 0;
      //    request.get(2, addr, numCoils);
      //    logd("READ_COIL %d %d[%d]", request.getFunctionCode(), addr, numCoils);
      //    // Address overflow?
      //    addr -= _iot.getMBBaseAddress(DigitalOutputs);
      //    if ((addr + numCoils) <= NumberOfRelays()) {
      //       CoilSet coils;
      //       coils.Init(NumberOfRelays());
      //       for (int i = 0; i < NumberOfRelays(); i++) {
      //          coils.set(i, GetRelay(i) == 0 ? false : true);
      //       }
      //       vector<uint8_t> coilset = coils.slice(addr, NumberOfRelays());
      //       response.add(request.getServerID(), request.getFunctionCode(), (uint8_t)coilset.size(), coilset);
      //    } else {
      //       logw("READ_COIL Address overflow: %d", (addr + numCoils));
      //       response.setError(request.getServerID(), request.getFunctionCode(), ILLEGAL_DATA_ADDRESS);
      //    }
      //    return response;
      // };
      _iot.registerMBTCPWorkers(READ_INPUT_REGISTER, modbusFC04);
      // _iot.registerMBTCPWorkers(READ_COIL, modbusFC01);
#endif
}

#ifdef HasMQTT

void Thing2::onMqttConnect(esp_mqtt_client_handle_t &client) {
   if (!_discoveryPublished) {
      // Publish Discovery ...
   }
}

void Thing2::onMqttMessage(char *topic, char *payload) {
   // process incomming MQTT command
}
#endif