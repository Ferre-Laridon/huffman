#ifndef BUILD_CODES_H
#define BUILD_CODES_H

#include "data/binary-tree.h"
#include "util.h"
#include <vector>


void build(const data::Node<std::pair<Datum, unsigned long>>& tree, std::vector<Datum>& bits, std::vector<std::vector<Datum>>& codes);
std::unique_ptr<std::vector<std::vector<Datum>>> build_codes(const data::Node<std::pair<Datum, unsigned long>>& tree, const u64& domain_size);

#endif // !BUILD_CODES_H
