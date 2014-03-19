#import <Preferences/Preferences.h>
#import <Twitter/Twitter.h>
#import <Accounts/Accounts.h>
#import <UIKit/UIKit.h>
#include <AppSupport/CPDistributedMessagingCenter.h>

#import "Shared.h"
#import "OKPrefs.h"

#import "OKDicts.h"

#include <asl.h>

static bool s_timeOK;

static __attribute__((inline)) mach_port_t GetColobusPort()
{
	return 0;
}

mach_port_t GetServerPort()
{
    kern_return_t           kr;
    static mach_port_t      bsPort = 0;
    mach_port_t     srvPort = 0;
    
    if (bsPort == 0)
    {
        kr = task_get_bootstrap_port( mach_task_self(), &bsPort );
        if (kr != MACH_MSG_SUCCESS)
        {
            NSLog(@"OK Prefs: Failed to get the boostrap port!");
            //mach_error("task_get_bootstrap_port:", kr);
            return 0;
        }
    }
    
    if (srvPort == 0)
    {
        kr = bootstrap_look_up( bsPort, "me.k3a.octopusd", &srvPort );
        if (kr != MACH_MSG_SUCCESS)
        {
            NSLog(@"OK Prefs: Could not lookup the service, is daemon running?");
            //mach_error("Could not lookup the service, is daemon running?", kr);
            return 0;
        }
    }
    
    return srvPort;
}

/// Informs the daemon that settings changed
static void OnSettingsChanged()
{
	oReloadPrefs(GetServerPort());
}
static void OnSettingsChangedNotif(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo)
{
	OnSettingsChanged();
}

static void AlertView(NSString* title, NSString* text)
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title message:text  delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert show];
    [alert release];
}

static NSString* GetSystemLanguage()
{
    NSString *language = [[NSLocale preferredLanguages] objectAtIndex:0];
    /*NSUserDefaults* userDefaults = [NSUserDefaults standardUserDefaults];
     NSArray* arrayLanguages = [userDefaults objectForKey:@"AppleLanguages"];
     NSString* language = [arrayLanguages objectAtIndex:0];*/
    
    char lang[16];
    strcpy(lang, [language UTF8String]);
    
    unsigned sepIdx = strlen(lang);
    bool afterSep = false;
    for (unsigned i=0; i<strlen(lang); i++)
    {
        if (lang[i] == '_' || lang[i] == '-')
        {
            lang[i] = '-';
            sepIdx = i;
            afterSep = true;
        }
        else if (afterSep)
            lang[i] = toupper(lang[i]);
    }
    
    return [NSString stringWithUTF8String:lang];
}

// ---------------------------------------------------------------------------------------------------------------------------
#pragma mark - DICTIONARY CONTROLLER
@interface OKUserDictEdit : PSViewController <UITableViewDataSource,UITableViewDelegate> {
	UITableView *_tableView;
	NSString *_navigationTitle;
	
	uint32_t wordCount;
}
- (id)initForContentSize:(CGSize)size;

@property (nonatomic, retain) NSString *navigationTitle;
@property (nonatomic, readonly) UITableView *tableView;
@end

