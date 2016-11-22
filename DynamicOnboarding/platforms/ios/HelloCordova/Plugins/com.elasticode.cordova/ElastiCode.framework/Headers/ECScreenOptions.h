//
//  ECScreenOptions.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 20/08/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ElastiCode+PEnums.h"

@class ECOnBoardingScreenTemplate;
@class ECOnBoardingOptions;
@interface ECScreenOptions : NSObject


@property (nonatomic, strong) ECOnBoardingScreenTemplate* screen;

@property (nonatomic,assign) BOOL shouldContinueOnScroll;
@property (nonatomic,assign) BOOL showScreenIndicator;
@property (nonatomic, strong, readonly) NSArray* elementsInScreen;

//@property (nonatomic, strong) NSArray* elementsOrderCodes;

-(void) setElementsOrderFromArray:(NSArray*) orderArray;

+(NSArray*) getScreensOptionsFromDictionary:(NSDictionary*) screensInfo updateonBoardingOptions:(ECOnBoardingOptions*) onBoardingOptions;
+(NSArray*) getScreensOptionsAndUpdateonBoardingOptions:(ECOnBoardingOptions*) onBoardingOptions;
+(void) updateServerAboutMoment:(NSString*) momentName optionElements:(NSArray*) elements orderOfElements:(NSArray*) orderOfElements momentType:(ECMomentType) momentType;
@end
