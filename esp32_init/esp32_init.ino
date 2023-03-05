#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int lcdColumns = 16;
int lcdRows = 2;

#define I2C_SDA 23
#define I2C_SCL 19

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    Wire.begin(I2C_SDA, I2C_SCL, 100000);
    // initialize LCD
    lcd.init();
    // turn on LCD backlight                      
    lcd.backlight();

    WiFi.begin(ssid, password);


    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
 lcd.setCursor(0, 0);
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");



            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(5, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(5, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}



// // set the LCD number of columns and rows


// // set LCD address, number of columns and rows
// // if you don't know your display address, run an I2C scanner sketch

// void setup(){
//   Wire.begin(I2C_SDA, I2C_SCL, 100000);
//   // initialize LCD
//   lcd.init();
//   // turn on LCD backlight                      
//   lcd.backlight();
// }

// void loop(){
//   // set cursor to first column, first row
//   lcd.setCursor(0, 0);
//   // print message
//   lcd.print("Hello, World!");
//   delay(1000);
//   // clears the display to print new message
//   lcd.clear();
//   // set cursor to first column, second row
//   lcd.setCursor(0,1);
//   lcd.print("Hello, World!");
//   delay(1000);
//   lcd.clear(); 
// }