#include <iostream>
#include <fstream>
#include "bitio.hh"
#include <string>
#include "assert.h"
#include "huffman.hh"

class Encoder {

  public:

    Encoder(const char * file);
    ~Encoder();

    Encoder(const Encoder&) = delete;
    Encoder(Encoder&) = delete;
    Encoder& operator=(const Encoder&) = delete;
    Encoder& operator=(Encoder&&) = delete;

    void encode();

  private:

    std::ifstream * input_file_;
    std::ofstream * output_file_;

    bool eof_reached_;
    BitIO * writer_;

    Huffman * huffman_encoder_;

    int read_symbol();                  // returns Huffman::HEOF when done
    void write_bits(Huffman::bits_t bits);   // writes the bits to the file
};
