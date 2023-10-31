#include "Hit.h"

SemaphoreHandle_t interruptSemaphore;

Hit::Hit() {
}

void Hit::begin(void (*sendHit)()) {
    this->sendHit = sendHit;
    pinMode(this->pin, INPUT);

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
            Serial.println("analizing hit");
            static int lastDebounceTime = millis();

            if ((millis() - lastDebounceTime) > hit.debounceTime) {
                hit.sendHit();
            }
            lastDebounceTime = millis();
        }
    }
}
