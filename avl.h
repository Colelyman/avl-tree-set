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

		Node(Node* n) {
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
	int size;
	queue<Node*> q;
public:
	set() {
		size = 0;
	}
	~set() {

	}
	int height(Node* n) {
		if(n == NULL)
			return 0;
		return n->height;
	}
	bool checkHeight(Node* n, Node* n2) { // returning true means the subtree is out of balance
		if(height(n) > (height(n2) + 1))
			return true; 
		else if((height(n) + 1) > height(n2))
			return true;
		else if(height(n) < (height(n2) - 1))
			return true;
		else if((height(n) - 1) < height(n2))
			return true;
		else
			return false;
	}
	Node* insert(Node* n, const ItemType& item) {
		if(n == NULL)
			return new Node(item);
		else if(item < n->item)
			n->left = insert(n->left, item);
		else if(item > n->item)
			n->right = insert(n->right, item);

		n->height = max(height(n->left), height(n->right)) + 1;
		return n;
	}
	void add(const ItemType& item) {
		if(root == NULL || size == 0) 
			root = new Node(item);
		else if(find(item))
			return;
		else {
			insert(root, item);
		}
		size++;
	}
	void remove(const ItemType& item) {
		if(find(item))
			return;

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
		stringstream s;
		Node* sentinal = new Node();
		
		q.push(root);
		q.push(sentinal);
		
		queue<Node*> q2;
		int level = 0;
		s << "level " << level << ": ";
		level++;
		while(!q.empty()) {
			Node* n = q.pop();
			if(n == sentinal && !q.empty()) {
				q.push(sentinal);
				s << endl << "level " << level << ": ";
				level++;
			}
			if(n != sentinal)
				s << n->item << "(" << n->height << ") "; 
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
