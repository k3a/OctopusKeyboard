//
//  Shared.h
//  SEPrefs
//
//  Created by K3A on 2/26/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Preferences/Preferences.h>

@interface PSViewController (K3ASEPrefsFakeUIViewController)
-(void)presentModalViewController:(id)ctrl animated:(BOOL)animated;
-(void)dismissModalViewControllerAnimated:(BOOL)animated;
@property(nonatomic, readonly) UINavigationController* navigationController;
@end

