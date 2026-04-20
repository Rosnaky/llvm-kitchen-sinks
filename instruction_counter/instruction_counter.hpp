#ifndef LLVM_TRANSFORMS_INSTRUCTION_COUNTER_H
#define LLVM_TRANSFORMS_INSTRUCTION_COUNTER_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class InstructionCounter : public PassInfoMixin<InstructionCounter> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

    static bool isRequired() { return true; }
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_INSTRUCTION_COUNTER_H
