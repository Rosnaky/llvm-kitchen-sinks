#include "dead_code_elim.hpp"

#include "llvm/IR/Function.h"
#include "llvm/IR/Analysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Plugins/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Local.h"


#include <vector>

using namespace llvm;

PreservedAnalyses DeadCodeElim::run(Function &F,
                                          FunctionAnalysisManager &AM) {

    bool changed = false;
    bool cfg_changed = false;
    bool curr_progress;

    do {
        curr_progress = false;

        std::vector<Instruction*> dead;

        for (BasicBlock &BB : F) {
            auto *BI = dyn_cast<CondBrInst>(BB.getTerminator());
            // Skip if not branch or unconditional branch
            if (!BI) continue;

            // Check if compile-time constant
            auto *Cond = dyn_cast<ConstantInt>(BI->getCondition());
            if (!Cond) continue;

            BasicBlock *Taken = Cond->isOne() ? BI->getSuccessor(0) : BI->getSuccessor(1);
            BasicBlock *NotTaken = Cond->isOne() ? BI->getSuccessor(1) : BI->getSuccessor(0);
            
            errs() << "[DCE] Removing branch: " << *BI << "\n";
            
            // Remove branch
            NotTaken->removePredecessor(&BB);
            
            // Replace conditional branch with unconditional branch to taken
            UncondBrInst::Create(Taken, BI->getIterator());
            BI->eraseFromParent();
            curr_progress = true;
            cfg_changed = true;
            changed = true;

        }

        for (Instruction &I : instructions(F)) {
            if (I.isTerminator()) continue;
            if (I.mayHaveSideEffects()) continue;
            if (I.use_empty()) {
                dead.push_back(&I);
            }
        }

        for (Instruction *I : dead) {
            errs() << "[DCE] Removing instruction: " << *I << "\n";
            I->replaceAllUsesWith(UndefValue::get(I->getType()));
            I->eraseFromParent();
            curr_progress = true;
            changed = true;
        }
    } while (curr_progress);

    if (changed) {
        PreservedAnalyses PA;
        if (!cfg_changed) {
            PA.preserveSet<CFGAnalyses>();
        }
        return PA;
    }

    return PreservedAnalyses::all();
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "DeadCodeElim",
        LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "dead-code-elim") {
                        FPM.addPass(DeadCodeElim());
                        return true;
                    }
                    return false;
                });
        }
    };
}
