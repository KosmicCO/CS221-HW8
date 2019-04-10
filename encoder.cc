#include "encoder.hh"
#include <assert.h>

Encoder::Encoder(const char * file) {
    input_file_ = new std::ifstream();
    output_file_ = new std::ofstream();

    input_file_->open(file);
    output_file_->open("enc.txt.comp");

    assert(* input_file_);
    assert(* output_file_);

    eof_reached_ = false;
    writer_ = new BitIO(output_file_, nullptr);

    huffman_encoder_ = new Huffman();   
}

Encoder::~Encoder()
{
    if(input_file_){
        input_file_->close();
    }

    if(output_file_){
        output_file_->close();
    }
    
    delete writer_;
    delete input_file_;
    delete output_file_;
}

int Encoder::read_symbol()
{
    assert(!eof_reached_);
    
    if(input_file_->eof()){
        eof_reached_ = true;
        return Huffman::HEOF;
    }

    return input_file_->get();
}

void Encoder::write_bits(Huffman::bits_t bits)
{
    for(bool b : bits){
        writer_->output_bit(b);
    }
}

void Encoder::encode()
{
    while(!eof_reached_){
        write_bits(huffman_encoder_->encode(read_symbol())); // write the encoded inputs
    }
}

int main(int argc, const char ** argv)
{


    if(false) { //argc != 2){
        std::cerr << "Needs two command arguments";
        std::cout << argc << argv;
        std::cout.flush();
        assert(false);
    }

    Encoder encode("enc");
    encode.encode();
}












