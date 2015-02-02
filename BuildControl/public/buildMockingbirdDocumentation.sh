#!/bin/bash

# set -x

# constant values
DOCSET_PUBLISHER_NAME="Gilt Groupe"
DOCSET_PUBLISHER_ID="com.gilt.documentation"
DOCSET_PLATFORM_FAMILY="iphoneos"

# allow the APPLEDOC_PATH environment variable to override
# the default installation location of the appledoc tool
if [[ -z "$APPLEDOC_PATH" ]]; then
	APPLEDOC_PATH=/usr/local/bin/appledoc
fi
if [[ -z "$APPLEDOC_PATH" || ! -x "$APPLEDOC_PATH" ]]; then
	printf "error: 'appledoc' must be installed in order to generate documentation.\n\n\t\tYou may download it from:\n\n\t\t\thttps://github.com/tomaz/appledoc"
	exit 1
fi

exitWithError()
{
	echo "error: $1"
	exit 2
}

exitWithMissingArgValue()
{
	exitWithError "The --$1 argument was specified, but no value was provided; this argument requires a value"
}

validateArgValue()
{
	if [[ -z "$2" ]]; then
		exitWithError "The --$1 argument was not specified; this argument is required"
	fi
}

removeStaleDocumentation()
{
	if [[ -d "$1" ]]; then
		rm -rf "$1"
		if [[ $? != 0 ]]; then
			exitWithError "Couldn't remove stale documentation at: $1"
		fi
	fi
}

installDocumentation()
{
	if [[ ! -d "$1" ]]; then
		exitWithError "Expected to find appledoc-generated documentation at: $1"
	fi

	removeStaleDocumentation "$2"
	
	touch "$1"
	cp -R "$1" "$2"
	if [[ $? != 0 ]]; then
		exitWithError "Couldn't install documentation from $1 at: $2"
	fi
}

# process the command-line arguments
while [[ $1 ]]; do
	case $1 in

	--module)
		shift
		if [[ -z "$1" ]]; then
			exitWithMissingArgValue module
		fi
		MOCKINGBIRD_MODULE=$1
		;;

	-*)
		exitWithError "Unrecognized argument: $1"
		;;
		
	esac
	shift
done

# make sure we got the expected command-line args
validateArgValue module "$MOCKINGBIRD_MODULE"

# derived values
DOCSET_FEEDNAME="Mockingbird $MOCKINGBIRD_MODULE"
DOCSET_BUNDLE_ID="${DOCSET_PUBLISHER_ID}.Mockingbird-${MOCKINGBIRD_MODULE/ /-}"
APPLEDOC_OUTPUT_DIR="${TARGET_TEMP_DIR}/appledoc-generated"
INDEX_OUTPUT_FILE="${TARGET_TEMP_DIR}/README-rewritten.md"
HTML_OUTPUT_DIR="${APPLEDOC_OUTPUT_DIR}/html"
HTML_INSTALL_DIR="${PROJECT_DIR}/Documentation/html"
DOCSET_OUTPUT_DIR="${APPLEDOC_OUTPUT_DIR}/docset"
DOCSET_FILENAME="${DOCSET_BUNDLE_ID}.docset"
DOCSET_INSTALL_DIR="${PROJECT_DIR}/Documentation/${DOCSET_FILENAME}"
XCODE_DOCSET_INSTALL_DIR="${HOME}/Library/Developer/Shared/Documentation/DocSets/${DOCSET_FILENAME}"
ONLINE_ROOT_URL="https://rawgit.com/emaloney/${PROJECT_NAME}/master/Documentation/html/"

# verify that we can find the code
CODE_DIR="${PROJECT_DIR}/Code"
if [[ -z "$CODE_DIR" || ! -d "$CODE_DIR" ]]; then
	exitWithError "Couldn't find source directory: $CODE_DIR";
fi

# rewrite the links in the Code/README.md file to work properly in the docset
cat "${PROJECT_DIR}/Code/README.md" | sed sq${ONLINE_ROOT_URL}qqg > "${INDEX_OUTPUT_FILE}"

# create the documentation
find "$CODE_DIR" -name "*.h" ! -path "*/Private/*" -print0 | xargs -0 \
$APPLEDOC_PATH \
	--output "$APPLEDOC_OUTPUT_DIR" \
	--clean-output \
	--project-name "$DOCSET_FEEDNAME" \
	--project-company "$DOCSET_PUBLISHER_NAME" \
	--company-id "$DOCSET_PUBLISHER_ID" \
	--docset-bundle-id "$DOCSET_BUNDLE_ID" \
	--docset-platform-family "$DOCSET_PLATFORM_FAMILY" \
	--create-html \
	--create-docset \
	--install-docset \
	--keep-intermediate-files \
	--keep-undocumented-objects \
	--keep-undocumented-members \
	--no-repeat-first-par \
	--no-merge-categories \
	--logformat xcode \
	--index-desc "${INDEX_OUTPUT_FILE}" > /dev/null

if [[ $? != 0 ]]; then
	echo "warning: HTML documentation generation finished with errors or warnings."
fi

# install the HTML and docset in the project's Documentation dir
installDocumentation "$HTML_OUTPUT_DIR" "$HTML_INSTALL_DIR"
installDocumentation "$DOCSET_OUTPUT_DIR" "$DOCSET_INSTALL_DIR"

# install the docset in Xcode
installDocumentation "$DOCSET_OUTPUT_DIR" "$XCODE_DOCSET_INSTALL_DIR"

# if we find the Dash app, install there, too
if [[ -d /Applications/Dash.app ]]; then
	open -a /Applications/Dash.app "$XCODE_DOCSET_INSTALL_DIR"
fi
