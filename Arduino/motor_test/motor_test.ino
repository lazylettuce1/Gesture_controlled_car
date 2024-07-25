const int in1=3,in2=4,in3=7,in4=8,enA=5,enB=6;
void setup() {
  // put your setup code here, to run once:
Serial.begin(19200);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
//in2 and 3 +ve, and in1 and 4 -ve
//enA to the right, enB to the left.
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}