@implementation OKUserDictEdit
-(id)initForContentSize:(CGSize)size {
	if ([[PSViewController class] instancesRespondToSelector:@selector(initForContentSize:)])
		self = [super initForContentSize:size];
	else
		self = [super init];
	if (self) {
		CGRect frame;
		frame.origin = CGPointMake(0,0);
		frame.size = size;
		_tableView = [[UITableView alloc] initWithFrame:frame style:UITableViewStyleGrouped];
		[_tableView setDataSource:self];
		[_tableView setDelegate:self];
		[_tableView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	}
	return self;
}

-(void)dealloc {
	[_tableView setDelegate:nil];
	[_tableView setDataSource:nil];
	[_tableView release];
	[_navigationTitle release];
	[super dealloc];
}


-(void)tableView:(UITableView *)tv commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
	///remove word
	wordCount--;
	
	[_tableView beginUpdates];
	[_tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
	[_tableView endUpdates];
}
-(void)loadFromSpecifier:(PSSpecifier *)specifier {
	[self setNavigationTitle:[specifier name]];
	
	oUserDictGetNumWords(GetServerPort(), &wordCount);
	//Get wordlist?
	
	[_tableView reloadData];
	[_tableView setEditing:YES animated:NO];
}
-(id)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	UITableViewCell *cell=[tableView dequeueReusableCellWithIdentifier:@"OKWCell"];
	if (!cell) {
		cell=[[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"OKWCell"] autorelease];
	}
	
	//set word
	cell.textLabel.text=@"";
	return cell;
}
-(int)tableView:(UITableView *)tableView numberOfRowsInSection:(int)section {
	return wordCount;
}
@synthesize tableView = _tableView, navigationTitle = _navigationTitle;
-(int)numberOfSectionsInTableView:(UITableView *)tableView { return 1; }
-(id)tableView:(UITableView *)tableView titleForHeaderInSection:(int)section {return nil;}
-(BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath { return NO; }
-(BOOL)tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath { return NO; }
-(UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath { return UITableViewCellEditingStyleDelete; }
-(void)setNavigationTitle:(NSString *)navigationTitle {[_navigationTitle autorelease]; _navigationTitle = [navigationTitle retain]; if ([self respondsToSelector:@selector(navigationItem)]) [[self navigationItem] setTitle:_navigationTitle];}
-(void)setSpecifier:(PSSpecifier *)specifier {[self loadFromSpecifier:specifier];[super setSpecifier:specifier];}
-(void)viewWillBecomeVisible:(void *)source {if (source) [self loadFromSpecifier:(PSSpecifier *)source];[super viewWillBecomeVisible:source];}
-(UIView *)view {return _tableView;}
-(CGSize)contentSize {return [_tableView frame].size;}
@end

#pragma mark - DICTIONARY CONTROLLER
@interface OKUserDictCtrl : PSListController {
	NSTimer* _reloadTimer;
}
+(id)specifierCtrl:(NSString*)spec;
@end

@implementation OKUserDictCtrl
+(id)controlerWithParent:(PSViewController*)parent
{
    id obj = [[[OKUserDictCtrl alloc] initWithParent:parent] autorelease];
    
    return obj;
}
-(id)initWithParent:(PSViewController*)parent
{
    if ((self = [super init]))
    {
        self.parentController = parent;
        self.rootController = parent.rootController;
		
		
    }
    return self;
}
- (void)willResignActive {
	if (_reloadTimer!=nil) {
		[_reloadTimer invalidate];
		[_reloadTimer release];
		_reloadTimer=nil;
	}
}
- (void)willBecomeActive {
	if (_reloadTimer==nil) {
		_reloadTimer = [[NSTimer scheduledTimerWithTimeInterval:1.4f target:self selector:@selector(reloadSpecifiers) userInfo:nil repeats:YES] retain];
	}
}
-(void)dealloc
{
	if (_reloadTimer!=nil) {
		[_reloadTimer invalidate];
		[_reloadTimer release];
	}
	[super dealloc];
}
- (id) specifiers
{
    if (!_specifiers) {
        _specifiers = [[self loadSpecifiersFromPlistName:@"UserDict" target: self] retain];
		
		
	}
    
    return _specifiers;
}
-(void)learnWords
{
    AlertView(@"Importing", @"Importing words from Messages in the background. You can click OK and continue with your work.");
    oUserDictImportMessages(GetServerPort());
}
-(void)learnContacts
{
	AlertView(@"Importing", @"Importing contact names in the background. You can click OK and continue with your work.");
    oUserDictImportContacts(GetServerPort());
}
-(void)deleteWords
{
    oUserDictClear(GetServerPort());
	[self reloadSpecifiers];
}
-(id)numWords:(PSSpecifier*)spec;
{
    unsigned numWords = 0;
    oUserDictGetNumWords(GetServerPort(), &numWords);
    return [NSString stringWithFormat:@"%u", numWords];
}

@end

// ---------------------------------------------------------------------------------------------------------------------------
#pragma mark - UNIVERSAL SPECIFIER CONTROLLER
@interface OKSpecifierCtrl : PSListController {
    NSString* _specName;
}
+(id)specifierCtrl:(NSString*)spec;
@end

@implementation OKSpecifierCtrl
+(id)specifierCtrl:(NSString*)spec parent:(PSViewController*)parent
{
    id obj = [[[OKSpecifierCtrl alloc] initWithSpecifiers:spec parent:parent] autorelease];
    
    return obj;
}
-(id)initWithSpecifiers:(NSString*)spec parent:(PSViewController*)parent
{
    if ((self = [super init]))
    {
        _specName = [spec copy];
        self.parentController = parent;
        self.rootController = parent.rootController;
    }
    return self;
}
-(void)dealloc
{
    [_specName release];
    [super dealloc];
}

- (id) specifiers
{
    if (!_specifiers)
        _specifiers = [[self loadSpecifiersFromPlistName:_specName target: self] retain];
    
    return _specifiers;
}

@end

// ---------------------------------------------------------------------------------------------------------------------------
#pragma mark - LEGAL CONTROLLER
@interface OKLegalController : PSViewController {
    //UITextView* _view;
}
@end
@implementation OKLegalController
- (id)init
{
    if ( (self = [super init]) )
    {
        [self setView: [[UITextView alloc] initWithFrame:CGRectMake(0,0,320,400)] ];
        NSString* path = [[NSBundle bundleForClass:[self class]] pathForResource:@"about" ofType:@"txt"];
        [self.view setText:[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil]];
        [self.view setEditable:NO];
        
        [[self navigationItem] setTitle:@"About"];
    }
    
    return self;
}
-(void)dealloc
{
    //[_view release];
	[super dealloc];
}
/*- (id) view
{
    return _view;
}*/
@end

// ---------------------------------------------------------------------------------------------------------------------------
#pragma mark - MAIN CONTROLLER

#include <sys/time.h>
static unsigned GetTimestampSec()
{
    timeval time;
    gettimeofday(&time, NULL);
    
    unsigned elapsed_seconds  = time.tv_sec;
    
    return elapsed_seconds;
}

@implementation K3AOKPrefsController

static K3AOKPrefsController* s_singleton = nil;

static void ColobusSuccess(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo)
{
    NSLog(@"OK: Prefs: Success");
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [s_singleton onSuccess];
    }); 
}

