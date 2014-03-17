//
//  OctopusBeast.h
//  Octopus
//
//  Created by K3A on 5/20/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "octopuscore/OctopusDaemon/octopus.h"
#include <vector>

#define MAX_SUGGS 12
#define PREF_FILE "/var/mobile/Library/Preferences/me.k3a.OctopusKeyboard.plist"

#define UIKeyboardTypeTwitter 9

struct sLine
{
	float x1;
	float x2; // must be higher than x1
	int y;

	sLine(float _x1, float _x2, int _y)
	{
		x1 = _x1; x2 = _x2; y = _y;
	}
	
	bool CollidesWith(const sLine& ln)const
	{
		return y == ln.y && ( (ln.x1 > x1 && ln.x1 < x2) || (x1 > ln.x1 && x1 < ln.x2) );
	}
};
typedef std::vector<sLine> LineVector;

void OLog(int level, const char* format, ...);
void OErr(const char* format, ...);

@interface OctopusBeast : UIView {
    NSString* _inputMode;
	BOOL _rightToLeft;
    NSMutableString* _input;
    NSString* _prevWord;
    
	NSMutableSet* _keysDrawn;
    NSMutableString* _suggs[MAX_SUGGS];
    sSuggestions _suggs_struct;
    bool _isCorrection[MAX_SUGGS];
    unsigned _numSuggs;
    
    BOOL _capitalizeWord;
    BOOL _serverOK;
	
	int _swipeLength;
	bool _autocapitalization;
	BOOL _enabled;
	BOOL _downPlural;
	BOOL _abovekeys;
	BOOL _isPad;
    int _minChars;
	
	BOOL _longPressed;
	LineVector _lines;
	
	BOOL hasPendingChanges;
	BOOL processingUpdate;
    
    UIColor* _textColor;
    UIColor* _outlineColor;
}

@property (nonatomic,retain) id keyplane;
@property (nonatomic,copy) id input;
@property (nonatomic,retain) UITextInputTraits* traits;

+(OctopusBeast*)inst;

-(void)applyPrefs;
-(void)printKeyplane;
-(int)swipeLength;
-(BOOL)pluralOnSwipeDown;

-(BOOL)canComplete;
-(BOOL)shouldCapitalize;
-(void)releaseCompletionEngine;
-(void)initCompletionEngine;
-(void)setInputMode:(NSString*)inpM;

-(void)updateSuggestions;
-(void)inputAdd:(NSString*)str;
-(void)inputSet:(NSString*)str;
-(void)inputBackspace;
-(void)inputClear;
-(void)inputClearWord;
-(void)setContext:(NSString*)ctx word:(NSString*)word offset:(int)offset;

-(int)suggestionIndexForKey:(NSString*)k;
-(NSString*)suggestionForKey:(NSString*)k isCorrection:(BOOL*)corr;
-(void)acceptWord:(NSString*)w;
-(NSString*)acceptWordFromSuggestionKey:(NSString *)k;

-(NSString*)inputMode;
-(NSString*)inputString;

// long press (variation keys)
-(void)longPress;
-(void)resetLongPress;
-(BOOL)isLongPressed;

// color management
-(UIColor*)colorForText;
-(UIColor*)colorForOutline;

@end


#include <sys/time.h>

inline unsigned GetTimestampMsec()
{
    timeval time;
    gettimeofday(&time, NULL);
    
    unsigned elapsed_seconds  = time.tv_sec;
    unsigned elapsed_useconds = time.tv_usec;
    
    return elapsed_seconds * 1000 + elapsed_useconds/1000;
}

inline BOOL isPad() {
#ifdef UI_USER_INTERFACE_IDIOM
    return (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad);
#else
    return NO;
#endif
}






