// Copyright 2013 Google Inc.

#import <GoogleCast/GCKCastChannel.h>
#import <GoogleCast/GCKMediaCommon.h>

#ifdef USE_CAST_DYNAMIC_FRAMEWORK
#define GCKMediaControlChannelClass NSClassFromString(@"GCKMediaControlChannel")
#endif

@class GCKMediaInformation;
@class GCKMediaQueueItem;
@class GCKMediaStatus;
@class GCKMediaTextTrackStyle;

@protocol GCKMediaControlChannelDelegate;

/**
 * @file GCKMediaControlChannel.h
 * GCKMediaControlChannelResumeState enum.
 */

GCK_ASSUME_NONNULL_BEGIN

/**
 * The receiver application ID for the Default Media Receiver.
 */
#ifdef USE_CAST_DYNAMIC_FRAMEWORK
#define kGCKMediaDefaultReceiverApplicationID \
  GCK_EXTERN_NSSTRING(kGCKMediaDefaultReceiverApplicationID)
#else
GCK_EXTERN NSString *const kGCKMediaDefaultReceiverApplicationID;
#endif

/**
 * A GCKCastChannel subclass for media control operations.
 *
 * Any operations which apply to a currently active stream (play, pause, seek, stop, etc.) require
 * a valid (that is, non-nil) media status, or they will return @ref kGCKInvalidRequestID
 * and will not send the request. A media status is requested automatically when the channel
 * connects, is included with a successful load completed respose, and can also be updated at any
 * time. The media status can also become nil at any time; this will happen if the channel is
 * temporarily disconnected, for example. When using this channel, media status changes should be
 * monitored via the GCKMediaControlChannelDelegate::mediaControlChannelDidUpdateStatus: callback,
 * and methods which act on streams should be called only while the media status is non-nil.
 *
 * If a request is successfully started, the corresponding method returns the request ID that was
 * assigned to that request. If the request fails to start, the method returns
 * @ref kGCKInvalidRequestID and sets the #lastError property to indicate the
 * reason for the failure. If a request is successfully started but ultimately fails, the
 * GCKMediaControlChannelDelegate::mediaControlChannel:requestDidFailWithID:error: callback will be
 * invoked to indicate the failure.
 *
 * See GCKMediaControlChannelDelegate for the delegate protocol.
 *
 * @deprecated Use the GCKRemoteMediaClient property of the GCKCastSession to control media
 * playback.
 */
GCK_EXPORT
@interface GCKMediaControlChannel : GCKCastChannel

/**
 * The media status for the currently loaded media, if any; otherwise <code>nil</code>.
 */
@property(nonatomic, strong, readonly, GCK_NULLABLE) GCKMediaStatus *mediaStatus;

/**
 * The amount of time that has passed since the last media status update was received. If a
 * status request is currently in progress, this will be 0.
 */
@property(nonatomic, assign, readonly) NSTimeInterval timeSinceLastMediaStatusUpdate;

/**
 * The error detail from the last request, if any, or <code>nil</code> if the last request was
 * successful.
 */
@property(nonatomic, copy, readonly, GCK_NULLABLE) GCKError *lastError;

/**
 * The delegate for receiving notifications about changes in the channel's state.
 */
@property(nonatomic, weak, readwrite, GCK_NULLABLE) id<GCKMediaControlChannelDelegate> delegate;

/**
 * Designated initializer.
 */
- (instancetype)init;

