/*
 * Nombre del proyecto: Kantam
 * Copyright (C) 2024 Kantamers
 *
 * Este archivo es parte de Mecatronica-Proyecto.
 *
 * Mecatronica-Proyecto es software libre: usted puede redistribuirlo y/o modificarlo
 * bajo los términos de la Licencia Pública General Reducida de GNU publicada
 * por la Free Software Foundation, ya sea la versión 2.1 de la Licencia, o (a su elección)
 * cualquier versión posterior.
 *
 * Mecatronica-Proyecto se distribuye con la esperanza de que sea útil,
 * pero SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita
 * MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. Consulte
 * la Licencia Pública General Reducida de GNU para más detalles.
 *
 * Usted debería haber recibido una copia de la Licencia Pública General Reducida de GNU
 * junto con este programa. En caso contrario, consulte <https://www.gnu.org/licenses/>.
 */

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
