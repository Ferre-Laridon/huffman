#include "build-tree.h"

const unsigned long weight(const data::Node<std::pair<Datum, unsigned long>>& node)
{
	const data::Leaf<std::pair<Datum, unsigned long>>* leaf;
	if ((leaf = dynamic_cast<const data::Leaf<std::pair<Datum, unsigned long>>*>(&node)) != nullptr)
	{
		return leaf->get_value().second;
	}
	else 
	{
		const data::Branch<std::pair<Datum, unsigned long>>& branch = dynamic_cast<const data::Branch<std::pair<Datum, unsigned long>>&>(node);
		return weight(branch.get_left_child()) + weight(branch.get_right_child());
	}
}

std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>> build_tree(const data::FrequencyTable<Datum>& frequencyTable)
{
	std::vector<std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>>> leaves;
	for (const Datum& d : frequencyTable.values())
	{
		leaves.push_back(std::make_unique<data::Leaf<std::pair<Datum, unsigned long>>>(std::make_pair(d, frequencyTable[d])));
	}

	while (leaves.size() > 1)
	{
		std::sort(leaves.begin(), leaves.end(), [](std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>>& param1, std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>>& param2) 
			{
				return weight(*param1) > weight(*param2);
			});
		std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>> last = std::move(leaves.back());
		leaves.pop_back();
		std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>> secondToLast = std::move(leaves.back());
		leaves.pop_back();

		std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>> branch = std::make_unique<data::Branch<std::pair<Datum, unsigned long>>>(std::move(last), std::move(secondToLast));
		leaves.push_back(std::move(branch));
	}

	return std::move(leaves.back());
}
