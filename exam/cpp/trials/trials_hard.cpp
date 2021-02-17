#include "../include/bst.h"
#include <vector>
#include <random>
#include <chrono>

// HARD TESTS FOR THE BST CLASS


/**
 * \brief Creates a random vector of keys from 0 to v.size()-1
 * \tparam U Key type
 * \param v Vector
 */
template<typename U>
void create_keys(std::vector<U>* v) {
	for (auto i = 0lu; i < v->size(); i++) {
		v->at(i) = i;
	}
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(v->begin(), v->end(), std::default_random_engine(seed));
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
    auto bst_0 = new bst<int, int>{};

    for (auto key : *keys)
    {
        auto pair = std::make_pair(key, key+1);
        bst_0->insert(pair);
    }

    for (auto i = 0; i<N; ++i)
    {
        auto node = bst_0->find(i);
        std::cout << node << std::endl;
        if(node->first != i || node->second != i+1)
        {
            std::cout << "ERROR!!" << std::endl;
        }
    }

	
	std::cout << "TEST R-VALUE INSERT" << std::endl;
	std::cout << "Inserting " << N << " nodes passing r-value reference to pair" << std::endl;
	bst<int, int> bst_1{};

	for (auto key : *keys)
	{
		bst_1.insert(std::make_pair(key, key + 1));
	}

	for (auto i = 0; i < N; ++i)
	{
		auto node = bst_1.find(i);
		std::cout << node->first << node->second << std::endl;
		if (node->first != i || node->second != i + 1)
		{
			std::cout << "ERROR!!" << std::endl;
		}
	}



	// COPY SEMANTICS

    // MOVE SEMANTICS


	// EMPLACE




	// SUBSCRIPTING OPERATOR

	
	// ERASE



	
	// BALANCE

    // CLEAR

	return 0;
}