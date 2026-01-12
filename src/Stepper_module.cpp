#include "../inc/Stepper_module.h"
#include "../inc/pins.h"
#include "../inc/HX711_driver.h"
#include <Arduino.h>
#include <Stepper.h>

#define STEPS 2048
#define MAX_RETRY 3

static Stepper s = Stepper(STEPS, IN1, IN2, IN3, IN4);
extern HX711_t cantar;

void Stepper_init() {
    s.setSpeed(10);
    Stepper_stop();
}

void Stepper_stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

int Stepper_dispense(float targetGrams) {
    float currentWeight = HX711_get_weight(&cantar);

    if (currentWeight >= targetGrams) {
        Serial.println("already full");
        return 1;
    }
    
    long currentSteps = 0;
    long stepLimit = 5000;
    int retryCount = 0;

    float newWeight = currentWeight;

    while (newWeight < targetGrams && retryCount < MAX_RETRY)
    {
        s.step(-1000);
        currentSteps += 1000;

        newWeight = HX711_get_weight(&cantar);
        if (currentSteps >= stepLimit)
        {
            if (newWeight - currentWeight < 0.5f) {
                retryCount++;
                Serial.println("no weight change detected, retrying...");
                s.step(1000);
                delay(200);
                s.step(-1000);

                currentSteps = 0;
            } else {
                currentWeight = newWeight;
                currentSteps = 0;
                retryCount = 0; 
            }
        }
    }

    if (retryCount >= MAX_RETRY) 
    {
        Serial.println("error: check dispenser mechanism");
        return -1;
    }
    return 1;

}