static void ColobusFail(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo)
{
    NSLog(@"OK: Prefs: Fail");
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [s_singleton onFail];
    }); 
}

-(void)onSuccess
{
    _state = 1;
    [_tableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationNone];
}
-(void)onFail
{
    _state = 2;
    [_tableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationNone];
}

-(void)loadSettings
{
    [_settings release];
    _settings = [[NSMutableDictionary alloc] initWithContentsOfFile:@PREF_FILE];
    if (_settings)
        NSLog(@"OK: Prefs: Preferences loaded.");
    else
    {
        NSLog(@"OK: Prefs: Failed to load preferences. Creating...");
        _settings = [[NSMutableDictionary alloc] init];
    }
}

+(K3AOKPrefsController*)instance
{
	return s_singleton;
}

-(id)table
{
    return nil; //wtf...
}

- (id)init
{
    if ( (self = [super init]) )
    {
        s_singleton = self;
        
        [self loadSettings];
		
		// CHECK BETA TIMEOUT!!!!!
		//unsigned tm = GetTimestampSec();
		//s_timeOK = tm < 1340060264 + 15*24*60*60+1;
        s_timeOK = true;
		
        
        // apply defaults
        //if (![_settings objectForKey:@"detectLang"])
        //    [_settings setObject:[NSNumber numberWithBool:YES] forKey:@"detectLang"];
        
        // save defaults just in case
        [_settings writeToFile:@PREF_FILE atomically:YES];
        
       _state = 1;
		
		// watch settings change
		CFNotificationCenterAddObserver(CFNotificationCenterGetDarwinNotifyCenter(), NULL, OnSettingsChangedNotif, CFSTR("me.k3a.OctopusKeyboard/reloadPrefs"), NULL, CFNotificationSuspensionBehaviorCoalesce);
    }
    
    return self;
}

- (void) dealloc {
    
    // remove observer
    CFNotificationCenterRemoveEveryObserver(CFNotificationCenterGetDarwinNotifyCenter(), self);
    s_singleton = nil;
    
    [_tableView release];
	//[_title release];
    [_settings release];
    [super dealloc];
}

-(void)followSafari
{
    NSString* followUrl = @"https://twitter.com/intent/follow?original_referer=http%3A%2F%2Fae.k3a.me%2F&region=follow_link&screen_name=kexik&source=followbutton&variant=2.0";
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:followUrl]];
}

