// Main code for the project

#include <Arduino.h>

void setup(){
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(921600);
    Serial.println("Hello from the serial port!");

}

void loop(){
    // put your main code here, to run repeatedly:
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    Serial.println("Hello from the loop!");
}