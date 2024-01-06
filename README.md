Call Haskell code from Godot engine

1. Build godot-cpp using Haskell Clang and LLVM libc++
    1. `set PATH=C:\ghcup\ghc\9.6.3\mingw\bin;%PATH%`
    2. `cmake -G Ninja -S godot-cpp -B build`
    3. `cmake --build build`
2. Build Haskell project: `cabal build`
3. Copy required files into demo project directory
    * `godot-hs-example.dll`
    * `godot-hs-example.gdextension`
    * `libc++.dll`
    * `libunwind.dll`
