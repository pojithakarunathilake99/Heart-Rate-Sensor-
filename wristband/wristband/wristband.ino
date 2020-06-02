//Copyrights Pojitha KArunathilake
// visit my website for more projects www.pojithakarunathilake.com / www.pojithakarunathilake.tech
#include <ESP8266WiFi.h>;
 
#include <WiFiClient.h>;
 
#include <ThingSpeak.h>;
 
const char* ssid = "SSID"; //Your Network SSID
 
const char* password = "WIFI PASSWORD"; //Your Network Password
const char* server ="api.thingspeak.com";

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
WiFiClient client;
 
unsigned long myChannelNumber = Your Channel id ; //Your Channel Number (Without Brackets)


const char * myWriteAPIKey = "YourAPIKEY";
void setup() {
  // put your setup code here, to run once:
 pinMode(INPUT,A0);

 Serial.begin(115200);
  Serial.println("Initializing...");
 
 Serial.println("Wi-Fi...");
    WiFi.begin(ssid, password);
    Serial.println("Connecting...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println(".");
        delay(500);
    }
    Serial.println();
    Serial.println("Connected to: ");
    Serial.println(WiFi.localIP());
 
ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
int Signal = analogRead(A0); 
if (Signal <600){
  long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta *17  / 1000.0);
     if (beatsPerMinute < 220 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
     int x = (beatAvg)  ;
 
     if(x>=60){
       ThingSpeak.writeField(myChannelNumber, 4,x, myWriteAPIKey); 
     }
    else
    {
      int i = x+40 ;
      ThingSpeak.writeField(myChannelNumber, 4,i, myWriteAPIKey);
    }
    }
//Update in ThingSpea
    
  //Serial.print("IR=");

      Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
  Serial.println();
    
}
}
