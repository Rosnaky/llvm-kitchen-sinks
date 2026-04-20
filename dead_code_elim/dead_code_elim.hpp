#ifndef LLVM_TRANSFORMS_DEAD_CODE_ELIM_H
#define LLVM_TRANSFORMS_DEAD_CODE_ELIM_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class DeadCodeElim : public PassInfoMixin<DeadCodeElim> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

    static bool isRequired() { return true; }
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_DEAD_CODE_ELIM_H
