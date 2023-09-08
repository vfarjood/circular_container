#include "include/CircularContainer.hpp"
#include <string>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <algorithm>

constexpr std::size_t buffer_size = 5;
struct Person {
	
	std::string name = "null";
	int age = 0;
	
	bool operator<(const Person& other) {
		return this->age < other.age;
	}

	void print() const {
		std::cout << "name: " << name << std::endl;
		std::cout << "age : " << age  << std::endl;
		std::cout << "--------------" << std::endl;

	}
};


int main(){

	Person p1{.name="p1", .age=1};
	Person p2{.name="p2", .age=2};
	Person p3{.name="p3", .age=3};
	Person p4{.name="p4", .age=4};
	Person p5{.name="p5", .age=5};
	Person p6{.name="p6", .age=6};
	Person p7{.name="p7", .age=7};
	Person p8{.name="p8", .age=8};

	vfc::CircularContainer<Person, buffer_size> container;

	std::cout << "size of container:     " << container.size() << std::endl;
	std::cout << "capacity of container: " << container.capacity() << std::endl;
		if(container.empty()){
		std::cout << "its empty!!!!!!!" << std::endl;
	}



	// std::cout << "head:" << container.m_head << std::endl;
	// std::cout << "tail:" << container.m_tail << std::endl;
	container.push_back(p1); 
	// std::cout << "head:" <<container.m_head << std::endl;
	// std::cout << "tail:" <<container.m_tail << std::endl;
	container.push_back(p2); 
	// std::cout << "head:" <<container.m_head << std::endl;
	// std::cout << "tail:" <<container.m_tail << std::endl;
	container.push_back(p3); 
	// std::cout << "head:" <<container.m_head << std::endl;
	// std::cout << "tail:" <<container.m_tail << std::endl;
	container.push_back(p4); 
	// std::cout << "head:" <<container.m_head << std::endl;
	// std::cout << "tail:" <<container.m_tail << std::endl;
	container.push_back(p5); 
	// std::cout << "head:" <<container.m_head << std::endl;
	// std::cout << "tail:" <<container.m_tail << std::endl;
	// container.push_back(p6); 
	// container.push_back(p7); 
	// container.push_back(p8); 
	// std::cout <<"head:" << container.m_head << std::endl;
	// std::cout << "tail:" <<container.m_tail << std::endl;
	// std::cout << "----start poping----" << std::endl;
	// container.pop_front(); 
	// container.pop_front(); 
	// container.pop_front(); 
	// container.pop_front(); 
	// container.pop_front(); 
	// container.pop_front(); 
	// std::cout << "head:" <<container.m_head << std::endl;
	// std::cout << "tail:" <<container.m_tail << std::endl;
	std::cout << std::endl;

	if(p4 < p5)

	std::cout << "---range base for loop" << std::endl;
	for (const auto& it : container){
		it.print();
	}
	std::cout << std::endl;

	if(!container.empty()){
	std::cout << "---read cbegin() by const_iterator: " << std::endl;
	vfc::CircularContainer<Person, buffer_size>::const_iterator  const_iter = container.cbegin();
	std::cout << const_iter->age << std::endl;
	// const_iter->age = 88;
	// std::cout << const_iter->age << std::endl;
	}

	if(!container.empty()){
	std::cout << "---write begin() by non-const_iterator: " << std::endl;
	vfc::CircularContainer<Person, buffer_size>::iterator  iter = container.begin();
	iter->age = 11;
	std::cout << iter->age << std::endl;
	}


	std::cout << std::endl;
	std::cout << "---iterator base for loop" << std::endl;
	for ( vfc::CircularContainer<Person, buffer_size>::iterator it = container.begin(); it != container.end(); ++it){
		// it->age = 0;
		std::cout << "it: " << it.index() << std::endl;
		it->print();
	}
	std::cout << std::endl;

	container.insert(container.cbegin(), p8); // with l-value item
	container.insert(++(container.cbegin()), Person{.name="p9", .age=9}); // with r-value item

	std::cout << std::endl;
	std::cout << "---iterator base for loop after insertion" << std::endl;
	for ( vfc::CircularContainer<Person, buffer_size>::iterator it = container.begin(); it != container.end(); ++it){
		// it->age = 0;
		std::cout << "it: " << it.index() << std::endl;
		it->print();
	}

	std::cout << "---reverse_iterator for loop" << std::endl;
	for (auto it = container.rbegin(); it != container.rend(); ++it){
		std::cout << "it: " << it.index() << std::endl;
		it->print();
	}
	std::cout << std::endl;

	std::cout << "---const reverse_iterator for loop" << std::endl;
	for (auto it = container.crbegin(); it != container.crend(); ++it){
		std::cout << "it: " << it.index() << std::endl;
		it->print();
	}
	std::cout << std::endl;


	std::cout << "---range base for loop" << std::endl;
	for (const auto& it : container){
		it.print();
	}
	std::cout << std::endl;
	
	container.clear();
	std::cout << "clear() method was called!" << std::endl;

	if(container.empty()){
		std::cout << "the container is empty now!\n" << std::endl;
	}
	std::cout << "-front:\n";
	container.front().print();
	std::cout << "-end:\n";
	container.back().print();
	std::cout << "---> Accessing front() and back() is 'Undefined Behavior' when container is empty!\n";


	std::cout << "---range base for loop" << std::endl;
	for (const auto& it : container){
		it.print();
	}
	std::cout << std::endl;


	auto i1 = container.cbegin();
	auto i2 = container.cbegin();
	std::cout << "-------------------" << std::endl;

	std::cout << "i1 = " << std::endl;
	i1->print();
	std::cout << "i2 = " << std::endl;
	i2->print();

	if(i1 == i2) std::cout << " i1 and i2 are equal\n";
	if(i1 != i2) std::cout << " i1 and i2 are no equal\n";

	// std::advance(i2, 5);
	// std::cout << "distance: " << std::distance(i1, i2) << std::endl;

	auto i11 = std::next(i1, 2);
	
	if(i1 == i2) std::cout << " i1 and i2 are equal\n";
	if(i1 != i2) std::cout << " i1 and i2 are no equal\n";

	std::cout << "-------------------" << std::endl;
	std::cout << "i11 = " << std::endl;
	i11->print();
	std::cout << "i1 = " << std::endl;
	i1->print();
	std::cout << "i2 = " << std::endl;
	i2->print();
	// std::shuffle(container.begin(), container.end());

	std::cout << "---range base for loop" << std::endl;
	for (const auto& it : container){
		it.print();
	}
	std::cout << std::endl;
	std::cout << "size of container:     " << container.size() << std::endl;
	std::cout << "capacity of container: " << container.capacity() << std::endl;
	std::cout << std::endl;

	container.push_back(p1); 
	container.push_back(p2); 
	container.push_back(p3); 
	container.push_back(p4); 
	container.push_back(p5);


	std::cout << "---range base for loop" << std::endl;
	for (const auto& it : container){
		it.print();
	}
	// container.pop_front();
	std::cout << "size of container:     " << container.size() << std::endl;
	std::cout << "capacity of container: " << container.capacity() << std::endl;

	const int a = 1;
	const int b = 2;
	const int c = 3;
	const int d = 4;
	vfc::CircularContainer<int, 5> c1;
	c1.push_back(a);
	c1.push_back(b);
	c1.push_back(c);
	c1.push_back(d);

	for(const auto i : c1){
		std::cout << "i: " << i << std::endl;
	}
	auto c1_it = ++c1.begin();
	std::cout << *c1_it << std::endl;

	for(auto it = c1.begin(); it != c1.end(); ++it){

	}

	vfc::CircularContainer init{1,2,3,4,5};
	for(auto it = init.begin(); it != init.end(); ++it){
		std::cout << *it << ", " ;
	}
	std::cout << std::endl;


	vfc::CircularContainer p{p6, p7, p8};
	for(auto it = p.begin(); it != p.end(); ++it){
		it->print();
	}
	std::cout << std::endl;

	if(auto found = std::find_if(p.begin(), p.end(), [](auto&& item){
		return item.age == 8;
	}); found != p.end()) {
		found->print();
	}

	return 0;
}
