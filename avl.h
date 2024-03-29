#ifndef AVL_H
#define AVL_H
#include "queue.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

using std::string;
using std::stringstream;
using std::endl;
using std::max;
using std::cout;

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

		Node(const Node* n) {
			item = n->item;
			left = n->left;
			right = n->right;
			height = n->height;
		}

		Node(const ItemType& item) {
			this->item = item;
			left = NULL;
			right = NULL;
			height = 1;
		}
	};
	Node* root;
	Node* sentinal;
	int size;
	queue<Node*> q;
public:
	set() {
		size = 0;
		sentinal = new Node();
	}
	~set() {
		while(size > 0)
			remove(root->item);

		delete sentinal;
	}
	int height(Node* n) {
		if(n == NULL)
			return 0;
		return n->height;
	}
	void balance(Node*& n) {
		if(n == NULL)
			return;
		balance(n->left);
		balance(n->right);

		if(height(n->left) - height(n->right) > 1) 
			n = rightBalance(n);
		else if(height(n->right) - height(n->left) > 1)
			n = leftBalance(n);
	}
	void balance(Node*& parent, const ItemType& item) {
		if(parent->item == item)
			return;
		else if(item < parent->item)
			balance(parent->left, item);
		else
			balance(parent->right, item);

		if(height(parent->left) - height(parent->right) > 1) {
			parent = rightBalance(parent);
		}
		else if(height(parent->right) - height(parent->left) > 1) {
			parent = leftBalance(parent);
		}
	}
	Node* rightBalance(Node* n) {
		if(height(n->left->right) > height(n->left->left))
			n->left = singleRotateLeft(n->left);
		n = singleRotateRight(n);
		return n;
	}
	Node* singleRotateRight(Node* n) {
		Node* k = n->left;
		n->left = k->right;
		k->right = n;

		k->height = max(height(k->left), height(k->right)) + 1;
		n->height = max(height(n->left), height(n->right)) + 1;
		return k;
	}
	Node* leftBalance(Node* n) {
		if(height(n->right->left) > height(n->right->right))
			n->right = singleRotateRight(n->right);
		n = singleRotateLeft(n);
		return n;
	}
	Node* singleRotateLeft(Node* n) {
		Node* k = n->right;
		n->right = k->left;
		k->left = n;

		k->height = max(height(k->left), height(k->right)) + 1;
		n->height = max(height(n->left), height(n->right)) + 1;
		return k;
	}
	Node* insert(Node* n, const ItemType& item) {
		if(n == NULL)
			return new Node(item);
		else if(item < n->item) {
			n->left = insert(n->left, item);
		}
		else if(item > n->item) {
			n->right = insert(n->right, item);
		}

		balance(n, item);
		n->height = max(height(n->left), height(n->right)) + 1;
		return n;
	}
	void add(const ItemType& item) {
		if(size == 0)
			root = new Node(item);
		else if(find(item))
			return;
		else
			root = insert(root, item);
		size++;
	}
	Node* smallest(Node* n) {
		if(n->left == NULL)
			return n;
		n = smallest(n->left);

		return n;
	}
	Node* helpRemove(Node*& n) {
		Node* temp = n;
		if(n->left == NULL) {
			temp = n->right;
			delete n;
			n = temp;
		}
		else if(n->right == NULL) {
			temp = n->left;
			delete n;
			n = temp;
		}
		else {
			Node* small = smallest(n->right);
			n->item = small->item;
			if(n->right != NULL)
				remove(n->right, small->item);
		}
		return n;
	}
	Node* remove(Node*& n, const ItemType& item) {
		if(n == NULL)
			return n;
		if(item == n->item) {
			n = helpRemove(n);
		}
		else if(item < n->item)
			n->left = remove(n->left, item);
		else if(item > n->item)
			n->right = remove(n->right, item);

		if(n != NULL) {
			n->height = max(height(n->left), height(n->right)) + 1;
			balance(root, n->item);
		}

		return n;
	}
	void remove(const ItemType& item) {
		if(!find(item))
			return;
		else
			remove(root, item);
		balance(root);
		if(root != NULL)
			root->height = max(height(root->left), height(root->right)) + 1;
		size--;
	}
	bool find(const ItemType& item) {
		Node* n = find(root, item);
		if(n == NULL)
			return false;
		else if(n->item == item)
			return true;
		else
			return false;
	}
	Node* find(Node* n, const ItemType& item) {
		if(n == NULL || n->item == item)
			return n;
		else if(item < n->item)
			return find(n->left, item);
		else
			return find(n->right, item);
	}
	string print() {
		if(size == 0)
			return "";
		stringstream s;

		q.push(root);
		q.push(sentinal);
		
		int level = 0;
		int count = 0;
		s << "level " << level << ": ";
		level++;
		while(!q.empty()) {
			Node* n = q.pop();
			if(n == sentinal && !q.empty()) {
				q.push(sentinal);
				s << endl << "level " << level << ": ";
				level++;
				count = 0;
			}
			if(count == 8 && n != sentinal) {
				s << endl << "level " << level - 1 << ": ";
				count = 0;
			}
			if(n != sentinal) {
				s << n->item << "(" << height(n) << ") "; 
				count++;
			}
			if(n->left != NULL)
				q.push(n->left);
			if(n->right != NULL)
				q.push(n->right);
		}
		s << endl;

		return s.str();
	}
};
#endif
