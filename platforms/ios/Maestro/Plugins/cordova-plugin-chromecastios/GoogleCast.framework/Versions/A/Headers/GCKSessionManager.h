// Copyright 2015 Google Inc.

#import <GoogleCast/GCKCommon.h>
#import <GoogleCast/GCKDefines.h>

#ifdef USE_CAST_DYNAMIC_FRAMEWORK
#define GCKSessionManagerClass NSClassFromString(@"GCKSessionManager")
#endif

@class GCKCastSession;
@class GCKDevice;
@class GCKSession;
@protocol GCKSessionManagerListener;

GCK_ASSUME_NONNULL_BEGIN

#ifdef USE_CAST_DYNAMIC_FRAMEWORK
#define kGCKKeyConnectionState GCK_EXTERN_NSSTRING(kGCKKeyConnectionState)
#else
GCK_EXTERN NSString *const kGCKKeyConnectionState;
#endif

/**
 * A class that manages sessions. The method @ref startSessionWithDevice: is used to
 * create a new session with a given GCKDevice. The session manager uses the GCKDeviceProvider
 * for that device type to construct a new GCKSession object, to which it then delegates all
 * session requests.
 *
 * GCKSessionManager handles the automatic resumption of suspended sessions (that is, resuming
 * sessions that were ended when the application went to the background, or in the event that
 * the application crashed or was forcibly terminated by the user). When the application resumes or
 * restarts, the session manager will wait for a short time for the device provider of the suspended
 * session's device to discover that device again, and if it does, it will attempt to reconnect to
 * that device and re-establish the session automatically.
 *
 * If the application has created a GCKUICastButton without providing a target and selector, then a
 * user tap on the button will display the default Cast dialog and it will automatically start
 * and stop sessions based on user selection or disconnection of a device.
 * If however the application is providing its own device selection/control dialog UI, then it
 * should use the GCKSessionManager directly to create and control sessions.
 *
 * Whether or not the application uses the GCKSessionManager to control sessions, it can attach a
 * GCKSessionManagerListener to be notified of session events, and can also use KVO to monitor the
 * #connectionState property to track the current session lifecycle state.
 *
 * @since 3.0
 */
GCK_EXPORT
@interface GCKSessionManager : NSObject

/** The current session, if any. */
@property(nonatomic, strong, readonly, GCK_NULLABLE) GCKSession *currentSession;

/** The current cast session, if any. */
@property(nonatomic, strong, readonly, GCK_NULLABLE) GCKCastSession *currentCastSession;

/** The current session connection state. */
@property(nonatomic, assign, readonly) GCKConnectionState connectionState;

/**
 * Starts a new session with the given device. This is an asynchronous operation.
 *
 * @param device The device to use for this session.
 * @return <code>YES</code> if the operation has been started successfully, <code>NO</code> if
 * there is a session currently established or if the operation could not be started.
 */
- (BOOL)startSessionWithDevice:(GCKDevice *)device;

/**
 * Suspends the current session. This is an asynchronous operation.
 *
 * @param reason The reason for the suspension.
 * @return <code>YES</code> if the operation has been started successfully, <code>NO</code> if
 * there is no session currently established or if the operation could not be started.
 */
- (BOOL)suspendSessionWithReason:(GCKConnectionSuspendReason)reason;

/**
 * Ends the current session. This is an asynchronous operation.
 *
 * @return <code>YES</code> if the operation has been started successfully, <code>NO</code> if
 * there is no session currently established or if the operation could not be started.
 */
- (BOOL)endSession;

/**
 * Ends the current session, optionally stopping casting. This is an asynchronous operation.
 *
 * @param stopCasting Whether casting of content on the receiver should be stopped when the session
 * is ended.
 * @return <code>YES</code> if the operation has been started successfully, <code>NO</code> if
 * there is no session currently established or if the operation could not be started.
 */
- (BOOL)endSessionAndStopCasting:(BOOL)stopCasting;

/**
 * Tests if a session is currently being managed by this session manager, and it is currently
 * connected. This will be <code>YES</code> if the session state is
 * @ref GCKConnectionStateConnected.
 */
- (BOOL)hasConnectedSession;

/**
 * Tests if a Cast session is currently being managed by this session manager, and it is currently
 * connected. This will be <code>YES</code> if the session state is @ref GCKConnectionStateConnected
 * and the session is a Cast session.
 */
- (BOOL)hasConnectedCastSession;

/**
 * Adds a listener for receiving notifications.
 *
 * @param listener The listener to add.
 */
- (void)addListener:(id<GCKSessionManagerListener>)listener;

/**
 * Removes a listener that was previously added with @ref addListener:.
 *
 * @param listener The listener to remove.
 */
- (void)removeListener:(id<GCKSessionManagerListener>)listener;

@end

