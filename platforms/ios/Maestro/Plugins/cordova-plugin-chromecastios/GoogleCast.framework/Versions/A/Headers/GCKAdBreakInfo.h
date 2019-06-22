// Copyright 2013 Google Inc.

#import <Foundation/Foundation.h>

#import <GoogleCast/GCKDefines.h>

/**
 * A class representing an ad break.
 *
 * @since 3.1
 */
@interface GCKAdBreakInfo : NSObject

/* The playback position, in seconds, at which this ad will start playing. */
@property(nonatomic, assign, readonly) NSTimeInterval playbackPosition;

/**
 * Designated initializer. Constructs a new GCKAdBreakInfo.
 * @param playbackPosition The playback position in seconds for this ad break.
 */
- (instancetype)initWithPlaybackPosition:(NSTimeInterval)playbackPosition;

@end
