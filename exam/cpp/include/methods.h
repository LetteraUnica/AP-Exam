#include <iostream>
#include <memory>
#include <utility>


#include "bst.h"
#include "node.h"
#include "iterators.h"

#ifndef __METHODS_
#define __METHODS_

template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::begin() noexcept
{
	if(root)
	{
		return iterator{ root->findLowest() };
	}
	return iterator{ nullptr };
}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::begin() const noexcept
{
	if (root)
	{
		return const_iterator{ root->findLowest() };
	}
	return const_iterator{ nullptr };
}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::cbegin() const noexcept
{
	if (root)
	{
		return const_iterator{ root->findLowest() };
	}
	return const_iterator{ nullptr };
}


template <class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(const pair_type& x)
{
	// If the root is null I insert a new node here
	if(!root)
	{
		auto new_node = new node{x};
		root.reset(new_node);
		return std::pair<K, V>(iterator{ &new_node }, true);
	}
	node* current = root.get();
	while(current)
	{
		// x.key < current.key
		if (comp(x.data.first, current->data.first))
		{
			// If the key is smaller and left!=nullptr I go to the left		
			if(current->left)
				current = current->left;
			// If the left is empty I insert a new node
			else
			{
				auto new_node = new node{x, current};
				return std::pair<K, V>(iterator{ new_node }, true);
			}
		}
		// x.key > current.key
		else if (comp(current->data.first, x.data.first))
		{
			// If the key is greater or equal and left!=nullptr I go to the right
			if (current->right)
				current = current->right;
			// If the right is empty I insert a new node
			else
			{
				auto new_node = new node{ x, current };
				return std::pair<K, V>(iterator{ new_node }, true);
			}
		}
		// x.key == current.key
		else
		{
			return std::pair<K, V>(iterator{ current }, false);
		}
	}
	
}


template<class K, class V, class CO>
std::pair<iterator, bool> bst<K, V, CO>::insert(pair&& x)
{
	node* here = root.get();
	node* parent = nullptr;
	// if there is no root node, i create one
	if (root == nullptr)
	{
		root.reset(new node(std::forward<pair_type>(x), parent))
			return std::pair<K, V>(iterator{ here }, true);
	}
	// Navigate through the tree until i find che correct parent node

	while (here != nullptr) {


		parent = here;
		//if a node with the same key already exist, return the boolean saying that the new node was not created
		if (!comp(x.first, here->data.first) && !comp(x.first, here->data.first)) {
			return std::pair<K, V>(iterator{ here }, false);
		}
		else if (comp(x.first, here->data.first)) {
			here = here->left;
		}
		else {
			here = here->right;
		}

	}

	//create the new node depending on the parent node previously found
	if (comp(x.first, parent->data.first))
		parent->left.reset(new node(std::forward<pair_type>(x), parent));
	return std::pair<K, V>(iterator{ parent->left.get() }, true);
	else
		parent->right.reset(new node(std::forward<pair_type>(x), parent));
	return std::pair<K, V>(iterator{ parent->right.get() }, true);

}


template <class K, class V, class CO>
template<class... Types>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::emplace(Types&&... args) {

	if (std::is_constructible<pair_type, Types...>::value) {
		return insert(std::pair<const K, V>(std::forward<Types>(args)...));
	}
	return std::pair<typename bst<K, V, CO>::iterator, bool>(typename bst<K, V, CO>::iterator{ nullptr }, false);

}


template <class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(pair_type&& x)
{
}


template <class K, class V, class CO>
void bst<K, V, CO>::clear()
{
	clear_node(root);
}

template <class K, class V, class CO>
void clear_node(typename bst<K, V, CO>::node* n)
{
	if (n->left)
		clear_node(n->left);
	if (n->right)
		clear_node(n->right);

	delete n;
}

template<class K, class V, class CO>
void bst<K, V, CO>::balance() {
	std::vector<std::pair<K, V>> v;
	iterator first{ this->begin() };
	iterator last{ this->end() };
	if (first == last)//tree is Empty
		return v;
	else
	{
		while (first < last) {
			v.push_back(*first);
			++first;
		}
	}
	clear();
	newbalancedtree(v, 0, v.size() - 1);
}

// build a balanced tree from an vector of node
template<class K, class V, class CO>
void bst<K, V, CO>::newbalancedtree(std::vector<pair>& v, int first, int last) {
	if (last == v.size() - 1) { //si può spostare in balance, ed evitre confonti inutili, ma non si può inserire un vettore qualsiasi
		std::sort(v.begin(), v.end());
	}
	if (first == last) {
		return;
	}

	int middle = (first + last) / 2;
	insert(v[middle]);
	newbalancedtree(v, first, middle - 1);
	newbalancedtree(v, middle + 1, last);
}


// Insertion with copy
template <class K, class V, class CO>
V& bst<K, V, CO>::operator[](const K& x)
{	
	iterator node_found = find(x);
	if(node_found)
		return node_found.here->data.second;

	iterator node_inserted = insert(std::pair<K, V>(x, NULL)).first;
	return node_inserted.here->data.second;
}


// Insertion with move
template <class K, class V, class CO>
V& bst<K, V, CO>::operator[](K&& x)
{
	iterator node_found = find(std::move(x));
	if (node_found)
		return node_found.here->data.second;

	iterator node_inserted = insert(std::pair<K, V>(x, NULL)).first;
	return node_inserted.here->data.second;
}


template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::find(const key_type& x) {

	for (const auto& item : *this) {

		if (!comp(item->here->data.first, x) && !comp(x, item->here->data.first)) {
			return iterator{ item->here };
		}

	}

	return end();

}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::find(const key_type& x) const {

	for (const auto& item : *this) {

		if (!comp(item->here->data.first, x) && !comp(x, item->here->data.first)) {
			return const_iterator{ item->here };
		}

	}

	return cend();

}

#endif