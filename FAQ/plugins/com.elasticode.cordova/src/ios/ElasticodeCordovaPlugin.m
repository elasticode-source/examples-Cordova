#import "ElasticodeCordovaPlugin.h"
#import <ElastiCode/ElastiCode+Cordova.h>
@implementation ElasticodeCordovaPlugin
{
    NSNotification* _finishLaunchingNotif;
    NSNotification* _handleOpenURLNotif;
}
-(void)pluginInitialize{
    [super pluginInitialize];
    _finishLaunchingNotif = nil;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(finishLaunching:) name:UIApplicationDidFinishLaunchingNotification object:nil];
    //    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onResume) name:UIApplicationWillEnterForegroundNotification object:nil];
}

- (void)finishLaunching:(NSNotification *)notification{
    _finishLaunchingNotif = notification;
}
- (void)handleOpenURL:(NSNotification*)notification{
    // override to handle urls sent to your app
    // register your url schemes in your App-Info.plist
    
    if(_finishLaunchingNotif){
        _handleOpenURLNotif = notification;
    }else{
        NSURL* deepLinkURL = [notification object];
        [ElastiCode openURL:deepLinkURL completion:^(BOOL didAppear) {
            [self _cordovaFireJSFunction:@"onLaunchComplete" funcFamily:@"ec" boolean:[NSNumber numberWithBool:didAppear]];
        }];
    }
}

-(void) dealloc{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - initialize
-(void) initJSFunctionCallback:(CDVInvokedUrlCommand*)command        {}
-(void) initJSEventCallback:(CDVInvokedUrlCommand*)command           {}
-(void) setAndroidApiKey:(CDVInvokedUrlCommand*)command              {}

-(void) setIOSApiKey:(CDVInvokedUrlCommand*)command          {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* apiKey = [command argumentAtIndex:0];
    [ElastiCode setAPIKey:apiKey];
    [self _cordovaOK:command];
}
-(void) ready:(CDVInvokedUrlCommand*)command           {
    NSDictionary* paramsJS = [command argumentAtIndex:1];
    NSDictionary* actions = [paramsJS objectForKey:@"actions"];
    if(actions && [actions isKindOfClass:[NSDictionary class]]){
        NSDictionary* userActions = [actions objectForKey:@"global"];
        NSMutableArray* arrayOfActions = [NSMutableArray new];
        for (NSString* actionName in userActions) {
            if([actionName isKindOfClass:[NSString class]]){
                [arrayOfActions addObject:
                 [ECOnBoardingAction createWithName:actionName
                                  actionWithContext:^(NSDictionary *context) {
                                      [self _cordovaFireJSFunction:actionName funcFamily:nil params:context];
                                  }]];
            }
        }
        if([arrayOfActions count] > 0){
            [ElastiCode setActions:arrayOfActions];
        }
        
        NSDictionary* userTPA = [actions objectForKey:@"tpa"];
        for (NSString* tpaName in userTPA) {
            if([tpaName isKindOfClass:[NSString class]]){
                [ElastiCode setThirdPartyAnalytics:tpaName
                                            action:^(NSString * _Nonnull eventName) {
                                                [self _cordovaFireJSFunction:tpaName funcFamily:@"tpa" string:eventName];
                                            }
                 ];
            }
        }
    }
    
    NSDictionary* currentLaunchOption = nil;
    if(_finishLaunchingNotif){
        currentLaunchOption = [_finishLaunchingNotif userInfo];
    }else if(_handleOpenURLNotif){
        NSURL* openLink = [_handleOpenURLNotif object];
        if(openLink && [openLink isKindOfClass:[NSURL class]]){
            currentLaunchOption = @{
                                    UIApplicationLaunchOptionsURLKey : openLink
                                    };
        }
    }
    _finishLaunchingNotif = nil;
    _handleOpenURLNotif = nil;
    [ElastiCode setLaunchingOptions:currentLaunchOption];
    [ElastiCode setOnLaunchCompletionBlock:^(BOOL didAppear) {
        [self _cordovaFireJSFunction:@"onLaunchComplete" funcFamily:@"ec" boolean:[NSNumber numberWithBool:didAppear]];
    }];
    [ElastiCode ready];
    [self _cordovaOK:command];
}
-(void) enableHTTPS:(CDVInvokedUrlCommand*)command           {
    [self _cordovaOK:command];
}

#pragma mark - Session
-(void) setSessionParams:(CDVInvokedUrlCommand*)command          {
    if(![self _cordovaValidateCommand:command requiredArgs:2]){
        return;
    }
    
    NSNumber* isProduction = [command argumentAtIndex:0];
    NSDictionary* paramsJS = [command argumentAtIndex:1];
    
    ECSessionParams* params = [ECSessionParams createInProduction:[isProduction boolValue]];
    if(![self _parseSessionParams:paramsJS updateObject:params command:command]){
        return;
    }
    
    NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(_elasticode_finishedSync:) name:ELASTICODE_SESSION_STARTED object:nil];
    [center addObserver:self selector:@selector(_elasticode_restarted:) name:ELASTICODE_SESSION_RESTARTED object:nil];
    [center addObserver:self selector:@selector(_elasticode_momentDefined:) name:ELASTICODE_MOMENT_DEFINED object:nil];
    
    [ElastiCode setSessionParams:params];
    
    [self _cordovaOK:command];
}

