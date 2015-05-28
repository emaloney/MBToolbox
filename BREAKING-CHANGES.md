# MBToolbox Breaking Changes

Mockingbird Project repositories adhere to [the semantic versioning system used by Carthage](https://github.com/Carthage/Carthage/blob/master/Documentation/Artifacts.md#version-requirement).

This system assigns version numbers with three independent integer values separated by periods:

    major.minor.patch

- When the *major version* is incremented, it reflects large-scale changes to the framework that are likely to introduce public API changes, possibly significant ones.
- An incremented the *minor version* usually signals additional functionality or minor rearchitecting, either of which *may* bring changes to the public API.
- An incremented *patch version* signals bugfixes and/or cleanup, but should **not** signal breaking API changes. (If a breaking change is made to the public API in a patch release, it is unintentional and should be considered a bug.)

## 1.1.0

- To provide optimal Swift interoperability, [nullability annotations](https://developer.apple.com/swift/blog/?id=25) have been added to the public API. This change introduces a new requirement, however: **as of this version, _Xcode 6.3 or higher is required_ to build the project.**

- Previously, the `NSError` class extension provided an  `errorByAddingUserInfoKey:value:` method. This method now has the signature `errorByAddingOrRemovingUserInfoKey:value:` to reflect the fact that values can be removed from the user info dictionary by passing `nil` as the value argument.

- `MBModuleLog` has been reworked to provide hooks for specifying a custom log implementation. (For example, this mechanism allows the creation of bridging code to plug in external loggers such as [CleanroomLogger](https://github.com/emaloney/CleanroomLogger) to record log messages sent through Mockingbird.)

- Various logging macros provided in `MBDebug.h` have been removed and replaced with new ones declared in `MBModuleLogMacros.h`. The new macros allow the use of the new functionality provided by `MBModuleLog` and adopt the `MB` naming prefix to help avoid namespace clashes. There is a one-to-one mapping between the old, now-removed macros and the new ones:

Old Macro|New Macro|Comments
---------|---------|--------
`errorLog(`...`)`|`MBLogError(`...`)`|
`errorObj(`_object_`)`|`MBLogErrorObject(`_object_`)`|
`errorStr(`_string_`)`|`MBLogErrorString(`_string_`)`|
`consoleLog(`...`)`|`MBLogInfo(`...`)`|
`consoleTrace()`|`MBLogInfoTrace()`|
`consoleObj(`_object_`)`|`MBLogInfoObject(`_object_`)`|
`consoleStr(`_string_`)`|`MBLogInfoString(`_string_`)`|
`debugLog(`...`)`|`MBLogDebug(`...`)`|As before, you must still `#define` a boolean `DEBUG_LOCAL` constant in any `.m` file that references this macro. Logging will occur when `DEBUG_LOCAL` is `YES` (or non-zero). 
`debugTrace()`|`MBLogDebugTrace()`|*see above*
`debugObj(`_object_`)`|`MBLogDebugObject(`_object_`)`|*see above*
`debugStr(`_string_`)`|`MBLogDebugString(`_string_`)`|*see above*
`verboseDebugLog(`...`)`|`MBLogVerbose(`...`)`|As before, you must still `#define` the boolean constants `DEBUG_LOCAL` and `DEBUG_VERBOSE` in any `.m` file that references this macro. Logging will occur when `DEBUG_LOCAL` and `DEBUG_VERBOSE` are both `YES` (or non-zero).
`verboseDebugTrace()`|`MBLogVerboseTrace()`|*see above*
`verboseDebugObj(`_object_`)`|`MBLogVerboseObject(`_object_`)`|*see above*
`verboseDebugStr(`_string_`)`|`MBLogVerboseString(`_string_`)`|*see above*

- The `exceptionLog(`_exception_`)` macro has been removed and has not been replaced with a direct analogue; use `MBLogErrorObject(`_exception_`)` instead.
