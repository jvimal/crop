
FILES=common.h disasm.cc instruction.cc trie.cc main.cc
INC=-I lib/libdisasm-0.23/libdisasm/
LIBS=-ldisasm

all: $(FILES)
	$(CXX) $(FLAGS) $(INC) $(LIBS) main.cc -o disasm


