//
//  Created by K3A on 5/20/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#include <objc/runtime.h>
#import <UIKit/UIKit.h>
#import <UIKit/UITextInputPrivate.h>
#import <UIKit/UIKeyboardImpl.h>
#import <UIKit/UITextChecker.h>

//#include "complete.h"
#import "OctopusBeast.h"

static void __attribute__((constructor)) Init()
{
	NSLog(@"[[[[[ OCTOPUS KEYBOARD CLIENT INIT ]]]]]");
    
    //setlocale(LC_ALL,"en_US.utf8");
} 

void dumpView(UIView* aView, NSString* indent) {
    if (aView) {
        NSLog(@"%@%@", indent, aView);      // dump this view

        if (aView.subviews.count > 0) {
            NSString* subIndent = [[NSString alloc] initWithFormat:@"%@%@", 
                           indent, ([indent length]/2)%2==0 ? @"| " : @": "];
            for (UIView* aSubview in aView.subviews) dumpView( aSubview, subIndent );
            [subIndent release];
        }
    }
}

@protocol K3AUIKeyboardLayoutStar <NSObject>

-(BOOL)shift;
-(BOOL)isShiftKeyBeingHeld;

@end

// ----------------------------------------------------------------------------------------------------------------------------------
%hook UIKeyboardLayoutStar

static OctopusBeast* wtf = nil; // overlay
static CGPoint s_startPos; // pos of touch when touchDown
static unsigned s_touchDownTime = 0; // timestamp

-(void)longPressAction
{
	//%log;
	%orig;

	// tweak is disabled
	if ([wtf canComplete] == NO) return;
	
	// iPad fix (long press must take longer than 200 ms!)
	if (GetTimestampMsec() - s_touchDownTime > 200) [wtf longPress];
}

-(void)layoutSubviews
{
    //%log;

    if ([wtf canComplete]) [wtf setNeedsDisplay];

    %orig;
}

- (id)initWithFrame:(struct CGRect)frame
{
    id ret = %orig;
    
    ///%log;

	if (!wtf) wtf = [[OctopusBeast alloc] initWithFrame:CGRectMake(0,-10,frame.size.width,frame.size.height+10)]; //TODO: keyplane size
    
	[(UIView*)self addSubview:wtf]; // can be done more times ;)
	[wtf initCompletionEngine];

	return ret;
}
-(void)dealloc
{
	[wtf releaseCompletionEngine];

	%orig;
}

//- (void)showKeyboardType:(int)arg1 appearance:(int)arg2 orientation:(id)arg3 withShift:(BOOL)arg4
- (void)updateKeyboardForKeyplane:(id)keyplane
{
	//%log;
	%orig;

	NSArray* inpModeArr = [UIKeyboardGetCurrentInputMode() componentsSeparatedByString:@"@"];
	NSString* inpMode = [inpModeArr count]>0?[inpModeArr objectAtIndex:0]:@"en_US";

	//NSLog(@"INPUT MODE :::: %@", inpMode);
	//NSLog(@"TRAITS ::: %@", [[UIKeyboardImpl sharedInstance] textInputTraits]);

	wtf.keyplane = keyplane;
	wtf.traits = [[UIKeyboardImpl sharedInstance] textInputTraits];
	[wtf setInputMode:inpMode];
    
/*    UIKeyboardInputManager* im = [[UIKeyboardImpl sharedInstance] inputManager];
    [wtf inputSet:[im inputString]];
    
	[wtf updateSuggestions];*/
}

static BOOL s_handled = NO;
static NSString* s_key = nil;

