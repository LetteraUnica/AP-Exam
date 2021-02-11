#include <iostream>
#include <memory>
#include <utility>


#include "bst.h"
#include "node.h"
#include "iterators.h"

template <class K, class V, class CO>
auto bst<K, V, CO>::begin() noexcept
{
	if(root)
	{
		return iterator{ root->findLowest() };
	}
	return iterator{ nullptr };
}


template <class K, class V, class CO>
auto bst<K, V, CO>::begin() const noexcept
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
		node new_node = new node{x};
		root = &new_node;
		return std::pair<K, V>(iterator{ &new_node }, true);
	}
	node* current = root;
	while(current)
	{
		if (comp(x.data.first, current->data.first))
		{
			// If the key is smaller and left!=nullptr I go to the left		
			if(current->left)
				current = current->left;
			// If the left is empty I insert a new node
			else
			{
				node new_node = new node{x, current};
				return std::pair<K, V>(iterator{ &new_node }, true);
			}
		}
		else
		{
			// If the key is greater or equal and left!=nullptr I go to the right
			if (current->right)
				current = current->right;
			// If the right is empty I insert a new node
			else
			{
				node new_node = new node{ x, current };
				return std::pair<K, V>(iterator{ &new_node }, true);
			}
		}
	}
	
}

template <class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(pair&& x)
{
}
