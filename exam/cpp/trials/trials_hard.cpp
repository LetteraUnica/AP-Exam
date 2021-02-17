#include "../include/bst.h"

// HARD TESTS FOR THE BST CLASS


/**
 * \brief Creates a random vector of keys from 0 to v.size()-1
 * \tparam U Key type
 * \param v Vector
 */
template<typename U>
void create_keys(std::vector<U>* v) {
	for (int i = 0; i < v->size(); i++) {
		v->at(i) = i;
	}
	std::shuffle(v->begin(), v->end());
}

/**
 * \brief Fills a container with N randomly generated nodes
 * \tparam T Type of the container
 * \param container to be filled (must implement a emplace function like in std::map)
 * \param N Number of nodes to put in the container
 */
template<typename T>
void fill(T* container, int N) {
	auto* keys = new std::vector<int>(N);
	create_keys(keys);
	for (auto i = 0; i < N; i++)
		container->emplace(keys->at(i), i);
}


int main()
{
	const int N = 1000;
	auto* keys = new std::vector<int>(N);
	create_keys(keys);

	// INSERT
	std::cout << "TEST L-VALUE INSERT" << std::endl;
	std::cout << "Inserting " << N << " nodes to bst_0 passing l-value reference to pair" << std::endl;
	bst<int,int> bst_0{};
	
	for (auto key : keys)
	{
		auto pair = std::make_pair(key, key+1);
		bst_0.insert(pair);
	}

	for (auto i = 0; i<keys->size(); ++i)
	{
		auto node = bst_0.find(i);
		std::cout << node->first << node->second << std::endl;
		if(node->first != i || node->second != i+1)
		{
			std::cout << "ERROR!!" << std::endl;
		}
	}

	
	std::cout << "TEST R-VALUE INSERT" << std::endl;
	std::cout << "Inserting " << N << " nodes passing r-value reference to pair" << std::endl;
	bst<int, int> bst_1{};

	for (auto key : keys)
	{
		bst_0.insert(std::make_pair(key, key + 1));
	}

	for (auto i = 0; i < keys->size(); ++i)
	{
		auto node = bst_0.find(i);
		std::cout << node->first << node->second << std::endl;
		if (node->first != i || node->second != i + 1)
		{
			std::cout << "ERROR!!" << std::endl;
		}
	}
	
	

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
	std::cout << "bst_0: " << "\n";
	std::cout << bst_0;


	(void)bst_0.insert(pair_5);
	std::cout << "inserting (10, 7)\nbst_0: " << "\n";
	std::cout << bst_0;

	bst_0.insert(pair_3);
	std::cout << "Inserting a already known pair\nbst_0:" << "\n";
	std::cout << bst_0;

	
	// FIND
	std::cout << "\n\n" << "TEST FIND" << "\n";
	auto node_0 = bst_0.find(0);

	std::cout << "finding node with key=0 in bst_0" << "\n";
	std::cout << "node found: " << node_0 << "\n" << std::endl;

	node_0 = bst_0.find(102);
	std::cout << "finding a node with unknown key in bst_0" << "\n";
	std::cout << "node found: " << node_0 << "\n" << std::endl;


	// COPY SEMANTICS
	std::cout << "\n\n" << "TEST COPY SEMANTICS" << "\n";
	
	bst<int,int> bst_1{pair_3};
	std::cout << "bst_1:" << "\n";
	std::cout << bst_1;

	auto bst_2{bst_1};

	std::cout << "bst_2 (copy of bst_1):" << "\n";
	std::cout << bst_2;

	bst<int,int> bst_3{3,10};

	std::cout << "bst_3:" << "\n";
	std::cout << bst_3;

	bst_3=bst_2;

	std::cout << "bst_3=bst_2\nbst_3:" << "\n";
	std::cout << bst_3;

	bst_2.insert(pair_1);
	std::cout << "changing bst_2:" << "\n";
	std::cout << bst_2;
	std::cout << "bst_3 (should stay the same):" << "\n";
	std::cout << bst_3;


	// EMPLACE
	std::cout << "\n\n" << "TEST EMPLACE" << "\n";

	std::cout << "bst_3:" << "\n";
	std::cout << bst_3;

	(void)bst_3.emplace(3,5);
	std::cout << "adding node (3,5)\nbst_3:" << "\n";
	std::cout << bst_3;

	std::cout << "printing root of bst_3 after emplacement" << "\n";
	std::cout << "(" << "root key: " << get_root(bst_3).first << ", root value: " << get_root(bst_3).second << ")" << "\n" << std::endl;


	// CLEAR
	std::cout << "\n\n" << "TEST CLEAR" << "\n";
	std::cout << "bst_3:" << "\n";
	std::cout << bst_3;

	bst_3.clear();

	std::cout << "bst_3 (after clear):" << "\n";
	std::cout << bst_3;


	// SUBSCRIPTING OPERATOR
	std::cout << "\n\n" << "TEST SUBSCRIPTING OPERATOR" << "\n";

	std::cout << "bst_0:" << "\n";
	std::cout << bst_0;

	std::cout << "retrieving value of key -3 (should be 8):" << "\n";
	std::cout << "value: " << bst_0[-3] << std::endl;

	std::cout << "retrieving value of key 11 (doesnt exist) of bst_0:" << "\n";
	std::cout << bst_0[11] << std::endl;
	std::cout << "printing the tree, there should a new node (11, 0)" << "\n";
	std::cout << bst_0;

	
	// ERASE
	std::cout << "\n\n" << "TEST ERASE" << "\n";

	std::cout << "bst_0:" << "\n";
	std::cout << bst_0;
	bst_0.erase(-3);
	std::cout << "erasing node with key=-3" << "\n";
	std::cout << bst_0;
	bst_0.erase(-128);
	std::cout << "erasing node with key=-128 (doesn't exist) of bst_0:" << "\n";
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
	std::cout << "depth: " << bst_4.max_depth() << std::endl;
	
	std::cout << "creating bst_5 with depth=4 with 7 nodes" << "\n";
	bst<int, int> bst_5{bst_4};
	bst_5.emplace(-1, 1);
	bst_5.emplace(-2, 1);
	bst_5.emplace(-3, 1);
	std::cout << "printing bst_5 and its depth" << "\n";
	std::cout << bst_5;
	std::cout  << bst_5.max_depth() << std::endl;

	
	// BALANCE
	std::cout << "\n\n" << "TEST BALANCE" << "\n";
	std::cout << "Balancing bst_4 and printing its depth, should be 3" << "\n";
	bst_4.balance();
	std::cout << bst_4;
	std::cout << "depth: " << bst_4.max_depth() << std::endl;
	
	std::cout << "Balancing bst_5 and printing its depth, should be 3" << "\n";
	bst_5.balance();
	std::cout << bst_5;
	std::cout << "depth: " << bst_5.max_depth() << std::endl;


	return 0;
}