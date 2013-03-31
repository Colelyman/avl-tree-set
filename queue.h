#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include <string>
#include <iostream>

using std::string;
using std::endl;
using std::cout;

template<typename ItemType>
class queue {
private:
	struct Node {
		ItemType item;
		Node* prev;
		Node* next;

		Node() {
			prev = NULL;
			next = NULL;
		}
		Node(ItemType item) {
			this->item = item;
		}
	};
	Node* head;
	Node* tail;
	int size;
public:
	queue() {
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;

		size = 0;
	}
	~queue() {
		delete head;
		delete tail;
	}
	void push_back(const ItemType& item) {
		Node* n = new Node(item);
		n->next = tail;
		n->prev = tail->prev;
		tail->prev->next = n;
		tail->prev = n;
		size++;
	}
	ItemType pop_front() {
		ItemType temp = head->next->item;
		Node* n = head->next;
		head->next = head->next->next;
		head->next->prev = head;
		delete n;
		size--;
		return temp;
	}
	int getSize() {
		return size;
	}
};
#endif
