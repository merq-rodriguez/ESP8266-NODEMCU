
/*
    Modos de funcionamiento

    WIFI_OFF:	    Apagado
    WIFI_STA:	    Estacion
    WIFI_AP:	    Access point
    WIFI_AP_STA:	Station+Acces Point
*/

/*
    OTRAS FUNCIONES AP DEL ESP8266

    configurar el WiFi generado
    bool WiFi.softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
    
    desconectar el AP
    bool WiFi.softAPdisconnect(bool wifioff = false);

    devuelve la direccion IP del ESP8266
    IPAddress WiFi.softAPIP()
    
    devuelven la direccion MAC del ESP8266
    String WiFi.softAPmacAddress(void);
    uint8_t* WiFi.softAPmacAddress(uint8_t* mac);
*/
#include <ESP8266WiFi.h>        
 
// Configuración de la WiFi generada
const char *ssid = "ESP8266";
const char *password = "1234";
 
void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid, password)){
   Serial.println(".");
    delay(100);
  }
  
  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
  
}
 
void loop() { }