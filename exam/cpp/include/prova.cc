#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include "../include/bst.h"


template<typename T>
void foo(T* container, const bool balance) {
	if(balance) {
		container->balance();	
	}
}

void print(int x) {
	std::cout << "asd" << std::endl;
}

int main()
{
	auto* bst_i = new bst<double, int>{};
	auto* map_i = new std::map<double, int>{};

	foo(map_i, false);

	return 0;
}