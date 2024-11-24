# TinyML

## Detección de palabra clave

### Entrenar el modelo

Corra el notebook `ProyectoFinalGrupo7.ipnb` en colab.

### ¿Cómo actualizar el modelo?

Para usar el nuevo modelo que va a ser desplegado en el arduino, necesitamos hacer 3 cosas:
1. En [micro_features_tiny_conv_micro_features_model_data.cpp](tensorflow_lite/examples/micro_speech/micro_features_tiny_conv_micro_features_model_data.cpp), reemplace el modelo original con el nuevo modelo. Esto es, reemplace el arreglo `g_tiny_conv_micro_features_model_data` con el que fue generado a partir de la conversión `tiny_conv.cc`.
2. Actualice los nombres de las etiquetas en [micro_features_micro_model_settings.cpp](tensorflow_lite/examples/micro_speech/micro_features_micro_model_settings.cpp) con las nuevas etiquetas las cuales se definieron usando la variable de entorno `WANTED_WORDS`.
3. Actualice el archivo [command_responder.cc](tensorflow_lite/examples/micro_speech/arduino_command_responder.cpp) para realizar las acciones deseadas basadas en el comando de voz detectado.

### Despliegue en Arduino


Cree el zip file para que sea compatible con Arduino:

```bash
# Detección de "yes,no"
zip -r yesno.zip lite_rt_yes_no/
# Detección de "left,right"
zip -r leftright.zip lite_rt_left_right/
```

Incluya la libreria en Arduino:

![](assets/arduino_install1.png)


Haga click en el ejemplo `micro_speech` para abrirlo con el Arduino IDE:

![](assets/arduino_install2.png)

Seleccione la tarjeta a utilizar. En este caso, Arduino Nano BLE:

![](assets/arduino_install3.png)

Haga click en `upload` en la parte superior izquierda del IDE para compilar y subir el ejemplo a la tarjeta:

![](assets/arduino_install4.png)


### Estructura del código

- `arduino_audio_provider.cpp`
- `feature_provider.cpp`
- `micro_speech.ino`
- `recognize_commands.cpp`

## Predicción XOR

### Requrimientos

- Arduino IDE
- conda

### Configuración inicial

Cree y active el ambiente virtual de conda:
```bash
conda env create -f conda.yaml -y && conda activate tinyml-arduino
```

Usando el ambiente virtual, instale emlearn como librería de Arduino:
```bash
python -m emlearn.arduino.install
```

Luego de esto, debería ser capaz de encontrar una carpeta llamada `emlearn` dentro de la carpeta de librerías de Arduino desde Arduino IDE:

### Entrenar el modelo

Corra el entrenamiento del modelo:
```bash
python emlearn/xor_train.py
```

### Despligue en Arduino

Copie los contenidos del xor_predict.ino en un nuevo sketch y guardelos en una carpeta.

![](assets/create_folder.png)

Copie el archivo xor_model.h generado dentro de la misma carpeta donde guardo el sketch.

Haga click en `upload` en la parte superior izquierda del IDE para compilar y subir el ejemplo a la tarjeta:

![](assets/arduino_install4.png)
