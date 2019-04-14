/*
      
      WiFi.begin(ssid, password = null, channel = 0, bssid = null, connect = true)

      ssid:       nombre de la red WiFi a la que nos queremos conectar (max 32 char)
      password:   opcional, contraseña (mínimo 8 char y máximo 64)
      channel:    opcional, el canal de WiFi a emplear
      bssid:      opcional, dirección MAC del punto de acceso
      connect:    indica si queremos conectar inmediatamente (si es false, sólo guarda los parámetros)
*/

/*
      WiFi.status(). Esta variable de estado del ESP8266 puede ser:

      WL_CONNECTED:	      Conexión establecida
      WL_NO_SSID_AVAIL:	  El SSID no se encuentra
      WL_CONNECT_FAILED:	Contraseña incorrecta
      WL_IDLE_STATUS:	    Wi-Fi está cambiando entre estados
      WL_DISCONNECTED:	  El ESP8266 no está configurado en modo STA
*/

/*
      WIFI_STA:	Estacion
      WIFI_AP:	Access point
      WIFI_AP_STA:	Station+Acces Point
*/

#include <ESP8266WiFi.h>
 
// Sustituir con datos de la red a la que se va a conectar
const char* ssid     = "La nueva Fraternidad";
const char* password = "estanoesunaclave";
 
void setup(){
  Serial.begin(115200);
  delay(10);
  
  //La función WiFi.mode(WIFI_STA) es opcional en este ejemplo. 
  //Sirve para dejar únicamente el modo STA y desactivar el AP
  WiFi.mode(WIFI_STA);

  //  Guarda los credenciales indicados en la memoria flash no volátil
  //  (que se mantiene incluso aunque carguemos otro programa). Ante un fallo de conexión,
  //  el ESP8266 se conectará automáticamente al último punto de acceso cuando esté disponible.
  WiFi.begin(ssid, password);
  Serial.print("Conectando a:\t");
  Serial.println(ssid); 
 
  // Esperar a que nos conectemos
  while (WiFi.status() != WL_CONNECTED) {
     delay(200);
     Serial.print('.');
  }
 
  // Mostrar mensaje de exito y dirección IP asignada
  Serial.println("Conectado correctamente");
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID()); 
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname:\t");
  Serial.println(WiFi.hostname());
  Serial.print("Subnetmask:\t");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway:\t");
  Serial.println(WiFi.gatewayIP());
  Serial.print("MAC:\t");
  Serial.println(WiFi.macAddress());  
  Serial.print("DNS:\t");
  Serial.println(WiFi.dnsIP());

/*
================================================
    Gestión de la conexión
================================================
    WiFi.reconnect();
    WiFi.disconnect(true);
    WiFi.isConnected();
    WiFi.setAutoConnect(autoConnect);
    WiFi.status();
================================================
*/


//WiFi.dnsIP(dns_no);
  
}
 
void loop() {}
