/*
   Arduino Code: MQ135 (A0) + DHT11 (A3) on I2C LCD
   New Layout: Line 1 = AQ Value + Temp | Line 2 = Humidity + Status
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>          

// LCD Initialization
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Sensor Pin Definitions
const int mqPin = A0;
#define DHTPIN A3         
#define DHTTYPE DHT11     

// Initialize DHT Sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables
int airQualityValue = 0;
float humidity = 0.0;
float temperatureC = 0.0;
String statusText = "";

void setup()
{
  lcd.init();
  lcd.backlight();
  
  // Start the DHT sensor
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Sensor System OK");
  delay(1500);
  lcd.clear();
}

void loop()
{
  // --- 1. Read Sensors ---
  
  // Read DHT11 data
  humidity = dht.readHumidity();
  temperatureC = dht.readTemperature();

  // Check if DHT readings were successful
  if (isnan(humidity) || isnan(temperatureC)) {
    lcd.setCursor(0, 0);
    lcd.print("DHT Error");
    lcd.setCursor(0, 1);
    lcd.print("Check Wiring");
    delay(2000);
    return; 
  }

  // Read MQ135 data
  airQualityValue = analogRead(mqPin);


  // --- 2. Determine AQ Status ---
  
  if (airQualityValue < 200) {
    statusText = "GOOD    "; 
  } 
  else if (airQualityValue < 400) {
    statusText = "MODERATE";
  } 
  else {
    statusText = "DANGER  ";
  }
  
  // --- 3. Display on LCD ---
  
  // LINE 1: Air Quality Value and Temperature
  lcd.setCursor(0, 0);
  lcd.print("AQI:"); 
  lcd.print(airQualityValue);
  lcd.print(" "); // Add space for separation
  
  lcd.setCursor(8, 0); // Start Temperature from position 8
  lcd.print("T:");
  lcd.print((int)temperatureC); 
  lcd.print("C  "); // Trailing spaces to clear previous chars

  // LINE 2: Humidity and Air Quality Status
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print((int)humidity); 
  lcd.print("% "); // Print humidity value
  
  // Start Status from position 8
  lcd.setCursor(8, 1);
  lcd.print("AQ:");
  lcd.print(statusText); // Print AQ Status text

  delay(1500); // Wait 1.5 seconds before updating
}
