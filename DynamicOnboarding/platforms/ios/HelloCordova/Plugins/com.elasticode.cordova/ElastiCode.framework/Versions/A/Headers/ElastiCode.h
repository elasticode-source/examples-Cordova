//
//  ElastiCode.h
//  ElastiCode
//
//  Created by Dan Iosub on 10/15/13.
//  Updated by Tomer Shkolnik on 09/07/2016.
//  Copyright (c) 2016 elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ECOnBoardingAction.h"
#import "ElastiCode+PEnums.h"
#import "ECSessionParams.h"

@class ECOnboardingViewController;
@class ECOnBoardingOptions;

//Local notifications

/** Notification called when elasticode finish initialization */
#define ELASTICODE_SESSION_STARTED @"ELASTICODE_SESSION_INITIALIZE_SUCCESS"

/** Notification called when elasticode got updated information */
#define ELASTICODE_SESSION_RESTARTED @"ELASTICODE_SESSION_RESTARTED_SUCCESS"

/** Notification called when a moment has finish inisialization */
#define ELASTICODE_MOMENT_DEFINED @"ELASTICODE_MOMENT_DEFINED_SUCCESS"

@interface ElastiCode : NSObject


NS_ASSUME_NONNULL_BEGIN
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Session
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Set the log level of the ElastiCode SDK.
 Logs can show errors only (default): elastiCodeLogLevelErrors,
 or detailed log: elastiCodeLogLevelDetailed.
 It is recomended to set the log level before any other Elasticode calls
 *
 *  @param logLevel The log level: elastiCodeLogLevelErrors, elastiCodeLogLevelDetailed.
 */
+(void) setLogLevel:(enum elastiCodeLogLevel)logLevel;

/**
 * Notify Elasticode about application launch
 */
+(void) setLaunchingOptions:(NSDictionary *)launchOptions;
/**
 * Set onBoarding completion block.
 * When being triggered by Elasticode SDK, 
 * didAppear will be YES in case an experience was displayed to the user, otherwise NO
 */
+(void) setOnLaunchCompletionBlock:(void (^_Nullable)(BOOL didAppear))completion;

/**
 * @see ECSessionParams
 *
 *  @param params       Session settings and data
 *
 *  @return YES if the session passed all validation to get started; otherwise, NO.
 */
+(BOOL)setSessionParams:(ECSessionParams*) params;
/**
 *  This method serves as the entry point to ElastiCode.
 */
+(void)ready;
/**
 * Notify Elasticode about handling open url
 */
+(BOOL) openURL:(NSURL *)url completion:(void (^)(BOOL didAppear))completion;

/**
 * Set Elasticode API key
 */
+(void) setAPIKey:(NSString*) apiKey;

/**
 * Set User email address
 */
+(void) setUserEmail:(NSString*) userEmail;




/**
 *  When you want to force restart the session,
 *  you can call this method to perform a session restart.
 */
+ (void)restartSession;

/** Set the connection protocol to HTTP, default is NO
 *  When changing to HTTP don't forget to whitlist elasticode domains, by adding the following to your app plist:
 *  @code
 *  <key>NSAppTransportSecurity</key>
 *  <dict>
 *      <key>NSExceptionDomains</key>
 *      <dict>
 *          <key>appove-api.com</key>
 *          <dict>
 *              <key>NSIncludesSubdomains</key>
 *              <true/>
 *              <key>NSTemporaryExceptionAllowsInsecureHTTPLoads</key>
 *              <true/>
 *          </dict>
 *      </dict>
 *  </dict>
 */
+(void) disableHTTPS:(BOOL)disable;

+(void) showFAQTrigger:(NSString*) triggerCode callback:(void (^)(BOOL didAppear))callback;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Moments
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *  Display in-session experiences
 *
 *  @param appTriggerName The app trigger name
 */
+(void) showAppTrigger:(NSString*) appTriggerName;

/**
 *  Display in-session moments.
 *
 *
 *  @param appTriggerName The moment name
 *  @param context    context that will be available in all action triggered from the moment
 */
+(void) showAppTrigger:(NSString*) appTriggerName context:(NSDictionary* _Nullable) context;
/**
 *  Display in-session moments.
 *
 *  @param appTriggerName     The moment name
 *  @param context        context that will be available in all action triggered from the moment
 *  @param viewController viewController to present the moment from
 */
+(void) showAppTrigger:(NSString*) appTriggerName context:(NSDictionary* _Nullable) context onViewController:(UIViewController* _Nullable) viewController;

