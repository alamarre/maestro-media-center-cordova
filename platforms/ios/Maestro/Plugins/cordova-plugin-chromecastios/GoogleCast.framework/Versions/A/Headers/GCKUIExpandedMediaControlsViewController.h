// Copyright 2016 Google Inc.

/** @cond ENABLE_FEATURE_GUI */

#import <GoogleCast/GCKDefines.h>
#import <GoogleCast/GCKUIMediaButtonBarProtocol.h>

#if TARGET_OS_IPHONE

GCK_ASSUME_NONNULL_BEGIN

/**
 * A view controller which implements the expanded controls fullscreen view.
 *
 * @since 3.1
 */
GCK_EXPORT
@interface GCKUIExpandedMediaControlsViewController : UIViewController <GCKUIMediaButtonBarProtocol>
@end

GCK_ASSUME_NONNULL_END

#endif  // TARGET_OS_IPHONE

/** @endcond */
