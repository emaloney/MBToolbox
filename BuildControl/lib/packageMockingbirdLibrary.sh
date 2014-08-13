#!/bin/bash

PRODUCTS_DIR="$PROJECT_DIR/Products/$PRODUCT_NAME"
HEADERS_DIR="$PRODUCTS_DIR/Headers"

# create the output dir if necessary
if [[ ! -e "$PRODUCTS_DIR" ]]; then
    mkdir -p "$PRODUCTS_DIR"
fi

# ensure a clean include dir
if [[ -e "$HEADERS_DIR" ]]; then
    rm -rf "$HEADERS_DIR/*"
elif [[ ! -e "$HEADERS_DIR" ]]; then
	mkdir -p "$HEADERS_DIR"
fi

# figure out what to call this thingamajiggy
case $PLATFORM_NAME in
	iphonesimulator)
		LIBRARY_FILENAME="lib${PRODUCT_NAME}-simulator.a"
		;;

	iphoneos)
		LIBRARY_FILENAME="lib${PRODUCT_NAME}-device.a"
		;;
		
	*)
		LIBRARY_FILENAME="lib${PRODUCT_NAME}-${PLATFORM_NAME}.a"
		;;
esac

# copy the product to the output directory
MAIN_PRODUCT_PATH="$BUILT_PRODUCTS_DIR/$FULL_PRODUCT_NAME"
cp "$MAIN_PRODUCT_PATH" "$PRODUCTS_DIR/$LIBRARY_FILENAME"

# copy the headers to the include directory
find "$PROJECT_DIR/Code" -name "*.h" ! -path "*/Private/*" -exec cp "{}" "$HEADERS_DIR/." \;

