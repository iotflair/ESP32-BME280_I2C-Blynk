#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "driver/ESP32_BME280_I2C.h"

const uint8_t SCL_bme280 = 27;
const uint8_t SDA_bme280 = 26; //SDA

ESP32_BME280_I2C bme280i2c(0x76, SCL_bme280, SDA_bme280, 100000); //address, SCK, SDA, frequency
char temp_c[10], hum_c[10], pres_c[10];

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "AUTH";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASS";
byte temperature;
byte humidity;
uint16_t pressure;

void bme_get(void);

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  bme_get();
  Blynk.virtualWrite(V10, pressure);
  Blynk.virtualWrite(V11, temperature);
  Blynk.virtualWrite(V12, humidity);
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

   uint8_t t_sb = 5; //stanby 1000ms
   uint8_t filter = 0; //filter O = off
   uint8_t osrs_t = 4; //OverSampling Temperature x4
   uint8_t osrs_p = 4; //OverSampling Pressure x4
   uint8_t osrs_h = 4; //OverSampling Humidity x4
   uint8_t Mode = 3; //Normal mode
    
  bme280i2c.ESP32_BME280_I2C_Init(t_sb, filter, osrs_t, osrs_p, osrs_h, Mode);
  delay(1000);

  // Setup a function to be called every second
  timer.setInterval(60000L, myTimerEvent);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
      WiFi.reconnect();
      //Serial.print("Reconnecting....");
      delay(5000);
  }
   
  Blynk.run();
  timer.run(); // Initiates BlynkTimer 
}

//************************* BME280  ******************************//
void bme_get(){ 
  temperature = (byte)round(bme280i2c.Read_Temperature());
  humidity = (byte)round(bme280i2c.Read_Humidity());
  pressure = (uint16_t)round(bme280i2c.Read_Pressure());

  //char temp_c[10], hum_c[10], pres_c[10];
  sprintf(temp_c, "%2d ℃", temperature);
  sprintf(hum_c, "%2d ％", humidity);
  sprintf(pres_c, "%4d hPa", pressure);

  Serial.println("-----------------------");
  Serial.print("Temperature = "); Serial.println(temp_c);
  Serial.print("Humidity = "); Serial.println(hum_c);
  Serial.print("Pressure = "); Serial.println(pres_c);
  Serial.println("-----------------------");
  Serial.flush();
}
//***************************************************************//

