# Instruction Counter Test

#### Compile to LLVM IR
Run the root `CMakeList.txt`  
Then run:
```
clang -emit-llvm -S -o tmp/instruction_counter.ll tests/instruction_counter/main.cpp
```

#### Run Pass
```
opt -load-pass-plugin ./build/instruction_counter/InstructionCounter.so -passes=instruction-counter -disable-output tmp/instruction_counter.ll
```
