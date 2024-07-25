#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <math.h>

struct DataPacket{
  signed char value1;
  signed char value2;
};
//pins
const int CE = 9;
const int CSN = 10;


//instantiating objects
Adafruit_MPU6050 mpu;

RF24 radio(CE, CSN);
const byte address[6] = "00001";

void setup() {
  //Initializing comm.
  Serial.begin(19200);
  //SPI.begin();
  //nRF related setup calls
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  //pinmodes - do not think this is necessary bu whatever
  pinMode(CE, OUTPUT);
  pinMode(CSN, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  
  //Just code for checking connection of MPU
  while (!mpu.begin()) {
    Serial.println("MPU6050 not connected!!");
    delay(1000);
  }
  Serial.println("MPU6050 connected!!");
}

void loop() {
  sensors_event_t acc, gcc, temp;
  mpu.getEvent(&acc, &gcc, &temp);

  float ax = acc.acceleration.x, ay = acc.acceleration.y, az = acc.acceleration.z;
  float roll, pitch;

  /*Serial.println("Acceleration:");
  Serial.println(ax);
  Serial.println(ay);
  Serial.println(az);
  delay(200);*/

  //obtained acc values, now moving on to angles
  roll = (atan(ay / ((ax * ax) + (az * az))) * 180) / 3.142;
  pitch = (atan(-ax / ((ay * ay) + (az * az))) * 180) / 3.142;
  Serial.println("Angles:");
  // Serial.println(roll);
  // Serial.println(pitch);
  // delay(200);
  //	stage1: sending them through I2C 
	//  stage2: Obtaining angles done
  //now, stage3: manipulating them according to the desired motor movement
//uh somehow convert into bytes
signed char r = (round(roll));
signed char p = (round(pitch));
  // Serial.println("Duty Cycles:");

DataPacket data = {r,p};
  // Serial.println(data.value1);
  // Serial.println(data.value2);
//stage3: done
/*stage4: sending to NRF via SPI
SPI comm. protocol using RF24*/
bool rslt;
rslt = radio.write(&data, sizeof(data));

if(!rslt){
  Serial.println("Transmission failed!");
  digitalWrite(LED_BUILTIN, HIGH);
}
delay(500);
/*radio.write(&r, sizeof(r));
delay(200);
radio.write(&p, sizeof(p));
delay(1000);*/

}

/*void Send_DutyCycles_to_nRF(int address, int value1, int value2){
  //to select the chip
  digitalWrite(CSN, LOW);
  delay(100); 
  // 
  SPI.transfer(address);
  SPI.transfer(value1);
  SPI.transfer(value2);
  delay(100);
  //now de-selecting the chip
  digitalWrite(CSN, HIGH);
}*/


