# Mockingbird Toolbox

The Mockingbird Toolbox is a set of general-purpose utility code for use in iOS applications.

The Toolbox is the lowest-level module in the Mockingbird open-source project from Gilt Groupe.

## Highlights

The Mockingbird Toolbox includes:

### Battery & Power Monitoring

The `MBBatteryMonitor` class reports the device's power status and battery level, and also posts events through the `NSNotificationCenter` when these values change.

### Network Monitoring

The `MBNetworkMonitor` class provides details about the current status of the device's wifi and carrier network, and can also be configured to post `NSNotificationCenter` events as network status changes occur.

### Caching

Mockingbird Toolbox provides a simple but extensible caching architecture.

The `MBThreadsafeCache` class implements a basic memory cache that can be safely shared across threads.

A subclass, `MBFilesystemCache`, adds a filesystem backing store to the memory cache.

### Thread-Local Storage

The `MBThreadLocalStorage` provides an interface for safely sharing thread-local storage among unrelated units of code.

The class can also be used as a lock-free cache: Objects that are expensive to create, such as `NSDateFormatter` instances, can be cached in thread-local storage without incurring the locking overhead required by a shared object cache like `MBThreadsafeCache`.

### Regular Expressions

The Mockingbird Toolbox provides `NSString` and `NSMutableString` class extensions to help create, manipulate, and execute regular expressions.

These extensions make use of the `MBRegexCache` for reusing regular expressions, which can be expensive to create.

### Message Digests

The `MBMessageDigest` class provides a high-level API for generating MD5 and SHA-1 secure one-way hashes from strings, `NSData` instances, byte arrays, and files.

Class extensions for `NSString` and `NSData` are also provided to simplify creating message digests from existing objects.

### Network Activity Indicator

The `MBNetworkIndicator` class provides a mechanism to coordinate the display of the status bar network activity indicator.

### Colors

Mockingbird Toolbox includes various utilities for creating, examining, and manipulating colors.

### Images

The Toolbox contains a `UIImage` class extension that adds methods for scaling images, as well as a `UIView` class extension for capturing the contents of a view as a `UIImage`, `CIImage` or `CGImageRef`.

### Bitmaps

The `MBBitmapPixelPlane` class represents a plane of pixels that can be accessed individually, regardless of the underlying pixel format. This allows direct extraction and manipulation of pixel data within a bitmap.

### ...and more

That's just a quick summary.

For further details, start with [the Mockingbird Toolbox API documentation](https://rawgit.com/gilt/mockingbird-toolbox/master/Documentation/html/index.html).

## About Mockingbird Toolbox

The Mockingbird Toolbox represents the base set of components that comprise the Mockingbird Library.

![Mockingbird Library Module Layers](Documentation/images/mockingbird-module-layers.png)

Mockingbird began life as AppFramework, created by Jesse Boyes.

AppFramework found a home at Gilt Groupe and eventually became Mockingbird Library.

In recent years, Mockingbird Library has been developed and maintained by Evan Coyne Maloney, Gilt Groupe's principal iOS engineer.

### Copyright & License

Mockingbird Library © Copyright 2009-2014, Gilt Groupe.

Licensed under [the MIT license](LICENSE).
