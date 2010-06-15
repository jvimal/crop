#include <map>
#include <vector>
#include <list>
using namespace std;

#include "common.h"

template<class T,class KeyCmp>
class Trie {
	T node; 
	map<T, Trie*, KeyCmp> child;
	map<T, int, KeyCmp> count;
public:
	
	Trie() {}
	Trie(T root):node(root){}
	~Trie(){ child.clear(); count.clear(); }
	
	bool insert(const vector<T> &arr, int d = 0) {
    bool fresh = false;
		if(d == arr.size())
			return fresh;
		T curr = arr[d];
		
		Trie<T,KeyCmp>* &next = child[curr];

	  if(next == NULL) {
			next = new Trie<T,KeyCmp>(curr);
      fresh = true;
		}
		
		count[curr] ++;
		bool bchild = (next)->insert(arr, d+1);
    return fresh or bchild;
	}
	
	void print(int d = 0) {
		//assume int for now
		REP(i, d) printf("  ");
		printf("Node: %d\n", node);
		
		EACH(it, child) {
			it->value->print(d+1);
		}
	}
};
