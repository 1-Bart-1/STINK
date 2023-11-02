#include "SendReceiveJson.h"


SendReceiveJson* SendReceiveJson::_instance = nullptr;

SendReceiveJson::SendReceiveJson() {
    _instance = this;
    _callback = nullptr;
}

void SendReceiveJson::begin(void (*callback)(JsonDocument* receivedData)) {
    _callback = callback;
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        ESP.restart();
    } else {
        Serial.println("ESP-NOW initialized");
    }
    esp_now_register_send_cb(onDataSent);
    esp_now_register_recv_cb(onDataReceived);
    initBroadcastSlave();
}

void SendReceiveJson::deletePeer() {
	const esp_now_peer_info_t *peer = &slave;
	const uint8_t *peer_addr = slave.peer_addr;
	esp_err_t delStatus = esp_now_del_peer(peer_addr);
	Serial.print("Slave Delete Status: ");
	if (delStatus == ESP_OK) {
		// Delete success
		Serial.println("Success");
	}
	else if (delStatus == ESP_ERR_ESPNOW_NOT_INIT) {
		// How did we get so far!!
		Serial.println("ESPNOW Not Init");
	}
	else if (delStatus == ESP_ERR_ESPNOW_ARG) {
		Serial.println("Invalid Argument");
	}
	else if (delStatus == ESP_ERR_ESPNOW_NOT_FOUND) {
		Serial.println("Peer not found.");
	}
	else {
		Serial.println("Not sure what happened");
	}
}

bool SendReceiveJson::manageSlave() {
	if (slave.channel == CHANNEL) {
		if (DELETEBEFOREPAIR) {
			deletePeer();
		}

		Serial.print("Slave Status: ");
		const esp_now_peer_info_t *peer = &slave;
		const uint8_t *peer_addr = slave.peer_addr;
		// check if the peer exists
		bool exists = esp_now_is_peer_exist(peer_addr);
		if (exists) {
			// Slave already paired.
			Serial.println("Already Paired");
			return true;
		}
		else {
			// Slave not paired, attempt pair
			esp_err_t addStatus = esp_now_add_peer(peer);
			if (addStatus == ESP_OK) {
				// Pair success
				Serial.println("Pair success");
				return true;
			}
			else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
				// How did we get so far!!
				Serial.println("ESPNOW Not Init");
				return false;
			}
			else if (addStatus == ESP_ERR_ESPNOW_ARG) {
				Serial.println("Invalid Argument");
				return false;
			}
			else if (addStatus == ESP_ERR_ESPNOW_FULL) {
				Serial.println("Peer list full");
				return false;
			}
			else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
				Serial.println("Out of memory");
				return false;
			}
			else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
				Serial.println("Peer Exists");
				return true;
			}
			else {
				Serial.println("Not sure what happened");
				return false;
			}
		}
	}
	else {
		// No slave found to process
		Serial.println("No Slave found to process");
		return false;
	}
}


void SendReceiveJson::initBroadcastSlave() {
	// clear slave data
	memset(&slave, 0, sizeof(slave));
	for (int ii = 0; ii < 6; ++ii) {
		slave.peer_addr[ii] = (uint8_t)0xff;
	}
	slave.channel = CHANNEL; // pick a channel
	slave.encrypt = 0; // no encryption
	manageSlave();
}

void SendReceiveJson::send(const JsonDocument& jsonDoc) {
    // Serialize the JSON document to a string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

	const uint8_t *peer_addr = slave.peer_addr;

    // Send the JSON string
    esp_now_send(peer_addr, (uint8_t*)jsonString.c_str(), jsonString.length());
}

void SendReceiveJson::onDataSent(const uint8_t* mac, esp_now_send_status_t status) {
    if (status == ESP_NOW_SEND_SUCCESS) {
        Serial.println("Data sent successfully");
    } else {
        Serial.println("Error sending data");
    }
}

void SendReceiveJson::onDataReceived(const uint8_t* mac, const uint8_t* data, int len) {
    // Parse the JSON string
	String json((char*)data);
	DynamicJsonDocument doc(MAX_DATA_SIZE);
	DeserializationError error = deserializeJson(doc, json);

	// Check for parsing errors
	if (error) {
		Serial.println("Error parsing JSON");
		return;
	}

	Serial.println("Data received: " + doc["message"].as<String>());

	_instance->_callback(&doc);
}

SendReceiveJson sendReceiveJson;
