cmake_minimum_required(VERSION 3.28)
project(hs-shim LANGUAGES C CXX)

set(GHC_INCLUDE_DIR      C:/ghcup/ghc/9.6.3/include)
set(HS_LOGIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dist-newstyle/build/x86_64-windows/ghc-9.6.3/godot-hs-example-0.1.0.0/f/hs-logic/build/hs-logic/hs-logic-tmp)
set(HS_LOGIC_LIB         ${CMAKE_CURRENT_SOURCE_DIR}/../dist-newstyle/build/x86_64-windows/ghc-9.6.3/godot-hs-example-0.1.0.0/f/hs-logic/build/hs-logic/hs-logic.dll.a)

add_library(hs-shim SHARED
    register_types.cpp
)
target_include_directories(hs-shim SYSTEM
    PRIVATE
    ../godot-cpp/gdextension
    ../godot-cpp/gen/include
    ../godot-cpp/include
    ${GHC_INCLUDE_DIR}
    ${HS_LOGIC_INCLUDE_DIR}
)
target_link_libraries(hs-shim
    ../godot-cpp/bin/godot-cpp.windows.debug.64
    ${HS_LOGIC_LIB}
)
target_compile_features(hs-shim PRIVATE cxx_std_17)
