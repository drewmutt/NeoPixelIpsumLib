#include <Adafruit_NeoPixel.h>
#import "NeoPixelIpsum.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(80, 11, NEO_GRB + NEO_KHZ800);
NeoPixelIpsum ipsum = NeoPixelIpsum(strip, 5, 16);


#define ST S_CHAR(SP_ROAD_STRAIGHT)
#define DT S_CHAR(SP_ROAD_DOTTED)
#define SSP S_SINGLE_SPACE

#define C_WHI 0
#define C_YEL 1
#define C_BLU 2
#define C_GRN 3

#define ALL_COL(x) {x,x,x,x,x,x,x,x,x,x,x,x,x,x,x}
#define C____ 0

byte _palSetRangeForAllAscii;
void setup()
{

Serial.begin(9600);
Serial.println("ok!");
  ipsum.clearPixels();
  ipsum.displayPixels();
  
  ipsum.setPalette(C_WHI, (PixelRGB) {10,10,10});
  ipsum.setPalette(C_YEL, (PixelRGB) {10,6,0});
  ipsum.setPalette(C_BLU, (PixelRGB) {25,0,25});
  ipsum.setPalette(C_GRN, (PixelRGB) {5,25,5});

  byte palRange1[15] = ALL_COL(C_WHI);

  
  byte palRange2[15] = {C_WHI, C_WHI, C_WHI,
                        C____, C____, C____,
                        C_YEL, C_YEL, C_YEL,
                        C____, C____, C____,
                        C_WHI, C_WHI, C_WHI};
                        
  byte palRange3[15] = ALL_COL(C_BLU);
  

  ipsum.addPaletteSetRange(SP_ROAD_STRAIGHT, SP_ROAD_STRAIGHT, palRange1);
  ipsum.addPaletteSetRange(SP_ROAD_DOTTED, SP_ROAD_DOTTED, palRange2);

  _palSetRangeForAllAscii = ipsum.addPaletteSetRange(0, 127, palRange3);
  
  
  PixelRGB pixelRGB[150] = {(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,54,70},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,54,70},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){81,8,47},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){81,8,47},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0},(PixelRGB){0,0,0}};
  ipsum.setBitmap(pixelRGB, 10);
}


void loop()
{
  

  PixelRGB timeRGB = ipsum.createRGB(10, 10, 10);
  
//  strip.setPixelColor(1, strip.Color(255, 255, 255));
//  strip.show();
  //ipsum.clearPixels();
//  String aString = String("1ºF");
  //Serial.println("1[");
  unsigned char deg = 'º';
  //Serial.println(deg, DEC);
  char charBuf[50];
  String stringOne = ST+ST+DT+DT+DT+DT+SSP+"23m    21"+SSP+"37";
//  stringOne+= millis();
//  String stringOne = ipsum.bitmapString();
  stringOne.toCharArray(charBuf, 50);
  ipsum.scrollText(charBuf);


  //ipsum.displayString(S_CHAR(SP_ROAD_STRAIGHT) + S_CHAR(SP_ROAD_STRAIGHT) + S_CHAR(SP_ROAD_DOTTED) + "213", (PixelRGB){20,3,8});
//  delay(3000);
//  int x = 'a';
//  ipsum.displayString(String(x), (PixelRGB){20,20,8});

  //delay(1000);

  ipsum.setPaletteSetRangeToPaletteIndex(_palSetRangeForAllAscii, C_BLU);
  while(ipsum.columnsLeftInScroll() >= ipsum.columnLengthFromString(SSP+"23m    21"+SSP+"37"))
  {
    ipsum.updateScroll();
  }
 
  delay(2000);

  while(ipsum.columnsLeftInScroll() >= ipsum.columnLengthFromString("    21" +SSP+ "37"))
  {
    ipsum.updateScroll();
  }

  ipsum.setPaletteSetRangeToPaletteIndex(_palSetRangeForAllAscii, C_GRN);

  while(ipsum.columnsLeftInScroll() >= ipsum.columnLengthFromString("21" +SSP+ "37"))
  {
    ipsum.updateScroll();
  }


  delay(2000);
  while(!ipsum.isDoneScrolling())
  {
    ipsum.updateScroll();
  }

}
  /*
  while(ipsum.columnsLeftInScroll() >= ipsum.columnLengthFromString("    23"+SSP+"15"))
  {
    ipsum.updateScroll();
  }
  ipsum.setPaletteSetRangeToPaletteIndex(_palSetRangeForAllAscii, C_WHI);
  
  while(ipsum.columnsLeftInScroll() >= ipsum.columnLengthFromString("23"+SSP+"15"))
  {
    ipsum.updateScroll();
  }
  delay(2000);
  
  while(!ipsum.isDoneScrolling())
  {
    ipsum.updateScroll();
  }
 
  while(!ipsum.isDoneScrolling())
  {
    ipsum.updateScroll();
  }
  
  delay(10000);
//  Serial.println("okay!");
//  ipsum.floodPanelWithColor(ipsum.createRGB(10,10,10));
//  ipsum.displayPixels();
//  delay(100);
}

  String hoursString = String(12);

  unsigned char digit0, digit1, digit2, digit3;

  digit0 = hoursString.charAt(0);
  digit1 = hoursString.charAt(1);
  digit2='1';
  digit3='4';
  
  if(digit0 > 0)
    ipsum.displayChar(digit0, 0, timeRGB);

  ipsum.displayChar(digit1, 4, timeRGB);

  //  displayDigit(COLON_DIGIT, 7, createRGB(100, 0, 0));

  ipsum.displayChar(digit2, 9, timeRGB);
  ipsum.displayChar(digit3, 13, timeRGB);

//displayChar('M', 0, timeRGB);
//displayChar('N', 4, timeRGB);
//displayChar('H', 9, timeRGB);
//displayChar('º',13, timeRGB);
  ipsum.displayPixels();
}*/
