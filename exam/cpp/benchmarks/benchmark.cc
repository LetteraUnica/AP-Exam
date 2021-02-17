#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <fstream>
#include "../include/bst.h"

/**
 * \brief Creates a random vector of keys from 0 to v.size()-1
 * \tparam U Key type
 * \param v Vector
 */
template<typename U>
void create_keys(std::vector<U>* v) {
    for(int i=0; i<v->size(); i++) {
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
    for(auto i=0; i<N; i++) 
        container->emplace(keys->at(i), i);
}

/**
 * \brief Tests the time to find N nodes in a container
 * \tparam T Type of the container
 * \param container to test (must implement a find function like in std::map)
 * \param N Number of nodes to find
 * \param trials Number of times the test is executed default=10
 * \return (double) Average time taken for one trial in microseconds
 */
template<typename T>
double test(T* container, int N, int trials = 10) {

    double time = 0.;
    for(int i=0; i<trials; ++i) {
        
        auto start = std::chrono::steady_clock::now();
        for(int j=0; j<N; ++j)
            (void)container->find(j);
        auto end = std::chrono::steady_clock::now();

        time += std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
    }
    return time / (double)trials / 1000;
} 

int main(int argc, char* argv[])
{
	int N = 10000;
	auto* map_ii = new std::map<int, int>{};
	auto* u_map_ii = new std::unordered_map<int, int>{};
    auto* map_di = new std::map<double, int>{};
    auto* u_map_di = new std::unordered_map<int, int>{};
    auto* map_dd = new std::map<int, int>{};
    auto* u_map_dd = new std::unordered_map<int, int>{};
    auto* bst_ii = new bst<int, int>{};
    auto* bst_di = new bst<int, int>{};
    auto* bst_dd = new bst<int, int>{};

    std::cout << "Filling containers with " << N << " elements\n" << std::endl;
    fill(u_map_ii, N);
    fill(map_ii, N);
    fill(u_map_di, N);
    fill(map_di, N);
    fill(u_map_dd, N);
    fill(map_dd, N);
    fill(bst_ii, N);
    fill(bst_di, N);
    fill(bst_dd, N);
    
    std::string name = "results.txt";
    
    std::ofstream f;
    f.open(name);

    f << "# map=std::map, u_map=std::unordered_map\n";
    f << "# <K, V> =  K: type of key V: type of value\n#\n";
    f << "# Time[us] to find " << N << " elements in various containers\n";
    f << "\t\t<int, int>\t<double, int>\t<double, double>\n";
    f << "map\t\t" << test(map_ii, N) << "\t\t" << test(map_di, N) << "\t\t" << test(map_dd, N) << "\n";
    f << "u_map\t" << test(u_map_ii, N) << "\t\t" << test(u_map_di, N) << "\t\t" << test(u_map_dd, N) << "\n";

    std::cout << "Time[us] to find " << N << " elements in various containers\n";
    std::cout << "\t\t<int, int>\t<double, int>\t<double, double>\n";
    std::cout << "map\t" << test(map_ii, N) << "\t" << test(map_di, N) << "\t" << test(map_dd, N) << std::endl;
    std::cout << "u_map\t" << test(u_map_ii, N) << "\t" << test(u_map_di, N) << "\t" << test(u_map_dd, N) << std::endl;
    std::cout << "bst\t" << test(bst_ii, N) << "\t" << test(bst_di, N) << "\t" << test(bst_dd, N) << std::endl;

    f.close();
    return 0;
}