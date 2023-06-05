/*macro definitions of PIR motion sensor pin and LED pin*/
#define PIR_MOTION_SENSOR 2//Use pin 2 to receive the signal from the module
#define Buzzer 6


#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN 3     // what pin we're connected to（DHT10 and DHT20 don't need define it）
DHT dht(DHTPIN, DHTTYPE);   //   DHT11 DHT21 DHT22
#if defined(ARDUINO_ARCH_AVR)
    #define debug  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
    #define debug  SerialUSB
#else
    #define debug  Serial
#endif


#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);

  // Print a message to the LCD.
  lcd.print("WARNING!");
  delay(1000);

    pinMode(PIR_MOTION_SENSOR, INPUT);
    pinMode(Buzzer, OUTPUT);

    Wire.begin();
    dht.begin();

    Serial.begin(9600);  

}

void loop()
{
  lcd.setRGB(0,0,255);
  float Humidity = dht.readHumidity();          // 湿度の読み取り
  float Temperature = dht.readTemperature();    // 温度の読み取り(摂氏)
  
  String hum = String(Humidity);
  String temp = String(Temperature);

  if (isnan(Humidity) || isnan(Temperature)) {  // 読み取りのチェック
    hum="ERROR";
    temp="ERROR";
  }

    if(digitalRead(PIR_MOTION_SENSOR)){
        // digitalWrite(6, HIGH);
        // delay(100);
        // digitalWrite(6, LOW);

        lcd.setRGB(255, 0, 0);
        Serial.println("people is coming," + hum + "%,"+ temp+"℃");
        delay(2000);
        lcd.setRGB(0,0,255);
      
        delay(10000);
    }
}