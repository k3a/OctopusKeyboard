//
//  SEPrefs.h
//  SEPrefs
//
//  Created by K3A on 3/3/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#import <Preferences/PSListController.h>
#import <MessageUI/MessageUI.h>

extern "C" {
    #include "../octopuscore/OctopusDaemon/octopus.h"
}
    
#define PREF_FILE "/var/mobile/Library/Preferences/me.k3a.OctopusKeyboard.plist"
#define COLOBUS_PREF_FILE "/var/mobile/Library/Preferences/.me.k3a.OctopusKeyboard.plist"

mach_port_t GetServerPort();

@interface K3AOKPrefsController : PSViewController <UITextFieldDelegate,UITableViewDataSource,UITableViewDelegate, MFMailComposeViewControllerDelegate,UIAlertViewDelegate> {
    
    UITableView *_tableView;
	//NSMutableString *_title;
    NSMutableDictionary *_settings;
    NSMutableDictionary *_colobusSettings;
    NSString* _softVersion;
    
    unsigned _state; // 0-unknown, 1-success, 2-fail
}
+(K3AOKPrefsController*)instance;
- (id) view;
- (id) navigationTitle;
- (void) dealloc;
- (void)loadFromSpecifier:(PSSpecifier *)spec;
- (void)setSpecifier:(PSSpecifier *)spec;
-(void)saveSettings;
-(int)prefInt:(NSString*)key default:(int)def;
-(BOOL)setPrefInt:(NSString*)key value:(int)val;

-(void)onSuccess;
-(void)onFail;

@end

@interface UISwitch (K3AOKAdditions)
- (void)setAlternateColors:(BOOL)alternateColors;
@end
