/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


char auth[] = "zcyfzOhhh-C6bIrE9SKCGXI_A4xKX-VR";


char ssid[] = "khanh"; 
char pass[] = "vuminhkhanh";   

#define DHTPIN D7
#define DHTTYPE DHT11
#define LEDPIN D2
#define DETECT D6        
#define BLYNK D5

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V6, h);
  Serial.print("Humidity: ");
  Serial.println(h);
  Blynk.virtualWrite(V5, t);
  Serial.print("Temperature: ");
  Serial.println(t);
}


void setup()
{
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  if(digitalRead(DETECT)==LOW&digitalRead(BLYNK)==HIGH)
  {
       digitalWrite(LEDPIN, HIGH);
       Serial.println("Nobody.");
  }
  else if (digitalRead(DETECT)==HIGH||digitalRead(BLYNK)==HIGH)
  {
    if(digitalRead(DETECT)==HIGH)
    {
      Serial.println("Somebody is here.");
    }
    digitalWrite(LEDPIN, HIGH);
  }
  else 
  {
       digitalWrite(LEDPIN, LOW);
       Serial.println("Nobody.");

  }
   delay(1000);
}
