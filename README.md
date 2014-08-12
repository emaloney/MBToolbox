**Master branch status:**

[![Build Status](https://travis-ci.org/gilt/mockingbird-toolbox.svg?branch=master)](https://travis-ci.org/gilt/mockingbird-toolbox)

# Mockingbird Toolbox

The Mockingbird Toolbox is a set of general-purpose utility code for use in iOS applications.

The Toolbox is the lowest-level module in the Mockingbird Library open-source project from Gilt Groupe.

![Gilt Tech logo](Documentation/images/gilt-tech-logo.png)

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

`MBThreadLocalStorage` provides an interface for safely sharing thread-local storage among unrelated units of code.

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

## Integrating with Mockingbird Toolbox

There are several ways you can make use of Mockingbird Toolbox:

* Embedding the Project File
* Building the Static Library — __*documentation coming soon*__
* Building the Framework — __*support coming soon*__ (only for iOS 8+)
* Using Cocoapods — __*support coming soon*__

### Embedding the Project File

You can add Mockingbird Toolbox to an existing Xcode project by embedding the `MBToolbox.xcodeproj` project file.

If your project relies on the default "Debug" and "Release" build configurations created by Xcode, your selection for that setting will cascade down to the Toolbox when it is built. This is handy if you find yourself needing to do debugging within the Toolbox itself.

When you embed the project file, you will need to modify your current project's build settings to ensure your targets can link against the library binary and Xcode can find the necessary header files.

Here's how you can incorporate Mockingbird Toolbox through project file embedding:

#### I. Embedding

1. In Xcode, Open the project file to which you want to add Mockingbird Toolbox. 

2. In the Navigator sidebar, select the first tab, the **Project Navigator**. You can display it quickly by pressing ⌘1.

3. Select the item representing your project in the Project Navigator. Unless you have a complicated project structure, your project will be the topmost item in the tree.

4. In the **File** menu, select "Add Files to...".

5. Locate the `MBToolbox.xcodeproj` file, select it, and press the **Add** button.

#### II. Build "MBToolbox"

Once you've embedded the project file, perform an Xcode build using the "MBToolbox" scheme.

Not only will this be a good sanity check to make sure everything's working as expected, a successful build ensures that the appropriate header files are copied to the `Products/MBToolbox/include` directory within your local copy of the `mockingbird-toolbox` repository.

Next, we'll be configuring Xcode to find those header files.

#### III. Header Files

1. With your project selected in the **Project Navigator**, select your project in the main portion of the window and select the **Build Settings** pane

2. Find the setting for "User Header Search Paths" and double-click the current value. This will pop up an editor for the setting's value.

3. In the lower-left corner of the editor, click the "+" button. A new text entry box will appear below any values already listed in the editor.

4. Enter the filesystem path pointing to the `Products/MBToolbox/include` directory within your local copy of the `mockingbird-toolbox` repository. This can be relative to the directory containing your project file, or it can be an absolute path. The exact value depends on where you've put `mockingbird-toolbox` in your filesystem.

#### IV. Dependencies & Linking

For each target in your project that will use the Toolbox, do the following:

1. With your project selected in the **Project Navigator**, select your target in the main portion of the window and select the **Build Phases** settings pane

2. In the "Target Dependencies" section, click the "+" button and add the `MBToolbox` library as a target dependency.

3. In "Link Binary With Libraries" section, click the "+" button and add `libMBToolbox.a`. 

#### V. You're done!

If you've successfully completed the steps above, you can now begin using Mockingbird Toolbox from within your project.

**Note:**  When you integrate Mockingbird Toolbox through project file embedding, you will need to reference headers with "user header" import notation, eg.:

```objc
	#import "MBDebug.h"
```

## About Mockingbird Toolbox

The Mockingbird Toolbox represents the foundation of the Mockingbird Library.

Over the years, Gilt Groupe has used and refined Mockingbird Library as the base platform for its various iOS projects.

![Mockingbird Library Module Layers](Documentation/images/mockingbird-module-layers.png)

Mockingbird began life as AppFramework, created by Jesse Boyes.

AppFramework found a home at Gilt Groupe and eventually became Mockingbird Library.

In recent years, Mockingbird Library has been developed and maintained by Evan Coyne Maloney, Gilt Groupe's principal iOS engineer.

### Copyright & License

Mockingbird Library and Mockingbird Toolbox © Copyright 2009-2014, Gilt Groupe.

Licensed under [the MIT license](LICENSE).
