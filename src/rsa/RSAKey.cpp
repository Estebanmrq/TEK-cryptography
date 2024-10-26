/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** RSAKey
*/

#include "RSAKey.hpp"


void Cryptography::RSA::RSAKey::load(mpz_class const &f, mpz_class const &n)
{
    auto ftmp = f.get_str(16);
    auto ntmp = n.get_str(16);

    _f = f;
    _n = n;

    _key = RSAKey::hexaBigEndianToLittleEndian(ftmp.size() % 2 == 0 ? ftmp : "0" + ftmp) + "-" + RSAKey::hexaBigEndianToLittleEndian(ntmp.size() % 2 == 0 ? ntmp : "0" + ntmp);
}

void Cryptography::RSA::RSAKey::load(std::string const &key)
{
    _key = key;

    auto sp = key.find("-");
    if (sp == std::string::npos)
        throw RSAKeyException("Invalid key format.");

    auto f = key.substr(0, sp);
    auto n = key.substr(sp + 1);

    if (f.size() == 0 || n.size() == 0)
        throw RSAKeyException("Invalid key format.");

    _f.set_str(RSAKey::hexaBigEndianToLittleEndian(f), 16);
    _n.set_str(RSAKey::hexaBigEndianToLittleEndian(n), 16);
}

std::string Cryptography::RSA::RSAKey::hexaBigEndianToLittleEndian(const std::string &hexa)
{
    std::string littleEndianHexa;

    if (hexa.size() % 2 != 0)
        throw RSAKeyException("The size of the \'" + hexa + "\' hexadecimal string must be a multiple of 2.");

    for (std::size_t i = 0; i < hexa.size(); i += 2) {
        std::string word = hexa.substr(i, 2);
        littleEndianHexa = word + littleEndianHexa;
    }
    return littleEndianHexa;
}
