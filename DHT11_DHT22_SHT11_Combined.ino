// SHT11
#include <SHT1x.h>
#define dataPin  12
#define clockPin 14
SHT1x sht1x(dataPin, clockPin);

// DHT22
#include "DHT.h"
#define DHTPIN 5     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//DHT dht(DHTPIN, DHTTYPE);
DHT dht22(5, DHT22);

// DHT11
DHT dht11(4, DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Open serial connection to report values to host
  dht22.begin();
  dht11.begin();
  Serial.println("Starting up");
}

void loop() {

  // SHT11
  float temp_c;
  float temp_f;
  float humidity;

  // Read values from the sensor
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();

  // Print the values to the serial port
  Serial.print("SHT11 >> Temperature: ");
  // Serial.print(temp_c, DEC);
  Serial.print(temp_c);
  Serial.print(" degC / ");
  Serial.print(temp_f);
  Serial.print(" degF. Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // DHT22
  float h22 = dht22.readHumidity();
  // Read temperature as Celsius (the default)
  float t22 = dht22.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f22 = dht22.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h22) || isnan(t22) || isnan(f22)) {
    Serial.println("Failed to read from DHT22 sensor!");
  } else {

    // Compute heat index in Fahrenheit (the default)
    float hif22 = dht22.computeHeatIndex(f22, h22);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic22 = dht22.computeHeatIndex(t22, h22, false);

    Serial.print("DTH22 >> Temperature: ");
    Serial.print(t22);
    Serial.print(" degC / ");
    Serial.print(f22);
    Serial.print(" degF. Humidity: ");
    Serial.print(h22);
    Serial.print("%");

    Serial.print(" Heat index: ");
    Serial.print(hic22);
    Serial.print(" *C ");
    Serial.print(hif22);
    Serial.println(" *F");
  }

  // DHT11
  float h11 = dht11.readHumidity();
  // Read temperature as Celsius (the default)
  float t11 = dht11.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f11 = dht11.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h11) || isnan(t11) || isnan(f11)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    // Compute heat index in Fahrenheit (the default)
    float hif11 = dht11.computeHeatIndex(f11, h11);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic11 = dht11.computeHeatIndex(t11, h11, false);

    Serial.print("DTH11 >> Temperature: ");
    Serial.print(t11);
    Serial.print(" degC / ");
    Serial.print(f11);
    Serial.print(" degF. Humidity: ");
    Serial.print(h11);
    Serial.print("%");

    Serial.print(" Heat index: ");
    Serial.print(hic11);
    Serial.print(" *C ");
    Serial.print(hif11);
    Serial.println(" *F");
  }
  
  Serial.println("");
  delay(3000);
}
