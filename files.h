#ifndef FILES_H
#define FILES_H
#include "avl.h"
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::endl;

class files {
private:
	ofstream out;
	ifstream in;
	string command;
	int index;
	string temp;
	set<string>* pset;
public:
	files(const char* inName, const char* outName) {
		in.open(inName);
		out.open(outName);
		pset = new set<string>();
	}
	~files() {
		in.close();
		out.close();
		delete pset;
	}
	void init() {
		while(in >> command) 
			run(command);
	}
	void run(string command) {
		if(command == "clear") {
			clear();
		}
		else if(command == "add") {
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
	void clear() {
		delete pset;
		pset = new set<string>();
		out << "clear" << endl;
	}
	void insert() {
		in >> temp;
		pset->add(temp);
		out << "add " << temp << endl;
	}
	void find() {
		in >> temp;
		out << "find " << temp << " " << pset->find(temp) << endl;
	}
	void remove() {
		in >> temp;
		pset->remove(temp);
		out << "remove " << index << endl;
	}
	void print() {
		out << "print" << endl << pset->print();
	}
};
#endif
