//
//  AppDelegate.h
//  font-expo
//
//  Created by Andrew Simmons on 5/5/14.
//  Copyright (c) 2014 ok. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (weak) IBOutlet NSTextField *textLabel;
@property (weak) IBOutlet NSColorWell *colorWell;



@property (weak) IBOutlet NSButton *button0_0;
@property (weak) IBOutlet NSButton *button1_0;
@property (weak) IBOutlet NSButton *button2_0;

@property (weak) IBOutlet NSButton *button0_1;
@property (weak) IBOutlet NSButton *button1_1;
@property (weak) IBOutlet NSButton *button2_1;

@property (weak) IBOutlet NSButton *button0_2;
@property (weak) IBOutlet NSButton *button1_2;
@property (weak) IBOutlet NSButton *button2_2;

@property (weak) IBOutlet NSButton *button0_3;
@property (weak) IBOutlet NSButton *button1_3;
@property (weak) IBOutlet NSButton *button2_3;

@property (weak) IBOutlet NSButton *button0_4;
@property (weak) IBOutlet NSButton *button1_4;
@property (weak) IBOutlet NSButton *button2_4;

@property (weak) IBOutlet NSButton *exportButton;
@property (weak) IBOutlet NSButton *importButton;
@property (weak) IBOutlet NSTextField *importField;

@end