+(void) showAppTrigger:(NSString*) appTriggerName context:(NSDictionary* _Nullable) context onViewController:(UIViewController* _Nullable) viewController completion:(void (^_Nullable)(BOOL didAppear))completion;

/**
 *  End the current app trigger
 *
 *  @param goalConverted YES if the app trigger completed successfully; otherwise, NO.
 */
+(void) endAppTriggerWithGoalConversion:(BOOL) goalConverted;

/**
 *  End the current app trigger
 *
 *  @param goalConverted    YES if the app trigger completed successfully; otherwise, NO.
 *  @param dissmissBlock block to be triggered after app trigger dismissed
 */
+(void) endAppTriggerWithGoalConversion:(BOOL) goalConverted afterDismissBlock:(dispatch_block_t)dissmissBlock;

/**
 *  Notify elasticode a backView section has started
 *
 *  @param sectionName The name of the secion
 */
+(void) beginBackViewSection:(NSString*) sectionName;
/**
 *  Notify elasticode a backView section has ended. Main section will apply.
 */
+(void) endBackViewSection;
/**
 *  In case the app-launch moment displayed, you can launch it again
 */
+(void) relaunchOnLaunch;

/**
 *  Add array of ECOnBoardingAction object contains logic for actions in the app
 *
 *  @param actions Array of ECOnBoardingAction objects
 *  @see ECOnBoardingAction
 */
+(void) setActions:(NSArray *)actions;

/**
 *  Add logic for third-party analytics to be triggered on button's actions
 *  @param name - name of the analytics platform
 *  @param analyticsAction action block that get the event name
 */
+(void) setThirdPartyAnalytics:(NSString*) name action:(void (^)(NSString* eventName))analyticsAction;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Share User Info
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Update the SDK with info about the user. Please visit the ElastiCode documentation for more info about supported values in this hashmap.
 *
 *  @param userInfo    Provide the server with more about the user. This info will take into consider when choosing the best state for this case.
 */
+(void)shareUserInfo:(NSDictionary*)userInfo;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Cases & Dynamic objects:
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark State For Case
/**
 *  Get the selected state index of a case.
 *
 *  @param caseName    The case name
 *
 *  @return The selected state index. 0 for default.
 */
+(NSInteger)stateIndexForCase:(NSString*)caseName;
/**
 *  Get the selected state index of a case.
 *
 *  In case you going to use the state index later, use this method, 
 *  and when using index call the visitCase method.
 *
 *  @param caseName    The case name
 *
 *  @return The selected state index. 0 for default.
 */
+(NSInteger)stateIndexWithoutVisitForCase:(NSString*)caseName;

#pragma mark Value For Dynamic Object
/**
 *  Get the selected value of a dynamic object.
 *
 *  @param dObjName    The dynamic object name
 *
 *  @return NSObject with the selected value, 
 *  nil in case of using before defining a dynamic object or default value in case of error.
 */
+(NSObject*)valueForDynamicObject:(NSString*)dObjName;
/**
 *  Get the selected value of a dynamic object.
 *
 *  In case you going to use the value later, use this method,
 *  and when using the value, call the visitDynamicObject method.
 *
 *  @param dObjName    The dynamic object name
 *
 *  @return NSObject with the selected value,
 *  nil in case of using before defining a dynamic object or default value in case of error.
 */
+(NSObject*)valueWithoutVisitForDynamicObject:(NSString*)dObjName;


#pragma mark Visit
/**
 *  Signal the SDK when a case becomes visible to the user.
 *
 *  @param caseName    The case name
 *
 *  @see stateIndexWithoutVisitForCase:
 */
+(void)visitCase:(NSString*)caseName;
/**
 *  Signal the SDK when a dynamic object becomes visible to the user.
 *
 *  @param dObjName    The dynamic object name
 *
 *  @see valueWithoutVisitForDynamicObject:
 */
+(void)visitDynamicObject:(NSString*)dObjName;

#pragma mark Goal Reached
/**
 *  Indicate when the goal of the case is reached.
 *  Case must be visited first with 'stateIndexForCase' or 'visitCase'
 *  @param caseName The case name
 */
+(void)goalReached:(NSString*)caseName;
/**
 *  Indicate when the goal for the dynamic object is reached.
 *  Dynamic object must be visited first with 'valueForDynamicObject' or 'visitDynamicObject'
 *  @param dObjName The dynamic object name
 */
+(void)dynamicObjectGoalReached:(NSString*)dObjName;
/**
 *  Indicate when the goal for the app trigger is reached.
 *  The app trigger must display an experience first.
 *  @param appTriggerName the app trigger name
 */
+(void) goalReachedForAppTrigger:(NSString *)appTriggerName;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Event
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Signal the SDK on events, other then cases.
 *
 *  @param eventName    The event name
 */
