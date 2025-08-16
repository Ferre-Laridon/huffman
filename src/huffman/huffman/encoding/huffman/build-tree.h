#ifndef BUILD_TREE_H
#define BUILD_TREE_H

#include "util.h"
#include "data/binary-tree.h"
#include "frequency-table.h"

const unsigned long weight(const data::Node<std::pair<Datum, unsigned long>>& node);
std::unique_ptr<data::Node<std::pair<Datum, unsigned long>>> build_tree(const data::FrequencyTable<Datum>& frequencyTable);

#endif // !BUILD_TREE_H
