#include <Bluepad32.h>

// Pines de hardware
#define ENA 32 // Pin PWM para Motor A (habilitación)
#define IN1 33 // Pin dirección Motor A
#define IN2 25 // Pin dirección Motor A
#define ENB 26 // Pin PWM para Motor B (habilitación)
#define IN3 27 // Pin dirección Motor B
#define IN4 14 // Pin dirección Motor B
const int servoPin = 13; // Pin GPIO conectado al servo

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// Configuración de los motores
void setupMotors() {
  // Configuración de pines para Motor A
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Configuración de pines para Motor B
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Inicializar ambos motores apagados
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); // Velocidad 0 (apagado)
  analogWrite(ENB, 0); // Velocidad 0 (apagado)
}

// Función para mover el servo a un ángulo específico
void moveServo(int angle) {
  int pulseWidth = map(angle, 0, 180, 500, 2500); // Calcula el ancho del pulso en microsegundos (500-2500 us)
  
  // Genera un pulso de 20 ms de duración (frecuencia de 50 Hz)
  for (int i = 0; i < 50; i++) { // 50 ciclos para garantizar estabilidad del movimiento
    digitalWrite(servoPin, HIGH); // Pulso alto
    delayMicroseconds(pulseWidth); // Duración del pulso según el ángulo
    digitalWrite(servoPin, LOW); // Pulso bajo
    delayMicroseconds(20000 - pulseWidth); // Duración del periodo restante (20 ms - pulso)
  }
}

// Procesa el joystick para mover los motores
void processJoystick(ControllerPtr ctl) {
  int yAxis = ctl->axisY();  // Valor del eje Y del joystick

  if (yAxis < -20) {  // Hacia adelante
    int speed = map(abs(yAxis), 0, 128, 0, 255);  // Ajusta la velocidad

    // Motor A hacia adelante
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    analogWrite(ENA, speed);

    // Motor B hacia adelante
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW);
    analogWrite(ENB, speed);
  } else if (yAxis > 20) {  // Hacia atrás
    int speed = map(yAxis, 0, 128, 0, 255);  // Ajusta la velocidad

    // Motor A hacia atrás
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, speed);

    // Motor B hacia atrás
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, speed);
  } else { // Detener motores
    // Detiene Motor A
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);

    // Detiene Motor B
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
  }
}

// Procesa el mando para detectar botón y mover el servo
void processGamepad(ControllerPtr ctl) {
  processJoystick(ctl);

  // Cuando se presiona el botón "A"
  if (ctl->a()) {
    Serial.println("Botón A presionado, moviendo servo...");
    // Espera 1 segundo
    moveServo(180);  // Mueve el servo al ángulo 180
    delay(1000);     // Espera 1 segundo
    moveServo(0);    // Devuelve el servo al ángulo 0
  }
}

// Callback cuando se conecta un nuevo mando
void onConnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.printf("CALLBACK: Controller conectado, índice=%d\n", i);
      myControllers[i] = ctl;
      break;
    }
  }
}

// Callback cuando se desconecta un mando
void onDisconnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.printf("CALLBACK: Controller desconectado de índice=%d\n", i);
      myControllers[i] = nullptr;
      break;
    }
  }
}

// Procesa todos los mandos conectados
void processControllers() {
  for (auto myController : myControllers) {
    if (myController && myController->isConnected() && myController->hasData() && myController->isGamepad()) {
      processGamepad(myController);
    }
  }
}

// Configuración inicial
void setup() {
  Serial.begin(115200);
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
  
  setupMotors();  // Configura los motores
  pinMode(servoPin, OUTPUT); // Configura el pin del servo como salida

  // Mueve el servo a la posición inicial (0 grados)
  Serial.println("Inicializando servo a 0 grados...");
  moveServo(0);
  delay(1000); // Espera 1 segundo para completar el movimiento
}


// Bucle principal
void loop() {
  bool dataUpdated = BP32.update();
  if (dataUpdated) {
    processControllers();
  }
  delay(20);
}
