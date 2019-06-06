#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// BT
SoftwareSerial mySerial(11, 10); // TX/RX pins

// LED
#define LED_PIN 2
String statLed = "OFF";
bool ledOn = 0;

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  mySerial.begin(9600);
  // init done

  pinMode(LED_PIN, OUTPUT);
}


void loop() {

  // BT
  String msg = getMessage();
  if(msg!=""){
    Serial.println(msg);
    if(msg=="on")
    {
      statLed = "ON";
      ledOn = 1;
    }

    if(msg=="off")
    {
      statLed = "OFF";
      ledOn = 0;
    }
  }

  // LED
  digitalWrite(LED_PIN, ledOn);   // turn the LED on (HIGH is the voltage level)

  // LCD
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("BT CONTROL LED + LCD\n");
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("LED : ");
  display.println(statLed);
  display.display();
  display.clearDisplay();

}

String getMessage(){
  String msg = "";
  char a;
  
  while(mySerial.available()) {
      a = mySerial.read();
      msg+=String(a);
  }
  return msg;
}

