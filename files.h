#ifndef FILES_H
#define FILES_H
#include "avl.h"
#include <fstream>

using std::ofstream;
using std::ifstream;

class files {
private:
	ofstream out;
	ifstream in;
	string command;
	int index;
	string temp;
	list<string>* plist;
public:
	files(const char* inName, const char* outName) {
		in.open(inName);
		out.open(outName);
		plist = new list<string>(4);
	}
	~files() {
		in.close();
		out.close();
		delete plist;
	}
	void init() {
		while(in >> command) 
			run(command);
	}
	void run(string command) {
		if(command == "list") {
			flist();
		}
		else if(command == "insert") {
			insert();
		}
		else if(command == "find") {
			find();
		}
		else if(command == "remove") {
			remove();
		}
		else if(command == "print") {
			print();
		}
	}
	void flist() {
		int capacity;
		in >> capacity;
		if(capacity >= 2) {
			delete plist;
			plist = new list<string>(capacity);
		}
		out << "list " << capacity << endl;
	}
	void insert() {
		in >> index;
		in >> temp;
		plist->insert(index, temp);
		out << "insert " << index << " " << temp << endl;
	}
	void find() {
		in >> temp;
		out << "find " << temp << " " << plist->find(temp) << endl;
	}
	void remove() {
		in >> index;
		out << "remove " << index << " " <<plist->remove(index) << endl;
	}
	void print() {
		out << "print" << endl << plist->print();
	}
};
#endif
