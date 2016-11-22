//
//  ECTransition.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 17/08/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ECOnBoardingElement;
@interface ECTransition : NSObject

+(ECTransition*) createTransitionWithElement:(ECOnBoardingElement *)element configString:(NSString*) configString;
- (instancetype)initWithElement:(ECOnBoardingElement*) element;

-(void) updateProgress:(CGFloat) progress
        isTransitionIn:(BOOL) isTransitionIn
                 index:(NSInteger) index;

-(NSString*) getConfigurationString;
-(BOOL) updateConfigurationFromString:(NSString*) configString;
+(NSString*) nop;
-(void) hideView;
-(void) updateUI;
@end
