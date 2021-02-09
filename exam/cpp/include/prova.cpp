#include <iostream>

template <typename T>
void copy(T* f1, T* e1, T* e2)
{
	
	
}


template <typename T>
void fill(T* f1, T* e1)
{
	for(T* p=f1; p!=e1; ++p)
	{
		*p = 1;
	}
}

template <typename T>
void print(T* f1, T* e1)
{
	for (T* p = f1; p != e1; ++p)
	{
		std::cout << *p;
	}
	std::cout << std::endl;
}

int main()
{
	auto count = 10;
	int vector[count];
	fill(vector, vector + count);
	print(vector, vector + count);
	
	return 0;
}