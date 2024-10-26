/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** RCon
*/

#include "RCon.hpp"

const std::vector<unsigned char> Cryptography::AES::RCon::_RConValues = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

unsigned char Cryptography::AES::RCon::get(unsigned char ind)
{
    if (_RConValues.size() <= (std::size_t)ind)
        throw RConError("The ind must be between 0 and " + std::to_string(_RConValues.size() - 1) + ", got " + std::to_string(ind));
    return _RConValues[ind];
}