/**
 * Loads and starts playback of a new media item.
 *
 * @param mediaInfo An object describing the media item to load.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)loadMedia:(GCKMediaInformation *)mediaInfo;

/**
 * Loads and optionally starts playback of a new media item.
 *
 * @param mediaInfo An object describing the media item to load.
 * @param autoplay Whether playback should start immediately.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)loadMedia:(GCKMediaInformation *)mediaInfo autoplay:(BOOL)autoplay;

/**
 * Loads and optionally starts playback of a new media item.
 *
 * @param mediaInfo An object describing the media item to load.
 * @param autoplay Whether playback should start immediately.
 * @param playPosition The initial playback position.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)loadMedia:(GCKMediaInformation *)mediaInfo
              autoplay:(BOOL)autoplay
          playPosition:(NSTimeInterval)playPosition;

/**
 * Loads and optionally starts playback of a new media item.
 *
 * @param mediaInfo An object describing the media item to load.
 * @param autoplay Whether playback should start immediately.
 * @param playPosition The initial playback position.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)loadMedia:(GCKMediaInformation *)mediaInfo
              autoplay:(BOOL)autoplay
          playPosition:(NSTimeInterval)playPosition
            customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Loads and optionally starts playback of a new media item.
 *
 * @param mediaInfo An object describing the media item to load.
 * @param autoplay Whether playback should start immediately.
 * @param playPosition The initial playback position.
 * @param activeTrackIDs An array of integers specifying the active tracks. May be <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)loadMedia:(GCKMediaInformation *)mediaInfo
              autoplay:(BOOL)autoplay
          playPosition:(NSTimeInterval)playPosition
        activeTrackIDs:(NSArray<NSNumber *> * GCK_NULLABLE_TYPE)activeTrackIDs;

/**
 * Loads and optionally starts playback of a new media item.
 *
 * @param mediaInfo An object describing the media item to load.
 * @param autoplay Whether playback should start immediately.
 * @param playPosition The initial playback position.
 * @param activeTrackIDs An array of integers specifying the active tracks. May be <code>nil</code>.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)loadMedia:(GCKMediaInformation *)mediaInfo
              autoplay:(BOOL)autoplay
          playPosition:(NSTimeInterval)playPosition
        activeTrackIDs:(NSArray<NSNumber *> * GCK_NULLABLE_TYPE)activeTrackIDs
            customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Sets the active tracks. Request will fail if there is no current media status.
 *
 * @param activeTrackIDs An array of integers specifying the active tracks.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 * May be <code>nil</code> or an empty array to set the active tracks to the empty list.
 */
- (NSInteger)setActiveTrackIDs:(NSArray<NSNumber *> * GCK_NULLABLE_TYPE)activeTrackIDs;

