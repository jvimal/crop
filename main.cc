#include <iostream>
using namespace std;

#include "trie.cc"
#include "disasm.cc"

int main() {
  X86Disasm d((unsigned char *)
    "\x48\x83\xec\x08"
    "\xe8\xa3\x0b\x00\x00"
    "\xe8\x02\x0c\x00\x00"
    "\xe8\x8d\x4f\x07\x00"
    "\x48\x83\xc4\x08"
    "\xc3", 24);
  
  Instruction ins;
  while(ins = d.next_instruction()) {
    ins.print();
  }
  
	return 0;
}
