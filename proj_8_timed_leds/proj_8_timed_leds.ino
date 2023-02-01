const int buzzer=8;
unsigned long previousTime=0;
int led=2;
long interval=2000;
int blinkTimes=0;

void setup() {
	for(int x=2;x<8;x++){
		pinMode(x,OUTPUT);
	}
}

void loop() {
	unsigned long currentTime=millis();
	if(currentTime-previousTime>interval){
      previousTime = currentTime;
      digitalWrite(led,HIGH);
      if (led == 8){ 
        for(int x=2;x<8;x++){
          digitalWrite(x, LOW);
        }
        delay(500);
        while(blinkTimes<3){
            for(int x=2;x<8;x++){
            digitalWrite(x,HIGH);
            tone(buzzer, 500, 50);
          } 
          delay(500);
          for(int x=2;x<8;x++){
            digitalWrite(x,LOW);
            tone(buzzer, 500, 50);
          }
          delay(500);
          blinkTimes++;  
        }
        blinkTimes = 0; 
        led = 1;
      } 
    led++;
    tone(buzzer, 500, 50);
  }
}
  

