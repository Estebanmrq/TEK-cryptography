/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** PGPAES
*/

#include "PGPAES.hpp"
#include <iostream>

std::tuple<std::string, std::string> Cryptography::PGPAES::PGPAES::encrypt(std::string const &message)
{
    std::string encrypted_message = _aes.encrypt(message);
    std::string encrypted_aeskey = rsa.encrypt(_aes.getOkey(), true);

    return std::make_tuple(encrypted_aeskey, encrypted_message);
}

std::string Cryptography::PGPAES::PGPAES::decrypt(std::string const &message, std::string const &aeskey)
{
    AES::AES aes(RSA::RSA::messageToHexa(rsa.decrypt(aeskey)));

    return aes.decrypt(message);
}
