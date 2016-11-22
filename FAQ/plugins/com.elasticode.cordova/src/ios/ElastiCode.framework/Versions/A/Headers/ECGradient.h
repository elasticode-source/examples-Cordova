//
//  ECGradient.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 23/08/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ECOverlayView;
@interface ECGradient : NSObject

@property (nonatomic, strong) NSArray* colors;
@property (nonatomic, strong) NSArray* locations;
@property (nonatomic, assign) CGPoint startPoint;
@property (nonatomic, assign) CGPoint endPoint;



@property (nonatomic, strong) NSString* json;

-(BOOL) applyToView:(ECOverlayView*) view;
-(BOOL) hasTransparency;

@end
