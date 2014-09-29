## Mockingbird Documentation

This directory contains [automatically-generated Mockingbird API documentation](https://rawgit.com/gilt/MBToolbox/master/Documentation/html/index.html).


### Building

You can generate this documentation from within the Mockingbird Xcode project if you have [the **appledoc** utility](https://github.com/tomaz/appledoc) installed along with appledoc's default templates.

As of this writing, we recommend using appledoc 2.2 (build 963) available from:

	https://github.com/tomaz/appledoc/releases/tag/v2.2-963

When you build the documentation target in the Xcode project, the contents of this directory are deleted, and the documentation is re-generated using your local copy of the source code.

Documentation is generated as HTML, and as an Xcode-compatible docset bundle.

### Xcode Integration

When the documentation target is successfully built, the docset will be exposed to Xcode by copying it to:

	~/Library/Developer/Shared/Documentation/DocSets

This makes the Mockingbird documentation available from within Xcode, alongside all the standard Apple SDK documentation.

### Dash Integration

We're also fans of the [Dash](https://itunes.apple.com/us/app/dash-docs-snippets/id458034879?mt=12) documentation browser for Mac. So, we've also included Dash integration.

If we detect a Dash installation at `/Applications/Dash.app`, we'll also install the docset in Dash.
