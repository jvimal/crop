#include <iostream>
using namespace std;

#include "trie.cc"
#include "disasm.cc"

/* 2M buffer */
unsigned char code[1<<21];

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

int main() {
  int len = read_code("binsh.txt");
  X86Disasm d(code, len);
  
  Instruction ins;
  while(ins = d.next_instruction()) {
    ins.print();
  }
  
	return 0;
}
