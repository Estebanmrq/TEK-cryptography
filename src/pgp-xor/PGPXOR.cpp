/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** PGPXOR
*/

#include "PGPXOR.hpp"
#include <iostream>

std::tuple<std::string, std::string> Cryptography::PGPXOR::PGPXOR::encrypt(std::string const &message)
{
    std::string encrypted_message = _xor.encrypt(message);
    std::string encrypted_xorkey = rsa.encrypt(_xor.getKey(), true);

    return std::make_tuple(encrypted_xorkey, encrypted_message);
}

std::string Cryptography::PGPXOR::PGPXOR::decrypt(std::string const &message, std::string const &xorkey)
{
    XOR XOR(RSA::RSA::messageToHexa(rsa.decrypt(xorkey)));
    return XOR.decrypt(message);
}