/**
 * Sets the text track style. Request will fail if there is no current media status.
 *
 * @param textTrackStyle The text track style. The style will not be changed if this is
 * <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)setTextTrackStyle:(GCKMediaTextTrackStyle * GCK_NULLABLE_TYPE)textTrackStyle;

/**
 * Pauses playback of the current media item. Request will fail if there is no current media status.
 *
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)pause;

/**
 * Pauses playback of the current media item. Request will fail if there is no current media status.
 *
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)pauseWithCustomData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Stops playback of the current media item. Request will fail if there is no current media status.
 * If a queue is currently loaded, it is removed.
 *
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)stop;

/**
 * Stops playback of the current media item. Request will fail if there is no current media status.
 * If a queue is currently loaded, it is removed.
 *
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)stopWithCustomData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Begins (or resumes) playback of the current media item. Playback always begins at the
 * beginning of the stream. Request will fail if there is no current media status.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)play;

/**
 * Begins (or resumes) playback of the current media item. Playback always begins at the
 * beginning of the stream. Request will fail if there is no current media status.
 *
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)playWithCustomData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Seeks to a new position within the current media item. Request will fail if there is no current
 * media status.
 *
 * @param position The new position from the beginning of the stream.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)seekToTimeInterval:(NSTimeInterval)position;

/**
 * Seeks to a new position within the current media item. Request will fail if there is no current
 * media status.
 *
 * @param position The new position interval from the beginning of the stream.
 * @param resumeState The action to take after the seek operation has finished.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)seekToTimeInterval:(NSTimeInterval)position
                    resumeState:(GCKMediaControlChannelResumeState)resumeState;

/**
 * Seeks to a new position within the current media item. Request will fail if there is no current
 * media status.
 *
 * @param position The new position from the beginning of the stream.
 * @param resumeState The action to take after the seek operation has finished.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)seekToTimeInterval:(NSTimeInterval)position
                    resumeState:(GCKMediaControlChannelResumeState)resumeState
                     customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Loads and optionally starts playback of a new queue of media items.
 *
 * @param queueItems An array of GCKMediaQueueItem instances to load. Must not be <code>nil</code>
 * or empty.
 * @param startIndex The index of the item in the items array that should be played first.
 * @param repeatMode The repeat mode for playing the queue.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueLoadItems:(NSArray<GCKMediaQueueItem *> *)queueItems
                 startIndex:(NSUInteger)startIndex
                 repeatMode:(GCKMediaRepeatMode)repeatMode;

/**
 * Loads and optionally starts playback of a new queue of media items.
 *
 * @param queueItems An array of GCKMediaQueueItem instances to load. Must not be <code>nil</code>
 * or empty.
 * @param startIndex The index of the item in the items array that should be played first.
 * @param repeatMode The repeat mode for playing the queue.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueLoadItems:(NSArray<GCKMediaQueueItem *> *)queueItems
                 startIndex:(NSUInteger)startIndex
                 repeatMode:(GCKMediaRepeatMode)repeatMode
                 customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Loads and optionally starts playback of a new queue of media items.
 *
 * @param queueItems An array of GCKMediaQueueItem instances to load. Must not be <code>nil</code>
 * or empty.
 * @param startIndex The index of the item in the items array that should be played first.
 * @param playPosition The initial playback position for the item when it is first played,
 * relative to the beginning of the stream. This value is ignored when the same item is played
 * again, for example when the queue repeats, or the item is later jumped to. In those cases the
 * item's startTime is used.
 * @param repeatMode The repeat mode for playing the queue.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueLoadItems:(NSArray<GCKMediaQueueItem *> *)queueItems
                 startIndex:(NSUInteger)startIndex
               playPosition:(NSTimeInterval)playPosition
                 repeatMode:(GCKMediaRepeatMode)repeatMode
                 customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Inserts a list of new media items into the queue.
 *
 * @param queueItems An array of GCKMediaQueueItem instances to insert. Must not be <code>nil</code>
 * or empty.
 * @param beforeItemID The ID of the item that will be located immediately after the inserted list.
 * If the value is @ref kGCKMediaQueueInvalidItemID, the inserted list will be appended to the end
 * of the queue.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueInsertItems:(NSArray<GCKMediaQueueItem *> *)queueItems
             beforeItemWithID:(NSUInteger)beforeItemID;

/**
 * Inserts a list of new media items into the queue.
 *
 * @param queueItems An array of GCKMediaQueueItem instances to insert. Must not be <code>nil</code>
 * or empty.
 * @param beforeItemID ID of the item that will be located immediately after the inserted list. If
 * the value is @ref kGCKMediaQueueInvalidItemID, the inserted list will be appended to the end of
 * the queue.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueInsertItems:(NSArray<GCKMediaQueueItem *> *)queueItems
             beforeItemWithID:(NSUInteger)beforeItemID
                   customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * A convenience method that inserts a single item into the queue.
 *
 * @param item The item to insert.
 * @param beforeItemID The ID of the item that will be located immediately after the inserted item.
 * If the value is @ref kGCKMediaQueueInvalidItemID, or does not refer to any item currently in the
 * queue, the inserted item will be appended to the end of the queue.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueInsertItem:(GCKMediaQueueItem *)item beforeItemWithID:(NSUInteger)beforeItemID;

/**
 * A convenience method that inserts a single item into the queue and makes it the current item.
 *
 * @param item The item to insert.
 * @param beforeItemID The ID of the item that will be located immediately after the inserted item.
 * If the value is @ref kGCKMediaQueueInvalidItemID, or does not refer to any item currently in the
 * queue, the inserted item will be appended to the end of the queue.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueInsertAndPlayItem:(GCKMediaQueueItem *)item
                   beforeItemWithID:(NSUInteger)beforeItemID;

/**
 * A convenience method that inserts a single item into the queue and makes it the current item.
 *
 * @param item The item to insert.
 * @param beforeItemID The ID of the item that will be located immediately after the inserted item.
 * If the value is @ref kGCKMediaQueueInvalidItemID, or does not refer to any item currently in the
 * queue, the inserted item will be appended to the end of the queue.
 * @param playPosition The initial playback position for the item when it is first played,
 * relative to the beginning of the stream. This value is ignored when the same item is played
 * again, for example when the queue repeats, or the item is later jumped to. In those cases the
 * item's startTime is used.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueInsertAndPlayItem:(GCKMediaQueueItem *)item
                   beforeItemWithID:(NSUInteger)beforeItemID
                       playPosition:(NSTimeInterval)playPosition
                         customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Updates the queue.
 *
 * @param queueItems The list of updated items.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueUpdateItems:(NSArray<GCKMediaQueueItem *> *)queueItems;

/**
 * Updates the queue.
 *
 * @param queueItems The list of updated items.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueUpdateItems:(NSArray<GCKMediaQueueItem *> *)queueItems
                   customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Removes a list of media items from the queue. If the queue becomes empty as a result, the current
 * media session will be terminated.
 *
 * @param itemIDs An array of media item IDs identifying the items to remove. Must not be
 * <code>nil</code> or empty.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueRemoveItemsWithIDs:(NSArray<NSNumber *> *)itemIDs;

/**
 * Removes a list of media items from the queue. If the queue becomes empty as a result, the current
 * media session will be terminated.
 *
 * @param itemIDs An array of media item IDs identifying the items to remove. Must not be
 * <code>nil</code> or empty.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueRemoveItemsWithIDs:(NSArray<NSNumber *> *)itemIDs
                          customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * A convenience method that removes a single item from the queue.
 *
 * @param itemID The ID of the item to remove.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message
 * could not be sent or if any of the parameters are invalid.
 */
