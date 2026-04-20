#include "instruction_counter.hpp"

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Plugins/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"


#include <string>
#include <map>

using namespace llvm;

PreservedAnalyses InstructionCounter::run(Function &F,
                                          FunctionAnalysisManager &AM) {

    std::map<std::string, unsigned> opcode_counts;
    unsigned total = 0;
    unsigned num_blocks = 0;

    for (BasicBlock &BB : F) {
        num_blocks++;
        for (Instruction &I: BB) {
            opcode_counts[I.getOpcodeName()]++;
            total++;
        }
    }

    // Print analysis
    errs() << "Instruction Counter: " << F.getName() << '\n';
    errs() << "    Basic blocks: " << num_blocks << '\n';
    errs() << "    Total instructions: " << total << '\n';
    errs() << '\n';
    for (auto &[opcode, count] : opcode_counts) {
        errs() << "    " << opcode << ": " << count << '\n';
    }

    return PreservedAnalyses::all();
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "InstructionCounter",
        LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "instruction-counter") {
                        FPM.addPass(InstructionCounter());
                        return true;
                    }
                    return false;
                });
        }
    };
}
