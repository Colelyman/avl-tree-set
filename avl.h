#ifndef AVL_H
#define AVL_H
#include "queue.h"
#include <string>
#include <sstream>

using std::string;
using std::stringstream;
using std::endl;

template<typename ItemType>
class set {
private:
	struct Node {
		ItemType item;
		Node* left;
		Node* right;
		int height;

		Node() {
			left = NULL;
			right = NULL;
			height = 1;
		}

		Node(Node* n) {
			item = n->item;
			left = n->left;
			right = n->right;
			height = n->height;
		}

		Node(ItemType item) {
			this->item = item;
			left = NULL;
			right = NULL;
			height = 0;
		}
	};
	Node* root;
	int size;
	queue<ItemType> q;
public:
	set() {
		root = new Node();
		size = 0;
	}
	~set() {

	}
	bool checkHeight(Node* n, Node* n2) { // returning true means the subtree is out of balance
		if(n->height > (n2->height + 1))
			return true; 
		else if((n->height + 1) > n2->height)
			return true;
		else if(n->height < (n2->height - 1))
			return true;
		else if((n->height - 1) < n2->height)
			return true;
		else
			return false;
	}
	void add(const ItemType& item) {

	}
	void remove(const ItemType& item) {

	}
	bool find(const ItemType& item) {

		return false;
	}
	string printLevel(Node* n, int level) {
		stringstream s;
		if(n == NULL)
			return s.str();
		if(level == 1)
			s << n->item << "(" << n->height << ") ";
		else {
			printLevel(n->left, level - 1);
			printLevel(n->right, level -1);
		}
		return s.str();
	}
	string print() {
		stringstream s;
		for(int i = 1; i <= root->height; i++)
			s << "level " << i - 1 << ": " << printLevel(root, i);

		return s.str();
	}
};
#endif
