/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** AES
*/
#include <iostream>
#include "AES.hpp"

std::string convertHexaStringToChar(std::string const &hexaString)
{
    std::string result;
    for (std::size_t i = 0; i < hexaString.size(); i += 2) {
        std::string byte = hexaString.substr(i, 2);
        char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
        result += chr;
    }
    return result;
}

std::string Cryptography::AES::AES::encrypt(std::string const &message)
{
    std::vector<Key<SIZE_KEY>> cypheredKeys;
    std::string cypheredMessage;

    for (std::size_t i = 0; i < message.size(); i += 16) {
        auto key = Key<SIZE_KEY>(message.substr(i, 16), false, true);

        key.addRoundKey(_keys[0]);
        for (std::size_t i = 1; i < 10; ++i) {
            key.subBytes();
            key.shiftRows();
            key.mixColumns();
            key.addRoundKey(_keys[i]);
        }
        key.subBytes();
        key.shiftRows();
        key.addRoundKey(_keys[10]);

        cypheredKeys.push_back(key);
    }

    for (auto &key : cypheredKeys) {
        key.reverseLittleEndian();
        cypheredMessage += key.toString();
    }

    return cypheredMessage;
}

std::string Cryptography::AES::AES::decrypt(std::string const &message)
{
    std::string decryptedMessage;

    for (std::size_t i = 0; i < message.size(); i += 32) {
        auto key = Key<SIZE_KEY>(message.substr(i, 32));
        
        key.reverseLittleEndian();

        key.addRoundKey(_keys[10]);
        key.shiftRowsInv();
        key.subBytesInv();
        for (std::size_t i = 9; i > 0; --i) {
            key.addRoundKey(_keys[i]);
            key.mixColumnsInv();
            key.shiftRowsInv();
            key.subBytesInv();
        }
        key.addRoundKey(_keys[0]);
        for (std::size_t i = 0; i < SIZE_KEY; ++i) {
            for (std::size_t j = 0; j < SIZE_KEY; ++j) {
                unsigned char byte = key.get()[i].get()[j];
                if (byte == 0)
                    break;
                decryptedMessage.push_back(byte);
            }
        }
    }

    return decryptedMessage;
}