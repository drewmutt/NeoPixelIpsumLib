/*
  NeoPixelIpsum.cpp - Library for displaying text on NeoPixels
  Created by Andrew Simmons, Mar 18, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "NeoPixelIpsum.h"
#include <avr/pgmspace.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#if defined (__SAM3X8E__) //Due
#define GLYPH_DATA_TYPE static const unsigned long
#else //Yun / Uno / Mega / etc..
#define GLYPH_DATA_TYPE PROGMEM prog_uint16_t
#define USE_FLASH_RAM 1
#endif


#define CHAR_TABLE_START 32
#define CHAR_TABLE_COUNT 95
#define CHAR_SPECIAL_START 127



GLYPH_DATA_TYPE font[] PROGMEM = {
0x0,	//32  
0x2092,	//33 !
0x2d,	//34 "
0x0,	//35 #
0x0,	//36 $
0x42a1,	//37 %
0x0,	//38 &
0x12,	//39 '
0x4494,	//40 (
0x1491,	//41 )
0x34,	//42 *
0x5d0,	//43 +
0x2400,	//44 ,
0x1c0,	//45 -
0x2000,	//46 .
0x1494,	//47 /
0x7f7f,	//48 0
0x7493,	//49 1
0x73e7,	//50 2
0x79a7,	//51 3
0x49e9,	//52 4
0x79cf,	//53 5
0x7bcf,	//54 6
0x24a7,	//55 7
0x7bef,	//56 8
0x79ef,	//57 9
0x410,	//58 :
0x2410,	//59 ;
0x8e0,	//60 <
0xe38,	//61 =
0x388,	//62 >
0x21a7,	//63 ?
0x0,	//64 @
0x5f6a,	//65 A
0x3aeb,	//66 B
0x724f,	//67 C
0x3b6b,	//68 D
0x73cf,	//69 E
0x12cf,	//70 F
0x7b4f,	//71 G
0x5bed,	//72 H
0x7497,	//73 I
0x3b24,	//74 J
0x5aed,	//75 K
0x7249,	//76 L
0x5b7d,	//77 M
0x5ffd,	//78 N
0x7b6f,	//79 O
0x1f6f,	//80 P
0x4f6f,	//81 Q
0x576b,	//82 R
0x39ce,	//83 S
0x2497,	//84 T
0x7b6d,	//85 U
0x2b6d,	//86 V
0x5f6d,	//87 W
0x5aad,	//88 X
0x256d,	//89 Y
0x72a7,	//90 Z
0x6496,	//91 [
0x4491,	//92 forward-slash
0x3493,	//93 ]
0x152,	//94 ^
0x7000,	//95 _
0x11,	//96 `
0x7b80,	//97 a
0x3ac9,	//98 b
0x73c0,	//99 c
0x7be4,	//100 d
0x77c0,	//101 e
0x25d4,	//102 f
0x3980,	//103 g
0x5ac9,	//104 h
0x2482,	//105 i
0x3482,	//106 j
0x5749,	//107 k
0x4492,	//108 l
0x5fc0,	//109 m
0x5ac0,	//110 n
0x7bc0,	//111 o
0x1fc0,	//112 p
0x4fc0,	//113 q
0x13c0,	//114 r
0x3580,	//115 s
0x64ba,	//116 t
0x7b40,	//117 u
0x2b40,	//118 v
0x7f40,	//119 w
0x5540,	//120 x
0x2540,	//121 y
0x64c0,	//122 z
0x64d6,	//123 {
0x2492,	//124 |
0x3593,	//125 }
0x3e0,	//126 ~ *_*_*_*_**_*_*_*_*_*_
0x7007, //127 RoadStart
0x70c7  //128 RoadDotted
};


unsigned char NeoPixelIpsum::convertGridPointToIndex(GridPoint gp)
{
  int index = 0;
  //Panel 1
  if(gp.x >= _TotalCols || gp.y >= _DigitRows || gp.x < 0 || gp.y < 0)
    return 0;
  if(gp.x < _ColsPerPanel)
  {
    index = (gp.y * _ColsPerPanel) + gp.x;
  }
  else
  {
    gp.x -= _ColsPerPanel;
    index = (gp.y * _ColsPerPanel) + gp.x;
    index += _LEDsPerPanel;
  }
  
  return index;
}



GridPoint NeoPixelIpsum::convertIndexToGridPoint(unsigned char index)
{
  unsigned char column = 0;
  unsigned char row = 0;
  unsigned char colOffset = 0;
  unsigned char rowOffset = 0;

  if(index >= _LEDsPerPanel)
  {
    colOffset = _ColsPerPanel;
    rowOffset = -_Rows;
  } 

  column = index % _ColsPerPanel;
  row = (unsigned char) (index / _ColsPerPanel);

  column += colOffset;
  row += rowOffset;
  
  /*
  Serial.print(index);
  Serial.print(" = ");
  Serial.print(createGridPoint(column, row).x);
  Serial.print(" , ");
  Serial.println(createGridPoint(column, row).y);
  */
  
  return createGridPoint(column, row);
}

