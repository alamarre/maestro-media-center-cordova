// Copyright 2013 Google Inc.

#import <Foundation/Foundation.h>

#import <GoogleCast/GCKDefines.h>

#ifdef USE_CAST_DYNAMIC_FRAMEWORK
#define GCKApplicationMetadataClass NSClassFromString(@"GCKApplicationMetadata")
#endif

@class GCKImage;
@class GCKSenderApplicationInfo;

GCK_ASSUME_NONNULL_BEGIN

/**
 * Information about a receiver application.
 */
GCK_EXPORT
@interface GCKApplicationMetadata : NSObject <NSCopying>

/** The application's unique ID. */
@property(nonatomic, copy, readonly) NSString *applicationID;

/** The application's name, in a format that is appropriate for display. */
@property(nonatomic, copy, readonly) NSString *applicationName;

/** Any icon images for the application, as an array of GCKImage objects. */
@property(nonatomic, copy, readonly, GCK_NULLABLE) NSArray<GCKImage *> *images;

/** The set of protocol namespaces supported by this application. */
@property(nonatomic, copy, readonly, GCK_NULLABLE) NSArray<NSString *> *namespaces;

/**
 * Information about the sender application that is the counterpart to the receiver application,
 * if any.
 */
@property(nonatomic, copy, readonly, GCK_NULLABLE) GCKSenderApplicationInfo *senderApplicationInfo;

/**
 * The identifier (app ID) of the sender application that is the counterpart to the receiver
 * application, if any.
 */
- (NSString *)senderAppIdentifier;

/**
 * The launch URL (URL scheme) for the sender application that is the counterpart to the receiver
 * application, if any.
 */
- (NSURL *)senderAppLaunchURL;

@end

GCK_ASSUME_NONNULL_END
