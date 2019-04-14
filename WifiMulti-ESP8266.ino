#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
 
ESP8266WiFiMulti wifiMulti;
 
void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("JULIAN MATEO", "estonodainternet");
  wifiMulti.addAP("La nueva Fraternidad", "estanoesunaclave");
 
  Serial.println("Conectando");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(250);
    Serial.print('.');
  }
 
  // Mostrar mensaje de exito, WiFI conectada y dirección IP asignada
  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}
 
void loop() 
{
}