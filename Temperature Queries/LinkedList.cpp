#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList() {
	// Implement this function
	head = nullptr;
	tail = nullptr;
}

LinkedList::~LinkedList() {
	// Implement this function
	Node *pCurr = head;
	while(pCurr!= nullptr){
		Node *pTemp = pCurr->next;
		delete pCurr;
		pCurr = pTemp;
	}
	head=tail=nullptr;
}

LinkedList::LinkedList(const LinkedList& source) {
	// Implement this function
	Node* pCurr=source.head;
	Node* prev=nullptr;
	Node* newnode=new Node(pCurr->data.id, pCurr->data.year, pCurr->data.month, pCurr->data.temperature);
	prev->next=newnode;
	prev= newnode;
	head = newnode;
	while(pCurr != nullptr){
		pCurr=pCurr->next;
		Node* newnode=new Node(pCurr->data.id, pCurr->data.year, pCurr->data.month, pCurr->data.temperature);
		prev->next=newnode;
		prev=newnode;
	}
	tail=newnode;
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// Implement this function
	Node *pCurr = head;
	while(pCurr == pCurr->next){
		Node *pTemp = pCurr->next;
		delete pCurr;
		pCurr = pTemp;
	}
	head = nullptr;
	tail = nullptr;
	pCurr=source.head;
	Node* prev=nullptr;
	Node* newnode=new Node(pCurr->data.id, pCurr->data.year, pCurr->data.month, pCurr->data.temperature);
	prev->next=newnode;
	prev=newnode;
	head = newnode;
	while(pCurr != nullptr){
		pCurr=pCurr->next;
		Node* newnode=new Node(pCurr->data.id, pCurr->data.year, pCurr->data.month, pCurr->data.temperature);
		prev->next=newnode;
		prev=newnode;
	}
	tail=newnode;
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	// Implement this function
	Node* newnode=new Node(location, year, month, temperature);
	Node* ptr=head;
	if(head==nullptr){
		head=newnode;
		tail=newnode;
	}
	else if(head==tail && head != nullptr){
		if(head->data < newnode->data){
			tail=newnode;
			head->next=newnode;
			tail->next=nullptr;
		} else{
			head=newnode;
			newnode->next=tail;
			tail->next=nullptr;
		}
	}
	else if(newnode->data < head->data){
		newnode->next=head;
		head=newnode;
	}
	else if(!(newnode->data<tail->data)){
		tail->next= newnode;
		tail=newnode;
	}
	else{
		Node* prev_ptr = head;
		ptr = head->next;
		while(ptr!=nullptr){
			if(newnode->data<ptr->data){
				prev_ptr->next = newnode;
				newnode->next=ptr;
				break;
			}
			prev_ptr = prev_ptr->next;
			ptr=ptr->next;
		}
	}
}

void LinkedList::clear() {
	// Implement this function
	Node *pCurr = head;
	while (pCurr != nullptr){
		Node *pTemp =pCurr->next;
		delete pCurr;
		pCurr = pTemp;
	}
	head = nullptr;
	tail = nullptr;
}

Node* LinkedList::getHead() const {
	// Implement this function it will be used to help grade other functions
	return head;
}

string LinkedList::print() const {
	// Implement this function
	string outputString="";
	ostringstream sout;
	Node *pCurr = head;
	while(pCurr != nullptr){
		sout << pCurr->data.id << " " << pCurr->data.year << " " << pCurr->data.month << " " << pCurr->data.temperature << endl;
		pCurr = pCurr->next;
	}
	outputString=sout.str();
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
