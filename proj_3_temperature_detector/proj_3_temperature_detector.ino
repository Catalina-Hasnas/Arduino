const int sensorPin = A0;
const float baselineTemp = 19.0;

void setup() {
  Serial.begin(9600);
  for (int pinNumber = 3; pinNumber <7; pinNumber ++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }

}

void loop() {
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal/1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;

  Serial.print("\n Sensor Value: ");
  Serial.print(sensorVal);
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print(", degrees C: ");
  Serial.print(temperature);

  if(temperature < baselineTemp+2) {
    for (int pinNumber = 3; pinNumber <7; pinNumber ++) {
    digitalWrite(pinNumber, LOW);
  	}
  } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6) {
	  digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  } else if (temperature >= baselineTemp+6) {
    for (int pinNumber = 3; pinNumber <7; pinNumber ++) {
    digitalWrite(pinNumber, HIGH);
  	}
  }
  delay(500);
}
