//
//  OnboardingViewController.h
//  Onboard
//
//  Created by Mike on 8/17/14.
//  Copyright (c) 2014 Mike Amaral. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ECOnBoardingImageElement;
@class ECOnBoardingScreenTemplate;
@class ECOnBoardingOptions;
@interface ECOnboardingViewController : UIViewController <UIScrollViewDelegate, UIGestureRecognizerDelegate>

// Page Control
@property (nonatomic) BOOL hidePageControl;
@property (nonatomic, strong) UIPageControl *pageControl;
/**
 *  Create an onboard with template screens,
 *  and a completion handler that will be attached to the skip buttons
 */
+ (instancetype)onboardWithTemplateScreens:(NSArray *)screens
                                   options:(ECOnBoardingOptions*) options
                         completionHandler:(dispatch_block_t) completionBlock
                            skippedHandler:(dispatch_block_t) skippedBlock;
- (instancetype)initWithTemplateScreens:(NSArray *)screens options:(ECOnBoardingOptions*) options completionHandler:(dispatch_block_t) completionBlock skippedHandler:(dispatch_block_t) skippedBlock;

////////////////////////////////////////////////////////////////////

/**
 *  Page control bottom padding
 */
@property (nonatomic) CGFloat pageControlBottomPadding;

////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// Delegate methods for internal use.
- (void)moveNextPage;
- (void)movePreviousPage;
-(void)moveToPage:(NSInteger) page animated:(BOOL) animated;
//- (void)setCurrentPage:(ECOnBoardingScreenTemplate *)currentPage;
//- (void)setNextPage:(ECOnBoardingScreenTemplate *)nextPage;
////////////////////////////////////////////////////////////////////

@end

