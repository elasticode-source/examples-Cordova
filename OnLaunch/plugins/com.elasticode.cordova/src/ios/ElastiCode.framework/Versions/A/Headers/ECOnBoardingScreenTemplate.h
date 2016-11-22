//
//  ECOnBoardingScreenTemplate.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 2/11/15.
//  Copyright (c) 2015 Elasticode. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "ECOnBoardingElements.h"
#import "ECOnBoardingAction.h"


@class ECOnboardingViewController;
@class ECOnBoardingButtonElement;
@class ECOnBoardingSync;
@class ECScreenOptions;
@class ECOnBoardingOptions;
/**
 *  Basic on boarding template object
 */
@interface ECOnBoardingScreenTemplate : UIViewController

@property (nonatomic, weak) ECOnboardingViewController *delegate;
@property (nonatomic,strong) NSDictionary* templateFormat;

@property (nonatomic,assign) NSInteger templateHint;

@property (nonatomic,assign) NSInteger screenIndex;

@property (nonatomic,strong, readonly) NSArray *elementsOrder;
/** Action to trigger when on boarding finished */
@property (strong, nonatomic) dispatch_block_t completionAction;
/** Action to trigger when on boarding skipped */
@property (strong, nonatomic) dispatch_block_t skipAction;


// Labels
@property (nonatomic, strong) ECOnBoardingLabelElement* label1;
@property (nonatomic, strong) ECOnBoardingLabelElement* label2;
@property (nonatomic, strong) ECOnBoardingLabelElement* label3;
@property (nonatomic, strong) ECOnBoardingLabelElement* label4;

// Buttons
@property (nonatomic, strong) ECOnBoardingButtonElement *cta1Button;
@property (nonatomic, strong) ECOnBoardingButtonElement *cta2Button;
@property (nonatomic, strong) ECOnBoardingButtonElement *cta3Button;
@property (nonatomic, strong) ECOnBoardingButtonElement *cta4Button;

// Overlays
@property (nonatomic, strong) ECOnBoardingOverlayElement* overlay1;
@property (nonatomic, strong) ECOnBoardingOverlayElement* overlay2;
@property (nonatomic, strong) ECOnBoardingOverlayElement* overlay3;

// Images
@property (nonatomic, strong) ECOnBoardingImageElement* image1;
@property (nonatomic, strong) ECOnBoardingImageElement* image2;
@property (nonatomic, strong) ECOnBoardingImageElement* image3;
@property (nonatomic, strong) ECOnBoardingImageElement* image4;
@property (nonatomic, strong) ECOnBoardingImageElement* image5;

// Background
@property (nonatomic, strong) ECOnBoardingOverlayElement* background;

// Screen options
@property (nonatomic, strong) ECScreenOptions* options;

-(instancetype) initWithTemplateHint:(NSInteger) templateHint;

-(void) updateElementsInScreen:(NSArray*) elementsInScreen;

+(NSArray*) getScreensFromDictionary:(NSDictionary*) screensInfo withAdditionalActions:(NSArray*) additionalActions updateOptions:(ECOnBoardingOptions*) options;

/**
 *  Get updated screens from server, based on elasticode information
 *
 *  @return Array of screens
 */
+(NSArray*) getScreensFromServerWithTemplateHint:(NSInteger) templateHint onBoardingOptions:(ECOnBoardingOptions*) onBoardingOptions;

/**
 *  Update server about information in the given array of screens, 
 * to be set as default value for this onboarding
 *
 *  @param obSync            on boarding sync object.
 *  @param onBoardingScreens array of on boarding array screens.
 *
 *  @return YES if the on borading sync object managed to sync the screens with server,
 *  NO if something was missing
 */
-(BOOL) updateOBSync:(ECOnBoardingSync*) obSync WithScreens:(NSArray*) onBoardingScreens;

- (void)hideTransitionViews;

- (void)updateProgress:(CGFloat)progress isTransitionIn:(BOOL)isTransitionIn;

-(NSArray*) getViews;
-(CGFloat) screenIndicatorY;
@end
