const int switchPin=8;
const int motorPin=7;
int switchState=0;

void setup() {
  pinMode(switchPin,INPUT);
  pinMode(motorPin,OUTPUT);
}

void loop() {
  switchState=digitalRead(switchPin);
  if(switchState==HIGH){
    digitalWrite(motorPin,HIGH);
  }
  else{
    digitalWrite(motorPin,LOW);    
  }
}