- (void)follow
{
    ACAccountStore *accountStore = [[[ACAccountStore alloc] init] autorelease];
    
    ACAccountType *accountType = [accountStore accountTypeWithAccountTypeIdentifier:ACAccountTypeIdentifierTwitter];
    
    [accountStore requestAccessToAccountsWithType:accountType withCompletionHandler:^(BOOL granted, NSError *error) {
        if(granted) {
            // Get the list of Twitter accounts.
            NSArray *accountsArray = [accountStore accountsWithAccountType:accountType];
            
            // For the sake of brevity, we'll assume there is only one Twitter account present.
            // You would ideally ask the user which account they want to tweet from, if there is more than one Twitter account present.
            if ([accountsArray count] > 0) {
                // Grab the initial Twitter account to tweet from.
                ACAccount *twitterAccount = [accountsArray objectAtIndex:0];
                
                NSMutableDictionary *tempDict = [[NSMutableDictionary alloc] init];
                [tempDict setValue:@"kexik" forKey:@"screen_name"];
                [tempDict setValue:@"true" forKey:@"follow"];
                
                TWRequest *postRequest = [[TWRequest alloc] initWithURL:[NSURL URLWithString:@"http://api.twitter.com/1/friendships/create.json"] 
                                                             parameters:tempDict 
                                                          requestMethod:TWRequestMethodPOST];
                
                
                [postRequest setAccount:twitterAccount];
                
                [postRequest performRequestWithHandler:^(NSData *responseData, NSHTTPURLResponse *urlResponse, NSError *error) {
                    if ([urlResponse statusCode] != 200)
                    {
                        NSLog(@"OK: Prefs: TWF Status: %i", [urlResponse statusCode]);
                        [self followSafari];
                    }
                    else
                    {
                        NSLog(@"OK: Prefs: TWF Success");
                        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Follow" message:@"Thanks!"  delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
                        [alert show];
                        [alert release];
                    }
                }];
            }
            else
            {
                [self followSafari]; // no accounts
            }
        }
        else
            [self followSafari]; // denied
    }];
}


- (void)setSpecifier:(PSSpecifier *)spec{
	[self loadFromSpecifier:spec];
}

- (void)loadFromSpecifier:(PSSpecifier *)spec{
	_tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, 320, 480-64) style:UITableViewStyleGrouped];
	_tableView.autoresizingMask=(UIViewAutoresizingFlexibleHeight|UIViewAutoresizingFlexibleWidth);
	[_tableView setDelegate:self];
	[_tableView setDataSource:self];

	if ([self respondsToSelector:@selector(navigationItem)])
		[[self navigationItem] setTitle:@"Octopus Keyboard"];
}

// called when returning from a child view controller
- (void)viewWillAppear:(UIView*)view 
{
    //NSLog(@"SE: View will appear");
    [self loadSettings];
}

- (id) view {
	return _tableView;
}

/*- (id) table {
	    return _tableView;
}*/

/*- (id) navigationTitle {
	if(_title)
		return _title;

	return [super navigationTitle];
}*/

-(int)prefInt:(NSString*)key default:(int)def
{
	id v = [_settings objectForKey:key];
	if (!v) return def;
	return [v intValue];
}
-(BOOL)setPrefInt:(NSString*)key value:(int)val
{
	[_settings setObject:[NSNumber numberWithInt:val] forKey:key];
}

-(void)saveSettings
{
    if ([_settings writeToFile:@PREF_FILE atomically:YES])
        NSLog(@"OK: Prefs: Settings saved");
    else
        NSLog(@"OK: Prefs: Failed to save settings");
    
    // inform the tweak
	OnSettingsChanged();
}

- (void)suspend
{
    [self saveSettings];
}


