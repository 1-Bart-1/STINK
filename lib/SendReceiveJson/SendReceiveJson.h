#ifndef SendReceiveJson_h
#define SendReceiveJson_h

#include <ArduinoJson.h>
#include <esp_now.h>

// Define the maximum size of the data that can be sent or received
#define MAX_DATA_SIZE 100

class SendReceiveJson {
    public:
        SendReceiveJson();
        void begin();
        void send(const uint8_t* address, const JsonObject& data);
        bool receive(JsonObject& data);
    private:
        static void onDataSent(const uint8_t* mac, esp_now_send_status_t status);
        static void onDataReceived(const uint8_t* mac, const uint8_t* data, int len);
        static SendReceiveJson* instance;
};

extern SendReceiveJson sendReceiveJson;

#endif
