#include "encoder.hh"
#include <assert.h>

Encoder::Encoder(std::string file)
{
    input_file_(file, ios::binary);
    output_file_(file + ".comp", ios::binary);

    assert(input_file_.open());
    assert(output_file_.open());

    eof_reached_ = false;
    writer_(&output_file_, nullptr);

    huffman_encoder_();   
}

Encoder::~Encoder()
{
    if(input_file_){
        input_file_.close();
    }

    if(output_file_){
        output_file_.close();
    }
}

int Encoder::read_symbol()
{
    assert(!eof_reached_);
    
    if(input_file_.eof()){
        eof_reached_ = true;
        return Huffman::HEOF;
    }

    return input_file_.get();
}

void Encoder::write_bits(Huffman::bits_t bits)
{
    for(bool b : bits){
        writer_.output_bit(b);
    }
}

void Encoder::encode()
{
    while(!eof_reached_){
        write_bits(huffman_encoder_.encode(read_symbol())); // write the encoded inputs
    }
}














