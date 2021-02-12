/**
 * \file iterators.h
 * \authors 
 * \brief header containing the implementation of the class iterator.
 */

#ifndef __ITERATORS_
#define __ITERATORS_

#include<memory> //unique_ptr
#include<utility> //pair

#include "node.h"
#include "bst.h"

template<class K, class V, class CO>
template<class oK, class oV>
class bst<K, V, CO>::_iterator {

    node* here;

public:
	
    using value_type = std::pair<oK, oV>;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
	
    _iterator() = default;

    explicit _iterator(node * p) : here{ p } {}

    ~_iterator() = default;

    _iterator& operator++() {
        if (here) 
        {
            if (here->right) 
            {            	
                here = here->right->findLowest();
            }
            else
            {
                here = here->findUpper();
            }
        }
        return *this;
    }

    _iterator operator++(int) {
        auto old(*this);
        operator++();
        return old;
    }


    bool operator==(const _iterator& other_it) { return here == other_it.here; }

    bool operator!=(const _iterator& other_it) { return !(*this == other_it); }

    reference operator*() { return here->data; }

    pointer operator->() { return &(*(*this)); }

};

#endif //__ITERATORS_