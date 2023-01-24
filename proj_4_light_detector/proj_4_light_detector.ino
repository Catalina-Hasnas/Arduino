  struct Color {
  int LEDPin;
  int sensorPin;
  int sensorValue;
  int value;
  String name;
} green, red, blue; 

Color ColorArr[3];

void setup() {
  green.LEDPin = 9;
  green.sensorPin = A1;
  green.sensorValue = 0;
  green.value = 0;
  green.name = "green";

  red.LEDPin = 11;
  red.sensorPin = A0;
  red.sensorValue = 0;
  red.value = 0;
  red.name = "red";

  blue.LEDPin = 10;
  blue.sensorPin = A2;
  blue.sensorValue = 0;
  blue.value = 0;
  blue.name = "blue";

  ColorArr[0] = green;
  ColorArr[1] = red;
  ColorArr[2] = blue;

  Serial.begin(9600);

  int i;
  for (i = 0; i<3; i++) {
    pinMode(ColorArr[i].LEDPin, OUTPUT);
  };

}

void loop() {
  int i;
  for (i = 0; i<3; i++) {
    ColorArr[i].sensorValue = analogRead(ColorArr[i].sensorPin);
    delay(5);
    ColorArr[i].value = ColorArr[i].sensorValue / 4;
    int opposite = 255 - ColorArr[i].value;
    analogWrite(ColorArr[i].LEDPin, opposite > 250 ? opposite : 0);
  }
  delay(100);
}
