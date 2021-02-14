/**
 * \file bst.h
 * \authors Marco Sicklinger, Marco Sciorilli, Lorenzo Cavuoti
 * \brief header containing the implementation of the binary search tree class
*/

#ifndef	_BST_
#define _BST_

#include<memory> // unique_ptr
#include<utility> // pair
#include<functional> // less
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

/**
 * \brief Implements a binary search tree
 * \tparam K Type of the node key
 * \tparam V Type of the node value
 * \tparam CO Type of the comparison operator. Default std::less<K>
 */
template<class K, class V, class CO = std::less<K>>
class bst
{
private:
	
    using pair_type = std::pair<const K, V>;
    using key_type = K;
    using value_type = V;
    using reference = V&;

    // Struct holding the node of the tree, defined in node.h
    struct node;

    // Unique pointer to the root node
    std::unique_ptr<node> root;

    /**
	 * \brief Returns the key and value of the root of the given bst
	 * \param x bst to return the info
	 * \return std::pair<key_type, value_type> key and value pair of the root
	 */
    friend
        auto get_root(const bst& x) {
        auto root_info = std::make_pair(x.root->data.first, x.root->data.second);
        return root_info;
    }

    /**
     * \brief DA COMMENTARE
     * \param v 
     * \param first 
     * \param last 
     */
    void newbalancedtree(std::vector<pair_type>& v, int first, int last);
	
    /**
     * \brief DA COMMENTARE
     * \param x 
     * \param y 
     */
    void transplant(key_type& x, key_type& y);
	
    /**
     * \brief DA COMMENTARE
     * \param x 
     * \param y 
     * \param side 
     */
    void new_child(key_type& x, key_type& y, bool side);
    /**
     * \brief DA COMMENTARE
     * \param x 
     */
    void child_side(key_type& x);

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

    explicit bst(const pair_type& pair) { root.reset(new node{ pair }); }

    explicit bst(pair_type&& pair) { root.reset(new node{ std::move(pair) }); }

    bst(key_type&& _key, value_type&& _value) {
        root.reset(new node{ std::make_pair(_key, _value) });
    }

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
    bst(bst&& move_from) noexcept : root(std::move(move_from.root)) { move_from.root.reset(nullptr); }

    /**
     * \brief Move assignment of bst
     * \param move_from bst to be moved
     * \return bst& modified binary search tree
     */
    bst& operator=(bst&& move_from) noexcept {
        root = std::move(move_from.root);
        move_from.root.reset(nullptr);
        return *this;
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
    iterator end() noexcept;

    /**
     * \brief Function used to finish the iteration on the tree
     * \return const_iterator A const_iterator pointing to one past the last node,
     * i.e. the node past the one with the highest key
     */
    const_iterator end() const noexcept;

    /**
     * \brief Function used to finish the iteration on the tree
     * \return const_iterator A const_iterator pointing to one past the last node,
     * i.e. the node past the one with the highest key
     */
    const_iterator cend() const noexcept;

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

	// FORSE SI PUO' AGGIUNGERE NOEXEPT?
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
     * \brief Balances the bst, i.e. re-structures the tree in order to
     * minimize its depth
     */
    void balance();

    /**
     * \brief Removes the node with a given key from the tree
     * \param x key of the node to be removed
     */
    void erase(const key_type& x);

    /**
     * \brief Overload of the << operator, prints the tree in ascending order
     * \param os Stream where to print the content of the tree
     * \param x bst to be printed
     * \return os Stream where the content has been sent
     */
    friend
    std::ostream& operator<<(std::ostream& os, const bst& x) {
        for (auto p = x.cbegin(); p != x.cend(); ++p) {
            os << p << "\n";
        }
        os << std::endl;
        return os;
    }

    /**
     * \brief Overload of the [] operator, finds a value given the key
     * \param x Key to be found
     * \return If the key exists returns a reference to the associated value
     * Otherwise it adds a new node containing the input key and the default
     * value and returns a reference to the value
     */
    reference operator[](const key_type& x);

    /**
     * \brief Overload of the [] operator for moves
     * \param x Key to be found
     * \return If the key exists returns a reference to the associated value
     * Otherwise it adds a new node containing the input key and the default
     * value and returns a reference to the value
     */
    reference operator[](key_type&& x);

    void erase_node();

};

#include"methods.h"

#endif //__BST_