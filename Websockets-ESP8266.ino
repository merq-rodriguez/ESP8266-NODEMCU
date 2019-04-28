
 
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
 
#define LED     05 // D1          
 
const char* ssid = "MOTOR";
const char* password = "1234";
 
static const char PROGMEM INDEX_HTML[] = R"( 
<!DOCTYPE html>
<html>

<head>
    <meta charset=utf-8>
    <title>Control de Robot - Semana de la ciencia</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
        integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
</head>

<body>
    <h1>Control de motores</h1>
    <style>
        .container {
            width: 50%;
            height: 400px;
            border-radius: 10px;
            -webkit-box-shadow: 0px 3px 11px -1px rgba(0, 0, 0, 0.73);
            -moz-box-shadow: 0px 3px 11px -1px rgba(0, 0, 0, 0.73);
            box-shadow: 0px 3px 11px -1px rgba(0, 0, 0, 0.73);
            background-image: url("https://timedotcom.files.wordpress.com/2014/05/digital-blasphemy.jpg");
        }

        .up {
            display: inline-block;
            text-align: center;
        }

        .btn-circle {
            width: 250px;
            height: 250px;
            text-align: center;
            padding: 6px 0;
            font-size: 12px;
            line-height: 1.428571429;
            border-radius: 15px;
        }

        .btn-circle.btn-lg {
            width: 200px;
            height: 200px;
            padding: 10px 16px;
            font-size: 18px;
            line-height: 1.33;
            border-radius: 25px;
        }

        .btn-circle.btn-xl {
            width: 100px;
            height: 100px;
            padding: 10px 16px 10px 16px;
            font-size: 24px;
            line-height: 1.33;
            border-radius: 35px;
        }



        .grid {
            display: grid;
            grid-template-columns: 1fr 1fr;
            grid-template-rows: 2fr 1fr;
        }
    </style>

    <!-- <button type="button" class="btn btn-default btn-circle btn-xl"><i class="glyphicon glyphicon-ok"></i></button>
    <button type="button" class="btn btn-primary btn-circle btn-xl"><i class="glyphicon glyphicon-list"></i></button>
    <button type="button" class="btn btn-success btn-circle btn-xl"><i class="glyphicon glyphicon-link"></i></button>
    <button type="button" class="btn btn-warning btn-circle btn-xl"><i class="glyphicon glyphicon-remove"></i></button>
    <button type="button" class="btn btn-danger btn-circle btn-xl"><i class="glyphicon glyphicon-heart"></i></button>
     -->




    <div class="container">
        <div class="row d-flex justify-content-center">
            <div class="col-1 up">
                <button 
                    type="button" 
                    class="btn btn-info btn-circle btn-xl" 
                    onclick='moveUp()'
                    > Up </button>
            </div>
        </div>

        <div class="row d-flex justify-content-center">
            <div class="col-2 left">
                <button 
                type="button" 
                class="btn btn-info btn-circle btn-xl" 
                onclick='moveLeft()'
                >Left</button>
            </div>

            <div class="col-2 stop">
                <button 
                type="button" 
                class="btn btn-info btn-circle btn-xl" 
                onclick='stop()'
                >Stop</button>
            </div>

            <div class="col-2 rigth">
                <button 
                type="button" 
                class="btn btn-info btn-circle btn-xl"
                onclick='moveRigth()'
                >Rigth</button>
            </div>

        </div>

        <div class="row d-flex justify-content-center">
            <div class="col-1 down">
                <button 
                type="button" 
                class="btn btn-info btn-circle btn-xl"
                onclick='moveDown()'
                >Down</button>
            </div>
        </div>
    </div>


    <p>Comunicación vía WebSocket: Servidor (ESP8266) <---> Cliente</p>
    <input type='range' min='0' max='255' value='127' id='miValor' oninput='verValor()'>
    <p id='valor'></p>

    <script>
        var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

        connection.onopen = function () {
            connection.send('Conectado  -  ' + new Date());
            verValor();
        }
        connection.onmessage = function (event) {
            console.log('Servidor (recibe): ', event.data);
        }
        connection.onerror = function (error) {
            console.log('WebSocket Error!!!', error);
        }
        function verValor() {
           // x = document.getElementById('miValor').value;
          //  document.getElementById('valor').innerHTML = 'Intensidad (0-255): ' + x;
          ///  sendValue();
        }

        function moveUp(){
            sendValue('Arriba');
        }
        function moveLeft(){
            sendValue('Izquierda');
        }
        function moveRigth(){
            sendValue('Derecha');
        }
        function moveDown(){
            sendValue('Atras');
        }
        function stop(){
            sendValue('Parar');
        }

        function sendValue(value) {
            console.log('Cliente (envía): ' + value);
            connection.send(value);
        }
    </script>

</body>

</html>
)";
 
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
 
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Conectado a la URL: %d.%d.%d.%d - %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
 
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectado!\n", num);
      break;
 
    case WStype_TEXT:
      Serial.printf("Número de conexión: %u  -  Carácteres recibidos: %s\n  ", num, payload);
      webSocket.sendTXT(num, payload);      //Devuelve el mensaje recibido al cliente
      String str = (char*)payload;          //Conversión de los carácteres recibidos a cadena de texto
      int intensidad = str.toInt();         //Conversión de la cadena de texto a número
      analogWrite(LED, intensidad);
      break;
  }
}
 
void setup() {
  Serial.begin(115200);
  Serial.println();
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("IP del access point: ");
  Serial.println(myIP);
  
   // Iniciando webSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
 
  // Route index
  server.on("/", []() {
      server.send_P(200, "text/html", INDEX_HTML);
  });
 
  server.begin();
  Serial.println("WebServer iniciado...");
 
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, 0); 
 
  analogWriteRange(255);
}
 
void loop() {
    webSocket.loop();
    server.handleClient();
}