static BOOL s_doneShown = NO;
-(void)hideDone
{
    [[self navigationItem] setRightBarButtonItem:nil animated:NO];
    s_doneShown = NO;
}
- (void)onDone:(id)sender
{
    [self.view endEditing:TRUE];
    
    // save preferences
    [self saveSettings];
    
    /*UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Title" message:@"DONE!"  delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert show];
    [alert release];*/
    
    [_tableView beginUpdates];
    [_tableView endUpdates];
    
    [self hideDone];
}
-(void)showDone
{
    if (s_doneShown) return;
    
    UIBarButtonItem *anotherButton = [[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:self action:@selector(onDone:)];
    [[self navigationItem] setRightBarButtonItem:anotherButton animated:YES];
    [anotherButton release];
    
    s_doneShown = YES;
}

// text views
- (void) textFieldDidEndEditing:(UITextField *)textField {
    switch (textField.tag) {
        case 1:
            //NSLog(@"E-Mail: %@", textField.text);
            [_settings setObject:textField.text forKey:@"email"];
			textField.secureTextEntry = YES;
            break;
        default:
            NSLog(@"Unknown textfield %u: %@", textField.tag, textField.text);
            break;
    }
    [self saveSettings];
}
- (void) textFieldDidBeginEditing:(UITextField *)textField {
	textField.secureTextEntry = NO;
    [self showDone];
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{	
	return s_timeOK?5:1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    /*if (section == 0)
        return @"Donation";
    else if (section == 1)
        return @"Links";*/
    
    if (section == 1)
        return @"Octopus Keyboard";
    if (section == 2)
        return @"Settings";
    
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    if (section == 2)
        return @"You can install more dictionaries from Cydia for free or use User Dictionary only.";
    return nil;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	if (!s_timeOK) return 1;
	
    if (section == 0) // license and buttons
        return 0; // on beta 3, on release 4
    else if (section == 1) // speak
        return 1;
    else if (section == 2) // link cells
        return 3;
    else if (section == 3) // follow and web
        return 3;
    else if (section == 4) // legal
        return 1;
        
	return 0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
{
    if (indexPath.section == 0)
    {
       // if (indexPath.row == 2)
         //   return 50;
    }
    return 45;
}

-(void)switchChanged:(UISwitch*)sw
{
    if ([sw tag] == 0) 
    {
        NSLog(@"OK: Prefs: Enabled toggle = %u", sw.on);
        [_settings setObject:[NSNumber numberWithBool:sw.on] forKey:@"enabled"];
    }
    [self saveSettings];
}

static char* s7 = "d";
static char* s6 = "ire";
static char* s5 = "Exp";
static char* s4 = "od ";
static char* s3 = "eri";
static char* s2 = "a P";
static char* s1 = "Bet";

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = nil;
    CGSize sz = tableView.frame.size;
    
    if (indexPath.section == 1) // switches + speak between...
    {
        if (indexPath.row == 0)
        {
            static NSString *CellIdentifier = @"SESwitchAlternate";
            cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
            if (cell == nil) 
            {
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
                
                UISwitch *switchView = [[UISwitch alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                switchView.tag = indexPath.row;
                cell.accessoryView = switchView;
                cell.textLabel.text = @"Enabled";
                [switchView setAlternateColors:YES];
                NSNumber* h = [_settings objectForKey:@"enabled"];
                [switchView setOn:(!h || [h boolValue]) animated:NO];
                [switchView addTarget:self action:@selector(switchChanged:) forControlEvents:UIControlEventValueChanged];
                [switchView release];
            }
        }
    }
    else if (indexPath.section == 2) // switches
    {
        static NSString *CellIdentifier = @"SEMoreCell";
        cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
        if (cell == nil) 
        {
            cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier] autorelease];
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }
        
        if (indexPath.row == 0)
            cell.textLabel.text = @"Installed Dictionaries";
        else if (indexPath.row == 1)
            cell.textLabel.text = @"User Dictionary";
        else if (indexPath.row == 2)
            cell.textLabel.text = @"Options";
    }
    else if (indexPath.section == 3)
    {
        /*if (indexPath.row == 0)
        {
            static NSString *CellIdentifier = @"AEWeb";
            
            cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
            if (cell == nil) 
            {
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
                
                //UILabel* label = [[UILabel alloc] initWithFrame:CGRectMake(8,0,sz.width-35, 40)];
                cell.textLabel.font = [UIFont systemFontOfSize:15];
                cell.textLabel.numberOfLines = 0;
                //cell.textLabel.backgroundColor = [UIColor clearColor];
                cell.textLabel.textAlignment = UITextAlignmentCenter;
                cell.textLabel.text = @"Website: http://ae.k3a.me";
                
                //[cell.contentView addSubview:label];
                //[label release];
            }
        }
        else */if (indexPath.row == 0)
        {
            static NSString *CellIdentifier = @"SELink";
            cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
            if (cell == nil) 
            {
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
                
                //UILabel* label = [[UILabel alloc] initWithFrame:CGRectMake(8,0,sz.width-35, 40)];
                cell.textLabel.font = [UIFont boldSystemFontOfSize:15];
                cell.textLabel.numberOfLines = 0;
               // cell.textLabel.backgroundColor = [UIColor clearColor];
                cell.textLabel.textAlignment = UITextAlignmentCenter;
                cell.textLabel.text = @">>  Follow Me @kexik  <<";
                
                //[cell.contentView addSubview:label];
                //[label release];
            }
        }
        else if (indexPath.row == 1)
        {
            static NSString *CellIdentifier = @"SELink";
            cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
            if (cell == nil) 
            {
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
                
               // UILabel* label = [[UILabel alloc] initWithFrame:CGRectMake(8,0,sz.width-35, 40)];
                cell.textLabel.font = [UIFont boldSystemFontOfSize:15];
                cell.textLabel.numberOfLines = 0;
                //cell.textLabel.backgroundColor = [UIColor clearColor];
                cell.textLabel.textAlignment = UITextAlignmentCenter;
                cell.textLabel.text = @">>  Octopus Keyboard Website  <<";
                
                //[cell.contentView addSubview:label];
                //[label release];
            }
        }
        else if (indexPath.row == 2)
        {
            static NSString *CellIdentifier = @"SELink";
            cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
            if (cell == nil) 
            {
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
                
                //UILabel* label = [[UILabel alloc] initWithFrame:CGRectMake(8,0,sz.width-35, 40)];
                cell.textLabel.font = [UIFont boldSystemFontOfSize:15];
                cell.textLabel.numberOfLines = 0;
                //cell.textLabel.backgroundColor = [UIColor clearColor];
                cell.textLabel.textAlignment = UITextAlignmentCenter;
                cell.textLabel.text = @"Send Diagnostic Log";
                
                //[cell.contentView addSubview:label];
                //[label release];
            }
        }
    }
    else if (indexPath.section == 4)
    {
        if (indexPath.row == 0)
        {
            static NSString *CellIdentifier = @"SELegal";
            
            cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
            if (cell == nil) 
            {
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
                
                cell.textLabel.text = @"About";
                cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;//UITableViewCellAccessoryDetailDisclosureButton;
            }
        }
    }
    
    if (!cell)
    {
        static NSString *CellIdentifier = @"SADefaultCell";
        
        cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
        if (cell == nil) 
        {
            cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
            if (cell == nil) 
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
        }
    }
 
    return cell;
}

-(BOOL)downloadLicense:(NSString*)email
{
    
    return TRUE;
}

-(NSString*)aslLog
{
    NSMutableString *consoleLog = [NSMutableString string];
    
    aslclient client = asl_open(NULL, NULL, ASL_OPT_STDERR);
    
    NSTimeInterval fromTimestamp = [[NSDate date] timeIntervalSince1970]-60*60*24*10;
    char strFrom[128];
    sprintf(strFrom, "%.0f", fromTimestamp);
    
    aslmsg query = asl_new(ASL_TYPE_QUERY);
    //asl_set_query(query, ASL_KEY_SENDER, "SpringBoard", ASL_QUERY_OP_EQUAL);
    //asl_set(query, ASL_KEY_FACILITY, "com.apple.springboard");
    asl_set_query(query, ASL_KEY_TIME, strFrom, ASL_QUERY_OP_GREATER_EQUAL);
    asl_set_query(query, ASL_KEY_MSG, NULL, ASL_QUERY_OP_NOT_EQUAL);
    aslresponse response = asl_search(client, query);
    
    asl_free(query);
    
    aslmsg message;
    while((message = aslresponse_next(response)))
    {
        const char *msg = asl_get(message, ASL_KEY_MSG);
        const char *sender = asl_get(message, ASL_KEY_SENDER);
        if (msg && (!strncmp(msg, "SE: ", 4) || !strncmp(msg, "Colobus:", 8)) )
            [consoleLog appendFormat:@"%s: %s\n", sender, msg];
    }
    
    aslresponse_free(response);
    asl_close(client);
    
    return consoleLog;
}

-(BOOL)syslogEnabled
{
    NSDictionary* syslogDict = [NSDictionary dictionaryWithContentsOfFile:@"/System/Library/LaunchDaemons/com.apple.syslogd.plist"];
    if (!syslogDict)
    {
        NSLog(@"SE: Prefs: Could not open syslog daemon definition plist!");
        return NO;
    }
    
    NSArray* args = [syslogDict objectForKey:@"ProgramArguments"];
    if (!args)
    {
        NSLog(@"SE: Prefs: ProgramArguments not found in syslog daemon definition plist!");
        return NO;
    }
    
    for (unsigned idx=0; idx<[args count]; idx++)
    {
        NSString* arg = [args objectAtIndex:idx];
        if ([arg caseInsensitiveCompare:@"-bsd_out"] == NSOrderedSame && idx+1<[args count])
        {
            return [[args objectAtIndex:idx+1] isEqualToString:@"1"];
        }
    }
    
    return NO;
}

-(NSString*)syslog
{
    FILE* fp = fopen("/var/log/syslog", "rb");
    if (!fp)
    {
        NSLog(@"SE: Prefs: Failed to open syslog!");
        return nil;
    }
    
    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    
    size_t reqLen = 4000*100;
    if (len < reqLen) reqLen = len;
    
    // read into buf
    fseek(fp, len-reqLen, SEEK_SET);
    char* buf = (char*)malloc(reqLen+1);
    fread(buf, 1, reqLen, fp);
    buf[reqLen]=0;
    
    NSMutableString* ret = [NSMutableString string];
    char* line = strtok(buf, "\n");
    while (line) 
    {
        if (strstr(line, "SpringBoard") || strstr(line, "Preferences") || strstr(line, "ReportCrash"))
            [ret appendFormat:@"%s\n", line];
        
        line = strtok(NULL, "\n");
    }
    
    // clean
    free(buf);
    fclose(fp);
    
    return ret;
}

-(NSString*)latestSpringBoardCrash
{
    return [NSString stringWithContentsOfFile:@"/var/mobile/Library/Logs/CrashReporter/LatestCrash-SpringBoard.plist" encoding:NSUTF8StringEncoding error:nil];
}

-(NSString*)listOfPackages
{
    [_softVersion release];
    _softVersion = nil;
    
    FILE* fp = fopen("/var/lib/dpkg/status", "rb");
    if (!fp)
    {
        NSLog(@"SE: Prefs: Failed to open the list of apt packages!");
        return nil;
    }
    else
    {
        NSMutableString* ret = [NSMutableString string];
        
        char line[512];
        int linelen = 0;
        bool packageParsed=false;
        char package[256];
        
        while(!feof(fp))
        {
            fgets(line, 510, fp);
            linelen = strlen(line);
            if (linelen < 3) continue; // probably a new line only => skip
            
            // strip \n and \r in the end
            if (line[linelen-2]=='\r' || line[linelen-2]=='\n')
            {
                line[linelen-2] = 0;
                linelen-=2;
            }
            else if (line[linelen-1]=='\r' || line[linelen-1]=='\n')
            {
                line[linelen-1] = 0;
                linelen-=1;
            }
            line[linelen] = 0; // terminate
            
            // now we have a line
            if (!packageParsed && !strncmp(line, "Package: ", 9))
            {                
                strncpy(package, &line[9], 255);
                package[255]=0;
                packageParsed = true;
            }
            else if (packageParsed && !strncmp(line, "Version: ", 9))
            {
                packageParsed = false;
                char ver[16];
                strncpy(ver, &line[9], 15);
                ver[15]=0;
                
                if (!strcmp(package, "me.k3a.octopus"))
                    _softVersion = [[NSString alloc] initWithUTF8String:ver];
                
                [ret appendFormat:@"%s: %s\n", package, ver];
            }
            
        }
        
        fclose(fp);
        return ret;
    }
}

-(NSString*)settingsFile
{
    return [NSString stringWithContentsOfFile:@PREF_FILE usedEncoding:nil error:nil];
}

-(void)sendDiagnosticLogs
{
    static bool askedForSyslog = false;
    
    BOOL hasSyslog = [self syslogEnabled];
    
    if (!hasSyslog && !askedForSyslog)
    {
        askedForSyslog = true;

        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Syslog not enabled" message:@"If you are reporting a crash, syslog may be useful. Do you want to get more info about syslog?"  delegate:self cancelButtonTitle:@"Report anyway" otherButtonTitles:@"Yes",nil];
        alert.tag = 666;
        [alert show];
        [alert release];
        
        return;
    }
    
    // send diagnostic logs
    MFMailComposeViewController *mail = [[[MFMailComposeViewController alloc] init] autorelease];
    mail.mailComposeDelegate = self;
    
    [mail setToRecipients:[NSArray arrayWithObject:@"ok@k3a.me"]];
    [mail setMessageBody:@"Please briefly describe your problem or steps to reproduce it. If you asked for help via Twitter, please specify your username.\r\n\r\n\r\n(If you do not write anything, it will be ignored.)\r\n\r\n" isHTML:NO];
    
    NSString* syslog = [self syslog];
    if (hasSyslog) 
    {
        [mail addAttachmentData:[syslog dataUsingEncoding:NSUTF8StringEncoding] mimeType:@"text/plain" fileName:@"system.log"];
    }
    
    NSString* aslLog = [self aslLog];
    if (aslLog)
    {
        [mail addAttachmentData:[aslLog dataUsingEncoding:NSUTF8StringEncoding] mimeType:@"text/plain" fileName:@"asl.log"];
    }
    
    NSString* latestCrash = [self latestSpringBoardCrash];
    if (latestCrash)
    {
        [mail addAttachmentData:[latestCrash dataUsingEncoding:NSUTF8StringEncoding] mimeType:@"text/plain" fileName:@"LatestCrash-SpringBoard.plist"];
    }
    
    NSString* packages = [self listOfPackages];
    if (packages)
    {
        [mail addAttachmentData:[packages dataUsingEncoding:NSUTF8StringEncoding] mimeType:@"text/plain" fileName:@"packages.txt"];
    }
    
    NSString* settings = [self settingsFile];
    if (settings)
    {
        [mail addAttachmentData:[settings dataUsingEncoding:NSUTF8StringEncoding] mimeType:@"text/plain" fileName:@"settings.plist"];
    }
    
    [mail setSubject:[NSString stringWithFormat:@"Diagnostic Logs - %@", _softVersion]];
    
    [self presentModalViewController:mail animated:YES];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView.tag == 666)
    {
        if (buttonIndex == 0)
        {
            [self sendDiagnosticLogs];
        }
        else if (buttonIndex == 1)
        {
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://ok.k3a.me/syslog.html"]];
        }
    }
}

-(BOOL)checkEmail:(NSString*)checkString
{
   BOOL stricterFilter = YES; // Discussion http://blog.logichigh.com/2010/09/02/validating-an-e-mail-address/
   NSString *stricterFilterString = @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
   NSString *laxString = @".+@.+\\.[A-Za-z]{2}[A-Za-z]*";
   NSString *emailRegex = stricterFilter ? stricterFilterString : laxString;
   NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", emailRegex];
   if (![emailTest evaluateWithObject:checkString])
    {
        AlertView(@"Please Enter Valid E-Mail", @"Please enter an email for license identification. We don't allow nicknames anymore to prevent abuse. If you previously used a nickname, please use your PayPal email address if you have one, otherwise contact support at se@k3a.me.");
        return NO;
    }
    else
        return YES;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    if (indexPath.section == 0)
    {
        NSString* email = nil;
        if (indexPath.row == 2 || indexPath.row == 3)
        {
            [self.view endEditing:TRUE];
            
            email = [_settings objectForKey:@"email"];
            if ([email length] == 0)
            {
                AlertView(@"E-Mail", @"Please enter your e-mail address.");
                return;
            }
        }
            
        if (indexPath.row == 2) //download the license
        {
			if (![self checkEmail:email])
				return;

            [self downloadLicense:email];
            return;
        }
        else if (indexPath.row == 3)
        {
			if (![self checkEmail:email])
				return;

            // check that cookies are enabled
            NSDictionary* webf = [NSDictionary dictionaryWithContentsOfFile:@"/var/mobile/Library/Preferences/com.apple.WebFoundation.plist"];
            NSString* acceptCookies = [webf objectForKey:@"NSHTTPAcceptCookies"];
            if (acceptCookies && ![acceptCookies isEqualToString:@"always"])
            {
                AlertView(@"Cookies not enabled", @"Please set \"Accept Cookies\" in iOS Settings->Safari to \"Always\" even if using a different browser.");
                return;
            }
            
            NSString* followUrl = [NSString stringWithFormat:@"http://ok.k3a.me/accounts/buy?email=%@", email];
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:followUrl]];
            
            /*K3ASEPrefsBuyController* ctrl = [[[K3ASEPrefsBuyController alloc] init] autorelease];
            ctrl.parentController = self; 
            ctrl.rootController = self.rootController;
            [ctrl startLoadingForEmail:email];
            [self pushController:ctrl];*/
        }
    }
    else if (indexPath.section == 1) // from to hours
    {        
        
    }
    else if (indexPath.section == 2) // what to speak (switches)
    {
        if (indexPath.row == 0)
            [self pushController: [[[OKDicts alloc] init] autorelease] ];
        else if (indexPath.row == 1)
            [self pushController:[OKUserDictCtrl controlerWithParent:self]];
        else if (indexPath.row == 2)
            [self pushController:[OKSpecifierCtrl specifierCtrl:@"Options" parent:self]];
    }
    else if (indexPath.section == 3) // follow
    {
        if (indexPath.row == 0)
            [self follow];
        else if (indexPath.row == 1)
        {
            NSString* strUrl = @"http://ok.k3a.me/";
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:strUrl]];
        }
        else if (indexPath.row == 2)
        {
            [self sendDiagnosticLogs];
        }
    }
    else if (indexPath.section == 4) // legal
    {
        [self pushController: [[[OKLegalController alloc] init] autorelease] ];
    }
}

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
    [self dismissModalViewControllerAnimated:YES];
}

@end



static NSString* MainLangPart(NSString* lang)
{
    NSArray* l = [lang componentsSeparatedByString:@"-"];
    if ([l count] == 1) l = [lang componentsSeparatedByString:@"_"];
    return [l objectAtIndex:0];
}















// vim:ft=objc
