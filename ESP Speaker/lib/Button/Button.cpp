#include "Button.h"

SemaphoreHandle_t interruptSemaphore;

Button::Button() {
}

void Button::begin(void (*sendButton)(bool song_playing)) {
    this->sendButton = sendButton;
    pinMode(this->pin, INPUT);
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
                button.song_playing = !button.song_playing;
                button.sendButton(button.song_playing);
            }
            lastDebounceTime = millis();
        }
    }
}
