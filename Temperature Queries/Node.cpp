#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node() {
	next = nullptr;
} // remember to initialize next to nullptr(done)

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature):next(nullptr) {
	data.id = id;
	data.month = month;
	data.year = year;
	data.temperature = temperature;
}
// remember to initialize next to nullptr(done)

bool Node::operator<(const Node& b) {
	return this->data < b.data;
}
