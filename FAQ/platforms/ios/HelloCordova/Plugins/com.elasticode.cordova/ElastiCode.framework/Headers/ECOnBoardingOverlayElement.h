//
//  ECOnBoardingOverlayElement.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 29/07/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import "ECOnBoardingElement.h"

#import "ECGradient.h"
/**
 *  On boarding overlay element
 */
@interface ECOnBoardingOverlayElement : ECOnBoardingElement

///** Overlay color */
//@property (nonatomic,strong) UIColor* color;
/** Overlay use round corners. */
@property (nonatomic,assign) NSInteger cornerRadius;
/** Overlay border color. */
@property (nonatomic,strong) UIColor* borderColor;
/** Overlay Gradient element. */
@property (nonatomic,strong) ECGradient* gradient;

/** Overlay border width. */
@property (nonatomic,assign) NSInteger borderWidth;

-(void) applyToView:(ECOverlayView*) view;

// Inner methods

+(void) updateServerAboutMoment:(NSString*) momentName elements:(NSArray*) elements group:(int)group momentType:(ECMomentType) momentType;
+(NSMutableArray*) getMoment:(NSString*) momentName elementsWithName:(NSString*) elementName frame:(CGRect) defaultFrame;
+(NSMutableArray*) getElementsWithName:(NSString*) elementName fromDictionary:(NSDictionary*) dictionary;

@end
