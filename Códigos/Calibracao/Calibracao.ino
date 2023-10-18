#include "HX711.h"

// Conexões do circuito HX711
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

void setup() {
  Serial.begin(115200);
  //rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    scale.set_scale();
    Serial.println("Zerando a escala... remova qualquer peso da balança.");
    delay(5000);
    scale.tare();
    Serial.println("Zeragem concluída...");
    Serial.print("Coloque um peso conhecido na balança...");
    delay(5000);
    long reading = scale.get_units(10);
    Serial.print("Resultado: ");
    Serial.println(reading);
  }
  else {
    Serial.println("HX711 não encontrado.");
  }
  delay(1000);
}

// O fator de calibração será (leitura)/(peso conhecido)
