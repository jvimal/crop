#include "common.h"
#include <libdis.h>

class Instruction {
  x86_insn_t ins; 
  
public:
  Instruction(){}
  
  Instruction(x86_insn_t i) {
    ins = i;
  }
  
  void print() {
    char buff[128];
    x86_format_insn(&ins, buff, 128, intel_syntax);
    printf("%s\n", buff);
  }
  
  bool operator==(const Instruction &right) {
    return memcmp(ins.bytes, right.ins.bytes, 32)==0;
  }
  
  bool operator<(const Instruction &right) {
    return memcmp(ins.bytes, right.ins.bytes, 32); 
  }
  
  operator bool() const {
    return ins.size > 0;
  }
  
  ~Instruction(){}
};
