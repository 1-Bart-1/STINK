#include "Hit.h"

SemaphoreHandle_t interruptSemaphore;

Hit::Hit() {
}

void Hit::begin(void (*sendHit)()) {
    this->sendHit = sendHit;
    pinMode(this->pin, INPUT);
    gpio_set_pull_mode(static_cast<gpio_num_t>(this->pin), GPIO_PULLUP_ONLY);

    TaskHandle_t taskHandle;
    xTaskCreate(analizeHit, // Task function
              "Analize Hit", // Task name
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

Hit hit;

void interruptHandler() {
    BaseType_t  xHigherPriorityTaskWoken  pdFALSE;
    xSemaphoreGiveFromISR(interruptSemaphore, &xHigherPriorityTaskWoken);
}

void analizeHit(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
            if(hit.song_playing == false) {
                continue;
            }
            static int lastDebounceTime = millis();
            if ((millis() - lastDebounceTime) > hit.debounceTime) {
                hit.sendHit();
            }
            lastDebounceTime = millis();
        }
    }
}
