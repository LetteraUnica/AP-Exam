#include "../include/bst.h"

int main()
{
	// INSERT
	std::cout << "\n\n" << "TEST INSERT" << "\n";
	bst<int,int> bst_0{};

	std::pair<int, int> pair_0=std::make_pair(0, 1);
	std::pair<int, int> pair_1=std::make_pair(-3, 8);
	std::pair<int, int> pair_2=std::make_pair(4, 2);
	std::pair<int, int> pair_3=std::make_pair(-1, 1);
	std::pair<int, int> pair_4=std::make_pair(6, 12);
	std::pair<int, int> pair_5=std::make_pair(10, 7);
	

	(void)bst_0.insert(pair_0);
	(void)bst_0.insert(pair_1);
	(void)bst_0.insert(pair_2);
	(void)bst_0.insert(pair_3);
	(void)bst_0.insert(pair_4);
	std::cout << "printing bst_0" << "\n";
	std::cout << bst_0;

	std::cout << "printing root of bst_0" << "\n";
	std::cout << "(" << "root key: " << get_root(bst_0).first << ", root value: " << get_root(bst_0).second << ")" << "\n" << std::endl;

	(void)bst_0.insert(pair_5);
	std::cout << "inserting (10, 7) and printing bst_0" << "\n";
	std::cout << bst_0;

	bst<int,int> bst_0{pair_3};
	std::cout << "Inserting a already known pair and printing bst_0" << "\n";
	std::cout << bst_0;

	
	// FIND
	std::cout << "\n\n" << "TEST FIND" << "\n";
	auto node_0 = bst_0.find(0);

	std::cout << "finding node with key=0 in bst_0" << "\n";
	std::cout << node_0 << "\n" << std::endl;

	auto node_0 = bst_0.find(102);
	std::cout << "finding a node with unknown key in bst_0" << "\n";
	std::cout << node_0 << "\n" << std::endl;


	// COPY SEMANTICS
	std::cout << "\n\n" << "TEST COPY SEMANTICS" << "\n";
	
	bst<int,int> bst_1{pair_3};
	std::cout << "printing bst_1" << "\n";
	std::cout << bst_1;

	bst<int,int> bst_2{bst_1};

	std::cout << "copying bst_1 to bst_2 and printing bst_2" << "\n";
	std::cout << bst_2;

	bst<int,int> bst_3{3,10};

	std::cout << "printing bst_3" << "\n";
	std::cout << bst_3;

	bst_3=bst_2;

	std::cout << "bst_3=bst_2 and printing bst_3" << "\n";
	std::cout << bst_3;

	bst_2.insert(pair_1);
	std::cout << "changing bst_2 and printing bst_2" << "\n";
	std::cout << bst_2;
	std::cout << "printing bst_3" << "\n";
	std::cout << bst_3;


	// EMPLACE
	std::cout << "\n\n" << "TEST EMPLACE" << "\n";

	(void)bst_3.emplace(3,5);

	std::cout << "printing bst_3 after emplacement" << "\n";
	std::cout << bst_3;

	std::cout << "printing root of bst_3 after emplacement" << "\n";
	std::cout << "(" << "root key: " << get_root(bst_3).first << ", root value: " << get_root(bst_3).second << ")" << "\n" << std::endl;


	// CLEAR
	std::cout << "\n\n" << "TEST CLEAR" << "\n";
	bst_3.clear();

	std::cout << "printing bst_3 after clearing tree" << "\n";
	std::cout << bst_3;


	// SUBSCRIPTING OPERATOR
	std::cout << "\n\n" << "TEST SUBSCRIPTING OPERATOR" << "\n";

	std::cout << "retrieving value related to key -3 of bst_0" << "\n";
	std::cout << bst_0[-3] << std::endl;

	std::cout << "retrieving value related to key 11 (which doesnt exist) of bst_0" << "\n";
	std::cout << bst_0[11] << std::endl;
	std::cout << "printing the tree, should add a new node" << "\n";
	std::cout << bst_0;

	
	// ERASE
	std::cout << "\n\n" << "TEST ERASE" << "\n";

	std::cout << "printing bst_0" << "\n";
	std::cout << bst_0;
	bst_0.erase(-3);
	std::cout << "erasing the node with key=-3 of bst_0" << "\n";
	std::cout << bst_0;
	bst_0.erase(-128);
	std::cout << "erasing the node with key=-128 (doesn't exist) of bst_0" << "\n";
	std::cout << bst_0;

	return 0;


	// BALANCE (CI DOVREMO INVENTARE QUALCOSA QUA)
}