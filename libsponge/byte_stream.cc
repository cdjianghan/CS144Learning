#include "byte_stream.hh"
#include <iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`



using namespace std;

ByteStream::ByteStream(const size_t capacity):
    bytestream(""),
    cap(capacity),
    write_cnt(0),
    read_cnt(0),
    end_eof(false)
{}

size_t ByteStream::write(const string &data) {
    if(data.empty()) {
        return 0;
    }
    size_t res;
    if(remaining_capacity() > data.size()) {
        res = data.size();
        bytestream += data;
    }else {
        res = cap - bytestream.size();
        bytestream += data.substr(0,cap - bytestream.size());
    }
    write_cnt += res;
    return res;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return bytestream.substr(0,len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    bytestream = bytestream.substr(len,bytestream.size());
    read_cnt += len;
    cout << "-----------read_cnt:" << read_cnt << endl;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string res;
    if(len > bytestream.size()) {
        res = peek_output(bytestream.size());
        pop_output(bytestream.size());
    }else {
        res = peek_output(len);
        pop_output(len);
    }
    return res;
}

void ByteStream::end_input() {end_eof = true;}

bool ByteStream::input_ended() const { return end_eof; }

size_t ByteStream::buffer_size() const { return bytestream.size(); }

bool ByteStream::buffer_empty() const {
    return bytestream.empty();
}

bool ByteStream::eof() const { return end_eof&&bytestream.empty();}

size_t ByteStream::bytes_written() const { return write_cnt; }

size_t ByteStream::bytes_read() const { return read_cnt; }

size_t ByteStream::remaining_capacity() const { return cap - bytestream.size(); }
