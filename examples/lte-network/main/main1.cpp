#include <Arduino.h>
#include <esp_task_wdt.h>
#include "main1.h"
#include "Log.h"
#include "Thing2.h"

using namespace CLASSICDIY;

static Main1 my_main;
Thing2 *_thing = new Thing2();

esp_err_t Main1::setup() {
    // wait for Serial to connect, give up after 5 seconds, USB may not be connected
    delay(3000);
    unsigned long start = millis();
    Serial.begin(115200);
    while (!Serial)
    {
        if (5000 < millis() - start)
        {
            break;
        }
    }
    esp_err_t ret = ESP_OK;
    logd("------------ESP32 specifications ---------------");
    logd("Chip Model: %s", ESP.getChipModel());
    logd("Chip Revision: %d", ESP.getChipRevision());
    logd("Number of CPU Cores: %d", ESP.getChipCores());
    logd("CPU Frequency: %d MHz", ESP.getCpuFreqMHz());
    logd("Flash Memory Size: %d MB", ESP.getFlashChipSize() / (1024 * 1024));
    logd("Flash Frequency: %d MHz", ESP.getFlashChipSpeed() / 1000000);
    logd("Heap Size: %d KB", ESP.getHeapSize() / 1024);
    logd("Free Heap: %d KB", ESP.getFreeHeap() / 1024);
    logd("------------ESP32 specifications ---------------");
    esp_task_wdt_init(60, true); // 60-second timeout, panic on timeout
    esp_task_wdt_add(NULL);
    _thing->Setup();
    logd("Free Heap after setup: %d KB", ESP.getFreeHeap() / 1024);
    logd("------------Setup Done ---------------");
    return ret;
}

void Main1::loop() {
   _thing->Process();
   esp_task_wdt_reset(); // Feed the watchdog
   delay(10);
}

extern "C" void app_main(void) {
   logi("Creating default event loop");
   // Initialize esp_netif and default event loop
   ESP_ERROR_CHECK(esp_netif_init());
   ESP_ERROR_CHECK(esp_event_loop_create_default());
   logi("Initialising NVS");
   ESP_ERROR_CHECK(nvs_flash_init());
   logi("Calling my_main.setup()");
   ESP_ERROR_CHECK(my_main.setup());
   while (true) {
      my_main.loop();
   }
}