//Sensor modules --> Esp 8266 pins
//Temperature - D4
//moisture - A0
//Sound - D2
//Servo - D1

//Blynk Credentials
#define BLYNK_TEMPLATE_ID "TMPL3B_9jJmse"
#define BLYNK_TEMPLATE_ NAME "SBC"
#define BLYNK_AUTH_TOKEN "ewY0ydhJaC9BT-U04pvX89npNAwXWssR"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SGA007";        // wifi name of device to be connected to.
char pass[] = "Shero2020";  // wifi password of device to be connected to.

#define DHTPIN 2          // D4 pin
#define DHTTYPE DHT11     // DHT 11  
DHT dht(DHTPIN, DHTTYPE); //configuring DHT pins
#define soundSensorPin 4   // D2 pin
#define soilMoisturePin A0 // A0 pin

Servo servo;
int servo_sw = D6; // Dummy pin for Blynk control switch

BlynkTimer timer;  // To update sensed data periodically in Blynk

void sendSensor(){
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  float h = dht.readHumidity();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  int soundDetected = digitalRead(soundSensorPin);
  if (soundDetected == HIGH) {
    Blynk.logEvent("cry_alert","Baby crying Attention needed!");
    //Blynk.email("cry_alert","Baby crying Attention needed!"); // Blynk notification
    Serial.println("Baby Crying !!");
  }

  int soilMoistureValue = analogRead(soilMoisturePin);
  int w = map(soilMoistureValue, 1023, 0, 0, 100); // Convert the analog value to percentage
  
  // Blynk virtual pins
  Blynk.virtualWrite(V5, t); // Temperature
  Blynk.virtualWrite(V7, w); // Wetness

  Serial.println(t);
  // Temperature alert
  if(t > 25){
    Blynk.logEvent("temp_alert","Temp above 25 degree");
    //Blynk.email("temp_alert","Temp above 25 degree"); // Blynk.email
    Serial.println("Temperature above 25 degrees");
  }

  // Wetness alert
  if(w > 30){
   // Blynk.email
    Blynk.logEvent("wetness_alert","wetness above above 30 %");
    //Blynk.email("wetness_alert","wetness above above 30 %");
  }
}

void setup(){
  Serial.begin(115200); //Setting Baud rate

  //Configuring sensor & Servo pins
  pinMode(soundSensorPin, INPUT); 
  pinMode(servo_sw, OUTPUT);
  dht.begin();
  servo.attach(5); // D1
  servo.write(0); // Setting to 0° rotation initially

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(2500L, sendSensor); //Update info every 5 Sec in Blynk
}
 
void loop(){
  int sw = digitalRead(servo_sw);
  
  // When Servo switch is turned on in Blynk, servo turns on
  if(sw == HIGH) {
    servo.write(90*2); delay(500); // Rotates 90°
    servo.write(0*2); delay(500); // Back to 0° 
  }

  Blynk.run();
  timer.run();
}