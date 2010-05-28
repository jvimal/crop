#include "instruction.cc"
#include <libdis.h>

/* Too lazy to setup inheritances */
class X86Disasm {
  unsigned char *buff; 
  int len; 
  int pos;
  
public:
  X86Disasm(unsigned char *b, int l) {/* assume default options */
    x86_init(opt_none, NULL, NULL);
    buff = b; 
    len = l;
    pos = 0;
  } 
  
  Instruction next_instruction() {
    x86_insn_t temp;
    int sz = x86_disasm(buff, len, 0, pos, &temp);
    pos += sz;
    return Instruction(temp);
  }
  
  ~X86Disasm() {
    x86_cleanup();
  }
};
