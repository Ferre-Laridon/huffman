#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <functional>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <algorithm>


namespace data
{
	template<typename T>
	class Node
	{
	public:
		// virtual destructor
		virtual ~Node() {}
	};

	template<typename T>
	class Branch : public Node<T>
	{
		// part of hierarchy (pointer or reference), ownership, auto freed, no modification
		std::unique_ptr<const Node<T>> left_child;
		std::unique_ptr<const Node<T>> right_child;

	public:
		Branch(std::unique_ptr<const Node<T>> left_child, std::unique_ptr<const Node<T>> right_child) : left_child(std::move(left_child)), right_child(std::move(right_child))
		{
			assert(left_child != nullptr);
			assert(right_child != nullptr);
		}

		const Node<T>& get_left_child() const
		{
			return *left_child;
		}

		const Node<T>& get_right_child() const
		{
			return *right_child;
		}

	};


	template<typename T>
	class Leaf : public Node<T>
	{
	private:
		// own copy (no pointer or reference), no modification
		const T value;

	public:
		Leaf(const T& value) : value(value)
		{

		};

		const T& get_value() const
		{
			return value;
		}

	};

	template<typename IN, typename OUT>
	std::unique_ptr<Node<OUT>> map(const Node<IN>& tree, std::function<OUT(const IN&)> function)
	{
		/*
		if tree is leaf
			create new leaf with value = function(old_value)
		else tree is branch
			new_left_child = apply map to left child
			new_right_child = apply map to right child
			create new branch with new_left_child and new_right_child
		*/

		if (const auto* leaf = dynamic_cast<const Leaf<IN>*>(&tree))
		{
			return std::make_unique<Leaf<OUT>>(function(leaf->get_value()));
		}
		else if (const auto* branch = dynamic_cast<const Branch<IN>*>(&tree))
		{
			return std::make_unique<Branch<OUT>>(map(branch->get_left_child(), function), map(branch->get_right_child(), function));
		}
		else 
		{
			throw std::runtime_error("Node type not found");
		}
	}
}

#endif