GridPoint NeoPixelIpsum::createGridPoint(int x, int y)
{
  GridPoint gp;
  gp.x = x;
  gp.y = y;
  return gp;
}

PixelRGB NeoPixelIpsum::createRGB(unsigned char r, unsigned char g, unsigned char b)
{
  PixelRGB color = {r, g, b};
  return color;
}


void NeoPixelIpsum::addRGBToPixel(GridPoint gp, PixelRGB rgb)
{
  if(gp.x >= _TotalCols || gp.x < 0 || gp.y >= _TotalRows || gp.y < 0)
    return;
    
  unsigned char index = convertGridPointToIndex(gp);
  PixelRGB pixel = _pixels[index];
  pixel.r = constrain(pixel.r + rgb.r, 0, 255);
  pixel.g = constrain(pixel.g + rgb.g, 0, 255);
  pixel.b = constrain(pixel.b + rgb.b, 0, 255);  

  _pixels[index] = pixel;
}

void NeoPixelIpsum::floodPanelWithColor(PixelRGB aRGB)
{
  for(int i = 0; i < _TotalLEDs; i++)
    _pixels[i] = aRGB;
}  

void NeoPixelIpsum::clearPixels()
{
  for(int i = 0; i < _TotalLEDs; i++)
    _pixels[i] = createRGB(0,0,0);
}

PixelRGB NeoPixelIpsum::normalizeRGB(PixelRGB aRGB, double scale)
{
  double magnitude = sqrt( (aRGB.r * aRGB.r) + (aRGB.g * aRGB.g) + (aRGB.b * aRGB.b) );
  PixelRGB normalRGB;
  
  normalRGB.r = (int) ((((double) aRGB.r) / magnitude) * scale);
  normalRGB.g = (int) ((((double) aRGB.g) / magnitude) * scale);
  normalRGB.b = (int) ((((double) aRGB.b) / magnitude) * scale);  
  
  return normalRGB;
}

byte NeoPixelIpsum::getXLocationForCharAt(byte charLoc, bool addSpacing)
{
  byte spacing = 1;
//  if(aChar > SPECIAL_CHAR_ASCII_START)
//    spaci = 0;
  unsigned char xLoc = charLoc * (_DigitCols + addSpacing);
  return xLoc;
}

int incrementXValue(unsigned char currentChar)
{
  
}

int NeoPixelIpsum::columnLengthFromString(String aString)
{
  int totalColumns = 0; 
  for(int i = 0; i < aString.length(); i++)
   {
      unsigned char currentChar = aString.charAt(i);
      
      unsigned char spacingAmount = 0;
      if(currentChar < CHAR_SPECIAL_START)
        spacingAmount = _DigitCols + 1;
      else if(currentChar == C_SINGLE_SPACE)
        spacingAmount = 1;
      else if(currentChar == C_DOUBLE_SPACE)
        spacingAmount = 2;
      else
        spacingAmount = _DigitCols;
        
      totalColumns = totalColumns + spacingAmount;
      
   }
  return totalColumns;   
}

