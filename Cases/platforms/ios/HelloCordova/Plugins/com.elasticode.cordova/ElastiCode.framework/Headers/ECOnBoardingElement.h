//
//  ECOnBoardingElement.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 2/27/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ElastiCode.h"
#import "ElastiCode+PEnums.h"
#import "ECTransition.h"

#define kMinimumFontSize 14.0

@interface ECOnBoardingElement : NSObject

@property (nonatomic,strong) NSString* elementName;

/** Show or hide the element, if YES element will appear */
@property (nonatomic,assign) BOOL show;

/** Element frame - origin and size */
@property (nonatomic,assign) CGRect frame;

@property (nonatomic,strong) NSString* devicesOffsetsJSON;

@property (nonatomic,strong) ECTransition* transition;

@property (nonatomic,assign) CGFloat opacity;

-(instancetype) initWithName:(NSString*) name frame:(CGRect) frame;

-(UIView*) createUI;
-(BOOL) shouldCreateUI;
-(CGRect) getFrameForDeviceType:(CGPoint) offset;
-(CGRect) convertFrameForDeviceType:(CGRect) fromFrame;
-(CGRect) unconvertFrameForDeviceType:(CGRect) fromFrame;
+(NSUInteger) _numberOfScreens:(NSArray*) countPerArray;

+(CGRect) getRectFromDictionary:(NSDictionary*) dict;

+(CGFloat) getOffsetYRatioForDeviceType;
+(CGFloat) getXRatioForDeviceType;


+(NSString *)hexValuesFromUIColor:(UIColor *)color;
+(UIColor *)colorWithHexString:(NSString *)hexString;
@end
