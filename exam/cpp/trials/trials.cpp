#include "../include/bst.h"

int main()
{
	// INSERT
	std::cout << "\n\n" << "TEST INSERT" << "\n";
	bst<int,int> bst_0{};

	const auto pair_0=std::make_pair(0, 1);
	const auto pair_1=std::make_pair(-3, 8);
	const auto pair_2=std::make_pair(4, 2);
	const auto pair_3=std::make_pair(-1, 1);
	const auto pair_4=std::make_pair(6, 12);
	const auto pair_5=std::make_pair(10, 7);
	

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

	auto bst_2{bst_1};

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


	// GET_DEPTH (USED TO TEST BALANCE AFTERWARDS)
	std::cout << "\n\n" << "TEST GET_DEPTH (USED TO TEST BALANCE)" << "\n";
	std::cout << "creating bst_4 with depth=4 with 4 nodes" << "\n";
	bst<int, int> bst_4{};
	bst_4.emplace(1, 1);
	bst_4.emplace(2, 1);
	bst_4.emplace(3, 1);
	bst_4.emplace(4, 1);
	std::cout << "printing bst_4 and its depth" << "\n";
	std::cout << bst_4;
	std::cout << bst_4.get_depth() << std::endl;
	
	std::cout << "creating bst_5 with depth=4 with 7 nodes" << "\n";
	bst<int, int> bst_5{bst_4};
	bst_5.emplace(-1, 1);
	bst_5.emplace(-2, 1);
	bst_5.emplace(-3, 1);
	std::cout << "printing bst_5 and its depth" << "\n";
	std::cout << bst_5;
	std::cout << bst_5.get_depth() << std::endl;

	
	// BALANCE
	std::cout << "\n\n" << "TEST BALANCE" << "\n";
	std::cout << "Balancing bst_4 and printing its depth, should be 3" << "\n";
	bst_4.balance();
	std::cout << bst_4;
	std::cout << bst_4.get_depth() << std::endl;
	
	std::cout << "Balancing bst_5 and printing its depth, should be 3" << "\n";
	bst_5.balance();
	std::cout << bst_5;
	std::cout << bst_5.get_depth() << std::endl;


	return 0;
}