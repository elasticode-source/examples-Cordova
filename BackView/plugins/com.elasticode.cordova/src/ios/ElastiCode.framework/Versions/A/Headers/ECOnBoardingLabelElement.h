//
//  ECOnBoardingTextElement.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 2/27/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import "ECOnBoardingElement.h"

/**
 *  On boarding label element
 */
@interface ECOnBoardingLabelElement : ECOnBoardingElement

/** Label text */
@property (nonatomic,strong) NSString* text;
/** Label text color */
@property (nonatomic,strong) UIColor* textColor;
/** Label text alignment */
@property (nonatomic,assign) NSTextAlignment textAlignment;
/** Label font size */
@property (nonatomic,assign) NSUInteger fontSize;
/** Label offset from template location. can be any integer number */
@property (nonatomic,assign) NSInteger textOffsetY __deprecated_msg("Use frame instead");
/** Label font name */
@property (nonatomic,strong) NSString* fontName;


// Inner methods
-(NSString*) getTextAlignment;
-(void) setTextAlignmentString:(NSString*)textAlignmentString;
+(void) updateServerAboutMoment:(NSString*) momentName elements:(NSArray*) elements group:(int)group momentType:(ECMomentType) momentType;
+(NSMutableArray*) getMoment:(NSString*) momentName elementsWithName:(NSString*) elementName frame:(CGRect)defaultFrame;
+(NSMutableArray*) getElementsWithName:(NSString*) elementName fromDictionary:(NSDictionary*) dictionary;

@end