+(void)event:(NSString*)eventName;
/**
 *  Signal the SDK on events, other then cases.
 *  With attributes relevant to the event
 *  @param eventName The event name
 *  @param attributes The attributes relevant to the event
 */
 +(void)event:(NSString*)eventName attributes:(NSDictionary* _Nullable) attributes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Debugging
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Take case/dynamic object snapshot.
 *  Only available in debug mode, take a screen shot of the visible screen and upload it to MC.
 *  Case must be visited first with 'stateIndexForCase' or 'visitCase'
 *  Dynamic object must be visited first with 'valueForDynamicObject' or 'visitDynamicObject'
 */
+(void)takeSnapShot:(NSString*) caseName;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - deprecated methods

#define StartSession_Depricate_msg "Use setSessionwithParams method instead"
#define InitializationSettings_Depricate_msg "Use ECSessionParams object instead"

+(void) endMomentWithCompletion:(BOOL) completion __deprecated_msg("Please use showAppTrigger:context");
+(void) endMomentWithCompletion:(BOOL) completion afterDismissBlock:(dispatch_block_t)dissmissBlock __deprecated_msg("Please use endAppTriggerWithGoalConvesion:afterDismissBlock:");
+(void) showMoment:(NSString*) momentName __deprecated_msg("Please use showAppTrigger");
+(void) showMoment:(NSString*) momentName context:(NSDictionary* _Nullable) context __deprecated_msg("Please use endAppTriggerWithGoalConvesion:");
+(void) showMoment:(NSString*) momentName context:(NSDictionary* _Nullable) context onViewController:(UIViewController* _Nullable) viewController __deprecated_msg("Please use showAppTrigger:context:onViewController");
+(void) showMoment:(NSString*) momentName context:(NSDictionary*) context onViewController:(UIViewController*) viewController completion:(void (^_Nullable)(BOOL didAppear))completion __deprecated_msg("Please use showAppTrigger:context:onViewController:completion");

+ (BOOL)startSessionWithParams:(ECSessionParams*) params __deprecated_msg(StartSession_Depricate_msg);
+ (void)startSession:(NSString*)elastiCodeApiKey __deprecated_msg(StartSession_Depricate_msg);
+ (void)startSession:(NSString*)elastiCodeApiKey onBoardingVersion:(NSString*) onBoardingVersion __deprecated_msg(StartSession_Depricate_msg);
+ (void)startSession:(NSString*)elastiCodeApiKey onBoardingVersion:(NSString*) onBoardingVersion completionHandler:(dispatch_block_t _Nullable)completionBlock skippedHandler:(dispatch_block_t _Nullable)skippedBlock __deprecated_msg(StartSession_Depricate_msg);

+(void) setConnectionTimeout:(NSUInteger) timeout __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) setImageDownloadTimeout:(NSUInteger) timeout __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) offlineMode __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) disableOnBoarding:(BOOL) disable __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) onTimeoutDisableOnBoarding:(BOOL) disable __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) disableAppSwitcher:(BOOL) disable __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) defineMoment:(NSString*) momentName __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) defineMoment:(NSString*) momentName completionHandler:(dispatch_block_t _Nullable)completionBlock skippedHandler:(dispatch_block_t _Nullable)skippedBlock __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) defineSwitcherSection:(NSString*) sectionName __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) addSessionAttributes:(NSDictionary*)attributes __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) addSessionAppsFlyerAttributes:(NSDictionary*)attributes __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) addSessionBranchIOAttributes:(NSDictionary*)attributes __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) addSessionButtonAttributes:(NSDictionary*)attributes __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) addSessionAdjustAttributes:(NSDictionary*)attributes __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) addSessionKochavaAttributes:(NSDictionary*)attributes __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) defineCase:(NSString*)caseName withNumOfStates:(NSInteger)numOfStates __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) defineDynamicObject:(NSString*)dObjName type:(ElastiCodeDObjType) dObjType defaultValue:(NSObject*) defaultValue __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) activateDebugMode __deprecated_msg(InitializationSettings_Depricate_msg);
+(void) devModeWithLogging:(enum elastiCodeLogLevel) logLevel __deprecated_msg(InitializationSettings_Depricate_msg);

+(void) beginSwitcherSection:(NSString*) sectionName __deprecated_msg("Use beginBackViewSection:");
+(void) endSwitcherSection __deprecated_msg("Use endBackViewSection");

+(void) relaunchOnBoarding __deprecated_msg("Use relaunchAppLaunch");
NS_ASSUME_NONNULL_END
@end
