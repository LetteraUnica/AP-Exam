#include "../include/bst.h"

int main()
{
	
	bst<int,int> binary_tree_0{};

	std::pair<int, int> pair_0=std::make_pair(0, 1);
	std::pair<int, int> pair_1=std::make_pair(-3, 8);
	std::pair<int, int> pair_2=std::make_pair(4, 2);
	std::pair<int, int> pair_3=std::make_pair(-1, 1);
	std::pair<int, int> pair_4=std::make_pair(6, 12);
	std::pair<int, int> pair_5=std::make_pair(10, 7);
	

	(void)binary_tree_0.insert(pair_0);
	(void)binary_tree_0.insert(pair_1);
	(void)binary_tree_0.insert(pair_2);
	(void)binary_tree_0.insert(pair_3);
	(void)binary_tree_0.insert(pair_4);
	(void)binary_tree_0.insert(pair_5);

	std::cout << "printing binary_tree_0" << "\n";
	std::cout << binary_tree_0;

	std::cout << "printing root of binary_tree_0" << "\n";
	std::cout << "(" << "root key: " << get_root(binary_tree_0).first << ", root value: " << get_root(binary_tree_0).second << ")" << "\n" << std::endl;

	auto node_0=binary_tree_0.find(0);

	std::cout << "finding node with key=0 in binary_tree_0" << "\n";
	std::cout << node_0 << "\n" << std::endl;

	bst<int,int> binary_tree_1{pair_3};

	std::cout << "printing binary_tree_1" << "\n";
	std::cout << binary_tree_1;

	// TESTING COPY SEMANTICS

	bst<int,int> binary_tree_2{binary_tree_1};

	std::cout << "printing binary_tree_2" << "\n";
	std::cout << binary_tree_2;

	bst<int,int> binary_tree_3{3,10};

	std::cout << "printing binary_tree_3" << "\n";
	std::cout << binary_tree_3;

	binary_tree_3=binary_tree_2;

	std::cout << "printing binary_tree_3 after assignment" << "\n";
	std::cout << binary_tree_3;

	std::cout << "printing binary_tree_2 after assignment" << "\n";
	std::cout << binary_tree_2;

	// TESTING EMPLACE

	(void)binary_tree_3.emplace(3,5);

	std::cout << "printing binary_tree_3 after emplacement" << "\n";
	std::cout << binary_tree_3;

	std::cout << "printing root of binary_tree_3 after emplacement" << "\n";
	std::cout << "(" << "root key: " << get_root(binary_tree_3).first << ", root value: " << get_root(binary_tree_3).second << ")" << "\n" << std::endl;

	binary_tree_3.clear();

	std::cout << "printing binary_tree_3 after clearing tree" << "\n";
	std::cout << binary_tree_3;

	// SUBSCRIPTING OPERATOR

	std::cout << "retrieving value related to key -3 of binary_tree_0" << "\n";
	std::cout << binary_tree_0[-3] << std::endl;

	std::cout << "retrieving value related to key 11 (which doesnt exist) of binary_tree_0" << "\n";
	std::cout << binary_tree_0[11] << std::endl;

	return 0;

}
