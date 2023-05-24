#include "hash_functions.h"

size_t polynomial_rolling_hash::operator() (std::string const & str) const {
    size_t hash = 0;
    size_t p = 1;
    size_t b = 19;
    long m = 3298534883309ul;

    for(size_t chr = 0; chr < str.length(); chr++){
        hash += int(str[chr]) * p;
        p = (p*b) % m;
    }
    return hash;
}

size_t fnv1a_hash::operator() (std::string const & str) const {
    size_t prime = 0x00000100000001B3;
    size_t basis = 0xCBF29CE484222325;
    size_t hash = basis;

    for(size_t chr = 0; chr < str.length(); chr++){
        hash = hash^int(str[chr]);
        hash = hash*prime;
    }
    return hash;
    
}
