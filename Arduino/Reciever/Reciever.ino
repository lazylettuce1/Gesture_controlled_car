#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//structure for receiving data
struct DataPacket{
  signed char value1;
  signed char value2;
};
//pins
const int CE = 9;
const int CSN = 10;


//instantiating objects
RF24 radio(CE, CSN);
const byte address[6] = "00001";


const int in1=3,in2=4,in3=7,in4=8,enA=5,enB=6;
void setup() {
Serial.begin(19200);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(LED_BUILTIN,OUTPUT);
//in2 and 3 +ve, and in1 and 4 -ve
//enA to the right, enB to the left.
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  //pinmodes - do not think this is necessary bu whatever
pinMode(CE, OUTPUT);
pinMode(CSN, OUTPUT);

  //nRF related setup calls
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
DataPacket data;
//signed char r, p;
if(radio.available()>0){
  Serial.println("Radio connected!");
  radio.read(&data, sizeof(data));
  // Serial.println(data.value1);
  // Serial.println(data.value2);
  delay(500);
}else{
  Serial.println("Error! Radio not connected!");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}
int pitch = -(data.value1);
int roll = -(data.value2);
//exchanged roll and pitch
// Serial.println("Data Recieved:");
// Serial.println(roll);
// Serial.println(pitch);

//movement conditions
//if(pitch>3 || pitch<(-3)){
//front
  if(pitch>0){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);

  analogWrite(enA, (pitch*4));
  analogWrite(enB, (pitch*4));

  }else if(pitch<0){ //back
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
  analogWrite(enA, (-(pitch*4)));
  analogWrite(enB, (-(pitch*4)));
  }
if(roll>1 || roll<(-1)){
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
  if(roll>0){ //right
    analogWrite(enA, (roll*3));
    analogWrite(enB, 0);
  }else if(roll<0){ //left
    analogWrite(enB, (roll*3));
    analogWrite(enA, 0);
  }
}


}

