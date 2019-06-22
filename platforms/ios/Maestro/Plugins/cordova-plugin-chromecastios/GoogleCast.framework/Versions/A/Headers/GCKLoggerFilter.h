// Copyright 2016 Google Inc.

#import <Foundation/Foundation.h>

#import <GoogleCast/GCKDefines.h>
#import <GoogleCast/GCKLoggerCommon.h>

GCK_ASSUME_NONNULL_BEGIN

/**
 * A class for filtering log messages that are produced using GCKLogger.
 *
 * @since 3.0
 */
GCK_EXPORT
@interface GCKLoggerFilter : NSObject

/**
 * A flag indicating whether the filter is exclusive (<code>YES</code>) or inclusive
 * (<code>NO</code>). By default filters are inclusive, that is, they accept all log messages that
 * match the filter.
 */
@property(nonatomic, assign, readwrite) BOOL exclusive;

/**
 * Constructs a new GCKLoggerFilter with empty criteria.
 */
- (instancetype)init;

/**
 * Adds a list of class names to be matched by the filter. A class name can be a simple name or the
 * name of an extension, for example, <code>@@"MyClass"</code> or
 * <code>@@"MyClass(MyExtension)"</code>. If an extension is not included in the name, all
 * extensions of the class will be included implicitly. Glob patterns are supported.
 */
- (void)addClassNames:(NSArray<NSString *> *)classNames;

/**
 * Adds a list of non-member function names to be matched by the filter. Glob patterns are
 * supported.
 */
- (void)addFunctionNames:(NSArray<NSString *> *)functionNames;

/**
 * Adds a list of regular expression patterns for matching the text of the log messages.
 */
- (void)addMessagePatterns:(NSArray<NSString *> *)messagePatterns;

/**
 * Adds a list of regular expression patterns for matching the text of the log messages with
 * optional case-insensitivity.
 */
- (void)addMessagePatterns:(NSArray<NSString *> *)messagePatterns
           caseInsensitive:(BOOL)caseInsensitive;

/**
 * Resets the filter; removing all match criteria.
 */
- (void)reset;

@end

GCK_ASSUME_NONNULL_END
