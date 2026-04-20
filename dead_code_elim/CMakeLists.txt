cmake_minimum_required(VERSION 3.16)
project(DeadCodeElim)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM: ${LLVM_DIR} version ${LLVM_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(DeadCodeElim MODULE
    dead_code_elim.cpp
)

target_compile_features(DeadCodeElim PRIVATE cxx_std_17)
set_target_properties(DeadCodeElim PROPERTIES PREFIX "" SUFFIX ".so")
