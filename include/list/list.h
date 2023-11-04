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
	linked_list() : _head(nullptr), _size(0) {};

	linked_list(size_t size) : _size(size) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist_for_head(1, 9);
		std::uniform_int_distribution<> dist(0, 9);
		_head = new node(dist_for_head(gen), nullptr, nullptr);
		auto tmp = _head;
		size_t cur_ind = 1;
		while (cur_ind++ < size) {
			tmp->next = new node(dist(gen), tmp, nullptr);
			tmp = tmp->next;
		}
	}
	
	linked_list(const linked_list& list): _head(nullptr){
		this->add_to_tail(list);
	}

	linked_list& operator=(const linked_list& list) {
		auto tmp = _head;
		_size = 0;
		while (tmp) {
			tmp = _head;
			_head = _head->next;
			delete tmp;
		}
		this->add_to_tail(list);
		return *this;
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

	void add_to_head(const T& value) {
		++_size;
		auto tmp = _head;
		_head = new node(value, nullptr, tmp);
		tmp->prev = _head;
	}
	void add_to_head(const linked_list& list) {
		_size += list._size;
		auto tmp = _head;
		auto tmp2 = list._head;

	}

	void add_to_tail(const T& value) {
		++_size;
		if (!_head) _head = new node(value, nullptr, nullptr);
		auto tmp = _head;
		while (tmp->next) {
			tmp = tmp-> next;
		}
		tmp->next = new node(value, tmp, nullptr);
	}
	
	void add_to_tail(const linked_list& list) {
		_size += list._size;
		auto tmp_l = list._head;
		auto tmp = _head;
		if (!_head) {
			_head=new node(list._head->value,nullptr,nullptr);
			tmp = _head;
			tmp_l = tmp_l->next;
		}
		else{
			while (tmp->next) {
				tmp = tmp->next;
			}
		}
		while (tmp_l) {
			tmp->next = new node(tmp_l->value, tmp, nullptr);
			tmp_l = tmp_l->next;
			tmp = tmp->next;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const linked_list& list) {
		os << "{ ";
		auto tmp = list._head;
		while(tmp){
			os << tmp->value << " ";
			tmp = tmp->next;
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