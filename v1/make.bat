@echo off
SET PKG_CONFIG_PATH=C:\msys64\mingw64\lib\pkgconfig
SET PATH=%PATH%;c:/msys64/mingw64/bin/;c:/msys64/usr/bin/
c:/msys64/mingw64/bin/mingw32-make.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
