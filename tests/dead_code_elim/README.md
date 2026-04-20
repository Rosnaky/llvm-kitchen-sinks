# Instruction Counter Test

#### Compile to LLVM IR
Run the root `CMakeList.txt`  
Then run:
```
clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S -o tmp/dead_code_elim_test.ll tests/dead_code_elim/main.cpp
```

#### Run Pass
```
opt -load-pass-plugin ./build/dead_code_elim/DeadCodeElim.so -passes='mem2reg,dead-code-elim' -disable-output tmp/dead_code_elim_test.ll
```

and run the branch test

```
opt -load-pass-plugin ./build/dead_code_elim/DeadCodeElim.so -passes='mem2reg,dead-code-elim' -disable-output tests/dead_code_elim/test_branch.ll 
```
