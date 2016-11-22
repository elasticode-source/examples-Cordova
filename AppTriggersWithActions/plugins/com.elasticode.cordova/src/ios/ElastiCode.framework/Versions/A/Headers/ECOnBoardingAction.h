//
//  ECOnBoardingAction.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 3/23/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef NS_ENUM(NSInteger, ECActionType)
{
    ECActionType_noop = 0,
    ECActionType_nextScreen = 1,
    ECActionType_previousScreen = 2,
    ECActionType_endOnBoarding = 3,
    ECActionType_skipOnBoarding = 4,
};

@interface ECOnBoardingAction : NSObject
@property (strong, nonatomic) NSString* name;
@property (strong, nonatomic) void (^actionWithContext)(NSDictionary* context);

+ (ECOnBoardingAction*) createWithName:(NSString*) name actionWithContext:(void (^)(NSDictionary* context))actionWithContext;

+ (ECOnBoardingAction*) createWithName:(NSString*) name action:(dispatch_block_t) action __deprecated_msg("Use createWithName:actionWithContext: method instead");
@end
