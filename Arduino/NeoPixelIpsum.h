/*
  NeoPixelIpsum.h - Library for displaying text on NeoPixels
  Created by Andrew Simmons, Mar 18, 2014.
  Released into the public domain.
*/
#ifndef NeoPixelIpsum_h
#define NeoPixelIpsum_h

#include "Arduino.h"
#include "/Users/andrewsimmons/Documents/Arduino/libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.h"

/*
#define PIN 11

#define COLS 16
#define ROWS 5
#define LEDS 80

#define DIGIT_ROWS 5
#define DIGIT_COLS 3

#define COLS_PER_PANEL 8
#define LEDS_PER_PANEL 40
*/

#define BITMAP_CHAR_START 130

#define PALETTE_SIZE 16
#define MAX_PALETTE_RANGES 16

#define C_SINGLE_SPACE 200
#define C_DOUBLE_SPACE 201
#define SP_ROAD_STRAIGHT 127
#define SP_ROAD_DOTTED 128

#define S_SINGLE_SPACE String((char)C_SINGLE_SPACE) 
#define S_DOUBLE_SPACE String((char)C_DOUBLE_SPACE)
#define S_CHAR(X) String((char)X)
#define COLON_DIGIT 10

struct pixelRGB
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct gridPoint
{
  int x;
  int y;
};

struct paletteRange
{
  byte asciiStart;
  byte asciiEnd;
  byte *paletteSet;
};

typedef byte* PaletteSet;
typedef struct gridPoint GridPoint;
typedef struct pixelRGB PixelRGB;
typedef struct paletteRange PaletteRange;



typedef PixelRGB (* EffectFuncPtr) (int x, int y, int pixelIndex, PixelRGB inPixelColor);
struct pixelEffect
{
  EffectFuncPtr effectMethod;  
};





typedef struct pixelEffect PixelEffect;

class NeoPixelIpsum
{
  public:
    NeoPixelIpsum(Adafruit_NeoPixel &neoPixel, unsigned char rows, unsigned char cols);
    unsigned char convertGridPointToIndex(GridPoint gp);
    GridPoint convertIndexToGridPoint(unsigned char index);
    GridPoint createGridPoint(int x, int y);
    PixelRGB createRGB(unsigned char r, unsigned char g, unsigned char b);
    void floodPanelWithColor(PixelRGB aRGB);
    void clearPixels();
    bool isDoneScrolling();
    PixelRGB normalizeRGB(PixelRGB aRGB, double scale);
    void displayChar(unsigned char ascii, int offset, PixelRGB color);
    void displayPixels();
    void displayString(String output, PixelRGB displayRGB, int offset=0);
    void scrollText(char *aScrollText);
    void updateScroll();
    int columnsLeftInScroll();
    int columnLengthFromString(String aString);
    
    void setPalette(byte index, PixelRGB color);
    byte addPaletteSetRange(byte asciiRangeStart, byte asciiRangeEnd, byte *paletteSet);
    void setPaletteSetRangeToPaletteIndex(byte paletteSetRange, byte paletteIndex);
    void setBitmap(PixelRGB *pixelValues, byte charsInWidth);
    void clearPaletteSetRanges();
    String bitmapString();
  private:
    unsigned char _Rows;
    unsigned char _Cols;
    unsigned char _DigitRows;
    unsigned char _DigitCols;
    unsigned char _ColsPerPanel;
    unsigned char _LEDsPerPanel;
    unsigned int _TotalLEDs;
    unsigned char _TotalCols;
    unsigned char _TotalRows;
    unsigned char _TotalPaletteRanges;
    unsigned char _TotalPixelsPerDigit;
    PixelRGB *_pixels;
    Adafruit_NeoPixel _neoPixel;
    
    char *_scrollText;
    byte _scrollTextIndex;
    int _scrollTextOffset;
    unsigned long _nextScrollTime;
    bool _isDoneScrolling;
    
    PixelRGB *_palette;
    PaletteRange *_paletteRanges;
    unsigned int _scrollDelayBetweenCols;
    PixelRGB *_bitmapData;
    byte _bitmapCharWidths;
  protected:
    byte getXLocationForCharAt(byte charLoc, bool addSpacing = true);
    void addRGBToPixel(GridPoint gp, PixelRGB rgb);
    void clearColumns(int startColumnNumber, int totalColumns);
    PaletteSet getPaletteSetForAscii(byte ascii);
};

#endif

/*
struct rgb
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct gridPoint
{
  unsigned char x;
  unsigned char y;
};


typedef struct gridPoint GridPoint;
typedef struct rgb RGB;
*/
