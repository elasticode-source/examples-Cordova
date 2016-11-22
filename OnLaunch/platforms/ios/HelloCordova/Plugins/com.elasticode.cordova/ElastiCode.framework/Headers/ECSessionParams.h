//
//  ECSessionOptions.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 20.3.2016.
//  Copyright © 2016 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ECSessionParamsSettings.h"
#import "ECSessionParamsData.h"

@interface ECSessionParams : NSObject
NS_ASSUME_NONNULL_BEGIN

@property (nonatomic,strong, readonly) ECSessionParamsSettings* settings;
@property (nonatomic,strong, readonly) ECSessionParamsData* data;

@property (nonatomic,strong, readonly) NSString* apiKey;
@property (nonatomic,assign, readonly) BOOL inProduction;

+ (instancetype) createInProduction:(BOOL) inProduction;
+ (instancetype) createWithAPIKey:(NSString*) apiKey inProduction:(BOOL) inProduction;
NS_ASSUME_NONNULL_END
@end





