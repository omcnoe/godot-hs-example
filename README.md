Call Haskell code from Godot engine

Uses a C shim layer due to C++ ABI incompatibilities between Godot and Haskell on Windows. Other options are to build godot with libc++ (LLVM), or somehow build Haskell using MS VC++... neither sounds like a great time.

`godot <C++ ABI> hs-shim.dll <C ABI> hs-logic.dll`

1. Open x64 Native Tools Command Prompt
2. `cmake -G Ninja -S . -B build`
3. `cmake --build build && cmake --build build`

Double build required due to outstanding Ninja issue https://github.com/ninja-build/ninja/issues/1251
