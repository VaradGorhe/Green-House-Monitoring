  #include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

#include<dht.h>// DHT11 humidity sensor library
dht DHT; //Creating sensor object
#define DHT11_PIN 3 // Sensor is connected to Arduino pin 3
#define Fan 8
#define Spray 7
const int sensor_pin = A1;  /* Soil moisture sensor O/P pin */

const int ledPin = 9;
const int ldrPin = A0;

void setup() 
{
Serial.begin(9600);
pinMode(ldrPin, INPUT);
pinMode(Fan,OUTPUT);
pinMode(Spray,OUTPUT); 
lcd.init();
lcd.begin(16,2);
lcd.backlight();
lcd.cursor();
lcd.blink();
lcd.setCursor(3,0);
lcd.print("Greenhouse");
lcd.setCursor(5,1);
lcd.print("System");
delay(3000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("RIYA DESHPANDE");
//delay(3000);
lcd.setCursor(0,1);
lcd.print("SHUBHANKAR HIRE");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("VARAD GORHE");
//delay(3000);
lcd.setCursor(0,1);
lcd.print("RENUKA GHATGE");
delay(3000);
lcd.clear();



}

void loop() 
{
  delay(10000);
float moisture_percentage;
int sensor_analog;
sensor_analog = analogRead(sensor_pin);
moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
int ldrStatus = analogRead(ldrPin);
int chk = DHT.read11(DHT11_PIN); //Reading data from sensor
if (ldrStatus <= 300) 
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Dark Condition");
lcd.setCursor(0,1);
lcd.print("LED ON");
delay(1000);
digitalWrite(ledPin, HIGH);
Serial.println("Its DARK, Turn on the LED : ");
Serial.println(ldrStatus);
} 
else
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Bright Condition");
lcd.setCursor(0,1);
lcd.print("LED OFF");
delay(1000);
digitalWrite(ledPin, LOW);
Serial.println("Its BRIGHT, Turn off the LED : ");
Serial.println(ldrStatus);
}
delay(2000);
if(DHT.temperature>=24)
{
  Serial.print(DHT.temperature, 1);//prints obtained temperature on serial port
  Serial.println("degree Celsius");
  Serial.print(" Humidity = ");//prints on the serial monitor
  Serial.print(DHT.humidity);// prints obtained humidity on serial port
  Serial.print(" g/m^3");
  digitalWrite(Fan,HIGH);
  delay(1000);//ANALOG OR DIGITAL CONFIRM
  lcd.clear();
  lcd.setCursor(0,0);
  //delay(1000);
  lcd.print("Temp=");
  //delay(1000);
  lcd.print(DHT.temperature);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Humidity=");
  lcd.print(DHT.humidity);
  delay(1000);
  lcd.clear();
  lcd.print("FAN ON");
  delay(1000);
}

else
{
  lcd.clear();
  lcd.print("Temp=");
  //delay(1000);
  lcd.print(DHT.temperature);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Humidity=");
  lcd.print(DHT.humidity);
  delay(1000);
  lcd.clear();
  lcd.print("FAN OFF");
  delay(1000);
  Serial.print(DHT.temperature, 1);//prints obtained temperature on serial port
  Serial.println("Degree Celsius");
  Serial.print(" Humidity = ");//prints on the serial monitor
  Serial.print(DHT.humidity);// prints obtained humidity on serial port
  Serial.print(" g/m^3");
  digitalWrite(Fan,LOW); //ANALOG OR DIGITAL CONFIRM
  
}
delay(2000);
if(moisture_percentage<=80)
{
  lcd.clear();
  lcd.print("Moisture=");
  lcd.print(moisture_percentage);
  lcd.setCursor(0,1);
  //delay(1000);
  lcd.print("Spray ON");
  delay(1000);
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  digitalWrite(Spray, HIGH); //CONFIRM AGAIN DIGITAL OR ANALOG
  
}
else
{
  lcd.clear();
  lcd.print("Moisture=");
  lcd.print(moisture_percentage);
  lcd.setCursor(0,1);
  delay(1000);
  lcd.print("Spray OFF");
  delay(1000);
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  digitalWrite(Spray, LOW); //CONFIRM AGAIN DIGITAL OR ANALOG
}

}
