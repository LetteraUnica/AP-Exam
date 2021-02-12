#include <iostream>
#include <memory>
#include <utility>


#include "bst.h"
#include "node.h"
#include "iterators.h"


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
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::cbegin() const noexcept
{
	if (root)
	{
		return const_iterator{ root->findLowest() };
	}
	return const_iterator{ nullptr };
}


template <class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(const pair& x)
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

template <class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(pair&& x)
{
}


template <class K, class V, class CO>
void bst<K, V, CO>::clear()
{
	clear_node(root);
}

template <class N>
void clear_node(node<N>* n)
{
	if (n->left)
		clear_node(n->left);
	if (n->right)
		clear_node(n->right);

	delete n;
}

// Insertion with copy
template <class K, class V, class CO>
V& bst<K, V, CO>::operator[](const K& x)
{
	auto my_node = find(x);
	if(my_node)
		return my_node->data.second;

	res = insert(std::pair<K, V>(x, NULL));
	return *res.first;
}


// Insertion with move
template <class K, class V, class CO>
V& bst<K, V, CO>::operator[](K&& x)
{
	auto my_node = find(x);
	if (my_node)
		return my_node->data.second;
	return end().here;
}

iterator find(const key_type& x);
const_iterator find(const key_type& x) const;
