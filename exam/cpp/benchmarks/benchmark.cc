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

// Fills a vector with randomly generated values
template<typename U>
void create_keys(std::vector<U>* v) {
    for(auto i=0lu; i<v->size(); i++) {
        v->at(i) = (U)(i*1.4 + 3.32);
    }
    shuffle(v->begin(), v->end());
}

// Fills a container with randomly generated keys
template<typename T, typename I>
void fill(T* container, I begin, I end) {
    while(begin!=end) {
        container->insert(std::make_pair(*begin, 0));
        ++begin;
    }
}

// Times a container with fixed size
template<typename T, typename U>
double time(T* container, std::vector<U>* keys, int ntrials, int step) {
    auto start = std::chrono::high_resolution_clock::now();
    
    for(int trial=0; trial<ntrials; ++trial) {
        for(int j=0; j<step; ++j) {
            volatile auto a = container->find((*keys)[j]);
        }           
    }

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
    return time / double(ntrials);
}


// Times a container with increasing values of its size
template<typename T, typename U>
void test(T* container, std::vector<U>* keys, std::string fname, const bool balance=false, int ntrials = 10) {
    std::ofstream f;
    int step=100;
    
    f.open(fname);
    f << "# Time to find " << step << " elements in a container with increasing values of its size\n";
    f << "# Size / time\n";
    
    for (int n=step; n<keys->size(); n+=step) {
        f << n << " ";
        fill(container, keys->begin()+n-step, keys->begin()+n);
        if(balance)
            container->balance();
        shuffle(keys->begin(), keys->begin() + n);
        
        f << time(container, keys, ntrials, step) << "\n";
    }
    f.close();
} 

// Same as test, I need this function because the map and unordered_map containers
// don't have a balance() method so, calling the above test function would give a compile
// error, even if the function would not call the balance() method.
template<typename T, typename U>
void nb_test(T* container, std::vector<U>* keys, std::string fname, int ntrials = 10) {
    std::ofstream f;
    int step=100;
    
    f.open(fname);
    f << "# Time to find " << step << " elements in a container with increasing values of its size\n";
    f << "# Size / time\n";
    
    for (int n=step; n<keys->size(); n+=step) {
        f << n << " ";
        fill(container, keys->begin()+n-step, keys->begin()+n);

        shuffle(keys->begin(), keys->begin() + n);
        auto start = std::chrono::high_resolution_clock::now();
        
        f << time(container, keys, ntrials, step) << "\n";
    }
    f.close();
}

int main()
{
	const int N = 20000;
	auto* map_i = new std::map<int, int>{};
	auto* u_map_i = new std::unordered_map<int, int>{};
    auto* bst_i = new bst<int, int>{};
    auto* bst_i_b = new bst<int, int>{};
    auto* bst_d_b = new bst<double, int>{};

    auto* keys_i = new std::vector<int>(N);
    create_keys(keys_i);
    auto* keys_d = new std::vector<double>(N);
    create_keys(keys_d);

    nb_test(map_i, keys_i, "results/map_int.txt");
    map_i->clear();
    nb_test(u_map_i, keys_i, "results/u_map_int.txt");
    u_map_i->clear();
    test(bst_i, keys_i, "results/bst_int.txt");
    bst_i->clear();
    test(bst_i_b, keys_i, "results/bst_int_b.txt", true);
    bst_i_b->clear();
    test(bst_d_b, keys_d, "results/bst_double_b.txt", true);
    bst_d_b->clear();

    keys_i->clear();
    keys_d->clear();

    return 0;
}