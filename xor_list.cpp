// creating a XOR linked list
#include <iostream>
#include <limits>

template <typename t>
class xor_list {
 private:
	xor_list *head, *tail;
	int _size;
	xor_list *end_ptr, *rend;  // want to make these pointers constants
	xor_list *npx;
	t key;

	xor_list(t key) {
		this->key = key;
		this->npx = nullptr;
	}

 public:
	xor_list() : head(nullptr), tail(nullptr), _size(0) {
		end_ptr = new xor_list<t>(std::numeric_limits<t>::max());
		rend = new xor_list<t>(std::numeric_limits<t>::min());
		end_ptr->npx = rend;
		rend->npx = end_ptr;
		// cout<<"starting end_ptr address: "<<end_ptr<<endl;
	}

	void push_front(t);
	void push_back(t);
	void pop_front();
	void pop_back();

	static xor_list *XOR(xor_list *, xor_list *);
	int size() { return _size; }

	class iterator {
	 private:
		xor_list *prev, *current;

	 public:
		iterator() : prev(nullptr), current(nullptr) {}
		iterator(xor_list<t> *a, xor_list<t> *b) : current(a), prev(b) {}
		iterator operator++() {
			if (current == nullptr)
				throw std::runtime_error(
						"Null point reference(incrementing a null iterator)");
			xor_list *temp = new xor_list();
			temp = current;
			current = XOR(prev, current->npx);
			prev = temp;
			delete (temp);
			return *this;
		}

		t operator*() {
			if (current == nullptr)
				throw std::runtime_error("Dereferencing null iterator ");
			return current->key;
		}

		iterator operator++(int) {
			if (!current)
				throw std::runtime_error(
						"Null point reference(incrementing a null iterator)");
			xor_list *temp = new xor_list();
			temp = current;
			current = XOR(prev, current->npx);
			prev = temp;
			delete (temp);
			return *this;
		}

		iterator operator--() {
			if (!current)
				throw std::runtime_error(
						"Null point reference(decrementing a null pointer)");
			xor_list *temp = new xor_list();
			temp = prev;
			prev = XOR(prev->npx, current);
			current = temp;
			delete (temp);
			return *this;
		}

		iterator operator--(int) {
			if (!current)
				throw std::runtime_error(
						"Null point reference(decrementing a null pointer)");
			xor_list *temp = new xor_list();
			temp = prev;
			prev = XOR(prev->npx, current);
			current = temp;
			delete (temp);
			return *this;
		}

		bool operator==(iterator it) {
			//    cout<<it.current<<" "<<it.prev;
			return (this->current == it.current);
		}
		bool operator!=(iterator it) {
			return (prev != it.prev) || (current != it.current);
		}
	};

	bool empty();
	iterator begin() {
		iterator *temp = new iterator(this->head, this->rend);
		return (*temp);
	}
	iterator end() {
		iterator *temp = new iterator(this->end_ptr, this->tail);
		//  cout<<end_ptr<<"end ptr\n";
		//  cout<<tail<<"tail \n";
		return *(temp);
	}
};

template <typename t>
xor_list<t> *xor_list<t>::XOR(xor_list *a, xor_list *b) {
	return (xor_list *)((unsigned long)(a) ^ (unsigned long)(b));
}

template <typename t>
void xor_list<t>::push_front(t value) {
	xor_list *temp = new xor_list();
	temp->key = value;
	temp->npx = head;
	if (_size == 0) {
		head = tail = temp;
		temp->npx = xor_list<t>::XOR(rend, end_ptr);
		rend->npx = temp;
		end_ptr->npx = temp;
		_size++;
		return;
	}
	temp->npx = xor_list::XOR(rend, head);
	head->npx = xor_list::XOR(temp, xor_list::XOR(rend, head->npx));
	rend->npx = temp;
	head = temp;
	_size++;
	return;
}

template <typename t>
void xor_list<t>::push_back(t value) {
	xor_list *temp = new xor_list();
	temp->key = value;
	temp->npx = tail;
	if (_size == 0) {
		head = tail = temp;
		temp->npx = xor_list<t>::XOR(rend, end_ptr);
		rend->npx = end_ptr->npx = temp;
		_size++;
		return;
	}
	temp->npx = xor_list::XOR(end_ptr, tail);
	tail->npx = xor_list::XOR(temp, xor_list::XOR(end_ptr, tail->npx));
	end_ptr->npx = temp;
	tail = temp;
	_size++;
	return;
}

template <typename t>
void xor_list<t>::pop_front()
{
	xor_list *temp = XOR(rend,head->npx);
	temp->npx = XOR(rend,XOR(head,temp->npx));
	rend->npx = temp;
	head=temp;
	return;
}

template <typename t>
void xor_list<t>::pop_back()
{
	xor_list *temp = XOR(tail->npx,end_ptr);
	temp->npx = XOR(end_ptr,XOR(tail,temp->npx));
	end_ptr = 
	//still to be implemented 
}
int main() {
	xor_list<int> mylist;

	mylist.push_front(4);
	mylist.push_front(5);
	mylist.push_front(6);
	mylist.push_front(7);
	mylist.push_back(8);

	xor_list<int>::iterator it = mylist.end();
	std::cout << "Size of list: " << mylist.size() << std::endl;

	it--;
	while (it != mylist.begin()) {
		std::cout << (*it);
		--it;
	}
	mylist.pop_front();
	it=mylist.begin();
	std::cout<<std::endl;
	while(it!=mylist.end())
	{
		std::cout<<(*it);
		it++;
	}

	std::cout << (*it) << std::endl;
}