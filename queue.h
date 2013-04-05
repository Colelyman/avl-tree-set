#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>

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
		Node* n = head->next;
		Node* temp;
		while(n != tail) {
			temp = n->next;
			delete n;
			n = temp;
		}
		delete head;
		delete tail;
	}
	void push(const ItemType& item) {
		Node* n = new Node(item);
		n->next = tail;
		n->prev = tail->prev;
		tail->prev->next = n;
		tail->prev = n;
		size++;
	}
	ItemType pop() {
		ItemType temp = head->next->item;
		Node* n = head->next;
		head->next = head->next->next;
		head->next->prev = head;
		delete n;
		size--;
		return temp;
	}
	ItemType top() {
		return head->next->item;
	}
	bool empty() {
		if(size == 0)
			return true;
		else
			return false;
	}
};
#endif
