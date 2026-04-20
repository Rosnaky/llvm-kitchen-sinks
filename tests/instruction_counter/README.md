# Instruction Counter Test

#### Compile to LLVM IR
Run this `CMakeList.txt`  
Then run:
```
clang -emit-llvm -S -o test.ll tests/instruction_counter/main.cpp
```

#### Run Pass
```
opt -load-pass-plugin ./build/InstructionCounter.so -passes=instruction-counter -disable-output test.ll
```
