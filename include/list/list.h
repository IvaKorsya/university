#include <random>
#include <stdexcept>
#include <iostream>
template<class T>
class linked_list {
	struct node {
		T value;
		node* prev;
		node* next;

		node(T value, node* prev, node* next) : value(value), prev(prev), next(next) {};
	};
	node* _head;
	size_t _size;
public:
	linked_list() : _head(new node{0,nullptr,nullptr}), _size(0) {};
	linked_list(size_t size) : _size(size) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist_for_head(1, 9);
		std::uniform_int_distribution<> dist(0, 9);
		_head = new node(dist_for_head(gen), nullptr, nullptr);
		auto tmp = _head;
		size_t s = 0;
		while (s < size) {
			tmp->next = new node(dist(gen), tmp, nullptr);
			tmp = tmp->next;
			++s;
		}
	}
	const node& operator[](size_t index) const {
		if (index < 0 || index >= _size) throw std::invalid_argument("index out of the range");
		size_t cur_ind = 0;
		node* tmp = _head;
		while (cur_ind++!=index) {
			tmp = tmp->next;
		}
		return *tmp;
	}
	node& operator[](size_t index){
		if (index < 0 || index >= _size) throw std::invalid_argument("index out of the range");
		size_t cur_ind = 0;
		node* tmp = _head;
		while (cur_ind++ != index) {
			tmp = tmp->next;
		}
		return *tmp;
	}
	friend std::ostream& operator<<(std::ostream& os, const linked_list& list) {
		os << "{ ";
		for (size_t i = 0; i < list._size; ++i) {
			os << list[i].value << " ";
		}
		os << "}";
		return os;
	}
	~linked_list() {
		while (_head) {
			auto tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}
	size_t get_size() {
		return _size;
	}
	node* get_head() {
		return _head;
	}
};