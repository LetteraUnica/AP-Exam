#include<memory> //unique_ptr
#include<utility> //pair

#include "node.h"
#include "bst.h"

template<class N>
class iterator {
    N* current;

public:
    /**
     * \brief Default constructor for the class iterator
     */
    iterator() : current{FindSmallest()} {}

    /**
     * \brief Custom constructor for the class iterator, creates an iterator given a pointer to node
     * \param n Pointer to node
     */
    iterator(N* n) noexcept : current{n} {}

    /**
     * \brief Default destructor for the class iterator
     */
    ~iterator() noexcept = default;

	bool operator==(N* lhs, N* rhs)
	{
        return lhs == rhs;
	}

    bool operator!=(N* lhs, N* rhs)
    {
        return lhs != rhs;
    }

	N& operator*()
	{
        return *current;
	}

	N* operator->()
	{
        return current;
	}

    N* operator++()
	{
        return FindBigger(current);
	}
	
};