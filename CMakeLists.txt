cmake_minimum_required(VERSION 3.28)
project(hs-shim LANGUAGES C CXX)


# build godot-cpp
add_subdirectory(godot-cpp)


# paths for ghc and hs-logic
execute_process(COMMAND ghc --numeric-version OUTPUT_VARIABLE GHC_VER)
string(REGEX REPLACE "\n$" "" GHC_VER ${GHC_VER})
string(REGEX REPLACE "\\\\" "/" GHCUP_INSTALL_BASE_PREFIX $ENV{GHCUP_INSTALL_BASE_PREFIX})
string(REGEX REPLACE "/$" "" GHCUP_INSTALL_BASE_PREFIX ${GHCUP_INSTALL_BASE_PREFIX})
set(GHC_INCLUDE_DIR "${GHCUP_INSTALL_BASE_PREFIX}/ghcup/ghc/${GHC_VER}/include")
execute_process(
    COMMAND cabal list-bin hs-logic
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE HS_LOGIC_BIN_DIR
)
string(REGEX REPLACE "\\\\" "/" HS_LOGIC_BIN_DIR ${HS_LOGIC_BIN_DIR})
string(REGEX REPLACE "/[^/]*\n$" "" HS_LOGIC_BIN_DIR ${HS_LOGIC_BIN_DIR})
set(HS_LOGIC_INCLUDE_DIR "${HS_LOGIC_BIN_DIR}/hs-logic-tmp")
set(HS_LOGIC_DLL         "${HS_LOGIC_BIN_DIR}/hs-logic.dll")
set(HS_LOGIC_LIB         "${HS_LOGIC_BIN_DIR}/hs-logic.dll.a")
message("")
message("GHC_INCLUDE_DIR       = ${GHC_INCLUDE_DIR}")
message("HS_LOGIC_BIN_DIR      = ${HS_LOGIC_BIN_DIR}")
message("HS_LOGIC_INCLUDE_DIR  = ${HS_LOGIC_INCLUDE_DIR}")
message("HS_LOGIC_LIB          = ${HS_LOGIC_LIB}")


# build Haskell project with cabal
file(GLOB_RECURSE HS_LOGIC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
add_custom_command(
    OUTPUT ${HS_LOGIC_LIB}
    COMMAND cabal build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${HS_LOGIC_SOURCES}
)
add_custom_target(hs-logic DEPENDS ${HS_LOGIC_LIB})


# build hs-shim C++ library
add_library(hs-shim SHARED
    src/hs-shim/register_types.cpp
)
add_dependencies(hs-shim hs-logic)
target_include_directories(hs-shim
    SYSTEM
    PRIVATE
    ${GHC_INCLUDE_DIR}
    ${HS_LOGIC_INCLUDE_DIR}
)
target_compile_features(hs-shim PRIVATE cxx_std_17)
target_link_libraries(hs-shim
    godot::cpp
    ${HS_LOGIC_LIB}
)


# copy gdextension files to demo
add_custom_command(
    TARGET hs-shim
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${HS_LOGIC_DLL} "${CMAKE_CURRENT_SOURCE_DIR}/demo"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:hs-shim> "${CMAKE_CURRENT_SOURCE_DIR}/demo"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/src/hs-shim/hs-shim.gdextension" "${CMAKE_CURRENT_SOURCE_DIR}/demo"
)
