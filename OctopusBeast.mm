//
//  OctopusBeast.m
//  Octopus
//
//  Created by K3A on 5/20/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//
#include <objc/runtime.h>
#import <UIKit/UITextInputPrivate.h>
#import <UIKit/UIKeyboardImpl.h>
#include <string>

enum sandbox_filter_type {
	SANDBOX_FILTER_NONE = 0,
	SANDBOX_FILTER_PATH = 1,
	SANDBOX_FILTER_GLOBAL_NAME =2,
	SANDBOX_FILTER_LOCAL_NAME = 3,
	SANDBOX_CHECK_NO_REPORT = 0x40000000
};
extern "C" int sandbox_check(pid_t pid, const char *operation, int type, ...);

#import "OctopusBeast.h"

void OLog(int level, const char* format, ...)
{
#ifndef DEBUG
	if (level>1) return;
#endif
	
    std::string strf(format);
    strf.insert(0, "OK INF: ");
    strf.append("\n");
    
    va_list args;
    va_start( args, format );
    NSLogv([NSString stringWithUTF8String:strf.c_str()], args);
    va_end( args );
}

void OErr(const char* format, ...)
{
    std::string strf(format);
    strf.insert(0, "OK ERR: ");
    strf.append("\n");
    
    va_list args;
    va_start( args, format );
    NSLogv([NSString stringWithUTF8String:strf.c_str()], args);
    va_end( args );
}

static mach_port_t GetServerPort()
{
    kern_return_t           kr;
	static mach_port_t		bsPort = 0;
    mach_port_t		srvPort = 0;
	
	if (bsPort == 0)
	{
		kr = task_get_bootstrap_port( mach_task_self(), &bsPort );
        if (kr != MACH_MSG_SUCCESS)
        {
            OErr("Failed to get the boostrap port!");
            //mach_error("task_get_bootstrap_port:", kr);
            return 0;
        }
    }
    
    if (srvPort == 0)
    {
		if (IS_IOS7)
		{
			int sandbox_result = sandbox_check(getpid(), "mach-lookup", SANDBOX_FILTER_LOCAL_NAME | SANDBOX_CHECK_NO_REPORT, "me.k3a.octopusd");
			if (sandbox_result)
			{
				OErr("Mach lookup disabled by seatbelt");
				return 0;
			}
		}

        kr = bootstrap_look_up( bsPort, "me.k3a.octopusd", &srvPort );
        if (kr != MACH_MSG_SUCCESS)
        {
            OErr("Could not lookup the service, is daemon running?");
            //mach_error("Could not lookup the service, is daemon running?", kr);
            return 0;
        }
    }
    
	return srvPort;
}

static void printKBTree(id tree, NSString* indent)
{
    if (strcmp(class_getName([tree class]), "UIKBTree")) return;
    NSDictionary* props = [tree properties];
    
    NSLog(@"%@-[disp:%@, rep:%@, shap:%@] %@", indent,
          [props objectForKey:@"KBdisplayString"], [props objectForKey:@"KBrepresentedString"], 
          [props objectForKey:@"KBshape"], [tree name]);
    
    indent = [indent stringByAppendingString:@"  "];
    for (id t in [tree subtrees])
        printKBTree(t, indent);
}

NSDictionary* s_prefs = nil;

static BOOL prefsLoad()
{
	if (s_prefs) [s_prefs release];
	s_prefs = [[NSDictionary alloc] initWithContentsOfFile:@PREF_FILE];
	return s_prefs!=nil;
}

static NSString* prefString(NSString* key, NSString* def)
{
	NSString* str = [s_prefs objectForKey:key];
	if (!str) return def;
	
	if ([str isKindOfClass:[NSString class]])
		return str;
	else 
		return [str description];
}

static int prefInt(NSString* key, int def)
{
	id v = [s_prefs objectForKey:key];
	if (!v) return def;
	return [v intValue];
}

static void prefsLoadApply(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo)
{
	OLog(1, "Client is reloading prefs...");
	prefsLoad();
	
	[[OctopusBeast inst] applyPrefs];
}

@implementation OctopusBeast

