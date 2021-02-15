#ifndef _BST_METHODS_
#define _BST_METHODS_

#include <vector>

#include "bst.h"


template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::begin() noexcept
{
	if (root)
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
typename bst<K, V, CO>::iterator bst<K, V, CO>::end() noexcept
{
	return iterator{ nullptr };
}


template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::end() const noexcept
{
	return const_iterator{ nullptr };
}


template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::cend() const noexcept
{
	return const_iterator{ nullptr };
}

template <class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(const pair_type& x)
{
	// If the root is null I insert a new node here
	if (!root)
	{
		root.reset(new node{ x });
		return std::make_pair(iterator{ root.get() }, true);
	}

	node* here = root.get();
	node* parent = nullptr;
	while (here) {

		parent = here;

		// x.key < here.key
		if (comp(x.first, here->data.first))
		{
			here = here->left.get();
		}
		// x.key > here.key
		else if (comp(here->data.first, x.first))
		{
			here = here->right.get();
		}
		// x.key == here.key
		else
		{
			return std::make_pair(iterator{ here }, false);
		}

	}

	//create the new node depending on the parent node previously found
	auto auxiliary_node = new node{ x, parent };

	if (comp(x.first, parent->data.first)) {
		parent->left.reset(auxiliary_node);
		return std::make_pair(iterator{ parent->left.get() }, true);
	}
	
	parent->right.reset(auxiliary_node);
	return std::make_pair(iterator{ parent->right.get() }, true);
}

template<class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(pair_type&& x)
{
	// if there is no root node, i create one
	if (!root)
	{
		root.reset(new node{ std::forward<pair_type>(x) });
		return std::make_pair<iterator, bool>(iterator{ root.get() }, true);
	}

	// Navigate through the tree until i find che correct parent node
	node* here = root.get();
	node* parent = nullptr;

	while (here) {

		parent = here;
		//if a node with the same key already exist, return the boolean saying that the new node was not created
		if (!comp(x.first, here->data.first) && !comp(here->data.first, x.first))
		{
			return std::make_pair<iterator, bool>(iterator{ here }, false);
		}
		if (comp(x.first, here->data.first))
		{
			here = here->left.get();
		}
		else
		{
			here = here->right.get();
		}

	}

	//create the new node depending on the parent node previously found
	auto auxiliary_node = new node{ std::forward<pair_type>(x), parent };

	if (comp(x.first, parent->data.first))
	{
		parent->left.reset(auxiliary_node);
		return std::make_pair<iterator, bool>(iterator{ parent->left.get() }, true);
	}
	parent->right.reset(auxiliary_node);
	return std::make_pair<iterator, bool>(iterator{ parent->right.get() }, true);
}

template <class K, class V, class CO>
template<class... Types>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::emplace(Types&&... args) {
	if (std::is_constructible<pair_type, Types...>::value) {
		return insert(std::make_pair<const K, V>(std::forward<Types>(args)...));
	}
	return std::make_pair<typename bst<K, V, CO>::iterator, bool>(typename bst<K, V, CO>::iterator{ nullptr }, false);
}

template <class K, class V, class CO>
void bst<K, V, CO>::clear()
{
	root.reset(nullptr);
}

template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::find(const key_type& x) {
	for (auto p = cbegin(); p != cend(); ++p) {
		if (!comp(p.here->data.first, x) && !comp(x, p.here->data.first)) {
			return iterator{ p.here };
		}
	}
	return end();
}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::find(const key_type& x) const {
	for (auto p = cbegin(); p != cend(); ++p) {
		if (!comp(p.here->data.first, x) && !comp(x, p.here->data.first)) {
			return const_iterator{ p.here };
		}
	}
	return cend();
}

template <class K, class V, class CO>
unsigned bst<K, V, CO>::get_depth()
{
	// If the root is null I return depth 0
	if (!root)
		return 0;

	// For each node in the tree I compute its depth and store the maximum in max_depth
	unsigned max_depth{ 0 };
	for (auto p = cbegin(); p != cend(); ++p) {
		unsigned int depth{ 1 };
		node* here = root.get();
		auto x = p.here->data;
		
		while (here) {
			// x.key < here.key
			if (comp(x.first, here->data.first))
			{
				here = here->left.get();
			}
			// x.key > here.key
			else if (comp(here->data.first, x.first))
			{
				here = here->right.get();
			}
			// x.key == here.key
			else
			{
				if (depth > max_depth)
					max_depth = depth;
				break;
			}
			depth++;
		}
	}

	return max_depth;
}

template<class K, class V, class CO>
void bst<K, V, CO>::balance() {
	std::vector<std::pair<K, V>> v;
	iterator first{ this->begin() };
	iterator last{ this->end() };
	if (first == last)//tree is Empty
		return;
	else
	{
		while (first < last) {
			v.push_back(first.here->data);
			++first;
		}
	}
	clear();
	newbalancedtree(v, 0, v.size() - 1);
}

//built a balanced tree from an vector of node
template<class K, class V, class CO>
void bst<K, V, CO>::newbalancedtree(std::vector<pair_type>& v, int first, int last) {
	if (first == last) {
		return;
	}
	int middle = (first + last) / 2;
	insert(v[middle]);
	newbalancedtree(v, first, middle - 1);
	newbalancedtree(v, middle + 1, last);
}


template<class K, class V, class CO>
void bst<K, V, CO>::erase(const key_type& x) {

	iterator my{ find(x) }; //have to return the one with no left child
	if (my == end()) { std::cout << "key is not in the tree" << std::endl; }
	else {
		node* here = my.node();
		if ((here->left == nullptr) && (here->right == nullptr)) { //if no child, erase the node
			here->erase_node();
			return;
		}
		if (here->left == nullptr) {          //if no left child, substitute with left
			transplant(here->data.first, here->right->data.first);
			return;
		}
		if (here->right == nullptr) {         //if no left child, substitute with left
			transplant(here->data.first, here->left->data.first);
			return;
		}
		else {
			node* smaller = here->right->findLowest(); //find the smaller node to the right of the one to erase
			here->data.first = smaller->data.first;
			here->data.second = smaller->data.second;
			if (smaller->right == nullptr) { //if the smaller node has no child, erase it
				smaller->erase_node();
				return;
			}
			else {   //if it has a right child, substitute smaller with its child
				smaller->right->parent = smaller->parent;
				smaller->perent->left = smaller->right;
				smaller->erase_node();
				return;
			}
		}
	}

}


template<class K, class V, class CO>
void bst<K, V, CO>::transplant(key_type& x, key_type& y) {
	iterator one{ find(x) };
	iterator two{ find(y) };//have to return the one with no left child
	node* here_one = one.node();
	node* here_two = two.node();
	if (here_one->parent == nullptr) {
		root = here_two;
		here_one->erase_node();
		return;
	}
	else {
		bool side{ child_side(here_one->data.first) };
		new_child(here_one->parent->data.first, here_two->data.first, side);
		here_one->erase_node();
	}
	return;
}

template <class K, class V, class CO>
void bst<K, V, CO>::new_child(key_type& x, key_type& y, bool side) {
	iterator one{ find(x) };
	iterator two{ find(y) };//have to return the one with no left child
	node* here_one = one.node();
	node* here_two = two.node();
	if (side == false) {
		here_one->left = here_two;
	}
	else {
		here_one->right = here_two;
	}
	here_two->parent = here_one;
	return;
}

template <class K, class V, class CO>
void bst<K, V, CO>::child_side(key_type& x) {
	iterator my{ find(key) };
	node* here = my.node();
	if (here->parent->right == here)
		return 1;
	else {
		return 0;
	}
}

// Insertion with copy
template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](const key_type& x)
{
	iterator node_found = find(x);
	if (node_found.here)
		return node_found.here->data.second;

	iterator node_inserted = insert(std::make_pair(x, value_type{})).first;
	return node_inserted.here->data.second;
}


// Insertion with move
template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](key_type&& x)
{
	iterator node_found = find(std::move(x));
	if (node_found.here)
		return node_found.here->data.second;

	iterator node_inserted = insert(std::make_pair(x, value_type{})).first;
	return node_inserted.here->data.second;
}

template<class K, class V, class CO>
void erase_node(typename bst<K, V, CO>::node* N) {
	N->data.clear();
	N->left.reset();
	N->right.reset();
	N->parent = nullptr;
}

#endif //__METHODS_