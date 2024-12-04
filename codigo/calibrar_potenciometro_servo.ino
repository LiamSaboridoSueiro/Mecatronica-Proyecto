const int servoPin = 12; // Pin GPIO 12 de la ESP32 conectado al servo

void setup() {
  pinMode(servoPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Detiene el servo durante 10 segundos
  Serial.println("Deteniendo servo...");
  moveServoForDuration(1500, 10000); // Pulso central para detener el servo
}

// Función para mover el servo modificado durante un tiempo
void moveServoForDuration(int pulseWidth, int durationMs) {
  unsigned long startTime = millis(); // Marca el tiempo de inicio
  
  while (millis() - startTime < durationMs) {
    digitalWrite(servoPin, HIGH); // Pulso alto
    delayMicroseconds(pulseWidth); // Duración del pulso
    digitalWrite(servoPin, LOW); // Pulso bajo
    delayMicroseconds(20000 - pulseWidth); // Duración del periodo restante (20 ms - pulso)
  }
}