static OctopusBeast* s_inst = nil;
+(OctopusBeast*)inst
{
	return s_inst;
}

@synthesize keyplane, input, traits;

static UIColor* Int2Color(int c)
{
    if (c == 0)
        return [UIColor blackColor];
    else if (c == 1)
        return [UIColor darkGrayColor];
    else if (c == 2)
        return [UIColor lightGrayColor];
    else if (c == 3)
        return [UIColor whiteColor];
    else if (c == 4)
        return [UIColor grayColor];
    else if (c == 5)
        return [UIColor redColor];
    else if (c == 6)
        return [UIColor greenColor];
    else if (c == 7)
        return [UIColor blueColor];
    else if (c == 8)
        return [UIColor cyanColor];
    else if (c == 9)
        return [UIColor yellowColor];
    else if (c == 10)
        return [UIColor magentaColor];
    else if (c == 11)
        return [UIColor orangeColor];
    else if (c == 12)
        return [UIColor purpleColor];
    else if (c == 13)
        return [UIColor brownColor];
    else if (c == 14)
        return [UIColor clearColor];
    
    return [UIColor blackColor];
}

-(void)applyPrefs
{
	_swipeLength = prefInt(@"swipeLength", 1);
	_autocapitalization = prefInt(@"autocapitalization", 1) != 0;
	_enabled = prefInt(@"enabled", 1) != 0;
	_downPlural = prefInt(@"downplural", 1) != 0;
	_abovekeys = prefInt(@"abovekeys", 1) != 0;
    _minChars = prefInt(@"minChars", 0);
    
    // update colors
    [_textColor release];
    [_outlineColor release];
    _textColor = [Int2Color(prefInt(@"textColor", 0)) retain];
    _outlineColor = [Int2Color(prefInt(@"outlineColor", 3)) retain];
	
	oReloadPrefs(GetServerPort());
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) 
    {
		/*if (GetServerPort() == 0)
		{
			[self release];
			return nil;
		}*/

		s_inst = self;
		prefsLoad();
		[self applyPrefs];
		
        self.autoresizingMask = 0xFFFFFFFF;
        
        self.backgroundColor = [UIColor clearColor];
		self.input = @"";
		_inputMode = [NSString new];
        _input = [NSMutableString new];
		_keysDrawn = [NSMutableSet new];
		_isPad = isPad();
        
        _suggs_struct.count = 0;
        for (int i=0; i<MAX_SUGGS; i++)
            _suggs[i] = [NSMutableString new];
        
        self.userInteractionEnabled = NO;
		
		CFNotificationCenterAddObserver(CFNotificationCenterGetDarwinNotifyCenter(), NULL, prefsLoadApply, CFSTR("me.k3a.OctopusKeyboard/reloadPrefs"), NULL, CFNotificationSuspensionBehaviorCoalesce);
    
		hasPendingChanges=NO;
		processingUpdate=NO;
	}
    return self;
}

-(void)dealloc
{
	s_inst = nil;
	
	[_keysDrawn release];
    [_prevWord release];
    [_inputMode release];
    [_input release];
    for (int i=0; i<MAX_SUGGS; i++)
        [_suggs[i] release];
    
    [_textColor release];
    [_outlineColor release];
    
    [super dealloc];
}

-(int)swipeLength
{
	return _swipeLength;
}
-(BOOL)pluralOnSwipeDown
{
	return _downPlural;
}

// returns TRUE if no intersecting line found and adds that line to the list
-(BOOL)checkAndInsertLineX1:(float)x1 X2:(float)x2 Y:(float)y
{
	sLine inpLine(x1, x2, y);
	BOOL colides = NO;
	
	for(LineVector::const_iterator it = _lines.begin(); it != _lines.end(); it++)
	{
		const sLine& ln = *it;
		if (ln.CollidesWith(inpLine))
		{
			colides = YES;
			break;
		}
	}
	
	if (!colides)
	{
		_lines.push_back(inpLine);
		return TRUE;
	}
	else 
		return FALSE;
}

static BOOL digitsOnly(NSString* objcstr)
{
    if (!objcstr) return NO;
    const char* str = [objcstr UTF8String];
    for (unsigned i=0; i<strlen(str); i++)
    {
        if (!isdigit(str[i]))
            return NO;
    }
    return YES;
}

