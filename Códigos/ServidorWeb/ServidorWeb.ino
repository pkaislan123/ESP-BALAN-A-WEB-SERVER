#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

// Informações da rede Wi-Fi
const char* ssid = "Sua rede wifi";
const char* password = "Senha da rede wifi";

// Configuração do servidor web
ESP8266WebServer server(80);

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

  server.on("/", sendHtml);



  server.begin();
  Serial.println("Servidor web iniciado.");



}

void loop() {
  server.handleClient();

  delay(10);

}
