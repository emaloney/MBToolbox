# MBToolbox Breaking Changes

Mockingbird Project repositories adhere to [the semantic versioning system used by Carthage](https://github.com/Carthage/Carthage/blob/master/Documentation/Artifacts.md#version-requirement).

This system assigns version numbers with three independent integer values separated by periods:

    major.minor.patch

- When the *major version* is incremented, it reflects large-scale changes to the framework that are likely to introduce public API changes, possibly significant ones.
- An incremented the *minor version* usually signals additional functionality or minor rearchitecting, either of which *may* bring changes to the public API.
- An incremented *patch version* signals bugfixes and/or cleanup, but should **not** signal breaking API changes. (If a breaking change is made to the public API in a patch release, it is unintentional and should be considered a bug.)

## 1.1.0

- To provide optimal Swift interoperability, [nullability annotations](https://developer.apple.com/swift/blog/?id=25) have been added to the public API. This change introduces a new requirement, however:

- As of this version, **Xcode 6.3 or higher is required** to build this project.

- Previously, the `NSError` class extension provided a  `errorByAddingUserInfoKey:value:` method. This method is now `errorByAddingOrRemovingUserInfoKey:value:` to better reflect the fact that values can be removed from the user info dictionary by passing `nil` as the value argument.

