## Overview

The Mockingbird Toolbox is a set of utility code for building iOS applications.

The Toolbox is part of the Mockingbird iOS open source project from Gilt Groupe.

Here's an overview of what's provided in the Toolbox:


### Battery & Power Monitoring

The [`MBBatteryMonitor`](Classes/MBBatteryMonitor.html) class reports the device's power status and battery level, and also posts events through the `NSNotificationCenter` when these values change.


### Network Monitoring

The [`MBNetworkMonitor`](Classes/MBNetworkMonitor.html) class provides details about the current status of the network, including:

* Whether the device currently has network connectivity
* Whether the device is currently connected via wifi
* Whether the device has an associated cellular carrier account
* Whether the device is currently connected through a cellular carrier
* The type of the current cellular connection, if any (eg. GPRS, Edge, HSDPA, LTE, etc.)

The `MBNetworkMonitor` can also be configured to post `NSNotificationCenter` events as network status changes occur.


### Caching

Mockingbird Toolbox provides a simple but extensible caching architecture.

The base of this architecture is provided by [`MBThreadsafeCache`](Classes/MBThreadsafeCache.html), which implements a basic memory cache that can be safely shared across threads.

The `MBThreadsafeCache` does not implement an expiration policy. Instead, cache instances can be configured to purge themselves in response to memory warnings.

The [`MBFilesystemCache`](Classes/MBFilesystemCache.html) is a subclass of `MBThreadsafeCache` that adds a filesystem backing store to the memory cache.

The storage behavior of an `MBFilesystemCache` instance can be customized through the use of an `MBFilesystemCacheDelegate`. Delegates can be used to override serialization and deserialization of cache objects, and for controlling whether or not a given object is stored in the memory or filesystem component of the cache.

The `MBFilesystemCache` implements an age-based expiration mechanism, but the class also provides ample hooks for subclasses to supply alternate implementations.


### Regular Expressions

To simplify working with regular expressions, the Mockingbird Toolbox provides [an `NSString` class extension](Categories/NSString+MBRegex.html) and [an `NSMutableString` class extension](Categories/NSMutableString+MBRegex.html) to help create, manipulate, and execute regular expressions.

These extensions make use of [the `MBRegexCache` singleton](Classes/MBRegexCache.html) for caching regular expressions, which can be expensive to create.


### Message Digests

[The `MBMessageDigest` class](Classes/MBMessageDigest.html) provides a high-level API for generating MD5 and SHA-1 secure one-way hashes (also known as *message digests*). Message digests can be created from strings, `NSData` instances, byte arrays, and files.

Class extensions for [`NSString`](Categories/NSString+MBMessageDigest.html) and [`NSData`](Categories/NSData+MBMessageDigest.html) are also provided to simplify creating message digests from existing objects.


### Network Activity Indicator

The network activity indicator that appears in the device's status bar is a shared resource the use of which needs to be coordinated if you have, say, multiple network operations running simultaneously on several threads.

The Toolbox provides [the `MBNetworkIndicator` class](Classes/MBNetworkIndicator.html) to coordinate use of the network activity indicator.


### Runtime Services

Certain services available at runtime are expensive to leave enabled for the duration of an application's lifetime.

For example, just having the `UIDevice`'s `batteryMonitoringEnabled` property always set to `YES` can cause *additional* battery drain, because an app that would otherwise remain suspended in the background will instead be periodically activated to process `UIDeviceBatteryLevelDidChangeNotification` and `UIDeviceBatteryStateDidChangeNotification` event notifications.

The best practice for such services is to leave them disabled until they're needed, and then to disable them immediately once they’re needed no longer.

If multiple units of code need access to these services, some mechanism is needed to coordinate when these services should be enabled and disabled. 

[The `MBServiceManager` class](Classes/MBServiceManager.html) is designed for such cases.

Classes that provide interfaces for shared services adopt [the `MBService` protocol](Protocols/MBService.html), and clients that need access to that service coordinate by *attaching to* and *detaching from* that service through the `MBServiceManager`.

The `MBBatteryMonitor` and `MBNetworkMonitor` classes are implemented as services in order to minimize their impact on the user's device.


### Colors

The Toolbox contains [a `UIColor` class extension](Categories/UIColor+MBToolbox.html) that:

- Determines whether a color is opaque
- Determines whether a color is *light* or *dark* (depending on its brightness value)
- Can create an appropriate highlight color for a given color
- Can create a new color by adjusting an existing color's brightness

The `MBColorTools.h` header file defines a set of macro functions for creating `UIColor` and `CGColorRef` instances from individual 8-bit RGB and RGBA components, as well as from RGB and RGBA hexadecimal values.


### Images

The Toolbox contains a `UIImage` class extension that adds [methods for scaling images](Categories/UIImage+MBImageScaling.html), as well as [a `UIView` class extension](UIView+MBSnapshotImage.html) for capturing the contents of a view as a `UIImage`, `CIImage` or `CGImageRef`.


### Bitmaps

[The `MBBitmapPixelPlane` class](Classes/MBBitmapPixelPlane.html) represents a plane of pixels that can be accessed individually, regardless of the underlying pixel format. This allows direct extraction and manipulation of pixel data within a bitmap.

Empty `MBBitmapPixelPlane` instances can be created directly and populated manually. Instances can also be created using a source `UIImage`, `CGImage` or a bitmap-based `CGContextRef`.


### Rounded Rectangles

[The `MBRoundedRectTools` class](Classes/MBRoundedRectTools.html) provides a set of tools for handling rounded rectangles, including methods to help size corner radii based on rectangle size, and methods for creating `CGPathRef`s that can be used to draw rounded rectangles.


### String Formatting

Mockingbird Toolbox provides [an `NSString` class extension](Categories/NSString+MBIndentation.html) with methods to indent the individual lines within a string using a single tab, multiple tabs, or an arbitrary prefix string.

The static inline C function `MBForceString()` takes an `id` as a parameter and is guaranteed to return a non-`nil` `NSString`.

The static inline C function `MBTrimString()` takes an `id` as a parameter and is guaranteed to return a non-`nil` `NSString` with no leading or trailing whitespace or newline characters.

Finally, [the `MBFieldListFormatter` class](Classes/MBFieldListFormatter.html) can be used to create lists of fields that are displayed in an easy-to-read format when rendered in a monospaced font.


### ...and more

There's even more to Mockingbird Toolbox, but we want to leave you with at least a few treats to find on your own!

Discover more in the API documentation below, and also in the freely-available [Mockingbird Toolbox source code](https://github.com/gilt/mockingbird-toolbox/).


## API Reference