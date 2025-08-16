#ifndef TEST_BUILD

/*
*   This file is only active in non-test builds (i.e., builds where TEST_BUILD is not defined).
*/

#include <iostream>
#include "io/files.h"
#include "encoding/eof-encoding.h"
#include "encoding/huffman/huffman-encoding.h"
#include "encoding/bit-grouper.h"
#include "encoding/encoding-combiner.h"


/*
* This is the main entry point of your application.
* Note that it will only work in non-test builds.
*/
int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Too few arguments";
    }
    else if (argc > 4)
    {
        std::cout << "Too many arguments";
    }
    else
    {
        const std::string method(argv[1]);
        const std::string file1(argv[2]);
        const std::string file2(argv[3]);

        if (method == "compress")
        {
            std::cout << "Compressing ..." << std::endl;

            auto input = io::create_file_data_source(argv[2]);
            auto output = io::create_file_data_destination(argv[3]);

            auto eof = encoding::eof_encoding<256>();
            auto huffmanEncoder = huffman<257>();
            auto bit_grouper = encoding::bit_grouper<8>();

            auto combined = eof | huffmanEncoder | bit_grouper;

            auto input_stream = input->create_input_stream();
            auto output_stream = output->create_output_stream();

            combined->encode(*input_stream, *output_stream);
        }
        else if (std::string(argv[1]) == "decompress")
        {
            std::cout << "Decompressing ..." << std::endl;

            auto input = io::create_file_data_source(argv[2]);
            auto output = io::create_file_data_destination(argv[3]);

            auto eof = encoding::eof_encoding<256>();
            auto huffmanEncoder = huffman<257>();
            auto bit_grouper = encoding::bit_grouper<8>();

            auto encoder = eof | huffmanEncoder | bit_grouper;

            auto input_stream = input->create_input_stream();
            auto output_stream = output->create_output_stream();

            encoder->decode(*input_stream, *output_stream);
        }
    }

#ifdef NDEBUG
    std::cout << "You are running the release build" << std::endl;
#else
    std::cout << "You are running the debug build" << std::endl;
#endif
}

#endif