- (void)sendStringAction:(id)str forKey:(id)kp isPopupVariant:(BOOL)arg3
{
    //%log;
    if (!s_handled) %orig;

    if (kp && [wtf canComplete])
    {
        const char* cstr = [str UTF8String];

        [s_key release];
        s_key = [str copy];
        
        // fix sentence ending
        if (cstr && (*cstr == '.' || *cstr == ',' || *cstr == '!' || *cstr == '?' /*|| *cstr == '\"' || *cstr == ':'*/))
        {
            id inpd = [[UIKeyboardImpl sharedInstance] inputDelegate];
            UITextRange* selRange = [inpd selectedTextRange];
            int len = (int)[inpd offsetFromPosition:[selRange start] toPosition:[selRange end]];
            int begLen = (int)[inpd offsetFromPosition:[inpd beginningOfDocument] toPosition:[selRange start]];
            if (len == 0 && begLen >= 2)
            {
                UITextPosition* start = [inpd positionFromPosition:[selRange start] offset:-2];
                UITextPosition* end = [selRange start];
                UITextRange* newr = [inpd textRangeFromPosition:start toPosition:end];
                NSString* str = [inpd textInRange:newr];
                //NSLog(@"PREVTEXT '%@'", str);
                BOOL corrected = NO;
                if ([str isEqualToString:@" ."]) 
                {
                    newr = [inpd textRangeFromPosition:start toPosition:[selRange end]];
					[inpd replaceRange:newr withText:@". "];
                    //[inpd replaceRangeWithTextWithoutClosingTyping:newr replacementText:@". "];
                    corrected = YES;
                }
                else if ([str isEqualToString:@" ?"]) 
                {
                    newr = [inpd textRangeFromPosition:start toPosition:[selRange end]];
					[inpd replaceRange:newr withText:@"? "];
                    //[inpd replaceRangeWithTextWithoutClosingTyping:newr replacementText:@"? "];
                    corrected = YES;
                }
                else if ([str isEqualToString:@" !"]) 
                {
                    newr = [inpd textRangeFromPosition:start toPosition:[selRange end]];
					[inpd replaceRange:newr withText:@"! "];
                    //[inpd replaceRangeWithTextWithoutClosingTyping:newr replacementText:@"! "];
                    corrected = YES;
                }
                else if ([str isEqualToString:@" ,"]) 
                {
                    newr = [inpd textRangeFromPosition:start toPosition:[selRange end]];
					[inpd replaceRange:newr withText:@", "];
                    //[inpd replaceRangeWithTextWithoutClosingTyping:newr replacementText:@", "];
                    corrected = YES;
                }
                /*else if ([str isEqualToString:@" \""]) 
                {
                    newr = [inpd textRangeFromPosition:start toPosition:[selRange end]];
                    [inpd replaceRange:newr withText:@"\" "];
					//[inpd replaceRangeWithTextWithoutClosingTyping:newr replacementText:@"\" "];
                    corrected = YES;
                }
                else if ([str isEqualToString:@" :"]) 
                {
                    newr = [inpd textRangeFromPosition:start toPosition:[selRange end]];
                    [inpd replaceRange:newr withText:@": "];
					//[inpd replaceRangeWithTextWithoutClosingTyping:newr replacementText:@": "];
                    corrected = YES;
                }*/
                
                if (corrected)
                {
                    [wtf inputAdd:@" "]; // add fake space
                    [wtf inputClearWord];
                }
            }
        }
    }
}

/*-(void)didClearInput
{
	%orig;
    OLog(3, "didClearInput");
    //OLog(3, "CLEARING WORD BECAUSE didClearInput");
	//[wtf inputClearWord];
}*/

- (id)keyHitTestForTouchInfo:(id)info touchStage:(int)arg2
{
   // %log;
    id hit = %orig;
    NSDictionary* props = [hit properties];
    
    [s_key release]; s_key = nil;
    
    if ([[props objectForKey:@"KBinteractionType"] intValue] == 2)
    {
        s_key = [[[hit properties] objectForKey:@"KBrepresentedString"] copy];
    }
    
    //NSLog(@"HIT %@", [hit properties]);
    
    return hit;
}


static UIGestureRecognizer *ssRecognizer=nil;
static void lookForSwipeSelection(void) {
	static BOOL done=NO;
	if (done) return;
	done=YES;
	
	Class KHRecognizer=objc_getClass("KHPanGestureRecognizer");
	if (KHRecognizer==Nil) return;
	
	UIKeyboardImpl* ki = [UIKeyboardImpl sharedInstance];
	NSArray *recognizers=[ki gestureRecognizers];
	for (UIGestureRecognizer *recognizer in recognizers) {
		if ([recognizer isKindOfClass:KHRecognizer]) {
			ssRecognizer=recognizer;
			return;
		}
	}
}


