#include "HX711.h"

// Conexões do circuito HX711
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;
float lastWeight = 0.0;

void setup() {
  Serial.begin(115200);
  Serial.println("Demonstração HX711");
  Serial.println("Inicializando a balança");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("Balança Iniciada!");

  
  scale.set_scale(0.42);
  //scale.set_scale(-471.497);                      // esse valor é obtido calibrando a balança com pesos conhecidos
  scale.tare();               // redefine a balança para 0


  Serial.println("Leituras:");
}

void loop() {
 

  // Lê o valor da balança
  float weight = scale.get_units(1);
  
  // Verifica se houve uma variação maior que 50g
  if (abs(weight - lastWeight) >= 50.0) {
    Serial.print("Peso Lido:\t");
    Serial.println(weight);
    lastWeight = weight;
  }
  
  delay(1000);

}
