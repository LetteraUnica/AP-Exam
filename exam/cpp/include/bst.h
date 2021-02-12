/**
 * \file node.h
 * \author
 * \brief header containing the implementation of the binary search tree
*/

#ifndef __BST_
#define __BST_

#include<memory> // unique_ptr
#include<utility> // pair
#include<functional> // less
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

#include"node.h"
#include"iterators.h"

template<class K, class V, class CO=std::less<K>>
class bst
{

    using pair_type = std::pair<const K, V>;
    using key_type = K;
    using value_type = V;
	
    struct node;

    std::unique_ptr<node> root;

public:

	// Comparison operator
    CO comp;
	
    template<class oK, class oV>
    class _iterator;

    using iterator = _iterator<K, V>;
    using const_iterator = _iterator<const K, const V>;

    bst() = default;

    ~bst() = default;

    bst(const bst& to_copy) {

        if (to_copy.root) { root.reset(new node{ to_copy.root }); }

    }

    bst& operator=(const bst& to_copy) {

        auto auxiliary{ to_copy };
        *this = std::move(auxiliary);
        return *this;

    }

	
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept { return iterator{ nullptr }; }

    const_iterator end() const noexcept { return const_iterator{ nullptr }; }

	/**
	 * \brief
	 * \return
	 */
    const_iterator cend() const noexcept { return const_iterator{ nullptr }; }
	
	/**
	 * \brief Inserts a new node in the tree and returns an iterator if the insertion was successful
	 * \param x Pair to be inserted of type std::pair<key, value>
	 * \return std::pair<Iterator,bool> The function returns a pair of:
	 * An iterator pointing to the node of the input pair
	 * A bool which is true if a new node has been allocated, false if the node is already in the tree
	 */
    std::pair<iterator, bool> insert(const pair_type& x);
    std::pair<iterator, bool> insert(pair_type&& x);

    //template<class... Types>
    //std::pair<iterator, bool> emplace(Types&&... args);

    iterator find(const key_type& x);

    const_iterator find(const key_type& x) const;

    void clear();
	
    friend
    std::ostream &operator<<(std::ostream &os, const bst &x) {
        for (auto p = x.cbegin(); p != x.cend(); ++p) {
            os << "(" << "key: " << p->data.first << ", value: " << p->data.second << ") " << "\n";
        }
        os << std::endl;
        return os;
    }

    V& operator[](const K& x);
    V& operator[](K&& x);
};

#endif //__BST_

#include "methods.h"