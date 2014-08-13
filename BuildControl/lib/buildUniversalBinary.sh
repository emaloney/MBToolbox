#!/bin/bash

exitWithError()
{
	echo "error: $1"
	exit 2
}

UNDERLYING_PRODUCT="$PROJECT_NAME"

PRODUCTS_DIR="$PROJECT_DIR/Products/$UNDERLYING_PRODUCT"

# build the device binary
xcodebuild -scheme $UNDERLYING_PRODUCT clean build -destination 'generic/platform=iOS' > /dev/null
if [[ $? != 0 ]]; then
	exitWithError "Clean build of $UNDERLYING_PRODUCT for device failed"
fi

# build the simulator binary
xcodebuild -scheme $UNDERLYING_PRODUCT clean build -destination 'platform=iOS Simulator,name=iPad,OS=latest' > /dev/null
if [[ $? != 0 ]]; then
	exitWithError "Clean build of $UNDERLYING_PRODUCT for simulator failed"
fi

# make sure our expected libraries are there
LIBRARY_FILENAME_DEVICE="lib${UNDERLYING_PRODUCT}-device.a"
LIBRARY_FILENAME_SIM="lib${UNDERLYING_PRODUCT}-simulator.a"
if [[ ! -f "$PRODUCTS_DIR/$LIBRARY_FILENAME_DEVICE" ]]; then
	exitWithError "Failed to find built binary for $PRODUCTS_DIR/$LIBRARY_FILENAME_DEVICE"
fi
if [[ ! -f "$PRODUCTS_DIR/$LIBRARY_FILENAME_SIM" ]]; then
	exitWithError "Failed to find built binary for $PRODUCTS_DIR/$LIBRARY_FILENAME_SIM"
fi
if [[ ! -f "$PRODUCTS_DIR/$LIBRARY_FILENAME_DEVICE" || ! -f "$PRODUCTS_DIR/$LIBRARY_FILENAME_SIM" ]]; then
	exitWithError "Failed to find built binary for $LIBRARY_FILENAME_DEVICE or $LIBRARY_FILENAME_SIM"
fi

# clear out the old one
LIBRARY_FILENAME_UNIVERSAL="lib${UNDERLYING_PRODUCT}-universal.a"
if [[ -f "$PRODUCTS_DIR/$LIBRARY_FILENAME_UNIVERSAL" ]]; then
	rm "$PRODUCTS_DIR/$LIBRARY_FILENAME_UNIVERSAL"
fi

pushd "$PRODUCTS_DIR" > /dev/null
lipo -create libMBToolbox-device.a libMBToolbox-simulator.a -output libMBToolbox-universal.a
popd > /dev/null
