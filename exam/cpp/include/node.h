/**
 * \file node.h
 * \author
 * \brief header containing the implementation of the bst node
 */

#ifndef __NODE_
#define __NODE_

#include<memory> //unique_ptr
#include<utility> //pair

#include "bst.h"

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
    explicit node(pair_type n) 
    : data{ n }, left{ nullptr }, right{ nullptr }, parent{ nullptr } {}

    /**
     * \brief Custom constructor for the class node
     * \param n Data to be inserted in the node
     * \param p Parent of the node
     * 
     * Initializes a node with data and parent node
    */
    node(pair_type n, node* p)
    : data{ n }, left{ nullptr }, right{ nullptr }, parent{ p } {}

    /**
     * \brief Copy constructor for the class node
     * \param n Node to be copied
    */
    node(const node& n)
    : data{n.data}, left{nullptr}, right{nullptr}, parent{n.parent} {}

    /**
     * \brief Default destructor of the class node
    */
    ~node() noexcept = default;

    explicit node(const std::unique_ptr<node>& copy_from) :
        data{ copy_from->data }, left{ nullptr }, right{ nullptr }, parent{ nullptr }
    {
        if (copy_from->left) { left.reset(new node{ copy_from->left }); }
        if (copy_from->right) { left.reset(new node{ copy_from->right }); }
    }

    node* findLowest() noexcept
    {
        if (left) { return left->findLowest(); }
        return this;
    }

    node* findUpper() noexcept
    {
        if (parent)
        {
            if (parent->left == this) { return parent; }
            return parent->findUpper();
        }
        return parent;
    }
};

#endif //__NODE_