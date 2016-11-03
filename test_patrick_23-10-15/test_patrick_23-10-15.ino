// copy the sketch below and paste it into the Arduino IDE compile and run the program.
// this sketch was created using code from both the adafruit and the virtuabotix sample sketches
// You can use any (4 or) 5 pins
#define sclk 4
#define mosi 5
#define cs   6
#define dc   7
#define rst  8  // you can also connect this to the Arduino reset
#define ANALOG_IN 0 // for cds light sensor

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <dht11.h> // dht temp humidity sensor library

dht11 DHT11;
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);



void setup(void) {
  DHT11.attach(2); // set digital port 2 to sense dht input
  Serial.begin(9600);
  Serial.print("hello!");
 
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  Serial.println("init");
  //tft.setRotation(tft.getRotation()+1); //uncomment to rotate display

// get time to display "sensor up time"
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);


  Serial.println("done");
  delay(1000);


tftPrintTest();
  delay(500);
  tft.fillScreen(ST7735_BLACK);
// Splash screen for esthetic purposes only
  // optimized lines
  testfastlines(ST7735_RED, ST7735_BLUE);
  delay(500);

  testdrawrects(ST7735_GREEN);
  delay(500);
  tft.fillScreen(ST7735_BLACK);
}
void loop() {
// tft.invertDisplay(true);
// delay(500);
//  tft.invertDisplay(false);
tft.setTextColor(ST7735_WHITE);
tft.setCursor(0,0);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setCursor(50, 20);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_BLUE);
  tft.print(millis() / 1000);
  tft.setTextSize(1);
  tft.setCursor(40, 40);
  tft.setTextColor(ST7735_WHITE);
  tft.println("seconds");
  tft.setCursor(0, 60);
  tft.drawLine(0, 50, tft.width()-1, 50, ST7735_WHITE); //draw line separator
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Temperature (C): ");
  tft.setTextColor(ST7735_GREEN);
  tft.println((float)DHT11.temperature,1);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Humidity    (%): ");
  tft.setTextColor(ST7735_RED);
  tft.println((float)DHT11.humidity,1);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Temperature (F): ");
  tft.setTextColor(ST7735_GREEN);
  tft.println(DHT11.fahrenheit(), 1);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Temperature (K): ");
// tft.print(" ");
  tft.setTextColor(ST7735_GREEN);
  tft.println(DHT11.kelvin(), 1);

  tft.setTextColor(ST7735_WHITE);
  tft.print("Dew Point   (C): ");
  tft.setTextColor(ST7735_RED);
  tft.println(DHT11.dewPoint(), 1);
  tft.setTextColor(ST7735_WHITE);
  tft.print("DewPointFast(C): ");
  tft.setTextColor(ST7735_RED);
  tft.println(DHT11.dewPointFast(), 1);
  tft.drawLine(0, 110, tft.width()-1, 110, ST7735_WHITE);
  tft.setCursor(0,115);
  tft.print("Light intensity ");
int val = analogRead(ANALOG_IN);
  tft.setCursor(60, 130);
   tft.setTextColor(ST7735_YELLOW);
  tft.println(val, 1);
  delay(2000);
  tft.fillScreen(ST7735_BLACK);
 
}
void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 60);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.println("temperature");
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("humidity");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(2);
  tft.println("monitor");
  tft.setTextColor(ST7735_BLUE);
  //tft.setTextSize(3);
  //tft.print(3598865);
  delay(500);
  }
 
void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}