-(void) restartSession:(CDVInvokedUrlCommand*)command           {
    [ElastiCode restartSession];
    [self _cordovaOK:command];
}

#pragma mark - App triggers
-(void) showAppTrigger:(CDVInvokedUrlCommand*)command                   {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* momentName = [[command arguments] objectAtIndex:0];
    [ElastiCode showAppTrigger:momentName];
    [self _cordovaOK:command];
}
-(void) showAppTriggerWithContext:(CDVInvokedUrlCommand*)command        {
    if(![self _cordovaValidateCommand:command requiredArgs:2]){
        return;
    }
    NSString* momentName = [[command arguments] objectAtIndex:0];
    NSDictionary* context = [[command arguments] objectAtIndex:1];
    [ElastiCode showAppTrigger:momentName context:context];
    [self _cordovaOK:command];
}
-(void) endAppTrigger:(CDVInvokedUrlCommand*)command                    {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSNumber* shouldComplete = [[command arguments] objectAtIndex:0];
    if(![shouldComplete isKindOfClass:[NSNumber class]]){
        [self _cordovaError:command];
        return;
    }
    [ElastiCode endAppTriggerWithGoalConversion:[shouldComplete boolValue] afterDismissBlock:^{
        [self _cordovaFireJSFunction:@"endMoment_afterDismiss" funcFamily:@"ec" params:nil];
    }];
    [self _cordovaOK:command];
}
-(void) beginBackViewSection:(CDVInvokedUrlCommand*)command         {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* momentName = [[command arguments] objectAtIndex:0];
    [ElastiCode beginBackViewSection:momentName];
    [self _cordovaOK:command];
}
-(void) endBackViewSection:(CDVInvokedUrlCommand*)command           {
    if(![self _cordovaValidateCommand:command requiredArgs:0]){
        return;
    }
    [ElastiCode endBackViewSection];
    [self _cordovaOK:command];
}
-(void) goalReachedForAppTrigger:(CDVInvokedUrlCommand*)command {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* appTriggerName = [[command arguments] objectAtIndex:0];
    [ElastiCode goalReachedForAppTrigger:appTriggerName];
    [self _cordovaOK:command];
}

#pragma mark - FAQ
-(void) showFAQ:(CDVInvokedUrlCommand*)command                   {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* faqCode = [command argumentAtIndex:0];
    [ElastiCode showFAQTrigger:faqCode callback:^(BOOL didAppear) {
        [self _cordovaFireJSFunction:@"faqCompleted" funcFamily:@"ec" boolean:[NSNumber numberWithBool:didAppear]];
    }];
    [self _cordovaOK:command];
}


