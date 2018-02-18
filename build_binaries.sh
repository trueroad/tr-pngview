#!/bin/sh

VERSION=0.0.0

rm -fr binary

set -e

make clean
make
mkdir -p binary/x64
mv pngview.exe binary/x64
cp README* LICENSE binary/x64
cd binary/x64
zip tr-pngview-${VERSION}-x64.zip *
cd ../..

make clean
make LDFLAGS_STATIC=-static
mkdir -p binary/x64-static
mv pngview.exe binary/x64-static
cp README* LICENSE binary/x64-static
cd binary/x64-static
zip tr-pngview-${VERSION}-x64-static.zip *
cd ../..

make clean
make API_STRINGS=ANSI
mkdir -p binary/x64-ansi
mv pngview.exe binary/x64-ansi

make clean
make HOST=i686-w64-mingw32
mkdir -p binary/x86
mv pngview.exe binary/x86
cp README* LICENSE binary/x86
cd binary/x86
zip tr-pngview-${VERSION}-x86.zip *
cd ../..

make clean
make HOST=i686-w64-mingw32 LDFLAGS_STATIC=-static
mkdir -p binary/x86-static
mv pngview.exe binary/x86-static
cp README* LICENSE binary/x86-static
cd binary/x86-static
zip tr-pngview-${VERSION}-x86-static.zip *
cd ../..

make clean
make HOST=i686-w64-mingw32 API_STRINGS=ANSI
mkdir -p binary/x86-ansi
mv pngview.exe binary/x86-ansi
