// Note: I kept it here for your information
// It was generated using ./theos/bin/logify.pl
// It is quite useful for watching what is happening in some keyboard classes.
// Problem is that logify is not 100% reliable and it needs some manual changes done in the generated code.
// Still helpful though!

%hook UIKeyboard
+ (BOOL)respondsToProxGesture { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
+ (struct CGRect)onscreenFrameForTextInputTraits:(id)arg1 { %log; struct CGRect r = %orig; NSLog(@" = {{%g, %g}, {%g, %g}}", r.origin.x, r.origin.y, r.size.width, r.size.height); return r; }
+ (struct CGRect)defaultFrameForInterfaceOrientation:(int)arg1 { %log; struct CGRect r = %orig; NSLog(@" = {{%g, %g}, {%g, %g}}", r.origin.x, r.origin.y, r.size.width, r.size.height); return r; }
+ (void)initImplementationNow { %log; %orig; }
+ (void)_clearActiveKeyboard { %log; %orig; }
+ (void)removeAllDynamicDictionaries { %log; %orig; }
+ (struct CGSize)keyboardSizeForInterfaceOrientation:(int)arg1 { %log; struct CGSize r = %orig; NSLog(@" = {%g, %g}", r.width, r.height); return r; }
+ (struct CGSize)defaultSizeForInterfaceOrientation:(int)arg1 { %log; struct CGSize r = %orig; NSLog(@" = {%g, %g}", r.width, r.height); return r; }
+ (BOOL)isOnScreen { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
+ (struct CGSize)sizeForInterfaceOrientation:(int)arg1 { %log; struct CGSize r = %orig; NSLog(@" = {%g, %g}", r.width, r.height); return r; }
+ (id)activeKeyboard { %log; id r = %orig; NSLog(@" = %@", r); return r; }
+ (struct CGSize)defaultSizeForOrientation:(int)arg1 { %log; struct CGSize r = %orig; NSLog(@" = {%g, %g}", r.width, r.height); return r; }
+ (struct CGSize)defaultSize { %log; struct CGSize r = %orig; NSLog(@" = {%g, %g}", r.width, r.height); return r; }
- (void)dealloc { %log; %orig; }
- (BOOL)_isAutomaticKeyboard { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
- (void)_clearCurrentInputManager { %log; %orig; }
- (void)_acceptCurrentCandidate { %log; %orig; }
- (void)_setInputMode:(id)arg1 { %log; %orig; }
- (id)_typeCharacter:(id)arg1 withError:(struct CGPoint)arg2 shouldTypeVariants:(BOOL)arg3 baseKeyForVariants:(BOOL)arg4 { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (id)_touchPoint:(struct CGPoint)arg1 { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (void)_changeToKeyplane:(id)arg1 { %log; %orig; }
- (id)_keyplaneNamed:(id)arg1 { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (id)_keyplaneForKey:(id)arg1 { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (id)_baseKeyForRepresentedString:(id)arg1 { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (void)manualKeyboardWasOrderedOut { %log; %orig; }
- (void)manualKeyboardWillBeOrderedOut { %log; %orig; }
- (void)manualKeyboardWasOrderedIn { %log; %orig; }
- (void)manualKeyboardWillBeOrderedIn { %log; %orig; }
- (void)syncMinimizedStateToHardwareKeyboardAttachedState { %log; %orig; }
- (int)textEffectsVisibilityLevel { %log; int r = %orig; NSLog(@" = %d", r); return r; }
- (void)displayLayer:(id)arg1 { %log; %orig; }
- (void)setTypingEnabled:(BOOL )typingEnabled { %log; %orig; }
- (BOOL )typingEnabled { %log; BOOL  r = %orig; NSLog(@" = %d", r); return r; }
- (id)initWithDefaultSize { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (void)maximize { %log; %orig; }
- (void)minimize { %log; %orig; }
- (void)keyboardMinMaximized:(id)arg1 finished:(id)arg2 context:(id)arg3 { %log; %orig; }
- (void)takeSnapshot { %log; %orig; }
- (void)clearSnapshot { %log; %orig; }
- (id)defaultTextInputTraits { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (void)autoAdjustOrientationForSize:(struct CGSize)arg1 { %log; %orig; }
- (void)autoAdjustOrientation { %log; %orig; }
- (int)_positionInCandidateList:(id)arg1 { %log; int r = %orig; NSLog(@" = %d", r); return r; }
- (id)_getAutocorrection { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (void)_setAutocorrects:(BOOL)arg1 { %log; %orig; }
- (id)_getLocalizedInputMode { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (id)_getCurrentKeyboardName { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (id)_getCurrentKeyplaneName { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (BOOL)returnKeyEnabled { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
- (void)setDefaultTextInputTraits:(id)arg1 { %log; %orig; }
- (BOOL)isActive { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
- (BOOL)canDismiss { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
- (void)setMinimized:(BOOL )minimized { %log; %orig; }
- (BOOL )isMinimized { %log; BOOL  r = %orig; NSLog(@" = %d", r); return r; }
- (BOOL)_hasCandidates { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
- (void)implBoundsHeightChangeDone:(float)arg1 suppressNotification:(BOOL)arg2 { %log; %orig; }
- (void)prepareForImplBoundsHeightChange:(float)arg1 suppressNotification:(BOOL)arg2 { %log; %orig; }
- (void)resizeForKeyplaneSize:(struct CGSize)arg1 { %log; %orig; }
- (void)setReturnKeyEnabled:(BOOL)arg1 { %log; %orig; }
- (void)setCaretVisible:(BOOL)arg1 { %log; %orig; }
- (void)removeAutocorrectPrompt { %log; %orig; }
- (void)acceptAutocorrection { %log; %orig; }
- (void)geometryChangeDone:(BOOL)arg1 { %log; %orig; }
- (void)prepareForGeometryChange { %log; %orig; }
- (void)activate { %log; %orig; }
- (void)updateLayout { %log; %orig; }
- (void)setCaretBlinks:(BOOL)arg1 { %log; %orig; }
- (void)deactivate { %log; %orig; }
- (BOOL)pointInside:(struct CGPoint)arg1 forEvent:(struct __GSEvent *)arg2 { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
- (void)movedFromSuperview:(id)arg1 { %log; %orig; }
- (BOOL)pointInside:(struct CGPoint)arg1 withEvent:(id)arg2 { %log; BOOL r = %orig; NSLog(@" = %d", r); return r; }
- (void)touchesEnded:(id)arg1 withEvent:(id)arg2 { %log; %orig; }
- (void)touchesMoved:(id)arg1 withEvent:(id)arg2 { %log; %orig; }
- (void)touchesBegan:(id)arg1 withEvent:(id)arg2 { %log; %orig; }
- (id)hitTest:(struct CGPoint)arg1 withEvent:(id)arg2 { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (void)touchesCancelled:(id)arg1 withEvent:(id)arg2 { %log; %orig; }
- (int)interfaceOrientation { %log; int r = %orig; NSLog(@" = %d", r); return r; }
- (int)orientation { %log; int r = %orig; NSLog(@" = %d", r); return r; }
- (id)delegate { %log; id r = %orig; NSLog(@" = %@", r); return r; }
- (void)setFrame:(struct CGRect)arg1 { %log; %orig; }
- (void)removeFromSuperview { %log; %orig; }
- (void)setNeedsDisplay { %log; %orig; }
- (id)initWithFrame:(struct CGRect)arg1 { %log; id r = %orig; NSLog(@" = %@", r); return r; }
%end
