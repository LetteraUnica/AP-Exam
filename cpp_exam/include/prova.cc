#include<iostream>
#include<vector>

template <typename T>
void print_vector(const std::vector<T> &v, std::ostream &os = std::cout) {
    for (auto i : v)
        os << i << " ";
    os << std::endl;
}

int main()
{
    auto v = new std::vector<int>{1,2,3,4,5,6,7};
    
    print_vector(*v);
}