- (void)touchDown:(UITouch*)t {
	lookForSwipeSelection();
    //OLog(3, "DOWN");
    
    //%log;
    %orig;
    
	s_startPos = [t locationInView:(UIView*)self];
    s_handled = NO;
	[wtf resetLongPress];
	s_touchDownTime = GetTimestampMsec();
}
- (void)touchDragged:(UITouch*)t
{
	

	if (![wtf canComplete] || [wtf isLongPressed])
	{
		%orig;
		return;
	}

	CGPoint pnt = [t locationInView:(UIView*)self];
	float dy = pnt.y - s_startPos.y;
	
	if (dy > 0 && (dy >= 3 && ![wtf pluralOnSwipeDown])) {
    	%orig;
	}
}
- (void)swipeDetected:(UISwipeGestureRecognizer*)recognizer {
	//%log;
	if ([wtf canComplete] && (recognizer.direction==UISwipeGestureRecognizerDirectionUp ||
							  recognizer.direction==UISwipeGestureRecognizerDirectionDown)) {
		if ([wtf suggestionIndexForKey:s_key]!=-1) return;
	}
	%orig;
}
static void handleEndedCancelled(CGPoint pnt, id akey, BOOL shift)
{  
	return; //TODO:ios7:fix
    if (s_handled) return;
    s_handled = YES;
    
    if (![wtf canComplete]) return;
    
    float dy = pnt.y - s_startPos.y;
    
    OLog(3, "DY: %.0f", dy);
	
	float minOffs = 35.0f;
	if (wtf)
	{
		if ([wtf swipeLength] == 0)
			minOffs = 25.0f;
		else if ([wtf swipeLength] == 1)
			minOffs = 35.0f;
		else if ([wtf swipeLength] == 2)
			minOffs = 45.0f;
	}

	if (fabsf(dy) > minOffs && (dy < 0 || [wtf pluralOnSwipeDown])) // swipe, try to complete
	{
		if (ssRecognizer) {
			[ssRecognizer setState:UIGestureRecognizerStateFailed];
		}
		bool makePlural = false;
		if (dy > 0) makePlural = true;
		
        // get key under the touch
		//NSDictionary* props = [akey properties];
	    //NSString* key = [props objectForKey:@"KBrepresentedString"];
//        OLog(3, "KEY: '%s'", [s_key UTF8String]);
		if (s_key)
		{
            NSString* comp = [wtf acceptWordFromSuggestionKey:s_key];
            if (comp) // we have a completion
            {
                OLog(3, "SENDING WORD '%s'", [comp UTF8String]);
                
                UIKeyboardImpl* ki = [UIKeyboardImpl sharedInstance];
                UIKeyboardInputManager* im = [[UIKeyboardImpl sharedInstance] inputManager];
				
				// make plural form if not already
				if (makePlural && ![comp hasSuffix:@"s"] && ![comp hasSuffix:@"es"])
				{
					if ([comp hasSuffix:@"ch"] || [comp hasSuffix:@"sh"])
						comp = [comp stringByAppendingString:@"es"]; // sandwich -> sandwiches
					else
						comp = [comp stringByAppendingString:@"s"];
				}
                
                // TODO: spaces
                if ([[im inputString] length] > 0)
                {
					// hack to allow ' to complete can't
					if ([s_key isEqualToString:@"'"]) [ki deleteBackwardAndNotify:NO];
					
                    static Class _UIKeyboardCandidateSingle = objc_getClass("UIKeyboardCandidateSingle");
                    [ki acceptWord:[[[_UIKeyboardCandidateSingle alloc] initWithCandidate:[comp stringByAppendingString:@" "]] autorelease] firstDelete:1];
                    [im clearInput];
                }
                else
                    [ki insertText:[comp stringByAppendingString:@" "]];
                
                [wtf updateSuggestions]; // FIXME: why we need this here (when it's not here, autocap after completed word is wrong)
            }
            else // we don't have a completion, just add to the input word
                [wtf inputAdd:shift?[s_key uppercaseString]:[s_key lowercaseString]];
        }
	}
    else // now swipe, add to the input word
        [wtf inputAdd:shift?[s_key uppercaseString]:[s_key lowercaseString]];
    
    UIKeyboardInputManager* im = [[UIKeyboardImpl sharedInstance] inputManager];
    OLog(3, "IM INPUT '%s'", [[im inputString] UTF8String]);
    
    // is necessary for (world key) and other system keys (keyplane may change)
    if (s_key == nil)
    {
        OLog(3,"FORCE-UPDATING KEYS");
        [wtf updateSuggestions];
    }
    
    
	// TEXT SELECTION
	static int wtf = 0;
	if (wtf++ == 5 && false)
	{
		id ti = [[UIKeyboardImpl sharedInstance] delegate];
		//id qqq = [ti positionFromPosition:[ti endOfDocument] inDirection:UITextLayoutDirectionLeft offset:3];
		//id tr = [ti textRangeFromPosition:qqq toPosition:qqq];
        
		id tr = [ti textRangeFromPosition:[ti positionFromPosition:[ti endOfDocument] inDirection:UITextLayoutDirectionLeft offset:3] toPosition:[ti endOfDocument]];
		
		[ti setSelectedTextRange:tr];
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event 
{
    %orig;
    
    handleEndedCancelled([[touches anyObject] locationInView:(UIView*)self], [self activeKey], [(id<K3AUIKeyboardLayoutStar>)self shift]);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event 
{
    %orig;
    
    handleEndedCancelled([[touches anyObject] locationInView:(UIView*)self], [self activeKey], [(id<K3AUIKeyboardLayoutStar>)self shift]);
    
	//%log;
	//dumpView(self, @"");
    
	//,1
	//printKBTree([self keyplane], @"");
    
}

%end

//------------------------------------------------------------------------------------------------------------------------------

%hook UIKeyboardImpl

-(void)deleteBackwardAndNotify:(BOOL)notify
{
	[wtf inputBackspace];

	%orig;
}

-(BOOL)acceptWord:(NSString*)word firstDelete:(unsigned int)del
{
	///%log;
	BOOL ret = %orig;

    if (del == 0)
    {
        NSString* w = [[word candidate] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
        [wtf acceptWord:w];
    }
    
	return ret;
}

-(void)updateForChangedSelection
{
    %orig;

    if ([wtf canComplete])
	{    
		id inpd = [self inputDelegate];
		
		UITextRange* selRange = [inpd selectedTextRange];
		if (!selRange) return;
		
		UITextRange* wordRange = [inpd _rangeOfEnclosingWord:[selRange start]];
		//OLog(3, "WR: %s -> %s", [[[selRange start] description] UTF8String], [[wordRange description] UTF8String]);
		if (!wordRange) wordRange = selRange;
			
		NSString* word = [inpd textInRange:wordRange];
		//NSString* context = [self currentInputContextFromInputDelegateWithWordRange:wordRange]; //TODO:ios7:fix
		NSString* context = word;

		int offset = [inpd offsetFromPosition:[wordRange end] toPosition:[selRange start]];
		OLog(3, "++ CONTEXT: '%s|%s' OFFSET %d", [context UTF8String], [word UTF8String], offset);
  	  
    	[wtf setContext:context word:word offset:offset];
		[wtf updateSuggestions];
	}
}

/*-(id)currentInputContextFromInputDelegateWithWordRange:(UITextRange*)range
{
    UITextRange* selRange = [[self inputDelegate] selectedTextRange];

    if (!range) range = selRange;
    
    ///%log;
    NSString* ctx = %orig;
	
	if ([wtf canComplete])
	{
		NSString* word = [[self inputDelegate] textInRange:range];
		int offset = [[self inputDelegate] offsetFromPosition:[range end] toPosition:[selRange start]];
		
		OLog(3, "SelRange = %s", [[selRange description] UTF8String]);
		OLog(3, "WordRange = %s", [[range description] UTF8String]);
		OLog(3, "'%s|%s' OFFSET %d", [ctx UTF8String], [word UTF8String], offset);
		
		[wtf setContext:ctx word:word offset:offset];
    }
	
    return ctx;
}*/

%end


/*%hook UIKeyboardInputManager

-(void)appendToInputContext:(NSString*)str 
{
    ///%log;
    %orig;
}

%end*/


/*
%hook NSObject
-(id)_rangeOfEnclosingWord:(id)wr
{
    ///%log;
    return %orig;
}
%end
*/


// allow non-standard keyboard shortcuts 
// commented out as not compatible with ios 6
//%hook TIUserDictionaryWord
//- (int)validateWithNewTarget:(id)arg1 newShortcut:(id)arg2
//{
//	%log;
//	return 0;
//}
//%end

// vim:ft=objc
