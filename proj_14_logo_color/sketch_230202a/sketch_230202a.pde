//including the serial ports external lybrary
import processing.serial.*;
Serial myPort;
//Creating an object for the image
PImage logo;
//Creating a variable to store the background colour
int bgcolor=0;
void setup(){
 //Setting the colour mode. In this case we're useing HSB(HueSaturationBrightness). The hue will change while turning the potentiometer.
 colorMode(HSB,255);
 //loading the image directly form the Internet
 logo=loadImage("http://arduino.cc/logo.png");
 // you can use "size(logo.width,logo.height)" to automatically adjust the scale
 //if you have problems, adjust it manually:
 size(170,120);
 //Printing a list with all the serial ports your computer has when the program first starts.
 println("Available serial ports:");
 printArray(Serial.list());
 //Telling Processing information about the serial connection. The parameters are: which application will be speaking to, which serial port will be communicating(depending on the previous result), and at what speed.
 myPort=new Serial(this,Serial.list()[2],9600);
}
//Analog function to void loop() in Arduino
void draw(){
 //Reading Arduino data from the serial port
 if(myPort.available()>0){
 bgcolor=myPort.read();
 println(bgcolor);
 }
 //changing the image background
 background(bgcolor,255,255);
 //Displaying the image and starting drawing on top left (0.0)
 image(logo,0,0);
}