- (NSInteger)queueRemoveItemWithID:(NSUInteger)itemID;

/**
 * Reorders a list of media items in the queue.
 *
 * @param queueItemIDs An array of media item IDs identifying the items to reorder. Must not be
 * <code>nil</code> or empty.
 * @param beforeItemID ID of the item that will be located immediately after the reordered list. If
 * the value is @ref kGCKMediaQueueInvalidItemID, or does not refer to any item currently in the
 * queue, the reordered list will be appended at the end of the queue.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueReorderItemsWithIDs:(NSArray<NSNumber *> *)queueItemIDs
               insertBeforeItemWithID:(NSUInteger)beforeItemID;

/**
 * Reorder a list of media items in the queue.
 *
 * @param queueItemIDs An array of media item IDs identifying the items to reorder. Must not be
 * <code>nil</code> or empty.
 * @param beforeItemID The ID of the item that will be located immediately after the reordered list.
 * If the value is @ref kGCKMediaQueueInvalidItemID, or does not refer to any item currently in the
 * queue, the reordered list will be moved to the end of the queue.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueReorderItemsWithIDs:(NSArray<NSNumber *> *)queueItemIDs
               insertBeforeItemWithID:(NSUInteger)beforeItemID
                           customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * A convenience method that moves a single item in the queue.
 *
 * @param itemID The ID of the item to move.
 * @param beforeItemID The ID of the item that will be located immediately after the reordered list.
 * If the value is @ref kGCKMediaQueueInvalidItemID, or does not refer to any item currently in the
 * queue, the item will be moved to the end of the queue.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueMoveItemWithID:(NSUInteger)itemID beforeItemWithID:(NSUInteger)beforeItemID;

/**
 * Jumps to the item with the specified ID in the queue.
 *
 * @param itemID The ID of the item to jump to.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent.
 */
- (NSInteger)queueJumpToItemWithID:(NSUInteger)itemID;

/**
 * Jumps to the item with the specified ID in the queue.
 *
 * @param itemID The ID of the item to jump to.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent.
 */
- (NSInteger)queueJumpToItemWithID:(NSUInteger)itemID
                        customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Jumps to the item with the specified ID in the queue.
 *
 * @param itemID The ID of the item to jump to.
 * @param playPosition The initial playback position for the item when it is first played,
 * relative to the beginning of the stream. This value is ignored when the same item is played
 * again, for example when the queue repeats, or the item is later jumped to. In those cases the
 * item's startTime is used.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent.
 */
- (NSInteger)queueJumpToItemWithID:(NSUInteger)itemID
                      playPosition:(NSTimeInterval)playPosition
                        customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Moves to the next item in the queue.
 *
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent.
 */
- (NSInteger)queueNextItem;

/**
 * Moves to the previous item in the queue.
 *
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent.
 */
- (NSInteger)queuePreviousItem;

/**
 * Sets the queue repeat mode.
 *
 * @param repeatMode The new repeat mode.
 * @return The request ID for this request, or @ref kGCKInvalidRequestID if the message could not be
 * sent or if any of the parameters are invalid.
 */
- (NSInteger)queueSetRepeatMode:(GCKMediaRepeatMode)repeatMode;

/**
 * Sets the stream volume. The request will fail if there is no current media session.
 *
 * @param volume The new volume, in the range [0.0 - 1.0].
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)setStreamVolume:(float)volume;

/**
 * Sets the stream volume. The request will fail if there is no current media session.
 *
 * @param volume The new volume, in the range [0.0 - 1.0].
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)setStreamVolume:(float)volume customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Sets whether the stream is muted. The request will fail if there is no current media session.
 *
 * @param muted Whether the stream should be muted or unmuted.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)setStreamMuted:(BOOL)muted;

/**
 * Sets whether the stream is muted. The request will fail if there is no current media session.
 *
 * @param muted Whether the stream should be muted or unmuted.
 * @param customData Custom application-specific data to pass along with the request. Must either
 * be an object that can be serialized to JSON using
 * <a href="https://goo.gl/0vd4Q2"><b>NSJSONSerialization</b></a>, or <code>nil</code>.
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)setStreamMuted:(BOOL)muted customData:(id GCK_NULLABLE_TYPE)customData;

/**
 * Requests updated media status information from the receiver.
 *
 * @return The request ID, or @ref kGCKInvalidRequestID if the message could not be sent.
 */
