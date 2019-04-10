#include "bitio.hh"
#include <cassert>

BitIO::BitIO(std::ostream * os, std::istream * is)
{
    os_ = os;
    is_ = is;

    assert((os_ && !is_) || (!os_ && is_));

    buffer_ = 0;
    bit_count_ = -1;
    if(os_){
        bit_count_ = 0;
    }
}

BitIO::~BitIO()
{
    if(os_){
        if(bit_count_ > 0){
            os_->put(buffer_);
        }
    }
}

void BitIO::load_byte()
{
    assert(is_);
    buffer_ = is_->get();
    bit_count_ = 0;
}

void BitIO::write_byte()
{
    assert(os_);
    os_->put(buffer_);
    buffer_ = 0;
    bit_count_ = 0;
}

bool BitIO::input_bit()
{
    if(bit_count_ >= 8 || bit_count_ == -1){
        load_byte();
    }

    bool bit = buffer_ & ( 1 << bit_count_);
    ++bit_count_;
    return bit;
}

void BitIO::output_bit(bool bit)
{
    if(bit){
        buffer_ |= (1 << bit_count_);
    }
    ++bit_count_;
    if(bit_count_ >= 8){
        write_byte();
    }
}
