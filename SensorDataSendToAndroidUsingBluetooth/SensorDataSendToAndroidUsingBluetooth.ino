#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>
 
SoftwareSerial blue(2,3); // bluetooth module connected here (Rx,Tx) 
 
void setup(){ 
   Serial.begin(9600); 
   dht.begin();
   blue.begin(9600); 
} 
void loop(){ 
  delay(1000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h, true);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  /*Send to Bluetooth*/
  blue.print("Humidity: ");
  blue.print(h);
  blue.println(" %");
  
  blue.print("Temperature: "); 
  blue.print(t);
  blue.print(" °C ");
  blue.print(f);
  blue.println(" °F"); 
  
  blue.print("Heat index: ");
  blue.print(hic); 
  blue.print(" °C ");
  blue.print(hif);
  blue.println(" °F");
  blue.println("________________");
}