void NeoPixelIpsum::displayString(String output, PixelRGB displayRGB, int offset)
{
    clearPixels();  

    //unsigned char charLoc = output.length() - 1;
    unsigned char charLoc = 0;
    int xLoc = offset;
    unsigned char spacingAmount;
    for(int i = 0; i < output.length(); i++)
    {        
      unsigned char currentChar = output.charAt(charLoc);
      if((currentChar < CHAR_SPECIAL_START)) //Normal chars
      {
         //xLoc = _DigitCols+1
        spacingAmount = 1;
      }
      else if(currentChar == C_SINGLE_SPACE)
      {
        //XLoc++
        clearColumns(xLoc, 1);
        xLoc++;
        charLoc++;
        continue;
      }
      else if(currentChar == C_DOUBLE_SPACE)
      {
        clearColumns(xLoc, 2);
        xLoc+=2;
        charLoc++;
        continue;
      }
      else 
      {
        spacingAmount = 0;
      }
        
      
     
      /*
      if(addSpacing)
      {
        if((i > 1) || (i == 1))
          xLoc++;
      }
      */
//      if((charLoc > 0) || (charLoc == 0))
//      {
        displayChar(currentChar, xLoc, displayRGB);

        xLoc += _DigitCols + spacingAmount;
          
        charLoc++;
//      }
    }
    
    displayPixels();

}

void NeoPixelIpsum::displayPixels()
{
  for(unsigned char i = 0; i < _TotalLEDs; i++)
  {
    PixelRGB pixel = _pixels[i];
    if(pixel.r == 0 && pixel.g == 0 && pixel.b == 0)
      _neoPixel.setPixelColor(i, _neoPixel.Color(0, 0, 0));
    else
    {
      GridPoint gp = convertIndexToGridPoint(i);
      //int intensity = _Rows - gp.y;
      
      PixelRGB out = pixel;
      /*
      out.r = constrain(pixel.r * (_Rows - intensity), 0, 255);
      out.g = constrain(pixel.g, 0, 255);
      out.b = constrain(pixel.b * intensity, 0, 255);
*/
      PixelRGB normalOut = pixel; //normalizeRGB(out, 100);
      _neoPixel.setPixelColor(i, _neoPixel.Color(normalOut.r, normalOut.g, normalOut.b));
    }
  }
  _neoPixel.show();
}

#if defined (USE_FLASH_RAM)
unsigned char charBuffer[15];
#else
const unsigned char *charBuffer;
#endif

void NeoPixelIpsum::clearColumns(int startColumnNumber, int totalColumns)
{
  for(int x = startColumnNumber; x < (totalColumns + startColumnNumber); x++)
  {
    for(int y = 0; y < _DigitRows; y++)
    {

      GridPoint gp = createGridPoint(x,y);
      addRGBToPixel(gp,(PixelRGB){0,0,0}); 
    }
  }
    
}


