#include <iostream>
#include <vector>

typedef unsigned char byte;

struct IInputStream {
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

struct IOutputStream {
    virtual void Write(byte value) = 0;
};


class VectorOutput : public IOutputStream {
public:
    VectorOutput(std::vector<byte>* output_buffer): buf(output_buffer) {

    }

    virtual void Write(byte value) {
        buf->push_back(value);
    }


private:
    std::vector<byte>* buf;
};


class VectorInput : public IInputStream {
public:
    VectorInput(std::vector<byte>* input_buffer ) : buf(input_buffer), pos(0) {
    }

    virtual bool Read(byte& value) {
        if (pos >= buf->size())
            return false;
        value = (*buf)[pos++];
        return true;
    }
private:
    std::vector<byte>* buf;
    size_t pos;
};

class BitReader {
public:
    BitReader(IInputStream& in_stream) : in(in_stream), buf(0), pos(0) {
    }

    bool read_bit(byte& value) {
        if (pos == 0) {
            bool res = in.Read(buf);
            if (!res) {
                return false;
            }
        }
        // pos = 0
        // 1000 0000 >> 7 = 0000 0001 & 1 = 1
        // pos = 7
        // 0000 0001 >> 0 =  0000 0001 & 1 = 1
        value = (buf >> (7 - pos++)) & 1;
        if (pos == 8) {
            pos = 0;
        }
        return true;
    }
private:
    IInputStream& in;
    byte buf;
    int pos;

};


class BitWriter {
public:
    BitWriter(IOutputStream& out_stream) : out(out_stream), buf(0), pos(0) {
    }

    void write_bit(byte value) {
        value &= 1;

        buf = buf | (value << (7 - pos++));
        if (pos == 8) {
            flush();
        }
    }

    void flush() {
        if (pos > 0) {
            out.Write(buf);
            buf = 0;
            pos = 0;
        }
    }
private:
    IOutputStream& out;
    byte buf;
    byte pos;
};


int main(int argc, const char * argv[]) {
    std::vector<byte> vec_output;
    VectorOutput vo(&vec_output);
    BitWriter bw(vo);
    bw.write_bit(1);
    bw.write_bit(0);
    bw.write_bit(1);
    bw.write_bit(0);
    bw.write_bit(1);
    bw.write_bit(0);
    bw.write_bit(1);
    bw.write_bit(0);

    bw.write_bit(1);
    bw.write_bit(1);
    bw.flush();
    //10101010|11 000000

    VectorInput vi(&vec_output);
    BitReader br(vi);

    byte value = 0;
    while (br.read_bit(value)) {
        std::cout << (int)value;
    }
    std::cout << std::endl;


    std::cout << "OK" << std::endl;
}
