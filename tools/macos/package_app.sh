#!/usr/bin/env bash
# ==============================================================================
# Zawra Browser — macOS App Bundle Packager
# Builds and structures a native Zawra.app bundle for macOS
# ==============================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

TARGET="${1:-aarch64-apple-darwin}"
BUILD_MODE="${2:-release}"
APP_NAME="Zawra"
APP_BUNDLE="${REPO_ROOT}/${APP_NAME}.app"

echo "==> Packaging macOS Application: ${APP_BUNDLE}"
echo "    Target:     ${TARGET}"
echo "    Build Mode: ${BUILD_MODE}"

# 1. Ensure target binary exists
BIN_PATH="${REPO_ROOT}/target/${TARGET}/${BUILD_MODE}/zawra-browser"
if [[ ! -f "${BIN_PATH}" ]]; then
    # Fallback to default cargo target directory
    BIN_PATH="${REPO_ROOT}/target/${BUILD_MODE}/zawra-browser"
fi

if [[ ! -f "${BIN_PATH}" ]]; then
    echo "==> Building ${APP_NAME} binary via cargo..."
    cargo build --manifest-path "${REPO_ROOT}/Cargo.toml" --target "${TARGET}" $([[ "${BUILD_MODE}" == "release" ]] && echo "--release")
    BIN_PATH="${REPO_ROOT}/target/${TARGET}/${BUILD_MODE}/zawra-browser"
fi

# 2. Create bundle directory layout
CONTENTS_DIR="${APP_BUNDLE}/Contents"
MACOS_DIR="${CONTENTS_DIR}/MacOS"
RESOURCES_DIR="${CONTENTS_DIR}/Resources"
FRAMEWORKS_DIR="${CONTENTS_DIR}/Frameworks"

rm -rf "${APP_BUNDLE}"
mkdir -p "${MACOS_DIR}" "${RESOURCES_DIR}" "${FRAMEWORKS_DIR}"

# 3. Copy executable
echo "==> Installing binary into bundle..."
cp "${BIN_PATH}" "${MACOS_DIR}/zawra-browser"
chmod +x "${MACOS_DIR}/zawra-browser"

# 4. Copy Info.plist and PkgInfo
echo "==> Installing bundle metadata..."
cp "${REPO_ROOT}/resources/macos/Info.plist" "${CONTENTS_DIR}/Info.plist"
echo -n "APPL????" > "${CONTENTS_DIR}/PkgInfo"

# 5. Copy UI assets if available
if [[ -f "${REPO_ROOT}/ui_shell.html" ]]; then
    cp "${REPO_ROOT}/ui_shell.html" "${RESOURCES_DIR}/"
fi
if [[ -f "${REPO_ROOT}/ui_shell.css" ]]; then
    cp "${REPO_ROOT}/ui_shell.css" "${RESOURCES_DIR}/"
fi

echo "==> Successfully created ${APP_BUNDLE}"
echo "    Execute with: open ${APP_BUNDLE}"
