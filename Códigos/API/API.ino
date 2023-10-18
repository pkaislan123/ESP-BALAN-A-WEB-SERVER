#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include "HX711.h"
#include <ArduinoJson.h>


// Informações da rede Wi-Fi
const char* ssid = "Aislan";
const char* password = "14111995";

// Conexões do circuito HX711
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;
float lastWeight = 0.0;

// Configuração do servidor web
ESP8266WebServer server(80);


void handlePeso() {
  DynamicJsonDocument jsonDoc(128);
  jsonDoc["pesoAtual"] = lastWeight;
  String jsonResponse;
  serializeJson(jsonDoc, jsonResponse);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", jsonResponse);
}


void sendHtml() {
  String response = R"(
    <!DOCTYPE html><html>
      <head>
        <title>Sistema de Pesagem Dinamica</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          html { font-family: sans-serif; text-align: center; }
          body { display: inline-flex; flex-direction: column; }
          h1 { margin-bottom: 1.2em; } 
          h2 { margin: 0; }
          div { display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
          .btn { background-color: #5B5; border: none; color: #fff; padding: 0.5em 1em;
                 font-size: 2em; text-decoration: none }
          .btn.OFF { background-color: #333; }
        </style>
        
      </head>
            
      <body>      
      </body>
    </html>
  )";

  server.send(200, "text/html", response);
}


void setup() {


  Serial.begin(115200);
  Serial.println("Inicializando a balança");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(0.42);
  scale.tare();

  Serial.println("Balança Inicializada");


  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wifi ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado à rede Wi-Fi!");

  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.on("/peso", HTTP_GET, handlePeso);
  server.on("/", sendHtml);



  server.begin();
  Serial.println("Servidor web iniciado.");



}

void loop() {
  server.handleClient();


  // Lê o valor da balança
  float weight = scale.get_units(1);

  // Verifica se houve uma variação maior que 50g
  if (abs(weight - lastWeight) >= 50.0) {
    Serial.print("Peso Lido:\t");
    Serial.println(weight);


    lastWeight = weight;


  }

  delay(50);
}
