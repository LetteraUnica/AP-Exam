#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include "../include/bst.h"

// Shuffles a vector
template<typename I>
void shuffle(I begin, I end) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(begin, end, std::default_random_engine(seed));
}

// Fills a vector with randomly generated keys
template<typename U>
void create_keys(std::vector<U>* v) {
    for(auto i=0lu; i<v->size(); i++) {
        v->at(i) = (U)(i*1.4 + 3.32);
    }
    shuffle(v->begin(), v->end());
}

// Fills a container with randomly generated keys
template<typename T, typename I>
void fill(T* container, I begin, I end, bool balance=false) {
    while(begin!=end) {
        container->insert(std::make_pair(*begin, 0));
        ++begin;
    }
    if(balance) {
        container->balance();
    }
}

// Times a container with increasing values of its size
template<typename T, typename U>
void test(T* container, std::vector<U>* keys, std::string fname, const bool balance=false, int ntrials = 50) {
    std::ofstream f;
    int step=100;
    
    f.open(fname);
    f << "# Time to find " << step << " elements in a container with increasing values of its size\n";
    f << "# Size / time\n";
    
    for (int n=step; n<keys->size(); n+=step) {
        f << n << " ";
        fill(container, keys->begin()+n-step, keys->begin()+n, balance);
        shuffle(keys->begin(), keys->begin() + n);
        auto start = std::chrono::high_resolution_clock::now();
        
        for(int trial=0; trial<ntrials; ++trial) {
            for(int j=0; j<step; ++j) {
                container->find((*keys)[j]);
            }           
        }

        auto end = std::chrono::high_resolution_clock::now();
        double time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
        f << time/double(ntrials) << "\n";
    }
    f.close();
} 


template<typename T, typename I>
void nb_fill(T* container, I begin, I end) {
    while(begin!=end) {
        container->insert(std::make_pair(*begin, 0));
        ++begin;
    }
}

template<typename T, typename U>
void nb_test(T* container, std::vector<U>* keys, std::string fname, int ntrials = 10) {
    std::ofstream f;
    int step=100;
    
    f.open(fname);
    f << "# Time to find " << step << " elements in a container with increasing values of its size\n";
    f << "# Size / trial1 / ... / trialN\n";
    
    for (int n=step; n<keys->size(); n+=step) {
        f << n << " ";
        nb_fill(container, keys->begin()+n-step, keys->begin()+n);

        shuffle(keys->begin(), keys->begin() + n);
        auto start = std::chrono::high_resolution_clock::now();
        
        for(int trial=0; trial<ntrials; ++trial) {
            for(int j=0; j<step; ++j) {
                container->find(keys->at(j));
            }           
        }

        auto end = std::chrono::high_resolution_clock::now();
        double time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
        f << time/double(ntrials) << "\n";
    }
    f.close();
} 

int main()
{
	const int N = 20000;
	auto* map_i = new std::map<int, int>{};
    auto* map_d = new std::map<double, int>{};
	auto* u_map_i = new std::unordered_map<int, int>{};
    auto* u_map_d = new std::unordered_map<double, int>{};
    auto* bst_i = new bst<int, int>{};
    auto* bst_d = new bst<double, int>{};
    auto* bst_i_b = new bst<int, int>{};
    auto* bst_d_b = new bst<double, int>{};

    auto* keys_i = new std::vector<int>(N);
    create_keys(keys_i);
    auto* keys_d = new std::vector<double>(N);
    create_keys(keys_d);

    nb_test(map_i, keys_i, "results/map_int.txt");
    nb_test(map_d, keys_d, "results/map_double.txt");
    nb_test(u_map_i, keys_i, "results/u_map_int.txt");
    nb_test(u_map_d, keys_d, "results/u_map_double.txt");
    test(bst_i, keys_i, "results/bst_int.txt");
    test(bst_d, keys_d, "results/bst_double.txt");
    test(bst_i_b, keys_i, "results/bst_int_b.txt", true);
    test(bst_d_b, keys_d, "results/bst_double_b.txt", true);

    return 0;
}