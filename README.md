![HBC Digital logo](https://raw.githubusercontent.com/gilt/Cleanroom/master/Assets/hbc-digital-logo.png)     
![Gilt Tech logo](https://raw.githubusercontent.com/gilt/Cleanroom/master/Assets/gilt-tech-logo.png)

# MBToolbox

The Mockingbird Toolbox is an Objective-C-based set of general-purpose utility code for use in iOS, macOS, tvOS and watchOS applications.
	
The Mockingbird Toolbox is the lowest-level module in the Gilt Groupe’s open source Mockingbird project.

MBToolbox is part of the Mockingbird Library from [Gilt Tech](http://tech.gilt.com).


### Xcode compatibility

This is the `master` branch. It **requires Xcode 8.3** to compile.


#### Current status

Branch|Build status
--------|------------------------
[`master`](https://github.com/emaloney/MBToolbox)|[![Build status: master branch](https://travis-ci.org/emaloney/MBToolbox.svg?branch=master)](https://travis-ci.org/emaloney/MBToolbox)


### License

MBToolbox is distributed under [the MIT license](https://github.com/emaloney/MBToolbox/blob/master/LICENSE).

MBToolbox is provided for your use—free-of-charge—on an as-is basis. We make no guarantees, promises or apologies. *Caveat developer.*


### Adding MBToolbox to your project

[![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)

The simplest way to integrate MBToolbox is with the [Carthage](https://github.com/Carthage/Carthage) dependency manager.

First, add this line to your [`Cartfile`](https://github.com/Carthage/Carthage/blob/master/Documentation/Artifacts.md#cartfile):

```
github "emaloney/MBToolbox" ~> 3.0.0
```

Then, use the `carthage` command to [update your dependencies](https://github.com/Carthage/Carthage#upgrading-frameworks).

Finally, you’ll need to [integrate MBToolbox into your project](https://github.com/emaloney/MBToolbox/blob/master/INTEGRATION.md) in order to use [the API](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/index.html) it provides.

Once successfully integrated, just add the following `import` statement to any Swift file where you want to use MBToolbox:

```swift
import MBToolbox
```

See [the Integration document](https://github.com/emaloney/MBToolbox/blob/master/INTEGRATION.md) for additional details on integrating MBToolbox into your project.


## MBToolbox Reference

The Mockingbird Toolbox includes the following tools, which are compatible with all four Apple platforms—iOS, macOS, tvOS and watchOS—except where noted otherwise:


### Battery & Power Monitoring

The [`MBBatteryMonitor`](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBBatteryMonitor.html) class (iOS only) reports the device's power status and battery level, and also posts events through the `NSNotificationCenter` when these values change.


### Network Monitoring

The [`MBNetworkMonitor`](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBNetworkMonitor.html) class (iOS, macOS, tvOS) provides details about the current status of the network, including:

* Whether the device currently has network connectivity
* Whether the device is currently connected via wifi

On iOS, the class also provides carrier information, such as:

* Whether the device has an associated cellular carrier account
* Whether the device is currently connected through a cellular carrier
* The type of the current cellular connection, if any (eg. GPRS, Edge, HSDPA, LTE, etc.)

The `MBNetworkMonitor` can also be configured to post `NSNotificationCenter` events as network status changes occur.


### Caching

Mockingbird Toolbox provides a simple but extensible caching architecture.

The base of this architecture is provided by [`MBThreadsafeCache`](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBThreadsafeCache.html), which implements a basic memory cache that can be safely shared across threads.

The `MBThreadsafeCache` does not implement an expiration policy. Instead, cache instances can be configured to purge themselves in response to memory warnings.

The [`MBFilesystemCache`](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBFilesystemCache.html) is a subclass of `MBThreadsafeCache` that adds a filesystem backing store to the memory cache.

The storage behavior of an `MBFilesystemCache` instance can be customized through the use of an `MBFilesystemCacheDelegate`. Delegates can be used to override serialization and deserialization of cache objects, and for controlling whether or not a given object is stored in the memory or filesystem component of the cache.

The `MBFilesystemCache` implements an age-based expiration mechanism, but the class also provides ample hooks for subclasses to supply alternate implementations.


### Concurrency & Threading

[The `MBConcurrentReadWriteCoordinator` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBConcurrentReadWriteCoordinator.html) uses Grand Central Dispatch to provide an efficient mechanism for enforcing orderly read/write access to a shared resource. The coordinator ensures that concurrent access to the shared resource follows consistent rules.

[The `MBThreadLocalStorage` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBThreadLocalStorage.html) provides an interface for safely sharing thread-local storage among unrelated units of code.

To prevent key clashes between different code using thread-local storage, values are accessed by specifying the requesting `Class`. Classes can store multiple values by providing an additional key string for each value.

The `MBThreadLocalStorage` class also provides methods that allow treating thread-local storage as a lock-free cache. Objects that are expensive to create, such as `NSDateFormatter` instances, can be cached in thread-local storage without incurring the locking overhead required by a shared object cache like `MBThreadsafeCache`.


### Regular Expressions

To simplify working with regular expressions on iOS, macOS, tvOS and watchOS, the Mockingbird Toolbox provides [an `NSString` class extension](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/NSString+MBRegex.html) and [an `NSMutableString` class extension](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/NSMutableString+MBRegex.html) to help create, manipulate, and execute regular expressions.

These extensions make use of [the `MBRegexCache` singleton](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBRegexCache.html) for caching regular expressions, which can be expensive to create.


### Message Digests

[The `MBMessageDigest` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBMessageDigest.html) provides a high-level API for generating MD5 and SHA-1 secure one-way hashes (also known as *message digests*). Message digests can be created from strings, `NSData` instances, byte arrays, and files.

Class extensions for [`NSString`](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/NSString+MBMessageDigest.html) and [`NSData`](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/NSData+MBMessageDigest.html) are also provided to simplify creating message digests from existing objects.


### Network Activity Indicator

The network activity indicator appearing in an iOS device's status bar is a shared resource the use of which needs to be coordinated if you have, say, multiple network operations running simultaneously on several threads.

The Toolbox provides [the `MBNetworkIndicator` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBNetworkIndicator.html) class (iOS only) to coordinate use of the status bar's network activity indicator.


### Colors

The Toolbox contains [a `UIColor` class extension](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/UIColor+MBToolbox.html) for iOS and tvOS that:

- Determines whether a color is opaque
- Determines whether a color is *light* or *dark* (depending on its brightness value)
- Can create an appropriate highlight color for a given color
- Can create a new color by adjusting an existing color's brightness

The `MBColorTools.h` header file defines a set of macro functions for creating `UIColor` and `CGColorRef` instances from individual 8-bit RGB and RGBA components, as well as from RGB and RGBA hexadecimal values.


### Images

The Toolbox contains a `UIImage` class extension compatible with iOS and tvOS that adds [methods for scaling images](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/UIImage+MBImageScaling.html), as well as [a `UIView` class extension](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/UIView+MBSnapshotImage.html) for capturing the contents of a view as a `UIImage`, `CIImage` or `CGImageRef`.


### Bitmaps

[The `MBBitmapPixelPlane` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBBitmapPixelPlane.html) represents a plane of pixels that can be accessed individually, regardless of the underlying pixel format. This allows direct extraction and manipulation of pixel data within a bitmap.

Empty `MBBitmapPixelPlane` instances can be created directly and populated manually. Instances can also be created using a source `UIImage`, `CGImage` or a bitmap-based `CGContextRef`.

You can use `MBBitmapPixelPlane` on iOS, macOS and tvOS.


### Runtime Services

Certain services available at runtime are expensive to leave enabled for the duration of an application's lifetime.

For example, just having the `UIDevice`'s `batteryMonitoringEnabled` property always set to `YES` can cause *additional* battery drain, because an app that would otherwise remain suspended in the background will instead be periodically activated to process `UIDeviceBatteryLevelDidChangeNotification` and `UIDeviceBatteryStateDidChangeNotification` event notifications.

The best practice for such services is to leave them disabled until they're needed, and then to disable them immediately once they’re needed no longer.

If multiple units of code need access to these services, some mechanism is needed to coordinate when these services should be enabled and disabled. 

[The `MBServiceManager` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBServiceManager.html) is designed for such cases.

Classes that provide interfaces for shared services adopt [the `MBService` protocol](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Protocols/MBService.html), and clients that need access to that service coordinate by *attaching to* and *detaching from* that service through the `MBServiceManager`.

The `MBBatteryMonitor` and `MBNetworkMonitor` classes are implemented as services in order to minimize their impact on the user's device.


### Rounded Rectangles

[The `MBRoundedRectTools` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBRoundedRectTools.html) provides a set of tools for handling rounded rectangles, including methods to help size corner radii based on rectangle size, and methods for creating `CGPathRef`s that can be used to draw rounded rectangles.


### String Formatting

Mockingbird Toolbox provides [an `NSString` class extension](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/NSString+MBIndentation.html) with methods to indent the individual lines within a string using a single tab, multiple tabs, or an arbitrary prefix string.

The static inline C function `MBForceString()` takes an `id` as a parameter and is guaranteed to return a non-`nil` `NSString`.

The static inline C function `MBTrimString()` takes an `id` as a parameter and is guaranteed to return a non-`nil` `NSString` with no leading or trailing whitespace or newline characters.

[The `MBFieldListFormatter` class](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Classes/MBFieldListFormatter.html) can be used to create lists of fields that are displayed in an easy-to-read format when rendered in a monospaced font.


### String Measurement

For iOS and tvOS, there's also [a `UIFont` class extension](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/Categories/UIFont+MBStringSizing.html) that provides a simple API for performing common text measurement tasks.


### ...and more

There's even more to Mockingbird Toolbox, but we want to leave you with at least a few treats to find on your own!

Discover more in the API documentation below, and also in the freely-available [Mockingbird Toolbox source code](https://github.com/emaloney/MBToolbox/).


### API documentation

For detailed information on using MBToolbox, [API documentation](https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/index.html) is available.


## About

Over the years, Gilt Groupe has used and refined Mockingbird Library as the base for its various Apple Platform projects.

Mockingbird began life as AppFramework, created by Jesse Boyes.

AppFramework found a home at Gilt Groupe and eventually became Mockingbird Library.

In recent years, Mockingbird Library has been developed and maintained by Evan Maloney.


### Acknowledgements

API documentation is generated using [appledoc](http://gentlebytes.com/appledoc/) from [Gentle Bytes](http://gentlebytes.com/).
