/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** Galois
*/

#include "Galois.hpp"

unsigned char Cryptography::AES::Galois::multiply(unsigned char val1, unsigned char val2)
{
    unsigned char res = 0;
    unsigned char msb = 0;
    
    for (unsigned char bit = 0; bit < 8; bit++) {
        if (val2 & 1)
            res ^= val1;

        msb = val1 & 0x80;
        val1 <<= 1;

        if (msb)
            val1 ^= 0x1B;

        val2 >>= 1;
    }
    return res & 0xFF;
}

const std::vector<std::vector<unsigned char>> Cryptography::AES::Galois::matrix = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2}
};

const std::vector<std::vector<unsigned char>> Cryptography::AES::Galois::matrixInv = {
        {14, 11, 13, 9},
        {9, 14, 11, 13},
        {13, 9, 14, 11},
        {11, 13, 9, 14}
};
