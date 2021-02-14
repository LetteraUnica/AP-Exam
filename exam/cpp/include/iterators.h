/**
 * \file iterators.h
 * \authors Marco Sicklinger, Marco Sciorilli, Lorenzo Cavuoti
 * \brief header containing the implementation of the bst iterator_ class
 */

#ifndef  _BST_ITERATORS_
#define  _BST_ITERATORS_

#include<memory> //unique_ptr
#include<utility> //pair

#include "bst.h"

/**
 * \brief Implements the iterator for the bst
 * \tparam oK type of the key
 * \tparam oV type of the value
 */
template<class K, class V, class CO>
template<class oK, class oV>
class bst<K, V, CO>::_iterator {

    //using node=typename bst<K,V,CO>::node;

    friend class bst;

    node* here;

public:

    using value_type = std::pair<oK, oV>;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    /**
     * \brief Default constructor of the class _iterator
     */
    _iterator() = default;

    /**
     * \brief Custom constructor of the class _iterator
     * \param p Raw pointer to node
     *
     * Creates an iterator pointing to the given node
     */
    explicit _iterator(node* p) : here{ p } {}

    _iterator(const _iterator& other_it) : here{ other_it.here } {}

    /**
     * \brief Default destructor of the class _iterator
     */
    ~_iterator() = default;

    /**
     * \brief Overload of the pre-increment operator ++
     * \return _iterator& pointing to the next node
     *
     * Used to traverse the tree from the leftmost to the rightmost node in
     * ascending key order
     */
    _iterator& operator++() {
        if (here) {
            if (here->right) {
                here = here->right->findLowest();
            }
            else {
                here = here->findUpper();
            }
        }
        return *this;
    }

    /**
     * \brief Overload of the post-increment operator ++
     * \return _iterator& before advancing to the next node
     *
     * Used to traverse the tree from the leftmost to the rightmost node in
     * ascending key order
     */
    _iterator operator++(int) {
        auto old(*this);
        operator++();
        return old;
    }

    /**
     * \brief Overload of the operator ==
     * \param other_it Iterator to be compared to
     * \return bool True if the iterators point to the same node, False otherwise
     */
    bool operator==(const _iterator& other_it) const { return here == other_it.here; }


    /**
     * \brief Overload of the operator !=
     * \param other_it Iterator to be compared to
     * \return bool False if the iterators point to the same node, True otherwise
     */
    bool operator!=(const _iterator& other_it) const { return !(*this == other_it); }

    /**
     * \brief Overload of the arrow operator ->
     * \return Pointer to the current node the iterator is pointing to
     */
    reference operator*() { return here->data; }

    /**
     * \brief Overload of the dereference operator *
     * \return Reference to the data of the node the iterator is pointing to
     */
    pointer operator->() { return &(*(*this)); }

    friend
        std::ostream& operator<<(std::ostream& os, const _iterator& it) {
        os << "(" << "key: " << it.here->data.first << ", value: " << it.here->data.second << ")";
        return os;
    }

};

#endif //__ITERATORS_