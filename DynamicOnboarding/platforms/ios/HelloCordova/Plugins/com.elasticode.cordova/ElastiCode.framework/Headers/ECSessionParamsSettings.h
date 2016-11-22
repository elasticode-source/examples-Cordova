//
//  ECSessionParamsSettings.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 22.3.2016.
//  Copyright © 2016 Elasticode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ElastiCode+PEnums.h"

/**
 *  Elasticode initialization settings
 */
@interface ECSessionParamsSettings : NSObject
NS_ASSUME_NONNULL_BEGIN

@property (nonatomic,strong) NSString* onLaunchVersion;
/**
 *  Set the log level of the ElastiCode SDK.
 Logs can show errors only (default): elastiCodeLogLevelErrors,
 or detailed log: elastiCodeLogLevelDetailed.
 *
 *  @param logLevel The log level: elastiCodeLogLevelErrors, elastiCodeLogLevelDetailed.
 */
-(void) setLogLevel:(ECLogLevel)logLevel;

#pragma mark - Session

/**
 *  Disable all Elasticode connection and run the SDK offline
 */
-(void) offlineMode;

/**
 *  Set the connection timeout for the ElastiCode SDK.
 *  Default value is 20 seconds, in case of slow internet connection.
 *  You can change to any positive number.
 *
 *  @param timeout The new timeout in seconds
 */
-(void) setConnectionTimeout:(NSUInteger) timeout;

/**
 *  Set the image download timeout for the ElastiCode SDK.
 *  Default value is 5 seconds, in case of slow internet connection.
 *  You can change to any positive number.
 *
 *  @param timeout The new timeout in seconds
 */
-(void) setImageDownloadTimeout:(NSUInteger) timeout;

/**
 *  Force not showing the on Launch moment
 *
 *  @param disable YES will disable; otherwise, NO
 */
-(void) disableOnLaunch:(BOOL) disable;
/**
 *  In case of timeout, Force not to disaply the "On device" experience
 *
 *  @param disable YES will disable; otherwise, NO
 */
-(void) onTimeoutDisableOnLaunch:(BOOL) disable;

/**
 *  Force not showing the backView
 *
 *  @param disable YES will disable; otherwise, NO
 */
-(void) disableBackView:(BOOL) disable;

/**
 *  Will dismiss moment before rotation, default is YES
 *  @param dismiss YES will dismiss moment on rotation; otherwise, NO
 */
-(void) shouldDismissMomentOnRotate:(BOOL) dismiss;

/** When device orientation not match the experience orientation, will not display experience, default is NO
 * @param allow NO will not display the experience; otherwise, YES
 */
-(void) allowOrientationMismatch:(BOOL)allow;

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
-(void) disableHTTPS:(BOOL)disable;
NS_ASSUME_NONNULL_END
@end
