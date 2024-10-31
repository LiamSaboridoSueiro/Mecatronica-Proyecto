#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// Pines de los motores
const int in1Pin = 14;  // Motor 1 - Dirección 1
const int in2Pin = 27;  // Motor 1 - Dirección 2
const int enPin1 = 25;  // Motor 1 - PWM

const int in3Pin = 26;  // Motor 2 - Dirección 1
const int in4Pin = 33;  // Motor 2 - Dirección 2
const int enPin2 = 32;  // Motor 2 - PWM

int motor1Speed = 0;    // Velocidad deseada para el motor 1
int motor2Speed = 0;    // Velocidad deseada para el motor 2
bool motor1Forward = true; // Dirección deseada para el motor 1
bool motor2Forward = true; // Dirección deseada para el motor 2

// Configuración de los motores
void setupMotors() {
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(enPin1, OUTPUT);
    
    pinMode(in3Pin, OUTPUT);
    pinMode(in4Pin, OUTPUT);
    pinMode(enPin2, OUTPUT);

    // Configura PWM
    ledcSetup(0, 1000, 8);  // Canal 0 para motor 1
    ledcAttachPin(enPin1, 0);
    ledcSetup(1, 1000, 8);  // Canal 1 para motor 2
    ledcAttachPin(enPin2, 1);
}

// Función de tarea para el motor 1
void motor1Task(void *parameter) {
    while (true) {
        if (motor1Forward) {
            digitalWrite(in1Pin, HIGH);
            digitalWrite(in2Pin, LOW);
        } else {
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, HIGH);
        }
        ledcWrite(0, motor1Speed);  // Controla la velocidad del motor 1
        delay(10);
    }
}

// Función de tarea para el motor 2
void motor2Task(void *parameter) {
    while (true) {
        if (motor2Forward) {
            digitalWrite(in3Pin, HIGH);
            digitalWrite(in4Pin, LOW);
        } else {
            digitalWrite(in3Pin, LOW);
            digitalWrite(in4Pin, HIGH);
        }
        ledcWrite(1, motor2Speed);  // Controla la velocidad del motor 2
        delay(10);
    }
}

// Callback cuando se conecta un nuevo mando
void onConnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller conectado, índice=%d\n", i);
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Modelo: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id, properties.product_id);
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

// Procesa el joystick para mover los motores
void processJoystick(ControllerPtr ctl) {
    int yAxis = ctl->axisY();  // Valor del eje Y del joystick

    if (yAxis < -20) {  // Hacia adelante
        int speed = map(abs(yAxis), 0, 128, 0, 255);  // Ajusta la velocidad
        motor1Speed = speed;
        motor2Speed = speed;
        motor1Forward = true;
        motor2Forward = true;
    } else if (yAxis > 20) {  // Hacia atrás
        int speed = map(yAxis, 0, 128, 0, 255);  // Ajusta la velocidad
        motor1Speed = speed;
        motor2Speed = speed;
        motor1Forward = false;
        motor2Forward = false;
    } else {
        // Detiene los motores si el joystick está en posición neutra
        motor1Speed = 0;
        motor2Speed = 0;
    }
}

// Procesa los mandos conectados
void processGamepad(ControllerPtr ctl) {
    if (ctl->isConnected()) {
        processJoystick(ctl);  // Procesa el joystick para mover los motores
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

    // Inicia las tareas en hilos separados para cada motor
    xTaskCreatePinnedToCore(motor1Task, "Motor1 Task", 1000, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(motor2Task, "Motor2 Task", 1000, NULL, 1, NULL, 1);
}

// Bucle principal
void loop() {
    bool dataUpdated = BP32.update();
    if (dataUpdated) {
        processControllers();
    }
    delay(150);
}