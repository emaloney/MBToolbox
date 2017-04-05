#!/bin/bash

# set -x

# constant values
DOCSET_PLATFORM_FAMILY="iphoneos"

# allow the APPLEDOC_PATH environment variable to override
# the default installation location of the appledoc tool
if [[ -z "$APPLEDOC_PATH" ]]; then
	APPLEDOC_PATH=`which appledoc`
fi
if [[ -z "$APPLEDOC_PATH" ]]; then
	APPLEDOC_PATH=/usr/local/bin/appledoc
fi
if [[ -z "$APPLEDOC_PATH" || ! -x "$APPLEDOC_PATH" ]]; then
	printf "error: 'appledoc' must be installed in order to generate documentation.

		You may download it from:

			https://github.com/tomaz/appledoc"
	exit 1
fi

exitWithError()
{
	echo "error: $1"
	exit 2
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
	mkdir -p "$2"
	
	touch "$1"
	cp -R "$1" "$2"
	if [[ $? != 0 ]]; then
		exitWithError "Couldn't install documentation from $1 at: $2"
	fi
}

# settings
DOCSET_PUBLISHER_ID="com.gilt.mockingbird.documentation"
DOCSET_BUNDLE_ID="${DOCSET_PUBLISHER_ID}.MBToolbox"
DOCSET_FILENAME="${DOCSET_BUNDLE_ID}.docset"
TEMP_DIR=`mktemp -d`
APPLEDOC_OUTPUT_DIR="${TEMP_DIR}/appledoc-generated"
INDEX_OUTPUT_FILE="${TEMP_DIR}/README-rewritten.md"
HTML_OUTPUT_DIR="${APPLEDOC_OUTPUT_DIR}/html"
HTML_INSTALL_DIR="Documentation/API"
DOCSET_OUTPUT_DIR="${APPLEDOC_OUTPUT_DIR}/docset"
DOCSET_INSTALL_DIR="Documentation/docsets/${DOCSET_FILENAME}"
ONLINE_ROOT_URL="https://rawgit.com/emaloney/MBToolbox/master/Documentation/API/"

# verify that we can find the source code
SOURCE_DIR="Sources"
if [[ -z "$SOURCE_DIR" || ! -d "$SOURCE_DIR" ]]; then
	exitWithError "Couldn't find source directory: $SOURCE_DIR";
fi

# rewrite the links in the README.md file to work properly in the docset
cat "$SOURCE_DIR/README.md" | sed sq${ONLINE_ROOT_URL}qqg > "${INDEX_OUTPUT_FILE}"

# create the documentation
find "$SOURCE_DIR" -name "*.h" ! -path "*/Private/*" -print0 | xargs -0 \
$APPLEDOC_PATH \
	--output "$APPLEDOC_OUTPUT_DIR" \
	--clean-output \
	--project-name "MBToolbox" \
	--project-company "Gilt Groupe" \
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

echo "Success!"