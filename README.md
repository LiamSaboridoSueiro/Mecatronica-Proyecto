# Mecatronica-Proyecto

¡Bienvenido a nuestro repositorio!

Este proyecto de trata del robot Kantam controlado mediante un dualshock 4 utilizando un ESP32. El robot incluye movimiento direccional en 8 posiciones (adelante, atrás, izquierda, derecha y diagonales) y un puño disparable para repartir justicia.

<div align="center">
  <img src="https://github.com/user-attachments/assets/b60e63ab-5aaf-4f3e-bce4-c088ab06995f" alt="image" width="300"/>
</div>

## Componentes Necesarios

Asegúrate de contar con los siguientes componentes para replicar este proyecto:

- **ESP32**: Microcontrolador principal para controlar los motores y el servo.
- **Microservo**: Utilizado para realizar movimientos específicos controlados por un botón del mando.
- **2 Motores DC amarillos**: Motores principales para el desplazamiento del robot.
- **L298N (de 2 Am mínimo)**: Módulo controlador de motores para manejar los motores DC.
- **Batería de 15V**: Para alimentar los motores y el controlador de motores.
- **Powerbank**: Fuente de energía para el ESP32.
- **Breadboard**: Para realizar las conexiones de los componentes electrónicos.
- **Cables de conexión (jumper wires)**: Para conectar todos los componentes.

### Esquema de Montaje

Para ensamblar el circuito correctamente, sigue el esquema mostrado en la imagen. Esta imagen muestra claramente cómo conectar los componentes, no te olvides de asegurarte de verificar cada conexión para evitar errores en el montaje.

<div align="center">
  <img src="https://github.com/LiamSaboridoSueiro/Mecatronica-Proyecto/blob/main/circuito/circuito_kantam.jpg" alt="circuito" width="800"/>
</div>

### Instrucciones para Imprimir y Montar

1. **Preparación para la Impresión**:
   - En el repositorio del proyecto, encontrarás una carpeta llamada **`stl`** que contiene los archivos 3D en formato `.stl`.
   - Utiliza un software de corte como **Ultimaker Cura**, para imprimir cada archivo por separado.

2. **Montaje del Robot Kantam**:
   - Una vez impresas todas las piezas, utiliza el sentido común para unir las piezas.
   - Asegúrate de fijar correctamente los motores, el servo y otros componentes electrónicos en las ubicaciones indicadas en las piezas impresas.

3. **Montaje de mecanismos**:
    - Sigue este link para montar las dos ruedas del robot en [modular tracks](https://www.thingiverse.com/thing:2804287). Podrás poner los cables de las ruedas por dentro de las piernas. También habrá espacio para una powerbank y la batería.
    - Para montar el brazo quizás tardas un poco más. Hay que pegar un servo dentro de la muñeca e ir pasando los cables cuidadosamente por cada parte del brazo hasta poder meterlo dentro del cuerpo por un agujero que hay en el hombro.



## Requisitos Previos

Antes de empezar, asegúrate de tener instalados y configurados los siguientes elementos:

### 1. **Instalación del entorno de desarrollo**

- Descarga e instala el **Arduino IDE** desde [su sitio oficial](https://www.arduino.cc/en/software).

### 2. **Configuración de Board Managers**

Para configurar el ESP32 y la librería **Bluepad32**, sigue estos pasos:

1. Abre el **Arduino IDE**.
2. Ve a **Archivo > Preferencias**.
3. En el campo **Gestor de URLs Adicionales de Tarjetas**, añade los siguientes enlaces JSON:
   - **ESP32**: 
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - **Bluepad32**:
     ```
     https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
     ```

### 3. **Instalación de Librerías**

Ve a **Herramientas > Administrar bibliotecas...** y busca e instala las siguientes librerías:
- **esp32** de **Espressif Systems**.
- **esp32_bluepad32** de **Ricardo Quesada**.

### 4. **Selección de Placa y Puerto**

- Selecciona la placa correcta desde el menú **Herramientas > Placa**, por ejemplo:
  - **DOIT ESP32 Devkit V1** (o el modelo que estés utilizando).
- Selecciona el puerto COM correspondiente donde está conectada la ESP32.

### 5. **Guía Visual**

En caso de no saber cómo realizar la configuración, puedes seguir este video explicativo:
[Video Tutorial: Configuración de Bluepad32 y ESP32 en Arduino IDE](https://www.youtube.com/watch?v=EEViXFoSzww&t)

### Conexión del DualShock4

Tras subir el código a la placa, puedes conectar un mando **DualShock4** al ESP32 de la siguiente manera:

1. Enciende el mando **DualShock4** y colócalo en modo de sincronización pulsando **Share** y **Home** al mismo tiempo.
2. Cuando el mando esté correctamente sincronizado, aparecerá una luz verde en el mando.
3. Una vez sincronizado:
   - Usa el **joystick izquierdo** para mover el robot en las 8 direcciones.
   - Presiona el botón **X** para activar el servo y disparar.

### Kantam
¡Aquí puedes ver como queda finalmente el robot y un vídeo de su funcionamiento!

<div align="center">
  <img src="https://github.com/user-attachments/assets/d4713fcb-cf35-472e-97c0-7bd320fbd779" alt="image" width="400"/>
</div>

[Ver el video en YouTube](https://www.youtube.com/shorts/YCpUkMmTc64)




