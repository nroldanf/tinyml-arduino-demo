#include <xor_model.h>

const int ledPin = LED_BUILTIN;

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  while (!Serial) {
    // Wait for the serial connection to be ready
  }
  Serial.println("Ingrese valores para a y b como 'a,b' (0 a 255):");
}

void loop() {
  static uint8_t a = 0; // Default values for a and b
  static uint8_t b = 0;

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read input from the serial monitor
    input.trim(); // Remove any trailing whitespace

    // Parse the input
    int commaIndex = input.indexOf(',');
    if (commaIndex > 0) {
      String aString = input.substring(0, commaIndex);
      String bString = input.substring(commaIndex + 1);

      int aValue = aString.toInt();
      int bValue = bString.toInt();

      // Validate the values
      if (aValue >= 0 && aValue <= 255 && bValue >= 0 && bValue <= 255) {
        a = (uint8_t)aValue;
        b = (uint8_t)bValue;
        Serial.print("Valores recibidos: a = ");
        Serial.print(a);
        Serial.print(", b = ");
        Serial.println(b);
      } else {
        Serial.println("Entrada inválida. Por favor ingrese un número entre 0 y 255.");
      }
    } else {
      Serial.println("Formato inválido. Por favor ingrese valores separados por coma: 'a,b'.");
    }
  }

  // Use the parsed values of a and b
  const int16_t features[] = { a, b };

  const int32_t out = xor_model_predict(features, 2);

  if (out == 1) {
    Serial.println("Clase predicha: 1");
  } else {
    Serial.println("Clase predicha: 0");
  }
  delay(1000);
}
