#include "Button.h"

SemaphoreHandle_t interruptSemaphore;

Button::Button() {
}

void Button::begin(void (*sendButton)(bool* song_playing), bool* song_playing) {
    this->song_playing = song_playing;
    this->sendButton = sendButton;
    pinMode(this->pin, INPUT);
    pinMode(this->ledPin, OUTPUT);
    gpio_set_pull_mode(static_cast<gpio_num_t>(this->pin), GPIO_PULLDOWN_ONLY);

    TaskHandle_t taskHandle;
    xTaskCreate(analizeButton, // Task function
              "Analize Button", // Task name
              2000, // Stack size
              NULL, 
              0 ,// Priority
              &taskHandle );
    Serial.println(uxTaskGetStackHighWaterMark(taskHandle));
    interruptSemaphore = xSemaphoreCreateBinary();
    if (interruptSemaphore != NULL) 
    {
        attachInterrupt(digitalPinToInterrupt(2), interruptHandler, HIGH);
    }  
}

Button button;


void interruptHandler() {
    BaseType_t  xHigherPriorityTaskWoken  pdFALSE;
    xSemaphoreGiveFromISR(interruptSemaphore, &xHigherPriorityTaskWoken);
}

void analizeButton(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
            Serial.println("analizing button");
            static int lastDebounceTime = millis();

            if ((millis() - lastDebounceTime) > button.debounceTime) {
                *(button.song_playing) = !(*(button.song_playing));
                digitalWrite(button.ledPin, *(button.song_playing) ? HIGH : LOW);
                button.sendButton(button.song_playing);
            }
            lastDebounceTime = millis();
        }
    }
}
