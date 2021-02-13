/**
 * \file bst.h
 * \authors Marco Sicklinger, Marco Sciorilli, Lorenzo Cavuoti
 * \brief header containing the implementation of the binary search tree class
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

/**
 * \brief Implements a binary search tree
 * \tparam K Type of the node key
 * \tparam V Type of the node value
 * \tparam CO Type of the comparison operator. Default std::less<K>
 */
template<class K, class V, class CO=std::less<K>>
class bst
{

    using pair_type = std::pair<const K, V>;
    using key_type = K;
    using value_type = V;

	// Struct holding the node of the tree, defined in node.h
    struct node;

	// Unique pointer to the root node
    std::unique_ptr<node> root;

public:

	// Comparison operator
    CO comp;

	// Class holding the iterator of the bst, defined in iterators.h
    template<class oK, class oV>
    class _iterator;
    using iterator = _iterator<K, V>;
    using const_iterator = _iterator<const K, const V>;

    /**
     * \brief Default constructor of bst
     */
    bst() = default;

    /**
     * \brief Default destructor of bst
     */
    ~bst() = default;

    /**
     * \brief Copy constructor of bst
     * \param to_copy bst to be copied
     *
     * Creates a bst by copying the content of the input tree
     */
    bst(const bst& to_copy) {
        if (to_copy.root) { root.reset(new node{ to_copy.root }); }
    }

    /**
     * \brief Copy assignment of bst
     * \param to_copy bst to be copied
     * \return bst& copied binary search tree
     */
    bst& operator=(const bst& to_copy) {

        auto auxiliary{ to_copy };
        *this = std::move(auxiliary);
        return *this;

    }

    /**
     * \brief Move constructor of bst
     * \param move_from bst to be moved
     *
     * Creates a bst by moving the content of the input tree
     */
    bst(bst&& move_from) noexcept
	: root(std::move(move_from.root)) { move_from.root.reset(nullptr); }

    /**
     * \brief Move assignment of bst 
     * \param move_from bst to be moved
     * \return bst& modified binary search tree
     */
    bst& operator=(bst&& move_from) {
        root = std::move(move_from.root);
        move_from.root.reset(nullptr);
    }

    /**
     * \brief Initializes the iterator on the tree
     * \return iterator An iterator pointing to the leftmost node, i.e. the one
     * with the smallest key
     */
    iterator begin() noexcept;

	/**
     * \brief Initializes the iterator on the tree
     * \return const_iterator A const_iterator pointing to the leftmost node
     * i.e. the one with the smallest key
     */
    const_iterator begin() const noexcept;
	
    /**
     * \brief Initializes the iterator on the tree
     * \return const_iterator A const_iterator pointing to the leftmost node
     * i.e. the one with the smallest key
     */
    const_iterator cbegin() const noexcept;

    /**
     * \brief Function used to finish the iteration on the tree
     * \return iterator An iterator pointing to one past the last node,
     * i.e. the node past the one with the highest key
     */
    iterator end() noexcept { return iterator{ nullptr }; }

    /**
	 * \brief Function used to finish the iteration on the tree
	 * \return const_iterator A const_iterator pointing to one past the last node,
	 * i.e. the node past the one with the highest key
	 */
    const_iterator end() const noexcept { return const_iterator{ nullptr }; }

    /**
	 * \brief Function used to finish the iteration on the tree
	 * \return const_iterator A const_iterator pointing to one past the last node,
	 * i.e. the node past the one with the highest key
	 */
    const_iterator cend() const noexcept { return const_iterator{ nullptr }; }
	
	
	/**
	 * \brief Inserts a new node in the tree
	 * \param x Pair to be inserted of type std::pair<key, value>
	 * \return std::pair<iterator,bool> The function returns a pair of:
	 * An iterator pointing to the inserted node
	 * A bool which is true if a new node has been allocated, false if the node
	 * is already in the tree
	 */
    std::pair<iterator, bool> insert(const pair_type& x);

    /**
     * \brief Inserts a new node in the tree
     * \param x Pair to be inserted of type std::pair<key, value>
     * \return std::pair<iterator,bool> The function returns a pair of:
     * An iterator pointing to the inserted node
     * A bool which is true if a new node has been allocated, false if the node
     * is already in the tree
     */
    std::pair<iterator, bool> insert(pair_type&& x);

	// FORSE ABBIAMO CAPITO MALE LA FUNZIONE, PINNA LA IMPLEMENTA IN MODO DIVERSO
    /**
     * \brief Inserts a new node in the tree constructed in-place
     * \tparam Types NON SO COSA METTERE
     * \param args A key value pair std::pair<key, value>
     * \return std::pair<iterator,bool> The function returns a pair of:
     * An iterator pointing to the inserted node
     * A bool which is true if a new node has been allocated, false if the node
     * is already in the tree
     */
    template<class... Types>
    std::pair<iterator, bool> emplace(Types&&... args);

	// PINNA QUA ELIMINA DIRETTAMENTE LA RADICE (root.reset();)
    /**
     * \brief Clears the content of the tree without any memory leak
     */
    void clear();

    /**
     * \brief Finds a node in the bst given the key
     * \param x Key to be found
     * \return iterator pointing to the node with that key if the key exists
     * Otherwise it returns an iterator pointing to "nullptr"
     */
    iterator find(const key_type& x);

	/**
     * \brief Finds a node in the bst given the key
     * \param x Key to be found
     * \return const_iterator pointing to the node with that key if the key exists
     * Otherwise it returns an iterator pointing to "nullptr"
     */
    const_iterator find(const key_type& x) const;


    /**
     * \brief Balances the bst, i.e. re-structures the tree in order
     * to minimize its depth
     */
    void balance();

	// DA IMPLEMENTARE
    /**
     * \brief Removes the node with a given key from the tree
     * \param x key of the node to be removed
     */
    void erase(const key_type& x);

	
    /**
     * \brief Overload of the [] operator, finds a value given the key
     * \param x Key to be found
     * \return If the key exists returns a reference to the associated value
     * Otherwise it adds a new node containing the input key and the default
     * value and returns a reference to the value
     */
    V& operator[](const K& x);

    /**
	 * \brief Overload of the [] operator for moves
	 * \param x Key to be found
	 * \return If the key exists returns a reference to the associated value
	 * Otherwise it adds a new node containing the input key and the default
	 * value and returns a reference to the value
	 */
    V& operator[](K&& x);

	// NON MI PIACE LA DOCUMENTAZIONE
    /**
     * \brief Overload of the << operator, prints the tree in ascending order
     * \param Stream to which to print the content of the tree
     * \param x Bst to be printed
     * \return std::ostream Stream where the content has been sent
     */
    friend
    std::ostream &operator<<(std::ostream &os, const bst &x) {
        for (auto p = x.cbegin(); p != x.cend(); ++p) {
            os << "(" << "key: " << p->data.first << ", value: " << p->data.second << ") " << "\n";
        }
        os << std::endl;
        return os;
    }

};

#endif //__BST_

#include "methods.h"