/**
 * The GCKSessionManager listener protocol. The protocol's methods are all optional. All of the
 * notification methods come in two varieties: one that is invoked for any session type, and one
 * that is invoked specifically for Cast sessions.
 *
 * Listeners are invoked in the order that they were registered. GCKSessionManagerListener instances
 * which are registered by components of the framework itself (such as GCKUIMediaController), will
 * always be invoked <i>after</i> those that are registered by the application for the callbacks
 * GCKSessionManagerListener::sessionManager:willStartSession:,
 * GCKSessionManagerListener::sessionManager:willStartCastSession:,
 * GCKSessionManagerListener::sessionManager:willResumeSession:, and
 * GCKSessionManagerListener::sessionManager:willResumeCastSession:; and <i>before</i> those
 * that are registered by the application for all of the remaining callbacks.
 *
 * @since 3.0
 */
GCK_EXPORT
@protocol GCKSessionManagerListener <NSObject>

@optional

/**
 * Called when a session is about to be started.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager willStartSession:(GCKSession *)session;

/**
 * Called when a session has been successfully started.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager didStartSession:(GCKSession *)session;

/**
 * Called when a Cast session is about to be started.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    willStartCastSession:(GCKCastSession *)session;

/**
 * Called when a Cast session has been successfully started.
 *
 * @param sessionManager The session manager.
 * @param session The Cast session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    didStartCastSession:(GCKCastSession *)session;

/**
 * Called when a session is about to be ended, either by request or due to an error.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager willEndSession:(GCKSession *)session;

/**
 * Called when a session has ended, either by request or due to an error.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 * @param error The error, if any; otherwise nil.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
         didEndSession:(GCKSession *)session
             withError:(NSError * GCK_NULLABLE_TYPE)error;

/**
 * Called when a Cast session is about to be ended, either by request or due to an error.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    willEndCastSession:(GCKCastSession *)session;

/**
 * Called when a Cast session has ended, either by request or due to an error.
 *
 * @param sessionManager The session manager.
 * @param session The Cast session.
 * @param error The error, if any; otherwise nil.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
     didEndCastSession:(GCKCastSession *)session
             withError:(NSError * GCK_NULLABLE_TYPE)error;

/**
 * Called when a session has failed to start.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 * @param error The error.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    didFailToStartSession:(GCKSession *)session
                withError:(NSError *)error;

/**
 * Called when a Cast session has failed to start.
 *
 * @param sessionManager The session manager.
 * @param session The Cast session.
 * @param error The error.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    didFailToStartCastSession:(GCKCastSession *)session
                    withError:(NSError *)error;

/**
 * Called when a session has been suspended.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 * @param reason The reason for the suspension.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
     didSuspendSession:(GCKSession *)session
            withReason:(GCKConnectionSuspendReason)reason;

/**
 * Called when a Cast session has been suspended.
 *
 * @param sessionManager The session manager.
 * @param session The Cast session.
 * @param reason The reason for the suspension.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    didSuspendCastSession:(GCKCastSession *)session
               withReason:(GCKConnectionSuspendReason)reason;

/**
 * Called when a session is about to be resumed.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager willResumeSession:(GCKSession *)session;

/**
 * Called when a session has been successfully resumed.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager didResumeSession:(GCKSession *)session;

/**
 * Called when a Cast session is about to be resumed.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    willResumeCastSession:(GCKCastSession *)session;

/**
 * Called when a Cast session has been successfully resumed.
 *
 * @param sessionManager The session manager.
 * @param session The Cast session.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
    didResumeCastSession:(GCKCastSession *)session;

/**
 * Called when updated device volume and mute state for a session have been received.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 * @param volume The current volume, in the range [0.0, 1.0].
 * @param muted The current mute state.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
                   session:(GCKSession *)session
    didReceiveDeviceVolume:(float)volume
                     muted:(BOOL)muted;
/**
 * Called when updated device volume and mute state for a Cast session have been received.
 *
 * @param sessionManager The session manager.
 * @param session The Cast session.
 * @param volume The current volume, in the range [0.0, 1.0].
 * @param muted The current mute state.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
               castSession:(GCKCastSession *)session
    didReceiveDeviceVolume:(float)volume
                     muted:(BOOL)muted;

/**
 * Called when updated device status for a session has been received.
 *
 * @param sessionManager The session manager.
 * @param session The session.
 * @param statusText The new device status text.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
                   session:(GCKSession *)session
    didReceiveDeviceStatus:(NSString * GCK_NULLABLE_TYPE)statusText;

/**
 * Called when updated device status for a Cast session has been received.
 *
 * @param sessionManager The session manager.
 * @param session The Cast session.
 * @param statusText The new device status text.
 */
- (void)sessionManager:(GCKSessionManager *)sessionManager
               castSession:(GCKCastSession *)session
    didReceiveDeviceStatus:(NSString * GCK_NULLABLE_TYPE)statusText;

@end

GCK_ASSUME_NONNULL_END
