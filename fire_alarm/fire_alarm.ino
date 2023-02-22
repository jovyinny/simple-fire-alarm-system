/*
 * SMOKE AND TEMP RAISE TRIGGER WATER PUMP AND ALARM
 */

#include <SoftwareSerial.h>
#include "DHT.h"

#define TEMP_SENSOR_PIN A3
#define PUMP_PIN 9
#define MQ2 A2
#define BUZZER 2
#define DHTTYPE DHT11

DHT dht(TEMP_SENSOR_PIN, DHTTYPE);

//declaration
void control_pump(float temp, int mq2);

float max_temp = 31;
int gas_limit = 570;
bool motor_run = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(MQ2, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  //  int readData = DHT.read11(TEMP_SENSOR_PIN);
  float temp_reading = dht.readTemperature();             // Read temperature in celcius
  int mq2 = analogRead(MQ2);
  control_pump(temp_reading, mq2);

}

//definition
void control_pump(float temp, int mq2) {
  Serial.print("Temperature readimgs: ");
  Serial.println(temp);
  Serial.print("Gas readimgs: ");
  Serial.println(mq2);

  if (mq2 >= gas_limit) {
    if (temp >= max_temp ) {
      if (motor_run) {
        digitalWrite(PUMP_PIN, HIGH);  //turn on relay module
        Serial.println("pump on ");
        motor_run = false;
      }
      digitalWrite(BUZZER, HIGH);

    }
    else {
      if(motor_run == false){
      digitalWrite(PUMP_PIN, LOW);
      Serial.println("Pump off ");
      motor_run = true;
      }
//      digitalWrite(BUZZER, HI/GH);
      tone(BUZZER,40,2000);
      
      //make buzzing sound only
    }
  }

  else {
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("Pump off");
    digitalWrite(BUZZER, LOW);
    motor_run = true;
  }
  Serial.println();
  delay(1000);
}
