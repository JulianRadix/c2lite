#!/usr/bin/env bash
# build.sh – Build C2Lite server and client on MinGW64
# Usage: ./build.sh [clean]

set -e                  # Exit on first error
set -u                  # Treat unset vars as errors

CC=gcc
CFLAGS="-Wall -O2 -s -mconsole"
LDFLAGS="-lws2_32"

SERVER_SRC="server/main.c server/server.c"
CLIENT_SRC="client/main.c client/client.c"

OUTPUT_SERVER="server.exe"
OUTPUT_CLIENT="client.exe"

if [[ "${1-}" == "clean" ]]; then
    echo "[*] Cleaning artifacts..."
    rm -f ${OUTPUT_SERVER} ${OUTPUT_CLIENT} server/*.o client/*.o
    exit 0
fi

echo "[*] Building server..."
$CC $CFLAGS $SERVER_SRC -o $OUTPUT_SERVER $LDFLAGS

echo "[*] Building client..."
$CC $CFLAGS $CLIENT_SRC -o $OUTPUT_CLIENT $LDFLAGS

echo "[+] Done. Artifacts:"
ls -1 ${OUTPUT_SERVER} ${OUTPUT_CLIENT}