#pragma mark - Share User Info
-(void) setUserEmail:(CDVInvokedUrlCommand*)command {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* userEmail = [command argumentAtIndex:0];
    if(![userEmail isKindOfClass:[NSString class]]){
        [self _cordovaError:command];
        return;
    }
    [ElastiCode setUserEmail:userEmail];
    [self _cordovaOK:command];
}
-(void) shareUserInfo:(CDVInvokedUrlCommand*)command {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSDictionary* attributes = [[command arguments] objectAtIndex:0];
    if(![attributes isKindOfClass:[NSDictionary class]]){
        [self _cordovaError:command];
        return;
    }
    [ElastiCode shareUserInfo:attributes];
    [self _cordovaOK:command];
}

#pragma mark - Cases & Dynamic objects
-(void) stateIndexForCase:(CDVInvokedUrlCommand*)command                    {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* caseName = [[command arguments] objectAtIndex:0];
    NSInteger state = [ElastiCode stateIndexForCase:caseName];
    [self _cordovaOK:command withInteger:state];
}
-(void) stateIndexWithoutVisitForCase:(CDVInvokedUrlCommand*)command        {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* caseName = [[command arguments] objectAtIndex:0];
    NSInteger state = [ElastiCode stateIndexWithoutVisitForCase:caseName];
    [self _cordovaOK:command withInteger:state];
}
-(void) valueForDynamicObject:(CDVInvokedUrlCommand*)command                {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    
    NSString* doName = [[command arguments] objectAtIndex:0];
    NSObject* value = [ElastiCode valueForDynamicObject:doName];
    ElastiCodeDObjType type = [ElastiCode typeOfDObj:doName];
    switch(type){
        case ElastiCodeDObjType_bool:
            if([value isKindOfClass:[NSNumber class]]){
                [self _cordovaOK:command withBool:[(NSNumber*)value boolValue]];
            }
            break;
        case ElastiCodeDObjType_int:
            if([value isKindOfClass:[NSNumber class]]){
                [self _cordovaOK:command withInteger:[(NSNumber*)value integerValue]];
            }
            break;
        case ElastiCodeDObjType_double:
            if([value isKindOfClass:[NSNumber class]]){
                [self _cordovaOK:command withDouble:[(NSNumber*)value doubleValue]];
            }
            break;
        case ElastiCodeDObjType_string:
            if([value isKindOfClass:[NSString class]]){
                [self _cordovaOK:command withString:(NSString*)value];
            }
            break;
        case ElastiCodeDObjType_arrayOfBool:
        case ElastiCodeDObjType_arrayOfInt:
        case ElastiCodeDObjType_arrayOfDouble:
        case ElastiCodeDObjType_arrayOfString:
            if([value isKindOfClass:[NSArray class]]){
                [self _cordovaOK:command withArray:(NSArray*)value];
            }
            break;
        default:
            [self _cordovaError:command];
            break;
    }
}
-(void) valueWithoutVisitForDynamicObject:(CDVInvokedUrlCommand*)command    {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* doName = [[command arguments] objectAtIndex:0];
    NSObject* value = [ElastiCode valueWithoutVisitForDynamicObject:doName];
    ElastiCodeDObjType type = [ElastiCode typeOfDObj:doName];
    switch(type){
        case ElastiCodeDObjType_bool:
            if([value isKindOfClass:[NSNumber class]]){
                [self _cordovaOK:command withBool:[(NSNumber*)value boolValue]];
            }
            break;
        case ElastiCodeDObjType_int:
            if([value isKindOfClass:[NSNumber class]]){
                [self _cordovaOK:command withInteger:[(NSNumber*)value integerValue]];
            }
            break;
        case ElastiCodeDObjType_double:
            if([value isKindOfClass:[NSNumber class]]){
                [self _cordovaOK:command withDouble:[(NSNumber*)value doubleValue]];
            }
            break;
        case ElastiCodeDObjType_string:
            if([value isKindOfClass:[NSString class]]){
                [self _cordovaOK:command withString:(NSString*)value];
            }
            break;
        case ElastiCodeDObjType_arrayOfBool:
        case ElastiCodeDObjType_arrayOfInt:
        case ElastiCodeDObjType_arrayOfDouble:
        case ElastiCodeDObjType_arrayOfString:
            if([value isKindOfClass:[NSArray class]]){
                [self _cordovaOK:command withArray:(NSArray*)value];
            }
            break;
        default:
            [self _cordovaError:command];
            break;
    }
}
-(void) visitCase:(CDVInvokedUrlCommand*)command                            {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* caseName = [[command arguments] objectAtIndex:0];
    [ElastiCode visitCase:caseName];
    [self _cordovaOK:command];
}
-(void) visitDynamicObject:(CDVInvokedUrlCommand*)command                   {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* doName = [[command arguments] objectAtIndex:0];
    [ElastiCode visitDynamicObject:doName];
    [self _cordovaOK:command];
}
-(void) goalReached:(CDVInvokedUrlCommand*)command                          {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* caseName = [[command arguments] objectAtIndex:0];
    [ElastiCode goalReached:caseName];
    [self _cordovaOK:command];
}
-(void) dynamicObjectGoalReached:(CDVInvokedUrlCommand*)command             {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* doName = [[command arguments] objectAtIndex:0];
    [ElastiCode dynamicObjectGoalReached:doName];
    [self _cordovaOK:command];
}

