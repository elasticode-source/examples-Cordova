//
//  ECOnBoardingScreenIndicatorElement.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 02/08/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import "ECOnBoardingElement.h"

@interface ECOnBoardingScreenIndicatorElement : ECOnBoardingElement

/** Screen indictor color for all screens. */
@property (nonatomic,strong) UIColor* color;
/** Screen indictor color for current screen. */
@property (nonatomic,strong) UIColor* selectedColor;
/** Screen indicator offset from template location. can be any integer number */
@property (nonatomic,assign) NSInteger offsetY;


// Inner methods
-(UIPageControl*) createUIPageControlWithNumberOfScreens:(NSInteger) numberOfScreens originY:(int) originY;
+(void) updateServerAboutMoment:(NSString*) momentName element:(ECOnBoardingScreenIndicatorElement*) element group:(int)group momentType:(ECMomentType) momentType;
+(ECOnBoardingScreenIndicatorElement*) getMoment:(NSString*) momentName elementAndUpdateScreens:(NSArray*) screens;
+(ECOnBoardingScreenIndicatorElement*) getElementFromDictionary:(NSDictionary*) dictionary andUpdateScreens:(NSArray*) screens;
@end
