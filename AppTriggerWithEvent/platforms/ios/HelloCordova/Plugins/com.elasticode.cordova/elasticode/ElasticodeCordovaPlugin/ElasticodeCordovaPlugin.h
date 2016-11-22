#import <Cordova/CDV.h>
#import <ElastiCode/ElastiCode.h>

@interface ElasticodeCordovaPlugin : CDVPlugin
-(void) initJSFunctionCallback:(CDVInvokedUrlCommand*)command;
-(void) initJSEventCallback:(CDVInvokedUrlCommand*)command;
-(void) setAndroidApiKey:(CDVInvokedUrlCommand*)command;
-(void) enableHTTPS:(CDVInvokedUrlCommand*)command;

#pragma mark - initialize
-(void) setIOSApiKey:(CDVInvokedUrlCommand*)command;
-(void) ready:(CDVInvokedUrlCommand*)command;

#pragma mark - Session
-(void) setSessionParams:(CDVInvokedUrlCommand*)command;
-(void) restartSession:(CDVInvokedUrlCommand*)command;

#pragma mark - App triggers
-(void) showAppTrigger:(CDVInvokedUrlCommand*)command;
-(void) showAppTriggerWithContext:(CDVInvokedUrlCommand*)command;
-(void) endAppTrigger:(CDVInvokedUrlCommand*)command;
-(void) beginBackViewSection:(CDVInvokedUrlCommand*)command;
-(void) endBackViewSection:(CDVInvokedUrlCommand*)command;
-(void) goalReachedForAppTrigger:(CDVInvokedUrlCommand*)command;

#pragma mark - FAQ
-(void) showFAQ:(CDVInvokedUrlCommand*)command;

#pragma mark - Share User Info
-(void) setUserEmail:(CDVInvokedUrlCommand*)command;
-(void) shareUserInfo:(CDVInvokedUrlCommand*)command;

#pragma mark - Cases & Dynamic objects
-(void) stateIndexForCase:(CDVInvokedUrlCommand*)command;
-(void) stateIndexWithoutVisitForCase:(CDVInvokedUrlCommand*)command;
-(void) valueForDynamicObject:(CDVInvokedUrlCommand*)command;
-(void) valueWithoutVisitForDynamicObject:(CDVInvokedUrlCommand*)command;
-(void) visitCase:(CDVInvokedUrlCommand*)command;
-(void) visitDynamicObject:(CDVInvokedUrlCommand*)command;
-(void) goalReached:(CDVInvokedUrlCommand*)command;
-(void) dynamicObjectGoalReached:(CDVInvokedUrlCommand*)command;

#pragma mark - Events
-(void) event:(CDVInvokedUrlCommand*)command;
-(void) eventWithAttributes:(CDVInvokedUrlCommand*)command;
@end
