#ifndef SerialToHttp_H
#define SerialToHttp_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class SerialToHttp {
public:
    SerialToHttp(const char* ssid, const char* password, const char* url);
    void begin();
    void handleSerialData();

private:
    static SerialToHttp* _instance;
    static void (*_userCallback)(JsonDocument* receivedData);
    const char* _ssid;
    const char* _password;
    const char* _url;
    static bool _serialDataAvailable;
    String jsonString = "";
    void sendJsonOverHttp();
};

#endif 
