#include "common.h"
#include <libdis.h>

class Instruction {
public:
  x86_insn_t ins; // for convenience
  Instruction(){}
  
  Instruction(x86_insn_t i) {
    ins = i;
  }
  
  void print() {
    char buff[128];
    
    x86_format_insn(&ins, buff, 128, intel_syntax);
    printf("%d => ", ins.size);
    REP(i, ins.size) {
      printf("%02x ", ins.bytes[i]);
    }
    FOR(k, ins.size, 10) { printf("   "); }
    printf("%s\n", buff);
  }
  
  operator bool() const {
    return ins.size > 0 and ins.type != insn_invalid;
  }
  
  ~Instruction(){}
};

struct InstructionCompare {
  bool operator()(const Instruction &a, const Instruction &b) {
    return memcmp(a.ins.bytes, b.ins.bytes, 20)<0;
  }
};
