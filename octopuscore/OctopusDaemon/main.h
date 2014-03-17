//
//  main.h
//  OctopusDaemon
//
//  Created by K3A on 5/23/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#ifndef OctopusDaemon_main_h
#define OctopusDaemon_main_h

#import <Foundation/Foundation.h>

#define PREF_FILE "/var/mobile/Library/Preferences/me.k3a.OctopusKeyboard.plist"
BOOL prefsLoad();
NSString* prefString(NSString* key, NSString* def=@"");
int prefInt(NSString* key, int def=0);

void OLog(int level, const char* format, ...);
void OErr(const char* format, ...);

#endif
