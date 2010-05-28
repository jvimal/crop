#include <map>
#include <vector>
#include <list>
using namespace std;

#include "common.h"

template<class T>
class Trie {
	T node; 
	map<T, Trie*> child;
	map<T, int> count;
public:
	
	Trie() {}
	Trie(T root):node(root){}
	~Trie(){ child.clear(); count.clear(); }
	
	Trie<T>* insert(const vector<T> &arr, int d = 0) {
		if(d == arr.size())
			return NULL;
		T curr = arr[d];
		
		Trie<T>* &next = child[curr];
		
		if(next == NULL) {
			next = new Trie<T>(curr);
		}
		
		count[curr] ++;
		return (next)->insert(arr, d+1);
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
