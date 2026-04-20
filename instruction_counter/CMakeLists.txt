cmake_minimum_required(VERSION 3.16)
project(InstructionCounter)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM: ${LLVM_DIR} version ${LLVM_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(InstructionCounter MODULE
    instruction_counter.cpp
)

target_compile_features(InstructionCounter PRIVATE cxx_std_17)
set_target_properties(InstructionCounter PROPERTIES PREFIX "" SUFFIX ".so")
