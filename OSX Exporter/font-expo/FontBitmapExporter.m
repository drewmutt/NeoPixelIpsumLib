//
//  AppDelegate.m
//  font-expo
//
//  Created by Andrew Simmons on 5/5/14.
//  Copyright (c) 2014 ok. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

#define MAX_ASCII 127
int currentAscii;
NSString *outString;


NSArray* checkArray;

-(bool) getCheckValueAtX:(int) aX y:(int)aY
{
	NSButton *button = [[checkArray objectAtIndex:aY] objectAtIndex:aX];
	return (button.state == NSOnState);
}

- (IBAction)exportPressed:(id)sender {
	int bitLocation = 0;
	int value = 0;
	for(int y = 0; y < 5; y++)
	{
		for(int x = 0; x < 3; x++)
		{
			int currentValue = pow(2, bitLocation);
			if([self getCheckValueAtX:x y:y])
			{
				value += currentValue;
			}
			bitLocation++;
		}
	}
	
	NSString *outString = @"";
	outString = [outString stringByAppendingFormat:@"0x%x", value];
	_importField.stringValue = outString;
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	
	checkArray = @[
				   @[_button0_0, _button1_0, _button2_0 ],
				   @[_button0_1, _button1_1, _button2_1 ],
				   @[_button0_2, _button1_2, _button2_2 ],
				   @[_button0_3, _button1_3, _button2_3 ],
				   @[_button0_4, _button1_4, _button2_4 ]
				   ];
	
	outString = @"";
    currentAscii = 32;
	outString = [outString stringByAppendingFormat:@"\n/* Starting at %d */\n", currentAscii];
	outString = [outString stringByAppendingFormat:@"/* Count is %d */\n", MAX_ASCII-currentAscii];
	outString = [outString stringByAppendingFormat:@"GLYPH_DATA_TYPE font[] PROGMEM = {\n"];


	
		
	//[self getPixels];
	
	
}

-(void) getPixels
{
    // Insert code here to initialize your application
    if(currentAscii >= MAX_ASCII)
	{
		NSLog(@"%@", outString);
        return;
	}

    
		


        [_textLabel setNeedsDisplay:YES];
        [_textLabel lockFocus];
        
        NSPoint pixelPosition = NSMakePoint(0, 0);
        NSColor *pixelColor;
        pixelColor = NSReadPixel(pixelPosition); //pixelPosition is of type NSPoint and has the value of the position where you want to read the color
        
        int pixelSize = 6;
        NSString *outText = @"\n";
    
		int value = 0;
		int bitLocation = 0;
	

        for(int y = 0; y < 5; y++)
        {
            for(int x = 0; x < 3; x++)
            {
                //            NSLog(@"Pixel %d, %d\n", x, y);
                float pixelPosX = (pixelSize / 2) + (pixelSize * x);
                float pixelPosY = (pixelSize / 2) + (pixelSize * (y+1));
                pixelPosition.x = pixelPosX;
                pixelPosition.y = pixelPosY;
                pixelColor = NSReadPixel(pixelPosition);
				
				int currentValue = pow(2, bitLocation);
                if(pixelColor.redComponent > 0)
				{
                    outText = [outText stringByAppendingString:@"* "];
					value = value + currentValue;
					//NSLog(@"Adding: %d", currentValue);
				}
                else
				{
                    outText = [outText stringByAppendingString:@"  "];
				}
                //            NSLog(@"  Color (Red): %f", pixelColor.redComponent);
				
				bitLocation++;
            }
            outText = [outText stringByAppendingString:@"\n"];
            
        }
        NSLog(@"%@\n%d - %c (%d)\n",outText, value, currentAscii, currentAscii);

	
	if(currentAscii == 92)
		outString = [outString stringByAppendingFormat:@"0x%x,\t//%d forward-slash\n", value, currentAscii];
	else
		outString = [outString stringByAppendingFormat:@"0x%x,\t//%d %c\n", value, currentAscii, currentAscii];
	
    [_textLabel unlockFocus];

    currentAscii++;
	
	if(currentAscii == '&' || currentAscii == ' ' || currentAscii == '#' || currentAscii == '$' || currentAscii == '@')
	{
		_textLabel.stringValue = @"";
	}
	else
	{
		_textLabel.stringValue = [NSString stringWithFormat:@"%c", currentAscii];
	}
	
    
    [self performSelector:@selector(getPixels) withObject:nil afterDelay:.05];
    

}

- (IBAction)bitmapOut:(id)sender
{
	NSString *path = @"~/Documents/test.png";
	NSImage * image =  [[NSImage alloc] initWithContentsOfFile: [path stringByExpandingTildeInPath]];
	NSBitmapImageRep* raw_img = [NSBitmapImageRep imageRepWithData:[image TIFFRepresentation]];
	
	int charWidth = 3;
	int charHeight = 5;
	
	long imageSizeWidth = raw_img.pixelsWide;
	int totalChars = (int) ( imageSizeWidth / ((long)charWidth));
	
	NSString *output = @"";
	for(int currentChar = 0; currentChar < totalChars; currentChar++)
	{
		for(int y = 0; y < charHeight; y++)
		{
			for(int x = 0; x < charWidth; x++)
			{
				int realX = x + (charWidth * currentChar);
				NSColor *color = [raw_img colorAtX:realX y:y];
				int r = color.redComponent * 30;
				int g = color.greenComponent * 30;
				int b = color.blueComponent * 30;
				
				unsigned int hex = (b << 16) | (g << 8) | r;
				NSLog(@"%d, %d, %d", realX, y);
				//output = [output stringByAppendingString:[NSString stringWithFormat:@"0x%x,", hex]];
				output = [output stringByAppendingString:[NSString stringWithFormat:@"(PixelRGB){%d,%d,%d},", r,g,b]];
			}
		}
	}
	NSLog(@"%@\n", output);
}

@end
