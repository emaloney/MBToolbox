![Gilt Tech logo](Documentation/images/gilt-tech-logo.png)

# Mockingbird Toolbox

The Mockingbird Toolbox is a set of general-purpose utility code for use in iOS applications.

The Toolbox is the lowest-level module in the Mockingbird Library open-source project from Gilt Groupe.

**Master branch status:**

[![Build Status](https://travis-ci.org/gilt/mockingbird-toolbox.svg?branch=master)](https://travis-ci.org/gilt/mockingbird-toolbox)

## Highlights

The Mockingbird Toolbox includes:

### Battery & Power Monitoring

The `MBBatteryMonitor` class reports the device’s power status and battery level, and also posts events through the `NSNotificationCenter` when these values change.

### Network Monitoring

The `MBNetworkMonitor` class provides details about the current status of the device’s wifi and carrier network, and can also be configured to post `NSNotificationCenter` events as network status changes occur.

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

That’s just a quick summary.

For further details, start with [the Mockingbird Toolbox API documentation](https://rawgit.com/gilt/mockingbird-toolbox/master/Documentation/html/index.html).

## Integrating with Mockingbird Toolbox

There are several ways you can make use of Mockingbird Toolbox:

* [Embedding the Project File](#embedding-the-project-file)
* [Building the Static Libraries](#building-the-static-libraries)
* Using Cocoapods — __*support coming soon*__

### Embedding the Project File

You can add Mockingbird Toolbox to an existing Xcode project by embedding the `MBToolbox.xcodeproj` project file.

If your project relies on the default “Debug” and “Release” build configurations created by Xcode, your selection for that setting will cascade down to the Toolbox when it is built. This is handy if you find yourself needing to do debugging within the Toolbox itself.

When you embed the project file, you will need to modify your current project’s build settings to ensure your targets can link against the library binary and Xcode can find the necessary header files.

Here’s how you can incorporate Mockingbird Toolbox through project file embedding:

#### I. Embedding

1. In Xcode, Open the project file to which you want to add Mockingbird Toolbox. 

2. In the Navigator sidebar, select the first tab, the **Project Navigator**. You can display it quickly by pressing ⌘1.

3. Select the item representing your project in the Project Navigator. Unless you have a complicated project structure, your project will be the topmost item in the tree.

4. In the **File** menu, select “Add Files to...”.

5. Locate the `MBToolbox.xcodeproj` file, select it, and press the **Add** button.

#### II. Build “MBToolbox”

Once you’ve embedded the project file, perform an Xcode build using the “MBToolbox” scheme.

Not only will this be a good sanity check to make sure everything’s working as expected, a successful build ensures that the appropriate header files are copied to the `Products/MBToolbox/Headers` directory within your local copy of the `mockingbird-toolbox` repository.

#### III. Configure Build Settings

1. With your project selected in the **Project Navigator**, select your project in the main portion of the window and select the **Build Settings** pane

2. Find the setting for “User Header Search Paths” and double-click the current value. This will pop up an editor for the setting’s value. In the lower-left corner of the editor, click the “+” button. A new text entry box will appear below any values already listed in the editor.

3. Enter the filesystem path pointing to the `Products/MBToolbox/Headers` directory within your local copy of the `mockingbird-toolbox` repository. This can be relative to the directory containing your project file, or it can be an absolute path. The exact value depends on where you’ve put `mockingbird-toolbox` in your filesystem.

4. Now, find the “Other Linker Flags” build setting. Double-click the current value to bring up the editor, and then click the “+” button to add a new linker flag.

5. Add the value `-ObjC` to the linker flags if it isn't there already.

#### IV. Dependencies & Linking

For each target in your project that will use the Toolbox, do the following:

1. With your project selected in the **Project Navigator**, select your target in the main portion of the window and select the **Build Phases** settings pane

2. In the “Target Dependencies” section, click the “+” button and add the `MBToolbox` library as a target dependency.

3. In “Link Binary With Libraries” section, click the “+” button and add `libMBToolbox.a`. 

#### V. You’re done!

If you’ve successfully completed the steps above, you can now begin using Mockingbird Toolbox from within your project.

**Note:**  When you integrate Mockingbird Toolbox through project file embedding, you will need to reference headers with “user header” import notation, eg.:

```objc
	#import "MBDebug.h"
```

### Building the Static Libraries

You can build Mockingbird Toolbox as one of three types of static libraries:

* A *device binary*, intended for use on iOS devices such as iPhones and iPads

* A *simulator binary*, intended for use with Xcode and the iOS Simulator running on a Macintosh

* A *universal binary*, which combines both the device and simulator binaries into a single library

In most cases, if you’re going to use a static library, you’ll want to go with the universal binary.

It’s far more convenient to link against the universal binary than it is to set up your builds to include the device binary when building for the device and the simulator binary when building for the simulator.

The downside to the universal binary is that is roughly double the size of the device binary alone.

So, unless you use `lipo` to remove the simulator architectures from the static library when building distribution binaries, you’re going to be adding unnecessary overhead to your shipping applications.

#### Device and Simulator Binaries

Selecting the “MBToolbox” build scheme allows you to build either the device binary or the simulator binary.

* Xcode will build the device binary if an iOS device run destination is selected. The run destination may be the generic “iOS Device”, or the name of an actual iOS device connected to the Macintosh.

* If some iOS Simulator variant is selected as the run destination, Xcode will build the simulator binary.

#### Universal Binary

You can build the universal binary using the “MBToolboxUniversal” scheme.

When building the universal binary, the any iOS-compatible run destination (i.e., device or simulator) may be selected.

#### Building

Choose the appropriate build scheme and run destination for the type of binary you want.

Then, select “Build” from Xcode’s **Product** menu or press ⌘B to build the static library.

#### Output

If no errors occur, you will find the static library in the `Products/MBToolbox` directory within your local copy of the `mockingbird-toolbox` repository.

* `libMBToolbox-device.a` is the library for use on iOS devices

* `libMBToolbox-simulator.a` is the library for use in the iOS Simulator developer tool

* `libMBToolbox-universal.a` is the universal binary, usable on device and in the simulator

* The `Headers` directory contains `.h` files necessary for developing with Mockingbird Toolbox

#### Integrating

Once you've built the static library you want to use, you will need to add the library binary and the header files to your project.

1. In Xcode, Open the project file to which you want to add Mockingbird Toolbox. 

2. In the Navigator sidebar, select the first tab, the **Project Navigator**. You can display it quickly by pressing ⌘1.

3. Find the “Other Linker Flags” build setting. Double-click the current value to bring up the editor, and then click the “+” button to add a new linker flag.

4. Add the value `-ObjC` to the linker flags if it isn't there already.

5. Copy `Headers` directory and the appropriate library file from within `Products/MBToolbox` into a new directory within your project.

6. Drag the new directory onto your project within the Xcode **Project Navigator**. This will bring up a dialog box allowing you to select the targets to which the Mockingbird Toolbox will be added. Select the appropriate checkbox(es) and click the **Finish** button.

If you’ve successfully completed the steps above, you can now begin using Mockingbird Toolbox from within your project.

**Note:**  When you integrate Mockingbird Toolbox using a static library, you will need to reference headers with “user header” import notation, eg.:

```objc
	#import "MBDebug.h"
```

## About Mockingbird Toolbox

The Mockingbird Toolbox represents the foundation of the Mockingbird Library.

Over the years, Gilt Groupe has used and refined Mockingbird Library as the base platform for its various iOS projects.

![Mockingbird Library Module Layers](Documentation/images/mockingbird-module-layers.png)

Mockingbird began life as AppFramework, created by Jesse Boyes.

AppFramework found a home at Gilt Groupe and eventually became Mockingbird Library.

In recent years, Mockingbird Library has been developed and maintained by Evan Coyne Maloney, Gilt Groupe’s principal iOS engineer.

### Copyright & License

Mockingbird Library and Mockingbird Toolbox © Copyright 2009-2014, Gilt Groupe.

Licensed under [the MIT license](LICENSE).
