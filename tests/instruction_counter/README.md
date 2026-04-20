# Instruction Counter Test

#### Compile to LLVM IR
Run the `CMakeList.txt` in `instruction_counter/`  
Then run:
```
clang -emit-llvm -S -o tmp/test.ll tests/instruction_counter/main.cpp
```

#### Run Pass
```
opt -load-pass-plugin ./build/InstructionCounter.so -passes=instruction-counter -disable-output tmp/test.ll
```
