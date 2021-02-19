#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include "../include/bst.h"

template<typename I>
void shuffle(I begin, I end) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(begin, end, std::default_random_engine(seed));
}

template<typename U>
void create_keys(std::vector<U>* v) {
    for(auto i=0lu; i<v->size(); i++) {
        v->at(i) = (U)(i*1.4 + 3.32);
    }
    shuffle(v->begin(), v->end());
}

template<typename T>
void print(std::vector<T>* v) {
	for (auto i=0; i<v->size(); ++i)
		std::cout << v->at(i) << " ";
	std::cout << std::endl;
}






template<typename T>
void foo(T* container, const bool balance) {
	if(balance) {
		container->balance();	
	}
}

int main()
{
	auto* bst_i = new bst<double, int>{};
	auto* map_i = new std::map<double, int>{};

	foo(map_i, false);
	
	return 0;
}