-(void)drawKBTree:(id)tree
{
	if (GetServerPort() == 0 || !_enabled) return;

    if (strcmp(class_getName([tree class]), "UIKBTree")) return;
    NSDictionary* props = [tree properties];
    
	NSString* key = [props objectForKey:@"KBrepresentedString"];
	if ([_keysDrawn containsObject:key]) return; // key already drawn
	if (key) [_keysDrawn addObject:key];
	 
    //NSLog(@"KEY '%@'", key);
    
	CGContextRef context = UIGraphicsGetCurrentContext();
    
    static UIFont* font = [[UIFont systemFontOfSize:isPad()?14:12] retain];
    static UIFont* fontInp = [[UIFont boldSystemFontOfSize:isPad()?14:12] retain];
    CGColor* whiteColor = [_outlineColor CGColor];
    CGColor* blackColor = [_textColor CGColor];
    static CGColor* redColor = [[[UIColor colorWithRed:.5f green:0 blue:0 alpha:1] retain] CGColor];
    
    // compute length of input
    NSString* inp = _input;//TODO:ios7 not sure if _input is a good alternative
	if (!IS_IOS7) inp = [self inputString]; // this was ok on ios6
    unsigned inpLen = [inp length];
    
	// get completed word
    NSString* sugg; BOOL isCorrection = FALSE;
	if (key && [key length] == 1 /*keys are one-char only*/ && (sugg = [self suggestionForKey:key isCorrection:&isCorrection]))
	{
        CGRect frame = [[props objectForKey:@"KBshape"] frame];
        CGPoint kpos = frame.origin; kpos.y -= (_abovekeys?12:1) + self.frame.origin.y;
        float ksize = frame.size.width;
        unsigned suggLen = [sugg length];
        unsigned postLen = suggLen - inpLen;
        
        // TODO: becaue kptapi does not report it correctly,
        // use prefix comparison to detect whether the sugg is a correction
        if (inpLen>0 && suggLen >= inpLen)
        {
            isCorrection = ![[sugg lowercaseString] hasPrefix:[inp lowercaseString]];
            //NSLog(@"NOT COMPARE '%@' '%@' range 0, %d", inp, sugg, inpLen);
			
			// use the prefix from suggestion (to fix cases)
			inp = [sugg substringToIndex:[inp length]];
        }
		
		// compute pixel size of input string
		float inpSize = 0;
		if (inpLen) inpSize = [inp sizeWithFont:fontInp].width;
        
        if (isCorrection/*!prefixTheSame && suggLen>0*/) // draw autocorrected word sugg
        {
            float totalSize = [sugg sizeWithFont:font].width;
            float inpPos = kpos.x + ksize/2 - totalSize/2;
            
			if ([self checkAndInsertLineX1:inpPos X2:inpPos+totalSize Y:kpos.y])
			{
				// Draw outlined text
				CGContextSetTextDrawingMode(context, kCGTextStroke);
				CGContextSetLineWidth(context,2);
				CGContextSetStrokeColorWithColor(context, whiteColor);
				[sugg drawAtPoint:CGPointMake(inpPos, kpos.y) withFont:font];
				
				// Draw filled text
				CGContextSetTextDrawingMode(context, kCGTextFill);
				CGContextSetFillColorWithColor(context, redColor);
				[sugg drawAtPoint:CGPointMake(inpPos, kpos.y) withFont:font];
			}
        }
        else if (postLen>0) // draw prefix from inp + suggestion from sugg
        {
            
            // get sugg postfix
            NSString* suggPost = [sugg substringFromIndex:inpLen];
            
            // compute sugg font size
            float suggSize = [suggPost sizeWithFont:font].width;
            float totalSize = inpSize + suggSize;
            
            float inpPos = kpos.x + ksize/2 - totalSize/2;
            float suggPos = inpPos + inpSize;
			
			if (_rightToLeft && !digitsOnly(sugg))
			{
				suggPos = kpos.x + ksize/2 - totalSize/2;
				inpPos = suggPos + totalSize - inpSize;
			}
            
            //NSLog(@"INP '%@' SUGG: '%@' post: '%@' totalsize = %.0f", inp, sugg, suggPos, totalSize);
            //NSLog(@"ORIGIN [%.0f,%.0f;%.0f] Draw [%.0f,%.0f]", kpos.x, kpos.y, ksize, inpPos, kpos.y);
            
			if ([self checkAndInsertLineX1:inpPos X2:inpPos+totalSize Y:kpos.y])
			{
				// input part
				if (inpLen>0)
				{
					UIFont* fnt = font;
					if (prefInt(@"boldtext",1) != 0) fnt = fontInp;
					
					// Draw outlined text
					CGContextSetTextDrawingMode(context, kCGTextStroke);
					CGContextSetLineWidth(context,2);
					CGContextSetStrokeColorWithColor(context, whiteColor);
					[inp drawAtPoint:CGPointMake(inpPos, kpos.y) withFont:fnt];
					// draw underline
					/*CGContextSetLineWidth(context, 1);
					CGContextMoveToPoint(context, inpPos, kpos.y+10);
					CGContextAddLineToPoint(context, inpPos + inpSize, kpos.y+10);
					CGContextStrokePath(context);*/

					// Draw filled text
					CGContextSetTextDrawingMode(context, kCGTextFill);
					CGContextSetFillColorWithColor(context, blackColor);
					[inp drawAtPoint:CGPointMake(inpPos, kpos.y) withFont:fnt];
					
				}
				
				// suggestion part
				{
					// Draw outlined text
					CGContextSetTextDrawingMode(context, kCGTextStroke);
					CGContextSetLineWidth(context,2);
					CGContextSetStrokeColorWithColor(context, whiteColor);
					[suggPost drawAtPoint:CGPointMake(suggPos, kpos.y) withFont:font];
					
					// Draw filled text
					CGContextSetTextDrawingMode(context, kCGTextFill);
					CGContextSetFillColorWithColor(context, blackColor);
					[suggPost drawAtPoint:CGPointMake(suggPos, kpos.y) withFont:font];
					
				}
			}
            
        }
	}
    
    for (id t in [tree subtrees])
        [self drawKBTree:t];
}

