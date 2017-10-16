#!/bin/bash

set -o pipefail

if [[ $# != 2 ]]; then
	echo "error: Expecting 2 arguments; <operation> <platform>"
	exit 1
fi

OPERATION="$1"
PLATFORM="$2"

SCRIPT_NAME=$(basename "$0")
SCRIPT_DIR=$(cd "$PWD" ; cd `dirname "$0"` ; echo "$PWD")

source "${SCRIPT_DIR}/include-common.sh"

BUILD_ACTION="clean $(testActionForPlatform $PLATFORM)"
DESTINATION=$(runDestinationForPlatform $PLATFORM)

( set -o pipefail && xcodebuild -project MBToolbox.xcodeproj -configuration Debug -scheme "MBToolbox" -destination "$DESTINATION" -destination-timeout 300 $BUILD_ACTION 2>&1 | tee "MBToolbox-$PLATFORM-$OPERATION.log" | xcpretty )
XCODE_RESULT="${PIPESTATUS[0]}"
if [[ "$XCODE_RESULT" == "0" ]]; then
	rm "MBToolbox-$PLATFORM-$OPERATION.log"
	exit 0
fi

exit $XCODE_RESULT
