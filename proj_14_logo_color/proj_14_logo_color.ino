int sensorValue;

void setup() {
  // starting serial communication. Make sure Processing and Arduino have the same serial baud rate.
 Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(A0);
  // Sending to the serial connection the analug inputs introcued by the potentiometer.
  // As only is possible to send values from 0 to 255, devide de AnalogRead value by 4.
  Serial.write(sensorValue / 4);
  // After sending the byte, let the ADC stabilize.
 delay(100);
}