-(void)printKeyplane
{
    printKBTree([self keyplane], @"");
}

-(BOOL)canComplete
{
	if (GetServerPort() == 0 || !_enabled) return NO;
	
	BOOL secureTextEntry = NO;
	if ([self.traits respondsToSelector:@selector(isSecureTextEntry)])
		secureTextEntry = [self.traits isSecureTextEntry];
    
	UIKeyboardType type = [self.traits keyboardType];
	
	return !secureTextEntry && 
    (type == UIKeyboardTypeDefault || type == UIKeyboardTypeASCIICapable || type == UIKeyboardTypeTwitter) /*&&
    ([self.traits autocorrectionType] != UITextAutocorrectionTypeNo)*/;
}
-(BOOL)shouldCapitalize
{
	if (!_autocapitalization) return NO;
	
	if ([self.traits respondsToSelector:@selector(autocapitalizationType)])
		return [self.traits autocapitalizationType] == UITextAutocapitalizationTypeSentences || [self.traits autocapitalizationType] == UITextAutocapitalizationTypeWords;
}
-(void)drawRect:(CGRect)rect
{
	if (![self canComplete]) return;
	
	_lines.clear();
    [_keysDrawn removeAllObjects];
	[self drawKBTree:self.keyplane];
}
-(void)releaseCompletionEngine
{
	OLog(0, "Client shutdown");
    
    oProfileSave(GetServerPort());
    
    /*db_refresh();
     db_sync();
     db_shutdown();*/
}
-(void)initCompletionEngine
{
    if (![_inputMode length]) return;
    
	OLog(0, "Client init (mode %s)", [_inputMode UTF8String]);
    
    if (GetServerPort() == 0)
	{
        OErr(0, "Error connecting to the daemon!!");
		return;
	}
    
    // clearing input may be needed, but normally input should be set by 
    // UIKeyboardImpl updateForChangedSelection
    
}
-(void)setInputMode:(NSString*)inpM
{
	if (inpM && ![inpM isEqualToString:_inputMode])
	{
		[_inputMode release];
		_inputMode = [inpM copy];
        
		// is right-to-left language?
		_rightToLeft = [inpM hasPrefix:@"he"] || [inpM hasPrefix:@"ar"];
		
		[self releaseCompletionEngine];
		[self initCompletionEngine];
	}
}
-(NSString*)inputMode
{
	return _inputMode;
}

