//
//  ECSessionParamsData.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 22.3.2016.
//  Copyright © 2016 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ElastiCode+PEnums.h"

/**
 *  Elasticode initialization data
 */
@interface ECSessionParamsData : NSObject
NS_ASSUME_NONNULL_BEGIN
/**
 *  Add array of ECOnBoardingAction object contains logic for actions in the app
 *
 *  @param additionalActions Array of ECOnBoardingAction objects
 *  @see ECOnBoardingAction
 */
-(void) addActions:(NSArray *)additionalActions;

#pragma mark - Session attributes
/**
 *  Add additional attributes to the session
 *  @param attributes The attributes relevant to the session
 */
-(void) addSessionAttributes:(NSDictionary*)attributes;
/**
 *  Add AppsFlyers attributes to the session
 *  @param attributes The attributes relevant to the session
 */
-(void) addSessionAppsFlyerAttributes:(NSDictionary*)attributes;
/**
 *  Add branch.io attributes to the session
 *  @param attributes The attributes relevant to the session
 */
-(void) addSessionBranchIOAttributes:(NSDictionary*)attributes;
/**
 *  Add button attributes to the session
 *  @param attributes The attributes relevant to the session
 */
-(void) addSessionButtonAttributes:(NSDictionary*)attributes;
/**
 *  Add Adjust attributes to the session
 *  @param attributes The attributes relevant to the session
 */
-(void) addSessionAdjustAttributes:(NSDictionary*)attributes;
/**
 *  Add Kochava attributes to the session
 *  @param attributes The attributes relevant to the session
 */
-(void) addSessionKochavaAttributes:(NSDictionary*)attributes;


#pragma mark - Moments
/**
 *  Define app trigger with the given name
 *  Add a callback block to get updated when block is active
 *  The given block will be called each time session has been restarted
 *
 *  @param appTriggerName Array of moment names
 *  @param activeCallback callback called after trigger is ready, isActive is Yes when trigger is active
 */
-(void) defineAppTrigger:(NSString*) appTriggerName isActiveCallback:(void (^)(BOOL isActive))activeCallback;

/**
 *  Define backView section with the given name
 *
 *  @param sectionName The section name
 */
-(void) defineBackViewSection:(NSString*) sectionName;
/**
 *  Define multiple backView section with the given names
 *
 *  @param sectionNames Array of section names
 */
-(void) defineBackViewSections:(NSArray*) sectionNames;

#pragma mark - Define Cases & Dynamic objects

/**
 *  Define a case and the number of possible states.
 *
 *  @param caseName    The case name
 *  @param numOfStates Number of states for this case.
 *
 */
-(void) defineCase:(NSString*)caseName withNumOfStates:(NSInteger)numOfStates;
/**
 *  Define a dynamic object.
 *
 *  @param dObjName The dynamic object name.
 *  @param dObjType The dynamic object type.
 *  @param defaultValue default value that will be used in case of error.
 *
 */
-(void) defineDynamicObject:(NSString*)dObjName type:(ElastiCodeDObjType) dObjType defaultValue:(NSObject*) defaultValue;

#pragma mark - Third party analytics

/**
 *  Add logic for third-party analytics to be triggered on button's actions
 *  @param name - name of the analytics platform
 *  @param analyticsAction action block that get the event name
 */
-(void) setThirdPartyAnalytics:(NSString*) name action:(void (^)(NSString* eventName))analyticsAction;


-(void) defineMoment:(NSString*) momentName __deprecated_msg("Please use defineAppTrigger:isActiveCallback:");

NS_ASSUME_NONNULL_END
@end
