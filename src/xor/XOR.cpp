/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** XOR
*/

#include <sstream>
#include <iomanip>
#include "XOR.hpp"

std::string Cryptography::XOR::encrypt(std::string const &message, bool fill)
{
    std::string encryptedMessage;

    for (std::size_t i = 0; i < _key.size(); i++) {
        if (i < message.size())
            encryptedMessage += message[i] ^ _key[i];
        else if (fill) {
            encryptedMessage += 0 ^ _key[i];
        }
    }
    return _hexaBigEndianToLittleEndian(_convertStringToHexa(encryptedMessage), 2);
}

std::string Cryptography::XOR::decrypt(std::string const &message, bool fill)
{
    auto bytes = _convertHexaToBytes(_hexaBigEndianToLittleEndian(message, 2));
    std::string decryptedMessage;

    for (std::size_t i = 0; i < _key.size(); i++) {
        if (i < bytes.size()) {
            auto tmp = bytes[i] ^ _key[i % _key.size()];
            if (tmp == 0)
                break;
            decryptedMessage += tmp;
        } else if (fill) {
            decryptedMessage += 0 ^ _key[i % _key.size()];
        }
    }
    return decryptedMessage;
}

std::string Cryptography::XOR::_hexaBigEndianToLittleEndian(const std::string &hexa, std::size_t wordSize)
{
    std::string littleEndianHexa;

    if (wordSize % 2 != 0) {
        throw XORException("The word size must be a multiple of 2.");
    }

    if (hexa.size() % wordSize != 0) {
        throw XORException("The size of the hexadecimal string must be a multiple of the word size.");
    }

    for (std::size_t i = 0; i < hexa.size(); i += wordSize) {
        std::string word = hexa.substr(i, wordSize);
        littleEndianHexa = word + littleEndianHexa;
    }
    return littleEndianHexa;
}

std::string Cryptography::XOR::_convertStringToHexa(const std::string &str)
{
    std::string res;

    for (auto &byte : str) {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
        res += ss.str();
    }
    return res;
}

std::vector<unsigned char> Cryptography::XOR::_convertHexaToBytes(const std::string &hexa)
{
    std::vector<unsigned char> res;

    for (std::size_t i = 0; i < hexa.size(); i += 2) {
        std::string byte = hexa.substr(i, 2);
        res.push_back(std::stoi(byte, nullptr, 16));
    }
    return res;
}