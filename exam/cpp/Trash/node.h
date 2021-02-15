/**
 * \file node.h
 * \authors Marco Sicklinger, Marco Sciorilli, Lorenzo Cavuoti
 * \brief header containing the implementation of the bst node struct
*/

#ifndef _BST_NODE_
#define _BST_NODE_

#include<memory> //unique_ptr
#include<utility> //pair

#include "bst.h"

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

#endif //__NODE_