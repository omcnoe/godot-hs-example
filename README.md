Call Haskell code from Godot engine
Due to C++ ABI incompatibilities between Godot and Haskell on Windows, uses a C shim layer. Other options are to build godot with libc++ (LLVM), or somehow build Haskell using MS VC++... neither sounds like a great time.

`godot <C++ ABI> hs-shim.dll <C ABI> hs-logic.dll`

1. Open x64 Native Tools Command Prompt
2. In `godot-cpp`, build the godot C++ project:
    ```
    cmake -G Ninja .
    cmake --build .
    ```
3. In root of repository:
    ```cabal build```
4. In `hs-shim`:
    1. Update hardcoded paths in `CMakeLists.txt`:
        ```
        GHC_INCLUDE_DIR
        HS_LOGIC_INCLUDE_DIR
        HS_LOGIC_LIB
        ```
    2. Build the shim:
        ```
        cmake -G Ninja .
        cmake --build .
        ```
5. Copy output files to godot project directory:
    ```
    hs-shim.gdextension -- extension definition used by godot
    hs-shim.dll         -- C++ shim layer
    hs-logic.dll        -- underlying Haskell logic
    ```
