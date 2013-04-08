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

		n->height = max(height(n->left), height(n->right)) + 1;
		k->height = max(height(k->left), height(k->right)) + 1;
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

		n->height = max(height(n->left), height(n->right)) + 1;
		k->height = max(height(k->left), height(k->right)) + 1;
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
	Node* smallest(Node* n, const ItemType& small) const {
		if(n->left == NULL) {
			cout << "smallest: " << n->item << endl;
			return n;
		}
		if(n->left->item < small)
			n = smallest(n->left, n->left->item);
		return n;
	}
	Node* ctr(Node* n) { // ctr = choose the right
		cout << "enter ctr with: " << n->item << endl;
		if(n->left == NULL && n->right == NULL)
			return n;
		else if(n->left == NULL && n->right != NULL)
			return n->right;
		else if(n->right == NULL && n->left != NULL)
			return n->left;
		else {
			cout << "using smallest" << endl;
			Node* temp = n->left;
			n = smallest(n->right, n->item);
			n->left = temp;
			return n;
		}
	}
	Node* helpRemove(Node* n, Node* prev) {
		Node* temp = n;
		if(n->right == NULL && n->left == NULL) {
			temp = prev;
			if(temp->left == n)
				temp->left = NULL;
			else
				temp->right = NULL;
			cout << "exit if(item == n->item)" << endl;
		}
		else if(n->left == NULL) {
			temp = n->right;
		}
		else if(n->right == NULL) {
			temp = n->left;
		}
		else {
			temp = ctr(n);
			temp->left = n->left;
			cout << "remove: " << n->item << endl;
			cout << "n->item: " << temp->item << endl;
		}
//		balance(temp, temp->item);
		temp->height = max(height(temp->left), height(temp->right)) + 1;
		delete n;

		return temp;
	}
	Node* remove(Node* n, Node* prev, const ItemType& item) {
		if(item == n->item) {
			return helpRemove(n, prev);
		}
		else if(item < n->item)
			n->left = remove(n->left, n, item);
		else if(item > n->item)
			n->right = remove(n->right, n, item);

		return n;
	}
	void remove(const ItemType& item) {
		if(!find(item))
			return;
		else
			root = remove(root, root, item);
		cout << "after remove(root, root, item)" << endl;
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
			return "level 0:\n";
		stringstream s;
		Node* sentinal = new Node();

		q.push(root);
		q.push(sentinal);
		
		int level = 0;
		int count = 1;
		s << "level " << level << ": ";
		level++;
		while(!q.empty()) {
			Node* n = q.pop();
			if(n == sentinal && !q.empty()) {
				q.push(sentinal);
				s << endl << "level " << level << ": ";
				level++;
				count = 1;
			}
			if(n != sentinal) {
				s << n->item << "(" << height(n) << ") "; 
				count++;
			}
			if(count % 9 == 0 && q.top() != sentinal && !q.empty())
				s << endl << "level " << level - 1 << ": ";
			if(n->left != NULL)
				q.push(n->left);
			if(n->right != NULL)
				q.push(n->right);
		}
		s << endl;

		delete sentinal;
		return s.str();
	}
};
#endif
