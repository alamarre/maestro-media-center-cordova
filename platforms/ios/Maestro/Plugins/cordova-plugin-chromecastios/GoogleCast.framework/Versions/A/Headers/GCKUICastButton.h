// Copyright 2015 Google Inc.

/** @cond ENABLE_FEATURE_GUI */

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

#import <GoogleCast/GCKCommon.h>
#import <GoogleCast/GCKDefines.h>

#ifdef USE_CAST_DYNAMIC_FRAMEWORK
#define GCKUICastButtonClass NSClassFromString(@"GCKUICastButton")
#endif

GCK_ASSUME_NONNULL_BEGIN

/**
 * A subclass of <a href="https://goo.gl/VK61wU"><b>UIButton</b></a> that implements a "Cast"
 * button.
 *
 * @since 3.0
 */
GCK_EXPORT
@interface GCKUICastButton : UIButton

/**
 * A flag that indicates whether a touch event on this button will trigger the display of the
 * Cast dialog that is provided by the framework. By default this property is set to
 * <code>YES</code>. If an application wishes to handle touch events itself, it should set the
 * property to <code>NO</code> and register an appropriate target and action for the touch event.
 */
@property(nonatomic, assign, readwrite) BOOL triggersDefaultCastDialog;

/**
 * Constructs a new GCKUICastButton using the given decoder.
 */
- (instancetype)initWithCoder:(NSCoder *)decoder;

/**
 * Constructs a new GCKUICastButton with the given frame.
 */
- (instancetype)initWithFrame:(CGRect)frame;

/**
 * Sets the icons for the active, inactive, and animated states of the button.
 */
- (void)setInactiveIcon:(UIImage *)inactiveIcon
             activeIcon:(UIImage *)activeIcon
         animationIcons:(NSArray<UIImage *> *)animationIcons;

@end

GCK_ASSUME_NONNULL_END

#endif  // TARGET_OS_IPHONE

/** @endcond */