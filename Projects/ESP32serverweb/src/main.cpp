#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid ="APC..";
const char* password ='Tchokoualeu.20';
WebServer server(80);

const int led =2;
bool standled=false;
char text_stand_led [2][10]={"ETEINTE!", "Allumee"};
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n"); 

  pinMode(led,OUTPUT);
  digitalWrite(led, LOW);

  Wifi.begin(ssid, password);
  Serial.print("Tentative de connexion...");

  while(Wifi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.println("\n");
  Serial.println("Connextion etablie!");
  Serial.print("Adress IP:");
  Serial.println(Wifi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("server web");
}

void loop() {
  server.handleClient();
}

void handleRoot(){
		 
String page= "<!DOCTYPE html>";

   page+="<html lang='fr'>";
     page+="<head>";
         page+="<title> Serveur ESP32 </title>";
		  page+="<meta http-equiv 'refresh' content='60' name='viewport' content='width=device-width, intítial-scale=1' charset='UTF-8'/>";
	 page+="</head>";
    page+="<body>";
		   page+="<h1> Serveur TTS </h1>";
		   page+="<p>  ce serveur est heberge sur un SP32 </>";
		   page+="<i> cree par TTS.kmer </i>";
		    page+="<p>  cliquer ici pour vous connecter</>";
	page+="</body>";
		 
page+="</html>";
server.send(200,"text/html", page);
}

void handleNotFound(){
  server.send(404, "test/plain", "404:Not found!");
}

void handleOn(){
standled=true;
digitalWrite(led, HIGH);
server.sendHeader("Location", "/");
server.send(303);
}
void handleOff(){
standled=false;
digitalWrite(led, LOW);
server.sendHeader("Location", "/");
server.send(303);
}