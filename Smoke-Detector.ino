// Program/Source Code: Smoke_Detector using Arduino//
#include <MQ2.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define B1     3 //14 //D5
#define B2    4 //12 //D6
#define B3   5  //13 //D7
#define BUZZ  2 //2 //D4 
#define LED   13 //0 //D3
//change this with the pin that you use
int pin = A0;
int dly1;
float lpg, co, smoke;
long ppm,ppm1,dly,beep;
bool mode,alarm,st;
MQ2 mq2(pin);

void setup(){
  Serial.begin(115200);
  pinMode(B1,INPUT_PULLUP);
  pinMode(B2,INPUT_PULLUP);
  pinMode(B3,INPUT_PULLUP);
  pinMode(BUZZ,OUTPUT);
  pinMode(LED,OUTPUT);
  // calibrate the device
  mq2.begin();

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  alarm=1;
}

void loop(){
  dly++;
   dly1++;
if(!digitalRead(B1)&digitalRead(B2)){
  mode=0;
  }
if(digitalRead(B1)&!digitalRead(B2)){
  mode=1;
  }
 if(digitalRead(B3))st=0;
if(!digitalRead(B3)&!st){
  st=1;
  alarm=!alarm;
  }
float* values= mq2.read(true); //set it false if you don't want to print the values to the Serial
  

  co = mq2.readCO();

  smoke = mq2.readSmoke();
  ppm=smoke;
  ppm1=co;


 display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
   if(mode) display.println(F("    CO    "));
    else display.println(F("  SMOKE   "));
  display.setTextSize(3);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,20);
   if(mode) {if(ppm1<10000)display.print(F(" "));
    else display.print(ppm1/10000);
    if(ppm1<1000)display.print(F(" "));
    else display.print((ppm1/1000)%10);
    if(ppm1<100)display.print(F(" "));
    else display.print((ppm1/100)%10);
    if(ppm1<10)display.print(F(" "));
    else display.print((ppm1/10)%10);
     display.print(ppm1%10);}
 else {if(ppm<10000)display.print(F(" "));
    else display.print(ppm/10000);
    if(ppm<1000)display.print(F(" "));
    else display.print((ppm/1000)%10);
    if(ppm<100)display.print(F(" "));
    else display.print((ppm/100)%10);
    if(ppm<10)display.print(F(" "));
    else display.print((ppm/10)%10);
     display.print(ppm%10);}
     
display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(105,30);             // Start at top-left corner
  display.println(F("PPM"));
             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,55);             // Start at top-left corner
 if(mode){ display.print(F("SMOKE "));
           display.print(ppm);}
    else{ display.print(F(" CO "));
    display.print(ppm1);
     }
  display.setCursor(64,55); 
  if(alarm)display.println(F(" ALARM ON"));
  else display.println(F(" ALARM OFF"));
  
  display.display();


  beep=50000/ppm1;
  if(beep<10)beep=10;
  if(ppm1>beep){
   if(alarm){ digitalWrite(BUZZ,1);digitalWrite(LED,1);}
    delay(100);
    digitalWrite(BUZZ,0);digitalWrite(LED,0);
    }
  delay(100);
}