-(NSString*)inputString
{
    return _input;
}
-(void)updateSuggestions {
	
	if (!_enabled) { _numSuggs=0; return; } // TODO: also delete existing suggs
	if (GetServerPort() == 0) { _numSuggs=0; return; } // no daemon conn
	
	//
	if (processingUpdate) {
		hasPendingChanges=YES;
		return;
	}
	processingUpdate=YES;
	//
	self.hidden=YES;
	static Class _UIKeyboardImpl = objc_getClass("UIKeyboardImpl");
	UIKeyboardImpl* ki = [_UIKeyboardImpl sharedInstance];
    id inpd = [ki inputDelegate];

	// HACK: set input from input manager directly
	UIKeyboardInputManager* im = [ki inputManager];
    NSString* wstr = _input;//TODO:ios7 not sure if this is a good alternative
	if (!IS_IOS7) wstr = [im inputString]; // this was fine on ios6
    if (wstr) [_input setString:wstr];
    
    // check if input length is long enough
    if ([wstr length] < _minChars)
    {
        OLog(0, "Input too short");
        processingUpdate = NO;
        _numSuggs = 0;
        return;
    }

    UITextRange* selRange = [inpd selectedTextRange];
	UITextRange* wordRange = nil;
    if (selRange)
    {
        wordRange = [inpd _rangeOfEnclosingWord:[selRange start]];
        if (!wordRange) wordRange = selRange;
	}

    OLog(3, "UPDATING SUGGS FOR INPUT WORD '%s'", [_input UTF8String]);
    
    // should capitalize?
    _capitalizeWord = NO;
    if (wordRange)
    {
        NSString* context = _input;//TODO:ios7 not sure if that is a good alternative
		if (!IS_IOS7) context = [ki currentInputContextFromInputDelegateWithWordRange:wordRange];
        if (context)
        {
			int offset = [inpd offsetFromPosition:[wordRange end] toPosition:[selRange start]];
			[self setContext:context word:_input offset:offset];

            const char* cctx = [context UTF8String];
            unsigned cctxLen = strlen(cctx);
            for (int i=cctxLen-1; i>=0; i--)
            {
                if (cctx[i] == ' ')
                    continue;
                else if (cctx[i] == '.' || cctx[i] == '!' || cctx[i] == '?')
                {
                    _capitalizeWord = [self shouldCapitalize]; // capitalize if possible
                    break;
                }
                else
                    break;
            }
        }
		if (!context || [context length] == 0)
			_capitalizeWord = [self shouldCapitalize]; // no context -> capitalize if possible
    }
	else
		_capitalizeWord = [self shouldCapitalize]; // no selected range -> capitalize if possible
    OLog(3, "CAPITALIZE: %s", _capitalizeWord?"YES":"NO");
    
    if (_capitalizeWord) 
		[_input setString:[_input capitalizedString]];
	else if ([_input length]>0) 
	{
		// maybe user started the word with uppercase?
		NSString *character = [_input substringWithRange:NSMakeRange(0, 1)];
		_capitalizeWord = [character isEqualToString:[character uppercaseString]];
	}
	
    [self performSelectorInBackground:@selector(updateSuggestionsBg) withObject:nil];
}
-(void)updateSuggestionsBg {
   	_suggs_struct.count = 0; 
    oSuggGetSuggestions(GetServerPort(), &_suggs_struct);
    _numSuggs = _suggs_struct.count;
	[self performSelectorOnMainThread:@selector(updateSuggestionsRest) withObject:nil waitUntilDone:NO];
}
-(void)updateSuggestionsRest {
	
	/*if (hasPendingChanges) {
		hasPendingChanges=NO;
		processingUpdate=NO;
		[self updateSuggestions];
		return;
	}//*/
	
    for (int i=0; i<_suggs_struct.count; i++)
    {
        NSString* suggStr = [NSString stringWithUTF8String:_suggs_struct.suggs[i].word];
		if (!suggStr) suggStr = @"";

		// fix case where there is "@" or "#" at the beginning of input buffer
		//if ([_input hasPrefix:@"@"])
		//	suggStr = [NSString stringWithFormat:@"@%@", suggStr];
		//else if ([_input hasPrefix:@"#"])
        //    suggStr = [NSString stringWithFormat:@"#%@", suggStr];
        
		// caps lock?
		if ([[UIKeyboardImpl sharedInstance] isShiftLocked])
			[_suggs[i] setString:[suggStr uppercaseString]];
		else 
		{
			if (_capitalizeWord)
				[_suggs[i] setString:[suggStr capitalizedString]];
			else
				[_suggs[i] setString:suggStr];
		}
		
        _isCorrection[i] = (_suggs_struct.suggs[i].type & ST_ERRORCORRECTION) || 
							(_suggs_struct.suggs[i].type & ST_PROXIMITYSUGGESTION);
		
		OLog(3,"- %s%s", [_suggs[i] UTF8String], _isCorrection[i]?" (corr)":"");
    }
    //[self performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:NO];
    if (hasPendingChanges) {
		hasPendingChanges=NO;
		processingUpdate=NO;
		[self updateSuggestions];
		return;
	}
	[self setNeedsDisplay];
	self.hidden=NO;
	processingUpdate=NO;
}
-(void)inputAdd:(NSString*)str
{
	if (GetServerPort() == 0 || !_enabled) return;
    if (!str || ![str length]) return;

	// prevent suggestins looking as corrections when there is @ or # at the beginning of input buffer
	if (![_input length] && ([str isEqualToString:@"#"] || [str isEqualToString:@"@"])) return;
    
    OLog(3, "INPUT ADD %s", [str UTF8String]);
    
    const char* cstr = [str UTF8String];
    
    // append fake space after punctuations (just in case)
    bool clear = false;
    if (cstr && (*cstr == '.' || *cstr == ',' || *cstr == '!' || *cstr == '?' /*|| *cstr == '\"' || *cstr == ':'*/))
    {
        str = [str stringByAppendingString:@" "];
        clear = true;
    }
    
    [_input appendString:str];
    oInputInsertString(GetServerPort(), [str UTF8String], CM_NONE, false);
    
    if (cstr && (clear || *cstr == ' ' || *cstr == '\r' || *cstr == '\n'))
        [self inputClearWord];
    
    [self updateSuggestions];
}
-(void)inputClearWord
{
    [_input setString:@""];
}
-(void)inputClear
{
    OLog(3, "INP CLEAR");
    
    [self inputClearWord];
    oInputClear(GetServerPort()); 
    /*if (_prevWord) 
    {
        char phrase[1024];
        sprintf(phrase, "%s ", [_prevWord UTF8String]);
        oInputInsertString(GetServerPort(), phrase, CM_NONE, false);
    } */
    
    [self updateSuggestions];
}
-(void)inputSet:(NSString*)str
{
	if (GetServerPort() == 0 || !str || !_enabled) return;

    [_input setString:str];
    oInputClear(GetServerPort()); 
    oInputInsertString(GetServerPort(), [str UTF8String], CM_NONE, false);
}
-(void)setContext:(NSString*)ctx word:(NSString*)word offset:(int)offset
{
	if (GetServerPort() == 0 || !_enabled) return;

    oInputClear(GetServerPort()); 
    
    int begOff = [word length]+offset;
    OLog(3, "CONTEXT WORD '%s' begOff %d", [word UTF8String], begOff);
    if (begOff > 0 && begOff <= [word length])
        [_input setString:[word substringWithRange:NSMakeRange(0, begOff)]];
    else
        [_input setString:@""];
    
    oInputInsertString(GetServerPort(), [[NSString stringWithFormat:@"%@%@", ctx, word] UTF8String], CM_NONE, false);
    oInputCursorMove(GetServerPort(), SO_END, offset);
}
// original accept word (just insert)
-(void)acceptWord:(NSString*)w
{
    if (![self canComplete]) return;
    
    OLog(3,"ORIG ACCEPT WORD");
    
    //TODO: here I suppose that the user wrote complete word, in this case, only thing needed is just send space to the daemon.
    // If the input was IOS autocompletion or simply not complete, I would need to replace the current word with this one in the daemon.
    
	if (prefInt(@"learn",1)!=0)
		oInputLearn(GetServerPort()); // learn the current buffer
    oInputInsertString(GetServerPort(), [@" " UTF8String], CM_NONE, false);
    
    //[_prevWord release];
    //_prevWord = [w copy];
    //[self inputClear];
}
-(NSString*)acceptWordFromSuggestionKey:(NSString *)k
{
	OLog(3, "acceptWordFromSuggestionKey - canComplete %s longPressed %s", [self canComplete]?"y":"n", _longPressed?"y":"n");
    if (![self canComplete]) return nil;
	if (_longPressed) return nil;
    
    BOOL isCorrection = FALSE;
    int suggIdx = [self suggestionIndexForKey:k];
    if (suggIdx == -1) return nil;
    
    NSString* sugg = _suggs[suggIdx];
    NSString* suggPost = nil;
    
    if (sugg)
    {
        OLog(3, "ACCEPT FROM SUGG WITH KEY %s => '%s'", [k UTF8String], [sugg UTF8String]);
        
        unsigned inpLen = [_input length];
        
       /* if ([sugg length]>inpLen)
            suggPost = [sugg substringFromIndex:inpLen];*/
        suggPost = [[sugg copy] autorelease];

        // send sugg insert to the daemon
        oInputInsertSugg(GetServerPort(), _suggs_struct.set, _suggs_struct.suggs[suggIdx].ident, true);
        [self updateSuggestions];
        
        // clear our internal buffer
        [_input setString:@""];
    }
    
    return suggPost;//[suggPost stringByAppendingString:@" "]; //TODO: appending spaces!
}
-(void)inputBackspace 
{
    if ([_input length] == 0) 
	{	
		/*static Class _UIKeyboardImpl = objc_getClass("UIKeyboardImpl");
        UIKeyboardImpl* ki = [_UIKeyboardImpl sharedInstance];
        UIKeyboardInputManager* im = [ki inputManager];

		NSString* wstr = [im inputString];
        if (wstr) [_input setString:wstr];
		*/
		[self updateSuggestions];
		return;
	}

    OLog(3, "BACKSPACE");
    
    oInputRemove(GetServerPort(), 1, 0);
    [_input deleteCharactersInRange:NSMakeRange([_input length]-1, 1)];
 
    [self updateSuggestions];
}

