#ifndef AVL_H
#define AVL_H
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
			height = 0;
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
public:
	set() {
		root = new Node();
		size = 0;
	}
	~set() {

	}
	void add(const ItemType& item) {

	}
	void remove(const ItemType& item) {

	}
	bool find(const ItemType& item) {

		return false;
	}
	string print() {

		return "";
	}
};
#endif
