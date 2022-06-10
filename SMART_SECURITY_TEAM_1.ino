#include <AntaresESP8266HTTP.h>
#include <ESP8266WiFi.h>

#define ACCESSKEY "6388160f97f65e86:814c491f9d66078b"
#define WIFISSID "awl"
#define PASSWORD "awl12345"

#define projectName "smart_security"
#define deviceName "tombol_led"


AntaresESP8266HTTP antares(ACCESSKEY);
int buzzer = 4;       
float SENSOR_OUTPUT_PIN = 5;
int pirStatus = LOW;
String data= "Tidak ada pergerakan";


void setup() {
  
  pinMode(SENSOR_OUTPUT_PIN, INPUT);  

  pinMode(buzzer, OUTPUT);           

  Serial.begin(9600);
  delay(1000);

  antares.setDebug(false);
  antares.wifiConnection(WIFISSID, PASSWORD);

  Serial.print("Connecting to : ");
  Serial.println(WIFISSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFISSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
}
  //antares.setDebug(true);
  //antares.wifiConnection(WIFISSID, PASSWORD);
  //antares.setMqttServer();

  void loop() {
  //Ini buat kodingan kita
  int hasil = digitalRead(SENSOR_OUTPUT_PIN);
  if (hasil == HIGH) //buzzer on
  {
    Serial.println("Pergerakan Terdeteksi");
    digitalWrite(buzzer, HIGH);
    data="ada maling";
  }
  else//buzzer off
  {
    Serial.println ("Tidak Ada Pergerakan");
    digitalWrite (buzzer, LOW);
    data ="aman";
  }
  
  antares.add("Ada_Pergerakan", data);
  antares.send(projectName, deviceName);
  delay(1000);
}
