int notes[]={262,329,392,440};

void setup()
{
  Serial.begin(9600);
}

void loop() {
  int PushedKeyValue=analogRead(A0);
  Serial.println(PushedKeyValue);
  if (PushedKeyValue==1023){
    tone(8,notes[0]);
 
    }
  else if (PushedKeyValue >=990 && PushedKeyValue<=1010){
    tone(8,notes[1]);
 
  }
  else if (PushedKeyValue >=505 && PushedKeyValue<=515){
    tone(8,notes[2]);
    
  }
  else if (PushedKeyValue >=5 && PushedKeyValue<=10){
    tone(8,notes[3]);
    
  }
  else{
    noTone(8);
  }
}