- (NSInteger)requestStatus;

/**
 * Returns the approximate stream position as calculated from the last received stream
 * information and the elapsed wall-time since that update. Returns 0 if the channel is not
 * connected or if no media is currently loaded.
 */
- (NSTimeInterval)approximateStreamPosition;

/**
 * Cancels an in-progress request. Cancelling a request does not prevent it from being executed;
 * it simply indicates that the calling application is no longer interested in the results of the
 * request, so any state associated with the tracking of the request will be cleared.
 *
 * @param requestID The ID of the request to cancel.
 * @return <code>YES</code> if the request was cancelled, or <code>NO</code> if there is no request
 * being tracked with the given ID.
 */
- (BOOL)cancelRequestWithID:(NSInteger)requestID;

@end

/**
 * The GCKMediaControlChannel delegate protocol.
 */
GCK_EXPORT
@protocol GCKMediaControlChannelDelegate <NSObject>

@optional

/**
 * Called when a request to load media has completed.
 *
 * @param mediaControlChannel The channel.
 * @param sessionID The unique media session ID that has been assigned to this media item.
 */
- (void)mediaControlChannel:(GCKMediaControlChannel *)mediaControlChannel
    didCompleteLoadWithSessionID:(NSInteger)sessionID;

/**
 * Called when a request to load media has failed.
 *
 * @param mediaControlChannel The channel.
 * @param error The load error.
 */
- (void)mediaControlChannel:(GCKMediaControlChannel *)mediaControlChannel
    didFailToLoadMediaWithError:(GCKError *)error;

/**
 * Called when updated player status information is received.
 *
 * @param mediaControlChannel The channel.
 */
- (void)mediaControlChannelDidUpdateStatus:(GCKMediaControlChannel *)mediaControlChannel;

/**
 * Called when updated queue status information is received.
 *
 * @param mediaControlChannel The channel.
 */
- (void)mediaControlChannelDidUpdateQueue:(GCKMediaControlChannel *)mediaControlChannel;

/**
 * Called when updated preload status is received.
 *
 * @param mediaControlChannel The channel.
 */
- (void)mediaControlChannelDidUpdatePreloadStatus:(GCKMediaControlChannel *)mediaControlChannel;

/**
 * Called when updated media metadata is received.
 *
 * @param mediaControlChannel The channel.
 */
- (void)mediaControlChannelDidUpdateMetadata:(GCKMediaControlChannel *)mediaControlChannel;

/**
 * Called when a request succeeds.
 *
 * @param mediaControlChannel The channel.
 * @param requestID The request ID that failed. This is the ID returned when the request was made.
 */
- (void)mediaControlChannel:(GCKMediaControlChannel *)mediaControlChannel
    requestDidCompleteWithID:(NSInteger)requestID;

/**
 * Called when a request is no longer being tracked because another request of the same type has
 * been issued by the application.
 *
 * @param mediaControlChannel The channel.
 * @param requestID The request ID that has been replaced. This is the ID returned when the request
 * was made.
 */
- (void)mediaControlChannel:(GCKMediaControlChannel *)mediaControlChannel
    didReplaceRequestWithID:(NSInteger)requestID;

/**
 * Called when a request is no longer being tracked because it has been explicitly cancelled.
 *
 * @param mediaControlChannel The channel.
 * @param requestID The request ID that has been cancelled. This is the ID returned when the request
 * was made.
 */
- (void)mediaControlChannel:(GCKMediaControlChannel *)mediaControlChannel
     didCancelRequestWithID:(NSInteger)requestID;

/**
 * Called when a request fails.
 *
 * @param mediaControlChannel The channel.
 * @param requestID The request ID that failed. This is the ID returned when the request was made.
 * @param error The error. If any custom data was associated with the error, it will be in the
 * error's userInfo dictionary with the key {@code kGCKErrorCustomDataKey}.
 */
- (void)mediaControlChannel:(GCKMediaControlChannel *)mediaControlChannel
       requestDidFailWithID:(NSInteger)requestID
                      error:(GCKError *)error;

@end

GCK_ASSUME_NONNULL_END
