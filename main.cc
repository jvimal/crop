#include <iostream>
using namespace std;

#include "trie.cc"

int main() {
	Trie<int> t; 
	vector<int> l;
	l.push_back(100);
	l.push_back(200);
	
	t.insert(l);
	l.pop_back();
	l.push_back(300);
	
	t.insert(l);
	
	t.print();
	return 0;
}