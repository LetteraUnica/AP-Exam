#include <iostream>
#include<memory> //unique_ptr
#include<utility> //pair

#include "node.h"


/**
 * \tparam Tk type of the node key
 * \tparam Tv type of the node values
 * \tparam Tc type of the comparison operator. Default is std::less<Tk>
*/
template <class Tk, class Tv, class Tc=std::less<Tk>>
class bst {
private:

    using pair = std::pair<const Tk, Tv>;
    using node = node<pair>;

    // Unique pointer to the root node of the tree
    std::unique_ptr<node> root;

    Tc comp;
    
    bst() = default;
    
    ~bst() noexcept = default;

public:

    /**
     * \brief Inserts a new node in the tree
     * \param 
    */
    void insert();

    node* FindSmallest(node* current)
    {
	    while(current->left.get())
	    {
            current->left;
	    }
        return current;
    }

    node* FindBigger(node* current)
    {
        if (current->right)
        {
			return FindSmallest(current->right);
        }
    	
        Tk key = current->data.first;
    	while(current->parent && comp(current->parent->data.first, key))
    	{
            current = current->parent;
    	}
	    if (current->parent)
	    {
            return current->parent;
	    }

    	return nullptr;
    }
};

#include "methods.h"