#pragma mark - Events
-(void) event:(CDVInvokedUrlCommand*)command                 {
    if(![self _cordovaValidateCommand:command requiredArgs:1]){
        return;
    }
    NSString* eventName = [[command arguments] objectAtIndex:0];
    [ElastiCode event:eventName];
    [self _cordovaOK:command];
}
-(void) eventWithAttributes:(CDVInvokedUrlCommand*)command   {
    if(![self _cordovaValidateCommand:command requiredArgs:2]){
        return;
    }
    NSString* eventName = [[command arguments] objectAtIndex:0];
    NSDictionary* eventAttributes = [[command arguments] objectAtIndex:1];
    [ElastiCode event:eventName attributes:eventAttributes];
    [self _cordovaOK:command];
}

#pragma mark - elasticode helpers
-(void) _elasticode_finishedSync:(NSNotification*) note {
    [self _cordovaFireJSEvent:@"EC_SessionStarted" userInfo:[note userInfo]];
}
-(void) _elasticode_restarted:(NSNotification*) note {
    [self _cordovaFireJSEvent:@"EC_SessionRestarted" userInfo:[note userInfo]];
}
-(void) _elasticode_momentDefined:(NSNotification*) note {
    [self _cordovaFireJSEvent:@"EC_MomentDefined" userInfo:[note userInfo]];
}
-(NSString*) _dictionaryToJSON:(NSDictionary*) dict{
    NSError *error;
    NSData *jsonData = nil;
    if(dict && [dict isKindOfClass:[NSDictionary class]]){
        jsonData = [NSJSONSerialization dataWithJSONObject:dict
                                                   options:0
                                                     error:&error];
    }
    NSString* paramsJson;
    if (! jsonData) {
        paramsJson = nil;
    } else {
        paramsJson = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    return paramsJson;
}
-(BOOL) _parseSessionParams:(NSDictionary*) paramsJS updateObject:(ECSessionParams*) params command:(CDVInvokedUrlCommand*) command{
    NSDictionary* settings = [paramsJS objectForKey:@"settings"];
    NSDictionary* data = [paramsJS objectForKey:@"data"];
    if(!settings || ![settings isKindOfClass:[NSDictionary class]]
       || !data){
        [self _cordovaError:command];
        return NO;
    }
    NSArray* settingsKeys = @[@"onLaunchVersion",
                              @"connectionTimeout",
                              @"imageDownloadTimeout",
                              @"disableOnLaunch",
                              @"disableBackView",
                              @"onTimeoutDisableOnLaunch",
                              @"offlineMode",
                              @"logLevel"];
    for (NSString* settingsKey in settings) {
        if(![settingsKey isKindOfClass:[NSString class]]){
            continue;
        }
        if([settingsKeys containsObject:settingsKey]) {
            NSInteger sKeyIndex = [settingsKeys indexOfObject: settingsKey];
            NSObject* sObj = [settings objectForKey:settingsKey];
            switch (sKeyIndex) {
                case 0:
                    if([sObj isKindOfClass:[NSString class]]){
                        params.settings.onLaunchVersion = (NSString*) sObj;
                    }
                    break;
                case 1:
                    if([self _isNSNumberInteger:sObj]){
                        [params.settings setConnectionTimeout:[(NSNumber*)sObj integerValue]];
                    }
                    break;
                case 2:
                    if([self _isNSNumberInteger:sObj]){
                        [params.settings setImageDownloadTimeout:[(NSNumber*)sObj integerValue]];
                    }
                    break;
                case 3:
                    if([self _isNSNumberBool:sObj] && [(NSNumber*)sObj boolValue]){
                        [params.settings disableOnLaunch:YES];
                    }
                    break;
                case 4:
                    if([self _isNSNumberBool:sObj] && [(NSNumber*)sObj boolValue]){
                        [params.settings disableBackView:YES];
                    }
                    break;
                case 5:
                    if([self _isNSNumberBool:sObj] && [(NSNumber*)sObj boolValue]){
                        [params.settings onTimeoutDisableOnLaunch:YES];
                    }
                    break;
                case 6:
                    if([self _isNSNumberBool:sObj] && [(NSNumber*)sObj boolValue]){
                        [params.settings offlineMode];
                    }
                    break;
                case 7:
                    if([self _isNSNumberInteger:sObj]){
                        [params.settings setLogLevel:(ECLogLevel)[(NSNumber*)sObj integerValue]];
                    }
                default:
                    break;
            }
        } else {
            continue;
        }
    }
    
    NSDictionary* actions = [data objectForKey:@"actions"];
    if(actions && [actions isKindOfClass:[NSDictionary class]]){
        NSDictionary* userActions = [actions objectForKey:@"global"];
        NSMutableArray* arrayOfActions = [NSMutableArray new];
        for (NSString* actionName in userActions) {
            if([actionName isKindOfClass:[NSString class]]){
                [arrayOfActions addObject:
                 [ECOnBoardingAction createWithName:actionName
                                  actionWithContext:^(NSDictionary *context) {
                                      [self _cordovaFireJSFunction:actionName funcFamily:nil params:context];
                                  }]];
            }
        }
        if([arrayOfActions count] > 0){
            [params.data addActions:arrayOfActions];
        }
        
        NSDictionary* userTPA = [actions objectForKey:@"tpa"];
        for (NSString* tpaName in userTPA) {
            if([tpaName isKindOfClass:[NSString class]]){
                [params.data setThirdPartyAnalytics:tpaName
                                             action:^(NSString * _Nonnull eventName) {
                                                 [self _cordovaFireJSFunction:tpaName funcFamily:@"tpa" string:eventName];
                                             }
                 ];
            }
        }
    }
    
    
    NSDictionary* attributes = [data objectForKey:@"attributes"];
    if(attributes && [attributes isKindOfClass:[NSDictionary class]]){
        NSArray* global = [attributes objectForKey:@"global"];
        if(global && [global isKindOfClass:[NSArray class]] && [global count] > 0){
            for (NSDictionary* att in global) {
                [params.data addSessionAttributes:att];
            }
        }
        NSArray* adjust = [attributes objectForKey:@"adjust"];
        if(adjust && [adjust isKindOfClass:[NSArray class]] && [adjust count] > 0){
            for (NSDictionary* att in adjust) {
                [params.data addSessionAdjustAttributes:att];
            }
        }
        NSArray* appsFlyer = [attributes objectForKey:@"appsFlyer"];
        if(appsFlyer && [appsFlyer isKindOfClass:[NSArray class]] && [appsFlyer count] > 0){
            for (NSDictionary* att in appsFlyer) {
                [params.data addSessionAppsFlyerAttributes:att];
            }
        }
        NSArray* branchio = [attributes objectForKey:@"branchio"];
        if(branchio && [branchio isKindOfClass:[NSArray class]] && [branchio count] > 0){
            for (NSDictionary* att in branchio) {
                [params.data addSessionBranchIOAttributes:att];
            }
        }
        NSArray* button = [attributes objectForKey:@"button"];
        if(button && [button isKindOfClass:[NSArray class]] && [button count] > 0){
            for (NSDictionary* att in button) {
                [params.data addSessionButtonAttributes:att];
            }
        }
        NSArray* kochava = [attributes objectForKey:@"kochava"];
        if(kochava && [kochava isKindOfClass:[NSArray class]] && [kochava count] > 0){
            for (NSDictionary* att in kochava) {
                [params.data addSessionKochavaAttributes:att];
            }
        }
    }
    NSArray* backViewSections = [data objectForKey:@"backViewSections"];
    if(backViewSections && [backViewSections isKindOfClass:[NSArray class]] && [backViewSections count] > 0){
        for (NSString* backViewSectionName in backViewSections) {
            [params.data defineBackViewSection:backViewSectionName];
        }
    }
    NSArray* moments = [data objectForKey:@"moments"];
    if(moments && [moments isKindOfClass:[NSArray class]] && [moments count] > 0){
        for (NSString* momentName in moments) {
            [params.data defineAppTrigger:momentName isActiveCallback:^(BOOL isActive) {
                [self _cordovaFireJSFunction:momentName funcFamily:@"atu" boolean:[NSNumber numberWithBool: isActive]];
            }];
        }
    }
    NSDictionary* advanced = [data objectForKey:@"advanced"];
    if(advanced && [advanced isKindOfClass:[NSDictionary class]]){
        
        NSArray* cases = [advanced objectForKey:@"cases"];
        if(cases && [cases isKindOfClass:[NSArray class]] && [cases count] > 0){
            for (NSArray* caseData in cases) {
                if(![caseData isKindOfClass:[NSArray class]] || [caseData count] != 2){
                    continue;
                }
                NSString* caseName = [caseData objectAtIndex:0];
                NSNumber* numOfStates = [caseData objectAtIndex:1];
                if(![self _isNSNumberInteger:numOfStates]){
                    continue;
                }
                [params.data defineCase:caseName withNumOfStates:[numOfStates integerValue]];
            }
        }
        NSArray* dynamicObjects = [advanced objectForKey:@"dynamicObjects"];
        if(dynamicObjects && [dynamicObjects isKindOfClass:[NSArray class]] && [dynamicObjects count] > 0){
            for (NSArray* doData in dynamicObjects) {
                if(![doData isKindOfClass:[NSArray class]] || [doData count] != 3){
                    continue;
                }
                NSString* doName = [doData objectAtIndex:0];
                NSNumber* doType = [doData objectAtIndex:1];
                NSObject* defaultValue = [doData objectAtIndex:2];
                if(![self _isNSNumberInteger:doType]){
                    continue;
                }
                [params.data defineDynamicObject:doName type:(ElastiCodeDObjType)[doType integerValue]  defaultValue:defaultValue];
            }
        }
    }
    return YES;
}
-(BOOL) _isNSNumberBool:(NSObject*) number {
    if(![number isKindOfClass:[NSNumber class]]){
        return NO;
    }
    return (strcmp([((NSNumber*)number) objCType], @encode(char)) == 0);
}
-(BOOL) _isNSNumberInteger:(NSObject*) number {
    if(![number isKindOfClass:[NSNumber class]]){
        return NO;
    }
    return (strcmp([((NSNumber*)number) objCType], @encode(int)) == 0) || (strcmp([((NSNumber*)number) objCType], @encode(NSInteger)) == 0);
}
#pragma mark - cordova helpers
-(BOOL) _cordovaValidateCommand:(CDVInvokedUrlCommand*)command requiredArgs:(int) requiredArgs{
    BOOL valid = ([[command arguments] count] == requiredArgs);
    if(!valid){
        [self _cordovaError:command];
    }
    return valid;
}
-(void) _cordovaOK:(CDVInvokedUrlCommand*)command{
    NSString* msg = (command.methodName? command.methodName : @"elasticode_OK");
    [self _cordovaOK:command withString:msg];
}
-(void) _cordovaOK:(CDVInvokedUrlCommand*)command withBool:(BOOL) boolValue{
    NSString* callbackId = [command callbackId];
    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsBool:boolValue];
    [self.commandDelegate sendPluginResult:result callbackId:callbackId];
}
-(void) _cordovaOK:(CDVInvokedUrlCommand*)command withInteger:(NSInteger) integerValue{
    NSString* callbackId = [command callbackId];
    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsInt:(int)integerValue];
    [self.commandDelegate sendPluginResult:result callbackId:callbackId];
}
-(void) _cordovaOK:(CDVInvokedUrlCommand*)command withDouble:(double) doubleValue{
    NSString* callbackId = [command callbackId];
    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsDouble:doubleValue];
    [self.commandDelegate sendPluginResult:result callbackId:callbackId];
}
-(void) _cordovaOK:(CDVInvokedUrlCommand*)command withString:(NSString*) stringValue{
    NSString* callbackId = [command callbackId];
    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsString:stringValue];
    [self.commandDelegate sendPluginResult:result callbackId:callbackId];
}
-(void) _cordovaOK:(CDVInvokedUrlCommand*)command withArray:(NSArray*) arrayValue{
    NSString* callbackId = [command callbackId];
    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsArray:arrayValue];
    [self.commandDelegate sendPluginResult:result callbackId:callbackId];
}
-(void) _cordovaError:(CDVInvokedUrlCommand*)command{
    NSString* callbackId = [command callbackId];
    NSString* msg = (command.methodName? command.methodName : @"elasticode_General");
    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_ERROR
                               messageAsString:msg];
    
    [self.commandDelegate sendPluginResult:result callbackId:callbackId];
}
-(void) _cordovaFireJSFunction:(NSString*) fucntionName funcFamily:(NSString*) family params:(NSDictionary*) params{
    NSString* paramsJson = [self _dictionaryToJSON:params];
    NSString* fireEvent = [NSString stringWithFormat:@"window.elasticode._actionsByName.%@['%@'](%@)", (family? family : @"global"),fucntionName, (paramsJson? paramsJson : @"")];
    [self.commandDelegate evalJs:fireEvent scheduledOnRunLoop:YES];
}
-(void) _cordovaFireJSFunction:(NSString*) fucntionName funcFamily:(NSString*) family string:(NSString*) string{
    NSString* fireEvent = [NSString stringWithFormat:@"window.elasticode._actionsByName.%@['%@']('%@')", (family? family : @"global"),fucntionName, (string? string : @"")];
    [self.commandDelegate evalJs:fireEvent scheduledOnRunLoop:YES];
}
-(void) _cordovaFireJSFunction:(NSString*) fucntionName funcFamily:(NSString*) family boolean:(NSNumber*) booleanNum{
    NSString* fireEvent = [NSString stringWithFormat:@"window.elasticode._actionsByName.%@['%@'](%@)", (family? family : @"global"),fucntionName, ([booleanNum boolValue]? @"true" : @"false")];
    [self.commandDelegate evalJs:fireEvent scheduledOnRunLoop:YES];
}
-(void) _cordovaFireJSEvent:(NSString*) eventName userInfo:(NSDictionary*) userInfo{
    NSString *userInfoJSON = [self _dictionaryToJSON:userInfo];
    NSString* fireEvent = [NSString stringWithFormat:@"document.dispatchEvent(new CustomEvent('%@', { detail: %@}))", eventName, (userInfoJSON ? userInfoJSON : @"false")];
    [self.commandDelegate evalJs:fireEvent scheduledOnRunLoop:YES];
}


@end
