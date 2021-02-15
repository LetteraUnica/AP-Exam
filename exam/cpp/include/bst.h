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
     * \brief Returns the depth of the bst, mainly for testing purposes
     * \return unsigned int The depth of the bst
     */
    unsigned int get_depth();
	
     /**
     * \brief Balances the bst, i.e. re-structures the tree in order to
     * minimize its depth
     */
    void balance();

    void newbalancedtree(std::vector<pair_type>& v, int first, int last);
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
	 * \brief Returns the key and value of the root of the given bst
	 * \param x bst to return the info
	 * \return std::pair<key_type, value_type> key and value pair of the root
	 */
    friend
        auto get_root(const bst& x) {
        auto root_info=std::make_pair(x.root->data.first, x.root->data.second);
        return root_info; 
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

/**
 * \brief Definition of the node struct
 */
template<class K, class V, class CO>
struct bst<K, V, CO>::node {

    // Data contained in the node
    pair_type data;

    // Unique pointer to the left node
    std::unique_ptr<node> left;
    // Unique pointer to the right node
    std::unique_ptr<node> right;
    // Raw pointer to the parent node
    node* parent;

    /**
     * \brief Default constructor for the class node.
    */
    node() = default;

    /**
     * \brief Custom constructor for the class node
     * \param n Data to be inserted in the node
     *
     * Initializes a node with its data
    */
    explicit node(pair_type& n)
        : data{ n }, left{ nullptr }, right{ nullptr }, parent{ nullptr } {}

    /**
     * \brief Custom constructor for the class node
     * \param n Data to be inserted in the node
     * \param new_parent Parent of the node
     *
     * Initializes a node with data and parent node
    */
    node(const pair_type& n, node* new_parent) : data{ n }, left{ nullptr }, right{ nullptr }, parent{ new_parent } {}

    /**
     * \brief Default destructor of the class node
    */
    ~node() noexcept = default;

    /**
     * \brief DA COMMENTARE
     * \param copy_from
     */
    explicit node(const std::unique_ptr<node>& copy_from) :
        data{ copy_from->data }, left{ nullptr }, right{ nullptr }, parent{ nullptr } {

        if (copy_from->left) { left.reset(new node{ copy_from->left }); }

        if (copy_from->right) { left.reset(new node{ copy_from->right }); }
    }

    /**
     * \brief Finds the node with the lowest key in the tree
     * \return Raw pointer to the node with the smallest key
     */
    node* findLowest() noexcept {

        if (left) { return left->findLowest(); }
        return this;

    }

    /**
     * \brief DA COMMENTARE
     * \return
     */
    node* findUpper() {

        if (parent) {
            if (parent->left.get() == this) { return parent; }
            return parent->findUpper();
        }
        return parent;

    }

    /**
     * \brief DA COMMENTARE
     * \return
     */
    node* rightmost() {

        if (right) { return right->rightmost(); }
        return right.get();

    }

};

/**
 * \brief Implements the iterator for the bst
 * \tparam oK type of the key
 * \tparam oV type of the value
 */
template<class K, class V, class CO>
template<class oK, class oV>
class bst<K, V, CO>::_iterator {

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


#endif //__BST_