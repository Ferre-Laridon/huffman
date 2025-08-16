#include "encoding/huffman/build-codes.h"


void build(const data::Node<std::pair<Datum, unsigned long>>& tree, std::vector<Datum>& bits, std::vector<std::vector<Datum>>& codes)
{
    const data::Leaf<std::pair<Datum, unsigned long>>* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, unsigned long>>*>(&tree);
    const data::Branch<std::pair<Datum, unsigned long>>* branch = dynamic_cast<const data::Branch<std::pair<Datum, unsigned long>>*>(&tree);

    if (leaf != nullptr)
    {
        codes[leaf->get_value().first] = bits;
    }
    else if (branch != nullptr)
    {
        std::vector<Datum> left = bits;
        left.push_back(0);
        build(branch->get_left_child(), left, codes);

        std::vector<Datum> right = bits;
        right.push_back(1);
        build(branch->get_right_child(), right, codes);
    }
}

std::unique_ptr<std::vector<std::vector<Datum>>> build_codes(const data::Node<std::pair<Datum, unsigned long>>& tree, const u64& domain_size)
{
    std::vector<std::vector<Datum>> codes(domain_size);
    std::vector<Datum> bits;
    build(tree, bits, codes);
    return std::make_unique<std::vector<std::vector<Datum>>>(std::move(codes));
}