-(int)suggestionIndexForKey:(NSString*)k
{
	if (processingUpdate) return -1;
	
    unsigned inpLen = [_input length];

    for (int i=0; i<_numSuggs; i++)
    {
        unsigned suggLen = [_suggs[i] length];
        if (suggLen <= inpLen) continue;
        
        NSString* nextSuggChar = [_suggs[i] substringWithRange:NSMakeRange(inpLen, 1)];
        //NSLog(@"suggestionIndexForKey '%s' '%s'", nextSuggChar, k);
		if ([nextSuggChar compare:k options:NSCaseInsensitiveSearch|NSDiacriticInsensitiveSearch|NSWidthInsensitiveSearch] == NSOrderedSame)
            return i;
    }
    return -1;
}

-(NSString*)suggestionForKey:(NSString*)k isCorrection:(BOOL*)corr
{
    unsigned inpLen = [_input length];
    int idx = [self suggestionIndexForKey:k];
    if (idx == -1) return nil;
    
    if (corr) *corr = _isCorrection[idx];
    //NSLog(@"nextSugg char '%@' for key '%@' => %@", nextSuggChar, k, _suggs[i]);
    return _suggs[idx];
}

-(void)longPress
{
	_longPressed = YES;
}
-(void)resetLongPress
{
	_longPressed = NO;
}
-(BOOL)isLongPressed
{
	return _longPressed;
}

@end




