void NeoPixelIpsum::displayChar(unsigned char ascii, int offset, PixelRGB color)
{

  PaletteSet palSet = getPaletteSetForAscii(ascii);
  
//  if(ascii > 90)
//    ascii -= 5;
    
  unsigned char charTableIndex = ascii - CHAR_TABLE_START;

//  if(ascii == 42)
//    charTableIndex = CHAR_TABLE_COUNT - 1;
//  else if(ascii > 64)
//    charTableIndex = charTableIndex - 7;
  
#if defined (USE_FLASH_RAM)
  
  //Super fun way to copy from Flash RAM. It reads a word because the sizeof(unsigned char *) is 2 bytes = a word
  //Then it reads the "byte_near" this pretty much has to do with getting a byte from a 16-bit address 
  //as opposed to "byte_far" which gets a value from a 32-bit address.
  //More info: http://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html#ga88d7dd4863f87530e1a34ece430a587c
  
  unsigned int glyphData = pgm_read_word_near(font + charTableIndex);
 #else  
    charBuffer = charTable[charTableIndex];  
 #endif
 

  
  for(unsigned char i = 0; i < (_DigitRows * _DigitCols); i++)
  {
    //if(ascii == 248)
    //  charBuffer[i] = pgm_read_byte_near(char248 + i);
    
      charBuffer[i] = bitRead(glyphData, i);

  } 
 
  unsigned char index = 0;
  for(unsigned char y = 0; y < _DigitRows; y++)
  {
    for(unsigned char x = 0; x < _DigitCols; x++)
    {
  
  
      GridPoint gp = createGridPoint(x,y);
      gp.x += offset;
      if( (gp.x >= _TotalCols) || (gp.x < 0) )
      {
        index++;
        continue;
      }

      if(ascii >= BITMAP_CHAR_START)
      {
          byte bitmapCharIndex = (byte) ((int) ascii - (int) BITMAP_CHAR_START);
          unsigned int arrayLoc = (_TotalPixelsPerDigit * bitmapCharIndex) + index;
          PixelRGB color = _bitmapData[arrayLoc];
          /*
          Serial.print(offset);
          Serial.print("----");
          Serial.print(bitmapCharIndex);
          Serial.print(" -- ");
          Serial.print(ascii, DEC);
          Serial.print(" || ");
          Serial.print(gp.x);
          Serial.print(",");
          Serial.print(gp.y);
          Serial.print(" - ");
          Serial.print(arrayLoc);
          Serial.print(" - ");
          Serial.print(index, DEC);
          Serial.print(" | " );
          Serial.print(color.r, DEC);
          Serial.print(",");
          Serial.print(color.g, DEC);
          Serial.print(",");
          Serial.println(color.b, DEC);
          */
          addRGBToPixel(gp, color);
      }
      else if( charBuffer[index] == 1 )
      {
        if(palSet == 0)
          addRGBToPixel(gp, color);
        else
          addRGBToPixel(gp, _palette[palSet[index]]);
        
      }
      index++;
    }
  }
}


  
NeoPixelIpsum::NeoPixelIpsum(Adafruit_NeoPixel &neoPixel, unsigned char rows, unsigned char cols):_neoPixel(neoPixel), _Rows(rows), _Cols(cols)
{

  _DigitRows = 5;
  _DigitCols = 3;
  _TotalPixelsPerDigit = _DigitRows * _DigitCols;
  _ColsPerPanel = 8;
  _LEDsPerPanel = 40;
  _TotalLEDs = 80;
  _TotalCols = 16;
  _TotalRows = 5;

  _pixels = (PixelRGB *) malloc(sizeof(PixelRGB) * _TotalLEDs);
  _palette = (PixelRGB *) malloc(sizeof(PixelRGB) * PALETTE_SIZE);
  _paletteRanges = (PaletteRange *) malloc(sizeof(PaletteRange) * MAX_PALETTE_RANGES);
  _scrollDelayBetweenCols = 40;
  _neoPixel.begin();
}


void NeoPixelIpsum::scrollText(char *aScrollText)
{
  _isDoneScrolling = false;
  _scrollText = aScrollText;
  _scrollTextOffset = _TotalCols;
  _nextScrollTime = 0;
}


int NeoPixelIpsum::columnsLeftInScroll()
{
  return _scrollTextOffset - (-columnLengthFromString(_scrollText));
}

bool NeoPixelIpsum::isDoneScrolling()
{
  return _isDoneScrolling;
}

