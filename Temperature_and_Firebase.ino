#include <common.h>
#include <Firebase.h>
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <Utils.h>

// Bibliothek
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

// DHT Sensor variable deklaration
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// FIrebae und WLAN Verbindung Parameter
#define FIREBASE_HOST "https://dht11with-esp8266-40f3e-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "ER39ie5m4Qlv15d2VK6nO4mFfwHbMaKPWwU02PNM"
#define WIFI_SSID "AndroidAPCEC7" 
#define WIFI_PASSWORD "Tchokoualeu.20"   

// Objekte FirebaseESP8266 deklaration
FirebaseData firebaseData;

void setup() {
  
  Serial.begin(115200);
  
  dht.begin();
  
  // WLAN Verbindung 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
  
  // Sensor DHT11 Temperatur und Luftfeuchtigkeit ablesen
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Überprüfen Sie, ob der Sensor DHT11 die Temperatur und Luftfeuchtigkeit lesen kann
  if (isnan(t) || isnan(h)) {
    Serial.println("GaFehler beim Lesen des DHT11 Sensors");
    return;
  }

  // Temperatur und Luftfeuchtigkeit auf seriellem Monitor anzeigen 
  Serial.print("Temperatur: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println();

  // Die Temperatur- und Feuchtigkeitsstatus wir der Firebase zur Verfügung gestellt
  if (Firebase.setFloat(firebaseData, "/Ergebnis_Anzeigen/Temperatur", t)){
      Serial.println("Temperatur gesendet ");
    } else{
      Serial.println("Temperatur nicht gesendet");
      Serial.println("weil,: " + firebaseData.errorReason());
    } 
    
  if (Firebase.setFloat(firebaseData, "/Ergebnis_Anzeigen/Luftfeuchtigkeit", h)){
      Serial.println("Luftfeuchtigkeit gesendet");
      Serial.println();
    } else{
      Serial.println("Luftfeuchtigkeit nicht gesendet");
      Serial.println("weil: " + firebaseData.errorReason());
    }
    
  delay(1000);
}
