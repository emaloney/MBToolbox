#!/bin/bash

OUTPUT_DIR="$PROJECT_DIR/Products/$PRODUCT_NAME"
OUTPUT_INCLUDE_DIR="$PROJECT_DIR/Products/$PRODUCT_NAME/include"

# create the output dir if necessary
if [[ ! -e "$OUTPUT_DIR" ]]; then
    mkdir -p "$OUTPUT_DIR"
fi

# ensure a clean include dir
if [[ -e "$OUTPUT_INCLUDE_DIR" ]]; then
    rm -rf "$OUTPUT_INCLUDE_DIR/*"
elif [[ ! -e "$OUTPUT_INCLUDE_DIR" ]]; then
	mkdir -p "$OUTPUT_INCLUDE_DIR"
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
cp "$MAIN_PRODUCT_PATH" "$OUTPUT_DIR/$LIBRARY_FILENAME"

# copy the headers to the include directory
CODE_DIR="$PROJECT_DIR/Code"
find "$CODE_DIR" -name "*.h" ! -path "*/Private/*" -exec cp "{}" "$OUTPUT_INCLUDE_DIR/." \;

