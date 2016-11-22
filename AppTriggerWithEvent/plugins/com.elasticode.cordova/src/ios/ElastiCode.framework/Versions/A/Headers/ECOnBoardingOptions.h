//
//  ECOnBoardingOptions.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 28/07/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ElastiCode+PEnums.h"

@class ECOnBoardingScreenIndicatorElement;
@class ECGradient;

@interface ECOnBoardingOptions : NSObject

@property (nonatomic, strong) NSString* version;
@property (nonatomic, strong) NSString* name;
@property (nonatomic, assign) ECMomentType type;

@property (nonatomic, strong) NSArray* screensElementsOrder;
@property (nonatomic, strong, readonly) NSString* tag;

@property (nonatomic, assign, readonly) UIModalTransitionStyle transitionStyle;
@property (nonatomic, strong, readonly) ECGradient* backgroundGradient;
@property (nonatomic, assign, readonly) BOOL blurBGUse;
@property (nonatomic, assign, readonly) UIBlurEffectStyle blurBGType;


@property (nonatomic, strong) ECOnBoardingScreenIndicatorElement* screenIndicator;

-(void) updateServerWithMomentType:(ECMomentType) momentType;
-(void) updateOptionsToScreens:(NSArray*) screens;
-(void) updateOptionsFromDictionary:(NSDictionary*) dictionary toScreens:(NSArray*) screens;
-(NSArray*) getOrderViewsFromList:(NSArray*) viewsPerScreen;

-(void) momentWillAppear;
@end
