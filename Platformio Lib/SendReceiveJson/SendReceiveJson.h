#ifndef SendReceiveJson_h
#define SendReceiveJson_h

#include <ArduinoJson.h>
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 0
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

// Define the maximum size of the data that can be sent or received
#define MAX_DATA_SIZE 1000

class SendReceiveJson {
    public:
        SendReceiveJson();
        void begin(void (*callback)(JsonDocument* receivedData));
        void send(const JsonDocument& jsonDoc);
    private:
        static void onDataSent(const uint8_t* mac, esp_now_send_status_t status);
        static void onDataReceived(const uint8_t* mac, const uint8_t* data, int len);
        static SendReceiveJson* _instance;
        void (*_callback)(JsonDocument* receivedData);
        void initBroadcastSlave();
        bool manageSlave();
        void deletePeer();
        esp_now_peer_info_t slave;
};

extern SendReceiveJson sendReceiveJson;

#endif
