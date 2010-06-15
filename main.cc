#include <iostream>
using namespace std;

#include "trie.cc"
#include "disasm.cc"
#define RET (0xc3)
#define LEAVE (0xc9)

/* 2M buffer */
unsigned char code[1<<26];
Trie<Instruction,InstructionCompare> trie;

int read_code(char *f) {
  int len = 0, num;
  
  FILE *fp = fopen(f, "r");
  if(fp == NULL) {
    fprintf(stderr, "File %s not found\n", f);
    return -1;
  }
  
  while(!feof(fp)) {
    fscanf(fp, "%2x", &num);
    code[len++] = num;
  }
  
  fclose(fp);
  return len;
}

void build_from(
  X86Disasm &d, 
  int pos, 
  Instruction ins, 
  vector<Instruction> &v, 
  int depth = 0) 
{
  if(depth == 20) {
    goto stopit;
  }
  v.resize(depth+1);
  v[depth] = ins;
  
  // max len of x86 instruction = 22, but let's stick to 6
  FOR(step,1,22+1) {
    Instruction temp = d.get_instruction(code+pos-step, step);
    if(temp && temp.ins.size == step && temp.ins.bytes[0] != LEAVE && temp.ins.bytes[0] != RET) {
      build_from(d, pos-step, temp, v, depth+1);
    }
  }
  
  stopit:
  if(depth > 1) {
    reverse(v.begin(), v.end());
    if(trie.insert(v)) {
      printf("inserting sequence of length: %d\n", v.size());
      EACH(ins, v) {
        ins->print();
      }
      printf("\n");
    }
    reverse(v.begin(), v.end());
  }
}

int main(int argc, char *argv[]) {
  int len = read_code("binsh.txt");
  
  if(len == -1)
    return -1;
  
  X86Disasm d(code, len);
  Instruction ins;
  
  if(argc == 2) {
    REP(pos, len) {
      if(code[pos] == RET) {
        vector<Instruction> v;
        Instruction ins = d.get_instruction(code+pos, 1);
        assert(ins.ins.bytes[0]==RET and ins.ins.size==1);
        build_from(d, pos, ins, v);
      }
    }
  } else {
    while(ins = d.next_instruction()) {
      if(ins.ins.bytes[0] == RET and ins.ins.size == 1) {
        /* This is a ret instruction */
        //printf("********** ret encountered at offset %d\n", ins.ins.offset);
        vector<Instruction> v;
        build_from(d, ins.ins.offset, ins, v);
      }
    }    
  }
  
  trie.print();
	return 0;
}
