#include <iostream>
#include <fstream>
#include "bitio.hh"
#include <string>
#include "assert.h"
#include "huffman.hh"

class Encoder {

  private:

    std::ifstream input_file_;
    std::ofstream output_file_;

    bool eof_reached_;
    BitIO writer_;

    Huffman huffman_encoder_;

    int read_symbol();                  // returns Huffman::HEOF when done;
    void write_bits(Huffman::bits_t);   // writes the bits to the file

  public:

    Encoder(std::string);
    ~Encoder();

    Encoder(const Encoder&) = delete;
    Encoder(Encoder&) = delete;
    Encoder& operator=(const Encoder&) = delete;
    Encoder& operator=(Encoder&&) = delete;

    void encode();

}

int main(int argc, char ** argv){

    assert(argc == 1);

    std::string name_base(argv[0]);

    std::ifstream input_file(name_base);
    std::ofstream output_file{name_base + ".comp" };

    BitIO reader(nullptr, &input_file);
    BitIO writer(&output_file, nullptr);

    
    bool bb = reader.input_bit();
    writer.output_bit(bb);

    input_file.close();
    output_file.close();
}
