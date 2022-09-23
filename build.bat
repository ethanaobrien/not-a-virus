@echo off
set PATH=%PATH%;G:\My Drive\koding klass\llvm-mingw-20220906-ucrt-x86_64\bin;G:\My Drive\koding klass\llvm-mingw-20220906-ucrt-x86_64\x86_64-w64-mingw32\bin

"G:\My Drive\koding klass\llvm-mingw-20220906-ucrt-x86_64\bin\g++" -static -lurlmon -mwindows -oapplication.exe main.cpp