void NeoPixelIpsum::updateScroll()
{
  if(millis() < _nextScrollTime)
    return;

  clearPixels();    

  byte firstLetterIndex = 0;
  byte lastLetterIndex = 3;
  
  displayString(_scrollText, (PixelRGB) {10,2,2}, _scrollTextOffset);
/*
  for(int i = firstLetterIndex; i < strlen(_scrollText); i++)
  {
    char letter = _scrollText[i];

    charOffset += _scrollTextOffset;
    displayChar(letter, charOffset, (PixelRGB) {3 , 3, 3} );
    if( (i == (strlen(_scrollText) - 1)) && (charOffset == (-_DigitCols)) )
    {
      _isDoneScrolling = true;
    }
  }
  */
  //Serial.println(columnLengthFromString(_scrollText), DEC);
  
  
  if(_scrollTextOffset <= -columnLengthFromString(_scrollText))
    _isDoneScrolling = true;
    
   // _isDoneScrolling = true;
  
  
  _scrollTextOffset--;
  _nextScrollTime = millis() + _scrollDelayBetweenCols;
  displayPixels();
}


void NeoPixelIpsum::setPalette(byte index, PixelRGB color)
{
  _palette[index] = color;
}

void NeoPixelIpsum::clearPaletteSetRanges()
{
  memset(_palette, 0, sizeof(PaletteRange) * MAX_PALETTE_RANGES);
  _TotalPaletteRanges = 0;
}


byte NeoPixelIpsum::addPaletteSetRange(byte asciiRangeStart, byte asciiRangeEnd, byte *paletteSet)
{
  if(_TotalPaletteRanges >= MAX_PALETTE_RANGES)
    return 0;
    
  PaletteRange palRange;
  palRange.asciiStart = asciiRangeStart;
  palRange.asciiEnd = asciiRangeEnd;
 
  int paletteSetSize = sizeof(byte) * (_DigitRows * _DigitCols);
  PaletteSet palSet = (PaletteSet) malloc(paletteSetSize);
  memcpy( palSet, paletteSet, paletteSetSize);
  palRange.paletteSet = palSet;

  _paletteRanges[_TotalPaletteRanges] = palRange;
  
  _TotalPaletteRanges++;
  
  return _TotalPaletteRanges - 1;
}

void NeoPixelIpsum::setPaletteSetRangeToPaletteIndex(byte paletteSetRange, byte paletteIndex)
{
  memset(_paletteRanges[paletteSetRange].paletteSet, paletteIndex, sizeof(byte) * (_DigitRows * _DigitCols));
}

PaletteSet NeoPixelIpsum::getPaletteSetForAscii(byte ascii)
{
  for(byte i = 0; i < _TotalPaletteRanges; i++)
  {
    PaletteRange palRange = _paletteRanges[i];
    /*
    Serial.print("Range ");
    Serial.print(i);
    Serial.print("  ");
    Serial.print(palRange.asciiStart, DEC);
    Serial.print(" ");
    Serial.println(palRange.asciiEnd, DEC);
    */
    if(palRange.asciiStart <= ascii && palRange.asciiEnd >= ascii)
      return _paletteRanges[i].paletteSet;
      
//   Serial.println("No match");
  }
  return 0;
}

String NeoPixelIpsum::bitmapString()
{
  String outString = "";
  for(byte i = BITMAP_CHAR_START; i < (BITMAP_CHAR_START+_bitmapCharWidths); i++)
  {
    outString += S_CHAR(i);
//    Serial.println(i, DEC);
  }
  return outString; 
}

///Bitmap
void NeoPixelIpsum::setBitmap(PixelRGB *bitmapData, byte charsInWidth)
{
  free(_bitmapData);
  int bitmapSizeInBytes = sizeof(PixelRGB) * (_TotalPixelsPerDigit + 1) * charsInWidth;
  _bitmapData = (PixelRGB *) malloc( bitmapSizeInBytes );
/*
  delay(5000);
  Serial.println("--");
  Serial.println(sizeof(PixelRGB), DEC);
  Serial.println(_TotalPixelsPerDigit, DEC);
  Serial.println(charsInWidth, DEC);
  Serial.println(bitmapSizeInBytes);
  delay(5000);
  */
  memcpy(_bitmapData, bitmapData, bitmapSizeInBytes);
  
  _bitmapCharWidths = charsInWidth;
}
